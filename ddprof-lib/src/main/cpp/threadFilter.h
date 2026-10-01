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
#ifndef _THREADFILTER_H
#define _THREADFILTER_H

#include <atomic>
#include <array>
#include <vector>
#include <cstdint>
#include <memory>
#include <mutex>

#include "arch.h"
#include "threadState.h"

struct ThreadEntry;  // defined after ThreadFilter; carries a pointer to a ThreadFilter::Slot
class WallClockBlockTracker;  // wall-clock owned/unowned block-run suppression state, see wallClockBlockTracker.h

class ThreadFilter {
public:
    using SlotID = int;
    using RecordingEpoch = u64;

    // Optimized limits for reasonable memory usage
    static constexpr int kChunkSize = 256;
    static constexpr int kChunkShift = 8;   // log2(256)
    static constexpr int kChunkMask = kChunkSize - 1;
    static constexpr int kMaxThreads = 2048;
    static constexpr int kMaxChunks = (kMaxThreads + kChunkSize - 1) / kChunkSize;  // = 8 chunks
    // High-performance free list using Treiber stack, 64 shards
    static constexpr int kFreeListSize  = kMaxThreads;
    static constexpr int kShardCount    = 64;          // power-of-two for fast modulo
    static constexpr int kTidIndexSize  = 8192;        // 4x maximum live slots
    static constexpr int kTidIndexMask  = kTidIndexSize - 1;

    // One cache line per slot to avoid false sharing. Slot instances are never freed
    // (ChunkStorage is process-lifetime), so a captured Slot* is always dereferenceable.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        // Packed as (epoch << 1) | in_context_window so a transition and its
        // epoch change are observed atomically by block admission and exit.
        std::atomic<u64>           context_window_state{0};
        std::atomic<u64>           lifecycle_generation{0};
        // Per-recording publication flag. A retained TID mapping is eligible for
        // unfiltered suppression only when this value matches the registry's
        // active recording epoch. The payload is reset before the epoch is
        // release-published.
        std::atomic<u64>           recording_epoch{0};
        // Native identity and context-window membership are independent so an
        // unfiltered wall recording can retain lifecycle metadata without
        // changing ordinary thread selection.
        std::atomic<int>           tid{-1};
        char padding[DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<int>)];

        inline int nativeTid() const {
            return tid.load(std::memory_order_acquire);
        }
        inline u64 lifecycleGeneration() const {
            return lifecycle_generation.load(std::memory_order_acquire);
        }
        inline RecordingEpoch recordingEpoch() const {
            return recording_epoch.load(std::memory_order_acquire);
        }
        inline bool inContextWindow() const {
            return (context_window_state.load(std::memory_order_acquire) & 1) != 0;
        }
        inline u64 contextWindowEpoch() const {
            return context_window_state.load(std::memory_order_acquire) >> 1;
        }
        // add()/remove() (and therefore these) are only ever called by the slot's
        // own owning thread transitioning its own context window, so there is no
        // writer-writer race to protect against here. A CAS is unnecessary: the
        // load and store below are never interleaved with another writer's RMW,
        // only observed by concurrent readers via the acquire load in
        // inContextWindow()/contextWindowEpoch(), for which the release store is
        // sufficient. (unregisterThreadLocked()/resetRegistrationsLocked() can
        // also zero this field from another thread, but only as part of tearing
        // down or resetting the slot entirely, a case where clobbering an
        // in-flight transition from the exiting/reset thread is already
        // tolerated.) Avoiding the CAS turns a locked RMW into a plain store on
        // every context-filtered enter/exit.
        inline bool enterContextWindow() {
            u64 current = context_window_state.load(std::memory_order_relaxed);
            if ((current & 1) != 0) return false;
            context_window_state.store(current + 3, std::memory_order_release);
            return true;
        }
        inline bool exitContextWindow() {
            u64 current = context_window_state.load(std::memory_order_relaxed);
            if ((current & 1) == 0) return false;
            context_window_state.store(current + 1, std::memory_order_release);
            return true;
        }
        // Exposes the raw packed context-window state to WallClockBlockTracker,
        // which needs it (twice, around a CAS) to validate that an owned block
        // run did not span a context-window transition, but no longer stores
        // context-window state itself. See wallClockBlockTracker.h.
        inline u64 rawContextWindowState() const {
            return context_window_state.load(std::memory_order_acquire);
        }
    };
    static_assert(sizeof(Slot) == DEFAULT_CACHE_LINE_SIZE, "Slot must fit exactly one cache line");
    static_assert(std::atomic<u64>::is_always_lock_free,
                  "Slot::recording_epoch must be lock-free for signal-handler safety");

    ThreadFilter();
    ~ThreadFilter();

    void init(const char* filter, bool track_unfiltered_wall = false);
    void initFreeList();
    bool enabled() const;
    bool registryActive() const;
    bool unfilteredWallTrackingActive() const;
    RecordingEpoch recordingEpoch() const;
    // Hot path methods - slot_id MUST be from registerThread(), undefined behavior otherwise.
    // add() is lock-free. It returns false, without touching the slot, when the slot no
    // longer belongs to `tid` (its cached slot id went stale, e.g. an unfiltered
    // recording restart reset the registry); callers must not assume membership on
    // failure and should clear any cached slot id so registerThread() re-derives it.
    bool accept(SlotID slot_id) const;
    bool add(int tid, SlotID slot_id);
    void remove(SlotID slot_id);
    void collect(std::vector<int>& tids) const;
    void collect(std::vector<ThreadEntry>& entries) const;
    // Clears per-recording membership and suppression state while keeping
    // process-lifetime slot ownership intact. Threads must opt in again with add().
    void clearActive();
    // Forwards to WallClockBlockTracker::resetSlot(); kept on ThreadFilter
    // since it addresses a slot by SlotID, a ThreadFilter concept.
    void resetSlotRunState(SlotID slot_id);

    // Non-owning; wired up once by Profiler so ThreadFilter's own
    // registry-lifecycle resets (registerThread/unregisterThread/
    // resetRegistrationsLocked/clearActive) can clear the tracker's
    // parallel per-slot state at the same points that used to call
    // Slot::clearActiveBlockRun() directly. See wallClockBlockTracker.h.
    void setBlockTracker(WallClockBlockTracker* tracker) { _block_tracker = tracker; }

