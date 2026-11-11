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

// Tiered selection: a container-shaped anchor (its own class implements Collection/Map) admitted
// at a LATE index position must leap the queue of ~28k other-tier anchors - admission-order
// selection put the leak holder at position ~12-21k against ~4k walk coverage per search.
TEST_F(ReferenceChainsBfsTest, ContainerAnchorLeapsQueueAcrossLargeIndex) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Large-but-capped index (the durable share caps at 8192): containers only at positions
    // 5000..5003 - outside the fresh queue's last-1024-admissions window (tags 6076..7099) and
    // buried behind ~6k other-tier anchors under any admission-order cursor.
    constexpr int kAnchorCount = 7000;
    for (int i = 0; i < kAnchorCount; i++) {
        jlong tag = 100 + i;
        jlong class_tag = 500000 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD));
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            tag, class_tag, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
        bool container = (i >= 5000 && i <= 5003);
        ReferenceChainsTestAccessor::primeClassShapeForTest(class_tag,
                                                             container);
    }
    // One leak-tagged anchor at the very tail - tier 0, must lead.
    jlong leak_anchor = 100 + kAnchorCount;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, leak_anchor, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    frontier->setLeakTag(leak_anchor, 777, /*leak_tag_incarnation=*/0);
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        leak_anchor, 599999, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    ReferenceChainsTestAccessor::primeClassShapeForTest(
        599999, false /* its tier comes from leak_tag, not shape */);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(
            16);
    ASSERT_EQ(16u, selected.size())
        << "7000+1 eligible anchors at a 16 budget must fill the selection";
    EXPECT_EQ(leak_anchor, selected[0])
        << "the leak-tagged anchor (tier 0) must lead the walk order";
    // The four container anchors are selected in this FIRST call despite positions 5000+ (tags
    // 5100-5103) - outside the fresh queue's window, so only the container tier can pick them.
    for (jlong t : {5100, 5101, 5102, 5103}) {
        EXPECT_NE(std::find(selected.begin(), selected.end(), t), selected.end())
            << "container anchor " << t
            << " did not leap the other-tier queue";
    }
    // Sanity: an early other-tier anchor also made the cut (cursor-fair fill from position 0).
    EXPECT_NE(std::find(selected.begin(), selected.end(), (jlong)100),
              selected.end());

    tracker->stop();
}

// Fresh-admission priority: a container admitted LATE in a search lands at the anchor-index TAIL,
// behind the whole fair container backlog (measured at 1633 entries against 44-75-pass search
// lifetimes - the fair cursor would reach it at pass ~102+, after the search is dead).
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

// Tier fairness: the other tier (everything not leak-tagged, not container-shaped) still
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

// Restart hygiene: discovered-instance tags are FRONTIER tags; restartSearch() resets the frontier
// table and _next_tag=1, so a surviving discovered slot would fail reconstructChain() or resolve
// to whatever new entry reuses its tag.
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

// A chain whose target carries a leak tag must mark its canary candidate found - otherwise the
// search reports "0/1 candidates found" while leak-tagged instances ARE intercepted and chains
// re-emitted.
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
    frontier->setLeakTag(4242, 1073742079,
                         LivenessTracker::instance()->leakTagIncarnation(1073742079));
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

// At-risk FIFO (_static_anchor_fifo) push site 1 - DEMOTION TIME: when
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

// At-risk FIFO push site 2 - SWEEP TIME: the static sweep's class->field edge onto an already-admitted
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

    // The same pass's rotation phase drained the pushed tag into the anchor walk, which admitted
    // the holder's child; the FIFO is left empty.
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    jlong childTag = tags_ever_assigned[holderChildNode];
    ASSERT_GT(childTag, 0) << "the FIFO-drained anchor walk never admitted "
                             "the holder's child";
    FrontierEntry childEntry{};
    ASSERT_TRUE(frontier->lookup(childTag, &childEntry));
    EXPECT_EQ(105, childEntry.parent_tag);
    EXPECT_EQ(2u, childEntry.depth);
    // The push records the at-risk shape; it never re-attributes the holder's entry.
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(105, &entry));
    EXPECT_EQ(104, entry.parent_tag);
    EXPECT_EQ(1u, entry.depth);

    tracker->stop();
}

