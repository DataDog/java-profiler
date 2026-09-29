/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainsTestAccessors.h"
#include "referenceChainsMockHeap.h"




// The gtest fixture inherits the extracted harness wholesale so the TEST_F
// bodies below keep compiling unchanged (script/addNode/tags/... are all
// ReferenceChainsMockHeap members now).
class ReferenceChainsBfsTest : public ::testing::Test,
                               public ReferenceChainsMockHeap {
protected:
    void SetUp() override { setUp(); }
    void TearDown() override { tearDown(); }
};

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

    // A single pass that reaches full exhaustion of the reachable graph completes the search and
    // releases every tag it assigned - so the tag must be fetched via tags_ever_assigned (captured
    // at assignment time), not node_tags (already reset to 0 by releaseSearchTags() by the time
    // runPass() returns; see ReleasesTagsOnCompletion below for the release itself).
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

    // buildChainEvent() wraps the same reconstructChain() call into the ReferenceChainEvent shape
    // Recording::recordReferenceChain() (flightRecorder.cpp) expects - same chain/order, plus the
    // target's own depth from FrontierEntry.
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
    // Not truncated -> graph fully explored within the hop cap -> the search completes and releases
    // its tags in the same call (see the previous test's comment) - fetch nodeA's tag via
    // tags_ever_assigned, not node_tags.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeB]); // never admitted into the frontier

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BudgetExhaustionTruncatesAndIsReported) {
    Arguments args;
    // budget=1: root enumeration and the expand phase draw from separate budget pools (see
    // runPassManualWalk()'s own comment), each sized 1 here - root enum admits nodeA, then the
    // expand phase's own 1-unit budget admits exactly one of nodeA's two children before
    // exhausting.
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
    // Budget exhaustion for *this pass* leaves pending work (nodeC's own edge was never even
    // attempted) - the search stays RUNNING, not COMPLETED, so no tag release happens yet and
    // node_tags[nodeA]/[nodeB] are still the real assigned tags.
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
                               // resolveLoadedClasses() before this pass - see ClassTagTable's
                               // tag-sign convention.
    int fieldTargetNode = addNode();

    script = {
        // A root reference straight to the class object (e.g. a JVMTI_HEAP_REFERENCE_SYSTEM_CLASS
        // root edge in a real walk).
        {JVMTI_HEAP_REFERENCE_SYSTEM_CLASS, -1, classNode, -1},
        // A static field of that class - must never be delivered by a real FollowReferences call,
        // since the class-object edge above must not return JVMTI_VISIT_OBJECTS;
        // mock_FollowReferences enforces this the same way a real traversal would (see its own
        // comment).
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

// Regression test for admitStaticFieldRoots(): an object retained solely by a static field (no
// other GC root reaches it) must still be discovered.
TEST_F(ReferenceChainsBfsTest, DiscoversObjectRetainedOnlyByStaticField) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int fieldTargetNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/Holder;");

    script = {
        // No GC-root path to fieldTargetNode at all - it is reachable only via classNode's static
        // field.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, fieldTargetNode, -1},
    };

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);

    // classNode got tagged negative by the real resolveLoadedClasses() scan (not manually, unlike
    // PreTaggedClassObjectsAreNeverExpandedOrAdmitted above), and was never itself admitted as a
    // frontier object.
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

    // buildChainEvent() appends the root TYPE (the declaring class) as the chain's root-side end:
    // the frontier path's terminal element is the static field's holder instance, one hop below the
    // root type.
    ReferenceChainEvent event;
    ASSERT_TRUE(tracker->buildChainEvent(&mock_jvmti, &mock_jni, target_tag,
                                          &event));
    int expectedHolder = Profiler::instance()->lookupClass(
        "com/rc/statics/Holder", strlen("com/rc/statics/Holder"));
    ASSERT_NE(-1, expectedHolder);
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_EQ(chain[0], event._hops[0].klass_id); // the target's own class, unchanged
    EXPECT_EQ((u32)expectedHolder, event._hops[1].klass_id);
    // One label per hop (recordReferenceChain() drops ALL labels when any is empty); the root-type
    // hop's own edge is the unlabeled root edge (field_index -1).
    ASSERT_EQ(2u, event._hops.size());
    EXPECT_FALSE(event._hops[0].edge_label.empty());
    EXPECT_FALSE(event._hops[1].edge_label.empty());

    tracker->stop();
}

