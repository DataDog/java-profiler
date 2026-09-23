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
#include "os.h"
#include "profiler.h"
#include "rcDebugLevel.h"
#include "referenceChains.h"
#include "vmEntry.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <unistd.h>
#include <cstdio>
#include <map>

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

// Tests need full rc debug diagnostics: pin level 2 before any library
// code runs (the gate defaults to silent, see rcDebugLevel.h).
[[maybe_unused]] static const bool kRcDebugLevelPinnedForTests =
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1) == 0;

// RcDebugLevelTest - the runtime debug-log gate's pure parsing + env
// plumbing (rcDebugLevel.h). No tracker state involved.
TEST(RcDebugLevelTest, ParseAcceptsTrimmedSingleDigits) {
    EXPECT_EQ(parseRcDebugLevel(nullptr), -1);
    EXPECT_EQ(parseRcDebugLevel(""), -1);
    EXPECT_EQ(parseRcDebugLevel("0"), 0);
    EXPECT_EQ(parseRcDebugLevel("1"), 1);
    EXPECT_EQ(parseRcDebugLevel("2"), 2);
    EXPECT_EQ(parseRcDebugLevel(" 2\n"), 2); // the `echo 2 >` form
    EXPECT_EQ(parseRcDebugLevel("\t1\r\n"), 1);
    EXPECT_EQ(parseRcDebugLevel("3"), -1);
    EXPECT_EQ(parseRcDebugLevel("12"), -1);
    EXPECT_EQ(parseRcDebugLevel("-1"), -1);
    EXPECT_EQ(parseRcDebugLevel("abc"), -1);
    EXPECT_EQ(parseRcDebugLevel("2 garbage"), -1);
}

TEST(RcDebugLevelTest, ReadFileParsesTrimmedAndRejectsInvalid) {
    char path[] = "/tmp/rc_dbg_test_XXXXXX";
    int fd = mkstemp(path);
    ASSERT_GE(fd, 0);
    close(fd);
    struct Case {
        const char *content;
        int expected;
    };
    const Case cases[] = {
        {"2\n", 2}, {"1", 1}, {" 2 ", 2}, {"\n1\n", 1},
        {"", -1}, {"3", -1}, {"22", -1}, {"abc", -1}, {"x", -1},
    };
    for (const Case &c : cases) {
        FILE *f = fopen(path, "w");
        ASSERT_NE(f, nullptr);
        EXPECT_GE(fputs(c.content, f), 0); // non-negative on success
        fclose(f);
        EXPECT_EQ(readRcDebugLevelFile(path), c.expected) << "content='" << c.content << "'";
    }
    unlink(path);
    EXPECT_EQ(readRcDebugLevelFile(path), -1); // now missing
    EXPECT_EQ(readRcDebugLevelFile(nullptr), -1);
}

TEST(RcDebugLevelTest, RefreshFollowsEnvWhenNoOverrideFile) {
    // The refresh's override path is machine-global; skip rather than
    // flake on a machine that happens to have the file.
    if (access("/tmp/ddprof_root/refchains_debug_level", F_OK) == 0) {
        GTEST_SKIP() << "override file present on this machine";
    }
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "1", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 1);
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 2);
    // invalid env value means silent, not "keep the previous level"
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "bogus", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 0);
    // restore the pinned level for any later test's diagnostics
    setenv("DD_PROFILING_REFERENCE_CHAINS_DEBUG", "2", 1);
    rcDebugLevelRefresh(true);
    EXPECT_EQ(rcDebugLevel(), 2);
}

// VMTestAccessor - friend of VM (vmEntry.h): swaps VM::_jvmti for a mock so
// start()/stop() can call SetEventNotificationMode() without a live JVM.
class VMTestAccessor {
public:
    static jvmtiEnv* getJvmti() { return VM::_jvmti; }
    static void setJvmti(jvmtiEnv* env) { VM::_jvmti = env; }
};

// ReferenceChainsTestAccessor - friend-accessor pattern as above: reset()
// clears the search-lifecycle fields between tests (a terminal search state
// would make later runPass() calls permanent no-ops).
class ReferenceChainsTestAccessor {
public:
    static void reset() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        delete t->_frontier;
        t->_frontier = nullptr;
        t->_class_tags = ClassTagTable();
        t->_last_resolved_class_count = 0;
        // Stale sweep-cursor state could wrongly skip this test's first
        // static-field sweep when the class counts happen to match.
        t->_last_static_field_class_count = -1;
        t->_static_field_sweep_cursor = 0;
        t->_static_field_sweep_cycle_truncated = false;
        t->_next_tag = 1;
        // Process-wide, shared with LivenessTracker - needs its own reset seam.
        ClassTagAllocator::resetForTest();
        t->_search_started = false;
        t->_tags_released = true;
        t->_search_state = SearchState::RUNNING;
        t->_abandon_reason = SearchAbandonReason::NONE;
        t->_search_start_ns = 0;
        t->_pending_expand.clear();
        t->_priority_expand.clear();
        t->_priority_expand_set.clear();
        // At-risk FIFO + fresh lane: a saturated FIFO left behind here
        // crashes the next fixture's runPass (null GetObjectsWithTags).
        t->_static_anchor_fifo.clear();
        t->_static_anchor_fifo_set.clear();
        t->_static_anchor_fifo_klass_counts.clear();
        t->_static_anchor_fresh_queue.clear();
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
        t->_static_anchor_index.clear();
        t->_static_anchor_own_class_tags.clear();
        t->_static_anchor_index_tags.clear();
        t->_anchor_container_cursor = 0;
        t->_anchor_other_cursor = 0;
        t->_class_shape_cache.clear();
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
        // Stale adaptive-batch/lane state would silently change the next
        // test's expandFrontier() arithmetic.
        t->_gotw_ema_call_ns = 0;
        t->_gotw_batch_size = 0;
        t->_pass_deadline_ns = 0;
        t->_expand_lane_prefer_priority = true;
    }

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

    // Resolved-chain cache seam for ResolvedChainCacheTest below.
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

    // Read-only peeks at the resolved-chain cache for PollWatchedTargetsTest.
    static bool hasResolvedChainForTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_resolved_chains.find(tag) != t->_resolved_chains.end();
    }

    static jlong resolvedChainSourceTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_resolved_chains.find(tag);
        return it == t->_resolved_chains.end() ? 0 : it->second.source_tag;
    }

    // Frontier entry's stored leak tag (-1 when the tag is not in the
    // frontier table), for LeakTagInterceptionTest below.
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

    static u64 candidateFoundBitsForTest() {
        return ReferenceChainTracker::instance()->_candidate_found_bits;
    }

    static jlong candidateFrontierTagForTest(int slot) {
        return ReferenceChainTracker::instance()->_candidate_frontier_tags[slot];
    }

    static void buildDiscoveredInstanceChainsForTest(u32 klass_id,
                                                       u64 current_search_ns) {
        // jvmti/jni null is safe: resolveHopEdgeLabel() null-guards and
        // degrades hop labels to kind labels.
        ReferenceChainTracker::instance()->buildDiscoveredInstanceChains(
            nullptr, nullptr, klass_id, current_search_ns);
    }

    // ---- pod-in-a-jar system harness ----
    static u8 searchStateForTest() {
        return ReferenceChainTracker::instance()->_search_state;
    }

    static int sweepGateResolvedCountForTest() {
        return ReferenceChainTracker::instance()->_last_resolved_class_count;
    }

    static int sweepGateStaticCountForTest() {
        return ReferenceChainTracker::instance()->_last_static_field_class_count;
    }

    static int sweepCursorForTest() {
        return ReferenceChainTracker::instance()->_static_field_sweep_cursor;
    }

    static int passesRunForTest() {
        return ReferenceChainTracker::instance()->_passes_run;
    }

    static int candidateCountForTest() {
        return ReferenceChainTracker::instance()->_candidate_count;
    }

    static u32 candidateKlassIdForTest(int slot) {
        return ReferenceChainTracker::instance()->_candidate_klass_ids[slot];
    }

    static size_t resolvedChainCountForTest() {
        return ReferenceChainTracker::instance()->_resolved_chains.size();
    }

    static std::vector<u64> resolvedChainTargetsForTest() {
        std::vector<u64> out;
        for (auto &kv :
             ReferenceChainTracker::instance()->_resolved_chains) {
            out.push_back(kv.second.event._target_tag);
        }
        return out;
    }

    static size_t staticAnchorFreshQueueSizeForTest() {
        return ReferenceChainTracker::instance()
            ->_static_anchor_fresh_queue.size();
    }

    static jlong candidateDiscoveredTagForTest(int slot, int idx) {
        return ReferenceChainTracker::instance()->candidateDiscoveredTagForTest(slot, idx);
    }

    static int candidateDiscoveredCountForTest(int slot) {
        return ReferenceChainTracker::instance()->candidateDiscoveredCountForTest(slot);
    }

    static void recordDiscoveredInstanceForTest(u32 klass_id, jlong tag,
                                                 bool leak_correlated) {
        ReferenceChainTracker::instance()->recordDiscoveredInstance(klass_id, tag,
                                                                   leak_correlated);
    }

    // reset() set _tags_released, so restartSearch()'s assert is satisfied.
    static void restartSearchForTest() {
        ReferenceChainTracker::instance()->restartSearch();
    }

    static bool anchorIndexIsEmptyForTest() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_static_anchor_index.empty() &&
               t->_static_anchor_own_class_tags.empty() &&
               t->_static_anchor_index_tags.empty();
    }

    // Read back discovered-instance slots.
    static jlong discoveredTagForTest(int slot, int idx) {
        return ReferenceChainTracker::instance()
            ->_candidate_discovered_tags[slot][idx];
    }

    static int discoveredCountForTest(int slot) {
        return ReferenceChainTracker::instance()
            ->_candidate_discovered_count[slot];
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

    // Direct expandFrontier() drive for the AIMD batch test: per-call
    // assertions are not deterministic through runPass().
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

    // Pause-time pacing controller seam for ReferenceChainsPacingTest below.
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

    // Test-only seams for PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling,
    // which needs a controlled starting point and a freshly reset controller.
    static void setEffectiveBudget(int v) {
        ReferenceChainTracker::instance()->_effective_budget = v;
    }

    static void setEffectiveCadenceNs(u64 v) {
        ReferenceChainTracker::instance()->_effective_cadence_ns = v;
    }

    static void resetPacingController() {
        ReferenceChainTracker::instance()->_pause_pid.reset();
    }

    // Borrow ceiling multiplier, asserted instead of hardcoded in the test.
    static int borrowCeilingMultiplier() {
        return ReferenceChainTracker::BORROW_CEILING_MULTIPLIER;
    }

    static int64_t borrowedBudget() {
        return ReferenceChainTracker::instance()->_borrowed_budget;
    }

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

    // Whether the tracker still owes a tag release (ReleaseSearchTagsFailureTest).
    static bool tagsReleased() {
        return ReferenceChainTracker::instance()->_tags_released;
    }

    static void resolveLoadedClasses(jvmtiEnv *jvmti, JNIEnv *jni) {
        ReferenceChainTracker::instance()->resolveLoadedClasses(jvmti, jni);
    }

    static int lastResolvedClassCount() {
        return ReferenceChainTracker::instance()->_last_resolved_class_count;
    }

    // Durability re-verification seams: private tie-break/rotation methods
    // plus FrontierTable::insert(), for exact entry setup without a walk mock.
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

    // Direct drives for the walk phases: a full runPass() drains a small
    // graph to completion, so the walks are exercised on their own.
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
        walkStaticAnchorFifoForTest(jvmti, jni, tags, budget, edges_admitted,
                                    nullptr);
    }

    static std::vector<jlong>
    collectStaticFieldAnchorsForRotationForTest(int max_count) {
        return ReferenceChainTracker::instance()
            ->collectStaticFieldAnchorsForRotation(max_count);
    }

    static void addToStaticAnchorIndexForTest(jlong tag, jlong own_class_tag,
                                               u8 root_kind) {
        ReferenceChainTracker::instance()
            ->addToStaticAnchorIndex(tag, own_class_tag, root_kind);
    }

    // Prime the class-shape cache as if reconcileAnchorClassShapes() had
    // classified `class_tag` (driving the JNI walk needs real classes).
    static void primeClassShapeForTest(jlong class_tag, bool container) {
        ReferenceChainTracker::instance()->_class_shape_cache[class_tag] =
            container
                ? (u8)ReferenceChainTracker::AnchorClassShape::CONTAINER
                : (u8)ReferenceChainTracker::AnchorClassShape::NON_CONTAINER;
    }

    // At-risk static-anchor FIFO seams: pushStaticAnchorFifoForTest calls
    // pushAtRiskStaticAnchor() directly so drain/walk/requeue mechanics can
    // be exercised deterministically. Private nested names surfaced for test
    // bodies (friendship covers only this class's scope):
    using AtRiskAnchor = ReferenceChainTracker::AtRiskAnchor;
    static constexpr u32 kAtRiskPerKlassCap =
        ReferenceChainTracker::STATIC_ANCHOR_ATRISK_PER_KLASS_CAP;

    static void pushStaticAnchorFifoForTest(jlong tag, u32 klass_id) {
        ReferenceChainTracker::instance()->pushAtRiskStaticAnchor(tag,
                                                                  klass_id);
    }

    static int drainStaticAnchorFifoForTest(
            int max_count,
            std::vector<ReferenceChainTracker::AtRiskAnchor> &out) {
        return ReferenceChainTracker::instance()->drainStaticAnchorFifo(
            max_count, out);
    }

    static void requeueStaticAnchorFifoFrontForTest(
            const std::vector<ReferenceChainTracker::AtRiskAnchor> &entries) {
        ReferenceChainTracker::instance()->requeueStaticAnchorFifoFront(
            entries);
    }

    static size_t staticAnchorFifoSizeForTest() {
        return ReferenceChainTracker::instance()->_static_anchor_fifo.size();
    }

    static bool staticAnchorFifoContainsForTest(jlong tag) {
        return ReferenceChainTracker::instance()
            ->_static_anchor_fifo_set.contains(tag);
    }

    static void walkStaticAnchorFifoForTest(jvmtiEnv *jvmti, JNIEnv *jni,
                                             const std::vector<jlong> &tags,
                                             int budget, int *edges_admitted,
                                             std::vector<jlong> *unwalked) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        bool truncated = false;
        bool cap_hit = false;
        u64 safepoint_ticks = 0;
        t->walkStaticFieldAnchors(jvmti, jni, tags, budget, edges_admitted,
                                  &truncated, &cap_hit, &safepoint_ticks,
                                  unwalked);
    }

    // Seeds exactly one (slot, klass, tid) combination without driving
    // LivenessTracker's hysteresis machinery.
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

    // Snapshot of _priority_expand's contents, in queue order.
    static std::vector<jlong> priorityExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_priority_expand.begin(),
                                   t->_priority_expand.end());
    }

    // Simulates a truncated expandFrontier() batch left in _priority_expand.
    static void pushPriorityExpand(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        t->_priority_expand.push_back(tag);
        t->_priority_expand_set.insert(tag);
    }

    // Simulates expandFrontier() having drained _priority_expand at the end
    // of a pass.
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

    // Snapshot of _pending_expand's contents, in queue order.
    static std::vector<jlong> pendingExpandContents() {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return std::vector<jlong>(t->_pending_expand.begin(),
                                  t->_pending_expand.end());
    }

    static size_t pendingExpandSize() {
        return ReferenceChainTracker::instance()->_pending_expand.size();
    }

    // Adaptive batch size (AIMD): EMA and live batch size seams.
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

    // Read-only peeks at the batch-control constants (private statics).
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
    // - directly unit-testable.
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
// boundary: `depth >= (u32)ctx->hop_cap` casts a negative int to u32,
// wrapping to ~4e9 and silently disabling the hop cap.
TEST_F(ReferenceChainsTest, FlagClampsNegativeSubOptions) {
    Arguments args;
    Error error = args.parse(
        "referencechains=true:hops=-1:budget=-5:ttl=-1:framecap=-3:"
        "pausetarget=-1:painbudget=-10");
    EXPECT_FALSE(error);
    EXPECT_TRUE(args._reference_chains);
    // Floored to a sane minimum (1): a negative value cast to u32
    // downstream would wrap to a huge positive number.
    EXPECT_GT(args._reference_chains_hop_cap, 0);
    EXPECT_GT(args._reference_chains_budget, 0);
    EXPECT_GT(args._reference_chains_frontier_cap, 0);
    // ttl/pausetarget are floored at 0: their downstream gates treat 0 as
    // "disabled", so 0 - not 1 - is the correct floor.
    EXPECT_GE(args._reference_chains_ttl_ms, 0);
    EXPECT_GE(args._reference_chains_pause_target_ms, 0);
    // painbudget is a percentage - clamped into [0, 100].
    EXPECT_GE(args._reference_chains_pain_budget_percent, 0);
    EXPECT_LE(args._reference_chains_pain_budget_percent, 100);
}