// At-risk FIFO mechanics: a chain-attached holder drained from the at-risk FIFO is descend-walked and
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
    // chain-attached holder and a transient root.
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(4);
    ASSERT_TRUE(selected.empty());

    // Push + drain + walk reaches what the collector cannot.
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

// At-risk FIFO requeue mechanics: a truncated anchor walk reports exactly the RESOLVED-but-unwalked tags, and
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

// A this-field self-edge is REAL in the heap - every java.util.Collections$Synchronized* holder
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

// Per-class quota: without it the at-risk FIFO sat cap-pinned at 1024 because three classes
// flooded it, so a leak holder's pushes were dropped at the cap check and the lane never carried
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

    // A different class's push lands despite the flood.
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

    // Leave the saturated FIFO drained so later tests do not depend on the reset() seam alone.
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

// Local-root holders enter the anchor index only once confirmed as containers: a classified
// non-container is ignored outright, and an unclassified holder waits in the pending buffer and is
// dropped by the resolve step if its class is still unknown or turns out to be a non-container.
TEST_F(ReferenceChainsBfsTest, LocalRootAnchorIndexHoldsOnlyConfirmedContainers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const jlong kNonContainer = -201, kLater = -202, kNever = -203, kContainer = -204;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kNonContainer, false);
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);

    // Classified non-container: neither indexed nor parked.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(301, kNonContainer);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    // Classified container: indexed directly and counted against the local cap.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(302, kContainer);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::localAnchorCountForTest());

    // Unclassified holders are parked (deduplicated), not indexed.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(303, kLater);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(303, kLater);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(304, kNever);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    // kLater classifies as a non-container, kNever stays unknown: both are dropped, and the
    // pending buffer is emptied every resolve.
    ReferenceChainsTestAccessor::primeClassShapeForTest(kLater, false);
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    tracker->stop();
}

// The local share of the anchor index is capped, and the pending buffer is capped too, so the
// per-pass anchor scan cannot grow with the number of application locals. At the cap, the resolve
// step compacts away local entries whose frontier entry is gone before admitting new ones.
TEST_F(ReferenceChainsBfsTest, LocalRootAnchorIndexIsCappedAndCompactsDeadEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kLocalAnchorIndexCap;
    const size_t pending_cap = ReferenceChainsTestAccessor::kPendingLocalAnchorCap;
    const jlong kContainer = -301;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);

    // A durable anchor is outside the local share and must survive compaction.
    const jlong durable = 50;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, durable, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        durable, -302, JVMTI_HEAP_REFERENCE_STATIC_FIELD);

    // Fill the local share with holders whose frontier entries are then released (dead objects:
    // the GC cleanup marks them ABANDONED).
    const jlong dead_base = 100;
    for (size_t i = 0; i < cap; i++) {
        jlong tag = dead_base + (jlong)i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(tag, kContainer);
        frontier->clear(tag);
    }
    ASSERT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    ASSERT_EQ(cap + 1, ReferenceChainsTestAccessor::anchorIndexSizeForTest());

    // Containers met at the cap are parked, and the pending buffer stops at its own cap.
    // Above every inserted tag, so un-inserted parked tags have no frontier entry at all.
    const jlong live_base = dead_base + (jlong)cap + 1000;
    for (size_t i = 0; i < pending_cap + 10; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(live_base + (jlong)i,
                                                                kContainer);
    }
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    // Only one parked holder is live; the resolve step compacts the dead local entries and
    // admits it. Dead parked holders are indexed too (liveness is checked at selection), but
    // all of them fit once the dead share is gone.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, live_base, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(pending_cap + 1, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    // A productive compaction leaves the compaction backoff disarmed.
    EXPECT_EQ(0, ReferenceChainsTestAccessor::localCompactBackoffForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_LE(ReferenceChainsTestAccessor::freshAnchorQueueSizeForTest(),
              ReferenceChainsTestAccessor::anchorIndexSizeForTest());

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaticFieldAnchorsForRotationForTest(4);
    EXPECT_NE(std::find(selected.begin(), selected.end(), durable), selected.end())
        << "durable anchor lost by local-share compaction";
    EXPECT_NE(std::find(selected.begin(), selected.end(), live_base), selected.end())
        << "live local container not admitted after compaction";

    tracker->stop();
}

