/*
 * Copyright 2026, Datadog, Inc
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
#ifndef _WALLCLOCKBLOCKTRACKER_H
#define _WALLCLOCKBLOCKTRACKER_H

#include <atomic>
#include <array>
#include <cassert>
#include <cstdint>

#include "arch.h"
#include "callTraceHashTable.h"
#include "context.h"
#include "threadFilter.h"
#include "threadState.h"

enum class BlockRunOwner : int {
    NONE = 0,
    JAVA = 1,
    JVMTI = 2,
    NATIVE = 3,
};

// Wall-clock owned/unowned block-run suppression state, addressed in parallel
// to ThreadFilter's own slots by ThreadFilter::SlotID. Kept separate from
// ThreadFilter::Slot because this is wall-clock-engine policy (has this
// blocked interval already produced a sample?), not thread identity - see
// threadFilter.h for the registry itself. Methods that need registry facts
// (context-window state, unfiltered-tracking mode) take a ThreadFilter
// pointer/Slot pointer as an explicit parameter rather than storing one, so
// tests can pair a tracker with any ThreadFilter instance.
class WallClockBlockTracker {
public:
    WallClockBlockTracker() = default;
    ~WallClockBlockTracker();

    // Published backing survives registry resets and recording restarts, so
    // captured pointers remain valid until destruction.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) BlockState {
        static constexpr u64 kUnownedBlockedFallbackRatio = 10;

        std::atomic<u64>           unowned_blocked_pending_weight{0};
        std::atomic<u64>           unowned_blocked_decision_count{0};
        std::atomic<u64>           unowned_blocked_call_trace_id{0};
        std::atomic<u64>           active_block_context_epoch{0};
        std::atomic<OSThreadState> unowned_blocked_state{OSThreadState::UNKNOWN};
        std::atomic<int>           active_block_owner{static_cast<int>(BlockRunOwner::NONE)};
        std::atomic<u32>           block_generation{0};
        // Wall-clock once-per-run suppression state. The signal handler records the
        // last sampled blocked state; the signal handler and timer thread read it to
        // suppress duplicate samples, while lifecycle/block-exit paths reset it.
        // Release/acquire on sampled_this_run pairs with relaxed last_sampled_state,
        // following the standard flag+payload pattern.
        std::atomic<OSThreadState> last_sampled_state{OSThreadState::UNKNOWN};
        // Set by explicit block enter/exit hooks. It lets the timer skip sending a signal
        // only while instrumentation still owns a suppressible blocking interval.
        std::atomic<OSThreadState> active_block_state{OSThreadState::UNKNOWN};
        std::atomic<bool>          sampled_this_run{false};
        char padding[DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<u64>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<u32>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<bool>)];

        inline bool sampledThisRun() const {
            return sampled_this_run.load(std::memory_order_acquire);
        }
        inline OSThreadState lastSampledState() const {
            return last_sampled_state.load(std::memory_order_relaxed);
        }
        inline void markSampledThisRun(OSThreadState state) {
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(true, std::memory_order_release);
        }
        inline void resetSampledRun(OSThreadState state) {
            resetUnownedBlockedSampling();
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(false, std::memory_order_release);
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
        inline u32 blockGeneration() const {
            return block_generation.load(std::memory_order_acquire);
        }
        inline void resetUnownedBlockedSampling() {
            unowned_blocked_pending_weight.store(0, std::memory_order_relaxed);
            unowned_blocked_decision_count.store(0, std::memory_order_relaxed);
            unowned_blocked_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);
            unowned_blocked_call_trace_id.store(0, std::memory_order_release);
        }
        inline bool shouldRecordUnownedBlockedSample(bool force_record = false, bool retain_weight = true) {
            u64 decision = unowned_blocked_decision_count.fetch_add(1, std::memory_order_relaxed) + 1;
            if (force_record || (decision % kUnownedBlockedFallbackRatio) == 1) {
                return true;
            }
            if (retain_weight) unowned_blocked_pending_weight.fetch_add(1, std::memory_order_relaxed);
            return false;
        }
        inline void clearUnownedBlockedTailKeepingCadence() {
            unowned_blocked_pending_weight.store(0, std::memory_order_release);
            unowned_blocked_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            unowned_blocked_call_trace_id.store(0, std::memory_order_release);
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
        // Unowned-blocked bookkeeping (pending weight, call_trace_id, state,
        // decision_count) is cleared ONLY by (R-B1):
        //  (a) a successful flushUnownedBlockedTail();
        //  (b) consumeUnownedBlockedWeight() at a recorded sample (weight only);
        //  (c) registry-lifecycle resetSlot()/resetAll() (registerThread,
        //      refreshSlotForRecording, unregisterThreadLocked,
        //      retireThreadByTid, drainRetiredLocked, clearActive).
        // The thread's own events - a failed flush, owned-run entry or
        // generation-checked exit, context-window entry - must not clear it.
        // Validate, then consume: an incomplete tail reports what was read
        // through the out-params and consumes nothing. Accepted residual: the
        // sampling cadence now carries across runs, so up to kRatio-1 units may
        // be attributed to an earlier run's stack/state.
        inline bool peekUnownedBlockedTail(u64& call_trace_id, u64& weight,
                                           OSThreadState& state) const {
            call_trace_id = unowned_blocked_call_trace_id.load(std::memory_order_acquire);
            weight = unowned_blocked_pending_weight.load(std::memory_order_relaxed);
            state = unowned_blocked_state.load(std::memory_order_relaxed);
            return call_trace_id != 0 && weight != 0 && state != OSThreadState::UNKNOWN;
        }
        inline bool flushUnownedBlockedTail(u64& call_trace_id, u64& weight,
                                            OSThreadState& state) {
            // Acquire pairs with the release store in recordUnownedBlockedSample().
            call_trace_id = unowned_blocked_call_trace_id.load(std::memory_order_acquire);
            weight = unowned_blocked_pending_weight.load(std::memory_order_relaxed);
            state = unowned_blocked_state.load(std::memory_order_relaxed);
            if (call_trace_id == 0 || weight == 0 || state == OSThreadState::UNKNOWN) {
                return false;
            }
            call_trace_id = unowned_blocked_call_trace_id.exchange(0, std::memory_order_acq_rel);
            weight = unowned_blocked_pending_weight.exchange(0, std::memory_order_relaxed);
            state = unowned_blocked_state.exchange(OSThreadState::UNKNOWN, std::memory_order_relaxed);
            unowned_blocked_decision_count.store(0, std::memory_order_relaxed);
            // A concurrent lifecycle reset may have intervened between the
            // loads and the exchanges.
            return call_trace_id != 0 && weight != 0 && state != OSThreadState::UNKNOWN;
        }
        // identity_slot supplies the context-window state, which lives on
        // ThreadFilter::Slot. See ThreadFilter::Slot::rawContextWindowState().
        inline bool trySetActiveBlockRun(ThreadFilter::Slot* identity_slot, OSThreadState state,
                                         BlockRunOwner owner, u32* generation_out,
                                         bool outside_context_required) {
            u64 context_state = identity_slot->rawContextWindowState();
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
                identity_slot->rawContextWindowState() != context_state) {
                active_block_owner.store(static_cast<int>(BlockRunOwner::NONE),
                                         std::memory_order_release);
                return false;
            }
            u32 generation = block_generation.fetch_add(1, std::memory_order_acq_rel) + 1;
            // Relaxed is enough: this payload is published by the trailing
            // active_block_state release store, and only the owner writes it.
            // shouldSuppressOwnedBlock() and prepareWallPrecheck() acquire
            // activeBlockState() before activeBlockRemainedOutsideContextWindow().
            // An older state is UNKNOWN, because resetSlot() and
            // clearActiveBlockRun() store state UNKNOWN before owner NONE. A
            // racing context transition leaves a stale epoch that can only fail
            // the equality check: a missed suppression, never a wrongful one.
            active_block_context_epoch.store(context_state >> 1, std::memory_order_relaxed);
            // The unowned-blocked tail is deliberately preserved (R-B1). Owned
            // runs in a precheck-suppression state never read or write the
            // unowned fields, because prepareWallPrecheck() takes the owned
            // path; an owned run in a non-suppression state falls through to
            // the unowned path, which is the same thread's weight.
            last_sampled_state.store(OSThreadState::UNKNOWN, std::memory_order_relaxed);
            sampled_this_run.store(false, std::memory_order_relaxed);
            active_block_state.store(state, std::memory_order_release);
            *generation_out = generation;
            return true;
        }
        inline void resetSlot(OSThreadState state) {
            active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            resetSampledRun(state);
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
        }
        bool needsActiveBlockRunClear(OSThreadState state) const {
            // Retained unowned context and epoch segments are not owned-run payload.
            return activeBlockOwner() != BlockRunOwner::NONE ||
                   activeBlockState() != OSThreadState::UNKNOWN || sampledThisRun() ||
                   last_sampled_state.load(std::memory_order_acquire) != state;
        }
#ifdef UNIT_TEST
        // Observation only; this counter publishes no payload or layout changes.
        inline static std::atomic<u64> clear_count_for_test{0};
#endif
        // End owned suppression without discarding an unowned origin's retained
        // context, trace or weight. Publish UNKNOWN before releasing ownership.
        inline void clearActiveBlockRun(OSThreadState state) {
#ifdef UNIT_TEST
            clear_count_for_test.fetch_add(1, std::memory_order_relaxed);
#endif
            active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(false, std::memory_order_release);
        }
        // identity_slot supplies the context-window state, which lives on
        // ThreadFilter::Slot. See ThreadFilter::Slot::rawContextWindowState().
        inline bool activeBlockRemainedOutsideContextWindow(ThreadFilter::Slot* identity_slot) const {
            u64 context_state = identity_slot->rawContextWindowState();
            return (context_state & 1) == 0 &&
                   active_block_context_epoch.load(std::memory_order_acquire) ==
                       (context_state >> 1);
        }
    };
    static_assert(sizeof(BlockState) == DEFAULT_CACHE_LINE_SIZE,
                  "BlockState must fit exactly one cache line");
    static_assert(std::atomic<OSThreadState>::is_always_lock_free,
                  "BlockState OSThreadState fields must be lock-free for signal-handler safety");
    static_assert(std::atomic<bool>::is_always_lock_free,
                  "BlockState::sampled_this_run must be lock-free for signal-handler safety");
    static_assert(std::atomic<u64>::is_always_lock_free,
                  "BlockState u64 fields must be lock-free for signal-handler safety");

    // Not signal-safe. Registry registration prepares backing under its mutex;
    // failure leaves lookups inert and the next registration retries.
    bool ensureAllocated();

    // Normal-only mode and backing preparation. The registry mutex serializes
    // every cold allocator; published backing survives resets until destruction.
    void setUnownedContextSnapshotsNeeded(bool needed);
    bool ensureUnownedContextAllocated(ThreadFilter::SlotID slot_id);
    bool readUnownedContext(ThreadFilter::SlotID slot_id, Context& context, u64& publication) const;
    bool canPublishUnownedContext(ThreadFilter::SlotID slot_id) const;
    static constexpr size_t kMaxWeightSegments = 4;
    struct WeightSegment {
        u64 epoch_start = 0;
        u64 weight = 0;
        size_t index = 0;
    };
    // The sampled owner alone accumulates; stripe-held serialization commits.
    // A full/unavailable array fails open without discarding older units.
    // Epoch-window starts preserve scaling when serialization is deferred.
    bool deferUnownedWeight(ThreadFilter::SlotID slot_id, u64 epoch_start);
    size_t copyUnownedWeightSegments(ThreadFilter::SlotID slot_id, WeightSegment* segments) const;
    bool unownedWeightMatchesEpoch(ThreadFilter::SlotID slot_id, u64 epoch_start) const;
    void commitUnownedWeightSegment(ThreadFilter::SlotID slot_id, const WeightSegment& segment);
    void clearUnownedWeightSegments(ThreadFilter::SlotID slot_id);
    // Publication requires a recording stripe (or a quiescent unit fixture).
    bool publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id, OSThreadState state,
                             const Context& context);
#ifdef UNIT_TEST
    void publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id, OSThreadState state);
#endif
    // Normal-thread callbacks; all recording stripes must exclude publication.
    void collectLiveTraceIds(CallTraceIdSet& live);
    void onUnpreservedTraceIds(const CallTraceIdSet& failed);

    // Returns nullptr if slot_id is out of range or storage is not yet
    // allocated (see ensureAllocated()).
    inline BlockState* slotForId(ThreadFilter::SlotID slot_id) const {
        if (slot_id < 0 || slot_id >= ThreadFilter::kMaxThreads) return nullptr;
        SlotStorage* storage = _storage.load(std::memory_order_acquire);
        return storage != nullptr ? &storage->slots[slot_id] : nullptr;
    }

    static constexpr ThreadFilter::SlotID kInvalidSlotId = -1;

    // Block-run tokens returned by enterBlockedRun() pack the generation in the
    // upper 32 bits and slot_id + 1 in the lower 32 bits, so 0 means "no run".
    // A valid slot_id (>= 0) is never encoded to a zero low word.
    static inline u64 encodeBlockRunToken(ThreadFilter::SlotID slot_id, u32 generation) {
        return (static_cast<u64>(generation) << 32) | static_cast<u32>(slot_id + 1);
    }
    // PRECONDITION (decoders): token != 0 ("no run"). A token whose low word is
    // 0 decodes to kInvalidSlotId (slotForId() returns nullptr for it).
    static inline ThreadFilter::SlotID tokenSlotId(u64 token) {
        assert(token != 0);
        u32 low = static_cast<u32>(token);
        return low == 0 ? kInvalidSlotId : static_cast<ThreadFilter::SlotID>(low - 1);
    }
    static inline u32 tokenGeneration(u64 token) {
        assert(token != 0);
        return static_cast<u32>(token >> 32);
    }

    u64 enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                        OSThreadState state, BlockRunOwner owner = BlockRunOwner::JAVA);
    // Generation-checked exits preserve retained unowned tails and cannot
    // clear another owner's run. Unconditional lifecycle cleanup uses resetSlot.
    bool exitBlockedRun(ThreadFilter::SlotID slot_id, u32 generation);
    // Clears stale suppression state so a new/reused slot cannot inherit a
    // predecessor's active block or once-per-run sampled marker. Called by
    // ThreadFilter at its own registry-lifecycle decision points.
    void resetSlot(ThreadFilter::SlotID slot_id, OSThreadState state);
    void resetAll();
    void clearActiveBlockRun(ThreadFilter::SlotID slot_id, OSThreadState state);
    // Reads the complete timer-side suppression payload and rejects it if slot
    // identity or block lifecycle changes before final validation.
    bool shouldSuppressOwnedBlock(ThreadFilter* registry, const ThreadEntry& entry) const;

#ifdef UNIT_TEST
    using AllocationHook = void (*)(void*);
    void setAllocationHookForTest(AllocationHook hook, void* arg) {
        _allocation_hook = hook;
        _allocation_hook_arg = arg;
    }
    void setAllocationFailureForTest(bool fail) {
        _allocation_failure.store(fail, std::memory_order_release);
    }
    static size_t storageSize();
    static size_t unownedContextChunkSizeForTest();
    bool exchangeUnownedContextAllocationFailureForTest(bool fail);
    void setUnownedContextPublicationForTest(ThreadFilter::SlotID slot_id, u64 publication);
    using UnownedContextReadHook = void (*)(void*);
    void setUnownedContextReadHookForTest(UnownedContextReadHook hook, void* arg) {
        _context_read_hook = hook;
        _context_read_hook_arg = arg;
    }
    using UnownedContextPublicationHook = void (*)(u32 words_written, void*);
    void setUnownedContextPublicationHookForTest(UnownedContextPublicationHook hook, void* arg) {
        _context_publication_hook = hook;
        _context_publication_hook_arg = arg;
    }

    // Pauses a JNI park/block hook after its caller resolved the registry slot,
    // before admission reads or changes that slot's block state.
    using BlockAdmissionHook = void (*)(void*);
    void setBlockAdmissionHookForTest(BlockAdmissionHook hook, void* arg) {
        _block_admission_hook = hook;
        _block_admission_hook_arg = arg;
    }

    using SuppressionSnapshotHook = void (*)(void*);
    void setSuppressionSnapshotHookForTest(SuppressionSnapshotHook hook, void* arg) {
        _suppression_snapshot_hook = hook;
        _suppression_snapshot_hook_arg = arg;
    }
#endif

private:
    struct alignas(DEFAULT_CACHE_LINE_SIZE) UnownedContextCell {
        std::atomic<u64> words[7]{};
        std::atomic<u64> publication{0};
        struct {
            std::atomic<u64> epoch_start{0};
            std::atomic<u64> weight{0};
        } segments[kMaxWeightSegments];
    };
    struct UnownedContextChunk {
        UnownedContextCell cells[ThreadFilter::kChunkSize];
    };
    static_assert(sizeof(UnownedContextCell) == 128, "Unowned context and provenance must fit two cache lines");
    static_assert(alignof(UnownedContextCell) == 64, "Unowned context cell must be cache aligned");
    static_assert(std::atomic<UnownedContextChunk*>::is_always_lock_free,
                  "Signal context chunk lookup must be lock-free");
    UnownedContextCell* unownedContextCell(ThreadFilter::SlotID slot_id) const;
    std::atomic<UnownedContextChunk*> _context_chunks[ThreadFilter::kMaxChunks]{};
    std::atomic<bool> _context_snapshots_needed{false};

    struct SlotStorage {
        std::array<BlockState, ThreadFilter::kMaxThreads> slots;
        std::array<std::atomic<u64>, ThreadFilter::kMaxThreads / 64> roots{};
    };
    // Signal paths only load backing; only the destructor reclaims it.
    std::atomic<SlotStorage*> _storage{nullptr};

#ifdef UNIT_TEST
    std::atomic<bool> _allocation_failure{false};
    AllocationHook _allocation_hook = nullptr;
    void* _allocation_hook_arg = nullptr;
    std::atomic<bool> _context_allocation_failure{false};
    UnownedContextReadHook _context_read_hook = nullptr;
    void* _context_read_hook_arg = nullptr;
    UnownedContextPublicationHook _context_publication_hook = nullptr;
    void* _context_publication_hook_arg = nullptr;
    BlockAdmissionHook _block_admission_hook = nullptr;
    void* _block_admission_hook_arg = nullptr;
    SuppressionSnapshotHook _suppression_snapshot_hook = nullptr;
    void* _suppression_snapshot_hook_arg = nullptr;
#endif
};

#endif // _WALLCLOCKBLOCKTRACKER_H