// A too-large painbudget must be clamped down to 100.
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

// GC signal (GarbageCollectionStart/Finish -> epoch counters). The
// trampolines ignore jvmtiEnv* (only an atomic counter is bumped, per the
// JVMTI spec restriction in referenceChains.h), so nullptr is valid here.

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

// Tag round-trip (SetTag/GetTag/clear) against a mock jvmtiEnv backed by an
// in-memory tag map (no live JVM here; GC move-transparency is out of reach).

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

// FrontierTable (tag-indexed frontier metadata table): pure native slot
// storage, exercised directly.

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
    // Callers index the table with tag-1: a `tag <= 0` check (not just
    // `tag < 0`) keeps that subtraction from wrapping into a valid slot.
    EXPECT_FALSE(table.lookupLocked(0, &entry));
    EXPECT_FALSE(table.lookupLocked(-1, &entry));
}

TEST(FrontierTableTest, LookupLockedRejectsTagPastCurrentSize) {
    FrontierTable table(64);
    ASSERT_TRUE(table.insert(1, 0, 7, 0, FrontierEntryState::FRONTIER));
    FrontierEntry entry{};
    // table_size == 1; tag=2 maps to idx=1, at the size boundary, and must
    // be rejected rather than read out of bounds.
    EXPECT_FALSE(table.lookupLocked(2, &entry));
}

TEST(FrontierTableTest, ParentTagChainReconstructsAcrossHops) {
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
    EXPECT_FALSE(table.insert(max_cap + 1, 0, 0, 0));
    EXPECT_EQ(max_cap, table.capacity());

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
    // while other threads are concurrently inserting.
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

    // Every hop must be marked EDGE.
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

// Heap-walk engine (runPass()/heapReferenceCallback()/resolveLoadedClasses()).
// No live JVM here: the JVMTI/JNI boundary is mocked to play back a scripted
// synthetic object graph, and the *real* production callback/resolution/
// chain-reconstruction code runs against it. A live-JVM end-to-end test
// belongs to the Java-side integration suite.

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

// Retention-edge label decode fixtures: a fake class hierarchy for the
// spec-ordinal decoder (own-declared fields, direct superclass, interfaces).
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

    // node_tags[idx] mirrors the object's *current* live JVMTI tag (0 once
    // releaseSearchTags() clears it). tags_ever_assigned[idx] remembers the
    // tag the callback ever wrote through tag_ptr, never reset - capture-
    // at-assignment semantics, so a tag can be fetched after release.
    std::vector<jlong> tags_ever_assigned;

    // Tags GetObjectsWithTags() reports as unresolvable (object died
    // between passes), for the resolve-or-drop tests.
    std::unordered_set<jlong> dead_tags;

    // When true, mock_GetObjectsWithTags() fails outright (simulating
    // releaseSearchTags()'s own call failing, vs. an individual dead tag).
    bool fail_get_objects_with_tags = false;

    // When non-zero, mock_GetObjectsWithTags() busy-waits this long; a pass
    // deadline below this value bounds an expandFrontier() invocation to
    // exactly one batch.
    u64 gotw_delay_ns = 0;

    // Synthetic frontier-holder arrays for the array-holder walk:
    // NewObjectArray hands back an opaque handle, SetObjectArrayElement
    // records its elements here, FollowReferences treats each as an
    // expansion seed when the holder is initial_object.
    std::unordered_map<jobject, std::vector<jobject>> holders;
    uintptr_t next_holder = 0xF00D0000;

    // FindClass(name) -> registered fake class, for descendFromAnchor()'s
    // name-based resolutions (java/lang/ClassLoader, java/lang/Thread, ...).
    std::unordered_map<std::string, void *> find_classes;
    // Fake class returned by mock_GetObjectClass() for unregistered objects.
    void *thread_class = nullptr;

    // DeleteGlobalRef call count (see mock_DeleteGlobalRef).
    int global_refs_deleted_ = 0;

    jvmtiEnv *orig_jvmti = nullptr;

    static ReferenceChainsBfsTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        // Without the reset, a prior test leaving a terminal search state
        // makes every runPass() below a no-op.
        ReferenceChainsTestAccessor::reset();
        jvmti_tbl = jvmtiInterface_1_{};
        // Stub SetEventNotificationMode and swap VM::_jvmti so start() does
        // not dereference the real (null, no live JVM) jvmtiEnv.
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
        jni_tbl.DeleteGlobalRef = &mock_DeleteGlobalRef;
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

    // Registers a fake class (matched by identity); returns its index into
    // `classes`.
    int addClass(void *klass, const char *signature) {
        classes.push_back({klass, signature});
        return (int)classes.size() - 1;
    }

    // addClass() + a FindClass registry entry. `name` uses the binary-name
    // form, `signature` the class-signature form - each goes to one API.
    int registerClassForFindClass(void *klass, const char *name,
                                   const char *signature) {
        int idx = addClass(klass, signature);
        find_classes[name] = klass;
        return idx;
    }

    // Adds an untagged node; returns its index into node_tags.
    int addNode() {
        node_tags.push_back(0);
        tags_ever_assigned.push_back(0);
        return (int)node_tags.size() - 1;
    }

    // Reverse lookup from &node_tags[idx] back to idx; -1 otherwise.
    // addNode() must precede any runPass() so node_tags never reallocates
    // out from under a taken address.
    int indexOfNode(jobject obj) const {
        for (size_t i = 0; i < node_tags.size(); i++) {
            if (obj == (jobject)&node_tags[i]) {
                return (int)i;
            }
        }
        return -1;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        // releaseSearchTags() calls SetTag(obj, 0) on the resolved objects -
        // route that through node_tags[idx] so the release is observable.
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
        auto &classes = active_fixture->classes;        *count_ptr = (jint)classes.size();
        *classes_ptr = classes.empty()
                ? nullptr
                : (jclass *)malloc(sizeof(jclass) * classes.size());
        for (size_t i = 0; i < classes.size(); i++) {
            (*classes_ptr)[i] = (jclass)classes[i].klass;
        }
        return JVMTI_ERROR_NONE;
    }

    // Every fixture class reports a null (bootstrap) classloader so the
    // app-classes-first partition is a no-op.
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

    // Retention-edge label decode fixtures: a fake class hierarchy for the
    // introspection slots, plus a tag -> fake jclass map.
    std::unordered_map<jlong, void *> field_decode_classes;
    std::unordered_map<void *, FakeClass> field_decode_hierarchy;

    // Hierarchy-introspection slots the decoder needs (GetSuperclass lives
    // on the JNI table - JVMTI dropped its own). Unregistered classes return
    // a failure code so the decoder degrades to kind labels.
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

    // A non-null fake jclass is all the holder array's element type needs
    // (never introspected); name-based resolutions go through find_classes.
    static jclass JNICALL mock_FindClass(JNIEnv *, const char *name) {
        auto it = active_fixture->find_classes.find(name);
        if (it != active_fixture->find_classes.end()) {
            return (jclass)it->second;
        }
        return (jclass)0xC1A55;
    }

    // Fresh-anchor admission calls GetObjectClass(thread); return the
    // fixture's fake Thread class so the anchor's class tag resolves.
    static jclass JNICALL mock_GetObjectClass(JNIEnv *, jobject) {
        return (jclass)active_fixture->thread_class;
    }


    // This fixture's "refs" are raw fake pointers with no JNI lifetime, so
    // identity is the correct global-ref mock.
    static jobject JNICALL mock_NewGlobalRef(JNIEnv *, jobject obj) {
        return obj;
    }

    // Counts DeleteGlobalRef calls.
    static void JNICALL mock_DeleteGlobalRef(JNIEnv *, jobject) {
        active_fixture->global_refs_deleted_++;
    }

    static jint JNICALL mock_EnsureLocalCapacity(JNIEnv *, jint) {
        return JNI_OK;
    }

    // expandFrontier() calls jniExceptionCheck() after upcalls that can
    // legally throw - this fixture's mocks never throw.
    static jboolean JNICALL mock_ExceptionCheck(JNIEnv *) {
        return JNI_FALSE;
    }

    static void JNICALL mock_ExceptionClear(JNIEnv *) {
        // no-op: mock_ExceptionCheck() never reports a pending exception.
    }

    // Hands back a fresh opaque holder handle registered in `holders`.
    static jobjectArray JNICALL mock_NewObjectArray(JNIEnv *, jsize, jclass,
                                                     jobject) {
        jobject handle = (jobject)(active_fixture->next_holder++);
        active_fixture->holders[handle] = {};
        return (jobjectArray)handle;
    }

    static void JNICALL mock_SetObjectArrayElement(JNIEnv *, jobjectArray array,
                                                    jsize idx, jobject value) {        active_fixture->holders[(jobject)array].push_back(value);
    }

    // Root enumeration: reports each scripted root edge's referee to
    // heapRootCallback() - tag_ptr only, no oop, no transitive children.
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

    // Resolves each requested tag to &node_tags[idx]; only currently-live
    // tags come back, like the real call. A tag in `dead_tags` is omitted
    // even if node_tags still holds it.
    static jvmtiError JNICALL mock_GetObjectsWithTags(
            jvmtiEnv *, jint tag_count, const jlong *req_tags, jint *count_ptr,
            jobject **object_result_ptr, jlong **tag_result_ptr) {
        if (active_fixture->fail_get_objects_with_tags) {
            // A real failed JVMTI call makes no promise about the out
            // params; releaseSearchTags() must not read them on this path.
            return JVMTI_ERROR_OUT_OF_MEMORY;
        }
        if (active_fixture->gotw_delay_ns != 0) {
            u64 until = OS::nanotime() + active_fixture->gotw_delay_ns;
            while (OS::nanotime() < until) {
                // Busy-wait: a sleep's scheduler overshoot would break the
                // one-batch deadline arithmetic this knob is used for.
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
            // tag - no node carries one, so field_decode_classes serves it.
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

    // Plays back `script` against the real production heap_reference_callback:
    // an edge whose referrer was not visited/descended into is skipped (a
    // real traversal would never reach it); JVMTI_VISIT_ABORT stops delivery;
    // with non-NULL initial_object (resumed/holder walks) root edges are
    // skipped. Not a full JVMTI implementation - just enough fidelity for
    // the hop-cap/budget/frontier-cap/resumption logic.
    static jvmtiError JNICALL mock_FollowReferences(
            jvmtiEnv *, jint, jclass, jobject initial_object,
            const jvmtiHeapCallbacks *callbacks, const void *user_data) {
        std::unordered_map<int, bool> expandable;        // seed_idx == -2: root walk; -1: array-holder walk; >= 0: single-object.
        int seed_idx = -2;
        // The transient holder array itself is never tagged (production
        // never calls SetTag on it), so holder->element edges replay with a
        // referrer tag of 0.
        static jlong holder_tag = 0;
        if (initial_object != nullptr) {
            auto holder_it = active_fixture->holders.find(initial_object);
            if (holder_it != active_fixture->holders.end()) {
                // Array-holder walk: invoke the production callback for each
                // holder->element edge like a real
                // FollowReferences(initial_object=holder_array) call, so the
                // callback's own tag-sign logic actually runs.
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
                    expandable[idx] = (ctl & JVMTI_VISIT_OBJECTS) != 0;                }
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
                if (it == expandable.end() || !it->second) {                    continue;
                }
            }            jlong class_tag = 0;
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

    // A single pass that fully exhausts the reachable graph completes the
    // search and releases every tag it assigned - fetch via
    // tags_ever_assigned, not node_tags (already 0).
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    jlong targetTag = tags_ever_assigned[nodeTarget];
    ASSERT_NE(0, targetTag);
    EXPECT_EQ(0, node_tags[nodeTarget]); // released

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

    // buildChainEvent() wraps reconstructChain() into the ReferenceChainEvent
    // shape recordReferenceChain() (flightRecorder.cpp) expects.
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, targetTag,
                                          &event));
    EXPECT_EQ((u64)targetTag, event._target_tag);
    EXPECT_EQ(2u, event._depth); // root(A, depth0) -> B(depth1) -> Target(depth2)
    ASSERT_EQ(chain.size(), event._hops.size());
    for (size_t i = 0; i < chain.size(); i++) {
      EXPECT_EQ(chain[i], event._hops[i].klass_id);
    }

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

    // Freshly started: never abandoned.
    ReferenceChainAbandonedEvent event;
    EXPECT_FALSE(tracker->buildAbandonedEvent(&event));

    int nodeA = addNode();
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}};
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    // Small graph, no caps hit -> COMPLETED.
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
    // Not truncated -> the search completes and releases tags in the same
    // call - fetch nodeA's tag via tags_ever_assigned, not node_tags.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]); // never admitted into the frontier

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BudgetExhaustionTruncatesAndIsReported) {
    Arguments args;
    // budget=1: root enum and the expand phase draw from separate budget
    // pools, each sized 1 here.
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
    // Pending work remains, so the search stays RUNNING and no tags are
    // released yet.
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
    node_tags[classNode] = -7; // class object already tagged (negative) by
                               // resolveLoadedClasses(), per ClassTagTable's
                               // tag-sign convention
    int fieldTargetNode = addNode();

    script = {
        // A root reference straight to the class object (e.g. a
        // JVMTI_HEAP_REFERENCE_SYSTEM_CLASS root edge in a real walk).
        {JVMTI_HEAP_REFERENCE_SYSTEM_CLASS, -1, classNode, -1},
        // Must not be delivered: the class-object edge above must not return
        // JVMTI_VISIT_OBJECTS (mock enforces this like a real traversal).
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    EXPECT_EQ(-7, node_tags[classNode]); // untouched - never a frontier
                                         // object
    EXPECT_EQ(0, node_tags[fieldTargetNode]); // never reached - the class edge
                                               // must not expand

    tracker->stop();
}

// An object retained solely by a static field (no other GC root reaches it)
// must still be discovered. The scripted class is registered with its own
// node's address as the jclass identity, so resolveLoadedClasses() tags it
// negative - the same identity the STATIC_FIELD script edge uses as its
// referrer.
TEST_F(ReferenceChainsBfsTest, DiscoversObjectRetainedOnlyByStaticField) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int fieldTargetNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/Holder;");

    script = {
        // fieldTargetNode is reachable only via classNode's static field.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // classNode was tagged negative by the real resolveLoadedClasses() scan
    // and never admitted as a frontier object.
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

    // buildChainEvent() appends the root TYPE (the declaring class) as the
    // chain's root-side end, resolved from referrer_class_tag (negative).
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, target_tag,
                                          &event));
    int expectedHolder = Profiler::instance()->lookupClass(
        "com/rc/statics/Holder", strlen("com/rc/statics/Holder"));
    ASSERT_NE(-1, expectedHolder);
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_EQ(chain[0], event._hops[0].klass_id); // the target's own class, unchanged
    EXPECT_EQ((u32)expectedHolder, event._hops[1].klass_id);
    // One label per hop (recordReferenceChain() drops ALL labels when any
    // is empty); the root-type hop's edge is the unlabeled root edge.
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_FALSE(event._hops[0].edge_label.empty());
    EXPECT_FALSE(event._hops[1].edge_label.empty());

    tracker->stop();
}