// When every local entry is live the cap holds: no compaction can free a slot, new holders are
// not indexed, and the pending buffer is still emptied.
TEST_F(ReferenceChainsBfsTest, LocalRootAnchorCapHoldsWhenAllEntriesLive) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kLocalAnchorIndexCap;
    const jlong kContainer = -401;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);
    for (size_t i = 0; i < cap; i++) {
        jlong tag = 1000 + (jlong)i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(tag, kContainer);
    }
    const jlong extra = 1000 + (jlong)cap;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, extra, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(extra, kContainer);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    tracker->stop();
}

// A local holder later attached by a durable root moves to the uncapped durable share, freeing its
// local-cap slot without duplicating the index entry.
TEST_F(ReferenceChainsBfsTest, DurableRootUpgradeReleasesLocalAnchorSlot) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const jlong kContainer = -501;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(777, kContainer);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::localAnchorCountForTest());
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        777, kContainer, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::anchorIndexSizeForTest());

    // restartSearch() resets the local share and the pending buffer with the rest of the index.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(778, -502);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    ReferenceChainsTestAccessor::restartSearchForTest();
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexIsEmptyForTest());

    tracker->stop();
}

// The durable share of the anchor index is capped: the admission that pushes it past
// DURABLE_ANCHOR_INDEX_CAP evicts the oldest durable entries down to cap - DURABLE_ANCHOR_EVICT_BATCH,
// dropping them from the index, the dedup set and the fresh queue, and keeping the parallel
// class-tag vector length-consistent. Dead evicted anchors are never re-reported; live ones are
// (covered by EvictedDurableAnchorIsReadmittedByRootEnumeration below).
TEST_F(ReferenceChainsBfsTest, DurableAnchorIndexIsCappedAndEvictsOldest) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const size_t batch = ReferenceChainsTestAccessor::kDurableAnchorEvictBatch;
    const jlong first_tag = 1001;
    // The (cap+1)-th admission crosses the cap and evicts overflow + batch oldest entries.
    for (size_t i = 0; i <= cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            first_tag + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    EXPECT_EQ(cap - batch, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(cap - batch,
              ReferenceChainsTestAccessor::anchorOwnClassTagsSizeForTest());
    EXPECT_EQ(cap - batch,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());
    for (size_t i = 0; i < batch + 1; i++) {
        EXPECT_FALSE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(
            first_tag + (jlong)i))
            << "oldest entry " << i << " should be evicted";
    }
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(
        first_tag + (jlong)(batch + 1)));
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(
        first_tag + (jlong)cap));
    // The fresh queue drops every evicted tag and keeps recently admitted survivors.
    EXPECT_FALSE(ReferenceChainsTestAccessor::freshAnchorQueueContainsForTest(
        first_tag));
    EXPECT_TRUE(ReferenceChainsTestAccessor::freshAnchorQueueContainsForTest(
        first_tag + (jlong)cap));
    EXPECT_LE(ReferenceChainsTestAccessor::freshAnchorQueueSizeForTest(), 1024u);

    tracker->stop();
}

// FIFO eviction walks index positions but never takes a local-share slot: the local cap and its
// compaction are owned by noteLocalRootHolder()/compactLocalAnchors(), so a local holder sitting at
// the oldest positions survives a durable-share eviction untouched.
TEST_F(ReferenceChainsBfsTest, DurableAnchorEvictionSparesLocalShare) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const jlong kContainer = -501;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);
    const size_t kLocals = 4;
    // Admitted first, so they occupy the oldest index positions.
    for (size_t i = 0; i < kLocals; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(500 + (jlong)i,
                                                                kContainer);
    }
    ASSERT_EQ(kLocals,
              ReferenceChainsTestAccessor::localAnchorCountForTest());
    const jlong first_durable = 2001;
    for (size_t i = 0; i <= cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            first_durable + (jlong)i, -900,
            JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    }
    EXPECT_EQ(kLocals,
              ReferenceChainsTestAccessor::localAnchorCountForTest());
    for (size_t i = 0; i < kLocals; i++) {
        EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(
            500 + (jlong)i))
            << "local holder " << i << " must survive durable eviction";
    }
    // The durable share alone sits at cap - batch after the eviction.
    EXPECT_EQ(cap - ReferenceChainsTestAccessor::kDurableAnchorEvictBatch,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());

    tracker->stop();
}

