/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

TEST_F(ReferenceChainsBfsTest, AnchorJournalSnapshotRequiresCurrentLease) {
    AnchorObservationBuffer buffer;
    AnchorObservationLease lease = buffer.tryLease();
    ASSERT_NE(0u, lease.id);
    ASSERT_TRUE(buffer.reserve(lease));
    buffer.commit(lease, AnchorObservation{1, 2, 3,
                                           AnchorObservation::LOCAL,
                                           (u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD});

    const AnchorObservation *records = nullptr;
    u32 count = 0;
    bool static_retry = false;
    ASSERT_TRUE(buffer.snapshot(lease, &records, &count, &static_retry));
    ASSERT_NE(nullptr, records);
    ASSERT_EQ(1u, count);
    EXPECT_EQ(1, records[0].tag);
    EXPECT_FALSE(static_retry);

    buffer.releaseLease(lease);
    EXPECT_FALSE(buffer.snapshot(lease, &records, &count, &static_retry));
    EXPECT_EQ(nullptr, records);
    EXPECT_EQ(0u, count);
    EXPECT_FALSE(static_retry);
}

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

    // The next enumeration re-reports both tags: both are indexed now, so the indexed-tag gate
    // stages nothing - their replay would be a no-op, and the slots stay free for real effects.
    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, first);
        reportRediscovery(pass, second);
        EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    }

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
    ReferenceChainTracker::instance()->setLocalStagingBudgetOverrideForTest(0);
}

// A stable durable population at the journal capacity is re-reported by every enumeration. Before
// the indexed-tag gate its re-enlist records refilled the journal at the same prefix every pass:
// the overflow aborted at the same report, _root_enum_incomplete latched, and no later root was
// ever reached. The gate must keep the repeat reports slot-free so the next enumeration admits
// the late root.
TEST_F(ReferenceChainsBfsTest, AnchorJournalStablePopulationLeavesSlotsForLaterRoots) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr size_t kCapacity = AnchorObservationBuffer::CAPACITY;
    const jlong first_tag = 20000;
    // The stable population plus one late root reported behind it.
    insertRootAttachedDurableEntries(frontier, first_tag, kCapacity + 1);

    // First enumeration: nothing is indexed yet, so every report stages a record and the replay
    // indexes the whole population through the durable cap (evicting its oldest share).
    {
        AnchorScopedPass pass(tracker, frontier);
        for (size_t i = 0; i < kCapacity; i++) {
            reportRediscovery(pass, first_tag + (jlong)i);
        }
        ASSERT_EQ(kCapacity, (size_t)AnchorAcc::journalCountForTest());
        EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
        pass.scope.flush();
    }
    const size_t indexed = AnchorAcc::anchorIndexSizeForTest();
    EXPECT_GT(indexed, (size_t)0);
    EXPECT_LT(indexed, kCapacity); // the durable cap evicted the oldest share

    // Second enumeration: the indexed share stages nothing; only the evicted holders re-enlist.
    // The journal must stay below capacity and admit the late root.
    AnchorScopedPass retry(tracker, frontier);
    for (size_t i = 0; i < kCapacity; i++) {
        reportRediscovery(retry, first_tag + (jlong)i);
    }
    EXPECT_FALSE(retry.ctx.anchor_observation_overflow);
    EXPECT_EQ(kCapacity - indexed, (size_t)AnchorAcc::journalCountForTest());
    const jlong late = first_tag + (jlong)kCapacity;
    reportRediscovery(retry, late);
    EXPECT_FALSE(retry.ctx.anchor_observation_overflow);
    retry.scope.flush();
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(late));

    tracker->stop();
}

// Root retries keep accepted durable reports complete when callback order changes.
TEST_F(ReferenceChainsBfsTest, RootEnumerationProgressSurvivesRepeatedAnchorJournalOverflow) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr size_t kJournalCapacity = AnchorObservationBuffer::CAPACITY;
    constexpr size_t kRootCount = 2 * kJournalCapacity + 1;
    const jlong first_tag = 20000;
    const std::vector<jlong> root_tags =
        insertRootAttachedDurableEntries(frontier, first_tag, kRootCount);
    std::vector<int> root_nodes;
    root_nodes.reserve(kRootCount);
    script.reserve(kRootCount);
    for (size_t i = 0; i < kRootCount; i++) {
        const int node = addNode();
        root_nodes.push_back(node);
        node_tags[node] = root_tags[i];
        script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, node, -1});
    }
    // Keep the search active after the final complete root enumeration to inspect the retained index.
    AnchorAcc::setCandidateCountForTest(1);
    AnchorAcc::setCandidateKlassIdForTest(0, 999);

    bool truncated = false;
    t8AllowRootEnumeration();
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(
        root_tags[kJournalCapacity - 1]));
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(
        root_tags[kJournalCapacity]));
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, active_fixture->last_ior_control);
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());

    // The retry skips completed tag observations and reaches the next journal-sized segment.
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(
        root_tags[2 * kJournalCapacity - 1]));
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(
        root_tags[2 * kJournalCapacity]));
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, active_fixture->last_ior_control);
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());

    // The final root was rejected; the next retry skips completed tags and indexes it. A pass's
    // truncated flag may also come from the unrelated static-field sweep, so membership proves it.
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    const int late_node = root_nodes.back();
    EXPECT_EQ(root_tags.back(), tags_ever_assigned[late_node]);
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(root_tags.back()));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, StaticSweepProgressSurvivesIndexEviction) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr size_t capacity = AnchorObservationBuffer::CAPACITY;
    constexpr u32 first_attempt =
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 1U;
    const jlong first_tag = 22000;
    for (size_t i = 0; i < 2 * capacity + 1; i++) {
        insertAnchorEntry(frontier, first_tag + (jlong)i, 0,
                          JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }

    {
        AnchorScopedPass first(tracker, frontier);
        first.ctx.static_field_seed = true;
        first.ctx.root_report_attempt_id = first_attempt;
        for (size_t i = 0; i < capacity; i++) {
            jlong tag = first_tag + (jlong)i;
            ASSERT_EQ(JVMTI_VISIT_OBJECTS, first.staticEdge(&tag));
        }
        ASSERT_EQ(capacity, AnchorAcc::journalCountForTest());
        jlong rejected = first_tag + (jlong)capacity;
        EXPECT_EQ(JVMTI_VISIT_ABORT, first.staticEdge(&rejected));
        first.scope.flush();
    }
    EXPECT_LT(AnchorAcc::durableAnchorCountForTest(), capacity);
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(first_tag));

    {
        AnchorScopedPass retry(tracker, frontier);
        retry.ctx.static_field_seed = true;
        retry.ctx.root_report_attempt_id = first_attempt + 1;
        retry.ctx.root_report_previous_attempt_id = first_attempt;
        retry.ctx.root_report_retrying_incomplete = true;
        for (size_t i = 0; i < 2 * capacity; i++) {
            jlong tag = first_tag + (jlong)i;
            EXPECT_EQ(JVMTI_VISIT_OBJECTS, retry.staticEdge(&tag));
        }
        EXPECT_EQ(capacity, AnchorAcc::journalCountForTest())
            << "the accepted first chunk must not be restaged after eviction";
        jlong second_rejected = first_tag + (jlong)(2 * capacity);
        EXPECT_EQ(JVMTI_VISIT_ABORT, retry.staticEdge(&second_rejected));
        retry.scope.flush();
    }

    const jlong last = first_tag + (jlong)(2 * capacity);
    {
        AnchorScopedPass final(tracker, frontier);
        final.ctx.static_field_seed = true;
        final.ctx.root_report_attempt_id = first_attempt + 2;
        final.ctx.root_report_previous_attempt_id = first_attempt + 1;
        final.ctx.root_report_retrying_incomplete = true;
        for (size_t i = 0; i < 2 * capacity; i++) {
            jlong tag = first_tag + (jlong)i;
            EXPECT_EQ(JVMTI_VISIT_OBJECTS, final.staticEdge(&tag));
        }
        jlong reported = last;
        EXPECT_EQ(JVMTI_VISIT_OBJECTS, final.staticEdge(&reported));
        EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
        final.scope.flush();
    }
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(last));

    tracker->stop();
}

