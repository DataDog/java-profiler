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
#include <functional>
#include <utility>
#include <vector>

#include "arch.h"
#include "taskBlockDiagnostics.h"
#include "counters.h"
#include "callTraceHashTable.h"
#include "countingAllocator.h"
#include "context.h"
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
    // The exit's claim on the open segment: segment_start is where the part no
    // dump reported begins; segment_advanced is set once a dump reported a part.
    bool segment_claimed{false};
    bool segment_advanced{false};
    u64 segment_start{0};
};

class WallClockBlockTracker {
public:
    WallClockBlockTracker() = default;
    ~WallClockBlockTracker();

    static constexpr int kBlockRunSlotBits = 11;
    static constexpr u64 kBlockRunSlotMask = (1ULL << kBlockRunSlotBits) - 1;
    static constexpr u64 kMaxBlockRunGeneration = UINT64_MAX >> kBlockRunSlotBits;
    static_assert(ThreadFilter::kMaxThreads == (1 << kBlockRunSlotBits),
                  "block-run token slot bits must cover every ThreadFilter slot");

    // Published backing survives registry resets and recording restarts, so
    // captured pointers remain valid until destruction.
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
        // Stop signal-side accumulation without discarding the pending tail.
        inline bool pauseUnownedBlockedFallback() {
            return unowned_blocked_fallback_enabled.exchange(0, std::memory_order_acq_rel) != 0;
        }
        inline void resumeUnownedBlockedFallback() {
            unowned_blocked_fallback_enabled.store(1, std::memory_order_release);
        }
        inline void enableUnownedBlockedFallback() {
            unowned_blocked_fallback_enabled.store(1, std::memory_order_release);
        }
        inline void disableUnownedBlockedFallback() {
            unowned_blocked_fallback_enabled.store(0, std::memory_order_release);
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
        // Transactional tails commit only successful writes; lifecycle resets
        // invalidate the payload. Context/owned-run transitions retain it.
        // Legacy flush validates the complete tail before consuming anything.
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
            state = unowned_blocked_state.load(std::memory_order_acquire);
            unowned_blocked_decision_count.store(0, std::memory_order_relaxed);
            // A concurrent lifecycle reset may have intervened between the
            // loads and the exchanges.
            return call_trace_id != 0 && weight != 0 && state != OSThreadState::UNKNOWN;
        }
        // identity_slot supplies the context-window state, which lives on
        // ThreadFilter::Slot. See ThreadFilter::Slot::rawContextWindowState().
        // On success the run is owned but not yet visible to readers; the
        // caller publishes it with publishActiveBlockRun().
#ifdef UNIT_TEST
        inline static void (*prepare_context_hook_for_test)(ThreadFilter::Slot*) = nullptr;
#endif
        inline bool tryPrepareActiveBlockRun(ThreadFilter::Slot* identity_slot,
                                             BlockRunOwner owner,
                                             u64* generation_out,
                                             bool outside_context_required
                                             TASK_BLOCK_DIAGNOSTIC_ONLY(, const TaskBlockDiagnosticRecord* diagnostic = nullptr)) {
            u64 context_state = identity_slot->rawContextWindowState();
            if (outside_context_required && (context_state & 1) != 0) {
                TASK_BLOCK_DIAGNOSTIC(ENTER_INSIDE_CONTEXT_WINDOW, diagnostic, context_state);
                return false;
            }
            int expected_owner = static_cast<int>(BlockRunOwner::NONE);
            if (!active_block_owner.compare_exchange_strong(
                    expected_owner, static_cast<int>(owner), std::memory_order_acq_rel,
                    std::memory_order_acquire)) {
                TASK_BLOCK_DIAGNOSTIC(ENTER_OWNER_ALREADY_HELD, diagnostic, expected_owner);
                return false;
            }
#ifdef UNIT_TEST
            if (prepare_context_hook_for_test != nullptr) prepare_context_hook_for_test(identity_slot);
#endif
            u64 observed_context_state = outside_context_required ? identity_slot->rawContextWindowState() : context_state;
            if (outside_context_required && observed_context_state != context_state) {
                TASK_BLOCK_DIAGNOSTIC(ENTER_CONTEXT_CHANGED_AFTER_OWNER_CAS, diagnostic, observed_context_state);
                active_block_owner.store(static_cast<int>(BlockRunOwner::NONE),
                                         std::memory_order_release);
                return false;
            }
            u64 generation = block_generation.load(std::memory_order_relaxed);
            if (generation == kMaxBlockRunGeneration) {
                TASK_BLOCK_DIAGNOSTIC(ENTER_GENERATION_SATURATED, diagnostic, generation);
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
            resetUnownedBlockedSampling();
            enableUnownedBlockedFallback();
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
        }
        bool needsActiveBlockRunClear() const {
            // TASK_BLOCK must survive a context crossing until its paired exit.
            if (activeBlockOwner() == BlockRunOwner::TASK_BLOCK) return false;
            return activeBlockOwner() != BlockRunOwner::NONE ||
                   activeBlockState() != OSThreadState::UNKNOWN || sampledBlockGeneration() != 0;
        }
#ifdef UNIT_TEST
        // Observation only; this counter publishes no payload or layout changes.
        inline static std::atomic<u64> clear_count_for_test{0};
#endif
        // Release owned suppression without discarding retained context or weight.
        // UNKNOWN precedes owner NONE; generation stays monotonic for stale tokens.
        inline void clearActiveBlockRun() {
#ifdef UNIT_TEST
            clear_count_for_test.fetch_add(1, std::memory_order_relaxed);
#endif
            active_block_state.store(OSThreadState::UNKNOWN, std::memory_order_release);
            resetSampledBlockGeneration();
            enableUnownedBlockedFallback();
            active_block_owner.store(static_cast<int>(BlockRunOwner::NONE), std::memory_order_release);
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
    struct PendingUnownedWeight {
        u64 total = 0;
        u64 max_segment = 0;
    };
    // Release-available test support: lock-free read of tid's slot in the registry's current
    // recording epoch, all zero when the tid has no entry. Normal threads only (JNI test seam).
    PendingUnownedWeight pendingUnownedWeightForTest(const ThreadFilter& registry, int tid) const;
    // Publication requires a recording stripe (or a quiescent unit fixture).
    bool publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id, OSThreadState state,
                             const Context& context);
#ifdef UNIT_TEST
    void publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id, OSThreadState state);
#endif
    // Normal-thread callbacks; all recording stripes must exclude publication.
    void collectLiveTraceIds(CallTraceIdSet& live);
    using EpochStarts = std::vector<u64, CountingAllocator<u64, NM_WALLCLOCK>>;
    // Appends the epoch starts of root slots' pending segments, sorted and unique.
    void collectUnownedEpochStarts(EpochStarts& epochs) const;
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