// An evicted anchor that is still root-attached is re-reported by the next root enumeration and
// re-admitted (fresh lane); the readmission lands at the back of the index.
TEST_F(ReferenceChainsBfsTest, EvictedDurableAnchorIsReadmittedByRootEnumeration) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const size_t batch = ReferenceChainsTestAccessor::kDurableAnchorEvictBatch;
    const jlong first_tag = 3001;
    for (size_t i = 0; i <= cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            first_tag + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    const jlong evicted = first_tag; // oldest position, evicted by the crossing admission
    ASSERT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(evicted));
    const size_t size_before = ReferenceChainsTestAccessor::anchorIndexSizeForTest();
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        evicted, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(evicted));
    EXPECT_EQ(size_before + 1,
              ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(evicted,
              ReferenceChainsTestAccessor::anchorIndexTagForTest(
                  size_before)); // readmitted at the back

    tracker->stop();
}

// A local-to-durable upgrade grows the durable share without an index push (the dedup in
// indexAnchorForRotation() returns early), so only addToStaticAnchorIndex()'s own eviction call
// can reclaim the share when the upgrade itself crosses the cap.
TEST_F(ReferenceChainsBfsTest, DurableUpgradeAtCapTriggersEviction) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const size_t batch = ReferenceChainsTestAccessor::kDurableAnchorEvictBatch;
    const jlong first_tag = 4001;
    for (size_t i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            first_tag + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_EQ(cap,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());
    // Admit a local holder (newest index position), then upgrade it: the upgrade alone pushes the
    // durable share to cap + 1.
    const jlong kContainer = -501;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);
    const jlong upgraded = first_tag + (jlong)cap;
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(upgraded, kContainer);
    ASSERT_EQ(1u,
              ReferenceChainsTestAccessor::localAnchorCountForTest());
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        upgraded, kContainer, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    EXPECT_EQ(0u,
              ReferenceChainsTestAccessor::localAnchorCountForTest());
    // The upgrade's eviction reclaimed the share to cap - batch, and the upgraded tag - the
    // newest entry, never among the FIFO-evicted oldest - is still indexed.
    EXPECT_EQ(cap - batch,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(upgraded));

    tracker->stop();
}

// A live evicted anchor has no fresh-admission path (its frontier entry is already ADMITTED) and
// no upgrade path (an unchanged durable root kind never upgrades), so the traversal callbacks'
// re-enlistment is its only route back into the rotation index. Non-durable root kinds and
// non-root-attached entries are filtered.
TEST_F(ReferenceChainsBfsTest, EvictedDurableAnchorIsReenlistedByTraversalReport) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const jlong kClass = -601;
    const jlong target = 7001;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, target, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        target, kClass, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    // Cross the cap: `target` sits at the oldest position and is evicted.
    for (size_t i = 0; i <= cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            8000 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(target));

    // The traversal callbacks' re-enlistment on the next report of the holder's durable edge.
    ReferenceChainsTestAccessor::reenlistEvictedDurableAnchorForTest(target,
                                                                     kClass);
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(target));
    EXPECT_TRUE(ReferenceChainsTestAccessor::freshAnchorQueueContainsForTest(
        target));

    // Negative controls: a non-root-attached entry and a transient root kind are not re-enlisted.
    const jlong child = 7100, transient = 7101;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, child, 42, 1, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, transient, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ReferenceChainsTestAccessor::reenlistEvictedDurableAnchorForTest(child,
                                                                     kClass);
    ReferenceChainsTestAccessor::reenlistEvictedDurableAnchorForTest(transient,
                                                                     kClass);
    EXPECT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(child));
    EXPECT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(transient));

    tracker->stop();
}

