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

enum class BlockRunOwner : int {
    NONE = 0,
    JAVA = 1,
    JVMTI = 2,
    NATIVE = 3,
};

struct BlockRunSnapshot {
    OSThreadState active_state{OSThreadState::UNKNOWN};
    BlockRunOwner owner{BlockRunOwner::NONE};
    u64 generation{0};
    bool active{false};
    bool context_eligible{false};
};

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
    static constexpr int kBlockRunSlotBits = 11;
    static constexpr u64 kBlockRunSlotMask = (1ULL << kBlockRunSlotBits) - 1;
    static constexpr u64 kMaxBlockRunGeneration = UINT64_MAX >> kBlockRunSlotBits;
    static_assert(kMaxThreads == (1 << kBlockRunSlotBits),
                  "block-run token slot bits must cover every ThreadFilter slot");
    // High-performance free list using Treiber stack, 64 shards
    static constexpr int kFreeListSize  = kMaxThreads;
    static constexpr int kShardCount    = 64;          // power-of-two for fast modulo
    static constexpr int kTidIndexSize  = 8192;        // 4x maximum live slots
    static constexpr int kTidIndexMask  = kTidIndexSize - 1;

    // One cache line per slot to avoid false sharing. Slot instances are never freed
    // (ChunkStorage is process-lifetime), so a captured Slot* is always dereferenceable.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        static constexpr u64 kUnownedBlockedFallbackRatio = 10;

        std::atomic<u64>           unowned_blocked_pending_weight{0};
        std::atomic<u64>           unowned_blocked_decision_count{0};
        std::atomic<u64>           unowned_blocked_call_trace_id{0};
        // Packed as (epoch << 1) | in_context_window so a transition and its
        // epoch change are observed atomically by block admission and exit.
        std::atomic<u64>           context_window_state{0};
        std::atomic<u64>           lifecycle_generation{0};
        // Per-recording publication flag. A retained TID mapping is eligible for
        // unfiltered suppression only when this value matches the registry's
        // active recording epoch. The payload is reset before the epoch is
        // release-published.
        std::atomic<u64>           recording_epoch{0};
        std::atomic<u64>           active_block_context_epoch{0};
        std::atomic<u64>           block_generation{0};
        std::atomic<OSThreadState> unowned_blocked_state{OSThreadState::UNKNOWN};
        // Native identity and context-window membership are independent so an
        // unfiltered wall recording can retain lifecycle metadata without
        // changing ordinary thread selection.
        std::atomic<int>           tid{-1};
        std::atomic<int>           active_block_owner{static_cast<int>(BlockRunOwner::NONE)};
        // Set by explicit block enter/exit hooks. It lets the timer skip sending a signal
        // only while instrumentation still owns a suppressible blocking interval.
        std::atomic<OSThreadState> active_block_state{OSThreadState::UNKNOWN};
        char padding[2 * DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<OSThreadState>)];

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
        inline bool enterContextWindow() {
            u64 current = context_window_state.load(std::memory_order_acquire);
            while ((current & 1) == 0) {
                if (context_window_state.compare_exchange_weak(
                        current, current + 3, std::memory_order_acq_rel,
                        std::memory_order_acquire)) {
                    return true;
                }
            }
            return false;
        }
        inline bool exitContextWindow() {
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

        inline OSThreadState activeBlockState() const {
            return active_block_state.load(std::memory_order_acquire);
        }
        inline void setActiveBlockState(OSThreadState state) {
            active_block_state.store(state, std::memory_order_release);
        }
        inline BlockRunOwner activeBlockOwner() const {
            return static_cast<BlockRunOwner>(active_block_owner.load(std::memory_order_acquire));
        }
        inline u64 blockGeneration() const {
            return block_generation.load(std::memory_order_acquire);
        }
        inline void resetUnownedBlockedSampling() {
            unowned_blocked_pending_weight.store(0, std::memory_order_relaxed);
            unowned_blocked_decision_count.store(0, std::memory_order_relaxed);
            unowned_blocked_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);
            unowned_blocked_call_trace_id.store(0, std::memory_order_release);
        }
        inline bool shouldRecordUnownedBlockedSample() {
            u64 decision = unowned_blocked_decision_count.fetch_add(1, std::memory_order_relaxed) + 1;
            if ((decision % kUnownedBlockedFallbackRatio) == 1) {
                return true;
            }
            unowned_blocked_pending_weight.fetch_add(1, std::memory_order_relaxed);
            return false;
        }
        inline u64 consumeUnownedBlockedWeight() {
            return unowned_blocked_pending_weight.exchange(0, std::memory_order_relaxed) + 1;
        }
        inline void restoreUnownedBlockedWeight(u64 weight) {
            if (weight > 1) {
                unowned_blocked_pending_weight.fetch_add(weight - 1, std::memory_order_relaxed);
            }
        }
        inline void recordUnownedBlockedSample(u64 call_trace_id, OSThreadState state) {
            unowned_blocked_state.store(state, std::memory_order_relaxed);
            unowned_blocked_call_trace_id.store(call_trace_id, std::memory_order_release);
        }
        inline bool flushUnownedBlockedTail(u64& call_trace_id, u64& weight,
                                            OSThreadState& state) {
            call_trace_id = unowned_blocked_call_trace_id.exchange(0, std::memory_order_acq_rel);
            weight = unowned_blocked_pending_weight.exchange(0, std::memory_order_relaxed);
            state = unowned_blocked_state.exchange(OSThreadState::UNKNOWN, std::memory_order_relaxed);
            unowned_blocked_decision_count.store(0, std::memory_order_relaxed);
            if (call_trace_id == 0 || weight == 0 || state == OSThreadState::UNKNOWN) {
                return false;
            }
            return true;
        }
        inline bool tryPrepareActiveBlockRun(BlockRunOwner owner,
                                             u64* generation_out,
                                             bool outside_context_required) {
            u64 context_state = context_window_state.load(std::memory_order_acquire);
            if (outside_context_required && (context_state & 1) != 0) {
                return false;
            }
            int expected_owner = static_cast<int>(BlockRunOwner::NONE);
            if (!active_block_owner.compare_exchange_strong(
                    expected_owner, static_cast<int>(owner), std::memory_order_acq_rel,
                    std::memory_order_acquire)) {
                return false;
            }
            if (outside_context_required &&
                context_window_state.load(std::memory_order_acquire) != context_state) {
                active_block_owner.store(static_cast<int>(BlockRunOwner::NONE),
                                         std::memory_order_release);
                return false;
            }
            u64 generation = block_generation.load(std::memory_order_relaxed);
            if (generation == kMaxBlockRunGeneration) {
                active_block_owner.store(static_cast<int>(BlockRunOwner::NONE),
                                         std::memory_order_release);
                return false;
            }
            generation++;
            block_generation.store(generation, std::memory_order_relaxed);
            active_block_context_epoch.store(context_state >> 1, std::memory_order_relaxed);
            resetUnownedBlockedSampling();
            *generation_out = generation;
            return true;
        }
        inline void publishActiveBlockRun(OSThreadState state) {
            active_block_state.store(state, std::memory_order_release);
        }
        inline void clearActiveBlockRun(OSThreadState) {
            active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            resetUnownedBlockedSampling();
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
        }
        inline bool activeBlockRemainedOutsideContextWindow() const {
            u64 context_state = context_window_state.load(std::memory_order_acquire);
            return (context_state & 1) == 0 &&
                   active_block_context_epoch.load(std::memory_order_acquire) ==
                       (context_state >> 1);
        }
        inline BlockRunSnapshot snapshotBlockRun() const {
            BlockRunSnapshot snapshot;
            snapshot.active_state = activeBlockState();
            snapshot.owner = activeBlockOwner();
            snapshot.generation = blockGeneration();
            snapshot.active = snapshot.owner != BlockRunOwner::NONE &&
                snapshot.active_state != OSThreadState::UNKNOWN;
            snapshot.context_eligible = activeBlockRemainedOutsideContextWindow();
            return snapshot;
        }
    };
    static_assert(sizeof(Slot) == 2 * DEFAULT_CACHE_LINE_SIZE, "Slot must be exactly two cache lines");
    static_assert(std::atomic<OSThreadState>::is_always_lock_free,
                  "Slot OSThreadState fields must be lock-free for signal-handler safety");
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
    // Hot path methods - slot_id MUST be from registerThread(), undefined behavior otherwise
    bool accept(SlotID slot_id) const;
    void add(int tid, SlotID slot_id);
    void remove(SlotID slot_id);
    void collect(std::vector<int>& tids) const;
    void collect(std::vector<ThreadEntry>& entries) const;
    // Clears per-recording membership and suppression state while keeping
    // process-lifetime slot ownership intact. Threads must opt in again with add().
    void clearActive();
    void resetSlotRunState(SlotID slot_id);
    u64 enterBlockedRun(SlotID slot_id, OSThreadState state,
                        BlockRunOwner owner = BlockRunOwner::JAVA);
    // Unconditional cleanup for reset/unregister paths only. Normal block
    // lifecycles must use the generation-checked overload so they cannot clear
    // another owner.
    void exitBlockedRun(SlotID slot_id);
    bool exitBlockedRun(SlotID slot_id, u64 generation);
    bool snapshotAndExitBlockedRun(SlotID slot_id, u64 generation,
                                   BlockRunSnapshot* snapshot);
    bool isOwnedBlockSuppressionCandidate(const ThreadEntry& entry) const;