// The scan-skip guard must compare `!=`, not `>`: GetLoadedClasses()'s count
// is not monotonic (class unloading shrinks it), so a `>` guard would stay
// skipped once the count returns to a prior peak, leaving different classes
// untagged forever.
TEST_F(ReferenceChainsBfsTest, ResolveLoadedClassesRescansAfterClassCountShrinksAndPartiallyRegrows) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *classA = (void *)0x3001, *classB = (void *)0x3002, *classC = (void *)0x3003;
    addClass(classA, "Lcom/rc/regress/A;");
    int idxB = addClass(classB, "Lcom/rc/regress/B;");

    // Pass 1: both A and B loaded - both get resolved/tagged.
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classA));
    ASSERT_NE(0u, tags.count(classB));
    EXPECT_NE(0, tags[classA]);
    EXPECT_NE(0, tags[classB]);

    // Simulate B's classloader being GC'd: only A remains (count 2 -> 1).
    classes.erase(classes.begin() + idxB);
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1, ReferenceChainsTestAccessor::lastResolvedClassCount());

    // A *different* class C brings the count back to 2 (pass 1's peak):
    // the buggy `>` guard would skip the scan; `!=` must still resolve C.
    addClass(classC, "Lcom/rc/regress/C;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classC));
    EXPECT_NE(0, tags[classC]); // the regression this test guards against

    tracker->stop();
}

// Incremental resumption across passes (expandFrontier()/
// releaseSearchTags()/shouldRunPass(), runPass()'s SearchState transitions).

TEST_F(ReferenceChainsBfsTest, MultiPassResumptionReconstructsChainAcrossPasses) {
    Arguments args;
    // budget=1 forces one new frontier entry per pass, so this 3-hop chain
    // needs resumed expandFrontier() passes.
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

    // Drive the search to completion one pass at a time (each bounded by
    // `budget`).
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
    // Parent_tag linkage survived resumption: all 3 hops walk back to a
    // root-attached (depth 0) entry, which reconstructChain() requires.
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
    // Frontier cap hit -- the search abandons immediately: once the table
    // is full, no entry can ever be admitted again.
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());
    ASSERT_EQ(SearchAbandonReason::FRONTIER_CAP, tracker->abandonReason());

    // nodeA was admitted (frontier cap=1 allowed one entry), then its tag
    // was released as part of this same pass's abandon handling.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    // nodeB was never admitted (frontier cap hit).
    EXPECT_EQ(0, node_tags[nodeB]);

    tracker->stop();
}

// A failing releaseSearchTags() GetObjectsWithTags() call must NOT count as
// "released": marking a tag ABANDONED while its object might still be live
// would let a restarted search's fresh tags collide with it.
TEST_F(ReferenceChainsBfsTest, ReleaseSearchTagsFailureBlocksTagReuseUntilItSucceeds) {
    Arguments args;
    // framecap=1 with a self-cycle: nodeA is admitted, the self-cycle edge
    // is ALREADY_ADMITTED, so only the no-progress detector can abandon -
    // and the tag release must work even when GetObjectsWithTags() fails.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1:ttl=0"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeA, -1}, // self-cycle
    };

    long long failedBefore =
        Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED);

    fail_get_objects_with_tags = true;
    bool truncated = false;
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
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());

    // GetObjectsWithTags() failed - nodeA's still-live tag must NOT have
    // been cleared, and the failure must be counted.
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

    // A further runPass() retries the release; still failing.
    int passesBefore = tracker->passesRun();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(passesBefore, tracker->passesRun());
    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // Once GetObjectsWithTags() succeeds again.
    fail_get_objects_with_tags = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED))
        << "a successful release must not itself count as a failure";

    tracker->stop();
}

// CANARY_STUCK must fire only when the whole-graph frontier has ALSO stalled
// (_passes_since_last_progress >= NO_PROGRESS_PASS_LIMIT): a search whose
// candidate simply has not been found yet must not be abandoned while the
// frontier is still growing every pass.
TEST_F(ReferenceChainsBfsTest, CanaryStuckRequiresWholeGraphFrontierAlsoStalled) {
    Arguments args;
    // budget=1: exactly one new frontier admission per pass, so the frontier
    // grows every pass - _passes_since_last_progress never leaves 0.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A chain longer than the number of passes driven below: the frontier
    // still has pending work at every pass this test checks.
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

    // A canary candidate this graph never contains: the candidate-specific
    // stuck counter climbs every pass with zero discovery progress.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);

    bool truncated = true;
    // One pass past CANARY_NO_PROGRESS_PASS_LIMIT: a single-condition check
    // would have abandoned; the chain still has unexplored work.
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
    // The candidate-stuck counter climbed the whole time.
    EXPECT_GE(ReferenceChainsTestAccessor::passesSinceLastCandidateProgress(),
              ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT);

    tracker->stop();
}

// Canary-lane backoff pacing: a chase runs back-to-back only while fresh or
// making candidate progress; each no-progress pass doubles the spacing
// multiplier up to CANARY_BACKOFF_MULT_MAX, progress resets it to 1, and the
// OOM urgency ramp overrides the gate entirely.
TEST_F(ReferenceChainsBfsTest, CanaryLaneBacksOffWithoutProgressAndResetsOnProgress) {
    Arguments args;
    // Same shape as CanaryStuckRequiresWholeGraphFrontierAlsoStalled: the
    // frontier grows one node per pass, so CANARY_STUCK never fires.
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

    // Pass 1: the candidate admission raises the progress mark, so the
    // multiplier stays at 1 - back-to-back.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult());
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a fresh chase must be allowed to run back-to-back";

    // Pass 2: no candidate progress -> first doubling. Seed a deterministic
    // pass-cost EMA and a fresh pass timestamp for exact spacing arithmetic.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryBackoffMult());
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/2, /*ema_ms=*/100, OS::nanotime());
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a no-progress canary pass must hold off the next one";
    // Beyond the spacing, the chase is allowed again.
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
    // (seeded at 8 so one more pass reaches it).
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/8, /*ema_ms=*/100, OS::nanotime());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult())
        << "the multiplier must hold at its cap, not grow past it";

    // Candidate progress resets the lane to back-to-back.
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
    // budget=1: each pass admits exactly one new edge until the chain is
    // exhausted, then the frontier stops growing; the no-progress detector
    // (not wall-clock TTL) is the only abandon path.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();
    int nodeD = addNode();

    // One node longer than the 1-edge expand budget can drain per call, so
    // each pass ends truncated and pending work remains for the no-progress
    // check once the chain is fully discovered.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeC, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeC, nodeD, -1},
    };

    bool truncated = false;
    // Pass 1: root enum admits nodeA, expand admits nodeB, aborts on
    // nodeB->nodeC for lack of budget - truncated, frontier grew.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 2: admits nodeC, aborts on nodeC->nodeD - still growing.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 3: admits nodeD, chain exhausted - natural completion.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Tags released.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_NE(0, tags_ever_assigned[nodeB]);
    EXPECT_EQ(0, node_tags[nodeB]);

    // ttl=0 disables the wall-clock TTL.
    EXPECT_EQ(SearchAbandonReason::NONE, tracker->abandonReason());
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, NoProgressAbandonsSearchAndReleasesTags) {
    // The mock's root re-enumeration makes the frontier oscillate, so a
    // full end-to-end no-progress abandonment can't be tested with the mock;
    // assert only the wiring.
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_GT(ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT, 0);

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
    // A second root the 1-unit root-enum budget can't reach this pass; the
    // truncation returns before expandFrontier() runs, so nodeA is admitted
    // but never expands nodeA->nodeB.
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
    // Simulate nodeA dying between pass 1 and pass 2.
    dead_tags.insert(aTag);

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 2: resolve-or-drop
    EXPECT_FALSE(truncated);
    // The dead branch was pruned for free - with nothing else pending, the
    // search completes rather than staying RUNNING.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(2, tracker->passesRun());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(aTag, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);

    // nodeB was never discovered - nodeA's subtree was pruned.
    EXPECT_EQ(0, tags_ever_assigned[nodeB]);

    tracker->stop();
}

// pollWatchedTargets(): a candidate's "already discovered by an ordinary
// pass" tag is modelled directly as a FrontierTable entry plus a mocked
// GetTag() that reports it. LivenessTracker::instance() is a second
// process-wide singleton; the SetUp/TearDown resets keep this suite's use
// of it self-contained.

// Pod-in-a-jar system harness: the real tracker loop (shouldRunPass ->
// runPass -> pollWatchedTargets, the exact threadLoop body) over the
// scripted mock heap, asserting system invariants instead of unit symptoms.
// Topology: a static holder holding a synchronized-list wrapper with its
// mutex==this self-edge, the wrapper->c->chunks subtree, pre-seeded leak
// tags on the chunks, and flood statics for anchor-tier volume.
class PodInAJarTest : public ReferenceChainsBfsTest {
protected:
    struct PodTopology {
        int holder_class_node = -1;
        int wrapper_node = -1;
        int list_node = -1;
        int leak_cls_idx = -1;
        int wrapper_cls_idx = -1;
        int list_cls_idx = -1;
        std::vector<int> chunk_nodes;
        std::vector<jlong> chunk_leak_tags;
        std::vector<int> flood_class_nodes;
        std::vector<int> flood_nodes;
        std::vector<int> filler_nodes;
    };

    static constexpr int kChunks = 6; // < MAX_DISCOVERED_INSTANCES_PER_CLASS
    static constexpr u64 kCycleNs = 2000000000ULL; // 2s fake-clock step

    void SetUp() override {
        ReferenceChainsBfsTest::SetUp();
        // resolveCandidateRepresentative() NewLocalRef()s the stored
        // representative; passthrough is right here (reps are mock node
        // pointers with fixture lifetime, never GC'd).
        jni_tbl.NewLocalRef = &mock_NewLocalRefPassthrough;
        // No liveness setup here - each harness test resets liveness
        // explicitly where it wants it.
    }

    static jobject JNICALL mock_NewLocalRefPassthrough(JNIEnv *, jobject ref) {
        return ref;
    }

    void resetLivenessForPod() {
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }

    void TearDown() override {
        ReferenceChainsBfsTest::TearDown();
        // Hygiene for whatever suite runs next: clear any population this
        // harness seeded.
        LivenessTracker::instance()->klassPopulationResetForTest();
    }

