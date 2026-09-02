/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <set>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "arguments.h"
#include "counters.h"
#include "livenessTracker.h"
#include "profiler.h"
#include "referenceChains.h"
#include "vmEntry.h"
#include "../../main/cpp/gtest_crash_handler.h"

static constexpr char REFERENCE_CHAINS_TEST_NAME[] = "ReferenceChainsTest";

class ReferenceChainsGlobalSetup {
public:
    ReferenceChainsGlobalSetup() {
        installGtestCrashHandler<REFERENCE_CHAINS_TEST_NAME>();
    }
    ~ReferenceChainsGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

static ReferenceChainsGlobalSetup global_setup;

// ---------------------------------------------------------------------------
// VMTestAccessor - friend of VM (vmEntry.h), lets tests swap VM::_jvmti for a
// mock. This gtest binary has no live JVM attached (see jvmSupport_ut.cpp's
// fixture comment for the same constraint on a different subsystem), but
// ReferenceChainTracker::start()/stop() now call VM::jvmti()->
// SetEventNotificationMode() (the lazy event-enable step), so a mock is
// required for those calls to be exercised without crashing on a null
// jvmtiEnv.
// ---------------------------------------------------------------------------
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// ---------------------------------------------------------------------------
// ReferenceChainsTestAccessor - same pattern as VMTestAccessor above, for the
// same reason: ReferenceChainTracker::instance() is a process-wide singleton
// (referenceChains.h), so the search-lifecycle fields
// (_search_state/_search_started/_pending_expand/...) would otherwise leak
// from one ReferenceChainsBfsTest TEST_F into the next in this same gtest
// binary - e.g. a test that drives the search to SearchState::COMPLETED
// would leave every later test's runPass() call a permanent no-op (see
// runPass()'s "already terminal -> no-op" branch). reset() puts the tracker
// back to its just-constructed state; it does not change production
// behavior.
// ---------------------------------------------------------------------------
class ReferenceChainsTestAccessor {
public:
    static void reset() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        delete t->_frontier;
        t->_frontier = nullptr;
        t->_class_tags = ClassTagTable();
        t->_last_resolved_class_count = 0;
        // Without these two, a prior test's fully-swept (or
        // partially-swept) admitStaticFieldRoots() state survives in this
        // process-wide singleton and can wrongly skip the sweep entirely on
        // this test's first pass if its resolved class count happens to
        // match whatever an earlier test last left behind - see
        // resetForRestart()'s identical reset of these same fields for the
        // production-restart equivalent of this same contract.
        t->_last_static_field_class_count = -1;
        t->_static_field_sweep_cursor = 0;
        t->_static_field_sweep_cycle_truncated = false;
        t->_next_tag = 1;
        // Shared with LivenessTracker (classTagAllocator.h) - process-wide,
        // not per-ReferenceChainTracker-instance, so it needs its own reset
        // seam rather than being a plain member write.
        ClassTagAllocator::resetForTest();
        t->_search_started = false;
        t->_tags_released = true;
        t->_search_state = SearchState::RUNNING;
        t->_abandon_reason = SearchAbandonReason::NONE;
        t->_search_start_ns = 0;
        t->_pending_expand.clear();
        t->_priority_expand.clear();
        t->_priority_expand_set.clear();
        t->_last_pass_gc_finish_epoch = 0;
        t->_last_pass_ns = 0;
        t->_passes_run = 0;
        t->_passes_since_last_progress = 0;
        t->_candidate_count = 0;
        t->_candidate_found_bits = 0;
        memset(t->_candidate_discovered_count, 0, sizeof(t->_candidate_discovered_count));
        t->_passes_since_last_candidate_progress = 0;
        t->_last_candidate_progress_mark = 0;
        t->_canary_stuck_restart_count = 0;
        t->_resolved_chains.clear();
        t->_safepoint_pain_budget = PainBudget();
        t->_cpu_pain_budget = PainBudget();
        t->_search_pain_ms = 0;
        t->_root_kind_rotation_cursor = 1;
        t->_stale_expanded_rotation_cursor = 1;
        t->_static_anchor_rotation_cursor = 1;
        t->_thread_walk_anchor_cursor = 0;
        memset(t->_candidate_qualifying_tid_count, 0,
               sizeof(t->_candidate_qualifying_tid_count));
        t->_hop_label_cache.clear();
        t->_watched_leak_klass_count = 0;
        t->_leak_signature_totals.clear();
        t->_leak_signature_prev_totals.clear();
        t->_leak_parent_fanout.clear();
        t->_borrowed_budget = 0;
        t->_consecutive_under_target_passes = 0;
        // Adaptive batch + lane state: NOT covered by anything above, and a
        // prior test that drove expansion leaves a non-zero EMA, a live
        // batch size, a stale pass deadline, and/or a mid-alternation lane
        // toggle behind - all of which silently change the next test's
        // expandFrontier() arithmetic (exact-value asserts on batch sizing
        // only pass standalone otherwise).
        t->_gotw_ema_call_ns = 0;
        t->_gotw_batch_size = 0;
        t->_pass_deadline_ns = 0;
        t->_expand_lane_prefer_priority = true;
    }

    // Search restart + pain budget (SearchRestartTest below) - same
    // rationale as the pacing accessors above: private state a test needs to
    // drive/observe directly.
    static bool canAffordNewSearch(u64 now_ns) {
        return ReferenceChainTracker::instance()->canAffordNewSearch(now_ns);
    }

    static bool shouldRunPass(u64 now_ns) {
        return ReferenceChainTracker::instance()->shouldRunPass(now_ns);
    }

    static void setSearchPainMs(u64 ms) {
        ReferenceChainTracker::instance()->_search_pain_ms = ms;
    }

    static void setCandidateFrontierTagForTest(int idx, jlong tag) {
        ReferenceChainTracker::instance()->setCandidateFrontierTagForTest(idx, tag);
    }

    static void setCandidateCountForTest(int n) {
        ReferenceChainTracker::instance()->setCandidateCountForTest(n);
    }

    // Canary-lane backoff state wrappers - see _canary_backoff_mult's own
    // comment (referenceChains.h).
    static int canaryBackoffMult() {
        return ReferenceChainTracker::instance()->canaryBackoffMultForTest();
    }
    static u64 lastCanaryPassNs() {
        return ReferenceChainTracker::instance()->lastCanaryPassNsForTest();
    }
    static void setCanaryBackoffForTest(int mult, u64 ema_ms, u64 last_pass_ns) {
        ReferenceChainTracker::instance()->setCanaryBackoffForTest(mult, ema_ms,
                                                                   last_pass_ns);
    }
    static void setOomRampActive(bool active) {
        ReferenceChainTracker::instance()->setOomRampActiveForTest(active);
    }

    static int passesSinceLastCandidateProgress() {
        return ReferenceChainTracker::instance()->passesSinceLastCandidateProgressForTest();
    }

    static int canaryStuckRestartCount() {
        return ReferenceChainTracker::instance()->canaryStuckRestartCountForTest();
    }

    static u64 searchPainMs() {
        return ReferenceChainTracker::instance()->_search_pain_ms;
    }

    // Resolved-chain cache: read-only size peek and a pass-through to the
    // private snapshot (drainPendingChainEvents()) and insert
    // (cacheResolvedChain()), for ResolvedChainCacheTest below - same
    // rationale as hasResolvedChainForTag()/resolvedChainCount() below.
    static size_t resolvedChainCount() {
        return ReferenceChainTracker::instance()->_resolved_chains.size();
    }

    static void drain(std::vector<ReferenceChainEvent> *out) {
        ReferenceChainTracker::instance()->drainPendingChainEvents(out);
    }

    static void cacheChain(jlong source_tag, ReferenceChainEvent event,
                           jlong source_tag_val, u64 source_search_ns) {
        ReferenceChainTracker::instance()->cacheResolvedChain(
            source_tag, std::move(event), source_tag_val, source_search_ns);
    }

    static int maxResolvedChains() {
        return ReferenceChainTracker::MAX_RESOLVED_CHAINS;
    }

    // Target-selection bridging step: read-only peeks into the resolved-chain
    // cache, for asserting exactly which klass a chain was resolved for and
    // the tag it was reconstructed from - see PollWatchedTargetsTest below.
    static bool hasResolvedChainForTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_resolved_chains.find(tag) != t->_resolved_chains.end();
    }

    static jlong resolvedChainSourceTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_resolved_chains.find(tag);
        return it == t->_resolved_chains.end() ? 0 : it->second.source_tag;
    }

    // Leak-tag correlation (design C): read a frontier entry's stored leak
    // tag, and a pass-through to the private buildChainEvent(), for
    // LeakTagInterceptionTest below - same friend-accessor rationale as
    // hasResolvedChainForTag() above. Returns -1 when the tag is not in the
    // frontier table.
    static jlong frontierLeakTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        FrontierEntry entry{};
        if (t->_frontier == nullptr || !t->_frontier->lookup(tag, &entry)) {
            return -1;
        }
        return entry.leak_tag;
    }

    static void setCandidateKlassIdForTest(int idx, u32 klass_id) {
        ReferenceChainTracker::instance()->setCandidateKlassIdForTest(idx, klass_id);
    }

    static jlong candidateDiscoveredTagForTest(int slot, int idx) {
        return ReferenceChainTracker::instance()->candidateDiscoveredTagForTest(slot, idx);
    }

    static int candidateDiscoveredCountForTest(int slot) {
        return ReferenceChainTracker::instance()->candidateDiscoveredCountForTest(slot);
    }

    // recordDiscoveredInstance()/correlateAdmittedLeakTag() are the
    // production paths for the leak-correlation tests below.
    static void recordDiscoveredInstanceForTest(u32 klass_id, jlong tag,
                                                 bool leak_correlated) {
        ReferenceChainTracker::instance()->recordDiscoveredInstance(klass_id, tag,
                                                                   leak_correlated);
    }

    static size_t priorityExpandCap() {
        return ReferenceChainTracker::PRIORITY_EXPAND_CAP;
    }

    static int maxDiscoveredPerClass() {
        return ReferenceChainTracker::MAX_DISCOVERED_INSTANCES_PER_CLASS;
    }

    static bool buildChainEventForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                      jlong tag, ReferenceChainEvent *out) {
        return ReferenceChainTracker::instance()->buildChainEvent(jvmti, jni,
                                                                   tag, out);
    }

    // Direct expandFrontier() drive for the AIMD batch test: a full runPass()
    // drains a small graph to completion and its rotation phase adds extra
    // GetObjectsWithTags calls, so per-call AIMD assertions cannot be made
    // deterministic through runPass(). Seeding _pending_expand and calling
    // expandFrontier() directly runs exactly one batch (one AIMD update).
    static void pushPendingExpandForTest(jlong tag) {
        ReferenceChainTracker::instance()->_pending_expand.push_back(tag);
    }

    static void expandFrontierForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                      int *edges_admitted) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->expandFrontier(jvmti, jni, t->_hop_cap, 1000, edges_admitted,
                          &truncated, &cap_hit, &safepoint_ticks);
    }

    // Pause-time pacing controller: read-only peeks at the controller's
    // derived values, and
    // a pass-through to the private updatePacing() itself, for
    // ReferenceChainsPacingTest below - same rationale as
    // hasResolvedChainForTag()/resolvedChainCount() above (the target-selection bridging step): private state a test needs to drive/
    // observe directly, exposed via this existing friend accessor rather
    // than adding public getters/setters to ReferenceChainTracker itself.
    static int effectiveBudget() {
        return ReferenceChainTracker::instance()->_effective_budget;
    }

    static u64 effectiveCadenceNs() {
        return ReferenceChainTracker::instance()->_effective_cadence_ns;
    }

    static void updatePacing(u64 pass_wall_ns) {
        ReferenceChainTracker::instance()->updatePacing(pass_wall_ns);
    }

    static u64 baselineCadenceNs() { return ReferenceChainTracker::PASS_CADENCE_NS; }

    // Test-only seams for PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling
    // below, which needs to start from a controlled below-ceiling/above-
    // baseline point with a freshly reset controller (see that test's own
    // comment for why chaining directly off a prior constant-input sequence
    // would leave _pause_pid's integral state mid-recovery from that
    // sequence's windup, muddying this method's per-step direction
    // assertions with a transient the test is not about).
    static void setEffectiveBudget(int v) {
        ReferenceChainTracker::instance()->_effective_budget = v;
    }

    static void setEffectiveCadenceNs(u64 v) {
        ReferenceChainTracker::instance()->_effective_cadence_ns = v;
    }

    static void resetPacingController() {
        ReferenceChainTracker::instance()->_pause_pid.reset();
    }

    // Budget-borrowing (referenceChains.h's _borrowed_budget comment): the
    // configured multiplier PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling
    // below asserts convergence against, instead of hardcoding it a second
    // time in the test itself.
    static int borrowCeilingMultiplier() {
        return ReferenceChainTracker::BORROW_CEILING_MULTIPLIER;
    }

    static int64_t borrowedBudget() {
        return ReferenceChainTracker::instance()->_borrowed_budget;
    }

    // MaybeRevokeBorrowForRootEnumPass* tests below: drive the borrow state
    // directly into "already granted" before exercising the revocation-only
    // seam, and a pass-through to that seam itself - same rationale as
    // updatePacing()'s own accessor above.
    static void setBorrowedBudget(int64_t v) {
        ReferenceChainTracker::instance()->_borrowed_budget = v;
    }

    static int consecutiveUnderTargetPasses() {
        return ReferenceChainTracker::instance()->_consecutive_under_target_passes;
    }

    static void setConsecutiveUnderTargetPasses(int v) {
        ReferenceChainTracker::instance()->_consecutive_under_target_passes = v;
    }

    static void maybeRevokeBorrowForRootEnumPass(u64 pass_wall_ticks) {
        ReferenceChainTracker::instance()->maybeRevokeBorrowForRootEnumPass(
            pass_wall_ticks);
    }

    // ReleaseSearchTagsFailureTest below: read-only peek at whether the
    // tracker still owes a tag release before it can allow a restart - see
    // _tags_released's own comment.
    static bool tagsReleased() {
        return ReferenceChainTracker::instance()->_tags_released;
    }

    // ResolveLoadedClassesRescansAfterClassCountShrinksAndPartiallyRegrows
    // below: direct pass-through to the private resolveLoadedClasses(), plus
    // a read-only peek at the count it stashes - the same rationale as
    // tagsReleased() above (private state/behavior a test needs to
    // drive/observe directly, without going through a full runPass()/search
    // lifecycle that resolveLoadedClasses() alone does not need).
    static void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni) {
        ReferenceChainTracker::instance()->resolveLoadedClasses(jvmti, jni);
    }

    static int lastResolvedClassCount() {
        return ReferenceChainTracker::instance()->_last_resolved_class_count;
    }

    // Phase 5 (durability re-verification) test seams: direct pass-throughs
    // to the private tie-break/rotation methods, plus FrontierTable::insert()
    // itself (also private-by-convention here in the sense that production
    // code only ever calls it via admitObject()) so tests can set up a
    // frontier entry's exact starting root_kind/state/parent_tag without
    // needing a live JVMTI mock for IterateOverReachableObjects/FollowReferences
    // (neither is mocked in this file - see the file header's FollowReferences-
    // only mock rationale).
    static bool insertFrontierEntry(FrontierTable *frontier, jlong tag,
                                     jlong parent_tag, u32 depth, u8 state,
                                     u8 root_kind, u32 referrer_klass = 0,
                                     jlong class_tag = 0,
                                     jint referrer_field_index = -1,
                                     u8 edge_kind = 0,
                                     jlong referrer_class_tag = 0) {
        return frontier->insert(tag, parent_tag, referrer_klass, depth,
                                 state, root_kind, class_tag,
                                 referrer_field_index, edge_kind,
                                 referrer_class_tag);
    }

    static bool maybeUpgradeRootAttachedRootKind(FrontierTable *frontier,
                                                  jlong tag,
                                                  u8 new_root_kind) {
        return ReferenceChainTracker::instance()
            ->maybeUpgradeRootAttachedRootKind(frontier, tag, new_root_kind);
    }

    static std::vector<jlong> collectStaleRootKindEntriesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaleRootKindEntriesForRotation(max_count);
    }

    static std::vector<jlong> collectStaleExpandedEntriesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaleExpandedEntriesForRotation(max_count);
    }

    // Candidate-scoped reach (descendFromAnchor()/walkCandidateThreadLocals()/
    // walkStaticFieldAnchors()): direct drives for the same reason as
    // expandFrontierForTest() above - a full runPass() drains a small graph
    // to completion and its other phases add interference, so the walk
    // phases are exercised on their own.
    static void walkCandidateThreadLocalsForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                                 int budget,
                                                 int *edges_admitted) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->walkCandidateThreadLocals(jvmti, jni, budget, edges_admitted,
                                     &truncated, &cap_hit, &safepoint_ticks);
    }

    static void walkStaticFieldAnchorsForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                               const std::vector<jlong> &tags,
                                               int budget,
                                               int *edges_admitted) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->walkStaticFieldAnchors(jvmti, jni, tags, budget, edges_admitted,
                                  &truncated, &cap_hit, &safepoint_ticks);
    }

    static std::vector<jlong>
    collectStaticFieldAnchorsForRotationForTest(int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaticFieldAnchorsForRotation(max_count);
    }

    // Direct candidate-slot seeding (the production path fills these via
    // pollWatchedTargets()'s snapshot loop - see _candidate_qualifying_tids'
    // own comment): the walk phase tests need exactly one (slot, klass, tid)
    // combination without driving LivenessTracker's hysteresis machinery.
    static void seedCandidateSlotForTest(int slot, u32 klass_id,
                                          const jint *tids, int tid_count) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_candidate_klass_ids[slot] = klass_id;
        for (int i = 0; i < tid_count; i++) {
            t->_candidate_qualifying_tids[slot][i] = tids[i];
        }
        t->_candidate_qualifying_tid_count[slot] = tid_count;
        if (slot + 1 > t->_candidate_count) {
            t->_candidate_count = slot + 1;
        }
    }

    static int candidateQualifyingTidCountForTest(int slot) {
        return ReferenceChainTracker::instance()
            ->_candidate_qualifying_tid_count[slot];
    }

    static jlong getTagForTest(jvmtiEnv *jvmti, jobject obj) {
        return ReferenceChainTracker::instance()->getTag(jvmti, obj);
    }

    // Snapshot of _priority_expand's current contents, in queue order - used
    // by tests to check for duplicate tags after both rotation collectors
    // have run against it within the same simulated pass.
    static std::vector<jlong> priorityExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_priority_expand.begin(),
                                   t->_priority_expand.end());
    }

    // StaleExpandedRotationSkipsPreexistingQueueEntries below: simulates a
    // tag left in _priority_expand by a prior pass's truncated expandFrontier()
    // batch (expandFrontier()'s own "leave the batch at the front of the
    // source queue for a later pass to retry" comment) without driving a full
    // expandFrontier()/JVMTI round-trip to produce one.
    static void pushPriorityExpand(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_priority_expand.push_back(tag);
        t->_priority_expand_set.insert(tag);
    }

    // Simulates expandFrontier() having fully drained _priority_expand at the
    // end of a pass (the common case: rotation's whole selection fit within
    // that pass's rotation_budget slice) - see
    // StaleExpandedRotationStarvesHighTagEntryBehindLowTagPopulation below,
    // which needs this to model collectStaleExpandedEntriesForRotation()
    // being called fresh on each of several simulated passes, the way
    // runPassManualWalk() actually does it once per real pass.
    static void clearPriorityExpand() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_priority_expand.clear();
        t->_priority_expand_set.clear();
    }

    static void setRootKindRotationCursor(jlong tag) {
        ReferenceChainTracker::instance()->_root_kind_rotation_cursor = tag;
    }

    static jlong rootKindRotationCursor() {
        return ReferenceChainTracker::instance()->_root_kind_rotation_cursor;
    }

    static int rootKindRotationBudget() {
        return ReferenceChainTracker::ROOT_KIND_ROTATION_BUDGET;
    }

    static int staleExpandedRotationBudget() {
        return ReferenceChainTracker::STALE_EXPANDED_ROTATION_BUDGET;
    }

    static size_t priorityExpandSize() {
        return ReferenceChainTracker::instance()->_priority_expand.size();
    }

    // Snapshot of _pending_expand's current contents, in queue order - used
    // by the rolling-resume smoke test to verify that a truncated
    // expandFrontier() batch pops fully-processed entries (mark EXPANDED)
    // and leaves only the partially-processed and unvisited entries at the
    // front of the queue for the next pass to retry.
    static std::vector<jlong> pendingExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_pending_expand.begin(),
                                  t->_pending_expand.end());
    }

    static size_t pendingExpandSize() {
        return ReferenceChainTracker::instance()->_pending_expand.size();
    }

    // Self-calibrating adaptive batch size (AIMD): read/write the per-call
    // EMA and live batch size so tests can verify the AIMD dynamics.
    static u64 gotwEmaCallNs() {
        return ReferenceChainTracker::instance()->_gotw_ema_call_ns;
    }

    static void setGotwEmaCallNs(u64 v) {
        ReferenceChainTracker::instance()->_gotw_ema_call_ns = v;
    }

    static size_t gotwBatchSize() {
        return ReferenceChainTracker::instance()->_gotw_batch_size;
    }

    static void setGotwBatchSize(size_t v) {
        ReferenceChainTracker::instance()->_gotw_batch_size = v;
    }

    // Read-only peeks at the batch-control constants (private statics -
    // friendship applies inside this class's methods, not in test bodies).
    static u64 gotwCpuBudgetNs() {
        return ReferenceChainTracker::GOTW_CPU_BUDGET_NS;
    }

    static size_t gotwInitialBatchSize() {
        return (size_t)ReferenceChainTracker::GOTW_INITIAL_BATCH_SIZE;
    }

    static size_t gotwMinBatch() {
        return ReferenceChainTracker::GOTW_MIN_BATCH;
    }

    static size_t gotwMaxBatch() {
        return ReferenceChainTracker::GOTW_MAX_BATCH;
    }

    static size_t gotwBacklogMinDepth() {
        return ReferenceChainTracker::GOTW_BACKLOG_MIN_DEPTH;
    }

    static u64 gotwBacklogWindowMult() {
        return ReferenceChainTracker::GOTW_BACKLOG_WINDOW_MULT;
    }

    // gotwWindowNs() is a pure function of (remaining window, lane depth)
    // and the seeded EMA - directly unit-testable without a mock JVMTI call.
    static u64 gotwWindowNs(u64 remaining_ns, size_t lane_depth) {
        return ReferenceChainTracker::instance()->gotwWindowNs(remaining_ns,
                                                                lane_depth);
    }

    static void setPassDeadlineNs(u64 v) {
        ReferenceChainTracker::instance()->_pass_deadline_ns = v;
    }

    static bool expandLanePreferPriority() {
        return ReferenceChainTracker::instance()->_expand_lane_prefer_priority;
    }

    // Leak-tag pool range base (private static) - same friend-access
    // rationale as the AIMD constants above.
    static jlong leakTagBase() {
        return ReferenceChainTracker::LEAK_TAG_BASE;
    }

    // Leak-accumulation rotation test seams (collectLeakAccumulationCandidatesForRotation()).
    static void setWatchedLeakKlassIdsForTest(const std::vector<u32> &ids) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        int n = (int)std::min(ids.size(),
                               (size_t)ReferenceChainTracker::MAX_WATCHED_LEAK_KLASSES);
        for (int i = 0; i < n; i++) {
            t->_watched_leak_klass_ids[i] = ids[i];
        }
        t->_watched_leak_klass_count = n;
    }

    static void trackLeakAccumulation(FrontierTable *frontier, u32 referrer_klass,
                                       jlong parent_tag, jlong tag) {
        ReferenceChainTracker::instance()->trackLeakAccumulation(
            frontier, referrer_klass, parent_tag, tag);
    }

    static std::vector<jlong> collectLeakAccumulationCandidatesForRotation(
        int max_count) {
        return ReferenceChainTracker::instance()
            ->collectLeakAccumulationCandidatesForRotation(max_count);
    }

    static int leakAccumulationRotationBudget() {
        return ReferenceChainTracker::LEAK_ACCUMULATION_ROTATION_BUDGET;
    }

    static u32 leakSignatureTotal(u32 leaf_klass_id, u32 parent_class_id) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        u64 key = t->leakSignatureKey(leaf_klass_id, parent_class_id);
        auto it = t->_leak_signature_totals.find(key);
        return it != t->_leak_signature_totals.end() ? it->second : 0;
    }

    static u32 leakParentFanout(jlong parent_tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_leak_parent_fanout.find(parent_tag);
        return it != t->_leak_parent_fanout.end() ? it->second.fanout : 0;
    }

    static size_t leakSignatureCount() {
        return ReferenceChainTracker::instance()->_leak_signature_totals.size();
    }

    static void seedLeakAccumulationForNewlyWatchedKlass(u32 klass_id) {
        ReferenceChainTracker::instance()
            ->seedLeakAccumulationForNewlyWatchedKlass(klass_id);
    }
};

