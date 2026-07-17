/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
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
        t->_next_class_tag_magnitude = 1;
        t->_search_started = false;
        t->_tags_released = true;
        t->_search_state = SearchState::RUNNING;
        t->_abandon_reason = SearchAbandonReason::NONE;
        t->_search_start_ns = 0;
        t->_pending_expand.clear();
        t->_last_pass_gc_finish_epoch = 0;
        t->_last_pass_ns = 0;
        t->_passes_run = 0;
        t->_emitted_target_tags.clear();
        t->_emitted_search_start_ns = 0;
        t->_pending_chain_events.clear();
        t->_pain_budget = PainBudget();
        t->_search_pain_ms = 0;
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

    static u64 searchPainMs() {
        return ReferenceChainTracker::instance()->_search_pain_ms;
    }

    // Pending-events queue: read-only size peek and a pass-through to the
    // private drainPendingChainEvents(), for PendingChainEventsQueueTest
    // below - same rationale as hasEmittedTag()/emittedCount() above.
    static size_t pendingCount() {
        return ReferenceChainTracker::instance()->_pending_chain_events.size();
    }

    static void drain(std::vector<ReferenceChainEvent> *out) {
        ReferenceChainTracker::instance()->drainPendingChainEvents(out);
    }

    static void enqueue(ReferenceChainEvent event) {
        ReferenceChainTracker::instance()->enqueueChainEvent(std::move(event));
    }

    static int maxPendingChainEvents() {
        return ReferenceChainTracker::MAX_PENDING_CHAIN_EVENTS;
    }

    // Target-selection bridging step: read-only peek at pollWatchedTargets()'s de-dup set, for
    // asserting exactly which target_tags it has emitted an event for so
    // far this search - see PollWatchedTargetsTest below.
    static bool hasEmittedTag(jlong tag) {
        ReferenceChainTracker *t = ReferenceChainTracker::instance();
        return t->_emitted_target_tags.find(tag) != t->_emitted_target_tags.end();
    }

    static size_t emittedCount() {
        return ReferenceChainTracker::instance()->_emitted_target_tags.size();
    }

    // Pause-time pacing controller: read-only peeks at the controller's
    // derived values, and
    // a pass-through to the private updatePacing() itself, for
    // ReferenceChainsPacingTest below - same rationale as hasEmittedTag()/
    // emittedCount() above (the target-selection bridging step): private state a test needs to drive/
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
        jvmti_tbl.GetObjectsWithTags = &mock_GetObjectsWithTags;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
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
        int seed_idx = -2; // -2 = root walk (initial_object == NULL)
        if (initial_object != nullptr) {
            seed_idx = active_fixture->indexOfNode(initial_object);
            expandable[seed_idx] = true;
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
    // budget=1: only one new frontier entry may be admitted this pass.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // admitted (1st)
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // budget exhausted
    };

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Budget exhaustion for *this pass* leaves pending work (nodeB's own
    // edge was never even attempted) - the search stays RUNNING, not
    // COMPLETED, so no tag release happens yet and node_tags[nodeA] is still
    // the real assigned tag.
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]);

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
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1"));
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

