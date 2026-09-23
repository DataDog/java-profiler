/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

TEST_F(ReferenceChainsBfsTest, HopEdgeLabelsDecodeSpecFieldOrdinals) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Hierarchy mirroring the spec's own numbering example shape: interface IBase { int p; } 1 own
    // field interface ISub extends IBase { int x; } 1 own field class Base { int base_f; } 1 own
    // field, no super class Holder extends Base implements ISub { int holder_a; Object leakList; }
    // interface ISink { Object CONST_A; Object CONST_B; } Spec ordinal spaces
    // (jvmtiHeapReferenceInfoField): Holder (class branch): base = ISub(1) + IBase(1) = 2
    // (transitive interfaces, each once); then the superclass chain root-first: base_f@2; then own
    // fields in GetClassFields order: holder_a@3, leakList@4.
    void *ibase = (void *)0x5001, *isub = (void *)0x5002, *base = (void *)0x5003,
         *holder = (void *)0x5004, *isink = (void *)0x5005;
    addClass(ibase, "Lcom/rc/labels/IBase;");
    addClass(isub, "Lcom/rc/labels/ISub;");
    addClass(base, "Lcom/rc/labels/Base;");
    addClass(holder, "Lcom/rc/labels/Holder;");
    addClass(isink, "Lcom/rc/labels/ISink;");
    ReferenceChainsTestAccessor::resolveLoadedClasses(&mock_jvmti, &mock_jni);
    // resolveLoadedClasses minted each class's raw (negative) tag via the mock's tag map - read
    // them back for the decoder's tag->class lookup and the entries' referrer_class_tag values.
    auto tagOf = [&](void *k) -> jlong { return tags[k]; };
    field_decode_classes[tagOf(holder)] = holder;
    field_decode_classes[tagOf(isink)] = isink;
    field_decode_classes[tagOf(base)] = base;
    // ibase deliberately NOT registered into field_decode_classes: an unresolvable referrer class
    // below must degrade to a kind label.
    field_decode_hierarchy[ibase] = {true, nullptr, {}, {{(void *)0x6001, "p"}}};
    field_decode_hierarchy[isub] =
            {true, nullptr, {ibase}, {{(void *)0x6002, "x"}}};
    field_decode_hierarchy[base] = {false, nullptr, {}, {{(void *)0x6003, "base_f"}}};
    field_decode_hierarchy[holder] =
            {false, base, {isub},
             {{(void *)0x6004, "holder_a"}, {(void *)0x6005, "leakList"}}};
    field_decode_hierarchy[isink] =
            {true, nullptr, {},
             {{(void *)0x6006, "CONST_A"}, {(void *)0x6007, "CONST_B"}}};

    FrontierTable *frontier = tracker->frontierTable();
    // Chain: [chunk(3)] <- Base.base_f(ordinal 0 over Base's space) <- [value2(2), class Base] <-
    // Holder.leakList(ordinal 4, the static root edge with the declaring class as referrer) <-
    // [static value(1), class Holder] <- [class Holder (the ROOT TYPE - buildChainEvent() appends
    // the root-attached entry's referrer_class_tag for static-field roots)].
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/4, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(holder)));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 1, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(base),
        /*referrer_field_index=*/3, JVMTI_HEAP_REFERENCE_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 2, 2, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/0, JVMTI_HEAP_REFERENCE_FIELD));

    ReferenceChainEvent event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/3, &event));
    ASSERT_EQ(4u, event._hops.size());
    // Leaf first: chunk is retained via Base.base_f (parent entry's class is Base, ordinal 0 in
    // Base's own space), then value2 via Holder's holder_a (ordinal 3 = interface offset 2 + Base's
    // 1 + own position 0), then the static root edge's field name leakList (ordinal 4), then the
    // root-type hop (class Holder) - the root edge itself, kind label only.
    EXPECT_EQ("base_f", event._hops[0].edge_label);
    EXPECT_EQ("holder_a", event._hops[1].edge_label);
    EXPECT_EQ("leakList", event._hops[2].edge_label);
    EXPECT_EQ("static_field", event._hops[3].edge_label);
    int expectedRootType = Profiler::instance()->lookupClass(
        "com/rc/labels/Holder", strlen("com/rc/labels/Holder"));
    ASSERT_NE(-1, expectedRootType);
    EXPECT_EQ((u32)expectedRootType, event._hops[3].klass_id);

    // Interface-referrer branch: ISink's own-field ordinals have NO superclass-chain component
    // (base = superinterfaces' fields only).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(isink),
        /*referrer_field_index=*/1, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(isink)));
    ReferenceChainEvent iface_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/4, &iface_event));
    // Same root-type append as above: the root-side end gains ISink (the declaring class of the
    // static field) plus its kind-only root edge.
    ASSERT_EQ(2u, iface_event._hops.size());
    EXPECT_EQ("CONST_B", iface_event._hops[0].edge_label);
    EXPECT_EQ("static_field", iface_event._hops[1].edge_label);
    int expectedSinkRoot = Profiler::instance()->lookupClass(
        "com/rc/labels/ISink", strlen("com/rc/labels/ISink"));
    ASSERT_NE(-1, expectedSinkRoot);
    EXPECT_EQ((u32)expectedSinkRoot, iface_event._hops[1].klass_id);

    // Fail-safe: a referrer class that cannot be resolved degrades to the edge KIND label, never a
    // fabricated name.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD,
        /*referrer_klass=*/0, /*class_tag=*/tagOf(holder),
        /*referrer_field_index=*/0, /*edge_kind=*/0,
        /*referrer_class_tag=*/tagOf(ibase)));
    ReferenceChainEvent degraded_event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildChainEventForTest(
        &mock_jvmti, &mock_jni, /*target_tag=*/5, &degraded_event));
    // Both hops degrade to kind labels: the holder hop's referrer class (IBase) is deliberately
    // unregistered from the decoder, and the appended root-type hop (IBase itself) carries no field
    // identity.
    ASSERT_EQ(2u, degraded_event._hops.size());
    EXPECT_EQ("static_field", degraded_event._hops[0].edge_label);
    EXPECT_EQ("static_field", degraded_event._hops[1].edge_label);
    int expectedIbaseRoot = Profiler::instance()->lookupClass(
        "com/rc/labels/IBase", strlen("com/rc/labels/IBase"));
    ASSERT_NE(-1, expectedIbaseRoot);
    EXPECT_EQ((u32)expectedIbaseRoot, degraded_event._hops[1].klass_id);

    tracker->stop();
}

