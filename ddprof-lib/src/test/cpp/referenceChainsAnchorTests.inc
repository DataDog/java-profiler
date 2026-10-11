/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

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

    // Static Map -> table -> Entry -> chunk: the collection-shaped static holder's internals,
    // deeper than one hop.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, tableNode, -1},
        {JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, tableNode, entryNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, entryNode, leakChunk, chunk},
    };

    // Seed the frontier exactly as the static sweep admits a static field's value: root-attached,
    // STATIC_FIELD root kind, FRONTIER state.
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
    // Both DURABLE root kinds are selected (STATIC_FIELD 101, JNI_GLOBAL 104, in cursor/tag order);
    // the transient-root decoy and the child are not.
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(101, selected[0]);
    EXPECT_EQ(104, selected[1]);
    std::vector<jlong> walk_selected = {selected[0]};

    // The static anchor's whole internal structure is admitted by one bounded walk, intercepting
    // the leak tag at depth 3 below the holder.
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

// Round-14 tiered selection: a container-shaped anchor (its own class implements Collection/Map -
// the LEAK_BUFFER wrapper shape) admitted at a LATE index position must leap the queue of ~28k
// other-tier anchors (the round-13 hotdog measurement: admission-order selection put the leak
// holder at position ~12-21k against ~4k walk coverage per search - deterministically unreachable).
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
        // Containers only at late positions 24000..24003 - buried behind 24k other-tier anchors
        // under any admission-order cursor.
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
    // The four container anchors are selected in this FIRST call despite positions 24000+ (tags
    // 24100-24103).
    for (jlong t : {24100, 24101, 24102, 24103}) {
        EXPECT_NE(std::find(selected.begin(), selected.end(), t), selected.end())
            << "container anchor " << t
            << " did not leap the other-tier queue";
    }
    // Sanity: an early other-tier anchor also made the cut (cursor-fair fill from position 0).
    EXPECT_NE(std::find(selected.begin(), selected.end(), (jlong)100),
              selected.end());

    tracker->stop();
}

// Round-15 fresh-admission priority: the hotdog wrapper is admitted LATE in a search (its holder
// class sits at sweep index 24627 of 33270, so admission lands at the anchor-index TAIL) - behind
// the whole fair container backlog measured at 1633 entries against 44-75-pass search lifetimes
// (the fair container cursor would reach it at pass ~102+, after the search is dead).
TEST_F(ReferenceChainsBfsTest, FreshContainerWalkedBeforeFairBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // A fair container backlog, "admitted long ago": 200 containers at positions 0..199.
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
    // First collector call: all 200 anchors are fresh (nothing has had a first look yet), the lane
    // keeps 16 and the rest spend their first look (they fall back to the fair container tier).
    std::vector<jlong> first =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, first.size()) << "200 eligible containers at a 16 budget";

    // The late admission wave: a wrapper-class container at the index tail, a fresh classified
    // NON-container (a fresh String static - it must NOT ride the fresh lane), and a fresh
    // unclassified anchor (a genuinely new class - it must ride the lane, so the classification lag
    // cannot lose the wrapper's fresh window).
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
    // The fair container lap still gets the leftover budget. Call 1's fresh picks (500-515) spent
    // the whole budget, so the fair cursor never advanced - call 2's fair picks start at tag 500
    // again (a benign one-call overlap: walks are idempotent, and it only happens when fresh and
    // fair coincide at a lap boundary).
    EXPECT_NE(std::find(second.begin(), second.end(), (jlong)500),
              second.end())
        << "the fair container lap must still advance with the leftover "
           "budget";
    EXPECT_EQ(14, (int)std::count_if(second.begin(), second.end(),
                                     [](jlong t) {
                                       return t >= 500 && t < 500 + kBacklog;
                                     }))
        << "16 budget - 2 fresh picks = 14 fair-container picks";

    // And the dropped fresh entries from call 1 (516-699 spent their first look) are still covered
    // by the fair tier: a third call with no new admits must keep advancing the fair container
    // cursor from wherever call 2 left it, not re-drain anything.
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

// Round-14 tier fairness: the other tier (everything not leak-tagged, not container-shaped) still
// reaches full coverage across wraps - a 40-anchor tier at a 16 budget covers all 40 in exactly 3
// calls with no duplicates within a call.
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

// Round-13/14 restart hygiene: discovered-instance tags are FRONTIER tags; restartSearch() resets
// the frontier table and _next_tag=1, so any surviving discovered slot either fails
// reconstructChain (observed on-pod: 'buildChainEvent failed ...
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

    // An anchor index entry (tag + parallel class tag) to confirm the index reset covers the
    // parallel structures too.
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

// Round-19 (pod 289f8 — three JVMs of "canary search, 0/1 candidates found" while leak-tagged
// instances WERE intercepted and chains re-emitted): the marker->leak-tag design migration never
// updated the found criterion.
TEST_F(ReferenceChainsBfsTest, LeakTagChainMarksCanaryFound) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Slot 0: candidate klass 7 whose discovered instance carries a leak tag (entry.leak_tag set —
    // the shape a walk + tagLeakInstances correlation produces; target_tag becomes the leak tag).
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, 7);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(1, 9);
    // depth=1 at a durable STATIC_FIELD root (root_kind 8) so the retention filter
    // (suppressChainEvent: depth==0, or depth==1 at a transient root) keeps both chains.
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

    // Slot 0 found via its leak-tag chain (bit 0 set, link recorded); slot 1's noise chain did not
    // mark anything found.
    EXPECT_EQ(1ULL, ReferenceChainsTestAccessor::candidateFoundBitsForTest());
    EXPECT_EQ(4242, ReferenceChainsTestAccessor::candidateFrontierTagForTest(0));
    EXPECT_EQ(0, ReferenceChainsTestAccessor::candidateFrontierTagForTest(1))
        << "noise-target chain must not mark the canary found";

    tracker->stop();
}

// B' push site 1 - DEMOTION TIME (find-anchor-holder-eviction / _static_anchor_fifo): when
// improveChain() replaces a root-attached durable (STATIC_FIELD/ JNI_GLOBAL) entry with a deeper
// chain-attached path, the entry is leaving the anchor tier's eligible population at exactly that
// moment - the push must fire right there.
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

    // Seed exactly the pre-demotion shape: holder root-attached STATIC (anchor-eligible), parent a
    // root-attached frontier object whose expansion delivers the deeper chain edge.
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
    // The chain edge was delivered: the holder's entry is now chain-attached (improveChain replaced
    // the depth-0 root-attached admission), and the demotion pushed its tag into the at-risk FIFO.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(105));

    // Re-walking the same edge must NOT push twice: improveChain refuses (new depth 1 is not >
    // current 1), and the set dedupes regardless.
    int edges2 = 0;
    ReferenceChainsTestAccessor::pushPendingExpandForTest(104);
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni,
                                                        &edges2);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    tracker->stop();
}

// B' push site 2 - SWEEP TIME: the static sweep's class->field edge onto an already-admitted
// CHAIN-ATTACHED entry (the admission-order eviction shape: born as a non-root child, never
// root-attached at all) must feed the FIFO.
TEST_F(ReferenceChainsBfsTest, SweepPushFiresOnStaticEdgeOntoChainAttachedHolder) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=100"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int holderNode = addNode();
    // A child reachable ONLY from the holder: nothing in the scripted graph walks holderNode except
    // the FIFO-drained anchor walk, so the child's admission after runPass is the end-to-end
    // evidence that the sweep pushed the holder, the rotation phase drained it, and
    // walkStaticFieldAnchors walked it.
    int holderChildNode = addNode();
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/ChainBornHolder;");

    script = {
        // Only the sweep's static edge onto the holder, plus the holder's own child edge for the
        // anchor walk to admit: nothing else reaches holderNode or holderChildNode, so the only
        // possible push is the static-edge-onto-chain-attached site.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, holderNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, holderChildNode, -1},
    };

    // Seed the born-chain-attached shape the eviction leaves: holder already a non-root child
    // (parent 104, depth 1).
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    // The child is untagged (0): the anchor walk's admission assigns it a fresh frontier tag,
    // observable via node_tags after the pass.
    ASSERT_EQ(0, node_tags[holderChildNode]);
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));

    // The rotation phase of the same pass drained the pushed tag into the anchor walk, and the walk
    // admitted the holder's child - the push itself left no residue in the FIFO (drained empty) and
    // never re-attributed the holder's entry (re-rooting is the documented refusal that motivated
    // the FIFO in the first place).
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    jlong childTag = tags_ever_assigned[holderChildNode];
    ASSERT_GT(childTag, 0) << "the FIFO-drained anchor walk never admitted "
                             "the holder's child";
    FrontierEntry childEntry{};
    ASSERT_TRUE(frontier->lookup(childTag, &childEntry));
    EXPECT_EQ(105, childEntry.parent_tag);
    EXPECT_EQ(2u, childEntry.depth);
    // The holder's entry is untouched by the push - the B' feed records the at-risk shape, it never
    // re-attributes the entry.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);

    tracker->stop();
}