TEST_F(ReferenceChainsBfsTest, FrontierCapAbandonsSearchAndReleasesTags) {
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
    // Frontier-size cap, not just this pass's budget, was hit - the whole
    // search is abandoned immediately (design doc's Termination section),
    // rather than staying RUNNING for a later pass to retry.
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());

    // Tag release on abandonment (design doc's Termination section; the
    // exit criteria for this work: "an abandoned search cleans up its tags
    // completely, no leak") - nodeA's tag was assigned in this same call,
    // then released before runPass() returned.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]); // never admitted at all

    // Abandonment reason and the JFR-event builder built from it.
    EXPECT_EQ(SearchAbandonReason::FRONTIER_CAP, tracker->abandonReason());
    ReferenceChainAbandonedEvent event;
    ASSERT_TRUE(tracker->buildAbandonedEvent(&event));
    EXPECT_EQ(SearchAbandonReason::FRONTIER_CAP, event._reason);
    EXPECT_EQ(1, event._passes_run);
    EXPECT_EQ(1, event._frontier_size); // the one slot framecap=1 allowed
    EXPECT_EQ(64, event._hop_cap);
    EXPECT_EQ(1000, event._budget);

    // A further runPass() call is a no-op - the search already reached a
    // terminal outcome (starting a new search once one ends is not
    // implemented - see runPass()'s own comment).
    int passesBefore = tracker->passesRun();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(passesBefore, tracker->passesRun());

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
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1}, // fits (the one slot)
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},   // frontier cap hit
    };

    long long failedBefore =
        Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED);

    fail_get_objects_with_tags = true;
    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    // Frontier-cap abandonment itself is independent of whether the tag
    // release that follows succeeds.
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());

    // GetObjectsWithTags() failed - nodeA's still-live tag must NOT have been
    // cleared, and the failure must be counted (previously silently
    // swallowed).
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]) << "tag must not be cleared when the "
                                       "release batch itself failed";
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 1,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // While the release is still outstanding, shouldRunPass() must force a
    // retry unconditionally - restartSearch()'s _next_tag reset must never
    // run while a stale tag could still be live (see shouldRunPass()'s own
    // comment).
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState())
        << "must retry the release in place, not restart, while tags are "
           "still unreleased";

    // A further runPass() call retries the release; still failing, it must
    // still refuse to mark the tag released.
    int passesBefore = tracker->passesRun();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(passesBefore, tracker->passesRun());
    EXPECT_NE(0, node_tags[nodeA]);
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // Once GetObjectsWithTags() starts succeeding again, the very next
    // runPass() call must actually clear the tag and confirm the release.
    fail_get_objects_with_tags = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 2,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED))
        << "a successful release must not itself count as a failure";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TTLAbandonsSearchAndReleasesTags) {
    Arguments args;
    // ttl=1 (1ms) with budget=1 on a graph deeper than one pass can cover -
    // the wall-clock TTL, not the hop/frontier cap, should force
    // abandonment here.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeC, -1},
    };

    bool truncated = false;
    // Pass 1 (root walk): admits nodeA only, budget exhausted.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    std::this_thread::sleep_for(std::chrono::milliseconds(5)); // exceed the 1ms TTL

    // Pass 2 (resumed): still has pending work (nodeB/nodeC undiscovered),
    // but the TTL from the search's first pass has now elapsed.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());

    // Tags released, including nodeA's from pass 1.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);

    // TTL, not the frontier cap, is reported as the reason.
    EXPECT_EQ(SearchAbandonReason::TTL, tracker->abandonReason());
    ReferenceChainAbandonedEvent event;
    ASSERT_TRUE(tracker->buildAbandonedEvent(&event));
    EXPECT_EQ(SearchAbandonReason::TTL, event._reason);
    EXPECT_EQ(2, event._passes_run);
    EXPECT_EQ(1, event._ttl_ms);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ResolveOrDropPrunesDeadFrontierEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();

    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
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
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.NewLocalRef = &mock_NewLocalRef;
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
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

    static jobject JNICALL mock_NewLocalRef(JNIEnv *, jobject ref) {
        if (active_fixture->dead_refs.count(ref) > 0) {
            return nullptr;
        }
        return ref; // identity passthrough - see this fixture's own comment
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject values are not real JNI refs.
    }

    // Seeds LivenessTracker's real population table with a growing series
    // for `klass_id` (10 strictly-increasing samples - satisfies
    // selectLeakCandidates()'s min-fill and positive-slope requirements,
    // livenessTracker.h) and points its representative at `rep`.
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 10; i++) {
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

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::emittedCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasEmittedTag(7));

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

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::emittedCount());

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

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::emittedCount());

    // Klass 1 is still flagged (LivenessTracker's ranking doesn't know an
    // event was already emitted for it) - a second, third, ... poll must
    // not re-emit for the same target_tag.
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::emittedCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasEmittedTag(7));

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

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::emittedCount());

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

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::emittedCount());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Pending-events queue (ReferenceChainTracker::enqueueChainEvent()/
// drainPendingChainEvents(), referenceChains.cpp) - the mechanism that keeps
// Profiler::writeReferenceChain()'s blocking lock-acquisition retry loop off
// the BFS scheduling thread (see _pending_chain_events' own comment,
// referenceChains.h). These tests drive enqueueChainEvent()/
// drainPendingChainEvents() directly via ReferenceChainsTestAccessor rather
// than through the full pollWatchedTargets()/selectLeakCandidates() pipeline
// - the queue/eviction/counter mechanism is independent of how an event was
// produced, and driving it through hundreds of real LivenessTracker
// candidates just to reach MAX_PENDING_CHAIN_EVENTS would test the seeding
// helper, not this mechanism.
// ---------------------------------------------------------------------------

class PendingChainEventsQueueTest : public ::testing::Test {
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

// Models two dumps in quick succession: drain() after the first enqueue must
// return exactly that one event and leave the queue empty, so a second
// enqueue+drain pair (the next dump) sees only its own new event - never a
// repeat of the first, and never an empty second drain silently swallowing
// the second event because it was mistaken for already-reported.
TEST_F(PendingChainEventsQueueTest, TwoDrainsInSuccessionEachSeeOnlyTheirOwnEvent) {
    ReferenceChainsTestAccessor::enqueue(makeEvent(7));

    std::vector<ReferenceChainEvent> firstDump;
    ReferenceChainsTestAccessor::drain(&firstDump);
    ASSERT_EQ(1u, firstDump.size());
    EXPECT_EQ(7u, firstDump[0]._target_tag);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingCount());

    // A dump taken right after, with nothing new queued, must not re-report
    // the first dump's event.
    std::vector<ReferenceChainEvent> emptyDump;
    ReferenceChainsTestAccessor::drain(&emptyDump);
    EXPECT_TRUE(emptyDump.empty());

    ReferenceChainsTestAccessor::enqueue(makeEvent(8));
    std::vector<ReferenceChainEvent> secondDump;
    ReferenceChainsTestAccessor::drain(&secondDump);
    ASSERT_EQ(1u, secondDump.size());
    EXPECT_EQ(8u, secondDump[0]._target_tag);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingCount());
}