// PRIORITY_EXPAND_CAP backpressure: with the fast lane at the cap, the rotation collectors must
// stop pushing.
TEST_F(ReferenceChainsBfsTest, PriorityExpandCapStopsRotationCollectorPushes) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // One eligible stale-EXPANDED entry.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    for (size_t i = 0; i < ReferenceChainsTestAccessor::priorityExpandCap(); i++) {
        ReferenceChainsTestAccessor::pushPriorityExpand((jlong)(100 + i));
    }
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(10);
    EXPECT_TRUE(selected.empty())
        << "collector must stop pushing once _priority_expand hits the cap";

    // With the lane drained (a pass's expand phase consumed it), the collector selects again.
    ReferenceChainsTestAccessor::clearPriorityExpand();
    selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(10);
    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);

    tracker->stop();
}

// The stale-expansion rotation must select leak parents from _leak_parent_fanout ahead of the blind
// table lap: the fanout entries are the EXPANDED parents that actually lead to watched leak-klass
// children, and neither the blind lap (~table_size/budget passes, hundreds live) nor the
// growth-gated leak-accumulation tier reaches them in steady state.
TEST_F(ReferenceChainsBfsTest, StaleRotationPrefersLeakParentsOverBlindLap) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Fanout parent 1 and an unrelated stale-EXPANDED entry 3.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0,
        /*class_tag=*/42));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, 1, 10);

    // Budget 1: the fanout parent wins over the blind-lap entry.
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(1);
    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);

    // Budget covering both: fanout parent first, blind lap fills the rest.
    ReferenceChainsTestAccessor::clearPriorityExpand();
    selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(2);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ((jlong)1, selected[0]);
    EXPECT_EQ((jlong)3, selected[1]);

    tracker->stop();
}