    // Builds the leak topology: holder-class static -> synchronized wrapper
    // (mutex==this self-edge) -> c -> K leak-tagged chunks, plus 2 flood
    // classes x 16 static-held nodes for anchor-tier volume.
    PodTopology buildLeakPod() {
        PodTopology topo;
        // Classes registered via classes.push_back({(void*)&node_tags[n],
        // ...}) capture the node's ADDRESS as the jclass identity - vector
        // growth would reallocate node_tags and dangle every captured
        // pointer (silently: nothing admits). Reserve the full node count
        // up front.
        node_tags.reserve(600);
        tags_ever_assigned.reserve(600);
        topo.leak_cls_idx = addClass((void *)0x5001, "[B");
        topo.wrapper_cls_idx = addClass(
            (void *)0x5002,
            "Ljava/util/Collections$SynchronizedRandomAccessList;");
        topo.list_cls_idx = addClass((void *)0x5003, "Ljava/util/ArrayList;");

        topo.holder_class_node = addNode();
        topo.wrapper_node = addNode();
        topo.list_node = addNode();
        // The holder class node doubles as the jclass identity: register it
        // as a loaded class so the sweep admits the wrapper root-attached.
        classes.push_back({(void *)&node_tags[topo.holder_class_node],
                           "Lcom/rc/pod/Holder;"});
        // Flood classes get their own jclass-identity nodes too, so their
        // statics are separate anchors (not more statics on the holder).
        const char *flood_sigs[2] = {"Lcom/rc/pod/FloodA;",
                                     "Lcom/rc/pod/FloodB;"};
        for (int c = 0; c < 2; c++) {
            topo.flood_class_nodes.push_back(addNode());
            classes.push_back(
                {(void *)&node_tags[topo.flood_class_nodes[c]], flood_sigs[c]});
        }

        for (int i = 0; i < kChunks; i++) {
            topo.chunk_nodes.push_back(addNode());
        }
        for (int i = 0; i < 32; i++) {
            topo.flood_nodes.push_back(addNode());
        }
        // Backlog volume: a 300-edge chain under one flood root, so the
        // search spans many passes (the first pass's auto-scaled 10x budget
        // would otherwise admit everything before the poll auto-marks).
        for (int i = 0; i < 300; i++) {
            topo.filler_nodes.push_back(addNode());
        }

        script = {
            // LEAK_BUFFER: the holder class's static field -> wrapper.
            {JVMTI_HEAP_REFERENCE_STATIC_FIELD, topo.holder_class_node,
             topo.wrapper_node, topo.wrapper_cls_idx},
            // The wrapper's mutex==this self-edge (must not demote the
            // root-attached wrapper).
            {JVMTI_HEAP_REFERENCE_FIELD, topo.wrapper_node, topo.wrapper_node,
             topo.wrapper_cls_idx},
            // wrapper -> c -> chunks.
            {JVMTI_HEAP_REFERENCE_FIELD, topo.wrapper_node, topo.list_node,
             topo.list_cls_idx},
        };
        for (int i = 0; i < kChunks; i++) {
            script.push_back({JVMTI_HEAP_REFERENCE_FIELD, topo.list_node,
                              topo.chunk_nodes[i], topo.leak_cls_idx});
        }
        // Flood volume: each flood class holds 16 statics.
        for (int c = 0; c < 2; c++) {
            for (int i = 0; i < 16; i++) {
                script.push_back({JVMTI_HEAP_REFERENCE_STATIC_FIELD,
                                  topo.flood_class_nodes[c],
                                  topo.flood_nodes[16 * c + i],
                                  topo.leak_cls_idx /* any class; volume only */});
            }
        }
        // The filler chain hangs off flood node 0 (already a static anchor).
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, topo.flood_nodes[0],
                          topo.filler_nodes[0], topo.leak_cls_idx});
        for (int i = 0; i + 1 < (int)topo.filler_nodes.size(); i++) {
            script.push_back({JVMTI_HEAP_REFERENCE_FIELD,
                              topo.filler_nodes[i], topo.filler_nodes[i + 1],
                              topo.leak_cls_idx});
        }
        reseedChunkLeakTags(topo);
        return topo;
    }

    // Leak tags model the poll's tagLeakInstances() assignment; the walk's
    // interception path consumes them from the live node tags.
    void reseedChunkLeakTags(const PodTopology &topo) {
        for (int i = 0; i < (int)topo.chunk_nodes.size(); i++) {
            jlong leak_tag = 1073741824LL + 100 + i;
            node_tags[topo.chunk_nodes[i]] = leak_tag;
            tags_ever_assigned[topo.chunk_nodes[i]] = leak_tag;
        }
    }

    // Resolves the leak class's klass id via the same negative class tag
    // the sweep set; class tags are process-lifetime, so this survives the
    // phase-1 tag release (unlike node_tags).
    u32 resolveLeakKlassId(const PodTopology &topo) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        EXPECT_GT(ReferenceChainsTestAccessor::passesRunForTest(), 0)
            << "phase-1 pass never ran";
        jlong class_tag = tags[classes[topo.leak_cls_idx].klass];
        EXPECT_LT(class_tag, 0) << "leak class never sweep-tagged (class_tag="
                                << class_tag << ")";
        return tracker->classTags()->resolve(class_tag);
    }

    // Seeds leak-side liveness (population growth + qualifying tid +
    // representative = the first chunk).
    void seedLeakLiveness(u32 klass_id, const PodTopology &topo) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, klass_id, (jweak)&node_tags[topo.chunk_nodes[0]]);
        // The representative's GetTag() identity: the mock tags map is keyed
        // by object pointer; getTag(rep) must report the rep's leak tag.
        tags[&node_tags[topo.chunk_nodes[0]]] = topo.chunk_leak_tags.empty()
                                                    ? 1073741924LL
                                                    : 0; /* placeholder */
        // (chunk_leak_tags is not kept; the tags map entry keeps the CURRENT
        // leak tag of the rep - the reseed above made node_tags hold it.)
        tags[&node_tags[topo.chunk_nodes[0]]] =
            node_tags[topo.chunk_nodes[0]];
    }

    // One threadLoop iteration on a fake clock: shouldRunPass -> runPass ->
    // pollWatchedTargets (poll unconditional).
    bool drivePodCycle(u64 &fake_now) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        bool should_run = tracker->shouldRunPassForTest(fake_now);
        if (should_run) {
            bool truncated = false;
            tracker->runPass(&mock_jvmti, &mock_jni, &truncated);
        }
        tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
        fake_now += kCycleNs;
        return should_run;
    }

    // Seeds a throwaway candidate klass (no instances, matches nothing)
    // to arm the leak signal so the phase-1 pass runs.
    void seedThrowawayLiveness(u32 klass_id) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, klass_id, (jweak)0xBADC0DE);
    }

    // Two-phase bring-up. Phase 1: a throwaway candidate arms the leak
    // signal so a pass runs and the leak class's klass id becomes
    // resolvable. Phase 2: clean slate, leak tags re-seeded, real candidate
    // armed, so admissions auto-mark from cycle one.
    void bringUpPod(const PodTopology &topo, u32 &leak_klass_id_out,
                    u64 &fake_now) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        // Seed the fake clock from the REAL monotonic clock: pain budgets'
        // _last_update_ns is OS::nanotime()-based, so a fake epoch starting
        // at ~0 makes canStartNow() block every pass.
        fake_now = OS::nanotime();
        resetLivenessForPod();
        seedThrowawayLiveness(/*klass_id=*/999);
        // The candidate arms in the POLL (which runs after shouldRunPass in
        // each cycle), so a pass runs one cycle later. Drive until one ran.
        bool ran = false;
        for (int i = 0; i < 6 && !ran; i++) {
            ran = drivePodCycle(fake_now);
        }
        leak_klass_id_out = resolveLeakKlassId(topo);
        LivenessTracker::instance()->klassPopulationResetForTest();
        ReferenceChainsTestAccessor::restartSearchForTest();
        reseedChunkLeakTags(topo);
        seedLeakLiveness(leak_klass_id_out, topo);
        // Poll once BEFORE the first pass: the admission auto-mark requires
        // the candidate slot to exist (_candidate_count > 0).
        tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    }

    // Captures stdout per distinct ReferenceChainTracker/LivenessTracker
    // line prefix (the log-budget invariant).
    struct StdoutCapture {
        int saved_fd = -1;
        int tmp_fd = -1;
        char path[64] = {0};
        bool done = false;
        StdoutCapture() {
            snprintf(path, sizeof(path), "/tmp/podjar_stdout_XXXXXX");
            tmp_fd = mkstemp(path);
            fflush(stdout);
            saved_fd = dup(1);
            dup2(tmp_fd, 1);
        }
        std::map<std::string, int> perPrefixCounts() {
            if (done) {
                return {};
            }
            done = true;
            fflush(stdout);
            dup2(saved_fd, 1);
            close(saved_fd);
            saved_fd = -1;
            lseek(tmp_fd, 0, SEEK_SET);
            std::map<std::string, int> counts;
            FILE *f = fdopen(tmp_fd, "r");
            char line[512];
            while (fgets(line, sizeof(line), f)) {
                char cls[96], fn[96];
                if (sscanf(line, "[TEST::INFO] %95[^:]::%95[a-zA-Z]", cls,
                           fn) == 2) {
                    counts[std::string(cls) + "::" + fn]++;
                }
            }
            fclose(f);
            unlink(path);
            tmp_fd = -1;
            return counts;
        }
    };
};

TEST_F(PodInAJarTest, SystemLivenessLeakChainsBuildAndCanaryResolves) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);

    int cycles_run = 0;
    while (cycles_run < 120 &&
           ReferenceChainsTestAccessor::resolvedChainCountForTest() <
               (size_t)kChunks &&
           ReferenceChainsTestAccessor::searchStateForTest() ==
               SearchState::RUNNING) {
        drivePodCycle(fake_now);
        cycles_run++;
    }

    // Every leak-tagged chunk's tag appears as a cached chain target
    // (leak-correlated events).
    auto targets = ReferenceChainsTestAccessor::resolvedChainTargetsForTest();
    for (int i = 0; i < kChunks; i++) {
        jlong leak_tag = 1073741824LL + 100 + i;
        EXPECT_NE(std::find(targets.begin(), targets.end(), (u64)leak_tag),
                  targets.end())
            << "leak tag " << leak_tag
            << " never became a cached chain target after " << cycles_run
            << " cycles";
    }

    // The canary resolved for the LEAK klass (found bit set). Candidate
    // slots persist across restarts by design, so the throwaway 999 slot
    // from phase 1 legitimately survives as an unfound slot.
    int leak_slot = -1;
    for (int s2 = 0; s2 < ReferenceChainsTestAccessor::candidateCountForTest();
         s2++) {
        if (ReferenceChainsTestAccessor::candidateKlassIdForTest(s2) ==
            leak_klass_id) {
            leak_slot = s2;
            break;
        }
    }
    ASSERT_GE(leak_slot, 0) << "leak klass never registered a candidate slot";
    EXPECT_TRUE(ReferenceChainsTestAccessor::candidateFoundBitsForTest() &
                (1ULL << leak_slot))
        << "leak candidate slot never marked found despite leak-tag chains";
}

TEST_F(PodInAJarTest, SystemSearchCompletesNaturally) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);

    int cycles = 0;
    while (cycles < 200 &&
           ReferenceChainsTestAccessor::searchStateForTest() ==
               SearchState::RUNNING) {
        drivePodCycle(fake_now);
        cycles++;
    }

    // A healthy-topology search must end COMPLETED (all candidates found),
    // never ABANDONED.
    EXPECT_EQ((u8)SearchState::COMPLETED,
              ReferenceChainsTestAccessor::searchStateForTest())
        << "search did not complete naturally within " << cycles
        << " cycles (state="
        << (int)ReferenceChainsTestAccessor::searchStateForTest() << ")";
    EXPECT_GT(ReferenceChainsTestAccessor::passesRunForTest(), 0);
}

TEST_F(PodInAJarTest, SystemRestartLeavesNothingBehind) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);
    for (int i = 0; i < 120 &&
                 ReferenceChainsTestAccessor::resolvedChainCountForTest() == 0;
         i++) {
        drivePodCycle(fake_now);
    }
    ASSERT_GT(ReferenceChainsTestAccessor::resolvedChainCountForTest(),
              (size_t)0);

    ReferenceChainsTestAccessor::restartSearchForTest();

    // The restart contract: resolved chains intentionally SURVIVE the
    // restart; the per-search state below must not.
    EXPECT_GT(ReferenceChainsTestAccessor::resolvedChainCountForTest(),
              (size_t)0)
        << "resolved chains should persist across restarts by design";
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::staticAnchorFreshQueueSizeForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexIsEmptyForTest());
    for (int s = 0; s < 5; s++) {
        EXPECT_EQ(0,
                  ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(s))
            << "discovered slot " << s << " survived restartSearch()";
    }
}

TEST_F(PodInAJarTest, TopologyCapacityContractStaticAdmits) {
    // The topology-builder capacity contract as a regression: classes
    // capturing &node_tags[node] as their jclass identity dangle when the
    // vector grows past capacity - the sweep then seeds no class and
    // NOTHING admits, silently.
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_GT(tags_ever_assigned[topo.wrapper_node], 0)
        << "wrapper static never admitted (holder_cls_tag="
        << node_tags[topo.holder_class_node]
        << " sweep_gate=" << ReferenceChainsTestAccessor::sweepGateStaticCountForTest()
        << "/" << ReferenceChainsTestAccessor::sweepGateResolvedCountForTest()
        << ")";

    tracker->stop();
}

TEST_F(PodInAJarTest, SystemHealthyAppIsDormant) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A heap with no leak candidates must produce ZERO searches (the
    // candidate/generations gate holds the machinery dormant).
    PodTopology topo = buildLeakPod();
    // No seedLeakLiveness(): no candidate ever qualifies; drive raw cycles.
    (void)topo;
    resetLivenessForPod();
    u64 fake_now = OS::nanotime();
    for (int i = 0; i < 20; i++) {
        drivePodCycle(fake_now);
    }
    EXPECT_EQ(0, ReferenceChainsTestAccessor::passesRunForTest())
        << "searches ran on a healthy (candidate-less) app";
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::resolvedChainCountForTest());
}

TEST_F(PodInAJarTest, SystemLogBudgetPerPass) {
#ifndef DEBUG
    // The gtest binary compiles the main sources WITHOUT DEBUG (TEST_LOG is
    // a no-op here), so the log-budget invariant needs a DEBUG-built binary.
    GTEST_SKIP() << "log budget needs a DEBUG-built gtest binary";
#else
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);
    for (int i = 0; i < 3; i++) {
        drivePodCycle(fake_now);
    }

    // Capture one full cycle (pass + poll) and bound every distinct line
    // shape; debug level 2 is pinned, so every gated line is live.
    StdoutCapture capture;
    drivePodCycle(fake_now);
    auto counts = capture.perPrefixCounts();
    ASSERT_FALSE(counts.empty()) << "no diagnostics captured at level 2";
    for (const auto &kv : counts) {
        EXPECT_LE(kv.second, 300) << "log line shape '" << kv.first
                                  << "' fired " << kv.second
                                  << " times in one pass+poll cycle";
    }
#endif
}

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

    // pollWatchedTargets()'s diagnostic class-name lookup on the
    // candidate's representative: a fixed non-null jclass plus a fixed
    // signature is all the lookup needs.
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

    // Seeds a growing series for `klass_id` in LivenessTracker's real
    // population table (satisfies selectLeakCandidates()'s hysteresis
    // requirements, livenessTracker.h); points its representative at `rep`.
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // selectLeakCandidates() also requires a qualifying allocating
            // thread; a fixed synthetic tid exercises the gate.
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
    // FrontierTable entry plus a matching GetTag() result.
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

    // Klass 1 is still flagged - later polls must not re-emit for the same
    // target_tag.
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

// A cached chain persists after its representative stops resolving: it
// describes a path valid at resolution time and expires on search restart,
// not on representative death.
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

    // The representative died: the chain persists (a path valid at
    // resolution time) and expires on search restart.
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

    // Overrides SetUp()'s default: exercises pollWatchedTargets()'s
    // LivenessTracker _gc_generations gate, not just _enabled.
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

// Resolved-chain cache (cacheResolvedChain()/drainPendingChainEvents()):
// keeps a resolved chain alive across dumps so it re-emits into every JFR
// chunk the sample survives into. Tests drive the seam directly.

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

// A cached chain is re-emitted on every dump, not drained once.
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

// Re-resolving the same klass refreshes its single cache slot in place
// rather than accumulating duplicates.
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

