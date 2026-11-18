/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

TEST_F(ReferenceChainsBfsTest, RollingResumePopsProcessedEntriesOnTruncatedBatch) {
    Arguments args;
    // budget=4: small enough that expand truncates mid-batch after admitting a few children.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=5000:budget=4:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A static-field root: classNode -> listNode (the leaking collection).
    int classNode = addNode();
    int listNode = addNode();

    // A chain of 20 children hanging off listNode. With budget=4, the callback admits 4 children
    // then returns JVMTI_VISIT_ABORT (BUDGET_EXHAUSTED), truncating mid-batch.
    constexpr int kChainLen = 20;
    std::vector<int> chainNodes(kChainLen);
    for (int i = 0; i < kChainLen; i++) {
        chainNodes[i] = addNode();
    }

    // Distractor roots: 20 independent JNI-global roots, each with one child.
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
        ASSERT_EQ((u8)SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        listTag = tags_ever_assigned[listNode];
    }
    ASSERT_NE(0, listTag) << "listNode was never admitted to the frontier";

    // Phase 2: run passes until listNode is expanded (rolling resume pops it).
    for (int i = 0; i < 200; i++) {
        ASSERT_EQ((u8)SearchState::RUNNING, tracker->searchState());
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
        ASSERT_EQ((u8)SearchState::RUNNING, tracker->searchState());
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

// Truncated-batch completion must follow the REFERRER of admitted child edges, not the order in
// which top-level batch entries are visited: FollowReferences over the holder array reports every
// batch entry (holder -> element) before any entry's own children (mirrored by
// mock_FollowReferences()), so a batch entry visited early may still have children the truncation
// cut off. Marking it EXPANDED would drop those children from the search for good.
TEST_F(ReferenceChainsBfsTest, TruncatedBatchKeepsEntryWhoseChildrenWereCutOff) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();

    // Three boundary entries, two children each.
    int e[3];
    int c[3][2];
    for (int i = 0; i < 3; i++) {
        e[i] = addNode();
        c[i][0] = addNode();
        c[i][1] = addNode();
    }
    jlong etag[3];
    for (int i = 0; i < 3; i++) {
        // tagObject() draws from the tracker's own tag counter, so the children admitted below
        // can never collide with these seed tags.
        etag[i] = tracker->tagObject(&mock_jvmti, (jobject)&node_tags[e[i]]);
        ASSERT_NE(0, etag[i]);
        ASSERT_TRUE(frontier->insert(etag[i], 0, 1, 0, FrontierEntryState::EDGE));
        ReferenceChainsTestAccessor::pushPendingExpandForTest(etag[i]);
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, e[i], c[i][0], -1});
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, e[i], c[i][1], -1});
    }

    // Budget 3: admits c[0][0], c[0][1], c[1][0], then aborts on c[1][1]. Only e[0] has had all of
    // its children reported.
    int edges = 0;
    bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 3, &edges, &truncated);
    ASSERT_TRUE(truncated);
    EXPECT_EQ(3, edges);
    EXPECT_EQ(0, tags_ever_assigned[c[1][1]]);

    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(etag[0], &entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, entry.state)
        << "e[0] had all its children reported and should be EXPANDED";
    ASSERT_TRUE(frontier->lookup(etag[1], &entry));
    EXPECT_NE(FrontierEntryState::EXPANDED, entry.state)
        << "e[1]'s second child was cut off by the truncation - it must stay unexpanded";
    // The admitted children are appended behind them.
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    ASSERT_GE(pending.size(), 2u);
    EXPECT_EQ((std::vector<jlong>{etag[1], etag[2]}),
              std::vector<jlong>(pending.begin(), pending.begin() + 2))
        << "e[1] and e[2] must be re-queued at the front for the next pass";

    // The next drive with room to spare admits the children the truncation cut off.
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    EXPECT_NE(0, tags_ever_assigned[c[1][1]]);
    EXPECT_NE(0, tags_ever_assigned[c[2][0]]);
    EXPECT_NE(0, tags_ever_assigned[c[2][1]]);

    tracker->stop();
}

// Leak-tag interception respects the pass budget like any other admission (the leak-tagged object
// keeps its leak tag and is intercepted on a later pass), and an intercepted object is queued for
// expansion, so a walk that stops right after it still admits its subtree on the next pass.
TEST_F(ReferenceChainsBfsTest, LeakTagInterceptionRespectsBudgetAndQueuesExpansion) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    FrontierTable *frontier = tracker->frontierTable();

    int entry = addNode();
    int other = addNode();
    int leak = addNode();
    int child = addNode();
    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();
    node_tags[leak] = leak_tag;

    jlong etag = tracker->tagObject(&mock_jvmti, (jobject)&node_tags[entry]);
    ASSERT_NE(0, etag);
    ASSERT_TRUE(frontier->insert(etag, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(etag);
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, entry, other, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, entry, leak, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, leak, child, -1},
    };

    // Budget 1: `other` takes the only admission; the leak-tagged object must not overshoot it.
    int edges = 0;
    bool truncated = false;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1, &edges, &truncated);
    ASSERT_TRUE(truncated);
    EXPECT_EQ(1, edges);
    EXPECT_NE(0, tags_ever_assigned[other]);
    EXPECT_EQ(leak_tag, node_tags[leak])
        << "leak-tagged object was intercepted past the exhausted budget";

    // Next pass, budget 1 again: the leak-tagged object takes the only admission and the walk
    // stops before its child. It must stay queued for expansion.
    edges = 0;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1, &edges, &truncated);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(1, edges);
    jlong leak_ftag = node_tags[leak];
    ASSERT_NE(leak_tag, leak_ftag) << "leak-tagged object was never intercepted";
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(leak_ftag));
    std::vector<jlong> pending = ReferenceChainsTestAccessor::pendingExpandContents();
    EXPECT_NE(std::find(pending.begin(), pending.end(), leak_ftag), pending.end())
        << "intercepted leak-tagged object was not queued for expansion";
    EXPECT_EQ(0, tags_ever_assigned[child]);

    // The pass after that expands it and admits the child under it.
    edges = 0;
    ReferenceChainsTestAccessor::expandFrontierWithBudgetForTest(
        &mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    jlong child_ftag = tags_ever_assigned[child];
    ASSERT_NE(0, child_ftag) << "leak-tagged object's subtree was never expanded";
    FrontierEntry child_entry{};
    ASSERT_TRUE(frontier->lookup(child_ftag, &child_entry));
    EXPECT_EQ(leak_ftag, child_entry.parent_tag);

    tracker->stop();
}

// Verify the AIMD adaptive batch_size: with the per-call EMA over the CPU budget, expandFrontier
// should multiplicatively decrease the batch; under the budget it should additively increase toward
// the cap.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchSizeProportionalToWindow) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Adaptive-batch state is zeroed by reset() (SetUp) but zeroed here too for the same reason as
    // before: exact per-phase arithmetic below.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0);
    ReferenceChainsTestAccessor::setGotwBatchSize(0);
    ReferenceChainsTestAccessor::setPassDeadlineNs(0);

    // Seed a frontier root manually (mirrors PollWatchedTargetsTest's seeding style): node carries
    // frontier tag 1, pending expansion has exactly that tag.
    int rootNode = addNode();
    int childNode = addNode();
    node_tags[rootNode] = 1;
    ASSERT_TRUE(tracker->frontierTable()->insert(
        1, 0, 1, 0, FrontierEntryState::EDGE));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    int edges = 0;
    const u64 budget = ReferenceChainsTestAccessor::gotwCpuBudgetNs();

    // --- Populate phase: first GetObjectsWithTags call. The EMA should be non-zero afterwards, and
    // the near-zero mock call time means the window (nominal budget, no deadline) fits ~unbounded
    // many calls - the proportion scales the batch all the way to the cap.
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0u, ReferenceChainsTestAccessor::gotwEmaCallNs())
        << "per-call EMA should be populated after first GetObjectsWithTags";
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMaxBatch(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "near-free call should scale the batch to the cap";

    // --- Shrink phase: EMA at 2x the window with no deadline -> batch halves (512 x 1 / 1.6 after
    // the EMA update).
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget * 2);
    ReferenceChainsTestAccessor::setGotwBatchSize(512);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // EMA after the call: 2x window x 0.8 + mock elapsed/5 - slightly above 1.6x window, so the
    // exact expectation is computed from the actual EMA the same way the control law does (window =
    // nominal budget, no deadline): next = 512 x window / ema.
    EXPECT_EQ((size_t)(512ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA at ~1.6x the window should scale the batch to 512/1.6";

    // --- Grow phase: EMA at half the window -> batch scales up 2.5x, i.e. the floor-dominated
    // regime GROWS the batch (the whole point of the proportional law - the old AIMD could not grow
    // past a fixed budget even when bigger batches were nearly free).
    ReferenceChainsTestAccessor::setGotwBatchSize(64);
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget / 2);
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    // Same computation from the actual post-call EMA (~0.4x window): next = 64 x window / ema.
    EXPECT_EQ((size_t)(64ULL * budget /
                       std::max(ReferenceChainsTestAccessor::gotwEmaCallNs(),
                                1ULL)),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "EMA under the window should scale the batch up proportionally";

    // --- Deadline-window phase: with a live pass deadline the window is the REMAINING time, not
    // the nominal budget.
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

    // --- Admission sanity: expansion still walks the graph. Root -> child edge, one more drive,
    // child must be admitted.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, rootNode, childNode, -1});
    ReferenceChainsTestAccessor::pushPendingExpandForTest(1);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);
    EXPECT_NE(0, tags_ever_assigned[childNode])
        << "expandFrontier failed to admit childNode with adaptive batch_size";

    tracker->stop();
}

