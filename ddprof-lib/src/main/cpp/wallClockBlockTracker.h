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
    // BlockState storage (~128 KiB) is allocated lazily by ensureAllocated(),
    // which ThreadFilter::registerThread() calls under _registry_lock on the
    // first registration. It is recorded under NM_WALLCLOCK only once
    // allocated and retracted by the destructor, so processes that never
    // register a thread pay nothing.
    WallClockBlockTracker();
    ~WallClockBlockTracker();

    // One cache line per slot, mirroring ThreadFilter::Slot's own
    // false-sharing avoidance. Storage, once published, is never freed before
    // ~WallClockBlockTracker (R-B2), so a captured BlockState* stays valid.
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
        // Unowned-blocked bookkeeping (pending weight, call_trace_id, state,
        // decision_count) is cleared ONLY by (R-B1):
        //  (a) a successful flushUnownedBlockedTail();
        //  (b) consumeUnownedBlockedWeight() at a recorded sample (weight only);
        //  (c) registry-lifecycle resetSlot()/resetAll() (registerThread,
        //      refreshSlotForRecording, unregisterThreadLocked,
        //      retireThreadByTid, drainRetiredLocked, clearActive,
        //      resetSlotRunState).
        // The thread's own events - a failed flush, owned-run entry or
        // generation-checked exit, context-window entry - must not clear it.
        // Validate, then consume: an incomplete tail reports what was read
        // through the out-params and consumes nothing. Accepted residual: the
        // sampling cadence now carries across runs, so up to kRatio-1 units may
        // be attributed to an earlier run's stack/state.
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
        // Clears only the owned block-run fields (owner, active state, the
        // once-per-run sampled marker), leaving the unowned-blocked
        // statistical sampling weight untouched -- unlike resetSlot(), which
        // is for registry-lifecycle events (slot reuse, epoch reset) where
        // the predecessor's weight must not leak into the new owner. This
        // narrower reset is for a context-window re-entry on the slot's own
        // thread: it only needs to drop a block run whose exit was missed
        // (e.g. an exception path with no finally), not disturb the
        // amortized weight tracking, which spans context-window
        // entries/exits by design. It is also the generation-checked
        // exitBlockedRun()'s reset, so an owned run's exit preserves an earlier
        // unowned tail (R-B1). Keep the order: state UNKNOWN before owner NONE.
        inline void clearActiveBlockRun(OSThreadState state) {
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

    // NOT signal-safe. Called by ThreadFilter::registerThread() under
    // _registry_lock. Returns false only on allocation failure (the tracker
    // stays inert and the allocation is retried on the next registration).
    bool ensureAllocated();

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
    // Generation-checked exit: block lifecycles use it so they cannot clear
    // another owner's run. Clears only the owned-run fields; the
    // unowned-blocked tail is preserved (R-B1). Callers that need an
    // unconditional clear use resetSlot(slot_id, OSThreadState::RUNNABLE).
    bool exitBlockedRun(ThreadFilter::SlotID slot_id, u32 generation);
    // Clears stale suppression state so a new/reused slot cannot inherit a
    // predecessor's active block or once-per-run sampled marker. Called by
    // ThreadFilter at its own registry-lifecycle decision points.
    void resetSlot(ThreadFilter::SlotID slot_id, OSThreadState state);
    void resetAll();
    // Drops a stuck owned block run (one whose exit was missed) without
    // touching the unowned-blocked sampling weight. Called by
    // ThreadFilter::add() on every context-window entry; see
    // BlockState::clearActiveBlockRun() for why this is safe and why it
    // leaves the weight alone.
    void clearActiveBlockRun(ThreadFilter::SlotID slot_id, OSThreadState state);
    // Reads the complete timer-side suppression payload and rejects it if slot
    // identity or block lifecycle changes before final validation.
    bool shouldSuppressOwnedBlock(ThreadFilter* registry, const ThreadEntry& entry) const;

#ifdef UNIT_TEST
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
    struct SlotStorage {
        std::array<BlockState, ThreadFilter::kMaxThreads> slots;
    };
    // Published once by ensureAllocated(); never freed before the destructor
    // (R-B2). Signal paths only load it, never allocate.
    std::atomic<SlotStorage*> _storage{nullptr};

#ifdef UNIT_TEST
    BlockAdmissionHook _block_admission_hook = nullptr;
    void* _block_admission_hook_arg = nullptr;
    SuppressionSnapshotHook _suppression_snapshot_hook = nullptr;
    void* _suppression_snapshot_hook_arg = nullptr;
#endif
};

#endif // _WALLCLOCKBLOCKTRACKER_H