    // start_ticks opens the run's first segment; 0 samples TSC::ticks().
    u64 enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                        OSThreadState state, BlockRunOwner owner = BlockRunOwner::JAVA,
                        u64 start_ticks = 0
                        TASK_BLOCK_DIAGNOSTIC_ONLY(, TaskBlockDiagnosticRecord* admitted_origin = nullptr));
    bool exitBlockedRun(ThreadFilter::SlotID slot_id, u64 generation);
    // Same generation check as exitBlockedRun(slot_id, generation), but
    // captures the run's state, context eligibility and segment claim before clearing it.
    bool snapshotAndExitBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                                   u64 generation, BlockRunSnapshot* snapshot
                                   TASK_BLOCK_DIAGNOSTIC_ONLY(, const TaskBlockDiagnosticRecord* origin = nullptr));

    // Open-segment protocol; see ProfilingEngines.md#open-interval-segments.
    // control packs generation << 2 | ADVANCED | start index; generation 0 means closed.
    struct OpenSegment {
        u64 control = 0;
        u64 start = 0;
        u64 generation() const { return control >> kSegmentGenerationShift; }
    };
    // Any thread. False when the slot has no open segment.
    bool readOpenSegment(ThreadFilter::SlotID slot_id, OpenSegment& segment) const;
    // Single advancer: callers hold Profiler::_state_lock. On true the caller owns
    // [segment.start, end_ticks); the run restarts there, or close_run ends it.
    bool advanceOpenSegment(ThreadFilter::SlotID slot_id, const OpenSegment& segment,
                            u64 end_ticks, bool close_run);

    using TailFlush = std::function<bool(ThreadFilter::SlotID, int, bool)>;
    // Wired once before registry use. Only the drained stop path passes blocking=true;
    // elsewhere lock contention must retain the tail, not wait.
    // Profiler wires this during static initialization, before TLS keys are guaranteed ready.
    void setTailFlush(TailFlush flush) { _tail_flush = std::move(flush); }
    // Teardown retains failed writes; registry reclamation must wait for success.
    bool flushUnownedTail(ThreadFilter::SlotID slot_id, int tid, bool blocking = false);
    bool retireSlot(ThreadFilter::SlotID slot_id, int tid);
    // Generation-checked exits preserve retained unowned context and epoch segments.
    // Clears stale suppression state so a new/reused slot cannot inherit a
    // predecessor's active block or sampled generation. Called by ThreadFilter
    // at its own registry-lifecycle decision points. block_generation is left
    // untouched so tokens issued before the reset cannot match a later run.
    void resetSlot(ThreadFilter::SlotID slot_id);
    // Preserves ordinary generations across reuse; restarts only a saturated
    // generation after native-owner teardown. Prior-owner runs must have ended.
    void resetSlotForReuse(ThreadFilter::SlotID slot_id);
    void resetAll();
    // Context boundaries clear missed instrumentation exits, not paired TASK_BLOCK runs.
    void clearActiveBlockRun(ThreadFilter::SlotID slot_id);
    bool hasActiveBlockRun(ThreadFilter::SlotID slot_id) const;
    // Drops every pending unowned tail (trace id, weight and epoch segments);
    // owned runs keep their state. Callers exclude signal handlers.
    // Returns the pending weight it discarded.
    u64 resetUnownedBlockedTails();
    // Timer- and signal-side owned-block decisions. All of them read the
    // complete suppression payload and reject it if slot identity or block
    // lifecycle changes before final validation.
    bool isOwnedBlockSuppressionCandidate(ThreadFilter* registry,
                                          const ThreadEntry& entry) const;
    // Returns the generation and sampled state from one validated payload snapshot.
    bool ownedBlockDecision(ThreadFilter* registry, const ThreadEntry& entry,
                            bool& already_sampled, u64& generation) const {
        return ownedBlockGeneration(registry, entry, generation, already_sampled);
    }

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
    TailFlush _tail_flush;

    static constexpr u64 kSegmentIndexBit = 1;
    static constexpr u64 kSegmentAdvancedBit = 2;
    static constexpr int kSegmentGenerationShift = 2;
    static_assert((kMaxBlockRunGeneration << kSegmentGenerationShift) >> kSegmentGenerationShift ==
                  kMaxBlockRunGeneration, "segment control must hold every block-run generation");
    // A dump writes only the start[] entry that control does not select, so the
    // exit's exchange and the dump's CAS on control decide alone who owns a tick.
    struct SegmentState {
        std::atomic<u64> control{0};
        std::atomic<u64> start[2]{};
    };
    SegmentState* segmentForId(ThreadFilter::SlotID slot_id) const;
    void openSegment(ThreadFilter::SlotID slot_id, u64 generation, u64 start_ticks);
    // Closes the open segment, if any; fills snapshot's claim when it was generation's.
    void closeSegment(ThreadFilter::SlotID slot_id, u64 generation = 0,
                      BlockRunSnapshot* snapshot = nullptr);

    bool ownedBlockGeneration(ThreadFilter* registry, const ThreadEntry& entry,
                              u64& generation, bool& already_sampled) const;

    // Span and root ids, then each pair of 32-bit tags packed into one word.
    static constexpr int kContextIdWords = 2;
    static constexpr int kContextTagWords = static_cast<int>(DD_TAGS_CAPACITY / 2);
    static constexpr int kContextWords = kContextIdWords + kContextTagWords;
    static_assert(DD_TAGS_CAPACITY % 2 == 0, "Unowned context packs tags in pairs");
    struct alignas(DEFAULT_CACHE_LINE_SIZE) UnownedContextCell {
        std::atomic<u64> words[kContextWords]{};
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
        std::array<SegmentState, ThreadFilter::kMaxThreads> segments{};
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