// gotwWindowNs() backlog-pressure widening, unit level: the pod regime is a remaining pass window
// (~10ms) smaller than the measured per-call floor (~22-40ms at a 242k-entry tag map), against a
// lane 127k deep.
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

    // Floor above the remaining window but a SHALLOW lane: no widening - the remaining window
    // stands (rotation fast-lane stays cheap).
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::gotwWindowNs(1, 1));

    // Floor above the remaining window and a DEEP lane: widened to EMA x mult, never below the
    // remaining window itself.
    EXPECT_EQ(floor * mult,
              ReferenceChainsTestAccessor::gotwWindowNs(1, depth));

    // Floor BELOW the remaining window: no widening even at depth - the ordinary proportional law
    // already fits the call in the window.
    ReferenceChainsTestAccessor::setGotwEmaCallNs(budget / 2);
    EXPECT_EQ(budget,
              ReferenceChainsTestAccessor::gotwWindowNs(budget, depth));
    ReferenceChainsTestAccessor::setGotwEmaCallNs(floor);

    // Floor above the NOMINAL window (deadline already passed, the exact pod's post-call state) at
    // depth: still widened - the floor is paid by the next call regardless, so the batch must
    // amortize it.
    EXPECT_EQ(floor * mult,
              ReferenceChainsTestAccessor::gotwWindowNs(0, depth));

    tracker->stop();
}

// The widened window in action through the real control loop: one GetObjectsWithTags call whose
// floor (simulated by the mock's busy-wait) exceeds both the remaining pass deadline and the
// nominal window, with a backlog deeper than GOTW_BACKLOG_MIN_DEPTH, must GROW the calibrated batch
// (calib x mult, exactly - the window scales with the measured EMA) instead of collapsing it to
// GOTW_MIN_BATCH.
TEST_F(ReferenceChainsBfsTest, AdaptiveBatchGrowsWhenFloorExceedsWindowUnderDeepBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A pass deadline a fraction of the simulated per-call floor: the call overruns it (exactly the
    // pod's 10ms window vs 22-40ms floor), so after the call the loop's deadline check stops the
    // invocation with ONE control update - deterministic arithmetic for the assertion below.
    gotw_delay_ns = ReferenceChainsTestAccessor::gotwCpuBudgetNs(); // 25ms floor
    ReferenceChainsTestAccessor::setPassDeadlineNs(OS::nanotime() + 5000000ULL);
    ReferenceChainsTestAccessor::setGotwBatchSize(ReferenceChainsTestAccessor::gotwMinBatch());
    ReferenceChainsTestAccessor::setGotwEmaCallNs(0); // seeded by the call below

    // A pending lane deep enough to cross GOTW_BACKLOG_MIN_DEPTH.
    const size_t depth = ReferenceChainsTestAccessor::gotwBacklogMinDepth() + 1;
    for (size_t i = 0; i < depth; i++) {
        ReferenceChainsTestAccessor::pushPendingExpandForTest(
            (jlong)(1000000 + i));
    }

    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti,
                                                       &mock_jni, &edges);

    // EMA after the call = the busy-wait floor (~25ms). The pass deadline is long past, so the
    // window is widened to EMA x GOTW_BACKLOG_WINDOW_MULT, and the control law computes calib x
    // window / ema = calib x mult - exactly, because the window is a whole multiple of the same EMA
    // it divides by.
    EXPECT_EQ(ReferenceChainsTestAccessor::gotwMinBatch() *
                  ReferenceChainsTestAccessor::gotwBacklogWindowMult(),
              ReferenceChainsTestAccessor::gotwBatchSize())
        << "the floor-dominated deep-backlog regime must GROW the batch, "
           "not clamp it to GOTW_MIN_BATCH";

    ReferenceChainsTestAccessor::setPassDeadlineNs(0);
    gotw_delay_ns = 0;
    tracker->stop();
}

// FAIR-SHARE DRAIN persistence: the lane toggle must survive across expandFrontier() invocations.
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

    // Mock GetObjectsWithTags calls are ~free, so without a deadline a single expandFrontier()
    // invocation would drain BOTH lanes in one loop.
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

    // Rotation refills the priority lane; invocation 2 must STILL prefer the pending lane - the
    // toggle persists, it is not reset per call.
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
// FANOUT HYGIENE: a _leak_parent_fanout entry whose parent no longer resolves in the frontier
// (pruned: dead object, or a search-restart wipe) can never be re-walked, so
// collectStaleExpandedEntriesForRotation() must erase it during selection rather than skip it
// forever - without the erase, the fanout grows monotonically with corpses (observed live at ~11k
// entries of overwhelmingly-dead old backing arrays), which both bloats the selection scan and
// turns the fanout cursor's lap arithmetic into mostly wasted skips.
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


// Leak-tag interception (design A + C): an object pre-tagged with a leak tag (as
// LivenessTracker::tagLeakInstances() would have set on a tracked leaking instance) must be
// admitted by converting the leak tag to a frontier tag, with the leak tag preserved in the
// frontier entry so buildChainEvent() emits it as target_tag - the ReferenceChain <->
// HeapLiveObject correlation key.
TEST_F(ReferenceChainsBfsTest, LeakTagInterceptionConvertsToFrontierTagAndCorrelates) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const jlong leak_tag = ReferenceChainsTestAccessor::leakTagBase();

    int rootNode = addNode();
    int leakChild = addNode();
    int plainChild = addNode();
    // Simulate tagLeakInstances(): the tracked leaking instance already carries a leak tag; the
    // sibling does not.
    node_tags[leakChild] = leak_tag;
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, rootNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, rootNode, leakChild, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, rootNode, plainChild, -1},
    };

    // A single pass drains this tiny graph to completion, and a completed search releases all JVMTI
    // tags (releaseSearchTags(), "tagsReleased" in runPass's own log) - so read the tags from
    // tags_ever_assigned, which records each tag at assignment time and is never reset (see its own
    // comment), not from node_tags (which reads 0 after release).
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));

    // The leak-tagged child's tag was REPLACED by a frontier tag (small positive, outside the leak
    // range).
    jlong leak_ftag = tags_ever_assigned[leakChild];
    ASSERT_NE(leak_tag, leak_ftag)
        << "leak tag was never intercepted - BFS did not reach the object";
    ASSERT_GT(leak_ftag, 0);
    EXPECT_LT(leak_ftag, leak_tag) << "frontier tag must be outside leak range";

    // The frontier entry preserves the leak tag for correlation.
    EXPECT_EQ(leak_tag, ReferenceChainsTestAccessor::frontierLeakTag(leak_ftag));

    // The untagged sibling got an ordinary admit: frontier tag assigned, but no leak tag stored.
    jlong plain_ftag = tags_ever_assigned[plainChild];
    ASSERT_GT(plain_ftag, 0);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::frontierLeakTag(plain_ftag));

    // Design C: buildChainEvent() reports the leak tag as target_tag for the leak-tagged instance,
    // and the plain frontier tag for the sibling.
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

