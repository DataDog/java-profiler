/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Destroying the scope is itself a flush boundary: the early-return paths of the callers never
// call flush() explicitly.
TEST_F(ReferenceChainsBfsTest, AnchorScopeDestructionFlushesPendingPrefix) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    insertAnchorEntry(frontier, 20001, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, 20001);
        ASSERT_EQ(1u, AnchorAcc::journalCountForTest());
        EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(20001));
    }
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(20001));
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());

    tracker->stop();
}

// Empty journal: a flush with no accepted report applies nothing and requests no resweep; the
// return observation reports no overflow.
TEST_F(ReferenceChainsBfsTest, AnchorJournalEmptyFlushAppliesNothing) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    AnchorAcc::addToStaticAnchorIndexForTest(30001, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    const u64 gen = AnchorAcc::durableAnchorResweepGenForTest();

    AnchorScopedPass pass(tracker, frontier);
    EXPECT_FALSE(pass.scope.observeReturn());
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(1u, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_EQ(gen, AnchorAcc::durableAnchorResweepGenForTest());
    EXPECT_FALSE(pass.scope.observeReturn());

    tracker->stop();
}

// Duplicates consume staging capacity but never duplicate an indexed tag, and a duplicate of a
// still-indexed holder keeps its original first-look (fresh queue) position.
TEST_F(ReferenceChainsBfsTest, AnchorJournalDuplicatesConsumeCapacityButIndexOnce) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong first = 20001, second = 20002;
    insertAnchorEntry(frontier, first, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    insertAnchorEntry(frontier, second, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    {
        AnchorScopedPass pass(tracker, frontier);
        for (int i = 0; i < 5; i++) {
            reportRediscovery(pass, first);
        }
        EXPECT_EQ(5u, AnchorAcc::journalCountForTest()); // duplicates are not coalesced
        pass.scope.flush();
    }
    EXPECT_EQ(1u, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_EQ(1u, AnchorAcc::anchorOwnClassTagsSizeForTest());
    EXPECT_EQ((std::vector<jlong>{first}), AnchorAcc::freshQueueTagsForTest());

    // The second tag joins behind it; then both are re-reported, the older one first and last.
    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, second);
        reportRediscovery(pass, first);
        reportRediscovery(pass, second);
        reportRediscovery(pass, first);
    }
    EXPECT_EQ(2u, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_EQ(first, AnchorAcc::anchorIndexTagForTest(0));
    EXPECT_EQ(second, AnchorAcc::anchorIndexTagForTest(1));
    EXPECT_EQ((std::vector<jlong>{first, second}), AnchorAcc::freshQueueTagsForTest());

    tracker->stop();
}

// Exact capacity, first record over it, and sustained overflow. The accepted prefix is never
// overwritten: the first record (a local holder) survives, the rejected report is not applied, and
// the replay of the whole prefix keeps arrival order through repeated durable evictions.
TEST_F(ReferenceChainsBfsTest, AnchorJournalExactCapacityFirstOverAndSustainedOverflow) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr size_t kCapacity = AnchorObservationBuffer::CAPACITY;
    const jlong kContainer = -3101;
    AnchorAcc::primeClassShapeForTest(kContainer, true);
    const jlong first_tag = 20000;
    // kCapacity - 1 durable rediscoveries behind the first (local) record, plus two entries for
    // the rejected reports.
    insertRootAttachedDurableEntries(frontier, first_tag, kCapacity + 1);
    const size_t accepted_durable = kCapacity - 1;
    const jlong rejected_tag = first_tag + (jlong)accepted_durable;
    const jlong rejected_tag2 = rejected_tag + 1;

    auto overflowed = std::make_unique<AnchorScopedPass>(tracker, frontier);
    AnchorScopedPass &pass = *overflowed;
    const jlong local = reportFreshLocal(pass, kContainer);
    ASSERT_GT(local, 0);
    for (size_t i = 0; i < accepted_durable; i++) {
        reportRediscovery(pass, first_tag + (jlong)i);
    }
    // Exactly at capacity: every report was accepted and nothing overflowed.
    ASSERT_EQ(kCapacity, (size_t)AnchorAcc::journalCountForTest());
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_FALSE(pass.ctx.truncated);
    EXPECT_FALSE(pass.scope.observeReturn());

    // First over: aborts without recording, flags the overflow (not a frontier cap) and leaves the
    // reported tag in place.
    jlong over = rejected_tag;
    EXPECT_EQ(JVMTI_ITERATION_ABORT,
              pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, kContainer, &over));
    EXPECT_EQ(rejected_tag, over);
    EXPECT_TRUE(pass.ctx.anchor_observation_overflow);
    EXPECT_TRUE(pass.ctx.truncated);
    EXPECT_FALSE(pass.ctx.frontier_cap_hit);
    EXPECT_TRUE(pass.scope.observeReturn());
    EXPECT_EQ(kCapacity, (size_t)AnchorAcc::journalCountForTest());

    // Sustained overflow: later reports of every kind abort without admission, upgrade or record.
    const size_t frontier_size = frontier->size();
    for (int i = 0; i < 3; i++) {
        jlong again = rejected_tag2;
        EXPECT_EQ(JVMTI_ITERATION_ABORT,
                  pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, kContainer, &again));
        jlong fresh_local = 0;
        EXPECT_EQ(JVMTI_ITERATION_ABORT,
                  pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kContainer, &fresh_local));
        EXPECT_EQ(0, fresh_local) << "an overflowed report must not be admitted";
        jlong edge = rejected_tag2;
        EXPECT_EQ(JVMTI_VISIT_ABORT, pass.staticEdge(&edge));
    }
    EXPECT_EQ(frontier_size, (size_t)frontier->size());
    EXPECT_EQ(kCapacity, (size_t)AnchorAcc::journalCountForTest());
    EXPECT_EQ(0u, AnchorAcc::anchorIndexSizeForTest()); // nothing applied before the flush

    pass.scope.flush();
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    EXPECT_FALSE(pass.scope.observeReturn()); // the flush reset the overflow latch

    // No overwrite: the first record's local holder is still indexed in the local share, the
    // rejected tags never were.
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(local));
    EXPECT_EQ(1u, AnchorAcc::localAnchorCountForTest());
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(rejected_tag));
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(rejected_tag2));
    // Arrival-order replay through the durable cap: model the helper's insert-then-evict rule.
    const size_t cap = AnchorAcc::kDurableAnchorIndexCap;
    const size_t batch = AnchorAcc::kDurableAnchorEvictBatch;
    size_t survivors = 0;
    for (size_t i = 0; i < accepted_durable; i++) {
        survivors++;
        if (survivors > cap) {
            survivors -= survivors - cap + batch;
        }
    }
    EXPECT_EQ(survivors, AnchorAcc::durableAnchorCountForTest());
    for (size_t i = 0; i < accepted_durable; i++) {
        EXPECT_EQ(i >= accepted_durable - survivors,
                  AnchorAcc::anchorIndexContainsForTest(first_tag + (jlong)i))
            << "durable record " << i;
    }

    // The next traversal (a fresh context and scope, as in production) accepts the rejected tag.
    overflowed.reset();
    AnchorScopedPass retry(tracker, frontier);
    reportRediscovery(retry, rejected_tag);
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
    retry.scope.flush();
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(rejected_tag));

    tracker->stop();
}