// Eviction requests a full static sweep lap: static-only holders are invisible to root
// enumeration, and the sweep is otherwise skipped while the loaded-class count is unchanged - an
// evicted static-only anchor would never be re-reported. Every eviction bumps the request
// generation, including during the restart cooldown (a dropped request would leave the holder
// unswept once evictions stop); only the cursor restart is paced. The request survives a
// lap-completion memo overwrite - a lap in flight when the eviction lands does not revisit the
// classes it already passed, so only a later lap starting from class 0 serves the request.
TEST_F(ReferenceChainsBfsTest, EvictionForcesStaticFieldSweepRerun) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    for (size_t i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            9000 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_EQ(cap,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());
    // Simulate a mid-lap state: the sweep memo latched and the cursor part-way into a lap.
    ReferenceChainsTestAccessor::setStaticFieldSweepMemoForTest(12345);
    ReferenceChainsTestAccessor::setStaticFieldSweepCursorForTest(456);
    // The cap-crossing admission evicts - and must record the resweep request and restart the
    // cursor (the cooldown is not armed at this point).
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        9000 + (jlong)cap, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::durableAnchorResweepUnservedForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::staticFieldSweepCursorForTest());
    EXPECT_EQ(8,
              ReferenceChainsTestAccessor::durableSweepReforceBackoffForTest());
    // The lap in flight completing (memo overwritten) must NOT consume the request: this lap's
    // behind-cursor classes were traversed before the eviction.
    ReferenceChainsTestAccessor::setStaticFieldSweepMemoForTest(12345);
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::durableAnchorResweepUnservedForTest());

    // During the restart cooldown an eviction still records the request - only the cursor restart
    // is paced, and the cooldown advances per sweep run, not per eviction. Refill the durable
    // share first: eviction drains it to cap - DURABLE_ANCHOR_EVICT_BATCH, so without the refill
    // the next admission would not cross the cap and this phase would assert on a no-op.
    const u64 gen_after_first =
        ReferenceChainsTestAccessor::durableAnchorResweepGenForTest();
    ASSERT_LT(ReferenceChainsTestAccessor::durableAnchorCountForTest(), cap);
    for (size_t i = 0;
         ReferenceChainsTestAccessor::durableAnchorCountForTest() < cap;
         i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            20000 + (jlong)i, -901, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    ASSERT_EQ(cap,
              ReferenceChainsTestAccessor::durableAnchorCountForTest());
    ReferenceChainsTestAccessor::setDurableSweepReforceBackoffForTest(5);
    ReferenceChainsTestAccessor::setStaticFieldSweepCursorForTest(789);
    // A tag outside the refill range (20000..21023) - a colliding tag would dedup to a no-op
    // instead of crossing the cap.
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        30000, -901, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    EXPECT_GT(ReferenceChainsTestAccessor::durableAnchorResweepGenForTest(),
              gen_after_first);
    EXPECT_TRUE(
        ReferenceChainsTestAccessor::durableAnchorResweepUnservedForTest());
    EXPECT_EQ(789,
              ReferenceChainsTestAccessor::staticFieldSweepCursorForTest());
    EXPECT_EQ(5,
              ReferenceChainsTestAccessor::durableSweepReforceBackoffForTest());

    tracker->stop();
}

// End-to-end wiring: the heap-root callback's re-enlist branch. An evicted JNI_GLOBAL root is
// re-reported every root enumeration; the already-admitted rediscovery takes the upgrade-refused
// path (an unchanged durable root kind never upgrades) and must restore the victim's index entry.
TEST_F(ReferenceChainsBfsTest, HeapRootCallbackReenlistsEvictedDurableAnchor) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const jlong victim = 15001;
    // The eviction removes only the index entry; the victim's frontier entry survives.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, victim, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        victim, -700, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    for (size_t i = 0; i < cap - 1; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            16000 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL);
    }
    const jlong filler = 16000 + (jlong)cap;
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        filler, -900, JVMTI_HEAP_REFERENCE_JNI_GLOBAL); // crosses the cap
    ASSERT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(victim));

    // The next root enumeration re-reports the victim: already admitted, unchanged durable kind,
    // so the upgrade refuses and the re-enlist branch fires.
    ReferenceChainPassContext ctx{};
    ctx.tracker = tracker;
    ctx.frontier = frontier;
    ctx.hop_cap = 64;
    ctx.budget = 1000;
    jlong reported = victim;
    ReferenceChainsTestAccessor::reportHeapRootForTest(
        JVMTI_HEAP_ROOT_JNI_GLOBAL, -700, &reported, &ctx);
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(victim));
    EXPECT_TRUE(ReferenceChainsTestAccessor::freshAnchorQueueContainsForTest(
        victim));

    tracker->stop();
}

