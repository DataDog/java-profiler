/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

TEST_F(ReferenceChainsBfsTest, StaleRootAttributionUpgradesOnRediscovery) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Synthetic stack-local root: admitted, root-attached (parent_tag == 0), its owning frame has
    // since "gone away" from the design doc's scenario (nothing further to model here - the entry
    // simply stays as-is until a more durable root is discovered).
    jlong tag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, tag, /*parent_tag=*/0, /*depth=*/0,
        FrontierEntryState::EXPANDED, JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // A second, equally-or-less durable root discovery does not overwrite the recorded root_kind.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_STACK_LOCAL, entry.root_kind);

    // A durable root (JNI global) attaching to the same object upgrades it.
    EXPECT_TRUE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_JNI_GLOBAL, entry.root_kind);
    EXPECT_EQ(0, entry.parent_tag); // still root-attached, unchanged

    // An even less durable root discovered afterwards cannot downgrade it.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, tag, JVMTI_HEAP_REFERENCE_MONITOR));
    ASSERT_TRUE(frontier->lookup(tag, &entry));
    EXPECT_EQ(JVMTI_HEAP_REFERENCE_JNI_GLOBAL, entry.root_kind);

    tracker->stop();
}

// Exercises the invariant conflict that durability re-verification exists to catch: a non-root
// entry (parent_tag != 0) rediscovered as if via a root context must never have its root_kind
// overwritten - doing so would leave a non-zero root_kind on an entry nothing else treats as
// root-attached (referenceChains.h's FrontierEntry::root_kind comment), since this mutator never
// touches parent_tag.
TEST_F(ReferenceChainsBfsTest, NonRootAttachedEntryNeverUpgraded) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Parent Y (root-attached) and child X, admitted the way frontier re-expansion admits a
    // non-root child: non-root (parent_tag == Y's tag), root_kind == 0.
    jlong yTag = 1;
    jlong xTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, yTag, /*parent_tag=*/0, /*depth=*/0,
        FrontierEntryState::EXPANDED, JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, xTag, /*parent_tag=*/yTag, /*depth=*/1,
        FrontierEntryState::EXPANDED, /*root_kind=*/0));

    // Re-expanding Y rediscovers an edge to X (already tracked) - even if this rediscovery is
    // (incorrectly) attempted with a durable root_kind, it must be rejected because X is not
    // root-attached.
    EXPECT_FALSE(ReferenceChainsTestAccessor::maybeUpgradeRootAttachedRootKind(
        frontier, xTag, JVMTI_HEAP_REFERENCE_STATIC_FIELD));
    FrontierEntry entry{};
    ASSERT_TRUE(frontier->lookup(xTag, &entry));
    EXPECT_EQ(0, entry.root_kind);
    EXPECT_EQ(yTag, entry.parent_tag);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, RotationSelectsOnlyTransientExpandedRootAttachedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Eligible: root-attached, EXPANDED, transient root_kind.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Not eligible: durable root_kind.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_GLOBAL));
    // Not eligible: transient but still FRONTIER, not yet EXPANDED.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    // Not eligible: transient root_kind but not root-attached.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, /*parent_tag=*/1, 1, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));
    // Eligible: root-attached, EXPANDED, transient (JNI local this time).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 5, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_JNI_LOCAL));

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(10);
    std::sort(selected.begin(), selected.end());
    EXPECT_EQ((std::vector<jlong>{1, 5}), selected);

    // Selected tags are queued for re-expansion, exactly like an ordinary admission would queue a
    // newly-discovered tag.
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::priorityExpandSize());

    tracker->stop();
}

// N transient-root_kind entries, rotation size R: every entry must be selected at least once within
// ceil(N/R) calls, regardless of where the cursor happened to start.
TEST_F(ReferenceChainsBfsTest, RotationCoversAllEntriesWithinCeilNOverR) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const int N = 10;
    const int R = 3;
    for (jlong tag = 1; tag <= N; tag++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    }

    std::unordered_set<jlong> covered;
    int calls = (N + R - 1) / R;
    for (int i = 0; i < calls; i++) {
        std::vector<jlong> selected =
            ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(R);
        for (jlong tag : selected) {
            covered.insert(tag);
        }
    }
    EXPECT_EQ((size_t)N, covered.size());

    tracker->stop();
}