static jvmtiError JNICALL mock_SetEventNotificationMode(jvmtiEnv *, jvmtiEventMode,
                                                         jvmtiEvent, jthread, ...) {
    return JVMTI_ERROR_NONE;
}

class ReferenceChainsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_env{};
    jvmtiEnv *orig_jvmti = nullptr;

    void SetUp() override {
        orig_jvmti = VMTestAccessor::getJvmti();
        tbl = jvmtiInterface_1_{};
        tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        mock_env.functions = &tbl;
        VMTestAccessor::setJvmti(&mock_env);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
    }
};

TEST_F(ReferenceChainsTest, DefaultDisabled) {
    Arguments args;
    EXPECT_FALSE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesEnabled) {
    Arguments args;
    Error error = args.parse("referencechains=true");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesDisabled) {
    Arguments args;
    Error error = args.parse("referencechains=false");
    EXPECT_FALSE(error);
    EXPECT_FALSE(args._reference_chains);
}

TEST_F(ReferenceChainsTest, FlagParsesSubOptions) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=64:budget=2000:ttl=5000:framecap=128");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    EXPECT_EQ(64, args._reference_chains_hop_cap);
    EXPECT_EQ(2000, args._reference_chains_budget);
    EXPECT_EQ(5000, args._reference_chains_ttl_ms);
    EXPECT_EQ(128, args._reference_chains_frontier_cap);
}

// Negative/out-of-range sub-options must be floored/clamped at the parse
// boundary (Arguments::parse(), arguments.cpp) rather than stored verbatim -
// see that call site's own comment for why an unclamped negative hops in
// particular is dangerous: `depth >= (u32)ctx->hop_cap` (referenceChains.cpp)
// casts a negative int to u32, wrapping to ~4e9 and silently disabling the
// hop cap entirely.
TEST_F(ReferenceChainsTest, FlagClampsNegativeSubOptions) {
    Arguments args;
    Error error = args.parse(
        "referencechains=true:hops=-1:budget=-5:ttl=-1:framecap=-3:"
        "pausetarget=-1:painbudget=-10");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    // Floored to a sane minimum (1), not left negative - a negative value
    // cast to u32 downstream would otherwise wrap to a huge positive number.
    EXPECT_GT(args._reference_chains_hop_cap, 0);
    EXPECT_GT(args._reference_chains_budget, 0);
    EXPECT_GT(args._reference_chains_frontier_cap, 0);
    // ttl/pausetarget are floored at 0 (their own downstream gates already
    // treat 0 as "disabled", so 0 - not 1 - is the correct floor).
    EXPECT_GE(args._reference_chains_ttl_ms, 0);
    EXPECT_GE(args._reference_chains_pause_target_ms, 0);
    // painbudget is a percentage - clamped into [0, 100].
    EXPECT_GE(args._reference_chains_pain_budget_percent, 0);
    EXPECT_LE(args._reference_chains_pain_budget_percent, 100);
}

// A too-large painbudget must be clamped down to 100, not stored verbatim -
// the sibling of FlagClampsNegativeSubOptions above, for the upper bound
// rather than the lower one.
TEST_F(ReferenceChainsTest, FlagClampsOversizedPainBudgetPercent) {
    Arguments args;
    Error error = args.parse("referencechains=true:painbudget=250");
    EXPECT_FALSE(error);
    EXPECT_EQ(100, args._reference_chains_pain_budget_percent);
}

TEST_F(ReferenceChainsTest, FlagWithOtherArgsDoesNotClobberOuterParse) {
    Arguments args;
    Error error = args.parse("event=cpu,referencechains=true:hops=32,interval=1000000");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    EXPECT_EQ(32, args._reference_chains_hop_cap);
    EXPECT_STREQ("cpu", args._event);
    EXPECT_EQ(1000000, args._interval);
}

TEST_F(ReferenceChainsTest, StartStopDisabledDoesNotCrash) {
    Arguments args;
    Error error = args.parse("referencechains=false");
    ASSERT_FALSE(error);

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Error startError = tracker->start(args);
    EXPECT_FALSE(startError);
    EXPECT_FALSE(tracker->enabled());
    tracker->stop();
}

TEST_F(ReferenceChainsTest, StartStopEnabledDoesNotCrash) {
    Arguments args;
    Error error = args.parse("referencechains=true:hops=10:budget=100");
    ASSERT_FALSE(error);

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Error startError = tracker->start(args);
    EXPECT_FALSE(startError);
    EXPECT_TRUE(tracker->enabled());
    tracker->stop();
}

// ---------------------------------------------------------------------------
// GC signal (GarbageCollectionStart/Finish -> epoch counters).
//
// The callback trampolines (ReferenceChainTracker::GarbageCollectionStart/
// Finish) ignore the jvmtiEnv* argument entirely - onGCStart()/onGCFinish()
// only bump an atomic counter, per the JVMTI spec restriction documented in
// referenceChains.h - so passing nullptr here exercises the real production
// code path.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsTest, GCCallbacksIncrementEpochWhenEnabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    u64 startBefore = tracker->gcStartEpoch();
    u64 finishBefore = tracker->gcFinishEpoch();

    ReferenceChainTracker::GarbageCollectionStart(nullptr);
    ReferenceChainTracker::GarbageCollectionFinish(nullptr);

    EXPECT_EQ(startBefore + 1, tracker->gcStartEpoch());
    EXPECT_EQ(finishBefore + 1, tracker->gcFinishEpoch());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, GCCallbacksAreNoOpWhenDisabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=false"));

    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_FALSE(tracker->enabled());

    u64 startBefore = tracker->gcStartEpoch();
    u64 finishBefore = tracker->gcFinishEpoch();

    ReferenceChainTracker::GarbageCollectionStart(nullptr);
    ReferenceChainTracker::GarbageCollectionFinish(nullptr);

    EXPECT_EQ(startBefore, tracker->gcStartEpoch());
    EXPECT_EQ(finishBefore, tracker->gcFinishEpoch());
}

// ---------------------------------------------------------------------------
// Tag round-trip (SetTag/GetTag/clear).
//
// The implementation plan's suggested test ("allocate an object, tag it,
// force a GC, confirm the tag is still readable via GetObjectsWithTags")
// assumes a live embedded JVM. This gtest binary has no live JVM attached
// (see jvmSupport_ut.cpp's fixture comment for the same constraint on a
// different subsystem), so - following this repo's established pattern for
// testing JVMTI call sites without a real JVM (objectSampler_ut.cpp's mock
// jvmtiInterface_1_ table) - these tests exercise tagObject()/getTag()/
// clearTag() against a mock jvmtiEnv backed by an in-memory tag map, rather
// than a real GC. This proves the SetTag/GetTag/SetTag(obj,0) call sequence
// and unique-tag allocation are correct; it does not prove GC-move-
// transparency, which requires a real collector and is out of reach of this
// native-only gtest binary.
// ---------------------------------------------------------------------------

class ReferenceChainsTagTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ tbl{};
    _jvmtiEnv mock_env{};
    std::unordered_map<void *, jlong> tags;

    static ReferenceChainsTagTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        tbl = jvmtiInterface_1_{};
        tbl.SetTag = &mock_SetTag;
        tbl.GetTag = &mock_GetTag;
        mock_env.functions = &tbl;
    }

    void TearDown() override {
        active_fixture = nullptr;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        if (tag == 0) {
            active_fixture->tags.erase(object);
        } else {
            active_fixture->tags[object] = tag;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }
};

ReferenceChainsTagTest *ReferenceChainsTagTest::active_fixture = nullptr;

TEST_F(ReferenceChainsTagTest, TagRoundTripsThenClears) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);

    jlong tag = tracker->tagObject(&mock_env, obj);
    EXPECT_NE(0, tag);
    EXPECT_EQ(tag, tracker->getTag(&mock_env, obj));

    tracker->clearTag(&mock_env, obj);
    EXPECT_EQ(0, tracker->getTag(&mock_env, obj));
}

TEST_F(ReferenceChainsTagTest, TagsAreUniqueAndNeverZero) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int a = 0, b = 0;
    jlong tagA = tracker->tagObject(&mock_env, reinterpret_cast<jobject>(&a));
    jlong tagB = tracker->tagObject(&mock_env, reinterpret_cast<jobject>(&b));

    EXPECT_NE(0, tagA);
    EXPECT_NE(0, tagB);
    EXPECT_NE(tagA, tagB);
}

TEST_F(ReferenceChainsTagTest, UntaggedObjectReadsBackZero) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    int untagged = 0;
    EXPECT_EQ(0, tracker->getTag(&mock_env, reinterpret_cast<jobject>(&untagged)));
}

// ---------------------------------------------------------------------------
// FrontierTable (tag-indexed frontier metadata table).
//
// No live JVM/JVMTI involvement here - FrontierTable is pure native slot
// storage indexed by an already-issued tag value, so these tests exercise it
// directly rather than through ReferenceChainTracker's tag helpers.
// ---------------------------------------------------------------------------

TEST(FrontierTableTest, InsertThenLookupRoundTrips) {
    FrontierTable table(64);

    ASSERT_TRUE(table.insert(1, /*parent_tag=*/0, /*referrer_klass=*/7,
                             /*depth=*/0, FrontierEntryState::FRONTIER));

    FrontierEntry entry{};
    ASSERT_TRUE(table.lookup(1, &entry));
    EXPECT_EQ(0, entry.parent_tag);
    EXPECT_EQ(7u, entry.referrer_klass);
    EXPECT_EQ(0u, entry.depth);
    EXPECT_EQ(FrontierEntryState::FRONTIER, entry.state);
}

TEST(FrontierTableTest, LookupOfNeverInsertedTagFails) {
    FrontierTable table(64);
    FrontierEntry entry{};
    EXPECT_FALSE(table.lookup(1, &entry));
    EXPECT_FALSE(table.lookup(5, &entry));
}

TEST(FrontierTableTest, NonPositiveTagIsRejected) {
    FrontierTable table(64);
    FrontierEntry entry{};
    EXPECT_FALSE(table.insert(0, 0, 0, 0));
    EXPECT_FALSE(table.insert(-1, 0, 0, 0));
    EXPECT_FALSE(table.lookup(0, &entry));
    EXPECT_FALSE(table.lookup(-1, &entry));
}

TEST(FrontierTableTest, LookupLockedRejectsNonPositiveTag) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));
    FrontierEntry entry{};
    // tag=0 must be rejected the same way lookup() rejects it - callers
    // index the table with tag-1, so a `tag <= 0` check (not just `tag < 0`)
    // is required to keep that subtraction from wrapping into a valid slot.
    EXPECT_FALSE(table.lookupLocked(0, &entry));
    EXPECT_FALSE(table.lookupLocked(-1, &entry));
}

TEST(FrontierTableTest, LookupLockedRejectsTagPastCurrentSize) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));
    FrontierEntry entry{};
    // Only tag=1 has ever been inserted (table_size == 1); tag=2 maps to
    // idx=1, exactly at the current size boundary, and must be rejected
    // rather than read out of bounds.
    EXPECT_FALSE(table.lookupLocked(2, &entry));
}

TEST(FrontierTableTest, ParentTagChainReconstructsAcrossHops) {
    // Mirrors how the heap-walk engine walks parent_tag links back to a root: insert
    // a small chain root(tag=1) <- mid(tag=2) <- leaf(tag=3) and confirm the
    // links resolve in order.
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 100, 0, FrontierEntryState::EDGE));
    ASSERT_TRUE(table.insert(2, 1, 200, 1, FrontierEntryState::EDGE));
    ASSERT_TRUE(table.insert(3, 2, 300, 2, FrontierEntryState::EDGE));

    FrontierEntry entry{};
    jlong tag = 3;
    std::vector<u32> chain;
    while (tag != 0) {
        ASSERT_TRUE(table.lookup(tag, &entry));
        chain.push_back(entry.referrer_klass);
        tag = entry.parent_tag;
    }

    ASSERT_EQ(3u, chain.size());
    EXPECT_EQ(300u, chain[0]);
    EXPECT_EQ(200u, chain[1]);
    EXPECT_EQ(100u, chain[2]);
}

TEST(FrontierTableTest, ClearMarksAbandonedWithoutRemovingEntry) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));

    table.clear(1);

    FrontierEntry entry{};
    ASSERT_TRUE(table.lookup(1, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);
}

TEST(FrontierTableTest, ClearOfNeverInsertedTagIsNoOp) {
    FrontierTable table(64);
    table.clear(1); // must not crash
    FrontierEntry entry{};
    EXPECT_FALSE(table.lookup(1, &entry));
}

TEST(FrontierTableTest, GrowsPastInitialCapacityUpToMaxCap) {
    // Force at least one resize by inserting beyond the small max_cap.
    const int max_cap = 10;
    FrontierTable table(max_cap);
    ASSERT_LE(table.capacity(), max_cap);

    for (jlong tag = 1; tag <= max_cap; tag++) {
        ASSERT_TRUE(table.insert(tag, tag - 1, (u32)tag, (u32)(tag - 1)))
            << "insert failed for tag " << tag;
    }
    EXPECT_EQ(max_cap, table.capacity());

    for (jlong tag = 1; tag <= max_cap; tag++) {
        FrontierEntry entry{};
        ASSERT_TRUE(table.lookup(tag, &entry));
        EXPECT_EQ((u32)tag, entry.referrer_klass);
    }
}

TEST(FrontierTableTest, CapacityExhaustedReportsFailureInsteadOfCrashing) {
    const int max_cap = 4;
    FrontierTable table(max_cap);

    for (jlong tag = 1; tag <= max_cap; tag++) {
        ASSERT_TRUE(table.insert(tag, 0, 0, 0));
    }
    // One past max_cap must be rejected, not silently dropped-but-crashing.
    EXPECT_FALSE(table.insert(max_cap + 1, 0, 0, 0));
    EXPECT_EQ(max_cap, table.capacity());

    // Existing entries remain intact after the failed insert.
    FrontierEntry entry{};
    EXPECT_TRUE(table.lookup(1, &entry));
}

TEST(FrontierTableTest, ZeroMaxCapRejectsEveryInsert) {
    FrontierTable table(0);
    EXPECT_EQ(0, table.capacity());
    EXPECT_FALSE(table.insert(1, 0, 0, 0));
}

TEST(FrontierTableTest, ConcurrentInsertWhileGrowingDoesNotCrash) {
    // Small max_cap relative to thread/tag count forces repeated resizes
    // while other threads are concurrently inserting distinct tags.
    const int max_cap = 4096;
    const int thread_count = 8;
    const int tags_per_thread = 256;
    FrontierTable table(max_cap);

    std::vector<std::thread> threads;
    for (int t = 0; t < thread_count; t++) {
        threads.emplace_back([&table, t, tags_per_thread]() {
            for (int i = 0; i < tags_per_thread; i++) {
                jlong tag = (jlong)t * tags_per_thread + i + 1;
                table.insert(tag, 0, (u32)tag, 0);
            }
        });
    }
    for (auto &th : threads) {
        th.join();
    }

    int found = 0;
    for (jlong tag = 1; tag <= (jlong)thread_count * tags_per_thread; tag++) {
        FrontierEntry entry{};
        if (table.lookup(tag, &entry)) {
            EXPECT_EQ((u32)tag, entry.referrer_klass);
            found++;
        }
    }
    // Every tag fits well within max_cap, so all inserts must have
    // succeeded and be independently readable.
    EXPECT_EQ(thread_count * tags_per_thread, found);
}

TEST(FrontierTableTest, ReconstructChainWalksParentTagsAndMarksEdge) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 100, 0, FrontierEntryState::FRONTIER));
    ASSERT_TRUE(table.insert(2, 1, 200, 1, FrontierEntryState::FRONTIER));
    ASSERT_TRUE(table.insert(3, 2, 300, 2, FrontierEntryState::FRONTIER));

    std::vector<u32> chain;
    ASSERT_TRUE(table.reconstructChain(3, &chain));
    ASSERT_EQ(3u, chain.size());
    EXPECT_EQ(300u, chain[0]);
    EXPECT_EQ(200u, chain[1]);
    EXPECT_EQ(100u, chain[2]);

    // Every hop walked must be marked EDGE - this table's degenerate
    // EdgeStore (design doc: "on a path toward a target sample").
    for (jlong tag = 1; tag <= 3; tag++) {
        FrontierEntry entry{};
        ASSERT_TRUE(table.lookup(tag, &entry));
        EXPECT_EQ(FrontierEntryState::EDGE, entry.state);
    }
}

TEST(FrontierTableTest, ReconstructChainOfNeverInsertedTagFails) {
    FrontierTable table(64);
    std::vector<u32> chain;
    EXPECT_FALSE(table.reconstructChain(1, &chain));
}

// ---------------------------------------------------------------------------
// Heap-walk engine (ReferenceChainTracker::runPass()/
// heapReferenceCallback()/resolveLoadedClasses()).
//
// The implementation plan suggests testing this against "a small live-object
// graph in a test JVM (via JNI from the test)". This native-only gtest
// binary has no live JVM at all (see this file's GC-signal/tag-round-trip
// comment above, and jvmSupport_ut.cpp's fixture comment, for the same
// pre-existing constraint) - no gtest binary in this codebase embeds a
// JNI_CreateJavaVM-created JVM. So, exactly like ReferenceChainsTagTest above
// mocks SetTag/GetTag with an in-memory map, these tests mock the JVMTI/JNI
// call boundary (FollowReferences/GetLoadedClasses/GetClassSignature/
// DeleteLocalRef) to play back a scripted synthetic object graph, and run
// the *real* production heapReferenceCallback()/resolveLoadedClasses()/
// reconstructChain() code against it - only the JVMTI/JNI calls are faked,
// not the logic under test. A live-JVM end-to-end test belongs to a
// Java-side integration test (see ReferenceChainTrackingTest.java), not this
// native gtest binary.
// ---------------------------------------------------------------------------

namespace {

struct ScriptedEdge {
    jvmtiHeapReferenceKind kind;
    int referrer_idx; // -1 = heap root (no referrer)
    int referee_idx;  // index into ReferenceChainsBfsTest::node_tags
    int class_idx;    // index into ReferenceChainsBfsTest::classes, or -1
};

struct ScriptedClass {
    void *klass;
    const char *signature; // JVMTI class signature, e.g. "Lcom/example/Foo;"
};

// Retention-edge label decode fixtures (ReferenceChainsBfsTest's
// field_decode_hierarchy + the hierarchy-introspection mock slots): a fake
// class hierarchy the slots read, mirroring just enough JVMTI class shape
// for the spec-ordinal decoder (own-declared fields in GetClassFields
// order, direct superclass, directly implemented/extended interfaces).
struct FakeField {
    void *id;       // fake jfieldID
    const char *name;
};
struct FakeClass {
    bool is_interface;
    void *super;                     // fake jclass, or nullptr
    std::vector<void *> interfaces;  // directly implemented/extended
    std::vector<FakeField> fields;   // own-declared, GetClassFields order
};

} // namespace

class ReferenceChainsBfsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};

    std::unordered_map<void *, jlong> tags;
    std::vector<ScriptedClass> classes;
    std::vector<ScriptedEdge> script;
    std::vector<jlong> node_tags;

    // node_tags[idx] mirrors "the object's *current* live JVMTI
    // tag" (0 once releaseSearchTags() clears it, exactly like a real
    // GetTag() would report after SetTag(obj, 0)). tags_ever_assigned[idx]
    // instead remembers the tag heapReferenceCallback() ever wrote through
    // tag_ptr for this node, and is never reset - a production consumer
    // would capture a target sample's tag the same way (at assignment time,
    // e.g. via its own sample-tracking), not by re-reading GetTag() after
    // the search has already released it. Tests use this to fetch a tag for
    // reconstructChain() without depending on whether the search released
    // it before or after the test could observe node_tags[idx].
    std::vector<jlong> tags_ever_assigned;

    // Tags that GetObjectsWithTags() below reports as unresolvable,
    // simulating the referenced object having died (GC'd) between passes -
    // see the resolve-or-drop tests.
    std::unordered_set<jlong> dead_tags;

    // When true, mock_GetObjectsWithTags() below fails outright (as if the
    // real JVMTI call had hit e.g. JVMTI_ERROR_OUT_OF_MEMORY), for
    // ReleaseSearchTagsFailureTest - simulates releaseSearchTags()'s own
    // GetObjectsWithTags() call failing rather than an individual tag
    // failing to resolve (dead_tags above).
    bool fail_get_objects_with_tags = false;

    // When non-zero, mock_GetObjectsWithTags() below busy-waits this many
    // nanoseconds. The mock call is otherwise ~free, so a pass deadline set
    // to a fraction of this value bounds an expandFrontier() invocation to
    // exactly ONE batch - the production regime (one real ~25-30ms call of
    // a 50ms window), needed by the lane-alternation test.
    u64 gotw_delay_ns = 0;

    // Synthetic frontier-holder arrays for expandFrontier()'s array-holder
    // walk: mock_NewObjectArray() hands back an opaque handle,
    // mock_SetObjectArrayElement() records its elements here, and
    // mock_FollowReferences() treats every recorded element as an expansion
    // seed (one hop, gated by the production callback's batch_tags) when the
    // holder is passed as initial_object.
    std::unordered_map<jobject, std::vector<jobject>> holders;
    uintptr_t next_holder = 0xF00D0000;

    // FindClass(name) -> registered fake class (see mock_FindClass' own
    // comment): names descendFromAnchor()'s resolutions look up
    // ("java/lang/ClassLoader", "java/lang/ThreadGroup",
    // "java/security/ProtectionDomain",
    // "java/lang/ThreadLocal$ThreadLocalMap", "java/lang/Thread").
    std::unordered_map<std::string, void *> find_classes;
    // Fake class returned by mock_GetObjectClass() for unregistered objects
    // (walkCandidateThreadLocals()'s fresh-anchor admission path).
    void *thread_class = nullptr;

    jvmtiEnv *orig_jvmti = nullptr;

    static ReferenceChainsBfsTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        // See ReferenceChainsTestAccessor's own comment - without this, a
        // prior test in this suite that drove the search to
        // SearchState::COMPLETED/ABANDONED would make every runPass() call
        // below a permanent no-op.
        ReferenceChainsTestAccessor::reset();
        jvmti_tbl = jvmtiInterface_1_{};
        // start() calls VM::jvmti()->SetEventNotificationMode() -
        // stub it and swap VM::_jvmti (VMTestAccessor, declared above) the
        // same way ReferenceChainsTest's fixture does, so start() does not
        // dereference the real (null, no live JVM) jvmtiEnv.
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.SetTag = &mock_SetTag;
        jvmti_tbl.GetTag = &mock_GetTag;
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses;
        jvmti_tbl.GetClassLoader = &mock_GetClassLoader;
        jvmti_tbl.GetClassSignature = &mock_GetClassSignature;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        jvmti_tbl.FollowReferences = &mock_FollowReferences;
        jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
        jvmti_tbl.GetObjectsWithTags = &mock_GetObjectsWithTags;
        // Retention-edge label decode path (hopLabelClassFor()).
        jvmti_tbl.IsInterface = &mock_IsInterface;
        jvmti_tbl.GetImplementedInterfaces = &mock_GetImplementedInterfaces;
        jvmti_tbl.GetClassFields = &mock_GetClassFields;
        jvmti_tbl.GetFieldName = &mock_GetFieldName;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
        jni_tbl.FindClass = &mock_FindClass;
        jni_tbl.GetObjectClass = &mock_GetObjectClass;
        jni_tbl.GetSuperclass = &mock_JniGetSuperclass;
        jni_tbl.NewGlobalRef = &mock_NewGlobalRef;
        jni_tbl.EnsureLocalCapacity = &mock_EnsureLocalCapacity;
        jni_tbl.NewObjectArray = &mock_NewObjectArray;
        jni_tbl.SetObjectArrayElement = &mock_SetObjectArrayElement;
        jni_tbl.ExceptionCheck = &mock_ExceptionCheck;
        jni_tbl.ExceptionClear = &mock_ExceptionClear;
        mock_jni.functions = &jni_tbl;
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        active_fixture = nullptr;
    }

    // Registers a fake class (matched by identity, not by any real JNI
    // semantics) that resolveLoadedClasses() will discover via the mocked
    // GetLoadedClasses(). Returns its index into `classes`.
    int addClass(void *klass, const char *signature) {
        classes.push_back({klass, signature});
        return (int)classes.size() - 1;
    }

    // addClass() + a mock_FindClass(name) registry entry in one step, for
    // the classes descendFromAnchor()'s resolution helpers look up by
    // name (see find_classes' own comment). `name` uses FindClass's
    // binary-name form ("java/lang/ClassLoader"), `signature` the
    // class-signature form resolveLoadedClasses() interns
    // ("Ljava/lang/ClassLoader;") - the production code passes each to
    // exactly one of the two APIs.
    int registerClassForFindClass(void *klass, const char *name,
                                   const char *signature) {
        int idx = addClass(klass, signature);
        find_classes[name] = klass;
        return idx;
    }

    // Adds an as-yet-untagged frontier node, returning its index into
    // node_tags for use as a ScriptedEdge referrer_idx/referee_idx.
    int addNode() {
        node_tags.push_back(0);
        tags_ever_assigned.push_back(0);
        return (int)node_tags.size() - 1;
    }

    // Reverse lookup from a node's synthetic identity
    // (&node_tags[idx], see mock_FollowReferences' initial_object handling
    // below) back to its index. Returns -1 for anything else (e.g. a
    // ScriptedClass's `klass` pointer, which never aliases node_tags'
    // backing storage). Requires every addNode() call to happen before any
    // runPass() call in a test, so node_tags never reallocates out from
    // under a previously-taken address - true of every test in this file.
    int indexOfNode(jobject obj) const {
        for (size_t i = 0; i < node_tags.size(); i++) {
            if (obj == (jobject)&node_tags[i]) {
                return (int)i;
            }
        }
        return -1;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        // releaseSearchTags() calls SetTag(obj, 0) on the resolved
        // objects GetObjectsWithTags() (below) hands back for a frontier
        // node - route that through node_tags[idx] directly (the same
        // storage GetObjectsWithTags's resolution and the production
        // callback's tag_ptr writes both key off of), so the release is
        // actually observable, not just recorded in a side map nothing else
        // reads.
        int idx = active_fixture->indexOfNode(object);
        if (idx >= 0) {
            active_fixture->node_tags[idx] = tag;
            return JVMTI_ERROR_NONE;
        }
        if (tag == 0) {
            active_fixture->tags.erase(object);
        } else {
            active_fixture->tags[object] = tag;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        int idx = active_fixture->indexOfNode(object);
        if (idx >= 0) {
            *tag_ptr = active_fixture->node_tags[idx];
            return JVMTI_ERROR_NONE;
        }
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count_ptr,
                                                     jclass **classes_ptr) {
        auto &classes = active_fixture->classes;
        *count_ptr = (jint)classes.size();
        *classes_ptr = classes.empty()
                ? nullptr
                : (jclass *)malloc(sizeof(jclass) * classes.size());
        for (size_t i = 0; i < classes.size(); i++) {
            (*classes_ptr)[i] = (jclass)classes[i].klass;
        }
        return JVMTI_ERROR_NONE;
    }

    // admitStaticFieldRoots()'s app-classes-first partition (referenceChains.cpp)
    // calls this for every loaded class. Every fixture class is "bootstrap"
    // (null classloader) so the partition is a no-op and this suite's
    // scripted class order/indices stay exactly as each test set them up.
    static jvmtiError JNICALL mock_GetClassLoader(jvmtiEnv *, jclass,
                                                   jobject *classloader_ptr) {
        *classloader_ptr = nullptr;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_GetClassSignature(jvmtiEnv *, jclass klass,
                                                       char **signature_ptr,
                                                       char **generic_ptr) {
        for (auto &c : active_fixture->classes) {
            if (c.klass == (void *)klass) {
                *signature_ptr = strdup(c.signature);
                if (generic_ptr != nullptr) {
                    *generic_ptr = nullptr;
                }
                return JVMTI_ERROR_NONE;
            }
        }
        return JVMTI_ERROR_INVALID_CLASS;
    }

    static jvmtiError JNICALL mock_Deallocate(jvmtiEnv *, unsigned char *mem) {
        free(mem);
        return JVMTI_ERROR_NONE;
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject/jclass values are not real JNI
        // local refs.
    }

    // Retention-edge label decode fixtures (fillHopEdgeLabels()/
    // hopLabelClassFor()): a fake class hierarchy the hierarchy-introspection
    // slots below read, plus a tag -> fake jclass map (the decoder resolves
    // the referrer class from its raw tag via GetObjectsWithTags - the test
    // populates field_decode_classes from resolveLoadedClasses()-minted
    // tags, and mock_GetObjectsWithTags consults it first).
    std::unordered_map<jlong, void *> field_decode_classes;
    std::unordered_map<void *, FakeClass> field_decode_hierarchy;

    // The hierarchy-introspection slots the decoder needs (IsInterface/
    // GetImplementedInterfaces/GetClassFields/GetFieldName on the JVMTI
    // table, GetSuperclass on the JNI table - modern JVMTI dropped its own
    // GetSuperclass). All lookups go through field_decode_hierarchy; an
    // unregistered class returns a failure code so the decoder marks the
    // class undecodable and degrades to kind labels - the exact production
    // fail-safe shape.
    static jvmtiError JNICALL mock_IsInterface(jvmtiEnv *, jclass cls,
                                               jboolean *is_interface_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        *is_interface_ptr = it->second.is_interface ? JNI_TRUE : JNI_FALSE;
        return JVMTI_ERROR_NONE;
    }
    static jclass JNICALL mock_JniGetSuperclass(JNIEnv *, jclass cls) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        return it == active_fixture->field_decode_hierarchy.end()
                       ? nullptr
                       : (jclass)it->second.super;
    }
    static jvmtiError JNICALL mock_GetImplementedInterfaces(
            jvmtiEnv *, jclass cls, jint *count_ptr, jclass **ifaces_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        const std::vector<void *> &ifaces = it->second.interfaces;
        *count_ptr = (jint)ifaces.size();
        *ifaces_ptr = ifaces.empty()
                ? nullptr
                : (jclass *)malloc(sizeof(jclass) * ifaces.size());
        for (size_t i = 0; i < ifaces.size(); i++) {
            (*ifaces_ptr)[i] = (jclass)ifaces[i];
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL mock_GetClassFields(
            jvmtiEnv *, jclass cls, jint *count_ptr, jfieldID **fields_ptr) {
        auto it = active_fixture->field_decode_hierarchy.find(cls);
        if (it == active_fixture->field_decode_hierarchy.end()) {
            return JVMTI_ERROR_INVALID_CLASS;
        }
        const std::vector<FakeField> &fields = it->second.fields;
        *count_ptr = (jint)fields.size();
        *fields_ptr = fields.empty()
                ? nullptr
                : (jfieldID *)malloc(sizeof(jfieldID) * fields.size());
        for (size_t i = 0; i < fields.size(); i++) {
            (*fields_ptr)[i] = (jfieldID)fields[i].id;
        }
        return JVMTI_ERROR_NONE;
    }
    static jvmtiError JNICALL mock_GetFieldName(
            jvmtiEnv *, jclass, jfieldID field, char **name_ptr,
            char ** /*signature_ptr*/, char ** /*generic_ptr*/) {
        for (const auto &kv : active_fixture->field_decode_hierarchy) {
            for (const FakeField &f : kv.second.fields) {
                if (f.id == (void *)field) {
                    size_t len = strlen(f.name) + 1;
                    char *name = (char *)malloc(len);
                    memcpy(name, f.name, len);
                    *name_ptr = name;
                    return JVMTI_ERROR_NONE;
                }
            }
        }
        return JVMTI_ERROR_INVALID_FIELDID;
    }

    // expandFrontier()/admitStaticFieldRoots() resolve java/lang/Object once
    // as the holder array's element type - a non-null fake jclass is all it
    // needs (the type is never introspected, only passed to NewObjectArray()).
    // descendFromAnchor()'s class resolution (resolveNoDescendClassTags()/
    // resolveThreadLocalMapClassTag()) additionally needs NAME lookup - the
    // find_classes registry maps a FindClass name to a class registered via
    // addClass() so those resolutions see the same tagged fake class the
    // scripted graph uses.
    static jclass JNICALL mock_FindClass(JNIEnv *, const char *name) {
        auto it = active_fixture->find_classes.find(name);
        if (it != active_fixture->find_classes.end()) {
            return (jclass)it->second;
        }
        return (jclass)0xC1A55;
    }

    // walkCandidateThreadLocals()'s fresh-anchor admission calls
    // GetObjectClass(thread) - unregistered classes return the fixture's
    // fake Thread class (set_thread_class) so the anchor entry's class tag
    // resolves through the same mocked GetTag/tagging path.
    static jclass JNICALL mock_GetObjectClass(JNIEnv *, jobject) {
        return (jclass)active_fixture->thread_class;
    }


    // The production code wraps that fake jclass in a global ref (a real
    // local ref would dangle across JNI-entered test seams - see
    // _cached_object_class's own comment). This fixture's "refs" are raw
    // fake pointers with no JNI lifetime, so identity is the correct mock.
    static jobject JNICALL mock_NewGlobalRef(JNIEnv *, jobject obj) {
        return obj;
    }

    static jint JNICALL mock_EnsureLocalCapacity(JNIEnv *, jint) {
        return JNI_OK;
    }

    // expandFrontier() calls jniExceptionCheck() after every upcall that can
    // legally throw (NewObjectArray/SetObjectArrayElement/EnsureLocalCapacity
    // failures) - this fixture's mocks never throw, so there is never a
    // pending exception to report or clear.
    static jboolean JNICALL mock_ExceptionCheck(JNIEnv *) {
        return JNI_FALSE;
    }

    static void JNICALL mock_ExceptionClear(JNIEnv *) {
        // no-op: mock_ExceptionCheck() never reports a pending exception.
    }

    // Hands back a fresh opaque holder handle and registers it in `holders` so
    // mock_SetObjectArrayElement()/mock_FollowReferences() can find its
    // elements. `length`/`elementClass`/`initialElement` are unused - the
    // fixture never reads the array back, only its recorded element list.
    static jobjectArray JNICALL mock_NewObjectArray(JNIEnv *, jsize, jclass,
                                                     jobject) {
        jobject handle = (jobject)(active_fixture->next_holder++);
        active_fixture->holders[handle] = {};
        return (jobjectArray)handle;
    }

    static void JNICALL mock_SetObjectArrayElement(JNIEnv *, jobjectArray array,
                                                    jsize, jobject value) {
        active_fixture->holders[(jobject)array].push_back(value);
    }

    // runPassManualWalk()'s root enumeration (the default, non-fallback path):
    // reports each scripted root edge's referee to heapRootCallback() exactly
    // as a real IterateOverReachableObjects() reports a root-held object -
    // tag_ptr only, no oop, no transitive children (see runPassManualWalk()'s
    // own comment). Expansion past the roots is then driven by expandFrontier()
    // through the same mock_FollowReferences() array-holder path the resumed
    // fallback passes use. stack_ref/object_ref callbacks are unused here - a
    // JNI-global root (durable) is all these tests need to model.
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
            jvmtiEnv *, jvmtiHeapRootCallback heap_root_cb,
            jvmtiStackReferenceCallback, jvmtiObjectReferenceCallback,
            const void *user_data) {
        for (auto &e : active_fixture->script) {
            if (e.referrer_idx != -1) {
                continue;
            }
            jlong class_tag = 0;
            if (e.class_idx >= 0) {
                class_tag = active_fixture->tags[active_fixture->classes[e.class_idx].klass];
            }
            jlong *tag_ptr = &active_fixture->node_tags[e.referee_idx];
            jvmtiIterationControl ctl = heap_root_cb(
                    JVMTI_HEAP_ROOT_JNI_GLOBAL, class_tag, /*size=*/0, tag_ptr,
                    const_cast<void *>(user_data));
            if (*tag_ptr != 0) {
                active_fixture->tags_ever_assigned[e.referee_idx] = *tag_ptr;
            }
            if (ctl == JVMTI_ITERATION_ABORT) {
                break;
            }
        }
        return JVMTI_ERROR_NONE;
    }

    // Resolves each requested tag to its node's synthetic identity
    // (&node_tags[idx]) by scanning node_tags for a matching current value -
    // mirroring real GetObjectsWithTags()'s "only currently-live tags come
    // back" contract. A tag in `dead_tags` is deliberately omitted even if
    // node_tags still holds it, simulating "the object died, JVMTI forgot
    // the tag with it" for the resolve-or-drop tests.
    static jvmtiError JNICALL mock_GetObjectsWithTags(
            jvmtiEnv *, jint tag_count, const jlong *req_tags, jint *count_ptr,
            jobject **object_result_ptr, jlong **tag_result_ptr) {
        if (active_fixture->fail_get_objects_with_tags) {
            // Deliberately leave *count_ptr/*object_result_ptr/*tag_result_ptr
            // untouched - a real failed JVMTI call makes no promise about
            // them, and releaseSearchTags() must not read them on this path.
            return JVMTI_ERROR_OUT_OF_MEMORY;
        }
        if (active_fixture->gotw_delay_ns != 0) {
            u64 until = OS::nanotime() + active_fixture->gotw_delay_ns;
            while (OS::nanotime() < until) {
                // busy-wait: a sleep could overshoot by scheduler latency,
                // and the overshoot direction matters for the one-batch
                // deadline arithmetic the callers of this knob rely on.
            }
        }
        std::vector<jobject> objs;
        std::vector<jlong> found;
        for (jint i = 0; i < tag_count; i++) {
            jlong want = req_tags[i];
            if (want == 0 || active_fixture->dead_tags.count(want) > 0) {
                continue;
            }
            // The decoder resolves a referrer CLASS from its raw (negative)
            // tag - no node carries one, so the tag -> fake jclass map
            // (field_decode_classes, see its own comment) serves it.
            auto fd = active_fixture->field_decode_classes.find(want);
            if (fd != active_fixture->field_decode_classes.end()) {
                objs.push_back((jobject)fd->second);
                found.push_back(want);
                break;
            }
            for (size_t idx = 0; idx < active_fixture->node_tags.size(); idx++) {
                if (active_fixture->node_tags[idx] == want) {
                    objs.push_back((jobject)&active_fixture->node_tags[idx]);
                    found.push_back(want);
                    break;
                }
            }
        }
        *count_ptr = (jint)objs.size();
        *object_result_ptr = objs.empty()
                ? nullptr : (jobject *)malloc(sizeof(jobject) * objs.size());
        *tag_result_ptr = found.empty()
                ? nullptr : (jlong *)malloc(sizeof(jlong) * found.size());
        for (size_t i = 0; i < objs.size(); i++) {
            (*object_result_ptr)[i] = objs[i];
            (*tag_result_ptr)[i] = found[i];
        }
        return JVMTI_ERROR_NONE;
    }

    // Plays back `script` against the real production heap_reference_callback,
    // modelling enough of FollowReferences' actual semantics for these
    // heap-walk tests to be meaningful:
    //   - "a reference from A to B is not traversed until A is visited" -
    //     an edge whose referrer was not returned JVMTI_VISIT_OBJECTS for
    //     (or was never itself visited) is skipped, exactly as a real
    //     traversal would never reach it.
    //   - a JVMTI_VISIT_ABORT return stops delivery immediately.
    //   - when `initial_object` is non-NULL (expandFrontier()'s
    //     resumed-pass calls), only edges reachable from that object's own
    //     node are replayed - root edges (referrer_idx == -1) are skipped
    //     entirely, matching FollowReferences' real "the specified object is
    //     used instead of the heap roots" contract. `initial_object == NULL`
    //     (the first-pass, root-seeded call) is unchanged from the original
    //     single-pass heap-walk engine.
    // This is not a full JVMTI implementation (real traversal order,
    // multi-referrer objects, and primitive/array callbacks are all out of
    // scope) - just enough fidelity to exercise the hop-cap/budget/
    // frontier-cap/class-skip/resumption logic in heapReferenceCallback()/
    // expandFrontier() themselves.
    static jvmtiError JNICALL mock_FollowReferences(
            jvmtiEnv *, jint, jclass, jobject initial_object,
            const jvmtiHeapCallbacks *callbacks, const void *user_data) {
        std::unordered_map<int, bool> expandable;
        // seed_idx == -2 marks the root walk (initial_object == NULL); any
        // other value marks an expansion walk seeded from one or more boundary
        // objects, in which case root edges are never replayed. -1 is the
        // array-holder walk (a whole BFS level's boundary objects at once);
        // >= 0 is the single-object legacy per-entry walk.
        int seed_idx = -2;
        // The transient holder array itself is never tagged (mirrors real
        // production: admitStaticFieldRoots()/expandFrontier() never call
        // SetTag on the frontier-holder array they build), so every
        // holder->element ARRAY_ELEMENT edge below is replayed with a
        // referrer tag of 0.
        static jlong holder_tag = 0;
        if (initial_object != nullptr) {
            auto holder_it = active_fixture->holders.find(initial_object);
            if (holder_it != active_fixture->holders.end()) {
                // Array-holder walk (expandFrontier()'s already-tagged
                // boundary batch, or admitStaticFieldRoots()'s negative-
                // tagged class-object seed): actually invoke the production
                // callback for each holder->element edge, exactly like a
                // real FollowReferences(initial_object=holder_array) call
                // would - this is what lets heap_reference_callback()'s own
                // tag-sign/reference_kind logic (e.g. the *tag_ptr < 0
                // early-return and its admitStaticFieldRoots() carve-out)
                // actually run, rather than assuming every element is
                // expandable.
                seed_idx = -1;
                for (jobject elem : holder_it->second) {
                    int idx = active_fixture->indexOfNode(elem);
                    if (idx < 0) {
                        continue;
                    }
                    jlong *tag_ptr = &active_fixture->node_tags[idx];
                    jint ctl = callbacks->heap_reference_callback(
                            JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, nullptr,
                            /*class_tag=*/0, /*referrer_class_tag=*/0,
                            /*size=*/0, tag_ptr, &holder_tag,
                            /*length=*/-1, const_cast<void *>(user_data));
                    if (*tag_ptr != 0) {
                        active_fixture->tags_ever_assigned[idx] = *tag_ptr;
                    }
                    if (ctl & JVMTI_VISIT_ABORT) {
                        return JVMTI_ERROR_NONE;
                    }
                    expandable[idx] = (ctl & JVMTI_VISIT_OBJECTS) != 0;
                }
            } else {
                seed_idx = active_fixture->indexOfNode(initial_object);
                expandable[seed_idx] = true;
            }
        }
        for (auto &e : active_fixture->script) {
            if (e.referrer_idx == -1) {
                if (seed_idx != -2) {
                    continue; // resumed pass: never replay root edges
                }
            } else {
                auto it = expandable.find(e.referrer_idx);
                if (it == expandable.end() || !it->second) {
                    continue;
                }
            }
            jlong class_tag = 0;
            if (e.class_idx >= 0) {
                class_tag = active_fixture->tags[active_fixture->classes[e.class_idx].klass];
            }
            jlong *referrer_tag_ptr = e.referrer_idx >= 0
                    ? &active_fixture->node_tags[e.referrer_idx] : nullptr;
            jlong *tag_ptr = &active_fixture->node_tags[e.referee_idx];
            jint ctl = callbacks->heap_reference_callback(
                    e.kind, nullptr, class_tag, /*referrer_class_tag=*/0,
                    /*size=*/0, tag_ptr, referrer_tag_ptr, /*length=*/-1,
                    const_cast<void *>(user_data));
            if (*tag_ptr != 0) {
                active_fixture->tags_ever_assigned[e.referee_idx] = *tag_ptr;
            }
            if (ctl & JVMTI_VISIT_ABORT) {
                return JVMTI_ERROR_NONE;
            }
            expandable[e.referee_idx] = (ctl & JVMTI_VISIT_OBJECTS) != 0;
        }
        return JVMTI_ERROR_NONE;
    }
};

ReferenceChainsBfsTest *ReferenceChainsBfsTest::active_fixture = nullptr;

TEST_F(ReferenceChainsBfsTest, ReconstructsChainForSyntheticGraph) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *classA = (void *)0x2001, *classB = (void *)0x2002,
         *classTarget = (void *)0x2003;
    int ca = addClass(classA, "Lcom/rc/phase3/graph/A;");
    int cb = addClass(classB, "Lcom/rc/phase3/graph/B;");
    int ct = addClass(classTarget, "Lcom/rc/phase3/graph/Target;");

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeTarget = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, ca},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, cb},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeTarget, ct},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // A single pass that reaches full exhaustion of the reachable
    // graph completes the search and releases every tag it assigned - so
    // the tag must be fetched via tags_ever_assigned (captured at
    // assignment time), not node_tags (already reset to 0 by
    // releaseSearchTags() by the time runPass() returns; see
    // ReleasesTagsOnCompletion below for the release itself).
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    jlong targetTag = tags_ever_assigned[nodeTarget];
    ASSERT_NE(0, targetTag);
    EXPECT_EQ(0, node_tags[nodeTarget]); // released - see the comment above

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(targetTag, &chain));
    ASSERT_EQ(3u, chain.size());

    int expectedTarget = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/Target", strlen("com/rc/phase3/graph/Target"));
    int expectedB = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/B", strlen("com/rc/phase3/graph/B"));
    int expectedA = Profiler::instance()->lookupClass(
        "com/rc/phase3/graph/A", strlen("com/rc/phase3/graph/A"));
    ASSERT_NE(-1, expectedTarget);
    ASSERT_NE(-1, expectedB);
    ASSERT_NE(-1, expectedA);

    EXPECT_EQ((u32)expectedTarget, chain[0]);
    EXPECT_EQ((u32)expectedB, chain[1]);
    EXPECT_EQ((u32)expectedA, chain[2]);

    // buildChainEvent() wraps the same reconstructChain() call into
    // the ReferenceChainEvent shape Recording::recordReferenceChain()
    // (flightRecorder.cpp) expects - same chain/order, plus the target's own
    // depth from FrontierEntry.
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, targetTag,
                                          &event));
    EXPECT_EQ((u64)targetTag, event._target_tag);
    EXPECT_EQ(2u, event._depth); // root(A, depth0) -> B(depth1) -> Target(depth2)
    ASSERT_EQ(chain, event._chain);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BuildChainEventFailsForUnknownTag) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainEvent event;
    EXPECT_FALSE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, 12345,
                                          &event));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BuildAbandonedEventFailsUnlessSearchAbandoned) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Freshly started: never abandoned (never even run a pass yet).
    ReferenceChainAbandonedEvent event;
    EXPECT_FALSE(tracker->buildAbandonedEvent(&event));

    int nodeA = addNode();
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}};
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    // Small graph, no caps hit -> COMPLETED, not ABANDONED.
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_FALSE(tracker->buildAbandonedEvent(&event));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, HopCapStopsAdmittingBeyondCap) {
    Arguments args;
    // hops=1: only depth 0 (direct root references) may be admitted.
    ASSERT_FALSE(args.parse("referencechains=true:hops=1:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // depth 0 - admitted
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // depth 1 - capped
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated); // hop cap is not truncation - a normal boundary
    // Not truncated -> graph fully explored within the hop cap -> the search
    // completes and releases its tags in the same call (see the previous
    // test's comment) - fetch nodeA's tag via tags_ever_assigned, not
    // node_tags.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]); // never admitted into the frontier

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BudgetExhaustionTruncatesAndIsReported) {
    Arguments args;
    // budget=1: root enumeration and the expand phase draw from separate
    // budget pools (see runPassManualWalk()'s own comment), each sized 1
    // here - root enum admits nodeA, then the expand phase's own 1-unit
    // budget admits exactly one of nodeA's two children before exhausting.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // admitted via root enum
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // admitted via expand
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeC, -1},   // expand budget exhausted
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Budget exhaustion for *this pass* leaves pending work (nodeC's own
    // edge was never even attempted) - the search stays RUNNING, not
    // COMPLETED, so no tag release happens yet and node_tags[nodeA]/[nodeB]
    // are still the real assigned tags.
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_NE(0, node_tags[nodeB]);
    EXPECT_EQ(0, node_tags[nodeC]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, PreTaggedClassObjectsAreNeverExpandedOrAdmitted) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    node_tags[classNode] = -7; // simulate a class object already tagged by
                               // resolveLoadedClasses() before this pass -
                               // see ClassTagTable's tag-sign convention.
    int fieldTargetNode = addNode();

    script = {
        // A root reference straight to the class object (e.g. a
        // JVMTI_HEAP_REFERENCE_SYSTEM_CLASS root edge in a real walk).
        {JVMTI_HEAP_REFERENCE_SYSTEM_CLASS, -1, classNode, -1},
        // A static field of that class - must never be delivered by a real
        // FollowReferences call, since the class-object edge above must not
        // return JVMTI_VISIT_OBJECTS; mock_FollowReferences enforces this
        // the same way a real traversal would (see its own comment).
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    EXPECT_EQ(-7, node_tags[classNode]); // untouched - never treated as a
                                         // frontier object
    EXPECT_EQ(0, node_tags[fieldTargetNode]); // never reached - the class
                                               // edge above must not expand

    tracker->stop();
}

// Regression test for admitStaticFieldRoots(): an object retained solely by
// a static field (no other GC root reaches it) must still be discovered.
// The scripted class is registered via addClass() with its own node's
// address as the jclass identity, so GetLoadedClasses()/resolveLoadedClasses()
// (real production code, driven through the same mocked jvmti) tag it
// negative through node_tags[classNode] exactly like a real Class object -
// the same identity the STATIC_FIELD script edge below uses as its
// referrer, mirroring how a real Class object is simultaneously "a loaded
// class" and "the referrer of its own static-field edges".
TEST_F(ReferenceChainsBfsTest, DiscoversObjectRetainedOnlyByStaticField) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int fieldTargetNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/Holder;");

    script = {
        // No GC-root path to fieldTargetNode at all - it is reachable only
        // via classNode's static field.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // classNode got tagged negative by the real resolveLoadedClasses() scan
    // (not manually, unlike PreTaggedClassObjectsAreNeverExpandedOrAdmitted
    // above), and was never itself admitted as a frontier object.
    EXPECT_LT(node_tags[classNode], 0);

    jlong target_tag = tags_ever_assigned[fieldTargetNode];
    ASSERT_NE(0, target_tag);

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(target_tag, &chain));
    ASSERT_EQ(1u, chain.size());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(target_tag, &entry));
    EXPECT_EQ(0, entry.parent_tag); // root-attached, not a child hop
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, entry.root_kind);

    tracker->stop();
}