// An incomplete retry sequence widens the recognized-stamp window to every attempt of the
// sequence: a report stamped by the sequence's FIRST attempt still suppresses restaging two
// attempts later (alternating oversized groups must not ping-pong each other out of the durable
// index). The window expires with the sequence: a completed sequence, or a range outside it,
// suppresses only on the current attempt's stamp.
TEST_F(ReferenceChainsBfsTest, RetrySequenceWindowRecognizesEverySequenceAttempt) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 21101;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    // Attempt 1 stamps the JNI report, then truncates (the sequence opens with base 1).
    frontier->markRootReportObserved(tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 1);
    // Attempt 2 (the immediate retry) suppresses via the previous-attempt window...
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 2, 1, true, nullptr,
        /*static_sweep=*/false, /*retry_base_id=*/1));
    // ...and attempt 3 must STILL suppress the attempt-1 stamp via the sequence window.
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 3, 2, true, nullptr,
        /*static_sweep=*/false, /*retry_base_id=*/1))
        << "a stamp from the sequence's first attempt must suppress within the sequence";
    // Outside the sequence (no open sequence): the old one-attempt window applies.
    EXPECT_FALSE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 3, 2, true, nullptr,
        /*static_sweep=*/false, /*retry_base_id=*/0));
    // The sequence completed: the suppression expires with it.
    EXPECT_FALSE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 3, 2, false, nullptr,
        /*static_sweep=*/false, /*retry_base_id=*/1));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, DurableRootReportProgressStampBoundaries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 21001;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    frontier->markRootReportObserved(
        0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);
    frontier->markRootReportObserved(
        -5, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);
    frontier->markRootReportObserved(
        (jlong)INT_MAX + 1, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);
    const jlong past_end = (jlong)frontier->size() + 1;
    frontier->markRootReportObserved(
        past_end, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);
    frontier->markRootReportObserved(tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 0);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(0u, entry.root_report_attempt);
    EXPECT_FALSE(frontier->lookup(past_end, &entry));
    EXPECT_FALSE(frontier->rootReportCompleted(
        past_end, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, true, 7, 6, true));
    EXPECT_FALSE(frontier->rootReportCompleted(
        (jlong)INT_MAX + 1, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, true, 7, 6, true));

    frontier->markRootReportObserved(tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 7, 6, true));
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 7, true));
    EXPECT_FALSE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 7, false));
    EXPECT_FALSE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 6, true));
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, true, 0, 0, false));
    EXPECT_FALSE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_LOCAL, true, 7, 6, true));

    const jlong static_tag = 21008;
    insertAnchorEntry(frontier, static_tag, 0,
                      JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    bool weaker_root_noop = false;
    EXPECT_FALSE(frontier->rootReportCompleted(
        static_tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 7, 6, true,
        &weaker_root_noop));
    EXPECT_FALSE(weaker_root_noop);
    frontier->markRootReportObserved(
        static_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 7U,
        /*static_sweep=*/true);
    EXPECT_TRUE(frontier->rootReportCompleted(
        static_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD, false,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 8U,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 7U, true,
        nullptr, /*static_sweep=*/true));
    weaker_root_noop = false;
    // A stale static-sweep stamp alone no longer suppresses the weaker JNI report: after the
    // static edge disappears and eviction drops the holder from the durable index, the JNI report
    // is the only route back into indexed rotation (see rootReportCompleted()).
    EXPECT_FALSE(frontier->rootReportCompleted(
        static_tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 8, false,
        &weaker_root_noop));
    EXPECT_FALSE(weaker_root_noop);
    // Index coverage still suppresses: the holder sits in the durable index, so the JNI report
    // restages nothing.
    EXPECT_TRUE(frontier->rootReportCompleted(
        static_tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, true, 9, 8, false,
        &weaker_root_noop));
    EXPECT_TRUE(weaker_root_noop);

    insertAnchorEntry(frontier, 21007, 21001, JVMTI_HEAP_REFERENCE_STACK_LOCAL);
    EXPECT_FALSE(frontier->rootReportCompleted(
        21007, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 0, 0, false));
    frontier->markRootReportObserved(
        21007, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 9);
    frontier->markRootReportObserved(
        21007, JVMTI_HEAP_REFERENCE_STATIC_FIELD, 9);
    EXPECT_TRUE(frontier->rootReportCompleted(
        21007, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 0, false));
    EXPECT_TRUE(frontier->rootReportCompleted(
        21007, JVMTI_HEAP_REFERENCE_STATIC_FIELD, false, 9, 0, false));
    EXPECT_TRUE(frontier->rootReportCompleted(
        21007, JVMTI_HEAP_REFERENCE_JNI_LOCAL, true, 0, 0, false));

    const jlong chain_static_tag = 21009;
    insertAnchorEntry(frontier, chain_static_tag, 21001,
                      JVMTI_HEAP_REFERENCE_STACK_LOCAL);
    frontier->markRootReportObserved(
        chain_static_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 11U,
        /*static_sweep=*/true);
    frontier->markRootReportObserved(
        chain_static_tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 12);
    EXPECT_TRUE(frontier->rootReportCompleted(
        chain_static_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD, false,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 12U,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 11U, true,
        nullptr, true));
    EXPECT_TRUE(frontier->rootReportCompleted(
        chain_static_tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 13, 12,
        true));

    tracker->stop();
}