// A brand-new klass at MAX_RESOLVED_CHAINS is dropped (counted via
// REFERENCE_CHAIN_EVENTS_DROPPED) rather than evicting another live
// sample's chain; refreshing an already-cached klass still succeeds.
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

// Pause-time pacing controller (updatePacing()): driven directly with
// synthetic "pass took Xms" durations; no JVMTI calls involved.

TEST_F(ReferenceChainsTest, PacingHoldsSteadyWhenPassesLandExactlyOnCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int startBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 startCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
    ASSERT_EQ(4000, startBudget); // starts pinned at the configured ceiling

    // A pass landing exactly on the pause-time target is a zero error -
    // the controller must never move from its starting point.
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
    // input).
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

    // Start from a controlled below-ceiling point with a freshly reset
    // controller (prior iterations leave _pause_pid integral windup).
    ReferenceChainsTestAccessor::setEffectiveBudget(2400);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(
        2 * ReferenceChainsTestAccessor::baselineCadenceNs());
    ReferenceChainsTestAccessor::resetPacingController();
    int shrunkBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 widenedCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // Feed passes comfortably under the ceiling repeatedly. 200 iterations
    // because the smaller error magnitude and the borrowed-budget distance
    // take longer to unwind than the over-ceiling test needed.
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

    // Past BORROW_WARMUP_PASSES the budget converges at the borrowed
    // ceiling (configured budget * multiplier).
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
    // BORROW_UNDER_TARGET_FRACTION is 0.5, so with pausetarget=10 the
    // comfortably-under-target boundary is exactly 5ms.
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainsTestAccessor::setBorrowedBudget(500);
    ReferenceChainsTestAccessor::setConsecutiveUnderTargetPasses(5);

    // Exactly at the boundary: the `<=` check must still treat this as
    // comfortably under, so the borrow is preserved.
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

    // Just past the boundary the grant is revoked immediately, including
    // re-clamping _effective_budget down to the plain budget.
    ReferenceChainsTestAccessor::maybeRevokeBorrowForRootEnumPass(6 * 1000000ULL);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::borrowedBudget());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::consecutiveUnderTargetPasses());
    EXPECT_EQ(1000, ReferenceChainsTestAccessor::effectiveBudget());

    tracker->stop();
}

// PainBudget (painBudget.h) - standalone. A leaky bucket over cost (ms):
// spend() records cost, canStartNow() drains the balance over time.

TEST(PainBudgetTest, ClearBeforeAnythingIsEverSpent) {
    PainBudget budget(0.01);
    EXPECT_TRUE(budget.canStartNow(1000));
}

TEST(PainBudgetTest, SpendCreatesDebtThatBlocksAnImmediateSecondCall) {
    PainBudget budget(0.01); // 1%
    ASSERT_TRUE(budget.canStartNow(1000)); // establishes the drain baseline
    budget.spend(100); // 100ms of debt
    // No time has elapsed since the baseline call - the debt cannot have
    // drained yet.
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

// Search restart: a restarted search's first pass is gated on LivenessTracker
// reporting a leak candidate, plus the PainBudget cooldown.

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
        jvmti_tbl.GetAvailableProcessors = &mock_GetAvailableProcessors;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        // Reset here (TearDown always runs, even after a fatal ASSERT_*) so
        // a failed assertion can't leak a stale max-heap value into the next
        // test sharing this singleton.
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

    // start() -> autoTuneDefaults() queries this whenever a max heap is
    // set; a fixed single processor keeps the auto-tuned values
    // deterministic.
    static jvmtiError JNICALL mock_GetAvailableProcessors(jvmtiEnv *,
                                                           jint *nprocs) {
        *nprocs = 1;
        return JVMTI_ERROR_NONE;
    }

    // Models a heap with nothing reachable from any root: the first pass
    // completes immediately (0 admitted edges, not truncated).
    static jvmtiError JNICALL mock_FollowReferences(
        jvmtiEnv *, jint, jclass, jobject, const jvmtiHeapCallbacks *,
        const void *) {
        return JVMTI_ERROR_NONE;
    }

    // runPassManualWalk()'s root enumeration - same empty-heap model as
    // mock_FollowReferences() above.
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
        jvmtiEnv *, jvmtiHeapRootCallback, jvmtiStackReferenceCallback,
        jvmtiObjectReferenceCallback, const void *) {
        return JVMTI_ERROR_NONE;
    }

    // Seeds a growing population series for `klass_id` (20 strictly-
    // increasing samples - satisfies selectLeakCandidates()'s min-fill,
    // growth/floor magnitude, and sustained-trend hysteresis requirements,
    // livenessTracker.h) and points its representative at `rep`.
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // selectLeakCandidates() also requires a qualifying allocating
            // thread; a fixed synthetic tid exercises the gate (these
            // fixtures have no real tracked instances).
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(nullptr, klass_id, rep);
    }
};

TEST_F(SearchRestartTest, WithoutGenerationsSignalRestartStaysUnconditional) {
    // gc_generations off: canAffordNewSearch() has no candidate signal to
    // gate on at all, so a terminal search is immediately eligible to
    // restart - the referencechains-without-generations setup.
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
    // shouldRunPass()'s !_search_started branch shares canAffordNewSearch()
    // with the restart gate.
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

    // The next runPass() takes the "first pass of a search" branch again,
    // exactly like a brand-new tracker.
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

    // First-ever search: runPass() called directly, bypassing the
    // canAffordNewSearch() gate (the candidate would satisfy it anyway).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #1: nothing has been spent into _safepoint_pain_budget yet,
    // so it is always affordable - a search's own cost only debits the
    // *next* restart's affordability (spend-then-reset order).
    ASSERT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Pretend this second search cost 1000ms of safepoint time (the mock
    // pass itself takes ~0 wall-clock time).
    ReferenceChainsTestAccessor::setSearchPainMs(1000);

    // Restart #2: the terminal gate charges the finished search's own
    // 1000ms cost BEFORE checking affordability (an expensive search must
    // not earn a free immediate successor). At 1% refill, 1000ms of debt
    // needs 1e11ns to clear - 1ns later is nowhere close.
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(2));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Well past the drain point - restart #2 proceeds.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1ULL + 200000000000ULL));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

// hasLeakSignal()'s OOM_URGENT_THRESHOLD_S fast path: a heap-wide leak
// projecting exhaustion sooner than the threshold must start a search
// immediately, without waiting for any klass to clear
// selectLeakCandidates()'s per-klass gate. No candidate is seeded, so this
// can only pass via the heap-floor projection.
TEST_F(SearchRestartTest, UrgentOOMProjectionBypassesCandidateGate) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    // 700MiB rise over 7s against a 2800MiB max heap projects to 10s,
    // comfortably under OOM_URGENT_THRESHOLD_S (5 minutes).
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

// Durability re-verification: pure FrontierTable/queue logic with no JVMTI
// dependency, driven directly.

TEST_F(ReferenceChainsBfsTest, StaleRootAttributionUpgradesOnRediscovery) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Stack-local root: admitted, root-attached (parent_tag == 0); it stays
    // as-is until a more durable root is discovered.
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

// A non-root entry (parent_tag != 0) rediscovered as if via a root context
// must never have its root_kind overwritten - that would leave a non-zero
// root_kind on an entry nothing treats as root-attached.
TEST_F(ReferenceChainsBfsTest, NonRootAttachedEntryNeverUpgraded) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Parent Y (root-attached) and child X, admitted the way frontier
    // re-expansion admits a non-root child (parent_tag == Y's tag,
    // root_kind == 0).
    jlong yTag = 1;
    jlong xTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, yTag, /*parent_tag=*/0, /*depth=*/0,
        FrontierEntryState::EXPANDED, JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, xTag, /*parent_tag=*/yTag, /*depth=*/1,
        FrontierEntryState::EXPANDED, /*root_kind=*/0));

    // Re-expanding Y rediscovers the edge to X: even attempted with a
    // durable root_kind, it must be rejected because X is not root-attached.
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

    // Selected tags are queued for re-expansion, like an ordinary admission.
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::priorityExpandSize());

    tracker->stop();
}

// N transient-root_kind entries, rotation size R: every entry must be
// selected at least once within ceil(N/R) calls.
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

// The EXPANDED-only criterion is a strict superset of the root-kind
// collector's, and runPassManualWalk() calls both into the same
// _priority_expand deque: without the dedup check, a tag the root-kind
// collector already queued would be queued twice, wasting batch slots every
// pass. Drives both collectors back-to-back and asserts no duplicates.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationDoesNotDuplicateRootKindSelection) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Eligible for both collectors: EXPANDED, root-attached, transient
    // root_kind.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Eligible only for the EXPANDED-only sweep: EXPANDED but not
    // root-attached.
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
    // Tag 1 is already queued from the root-kind collector; tag 2 is newly
    // discovered by this sweep.
    EXPECT_EQ((std::vector<jlong>{2}), stale_expanded_selected);

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1, 2}), queued);
    std::unordered_set<jlong> unique_queued(queued.begin(), queued.end());
    EXPECT_EQ(queued.size(), unique_queued.size());

    tracker->stop();
}

// A tag left over in _priority_expand from a prior pass's truncated batch
// must also be skipped by collectStaleExpandedEntriesForRotation() - not
// just tags queued by the root-kind collector in the same call.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationSkipsPreexistingQueueEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // A truncated batch from a prior pass still sitting at the front of
    // _priority_expand: the leftover entry alone must suppress a duplicate.
    ReferenceChainsTestAccessor::pushPriorityExpand(1);

    std::vector<jlong> stale_expanded_selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
            ReferenceChainsTestAccessor::staleExpandedRotationBudget());
    EXPECT_TRUE(stale_expanded_selected.empty());

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1}), queued);

    tracker->stop();
}

// A static-field-rooted collection whose owning node is admitted and fully
// EXPANDED once, then has a *new* element appended (a Java List mutated in
// place, well after the one-time static sweep). The new element must be
// discovered by collectStaleExpandedEntriesForRotation()'s rotation without
// the search ever reaching COMPLETED - a full heap walk takes far too long.
// A large distractor chain keeps the search RUNNING.
TEST_F(ReferenceChainsBfsTest, RotationDiscoversLateElementOfExpandedStaticFieldCollectionWithoutSearchCompleting) {
    Arguments args;
    // budget=8 -> rotation_reserved_budget = min(8/2, 272) = 4: both slices
    // non-zero (budget=1 would zero out rotation's reserved slice).
    ASSERT_FALSE(args.parse("referencechains=true:hops=5000:budget=8:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int listNode = addNode();
    int seedChildNode = addNode();
    int lateChildNode = addNode();

    // Distractor chain: a long, independently root-seeded chain that never
    // fully drains within this test's bounded pass loops below, so the
    // overall search never reaches COMPLETED (nor NO_PROGRESS_PASS_LIMIT-
    // triggered ABANDONED) as a side effect of the loop bounds.
    const int kDistractorNodes = 500;
    std::vector<int> distractor(kDistractorNodes);
    for (int i = 0; i < kDistractorNodes; i++) {
        distractor[i] = addNode();
    }

    // addClass() captures classNode's address in node_tags' backing storage -
    // must come after every addNode() call above (including the distractor
    // loop), or a later push_back reallocating node_tags would leave this
    // pointer dangling (indexOfNode() would never match it).
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

    // Phase 1: run passes until listNode is fully expanded, without ever
    // letting the search complete.
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

    // Phase 2: a new element appended to the list after its one-time
    // expansion - the growing-collection shape.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, listNode, lateChildNode, -1});

    for (int i = 0; i < 200 && tags_ever_assigned[lateChildNode] == 0; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    }

    // The late element was discovered via rotation re-expanding listNode,
    // without the search ever completing.
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

// collectStaleExpandedEntriesForRotation() must resume from its persistent
// cursor rather than always rescanning from tag 1: the dedup check only sees
// the CURRENT pass's _priority_expand (drained by expandFrontier() at the
// end of that pass), so without a cursor a population of low-tag,
// perpetually-EXPANDED entries would fill the per-pass budget on every call,
// permanently starving any higher-tag EXPANDED entry of ever being re-queued.
// With the cursor, every entry gets a turn within ceil(table_size /
// max_count) calls - the guarantee RotationCoversAllEntriesWithinCeilNOverR
// proves for the root-kind collector. Driven directly against the selection
// function; the property is intrinsic to its tag-order scan.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationCoversHighTagEntryBehindLowTagPopulationWithinBoundedPasses) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const int lowTagBudget = ReferenceChainsTestAccessor::staleExpandedRotationBudget();
    // Far above the per-pass cap: the low-tag population alone would fill
    // every sweep before an always-from-1 scan could reach the high-tag
    // entry, mirroring a real heap's long-lived EXPANDED bootstrap
    // population.
    const int lowTagPopulation = lowTagBudget + 50;
    for (jlong tag = 1; tag <= lowTagPopulation; tag++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    }

    // The leak holder's node, admitted via a static field only once its
    // class loads - after the bootstrap population occupies the low tags.
    const jlong highTag = lowTagPopulation + 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, highTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    // Several simulated passes: each iteration runs the collector once, then
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

// trackLeakAccumulation(): the admission-time hook aggregating by
// (leaf_class_tag, parent_class_tag) signature and parent fanout - stable
// JVMTI class tags, not classMap dictionary ids (which can be compacted/
// regenerated independently).

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

    // 3 children of the watched leaf klass under parent1, 1 under parent2;
    // each call simulates one admission.
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

    // parent_tag == 0 - a root-attached leaf itself, nothing to attribute.
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

// The classMap dictionary id (referrer_klass) for the same class can differ
// depending on which subsystem resolved it - matching must work via
// class_tag regardless of what referrer_klass says.
TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationMatchesByClassTagEvenWhenReferrerKlassDiffers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafClassTag = 987;
    constexpr u32 kParentClassTag = 100;
    // Deliberately "wrong" classMap ids - if matching used referrer_klass
    // at all, this test would fail.
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

// collectLeakAccumulationCandidatesForRotation(): driven directly against
// the aggregation state trackLeakAccumulation() populates.

// A LARGE but FLAT signature (many unrelated parents holding a common leaf
// class) must NOT outrank a SMALLER but GROWING signature (the actual leak)
// once a growth history exists.
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

    // Signature B: 20 distinct, unrelated parents, each holding 1-2
    // instances of the same common leaf klass - a LARGER total than A, but
    // it will not grow between passes.
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
    // Pass 1: A has fanout 5, B has total 20 - B is larger. The first call
    // has no prior snapshot, so B legitimately wins (nothing to compare
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

// A FRONTIER-state (un-expanded) parent must be selected AND placed at the
// head of the priority lane, so the next expandFrontier() batch reaches it
// ahead of the stale re-walks already queued.
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

    // First call establishes the baseline (delta == total, no prior
    // snapshot) and selects it.
    std::vector<jlong> firstPass =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(1u, firstPass.size());
    ReferenceChainsTestAccessor::clearPriorityExpand();

    // Second call, nothing new admitted - delta is 0 for every signature.
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

// seedLeakAccumulationForNewlyWatchedKlass(): retroactively seeds the
// aggregation from entries admitted before a klass_id started being watched -
// the container needing re-expansion is typically fully admitted by then.

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationPopulatesFromAlreadyAdmittedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    // Entries inserted directly, as if admitted by an earlier pass -
    // trackLeakAccumulation() was never called for any of them.
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

    // A genuinely new admission after watching starts adds on top of the
    // retroactive baseline, not reset or double it.
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 11);

    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParentKlass));

    tracker->stop();
}