// Candidate-scoped reach, prong 1 (walkCandidateThreadLocals()): a leak held through the leaking
// thread's ThreadLocalMap must be intercepted with its full chain by ONE bounded walk from the
// Thread object, no matter what the ordinary BFS backlog state is - and the walk's gates must keep
// it off the Thread's non-thread-local fields entirely.
TEST_F(ReferenceChainsBfsTest, ThreadWalkDescendsOnlyThreadLocalMapAndInterceptsLeak) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // The classes descendFromAnchor()'s resolutions look up by FindClass name (see
    // registerClassForFindClass' own comment) + the scripted graph's own classes.
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

    // Topological order (mock_FollowReferences replays edges in script order, expanding only refs
    // the production callback said to descend into).
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
    // The anchor gate compares the REFEREE's class tag, so the thread edges' class_idx values
    // matter: the tlmap edge carries ThreadLocalMap's tag, and the loader edges ClassLoader's.
    script[0].class_idx = tlmapIdx;
    script[1].class_idx = loaderIdx;
    script[3].class_idx = loaderIdx;

    // The first thread walks the REUSE path: its Thread object is already admitted (root-attached
    // THREAD entry + JVMTI tag) exactly as it is in production after the first walk pass or root
    // enumeration.
    FrontierTable *frontier = tracker->frontierTable();
    jlong anchor_tag =
        tracker->tagObject(&mock_jvmti,
                           reinterpret_cast<jobject>(&node_tags[threadNode]));
    ASSERT_GT(anchor_tag, 0);
    node_tags[threadNode] = anchor_tag;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, anchor_tag, 0, 0, FrontierEntryState::FRONTIER,
        (u8)JVMTI_HEAP_REFERENCE_THREAD));

    // Two candidate slots, two qualifying tids: tid 777's thread is pre-anchored (reuse path), tid
    // 778's is untagged (fresh-admission path - GetObjectClass + tagObject + insert, the path a
    // never-walked thread takes in production).
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

    // The ThreadLocalMap-held chain was admitted end-to-end and the leak-tagged chunk was
    // intercepted (tag replaced by a frontier tag, leak tag preserved for correlation).
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

    // Chain shape: Thread (root-attached, THREAD root kind) -> ThreadLocalMap -> holder -> chunk.
    FrontierEntry thread_entry{};
    ASSERT_TRUE(frontier->lookup(thread_ftag, &thread_entry));
    EXPECT_EQ(0, thread_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread_entry.root_kind);
    FrontierEntry chunk_entry{};
    ASSERT_TRUE(frontier->lookup(chunk_ftag, &chunk_entry));
    EXPECT_EQ(holder_ftag, chunk_entry.parent_tag);
    EXPECT_EQ(3u, chunk_entry.depth);

    // The gates kept the walk off the metadata branches: neither the Thread's own
    // contextClassLoader edge (anchor gate) nor a ClassLoader below ThreadLocalMap (no-descend
    // gate) was admitted.
    EXPECT_EQ(0, tags_ever_assigned[loaderNode])
        << "anchor gate must not admit the Thread's non-ThreadLocalMap fields";
    EXPECT_EQ(0, tags_ever_assigned[loaderNode2])
        << "no-descend gate must not admit fat-metadata classes below the anchor";

    // The second thread took the fresh-admission path (no prior tag/entry): its Thread object was
    // admitted root-attached with the THREAD root kind.
    jlong thread2_ftag = ReferenceChainsTestAccessor::getTagForTest(
        &mock_jvmti, reinterpret_cast<jobject>(&node_tags[threadNode2]));
    ASSERT_GT(thread2_ftag, 0) << "fresh thread anchor was never admitted";
    FrontierEntry thread2_entry{};
    ASSERT_TRUE(frontier->lookup(thread2_ftag, &thread2_entry));
    EXPECT_EQ(0, thread2_entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_THREAD, thread2_entry.root_kind);

    tracker->stop();
}

// unregisterThreadObject() must defer the global-ref deletion to releaseEndedThreadRefs():
// walkCandidateThreadLocals() copies the jobject out of _thread_objects under _thread_objects_lock,
// releases the lock, and can still be using it as a FollowReferences anchor when a concurrent
// ThreadEnd erases the entry - deleting there would be JNI use-after-free (see
// _thread_refs_pending_delete's comment).
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

    // The drain deletes exactly the queued ref, and draining an empty list is a no-op.
    tracker->releaseEndedThreadRefs(&mock_jni);
    EXPECT_EQ(1, global_refs_deleted_);
    tracker->releaseEndedThreadRefs(&mock_jni);
    EXPECT_EQ(1, global_refs_deleted_);

    tracker->stop();
}

// No pass runs while the tracker is idle, so threadLoop()'s per-iteration tail must drain the refs
// of threads that ended in the meantime - otherwise thread churn keeps queueing refs that are never
// deleted.
TEST_F(ReferenceChainsBfsTest, LoopIterationDrainsEndedThreadRefsWithoutPass) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int threadNode1 = addNode();
    int threadNode2 = addNode();
    tracker->registerThreadObject(
            &mock_jni, 556, reinterpret_cast<jthread>(&node_tags[threadNode1]));
    tracker->registerThreadObject(
            &mock_jni, 557, reinterpret_cast<jthread>(&node_tags[threadNode2]));
    tracker->unregisterThreadObject(&mock_jni, 556);
    tracker->unregisterThreadObject(&mock_jni, 557);
    ASSERT_EQ(2u, ReferenceChainsTestAccessor::pendingThreadRefDeletesForTest());

    tracker->finishLoopIterationSerialized(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, global_refs_deleted_);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingThreadRefDeletesForTest());

    tracker->stop();
}

// An onThreadStart() that read Profiler::_reference_chains_active before Profiler::stop() cleared it
// can call registerThreadObject() after releaseAllThreadObjects(); the registry is closed by then,
// so the new global ref is deleted instead of surviving into a later recording.
TEST_F(ReferenceChainsBfsTest, ThreadRefRegistrationAfterReleaseAllIsDropped) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    tracker->releaseAllThreadObjects(&mock_jni);

    int threadNode = addNode();
    int deleted_before = global_refs_deleted_;
    tracker->registerThreadObject(
            &mock_jni, 556, reinterpret_cast<jthread>(&node_tags[threadNode]));
    EXPECT_EQ(nullptr, ReferenceChainsTestAccessor::threadObjectForTest(556))
        << "registerThreadObject() registered into a released registry";
    EXPECT_EQ(deleted_before + 1, global_refs_deleted_)
        << "the rejected registration's global ref was not deleted";

    // The next recording's start() reopens the registry.
    ASSERT_FALSE(tracker->start(args));
    tracker->registerThreadObject(
            &mock_jni, 556, reinterpret_cast<jthread>(&node_tags[threadNode]));
    EXPECT_NE(nullptr, ReferenceChainsTestAccessor::threadObjectForTest(556));

    tracker->releaseAllThreadObjects(&mock_jni);
    tracker->stop();
}

// ProfilerTestAccessor - friend of Profiler (profiler.h), defined per translation unit like the
// identically-named classes in faultInjection_ut.cpp and referenceChainJfrRoundtrip_ut.cpp. Drives
// the private JVMTI thread-lifecycle handlers with no-op engines (both engines are NULL until
// Profiler::start(), which needs a live JVM).
class ProfilerTestAccessor {
public:
    static void setCpuEngine(Profiler *p, Engine *e) { p->_cpu_engine = e; }
    static void setWallEngine(Profiler *p, Engine *e) { p->_wall_engine = e; }
    static void setReferenceChainsActive(Profiler *p, bool v) { p->_reference_chains_active = v; }
    static Engine *cpuEngine(Profiler *p) { return p->_cpu_engine; }
    static Engine *wallEngine(Profiler *p) { return p->_wall_engine; }
    static void setEngines(Profiler *p, Engine *cpu, Engine *wall) {
        p->_cpu_engine = cpu;
        p->_wall_engine = wall;
    }
    static State state(Profiler *p) { return p->_state.load(std::memory_order_acquire); }
    static void setState(Profiler *p, State s) { p->_state.store(s, std::memory_order_release); }
    static int eventMask(Profiler *p) { return p->_event_mask; }
    static void setEventMask(Profiler *p, int mask) { p->_event_mask = mask; }
    static bool referenceChainsActive(Profiler *p) {
        return p->_reference_chains_active.load(std::memory_order_acquire);
    }
    static jvmtiEventMode threadEventsState(Profiler *p) { return p->_thread_events_state; }
    static void setThreadEventsState(Profiler *p, jvmtiEventMode m) { p->_thread_events_state = m; }
    static void onThreadStart(Profiler *p, jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
        p->onThreadStart(jvmti, jni, thread);
    }
    static void onThreadEnd(Profiler *p, jvmtiEnv *jvmti, JNIEnv *jni, jthread thread) {
        p->onThreadEnd(jvmti, jni, thread);
    }
};

