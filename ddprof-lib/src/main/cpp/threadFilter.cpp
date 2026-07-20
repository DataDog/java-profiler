/*
 * Copyright 2025, 2026 Datadog, Inc
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
#include "arch.h"
#include "counters.h"
#include "nativeMem.h"
#include "os.h"
#include "threadLocalData.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <algorithm>
#include <cstring>

ThreadFilter::ShardHead ThreadFilter::_free_heads[ThreadFilter::kShardCount] {};

#ifdef UNIT_TEST
std::atomic<ThreadFilter::BlockRunPublishObserver>
    ThreadFilter::_block_run_publish_observer{nullptr};

void ThreadFilter::setBlockRunPublishObserverForTest(BlockRunPublishObserver observer) {
    _block_run_publish_observer.store(observer, std::memory_order_release);
}
#endif

ThreadFilter::ThreadFilter()
    : _enabled(false), _registry_active(false), _track_unfiltered_wall(false) {
    // Initialize chunk pointers to null (lazy allocation)
    for (int i = 0; i < kMaxChunks; ++i) {
        _chunks[i].store(nullptr, std::memory_order_relaxed);
    }
    _free_list = std::make_unique<FreeListNode[]>(kFreeListSize);
    for (auto& entry : _tid_index) {
        entry.store(0, std::memory_order_relaxed);
    }
    NativeMem::record(NM_THREAD_FILTER,
                      (long long)(kFreeListSize * sizeof(FreeListNode)));

    // Initialize the first chunk
    initializeChunk(0);
    // ordering is fine because we are not enabled yet
    initFreeList();
}

// This function is not called as we keep the profiler alive
// Memory orders should be adjusted if we want to unload the profiler
// This could have a perf impact on reading chunk variables.
ThreadFilter::~ThreadFilter() {
    // Make the filter inert for any concurrent readers
    _enabled.store(false, std::memory_order_release);
    _registry_active.store(false, std::memory_order_release);
    _track_unfiltered_wall.store(false, std::memory_order_release);
    _recording_epoch.store(0, std::memory_order_release);
    // Reset free-list heads and nodes first
    for (int s = 0; s < kShardCount; ++s) {
        _free_heads[s].head.store(-1, std::memory_order_relaxed);
    }
    for (int i = 0; i < kFreeListSize; ++i) {
        _free_list[i].value.store(-1, std::memory_order_relaxed);
        _free_list[i].next.store(-1, std::memory_order_relaxed);
    }
    for (auto& entry : _tid_index) {
        entry.store(0, std::memory_order_relaxed);
    }
    // Publish 0 chunks to stop range scans (collect)
    _num_chunks.store(0, std::memory_order_release);
    // Detach and delete chunks. Record the decrement after the delete so the
    // gauge reflects the free only once it has happened.
    for (int i = 0; i < kMaxChunks; ++i) {
        ChunkStorage* chunk = _chunks[i].exchange(nullptr, std::memory_order_acquire);
        delete chunk;
        if (chunk != nullptr) {
            NativeMem::record(NM_THREAD_FILTER, -(long long)sizeof(ChunkStorage));
        }
    }
    // Free the FreeListNode[] explicitly before recording, rather than letting
    // the unique_ptr free it after this destructor returns, so the decrement
    // does not lead the actual free.
    _free_list.reset();
    NativeMem::record(NM_THREAD_FILTER,
                      -(long long)(kFreeListSize * sizeof(FreeListNode)));
}

void ThreadFilter::initializeChunk(int chunk_idx) {
    if (chunk_idx >= kMaxChunks) return;

    // Check if chunk already exists
    ChunkStorage* existing = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (existing != nullptr) return;

    // Allocate and initialize new chunk completely before swapping
    ChunkStorage* new_chunk = new ChunkStorage();
    for (auto& slot : new_chunk->slots) {
        slot.tid.store(-1, std::memory_order_relaxed);
        slot.recording_epoch.store(0, std::memory_order_relaxed);
        slot.context_window_state.store(0, std::memory_order_relaxed);
        slot.active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);
        slot.unowned_blocked_fallback_enabled.store(1, std::memory_order_relaxed);
    }

    // Try to install it atomically
    ChunkStorage* expected = nullptr;
    if (_chunks[chunk_idx].compare_exchange_strong(expected, new_chunk, std::memory_order_release)) {
        // Successfully installed
        NativeMem::record(NM_THREAD_FILTER, (long long)sizeof(ChunkStorage));
    } else {
        // Another thread beat us to it - clean up our allocation
        delete new_chunk;
    }
}

ThreadFilter::SlotID ThreadFilter::registerThread(int tid) {
    if (!_registry_active.load(std::memory_order_acquire)) {
        return -1;
    }
    std::lock_guard<std::mutex> lock(_registry_lock);

    if (tid >= 0) {
        SlotID existing = lookupSlotIdByTid(tid);
        if (existing >= 0) {
            RecordingEpoch epoch = recordingEpoch();
            if (epoch != 0) {
                refreshSlotForRecording(slotForId(existing), epoch);
            }
            return existing;
        }
    }

    RecordingEpoch epoch = recordingEpoch();

    // First, try to get a slot from the free list (lock-free stack)
    SlotID reused_slot = popFromFreeList();
    if (reused_slot >= 0) {
        Slot* slot = slotForId(reused_slot);
        slot->lifecycle_generation.fetch_add(1, std::memory_order_acq_rel);
        slot->recording_epoch.store(0, std::memory_order_relaxed);
        slot->context_window_state.store(0, std::memory_order_relaxed);
        slot->enableUnownedBlockedFallback();
        slot->clearActiveBlockRun(OSThreadState::UNKNOWN);
        slot->tid.store(tid, std::memory_order_release);
        if (tid >= 0 && !indexSlot(reused_slot, tid)) {
            slot->tid.store(-1, std::memory_order_release);
            pushToFreeList(reused_slot);
            Counters::increment(THREAD_REGISTRY_INDEX_FAILURES);
            return -1;
        }
        if (epoch != 0) {
            slot->recording_epoch.store(epoch, std::memory_order_release);
        }
        return reused_slot;
    }

    // Allocate a new slot
    SlotID index = _next_index.fetch_add(1, std::memory_order_relaxed);
    if (index >= kMaxThreads) {
        // Revert the increment and return failure
        _next_index.fetch_sub(1, std::memory_order_relaxed);
        Counters::increment(THREAD_REGISTRY_CAPACITY_EXHAUSTED);
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

    Slot* slot = slotForId(index);
    slot->lifecycle_generation.fetch_add(1, std::memory_order_acq_rel);
    slot->recording_epoch.store(0, std::memory_order_relaxed);
    slot->context_window_state.store(0, std::memory_order_relaxed);
    slot->enableUnownedBlockedFallback();
    slot->clearActiveBlockRun(OSThreadState::UNKNOWN);
    slot->tid.store(tid, std::memory_order_release);
    if (tid >= 0 && !indexSlot(index, tid)) {
        slot->tid.store(-1, std::memory_order_release);
        pushToFreeList(index);
        Counters::increment(THREAD_REGISTRY_INDEX_FAILURES);
        return -1;
    }
    if (epoch != 0) {
        slot->recording_epoch.store(epoch, std::memory_order_release);
    }

    return index;
}

void ThreadFilter::refreshSlotForRecording(Slot* slot, RecordingEpoch epoch) {
    if (slot == nullptr || epoch == 0 || slot->recordingEpoch() == epoch) {
        return;
    }

    // Make the retained identity ineligible before resetting its recording-local
    // payload, then publish the new epoch only after the reset is complete.
    slot->recording_epoch.store(0, std::memory_order_release);
    slot->context_window_state.store(0, std::memory_order_relaxed);
    slot->enableUnownedBlockedFallback();
    slot->clearActiveBlockRun(OSThreadState::UNKNOWN);
    slot->recording_epoch.store(epoch, std::memory_order_release);
}

bool ThreadFilter::indexSlot(SlotID slot_id, int tid) {
    unsigned start = hashTid(tid) & kTidIndexMask;
    for (int probe = 0; probe < kTidIndexSize; ++probe) {
        int index = (start + probe) & kTidIndexMask;
        int value = _tid_index[index].load(std::memory_order_acquire);
        if (value <= 0) {
            _tid_index[index].store(slot_id + 1, std::memory_order_release);
            return true;
        }
        if (value > 0) {
            Slot* slot = slotForId(value - 1);
            if (slot != nullptr && slot->nativeTid() == tid) {
                return value - 1 == slot_id;
            }
        }
    }
    return false;
}

void ThreadFilter::unindexSlot(SlotID slot_id, int tid) {
    if (tid < 0) return;
    unsigned start = hashTid(tid) & kTidIndexMask;
    for (int probe = 0; probe < kTidIndexSize; ++probe) {
        int index = (start + probe) & kTidIndexMask;
        int value = _tid_index[index].load(std::memory_order_acquire);
        if (value == 0) return;
        if (value == slot_id + 1) {
            int next = (index + 1) & kTidIndexMask;
            int replacement =
                _tid_index[next].load(std::memory_order_acquire) == 0 ? 0 : -1;
            _tid_index[index].store(replacement, std::memory_order_release);
            if (replacement == 0) {
                int previous = (index - 1) & kTidIndexMask;
                while (_tid_index[previous].load(std::memory_order_acquire) == -1) {
                    _tid_index[previous].store(0, std::memory_order_release);
                    previous = (previous - 1) & kTidIndexMask;
                }
            }
            return;
        }
    }
}

ThreadFilter::SlotID ThreadFilter::lookupSlotIdByTid(int tid) const {
    if (tid < 0) return -1;
    unsigned start = hashTid(tid) & kTidIndexMask;
    for (int probe = 0; probe < kTidIndexSize; ++probe) {
        int index = (start + probe) & kTidIndexMask;
        int value = _tid_index[index].load(std::memory_order_acquire);
        if (value == 0) return -1;
        if (value > 0) {
            Slot* slot = slotForId(value - 1);
            if (slot != nullptr && slot->nativeTid() == tid) {
                return value - 1;
            }
        }
    }
    return -1;
}

ThreadFilter::Slot* ThreadFilter::lookupByTid(int tid) const {
    SlotID slot_id = lookupSlotIdByTid(tid);
    return slot_id < 0 ? nullptr : slotForId(slot_id);
}

ThreadFilter::Slot* ThreadFilter::lookupByTid(int tid,
                                             RecordingEpoch epoch) const {
    if (epoch == 0 || recordingEpoch() != epoch) {
        return nullptr;
    }
    Slot* slot = lookupByTid(tid);
    return slot != nullptr && slot->recordingEpoch() == epoch ? slot : nullptr;
}

ThreadFilter::Slot* ThreadFilter::activeSlotForId(SlotID slot_id,
                                                  int tid) const {
    Slot* slot = slotForId(slot_id);
    if (slot == nullptr || slot->nativeTid() != tid) {
        return nullptr;
    }
    RecordingEpoch epoch = recordingEpoch();
    if (epoch != 0 && slot->recordingEpoch() != epoch) {
        return nullptr;
    }
    return slot;
}

bool ThreadFilter::lookupThreadEntry(ThreadEntry& entry,
                                     RecordingEpoch epoch) const {
    Slot* slot = epoch != 0 ? lookupByTid(entry.tid, epoch)
                            : lookupByTid(entry.tid);
    if (slot == nullptr) {
        return false;
    }
    entry.slot = slot;
    entry.lifecycle_generation = slot->lifecycleGeneration();
    entry.recording_epoch = slot->recordingEpoch();
    return true;
}

ThreadFilter::SlotID ThreadFilter::ensureCurrentThreadSlot(ProfiledThread* current) {
    if (current == nullptr) {
        return -1;
    }
    int tid = current->tid();
    if (unlikely(tid < 0)) {
        return -1;
    }

    SlotID slot_id = current->filterSlotId();
    if (likely(slot_id >= 0)) {
        if (likely(activeSlotForId(slot_id, tid) != nullptr)) {
            return slot_id;
        }
        current->setFilterSlotId(-1);
    }

    // Startup can register this TID centrally, but it cannot update another
    // pthread's TLS. registerThread(tid) reuses that existing slot.
    slot_id = registerThread(tid);
    if (slot_id >= 0) {
        current->setFilterSlotId(slot_id);
    }
    return slot_id;
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

    // This is not a fast path like the add operation.
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (likely(chunk != nullptr)) {
        return chunk->slots[slot_idx].inContextWindow();
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
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (likely(chunk != nullptr)) {
        Slot& slot = chunk->slots[slot_idx];
        if (slot.nativeTid() == -1) {
            std::lock_guard<std::mutex> lock(_registry_lock);
            if (slot.nativeTid() == -1) {
                slot.tid.store(tid, std::memory_order_release);
                if (!indexSlot(slot_id, tid)) {
                    slot.tid.store(-1, std::memory_order_release);
                    Counters::increment(THREAD_REGISTRY_INDEX_FAILURES);
                    return;
                }
            }
        }
        slot.enterContextWindow();
    }
}

void ThreadFilter::remove(SlotID slot_id) {
    // PRECONDITION: slot_id must be from registerThread() or negative
    // Undefined behavior for invalid positive slot_ids (performance optimization)
    if (slot_id < 0) return;

    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx = slot_id & kChunkMask;

    if (unlikely(chunk_idx >= kMaxChunks)) {
        assert(false && "Invalid slot_id in ThreadFilter::remove - should not happen after wall clock fix");
        return;
    }

    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (unlikely(chunk == nullptr)) {
        return;
    }

    chunk->slots[slot_idx].exitContextWindow();
}

void ThreadFilter::unregisterThread(SlotID slot_id, int expected_tid) {
    std::lock_guard<std::mutex> lock(_registry_lock);
    unregisterThreadLocked(slot_id, expected_tid);
}

void ThreadFilter::unregisterThreadLocked(SlotID slot_id, int expected_tid) {
    if (slot_id < 0) return;
    Slot* slot = slotForId(slot_id);
    if (slot == nullptr) return;
    int tid = slot->nativeTid();
    if (expected_tid >= 0 && tid != expected_tid) return;
    unindexSlot(slot_id, tid);
    slot->recording_epoch.store(0, std::memory_order_release);
    slot->tid.store(-1, std::memory_order_release);
    slot->context_window_state.store(0, std::memory_order_release);
    slot->enableUnownedBlockedFallback();
    slot->clearActiveBlockRun(OSThreadState::UNKNOWN);
    pushToFreeList(slot_id);
}

void ThreadFilter::unregisterThreadByTid(int tid) {
    std::lock_guard<std::mutex> lock(_registry_lock);
    SlotID slot_id = lookupSlotIdByTid(tid);
    if (slot_id >= 0) {
        unregisterThreadLocked(slot_id);
    }
}

void ThreadFilter::resetRegistrationsLocked() {
    int num_chunks = _num_chunks.load(std::memory_order_acquire);
    for (int chunk_idx = 0; chunk_idx < num_chunks; ++chunk_idx) {
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        if (chunk == nullptr) continue;
        for (int slot_idx = 0; slot_idx < kChunkSize; ++slot_idx) {
            Slot& slot = chunk->slots[slot_idx];
            if (slot.nativeTid() != -1) {
                slot.lifecycle_generation.fetch_add(1, std::memory_order_acq_rel);
            }
            slot.recording_epoch.store(0, std::memory_order_release);
            slot.tid.store(-1, std::memory_order_release);
            slot.context_window_state.store(0, std::memory_order_release);
            slot.enableUnownedBlockedFallback();
            slot.clearActiveBlockRun(OSThreadState::UNKNOWN);
        }
    }
    for (auto& entry : _tid_index) {
        entry.store(0, std::memory_order_relaxed);
    }
    _next_index.store(0, std::memory_order_relaxed);
    initFreeList();
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
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        if (chunk == nullptr) {
            continue;  // Skip unallocated chunks
        }

        for (const auto& slot : chunk->slots) {
            int slot_tid = slot.nativeTid();
            if (slot_tid != -1 && slot.inContextWindow()) {
                tids.push_back(slot_tid);
            }
        }
    }

    // Optional: shrink if we over-reserved significantly
    if (tids.capacity() > tids.size() * 2) {
        tids.shrink_to_fit();
    }
}

void ThreadFilter::collect(std::vector<ThreadEntry>& entries) const {
    entries.clear();
    entries.reserve(512);

    int num_chunks = _num_chunks.load(std::memory_order_relaxed);
    for (int chunk_idx = 0; chunk_idx < num_chunks; ++chunk_idx) {
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        if (chunk == nullptr) {
            continue;
        }

        for (auto& slot : chunk->slots) {
            int slot_tid = slot.nativeTid();
            if (slot_tid != -1 && slot.inContextWindow()) {
                entries.push_back({slot_tid, &slot, slot.lifecycleGeneration(),
                                   slot.recordingEpoch()});
            }
        }
    }
}

void ThreadFilter::clearActive() {
    int num_chunks = _num_chunks.load(std::memory_order_acquire);
    for (int chunk_idx = 0; chunk_idx < num_chunks; ++chunk_idx) {
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        if (chunk == nullptr) {
            continue;
        }

        for (int slot_idx = 0; slot_idx < kChunkSize; ++slot_idx) {
            Slot& slot = chunk->slots[slot_idx];
            slot.exitContextWindow();
            slot.enableUnownedBlockedFallback();
            slot.clearActiveBlockRun(OSThreadState::UNKNOWN);
        }
    }
}

void ThreadFilter::resetSlotRunState(SlotID slot_id) {
    if (slot_id < 0) return;
    int chunk_idx = slot_id >> kChunkShift;
    int slot_idx  = slot_id & kChunkMask;
    ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
    if (chunk != nullptr) {
        // Clear stale suppression state so a new thread in this slot cannot
        // inherit its predecessor's active block.
        chunk->slots[slot_idx].enableUnownedBlockedFallback();
        chunk->slots[slot_idx].clearActiveBlockRun(OSThreadState::UNKNOWN);
    }
}

u64 ThreadFilter::enterBlockedRun(SlotID slot_id, OSThreadState state,
                                  BlockRunOwner owner) {
    if (state == OSThreadState::UNKNOWN) return 0;
    Slot* s = slotForId(slot_id);
    if (s != nullptr) {
        u64 generation = 0;
        if (!s->tryPrepareActiveBlockRun(
                owner, &generation, unfilteredWallTrackingActive())) {
            return 0;
        }
        s->publishActiveBlockRun(state);
#ifdef UNIT_TEST
        BlockRunPublishObserver observer =
            _block_run_publish_observer.load(std::memory_order_acquire);
        if (observer != nullptr) observer(this, slot_id);
#endif
        return encodeBlockRunToken(slot_id, generation);
    }
    return 0;
}

void ThreadFilter::exitBlockedRun(SlotID slot_id) {
    Slot* s = slotForId(slot_id);
    if (s != nullptr) {
        s->clearActiveBlockRun(OSThreadState::RUNNABLE);
    }
}

bool ThreadFilter::exitBlockedRun(SlotID slot_id, u64 generation) {
    Slot* s = slotForId(slot_id);
    if (s == nullptr || generation == 0 ||
        s->activeBlockState() == OSThreadState::UNKNOWN ||
        s->activeBlockOwner() == BlockRunOwner::NONE ||
        s->blockGeneration() != generation) {
        return false;
    }
    s->clearActiveBlockRun(OSThreadState::RUNNABLE);
    return true;
}

bool ThreadFilter::snapshotAndExitBlockedRun(SlotID slot_id, u64 generation,
                                             BlockRunSnapshot* snapshot) {
    Slot* s = slotForId(slot_id);
    if (s == nullptr || generation == 0 ||
        s->activeBlockState() == OSThreadState::UNKNOWN ||
        s->activeBlockOwner() == BlockRunOwner::NONE ||
        s->blockGeneration() != generation) {
        return false;
    }
    if (snapshot != nullptr) *snapshot = s->snapshotBlockRun();
    s->clearActiveBlockRun(OSThreadState::RUNNABLE);
    return true;
}

bool ThreadFilter::isOwnedBlockSuppressionCandidate(
    const ThreadEntry& entry) const {
    Slot* slot = entry.slot;
    if (!unfilteredWallTrackingActive() || slot == nullptr ||
        slot->nativeTid() != entry.tid ||
        slot->lifecycleGeneration() != entry.lifecycle_generation) {
        return false;
    }

    // active_block_state publishes the rest of the block-run payload. Acquire
    // it before reading the context epoch, owner, or generation so those reads
    // observe the stores that preceded publishActiveBlockRun().
    OSThreadState state = slot->activeBlockState();
    bool suppressible_state = state == OSThreadState::SLEEPING ||
                              state == OSThreadState::CONDVAR_WAIT ||
                              state == OSThreadState::OBJECT_WAIT ||
                              state == OSThreadState::MONITOR_WAIT;
    if (!suppressible_state) return false;

    RecordingEpoch epoch = recordingEpoch();
    if (epoch == 0 || entry.recording_epoch != epoch ||
        slot->recordingEpoch() != epoch ||
        !slot->activeBlockRemainedOutsideContextWindow()) {
        return false;
    }

    u64 block_generation = slot->blockGeneration();
    BlockRunOwner owner = slot->activeBlockOwner();
    if (owner == BlockRunOwner::NONE) return false;

#ifdef UNIT_TEST
    if (_suppression_snapshot_hook != nullptr) {
        _suppression_snapshot_hook(_suppression_snapshot_hook_arg);
    }
#endif

    // The payload is spread across independent atomics. Accept it only if the
    // slot still represents the lifecycle and block run captured by the timer.
    if (slot->activeBlockOwner() != owner ||
        slot->blockGeneration() != block_generation ||
        slot->activeBlockState() != state || slot->nativeTid() != entry.tid ||
        slot->lifecycleGeneration() != entry.lifecycle_generation) {
        return false;
    }
    if (recordingEpoch() != epoch || slot->recordingEpoch() != epoch ||
        !slot->activeBlockRemainedOutsideContextWindow()) {
        return false;
    }
    return true;
}

void ThreadFilter::init(const char* filter, bool track_unfiltered_wall) {
    // Preserve the legacy filter contract: every non-empty value, including
    // "0", enables context filtering. Empty filter disables filtering; the
    // extra flag only retains metadata for unfiltered wall prechecks.
    bool context_filter = filter != nullptr && strlen(filter) > 0;
    bool unfiltered_tracking = track_unfiltered_wall && !context_filter;
    // Close registration before clearing identities from a previous unfiltered
    // recording. Other threads retain only stale slot IDs; activeSlotForId()
    // rejects them until their next context or owned-block hook registers lazily.
    _registry_active.store(false, std::memory_order_release);
    if (unfiltered_tracking) {
        std::lock_guard<std::mutex> lock(_registry_lock);
        resetRegistrationsLocked();
    }
    RecordingEpoch epoch = 0;
    if (unfiltered_tracking) {
        epoch = _next_recording_epoch.fetch_add(1, std::memory_order_acq_rel) + 1;
        if (epoch == 0) {
            // Zero is reserved for inactive state. This can occur only after
            // 2^64 recording starts; skip it rather than publishing ambiguity.
            epoch = _next_recording_epoch.fetch_add(1, std::memory_order_acq_rel) + 1;
        }
    }
    _recording_epoch.store(epoch, std::memory_order_release);
    _track_unfiltered_wall.store(unfiltered_tracking,
                                 std::memory_order_release);
    _registry_active.store(unfiltered_tracking || context_filter,
                           std::memory_order_release);
    _enabled.store(context_filter, std::memory_order_release);
}

bool ThreadFilter::enabled() const {
    return _enabled.load(std::memory_order_acquire);
}

bool ThreadFilter::registryActive() const {
    return _registry_active.load(std::memory_order_acquire);
}

bool ThreadFilter::unfilteredWallTrackingActive() const {
    return _track_unfiltered_wall.load(std::memory_order_acquire);
}

ThreadFilter::RecordingEpoch ThreadFilter::recordingEpoch() const {
    return _recording_epoch.load(std::memory_order_acquire);
}

void ThreadFilter::deactivateRecording() {
    // Close producer admission before invalidating the recording epoch.
    // Context-filtered recordings may retain slots; a new unfiltered recording
    // resets them before reopening admission.
    _registry_active.store(false, std::memory_order_release);
    _enabled.store(false, std::memory_order_release);
    _track_unfiltered_wall.store(false, std::memory_order_release);
    _recording_epoch.store(0, std::memory_order_release);
}