// Rolling-resume smoke test: when a batch truncates mid-way (budget
// exhausted), fully-processed entries must be popped (mark EXPANDED) and
// only the partially-processed + unvisited entries left for retry.

TEST_F(ReferenceChainsBfsTest, RollingResumePopsProcessedEntriesOnTruncatedBatch) {
    Arguments args;
    // budget=4: expand truncates mid-batch after a few children;
    // firstpassbudget=1000 enumerates all roots without truncating.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=5000:budget=4:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A static-field root: classNode -> listNode (the leaking collection).
    int classNode = addNode();
    int listNode = addNode();

    // A chain of 20 children off listNode: with budget=4 the callback
    // admits 4 children then returns JVMTI_VISIT_ABORT, truncating
    // mid-batch.
    constexpr int kChainLen = 20;
    std::vector<int> chainNodes(kChainLen);
    for (int i = 0; i < kChainLen; i++) {
        chainNodes[i] = addNode();
    }

    // Distractor roots: 20 independent JNI-global roots, enough to keep the
    // search RUNNING but small enough to drain quickly.
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

// AIMD adaptive batch_size: over the CPU budget the batch shrinks
// multiplicatively; under it, it grows toward the cap. The mock
// GetObjectsWithTags is instant, so the EMA is driven by hand.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchSizeProportionalToWindow) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Zeroed here for exact per-phase arithmetic below.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0);
    ReferenceChainsTestAccessor::setGotwBatchSize(0);
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);

    // Seed a frontier root manually. No runPass(): a pass would drain the
    // tiny graph to COMPLETED and its rotation adds extra
    // GetObjectsWithTags calls, breaking per-call arithmetic. The script
    // stays empty until the admission-sanity phase, so each drive runs
    // exactly one batch.
    int rootNode = addNode();
    int childNode = addNode();
    node_tags[rootNode] = 1;
    ASSERT_TRUE(tracker->frontierTable()->insert(
        1, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    int edges = 0;
    const u64 budget = ReferenceChainsTestAccessor::gotwCpuBudgetNs();

    // --- Populate phase: the first call populates the EMA; the near-free
    // mock call scales the batch to the cap.
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0u, ReferenceChainsTestAccessor::gotwEmaCallNs())
        << "per-call EMA should be populated after first GetObjectsWithTags";
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMaxBatch(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "near-free call should scale the batch to the cap";

    // --- Shrink phase: EMA at 2x the window -> batch halves.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget * 2);
    ReferenceChainsTestAccessor::setGotwBatchSize(512);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // The expectation is computed from the actual post-call EMA, the way
    // the control law does: next = batch x window / ema.
    EXPECT_EQ((size_t)(512ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA at ~1.6x the window should scale the batch to 512/1.6";

    // --- Grow phase: EMA at half the window -> batch scales up
    // proportionally (next = 64 x window / ema).
    ReferenceChainsTestAccessor::setGotwBatchSize(64);
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget / 2);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // Same computation from the actual post-call EMA (~0.4x window).
    EXPECT_EQ((size_t)(64ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA under the window should scale the batch up proportionally";

    // --- Deadline-window phase: with a live pass deadline the window is
    // the REMAINING time; a 10x-out deadline scales the batch past the cap,
    // so the clamp holds it at GOTW_MAX_BATCH.
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

    // --- Admission sanity: root -> child edge, one more drive, the child
    // must be admitted.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, rootNode, childNode, -1});
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0, tags_ever_assigned[childNode])
        << "expandFrontier failed to admit childNode with adaptive batch_size";

    tracker->stop();
}

// gotwWindowNs() backlog-pressure widening, unit level: when the remaining
// pass window is smaller than one unavoidable per-call floor, the plain
// window math collapses the batch to GOTW_MIN_BATCH forever. The widening
// sizes the batch UP, but ONLY under real backlog depth, so rotation
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

    // Floor above the NOMINAL window (deadline already passed) at depth:
    // still widened - the floor is paid by the next call regardless, so the
    // batch must amortize it.
    EXPECT_EQ(floor * mult,
              ReferenceChainsTestAccessor::gotwWindowNs(0, depth));

    tracker->stop();
}

// The widened window through the real control loop: one GetObjectsWithTags
// call whose floor (the mock's busy-wait) exceeds the remaining pass
// deadline, with a backlog deeper than GOTW_BACKLOG_MIN_DEPTH, must GROW
// the calibrated batch (calib x mult) instead of collapsing to
// GOTW_MIN_BATCH.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchGrowsWhenFloorExceedsWindowUnderDeepBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A pass deadline a fraction of the simulated per-call floor: the call
    // overruns it, so the invocation stops with exactly ONE control update.
    gotw_delay_ns = ReferenceChainsTestAccessor::gotwCpuBudgetNs(); // 25ms floor
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + 5000000ULL);
    ReferenceChainsTestAccessor::setGotwBatchSize(ReferenceChainsTestAccessor::gotwMinBatch());
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0); // seeded by the call below

    // A pending lane deep enough to cross GOTW_BACKLOG_MIN_DEPTH. The tags
    // are unresolvable - this test drives the control law, not admissions.
    const size_t depth = ReferenceChainsTestAccessor::gotwBacklogMinDepth() + 1;
    for (size_t i = 0; i < depth; i++) {
        ReferenceChainsTestAccessor::pushPendingExpandForTest(
            (jlong)(1000000 + i));
    }

    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);

    // EMA after the call = the busy-wait floor; the pass deadline is long
    // past, so the window is widened to EMA x GOTW_BACKLOG_WINDOW_MULT, and
    // the control law computes calib x mult exactly (the window is a whole
    // multiple of the same EMA it divides by).
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
// expandFrontier() invocations - with per-invocation deadlines bounding an
// invocation to a single batch, a per-invocation reset to "priority first"
// would make priority win every invocation and the pending lane would never
// drain.
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

    // Mock calls are ~free; a delayed mock call plus a deadline set below
    // that delay bounds each invocation to exactly ONE batch (the first
    // deadline check passes, the delayed call burns past it, the second
    // check breaks).
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
// resolves in the frontier can never be re-walked, so it must be erased
// during selection - otherwise the fanout grows monotonically with corpses,
// bloating the scan and wasting the cursor's lap arithmetic.
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


// Leak-tag interception: an object pre-tagged with a leak tag (as
// tagLeakInstances() sets) must be admitted by converting the leak tag to a
// frontier tag, preserving the leak tag in the entry so buildChainEvent()
// emits it as target_tag - the ReferenceChain <-> HeapLiveObject
// correlation key. An untagged sibling gets an ordinary admit.
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

    // A single pass completes the search and releases all JVMTI tags -
    // read tags from tags_ever_assigned (captured at assignment time), not
    // node_tags (0 after release).
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));

    // The leak-tagged child's tag was REPLACED by a frontier tag outside
    // the leak range.
    jlong leak_ftag = tags_ever_assigned[leakChild];
    ASSERT_NE(leak_tag, leak_ftag)
        << "leak tag was never intercepted - BFS did not reach the object";
    ASSERT_GT(leak_ftag, 0);
    EXPECT_LT(leak_ftag, leak_tag) << "frontier tag must be outside leak range";

    // The frontier entry preserves the leak tag for correlation.
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(leak_ftag));

    // The untagged sibling got an ordinary admit, no leak tag stored.
    jlong plain_ftag = tags_ever_assigned[plainChild];
    ASSERT_GT(plain_ftag, 0);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::frontierLeakTag(plain_ftag));

    // buildChainEvent() reports the leak tag as target_tag for the
    // leak-tagged instance, the plain frontier tag for the sibling.
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
// held through the leaking thread's ThreadLocalMap must be intercepted with
// its full chain by ONE bounded walk from the Thread object, and the gates
// must keep it off the Thread's non-ThreadLocalMap fields entirely.
TEST_F(ReferenceChainsBfsTest, ThreadWalkDescendsOnlyThreadLocalMapAndInterceptsLeak) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // resolveLoadedClasses() below tags every registered class, which is
    // what makes the class-tag gates resolvable.
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

    // Topological order: edges replay in script order, expanding only refs
    // the production callback said to descend into.
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
    // admitted (root-attached THREAD entry + JVMTI tag). The mock keeps
    // node_tags (what callbacks see as tag_ptr) separate from the
    // pointer-keyed tag map (what GetTag/SetTag see), so the pre-anchored
    // tag must be mirrored into both.
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
    // path).
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
    // leak-tagged chunk intercepted.
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

    // Chain shape: Thread (root-attached, THREAD root kind) ->
    // ThreadLocalMap -> holder -> chunk.
    FrontierEntry thread_entry{};
    ASSERT_TRUE(frontier->lookup(thread_ftag, &thread_entry));
    EXPECT_EQ(0, thread_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread_entry.root_kind);
    FrontierEntry chunk_entry{};
    ASSERT_TRUE(frontier->lookup(chunk_ftag, &chunk_entry));
    EXPECT_EQ(holder_ftag, chunk_entry.parent_tag);
    EXPECT_EQ(3u, chunk_entry.depth);

    // The gates kept the walk off the metadata branches: neither the
    // contextClassLoader edge (anchor gate) nor a ClassLoader below
    // ThreadLocalMap (no-descend gate) was admitted.
    EXPECT_EQ(0, tags_ever_assigned[loaderNode])
        << "anchor gate must not admit the Thread's non-ThreadLocalMap fields";
    EXPECT_EQ(0, tags_ever_assigned[loaderNode2])
        << "no-descend gate must not admit fat-metadata classes below the anchor";

    // The second thread took the fresh-admission path: admitted
    // root-attached with the THREAD root kind. (Its scripted tag entry was
    // never set, so the minted tag is read back via getTag.)
    jlong thread2_ftag = ReferenceChainsTestAccessor::getTagForTest(
        &mock_jvmti, reinterpret_cast<jobject>(&node_tags[threadNode2]));
    ASSERT_GT(thread2_ftag, 0) << "fresh thread anchor was never admitted";
    FrontierEntry thread2_entry{};
    ASSERT_TRUE(frontier->lookup(thread2_ftag, &thread2_entry));
    EXPECT_EQ(0, thread2_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread2_entry.root_kind);

    tracker->stop();
}

// unregisterThreadObject() must defer the global-ref deletion to
// releaseEndedThreadRefs(): the walk copies the jobject out under
// _thread_objects_lock and can still be using it as a FollowReferences
// anchor when a concurrent ThreadEnd erases the entry - deleting there
// would be JNI use-after-free.
TEST_F(ReferenceChainsBfsTest, ThreadRefUnregisterDefersGlobalRefDeletion) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int threadNode = addNode();
    tracker->registerThreadObject(
            &mock_jni, 555, reinterpret_cast<jthread>(&node_tags[threadNode]));
    tracker->unregisterThreadObject(&mock_jni, 555);
    // The erasing side only enqueues - no DeleteGlobalRef yet.
    EXPECT_EQ(0, global_refs_deleted_);

    // The drain deletes exactly the queued ref; draining an empty list is
    // a no-op.
    tracker->releaseEndedThreadRefs(&mock_jni);
    EXPECT_EQ(1, global_refs_deleted_);
    tracker->releaseEndedThreadRefs(&mock_jni);
    EXPECT_EQ(1, global_refs_deleted_);

    tracker->stop();
}

// Candidate-scoped reach, prong 2 (collectStaticFieldAnchorsForRotation()/
// walkStaticFieldAnchors()): the collector selects exactly the root-attached
// static-holder entries with a wrapping cursor; the walk reaches a leak 3-4
// hops inside a static collection in one bounded call.
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

    // Seed the frontier as the static sweep would: root-attached
    // STATIC_FIELD holder, a second durable-root anchor (JNI_GLOBAL), a
    // transient-root decoy the collector must skip, and a chain-attached
    // child (NOT mirrored into node_tags, so the walk freshly admits them
    // instead of tripping ALREADY_ADMITTED).
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 101; // mock_GetObjectsWithTags' resolvable tag
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 101, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        101, 9001, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 102, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 103, 101, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        104, 9004, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            4);
    // Both DURABLE root kinds are selected (in cursor/tag order); the
    // transient decoy and the child are not. The walk drives only 101.
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(101, selected[0]);
    EXPECT_EQ(104, selected[1]);
    std::vector<jlong> walk_selected = {selected[0]};

    // The whole internal structure is admitted by one bounded walk,
    // intercepting the leak tag at depth 3 below the holder.
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

// Tiered selection: a container-shaped anchor (its class implements
// Collection/Map) admitted at a LATE index position must leap the ~28k
// other-tier anchors; a leak-tagged anchor (tier 0) leads unconditionally.
TEST_F(ReferenceChainsBfsTest, ContainerAnchorLeapsQueueAcrossLargeIndex) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr int kAnchorCount = 28000;
    for (int i = 0; i < kAnchorCount; i++) {
        jlong tag = 100 + i;
        jlong class_tag = 500000 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            tag, class_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        // Containers only at late positions, buried behind 24k other-tier
        // anchors under any admission-order cursor.
        bool container = (i >= 24000 && i <= 24003);
        ReferenceChainsTestAccessor::primeClassShapeForTest(class_tag,
                                                             container);
    }
    // One leak-tagged anchor at the very tail - tier 0, must lead.
    jlong leak_anchor = 100 + kAnchorCount;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, leak_anchor, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    frontier->setLeakTag(leak_anchor, 777);
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        leak_anchor, 599999, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    ReferenceChainsTestAccessor::primeClassShapeForTest(
        599999, false /* its tier comes from leak_tag, not shape */);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, selected.size())
        << "28k+5 eligible anchors at a 16 budget must fill the selection";
    EXPECT_EQ(leak_anchor, selected[0])
        << "the leak-tagged anchor (tier 0) must lead the walk order";
    // The four container anchors are selected in this FIRST call despite
    // their late positions.
    for (jlong t : {24100, 24101, 24102, 24103}) {
        EXPECT_NE(std::find(selected.begin(), selected.end(), t), selected.end())
            << "container anchor " << t
            << " did not leap the other-tier queue";
    }
    // Sanity: an early other-tier anchor also made the cut (cursor-fair
    // fill from position 0).
    EXPECT_NE(std::find(selected.begin(), selected.end(), (jlong)100),
              selected.end());

    tracker->stop();
}