// collectStaleExpandedEntriesForRotation()'s own EXPANDED-only criterion is a strict superset of
// collectStaleRootKindEntriesForRotation()'s (which also requires parent_tag == 0 and a transient
// root_kind), and runPassManualWalk() calls the root-kind collector first, into the very same
// _priority_expand deque.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationDoesNotDuplicateRootKindSelection) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    // Eligible for both collectors: EXPANDED, root-attached, transient root_kind - exactly the
    // overlap collectStaleRootKindEntriesForRotation() will pick up first.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    // Eligible only for the EXPANDED-only sweep: EXPANDED but not root-attached.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, /*parent_tag=*/1, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0));

    std::vector<jlong> root_kind_selected =
        ReferenceChainsTestAccessor::collectStaleRootKindEntriesForRotation(
            ReferenceChainsTestAccessor::rootKindRotationBudget());
    EXPECT_EQ((std::vector<jlong>{1}), root_kind_selected);

    std::vector<jlong> stale_expanded_selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
            ReferenceChainsTestAccessor::staleExpandedRotationBudget());
    // Tag 1 is already queued from the root-kind collector above and must not be selected again;
    // tag 2 is newly discovered by this sweep.
    EXPECT_EQ((std::vector<jlong>{2}), stale_expanded_selected);

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1, 2}), queued);
    std::unordered_set<jlong> unique_queued(queued.begin(), queued.end());
    EXPECT_EQ(queued.size(), unique_queued.size());

    tracker->stop();
}

// A tag left over in _priority_expand from a prior pass's truncated expandFrontier() batch (see
// expandFrontier()'s own "leave the batch at the front of the source queue for a later pass to
// retry" comment) must also be skipped by collectStaleExpandedEntriesForRotation() - not just tags
// queued by collectStaleRootKindEntriesForRotation() earlier in the same call.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationSkipsPreexistingQueueEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STACK_LOCAL));

    // Simulate a truncated batch from a prior pass still sitting at the front of _priority_expand,
    // without going through the root-kind collector at all - the leftover entry alone must still be
    // enough to suppress a duplicate.
    ReferenceChainsTestAccessor::pushPriorityExpand(1);

    std::vector<jlong> stale_expanded_selected =
        ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
            ReferenceChainsTestAccessor::staleExpandedRotationBudget());
    EXPECT_TRUE(stale_expanded_selected.empty());

    std::vector<jlong> queued = ReferenceChainsTestAccessor::priorityExpandContents();
    EXPECT_EQ((std::vector<jlong>{1}), queued);

    tracker->stop();
}

