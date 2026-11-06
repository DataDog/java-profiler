/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainsBatchTestSupport.h"

TEST_F(ReferenceChainsBfsTest, TruncatedBatchRetainsUnvisitedDeadEntryAndExpandsCompletedOne) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode(), e2 = addNode();
    int c00 = addNode(), c01 = addNode(), c20 = addNode(), c21 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    jlong t2 = seedBatchEntry(tracker, *this, frontier, e2);
    dead_tags.insert(t1);  // e1 died before GetObjectsWithTags resolved the batch
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c00, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c01, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c20, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c21, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 3, &edges, &truncated);
    ASSERT_TRUE(truncated);
    EXPECT_EQ(0, tags_ever_assigned[c21]);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state)
        << "every child of e0 was reported - the batch completed it";
    ASSERT_TRUE(frontier->lookup(t1, &entry)) << "dead entry must stay in the frontier";
    EXPECT_EQ(FrontierEntryState::EDGE, entry.state) << "and stay queued (EDGE), not pruned";
    ASSERT_TRUE(frontier->lookup(t2, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    ASSERT_GE(pending.size(), 2u);
    EXPECT_EQ((std::vector<jlong>{t1, t2}), std::vector<jlong>(pending.begin(), pending.begin() + 2));
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BatchDescentGateExpandsOnlyBatchMembers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), c0 = addNode(), c1 = addNode(), g0 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    // c0 already carries an EXPANDED entry and is never queued: a non-batch-member.
    jlong ctag = tracker->tagObject(&mock_jvmti,
                                    reinterpret_cast<jobject>(&node_tags[c0]));
    ASSERT_NE(0, ctag);
    ASSERT_TRUE(frontier->insert(ctag, t0, 1, 1, FrontierEntryState::EXPANDED));
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c0, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c1, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, c0, g0, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    EXPECT_NE(0, tags_ever_assigned[c1]);
    EXPECT_EQ(0, tags_ever_assigned[g0]) << "must not expand past the non-member c0";
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, BatchCompletionRequiresReferrerTransition) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode(), e2 = addNode();
    int c10 = addNode(), c11 = addNode(), c20 = addNode(), c21 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    jlong t2 = seedBatchEntry(tracker, *this, frontier, e2);
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c10, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c11, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c20, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c21, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 3, &edges, &truncated);
    ASSERT_TRUE(truncated);
    EXPECT_EQ(0, tags_ever_assigned[c21]);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t1, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state)
        << "the e1 -> e2 referrer transition completed e1";
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state)
        << "e0 has zero children - a top-level visit must not complete it";
    ASSERT_TRUE(frontier->lookup(t2, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    ASSERT_GE(pending.size(), 2u);
    EXPECT_EQ((std::vector<jlong>{t0, t2}), std::vector<jlong>(pending.begin(), pending.begin() + 2));
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TruncatedBatchWithoutCompletionLeavesWholeBatchQueued) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode();
    int c00 = addNode(), c01 = addNode(), c02 = addNode(), c10 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c00, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c01, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c02, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c10, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 2, &edges, &truncated);
    ASSERT_TRUE(truncated);
    EXPECT_EQ(0, tags_ever_assigned[c02]);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    ASSERT_TRUE(frontier->lookup(t1, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    ASSERT_GE(pending.size(), 2u);
    EXPECT_EQ((std::vector<jlong>{t0, t1}), std::vector<jlong>(pending.begin(), pending.begin() + 2));
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ReorderedObjectsWithTagsResultsFullBatch) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode(), e2 = addNode();
    int c0 = addNode(), c2 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    jlong t2 = seedBatchEntry(tracker, *this, frontier, e2);
    dead_tags.insert(t1);
    reverse_gotw_results = true;
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c0, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c2, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    ASSERT_TRUE(frontier->lookup(t1, &entry)) << "pruned dead entry stays parked as ABANDONED";
    EXPECT_EQ(FrontierEntryState::ABANDONED, entry.state) << "dead entry must be pruned";
    ASSERT_TRUE(frontier->lookup(t2, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    EXPECT_NE(0, tags_ever_assigned[c0]);
    EXPECT_NE(0, tags_ever_assigned[c2]);
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ReorderedObjectsWithTagsResultsTruncatedBatch) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode(), e2 = addNode();
    int c10 = addNode(), c11 = addNode(), c20 = addNode(), c21 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    jlong t2 = seedBatchEntry(tracker, *this, frontier, e2);
    reverse_gotw_results = true;
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c10, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c11, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c20, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e2, c21, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 3, &edges, &truncated);
    ASSERT_TRUE(truncated);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t1, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    ASSERT_TRUE(frontier->lookup(t2, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    ASSERT_GE(pending.size(), 2u);
    EXPECT_EQ((std::vector<jlong>{t0, t2}), std::vector<jlong>(pending.begin(), pending.begin() + 2))
        << "the remainder must be re-queued in request order, not result order";
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, DuplicateCandidateTagsMatchBaseline) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int e0 = addNode(), e1 = addNode(), c0 = addNode(), c1 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(t0);  // duplicate candidate tag
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c0, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c1, -1},
    };
    int edges = 0; bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    EXPECT_EQ(2, edges) << "each child must be admitted exactly once";
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    ASSERT_TRUE(frontier->lookup(t1, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingExpandContents().empty())
        << "every queue slot of the duplicate batch must be consumed";
    EXPECT_NE(0, tags_ever_assigned[c0]);
    EXPECT_NE(0, tags_ever_assigned[c1]);
    tracker->stop();
}

// Always fails, injected into the fixture's own JVMTI table: tagObject() returns 0 on a SetTag
// error (referenceChains.cpp), which the seeding helper must treat as broken setup.
static jvmtiError JNICALL fail_SetTag(jvmtiEnv *, jobject, jlong) {
    return JVMTI_ERROR_INTERNAL;
}

TEST_F(ReferenceChainsBfsTest, SeedBatchEntryThrowsWhenTagObjectFails) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int node = addNode();
    jvmti_tbl.SetTag = &fail_SetTag;
    EXPECT_THROW(seedBatchEntry(tracker, *this, frontier, node), std::logic_error);
    jvmti_tbl.SetTag = &ReferenceChainsMockHeap::mock_SetTag;
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingExpandContents().empty())
        << "a failed seed must not queue pending work";
    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, SeedBatchEntryThrowsWhenFrontierInsertionFails) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    int first = addNode(), second = addNode();
    // Consumes tag 1 so the next seed lands on index 1, past the one-slot table's capacity.
    ASSERT_NE(0, tracker->tagObject(&mock_jvmti,
                                   reinterpret_cast<jobject>(&node_tags[first])));
    FrontierTable one_slot(1);
    EXPECT_THROW(seedBatchEntry(tracker, *this, &one_slot, second), std::logic_error);
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingExpandContents().empty())
        << "a failed seed must not queue pending work";
    tracker->stop();
}