#ifdef UNIT_TEST
    using SuppressionSnapshotHook = void (*)(void*);
    void setSuppressionSnapshotHookForTest(SuppressionSnapshotHook hook,
                                           void* arg) {
        _suppression_snapshot_hook = hook;
        _suppression_snapshot_hook_arg = arg;
    }
#endif

    static inline u64 encodeBlockRunToken(SlotID slot_id, u64 generation) {
        return (generation << kBlockRunSlotBits) | static_cast<u64>(slot_id);
    }
    static inline SlotID tokenSlotId(u64 token) {
        return static_cast<SlotID>(token & kBlockRunSlotMask);
    }
    static inline u64 tokenGeneration(u64 token) {
        return token >> kBlockRunSlotBits;
    }
    static inline bool decodeBlockRunToken(u64 token, SlotID& slot_id,
                                           u64& generation) {
        if (token == 0) return false;
        slot_id = tokenSlotId(token);
        generation = tokenGeneration(token);
        return generation != 0;
    }

#ifdef UNIT_TEST
    using BlockRunPublishObserver = void (*)(ThreadFilter*, SlotID);
    static void setBlockRunPublishObserverForTest(BlockRunPublishObserver observer);
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

    SlotID registerThread(int tid = -1);
    void unregisterThread(SlotID slot_id, int expected_tid = -1);
    void unregisterThreadByTid(int tid);
    Slot* lookupByTid(int tid) const;
    Slot* lookupByTid(int tid, RecordingEpoch epoch) const;
    Slot* activeSlotForId(SlotID slot_id, int tid) const;
    void deactivateRecording();
    SlotID slotIdByTid(int tid) const { return lookupSlotIdByTid(tid); }

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
    // Entries contain slot_id + 1. Zero terminates a lookup probe; -1 is a
    // tombstone left by unregister. The slot's published TID is the key.
    std::array<std::atomic<int>, kTidIndexSize> _tid_index;
    // Registration and teardown never run in a signal handler. Serializing
    // writers prevents duplicate TID mappings while lookups remain lock-free.
    std::mutex _registry_lock;

#ifdef UNIT_TEST
    static std::atomic<BlockRunPublishObserver> _block_run_publish_observer;
    SuppressionSnapshotHook _suppression_snapshot_hook = nullptr;
    void* _suppression_snapshot_hook_arg = nullptr;
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
    bool indexSlot(SlotID slot_id, int tid);
    void unindexSlot(SlotID slot_id, int tid);
    void refreshSlotForRecording(Slot* slot, RecordingEpoch epoch);
    void resetRegistrationsLocked();
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
    u64 lifecycle_generation;
    ThreadFilter::RecordingEpoch recording_epoch;
};

#endif // _THREADFILTER_H