// End-to-end proof of the prof-analyzer-hotdog-jb pod's actual leak shape: a static-field-rooted
// collection (like ProfileAnalyzer.LEAK_BUFFER) whose owning node is admitted and fully EXPANDED
// once, then has a *new* element appended to it afterward - mirroring a Java List field being
// mutated in place, never reassigned, well after admitStaticFieldRoots()'s one-time sweep.
TEST_F(ReferenceChainsBfsTest, RotationDiscoversLateElementOfExpandedStaticFieldCollectionWithoutSearchCompleting) {
    Arguments args;
    // budget=8 -> rotation_reserved_budget = min(8/2, 272) = 4, ordinary = 4: both slices non-zero,
    // unlike a budget=1 pattern which would zero out rotation's reserved slice entirely (min(0,
    // 272) == 0).
    ASSERT_FALSE(args.parse("referencechains=true:hops=5000:budget=8:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int classNode = addNode();
    int listNode = addNode();
    int seedChildNode = addNode();
    int lateChildNode = addNode();

    // Distractor chain: a long, independently root-seeded chain that never fully drains within this
    // test's bounded pass loops below, so the overall search always has forward progress available
    // and never reaches SearchState::COMPLETED (nor NO_PROGRESS_PASS_LIMIT-triggered ABANDONED)
    // purely as a side effect of this test's own loop bounds.
    const int kDistractorNodes = 500;
    std::vector<int> distractor(kDistractorNodes);
    for (int i = 0; i < kDistractorNodes; i++) {
        distractor[i] = addNode();
    }

    // addClass() captures classNode's address in node_tags' backing storage - must come after every
    // addNode() call above (including the distractor loop), or a later push_back reallocating
    // node_tags would silently leave this pointer dangling (indexOfNode() would then never match
    // it).
    addClass((void *)&node_tags[classNode], "Lcom/rc/statics/GrowingListHolder;");

    script = {
        // listNode is retained only via classNode's static field - the same shape as
        // DiscoversObjectRetainedOnlyByStaticField above.
        {JVMTI_HEAP_REFERENCE_STATIC_FIELD, classNode, listNode, -1},
        // listNode's one pre-existing element, discovered the first time listNode itself is
        // expanded.
        {JVMTI_HEAP_REFERENCE_FIELD, listNode, seedChildNode, -1},
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, distractor[0], -1},
    };
    for (int i = 0; i + 1 < kDistractorNodes; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, distractor[i], distractor[i + 1], -1});
    }

    // Phase 1: run passes until listNode has been fully expanded (its one pre-existing child
    // discovered), without ever letting the search complete.
    bool truncated = true;
    FrontierEntry listEntry{};
    bool listExpanded = false;
    for (int i = 0; i < 200 && !listExpanded; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        jlong listTag = tags_ever_assigned[listNode];
        if (listTag != 0 && tracker->frontierTable()->lookup(listTag, &listEntry)
                && listEntry.state == FrontierEntryState::EXPANDED) {
            listExpanded = true;
        }
    }
    ASSERT_TRUE(listExpanded);
    ASSERT_NE(0, tags_ever_assigned[seedChildNode]);
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());

    // Phase 2: simulate a new element appended to the leaking static field's list *after*
    // listNode's one-time expansion - the exact "growing collection" shape found in the real pod's
    // leak generator.
    script.push_back({JVMTI_HEAP_REFERENCE_FIELD, listNode, lateChildNode, -1});

    for (int i = 0; i < 200 && tags_ever_assigned[lateChildNode] == 0; i++) {
        ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    }

    // The late element was discovered purely via rotation re-expanding listNode - and, critically,
    // without the search ever completing (no dependency on a full heap walk finishing).
    ASSERT_NE(0, tags_ever_assigned[lateChildNode]);
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    std::vector<u32> chain;
    ASSERT_TRUE(tracker->frontierTable()->reconstructChain(
            tags_ever_assigned[lateChildNode], &chain));
    FrontierEntry lateEntry{};
    ASSERT_TRUE(tracker->frontierTable()->lookup(
            tags_ever_assigned[lateChildNode], &lateEntry));
    EXPECT_EQ(tags_ever_assigned[listNode], lateEntry.parent_tag);

    tracker->stop();
}