// Multiple events enqueued between two dumps must all land in the same
// drain, in the order they were discovered - not split across dumps or
// reordered.
TEST_F(PendingChainEventsQueueTest, MultipleEnqueuesBeforeOneDrainAllArriveTogether) {
    ReferenceChainsTestAccessor::enqueue(makeEvent(1));
    ReferenceChainsTestAccessor::enqueue(makeEvent(2));
    ReferenceChainsTestAccessor::enqueue(makeEvent(3));
    ASSERT_EQ(3u, ReferenceChainsTestAccessor::pendingCount());

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(3u, dump.size());
    EXPECT_EQ(1u, dump[0]._target_tag);
    EXPECT_EQ(2u, dump[1]._target_tag);
    EXPECT_EQ(3u, dump[2]._target_tag);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingCount());
}

// Filling the queue past MAX_PENDING_CHAIN_EVENTS without an intervening
// drain (a search that discovers candidates faster than dump() is called)
// must evict the oldest entry - not grow without bound - and must count
// every eviction via REFERENCE_CHAIN_EVENTS_DROPPED (this codebase's own
// "dropped-event-without-counter" review lens) rather than silently losing
// it.
TEST_F(PendingChainEventsQueueTest, OverflowEvictsOldestAndCountsTheDrop) {
    const int cap = ReferenceChainsTestAccessor::maxPendingChainEvents();
    long long droppedBefore = Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED);

    for (int i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::enqueue(makeEvent((u64)i));
    }
    ASSERT_EQ((size_t)cap, ReferenceChainsTestAccessor::pendingCount());
    EXPECT_EQ(droppedBefore, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "filling exactly to capacity must not evict anything yet";

    // One more push past capacity - must evict tag 0 (the oldest) and count it.
    ReferenceChainsTestAccessor::enqueue(makeEvent((u64)cap));
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::pendingCount())
        << "queue must stay capped, not grow past MAX_PENDING_CHAIN_EVENTS";
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED));

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ((size_t)cap, dump.size());
    // Tag 0 (the oldest) was evicted and permanently lost - it must not
    // appear anywhere in the drained result. Tag 1 (the new oldest survivor)
    // through `cap` must all be present, in order.
    for (size_t i = 0; i < dump.size(); i++) {
        EXPECT_EQ((u64)(i + 1), dump[i]._target_tag);
    }
}