// A stale static-sweep stamp alone no longer suppresses the weaker JNI report: after the static
// edge disappears and eviction drops the holder from the durable index, the JNI report is the only
// route back into indexed rotation, so it stages a re-enlistment observation even though the old
// sweep stamp is still on the frontier entry.
TEST_F(ReferenceChainsBfsTest, WeakerJniGlobalReportStagesDespiteStaleSweepStamp) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 21009;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    frontier->markRootReportObserved(
        tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 1U,
        /*static_sweep=*/true);

    AnchorScopedPass pass(tracker, frontier);
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY - 1,
              AnchorAcc::fillAnchorJournalForTest(
                  pass.ctx, AnchorObservationBuffer::CAPACITY - 1));
    jlong reported = tag;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, 0, &reported));
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::journalCountForTest())
        << "the stale sweep stamp must not suppress the JNI re-enlistment observation";
    pass.scope.flush();

    tracker->stop();
}

// A static-sweep stamp must never displace a stored enumeration stamp: both share
// root_report_attempt, and the sweep's high-bit id falls outside root enumeration's retry-sequence
// window, so the overwrite would restage the weaker JNI-global report on every retry - the exact
// starvation the stamp machinery prevents.
TEST_F(ReferenceChainsBfsTest, SweepStampDoesNotDisplaceEnumerationStamp) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    // Root-attached static holder (the shape whose sweep stamp takes the shared field): the
    // enumeration accepts its weaker JNI-global report first.
    const jlong tag = 21021;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    frontier->markRootReportObserved(tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 7);

    // The sweep arrives between enumeration attempts: it must keep the enumeration stamp.
    frontier->markRootReportObserved(
        tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 40U,
        /*static_sweep=*/true);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(7u, entry.root_report_attempt)
        << "a sweep stamp must not clobber the enumeration stamp";
    EXPECT_TRUE(entry.root_report_kind_mask &
                FrontierRootReport::JNI_GLOBAL_MASK);

    // The retry sequence still recognizes the stamp: the weaker JNI-global report stays
    // suppressed instead of restaging on every attempt.
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 8, 7, true));
    EXPECT_TRUE(frontier->rootReportCompleted(
        tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL, false, 9, 7, true));

    // A root-attached entry with no enumeration stamp keeps its sweep suppression through
    // the parallel sweep field (chain-attached entries use referrer_class_tag instead).
    const jlong free_tag = 21022;
    insertAnchorEntry(frontier, free_tag, 0, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    frontier->markRootReportObserved(
        free_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 41U,
        /*static_sweep=*/true);
    EXPECT_TRUE(frontier->rootReportCompleted(
        free_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD, false,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 42U,
        FrontierRootReport::STATIC_SWEEP_ATTEMPT_BIT | 41U, true,
        nullptr, /*static_sweep=*/true));

    tracker->stop();
}

// LOCAL staging cannot exceed replay capacity or refill the same journal prefix on every retry.
// At zero budget, fresh locals stay unstaged while a durable root report in the same scope still
// stages; this keeps refused locals from starving later roots.
TEST_F(ReferenceChainsBfsTest, LocalStagingBoundStopsRecordsReplayWouldRefuse) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const jlong kContainer = -3155;
    AnchorAcc::primeClassShapeForTest(kContainer, true);

    // Fill the local index and pending buffer with confirmed containers. With no displaceable
    // pending victim, replay cannot absorb further LOCAL reports.
    {
        AnchorScopedPass pass(tracker, frontier);
        const int kSaturate = 4096 + 1024;
        for (int i = 0; i < kSaturate; i++) {
            jlong reported = 0;
            EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                      pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kContainer, &reported));
            EXPECT_GT(reported, 0);
        }
        pass.scope.flush();
        EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    }

    // A fresh scope: the absorbable budget is zero. LOCAL reports of distinct fresh holders stage
    // nothing; a durable root report still stages its re-enlist record.
    AnchorScopedPass pass(tracker, frontier);
    const int kOverflowAttempts = 64;
    for (int i = 0; i < kOverflowAttempts; i++) {
        jlong reported = 0;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kContainer, &reported));
        EXPECT_EQ(0u, AnchorAcc::journalCountForTest())
            << "a saturated absorbable budget stages no LOCAL records";
    }
    insertAnchorEntry(frontier, 4242, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    jlong durable_tag = 4242;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, 0, &durable_tag));
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest())
        << "the durable root still stages with the LOCAL budget exhausted";
    pass.scope.flush();

    tracker->stop();
}