// Proof of the fix for the actual prof-analyzer-hotdog-jb stall:
// collectStaleExpandedEntriesForRotation() (referenceChains.cpp) used to always rescan
// FrontierTable slots starting from tag 1, unlike its sibling
// collectStaleRootKindEntriesForRotation() which already carried its own persistent cursor.
TEST_F(ReferenceChainsBfsTest, StaleExpandedRotationCoversHighTagEntryBehindLowTagPopulationWithinBoundedPasses) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    const int lowTagBudget = ReferenceChainsTestAccessor::staleExpandedRotationBudget();
    // Comfortably above the 256-entry cap, so the low-tag population alone would fill every sweep
    // before an always-from-1 scan could ever reach the high-tag entry below - mirrors a real
    // multi-GiB heap's frontier table, which accumulates far more than 256 long-lived, perpetually-
    // EXPANDED entries (bootstrap classes, caches, etc.) well before any one leak-candidate class
    // even loads.
    const int lowTagPopulation = lowTagBudget + 50;
    for (jlong tag = 1; tag <= lowTagPopulation; tag++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STACK_LOCAL));
    }

    // The leak candidate's own owning node - e.g. LEAK_BUFFER's list, admitted via a static field
    // only once its class loads, well after the JVM's own bootstrap population already occupies
    // every low tag number.
    const jlong highTag = lowTagPopulation + 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, highTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD));

    // Several simulated passes: each iteration mirrors one real pass -
    // collectStaleExpandedEntriesForRotation() runs once, then clearPriorityExpand() mirrors
    // expandFrontier() having drained whatever it selected before the next pass's sweep resumes
    // from the cursor.
    const int table_size = lowTagPopulation + 1;
    const int calls = (table_size + lowTagBudget - 1) / lowTagBudget;
    bool highTagSelected = false;
    std::unordered_set<jlong> covered;
    for (int pass = 0; pass < calls && !highTagSelected; pass++) {
        std::vector<jlong> selected =
            ReferenceChainsTestAccessor::collectStaleExpandedEntriesForRotation(
                lowTagBudget);
        for (jlong tag : selected) {
            covered.insert(tag);
            if (tag == highTag) {
                highTagSelected = true;
            }
        }
        ReferenceChainsTestAccessor::clearPriorityExpand();
    }

    EXPECT_TRUE(highTagSelected)
        << "highTag was never selected within ceil(table_size / max_count) "
           "passes - the fix's coverage guarantee does not hold";
    EXPECT_EQ((size_t)table_size, covered.size());

    tracker->stop();
}

// trackLeakAccumulation() - the admission-time hook (called from

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationAggregatesBySignatureAndFanout) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    constexpr u32 kParent1Klass = 100, kParent2Klass = 200;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong parent1Tag = 1, parent2Tag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parent1Tag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParent1Klass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parent2Tag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParent2Klass));

    // 3 children of the watched leaf klass under parent1, 1 under parent2 - each call simulates one
    // admission (the childTag argument is only used by production code for logging/future use, not
    // read by this method).
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 10);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 11);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent1Tag, 12);
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parent2Tag, 20);

    EXPECT_EQ(3u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParent1Klass));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParent2Klass));
    EXPECT_EQ(3u, ReferenceChainsTestAccessor::leakParentFanout(parent1Tag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parent2Tag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsUnwatchedKlass) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, /*class_tag=*/100));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, /*class_tag=*/555,
                                                        parentTag, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsRootAttachedChild) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});

    // parent_tag == 0 - a root-attached leaf itself, nothing to attribute a container to.
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, 987, /*parent_tag=*/0, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationSkipsWhenParentNotFound) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({987});

    // parent_tag=99 was never inserted - graceful no-op, not a crash.
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, 987, /*parent_tag=*/99, 10);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

// Proof of the actual bug this design was found fixing: the classMap dictionary id (referrer_klass)
// for the exact same class can differ depending on which subsystem/generation resolved it (see
// class_tag's own comment, referenceChains.h, for the real-world case - "[B" resolving to two
// different classMap ids for LivenessTracker vs.
TEST_F(ReferenceChainsBfsTest, TrackLeakAccumulationMatchesByClassTagEvenWhenReferrerKlassDiffers) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafClassTag = 987;
    constexpr u32 kParentClassTag = 100;
    // Deliberately different, "wrong" classMap ids - simulating exactly the compaction/regeneration
    // scenario that broke referrer_klass-based matching.
    constexpr u32 kParentStaleReferrerKlass = 555555;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafClassTag});

    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, kParentStaleReferrerKlass,
        kParentClassTag));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafClassTag,
                                                        parentTag, 10);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafClassTag,
                                                                   kParentClassTag));
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

// collectLeakAccumulationCandidatesForRotation() - the two-tier design