// Regression test for the resolveLoadedClasses() scan-skip guard: it must
// compare `class_count != _last_resolved_class_count`, not `class_count >
// _last_resolved_class_count`. GetLoadedClasses()'s count is not monotonic -
// class unloading can shrink it - so a `>` guard would stay permanently
// skipped once the count is loaded back up to, but not past, a prior
// historical peak, silently leaving any *different* classes loaded in that
// regrowth untagged forever. See resolveLoadedClasses()'s own comment for
// the full rationale.
TEST_F(ReferenceChainsBfsTest, ResolveLoadedClassesRescansAfterClassCountShrinksAndPartiallyRegrows) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *classA = (void *)0x3001, *classB = (void *)0x3002, *classC = (void *)0x3003;
    addClass(classA, "Lcom/rc/regress/A;");
    int idxB = addClass(classB, "Lcom/rc/regress/B;");

    // Pass 1: both A and B loaded (count == 2) - both get resolved/tagged.
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classA));
    ASSERT_NE(0u, tags.count(classB));
    EXPECT_NE(0, tags[classA]);
    EXPECT_NE(0, tags[classB]);

    // Simulate B's classloader being GC'd: GetLoadedClasses() now reports
    // only A (count shrinks 2 -> 1), exactly like a real class unload.
    classes.erase(classes.begin() + idxB);
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1, ReferenceChainsTestAccessor::lastResolvedClassCount());

    // Simulate a *different* class C loading back in, bringing the count
    // back to 2 - the same count as pass 1's peak, but not the same class
    // set. The buggy `>` guard (2 > 2 is false, since it never re-lowered
    // _last_resolved_class_count on the shrink above either) would skip the
    // scan here and leave C's tag at 0 forever; the fixed `!=` guard must
    // still resolve it.
    addClass(classC, "Lcom/rc/regress/C;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classC));
    EXPECT_NE(0, tags[classC]); // the regression this test guards against

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Incremental resumption across passes (ReferenceChainTracker::
// expandFrontier()/releaseSearchTags()/shouldRunPass(), and runPass()'s
// SearchState transitions).
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsBfsTest, MultiPassResumptionReconstructsChainAcrossPasses) {
    Arguments args;
    // budget=1 forces each pass to admit at most one new frontier entry, so
    // this 3-hop chain cannot be discovered within a single pass -
    // exercising expandFrontier() (resumed passes), not just the first
    // pass's root walk.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeTarget = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeTarget, -1},
    };

    // Drive the search to completion one pass at a time, exactly as
    // threadLoop() would once wired up (each call bounded by `budget`).
    bool truncated = true;
    int passes_issued = 0;
    while (tracker->searchState() == SearchState::RUNNING && passes_issued < 20) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        passes_issued++;
    }

    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_GT(tracker->passesRun(), 1); // did not fit in a single pass
    EXPECT_EQ(tracker->passesRun(), passes_issued);

    jlong targetTag = tags_ever_assigned[nodeTarget];
    ASSERT_NE(0, targetTag);
    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(targetTag, &chain));
    // Depth/parent_tag linkage survived resumption intact - all 3 hops walk
    // back to a root-attached (depth 0) entry, which reconstructChain()
    // requires to succeed at all (see its own "reaching parent_tag == 0"
    // contract).
    EXPECT_EQ(3u, chain.size());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, FrontierCapHitAbandonsImmediately) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_EQ(1, tracker->frontierTable()->maxCapacity());

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // fits (the one slot)
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // frontier cap hit
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Frontier-size cap hit -- the search abandons immediately (design
    // doc's Termination-section priority 1). Once the table is full, no
    // new entry can ever be admitted, so the frontier can never grow
    // again -- deferring to a separate no-progress counter would never
    // actually observe that counter, since this same condition matches
    // every subsequent pass too.
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());
    ASSERT_EQ(SearchAbandonReason::FRONTIER_CAP, tracker->abandonReason());

    // nodeA was admitted (frontier cap=1 allowed one entry), then its tag
    // was released as part of this same pass's abandon handling (the mock
    // GetObjectsWithTags() succeeds by default).
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    // nodeB was never admitted (frontier cap hit).
    EXPECT_EQ(0, node_tags[nodeB]);

    tracker->stop();
}

// releaseSearchTags()'s GetObjectsWithTags() call failing must NOT be treated
// as "released" - see that method's own comment for why: marking a tag
// ABANDONED (or resetting _next_tag on restart) while its object might still
// be live would let a restarted search's fresh tags collide with it,
// corrupting FrontierTable's tag-uniqueness invariant. This is the regression
// test for that failure path (previously the return value was discarded
// entirely).
TEST_F(ReferenceChainsBfsTest, ReleaseSearchTagsFailureBlocksTagReuseUntilItSucceeds) {
    Arguments args;
    // framecap=1 with a self-cycle: pass 1 admits nodeA (the frontier's
    // only slot); the nodeA->nodeA edge then finds nodeA
    // ALREADY_ADMITTED rather than hitting the frontier cap (no new slot
    // is needed for an edge back to an already-tagged object), so the
    // search stays RUNNING and only the no-progress detector - after
    // NO_PROGRESS_PASS_LIMIT stale passes - can abandon it. This test
    // verifies that the tag release on that abandonment works even when
    // GetObjectsWithTags() fails.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1:ttl=0"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    // nodeA -> nodeA self-cycle. With framecap=1, pass 1 admits nodeA;
    // the self-cycle edge is ALREADY_ADMITTED, not a fresh frontier slot.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeA, -1}, // self-cycle
    };

    long long failedBefore =
        Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED);

    fail_get_objects_with_tags = true;
    bool truncated = false;
    // Pass 1: admits nodeA; the self-cycle keeps the pass truncated
    // without growing the frontier further.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]);

    // Run enough stale passes to trigger no-progress abandonment.
    for (int i = 1; i < ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT + 1; i++) {
      ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
      ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    }
    // The next pass should abandon via no-progress.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());

    // GetObjectsWithTags() failed - nodeA's still-live tag must NOT have been
    // cleared, and the failure must be counted.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]) << "tag must not be cleared when the "
                                       "release batch itself failed";
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 1,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // While the release is still outstanding, shouldRunPass() must force a
    // retry unconditionally.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState())
        << "must retry the release in place, not restart, while tags are "
           "still unreleased";

    // A further runPass() call retries the release; still failing.
    int passesBefore = tracker->passesRun();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(passesBefore, tracker->passesRun());
    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // Once GetObjectsWithTags() starts succeeding again.
    fail_get_objects_with_tags = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED))
        << "a successful release must not itself count as a failure";

    tracker->stop();
}

// Regression test for the CANARY_STUCK/frontier-wipe convergence bug: prior
// to this fix, runPass()'s canary-stuck branch fired purely off
// _passes_since_last_candidate_progress, so a search whose candidate simply
// had not been found yet was abandoned - and its frontier destructively
// wiped by the next restartSearch() - after only CANARY_NO_PROGRESS_PASS_LIMIT
// passes, even while the whole-graph frontier was still growing every single
// pass. Live on-pod evidence showed exactly this: a frontier that had grown
// to 12k-16k entries got wiped roughly every 20s while chasing a
// confirmed-reachable candidate. The fix requires the whole-graph frontier to
// ALSO have stalled (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT)
// before CANARY_STUCK can fire - see CANARY_NO_PROGRESS_PASS_LIMIT's and
// canaryStuckPassLimit()'s own comments.
TEST_F(ReferenceChainsBfsTest, CanaryStuckRequiresWholeGraphFrontierAlsoStalled) {
    Arguments args;
    // budget=1: exactly one new frontier admission per pass, so the frontier
    // grows every single pass for as long as the chain has unexplored nodes
    // left - _passes_since_last_progress never leaves 0.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A chain longer than the number of passes driven below, so the frontier
    // still has pending work - and is still growing one node per pass - at
    // every pass this test checks.
    constexpr int kChainLength = 50;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    // A canary candidate that this graph never actually contains (no node is
    // ever tagged with the candidate's marker tag) - the candidate-specific
    // stuck counter (_passes_since_last_candidate_progress) climbs every pass
    // with zero discovery progress, exactly like the live-pod scenario
    // chasing a candidate deeper than the old fixed
    // CANARY_NO_PROGRESS_PASS_LIMIT (30) passes could reach.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);

    bool truncated = true;
    // One more pass than the old fixed CANARY_NO_PROGRESS_PASS_LIMIT: long
    // enough that the pre-fix single-condition check would already have
    // abandoned the search, but short enough that the 40-node chain still has
    // unexplored work left, so the frontier is still genuinely growing every
    // pass.
    for (int i = 0; i < ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT + 2;
         i++) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        ASSERT_EQ(0, tracker->passesSinceLastProgressForTest())
            << "pass " << i << ": frontier must still be growing every pass";
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState())
            << "pass " << i
            << ": a canary search must not be abandoned while the "
               "whole-graph frontier is still growing, even if its specific "
               "candidate has not yet been found";
    }
    // The narrower candidate-stuck counter climbed the whole time - this is
    // what the old, single-condition check would have abandoned on alone.
    EXPECT_GE(ReferenceChainsTestAccessor::passesSinceLastCandidateProgress(),
              ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT);

    tracker->stop();
}

// Canary-lane backoff pacing (option A): a chase with unresolved candidates
// runs back-to-back only while it is fresh or making candidate progress;
// each pass with NO candidate progress doubles the spacing multiplier
// (_canary_backoff_mult) up to CANARY_BACKOFF_MULT_MAX, progress resets it
// to 1, and the OOM urgency ramp overrides the gate entirely. Live evidence
// this bounds (hotdog rounds 3-4): an un-findable candidate held the chase
// open for 32 minutes at ~88 passes/min - a full core - because canary_active
// bypassed every cadence check and threadLoop() skips its sleep whenever a
// pass will run. Work-scaled rather than a fixed cap: hotdog's own passes
// ran 0.7-4s, so any fixed cap below that would have changed nothing at all
// - the loop is work-bound when the pass exceeds the cap - while a fixed 1s
// cap starved ReferenceChainTrackingTest's deep ~200-pass chase outright.
TEST_F(ReferenceChainsBfsTest, CanaryLaneBacksOffWithoutProgressAndResetsOnProgress) {
    Arguments args;
    // Same shape as CanaryStuckRequiresWholeGraphFrontierAlsoStalled above:
    // budget=1 with a long chain keeps the frontier growing one node per
    // pass, so the CANARY_STUCK detector (which also requires a stalled
    // frontier) never fires and the chase stays RUNNING through the whole
    // loop below.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    constexpr int kChainLength = 50;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    bool truncated = true;

    // Pass 1: the candidate admission itself raises the progress mark
    // (0 -> 1), so this counts as progress and the multiplier stays at 1 -
    // back-to-back.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult());
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a fresh chase must be allowed to run back-to-back";

    // Pass 2: no candidate progress -> first doubling (1 -> 2). Seed a
    // deterministic pass-cost EMA (mock passes are sub-ms, so the real EMA
    // decays to 0) and a fresh pass timestamp so the spacing arithmetic is
    // exact: spacing = 2 x 100ms.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryBackoffMult());
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/2, /*ema_ms=*/100, OS::nanotime());
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a no-progress canary pass must hold off the next one";
    // Beyond the spacing, the chase is allowed again - the backoff paces,
    // it never abandons.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(
        ReferenceChainsTestAccessor::lastCanaryPassNs() +
        2ULL * 100ULL * 1000000ULL + 1))
        << "elapsed spacing must re-admit the canary pass";

    // The OOM urgency ramp overrides the backoff gate entirely.
    ReferenceChainsTestAccessor::setOomRampActive(true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "urgency must bypass the canary backoff";
    ReferenceChainsTestAccessor::setOomRampActive(false);

    // Consecutive no-progress passes double the multiplier up to the cap
    // (seeded at 8 so one more pass reaches it, the next holds it).
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/8, /*ema_ms=*/100, OS::nanotime());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult())
        << "the multiplier must hold at its cap, not grow past it";

    // Candidate progress (a new candidate admitted into a slot) resets the
    // lane to back-to-back.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(1, /*klass_id=*/987);
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult())
        << "candidate progress must reset the spacing multiplier to 1";
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ChainCompletesWithoutAbandonment) {
    Arguments args;
    // budget=1 on a graph where each pass admits exactly one new edge
    // until the chain is exhausted, then the frontier stops growing.
    // After NO_PROGRESS_PASS_LIMIT passes with no growth, the search
    // is abandoned (progress-based termination, not wall-clock TTL).
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();
    int nodeD = addNode();

    // A chain one node longer than either pass's 1-edge expand budget can
    // fully drain in a single call, so each pass still ends truncated (see
    // mock_FollowReferences()'s own comment: an array-holder walk chains
    // through as many script edges as it can admit before budget aborts it)
    // and there is still pending work left for the no-progress check to catch
    // once the chain is fully discovered.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeC, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeC, nodeD, -1},
    };

    bool truncated = false;
    // Pass 1: root enum admits nodeA, expand admits nodeB, aborts on
    // nodeB->nodeC for lack of budget - truncated, frontier grew (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 2: admits nodeC, aborts on nodeC->nodeD - still truncated,
    // still growing (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 3: admits nodeD, chain exhausted - no longer truncated,
    // no pending frontier, natural completion.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Tags released.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_NE(0, tags_ever_assigned[nodeB]);
    EXPECT_EQ(0, node_tags[nodeB]);

    // No-progress (not TTL) is reported as the reason when the frontier stalls.
    // This test uses ttl=0 to disable the wall-clock TTL, so only the
    // no-progress detector can abandon.
    EXPECT_EQ(SearchAbandonReason::NONE, tracker->abandonReason());
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, NoProgressAbandonsSearchAndReleasesTags) {
    // Verify the progress-based abandonment wiring: the no-progress limit
    // is accessible, positive, and reset to 0 by resetSearchStateForTest().
    // The mock runPass() re-enumerates roots on every search_started=0
    // pass, causing the frontier to oscillate rather than stabilize,
    // so a full end-to-end no-progress abandonment can't be tested
    // with the mock. The real JVM path is validated by the
    // AggressiveLeakReferenceChainTest Java integration test.
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Verify the no-progress limit is accessible and positive.
    EXPECT_GT(ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT, 0);

    // Verify that a fresh search starts with zero passes since last progress.
    EXPECT_EQ(0, tracker->passesSinceLastProgressForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ResolveOrDropPrunesDeadFrontierEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    // A second root that root enumeration's own 1-unit budget (firstpassbudget=1)
    // can't reach this pass - the resulting root-enum truncation makes
    // runPassManualWalk() return before expandFrontier() ever runs (see its
    // own comment on frontier-cap-hit/budget-exhausted root-enum truncation),
    // so nodeA is admitted but never gets a chance to expand nodeA->nodeB.
    int decoyRoot = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, decoyRoot, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 1
    ASSERT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    jlong aTag = tags_ever_assigned[nodeA];
    ASSERT_NE(0, aTag);
    // Simulate nodeA dying (collected) between pass 1 and pass 2 -
    // GetObjectsWithTags will no longer report it as live.
    dead_tags.insert(aTag);

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 2: resolve-or-drop
    EXPECT_FALSE(truncated);
    // The dead branch was pruned for free - with nothing else pending, the
    // search completes rather than staying RUNNING or being ABANDONED.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(2, tracker->passesRun());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(aTag, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);

    // nodeB was never discovered - nodeA's subtree was pruned, not expanded.
    EXPECT_EQ(0, tags_ever_assigned[nodeB]);

    tracker->stop();
}

// ---------------------------------------------------------------------------
// pollWatchedTargets() (design doc's Open Question 3 bridging
// step, corrected read-only mechanism - see referenceChains.h's own
// target-selection bridging step header comment and pollWatchedTargets()'s
// comment for the plan doc's "Correction to the design doc's Open Question 3
// mechanism").
//
// Mirrors referenceChainJfrRoundtrip_ut.cpp's FrontierTable::insert()
// seeding style rather than driving a full scripted runPass() (this test
// suite's gtest coverage bullet explicitly asks for reusing that seeding style over
// writing a third pattern): a candidate's "already discovered by an
// ordinary pass" tag is modelled directly as a FrontierTable entry plus a
// mocked GetTag() that reports it - both reach the same FrontierTable + tag
// state pollWatchedTargets()/buildChainEvent() read, regardless of whether a
// scripted heap walk or direct insertion produced it.
//
// LivenessTracker::instance() is a second process-wide singleton (see its
// own header comment) shared with livenessTracker_ut.cpp within this same
// gtest binary - klassPopulationResetForTest()/setGcGenerationsForTest() at
// SetUp/TearDown keep this suite's use of it self-contained, the same way
// ReferenceChainsTestAccessor::reset() already isolates
// ReferenceChainTracker::instance() above.
// ---------------------------------------------------------------------------

class PollWatchedTargetsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};

    std::unordered_map<jobject, jlong> tags;
    std::unordered_set<jobject> dead_refs; // NewLocalRef returns NULL for these

    jvmtiEnv *orig_jvmti = nullptr;
    static PollWatchedTargetsTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);

        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.GetTag = &mock_GetTag;
        jvmti_tbl.SetTag = &mock_SetTag;
        jvmti_tbl.GetClassSignature = &mock_GetClassSignature;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.NewLocalRef = &mock_NewLocalRef;
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
        jni_tbl.GetObjectClass = &mock_GetObjectClass;
        mock_jni.functions = &jni_tbl;
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        active_fixture = nullptr;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        active_fixture->tags[object] = tag;
        return JVMTI_ERROR_NONE;
    }

    static jobject JNICALL mock_NewLocalRef(JNIEnv *, jobject ref) {
        if (active_fixture->dead_refs.count(ref) > 0) {
            return nullptr;
        }
        return ref; // identity passthrough - see this fixture's own comment
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject values are not real JNI refs.
    }

    // pollWatchedTargets()'s diagnostic class-name lookup on the candidate's
    // representative: this fixture's fake jobjects carry no real class
    // identity, so a fixed non-null jclass plus a fixed signature is all
    // GetObjectClass()/GetClassSignature() need to return for that lookup to
    // complete without touching a real JVM.
    static jclass JNICALL mock_GetObjectClass(JNIEnv *, jobject) {
        return (jclass)0xC1A55;
    }

    static jvmtiError JNICALL mock_GetClassSignature(jvmtiEnv *, jclass,
                                                       char **signature_ptr,
                                                       char **generic_ptr) {
        *signature_ptr = strdup("Ltest/FakeKlass;");
        if (generic_ptr != nullptr) {
            *generic_ptr = nullptr;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_Deallocate(jvmtiEnv *, unsigned char *mem) {
        free(mem);
        return JVMTI_ERROR_NONE;
    }

    // Seeds LivenessTracker's real population table with a growing series
    // for `klass_id` (20 strictly-increasing samples - satisfies
    // selectLeakCandidates()'s min-fill, growth/floor magnitude, and
    // sustained-trend hysteresis requirements, livenessTracker.h; 20 rather
    // than the 10-sample minimum fill leaves comfortable margin past the
    // hysteresis threshold rather than sitting exactly on its boundary) and
    // points its representative at `rep`.
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // Per-(klass, tid) qualification: selectLeakCandidates() also
            // requires a qualifying allocating thread. These fixtures have
            // no real tracked instances (mock JVMTI, no live heap), so a
            // fixed synthetic tid exercises the gate without pretending to
            // match any instance's real tid.
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(nullptr, klass_id, rep);
    }
};