// updateThreadName(self=true) in onThreadStart() queries GetThreadInfo(); failing it skips the
// name bookkeeping, which this test does not exercise.
static jvmtiError JNICALL mock_GetThreadInfoUnavailable(jvmtiEnv *, jthread, jvmtiThreadInfo *) {
    return JVMTI_ERROR_THREAD_NOT_ALIVE;
}

// A thread started after recording start must reach the tid -> Thread registry through
// Profiler::onThreadStart() (registerExistingThreads() only snapshots threads alive at start),
// otherwise walkCandidateThreadLocals() never walks its thread-locals; onThreadEnd() must hand the
// ref to deferred deletion so a dead thread is not pinned or anchored under a reused tid.
TEST_F(ReferenceChainsBfsTest, ProfilerThreadLifecycleRegistersLateThreadObject) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    // Earlier tests leave thread refs registered (the tracker singleton outlives them); start from
    // an empty registry so the counts below are exact. start() reopens it.
    tracker->releaseAllThreadObjects(&mock_jni);
    ASSERT_FALSE(tracker->start(args));
    jvmti_tbl.GetThreadInfo = &mock_GetThreadInfoUnavailable;

    Profiler *profiler = Profiler::instance();
    Engine noop_engine;
    Engine *orig_cpu_engine = profiler->cpuEngine();
    Engine *orig_wall_engine = profiler->wallEngine();
    ProfilerTestAccessor::setCpuEngine(profiler, &noop_engine);
    ProfilerTestAccessor::setWallEngine(profiler, &noop_engine);
    ProfilerTestAccessor::setReferenceChainsActive(profiler, true);

    int threadNode = addNode();
    jthread thread_obj = reinterpret_cast<jthread>(&node_tags[threadNode]);
    int tid = -1;
    jobject registered = nullptr;
    jobject after_end = nullptr;
    size_t pending_after_end = 0;
    // A fresh native thread: onThreadEnd() releases the calling thread's ProfiledThread.
    std::thread late([&]() {
        ProfilerTestAccessor::onThreadStart(profiler, &mock_jvmti, &mock_jni, thread_obj);
        tid = ProfiledThread::currentTid();
        registered = ReferenceChainsTestAccessor::threadObjectForTest(tid);
        ProfilerTestAccessor::onThreadEnd(profiler, &mock_jvmti, &mock_jni, thread_obj);
        after_end = ReferenceChainsTestAccessor::threadObjectForTest(tid);
        pending_after_end = ReferenceChainsTestAccessor::pendingThreadRefDeletesForTest();
    });
    late.join();

    ProfilerTestAccessor::setReferenceChainsActive(profiler, false);
    ProfilerTestAccessor::setCpuEngine(profiler, orig_cpu_engine);
    ProfilerTestAccessor::setWallEngine(profiler, orig_wall_engine);

    ASSERT_GE(tid, 0);
    EXPECT_EQ(reinterpret_cast<jobject>(thread_obj), registered)
        << "onThreadStart() did not register the late thread's Thread object";
    EXPECT_EQ(nullptr, after_end)
        << "onThreadEnd() left the dead thread's Thread object registered";
    EXPECT_EQ(1u, pending_after_end)
        << "onThreadEnd() must queue exactly one ref for deferred deletion";

    // releaseAllThreadObjects() (Profiler::stop()'s teardown) deletes every queued ref.
    int deleted_before = global_refs_deleted_;
    tracker->releaseAllThreadObjects(&mock_jni);
    EXPECT_EQ(deleted_before + 1, global_refs_deleted_);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingThreadRefDeletesForTest());

    tracker->stop();
}

// Candidate-scoped reach, prong 2 (collectStaticFieldAnchorsForRotation()/
// walkStaticFieldAnchors()): the collector selects exactly the root-attached static-holder entries
// with a wrapping cursor, and the walk reaches a leak held 3-4 hops inside a static collection in
// one bounded call - the shape the one-hop Tier-2 rotation demonstrably cannot reach from an
// un-expanded FRONTIER holder on a rising heap (pod rounds 5-6).

// ---------------------------------------------------------------------------------------------
// Production-caller-path tests for the anchor-observation journal. Each drives a real traversal
// caller (runPass(), expandFrontier(), walkCandidateThreadLocals()); the scope those callers own
// applies the callbacks' records at the return boundary, and a full journal aborts the report
// before its destructive transition so the same object is reported again by a later traversal.
// ---------------------------------------------------------------------------------------------

namespace {

using T8Acc = ReferenceChainsTestAccessor;

// Fills the live caller scope at a JVMTI return boundary so the next real callback reaches overflow.
struct T8JournalFill {
    static inline bool fill_on_ior = false;
    static inline int fill_on_follow_call = -1; // 0-based FollowReferences call to fill before
    static inline int follow_calls = 0;
    static inline jlong holder_tag = 0;
    static inline jlong holder_class_tag = -9101;
    static inline u32 count_after_fill = 0;

    static void reset() {
        fill_on_ior = false;
        fill_on_follow_call = -1;
        follow_calls = 0;
        holder_tag = 0;
        count_after_fill = 0;
    }

    // Keeps one fixture frontier entry for tests that assert the count after a rejected report.
    static void seedHolder(ReferenceChainTracker *tracker) {
        holder_tag = tracker->nextTag();
        T8Acc::primeClassShapeForTest(holder_class_tag, false);
        ASSERT_TRUE(T8Acc::insertFrontierEntry(
            tracker->frontierTable(), holder_tag, /*parent_tag=*/1, /*depth=*/1,
            FrontierEntryState::FRONTIER, JVMTI_HEAP_REFERENCE_STACK_LOCAL, 0,
            holder_class_tag));
    }

    static void fill(const void *user_data) {
        auto *ctx = const_cast<ReferenceChainPassContext *>(
            static_cast<const ReferenceChainPassContext *>(user_data));
        count_after_fill = static_cast<u32>(T8Acc::fillAnchorJournalForTest(
            *ctx, AnchorObservationBuffer::CAPACITY));
    }
};

jvmtiError JNICALL t8FillingIterate(jvmtiEnv *env, jvmtiHeapRootCallback root_cb,
                                    jvmtiStackReferenceCallback stack_cb,
                                    jvmtiObjectReferenceCallback object_cb,
                                    const void *user_data) {
    if (T8JournalFill::fill_on_ior) {
        T8JournalFill::fill(user_data);
    }
    return ReferenceChainsMockHeap::mock_IterateOverReachableObjects(
        env, root_cb, stack_cb, object_cb, user_data);
}

jvmtiError JNICALL t8FillingFollow(jvmtiEnv *env, jint heap_filter, jclass klass,
                                   jobject initial_object,
                                   const jvmtiHeapCallbacks *callbacks, const void *user_data) {
    if (T8JournalFill::follow_calls++ == T8JournalFill::fill_on_follow_call) {
        T8JournalFill::fill(user_data);
    }
    return ReferenceChainsMockHeap::mock_FollowReferences(
        env, heap_filter, klass, initial_object, callbacks, user_data);
}

// A scripted-root pass must enumerate roots, whatever an earlier pass of the singleton left.
void t8AllowRootEnumeration() {
    T8Acc::setRootEnumRawStateForTest(0, 0);
}

} // namespace

