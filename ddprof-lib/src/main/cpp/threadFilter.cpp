// Copyright (C) Datadog 2025
// High-performance lock-free thread filter implementation

#include "threadFilter.h"

#include <cstdlib>
#include <thread>
#include <algorithm>

ThreadFilter::ThreadFilter() : _enabled(false) {
    // Initialize chunk pointers to null (lazy allocation)
    for (int i = 0; i < kMaxChunks; ++i) {
        _chunks[i].store(nullptr, std::memory_order_relaxed);
    }
    _free_list = std::make_unique<FreeListNode[]>(kFreeListSize);
    
    // Initialize the first chunk
    initializeChunk(0);
    clear();
}

ThreadFilter::~ThreadFilter() {
    // Clean up allocated chunks
    for (int i = 0; i < kMaxChunks; ++i) {
        ChunkStorage* chunk = _chunks[i].load(std::memory_order_relaxed);
        delete chunk;
    }
}

void ThreadFilter::initializeChunk(int chunk_idx) {
    if (chunk_idx >= kMaxChunks) return;
    
    // Check if chunk already exists
    ChunkStorage* existing = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (existing != nullptr) return;
    
    // Allocate new chunk
    ChunkStorage* new_chunk = new ChunkStorage();
    
    // Try to install it atomically
    ChunkStorage* expected = nullptr;
    if (_chunks[chunk_idx].compare_exchange_strong(expected, new_chunk, std::memory_order_acq_rel)) {
        // Successfully installed - initialize all slots
        for (auto& slot : new_chunk->slots) {
            slot.value.store(-1, std::memory_order_relaxed);
        }
        new_chunk->initialized.store(true, std::memory_order_release);
    } else {
        // Another thread beat us to it - clean up our allocation
        delete new_chunk;
    }
}

ThreadFilter::SlotID ThreadFilter::registerThread() {
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

void ThreadFilter::clear() {
    // Clear all initialized chunks
    int num_chunks = _num_chunks.load(std::memory_order_relaxed);
    for (int i = 0; i < num_chunks; ++i) {
        ChunkStorage* chunk = _chunks[i].load(std::memory_order_relaxed);
        if (chunk != nullptr) {
            for (auto& slot : chunk->slots) {
                slot.value.store(-1, std::memory_order_relaxed);
            }
        }
    }
    
    // Clear the free list
    for (int i = 0; i < kFreeListSize; ++i) {
        _free_list[i].value.store(-1, std::memory_order_relaxed);
        _free_list[i].next.store(-1, std::memory_order_relaxed);
    }
    _free_list_head.store(-1, std::memory_order_relaxed);
    _active_slots.store(0, std::memory_order_relaxed);
}

bool ThreadFilter::accept(SlotID slot_id) const {
    if (!_enabled) {
        return true;
    }
    if (slot_id < 0) return false;
    
    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;
    
    if (chunk_idx >= kMaxChunks) return false;
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (chunk == nullptr) return false;  // Fail-fast if not allocated
    
    return chunk->slots[slot_idx].value.load(std::memory_order_acquire) != -1;
}

void ThreadFilter::add(int tid, SlotID slot_id) {
    if (slot_id < 0) return;
    
    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;
    
    if (chunk_idx >= kMaxChunks) return;
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (chunk == nullptr) return;  // Fail-fast if not allocated
    
    // Store the tid and increment active slots if this was previously empty
    int old_value = chunk->slots[slot_idx].value.exchange(tid, std::memory_order_acq_rel);
    if (old_value == -1) {
        _active_slots.fetch_add(1, std::memory_order_relaxed);
    }
}

void ThreadFilter::remove(SlotID slot_id) {
    if (slot_id < 0) return;
    
    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;
    
    if (chunk_idx >= kMaxChunks) return;
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_relaxed);
    if (chunk == nullptr) return;  // Fail-fast if not allocated
    
    // Remove the tid and decrement active slots if this was previously occupied
    int old_value = chunk->slots[slot_idx].value.exchange(-1, std::memory_order_acq_rel);
    if (old_value != -1) {
        _active_slots.fetch_sub(1, std::memory_order_relaxed);
    }
}

void ThreadFilter::unregisterThread(SlotID slot_id) {
    if (slot_id < 0) return;

    // Clear the slot first
    remove(slot_id);

    // Add to free list for reuse
    pushToFreeList(slot_id);
}

bool ThreadFilter::pushToFreeList(SlotID slot_id) {
    // Lock-free Treiber stack push
    for (int i = 0; i < kFreeListSize; ++i) {
        int expected = -1;
        if (_free_list[i].value.compare_exchange_strong(expected, slot_id, std::memory_order_acq_rel)) {
            // Successfully stored in this slot
            int old_head = _free_list_head.load(std::memory_order_acquire);
            do {
                _free_list[i].next.store(old_head, std::memory_order_relaxed);
            } while (!_free_list_head.compare_exchange_weak(old_head, i, std::memory_order_acq_rel));
            return true;
        }
    }
    return false; // Free list full, slot is lost but this is rare
}

ThreadFilter::SlotID ThreadFilter::popFromFreeList() {
    // Lock-free Treiber stack pop
    while (true) {
        int head = _free_list_head.load(std::memory_order_acquire);
        if (head == -1) {
            return -1; // Empty list
        }
        
        int slot_id = _free_list[head].value.load(std::memory_order_acquire);
        int next = _free_list[head].next.load(std::memory_order_acquire);
        
        // Try to update the head
        if (_free_list_head.compare_exchange_weak(head, next, std::memory_order_acq_rel)) {
            // Clear the node
            _free_list[head].value.store(-1, std::memory_order_relaxed);
            _free_list[head].next.store(-1, std::memory_order_relaxed);
            return slot_id;
        }
        // Retry if another thread modified the head
    }
}

void ThreadFilter::collect(std::vector<int>& tids) const {
    tids.clear();
    
    // Early exit if no active slots
    int active_count = _active_slots.load(std::memory_order_relaxed);
    if (active_count == 0) {
        return;
    }
    
    // Reserve space for efficiency
    tids.reserve(active_count);
    
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
    if (!filter) {
        return;
    }
    // TODO: Implement parsing of filter string if needed
    _enabled = true;
}

bool ThreadFilter::enabled() const {
    return _enabled;
}