// reparentToDurableRoot: a depth-1 entry first admitted through a transient root (stack/JNI local)
// is re-parented to a durable root-attached parent at equal depth - the case improveChain() cannot
// express (it requires a strictly deeper path), and exactly the hotdog shape where the singleton
// collection is a depth-0 static root and its elements depth 1.
TEST_F(ReferenceChainsBfsTest, ReparentToDurableRootSwapsTransientForDurable) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // tag 1: transient root (old parent). tag 2: target at depth 1 under it.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // tag 5: durable static root (new parent).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    // tag 6: another transient root - must never be swapped TO.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 6, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    EXPECT_TRUE(frontier->reparentToDurableRoot(2, 5, 42));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(2, &entry));
    EXPECT_EQ((jlong)5, entry.parent_tag);
    EXPECT_EQ((u32)42, entry.referrer_klass);

    // Transient new parent: no swap (would trade one noise root for another).
    EXPECT_FALSE(frontier->reparentToDurableRoot(2, 6, 43));
    ASSERT_TRUE(frontier->lookup(2, &entry));
    EXPECT_EQ((jlong)5, entry.parent_tag) << "parent must be unchanged";

    // Depth-2 targets are out of scope (judging root durability there would require walking both
    // chains).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 7, 2, 2, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    EXPECT_FALSE(frontier->reparentToDurableRoot(7, 5, 44));

    tracker->stop();
}

// recordDiscoveredInstance eviction: noise instances fill discovery slots first-come-first-served,
// but a leak-correlated discovery must evict a noise slot when all are full - without eviction, the
// 8 noise instances observed on-pod permanently blocked every later leak-tagged instance of the
// watched class.
TEST_F(ReferenceChainsBfsTest, RecordDiscoveredInstanceEvictsNoiseSlots) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kKlass = 3;
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, kKlass);

    const int cap = ReferenceChainsTestAccessor::maxDiscoveredPerClass();
    for (int d = 0; d < cap; d++) {
        ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
            kKlass, /*tag=*/100 + d, /*leak_correlated=*/false);
    }
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // Noise beyond the cap is dropped, slots unchanged.
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 108, false);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)100,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));

    // Leak-correlated discovery evicts the first noise slot (tag 100 has no frontier entry ->
    // treated as uncorrelated).
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 200, true);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)200,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));
    EXPECT_EQ((jlong)101,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 1));

    // Once every slot is leak-correlated, a further leak discovery is dropped (no eviction of real
    // signal).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 200, 0, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    frontier->setLeakTag(200, ReferenceChainsTestAccessor::leakTagBase() + 1);
    // Entries for the remaining noise slots so the eviction scan finds all slots leak-tagged.
    for (int d = 1; d < cap; d++) {
        jlong tag = 101 + (d - 1);
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
        frontier->setLeakTag(tag, ReferenceChainsTestAccessor::leakTagBase() + 2);
    }
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(
        kKlass, 201, true);
    EXPECT_EQ(cap, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    for (int d = 0; d < cap; d++) {
        EXPECT_NE((jlong)201,
                  ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, d));
    }

    tracker->stop();
}