// Root enumeration: the prefix accepted before a JVMTI error is applied before the error handling
// returns, and the enumeration the error cut short is retried by the next pass.
TEST_F(ReferenceChainsBfsTest, RootEnumerationAppliesAcceptedPrefixBeforeJvmtiError) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const jlong leak_base = T8Acc::leakTagBase();
    int n[3] = {addNode(), addNode(), addNode()};
    for (int i = 0; i < 3; i++) {
        node_tags[n[i]] = leak_base + i;
        script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, n[i], -1});
    }
    active_fixture->ior_error_after_prefix = JVMTI_ERROR_OUT_OF_MEMORY;
    active_fixture->ior_prefix_count = 2;
    t8AllowRootEnumeration();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    // Two reports crossed the callback; the error then cut the walk before the third.
    EXPECT_EQ((int)JVMTI_ITERATION_CONTINUE, active_fixture->last_ior_control);
    jlong f0 = tags_ever_assigned[n[0]];
    jlong f1 = tags_ever_assigned[n[1]];
    ASSERT_NE(leak_base + 0, f0);
    ASSERT_GT(f0, 0);
    ASSERT_GT(f1, 0);
    EXPECT_EQ(0, tags_ever_assigned[n[2]]) << "the third root was never reported";
    EXPECT_EQ(leak_base + 2, node_tags[n[2]]);
    // The accepted prefix was flushed before the error return: both durable roots are indexed and
    // nothing is left in the journal.
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(f0));
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(f1));
    EXPECT_EQ(2u, T8Acc::anchorIndexSizeForTest());
    EXPECT_EQ(0u, T8Acc::journalCountForTest());

    // Retry: the third root is reported and indexed by the next enumeration.
    active_fixture->ior_error_after_prefix = JVMTI_ERROR_NONE;
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    jlong f2 = tags_ever_assigned[n[2]];
    ASSERT_GT(f2, 0);
    EXPECT_NE(leak_base + 2, f2);
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(f2));
    EXPECT_EQ(3u, T8Acc::anchorIndexSizeForTest());

    tracker->stop();
}

// Root enumeration with a full journal: the rejected leak conversion is not performed (the object
// keeps its leak tag, no frontier entry appears), the accepted prefix is still applied, and the
// retry converts it.
TEST_F(ReferenceChainsBfsTest, RootEnumerationOverflowLeavesLeakTagForRetry) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int leak_node = addNode();
    const jlong leak_tag = T8Acc::leakTagBase() + 7;
    node_tags[leak_node] = leak_tag;
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, leak_node, -1}};

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_ior = true;
    jvmti_tbl.IterateOverReachableObjects = &t8FillingIterate;
    t8AllowRootEnumeration();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill)
        << "the journal must be full when the rejected report arrives";
    EXPECT_TRUE(truncated);
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, active_fixture->last_ior_control);
    EXPECT_EQ(leak_tag, node_tags[leak_node]) << "overflow must leave the leak tag installed";
    EXPECT_EQ(1u, tracker->frontierTable()->size())
        << "no frontier entry may exist for the rejected conversion (only the fill holder)";
    EXPECT_EQ(0u, T8Acc::anchorIndexSizeForTest());
    EXPECT_EQ(0u, T8Acc::journalCountForTest()) << "the full prefix is replayed and cleared";

    jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
    T8JournalFill::reset();
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    jlong converted = tags_ever_assigned[leak_node];
    ASSERT_GT(converted, 0) << "the retry never converted the leak-tagged root";
    EXPECT_NE(leak_tag, converted);
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(converted));

    tracker->stop();
}

// Root upgrade of an already-admitted transient root to a durable one is a destructive transition:
// with a full journal the entry stays as it was and the next enumeration upgrades it.
TEST_F(ReferenceChainsBfsTest, RootEnumerationOverflowLeavesRootKindUnchangedForRetry) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int node = addNode();
    jlong tag = tracker->nextTag();
    node_tags[node] = tag;
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, node, -1}};

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_ior = true;
    jvmti_tbl.IterateOverReachableObjects = &t8FillingIterate;
    t8AllowRootEnumeration();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill);
    EXPECT_TRUE(truncated);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STACK_LOCAL, entry.root_kind)
        << "the rejected upgrade must not be performed";
    EXPECT_EQ(0, entry.parent_tag);
    EXPECT_EQ(tag, node_tags[node]);
    EXPECT_FALSE(T8Acc::anchorIndexContainsForTest(tag));

    jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
    T8JournalFill::reset();
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_JNI_GLOBAL, entry.root_kind);
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(tag));

    tracker->stop();
}

namespace {

// Seeds the demotion shape: `parent` is a queued, root-attached stack-local entry whose expansion
// delivers an edge onto `holder`, a root-attached STATIC_FIELD entry (deeper path => demotion).
struct T8DemotionSeed {
    static constexpr jlong kParentTag = 104;
    static constexpr jlong kHolderTag = 105;
};

} // namespace

// Expansion with a full journal: the demotion that would drop a durable root is not performed
// (entry stays root-attached, no at-risk push), the batch stays queued, and the retry demotes it.
TEST_F(ReferenceChainsBfsTest, ExpansionOverflowKeepsDemotionAndBatchForRetry) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int parent = addNode();
    int holder = addNode();
    script = {{JVMTI_HEAP_REFERENCE_FIELD, parent, holder, -1}};
    node_tags[parent] = T8DemotionSeed::kParentTag;
    node_tags[holder] = T8DemotionSeed::kHolderTag;
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, T8DemotionSeed::kHolderTag, 0, 0,
                                           FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, T8DemotionSeed::kParentTag, 0, 0,
                                           FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    T8Acc::pushPendingExpandForTest(T8DemotionSeed::kParentTag);

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_follow_call = 0;
    jvmti_tbl.FollowReferences = &t8FillingFollow;

    int edges = 0;
    bool truncated = false;
    // The test-only journal fill has no FIFO effect; the rejected demotion must not push one.
    const size_t fifo_before = T8Acc::staticAnchorFifoSizeForTest();
    T8Acc::expandFrontierWithBudgetForTest(&mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill);
    EXPECT_TRUE(truncated);
    EXPECT_EQ((int)JVMTI_VISIT_ABORT, active_fixture->last_follow_control);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(T8DemotionSeed::kHolderTag, &entry));
    EXPECT_EQ(0, entry.parent_tag) << "the rejected demotion must not be performed";
    EXPECT_EQ(0u, entry.depth);
    EXPECT_EQ(fifo_before, T8Acc::staticAnchorFifoSizeForTest());
    EXPECT_EQ(0u, T8Acc::journalCountForTest());
    // Incomplete batch: the source obligation stays queued and un-expanded.
    EXPECT_EQ(std::vector<jlong>{T8DemotionSeed::kParentTag}, T8Acc::pendingExpandContents());
    FrontierEntry parent_entry{};
    ASSERT_TRUE(frontier->lookup(T8DemotionSeed::kParentTag, &parent_entry));
    EXPECT_EQ(FrontierEntryState::FRONTIER, parent_entry.state);

    jvmti_tbl.FollowReferences = &mock_FollowReferences;
    T8JournalFill::reset();
    edges = 0;
    T8Acc::expandFrontierWithBudgetForTest(&mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_FALSE(truncated);
    ASSERT_TRUE(frontier->lookup(T8DemotionSeed::kHolderTag, &entry));
    EXPECT_EQ(T8DemotionSeed::kParentTag, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);
    EXPECT_TRUE(T8Acc::staticAnchorFifoContainsForTest(T8DemotionSeed::kHolderTag));
    EXPECT_EQ(0u, T8Acc::pendingExpandSize());
    ASSERT_TRUE(frontier->lookup(T8DemotionSeed::kParentTag, &parent_entry));
    EXPECT_EQ(FrontierEntryState::EXPANDED, parent_entry.state);

    tracker->stop();
}

// Expansion: records accepted before a JVMTI error are flushed before the error handling, and the
// batch (no entry known complete) stays queued.
TEST_F(ReferenceChainsBfsTest, ExpansionAppliesAcceptedPrefixBeforeJvmtiError) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int first = addNode();
    int second = addNode();
    int holder = addNode();
    int child = addNode();
    node_tags[first] = 104;
    node_tags[second] = 106;
    node_tags[holder] = 105;
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, first, holder, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, second, child, -1},
    };
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 105, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    for (jlong tag : {104, 106}) {
        ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
                                               JVMTI_HEAP_REFERENCE_STACK_LOCAL));
        T8Acc::pushPendingExpandForTest(tag);
    }
    // Two holder->element reports, then the first->holder demotion edge, then the error.
    active_fixture->follow_error_after_prefix = JVMTI_ERROR_OUT_OF_MEMORY;
    active_fixture->follow_prefix_count = 3;

    int edges = 0;
    bool truncated = false;
    T8Acc::expandFrontierWithBudgetForTest(&mock_jvmti, &mock_jni, 1000, &edges, &truncated);
    EXPECT_TRUE(truncated);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag) << "the demotion delivered before the error was kept";
    EXPECT_TRUE(T8Acc::staticAnchorFifoContainsForTest(105))
        << "its at-risk record was flushed before the error return";
    EXPECT_EQ(0u, T8Acc::journalCountForTest());
    EXPECT_EQ(0, tags_ever_assigned[child]) << "the error cut the walk before the second edge";
    EXPECT_EQ((std::vector<jlong>{104, 106}), T8Acc::pendingExpandContents());

    tracker->stop();
}