PollWatchedTargetsTest *PollWatchedTargetsTest::active_fixture = nullptr;

TEST_F(PollWatchedTargetsTest, EmitsEventForAlreadyDiscoveredCandidate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    // Model "already discovered by an ordinary runPass()": a root-level
    // FrontierTable entry plus a matching GetTag() result, mirroring
    // referenceChainJfrRoundtrip_ut.cpp's seeding style.
    ASSERT_TRUE(tracker->frontierTable()->insert(
        /*tag=*/7, /*parent_tag=*/0, /*referrer_klass=*/1, /*depth=*/0,
        FrontierEntryState::EDGE));
    tags[obj] = 7;
    // With class-tag matching, _candidate_frontier_tags must be set
    // so buildCanaryChainEvent() can reconstruct the chain.
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(7));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoEventForNotYetDiscoveredCandidate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    // GetTag() reports 0 (default) - no pass has reached this object yet.

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoDuplicateOnRepeatPoll) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());

    // Klass 1 is still flagged (LivenessTracker's ranking doesn't know an
    // event was already emitted for it) - a second, third, ... poll must
    // not re-emit for the same target_tag.
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(7));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, SkipsCandidateWhoseWeakReferenceDied) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    dead_refs.insert(obj); // NewLocalRef(rep) -> NULL, as if GC'd

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7; // would resolve to a discovered tag, if it could resolve

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

// A cached chain must not re-emit forever: once the klass's representative
// stops resolving (collected, or LRU-evicted from LivenessTracker's
// population table - klassPopulationSetRepresentativeForTest()'s ref is the
// stand-in for either), the very next poll must prune it from
// _resolved_chains rather than leaving a dump keep re-emitting a chain for a
// sample that is gone (see _resolved_chains' own comment, referenceChains.h,
// and pollWatchedTargets()'s "candidate died, or was evicted" branch).
TEST_F(PollWatchedTargetsTest, ChainPersistsAfterRepresentativeDies) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    ASSERT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));

    // The representative died. Per-instance caching: the chain persists
    // (it describes a reference path that was valid at resolution time).
    // It expires naturally when the search restarts and the frontier is
    // wiped. The backend can filter stale chains via HeapLiveObject events.
    dead_refs.insert(obj);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "per-instance chains persist after representative dies; "
           "they expire on search restart, not on representative death";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoOpWhenGcGenerationsDisabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Overrides this fixture's own SetUp() default - exercises the
    // pollWatchedTargets() guard covering LivenessTracker's own
    // _gc_generations gate (population tracking's own gate), not just this tracker's own _enabled.
    LivenessTracker::instance()->setGcGenerationsForTest(false);

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Resolved-chain cache (ReferenceChainTracker::cacheResolvedChain()/
// drainPendingChainEvents(), referenceChains.cpp) - the mechanism that keeps a
// resolved chain alive across dumps so it re-emits into every JFR chunk the
// sample survives into, and keeps Profiler::writeReferenceChain()'s blocking
// lock-acquisition retry loop off the BFS scheduling thread (see
// _resolved_chains' own comment, referenceChains.h). These tests drive
// cacheResolvedChain()/drainPendingChainEvents() directly via
// ReferenceChainsTestAccessor rather than through the full
// pollWatchedTargets()/selectLeakCandidates() pipeline - the cache/overflow/
// counter mechanism is independent of how a chain was produced, and driving it
// through hundreds of real LivenessTracker candidates just to reach
// MAX_RESOLVED_CHAINS would test the seeding helper, not this mechanism.
// ---------------------------------------------------------------------------

class ResolvedChainCacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
    }

    void TearDown() override {
        ReferenceChainsTestAccessor::reset();
    }

    static ReferenceChainEvent makeEvent(u64 target_tag) {
        ReferenceChainEvent event;
        event._target_tag = target_tag;
        event._depth = 0;
        return event;
    }
};

// The defining property of the "stick around" model: a cached chain is
// re-emitted on every dump, not drained once. Two successive drains with no
// intervening change must BOTH return the cached chain, and the cache must
// stay populated afterwards (unlike the old queue, which emptied on drain).
TEST_F(ResolvedChainCacheTest, SnapshotReEmitsOnEveryDumpWithoutClearing) {
    ReferenceChainsTestAccessor::cacheChain(/*source_tag=*/1, makeEvent(7),
                                            /*source_tag=*/7, /*search_ns=*/0);

    std::vector<ReferenceChainEvent> firstDump;
    ReferenceChainsTestAccessor::drain(&firstDump);
    ASSERT_EQ(1u, firstDump.size());
    EXPECT_EQ(7u, firstDump[0]._target_tag);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "drain must not clear the cache";

    // A second dump with nothing changed re-emits the same chain.
    std::vector<ReferenceChainEvent> secondDump;
    ReferenceChainsTestAccessor::drain(&secondDump);
    ASSERT_EQ(1u, secondDump.size());
    EXPECT_EQ(7u, secondDump[0]._target_tag);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
}

// Re-resolving the same klass (a restart re-tags its sample, or a fresh walk
// finds a deeper path) refreshes its single cache slot in place rather than
// accumulating duplicates - so a dump re-emits one current chain per klass,
// not one per resolution.
TEST_F(ResolvedChainCacheTest, RefreshReplacesSameKlassInPlace) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(7), 7, 0);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    // Same klass, rebuilt from a new tag (e.g. after a search restart).
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(9), 9, 0);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "refresh must overwrite, not append";
    EXPECT_EQ(9, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(1u, dump.size());
    EXPECT_EQ(9u, dump[0]._target_tag);
}

// Distinct klasses each get their own slot and all re-emit together in one
// dump (order is unspecified - the cache is a map keyed by klass_id).
TEST_F(ResolvedChainCacheTest, MultipleKlassesAllSnapshotTogether) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(1), 1, 0);
    ReferenceChainsTestAccessor::cacheChain(2, makeEvent(2), 2, 0);
    ReferenceChainsTestAccessor::cacheChain(3, makeEvent(3), 3, 0);
    ASSERT_EQ(3u, ReferenceChainsTestAccessor::resolvedChainCount());

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(3u, dump.size());
    std::set<u64> tags;
    for (const auto &e : dump) {
        tags.insert(e._target_tag);
    }
    EXPECT_EQ((std::set<u64>{1, 2, 3}), tags);
}

// A brand-new klass arriving with the cache already at MAX_RESOLVED_CHAINS is
// dropped (and counted via REFERENCE_CHAIN_EVENTS_DROPPED, this codebase's own
// "dropped-event-without-counter" review lens) rather than evicting some other
// still-live sample's chain - but refreshing a klass that is already cached
// still succeeds even at capacity.
TEST_F(ResolvedChainCacheTest, OverflowDropsNewKlassButAllowsRefresh) {
    const int cap = ReferenceChainsTestAccessor::maxResolvedChains();
    long long droppedBefore = Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED);

    for (int i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::cacheChain((jlong)i, makeEvent((jlong)i),
                                                (jlong)i, 0);
    }
    ASSERT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(droppedBefore, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "filling exactly to capacity must not drop anything yet";

    // A brand-new klass at capacity is dropped and counted.
    ReferenceChainsTestAccessor::cacheChain((jlong)cap, makeEvent((jlong)cap),
                                            (jlong)cap, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount())
        << "cache must stay capped, not grow past MAX_RESOLVED_CHAINS";
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED));
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag((u32)cap));

    // Refreshing an already-cached klass at capacity must still succeed - it
    // reuses that klass's existing slot rather than needing a free one.
    ReferenceChainsTestAccessor::cacheChain(/*source_tag=*/0, makeEvent(999),
                                            /*source_tag=*/999, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(999, ReferenceChainsTestAccessor::resolvedChainSourceTag(0));
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "an in-place refresh must not count as a drop";
}

// ---------------------------------------------------------------------------
// Pause-time pacing controller: pause-time-SLO feedback loop
// (ReferenceChainTracker::updatePacing(), referenceChains.cpp) - see that
// method's own comment (referenceChains.h) for the full mechanism. These
// tests drive updatePacing() directly with a synthetic sequence of "pass
// took Xms" wall-clock durations via ReferenceChainsTestAccessor (this
// file's existing pattern for reaching a private method/state - see the
// target-selection bridging step's hasResolvedChainForTag()/resolvedChainCount() above),
// reusing the ReferenceChainsTest fixture since updatePacing() itself makes
// no JVMTI calls.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsTest, PacingHoldsSteadyWhenPassesLandExactlyOnCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int startBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 startCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
    ASSERT_EQ(4000, startBudget); // starts pinned at the configured ceiling

    // A pass landing exactly on the pause-time target is a zero error every
    // call - the controller should never move away from its starting point,
    // regardless of how many such passes are observed in a row.
    for (int i = 0; i < 10; i++) {
        ReferenceChainsTestAccessor::updatePacing(5 * 1000000ULL); // 5ms
        EXPECT_EQ(startBudget, ReferenceChainsTestAccessor::effectiveBudget());
        EXPECT_EQ(startCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());
    }

    tracker->stop();
}

TEST_F(ReferenceChainsTest, PacingShrinksBudgetAndWidensCadenceWhenOverCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int initialBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 initialCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // A pass taking 10x the pause-time ceiling, fed repeatedly (a constant
    // input - the plan's own "does not oscillate indefinitely" scenario).
    int lastBudget = initialBudget;
    u64 lastCadence = initialCadence;
    for (int i = 0; i < 20; i++) {
        ReferenceChainsTestAccessor::updatePacing(50 * 1000000ULL); // 50ms
        int budget = ReferenceChainsTestAccessor::effectiveBudget();
        u64 cadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_LE(budget, lastBudget); // never grows while still over ceiling
        EXPECT_GE(cadence, lastCadence); // never shrinks while still over ceiling
        lastBudget = budget;
        lastCadence = cadence;
    }

    // Moved in the correct direction...
    EXPECT_LT(lastBudget, initialBudget);
    EXPECT_GT(lastCadence, initialCadence);
    // ...and converged to a fixed point rather than oscillating: one more
    // identical input produces no further change.
    ReferenceChainsTestAccessor::updatePacing(50 * 1000000ULL);
    EXPECT_EQ(lastBudget, ReferenceChainsTestAccessor::effectiveBudget());
    EXPECT_EQ(lastCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Start from a controlled below-ceiling/above-baseline point (as if an
    // earlier over-ceiling run had already shrunk/widened them - see the
    // previous test) with a freshly reset controller, rather than chaining
    // directly off a constant-input sequence like the previous test's own:
    // _pause_pid's integral state would otherwise still be recovering from
    // that sequence's windup for many iterations after switching to a
    // smaller-magnitude error, muddying this test's per-step "moves in the
    // correct direction every step" assertions with a transient this test
    // is not about.
    ReferenceChainsTestAccessor::setEffectiveBudget(2400);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(
        2 * ReferenceChainsTestAccessor::baselineCadenceNs());
    ReferenceChainsTestAccessor::resetPacingController();
    int shrunkBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 widenedCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // Now feed passes comfortably under the ceiling, repeatedly (a constant
    // input, to check convergence rather than oscillation). 200 iterations -
    // more than PacingShrinksBudgetAndWidensCadenceWhenOverCeiling needs -
    // because this scenario's error magnitude (pausetarget=5 vs. an
    // effectively-instant 0ms pass) is smaller, so the cadence side takes
    // more iterations to fully unwind down to MIN_EFFECTIVE_CADENCE_NS, and
    // because the borrowed-budget distance to close (configured budget *
    // (BORROW_CEILING_MULTIPLIER - 1)) scales with the configured budget
    // while the PID's per-pass step size does not.
    int lastBudget = shrunkBudget;
    u64 lastCadence = widenedCadence;
    for (int i = 0; i < 200; i++) {
        ReferenceChainsTestAccessor::updatePacing(0); // effectively instant
        int budget = ReferenceChainsTestAccessor::effectiveBudget();
        u64 cadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_GE(budget, lastBudget); // never shrinks while comfortably under
        EXPECT_LE(cadence, lastCadence); // never widens while comfortably under
        lastBudget = budget;
        lastCadence = cadence;
    }

    // Moved in the correct direction... and, since 50 identical
    // comfortably-under-target passes is well past BORROW_WARMUP_PASSES,
    // past the configured ceiling too - budget-borrowing lets it converge at
    // the borrowed ceiling (configured budget * multiplier) instead of
    // stalling at the plain configured budget.
    EXPECT_GT(lastBudget, shrunkBudget);
    EXPECT_EQ(4000 * ReferenceChainsTestAccessor::borrowCeilingMultiplier(), lastBudget);
    EXPECT_LT(lastCadence, widenedCadence);
    // ...and converged: one more identical input produces no further change.
    ReferenceChainsTestAccessor::updatePacing(0);
    EXPECT_EQ(lastBudget, ReferenceChainsTestAccessor::effectiveBudget());
    EXPECT_EQ(lastCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, MaybeRevokeBorrowForRootEnumPassPreservesBorrowAtBoundary) {
    Arguments args;
    // BORROW_UNDER_TARGET_FRACTION (referenceChains.h) is 0.5, so with
    // pausetarget=10 the comfortably-under-target boundary is exactly 5ms.
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainsTestAccessor::setBorrowedBudget(500);
    ReferenceChainsTestAccessor::setConsecutiveUnderTargetPasses(5);

    // Exactly at the boundary: comfortably_under_target's `<=` check must
    // still treat this as comfortably under, so the borrow is preserved.
    ReferenceChainsTestAccessor::maybeRevokeBorrowForRootEnumPass(5 * 1000000ULL);
    EXPECT_EQ(500, ReferenceChainsTestAccessor::borrowedBudget());
    EXPECT_EQ(5, ReferenceChainsTestAccessor::consecutiveUnderTargetPasses());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, MaybeRevokeBorrowForRootEnumPassRevokesJustPastBoundary) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainsTestAccessor::setBorrowedBudget(500);
    ReferenceChainsTestAccessor::setConsecutiveUnderTargetPasses(5);
    ReferenceChainsTestAccessor::setEffectiveBudget(1500); // as if borrow had raised the ceiling

    // Just past the boundary: no longer comfortably under target, so the
    // grant is revoked immediately, including re-clamping _effective_budget
    // down to the plain (non-borrowed) budget rather than leaving it
    // borrow-inflated until the next ordinary pass's updatePacing() call.
    ReferenceChainsTestAccessor::maybeRevokeBorrowForRootEnumPass(6 * 1000000ULL);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::borrowedBudget());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::consecutiveUnderTargetPasses());
    EXPECT_EQ(1000, ReferenceChainsTestAccessor::effectiveBudget());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// PainBudget (painBudget.h) - standalone, no ReferenceChainTracker singleton
// involved. A leaky bucket over cost (ms), not an event rate: spend()
// records how much an operation cost, canStartNow() drains the balance by
// elapsed wall-clock time at the configured refill rate and reports whether
// the debt has cleared.
// ---------------------------------------------------------------------------

TEST(PainBudgetTest, ClearBeforeAnythingIsEverSpent) {
    PainBudget budget(0.01);
    EXPECT_TRUE(budget.canStartNow(1000));
}

TEST(PainBudgetTest, SpendCreatesDebtThatBlocksAnImmediateSecondCall) {
    PainBudget budget(0.01); // 1%
    ASSERT_TRUE(budget.canStartNow(1000)); // establishes the drain baseline
    budget.spend(100); // 100ms of debt
    // No time has elapsed since the baseline call above - the debt cannot
    // have drained at all yet.
    EXPECT_FALSE(budget.canStartNow(1000));
}

TEST(PainBudgetTest, DebtDrainsProportionallyToElapsedTimeAndRefillRate) {
    PainBudget budget(0.01); // 1% -> 1ms of debt needs 100ms elapsed to clear
    ASSERT_TRUE(budget.canStartNow(0));
    budget.spend(10); // 10ms of debt -> needs 1000ms elapsed to fully clear
    EXPECT_FALSE(budget.canStartNow(500ULL * 1000000ULL));  // 500ms elapsed - not enough
    EXPECT_TRUE(budget.canStartNow(1500ULL * 1000000ULL));  // 1500ms total - enough
}

TEST(PainBudgetTest, ZeroRefillRateNeverClearsDebt) {
    PainBudget budget(0.0);
    ASSERT_TRUE(budget.canStartNow(0));
    budget.spend(1);
    // An enormous elapsed time still drains nothing at a 0 refill rate.
    EXPECT_FALSE(budget.canStartNow(1000000000000ULL));
}

// ---------------------------------------------------------------------------
// Search restart (referenceChains.h's own header comment: gating a
// restarted search's first pass on LivenessTracker already reporting a leak
// candidate, plus the PainBudget cooldown above, so a search that already
// walked the whole reachable graph once does not do so again indefinitely
// without a reason). Uses an "empty reachable graph" FollowReferences mock
// (no callback invocations at all) to reach SearchState::COMPLETED in one
// call - the simplest way to drive a search to a terminal state without
// ReferenceChainsBfsTest's full scripted-graph machinery, which exists for
// chain-reconstruction coverage this suite does not need.
// ---------------------------------------------------------------------------

class SearchRestartTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    jvmtiEnv *orig_jvmti = nullptr;

    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);

        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses;
        jvmti_tbl.FollowReferences = &mock_FollowReferences;
        jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        // UrgentOOMProjectionBypassesCandidateGate below sets this - reset it
        // here (TearDown always runs, even after a fatal ASSERT_* return)
        // rather than as a trailing statement in that test body, so a failed
        // assertion can't leak a stale max-heap value into the next test
        // sharing this singleton.
        LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
    }

    // No loaded classes to resolve - resolveLoadedClasses() reports 0 and
    // does nothing further.
    static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count,
                                                     jclass **out) {
        *count = 0;
        *out = nullptr;
        return JVMTI_ERROR_NONE;
    }

    // Never invokes the callback - models a heap with nothing reachable from
    // any root, so the very first pass completes immediately (0 admitted
    // edges, not truncated).
    static jvmtiError JNICALL mock_FollowReferences(
        jvmtiEnv *, jint, jclass, jobject, const jvmtiHeapCallbacks *,
        const void *) {
        return JVMTI_ERROR_NONE;
    }

    // runPassManualWalk()'s root enumeration - never invokes the root
    // callback, same "nothing reachable from any root" heap model as
    // mock_FollowReferences() above, so the first pass still completes
    // immediately with 0 admitted edges.
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
        jvmtiEnv *, jvmtiHeapRootCallback, jvmtiStackReferenceCallback,
        jvmtiObjectReferenceCallback, const void *) {
        return JVMTI_ERROR_NONE;
    }

    // Same seeding helper as PollWatchedTargetsTest above (20 strictly-
    // increasing samples - satisfies selectLeakCandidates()'s min-fill,
    // growth/floor magnitude, and sustained-trend hysteresis requirements).
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // Per-(klass, tid) qualification: selectLeakCandidates() also
            // requires a qualifying allocating thread. These fixtures have
            // no real tracked instances (mock JVMTI, no live heap), so a
            // fixed synthetic tid exercises the gate without pretending to
            // match any instance's real tid.
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(nullptr, klass_id, rep);
    }
};

TEST_F(SearchRestartTest, WithoutGenerationsSignalRestartStaysUnconditional) {
    // gc_generations off (this fixture's SetUp default): canAffordNewSearch()
    // has no candidate signal to gate on at all, so a terminal search is
    // immediately eligible to restart - preserves this tracker's pre-restart
    // behavior for a referencechains-without-generations setup (this class's
    // own header comment, last paragraph).
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    tracker->stop();
}

TEST_F(SearchRestartTest, GenerationsEnabledButNoCandidateBlocksFirstSearch) {
    // A brand-new tracker must not pay for the initial whole-heap
    // walk/tagging pass either when there is no leak candidate yet -
    // shouldRunPass()'s !_search_started branch now shares
    // canAffordNewSearch() with the restart gate below (this class's own
    // header comment).
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_EQ(0, tracker->passesRun());

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2));

    tracker->stop();
}

TEST_F(SearchRestartTest, GenerationsEnabledButNoCandidateBlocksRestart) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // No leak candidate flagged - nothing to justify the cost of a restart.
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(SearchRestartTest, RestartsOnceACandidateAppearsAndResetsPerSearchState) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    ASSERT_EQ(1, tracker->passesRun());

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1)); // restartSearch() runs inline
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_EQ(0, tracker->passesRun()); // restartSearch() zeroed per-search state

    // The next runPass() call takes the "first pass of a search" branch
    // again, exactly like a brand-new tracker.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(1, tracker->passesRun());

    tracker->stop();
}

TEST_F(SearchRestartTest, PainBudgetBlocksARestartUntilItDrains) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:painbudget=1")); // 1%
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    // First-ever search: called via runPass() directly here, bypassing
    // shouldRunPass()'s canAffordNewSearch() gate entirely - the candidate
    // seeded above would satisfy that gate anyway (this class's own header
    // comment).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #1: _safepoint_pain_budget has never had anything spent into it yet, so
    // this is always immediately affordable regardless of this first
    // search's own cost - the cost a search incurs only debits the *next*
    // restart's affordability (restartSearch()'s own spend-then-reset
    // order), not its own.
    ASSERT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Pretend this second search cost 1000ms of safepoint time - a mocked
    // FollowReferences call in this fixture takes ~0 real wall-clock time,
    // so this accessor stands in for what a real, expensive pass would have
    // accumulated into _search_pain_ms on its own.
    ReferenceChainsTestAccessor::setSearchPainMs(1000);

    // Restart #2: approved (nothing spent into _safepoint_pain_budget yet), and its
    // own spend() call debits 1000ms into the balance for the *next*
    // restart to contend with.
    ASSERT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #3, attempted immediately after restart #2's drain baseline:
    // at 1% refill, 1000ms of debt needs 100000ms (1e11ns) of elapsed
    // wall-clock time to clear - 1ns later is nowhere close.
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(3));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Well past the drain point - the debt has cleared, restart #3 proceeds.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2ULL + 200000000000ULL));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    tracker->stop();
}