// End-to-end wiring: heapReferenceCallback's already-admitted root-edge branch. The static sweep's
// class -> field edge is the only traversal that re-reports a static-only holder, whose re-enlist
// must not depend on the root enumeration (which never reports static-field holders).
TEST_F(ReferenceChainsBfsTest, HeapReferenceCallbackReenlistsEvictedDurableAnchor) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const size_t cap = ReferenceChainsTestAccessor::kDurableAnchorIndexCap;
    const jlong victim = 17001;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, victim, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        victim, -700, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    for (size_t i = 0; i < cap - 1; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            18000 + (jlong)i, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    const jlong filler = 18000 + (jlong)cap;
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        filler, -900, JVMTI_HEAP_REFERENCE_STATIC_FIELD); // crosses the cap
    ASSERT_FALSE(
        ReferenceChainsTestAccessor::anchorIndexContainsForTest(victim));

    // The sweep re-reports the victim's class -> field edge: root-like negative class referrer,
    // unchanged durable kind - upgrade refused, re-enlist fires.
    ReferenceChainPassContext ctx{};
    ctx.tracker = tracker;
    ctx.frontier = frontier;
    ctx.hop_cap = 64;
    ctx.budget = 1000;
    jlong reported = victim;
    ReferenceChainsTestAccessor::reportStaticFieldEdgeForTest(
        -555, &reported, &ctx);
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexContainsForTest(victim));
    EXPECT_TRUE(ReferenceChainsTestAccessor::freshAnchorQueueContainsForTest(
        victim));

    tracker->stop();
}