// Expansion: budget exhaustion keeps the accepted prefix, which includes the demotion delivered
// before the budget ran out.
TEST_F(ReferenceChainsBfsTest, ExpansionBudgetExhaustionKeepsAcceptedPrefix) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int parent = addNode();
    int holder = addNode();
    int admitted = addNode();
    int refused = addNode();
    node_tags[parent] = 104;
    node_tags[holder] = 105;
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, parent, holder, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, parent, admitted, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, parent, refused, -1},
    };
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 105, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    T8Acc::pushPendingExpandForTest(104);

    int edges = 0;
    bool truncated = false;
    T8Acc::expandFrontierWithBudgetForTest(&mock_jvmti, &mock_jni, 1, &edges, &truncated);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(1, edges);
    EXPECT_GT(tags_ever_assigned[admitted], 0);
    EXPECT_EQ(0, tags_ever_assigned[refused]);
    EXPECT_EQ((int)JVMTI_VISIT_ABORT, active_fixture->last_follow_control);
    EXPECT_TRUE(T8Acc::staticAnchorFifoContainsForTest(105))
        << "the demotion recorded before the budget abort must be applied";
    EXPECT_EQ(0u, T8Acc::journalCountForTest());

    tracker->stop();
}

// Root enumeration cut short by a full frontier: the rediscovery accepted before the cap-hitting
// root is flushed (indexed) on the abandoning exit, with nothing left in the journal.
TEST_F(ReferenceChainsBfsTest, RootEnumerationFrontierCapExitFlushesAcceptedAnchor) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int known = addNode();
    int fresh = addNode();
    const jlong known_tag = tracker->nextTag();
    node_tags[known] = known_tag;
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, known_tag, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_EQ(1u, frontier->size());
    ASSERT_FALSE(T8Acc::anchorIndexContainsForTest(known_tag));
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, known, -1},
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, fresh, -1},
    };
    t8AllowRootEnumeration();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(truncated);
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, active_fixture->last_ior_control);
    EXPECT_EQ(0, tags_ever_assigned[fresh]) << "the second root must not be admitted";
    EXPECT_EQ(1u, frontier->size()) << "the cap must have been what refused the second root";
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());
    EXPECT_EQ((u8)SearchAbandonReason::FRONTIER_CAP, T8Acc::searchAbandonReasonForTest());
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(known_tag))
        << "the rediscovery accepted before the cap exit must be flushed";
    EXPECT_EQ(1u, T8Acc::anchorIndexSizeForTest());
    EXPECT_EQ(0u, T8Acc::journalCountForTest());

    tracker->stop();
}

// Static sweep with a full journal: the rejected static attachment is not admitted, the lap is not
// reported complete (the next pass sweeps again), exactly one resweep retry is requested, and the
// retry admits and indexes the holder.
TEST_F(ReferenceChainsBfsTest, StaticSweepOverflowRetriesChunkWithoutServing) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int class_node = addNode();
    int holder = addNode();
    addClass((void *)&node_tags[class_node], "Lcom/rc/statics/OverflowHolder;");
    script = {{JVMTI_HEAP_REFERENCE_STATIC_FIELD, class_node, holder, -1}};

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_follow_call = 0; // no candidates: the sweep is the first Follow call
    jvmti_tbl.FollowReferences = &t8FillingFollow;
    t8AllowRootEnumeration();
    const u64 gen_before = T8Acc::durableAnchorResweepGenForTest();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill)
        << "the sweep's walk must be the one that met the full journal";
    EXPECT_TRUE(truncated);
    EXPECT_EQ(0, tags_ever_assigned[holder]) << "the rejected admission must not be performed";
    EXPECT_EQ(0, node_tags[holder]);
    EXPECT_EQ(0, T8Acc::staticFieldSweepCursorForTest());
    EXPECT_EQ(gen_before + 1, T8Acc::durableAnchorResweepGenForTest())
        << "a rejected static attachment requests exactly one resweep";
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest());
    EXPECT_EQ(0u, T8Acc::journalCountForTest());

    jvmti_tbl.FollowReferences = &mock_FollowReferences;
    T8JournalFill::reset();
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    jlong admitted_tag = tags_ever_assigned[holder];
    ASSERT_GT(admitted_tag, 0) << "overflow was reported as a served chunk: no second sweep ran";
    EXPECT_TRUE(T8Acc::anchorIndexContainsForTest(admitted_tag));
    EXPECT_EQ(0, T8Acc::staticFieldSweepCursorForTest());

    tracker->stop();
}