// hasLeakSignal()'s OOM_URGENT_THRESHOLD_S fast path (referenceChains.h/.cpp):
// a heap-wide leak growing fast enough to project exhaustion sooner than the
// threshold must start a search immediately, without waiting for any klass
// to clear selectLeakCandidates()'s own per-klass ring-fill/hysteresis gate -
// this is the aggressive-leak gap GenerationsEnabledButNoCandidateBlocksFirstSearch
// above documents for the non-urgent case. Deliberately seeds no candidate at
// all (LivenessTracker::instance()->klassPopulationResetForTest() in SetUp
// leaves the population table empty) so this test can only pass via the
// heap-floor projection, never via selectLeakCandidates() falling back to a
// real candidate.
TEST_F(SearchRestartTest, UrgentOOMProjectionBypassesCandidateGate) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    // Same worked example as livenessTracker_ut.cpp's
    // SecondsToOOMTest.RisingFloorProjectsExpectedSeconds: 700MiB rise over
    // 7s against a 2800MiB max heap projects to 10s - comfortably under
    // OOM_URGENT_THRESHOLD_S (5 minutes).
    LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 10; i++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            1000 * MiB + (u64)i * 100 * MiB, (u64)i * SEC_NS);
    }

    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Phase 5 - correctness hardening: durability re-verification.
//
// These tests drive maybeUpgradeRootAttachedRootKind()/
// collectStaleRootKindEntriesForRotation() directly via
// ReferenceChainsTestAccessor rather than through a full
// IterateOverReachableObjects()-driven runPassManualWalk() pass: neither
// IterateOverReachableObjects nor FollowReferences-as-a-safepoint-pin is
// mocked in this file (see the fixture's own FollowReferences-only mock
// rationale above), and both methods are pure FrontierTable/queue logic with
// no JVMTI dependency of their own - the same rationale
// admitObject()/rootKindDurability() being free of any callback shape
// already established for this subsystem.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsBfsTest, StaleRootAttributionUpgradesOnRediscovery) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Synthetic stack-local root: admitted, root-attached (parent_tag == 0),
    // its owning frame has since "gone away" from the design doc's scenario
    // (nothing further to model here - the entry simply stays as-is until a
    // more durable root is discovered).
    jlong tag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, tag, /*parent_tag=*/0, /*depth=*/0,
        FrontierEntryState::EXPANDED, JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // A second, equally-or-less durable root discovery does not overwrite
    // the recorded root_kind.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_STACK_LOCAL, entry.root_kind);

    // A durable root (JNI global) attaching to the same object upgrades it.
    EXPECT_TRUE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_JNI_GLOBAL, entry.root_kind);
    EXPECT_EQ(0, entry.parent_tag); // still root-attached, unchanged

    // An even less durable root discovered afterwards cannot downgrade it.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_MONITOR));
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_JNI_GLOBAL, entry.root_kind);

    tracker->stop();
}

// Exercises the invariant conflict Phase 5 itself calls out: a non-root
// entry (parent_tag != 0) rediscovered as if via a root context must never
// have its root_kind overwritten - doing so would leave a non-zero root_kind
// on an entry nothing else treats as root-attached (referenceChains.h's
// FrontierEntry::root_kind comment), since this mutator never touches
// parent_tag. This is the edge-based, non-root-Y re-expansion case the
// option (a) resolution above exists for.
TEST_F(ReferenceChainsBfsTest, NonRootAttachedEntryNeverUpgraded) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Parent Y (root-attached) and child X, admitted the way frontier
    // re-expansion admits a non-root child: non-root
    // (parent_tag == Y's tag), root_kind == 0.
    jlong yTag = 1;
    jlong xTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, yTag, /*parent_tag=*/0, /*depth=*/0,
        FrontierEntryState::EXPANDED, JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, xTag, /*parent_tag=*/yTag, /*depth=*/1,
        FrontierEntryState::EXPANDED, /*root_kind=*/0));

    // Re-expanding Y rediscovers an edge to X (already tracked) - even if
    // this rediscovery is (incorrectly) attempted with a durable root_kind,
    // it must be rejected because X is not root-attached.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, xTag, JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(xTag, &entry));
    EXPECT_EQ(0, entry.root_kind);
    EXPECT_EQ(yTag, entry.parent_tag);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, RotationSelectsOnlyTransientExpandedRootAttachedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Eligible: root-attached, EXPANDED, transient root_kind.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Not eligible: durable root_kind.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    // Not eligible: transient but still FRONTIER, not yet EXPANDED.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    // Not eligible: transient root_kind but not root-attached.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, /*parent_tag=*/1, 1, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    // Eligible: root-attached, EXPANDED, transient (JNI local this time).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(10);
    std::sort(selected.begin(), selected.end());
    EXPECT_EQ((std::vector<jlong>{1, 5}), selected);

    // Selected tags are queued for re-expansion, exactly like an ordinary
    // admission would queue a newly-discovered tag.
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::priorityExpandSize());

    tracker->stop();
}

// N transient-root_kind entries, rotation size R: every entry must be
// selected at least once within ceil(N/R) calls, regardless of where the
// cursor happened to start.
TEST_F(ReferenceChainsBfsTest, RotationCoversAllEntriesWithinCeilNOverR) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const int N = 10;
    const int R = 3;
    for (jlong tag = 1; tag <= N; tag++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    }

    std::unordered_set<jlong> covered;
    int calls = (N + R - 1) / R;
    for (int i = 0; i < calls; i++) {
        std::vector<jlong> selected =
            ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(R);
        for (jlong tag : selected) {
            covered.insert(tag);
        }
    }
    EXPECT_EQ((size_t)N, covered.size());

    tracker->stop();
}

// collectStaleExpandedEntriesForRotation()'s own EXPANDED-only criterion is a
// strict superset of collectStaleRootKindEntriesForRotation()'s (which also
// requires parent_tag == 0 and a transient root_kind), and runPassManualWalk()
// calls the root-kind collector first, into the very same _priority_expand
// deque. Without a dedup check, a tag the root-kind collector already queued
// would be queued a second time by the EXPANDED-only sweep, wasting one of
// expandFrontier()'s per-entry batch slots on an already-EXPANDED tag every
// pass. This drives both collectors back-to-back, the way runPassManualWalk()
// does, and asserts _priority_expand ends up with no duplicate tags.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationDoesNotDuplicateRootKindSelection) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Eligible for both collectors: EXPANDED, root-attached, transient
    // root_kind - exactly the overlap collectStaleRootKindEntriesForRotation()
    // will pick up first.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Eligible only for the EXPANDED-only sweep: EXPANDED but not root-attached.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, /*parent_tag=*/1, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0));

    std::vector<jlong> root_kind_selected =
        ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(
            ReferenceChainsTestAccessor::rootKindRotationBudget());
    EXPECT_EQ((std::vector<jlong>{1}), root_kind_selected);

    std::vector<jlong> stale_expanded_selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
            ReferenceChainsTestAccessor::staleExpandedRotationBudget());
    // Tag 1 is already queued from the root-kind collector above and must not
    // be selected again; tag 2 is newly discovered by this sweep.
    EXPECT_EQ((std::vector<jlong>{2}), stale_expanded_selected);

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1, 2}), queued);
    std::unordered_set<jlong> unique_queued(queued.begin(), queued.end());
    EXPECT_EQ(queued.size(), unique_queued.size());

    tracker->stop();
}

// A tag left over in _priority_expand from a prior pass's truncated
// expandFrontier() batch (see expandFrontier()'s own "leave the batch at the
// front of the source queue for a later pass to retry" comment) must also be
// skipped by collectStaleExpandedEntriesForRotation() - not just tags queued
// by collectStaleRootKindEntriesForRotation() earlier in the same call.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationSkipsPreexistingQueueEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // Simulate a truncated batch from a prior pass still sitting at the front
    // of _priority_expand, without going through the root-kind collector at
    // all - the leftover entry alone must still be enough to suppress a
    // duplicate.
    ReferenceChainsTestAccessor::pushPriorityExpand(1);

    std::vector<jlong> stale_expanded_selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
            ReferenceChainsTestAccessor::staleExpandedRotationBudget());
    EXPECT_TRUE(stale_expanded_selected.empty());

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1}), queued);

    tracker->stop();
}

// End-to-end proof of the prof-analyzer-hotdog-jb pod's actual leak shape:
// a static-field-rooted collection (like ProfileAnalyzer.LEAK_BUFFER) whose
// owning node is admitted and fully EXPANDED once, then has a *new* element
// appended to it afterward - mirroring a Java List field being mutated in
// place, never reassigned, well after admitStaticFieldRoots()'s one-time
// sweep. The critical property under test is that this new element is
// discovered by collectStaleExpandedEntriesForRotation()'s rotation without
// the overall search ever reaching SearchState::COMPLETED - i.e. without
// requiring a full heap walk to finish, which on a multi-GiB heap can take
// far longer than the pod can tolerate between the leaked field's own
// growth events. A large distractor root chain (never fully drained within
// this test's bounded pass loops) keeps the search perpetually RUNNING so
// this property is exercised directly, not sidestepped by letting the
// search finish and then trivially re-discovering everything from scratch.
TEST_F(ReferenceChainsBfsTest, RotationDiscoversLateElementOfExpandedStaticFieldCollectionWithoutSearchCompleting) {
    Arguments args;
    // budget=8 -> rotation_reserved_budget = min(8/2, 272) = 4, ordinary = 4:
    // both slices non-zero, unlike a budget=1 pattern which would zero out
    // rotation's reserved slice entirely (min(0, 272) == 0).
    ASSERT_FALSE(args.parse("referencechains=true:hops=5000:budget=8:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int listNode = addNode();
    int seedChildNode = addNode();
    int lateChildNode = addNode();

    // Distractor chain: a long, independently root-seeded chain that never
    // fully drains within this test's bounded pass loops below, so the
    // overall search always has forward progress available and never
    // reaches SearchState::COMPLETED (nor NO_PROGRESS_PASS_LIMIT-triggered
    // ABANDONED) purely as a side effect of this test's own loop bounds.
    const int kDistractorNodes = 500;
    std::vector<int> distractor(kDistractorNodes);
    for (int i = 0; i < kDistractorNodes; i++) {
        distractor[i] = addNode();
    }

    // addClass() captures classNode's address in node_tags' backing storage -
    // must come after every addNode() call above (including the distractor
    // loop), or a later push_back reallocating node_tags would silently
    // leave this pointer dangling (indexOfNode() would then never match it).
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/GrowingListHolder;");

    script = {
        // listNode is retained only via classNode's static field - the same
        // shape as DiscoversObjectRetainedOnlyByStaticField above.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, listNode, -1},
        // listNode's one pre-existing element, discovered the first time
        // listNode itself is expanded.
        {JVMTI_HEAP_REFERENCE_FIELD, listNode, seedChildNode, -1},
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, distractor[0], -1},
    };
    for (int i = 0; i + 1 < kDistractorNodes; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, distractor[i], distractor[i + 1], -1});
    }

    // Phase 1: run passes until listNode has been fully expanded (its one
    // pre-existing child discovered), without ever letting the search
    // complete.
    bool truncated = true;
    FrontierEntry listEntry{};
    bool listExpanded = false;
    for (int i = 0; i < 200 && !listExpanded; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        jlong listTag = tags_ever_assigned[listNode];
        if (listTag != 0 && tracker->frontierTable()->lookup(listTag, &listEntry)
                && listEntry.state == FrontierEntryState::EXPANDED) {
            listExpanded = true;
        }
    }
    ASSERT_TRUE(listExpanded);
    ASSERT_NE(0, tags_ever_assigned[seedChildNode]);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Phase 2: simulate a new element appended to the leaking static
    // field's list *after* listNode's one-time expansion - the exact
    // "growing collection" shape found in the real pod's leak generator.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, listNode, lateChildNode, -1});

    for (int i = 0; i < 200 && tags_ever_assigned[lateChildNode] == 0; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    }

    // The late element was discovered purely via rotation re-expanding
    // listNode - and, critically, without the search ever completing (no
    // dependency on a full heap walk finishing).
    ASSERT_NE(0, tags_ever_assigned[lateChildNode]);
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(
            tags_ever_assigned[lateChildNode], &chain));
    FrontierEntry lateEntry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(
            tags_ever_assigned[lateChildNode], &lateEntry));
    EXPECT_EQ(tags_ever_assigned[listNode], lateEntry.parent_tag);

    tracker->stop();
}

// Proof of the fix for the actual prof-analyzer-hotdog-jb stall:
// collectStaleExpandedEntriesForRotation() (referenceChains.cpp) used to
// always rescan FrontierTable slots starting from tag 1, unlike its sibling
// collectStaleRootKindEntriesForRotation() which already carried its own
// persistent cursor. isQueuedForRotation()'s dedup check only looks at the
// CURRENT pass's _priority_expand (drained by expandFrontier() at the end of
// that same pass - see clearPriorityExpand()'s own comment), so without a
// cursor, later passes had no memory of what earlier passes already
// selected: whenever a real heap's frontier table held
// STALE_EXPANDED_ROTATION_BUDGET (256) or more low-tag EXPANDED entries that
// stay EXPANDED forever (long-lived infrastructure objects - exactly what
// the sweep's own comment says it favors), that population alone filled the
// sweep's 256-entry-per-pass cap on every single call, permanently starving
// any EXPANDED entry with a higher tag (e.g. a static field's collection
// node, admitted only once its owning class first loads, well after
// startup) of ever being re-queued - a bug proved directly, before the fix,
// by this same test (then named
// StaleExpandedRotationStarvesHighTagEntryBehindLowTagPopulation).
//
// _stale_expanded_rotation_cursor now makes collectStaleExpandedEntriesForRotation()
// resume from where the previous call left off instead of always restarting
// at tag 1, the same wrapping-cursor guarantee
// RotationCoversAllEntriesWithinCeilNOverR above already proves for
// collectStaleRootKindEntriesForRotation(): every entry, including one
// sitting behind an arbitrarily large low-tag population, gets a turn within
// ceil(table_size / max_count) calls.
//
// Driven directly against collectStaleExpandedEntriesForRotation() (the same
// unit-level style as RotationCoversAllEntriesWithinCeilNOverR above) rather
// than through a full JVMTI-mocked BFS walk: this property is intrinsic to
// the selection function's own tag-order scan, so it needs neither a real
// graph nor runPass()'s pacing/budget machinery to demonstrate.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationCoversHighTagEntryBehindLowTagPopulationWithinBoundedPasses) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const int lowTagBudget = ReferenceChainsTestAccessor::staleExpandedRotationBudget();
    // Comfortably above the 256-entry cap, so the low-tag population alone
    // would fill every sweep before an always-from-1 scan could ever reach
    // the high-tag entry below - mirrors a real multi-GiB heap's frontier
    // table, which accumulates far more than 256 long-lived, perpetually-
    // EXPANDED entries (bootstrap classes, caches, etc.) well before any one
    // leak-candidate class even loads.
    const int lowTagPopulation = lowTagBudget + 50;
    for (jlong tag = 1; tag <= lowTagPopulation; tag++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    }

    // The leak candidate's own owning node - e.g. LEAK_BUFFER's list, admitted
    // via a static field only once its class loads, well after the JVM's own
    // bootstrap population already occupies every low tag number.
    const jlong highTag = lowTagPopulation + 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, highTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    // Several simulated passes: each iteration mirrors one real pass -
    // collectStaleExpandedEntriesForRotation() runs once, then
    // clearPriorityExpand() mirrors expandFrontier() having drained whatever
    // it selected before the next pass's sweep resumes from the cursor.
    const int table_size = lowTagPopulation + 1;
    const int calls = (table_size + lowTagBudget - 1) / lowTagBudget;
    bool highTagSelected = false;
    std::unordered_set<jlong> covered;
    for (int pass = 0; pass < calls && !highTagSelected; pass++) {
        std::vector<jlong> selected =
            ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
                lowTagBudget);
        for (jlong tag : selected) {
            covered.insert(tag);
            if (tag == highTag) {
                highTagSelected = true;
            }
        }
        ReferenceChainsTestAccessor::clearPriorityExpand();
    }

    EXPECT_TRUE(highTagSelected)
        << "highTag was never selected within ceil(table_size / max_count) "
           "passes - the fix's coverage guarantee does not hold";
    EXPECT_EQ((size_t)table_size, covered.size());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// trackLeakAccumulation() - the admission-time hook (called from
// admitObject(), the single shared admission path) that aggregates by
// (leaf_class_tag, parent_class_tag) signature and by individual parent
// fanout - stable JVMTI class tags (classTagAllocator.h), not classMap
// dictionary ids, precisely because that dictionary can be compacted/
// regenerated independently, silently reassigning the same class a
// different id at different times (found via the external-process test -
// see class_tag's own comment, referenceChains.h). Driven directly, pure
// FrontierTable/map logic with no JVMTI dependency of its own.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationAggregatesBySignatureAndFanout) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    constexpr u32 kParent1Klass = 100, kParent2Klass = 200;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong parent1Tag = 1, parent2Tag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parent1Tag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParent1Klass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parent2Tag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParent2Klass));

    // 3 children of the watched leaf klass under parent1, 1 under parent2 -
    // each call simulates one admission (the childTag argument is only used
    // by production code for logging/future use, not read by this method).
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 10);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 11);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 12);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent2Tag, 20);

    EXPECT_EQ(3u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParent1Klass));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParent2Klass));
    EXPECT_EQ(3u, ReferenceChainsTestAccessor::leakParentFanout(parent1Tag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parent2Tag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsUnwatchedKlass) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, /*class_tag=*/100));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, /*class_tag=*/555,
                                                        parentTag, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsRootAttachedChild) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});

    // parent_tag == 0 - a root-attached leaf itself, nothing to attribute a
    // container to.
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, 987, /*parent_tag=*/0, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsWhenParentNotFound) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});

    // parent_tag=99 was never inserted - graceful no-op, not a crash.
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, 987, /*parent_tag=*/99, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

// Proof of the actual bug this design was found fixing: the classMap
// dictionary id (referrer_klass) for the exact same class can differ
// depending on which subsystem/generation resolved it (see class_tag's own
// comment, referenceChains.h, for the real-world case - "[B" resolving to
// two different classMap ids for LivenessTracker vs. ReferenceChainTracker).
// Matching must work via class_tag regardless of what referrer_klass says.
TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationMatchesByClassTagEvenWhenReferrerKlassDiffers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafClassTag = 987;
    constexpr u32 kParentClassTag = 100;
    // Deliberately different, "wrong" classMap ids - simulating exactly the
    // compaction/regeneration scenario that broke referrer_klass-based
    // matching. If matching used referrer_klass at all, this test would fail.
    constexpr u32 kParentStaleReferrerKlass = 555555;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafClassTag});

    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, kParentStaleReferrerKlass,
        kParentClassTag));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafClassTag,
                                                        parentTag, 10);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafClassTag,
                                                                   kParentClassTag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

// ---------------------------------------------------------------------------
// collectLeakAccumulationCandidatesForRotation() - the two-tier design
// itself (see its own header comment, referenceChains.cpp, for the full
// rationale). Driven directly against the aggregation state
// trackLeakAccumulation() above populates, the same unit-level style as the
// other rotation collectors.
// ---------------------------------------------------------------------------

// The central discriminating test for the whole design (per the "ubiquitous
// common leaf class held by many small unrelated parents" concern this
// design exists to solve): a signature with a LARGE but FLAT total (many
// unrelated parents, e.g. a common leaf class scattered across a real
// classpath) must NOT outrank a signature with a SMALLER but GROWING total
// (the actual leak) once a growth history exists - retained-size-style
// ranking alone would pick the wrong one every time.
TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationPrioritizesGrowingSignatureOverLargeFlatOne) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    constexpr u32 kGrowingParentKlass = 100;  // signature A: the real leak
    constexpr u32 kUbiquitousParentKlass = 999; // signature B: common, but flat
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Signature A: one parent, growing.
    jlong growingParentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, growingParentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kGrowingParentKlass));

    // Signature B: 20 distinct, unrelated parents, each holding just 1-2
    // instances of the same common leaf klass - a much LARGER total than A,
    // but it will not grow between passes.
    constexpr int kUbiquitousParentCount = 20;
    std::vector<jlong> ubiquitousParentTags;
    for (int i = 0; i < kUbiquitousParentCount; i++) {
        jlong tag = 100 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kUbiquitousParentKlass));
        ubiquitousParentTags.push_back(tag);
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, tag, 1000 + i);
    }
    // Pass 1: A has fanout 5, B has total 20 (20 parents x 1 each) - B is
    // larger. First-ever call has no prior snapshot, so both deltas equal
    // their totals; B legitimately wins this one call (nothing to compare
    // growth against yet).
    for (int i = 0; i < 5; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            growingParentTag, 2000 + i);
    }
    ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
        ReferenceChainsTestAccessor::leakAccumulationRotationBudget());

    // Pass 2: B stays exactly flat (no new admissions); A grows from 5 to 8.
    for (int i = 0; i < 3; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            growingParentTag, 3000 + i);
    }
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
            ReferenceChainsTestAccessor::leakAccumulationRotationBudget());

    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ(growingParentTag, selected[0])
        << "the growing signature's parent must be selected, even though "
           "the flat-but-larger signature has a much bigger absolute total";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationRanksByFanoutWithinWinningSignature) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong lowFanoutTag = 1, highFanoutTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, lowFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, highFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, lowFanoutTag, 10);
    for (int i = 0; i < 5; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            highFanoutTag, 20 + i);
    }

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(highFanoutTag, selected[0]) << "higher fanout ranks first";
    EXPECT_EQ(lowFanoutTag, selected[1]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationRespectsMaxCountAndDedup) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong tag1 = 1, tag2 = 2, tag3 = 3;
    for (jlong tag : {tag1, tag2, tag3}) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, tag, 10);
    }
    // tag2 already queued from an earlier collector this same pass - must
    // be skipped even though it qualifies structurally.
    ReferenceChainsTestAccessor::pushPriorityExpand(tag2);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
            /*max_count=*/1);
    EXPECT_EQ(1u, selected.size()) << "capped at max_count";
    EXPECT_NE(tag2, selected[0]) << "already-queued tag must not be re-selected";

    tracker->stop();
}

// Reversed on round-4 pod evidence (ev-leaktag-onpod-round4): the previous
// EXPANDED-only selection made the targeted tier select ZERO every pass
// on a live leak - the growing holders are un-expanded FRONTIER-state
// backlog entries that the starved pending lane never reaches (a 127k
// backlog at ~120-200 objects/min). A FRONTIER-state parent must be
// selected AND placed at the head of the priority lane so the next
// expandFrontier() batch reaches it ahead of the stale re-walks already
// queued (the same pod's priority deque held ~1016 entries).
TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationSelectsUnexpandedFrontierParentAheadOfBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Stale re-walks already sitting in the priority lane (push_back, as
    // the other two collectors do).
    ReferenceChainsTestAccessor::pushPriorityExpand(900);
    ReferenceChainsTestAccessor::pushPriorityExpand(901);

    jlong notYetExpandedTag = 1, expandedLowFanoutTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, notYetExpandedTag, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, expandedLowFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    for (int i = 0; i < 10; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            notYetExpandedTag, 10 + i);
    }
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                        expandedLowFanoutTag, 100);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(notYetExpandedTag, selected[0])
        << "the FRONTIER-state parent qualifies and outranks the "
           "lower-fanout EXPANDED one";
    EXPECT_EQ(expandedLowFanoutTag, selected[1]);

    std::vector<jlong> queue = ReferenceChainsTestAccessor::priorityExpandContents();
    ASSERT_GE(queue.size(), 4u);
    EXPECT_EQ(notYetExpandedTag, queue[0])
        << "the targeted un-expanded holder must JUMP the backlog, not "
           "queue behind the stale re-walks";
    EXPECT_EQ(expandedLowFanoutTag, queue[1])
        << "selection order must be preserved at the head (fanout rank)";
    EXPECT_EQ(900, queue[2]);
    EXPECT_EQ(901, queue[3]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationReturnsEmptyWhenNothingHasGrownSincePreviousPass) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 10);

    // First call establishes the baseline (delta == total, since there is no
    // prior snapshot) and selects it.
    std::vector<jlong> firstPass =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(1u, firstPass.size());
    ReferenceChainsTestAccessor::clearPriorityExpand();

    // Second call, nothing new admitted - delta is now 0 for every
    // signature, so nothing should be selected.
    std::vector<jlong> secondPass =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    EXPECT_TRUE(secondPass.empty())
        << "no signature grew since the previous pass's snapshot";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationReturnsEmptyWhenNoSignaturesTracked) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    EXPECT_TRUE(selected.empty());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// seedLeakAccumulationForNewlyWatchedKlass() - the cold-start fix: retroactively
