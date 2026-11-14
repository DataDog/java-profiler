/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "referenceChainsBatchTestSupport.h"

// Deltas asserted across one expandFrontier() call for each failure-row test below.
struct BatchFailureRow {
    int gotw_delta;
    int follow_delta;
    int local_refs_delta;
    int dealloc_delta;
    bool pending_exception;
};

// Shared failure-row driver: seeds e0 -> c0 / e1 -> c1, applies the row's knob, and asserts one
// expandFrontier() call's failure exit - both entries stay queued at EDGE, no child is admitted,
// and every JNI/JVMTI cleanup delta is exact.
static void expectBatchFailureRow(ReferenceChainsBfsTest &t,
                                  const BatchFailureRow &row,
                                  void (*apply_knob)(ReferenceChainsBfsTest &)) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int edges = 0;
    bool truncated = false;
    // Empty-queue drive before seeding: caches java/lang/Object so the measured call's
    // DeleteLocalRef delta excludes the one-time FindClass() local ref.
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &t.mock_jvmti, &t.mock_jni, 1000, &edges, &truncated);
    int e0 = t.addNode(), e1 = t.addNode();
    int c0 = t.addNode(), c1 = t.addNode();
    jlong t0 = seedBatchEntry(tracker, t, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, t, frontier, e1);
    t.script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e0, c0, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e1, c1, -1},
    };
    apply_knob(t);
    int gotw0 = t.gotw_calls_, follow0 = t.follow_references_calls_;
    int local0 = t.local_refs_deleted_, dealloc0 = t.deallocate_calls_;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &t.mock_jvmti, &t.mock_jni, 1000, &edges, &truncated);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(0, t.tags_ever_assigned[c0]);
    EXPECT_EQ(0, t.tags_ever_assigned[c1]);
    EXPECT_EQ(row.pending_exception, t.pending_exception);
    FrontierEntry entry{};
    if (!frontier->lookup(t0, &entry)) {
        throw std::logic_error("expectBatchFailureRow: frontier lookup failed");
    }
    // EDGE pins "not expanded and not cleared": clear() parks an entry as ABANDONED while
    // lookup() still returns true, so a state != EXPANDED check alone would miss a clearing bug.
    EXPECT_EQ(FrontierEntryState::EDGE, entry.state);
    if (!frontier->lookup(t1, &entry)) {
        throw std::logic_error("expectBatchFailureRow: frontier lookup failed");
    }
    EXPECT_EQ(FrontierEntryState::EDGE, entry.state);
    EXPECT_EQ((std::vector<jlong>{t0, t1}),
              ReferenceChainsTestAccessor::pendingExpandContents());
    EXPECT_EQ(row.gotw_delta, t.gotw_calls_ - gotw0);
    EXPECT_EQ(row.follow_delta, t.follow_references_calls_ - follow0);
    EXPECT_EQ(row.local_refs_delta, t.local_refs_deleted_ - local0);
    EXPECT_EQ(row.dealloc_delta, t.deallocate_calls_ - dealloc0);
}

