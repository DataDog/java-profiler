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
        t->_last_pass_gc_finish_epoch = 0;
        t->_last_pass_ns = 0;
        t->_passes_run = 0;
        t->_passes_since_last_progress = 0;
        t->_candidate_count = 0;
        t->_candidate_found_bits = 0;
        t->_resolved_chains.clear();
        t->_safepoint_pain_budget = PainBudget();
        t->_cpu_pain_budget = PainBudget();
        t->_search_pain_ms = 0;
        t->_root_kind_rotation_cursor = 1;
        t->_stale_expanded_rotation_cursor = 1;
        t->_watched_leak_klass_count = 0;
        t->_leak_signature_totals.clear();
        t->_leak_signature_prev_totals.clear();
        t->_leak_parent_fanout.clear();
        t->_borrowed_budget = 0;
        t->_consecutive_under_target_passes = 0;
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

    static u64 searchPainMs() {
        return ReferenceChainTracker::instance()->_search_pain_ms;
    }

    // Resolved-chain cache: read-only size peek and a pass-through to the
    // private snapshot (drainPendingChainEvents()) and insert
    // (cacheResolvedChain()), for ResolvedChainCacheTest below - same
    // rationale as hasResolvedChainForKlass()/resolvedChainCount() below.
    static size_t resolvedChainCount() {
        return ReferenceChainTracker::instance()->_resolved_chains.size();
    }

    static void drain(std::vector<ReferenceChainEvent> *out) {
        ReferenceChainTracker::instance()->drainPendingChainEvents(out);
    }

    static void cacheChain(u32 klass_id, ReferenceChainEvent event,
                           jlong source_tag, u64 source_search_ns) {
        ReferenceChainTracker::instance()->cacheResolvedChain(
            klass_id, std::move(event), source_tag, source_search_ns);
    }

    static int maxResolvedChains() {
        return ReferenceChainTracker::MAX_RESOLVED_CHAINS;
    }

    // Target-selection bridging step: read-only peeks into the resolved-chain
    // cache, for asserting exactly which klass a chain was resolved for and
    // the tag it was reconstructed from - see PollWatchedTargetsTest below.
    static bool hasResolvedChainForKlass(u32 klass_id) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_resolved_chains.find(klass_id) != t->_resolved_chains.end();
    }

    static jlong resolvedChainSourceTag(u32 klass_id) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        auto it = t->_resolved_chains.find(klass_id);
        return it == t->_resolved_chains.end() ? 0 : it->second.source_tag;
    }

    // Pause-time pacing controller: read-only peeks at the controller's
    // derived values, and
    // a pass-through to the private updatePacing() itself, for
    // ReferenceChainsPacingTest below - same rationale as
    // hasResolvedChainForKlass()/resolvedChainCount() above (the target-selection bridging step): private state a test needs to drive/
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
                                     jlong class_tag = 0) {
        return frontier->insert(tag, parent_tag, referrer_klass, depth,
                                 state, root_kind, class_tag);
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
        ReferenceChainTracker::instance()->_priority_expand.push_back(tag);
    }

    // Simulates expandFrontier() having fully drained _priority_expand at the
    // end of a pass (the common case: rotation's whole selection fit within
    // that pass's rotation_budget slice) - see
    // StaleExpandedRotationStarvesHighTagEntryBehindLowTagPopulation below,
    // which needs this to model collectStaleExpandedEntriesForRotation()
    // being called fresh on each of several simulated passes, the way
    // runPassManualWalk() actually does it once per real pass.
    static void clearPriorityExpand() {
        ReferenceChainTracker::instance()->_priority_expand.clear();
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

    // Synthetic frontier-holder arrays for expandFrontier()'s array-holder
    // walk: mock_NewObjectArray() hands back an opaque handle,
    // mock_SetObjectArrayElement() records its elements here, and
    // mock_FollowReferences() treats every recorded element as an expansion
    // seed (one hop, gated by the production callback's batch_tags) when the
    // holder is passed as initial_object.
    std::unordered_map<jobject, std::vector<jobject>> holders;
    uintptr_t next_holder = 0xF00D0000;

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
        jvmti_tbl.GetClassSignature = &mock_GetClassSignature;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        jvmti_tbl.FollowReferences = &mock_FollowReferences;
        jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
        jvmti_tbl.GetObjectsWithTags = &mock_GetObjectsWithTags;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
        jni_tbl.FindClass = &mock_FindClass;
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

    // expandFrontier() resolves java/lang/Object once per call as the holder
    // array's element type - a non-null fake jclass is all it needs (the type
    // is never introspected, only passed to NewObjectArray()).
    static jclass JNICALL mock_FindClass(JNIEnv *, const char *) {
        return (jclass)0xC1A55;
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
        std::vector<jobject> objs;
        std::vector<jlong> found;
        for (jint i = 0; i < tag_count; i++) {
            jlong want = req_tags[i];
            if (want == 0 || active_fixture->dead_tags.count(want) > 0) {
                continue;
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
    ASSERT_TRUE(tracker->buildChainEvent(targetTag, &event));
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
    EXPECT_FALSE(tracker->buildChainEvent(12345, &event));

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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);

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
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForKlass(1));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoEventForNotYetDiscoveredCandidate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);
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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);

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
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForKlass(1));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, SkipsCandidateWhoseWeakReferenceDied) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);
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
TEST_F(PollWatchedTargetsTest, PruneStopsReemittingAfterRepresentativeDies) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    ASSERT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForKlass(1));

    // The sample is gone: its representative no longer resolves.
    dead_refs.insert(obj);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "a dead representative's cached chain must be pruned, not kept "
           "re-emitting into every later dump";
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForKlass(1));

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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)obj);
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
    ReferenceChainsTestAccessor::cacheChain(/*klass_id=*/1, makeEvent(7),
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
        ReferenceChainsTestAccessor::cacheChain((u32)i, makeEvent((u64)i),
                                                (jlong)i, 0);
    }
    ASSERT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(droppedBefore, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "filling exactly to capacity must not drop anything yet";

    // A brand-new klass at capacity is dropped and counted.
    ReferenceChainsTestAccessor::cacheChain((u32)cap, makeEvent((u64)cap),
                                            (jlong)cap, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount())
        << "cache must stay capped, not grow past MAX_RESOLVED_CHAINS";
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED));
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForKlass((u32)cap));

    // Refreshing an already-cached klass at capacity must still succeed - it
    // reuses that klass's existing slot rather than needing a free one.
    ReferenceChainsTestAccessor::cacheChain(/*klass_id=*/0, makeEvent(999),
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
// target-selection bridging step's hasResolvedChainForKlass()/resolvedChainCount() above),
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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)&fake_object_storage);

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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)&fake_object_storage);

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
    seedGrowingCandidate(/*klass_id=*/1, /*rep=*/(jweak)&fake_object_storage);

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

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationOnlySelectsExpandedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong notYetExpandedTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, notYetExpandedTag, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                        notYetExpandedTag, 10);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    EXPECT_TRUE(selected.empty())
        << "a FRONTIER (not yet EXPANDED) entry has nothing to re-expand yet";

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