// seeds the aggregation from entries ALREADY admitted before a klass_id
// started being watched, since trackLeakAccumulation() alone only ever sees
// admissions happening after watching starts, and the container that
// actually needs re-expansion is typically already fully admitted by then
// (found via the external-process test: the delegate ArrayList sits one hop
// below the root-attached wrapper, and admitStaticFieldRoots()'s own sweep
// admits both in the same call, long before any leak signal can plausibly
// have fired).
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationPopulatesFromAlreadyAdmittedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    // Entries inserted directly (as if admitted by an earlier pass), with no
    // watched klass_id set at all yet at insertion time - trackLeakAccumulation()
    // was never called for any of these.
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    for (int i = 0; i < 4; i++) {
        jlong childTag = 10 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, childTag, parentTag, 1, FrontierEntryState::EXPANDED,
            /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    }
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount())
        << "nothing tracked yet - trackLeakAccumulation() was never called";

    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);

    EXPECT_EQ(4u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParentKlass));
    EXPECT_EQ(4u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationSkipsNonMatchingAndNonExpandedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kOtherKlass = 555, kParentKlass = 100;
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    // Wrong class - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, parentTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kOtherKlass));
    // Right class, but still FRONTIER (not yet EXPANDED) - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 11, parentTag, 1, FrontierEntryState::FRONTIER,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    // Right class, root-attached (no real parent) - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 12, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kLeafKlass));

    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationComposesWithOngoingIncrementalUpdates) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, parentTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));

    // Retroactive seed sees the one pre-existing child.
    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    // A genuinely new admission after watching starts must add on top of the
    // retroactive baseline, not reset or double it.
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 11);

    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParentKlass));

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Smoke test simulating the hotdog pod conditions that starved BFS:
//
// 1. GetObjectsWithTags quadratic bottleneck: a large frontier backlog
//    makes each GetObjectsWithTags call expensive. The self-calibrating
//    adaptive batch_size must keep it bounded.
//
// 2. Shared deadline bug: the static-field sweep's FollowReferences ate
//    the entire per-pass wall-clock deadline, leaving expand with zero
//    time. The deadline split gives each sub-operation its own fresh
//    deadline.
//
// 3. Rolling resume: when FollowReferences truncates mid-batch (budget
//    exhausted), the fully-processed entries must be popped (mark
//    EXPANDED) and only the partially-processed + unvisited entries left
//    for retry.
//
// This test builds a graph with a static-field root leading to a chain of
// objects (simulating the leaking collection), plus a small set of
// distractor roots to keep the search RUNNING. It runs passes with a
// small budget so expand truncates mid-batch, then verifies the rolling
// resume and progress properties.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsBfsTest, RollingResumePopsProcessedEntriesOnTruncatedBatch) {
    Arguments args;
    // budget=4: small enough that expand truncates mid-batch after admitting
    // a few children. firstpassbudget=1000: large enough to enumerate all
    // roots in the first pass without truncating root enum.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=5000:budget=4:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A static-field root: classNode -> listNode (the leaking collection).
    int classNode = addNode();
    int listNode = addNode();

    // A chain of 20 children hanging off listNode. With budget=4, the
    // callback admits 4 children then returns JVMTI_VISIT_ABORT
    // (BUDGET_EXHAUSTED), truncating mid-batch.
    constexpr int kChainLen = 20;
    std::vector<int> chainNodes(kChainLen);
    for (int i = 0; i < kChainLen; i++) {
        chainNodes[i] = addNode();
    }

    // Distractor roots: 20 independent JNI-global roots, each with one child.
    // Enough to keep the search RUNNING but small enough to drain quickly.
    constexpr int kDistractors = 20;
    std::vector<int> distractorRoots(kDistractors);
    std::vector<int> distractorChildren(kDistractors);
    for (int i = 0; i < kDistractors; i++) {
        distractorRoots[i] = addNode();
        distractorChildren[i] = addNode();
    }

    // addClass() must come after all addNode() calls.
    addClass((void *)&node_tags[classNode], "Lcom/rc/SmokeTestHolder;");

    script = {
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, listNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, listNode, chainNodes[0], -1},
    };
    for (int i = 0; i + 1 < kChainLen; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, chainNodes[i], chainNodes[i + 1], -1});
    }
    for (int i = 0; i < kDistractors; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, distractorRoots[i], -1});
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, distractorRoots[i], distractorChildren[i], -1});
    }

    // Phase 1: run passes until listNode is admitted via the static-field sweep.
    bool truncated = true;
    jlong listTag = 0;
    for (int i = 0; i < 200 && listTag == 0; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        listTag = tags_ever_assigned[listNode];
    }
    ASSERT_NE(0, listTag) << "listNode was never admitted to the frontier";

    // Phase 2: run passes until listNode is expanded (rolling resume pops it).
    for (int i = 0; i < 200; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        FrontierEntry entry{};
        if (frontier->lookup(listTag, &entry) &&
            entry.state == FrontierEntryState::EXPANDED) {
            break;
        }
    }
    FrontierEntry listEntry{};
    ASSERT_TRUE(frontier->lookup(listTag, &listEntry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, listEntry.state)
        << "listNode should be EXPANDED after rolling resume popped it";

    // Verify some chain children were admitted.
    int admittedChildren = 0;
    for (int i = 0; i < kChainLen; i++) {
        if (tags_ever_assigned[chainNodes[i]] != 0) admittedChildren++;
    }
    EXPECT_GT(admittedChildren, 0)
        << "No chain children were admitted — expand never ran";

    // Phase 3: run more passes until all chain children are admitted.
    for (int i = 0; i < 500 && admittedChildren < kChainLen; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        admittedChildren = 0;
        for (int j = 0; j < kChainLen; j++) {
            if (tags_ever_assigned[chainNodes[j]] != 0) admittedChildren++;
        }
    }
    EXPECT_EQ(kChainLen, admittedChildren)
        << "Not all chain children were admitted within bounded passes";

    tracker->stop();
}

// Verify the AIMD adaptive batch_size: with the per-call EMA over the CPU
// budget, expandFrontier should multiplicatively decrease the batch; under
// the budget it should additively increase toward the cap. The mock
// GetObjectsWithTags is instant (no real tag-map cost), so we drive the EMA
// by hand and verify the AIMD response, not the timing.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchSizeProportionalToWindow) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Adaptive-batch state is zeroed by reset() (SetUp) but zeroed here too
    // for the same reason as before: exact per-phase arithmetic below.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0);
    ReferenceChainsTestAccessor::setGotwBatchSize(0);
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);

    // Seed a frontier root manually (mirrors PollWatchedTargetsTest's
    // seeding style): node carries frontier tag 1, pending expansion has
    // exactly that tag. No runPass() - a pass would drain the tiny graph to
    // COMPLETED and release all tags, and its rotation phase adds extra
    // GetObjectsWithTags calls, both of which break per-call arithmetic.
    // The script stays empty until the admission-sanity phase below, so
    // each expandFrontier() drive runs exactly one batch (one control
    // update) and admits nothing.
    int rootNode = addNode();
    int childNode = addNode();
    node_tags[rootNode] = 1;
    ASSERT_TRUE(tracker->frontierTable()->insert(
        1, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    int edges = 0;
    const u64 budget = ReferenceChainsTestAccessor::gotwCpuBudgetNs();

    // --- Populate phase: first GetObjectsWithTags call. The EMA should be
    // non-zero afterwards, and the near-zero mock call time means the
    // window (nominal budget, no deadline) fits ~unbounded many calls -
    // the proportion scales the batch all the way to the cap.
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0u, ReferenceChainsTestAccessor::gotwEmaCallNs())
        << "per-call EMA should be populated after first GetObjectsWithTags";
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMaxBatch(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "near-free call should scale the batch to the cap";

    // --- Shrink phase: EMA at 2x the window with no deadline -> batch
    // halves (512 x 1 / 1.6 after the EMA update).
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget * 2);
    ReferenceChainsTestAccessor::setGotwBatchSize(512);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // EMA after the call: 2x window x 0.8 + mock elapsed/5 - slightly
    // above 1.6x window, so the exact expectation is computed from the
    // actual EMA the same way the control law does (window = nominal
    // budget, no deadline): next = 512 x window / ema.
    EXPECT_EQ((size_t)(512ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA at ~1.6x the window should scale the batch to 512/1.6";

    // --- Grow phase: EMA at half the window -> batch scales up 2.5x,
    // i.e. the floor-dominated regime GROWS the batch (the whole point of
    // the proportional law - the old AIMD could not grow past a fixed
    // budget even when bigger batches were nearly free).
    ReferenceChainsTestAccessor::setGotwBatchSize(64);
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget / 2);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // Same computation from the actual post-call EMA (~0.4x window):
    // next = 64 x window / ema.
    EXPECT_EQ((size_t)(64ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA under the window should scale the batch up proportionally";

    // --- Deadline-window phase: with a live pass deadline the window is the
    // REMAINING time, not the nominal budget. A deadline 10x the budget out
    // with EMA ~ 1x budget scales the batch 10x/0.8 - past the cap, so the
    // clamp holds it at GOTW_MAX_BATCH (robust to the nanoseconds the call
    // itself consumes).
    ReferenceChainsTestAccessor::setPassDeadlineNs(
        OS::nanotime() + budget * 10);
    ReferenceChainsTestAccessor::setGotwBatchSize(64);
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMaxBatch(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "a wide remaining deadline should grow the batch to the cap";
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);

    // --- Admission sanity: expansion still walks the graph. Root -> child
    // edge, one more drive, child must be admitted.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, rootNode, childNode, -1});
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0, tags_ever_assigned[childNode])
        << "expandFrontier failed to admit childNode with adaptive batch_size";

    tracker->stop();
}

// gotwWindowNs() backlog-pressure widening, unit level: the pod regime is
// a remaining pass window (~10ms) smaller than the measured per-call floor
// (~22-40ms at a 242k-entry tag map), against a lane 127k deep. In that
// regime the previous window math handed the proportional law a window
// smaller than one unavoidable call, collapsing the batch to
// GOTW_MIN_BATCH forever (batch=8 live on every call while the backlog
// drained at ~120-200 objects/min). The widening makes the law size the
// batch UP instead - but ONLY under real backlog depth, so rotation
// fast-lane batches stay deadline-sized.
TEST_F(ReferenceChainsBfsTest, GotwWindowWidensOnlyUnderBacklogPressure) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const u64 budget = ReferenceChainsTestAccessor::gotwCpuBudgetNs();
    const size_t depth = ReferenceChainsTestAccessor::gotwBacklogMinDepth();
    const u64 mult = ReferenceChainsTestAccessor::gotwBacklogWindowMult();
    const u64 floor = budget * 2; // any floor above the nominal window

    // No deadline and no EMA yet: the nominal budget window.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0);
    EXPECT_EQ(budget, ReferenceChainsTestAccessor::gotwWindowNs(0, depth));

    ReferenceChainsTestAccessor::setGotwEmaCallNs(floor);

    // Floor above the remaining window but a SHALLOW lane: no widening -
    // the remaining window stands (rotation fast-lane stays cheap).
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::gotwWindowNs(1, 1));

    // Floor above the remaining window and a DEEP lane: widened to
    // EMA x mult, never below the remaining window itself.
    EXPECT_EQ(floor * mult,
              ReferenceChainsTestAccessor::gotwWindowNs(1, depth));

    // Floor BELOW the remaining window: no widening even at depth -
    // the ordinary proportional law already fits the call in the window.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget / 2);
    EXPECT_EQ(budget,
              ReferenceChainsTestAccessor::gotwWindowNs(budget, depth));
    ReferenceChainsTestAccessor::setGotwEmaCallNs(floor);

    // Floor above the NOMINAL window (deadline already passed, the exact
    // pod's post-call state) at depth: still widened - the floor is paid
    // by the next call regardless, so the batch must amortize it.
    EXPECT_EQ(floor * mult,
              ReferenceChainsTestAccessor::gotwWindowNs(0, depth));

    tracker->stop();
}

// The widened window in action through the real control loop: one
// GetObjectsWithTags call whose floor (simulated by the mock's busy-wait)
// exceeds both the remaining pass deadline and the nominal window, with
// a backlog deeper than GOTW_BACKLOG_MIN_DEPTH, must GROW the calibrated
// batch (calib x mult, exactly - the window scales with the measured EMA)
// instead of collapsing it to GOTW_MIN_BATCH. This is the round-4 pod
// failure reproduced mechanically: pre-widening, next = calib x nominal /
// ema < calib clamps to MIN forever.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchGrowsWhenFloorExceedsWindowUnderDeepBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A pass deadline a fraction of the simulated per-call floor: the call
    // overruns it (exactly the pod's 10ms window vs 22-40ms floor), so after
    // the call the loop's deadline check stops the invocation with ONE
    // control update - deterministic arithmetic for the assertion below.
    gotw_delay_ns = ReferenceChainsTestAccessor::gotwCpuBudgetNs(); // 25ms floor
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + 5000000ULL);
    ReferenceChainsTestAccessor::setGotwBatchSize(ReferenceChainsTestAccessor::gotwMinBatch());
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0); // seeded by the call below

    // A pending lane deep enough to cross GOTW_BACKLOG_MIN_DEPTH. The tags
    // are unresolvable (never assigned to a node): each batch resolves
    // nothing, which is fine - this test drives the control law, not
    // admissions.
    const size_t depth = ReferenceChainsTestAccessor::gotwBacklogMinDepth() + 1;
    for (size_t i = 0; i < depth; i++) {
        ReferenceChainsTestAccessor::pushPendingExpandForTest(
            (jlong)(1000000 + i));
    }

    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);

    // EMA after the call = the busy-wait floor (~25ms). The pass deadline is
    // long past, so the window is widened to EMA x GOTW_BACKLOG_WINDOW_MULT,
    // and the control law computes calib x window / ema = calib x mult -
    // exactly, because the window is a whole multiple of the same EMA it
    // divides by.
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMinBatch() *
                  ReferenceChainsTestAccessor::gotwBacklogWindowMult(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "the floor-dominated deep-backlog regime must GROW the batch, "
           "not clamp it to GOTW_MIN_BATCH";

    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    gotw_delay_ns = 0;
    tracker->stop();
}

// FAIR-SHARE DRAIN persistence: the lane toggle must survive across
// expandFrontier() invocations. With per-invocation deadlines bounding an
// invocation to a single batch (the production regime: one ~25-30ms
// GetObjectsWithTags call of a 50ms window), a per-invocation reset to
// "priority first" made priority win EVERY invocation and the ordinary
// pending lane was never drained - observed live on hotdog (pending grew
// 109k->113k over 260 passes, every call edges=0 stale re-walks). Here:
// invocation 1 drains the priority lane, the toggle flips to pending;
// priority is refilled (rotation would) and invocation 2 must still drain
// the PENDING lane despite priority being non-empty.
TEST_F(ReferenceChainsBfsTest, FairShareLaneAlternationPersistsAcrossInvocations) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int rootNode = addNode();
    int otherRoot = addNode();
    // Two live boundary objects: tag 1 in pending, tag 2 in priority.
    node_tags[rootNode] = 1;
    node_tags[otherRoot] = 2;
    ASSERT_TRUE(tracker->frontierTable()->insert(
        1, 0, 1, 0, FrontierEntryState::EDGE));
    ASSERT_TRUE(tracker->frontierTable()->insert(
        2, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::pushPriorityExpand(2);
    int edges = 0;

    // Mock GetObjectsWithTags calls are ~free, so without a deadline a
    // single expandFrontier() invocation would drain BOTH lanes in one
    // loop. A delayed mock call (gotw_delay_ns below) plus a deadline set
    // to a fraction of that delay bounds each invocation to exactly ONE
    // batch: the first iteration's top-of-loop check passes (the deadline
    // is ~200us away), the delayed call burns past it, and the second
    // iteration's check breaks - the production regime, where one real
    // ~25-30ms call consumes a 50ms window.
    gotw_delay_ns = 1 * 1000 * 1000; // 1ms
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + 200 * 1000);

    // Invocation 1: priority first (the standing preference).
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::priorityExpandSize())
        << "first invocation should drain the priority lane";
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::pendingExpandSize())
        << "first invocation must leave the pending lane for the next one";
    EXPECT_FALSE(ReferenceChainsTestAccessor::expandLanePreferPriority());

    // Rotation refills the priority lane; invocation 2 must STILL prefer
    // the pending lane - the toggle persists, it is not reset per call.
    ReferenceChainsTestAccessor::pushPriorityExpand(2);
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + 200 * 1000);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingExpandSize())
        << "second invocation should drain the pending lane";
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::priorityExpandSize())
        << "second invocation must leave the refilled priority lane alone";
    EXPECT_TRUE(ReferenceChainsTestAccessor::expandLanePreferPriority());

    tracker->stop();
}
// FANOUT HYGIENE: a _leak_parent_fanout entry whose parent no longer
// resolves in the frontier (pruned: dead object, or a search-restart wipe)
// can never be re-walked, so collectStaleExpandedEntriesForRotation() must
// erase it during selection rather than skip it forever - without the
// erase, the fanout grows monotonically with corpses (observed live at
// ~11k entries of overwhelmingly-dead old backing arrays), which both
// bloats the selection scan and turns the fanout cursor's lap arithmetic
// into mostly wasted skips.
TEST_F(ReferenceChainsBfsTest, StaleRotationEvictsDeadFanoutParents) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    constexpr u32 kLeafKlass = 987;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});
    FrontierTable *frontier = tracker->frontierTable();

    // Live fanout parent 1 and dead fanout parent 5 (frontier entry pruned).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0,
        /*class_tag=*/42));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0,
        /*class_tag=*/43));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, 1, 10);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, 5, 20);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(1));
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(5));

    frontier->clear(5); // parent 5's object died / search restart pruned it

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(4);
    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakParentFanout(5))
        << "dead fanout parent must be erased during selection";
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(1))
        << "live fanout parent must survive";

    tracker->stop();
}


// Leak-tag interception (design A + C): an object pre-tagged with a leak tag
// (as LivenessTracker::tagLeakInstances() would have set on a tracked leaking
// instance) must be admitted by converting the leak tag to a frontier tag,
// with the leak tag preserved in the frontier entry so buildChainEvent()
// emits it as target_tag - the ReferenceChain <-> HeapLiveObject correlation
// key. An untagged sibling of the same class must get an ordinary admit with
// no leak tag.
TEST_F(ReferenceChainsBfsTest, LeakTagInterceptionConvertsToFrontierTagAndCorrelates) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();

    int rootNode = addNode();
    int leakChild = addNode();
    int plainChild = addNode();
    // Simulate tagLeakInstances(): the tracked leaking instance already
    // carries a leak tag; the sibling does not.
    node_tags[leakChild] = leak_tag;
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, rootNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, rootNode, leakChild, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, rootNode, plainChild, -1},
    };

    // A single pass drains this tiny graph to completion, and a completed
    // search releases all JVMTI tags (releaseSearchTags(), "tagsReleased"
    // in runPass's own log) - so read the tags from tags_ever_assigned,
    // which records each tag at assignment time and is never reset (see
    // its own comment), not from node_tags (which reads 0 after release).
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));

    // The leak-tagged child's tag was REPLACED by a frontier tag (small
    // positive, outside the leak range).
    jlong leak_ftag = tags_ever_assigned[leakChild];
    ASSERT_NE(leak_tag, leak_ftag)
        << "leak tag was never intercepted - BFS did not reach the object";
    ASSERT_GT(leak_ftag, 0);
    EXPECT_LT(leak_ftag, leak_tag) << "frontier tag must be outside leak range";

    // The frontier entry preserves the leak tag for correlation.
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(leak_ftag));

    // The untagged sibling got an ordinary admit: frontier tag assigned, but
    // no leak tag stored.
    jlong plain_ftag = tags_ever_assigned[plainChild];
    ASSERT_GT(plain_ftag, 0);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::frontierLeakTag(plain_ftag));

    // Design C: buildChainEvent() reports the leak tag as target_tag for the
    // leak-tagged instance, and the plain frontier tag for the sibling.
    ReferenceChainEvent event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, leak_ftag, &event));
    EXPECT_EQ((u64)leak_tag, event._target_tag)
        << "chain target tag must be the leak tag (correlation key)";
    EXPECT_GE(event._depth, 1u) << "leak child sits behind the root, not at it";

    ReferenceChainEvent plain_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, plain_ftag, &plain_event));
    EXPECT_EQ((u64)plain_ftag, plain_event._target_tag)
        << "untagged instance must keep the frontier tag as target tag";

    tracker->stop();
}