// The central discriminating test for the whole design (per the "ubiquitous common leaf class held
// by many small unrelated parents" concern this design exists to solve): a signature with a LARGE
// but FLAT total (many unrelated parents, e.g. a common leaf class scattered across a real
// classpath) must NOT outrank a signature with a SMALLER but GROWING total (the actual leak) once a
// growth history exists - retained-size-style ranking alone would pick the wrong one every time.
TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationPrioritizesGrowingSignatureOverLargeFlatOne) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987;
    constexpr u32 kGrowingParentKlass = 100;  // signature A: the real leak
    constexpr u32 kUbiquitousParentKlass = 999; // signature B: common, but flat
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Signature A: one parent, growing.
    jlong growingParentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, growingParentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kGrowingParentKlass));

    // Signature B: 20 distinct, unrelated parents, each holding just 1-2 instances of the same
    // common leaf klass - a much LARGER total than A, but it will not grow between passes.
    constexpr int kUbiquitousParentCount = 20;
    std::vector<jlong> ubiquitousParentTags;
    for (int i = 0; i < kUbiquitousParentCount; i++) {
        jlong tag = 100 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kUbiquitousParentKlass));
        ubiquitousParentTags.push_back(tag);
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, tag, 1000 + i);
    }
    // Pass 1: A has fanout 5, B has total 20 (20 parents x 1 each) - B is larger.
    for (int i = 0; i < 5; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            growingParentTag, 2000 + i);
    }
    ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
        ReferenceChainsTestAccessor::leakAccumulationRotationBudget());

    // Pass 2: B stays exactly flat (no new admissions); A grows from 5 to 8.
    for (int i = 0; i < 3; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            growingParentTag, 3000 + i);
    }
    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
            ReferenceChainsTestAccessor::leakAccumulationRotationBudget());

    ASSERT_EQ(1u, selected.size());
    EXPECT_EQ(growingParentTag, selected[0])
        << "the growing signature's parent must be selected, even though "
           "the flat-but-larger signature has a much bigger absolute total";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationRanksByFanoutWithinWinningSignature) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong lowFanoutTag = 1, highFanoutTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, lowFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, highFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));

    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, lowFanoutTag, 10);
    for (int i = 0; i < 5; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            highFanoutTag, 20 + i);
    }

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(highFanoutTag, selected[0]) << "higher fanout ranks first";
    EXPECT_EQ(lowFanoutTag, selected[1]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationRespectsMaxCountAndDedup) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong tag1 = 1, tag2 = 2, tag3 = 3;
    for (jlong tag : {tag1, tag2, tag3}) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, tag, 0, 0, FrontierEntryState::EXPANDED,
            JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, tag, 10);
    }
    // tag2 already queued from an earlier collector this same pass - must be skipped even though it
    // qualifies structurally.
    ReferenceChainsTestAccessor::pushPriorityExpand(tag2);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(
            /*max_count=*/1);
    EXPECT_EQ(1u, selected.size()) << "capped at max_count";
    EXPECT_NE(tag2, selected[0]) << "already-queued tag must not be re-selected";

    tracker->stop();
}