// B' mechanics: a chain-attached holder drained from the at-risk FIFO is descend-walked and
// intercepts a leak chunk 3 hops below it - the repair for the population the root-attached
// collector demonstrably cannot select (the negative control below).
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

    // Chain: parent -> holder -> table -> entry -> leak chunk.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, tableNode, -1},
        {JVMTI_HEAP_REFERENCE_ARRAY_ELEMENT, tableNode, entryNode, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, entryNode, leakChunk, chunk},
    };

    // Seed the holder exactly as the eviction leaves it: chain-attached (parent_tag = 104, depth 1,
    // no root_kind).
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    // root_kind = 0: the entry is chain-attached, and a non-root entry's edge kind is not recorded
    // (FrontierEntry::root_kind's own comment).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 104, 1, FrontierEntryState::FRONTIER, 0));
    // The chain's root: TRANSIENT (stack local), so the collector's durable root-kind filter skips
    // it too - the whole table is un-selectable.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 104, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // Negative control: the root-attached collector selects NOTHING from a table holding only a
    // chain-attached holder and a transient root - the pre-B' behavior that stranded the
    // dual-reachable population.
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(4);
    ASSERT_TRUE(selected.empty());

    // B': push + drain + walk reaches what the collector cannot.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(105, 28366);
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> drained;
    // 16 = ReferenceChainTracker::STATIC_ANCHOR_FIFO_DRAIN (private), the same per-pass drain cap
    // runPassManualWalk() uses.
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

// B' requeue mechanics: a truncated anchor walk reports exactly the RESOLVED-but-unwalked tags, and
// requeueStaticAnchorFifoFront() restores them to the FIFO front in order with a consistent
// membership set - so an at-risk holder that lost its budget turn keeps it for the next pass
// instead of waiting for the next sweep lap.
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

    // Holder A's subtree is deep enough that a budget of 2 truncates the walk after A (two edges
    // admitted, budget exhausted on the descend); holder B then must come back unwalked.
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

    // Requeue exactly what the caller-side filter in runPassManualWalk() would requeue (here:
    // everything unwalked, both FIFO-sourced), keeping the drained entries' klass so the per-class
    // occupancy is restored.
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