// Candidate-scoped reach, prong 1 (walkCandidateThreadLocals()): a leak
// held through the leaking thread's ThreadLocalMap must be intercepted
// with its full chain by ONE bounded walk from the Thread object, no
// matter what the ordinary BFS backlog state is - and the walk's gates
// must keep it off the Thread's non-thread-local fields entirely.
TEST_F(ReferenceChainsBfsTest, ThreadWalkDescendsOnlyThreadLocalMapAndInterceptsLeak) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // The classes descendFromAnchor()'s resolutions look up by FindClass
    // name (see registerClassForFindClass' own comment) + the scripted
    // graph's own classes. resolveLoadedClasses() below tags every
    // registered class, which is what makes the class-tag gates resolvable.
    void *threadCls = (void *)0x3001, *tlmapCls = (void *)0x3002,
         *loaderCls = (void *)0x3003, *holderCls = (void *)0x3004,
         *chunkCls = (void *)0x3005;
    int tlmapIdx =
        registerClassForFindClass(tlmapCls,
                                  "java/lang/ThreadLocal$ThreadLocalMap",
                                  "Ljava/lang/ThreadLocal$ThreadLocalMap;");
    int loaderIdx =
        registerClassForFindClass(loaderCls, "java/lang/ClassLoader",
                                  "Ljava/lang/ClassLoader;");
    registerClassForFindClass(threadCls, "java/lang/Thread",
                               "Ljava/lang/Thread;");
    int holder = addClass(holderCls, "Lcom/rc/descendwalk/Holder;");
    int chunk = addClass(chunkCls, "Lcom/rc/descendwalk/LeakChunk;");
    thread_class = threadCls;
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);

    int threadNode = addNode();
    int threadNode2 = addNode(); // second candidate thread: fresh-admission path
    int tlmapNode = addNode();
    int loaderNode = addNode();   // Thread's contextClassLoader: anchor gate
    int loaderNode2 = addNode();  // a ClassLoader below the gate: no-descend
    int holderNode = addNode();
    int leakChunk = addNode();

    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();
    node_tags[leakChunk] = leak_tag;

    // Topological order (mock_FollowReferences replays edges in script
    // order, expanding only refs the production callback said to descend
    // into).
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, threadNode, tlmapNode,
         /*class_idx=*/-1},
        {JVMTI_HEAP_REFERENCE_FIELD, threadNode, loaderNode,
         /*class_idx=*/-1},
        {JVMTI_HEAP_REFERENCE_FIELD, tlmapNode, holderNode, holder},
        {JVMTI_HEAP_REFERENCE_FIELD, tlmapNode, loaderNode2,
         /*class_idx=*/-1},
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, leakChunk, chunk},
    };
    // The anchor gate compares the REFEREE's class tag, so the thread
    // edges' class_idx values matter: the tlmap edge carries
    // ThreadLocalMap's tag, and the loader edges ClassLoader's.
    script[0].class_idx = tlmapIdx;
    script[1].class_idx = loaderIdx;
    script[3].class_idx = loaderIdx;

    // The first thread walks the REUSE path: its Thread object is already
    // admitted (root-attached THREAD entry + JVMTI tag) exactly as it is
    // in production after the first walk pass or root enumeration. The
    // mock keeps the scripted tag array (node_tags, what callbacks see as
    // tag_ptr) separate from the pointer-keyed tag map (what GetTag/SetTag
    // see), so the pre-anchored tag must be mirrored into both.
    FrontierTable *frontier = tracker->frontierTable();
    jlong anchor_tag =
        tracker->tagObject(&mock_jvmti,
                           reinterpret_cast<jobject>(&node_tags[threadNode]));
    ASSERT_GT(anchor_tag, 0);
    node_tags[threadNode] = anchor_tag;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, anchor_tag, 0, 0, FrontierEntryState::FRONTIER,
        (u8)JVMTI_HEAP_REFERENCE_THREAD));

    // Two candidate slots, two qualifying tids: tid 777's thread is
    // pre-anchored (reuse path), tid 778's is untagged (fresh-admission
    // path - GetObjectClass + tagObject + insert, the path a never-walked
    // thread takes in production).
    jint tids0[] = {777};
    jint tids1[] = {778};
    ReferenceChainsTestAccessor::seedCandidateSlotForTest(
        /*slot=*/0, /*klass_id=*/6, tids0, 1);
    ReferenceChainsTestAccessor::seedCandidateSlotForTest(
        /*slot=*/1, /*klass_id=*/6, tids1, 1);
    tracker->registerThreadObject(
        &mock_jni, 777, reinterpret_cast<jthread>(&node_tags[threadNode]));
    tracker->registerThreadObject(
        &mock_jni, 778, reinterpret_cast<jthread>(&node_tags[threadNode2]));

    int edges = 0;
    ReferenceChainsTestAccessor::walkCandidateThreadLocalsForTest(
        &mock_jvmti, &mock_jni, 1000, &edges);

    // The ThreadLocalMap-held chain was admitted end-to-end and the
    // leak-tagged chunk was intercepted (tag replaced by a frontier tag,
    // leak tag preserved for correlation).
    jlong thread_ftag = anchor_tag;
    jlong tlmap_ftag = tags_ever_assigned[tlmapNode];
    ASSERT_GT(tlmap_ftag, 0) << "anchor gate did not descend into ThreadLocalMap";
    jlong holder_ftag = tags_ever_assigned[holderNode];
    ASSERT_GT(holder_ftag, 0) << "walk did not descend below ThreadLocalMap";
    jlong chunk_ftag = tags_ever_assigned[leakChunk];
    ASSERT_NE(chunk_ftag, leak_tag)
        << "leak-tagged chunk under the ThreadLocalMap was never intercepted";
    ASSERT_GT(chunk_ftag, 0);
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(chunk_ftag));

    // Chain shape: Thread (root-attached, THREAD root kind) -> ThreadLocalMap
    // -> holder -> chunk.
    FrontierEntry thread_entry{};
    ASSERT_TRUE(frontier->lookup(thread_ftag, &thread_entry));
    EXPECT_EQ(0, thread_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread_entry.root_kind);
    FrontierEntry chunk_entry{};
    ASSERT_TRUE(frontier->lookup(chunk_ftag, &chunk_entry));
    EXPECT_EQ(holder_ftag, chunk_entry.parent_tag);
    EXPECT_EQ(3u, chunk_entry.depth);

    // The gates kept the walk off the metadata branches: neither the
    // Thread's own contextClassLoader edge (anchor gate) nor a ClassLoader
    // below ThreadLocalMap (no-descend gate) was admitted.
    EXPECT_EQ(0, tags_ever_assigned[loaderNode])
        << "anchor gate must not admit the Thread's non-ThreadLocalMap fields";
    EXPECT_EQ(0, tags_ever_assigned[loaderNode2])
        << "no-descend gate must not admit fat-metadata classes below the anchor";

    // The second thread took the fresh-admission path (no prior tag/entry):
    // its Thread object was admitted root-attached with the THREAD root
    // kind. (Its scripted tag array entry was never set, so the minted tag
    // is read back through the pointer-keyed tag map via getTag.)
    jlong thread2_ftag = ReferenceChainsTestAccessor::getTagForTest(
        &mock_jvmti, reinterpret_cast<jobject>(&node_tags[threadNode2]));
    ASSERT_GT(thread2_ftag, 0) << "fresh thread anchor was never admitted";
    FrontierEntry thread2_entry{};
    ASSERT_TRUE(frontier->lookup(thread2_ftag, &thread2_entry));
    EXPECT_EQ(0, thread2_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread2_entry.root_kind);

    tracker->stop();
}

// Candidate-scoped reach, prong 2 (collectStaticFieldAnchorsForRotation()/
// walkStaticFieldAnchors()): the collector selects exactly the root-attached
// static-holder entries with a wrapping cursor, and the walk reaches a leak
// held 3-4 hops inside a static collection in one bounded call - the shape
// the one-hop Tier-2 rotation demonstrably cannot reach from an un-expanded
// FRONTIER holder on a rising heap (pod rounds 5-6).
TEST_F(ReferenceChainsBfsTest, StaticAnchorRotationWalksRootAttachedStaticHolders) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *holderCls = (void *)0x4001, *chunkCls = (void *)0x4002;
    addClass(holderCls, "Lcom/rc/descendwalk/StaticHolder;");
    int chunk = addClass(chunkCls, "Lcom/rc/descendwalk/StaticChunk;");

    int holderNode = addNode();
    int tableNode = addNode();
    int entryNode = addNode();
    int leakChunk = addNode();
    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();
    node_tags[leakChunk] = leak_tag;

    // Static Map -> table -> Entry -> chunk: the collection-shaped static
    // holder's internals, deeper than one hop.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, tableNode, -1},
        {JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, tableNode, entryNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, entryNode, leakChunk, chunk},
    };

    // Seed the frontier exactly as the static sweep admits a static field's
    // value: root-attached, STATIC_FIELD root kind, FRONTIER state. Plus a
    // second durable-root anchor (JNI_GLOBAL - the pod-round-7 filter
    // extension), a TRANSIENT-root decoy the collector must skip, and a
    // chain-attached child (table entries only - deliberately NOT mirrored
    // into node_tags, so the walk below freshly admits those nodes instead
    // of tripping ALREADY_ADMITTED on stale scripted tags).
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 101; // mock_GetObjectsWithTags' resolvable tag
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 101, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 102, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 103, 101, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_JNI_GLOBAL));

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            4);
    // Both DURABLE root kinds are selected (STATIC_FIELD 101, JNI_GLOBAL
    // 104, in cursor/tag order); the transient-root decoy and the child are
    // not. The walk below drives only 101 (the resolvable node).
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(101, selected[0]);
    EXPECT_EQ(104, selected[1]);
    std::vector<jlong> walk_selected = {selected[0]};

    // The static anchor's whole internal structure is admitted by one
    // bounded walk, intercepting the leak tag at depth 3 below the holder.
    int edges = 0;
    ReferenceChainsTestAccessor::walkStaticFieldAnchorsForTest(
        &mock_jvmti, &mock_jni, walk_selected, 1000, &edges);
    jlong table_ftag = tags_ever_assigned[tableNode];
    jlong entry_ftag = tags_ever_assigned[entryNode];
    jlong chunk_ftag = tags_ever_assigned[leakChunk];
    ASSERT_GT(table_ftag, 0) << "table array was not reached by the anchor walk";
    ASSERT_GT(entry_ftag, 0) << "Entry was not reached one hop below table";
    ASSERT_NE(chunk_ftag, leak_tag)
        << "leak-tagged chunk inside the static holder was never intercepted";
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(chunk_ftag));
    FrontierEntry chunk_entry{};
    ASSERT_TRUE(frontier->lookup(chunk_ftag, &chunk_entry));
    EXPECT_EQ(entry_ftag, chunk_entry.parent_tag);
    EXPECT_EQ(3u, chunk_entry.depth);

    tracker->stop();
}

// Retention-edge labels (fillHopEdgeLabels()/hopLabelClassFor()): the
// emitted chain's per-hop labels must decode the JVMTI-SPECIFICATION field
// ordinal captured at admission - the interface offset, the superclass-chain
// order, the interface-referrer branch - and degrade to the edge KIND on any
// undecodable hop, never a fabricated name (the fail-safe contract: a wrong
// numbering on an unverified JVM degrades, it does not lie).
TEST_F(ReferenceChainsBfsTest, HopEdgeLabelsDecodeSpecFieldOrdinals) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Hierarchy mirroring the spec's own numbering example shape:
    //   interface IBase                { int p; }         1 own field
    //   interface ISub extends IBase   { int x; }         1 own field
    //   class Base                     { int base_f; }    1 own field, no super
    //   class Holder extends Base implements ISub
    //                                  { int holder_a; Object leakList; }
    //   interface ISink                { Object CONST_A; Object CONST_B; }
    // Spec ordinal spaces (jvmtiHeapReferenceInfoField):
    //   Holder (class branch): base = ISub(1) + IBase(1) = 2 (transitive
    //     interfaces, each once); then the superclass chain root-first:
    //     base_f@2; then own fields in GetClassFields order:
    //     holder_a@3, leakList@4.
    //   ISink (interface branch): base = superinterfaces' fields = 0; own
    //     fields in GetClassFields order: CONST_A@0, CONST_B@1.
    void *ibase = (void *)0x5001, *isub = (void *)0x5002, *base = (void *)0x5003,
         *holder = (void *)0x5004, *isink = (void *)0x5005;
    addClass(ibase, "Lcom/rc/labels/IBase;");
    addClass(isub, "Lcom/rc/labels/ISub;");
    addClass(base, "Lcom/rc/labels/Base;");
    addClass(holder, "Lcom/rc/labels/Holder;");
    addClass(isink, "Lcom/rc/labels/ISink;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    // resolveLoadedClasses minted each class's raw (negative) tag via the
    // mock's tag map - read them back for the decoder's tag->class lookup
    // and the entries' referrer_class_tag values.
    auto tagOf = [&](void *k) -> jlong { return tags[k]; };
    field_decode_classes[tagOf(holder)] = holder;
    field_decode_classes[tagOf(isink)] = isink;
    field_decode_classes[tagOf(base)] = base;
    // ibase deliberately NOT registered into field_decode_classes: an
    // unresolvable referrer class below must degrade to a kind label.
    field_decode_hierarchy[ibase] = {true, nullptr, {}, {{(void *)0x6001, "p"}}};
    field_decode_hierarchy[isub] =
            {true, nullptr, {ibase}, {{(void *)0x6002, "x"}}};
    field_decode_hierarchy[base] = {false, nullptr, {}, {{(void *)0x6003, "base_f"}}};
    field_decode_hierarchy[holder] =
            {false, base, {isub},
             {{(void *)0x6004, "holder_a"}, {(void *)0x6005, "leakList"}}};
    field_decode_hierarchy[isink] =
            {true, nullptr, {},
             {{(void *)0x6006, "CONST_A"}, {(void *)0x6007, "CONST_B"}}};

    FrontierTable *frontier = tracker->frontierTable();
    // Chain: [chunk(3)] <- Base.base_f(ordinal 0 over Base's space) <-
    // [value2(2), class Base] <- Holder.leakList(ordinal 4, the static root
    // edge with the declaring class as referrer) <- [static value(1), class
    // Holder]. Interior hops decode against the PARENT entry's class_tag.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/4, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(holder)));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 1, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(base),
        /*referrer_field_index=*/3, JVMTI_HEAP_REFERENCE_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 2, 2, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/0, JVMTI_HEAP_REFERENCE_FIELD));

    ReferenceChainEvent event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/3, &event));
    ASSERT_EQ(3u, event._chain.size());
    ASSERT_EQ(3u, event._edges.size())
        << "edge labels must align with the chain, one per hop";
    // Leaf first: chunk is retained via Base.base_f (parent entry's class is
    // Base, ordinal 0 in Base's own space), then value2 via Holder's
    // holder_a (ordinal 3 = interface offset 2 + Base's 1 + own position 0),
    // then the static root edge's field name leakList (ordinal 4).
    EXPECT_EQ("base_f", event._edges[0]);
    EXPECT_EQ("holder_a", event._edges[1]);
    EXPECT_EQ("leakList", event._edges[2]);

    // Interface-referrer branch: ISink's own-field ordinals have NO
    // superclass-chain component (base = superinterfaces' fields only).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(isink),
        /*referrer_field_index=*/1, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(isink)));
    ReferenceChainEvent iface_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/4, &iface_event));
    ASSERT_EQ(1u, iface_event._edges.size());
    EXPECT_EQ("CONST_B", iface_event._edges[0]);

    // Fail-safe: a referrer class that cannot be resolved degrades to the
    // edge KIND label, never a fabricated name.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/0, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(ibase)));
    ReferenceChainEvent degraded_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/5, &degraded_event));
    ASSERT_EQ(1u, degraded_event._edges.size());
    EXPECT_EQ("static_field", degraded_event._edges[0]);

    tracker->stop();
}

// PRIORITY_EXPAND_CAP backpressure: with the fast lane at the cap, the
// rotation collectors must stop pushing. The uncapped queue is what starved
// the BFS on-pod (39k->103k entries while _pending_expand never drained a
// single batch - rotation inflow 256/pass exceeded the deadline-bounded
// drain ~150-300/pass on every pass).
TEST_F(ReferenceChainsBfsTest, PriorityExpandCapStopsRotationCollectorPushes) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // One eligible stale-EXPANDED entry.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    for (size_t i = 0; i < ReferenceChainsTestAccessor::priorityExpandCap(); i++) {
        ReferenceChainsTestAccessor::pushPriorityExpand((jlong)(100 + i));
    }
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(10);
    EXPECT_TRUE(selected.empty())
        << "collector must stop pushing once _priority_expand hits the cap";

    // With the lane drained (a pass's expand phase consumed it), the
    // collector selects again.
    ReferenceChainsTestAccessor::clearPriorityExpand();
    selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(10);
    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);

    tracker->stop();
}

// The stale-expansion rotation must select leak parents from
// _leak_parent_fanout ahead of the blind table lap: the fanout entries are
// the EXPANDED parents that actually lead to watched leak-klass children,
// and neither the blind lap (~table_size/budget passes, hundreds live) nor
// the growth-gated leak-accumulation tier reaches them in steady state.
TEST_F(ReferenceChainsBfsTest, StaleRotationPrefersLeakParentsOverBlindLap) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Fanout parent 1 and an unrelated stale-EXPANDED entry 3. Parent 1
    // needs a non-zero class_tag: trackLeakAccumulation() attributes via the
    // parent entry's class_tag and skips entries without one.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0,
        /*class_tag=*/42));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, 1, 10);

    // Budget 1: the fanout parent wins over the blind-lap entry.
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(1);
    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);

    // Budget covering both: fanout parent first, blind lap fills the rest.
    ReferenceChainsTestAccessor::clearPriorityExpand();
    selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(2);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);
    EXPECT_EQ((jlong)3, selected[1]);

    tracker->stop();
}

// reparentToDurableRoot: a depth-1 entry first admitted through a transient
// root (stack/JNI local) is re-parented to a durable root-attached parent
// at equal depth - the case improveChain() cannot express (it requires a
// strictly deeper path), and exactly the hotdog shape where the singleton
// collection is a depth-0 static root and its elements depth 1.
TEST_F(ReferenceChainsBfsTest, ReparentToDurableRootSwapsTransientForDurable) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // tag 1: transient root (old parent). tag 2: target at depth 1 under it.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // tag 5: durable static root (new parent).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    // tag 6: another transient root - must never be swapped TO.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 6, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    EXPECT_TRUE(frontier->reparentToDurableRoot(2, 5, 42));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(2, &entry));
    EXPECT_EQ((jlong)5, entry.parent_tag);
    EXPECT_EQ((u32)42, entry.referrer_klass);

    // Transient new parent: no swap (would trade one noise root for
    // another).
    EXPECT_FALSE(frontier->reparentToDurableRoot(2, 6, 43));
    ASSERT_TRUE(frontier->lookup(2, &entry));
    EXPECT_EQ((jlong)5, entry.parent_tag) << "parent must be unchanged";

    // Depth-2 targets are out of scope (judging root durability there
    // would require walking both chains).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 7, 2, 2, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    EXPECT_FALSE(frontier->reparentToDurableRoot(7, 5, 44));

    tracker->stop();
}

// recordDiscoveredInstance eviction: noise instances fill discovery slots
// first-come-first-served, but a leak-correlated discovery must evict a
// noise slot when all are full - without eviction, the 8 noise instances
// observed on-pod permanently blocked every later leak-tagged instance of
// the watched class.
TEST_F(ReferenceChainsBfsTest, RecordDiscoveredInstanceEvictsNoiseSlots) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kKlass = 3;
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, kKlass);

    const int cap = ReferenceChainsTestAccessor::maxDiscoveredPerClass();
    for (int d = 0; d < cap; d++) {
        ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
            kKlass, /*tag=*/100 + d, /*leak_correlated=*/false);
    }
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // Noise beyond the cap is dropped, slots unchanged.
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 108, false);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)100,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));

    // Leak-correlated discovery evicts the first noise slot (tag 100 has
    // no frontier entry -> treated as uncorrelated).
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 200, true);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)200,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));
    EXPECT_EQ((jlong)101,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 1));

    // Once every slot is leak-correlated, a further leak discovery is
    // dropped (no eviction of real signal).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 200, 0, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    frontier->setLeakTag(200, ReferenceChainsTestAccessor::leakTagBase() + 1);
    // Entries for the remaining noise slots so the eviction scan finds all
    // slots leak-tagged.
    for (int d = 1; d < cap; d++) {
        jlong tag = 101 + (d - 1);
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
        frontier->setLeakTag(tag, ReferenceChainsTestAccessor::leakTagBase() + 2);
    }
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 201, true);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    for (int d = 0; d < cap; d++) {
        EXPECT_NE((jlong)201,
                  ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, d));
    }

    tracker->stop();
}

// correlateAdmittedLeakTag: a tracked instance the BFS admitted BEFORE it
// was leak-tagged carries a frontier tag on the object; correlating stores
// the leak tag ON the entry (chain events then emit targetTag = leak tag)
// and records the instance as discovered. Never retags the object.
TEST_F(ReferenceChainsBfsTest, CorrelateAdmittedLeakTagSetsEntryAndDiscovers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kKlass = 3;
    constexpr jlong kLeakTag = 0x40000000LL + 5;
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, kKlass);

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 300, 0, 1, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    EXPECT_TRUE(tracker->correlateAdmittedLeakTag(300, kLeakTag, kKlass));
    EXPECT_EQ(kLeakTag, (jlong)ReferenceChainsTestAccessor::frontierLeakTag(300));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)300,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));

    // Idempotent: an already-correlated entry just returns true.
    EXPECT_TRUE(tracker->correlateAdmittedLeakTag(300, kLeakTag, kKlass));
    EXPECT_EQ(kLeakTag, (jlong)ReferenceChainsTestAccessor::frontierLeakTag(300));

    // Unknown tag: no crash, no discovery side effects.
    EXPECT_FALSE(tracker->correlateAdmittedLeakTag(999, kLeakTag, kKlass));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    tracker->stop();
}

// Retention-explanation gate on the discovered-instance chains (depth==0
// always suppressed; depth==1 suppressed only for TRANSIENT roots - a
// depth-1 chain from a durable root is the real direct-retention shape):
// transient depth-1 must NOT be cached, durable depth-1 and depth-2 must.
TEST_F(PollWatchedTargetsTest, DiscoveredChainGateSuppressesTransientDepthOne) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/3, /*rep=*/(jweak)obj);

    // First poll populates the candidate slots from LivenessTracker's
    // population. No discovered instances yet.
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    FrontierTable *frontier = tracker->frontierTable();
    // Noise shape: transient root (JNI local frame) -> depth-1 instance.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 6, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 7, 6, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Real direct-retention shape: static-field root -> depth-1 instance.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 8, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 9, 8, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Deeper chain through the transient root: passes on depth alone.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, 7, 2, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Depth-0 transient root: the candidate instance itself held by a live
    // frame - suppressed like the depth-1 transient shape.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 11, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Depth-0 durable root: the candidate instance IS the static field's
    // value (the singleton-collection-itself shape) - a real direct-retention
    // chain, NOT suppressible as noise.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 12, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 7, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 9, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 10, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 11, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 12, false);
    ASSERT_EQ(5, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7))
        << "depth-1 chain rooted at a transient (JNI local) root is noise";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(9))
        << "depth-1 chain rooted at a durable (static field) root is a real "
           "direct-retention chain";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(10))
        << "depth-2 chain passes the gate regardless of root kind";
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag(11))
        << "depth-0 chain rooted at a transient (stack local) root is noise";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(12))
        << "depth-0 chain rooted at a durable (static field) root is the "
           "direct-retention shape the search exists to report";

    tracker->stop();
}

// Orphan slot sweep: a candidate that qualified long enough for the walk to
// record discovered instances, then stopped qualifying (its trend aged out
// of the poll's candidate list), must still get chains built for those
// instances. The slot persists by design precisely so the klass "can still
// be found there" - before the sweep, nothing iterated it once the klass
// left the poll candidates, stranding every instance recorded while it
// qualified (observed live: 8 discovered instances recorded the pass
// after the candidate's trend aged out were never built across the
// remaining 116 passes of the run).
TEST_F(PollWatchedTargetsTest, OrphanedSlotBuildsDiscoveredChainsAfterCandidateDropsOut) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/3, /*rep=*/(jweak)obj);

    // First poll admits klass 3 into candidate slot 0 (nothing discovered
    // yet, so nothing is built here).
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(0, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // The walk discovered an instance while the candidate still
    // qualified: the real direct-retention shape (static-field root ->
    // depth-1 instance), which the discovered-chain gate lets through.
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 9, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 8, 9, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 8, false);
    ASSERT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // The candidate stops qualifying: LivenessTracker's population table
    // is wiped, so selectLeakCandidates() returns 0 on every poll from
    // here on. Before the orphan sweep, this poll would leave the recorded
    // instance permanently unbuildable.
    LivenessTracker::instance()->klassPopulationResetForTest();
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(8))
        << "discovered instances recorded while the candidate qualified must "
           "still get chains built after it stops qualifying";

    tracker->stop();
}