// Reversed on round-4 pod evidence (ev-leaktag-onpod-round4): the previous EXPANDED-only selection
// made the targeted tier select ZERO every pass on a live leak - the growing holders are
// un-expanded FRONTIER-state backlog entries that the starved pending lane never reaches (a 127k
// backlog at ~120-200 objects/min).
TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationSelectsUnexpandedFrontierParentAheadOfBacklog) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    // Stale re-walks already sitting in the priority lane (push_back, as the other two collectors
    // do).
    ReferenceChainsTestAccessor::pushPriorityExpand(900);
    ReferenceChainsTestAccessor::pushPriorityExpand(901);

    jlong notYetExpandedTag = 1, expandedLowFanoutTag = 2;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, notYetExpandedTag, 0, 0, FrontierEntryState::FRONTIER,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, expandedLowFanoutTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    for (int i = 0; i < 10; i++) {
        ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                            notYetExpandedTag, 10 + i);
    }
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass,
                                                        expandedLowFanoutTag, 100);

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(2u, selected.size());
    EXPECT_EQ(notYetExpandedTag, selected[0])
        << "the FRONTIER-state parent qualifies and outranks the "
           "lower-fanout EXPANDED one";
    EXPECT_EQ(expandedLowFanoutTag, selected[1]);

    std::vector<jlong> queue = ReferenceChainsTestAccessor::priorityExpandContents();
    ASSERT_GE(queue.size(), 4u);
    EXPECT_EQ(notYetExpandedTag, queue[0])
        << "the targeted un-expanded holder must JUMP the backlog, not "
           "queue behind the stale re-walks";
    EXPECT_EQ(expandedLowFanoutTag, queue[1])
        << "selection order must be preserved at the head (fanout rank)";
    EXPECT_EQ(900, queue[2]);
    EXPECT_EQ(901, queue[3]);

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationReturnsEmptyWhenNothingHasGrownSincePreviousPass) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});

    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 10);

    // First call establishes the baseline (delta == total, since there is no prior snapshot) and
    // selects it.
    std::vector<jlong> firstPass =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    ASSERT_EQ(1u, firstPass.size());
    ReferenceChainsTestAccessor::clearPriorityExpand();

    // Second call, nothing new admitted - delta is now 0 for every signature, so nothing should be
    // selected.
    std::vector<jlong> secondPass =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    EXPECT_TRUE(secondPass.empty())
        << "no signature grew since the previous pass's snapshot";

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, LeakAccumulationRotationReturnsEmptyWhenNoSignaturesTracked) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    std::vector<jlong> selected =
        ReferenceChainsTestAccessor::collectLeakAccumulationCandidatesForRotation(10);
    EXPECT_TRUE(selected.empty());

    tracker->stop();
}

// seedLeakAccumulationForNewlyWatchedKlass() - the cold-start fix: retroactively

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationPopulatesFromAlreadyAdmittedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    // Entries inserted directly (as if admitted by an earlier pass), with no watched klass_id set
    // at all yet at insertion time - trackLeakAccumulation() was never called for any of these.
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    for (int i = 0; i < 4; i++) {
        jlong childTag = 10 + i;
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, childTag, parentTag, 1, FrontierEntryState::EXPANDED,
            /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    }
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount())
        << "nothing tracked yet - trackLeakAccumulation() was never called";

    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);

    EXPECT_EQ(4u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParentKlass));
    EXPECT_EQ(4u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationSkipsNonMatchingAndNonExpandedEntries) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kOtherKlass = 555, kParentKlass = 100;
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    // Wrong class - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, parentTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kOtherKlass));
    // Right class, but still FRONTIER (not yet EXPANDED) - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 11, parentTag, 1, FrontierEntryState::FRONTIER,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));
    // Right class, root-attached (no real parent) - must not be counted.
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 12, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kLeafKlass));

    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::leakSignatureCount());

    tracker->stop();
}

TEST_F(ReferenceChainsBfsTest, SeedLeakAccumulationComposesWithOngoingIncrementalUpdates) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=64"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();

    constexpr u32 kLeafKlass = 987, kParentKlass = 100;
    jlong parentTag = 1;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, parentTag, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/0, kParentKlass));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 10, parentTag, 1, FrontierEntryState::EXPANDED,
        /*root_kind=*/0, /*referrer_klass=*/0, kLeafKlass));

    // Retroactive seed sees the one pre-existing child.
    ReferenceChainsTestAccessor::seedLeakAccumulationForNewlyWatchedKlass(kLeafKlass);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));

    // A genuinely new admission after watching starts must add on top of the retroactive baseline,
    // not reset or double it.
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({kLeafKlass});
    ReferenceChainsTestAccessor::trackLeakAccumulation(frontier, kLeafKlass, parentTag, 11);

    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakParentFanout(parentTag));
    EXPECT_EQ(2u, ReferenceChainsTestAccessor::leakSignatureTotal(kLeafKlass, kParentKlass));

    tracker->stop();
}

// Smoke test simulating the hotdog pod conditions that starved BFS:

