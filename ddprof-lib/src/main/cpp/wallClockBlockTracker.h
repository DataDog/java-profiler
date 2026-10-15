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
#include <cstdint>
#include <functional>

#include "arch.h"
#include "counters.h"
#include "threadFilter.h"
#include "threadState.h"

enum class BlockRunOwner : int {
    NONE = 0,
    JAVA = 1,
    JVMTI = 2,
    NATIVE = 3,
    // Explicit, caller-paced runs opened by beginTaskBlock0/endTaskBlock0.
    // Unlike JAVA/JVMTI/NATIVE (instrumentation hooks that assume their owning
    // thread can never be inside a run when it calls ThreadFilter::add()), a
    // TASK_BLOCK run can legitimately span an add()+remove() pair on its own
    // thread - see BlockState::clearActiveBlockRun().
    TASK_BLOCK = 4,
};

// Wall-clock owned/unowned block-run suppression state, addressed in parallel
// to ThreadFilter's own slots by ThreadFilter::SlotID. Kept separate from
// ThreadFilter::Slot because this is wall-clock-engine policy (has this
// blocked interval already produced a sample?), not thread identity - see
// threadFilter.h for the registry itself. Methods that need registry facts
// (context-window state, unfiltered-tracking mode) take a ThreadFilter
// pointer/Slot pointer as an explicit parameter rather than storing one, so
// tests can pair a tracker with any ThreadFilter instance.
struct BlockRunSnapshot {
    OSThreadState active_state{OSThreadState::UNKNOWN};
    bool context_eligible{false};
};

class WallClockBlockTracker {
public:
    // Reports/retracts the ~128 KiB eager _slots allocation to NativeMem
    // (NM_WALLCLOCK) -- unlike ThreadFilter's own chunk storage, this array
    // is not lazily allocated, so every process that constructs a
    // WallClockBlockTracker (currently: Profiler, unconditionally) pays for
    // it whether or not wall precheck is ever used, and that cost should be
    // visible in memory accounting.
    WallClockBlockTracker();
    ~WallClockBlockTracker();

    static constexpr int kBlockRunSlotBits = 11;
    static constexpr u64 kBlockRunSlotMask = (1ULL << kBlockRunSlotBits) - 1;
    static constexpr u64 kMaxBlockRunGeneration = UINT64_MAX >> kBlockRunSlotBits;
    static_assert(ThreadFilter::kMaxThreads == (1 << kBlockRunSlotBits),
                  "block-run token slot bits must cover every ThreadFilter slot");

    // One cache line per slot, mirroring ThreadFilter::Slot's own
    // false-sharing avoidance. BlockState instances are process-lifetime
    // (owned by WallClockBlockTracker's inline array), so a captured
    // BlockState* is always dereferenceable.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) BlockState {
        static constexpr u64 kUnownedBlockedFallbackRatio = 10;