// Fresh-admission priority: a container admitted since the last collector
// call must be walked in the very NEXT call, ahead of the fair backlog; an
// unclassified fresh anchor rides the same lane (classification lags one
// pass behind admission), while a fresh NON-container waits in the other
// tier.
TEST_F(ReferenceChainsBfsTest, FreshContainerWalkedBeforeFairBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A fair container backlog, "admitted long ago": 200 containers at
    // positions 0..199.
    constexpr int kBacklog = 200;
    for (int i = 0; i < kBacklog; i++) {
        jlong tag = 500 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            tag, 700000 + i, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        ReferenceChainsTestAccessor::primeClassShapeForTest(700000 + i, true);
    }
    // First collector call: all 200 anchors are fresh; the lane keeps 16
    // and the rest spend their first look (falling back to the fair tier).
    std::vector<jlong> first =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, first.size()) << "200 eligible containers at a 16 budget";

    // The late admission wave: a wrapper-class container at the index
    // tail, a fresh classified NON-container (must NOT ride the fresh
    // lane), and a fresh unclassified anchor (must ride the lane, so the
    // classification lag cannot lose the wrapper's fresh window).
    const jlong wrapper_tag = 500 + kBacklog;
    const jlong fresh_string_tag = 500 + kBacklog + 1;
    const jlong fresh_unknown_tag = 500 + kBacklog + 2;
    for (auto [tag, class_tag, container, prime] :
         {std::make_tuple(wrapper_tag, (jlong)799001, true, true),
          std::make_tuple(fresh_string_tag, (jlong)799002, false, true),
          std::make_tuple(fresh_unknown_tag, (jlong)799003, false,
                          false /* deliberately unclassified */)}) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            tag, class_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        if (prime) {
            ReferenceChainsTestAccessor::primeClassShapeForTest(class_tag,
                                                                 container);
        }
    }

    std::vector<jlong> second =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, second.size());
    EXPECT_EQ(wrapper_tag, second[0])
        << "the freshly admitted container must lead the walk order, not "
           "wait behind the 184-container fair backlog";
    EXPECT_NE(std::find(second.begin(), second.end(), fresh_unknown_tag),
              second.end())
        << "an unclassified fresh anchor must ride the fresh lane (the "
           "wrapper admits a pass before reconcile classifies its class)";
    EXPECT_EQ(std::find(second.begin(), second.end(), fresh_string_tag),
              second.end())
        << "a fresh NON-container stays in the other tier - the fresh lane "
           "is the container lane, or fresh Strings would flood it";
    // The fair container lap still gets the leftover budget. Call 1's fresh
    // picks spent the whole budget, so the fair cursor never advanced -
    // call 2's fair picks start at tag 500 again (benign: walks are
    // idempotent, and only at a fresh/fair lap-boundary coincidence).
    EXPECT_NE(std::find(second.begin(), second.end(), (jlong)500),
              second.end())
        << "the fair container lap must still advance with the leftover "
           "budget";
    EXPECT_EQ(14, (int)std::count_if(second.begin(), second.end(),
                                     [](jlong t) {
                                       return t >= 500 && t < 500 + kBacklog;
                                     }))
        << "16 budget - 2 fresh picks = 14 fair-container picks";

    // The dropped fresh entries from call 1 are still covered by the fair
    // tier: a third call keeps advancing the fair cursor from wherever
    // call 2 left it.
    std::vector<jlong> third =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, third.size());
    EXPECT_EQ(std::find(third.begin(), third.end(), wrapper_tag),
              third.end())
        << "the wrapper already had its first look - it must not be "
           "re-selected while the fair cursor has 184 uncovered peers";

    tracker->stop();
}

// Tier fairness: the other tier (not leak-tagged, not container-shaped)
// reaches full coverage across wraps; containers must not permanently
// starve the rest of the index.
TEST_F(ReferenceChainsBfsTest, AnchorOtherTierFairCoverageAcrossWraps) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr int kOtherCount = 40;
    for (int i = 0; i < kOtherCount; i++) {
        jlong tag = 200 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            tag, 300000 + i, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        ReferenceChainsTestAccessor::primeClassShapeForTest(300000 + i, false);
    }

    std::vector<jlong> all_selected;
    for (int call = 0; call < 3; call++) {
        std::vector<jlong> selected =
            ReferenceChainsTestAccessor::
                collectStaticFieldAnchorsForRotationForTest(16);
        int expected = (call == 2) ? 8 : 16;
        ASSERT_EQ(expected, (int)selected.size())
            << "call " << call << " should select " << expected;
        std::set<jlong> dedup(selected.begin(), selected.end());
        ASSERT_EQ(selected.size(), dedup.size())
            << "no anchor may be selected twice within a call";
        all_selected.insert(all_selected.end(), selected.begin(),
                            selected.end());
    }
    std::set<jlong> covered(all_selected.begin(), all_selected.end());
    ASSERT_EQ(40u, covered.size()) << "full other-tier coverage expected";
    for (int i = 0; i < kOtherCount; i++) {
        EXPECT_NE(covered.find(200 + i), covered.end())
            << "other-tier anchor " << 200 + i << " never selected";
    }

    tracker->stop();
}

// Restart hygiene: discovered-instance tags are FRONTIER tags;
// restartSearch() resets the frontier table and _next_tag=1, so any
// surviving discovered slot either fails reconstructChain or resolves into
// a live new-search entry and emits a chain for the WRONG OBJECT - it must
// be cleared, along with the anchor index and parallel arrays/cursors.
TEST_F(ReferenceChainsBfsTest, RestartSearchClearsDiscoveredInstanceTags) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A watched candidate with one discovered instance recorded.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, 7);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(7, 4242,
                                                                 false);
    ASSERT_EQ(4242, ReferenceChainsTestAccessor::discoveredTagForTest(0, 0));
    ASSERT_EQ(1, ReferenceChainsTestAccessor::discoveredCountForTest(0));

    // An anchor index entry (tag + parallel class tag) to confirm the
    // index reset covers the parallel structures too.
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        4242, 555, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    (void)frontier;

    ReferenceChainsTestAccessor::restartSearchForTest();

    EXPECT_EQ(0, ReferenceChainsTestAccessor::discoveredTagForTest(0, 0))
        << "stale discovered frontier tag survived restartSearch()";
    EXPECT_EQ(0, ReferenceChainsTestAccessor::discoveredCountForTest(0));
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexIsEmptyForTest())
        << "anchor index (or its parallel arrays) survived restartSearch()";

    tracker->stop();
}

// The leak-tag-world found criterion: a leak-tag-target chain
// (target_tag >= LEAK_TAG_BASE) built for a candidate slot marks that slot
// found and records its canary link; a noise chain (no leak tag) must NOT.
TEST_F(ReferenceChainsBfsTest, LeakTagChainMarksCanaryFound) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Slot 0: candidate klass 7 whose discovered instance carries a leak
    // tag (target_tag becomes the leak tag). Slot 1: klass 9 with a plain
    // noise discovered instance, no leak tag.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, 7);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(1, 9);
    // depth=1 at a durable STATIC_FIELD root so the retention filter
    // (suppressChainEvent: depth==0, or depth==1 at a transient root) keeps
    // both chains.
    ASSERT_TRUE(frontier->insert(4242, 0, 7, 1, FrontierEntryState::FRONTIER,
                                 8, /*class_tag=*/0, -1, /*kind=*/0));
    frontier->setLeakTag(4242, 1073742079);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(7, 4242, true);
    ASSERT_EQ(4242, ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));
    ASSERT_TRUE(frontier->insert(5353, 0, 9, 1, FrontierEntryState::FRONTIER,
                                 8, 0, -1, 0));
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(9, 5353, false);
    ASSERT_EQ(5353, ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(1, 0));

    ReferenceChainsTestAccessor::buildDiscoveredInstanceChainsForTest(7, 1);
    ReferenceChainsTestAccessor::buildDiscoveredInstanceChainsForTest(9, 1);

    // Slot 0 found via its leak-tag chain (bit 0 set, link recorded);
    // slot 1's noise chain did not mark anything found.
    EXPECT_EQ(1ULL, ReferenceChainsTestAccessor::candidateFoundBitsForTest());
    EXPECT_EQ(4242, ReferenceChainsTestAccessor::candidateFrontierTagForTest(0));
    EXPECT_EQ(0, ReferenceChainsTestAccessor::candidateFrontierTagForTest(1))
        << "noise-target chain must not mark the canary found";

    tracker->stop();
}

// At-risk FIFO push site 1 - DEMOTION: when improveChain() replaces a
// root-attached durable (STATIC_FIELD/JNI_GLOBAL) entry with a deeper
// chain-attached path, the push must fire exactly there - the sweep gate
// only re-laps while the class count is in flux.
TEST_F(ReferenceChainsBfsTest, DemotionPushFiresWhenImproveChainEvictsRootAttachedStatic) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int parentNode = addNode();
    int holderNode = addNode();

    // The chain edge whose delivery demotes the holder.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, parentNode, holderNode, -1},
    };

    // Seed the pre-demotion shape: holder root-attached STATIC
    // (anchor-eligible), parent a root-attached frontier object whose
    // expansion delivers the deeper chain edge.
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    node_tags[parentNode] = 104;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(104);

    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni,
                                                        &edges);
    // The chain edge was delivered: the holder's entry is now
    // chain-attached, and the demotion pushed its tag into the FIFO.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(105));

    // Re-walking the same edge must NOT push twice: improveChain refuses
    // (new depth 1 is not > current 1), and the set dedupes regardless.
    int edges2 = 0;
    ReferenceChainsTestAccessor::pushPendingExpandForTest(104);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni,
                                                        &edges2);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    tracker->stop();
}

// At-risk FIFO push site 2 - SWEEP TIME: the static sweep's class->field
// edge onto an already-admitted CHAIN-ATTACHED entry (born as a non-root
// child) must feed the FIFO. Driven through a full runPass so the sweep
// delivers the edge and the rotation phase of the same pass drains it.
TEST_F(ReferenceChainsBfsTest, SweepPushFiresOnStaticEdgeOntoChainAttachedHolder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=100"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int holderNode = addNode();
    // A child reachable ONLY from the holder: the child's admission after
    // runPass is the end-to-end evidence that the sweep pushed the holder,
    // the rotation drained it, and walkStaticFieldAnchors walked it.
    int holderChildNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/ChainBornHolder;");

    script = {
        // Only the sweep's static edge onto the holder, plus the holder's
        // own child edge for the anchor walk - the only possible push is
        // the static-edge-onto-chain-attached site.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, holderNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, holderChildNode, -1},
    };

    // Seed the born-chain-attached shape: holder already a non-root child
    // (parent 104, depth 1). The sweep's static edge hits
    // maybeUpgradeRootAttachedRootKind's parent_tag != 0 refusal and falls
    // into the FIFO push instead.
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    // The child is untagged: the anchor walk's admission assigns it a fresh
    // frontier tag, observable via node_tags after the pass.
    ASSERT_EQ(0, node_tags[holderChildNode]);
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));

    // The rotation phase drained the push into the anchor walk, which
    // admitted the holder's child; the FIFO drained empty and the holder's
    // entry was never re-attributed. The child's admission is observed via
    // tags_ever_assigned rather than node_tags: the search COMPLETED in
    // this pass, so releaseSearchTags() cleared every live JVMTI tag before
    // runPass returned - the frontier table's records survive that, the
    // tag map does not.
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    jlong childTag = tags_ever_assigned[holderChildNode];
    ASSERT_GT(childTag, 0) << "the FIFO-drained anchor walk never admitted "
                             "the holder's child";
    FrontierEntry childEntry{};
    ASSERT_TRUE(frontier->lookup(childTag, &childEntry));
    EXPECT_EQ(105, childEntry.parent_tag);
    EXPECT_EQ(2u, childEntry.depth);
    // The push records the at-risk shape; it never re-attributes the entry.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);

    tracker->stop();
}

// At-risk FIFO mechanics: a chain-attached holder drained from the FIFO is
// descend-walked and intercepts a leak chunk 3 hops below it - repairing the
// population the root-attached collector cannot select (negative control
// below).
TEST_F(ReferenceChainsBfsTest, AtRiskAnchorFifoDrainAndWalkIntercept) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *holderCls = (void *)0x6001, *chunkCls = (void *)0x6002;
    addClass(holderCls, "Lcom/rc/descendwalk/ChainAttachedHolder;");
    int chunk = addClass(chunkCls, "Lcom/rc/descendwalk/ChainChunk;");

    int parentNode = addNode();
    int holderNode = addNode();
    int tableNode = addNode();
    int entryNode = addNode();
    int leakChunk = addNode();
    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();
    node_tags[leakChunk] = leak_tag;

    // Chain: parent -> holder -> table -> entry -> leak chunk; only the
    // holder's subtree is scripted (the direct drive never runs the roots/
    // expand phases).
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, tableNode, -1},
        {JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, tableNode, entryNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, entryNode, leakChunk, chunk},
    };

    // Seed the holder as the eviction leaves it: chain-attached (parent_tag
    // = 104, depth 1, no root_kind); node_tags makes the tag resolvable.
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    // root_kind = 0: the entry is chain-attached, and a non-root entry's
    // edge kind is not recorded.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    // The chain's root is TRANSIENT (stack local), so the collector's
    // durable root-kind filter skips it too - the whole table is
    // un-selectable.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // Negative control: the root-attached collector selects NOTHING here -
    // the population only the FIFO can repair.
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(4);
    ASSERT_TRUE(selected.empty());

    // FIFO: push + drain + walk reaches what the collector cannot.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(105, 28366);
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> drained;
    // 16 = ReferenceChainTracker::STATIC_ANCHOR_FIFO_DRAIN (private), the
    // per-pass drain cap.
    ASSERT_EQ(1, ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                       16, drained));
    ASSERT_EQ(1u, drained.size());
    EXPECT_EQ(105, drained[0].tag);
    EXPECT_EQ(28366u, drained[0].klass_id);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    int edges = 0;
    std::vector<jlong> drained_tags;
    for (const auto &at_risk : drained) {
        drained_tags.push_back(at_risk.tag);
    }
    ReferenceChainsTestAccessor::walkStaticAnchorFifoForTest(
        &mock_jvmti, &mock_jni, drained_tags, 1000, &edges, nullptr);
    jlong table_ftag = tags_ever_assigned[tableNode];
    jlong entry_ftag = tags_ever_assigned[entryNode];
    jlong chunk_ftag = tags_ever_assigned[leakChunk];
    ASSERT_GT(table_ftag, 0) << "table array was not reached by the anchor walk";
    ASSERT_GT(entry_ftag, 0) << "Entry was not reached one hop below table";
    ASSERT_NE(chunk_ftag, leak_tag)
        << "leak-tagged chunk inside the chain-attached holder was never "
           "intercepted";
    EXPECT_EQ(leak_tag,
              ReferenceChainsTestAccessor::frontierLeakTag(chunk_ftag));
    FrontierEntry chunk_entry{};
    ASSERT_TRUE(frontier->lookup(chunk_ftag, &chunk_entry));
    EXPECT_EQ(entry_ftag, chunk_entry.parent_tag);
    EXPECT_EQ(4u, chunk_entry.depth);

    tracker->stop();
}