// Regression test for the resolveLoadedClasses() scan-skip guard: it must compare `class_count !=
// _last_resolved_class_count`, not `class_count > _last_resolved_class_count`.
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

    // Simulate B's classloader being GC'd: GetLoadedClasses() now reports only A (count shrinks 2
    // -> 1), exactly like a real class unload.
    classes.erase(classes.begin() + idxB);
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1, ReferenceChainsTestAccessor::lastResolvedClassCount());

    // Simulate a *different* class C loading back in, bringing the count back to 2 - the same count
    // as pass 1's peak, but not the same class set.
    addClass(classC, "Lcom/rc/regress/C;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, ReferenceChainsTestAccessor::lastResolvedClassCount());
    ASSERT_NE(0u, tags.count(classC));
    EXPECT_NE(0, tags[classC]); // the regression this test guards against

    tracker->stop();
}

// Incremental resumption across passes (ReferenceChainTracker::

TEST_F(ReferenceChainsBfsTest, MultiPassResumptionReconstructsChainAcrossPasses) {
    Arguments args;
    // budget=1 forces each pass to admit at most one new frontier entry, so this 3-hop chain cannot
    // be discovered within a single pass - exercising expandFrontier() (resumed passes), not just
    // the first pass's root walk.
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

    // Drive the search to completion one pass at a time, exactly as threadLoop() would once wired
    // up (each call bounded by `budget`).
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
    // Depth/parent_tag linkage survived resumption intact - all 3 hops walk back to a root-attached
    // (depth 0) entry, which reconstructChain() requires to succeed at all (see its own "reaching
    // parent_tag == 0" contract).
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
    // Frontier-size cap hit -- the search abandons immediately (design doc's Termination-section
    // priority 1).
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());
    ASSERT_EQ(SearchAbandonReason::FRONTIER_CAP, tracker->abandonReason());

    // nodeA was admitted (frontier cap=1 allowed one entry), then its tag was released as part of
    // this same pass's abandon handling (the mock GetObjectsWithTags() succeeds by default).
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    // nodeB was never admitted (frontier cap hit).
    EXPECT_EQ(0, node_tags[nodeB]);

    tracker->stop();
}

// releaseSearchTags()'s GetObjectsWithTags() call failing must NOT be treated as "released" - see
// that method's own comment for why: marking a tag ABANDONED (or resetting _next_tag on restart)
// while its object might still be live would let a restarted search's fresh tags collide with it,
// corrupting FrontierTable's tag-uniqueness invariant.
TEST_F(ReferenceChainsBfsTest, ReleaseSearchTagsFailureBlocksTagReuseUntilItSucceeds) {
    Arguments args;
    // framecap=1 with a self-cycle: pass 1 admits nodeA (the frontier's only slot); the
    // nodeA->nodeA edge then finds nodeA ALREADY_ADMITTED rather than hitting the frontier cap (no
    // new slot is needed for an edge back to an already-tagged object), so the search stays RUNNING
    // and only the no-progress detector - after NO_PROGRESS_PASS_LIMIT stale passes - can abandon
    // it.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1:ttl=0"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    // nodeA -> nodeA self-cycle. With framecap=1, pass 1 admits nodeA; the self-cycle edge is
    // ALREADY_ADMITTED, not a fresh frontier slot.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeA, -1}, // self-cycle
    };

    long long failedBefore =
        Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED);

    fail_get_objects_with_tags = true;
    bool truncated = false;
    // Pass 1: admits nodeA; the self-cycle keeps the pass truncated without growing the frontier
    // further.
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

    // GetObjectsWithTags() failed - nodeA's still-live tag must NOT have been cleared, and the
    // failure must be counted.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_NE(0, node_tags[nodeA]) << "tag must not be cleared when the "
                                       "release batch itself failed";
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(failedBefore + 1,
              Counters::getCounter(REFERENCE_CHAIN_TAG_RELEASE_FAILED));

    // While the release is still outstanding, shouldRunPass() must force a retry unconditionally.
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