// When the local share is at the cap and full of live containers, a compaction that removes nothing
// arms a backoff: the next LOCAL_ANCHOR_COMPACT_BACKOFF at-cap resolves skip the locked scan (the
// cap holds, the parked containers are dropped and re-reported). Dead locals are reclaimed by the
// first compaction after the backoff runs out, which disarms it. Under the cap the backoff is
// neither consulted nor changed.
TEST_F(ReferenceChainsBfsTest, LocalRootAnchorCompactBackoffSkipsNoProgressCompactions) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    EXPECT_EQ(0, ReferenceChainsTestAccessor::localCompactBackoffForTest());

    const size_t cap = ReferenceChainsTestAccessor::kLocalAnchorIndexCap;
    const int backoff = ReferenceChainsTestAccessor::kLocalCompactBackoff;
    ASSERT_GT(backoff, 1);
    const jlong kContainer = -451, kLater = -452;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);

    const jlong local_base = 1000;
    for (size_t i = 0; i < cap; i++) {
        jlong tag = local_base + (jlong)i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(tag, kContainer);
    }
    ASSERT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());

    // Parked containers carry no frontier entry: they are only checked for admission.
    jlong next_parked = local_base + (jlong)cap + 10000;

    // No-progress compaction arms the backoff; the cap holds.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(next_parked++, kContainer);
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(backoff, ReferenceChainsTestAccessor::localCompactBackoffForTest());

    // A skipped at-cap attempt decrements once per resolve, however many containers were parked.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(next_parked++, kContainer);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(next_parked++, kContainer);
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(backoff - 1, ReferenceChainsTestAccessor::localCompactBackoffForTest());

    // Under the cap the backoff is untouched: free one local slot via a durable-root upgrade, then
    // admit a holder that becomes a confirmed container while parked.
    ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
        local_base, kContainer, JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    ASSERT_EQ(cap - 1, ReferenceChainsTestAccessor::localAnchorCountForTest());
    const jlong later = next_parked++;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, later, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(later, kLater);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    ReferenceChainsTestAccessor::primeClassShapeForTest(kLater, true);
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
    const size_t index_size = cap + 1; // the upgraded durable entry stays indexed
    EXPECT_EQ(index_size, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(backoff - 1, ReferenceChainsTestAccessor::localCompactBackoffForTest());

    // Kill part of the local share. While the backoff is armed the dead entries keep their slots.
    const size_t dead = 100;
    for (size_t i = 1; i <= dead; i++) {
        frontier->clear(local_base + (jlong)i);
    }
    for (int k = backoff - 1; k > 0; k--) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(next_parked++, kContainer);
        ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
        EXPECT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());
        EXPECT_EQ(index_size, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
        EXPECT_EQ(k - 1, ReferenceChainsTestAccessor::localCompactBackoffForTest());
    }

    // Backoff exhausted: the next at-cap resolve compacts the dead share, disarms the backoff and
    // admits the parked container.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(next_parked++, kContainer);
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(cap - dead + 1, ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ(index_size - dead + 1, ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::localCompactBackoffForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    tracker->stop();
}

// A full pending buffer gives confirmed containers (met at the local cap) priority over entries not
// yet confirmed as containers: the oldest such entry is evicted through a forward-only cursor, dedup
// stays exact, and once only confirmed containers are parked a further container is dropped (to be
// re-reported by the next root enumeration).
TEST_F(ReferenceChainsBfsTest, LocalRootAnchorPendingBufferEvictsForConfirmedContainer) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const size_t cap = ReferenceChainsTestAccessor::kLocalAnchorIndexCap;
    const size_t pending_cap = ReferenceChainsTestAccessor::kPendingLocalAnchorCap;
    ASSERT_GT(pending_cap, 8u);
    const jlong kContainer = -601, kUnknown = -602;
    ReferenceChainsTestAccessor::primeClassShapeForTest(kContainer, true);

    // Fill the local cap so confirmed containers park instead of being indexed directly.
    for (size_t i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(10000 + (jlong)i, kContainer);
    }
    ASSERT_EQ(cap, ReferenceChainsTestAccessor::localAnchorCountForTest());

    // Fill the pending buffer with unclassified holders.
    const jlong unk_base = 20000;
    for (size_t i = 0; i < pending_cap; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(unk_base + (jlong)i, kUnknown);
    }
    ASSERT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    // The first container evicts the oldest unclassified entry, in place.
    const jlong c_base = 30000;
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(c_base, kContainer);
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(c_base));
    EXPECT_EQ(c_base, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(0));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(unk_base));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(unk_base + 1));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    // The second evicts the next-oldest; the parked container below the cursor is kept.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(c_base + 1, kContainer);
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_EQ(c_base, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(0));
    EXPECT_EQ(c_base + 1, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(1));
    EXPECT_FALSE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(unk_base + 1));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    // Dedup: re-reporting a parked container or a parked unclassified holder changes nothing.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(c_base, kContainer);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(unk_base + 5, kUnknown);
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_EQ(c_base, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(0));
    EXPECT_EQ(c_base + 1, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(1));
    EXPECT_EQ(unk_base + 2, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(2));
    EXPECT_TRUE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(unk_base + 2));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    // A new unclassified holder at a full buffer is dropped (no eviction).
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(40000, kUnknown);
    EXPECT_FALSE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(40000));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    // Evict every remaining unclassified entry.
    for (size_t i = 2; i < pending_cap; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(c_base + (jlong)i, kContainer);
    }
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());
    for (size_t i = 0; i < pending_cap; i++) {
        EXPECT_EQ(c_base + (jlong)i, ReferenceChainsTestAccessor::pendingLocalAnchorTagForTest(i));
        EXPECT_FALSE(
            ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(unk_base + (jlong)i));
    }

    // Only confirmed containers are parked: a further container is dropped.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(50000, kContainer);
    EXPECT_FALSE(ReferenceChainsTestAccessor::pendingLocalAnchorContainsForTest(50000));
    EXPECT_EQ(pending_cap, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    // Resolve empties the buffer and rewinds the cursor.
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalEvictCursorForTest());

    tracker->stop();
}