// ---------------------------------------------------------------------------
// Pause-time pacing controller: pause-time-SLO feedback loop
// (ReferenceChainTracker::updatePacing(), referenceChains.cpp) - see that
// method's own comment (referenceChains.h) for the full mechanism. These
// tests drive updatePacing() directly with a synthetic sequence of "pass
// took Xms" wall-clock durations via ReferenceChainsTestAccessor (this
// file's existing pattern for reaching a private method/state - see the
// target-selection bridging step's hasEmittedTag()/emittedCount() above),
// reusing the ReferenceChainsTest fixture since updatePacing() itself makes
// no JVMTI calls.
// ---------------------------------------------------------------------------

TEST_F(ReferenceChainsTest, PacingHoldsSteadyWhenPassesLandExactlyOnCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int startBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 startCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
    ASSERT_EQ(1000, startBudget); // starts pinned at the configured ceiling

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
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=5"));
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
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=5"));
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
    ReferenceChainsTestAccessor::setEffectiveBudget(200);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(
        2 * ReferenceChainsTestAccessor::baselineCadenceNs());
    ReferenceChainsTestAccessor::resetPacingController();
    int shrunkBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 widenedCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // Now feed passes comfortably under the ceiling, repeatedly (a constant
    // input, to check convergence rather than oscillation). 50 iterations -
    // more than PacingShrinksBudgetAndWidensCadenceWhenOverCeiling needs -
    // because this scenario's error magnitude (pausetarget=5 vs. an
    // effectively-instant 0ms pass) is smaller, so the cadence side takes
    // more iterations to fully unwind down to MIN_EFFECTIVE_CADENCE_NS.
    int lastBudget = shrunkBudget;
    u64 lastCadence = widenedCadence;
    for (int i = 0; i < 50; i++) {
        ReferenceChainsTestAccessor::updatePacing(0); // effectively instant
        int budget = ReferenceChainsTestAccessor::effectiveBudget();
        u64 cadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_GE(budget, lastBudget); // never shrinks while comfortably under
        EXPECT_LE(cadence, lastCadence); // never widens while comfortably under
        lastBudget = budget;
        lastCadence = cadence;
    }

    // Moved in the correct direction...
    EXPECT_GT(lastBudget, shrunkBudget);
    EXPECT_EQ(1000, lastBudget); // back at the configured ceiling
    EXPECT_LT(lastCadence, widenedCadence);
    // ...and converged: one more identical input produces no further change.
    ReferenceChainsTestAccessor::updatePacing(0);
    EXPECT_EQ(lastBudget, ReferenceChainsTestAccessor::effectiveBudget());
    EXPECT_EQ(lastCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());

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
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
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

    // Same seeding helper as PollWatchedTargetsTest above (10 strictly-
    // increasing samples - satisfies selectLeakCandidates()'s min-fill and
    // positive-slope requirements).
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 10; i++) {
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

    // First-ever search: always starts unconditionally, regardless of the
    // candidate above (this class's own header comment).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #1: _pain_budget has never had anything spent into it yet, so
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

    // Restart #2: approved (nothing spent into _pain_budget yet), and its
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