// The budget includes all entries the eviction cursor can skip to, without scanning the buffer.
TEST_F(ReferenceChainsBfsTest, LocalStagingBudgetCountsDisplaceablePendingEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const jlong kContainer = -3156;
    const jlong kUnclassified = -3157;
    const jlong kUnclassifiedTag = 50000;
    AnchorAcc::primeClassShapeForTest(kContainer, true);
    for (size_t i = 0; i < AnchorAcc::kLocalAnchorIndexCap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(10000 + (jlong)i, kContainer);
    }
    ASSERT_EQ(AnchorAcc::kLocalAnchorIndexCap, AnchorAcc::localAnchorCountForTest());
    AnchorAcc::noteLocalRootHolderForTest(kUnclassifiedTag, kUnclassified);
    for (size_t i = 0; i < AnchorAcc::kPendingLocalAnchorCap - 1; i++) {
        AnchorAcc::noteLocalRootHolderForTest(60000 + (jlong)i, kContainer);
    }
    ASSERT_EQ(AnchorAcc::kPendingLocalAnchorCap,
              AnchorAcc::pendingLocalAnchorCountForTest());
    AnchorAcc::preparePendingLocalAnchorEvictionCursorForTest();
    EXPECT_EQ(1u, AnchorAcc::localStagingAbsorbableForTest());

    AnchorScopedPass pass(tracker, frontier);
    jlong accepted_tag = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kContainer, &accepted_tag));
    ASSERT_GT(accepted_tag, 0);
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());

    jlong unstaged_tag = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kContainer, &unstaged_tag));
    ASSERT_GT(unstaged_tag, 0);
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());

    pass.scope.flush();
    EXPECT_FALSE(AnchorAcc::pendingLocalAnchorContainsForTest(kUnclassifiedTag));
    EXPECT_TRUE(AnchorAcc::pendingLocalAnchorContainsForTest(accepted_tag));
    EXPECT_FALSE(AnchorAcc::pendingLocalAnchorContainsForTest(unstaged_tag));
    EXPECT_EQ(0u, AnchorAcc::localStagingAbsorbableForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, UnclassifiedLocalsCannotSpendContainerIndexBudget) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const jlong unclassified = -3158;
    const jlong container = -3159;
    AnchorAcc::primeClassShapeForTest(container, true);
    AnchorScopedPass pass(tracker, frontier);
    const size_t pending_cap = AnchorAcc::kPendingLocalAnchorCap;
    const size_t index_cap = AnchorAcc::kLocalAnchorIndexCap;

    for (size_t i = 0; i < pending_cap + index_cap; i++) {
        jlong tag = 0;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, unclassified, &tag));
    }
    EXPECT_EQ(pending_cap, AnchorAcc::journalCountForTest())
        << "unclassified holders can consume pending slots only";

    std::vector<jlong> confirmed;
    confirmed.reserve(index_cap);
    for (size_t i = 0; i < index_cap; i++) {
        jlong tag = 0;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, container, &tag));
        confirmed.push_back(tag);
    }
    EXPECT_EQ(pending_cap + index_cap, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(pending_cap, AnchorAcc::pendingLocalAnchorCountForTest());
    EXPECT_EQ(index_cap, AnchorAcc::localAnchorCountForTest());
    for (jlong tag : confirmed) {
        EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(tag));
    }

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakTaggedLocalCollectionGetsAnAnchorObservation) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    const jlong container = -3160;
    AnchorAcc::primeClassShapeForTest(container, true);

    AnchorScopedPass pass(tracker, tracker->frontierTable());
    jlong leak_tag = AnchorAcc::leakTagForTest(7);
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, container, &leak_tag));
    ASSERT_GT(leak_tag, 0);
    EXPECT_NE(AnchorAcc::leakTagForTest(7), leak_tag);
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(leak_tag));
    EXPECT_EQ(1u, AnchorAcc::localAnchorCountForTest());

    tracker->stop();
}

// A local holder whose class is already classified non-container replays as a pure no-op
// (noteLocalRootHolder() returns before any state change): the LOCAL gate must not stage it, so
// a stable non-container local population never occupies journal slots.
TEST_F(ReferenceChainsBfsTest, AnchorJournalClassifiedNonContainerLocalStagesNothing) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const jlong kNonContainer = -3102;
    AnchorAcc::primeClassShapeForTest(kNonContainer, false);

    const jlong local = [&] {
        AnchorScopedPass pass(tracker, frontier);
        const jlong local = reportFreshLocal(pass, kNonContainer);
        EXPECT_GT(local, 0);
        EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
        pass.scope.flush();
        return local;
    }();
    ASSERT_GT(local, 0);
    EXPECT_EQ(0u, AnchorAcc::anchorIndexSizeForTest());

    // Re-report the same admitted tag at a full journal: it must not abort as a no-op.
    AnchorScopedPass retry(tracker, frontier);
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::fillAnchorJournalForTest(
                  retry.ctx, AnchorObservationBuffer::CAPACITY));
    jlong tag = local;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              retry.root(JVMTI_HEAP_ROOT_STACK_LOCAL, kNonContainer, &tag));
    EXPECT_EQ(local, tag);
    EXPECT_FALSE(retry.ctx.anchor_observation_overflow);
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::journalCountForTest());
    retry.scope.flush();

    tracker->stop();
}