#ifdef UNIT_TEST
    // Invoked by registerThread() immediately before _registry_lock is
    // acquired, once the pre-lock _registry_active and capacity checks have
    // passed - lets tests inject a deactivation into the exact TOCTOU window
    // being fixed, and observe whether a call reached the lock at all.
    using PostActiveCheckHook = void (*)(void*);
    void setPostActiveCheckHookForTest(PostActiveCheckHook hook, void* arg) {
        _post_active_check_hook = hook;
        _post_active_check_hook_arg = arg;
    }
    // Forwards to WallClockBlockTracker::setSuppressionSnapshotHookForTest()
    // so existing test call sites don't need to change now that
    // shouldSuppressOwnedBlock() lives on WallClockBlockTracker. Defined in
    // threadFilter.cpp (not inline here) since WallClockBlockTracker's full
    // definition isn't visible in this header - it includes threadFilter.h.
    void setSuppressionSnapshotHookForTest(void (*hook)(void*), void* arg);
#endif

    // Returns nullptr if slot_id is invalid or its chunk has not been allocated.
    inline Slot* slotForId(SlotID slot_id) const {
        if (slot_id < 0) return nullptr;
        int chunk_idx = slot_id >> kChunkShift;
        int slot_idx  = slot_id & kChunkMask;
        if (chunk_idx >= kMaxChunks) return nullptr;
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        return chunk != nullptr ? &chunk->slots[slot_idx] : nullptr;
    }

    // Returns the slot owned by native thread `tid` (allocating one if needed),
    // or -1 if tid < 0, the registry is inactive, or it is full.
    SlotID registerThread(int tid);
    void unregisterThread(SlotID slot_id, int expected_tid = -1);
    void unregisterThreadByTid(int tid);
    Slot* lookupByTid(int tid, SlotID* out_slot_id = nullptr) const;
    Slot* lookupByTid(int tid, RecordingEpoch epoch, SlotID* out_slot_id = nullptr) const;
    Slot* activeSlotForId(SlotID slot_id, int tid) const;
    void deactivateRecording();

