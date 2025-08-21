/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// High-performance lock-free thread filter implementation
//
// PERFORMANCE CONTRACT:
// - add(), remove(), accept() are optimized for signal-safe hot paths
// - These methods assume slot_id comes from registerThread() (undefined behavior otherwise)

#include "threadFilter.h"
#include "branch_hints.h"

#include <cstdlib>
#include <thread>
#include <algorithm>
#include <cstring>

ThreadFilter::ShardHead ThreadFilter::_free_heads[ThreadFilter::kShardCount] {};

ThreadFilter::ThreadFilter() : _enabled(false) {
    // Initialize chunk pointers to null (lazy allocation)
    for (int i = 0; i < kMaxChunks; ++i) {
        _chunks[i].store(nullptr, std::memory_order_relaxed);
    }
    _free_list = std::make_unique<FreeListNode[]>(kFreeListSize);

    // Initialize the first chunk
    initializeChunk(0);
    // ordering is fine because we are not enabled yet
    initFreeList();
}

ThreadFilter::~ThreadFilter() {
    // Make the filter inert for any concurrent readers
    _enabled.store(false, std::memory_order_release);
    // Reset free-list heads and nodes first
    for (int s = 0; s < kShardCount; ++s) {
        _free_heads[s].head.store(-1, std::memory_order_relaxed);
    }
    for (int i = 0; i < kFreeListSize; ++i) {
        _free_list[i].value.store(-1, std::memory_order_relaxed);
        _free_list[i].next.store(-1, std::memory_order_relaxed);
    }
    // Publish 0 chunks to stop range scans (collect)
    _num_chunks.store(0, std::memory_order_release);
    // Detach and delete chunks
    for (int i = 0; i < kMaxChunks; ++i) {
        ChunkStorage* chunk = _chunks[i].exchange(nullptr, std::memory_order_acq_rel);
        delete chunk;
    }
}

void ThreadFilter::initializeChunk(int chunk_idx) {
    if (chunk_idx >= kMaxChunks) return;

    // Check if chunk already exists
    ChunkStorage* existing = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (existing != nullptr) return;

    // Allocate and initialize new chunk completely before swapping
    ChunkStorage* new_chunk = new ChunkStorage();
    for (auto& slot : new_chunk->slots) {
        slot.value.store(-1, std::memory_order_relaxed);
    }

    // Try to install it atomically
    ChunkStorage* expected = nullptr;
    if (_chunks[chunk_idx].compare_exchange_strong(expected, new_chunk, std::memory_order_acq_rel)) {
        // Successfully installed
    } else {
        // Another thread beat us to it - clean up our allocation
        delete new_chunk;
    }
}

ThreadFilter::SlotID ThreadFilter::registerThread() {
    // If disabled, block new registrations
    if (!_enabled.load(std::memory_order_acquire)) {
        return -1;
    }

    // First, try to get a slot from the free list (lock-free stack)
    SlotID reused_slot = popFromFreeList();
    if (reused_slot >= 0) {
        return reused_slot;
    }

    // Allocate a new slot
    SlotID index = _next_index.fetch_add(1, std::memory_order_relaxed);
    if (index >= kMaxThreads) {
        // Revert the increment and return failure
        _next_index.fetch_sub(1, std::memory_order_relaxed);
        return -1;
    }

    const int chunk_idx = index >> kChunkShift;

    // Ensure the chunk is initialized (lock-free)
    if (chunk_idx >= _num_chunks.load(std::memory_order_acquire)) {
        // Update the chunk count atomically
        int expected_chunks = chunk_idx;
        int desired_chunks = chunk_idx + 1;
        while (!_num_chunks.compare_exchange_weak(expected_chunks, desired_chunks,
                                                   std::memory_order_acq_rel)) {
            if (expected_chunks > chunk_idx) {
                break; // Another thread already updated it
            }
            desired_chunks = expected_chunks + 1;
        }
    }

    // Initialize the chunk if needed
    initializeChunk(chunk_idx);

    return index;
}

void ThreadFilter::initFreeList() {
    // Initialize the free list storage
    for (int i = 0; i < kFreeListSize; ++i) {
        _free_list[i].value.store(-1, std::memory_order_relaxed);
        _free_list[i].next.store(-1, std::memory_order_relaxed);
    }

    // Reset the free heads for each shard
    for (int s = 0; s < kShardCount; ++s) {
        _free_heads[s].head.store(-1, std::memory_order_relaxed);
    }
}