// An unclassified local holder parks on its first report (a real effect); the re-report finds it
// already parked and must not stage a second record for it.
TEST_F(ReferenceChainsBfsTest, AnchorJournalParkedLocalRestagesNothing) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const jlong local = [&] {
        AnchorScopedPass pass(tracker, frontier);
        const jlong local = reportFreshLocal(pass, -3999);
        EXPECT_GT(local, 0);
        EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
        pass.scope.flush();
        return local;
    }();
    ASSERT_GT(local, 0);
    ASSERT_EQ(0u, AnchorAcc::anchorIndexSizeForTest());
    ASSERT_EQ(1u, AnchorAcc::pendingLocalAnchorCountForTest());

    AnchorScopedPass retry(tracker, frontier);
    jlong tag = local;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              retry.root(JVMTI_HEAP_ROOT_STACK_LOCAL, -3999, &tag));
    EXPECT_EQ(local, tag);
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    EXPECT_EQ(1u, AnchorAcc::pendingLocalAnchorCountForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AnchorJournalFullPendingBufferSkipsUnknownLocalNoops) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong unknown = -4101;
    const size_t cap = AnchorAcc::kPendingLocalAnchorCap;

    for (size_t i = 0; i < cap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(50000 + (jlong)i, unknown);
    }
    ASSERT_EQ(cap, AnchorAcc::pendingLocalAnchorCountForTest());

    AnchorScopedPass pass(tracker, frontier);
    jlong tag = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, unknown, &tag));
    ASSERT_GT(tag, 0);
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(cap, AnchorAcc::pendingLocalAnchorCountForTest());
    EXPECT_FALSE(AnchorAcc::pendingLocalAnchorContainsForTest(tag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AnchorJournalFullConfirmedPendingWithNoVictimSkipsLocalNoop) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong container = -4102;
    const size_t local_cap = AnchorAcc::kLocalAnchorIndexCap;
    const size_t pending_cap = AnchorAcc::kPendingLocalAnchorCap;
    AnchorAcc::primeClassShapeForTest(container, true);

    for (size_t i = 0; i < local_cap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(60000 + (jlong)i, container);
    }
    for (size_t i = 0; i < pending_cap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(70000 + (jlong)i, container);
    }
    ASSERT_EQ(local_cap, AnchorAcc::localAnchorCountForTest());
    ASSERT_EQ(pending_cap, AnchorAcc::pendingLocalAnchorCountForTest());

    AnchorScopedPass pass(tracker, frontier);
    ASSERT_EQ(pending_cap, AnchorAcc::pendingLocalEvictCursorForTest());
    jlong tag = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, container, &tag));
    ASSERT_GT(tag, 0);
    EXPECT_EQ(0u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(pending_cap, AnchorAcc::pendingLocalAnchorCountForTest());
    EXPECT_FALSE(AnchorAcc::pendingLocalAnchorContainsForTest(tag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AnchorJournalFullPendingWithVictimStagesConfirmedLocal) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong container = -4103, unknown = -4104;
    const size_t local_cap = AnchorAcc::kLocalAnchorIndexCap;
    const size_t pending_cap = AnchorAcc::kPendingLocalAnchorCap;
    AnchorAcc::primeClassShapeForTest(container, true);

    for (size_t i = 0; i < local_cap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(80000 + (jlong)i, container);
    }
    for (size_t i = 0; i < pending_cap; i++) {
        AnchorAcc::noteLocalRootHolderForTest(90000 + (jlong)i, unknown);
    }
    ASSERT_EQ(local_cap, AnchorAcc::localAnchorCountForTest());
    ASSERT_EQ(pending_cap, AnchorAcc::pendingLocalAnchorCountForTest());

    AnchorScopedPass pass(tracker, frontier);
    ASSERT_EQ(0u, AnchorAcc::pendingLocalEvictCursorForTest());
    jlong tag = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, container, &tag));
    ASSERT_GT(tag, 0);
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(tag, AnchorAcc::pendingLocalAnchorTagForTest(0));
    EXPECT_EQ(1u, AnchorAcc::pendingLocalEvictCursorForTest());
    EXPECT_FALSE(AnchorAcc::pendingLocalAnchorContainsForTest(90000));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AnchorJournalSkipsAlreadyQueuedAtRiskNoop) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong non_container = -4105;
    const jlong holder = 20001;
    AnchorAcc::primeClassShapeForTest(-555, false);
    insertAnchorEntry(frontier, holder, 20000, JVMTI_HEAP_REFERENCE_STACK_LOCAL,
                      non_container);
    AnchorAcc::pushStaticAnchorFifoForTest(holder, 0);

    AnchorScopedPass pass(tracker, frontier);
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::fillAnchorJournalForTest(
                  pass.ctx, AnchorObservationBuffer::CAPACITY));
    jlong tag = holder;
    EXPECT_EQ(JVMTI_VISIT_OBJECTS, pass.staticEdge(&tag));
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::journalCountForTest());
    EXPECT_TRUE(AnchorAcc::staticAnchorFifoContainsForTest(holder));
    pass.scope.flush();
    EXPECT_EQ(1u, AnchorAcc::staticAnchorFifoSizeForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AtRiskObservationGateHonorsQueueAndClassCaps) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    const size_t fifo_cap = AnchorAcc::priorityExpandCap();
    const u32 klass_cap = AnchorAcc::kAtRiskPerKlassCap;

    EXPECT_TRUE(AnchorAcc::atRiskAnchorNeedsObservationForTest(1, 42));
    for (u32 i = 0; i < klass_cap; i++) {
        AnchorAcc::pushStaticAnchorFifoForTest(100 + (jlong)i, 42);
    }
    EXPECT_FALSE(AnchorAcc::atRiskAnchorNeedsObservationForTest(1000, 42));
    EXPECT_TRUE(AnchorAcc::atRiskAnchorNeedsObservationForTest(1000, 43));

    for (size_t i = 0; i < fifo_cap - klass_cap; i++) {
        u32 klass_id = 100 + (u32)(i / klass_cap);
        AnchorAcc::pushStaticAnchorFifoForTest(2000 + (jlong)i, klass_id);
    }
    ASSERT_EQ(fifo_cap, AnchorAcc::staticAnchorFifoSizeForTest());
    EXPECT_FALSE(AnchorAcc::atRiskAnchorNeedsObservationForTest(5000, 999));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, StagedAtRiskReportsRespectPerClassQuota) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong class_tag = -4200;
    constexpr u32 klass_id = 42;
    tracker->classTags()->insert(class_tag, klass_id);
    const size_t cap = AnchorAcc::kAtRiskPerKlassCap;
    for (size_t i = 0; i < cap + 8; i++) {
        insertAnchorEntry(frontier, 30000 + (jlong)i, 20000,
                          JVMTI_HEAP_REFERENCE_STACK_LOCAL, class_tag);
    }

    AnchorScopedPass pass(tracker, frontier);
    for (size_t i = 0; i < cap + 8; i++) {
        jlong tag = 30000 + (jlong)i;
        EXPECT_EQ(JVMTI_VISIT_OBJECTS,
                  AnchorAcc::reportStaticFieldEdgeForTest(
                      -555, &tag, &pass.ctx, class_tag));
    }
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(cap, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(cap, AnchorAcc::staticAnchorFifoSizeForTest());

    std::vector<AnchorAcc::AtRiskAnchor> drained;
    EXPECT_EQ(1, AnchorAcc::drainStaticAnchorFifoForTest(1, drained));
    jlong reopened = 30000 + (jlong)(cap + 8);
    insertAnchorEntry(frontier, reopened, 20000, JVMTI_HEAP_REFERENCE_STACK_LOCAL,
                      class_tag);
    EXPECT_EQ(JVMTI_VISIT_OBJECTS,
              AnchorAcc::reportStaticFieldEdgeForTest(
                  -555, &reopened, &pass.ctx, class_tag));
    EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(cap, AnchorAcc::staticAnchorFifoSizeForTest());

    tracker->stop();
}

