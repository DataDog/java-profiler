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

    // One cache line per slot to avoid false sharing. Slot instances are freed
    // only by ~ThreadFilter, which requires quiescence (see the destructor), so a
    // captured Slot* stays dereferenceable while the filter is in use.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        // Packed as (epoch << 1) | in_context_window so a transition and its
        // epoch change are observed atomically by owned-block admission and by
        // the wall-clock suppression check.
        std::atomic<u64>           context_window_state{0};
        std::atomic<u64>           lifecycle_generation{0};
        // Per-recording publication flag. A retained TID mapping is eligible for
        // unfiltered suppression only when this value matches the registry's
        // active recording epoch. The slot's context-window state and its
        // WallClockBlockTracker::BlockState are reset before the epoch is
        // release-published.
        std::atomic<u64>           recording_epoch{0};
        // Native identity and context-window membership are independent so an
        // unfiltered wall recording can retain lifecycle metadata without
        // changing ordinary thread selection.
        std::atomic<int>           tid{-1};
        // Retirement bookkeeping (retireThreadByTid()/drainRetiredLocked()):
        // the tid a retired-pending slot was indexed under, and the intrusive
        // link of the per-instance retired stack. Both are -1 unless the slot
        // is retired-pending.
        std::atomic<int>           retiring_tid{-1};
        std::atomic<int>           retire_next{-1};
        char padding[DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<int>)
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
        // enterContextWindow()/exitContextWindow() are owner-only: add()/remove()
        // only ever call them on the calling thread's own slot, so the release
        // store is sufficient for concurrent readers using the acquire loads in
        // inContextWindow()/contextWindowEpoch(). Avoiding a CAS turns a locked
        // RMW into a plain store on every context-filtered enter/exit.
        //
        // Other writers of this field (R-A5):
        // - refreshSlotForRecording(), unregisterThreadLocked() and
        //   retireThreadByTid() reset it to 0 on the owner's own thread; the
        //   latter two only after winning the tid CAS, so the slot has no live
        //   owner afterwards.
        // - registerThread() zeroes it before an owner exists.
        // - clearActive() is the only cross-thread writer while the owner is
        //   live, and it uses exitContextWindowFromNonOwner() (a CAS).
        // Why this is safe: only the owner sets bit 0. After the owner loads
        // bit 0 clear, nobody else can change the word before its store. After
        // it loads bit 0 set, the only overlapping write is clearActive()'s
        // identical current+1. Neither the bit nor the epoch is lost or moved
        // backwards except by the deliberate resets to 0 above.
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
        // Cross-thread exit used by clearActive(): CAS so a racing owner
        // transition is never overwritten (R-A5). Returns whether this call
        // cleared bit 0.
        inline bool exitContextWindowFromNonOwner() {
            u64 current = context_window_state.load(std::memory_order_acquire);
            while ((current & 1) != 0) {
                if (context_window_state.compare_exchange_weak(
                        current, current + 1, std::memory_order_acq_rel,
                        std::memory_order_acquire)) {
                    return true;
                }
            }
            return false;
        }
        // Exposes the raw packed context-window state to WallClockBlockTracker,
        // which reads it (twice, around its owner CAS) to validate that an owned
        // block run did not span a context-window transition.
        inline u64 rawContextWindowState() const {
            return context_window_state.load(std::memory_order_acquire);
        }
    };
    static_assert(sizeof(Slot) == DEFAULT_CACHE_LINE_SIZE, "Slot must fit exactly one cache line");
    static_assert(std::atomic<u64>::is_always_lock_free,
                  "Slot::recording_epoch must be lock-free for signal-handler safety");

    ThreadFilter();
    // PRECONDITION: quiescence (no concurrent users); see threadFilter.cpp.
    ~ThreadFilter();

    // Retains native ownership across recordings. Unfiltered owners register on
    // their first context/block/park hook; live owners continue to consume capacity
    // until teardown. Their recording payload is refreshed lazily by its owner.
    void init(const char* filter, bool track_unfiltered_wall = false);
    void initFreeList();
    bool enabled() const;
    bool registryActive() const;
    bool unfilteredWallTrackingActive() const;
    RecordingEpoch recordingEpoch() const;
    // Hot path methods - slot_id MUST be from registerThread(), undefined behavior otherwise.
    // add() is lock-free. It returns false, without touching the slot, when the slot no
    // longer belongs to `tid` (the previous owner has exited). On failure, clear any
    // cached slot id so registerThread() re-derives it before assuming membership.
    bool accept(SlotID slot_id) const;
    bool add(int tid, SlotID slot_id);
    void remove(SlotID slot_id);
    void collect(std::vector<int>& tids) const;
    void collect(std::vector<ThreadEntry>& entries) const;
    // Clears per-recording membership and suppression state while keeping
    // native slot ownership intact. Threads must opt in again with add().
    void clearActive();
    // Forwards to WallClockBlockTracker::resetSlot(). Not called from
    // production code (registry-lifecycle paths call the tracker directly);
    // only park_state_ut uses it.
    void resetSlotRunState(SlotID slot_id);

    // Non-owning; wired up once by Profiler so ThreadFilter's own
    // registry-lifecycle resets (registerThread/unregisterThread/
    // refreshSlotForRecording/clearActive) also clear the tracker's
    // parallel per-slot state. See wallClockBlockTracker.h. Must be wired
    // before the first registerThread(); the tracker's storage is allocated
    // lazily by registerThread().
    void setBlockTracker(WallClockBlockTracker* tracker) { _block_tracker = tracker; }