// correlateAdmittedLeakTag: a tracked instance the BFS admitted BEFORE it was leak-tagged carries a
// frontier tag on the object; correlating stores the leak tag ON the entry (chain events then emit
// targetTag = leak tag) and records the instance as discovered.
TEST_F(ReferenceChainsBfsTest, CorrelateAdmittedLeakTagSetsEntryAndDiscovers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kKlass = 3;
    constexpr jlong kLeakTag = 0x40000000LL + 5;
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, kKlass);

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 300, 0, 1, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    EXPECT_TRUE(tracker->correlateAdmittedLeakTag(300, kLeakTag, kKlass));
    EXPECT_EQ(kLeakTag, (jlong)ReferenceChainsTestAccessor::frontierLeakTag(300));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_EQ((jlong)300,
              ReferenceChainsTestAccessor::candidateDiscoveredTagForTest(0, 0));

    // Idempotent: an already-correlated entry just returns true.
    EXPECT_TRUE(tracker->correlateAdmittedLeakTag(300, kLeakTag, kKlass));
    EXPECT_EQ(kLeakTag, (jlong)ReferenceChainsTestAccessor::frontierLeakTag(300));

    // Unknown tag: no crash, no discovery side effects.
    EXPECT_FALSE(tracker->correlateAdmittedLeakTag(999, kLeakTag, kKlass));
    EXPECT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    tracker->stop();
}

// Retention-explanation gate on the discovered-instance chains (depth==0 always suppressed;
// depth==1 suppressed only for TRANSIENT roots - a depth-1 chain from a durable root is the real
// direct-retention shape): transient depth-1 must NOT be cached, durable depth-1 and depth-2 must.
TEST_F(PollWatchedTargetsTest, DiscoveredChainGateSuppressesTransientDepthOne) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/3, /*rep=*/(jweak)obj);

    // First poll populates the candidate slots from LivenessTracker's population.
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    FrontierTable *frontier = tracker->frontierTable();
    // Noise shape: transient root (JNI local frame) -> depth-1 instance.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 6, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 7, 6, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Real direct-retention shape: static-field root -> depth-1 instance.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 8, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 9, 8, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Deeper chain through the transient root: passes on depth alone.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, 7, 2, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    // Depth-0 transient root: the candidate instance itself held by a live frame - suppressed like
    // the depth-1 transient shape.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 11, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Depth-0 durable root: the candidate instance IS the static field's value (the
    // singleton-collection-itself shape) - a real direct-retention chain, NOT suppressible as
    // noise.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 12, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 7, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 9, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 10, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 11, false);
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 12, false);
    ASSERT_EQ(5, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7))
        << "depth-1 chain rooted at a transient (JNI local) root is noise";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(9))
        << "depth-1 chain rooted at a durable (static field) root is a real "
           "direct-retention chain";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(10))
        << "depth-2 chain passes the gate regardless of root kind";
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag(11))
        << "depth-0 chain rooted at a transient (stack local) root is noise";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(12))
        << "depth-0 chain rooted at a durable (static field) root is the "
           "direct-retention shape the search exists to report";

    tracker->stop();
}

// Orphan slot sweep: a candidate that qualified long enough for the walk to record discovered
// instances, then stopped qualifying (its trend aged out of the poll's candidate list), must still
// get chains built for those instances.
TEST_F(PollWatchedTargetsTest, OrphanedSlotBuildsDiscoveredChainsAfterCandidateDropsOut) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/3, /*rep=*/(jweak)obj);

    // First poll admits klass 3 into candidate slot 0 (nothing discovered yet, so nothing is built
    // here).
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(0, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // The walk discovered an instance while the candidate still qualified: the real
    // direct-retention shape (static-field root -> depth-1 instance), which the discovered-chain
    // gate lets through.
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 9, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 8, 9, 1, FrontierEntryState::EXPANDED, /*root_kind=*/0));
    ReferenceChainsTestAccessor::recordDiscoveredInstanceForTest(3, 8, false);
    ASSERT_EQ(1, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));

    // The candidate stops qualifying: LivenessTracker's population table is wiped, so
    // selectLeakCandidates() returns 0 on every poll from here on.
    LivenessTracker::instance()->klassPopulationResetForTest();
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(8))
        << "discovered instances recorded while the candidate qualified must "
           "still get chains built after it stops qualifying";

    tracker->stop();
}