// Rejected per-klass staging must not consume scope class-set slots: a klass whose scope-local
// staging reached its per-klass cap rejects further records without claiming class-set slots, so
// another class keeps staging into the same scope afterwards (and the fixed table cannot fill up
// with zero-count claims).
TEST_F(ReferenceChainsBfsTest, RejectedAtRiskStagingKeepsClassSetSlotsForOtherClasses) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const size_t cap = AnchorAcc::kAtRiskPerKlassCap;
    const jlong class_tag_a = -4200;
    const jlong class_tag_b = -4201;
    tracker->classTags()->insert(class_tag_a, 42);
    tracker->classTags()->insert(class_tag_b, 43);
    // Per-klass cap anchors for A, then far more A anchors than the cap: the excess must be
    // REJECTED (not staged), and the rejections must not erode the class set.
    for (size_t i = 0; i < cap + 200; i++) {
        insertAnchorEntry(frontier, 30000 + (jlong)i, 20000,
                          JVMTI_HEAP_REFERENCE_STACK_LOCAL, class_tag_a);
    }
    const jlong b_tag = 31000;
    insertAnchorEntry(frontier, b_tag, 20000,
                      JVMTI_HEAP_REFERENCE_STACK_LOCAL, class_tag_b);

    AnchorScopedPass pass(tracker, frontier);
    for (size_t i = 0; i < cap + 200; i++) {
        jlong tag = 30000 + (jlong)i;
        EXPECT_EQ(JVMTI_VISIT_OBJECTS,
                  AnchorAcc::reportStaticFieldEdgeForTest(
                      -555, &tag, &pass.ctx, class_tag_a));
    }
    EXPECT_EQ(cap, AnchorAcc::journalCountForTest())
        << "only the per-klass cap's worth of A records may stage";

    // A different class stages into the same scope after all those rejections.
    jlong b_reported = b_tag;
    EXPECT_EQ(JVMTI_VISIT_OBJECTS,
              AnchorAcc::reportStaticFieldEdgeForTest(
                  -555, &b_reported, &pass.ctx, class_tag_b));
    EXPECT_EQ(cap + 1, AnchorAcc::journalCountForTest())
        << "the rejected A records must not have burned class-set slots";
    pass.scope.flush();
    EXPECT_EQ(cap + 1, AnchorAcc::staticAnchorFifoSizeForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, StagedAtRiskReportsRespectGlobalFifoQuota) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const size_t cap = AnchorAcc::priorityExpandCap();
    for (size_t i = 0; i < cap + 1; i++) {
        jlong class_tag = -50000 - (jlong)i;
        tracker->classTags()->insert(class_tag, (u32)i + 1);
        insertAnchorEntry(frontier, 40000 + (jlong)i, 20000,
                          JVMTI_HEAP_REFERENCE_STACK_LOCAL, class_tag);
    }

    AnchorScopedPass pass(tracker, frontier);
    for (size_t i = 0; i < cap + 1; i++) {
        jlong class_tag = -50000 - (jlong)i;
        jlong tag = 40000 + (jlong)i;
        EXPECT_EQ(JVMTI_VISIT_OBJECTS,
                  AnchorAcc::reportStaticFieldEdgeForTest(
                      -555, &tag, &pass.ctx, class_tag));
    }
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(cap, AnchorAcc::journalCountForTest());
    pass.scope.flush();
    EXPECT_EQ(cap, AnchorAcc::staticAnchorFifoSizeForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, AnchorJournalDeduplicatesLocalAndAtRiskWithinScope) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong unknown = -4106;
    const jlong non_container = -555;
    const jlong holder = 20002;
    AnchorAcc::primeClassShapeForTest(non_container, false);
    insertAnchorEntry(frontier, holder, 20000, JVMTI_HEAP_REFERENCE_STACK_LOCAL,
                      non_container);

    AnchorScopedPass pass(tracker, frontier);
    jlong local = 0;
    EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, unknown, &local));
    ASSERT_GT(local, 0);
    jlong at_risk = holder;
    EXPECT_EQ(JVMTI_VISIT_OBJECTS, pass.staticEdge(&at_risk));
    ASSERT_EQ(2u, AnchorAcc::journalCountForTest());
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::fillAnchorJournalForTest(
                  pass.ctx, AnchorObservationBuffer::CAPACITY));
    for (int i = 0; i < 8; i++) {
        jlong repeated = local;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, unknown, &repeated));
        EXPECT_EQ(JVMTI_VISIT_OBJECTS, pass.staticEdge(&at_risk));
    }
    EXPECT_FALSE(pass.ctx.anchor_observation_overflow);
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY,
              AnchorAcc::journalCountForTest());
    EXPECT_FALSE(AnchorAcc::staticAnchorFifoContainsForTest(holder));
    pass.scope.flush();
    EXPECT_TRUE(AnchorAcc::pendingLocalAnchorContainsForTest(local));
    EXPECT_TRUE(AnchorAcc::staticAnchorFifoContainsForTest(holder));

    tracker->stop();
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

    // Unbounded LOCAL staging: this test exercises the journal's own capacity mechanics, while
    // production bounds staging to what replay absorbs (localStagingAbsorbable()).
    ReferenceChainTracker::instance()->setLocalStagingBudgetOverrideForTest(0xFFFFFFFFu);
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
    ReferenceChainTracker::instance()->setLocalStagingBudgetOverrideForTest(0);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ReenlistedAnchorsKeepEveryFirstRotationTurn) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr int kHolders = 9000;
    std::vector<bool> served(kHolders + 1, false);
    int served_count = 0;
    for (int tag = 1; tag <= kHolders; tag++) {
        insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
        AnchorAcc::addToStaticAnchorIndexForTest(
            tag, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    }

    for (int pass = 0; pass < 1000 && served_count < kHolders; pass++) {
        for (int tag = 1; tag <= kHolders; tag++) {
            if (!AnchorAcc::anchorIndexContainsForTest(tag)) {
                AnchorAcc::addToStaticAnchorIndexForTest(
                    tag, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
            }
        }
        std::vector<jlong> selected =
            AnchorAcc::collectStaticFieldAnchorsForRotationForTest(32);
        for (jlong tag : selected) {
            ASSERT_GT(tag, 0);
            ASSERT_LE(tag, kHolders);
            if (!served[(size_t)tag]) {
                served[(size_t)tag] = true;
                served_count++;
            }
        }
    }
    EXPECT_EQ(kHolders, served_count)
        << "every live durable holder must retain a first-look turn across eviction";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, DurableAnchorIndexEvictionKeepsPendingFirstLooks) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const size_t cap = AnchorAcc::kDurableAnchorIndexCap;
    const size_t batch = AnchorAcc::kDurableAnchorEvictBatch;
    const jlong first = 1001;

    for (size_t i = 0; i <= cap; i++) {
        jlong tag = first + (jlong)i;
        insertAnchorEntry(frontier, tag, 0,
                          JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        AnchorAcc::addToStaticAnchorIndexForTest(
            tag, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    EXPECT_EQ(cap - batch, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_EQ(cap - batch, AnchorAcc::anchorOwnClassTagsSizeForTest());
    for (size_t i = 0; i < batch + 1; i++) {
        EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(first + (jlong)i));
    }
    EXPECT_TRUE(AnchorAcc::freshAnchorQueueContainsForTest(first))
        << "the evicted oldest holder keeps its unserved first look";
    EXPECT_FALSE(AnchorAcc::freshAnchorQueueContainsForTest(first + (jlong)cap))
        << "the bounded queue drops newest turns";
    EXPECT_LE(AnchorAcc::freshAnchorQueueSizeForTest(),
              AnchorAcc::freshAnchorQueueCapForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LocalThenDurableReportKeepsFirstLookOrder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong container = -3101;
    AnchorAcc::primeClassShapeForTest(container, true);
    const jlong earlier = 30001;
    insertAnchorEntry(frontier, earlier, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    AnchorAcc::addToStaticAnchorIndexForTest(
        earlier, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);

    AnchorScopedPass pass(tracker, frontier);
    jlong holder = 0;
    ASSERT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_STACK_LOCAL, container, &holder));
    ASSERT_GT(holder, 0);
    jlong again = holder;
    ASSERT_EQ(JVMTI_ITERATION_CONTINUE,
              pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, container, &again));
    EXPECT_EQ(2u, AnchorAcc::journalCountForTest());
    pass.scope.flush();

    EXPECT_EQ(2u, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_EQ(0u, AnchorAcc::localAnchorCountForTest());
    EXPECT_EQ((std::vector<jlong>{earlier, holder}),
              AnchorAcc::freshQueueTagsForTest());
    ASSERT_TRUE(frontier->improveChain(holder, earlier, 0, 1, 0));
    std::vector<jlong> selected =
        AnchorAcc::collectStaticFieldAnchorsForRotationForTest(8);
    EXPECT_NE(std::find(selected.begin(), selected.end(), holder),
              selected.end());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ReenlistedPendingTurnKeepsItsQueuePosition) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const size_t cap = AnchorAcc::kDurableAnchorIndexCap;
    const size_t batch = AnchorAcc::kDurableAnchorEvictBatch;
    const jlong victim = 20001;
    const jlong crossing = 20002;
    insertAnchorEntry(frontier, victim, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    insertAnchorEntry(frontier, crossing, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    AnchorAcc::addToStaticAnchorIndexForTest(
        victim, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    for (size_t i = 0; i < cap - 1; i++) {
        AnchorAcc::addToStaticAnchorIndexForTest(
            40000 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    }

    {
        AnchorScopedPass pass(tracker, frontier);
        ASSERT_TRUE(pass.scope.ownsLease());
        jlong reported = crossing;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  pass.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, -3001, &reported))
            << "journal=" << AnchorAcc::journalCountForTest()
            << " overflow=" << pass.ctx.anchor_observation_overflow;
        EXPECT_EQ(crossing, reported);
        pass.scope.flush();
    }
    EXPECT_EQ(cap - batch, AnchorAcc::anchorIndexSizeForTest());
    EXPECT_FALSE(AnchorAcc::anchorIndexContainsForTest(victim));
    ASSERT_GE(AnchorAcc::freshAnchorQueueSizeForTest(), 2u);
    EXPECT_EQ(victim, AnchorAcc::freshQueueTagsForTest().front());

    {
        AnchorScopedPass retry(tracker, frontier);
        ASSERT_TRUE(retry.scope.ownsLease());
        jlong reported = victim;
        EXPECT_EQ(JVMTI_ITERATION_CONTINUE,
                  retry.root(JVMTI_HEAP_ROOT_JNI_GLOBAL, -3001, &reported))
            << "journal=" << AnchorAcc::journalCountForTest()
            << " overflow=" << retry.ctx.anchor_observation_overflow;
        EXPECT_EQ(victim, reported);
        EXPECT_EQ(1u, AnchorAcc::journalCountForTest());
        retry.scope.flush();
    }
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(victim));
    EXPECT_EQ(victim, AnchorAcc::freshQueueTagsForTest().front());
    EXPECT_EQ(crossing, AnchorAcc::freshQueueTagsForTest()[1]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, ReplayedDurableWaveKeepsEvictedTurnsPending) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const size_t cap = AnchorAcc::kDurableAnchorIndexCap;
    const size_t batch = AnchorAcc::kDurableAnchorEvictBatch;
    const jlong first = 20000;
    insertRootAttachedDurableEntries(frontier, first, cap + 1);

    AnchorScopedPass pass(tracker, frontier);
    for (size_t i = 0; i <= cap; i++) {
        reportRediscovery(pass, first + (jlong)i);
    }
    pass.scope.flush();
    EXPECT_EQ(cap - batch, AnchorAcc::durableAnchorCountForTest());
    bool found_evicted_pending = false;
    for (jlong tag : AnchorAcc::freshQueueTagsForTest()) {
        FrontierEntry entry{};
        ASSERT_TRUE(frontier->lookup(tag, &entry));
        EXPECT_NE(0, entry.anchor_rotation_flags &
                        FrontierAnchorRotation::FIRST_LOOK_PENDING);
        if (!AnchorAcc::anchorIndexContainsForTest(tag)) {
            found_evicted_pending = true;
        }
    }
    EXPECT_TRUE(found_evicted_pending);

    tracker->stop();
}

// The root-enumeration stamp dedup suppresses a repeated durable report on an indexed holder
// (rootReportCompleted()'s anchor_indexed disjunct). When the index still stores the
// admission-time class tag 0 and this report carries the resolved tag, the callback must journal
// the re-enlist so replay's 0-to-resolved upgrade runs - otherwise selection cannot recognize
// the reparented holder's collection shape and persistent revisits stop.
TEST_F(ReferenceChainsBfsTest, SuppressedDurableReportStillRefreshesStoredClassTag) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 21001;
    const jlong resolved_class = -3107;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    ASSERT_EQ(0, AnchorAcc::indexedAnchorClassTagForTest(tag));

    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, tag, resolved_class);
        pass.scope.flush();
    }
    EXPECT_EQ(resolved_class, AnchorAcc::indexedAnchorClassTagForTest(tag))
        << "the suppressed report must still journal the 0-to-resolved refresh";

    // A further report on the resolved holder is a plain dedup no-op: the stored tag is already
    // resolved, so no refresh is journaled and the index state does not change.
    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, tag, resolved_class);
        pass.scope.flush();
    }
    EXPECT_EQ(resolved_class, AnchorAcc::indexedAnchorClassTagForTest(tag));
    EXPECT_EQ(1u, AnchorAcc::anchorIndexSizeForTest());

    tracker->stop();
}