// Regression test for the CANARY_STUCK/frontier-wipe convergence bug: prior to this fix,
// runPass()'s canary-stuck branch fired purely off _passes_since_last_candidate_progress, so a
// search whose candidate simply had not been found yet was abandoned - and its frontier
// destructively wiped by the next restartSearch() - after only CANARY_NO_PROGRESS_PASS_LIMIT
// passes, even while the whole-graph frontier was still growing every single pass.
TEST_F(ReferenceChainsBfsTest, CanaryStuckRequiresWholeGraphFrontierAlsoStalled) {
    Arguments args;
    // budget=1: exactly one new frontier admission per pass, so the frontier grows every single
    // pass for as long as the chain has unexplored nodes left - _passes_since_last_progress never
    // leaves 0.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A chain longer than the number of passes driven below, so the frontier still has pending work
    // - and is still growing one node per pass - at every pass this test checks.
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

    // A canary candidate that this graph never actually contains (no node is ever tagged with the
    // candidate's marker tag) - the candidate-specific stuck counter
    // (_passes_since_last_candidate_progress) climbs every pass with zero discovery progress,
    // exactly like the live-pod scenario chasing a candidate deeper than the old fixed
    // CANARY_NO_PROGRESS_PASS_LIMIT (30) passes could reach.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);

    bool truncated = true;
    // One more pass than the old fixed CANARY_NO_PROGRESS_PASS_LIMIT: long enough that the pre-fix
    // single-condition check would already have abandoned the search, but short enough that the
    // 40-node chain still has unexplored work left, so the frontier is still genuinely growing
    // every pass.
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
    // The narrower candidate-stuck counter climbed the whole time - this is what the old,
    // single-condition check would have abandoned on alone.
    EXPECT_GE(ReferenceChainsTestAccessor::passesSinceLastCandidateProgress(),
              ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT);

    tracker->stop();
}

// CANARY_STUCK escalation: each consecutive CANARY_STUCK restart of a candidate-chase sequence
// doubles the pass limit canaryStuckPassLimit() compares against (30 -> 60 -> 120, capped at 2^8
// doublings), so a repeatedly-unfindable candidate gets progressively more passes before the
// detector gives up on it; a terminal outcome of any other kind (including a natural completion)
// resets the escalation so the next fresh chase starts back at the base limit. Driven through the
// real runPass()/restartSearch() path, not the accessors.
TEST_F(ReferenceChainsBfsTest, CanaryStuckLimitDoublesPerRestartAndResetsOnCleanCompletion) {
    Arguments args;
    // The whole graph is exhausted within the first pass or two, so the frontier is stalled from
    // then on; the seeded watched-leak klass keeps the search from completing naturally, and the
    // seeded urgency suppresses the ordinary whole-graph stall branch (same frontier-stall
    // precondition, checked first - CANARY_STUCK is deliberately NOT urgent-suppressed, that is
    // the one window where it is reachable).
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1000:ttl=0:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // CANARY_STUCK is only reachable while urgent: the ordinary whole-graph stall branch (same
    // frontier-stall precondition, checked first) is deliberately suppressed by isUrgent(), and
    // at the base limit both conditions would fire on the same pass. Seed a ~224s-to-OOM
    // projection the same way referenceChainsOomTests.inc does (linear ramp over synthetic
    // timestamps); restored at the end so later tests see default heap state.
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    constexpr u64 MAX_HEAP_TEST = 1024 * MiB;
    LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)MAX_HEAP_TEST);
    LivenessTracker::instance()->setGcGenerationsForTest(true);
#ifdef DEBUG
    LivenessTracker::instance()->setHeapFloorRecordingForTest(false);