namespace {

// Fills the journal to exactly its capacity with LOCAL records of a class the shape cache does not
// know (replay parks at most the pending-buffer cap and drops the rest: no durable evictions).
void fillJournalWithUnknownLocals(AnchorScopedPass &pass) {
    for (size_t i = 0; i < AnchorObservationBuffer::CAPACITY; i++) {
        ASSERT_GT(reportFreshLocal(pass, -3999), 0);
    }
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY,
              (size_t)ReferenceChainsTestAccessor::journalCountForTest());
}

} // namespace

// A full journal rejecting a STATIC-FIELD report requests exactly one static-scan retry for the
// whole traversal (not one per rejected report), applied after the accepted prefix.
TEST_F(ReferenceChainsBfsTest, AnchorOverflowOnStaticReportRequestsOneStaticRetry) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong static_holder = 60001;
    insertAnchorEntry(frontier, static_holder, 0, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    const u64 gen = AnchorAcc::durableAnchorResweepGenForTest();

    AnchorScopedPass pass(tracker, frontier);
    fillJournalWithUnknownLocals(pass);
    for (int i = 0; i < 2; i++) {
        jlong tag = static_holder;
        EXPECT_EQ(JVMTI_VISIT_ABORT, pass.staticEdge(&tag));
    }
    EXPECT_TRUE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(gen, AnchorAcc::durableAnchorResweepGenForTest()); // nothing applied before flush
    pass.scope.flush();
    EXPECT_EQ(gen + 1, AnchorAcc::durableAnchorResweepGenForTest());
    EXPECT_TRUE(AnchorAcc::durableAnchorResweepUnservedForTest());
    // The accepted prefix was applied: the unknown locals parked in the capped pending buffer.
    EXPECT_EQ(AnchorAcc::kPendingLocalAnchorCap, AnchorAcc::pendingLocalAnchorCountForTest());

    tracker->stop();
}