// A locally indexed container sighted by a durable root edge promotes to the durable share: the
// callback journals the durable add even though the report itself is dedup-suppressed, and
// replay releases the local slot. Without it, a reparented holder consumes a local slot forever
// - 4,096 such holders block new local collections despite free durable capacity.
TEST_F(ReferenceChainsBfsTest, DurableSightingPromotesLocallyIndexedHolder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 22001;
    const jlong container_class = -3207;
    insertAnchorEntry(frontier, tag, 0, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    ReferenceChainsTestAccessor::primeClassShapeForTest(container_class, true);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(tag, container_class);
    ASSERT_EQ(1u, AnchorAcc::localAnchorCountForTest());
    ASSERT_EQ(1u, AnchorAcc::anchorIndexSizeForTest());

    {
        AnchorScopedPass pass(tracker, frontier);
        reportRediscovery(pass, tag, container_class);
        pass.scope.flush();
    }
    EXPECT_EQ(0u, AnchorAcc::localAnchorCountForTest())
        << "the durable sighting must release the local slot";
    EXPECT_EQ(1u, AnchorAcc::anchorIndexSizeForTest())
        << "the holder stays indexed, now in the durable share";
    EXPECT_EQ(container_class, AnchorAcc::indexedAnchorClassTagForTest(tag));

    tracker->stop();
}

// The re-enlist replay promotes a locally indexed holder the same way addToStaticAnchorIndex()
// does: the descent's durable-edge reports journal REENLIST_ELIGIBLE for indexed selectable
// holders, and that replay must release the local slot too.
TEST_F(ReferenceChainsBfsTest, ReenlistReplayPromotesLocallyIndexedHolder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong tag = 22051;
    const jlong container_class = -3208;
    insertAnchorEntry(frontier, tag, 555, JVMTI_HEAP_REFERENCE_STACK_LOCAL);
    ReferenceChainsTestAccessor::primeClassShapeForTest(container_class, true);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(tag, container_class);
    ASSERT_EQ(1u, AnchorAcc::localAnchorCountForTest());

    AnchorObservation record{};
    record.tag = tag;
    record.own_class_tag = container_class;
    record.actions = AnchorObservation::REENLIST_ELIGIBLE;
    ReferenceChainsTestAccessor::replayAnchorObservationsForTest({record});

    EXPECT_EQ(0u, AnchorAcc::localAnchorCountForTest())
        << "the re-enlist replay must release the local slot";
    EXPECT_EQ(1u, AnchorAcc::anchorIndexSizeForTest());

    tracker->stop();
}

// The re-enlist replay's promotion must enforce the durable cap the way addToStaticAnchorIndex()
// does: releasing the local slot grows the durable share while the dedup in
// indexAnchorForRotation() returns early for the still-indexed tag, so a promotion at a full
// durable share would exceed DURABLE_ANCHOR_INDEX_CAP until an unrelated admission evicts.
TEST_F(ReferenceChainsBfsTest, ReenlistReplayPromotionAtCapTriggersEviction) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const size_t batch = ReferenceChainsTestAccessor::kDurableAnchorEvictBatch;
    for (size_t i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            4001 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_EQ(cap, AnchorAcc::durableAnchorCountForTest());

    const jlong promoted = 22051;
    const jlong container_class = -3208;
    insertAnchorEntry(frontier, promoted, 555, JVMTI_HEAP_REFERENCE_STACK_LOCAL);
    ReferenceChainsTestAccessor::primeClassShapeForTest(container_class, true);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(promoted,
                                                            container_class);
    ASSERT_EQ(1u, AnchorAcc::localAnchorCountForTest());
    ASSERT_EQ(cap, AnchorAcc::durableAnchorCountForTest())
        << "the local holder's index push shifts the share boundary, not the "
           "durable share's size";

    AnchorObservation record{};
    record.tag = promoted;
    record.own_class_tag = container_class;
    record.actions = AnchorObservation::REENLIST_ELIGIBLE;
    ReferenceChainsTestAccessor::replayAnchorObservationsForTest({record});

    EXPECT_EQ(0u, AnchorAcc::localAnchorCountForTest())
        << "the promotion must release the local slot";
    EXPECT_EQ(cap - batch, AnchorAcc::durableAnchorCountForTest())
        << "the promotion at a full durable share must evict, not exceed the cap";
    EXPECT_TRUE(AnchorAcc::anchorIndexContainsForTest(promoted))
        << "the just promoted tag is the newest entry, never among the evicted "
           "oldest";

    tracker->stop();
}

// A confirmed container arriving after the pending buffer filled with unclassified holders in
// the same walk must still stage: every staged unknown is displaceable in replay, so the
// container's record displaces the oldest unknown instead of being rejected while a local slot
// would have been available through that displacement.
TEST_F(ReferenceChainsBfsTest, ConfirmedContainerDisplacesPendingUnknownInSameScope) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    const jlong container_class = -3307;
    ReferenceChainsTestAccessor::primeClassShapeForTest(container_class, true);
    // Fill the local share to its cap with confirmed containers.
    for (jlong t = 30001; t < 30001 + (jlong)ReferenceChainsTestAccessor::kLocalAnchorIndexCap;
         t++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(t, container_class);
    }
    ASSERT_EQ((size_t)ReferenceChainsTestAccessor::kLocalAnchorIndexCap,
              AnchorAcc::localAnchorCountForTest());

    {
        ReferenceChainAnchorObservationScope scope(tracker);
        auto stage_local_record = [&](jlong tag, jlong class_tag) -> bool {
            if (!scope.reserveLocalStaging(tag, class_tag)) {
                return false;
            }
            AnchorObservationReservationGuard reservation;
            if (!reservation.acquire(scope)) {
                return false;
            }
            AnchorObservation record{};
            record.tag = tag;
            record.own_class_tag = class_tag;
            record.actions = AnchorObservation::LOCAL;
            reservation.commit(record);
            return true;
        };
        // Unclassified holders fill the pending buffer: each spends one pending slot and, per
        // the displacement contract, makes itself evictable by a later confirmed container.
        for (int i = 0; i < (int)ReferenceChainsTestAccessor::kPendingLocalAnchorCap; i++) {
            ASSERT_TRUE(stage_local_record(40000 + i, -3999 - i));
        }
        ASSERT_TRUE(stage_local_record(50001, container_class))
            << "the confirmed container must stage by displacing a staged unknown";
        scope.flush();
    }
    EXPECT_TRUE(AnchorAcc::pendingLocalAnchorContainsForTest(50001));
    EXPECT_EQ((size_t)ReferenceChainsTestAccessor::kLocalAnchorIndexCap,
              AnchorAcc::localAnchorCountForTest())
        << "the container stays parked in the pending buffer; the local share is unchanged";
    EXPECT_EQ((size_t)ReferenceChainsTestAccessor::kPendingLocalAnchorCap,
              AnchorAcc::pendingLocalAnchorCountForTest());

    // The displacement budget is finite: once every pending unknown is displaced, further
    // confirmed containers are rejected. A mutation of the budget check from `> 0` to `>= 0`
    // would admit a container with no unknown left to displace.
    {
        ReferenceChainAnchorObservationScope scope(tracker);
        int admitted = 0;
        bool rejected = false;
        for (jlong t = 60000; t < 60000 + 1100 && !rejected; t++) {
            if (scope.reserveLocalStaging(t, container_class)) {
                admitted++;
            } else {
                rejected = true;
            }
        }
        EXPECT_TRUE(rejected) << "the displacement budget must be finite";
        EXPECT_EQ((size_t)ReferenceChainsTestAccessor::kPendingLocalAnchorCap - 1,
                  (size_t)admitted)
            << "exactly the remaining displaced unknowns may be staged";
    }

    tracker->stop();
}