#endif
    {
        u64 clock_ns = 0;
        u64 last_used = MAX_HEAP_TEST - 224 * MiB;
        for (int i = 0; i < 30; i++) {
            LivenessTracker::instance()->heapFloorRecordForTest(
                last_used - MiB * (u64)(29 - i), clock_ns, 0);
            clock_ns += SEC_NS;
        }
    }
    ASSERT_NEAR(LivenessTracker::instance()->secondsToOOM(), 224.0, 1.0);

    constexpr int kChainLength = 10;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    // A canary candidate this graph never contains, plus a watched-leak klass so the exhausted
    // frontier cannot complete the search out from under the CANARY_STUCK detector.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({1});

    auto driveUntilTerminal = [this, &tracker]() -> int {
        bool truncated = true;
        int passes = 0;
        while (tracker->searchState() == SearchState::RUNNING && passes < 1000) {
            // EXPECT (not ASSERT): gtest assertion macros return void, which cannot appear in an
            // int-returning lambda; the state check below governs the loop either way.
            EXPECT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
            passes++;
        }
        return passes;
    };

    // Chase 1: abandoned by the CANARY_STUCK detector at the base limit.
    int chase1_passes = driveUntilTerminal();
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());
    EXPECT_EQ((u8)SearchAbandonReason::CANARY_STUCK,
              ReferenceChainsTestAccessor::searchAbandonReasonForTest());
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest() >> 1);

    // Chase 2: a consecutive CANARY_STUCK restart keeps the escalation - the doubled limit must
    // give this chase strictly more passes than chase 1 got before abandoning it.
    ReferenceChainsTestAccessor::restartSearchForTest();
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({1});
    int chase2_passes = driveUntilTerminal();
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());
    EXPECT_EQ((u8)SearchAbandonReason::CANARY_STUCK,
              ReferenceChainsTestAccessor::searchAbandonReasonForTest());
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT << 2,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest());
    EXPECT_GT(chase2_passes, chase1_passes)
        << "the doubled limit must give the second chase more passes, not fewer";

    // A terminal outcome of a different kind resets the escalation: mark the candidate found, so
    // the next pass completes naturally and the fresh-chase limit goes back to the base.
    ReferenceChainsTestAccessor::restartSearchForTest();
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(1);
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest());

    // This test deliberately reaches states the fixtures' SetUp reset() cannot fully neutralize
    // for a *latched* tracker: the urgency latch (isUrgent() keeps bypassing the candidate gate
    // until it releases on its own, breaking later tests' gate expectations under shuffled
    // order), the watched-leak-klass list (restartSearch() does not clear it), and whatever
    // candidate/found state the last runPass() left. Restore all of it - the same seam the
    // fixtures use in SetUp, applied to the leaked half.
    LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
    LivenessTracker::instance()->setGcGenerationsForTest(false);
    tracker->stop();
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({});
    ReferenceChainsTestAccessor::reset();
}