        std::atomic<u64>           unowned_blocked_pending_weight{0};
        std::atomic<u64>           unowned_blocked_decision_count{0};
        std::atomic<u64>           unowned_blocked_call_trace_id{0};
        std::atomic<u64>           active_block_context_epoch{0};
        std::atomic<u64>           block_generation{0};
        // The most recent owned-block generation for which a MethodSample was
        // recorded successfully. Generations are monotonic, so a delayed
        // completion from an older run cannot mark a newer run as sampled.
        std::atomic<u64>           sampled_block_generation{0};
        std::atomic<OSThreadState> unowned_blocked_state{OSThreadState::UNKNOWN};
        std::atomic<int>           active_block_owner{static_cast<int>(BlockRunOwner::NONE)};
        std::atomic<int>           unowned_blocked_fallback_enabled{1};
        // Set by explicit block enter/exit hooks. It lets the timer skip sending a signal
        // only while instrumentation still owns a suppressible blocking interval.
        std::atomic<OSThreadState> active_block_state{OSThreadState::UNKNOWN};
        // The fields above fill the cache line exactly, so there is no padding
        // member; alignas() and the static_assert below keep it at one line.

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
#ifdef UNIT_TEST
        inline void setBlockGenerationForTest(u64 value) {
            block_generation.store(value, std::memory_order_relaxed);
        }
#endif
        inline void resetBlockGeneration() {
            block_generation.store(0, std::memory_order_relaxed);
        }
        inline u64 sampledBlockGeneration() const {
            return sampled_block_generation.load(std::memory_order_acquire);
        }
        inline void markBlockGenerationSampled(u64 generation) {
            u64 sampled = sampled_block_generation.load(std::memory_order_relaxed);
            while (sampled < generation &&
                   !sampled_block_generation.compare_exchange_weak(
                       sampled, generation, std::memory_order_release,
                       std::memory_order_relaxed)) {
            }
        }
        inline void resetSampledBlockGeneration() {
            sampled_block_generation.store(0, std::memory_order_relaxed);
        }
        inline bool unownedBlockedFallbackEnabled() const {
            return unowned_blocked_fallback_enabled.load(std::memory_order_acquire) != 0;
        }
        inline void enableUnownedBlockedFallback() {
            resetUnownedBlockedSampling();
            unowned_blocked_fallback_enabled.store(1, std::memory_order_release);
        }
        inline void disableUnownedBlockedFallback() {
            unowned_blocked_fallback_enabled.store(0, std::memory_order_release);
            resetUnownedBlockedSampling();
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
        // identity_slot supplies the context-window state, which lives on
        // ThreadFilter::Slot. See ThreadFilter::Slot::rawContextWindowState().
        // On success the run is owned but not yet visible to readers; the
        // caller publishes it with publishActiveBlockRun().
        inline bool tryPrepareActiveBlockRun(ThreadFilter::Slot* identity_slot,
                                             BlockRunOwner owner,
                                             u64* generation_out,
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
            u64 generation = block_generation.load(std::memory_order_relaxed);
            if (generation == kMaxBlockRunGeneration) {
                active_block_owner.store(static_cast<int>(BlockRunOwner::NONE),
                                         std::memory_order_release);
                Counters::increment(THREAD_REGISTRY_BLOCK_GENERATION_SATURATED);
                return false;
            }
            generation++;
            block_generation.store(generation, std::memory_order_relaxed);
            active_block_context_epoch.store(context_state >> 1, std::memory_order_relaxed);
            resetSampledBlockGeneration();
            disableUnownedBlockedFallback();
            *generation_out = generation;
            return true;
        }
        inline void publishActiveBlockRun(OSThreadState state) {
            active_block_state.store(state, std::memory_order_release);
        }
        inline void resetSlot() {
            active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            resetSampledBlockGeneration();
            enableUnownedBlockedFallback();
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
        }
        // Drops an owned block run whose exit was missed (e.g. an exception
        // path with no finally). A no-op when no run is owned, so the
        // unowned-blocked sampling weight, which spans context-window
        // entries/exits by design, is left untouched on every ordinary
        // context entry. When a run is owned, tryPrepareActiveBlockRun()
        // already disabled and cleared the unowned fallback, so resetSlot()
        // loses no weight. block_generation is kept, so the stale token's
        // eventual exit fails its generation check.
        //
        // TASK_BLOCK is exempt: beginTaskBlock0/endTaskBlock0 pair explicitly
        // around caller-controlled code, so the same thread calling
        // ThreadFilter::add() mid-run is an expected crossing, not a stuck
        // leak. Tearing the run down here would make endTaskBlock0 see a
        // "never started" run instead of a "crossed" one, losing the
        // TASK_BLOCK_SKIPPED_CONTEXT_WINDOW signal. Leaving it alone is safe:
        // enterContextWindow() already bumped the context epoch, so
        // activeBlockRemainedOutsideContextWindow() reports it ineligible at
        // exit without any extra bookkeeping here.
        inline void clearActiveBlockRun() {
            BlockRunOwner owner = activeBlockOwner();
            if (owner == BlockRunOwner::NONE || owner == BlockRunOwner::TASK_BLOCK) {
                return;
            }
            resetSlot();
        }
        // identity_slot supplies the context-window state, which lives on
        // ThreadFilter::Slot. See ThreadFilter::Slot::rawContextWindowState().
        inline bool activeBlockRemainedOutsideContextWindow(ThreadFilter::Slot* identity_slot) const {
            u64 context_state = identity_slot->rawContextWindowState();
            return (context_state & 1) == 0 &&
                   active_block_context_epoch.load(std::memory_order_acquire) ==
                       (context_state >> 1);
        }
        inline BlockRunSnapshot snapshotBlockRun(ThreadFilter::Slot* identity_slot) const {
            BlockRunSnapshot snapshot;
            snapshot.active_state = activeBlockState();
            snapshot.context_eligible = activeBlockRemainedOutsideContextWindow(identity_slot);
            return snapshot;
        }
    };
    static_assert(sizeof(BlockState) == DEFAULT_CACHE_LINE_SIZE,
                  "BlockState must fit exactly one cache line");
    static_assert(std::atomic<OSThreadState>::is_always_lock_free,
                  "BlockState OSThreadState fields must be lock-free for signal-handler safety");
    static_assert(std::atomic<u64>::is_always_lock_free,
                  "BlockState u64 fields must be lock-free for signal-handler safety");

    // Returns nullptr if slot_id is out of range. Storage is a single eager
    // allocation sized to ThreadFilter::kMaxThreads (unlike ThreadFilter's own
    // lazily-chunked storage), so lookup is a direct array index.
    inline BlockState* slotForId(ThreadFilter::SlotID slot_id) const {
        if (slot_id < 0 || slot_id >= ThreadFilter::kMaxThreads) return nullptr;
        return const_cast<BlockState*>(&_slots[slot_id]);
    }