private:

    // Lock-free free list using a stack-like structure
    struct FreeListNode {
        std::atomic<int> value{-1};
        std::atomic<int> next{-1};
    };

    // Pre-allocated chunk storage to eliminate mutex contention
    struct ChunkStorage {
        std::array<Slot, kChunkSize> slots;
    };

    std::atomic<bool> _enabled{false};
    std::atomic<bool> _registry_active{false};
    std::atomic<bool> _track_unfiltered_wall{false};
    std::atomic<RecordingEpoch> _recording_epoch{0};
    std::atomic<RecordingEpoch> _next_recording_epoch{0};

    // Lazily allocated storage for chunks
    std::atomic<ChunkStorage*> _chunks[kMaxChunks];
    std::atomic<int> _num_chunks{1};

    // Lock-free slot allocation
    std::atomic<SlotID> _next_index{0};
    std::unique_ptr<FreeListNode[]> _free_list;
    // Number of slots currently linked into the free list. Maintained only by
    // pushToFreeList()/popFromFreeList()/initFreeList(), all of which run under
    // _registry_lock (or single-threaded construction), so it is exact under
    // the lock and a hint outside it. Together with _next_index it lets
    // registerThread() reject registrations against a full registry without
    // taking _registry_lock (see capacityExhausted()).
    std::atomic<int> _free_count{0};
    // Entries contain slot_id + 1. Zero terminates a lookup probe; -1 is a
    // tombstone left by unregister. The slot's published TID is the key.
    // Allocated (kTidIndexSize entries) by the first init() that activates the
    // registry and kept until destruction, so processes that never use a
    // context filter or unfiltered precheck don't pay for it. Null until then:
    // lookups find nothing, and nothing can be indexed while it is null because
    // registration requires an active registry.
    std::atomic<std::atomic<int>*> _tid_index{nullptr};
    // Registration and teardown never run in a signal handler. Serializing
    // writers prevents duplicate TID mappings while lookups remain lock-free.
    std::mutex _registry_lock;

    WallClockBlockTracker* _block_tracker = nullptr;

#ifdef UNIT_TEST
    PostActiveCheckHook _post_active_check_hook = nullptr;
    void* _post_active_check_hook_arg = nullptr;
#endif

    // Cache line aligned to prevent false sharing between shards
    struct alignas(DEFAULT_CACHE_LINE_SIZE) ShardHead { std::atomic<int> head{-1}; };
    static ShardHead _free_heads[kShardCount];         // one cache-line each

    static inline int shardOf(int tid)  { return tid & (kShardCount - 1); }
    static inline int shardOfSlot(int s){ return s  & (kShardCount - 1); }
    // Helper methods for lock-free operations
    void initializeChunk(int chunk_idx);
    bool pushToFreeList(SlotID slot_id);
    SlotID popFromFreeList();
    // Lock-free hint: true when every slot index has been handed out and none
    // is waiting in the free list, i.e. a new registration cannot succeed.
    inline bool capacityExhausted() const {
        return _next_index.load(std::memory_order_acquire) >= kMaxThreads &&
               _free_count.load(std::memory_order_acquire) == 0;
    }
    bool indexSlot(SlotID slot_id, int tid);
    void unindexSlot(SlotID slot_id, int tid);
    void rollbackFailedIndex(Slot& slot);
    bool indexOrRollback(Slot& slot, SlotID slot_id, int tid);
    void refreshSlotForRecording(SlotID slot_id, Slot* slot, RecordingEpoch epoch);
    void resetRegistrationsLocked();
    void ensureTidIndexLocked();
    void unregisterThreadLocked(SlotID slot_id, int expected_tid = -1);
    SlotID lookupSlotIdByTid(int tid) const;
    static inline unsigned hashTid(int tid) {
        return static_cast<unsigned>(tid) * 2654435761u;
    }
};

// Snapshot entry produced by ThreadFilter::collect for the wall-clock timer.
struct ThreadEntry {
    int tid;
    ThreadFilter::Slot* slot;
    ThreadFilter::SlotID slot_id;
    u64 lifecycle_generation;
    ThreadFilter::RecordingEpoch recording_epoch;
};

#endif // _THREADFILTER_H