// Canary-lane backoff pacing (option A): a chase with unresolved candidates runs back-to-back only
// while it is fresh or making candidate progress; each pass with NO candidate progress doubles the
// spacing multiplier (_canary_backoff_mult) up to CANARY_BACKOFF_MULT_MAX, progress resets it to 1,
// and the OOM urgency ramp overrides the gate entirely.
TEST_F(ReferenceChainsBfsTest, CanaryLaneBacksOffWithoutProgressAndResetsOnProgress) {
    Arguments args;
    // Same shape as CanaryStuckRequiresWholeGraphFrontierAlsoStalled above: budget=1 with a long
    // chain keeps the frontier growing one node per pass, so the CANARY_STUCK detector (which also
    // requires a stalled frontier) never fires and the chase stays RUNNING through the whole loop
    // below.
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

    // Pass 1: the candidate admission itself raises the progress mark (0 -> 1), so this counts as
    // progress and the multiplier stays at 1 - back-to-back.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryBackoffMult());
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a fresh chase must be allowed to run back-to-back";

    // Pass 2: no candidate progress -> first doubling (1 -> 2).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryBackoffMult());
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/2, /*ema_ms=*/100, OS::nanotime());
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "a no-progress canary pass must hold off the next one";
    // Beyond the spacing, the chase is allowed again - the backoff paces, it never abandons.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(
        ReferenceChainsTestAccessor::lastCanaryPassNs() +
        2ULL * 100ULL * 1000000ULL + 1))
        << "elapsed spacing must re-admit the canary pass";

    // The OOM urgency ramp overrides the backoff gate entirely.
    ReferenceChainsTestAccessor::setOomRampActive(true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime()))
        << "urgency must bypass the canary backoff";
    ReferenceChainsTestAccessor::setOomRampActive(false);

    // Consecutive no-progress passes double the multiplier up to the cap (seeded at 8 so one more
    // pass reaches it, the next holds it).
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        /*mult=*/8, /*ema_ms=*/100, OS::nanotime());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(ReferenceChainTracker::CANARY_BACKOFF_MULT_MAX,
              ReferenceChainsTestAccessor::canaryBackoffMult())
        << "the multiplier must hold at its cap, not grow past it";

    // Candidate progress (a new candidate admitted into a slot) resets the lane to back-to-back.
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
    // budget=1 on a graph where each pass admits exactly one new edge until the chain is exhausted,
    // then the frontier stops growing.
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1:ttl=0:firstpassbudget=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int nodeA = addNode();
    int nodeB = addNode();
    int nodeC = addNode();
    int nodeD = addNode();

    // A chain one node longer than either pass's 1-edge expand budget can fully drain in a single
    // call, so each pass still ends truncated (see mock_FollowReferences()'s own comment: an
    // array-holder walk chains through as many script edges as it can admit before budget aborts
    // it) and there is still pending work left for the no-progress check to catch once the chain is
    // fully discovered.
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeB, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeB, nodeC, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeC, nodeD, -1},
    };

    bool truncated = false;
    // Pass 1: root enum admits nodeA, expand admits nodeB, aborts on nodeB->nodeC for lack of
    // budget - truncated, frontier grew (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 2: admits nodeC, aborts on nodeC->nodeD - still truncated, still growing (progress).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Pass 3: admits nodeD, chain exhausted - no longer truncated, no pending frontier, natural
    // completion.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Tags released.
    EXPECT_NE(0, tags_ever_assigned[nodeA]);
    EXPECT_EQ(0, node_tags[nodeA]);
    EXPECT_NE(0, tags_ever_assigned[nodeB]);
    EXPECT_EQ(0, node_tags[nodeB]);

    // No-progress (not TTL) is reported as the reason when the frontier stalls.
    EXPECT_EQ(SearchAbandonReason::NONE, tracker->abandonReason());
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, NoProgressAbandonsSearchAndReleasesTags) {
    // Verify the progress-based abandonment wiring: the no-progress limit is accessible, positive,
    // and reset to 0 by resetSearchStateForTest().
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
    // A second root that root enumeration's own 1-unit budget (firstpassbudget=1) can't reach this
    // pass - the resulting root-enum truncation makes runPassManualWalk() return before
    // expandFrontier() ever runs (see its own comment on frontier-cap-hit/budget-exhausted
    // root-enum truncation), so nodeA is admitted but never gets a chance to expand nodeA->nodeB.
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
    // Simulate nodeA dying (collected) between pass 1 and pass 2 - GetObjectsWithTags will no
    // longer report it as live.
    dead_tags.insert(aTag);

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated)); // pass 2: resolve-or-drop
    EXPECT_FALSE(truncated);
    // The dead branch was pruned for free - with nothing else pending, the search completes rather
    // than staying RUNNING or being ABANDONED.
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(2, tracker->passesRun());

    FrontierEntry entry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(aTag, &entry));
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state);

    // nodeB was never discovered - nodeA's subtree was pruned, not expanded.
    EXPECT_EQ(0, tags_ever_assigned[nodeB]);

    tracker->stop();
}

// pollWatchedTargets() (design doc's Open Question 3 bridging

// =========================================================================== Pod-in-a-jar system
// harness (design node: design-pod-in-a-jar-harness; meta-whackamole-analysis): the REAL tracker
// loop (shouldRunPass -> runPass -> pollWatchedTargets, the exact threadLoop body) driven over the
// scripted mock heap, asserting SYSTEM INVARIANTS instead of unit symptoms.