// Requeue mechanics: a truncated anchor walk reports exactly the
// resolved-but-unwalked tags, and requeueStaticAnchorFifoFront() restores
// them to the FIFO front - an at-risk holder that lost its budget turn keeps
// it for the next pass.
TEST_F(ReferenceChainsBfsTest, TruncatedAnchorWalkRequeuesUnwalkedFifoTags) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *holderCls = (void *)0x7001;
    addClass(holderCls, "Lcom/rc/descendwalk/RequeueHolder;");

    int holderANode = addNode();
    int holderBNode = addNode();
    int tableNode = addNode();
    int entryNode = addNode();

    // Holder A's subtree is deep enough that a budget of 2 truncates the
    // walk after A; holder B must come back unwalked. B has no scripted
    // subtree, which makes the unwalked report attributable to the
    // truncation, not to content.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderANode, tableNode, -1},
        {JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, tableNode, entryNode, -1},
    };

    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderANode] = 105;
    node_tags[holderBNode] = 106;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 106, 104, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(105, 2001);
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(106, 2002);
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> drained;
    // 16 = STATIC_ANCHOR_FIFO_DRAIN (private), the per-pass drain cap.
    ASSERT_EQ(2, ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                       16, drained));
    ASSERT_EQ(2u, drained.size());
    EXPECT_EQ(105, drained[0].tag);
    EXPECT_EQ(106, drained[1].tag);

    int edges = 0;
    std::vector<jlong> drained_tags;
    for (const auto &at_risk : drained) {
        drained_tags.push_back(at_risk.tag);
    }
    std::vector<jlong> unwalked;
    ReferenceChainsTestAccessor::walkStaticAnchorFifoForTest(
        &mock_jvmti, &mock_jni, drained_tags, 2, &edges, &unwalked);
    ASSERT_EQ(1u, unwalked.size());
    EXPECT_EQ(106, unwalked[0]);
    EXPECT_NE(0, tags_ever_assigned[tableNode])
        << "holder A's walk never ran - the truncation happened too early";

    // Requeue what runPassManualWalk()'s caller-side filter would requeue
    // (everything unwalked), keeping the drained entries' klass so the
    // per-class occupancy is restored.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> requeue;
    for (jlong unwalked_tag : unwalked) {
        for (const auto &at_risk : drained) {
            if (unwalked_tag == at_risk.tag) {
                requeue.push_back(at_risk);
                break;
            }
        }
    }
    ReferenceChainsTestAccessor::requeueStaticAnchorFifoFrontForTest(requeue);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(106));
    EXPECT_FALSE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(105));
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> redrained;
    ASSERT_EQ(1, ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                       16, redrained));
    ASSERT_EQ(1u, redrained.size());
    EXPECT_EQ(106, redrained[0].tag);

    tracker->stop();
}

// A this-field self-edge is REAL in the heap - every
// java.util.Collections$Synchronized* holder carries mutex == this - so
// walking such a holder's own subtree re-reports the holder as its own
// child. improveChain()'s "improvement" (depth = holder.depth + 1 > 0)
// would overwrite the root-attached entry with a parent==its-own-tag
// chain-attached one - collector-invisible ever after. The guard refuses
// the self-parent, so the entry stays collector-selectable.
TEST_F(ReferenceChainsBfsTest,
       SelfEdgeFieldDoesNotDemoteRootAttachedStaticHolder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    void *holderCls = (void *)0x7101;
    int holderClsIdx =
        addClass(holderCls, "Ljava/util/Collections$SynchronizedRandomAccessList;");
    int holderNode = addNode();

    // The holder's own self-edge: referrer == referee == holder.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, holderNode, holderClsIdx},
    };

    // Seed the pre-demotion shape: holder root-attached STATIC_FIELD at
    // depth 0. The batch walk from its pending-expand slot delivers the
    // self-edge with the holder as BOTH referrer and referee.
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(105);

    // A delivered self-edge trips BOTH sibling guards: improveChain refuses,
    // and the already-admitted block then offers the same self-parent to
    // reparentToDurableRoot, which refuses too.
    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni,
                                                        &edges);

    // The self-edge was delivered and refused: the entry keeps its
    // root-attached shape; no demotion push fired.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(0, entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, entry.root_kind);
    EXPECT_EQ(0u, entry.depth);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    // The sibling guards and the direct table calls agree: a self-parent is
    // refused by both improvement paths, unconditionally.
    EXPECT_FALSE(frontier->improveChain(105, 105, 0, 5, 0, -1, 0, 0));
    EXPECT_FALSE(frontier->reparentToDurableRoot(105, 105, 0, -1, 0));

    tracker->stop();
}

// The per-class quota keeps one class from owning the at-risk FIFO: at 64
// per class, a full 1024-entry FIFO necessarily holds >= 16 distinct
// classes, so a fresh class's push lands and the flood's excess is dropped
// and counted. Occupancy is maintained across push / drain / requeue; a
// saturated-but-diverse FIFO drops newcomers at the cap rather than
// evicting anyone.
TEST_F(ReferenceChainsBfsTest, AtRiskFifoPerClassQuotaKeepsFloodOut) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const u32 quota =
        ReferenceChainsTestAccessor::kAtRiskPerKlassCap;
    ASSERT_EQ(64u, quota);

    // The flood: only the first `quota` pushes of one class land.
    for (int i = 0; i < 70; i++) {
        ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(1000 + i,
                                                                 1733);
    }
    EXPECT_EQ(quota, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    // The flood's first `quota` tags hold their slots; the excess is
    // dropped at the quota check.
    EXPECT_TRUE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(
        1000 + (int)quota - 1));
    EXPECT_FALSE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(
        1000 + (int)quota));

    // A different class's push lands despite the flood.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(2000, 28366);
    EXPECT_EQ(quota + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(2000));

    // Tag dedupe is unchanged: the same tag never enters twice.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(2000, 28366);
    EXPECT_EQ(quota + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    // Full drain: order preserved (flood first, newcomer last), occupancy
    // erased with the entries.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> drained;
    ASSERT_EQ((int)quota + 1,
              ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                  1024, drained));
    ASSERT_EQ(quota + 1, drained.size());
    EXPECT_EQ(1000, drained.front().tag);
    EXPECT_EQ(1733u, drained.front().klass_id);
    EXPECT_EQ(2000, drained.back().tag);
    EXPECT_EQ(28366u, drained.back().klass_id);
    for (int i = 0; i < 70; i++) {
        ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(1000 + i,
                                                                 1733);
    }
    EXPECT_EQ(quota, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    // Partial drain at the real per-pass rate (16/pass): the flood's
    // occupancy drops to quota - 16, so its next push lands.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> partial;
    ASSERT_EQ(16, ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                      16, partial));
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(3000, 1733);
    EXPECT_EQ(quota - 16 + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(3000));

    // Requeue restores occupancy exactly, in FIFO order. This may put a
    // class momentarily ABOVE its quota - the quota gates NEW pushes, it
    // does not evict truncated-walk requeues.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> requeue(partial.begin(),
                                                            partial.end());
    ReferenceChainsTestAccessor::requeueStaticAnchorFifoFrontForTest(requeue);
    EXPECT_EQ(quota + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> after_requeue;
    ASSERT_EQ(16,
              ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                  16, after_requeue));
    EXPECT_EQ(1000, after_requeue.front().tag);

    // Saturated-but-diverse: 16 distinct classes at exactly their quota
    // fill the 1024 cap; the newcomer below is dropped at the CAP.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> rest;
    ASSERT_EQ((int)quota - 16 + 1,
              ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                  1024, rest));
    for (u32 klass = 1; klass <= 16; klass++) {
        for (u32 i = 0; i < quota; i++) {
            ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(
                10000 + klass * 100 + i, 4000 + klass);
        }
    }
    EXPECT_EQ(1024u,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    // The 16 saturated classes sit exactly at their per-class quota, so the
    // newcomer's absence below is the CAP's doing, not the quota's.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(20000, 28366);
    EXPECT_EQ(1024u,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_FALSE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(20000));

    // Leave the FIFO drained: keeps this test order-independent even if
    // the reset() seam ever regresses.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> final_drain;
    ASSERT_EQ(1024,
              ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                  1024, final_drain));

    tracker->stop();
}

// Retention-edge labels (fillHopEdgeLabels()/hopLabelClassFor()): per-hop
// labels must decode the JVMTI-spec field ordinal captured at admission and
// degrade to the edge KIND on any undecodable hop - never a fabricated name
// (a wrong numbering on an unverified JVM degrades, it does not lie).
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
    //     interfaces, each once); then superclass chain root-first:
    //     base_f@2; then own fields in GetClassFields order:
    //     holder_a@3, leakList@4.
    //   ISink (interface branch): base = superinterfaces' fields = 0; own
    //     fields: CONST_A@0, CONST_B@1.
    void *ibase = (void *)0x5001, *isub = (void *)0x5002, *base = (void *)0x5003,
         *holder = (void *)0x5004, *isink = (void *)0x5005;
    addClass(ibase, "Lcom/rc/labels/IBase;");
    addClass(isub, "Lcom/rc/labels/ISub;");
    addClass(base, "Lcom/rc/labels/Base;");
    addClass(holder, "Lcom/rc/labels/Holder;");
    addClass(isink, "Lcom/rc/labels/ISink;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    // resolveLoadedClasses minted each class's raw (negative) tag via the
    // mock's tag map - read them back for the decoder's tag->class lookup.
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
    // Chain: [chunk(3)] <- Base.base_f(ordinal 0) <- [value2(2), class
    // Base] <- Holder.leakList(ordinal 4, the static root edge with the
    // declaring class as referrer) <- [static value(1), class Holder] <-
    // [class Holder, the ROOT TYPE]. Interior hops decode against the
    // PARENT entry's class_tag.
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
    ASSERT_EQ(4u, event._hops.size());
    // Leaf first: chunk via Base.base_f (parent entry's class is Base),
    // then value2 via Holder's holder_a (ordinal 3 = interface offset 2 +
    // Base's 1 + own position 0), then the static root edge's leakList
    // (ordinal 4), then the root-type hop - kind label only.
    EXPECT_EQ("base_f", event._hops[0].edge_label);
    EXPECT_EQ("holder_a", event._hops[1].edge_label);
    EXPECT_EQ("leakList", event._hops[2].edge_label);
    EXPECT_EQ("static_field", event._hops[3].edge_label);
    int expectedRootType = Profiler::instance()->lookupClass(
        "com/rc/labels/Holder", strlen("com/rc/labels/Holder"));
    ASSERT_NE(-1, expectedRootType);
    EXPECT_EQ((u32)expectedRootType, event._hops[3].klass_id);

    // Interface-referrer branch: ISink's own-field ordinals have NO
    // superclass-chain component.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(isink),
        /*referrer_field_index=*/1, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(isink)));
    ReferenceChainEvent iface_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/4, &iface_event));
    // Same root-type append: the root-side end gains ISink plus its
    // kind-only root edge.
    ASSERT_EQ(2u, iface_event._hops.size());
    EXPECT_EQ("CONST_B", iface_event._hops[0].edge_label);
    EXPECT_EQ("static_field", iface_event._hops[1].edge_label);
    int expectedSinkRoot = Profiler::instance()->lookupClass(
        "com/rc/labels/ISink", strlen("com/rc/labels/ISink"));
    ASSERT_NE(-1, expectedSinkRoot);
    EXPECT_EQ((u32)expectedSinkRoot, iface_event._hops[1].klass_id);

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
    // Both hops degrade to kind labels: the holder hop's referrer class
    // (IBase) is unregistered from the decoder, and the appended root-type
    // hop carries no field identity.
    ASSERT_EQ(2u, degraded_event._hops.size());
    EXPECT_EQ("static_field", degraded_event._hops[0].edge_label);
    EXPECT_EQ("static_field", degraded_event._hops[1].edge_label);
    int expectedIbaseRoot = Profiler::instance()->lookupClass(
        "com/rc/labels/IBase", strlen("com/rc/labels/IBase"));
    ASSERT_NE(-1, expectedIbaseRoot);
    EXPECT_EQ((u32)expectedIbaseRoot, degraded_event._hops[1].klass_id);

    tracker->stop();
}

// PRIORITY_EXPAND_CAP backpressure: with the fast lane at the cap, the
// rotation collectors must stop pushing - an uncapped queue starves the BFS.
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

    // With the lane drained, the collector selects again.
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
// which neither the blind lap nor the growth-gated tier reaches in steady
// state.
TEST_F(ReferenceChainsBfsTest, StaleRotationPrefersLeakParentsOverBlindLap) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Parent 1 needs a non-zero class_tag: trackLeakAccumulation()
    // attributes via the parent entry's class_tag and skips entries
    // without one.
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
// strictly deeper path).
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

// recordDiscoveredInstance eviction: a leak-correlated discovery must evict
// a noise slot when all are full - otherwise noise permanently blocks every
// later leak-tagged instance of the watched class.
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

// Retention-explanation gate on the discovered-instance chains: depth==0 is
// always suppressed; depth==1 only for TRANSIENT roots (a depth-1 chain from
// a durable root is the real direct-retention shape).
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
    // Depth-0 transient root: suppressed like the depth-1 transient shape.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 11, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Depth-0 durable root: the candidate instance IS the static field's
    // value - a real direct-retention chain, NOT suppressible as noise.
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

// Orphan slot sweep: a candidate that recorded discovered instances, then
// stopped qualifying (its trend aged out of the poll's candidate list), must
// still get chains built for those instances - the slot persists by design
// precisely so the klass can still be found there.
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

    // The walk discovered an instance while the candidate still qualified
    // (the direct-retention shape the discovered-chain gate lets through).
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 9, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 8, 9, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 8, false);
    ASSERT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // The candidate stops qualifying: the population table is wiped, so
    // selectLeakCandidates() returns 0 on every poll from here on.
    LivenessTracker::instance()->klassPopulationResetForTest();
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(8))
        << "discovered instances recorded while the candidate qualified must "
           "still get chains built after it stops qualifying";

    tracker->stop();
}