// The per-pass classification request (the pure first step of reconcileAnchorClassShapes()) holds
// exactly ANCHOR_SHAPE_RECONCILE_BUDGET distinct class tags, in pending-buffer order; holders whose
// classes did not make the batch stay unclassified and are dropped by the resolve step.
TEST_F(ReferenceChainsBfsTest, AnchorShapeReconcileBudgetCapsRequestedClasses) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const int budget = ReferenceChainsTestAccessor::kAnchorShapeReconcileBudget;
    const int extra = 10;
    ASSERT_GT(ReferenceChainsTestAccessor::kPendingLocalAnchorCap, (size_t)(budget + extra + 1));
    ASSERT_GT(ReferenceChainsTestAccessor::kLocalAnchorIndexCap, (size_t)(budget + 1));

    // Holder 61000 shares the first holder's class: the request must list it once.
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(60000, -7000);
    ReferenceChainsTestAccessor::noteLocalRootHolderForTest(61000, -7000);
    for (int i = 1; i < budget + extra; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(60000 + i, -(jlong)(7000 + i));
    }
    ASSERT_EQ((size_t)(budget + extra + 1),
              ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());

    std::vector<jlong> req = ReferenceChainsTestAccessor::unclassifiedAnchorClassTagsForTest();
    ASSERT_EQ((size_t)budget, req.size());
    for (int i = 0; i < budget; i++) {
        EXPECT_EQ(-(jlong)(7000 + i), req[i]);
    }

    // Classify the requested batch as containers; the remainder stays unclassified and is dropped.
    for (jlong class_tag : req) {
        ReferenceChainsTestAccessor::primeClassShapeForTest(class_tag, true);
    }
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    EXPECT_EQ((size_t)(budget + 1), ReferenceChainsTestAccessor::localAnchorCountForTest());
    EXPECT_EQ((size_t)(budget + 1), ReferenceChainsTestAccessor::anchorIndexSizeForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::unclassifiedAnchorClassTagsForTest().empty());

    tracker->stop();
}

// Pending holders' classes are requested before indexed anchors' classes (the pending ones are
// dropped if left unclassified; indexed anchors just wait), and the index scan stops once the
// budget is exhausted.
TEST_F(ReferenceChainsBfsTest, AnchorShapeReconcilePrefersPendingHolders) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    const int budget = ReferenceChainsTestAccessor::kAnchorShapeReconcileBudget;
    const int fresh_pending = 4;
    ASSERT_GT(ReferenceChainsTestAccessor::kPendingLocalAnchorCap, (size_t)(budget + fresh_pending));
    ASSERT_GT(ReferenceChainsTestAccessor::kLocalAnchorIndexCap, (size_t)(budget + 1));
    // Class-tag ranges below must stay disjoint.
    ASSERT_LT(budget + 20, 500);

    // Phase 1: durable anchors with unclassified classes, then a full budget of pending classes.
    const int durable_first = 20;
    for (int i = 0; i < durable_first; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            80000 + i, -(jlong)(9000 + i), JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    for (int i = 0; i < budget; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(81000 + i, -(jlong)(9500 + i));
    }
    std::vector<jlong> req = ReferenceChainsTestAccessor::unclassifiedAnchorClassTagsForTest();
    ASSERT_EQ((size_t)budget, req.size());
    for (int i = 0; i < budget; i++) {
        EXPECT_EQ(-(jlong)(9500 + i), req[i]);
    }
    for (int i = 0; i < durable_first; i++) {
        EXPECT_EQ(std::find(req.begin(), req.end(), -(jlong)(9000 + i)), req.end())
            << "durable class requested ahead of pending classes";
    }

    // Phase 2: nothing classified, so the resolve drops every pending holder. A few new pending
    // classes come first, then durable classes fill the rest of the budget in index order.
    ReferenceChainsTestAccessor::resolvePendingLocalAnchorsForTest();
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::pendingLocalAnchorCountForTest());
    for (int i = 0; i < fresh_pending; i++) {
        ReferenceChainsTestAccessor::noteLocalRootHolderForTest(82000 + i, -(jlong)(9800 + i));
    }
    for (int i = durable_first; i < budget + durable_first; i++) {
        ReferenceChainsTestAccessor::addToStaticAnchorIndexForTest(
            80000 + i, -(jlong)(9000 + i), JVMTI_HEAP_REFERENCE_STATIC_FIELD);
    }
    req = ReferenceChainsTestAccessor::unclassifiedAnchorClassTagsForTest();
    ASSERT_EQ((size_t)budget, req.size());
    for (int i = 0; i < fresh_pending; i++) {
        EXPECT_EQ(-(jlong)(9800 + i), req[i]);
    }
    for (int j = 0; j < budget - fresh_pending; j++) {
        EXPECT_EQ(-(jlong)(9000 + j), req[fresh_pending + j]);
    }

    tracker->stop();
}