bool ThreadFilter::accept(SlotID slot_id) const {
    // Fast path: if disabled, accept everything (relaxed to avoid fences on hot path)
    if (unlikely(!_enabled.load(std::memory_order_relaxed))) {
        return true;
    }
    if (unlikely(slot_id < 0)) return false;

    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;

    // Fast path: assume valid slot_id from registerThread()
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (likely(chunk != nullptr)) {
        return chunk->slots[slot_idx].value.load(std::memory_order_acquire) != -1;
    }
    return false;
}

void ThreadFilter::add(int tid, SlotID slot_id) {
    // PRECONDITION: slot_id must be from registerThread() or negative
    // Undefined behavior for invalid positive slot_ids (performance optimization)
    if (slot_id < 0) return;

    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;

    // Fast path: assume valid slot_id from registerThread()
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (likely(chunk != nullptr)) {
        chunk->slots[slot_idx].value.store(tid, std::memory_order_release);
    }
}

void ThreadFilter::remove(SlotID slot_id) {
    // PRECONDITION: slot_id must be from registerThread() or negative
    // Undefined behavior for invalid positive slot_ids (performance optimization)
    if (slot_id < 0) return;

    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;

    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (likely(chunk != nullptr)) {
        chunk->slots[slot_idx].value.store(-1, std::memory_order_release);
    }
}

void ThreadFilter::unregisterThread(SlotID slot_id) {
    if (slot_id < 0) return;
    remove(slot_id);
    pushToFreeList(slot_id);
}

bool ThreadFilter::pushToFreeList(SlotID slot_id) {
    // Lock-free sharded Treiber stack push
    const int shard = shardOfSlot(slot_id);
    auto& head      = _free_heads[shard].head; // private cache-line

    for (int i = 0; i < kFreeListSize; ++i) {
        int expected = -1;
        if (_free_list[i].value.compare_exchange_strong(
                expected, slot_id, std::memory_order_acq_rel)) {
            // Link node into this shard’s Treiber stack
            int old_head;
            do {
                old_head = head.load(std::memory_order_acquire);
                _free_list[i].next.store(old_head, std::memory_order_relaxed);
            } while (!head.compare_exchange_weak(old_head, i,
                       std::memory_order_release, std::memory_order_relaxed));
            return true;
        }
    }
    return false; // Free list full, slot is lost but this is rare
}

ThreadFilter::SlotID ThreadFilter::popFromFreeList() {
    // Lock-free sharded Treiber stack pop
    int hash = static_cast<int>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
    int start = shardOf(hash);

    for (int pass = 0; pass < kShardCount; ++pass) {
        int s      = (start + pass) & (kShardCount - 1);
        auto& head = _free_heads[s].head;

        while (true) {
            int node = head.load(std::memory_order_acquire);
            if (node == -1) break;                 // shard empty → try next

            int next = _free_list[node].next.load(std::memory_order_relaxed);
            if (head.compare_exchange_weak(node, next,
                                           std::memory_order_release,
                                           std::memory_order_relaxed))
            {
                int id = _free_list[node].value.exchange(-1,
                              std::memory_order_relaxed);
                _free_list[node].next.store(-1, std::memory_order_relaxed);
                return id;
            }
        }
    }
    return -1; // Empty list
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    
    // Reserve space for efficiency
    // The eventual resize is not the bottleneck, so we reserve a reasonable size
    tids.reserve(512);
    
    // Scan only initialized chunks
    int num_chunks = _num_chunks.load(std::memory_order_relaxed);
    for (int chunk_idx = 0; chunk_idx < num_chunks; ++chunk_idx) {
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
        if (chunk == nullptr) {
            continue;  // Skip unallocated chunks
        }
        
        for (const auto& slot : chunk->slots) {
            int slot_tid = slot.value.load(std::memory_order_acquire);
            if (slot_tid != -1) {
                tids.push_back(slot_tid);
            }
        }
    }
    
    // Optional: shrink if we over-reserved significantly
    if (tids.capacity() > tids.size() * 2) {
        tids.shrink_to_fit();
    }
}

void ThreadFilter::init(const char* filter) {
    // Simple logic: any filter value (including "0") enables filtering
    // Only explicitly registered threads via addThread() will be sampled
    // Previously we had a syntax where we could manually force some thread IDs.
    // This is no longer supported.
    _enabled.store(filter != nullptr, std::memory_order_release);
}

bool ThreadFilter::enabled() const {
    return _enabled.load(std::memory_order_acquire);
}