    // Block-run tokens returned by enterBlockedRun() pack the generation in the
    // upper 64 - kBlockRunSlotBits bits and slot_id in the low kBlockRunSlotBits
    // bits. Generations start at 1, so 0 means "no run".
    static inline u64 encodeBlockRunToken(ThreadFilter::SlotID slot_id, u64 generation) {
        return (generation << kBlockRunSlotBits) | static_cast<u64>(slot_id);
    }
    static inline ThreadFilter::SlotID tokenSlotId(u64 token) {
        return static_cast<ThreadFilter::SlotID>(token & kBlockRunSlotMask);
    }
    static inline u64 tokenGeneration(u64 token) {
        return token >> kBlockRunSlotBits;
    }
    static inline bool decodeBlockRunToken(u64 token, ThreadFilter::SlotID& slot_id,
                                           u64& generation) {
        if (token == 0) return false;
        slot_id = tokenSlotId(token);
        generation = tokenGeneration(token);
        return generation != 0;
    }

    u64 enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                        OSThreadState state, BlockRunOwner owner = BlockRunOwner::JAVA);
    // Unconditional cleanup, used only by tests and the fuzzer (registry
    // reset/unregister paths use resetSlot()). Normal block lifecycles must
    // use the generation-checked overload so they cannot clear another owner.
    void exitBlockedRun(ThreadFilter::SlotID slot_id);
    bool exitBlockedRun(ThreadFilter::SlotID slot_id, u64 generation);
    // Same generation check as exitBlockedRun(slot_id, generation), but
    // captures the run's state and context eligibility before clearing it.
    bool snapshotAndExitBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                                   u64 generation, BlockRunSnapshot* snapshot);
    // Clears stale suppression state so a new/reused slot cannot inherit a
    // predecessor's active block or sampled generation. Called by ThreadFilter
    // at its own registry-lifecycle decision points. block_generation is left
    // untouched so tokens issued before the reset cannot match a later run.
    void resetSlot(ThreadFilter::SlotID slot_id);
    // Also restarts block_generation at 0. Only for a slot popped from the
    // free list, whose previous owner unregistered after ending its runs (see
    // THREAD_REGISTRY_UNREGISTER_ACTIVE_BLOCK_RUN).
    void resetSlotForReuse(ThreadFilter::SlotID slot_id);
    void resetAll();
    // Drops a stuck owned block run (one whose exit was missed) without
    // touching the unowned-blocked sampling weight. Called by
    // ThreadFilter::add() on every context-window entry; see
    // BlockState::clearActiveBlockRun() for why this is safe and why it
    // leaves the weight alone.
    void clearActiveBlockRun(ThreadFilter::SlotID slot_id);
    bool hasActiveBlockRun(ThreadFilter::SlotID slot_id) const;
    // Liveness hook for CallTraceStorage::processTraces: a slot may cache a
    // call_trace_id for a still-blocked thread's weighted fallback tail
    // (recordUnownedBlockedSample) well before flushUnownedBlockedTail() emits
    // it. Without this, a chunk rotation racing that window drops the trace,
    // and the eventual deferred sample references an id with no constant-pool
    // entry in the chunk it lands in.
    void collectUnownedBlockedTraceIds(const std::function<void(u64)>& visit) const;

    // Timer- and signal-side owned-block decisions. All of them read the
    // complete suppression payload and reject it if slot identity or block
    // lifecycle changes before final validation.
    bool activeOwnedBlockGeneration(ThreadFilter* registry, const ThreadEntry& entry,
                                    u64& generation) const;
    bool isOwnedBlockSuppressionCandidate(ThreadFilter* registry,
                                          const ThreadEntry& entry) const;
    // Single-pass merge of activeOwnedBlockGeneration()/isOwnedBlockSuppressionCandidate():
    // callers that need both the generation and the already-sampled state should use this
    // instead of calling the two wrappers above in sequence, which would re-validate the
    // same slot atomics twice.
    bool ownedBlockDecision(ThreadFilter* registry, const ThreadEntry& entry,
                            bool& already_sampled, u64& generation) const {
        return ownedBlockGeneration(registry, entry, generation, already_sampled);
    }

#ifdef UNIT_TEST
    using SuppressionSnapshotHook = void (*)(void*);
    void setSuppressionSnapshotHookForTest(SuppressionSnapshotHook hook, void* arg) {
        _suppression_snapshot_hook = hook;
        _suppression_snapshot_hook_arg = arg;
    }
#endif

private:
    bool ownedBlockGeneration(ThreadFilter* registry, const ThreadEntry& entry,
                              u64& generation, bool& already_sampled) const;

    std::array<BlockState, ThreadFilter::kMaxThreads> _slots;

#ifdef UNIT_TEST
    SuppressionSnapshotHook _suppression_snapshot_hook = nullptr;
    void* _suppression_snapshot_hook_arg = nullptr;
#endif
};

#endif // _WALLCLOCKBLOCKTRACKER_H