// a this-field self-edge is REAL in the heap - every java.util.Collections$Synchronized* holder
// carries mutex == this - so walking such a holder's own subtree (rotation anchor walk or BFS
// descent) re-reports the holder as its own child through that field.
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

    // The holder's own self-edge: referrer == referee == holder (the mutex == this field), exactly
    // as its rotation walk re-reports it.
    script = {
        {JVMTI_HEAP_REFERENCE_FIELD, holderNode, holderNode, holderClsIdx},
    };

    // Seed the pre-demotion shape: holder root-attached STATIC_FIELD (anchor-eligible), admitted at
    // depth 0.
    FrontierTable *frontier = tracker->frontierTable();
    node_tags[holderNode] = 105;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 105, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::pushPendingExpandForTest(105);

    // A delivered self-edge trips BOTH sibling guards: improveChain refuses, and the
    // already-admitted block's else-if then offers the same self-parent to reparentToDurableRoot,
    // which refuses too.
    int edges = 0;
    ReferenceChainsTestAccessor::expandFrontierForTest(&mock_jvmti, &mock_jni,
                                                        &edges);

    // The self-edge was delivered and refused: the entry keeps its root-attached shape (the
    // collector's parent_tag == 0 eligibility) and no demotion push fired.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(0, entry.parent_tag);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, entry.root_kind);
    EXPECT_EQ(0u, entry.depth);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    // The sibling guards and the direct table calls agree: a self-parent is refused by both
    // improvement paths, unconditionally.
    EXPECT_FALSE(frontier->improveChain(105, 105, 0, 5, 0, -1, 0, 0));
    EXPECT_FALSE(frontier->reparentToDurableRoot(105, 105, 0, -1, 0));

    tracker->stop();
}

// the B' at-risk FIFO sat cap-pinned at 1024 because three classes flooded it (klass 1: 1396
// pushes, klass 215: 1063, klass 1733: 988+), so the LEAK_BUFFER wrapper's pushes (klass 28366)
// were dropped at the cap check and the lane designed to repair exactly its demotion never carried
// it.
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
    // The flood's first `quota` tags hold their slots and the excess is dropped at the quota check
    // - absent from the FIFO, not queued.
    EXPECT_TRUE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(
        1000 + (int)quota - 1));
    EXPECT_FALSE(ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(
        1000 + (int)quota));

    // The wrapper's push (a different class) lands despite the flood - exactly the push the pod
    // dropped.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(2000, 28366);
    EXPECT_EQ(quota + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(2000));

    // Tag dedupe is unchanged: the same tag never enters twice.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(2000, 28366);
    EXPECT_EQ(quota + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());

    // Full drain: order preserved (flood first, newcomer last), occupancy erased with the entries -
    // the next flood can land again (it never owns MORE than its quota, but it is not permanently
    // locked out either).
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

    // Partial drain at the real per-pass rate (16/pass): the flood's occupancy is 64 - 16 = 48
    // after the drain, so its next push lands (refilling its share as it drains - the flood
    // self-throttles, it never starves the lane).
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> partial;
    ASSERT_EQ(16, ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                      16, partial));
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(3000, 1733);
    EXPECT_EQ(quota - 16 + 1,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(3000));

    // Requeue restores occupancy exactly: the requeued entries occupy their slots again and drain
    // in FIFO order.
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

    // Saturated-but-diverse: 16 distinct classes at exactly their quota fill the 1024 cap, and the
    // newcomer is dropped at the CAP (legitimate saturation - no eviction), not because of any
    // flood.
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
    // The 16 saturated classes sit exactly at their per-class quota (no quota drop is even possible
    // at exactly `quota` pushes), so the newcomer's absence below is the CAP's doing, not the
    // quota's.
    ReferenceChainsTestAccessor::pushStaticAnchorFifoForTest(20000, 28366);
    EXPECT_EQ(1024u,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_FALSE(
        ReferenceChainsTestAccessor::staticAnchorFifoContainsForTest(20000));

    // Leave the FIFO drained: this test is the one that saturates it, and the reset() seam above
    // now clears it for the next test regardless - but a drained ending also keeps this test
    // order-independent even if that seam ever regresses again.
    std::vector<ReferenceChainsTestAccessor::AtRiskAnchor> final_drain;
    ASSERT_EQ(1024,
              ReferenceChainsTestAccessor::drainStaticAnchorFifoForTest(
                  1024, final_drain));

    tracker->stop();
}

// Retention-edge labels (fillHopEdgeLabels()/hopLabelClassFor()): the emitted chain's per-hop
// labels must decode the JVMTI-SPECIFICATION field ordinal captured at admission - the interface
// offset, the superclass-chain order, the interface-referrer branch - and degrade to the edge KIND
// on any undecodable hop, never a fabricated name (the fail-safe contract: a wrong numbering on an
// unverified JVM degrades, it does not lie).