namespace {

// kLapClasses loaded mock classes (> one 512-class sweep chunk), each a class object with one
// static field holding its own distinct holder. All nodes are created before any class captures a
// node address (addNode() may reallocate node_tags).
constexpr int kLapClasses = 600;
// Mirrors ReferenceChainTracker::STATIC_FIELD_SWEEP_CHUNK_CLASSES (private; the cursor assertions
// fail if the production value differs).
constexpr int kLapChunk = 512;

struct T8LapWorld {
    std::vector<int> class_nodes;
    std::vector<int> holders;
    std::vector<int> chunk0; // class indices in the first sweep chunk (ascending class tag)
    std::vector<int> chunk1;
};

void t8BuildLapWorld(ReferenceChainsMockHeap &heap, T8LapWorld *w) {
    static char sigs[kLapClasses][40];
    for (int i = 0; i < kLapClasses; i++) {
        w->class_nodes.push_back(heap.addNode());
        w->holders.push_back(heap.addNode());
    }
    for (int i = 0; i < kLapClasses; i++) {
        snprintf(sigs[i], sizeof(sigs[i]), "Lcom/rc/lap/C%d;", i);
        heap.addClass((void *)&heap.node_tags[w->class_nodes[i]], sigs[i]);
        heap.script.push_back(
            {JVMTI_HEAP_REFERENCE_STATIC_FIELD, w->class_nodes[i], w->holders[i], -1});
    }
}

// The sweep orders classes by their (negative) class tag, minted by resolveLoadedClasses() in the
// first pass; reads that order back so assertions name the real chunk membership.
void t8PartitionChunks(const ReferenceChainsMockHeap &heap, T8LapWorld *w) {
    std::vector<int> order(kLapClasses);
    for (int i = 0; i < kLapClasses; i++) {
        order[i] = i;
    }
    std::sort(order.begin(), order.end(), [&](int a, int b) {
        return heap.node_tags[w->class_nodes[a]] < heap.node_tags[w->class_nodes[b]];
    });
    w->chunk0.assign(order.begin(), order.begin() + kLapChunk);
    w->chunk1.assign(order.begin() + kLapChunk, order.end());
}

size_t t8AdmittedHolders(const ReferenceChainsMockHeap &heap, const T8LapWorld &w,
                         const std::vector<int> &classes) {
    size_t n = 0;
    for (int c : classes) {
        n += heap.tags_ever_assigned[w.holders[c]] != 0;
    }
    return n;
}

// Fills the durable share to exactly the cap (distinct indexed anchors with EXPANDED frontier
// entries, so no pass re-expands them), without crossing it. Tags stay below the frontier cap.
void t8FillDurableShareToCap(ReferenceChainTracker *tracker, jlong first_tag) {
    const size_t cap = T8Acc::kDurableAnchorIndexCap;
    for (jlong tag = first_tag; T8Acc::durableAnchorCountForTest() < cap; tag++) {
        ASSERT_TRUE(T8Acc::insertFrontierEntry(tracker->frontierTable(), tag, 0, 0,
                                               FrontierEntryState::EXPANDED,
                                               JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        T8Acc::addToStaticAnchorIndexForTest(tag, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_EQ(cap, T8Acc::durableAnchorCountForTest());
}

// Crosses the cap exactly once: one more distinct anchor evicts, requesting one resweep.
void t8CrossDurableCapOnce(ReferenceChainTracker *tracker, jlong tag) {
    const u64 gen = T8Acc::durableAnchorResweepGenForTest();
    ASSERT_TRUE(T8Acc::insertFrontierEntry(tracker->frontierTable(), tag, 0, 0,
                                           FrontierEntryState::EXPANDED,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    T8Acc::addToStaticAnchorIndexForTest(tag, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    ASSERT_EQ(gen + 1, T8Acc::durableAnchorResweepGenForTest())
        << "the cap crossing must request exactly one resweep";
    ASSERT_GT(T8Acc::durableAnchorCountForTest(), 0u);
}

// Keeps the search RUNNING across passes that discover nothing new (a watched klass defers the
// natural-completion branch, which would release every tag and ignore later passes).
void t8KeepSearchRunning() {
    T8Acc::setWatchedLeakKlassIdsForTest({1});
}

} // namespace

// Real multi-chunk static sweep over > 512 loaded classes: chunk 0 completes and leaves the cursor
// at the chunk size; a cap crossing between passes requests a resweep WITHOUT resetting the
// cursor; the second chunk completes the lap latched at class 0 (old generation) and leaves the
// new generation unserved; the next full lap from class 0 serves it only after its final chunk.
TEST_F(ReferenceChainsBfsTest, StaticSweepMultiChunkLapServesOnlyItsStartLatchedGeneration) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=5000:firstpassbudget=5000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    t8KeepSearchRunning();

    T8LapWorld w;
    t8BuildLapWorld(*this, &w);
    ASSERT_EQ(kLapClasses, (int)classes.size());
    ASSERT_GT(kLapClasses, kLapChunk);

    // Lap 1, chunk 0 (class-zero start latches the current, already-served generation).
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    ASSERT_EQ((u8)SearchState::RUNNING, tracker->searchState());
    t8PartitionChunks(*this, &w);
    EXPECT_EQ(kLapChunk, T8Acc::staticFieldSweepCursorForTest());
    EXPECT_EQ((size_t)kLapChunk, t8AdmittedHolders(*this, w, w.chunk0));
    EXPECT_EQ(0u, t8AdmittedHolders(*this, w, w.chunk1)) << "chunk 1 must not be swept yet";
    EXPECT_FALSE(T8Acc::durableAnchorResweepUnservedForTest());

    // Cross the durable cap once while the lap is in flight.
    t8FillDurableShareToCap(tracker, 10000);
    t8CrossDurableCapOnce(tracker, 40000);
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest());
    EXPECT_EQ(kLapChunk, T8Acc::staticFieldSweepCursorForTest())
        << "the resweep request must not reset the in-flight cursor";

    // Chunk 1 completes the OLD lap: the cursor wraps, but the new generation stays unserved.
    truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ((size_t)kLapClasses - kLapChunk, t8AdmittedHolders(*this, w, w.chunk1));
    EXPECT_EQ(0, T8Acc::staticFieldSweepCursorForTest()) << "the lap must have completed";
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest())
        << "the lap latched before the eviction must not serve the later request";

    // The next lap starts at class 0, latches the new generation, and serves it only at its end.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(kLapChunk, T8Acc::staticFieldSweepCursorForTest());
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest())
        << "a lap's first chunk must not serve its generation";
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(0, T8Acc::staticFieldSweepCursorForTest());
    EXPECT_FALSE(T8Acc::durableAnchorResweepUnservedForTest())
        << "the lap's final chunk must serve the generation it latched at class 0";

    tracker->stop();
}

// A truncated (journal-overflow) second chunk is not served: the cursor retries the chunk start,
// the lap is not reported complete, and the retry later completes the lap without serving the
// resweep the overflow requested.
TEST_F(ReferenceChainsBfsTest, StaticSweepMultiChunkTruncatedChunkRetriesWithoutServingLap) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=5000:firstpassbudget=5000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    t8KeepSearchRunning();

    T8LapWorld w;
    t8BuildLapWorld(*this, &w);

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_FALSE(truncated);
    ASSERT_EQ(kLapChunk, T8Acc::staticFieldSweepCursorForTest());
    t8PartitionChunks(*this, &w);
    ASSERT_EQ((size_t)kLapChunk, t8AdmittedHolders(*this, w, w.chunk0));
    const int saved_cursor = T8Acc::staticFieldSweepCursorForTest();

    // Chunk 1 with a full journal: its new static attachments are rejected.
    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_follow_call = 0; // the sweep is the first Follow call of the pass
    jvmti_tbl.FollowReferences = &t8FillingFollow;
    const u64 gen_before = T8Acc::durableAnchorResweepGenForTest();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill)
        << "the chunk-1 sweep must be the walk that met the full journal";
    EXPECT_TRUE(truncated);
    EXPECT_EQ(saved_cursor, T8Acc::staticFieldSweepCursorForTest())
        << "a truncated chunk must retry its own start, not advance or wrap";
    EXPECT_EQ(0u, t8AdmittedHolders(*this, w, w.chunk1)) << "rejected attachments must not be admitted";
    EXPECT_EQ(gen_before + 1, T8Acc::durableAnchorResweepGenForTest());
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest());

    // Retry: the chunk completes the lap; the overflow-requested generation stays unserved.
    jvmti_tbl.FollowReferences = &mock_FollowReferences;
    T8JournalFill::reset();
    truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(truncated);
    EXPECT_EQ((size_t)kLapClasses - kLapChunk, t8AdmittedHolders(*this, w, w.chunk1));
    EXPECT_EQ(0, T8Acc::staticFieldSweepCursorForTest());
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest())
        << "a lap whose chunk was truncated must not serve the request that truncation raised";

    // A full fresh lap from class 0 then serves it.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_TRUE(T8Acc::durableAnchorResweepUnservedForTest());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_FALSE(T8Acc::durableAnchorResweepUnservedForTest());

    tracker->stop();
}

// Selected-anchor walk with a full journal: the rejected demotion below the anchor's walk is not
// performed, the anchor returns to the front of the at-risk FIFO, and the next pass walks it again.
TEST_F(ReferenceChainsBfsTest, SelectedAnchorWalkOverflowRequeuesAnchorForRetry) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    int root = addNode();
    int anchor = addNode();
    int holder = addNode();
    node_tags[root] = 104;
    node_tags[anchor] = 105;
    node_tags[holder] = 107;
    script = {{JVMTI_HEAP_REFERENCE_FIELD, anchor, holder, -1}};
    // The anchor is chain-attached (the at-risk shape); the holder below it is a durable root that
    // the walk's edge would demote.
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 107, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    T8Acc::pushStaticAnchorFifoForTest(105, 28366);

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_follow_call = 0; // the anchor walk is the pass's only Follow call
    jvmti_tbl.FollowReferences = &t8FillingFollow;
    t8AllowRootEnumeration();

    bool truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill);
    EXPECT_TRUE(truncated);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(107, &entry));
    EXPECT_EQ(0, entry.parent_tag) << "the rejected demotion must not be performed";
    EXPECT_FALSE(T8Acc::staticAnchorFifoContainsForTest(107));
    EXPECT_TRUE(T8Acc::staticAnchorFifoContainsForTest(105))
        << "the partially walked anchor must be restored to the FIFO";
    EXPECT_EQ(0u, T8Acc::journalCountForTest());

    jvmti_tbl.FollowReferences = &mock_FollowReferences;
    T8JournalFill::reset();
    t8AllowRootEnumeration();
    truncated = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_TRUE(frontier->lookup(107, &entry));
    EXPECT_EQ(105, entry.parent_tag);
    EXPECT_TRUE(T8Acc::staticAnchorFifoContainsForTest(107))
        << "the retried walk's demotion is applied before the pass returns";
    EXPECT_FALSE(T8Acc::staticAnchorFifoContainsForTest(105));

    tracker->stop();
}

