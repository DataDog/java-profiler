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

// Candidate-scoped reach, prong 2 (collectStaticFieldAnchorsForRotation()/
// walkStaticFieldAnchors()): the collector selects exactly the root-attached static-holder entries
// with a wrapping cursor, and the walk reaches a leak held 3-4 hops inside a static collection in
// one bounded call - the shape the one-hop Tier-2 rotation demonstrably cannot reach from an
// un-expanded FRONTIER holder on a rising heap (pod rounds 5-6).