#ifdef UNIT_TEST
    // Expose published bucket state for reclamation tests without timing assertions.
    int tidIndexEntryForTest(int bucket) const;
    static unsigned tidIndexBucketForTest(int tid) {
        return hashTid(tid) & kTidIndexMask;
    }

    // Invoked by registerThread() immediately before _registry_lock is
    // acquired, once the pre-lock _registry_active and capacity checks have
    // passed - lets tests inject a deactivation between the lock-free
    // _registry_active check and the in-lock recheck, and observe whether a
    // call reached the lock at all.
    using PostActiveCheckHook = void (*)(void*);
    void setPostActiveCheckHookForTest(PostActiveCheckHook hook, void* arg) {
        _post_active_check_hook = hook;
        _post_active_check_hook_arg = arg;
    }
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
    // Lock-free retirement for the pthread-key TLS destructor (never blocks).
    // Unknown/already-retired tid is a no-op. Locked bookkeeping is deferred to
    // the next _registry_lock holder (drainRetiredLocked()).
    void retireThreadByTid(int tid);
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

    struct TidIndex {
        std::array<std::atomic<int>, kTidIndexSize> entries;
        // Number of live entries whose home-to-destination probe path crosses
        // each bucket, excluding the destination itself. Writers alone access
        // these counts, under _registry_lock. A tombstone is needed exactly
        // while its count is nonzero; readers only inspect entries.
        std::array<uint16_t, kTidIndexSize> probe_through{};
    };
    static_assert(kMaxThreads <= UINT16_MAX, "TID probe counts must fit in uint16_t");

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
    // the lock; outside it may lag an in-flight push or lead an in-flight pop,
    // but never misses a completed push - see capacityExhausted(). Together
    // with _next_index and _retired_count it lets registerThread() reject
    // registrations against a full registry without taking _registry_lock.
    std::atomic<int> _free_count{0};
    // Per-instance intrusive Treiber stack of retired-pending slots linked via
    // Slot::retire_next (capacity == kMaxThreads, nothing can be dropped).
    // Pushed lock-free by retireThreadByTid(); consumed whole (exchange) by
    // drainRetiredLocked() under _registry_lock, so there is no ABA.
    std::atomic<SlotID> _retired_head{-1};
    // Retired-but-undrained slots; incremented BEFORE the push, decremented
    // AFTER pushToFreeList(), so a completed retirement is always counted in
    // _retired_count or _free_count (see capacityExhausted()).
    std::atomic<int> _retired_count{0};
    // Entries contain slot_id + 1. Zero terminates a lookup probe; -1 is a
    // tombstone left by unregister. The slot's published TID is the key.
    // Entries and probe counts share one allocation made by the first init()
    // that activates the registry and kept until destruction (requires
    // quiescence; no grace period for lock-free readers), so processes that never use a
    // context filter or unfiltered precheck don't pay for it. Null until then:
    // lookups find nothing, and nothing can be indexed while it is null because
    // registration requires an active registry.
    // Retired-but-undrained entries stay occupied; readers and indexSlot skip
    // them because slot->tid is -1; unindexSlot later matches on
    // value == slot_id+1.
    std::atomic<TidIndex*> _tid_index{nullptr};
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
    // Lock-free admission gate: true when every slot index has been handed
    // out, no retirement is pending and no slot is waiting in the free list,
    // i.e. a new registration cannot succeed.
    // 1. _next_index only changes under _registry_lock and never drops below
    //    kMaxThreads once reached (an overshoot is reverted, never reset).
    // 2. Load order matters: _retired_count before _free_count. Drain removes
    //    a slot from _retired_count only after pushToFreeList() has counted it
    //    in _free_count, so every completed retirement is visible in at least
    //    one of the two reads.
    // 3. A free whose pushToFreeList() has not yet incremented _free_count is
    //    an in-progress operation ordered after this rejection - the same
    //    outcome as the locked path.
    // 4. Consequently THREAD_REGISTRY_CAPACITY_EXHAUSTED counts genuine
    //    full-registry rejections; the caller retries on its next hook
    //    (ensureCurrentThreadFilterSlot()).
    // 5. Pending retirements count as capacity, so a registry full of retired
    //    slots reaches the lock and drains them (starvation guard).
    // 6. Do not reorder the loads and do not take the lock here
    //    (FullRegistryRejectsUnknownTidWithoutLocking).
    // 7. retireThreadByTid() increments _retired_count before its Treiber push,
    //    so if the exiting thread is descheduled between the two, drains briefly
    //    find an empty list while this gate returns false and over-capacity
    //    registrations take _registry_lock. That is intentional (over-report is
    //    the safe direction); do not "fix" the order.
    inline bool capacityExhausted() const {
        return _next_index.load(std::memory_order_acquire) >= kMaxThreads &&
               _retired_count.load(std::memory_order_acquire) == 0 &&
               _free_count.load(std::memory_order_acquire) == 0;
    }
    // Caller holds _registry_lock. Moves every retired-pending slot to the
    // free list (unindex, reset, push).
    void drainRetiredLocked();
    bool indexSlot(SlotID slot_id, int tid);
    void unindexSlot(SlotID slot_id, int tid);
    void rollbackFailedIndex(Slot& slot);
    bool indexOrRollback(Slot& slot, SlotID slot_id, int tid);
    void refreshSlotForRecording(SlotID slot_id, Slot* slot, RecordingEpoch epoch);
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