// Candidate-thread descent with a full journal: the first thread's rejected demotion stops the
// group before the second thread is walked; the accepted prefix is flushed on the way out, and the
// retry walks both threads.
TEST_F(ReferenceChainsBfsTest, CandidateThreadWalkOverflowStopsGroupAndFlushesPrefix) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    void *threadCls = (void *)0x3101, *tlmapCls = (void *)0x3102, *loaderCls = (void *)0x3103;
    int tlmapIdx = registerClassForFindClass(
        tlmapCls, "java/lang/ThreadLocal$ThreadLocalMap", "Ljava/lang/ThreadLocal$ThreadLocalMap;");
    registerClassForFindClass(loaderCls, "java/lang/ClassLoader", "Ljava/lang/ClassLoader;");
    registerClassForFindClass(threadCls, "java/lang/Thread", "Ljava/lang/Thread;");
    thread_class = threadCls;
    T8Acc::resolveLoadedClasses(&mock_jvmti, &mock_jni);

    int thread1 = addNode();
    int thread2 = addNode();
    int tlmap = addNode();
    int holder = addNode();
    node_tags[holder] = 107;
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, thread1, tlmap, tlmapIdx},
        {JVMTI_HEAP_REFERENCE_FIELD, tlmap, holder, -1},
    };
    // The first thread is already admitted root-attached (reuse path); the second is minted on
    // its first walk. The durable holder under the ThreadLocalMap is what the walk demotes.
    jlong anchor_tag = tracker->tagObject(
        &mock_jvmti, reinterpret_cast<jobject>(&node_tags[thread1]));
    ASSERT_GT(anchor_tag, 0);
    node_tags[thread1] = anchor_tag;
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, anchor_tag, 0, 0, FrontierEntryState::FRONTIER,
                                           (u8)JVMTI_HEAP_REFERENCE_THREAD));
    ASSERT_TRUE(T8Acc::insertFrontierEntry(frontier, 107, 0, 0, FrontierEntryState::FRONTIER,
                                           JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    jint tids0[] = {777};
    jint tids1[] = {778};
    T8Acc::seedCandidateSlotForTest(0, 6, tids0, 1);
    T8Acc::seedCandidateSlotForTest(1, 6, tids1, 1);
    tracker->registerThreadObject(&mock_jni, 777, reinterpret_cast<jthread>(&node_tags[thread1]));
    tracker->registerThreadObject(&mock_jni, 778, reinterpret_cast<jthread>(&node_tags[thread2]));

    T8JournalFill::reset();
    T8JournalFill::seedHolder(tracker);
    T8JournalFill::fill_on_follow_call = 0;
    jvmti_tbl.FollowReferences = &t8FillingFollow;

    int edges = 0;
    T8Acc::walkCandidateThreadLocalsForTest(&mock_jvmti, &mock_jni, 1000, &edges);
    ASSERT_EQ(AnchorObservationBuffer::CAPACITY, T8JournalFill::count_after_fill);
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(107, &entry));
    EXPECT_EQ(0, entry.parent_tag) << "the rejected demotion must not be performed";
    EXPECT_EQ(0, T8Acc::getTagForTest(&mock_jvmti, reinterpret_cast<jobject>(&node_tags[thread2])))
        << "an overflowed descent must end the group before the next thread";
    EXPECT_EQ(0u, T8Acc::journalCountForTest()) << "the group's scope flushed on exit";

    jvmti_tbl.FollowReferences = &mock_FollowReferences;
    T8JournalFill::reset();
    edges = 0;
    T8Acc::walkCandidateThreadLocalsForTest(&mock_jvmti, &mock_jni, 1000, &edges);
    ASSERT_TRUE(frontier->lookup(107, &entry));
    EXPECT_EQ(tags_ever_assigned[tlmap], entry.parent_tag)
        << "the retried descent demotes the holder under the ThreadLocalMap";
    EXPECT_GT(T8Acc::getTagForTest(&mock_jvmti, reinterpret_cast<jobject>(&node_tags[thread2])), 0)
        << "the retry continues to the second thread";

    tracker->stop();
}

// ---------------------------------------------------------------------------------------------
// Profiler::stop() and the BFS worker join (ProfilerTestAccessor, defined above).
// ---------------------------------------------------------------------------------------------

namespace {

// Counts the teardown calls stop() makes on an engine.
class T8CountingEngine : public Engine {
public:
    int stops = 0;
    int enable_calls = 0;
    void stop() override { stops++; }
    void enableEvents(bool) override { enable_calls++; }
};

// Puts the Profiler singleton back exactly as found, whatever the test asserted or returned from.
class T8ProfilerStateGuard {
public:
    T8ProfilerStateGuard()
        : _profiler(Profiler::instance()),
          _state(ProfilerTestAccessor::state(_profiler)),
          _cpu(ProfilerTestAccessor::cpuEngine(_profiler)),
          _wall(ProfilerTestAccessor::wallEngine(_profiler)),
          _mask(ProfilerTestAccessor::eventMask(_profiler)),
          _active(ProfilerTestAccessor::referenceChainsActive(_profiler)),
          _thread_events(ProfilerTestAccessor::threadEventsState(_profiler)),
          _vm(VMTestAccessor::getVm()) {}
    ~T8ProfilerStateGuard() {
        ProfilerTestAccessor::setState(_profiler, _state);
        ProfilerTestAccessor::setEngines(_profiler, _cpu, _wall);
        ProfilerTestAccessor::setEventMask(_profiler, _mask);
        ProfilerTestAccessor::setReferenceChainsActive(_profiler, _active);
        ProfilerTestAccessor::setThreadEventsState(_profiler, _thread_events);
        VMTestAccessor::setVm(_vm);
    }

private:
    Profiler *_profiler;
    State _state;
    Engine *_cpu;
    Engine *_wall;
    int _mask;
    bool _active;
    jvmtiEventMode _thread_events;
    JavaVM *_vm;
};

jint JNICALL t8MockGetEnv(JavaVM *, void **penv, jint) {
    *penv = &ReferenceChainsMockHeap::active_fixture->mock_jni;
    return JNI_OK;
}

jvmtiError JNICALL t8MockGetAllThreads(jvmtiEnv *, jint *count, jthread **threads) {
    *count = 0;
    *threads = nullptr;
    return JVMTI_ERROR_NONE;
}

} // namespace

#ifdef DEBUG
// A failed BFS-worker join must stop Profiler::stop() before any teardown the worker can still
// reach: the call returns an Error, the state stays RUNNING with the tracker active, no engine is
// stopped and the tracker's journal epoch is unchanged. Once the join succeeds, a retried stop()
// runs the whole teardown.
TEST_F(ReferenceChainsBfsTest, ProfilerStopFailedJoinSkipsTeardownAndRetrySucceeds) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    T8ProfilerStateGuard restore;
    Profiler *profiler = Profiler::instance();
    T8CountingEngine cpu_engine;
    T8CountingEngine wall_engine;
    JNIInvokeInterface_ invoke_tbl{};
    invoke_tbl.GetEnv = &t8MockGetEnv;
    JavaVM_ mock_vm{};
    mock_vm.functions = &invoke_tbl;
    // stop()'s teardown tail talks to the JVM through these.
    jvmti_tbl.GetAllThreads = &t8MockGetAllThreads;
    VMTestAccessor::setVm(&mock_vm);
    ProfilerTestAccessor::setEngines(profiler, &cpu_engine, &wall_engine);
    ProfilerTestAccessor::setEventMask(profiler, EM_CPU | EM_WALL);
    ProfilerTestAccessor::setThreadEventsState(profiler, JVMTI_DISABLE);
    ProfilerTestAccessor::setReferenceChainsActive(profiler, true);
    ProfilerTestAccessor::setState(profiler, RUNNING);

    // A started-but-unjoined worker whose join the stub refuses.
    T8Acc::setThreadUnjoinedForTest();
    T8Acc::setJoinResultForTest(EBUSY);
    const u64 epoch_before = T8Acc::journalEpochForTest();

    Error failed = profiler->stop();
    EXPECT_TRUE(failed) << "a failed join must make stop() report an error";
    EXPECT_EQ(1, T8Acc::joinCallCountForTest());
    EXPECT_FALSE(T8Acc::threadJoinedForTest());
    EXPECT_EQ(RUNNING, ProfilerTestAccessor::state(profiler));
    EXPECT_TRUE(ProfilerTestAccessor::referenceChainsActive(profiler));
    EXPECT_EQ(0, cpu_engine.stops);
    EXPECT_EQ(0, wall_engine.stops);
    EXPECT_EQ(epoch_before, T8Acc::journalEpochForTest()) << "tracker teardown must not have run";
    EXPECT_TRUE(tracker->enabled());

    // Retry with a successful join: the join is attempted again and the teardown completes.
    T8Acc::setJoinResultForTest(0);
    Error retried = profiler->stop();
    EXPECT_FALSE(retried) << (retried.message() != nullptr ? retried.message() : "");
    EXPECT_EQ(1, T8Acc::joinCallCountForTest());
    EXPECT_TRUE(T8Acc::threadJoinedForTest());
    EXPECT_EQ(IDLE, ProfilerTestAccessor::state(profiler));
    EXPECT_FALSE(ProfilerTestAccessor::referenceChainsActive(profiler));
    EXPECT_EQ(1, cpu_engine.stops);
    EXPECT_EQ(1, wall_engine.stops);
    EXPECT_GT(T8Acc::journalEpochForTest(), epoch_before)
        << "the tracker's recording-boundary reset ran after the join";

    T8Acc::clearJoinResultForTest();
}
#endif