TEST_F(ReferenceChainsBfsTest, BatchGetObjectsWithTagsErrorRetainsBatch) {
    expectBatchFailureRow(*this, {1, 0, 0, 0, false},
                          [](ReferenceChainsBfsTest &t) {
                              t.fail_get_objects_with_tags = true;
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchEnsureLocalCapacityFailureRetainsBatch) {
    // A negative EnsureLocalCapacity return short-circuits the `capacity_err < 0 ||
    // jniExceptionCheck()` check, so the pending exception survives this exit as-is.
    expectBatchFailureRow(*this, {1, 0, 2, 2, true},
                          [](ReferenceChainsBfsTest &t) {
                              t.fail_ensure_local_capacity = true;
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchNewObjectArrayFailureRetainsBatch) {
    expectBatchFailureRow(*this, {1, 0, 2, 2, false},
                          [](ReferenceChainsBfsTest &t) {
                              t.fail_new_object_array = true;
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchSetObjectArrayElementFailureRetainsBatch) {
    expectBatchFailureRow(*this, {1, 0, 3, 2, false},
                          [](ReferenceChainsBfsTest &t) {
                              t.fail_set_element_at = 1;
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchFollowReferencesErrorRetainsBatch) {
    expectBatchFailureRow(*this, {1, 1, 3, 2, false},
                          [](ReferenceChainsBfsTest &t) {
                              t.follow_references_error = JVMTI_ERROR_INTERNAL;
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchDeadlineBeforeBatchRetainsBatch) {
    expectBatchFailureRow(*this, {0, 0, 0, 0, false},
                          [](ReferenceChainsBfsTest &) {
                              ReferenceChainsTestAccessor::setPassDeadlineNs(1);
                          });
}

TEST_F(ReferenceChainsBfsTest, BatchSuccessReleasesEveryLocalRefAndBuffer) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();
    int edges = 0;
    bool truncated = true;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    int e0 = addNode(), e1 = addNode();
    jlong t0 = seedBatchEntry(tracker, *this, frontier, e0);
    jlong t1 = seedBatchEntry(tracker, *this, frontier, e1);
    int gotw0 = gotw_calls_, follow0 = follow_references_calls_;
    int local0 = local_refs_deleted_, dealloc0 = deallocate_calls_;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    EXPECT_EQ(1, gotw_calls_ - gotw0);
    EXPECT_EQ(1, follow_references_calls_ - follow0);
    // One holder local ref plus one per resolved object; the two result arrays are deallocated.
    EXPECT_EQ(3, local_refs_deleted_ - local0);
    EXPECT_EQ(2, deallocate_calls_ - dealloc0);
    FrontierEntry entry{};
    EXPECT_TRUE(frontier->lookup(t0, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    EXPECT_TRUE(frontier->lookup(t1, &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state);
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingExpandContents().empty());
}

// A batch whose entries were all visited keeps its completion set for the ROLLING RESUME branch;
// when the NEXT batch fails before FollowReferences runs, that stale set must not mark the new
// batch's entries visited.
TEST_F(ReferenceChainsBfsTest, SecondBatchFailureRetainsQueueDespiteFirstBatchCompletions) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    ReferenceChainsTestAccessor::setGotwBatchSize(
        ReferenceChainsTestAccessor::gotwMinBatch());
    FrontierTable *frontier = tracker->frontierTable();
    int e[8];
    jlong tag[8];
    for (int i = 0; i < 8; i++) {
        e[i] = addNode();
        tag[i] = seedBatchEntry(tracker, *this, frontier, e[i]);
    }
    int c0 = addNode(), c1 = addNode();
    ReferenceChainsTestAccessor::pushPendingExpandForTest(tag[0]);
    int last = addNode();
    jlong last_tag = seedBatchEntry(tracker, *this, frontier, last);
    // The e0 -> e1 referrer transition completes e0 during the first batch's walk.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, e[0], c0, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, e[1], c1, -1},
    };
    fail_ensure_local_capacity_on_gotw_call = 2;
    int gotw0 = gotw_calls_, follow0 = follow_references_calls_;
    int edges = 0;
    bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(2, gotw_calls_ - gotw0);
    EXPECT_EQ(1, follow_references_calls_ - follow0) << "exactly one successful walk";
    jlong child0 = tags_ever_assigned[c0];
    jlong child1 = tags_ever_assigned[c1];
    EXPECT_NE(0, child0);
    EXPECT_NE(0, child1);
    // The failed second batch visited none of its own entries: the retried duplicate, the new
    // entry and both newly admitted children stay queued in order.
    EXPECT_EQ((std::vector<jlong>{tag[0], last_tag, child0, child1}),
              ReferenceChainsTestAccessor::pendingExpandContents());
    FrontierEntry entry{};
    EXPECT_TRUE(frontier->lookup(last_tag, &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state);
}

TEST_F(ReferenceChainsBfsTest, BatchLargerThanDescriptorCapacityTruncatesAndRetainsBatch) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    ReferenceChainsTestAccessor::setGotwBatchSize(
        ReferenceChainsTestAccessor::gotwMaxBatch() + 88);
    FrontierTable *frontier = tracker->frontierTable();
    int edges = 0;
    bool truncated = false;
    // Empty-queue drive before seeding: caches java/lang/Object so the measured call's
    // DeleteLocalRef delta excludes the one-time FindClass() local ref.
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    std::vector<jlong> expected;
    for (int i = 0; i < 600; i++) {
        int node = addNode();
        expected.push_back(seedBatchEntry(tracker, *this, frontier, node));
    }
    int local0 = local_refs_deleted_, dealloc0 = deallocate_calls_;
    int follow0 = follow_references_calls_;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    // A batch larger than the batch descriptor's capacity must truncate before the holder walk:
    // no FollowReferences, the whole queue retained in order, no entry expanded.
    EXPECT_TRUE(truncated);
    EXPECT_EQ(0, follow_references_calls_ - follow0);
    EXPECT_EQ(600, local_refs_deleted_ - local0);
    EXPECT_EQ(2, deallocate_calls_ - dealloc0);
    EXPECT_EQ(expected, ReferenceChainsTestAccessor::pendingExpandContents());
    for (jlong tag : expected) {
        FrontierEntry entry{};
        EXPECT_TRUE(frontier->lookup(tag, &entry));
        EXPECT_EQ(FrontierEntryState::EDGE, entry.state);
    }
}

TEST_F(ReferenceChainsBfsTest, StaticFieldSweepAdmitsOneHopPastEachClass) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    int classNode = addNode();
    int target = addNode();
    int child = addNode();
    // addClass after every addNode: node_tags may reallocate on addNode, so the registered class
    // identity must be taken once the nodes exist.
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/Sweeper;");
    script = {
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, target, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, target, child, -1},
    };
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    int edges = 0;
    bool truncated = true;
    ReferenceChainsTestAccessor::admitStaticFieldRootsForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    EXPECT_LT(node_tags[classNode], 0) << "the class object must stay a tagged class, never admitted";
    jlong target_tag = tags_ever_assigned[target];
    EXPECT_NE(0, target_tag) << "the class's static field must admit its target";
    FrontierEntry entry{};
    EXPECT_TRUE(tracker->frontierTable()->lookup(target_tag, &entry));
    EXPECT_EQ(0, entry.parent_tag) << "admitted root-attached by the sweep";
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, entry.root_kind);
    EXPECT_EQ(0, tags_ever_assigned[child]) << "the sweep admits one hop past each class, no deeper";
}

TEST_F(ReferenceChainsBfsTest, LeakTagInterceptDoesNotDescendInlineUnderBatching) {
    BatchTrackerGuard guard("referencechains=true:hops=64:budget=1000");
    ReferenceChainTracker *tracker = guard.tracker();
    FrontierTable *frontier = tracker->frontierTable();
    int entry = addNode();
    int leak = addNode();
    int child = addNode();
    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();
    node_tags[leak] = leak_tag;
    jlong etag = tracker->tagObject(&mock_jvmti,
                                    reinterpret_cast<jobject>(&node_tags[entry]));
    ASSERT_NE(0, etag);
    ASSERT_TRUE(frontier->insert(etag, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(etag);
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, entry, leak, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, leak, child, -1},
    };
    // One batch only: the first GetObjectsWithTags busy-waits past the 50ms pass deadline, and the
    // loop-top deadline check stops the second batch (the callback's own check runs every 4096
    // calls, so the walk itself never truncates).
    constexpr u64 kDeadlineNs = 50 * 1000 * 1000;
    constexpr u64 kGotwDelayNs = 100 * 1000 * 1000;
    gotw_delay_ns = kGotwDelayNs;
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + kDeadlineNs);
    int edges = 0;
    bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_TRUE(truncated);
    jlong leak_ftag = node_tags[leak];
    EXPECT_NE(leak_tag, leak_ftag) << "the leak-tagged object was never intercepted";
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(leak_ftag));
    EXPECT_EQ((std::vector<jlong>{leak_ftag}),
              ReferenceChainsTestAccessor::pendingExpandContents())
        << "the intercepted object must be queued for a later batch, not descended inline";
    EXPECT_EQ(0, tags_ever_assigned[child]);
}
