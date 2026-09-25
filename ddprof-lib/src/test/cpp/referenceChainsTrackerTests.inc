/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

class PollWatchedTargetsTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    JNINativeInterface_ jni_tbl{};
    JNIEnv_ mock_jni{};

    std::unordered_map<jobject, jlong> tags;
    std::unordered_set<jobject> dead_refs; // NewLocalRef returns NULL for these

    jvmtiEnv *orig_jvmti = nullptr;
    static PollWatchedTargetsTest *active_fixture;

    void SetUp() override {
        active_fixture = this;
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);

        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.GetTag = &mock_GetTag;
        jvmti_tbl.SetTag = &mock_SetTag;
        jvmti_tbl.GetClassSignature = &mock_GetClassSignature;
        jvmti_tbl.Deallocate = &mock_Deallocate;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);

        jni_tbl = JNINativeInterface_{};
        jni_tbl.NewLocalRef = &mock_NewLocalRef;
        jni_tbl.DeleteLocalRef = &mock_DeleteLocalRef;
        jni_tbl.GetObjectClass = &mock_GetObjectClass;
        mock_jni.functions = &jni_tbl;
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        active_fixture = nullptr;
    }

    static jvmtiError JNICALL mock_GetTag(jvmtiEnv *, jobject object, jlong *tag_ptr) {
        auto it = active_fixture->tags.find(object);
        *tag_ptr = it != active_fixture->tags.end() ? it->second : 0;
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_SetTag(jvmtiEnv *, jobject object, jlong tag) {
        active_fixture->tags[object] = tag;
        return JVMTI_ERROR_NONE;
    }

    static jobject JNICALL mock_NewLocalRef(JNIEnv *, jobject ref) {
        if (active_fixture->dead_refs.count(ref) > 0) {
            return nullptr;
        }
        return ref; // identity passthrough - see this fixture's own comment
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject values are not real JNI refs.
    }

    // pollWatchedTargets()'s diagnostic class-name lookup on the candidate's representative: this
    // fixture's fake jobjects carry no real class identity, so a fixed non-null jclass plus a fixed
    // signature is all GetObjectClass()/GetClassSignature() need to return for that lookup to
    // complete without touching a real JVM.
    static jclass JNICALL mock_GetObjectClass(JNIEnv *, jobject) {
        return (jclass)0xC1A55;
    }

    static jvmtiError JNICALL mock_GetClassSignature(jvmtiEnv *, jclass,
                                                       char **signature_ptr,
                                                       char **generic_ptr) {
        *signature_ptr = strdup("Ltest/FakeKlass;");
        if (generic_ptr != nullptr) {
            *generic_ptr = nullptr;
        }
        return JVMTI_ERROR_NONE;
    }

    static jvmtiError JNICALL mock_Deallocate(jvmtiEnv *, unsigned char *mem) {
        free(mem);
        return JVMTI_ERROR_NONE;
    }

    // Seeds LivenessTracker's real population table with a growing series for `klass_id` (20
    // strictly-increasing samples - satisfies selectLeakCandidates()'s min-fill, growth/floor
    // magnitude, and sustained-trend hysteresis requirements, livenessTracker.h; 20 rather than the
    // 10-sample minimum fill leaves comfortable margin past the hysteresis threshold rather than
    // sitting exactly on its boundary) and points its representative at `rep`.
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // Per-(klass, tid) qualification: selectLeakCandidates() also requires a qualifying
            // allocating thread.
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(nullptr, klass_id, rep);
    }
};

PollWatchedTargetsTest *PollWatchedTargetsTest::active_fixture = nullptr;

TEST_F(PollWatchedTargetsTest, EmitsEventForAlreadyDiscoveredCandidate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    // Model "already discovered by an ordinary runPass()": a root-level FrontierTable entry plus a
    // matching GetTag() result, mirroring referenceChainJfrRoundtrip_ut.cpp's seeding style.
    ASSERT_TRUE(tracker->frontierTable()->insert(
        /*tag=*/7, /*parent_tag=*/0, /*referrer_klass=*/1, /*depth=*/0,
        FrontierEntryState::EDGE));
    tags[obj] = 7;
    // With class-tag matching, _candidate_frontier_tags must be set so buildCanaryChainEvent() can
    // reconstruct the chain.
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(7));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoEventForNotYetDiscoveredCandidate) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    // GetTag() reports 0 (default) - no pass has reached this object yet.

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoDuplicateOnRepeatPoll) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());

    // Klass 1 is still flagged (LivenessTracker's ranking doesn't know an event was already emitted
    // for it) - a second, third, ...
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(7));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, SkipsCandidateWhoseWeakReferenceDied) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    dead_refs.insert(obj); // NewLocalRef(rep) -> NULL, as if GC'd

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7; // would resolve to a discovered tag, if it could resolve

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

// A cached chain must not re-emit forever: once the klass's representative stops resolving
// (collected, or LRU-evicted from LivenessTracker's population table -
// klassPopulationSetRepresentativeForTest()'s ref is the stand-in for either), the very next poll
// must prune it from _resolved_chains rather than leaving a dump keep re-emitting a chain for a
// sample that is gone (see _resolved_chains' own comment, referenceChains.h, and
// pollWatchedTargets()'s "candidate died, or was evicted" branch).
TEST_F(PollWatchedTargetsTest, ChainPersistsAfterRepresentativeDies) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    ASSERT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));

    // The representative died. Per-instance caching: the chain persists (it describes a reference
    // path that was valid at resolution time).
    dead_refs.insert(obj);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "per-instance chains persist after representative dies; "
           "they expire on search restart, not on representative death";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));

    tracker->stop();
}

// Bounded canary parent-chain walk: a cyclic/corrupt parent chain must fail
// safe instead of spinning the poll thread (the bound mirrors
// FrontierTable::reconstructChain()'s maxCapacity() bound), and legitimate
// deep chains must still reconstruct fully - the bound must not cost
// convergence.
TEST_F(PollWatchedTargetsTest, CanaryChainWalkFailsSafeOnCyclicParentChain) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    FrontierTable *frontier = tracker->frontierTable();
    // Corrupt chain: 1 -> 2 -> 1 (a cycle no legitimate BFS admission could
    // produce, but insert() does not validate parent chains - exactly the
    // failure mode reconstructChain()'s own bound guards against).
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 2, 2, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/11));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 3, FrontierEntryState::EDGE, /*root_kind=*/0,
        /*referrer_klass=*/22));

    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, 99);
    ReferenceChainsTestAccessor::setCandidateParentTagForTest(0, 1);
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 2);
    ReferenceChainsTestAccessor::setCandidateReferrerKlassForTest(0, 99);
    ReferenceChainsTestAccessor::setCandidateDepthForTest(0, 4);

    ReferenceChainEvent event;
    // The unbounded predecessor of this walk spun forever here; the bound
    // must make it return promptly (the test itself is the termination
    // proof - a regression to an unbounded walk hangs this test).
    EXPECT_FALSE(ReferenceChainsTestAccessor::buildCanaryChainEventForTest(
        0, &event));

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, CanaryChainWalkStillReconstructsDeepChains) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    FrontierTable *frontier = tracker->frontierTable();
    // A 200-hop linear chain, root-attached at tag 1 (parent_tag == 0): far
    // past the 64-hop default _hop_cap, but the walk bounds at the FRONTIER's
    // maxCapacity() (65536 by default), not the BFS hop cap - legitimate deep
    // chains reconstruct exactly as before the bound.
    const int kDepth = 200;
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EDGE,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/1));
    for (int i = 2; i <= kDepth; i++) {
        ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
            frontier, i, i - 1, i - 1, FrontierEntryState::EDGE, /*root_kind=*/0,
            /*referrer_klass=*/(u32)i));
    }

    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateKlassIdForTest(0, 999);
    ReferenceChainsTestAccessor::setCandidateParentTagForTest(0, kDepth);
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 1);
    ReferenceChainsTestAccessor::setCandidateReferrerKlassForTest(0, 999);
    ReferenceChainsTestAccessor::setCandidateDepthForTest(0, kDepth);

    ReferenceChainEvent event;
    ASSERT_TRUE(ReferenceChainsTestAccessor::buildCanaryChainEventForTest(
        0, &event));
    // Candidate's own klass first, then the reversed walk: root-side hop
    // (tag 1, klass 1) first, parent-side hop (tag 200, klass 200) last.
    ASSERT_EQ((size_t)(kDepth + 1), event._hops.size());
    EXPECT_EQ(999u, event._hops[0].klass_id);
    for (int i = 1; i <= kDepth; i++) {
        EXPECT_EQ((u32)i, event._hops[i].klass_id)
            << "hop " << i;
    }
    EXPECT_EQ(1u, event._target_tag); // the candidate's frontier tag
    EXPECT_EQ((u32)kDepth, event._depth);
    // The root kind describes the chain's ROOT (the root-attached tag-1 entry
    // this walk terminates at), not the candidate-side parent entry - same
    // terminal-root semantics reconstructChain() uses.
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, event._root_kind);

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoOpWhenGcGenerationsDisabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Overrides this fixture's own SetUp() default - exercises the pollWatchedTargets() guard
    // covering LivenessTracker's own _gc_generations gate (population tracking's own gate), not
    // just this tracker's own _enabled.
    LivenessTracker::instance()->setGcGenerationsForTest(false);

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

// Resolved-chain cache (ReferenceChainTracker::cacheResolvedChain()/

class ResolvedChainCacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
    }

    void TearDown() override {
        ReferenceChainsTestAccessor::reset();
    }

    static ReferenceChainEvent makeEvent(u64 target_tag) {
        ReferenceChainEvent event;
        event._target_tag = target_tag;
        event._depth = 0;
        return event;
    }
};

// The defining property of the "stick around" model: a cached chain is re-emitted on every dump,
// not drained once.
TEST_F(ResolvedChainCacheTest, SnapshotReEmitsOnEveryDumpWithoutClearing) {
    ReferenceChainsTestAccessor::cacheChain(/*source_tag=*/1, makeEvent(7),
                                            /*source_tag=*/7, /*search_ns=*/0);

    std::vector<ReferenceChainEvent> firstDump;
    ReferenceChainsTestAccessor::drain(&firstDump);
    ASSERT_EQ(1u, firstDump.size());
    EXPECT_EQ(7u, firstDump[0]._target_tag);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "drain must not clear the cache";

    // A second dump with nothing changed re-emits the same chain.
    std::vector<ReferenceChainEvent> secondDump;
    ReferenceChainsTestAccessor::drain(&secondDump);
    ASSERT_EQ(1u, secondDump.size());
    EXPECT_EQ(7u, secondDump[0]._target_tag);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
}

// Re-resolving the same klass (a restart re-tags its sample, or a fresh walk finds a deeper path)
// refreshes its single cache slot in place rather than accumulating duplicates - so a dump re-emits
// one current chain per klass, not one per resolution.
TEST_F(ResolvedChainCacheTest, RefreshReplacesSameKlassInPlace) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(7), 7, 0);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(7, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    // Same klass, rebuilt from a new tag (e.g. after a search restart).
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(9), 9, 0);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "refresh must overwrite, not append";
    EXPECT_EQ(9, ReferenceChainsTestAccessor::resolvedChainSourceTag(1));

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(1u, dump.size());
    EXPECT_EQ(9u, dump[0]._target_tag);
}

// Distinct klasses each get their own slot and all re-emit together in one dump (order is
// unspecified - the cache is a map keyed by klass_id).
TEST_F(ResolvedChainCacheTest, MultipleKlassesAllSnapshotTogether) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(1), 1, 0);
    ReferenceChainsTestAccessor::cacheChain(2, makeEvent(2), 2, 0);
    ReferenceChainsTestAccessor::cacheChain(3, makeEvent(3), 3, 0);
    ASSERT_EQ(3u, ReferenceChainsTestAccessor::resolvedChainCount());

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(3u, dump.size());
    std::set<u64> tags;
    for (const auto &e : dump) {
        tags.insert(e._target_tag);
    }
    EXPECT_EQ((std::set<u64>{1, 2, 3}), tags);
}

// A brand-new klass arriving with the cache already at MAX_RESOLVED_CHAINS is dropped (and counted
// via REFERENCE_CHAIN_EVENTS_DROPPED, this codebase's own "dropped-event-without-counter" review
// lens) rather than evicting some other still-live sample's chain - but refreshing a klass that is
// already cached still succeeds even at capacity.
TEST_F(ResolvedChainCacheTest, OverflowDropsNewKlassButAllowsRefresh) {
    const int cap = ReferenceChainsTestAccessor::maxResolvedChains();
    long long droppedBefore = Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED);

    for (int i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::cacheChain((jlong)i, makeEvent((jlong)i),
                                                (jlong)i, 0);
    }
    ASSERT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(droppedBefore, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "filling exactly to capacity must not drop anything yet";

    // A brand-new klass at capacity is dropped and counted.
    ReferenceChainsTestAccessor::cacheChain((jlong)cap, makeEvent((jlong)cap),
                                            (jlong)cap, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount())
        << "cache must stay capped, not grow past MAX_RESOLVED_CHAINS";
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED));
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag((u32)cap));

    // Refreshing an already-cached klass at capacity must still succeed - it reuses that klass's
    // existing slot rather than needing a free one.
    ReferenceChainsTestAccessor::cacheChain(/*source_tag=*/0, makeEvent(999),
                                            /*source_tag=*/999, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(999, ReferenceChainsTestAccessor::resolvedChainSourceTag(0));
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "an in-place refresh must not count as a drop";
}

// Pause-time pacing controller: pause-time-SLO feedback loop

TEST_F(ReferenceChainsTest, PacingHoldsSteadyWhenPassesLandExactlyOnCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int startBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 startCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
    ASSERT_EQ(4000, startBudget); // starts pinned at the configured ceiling

    // A pass landing exactly on the pause-time target is a zero error every call - the controller
    // should never move away from its starting point, regardless of how many such passes are
    // observed in a row.
    for (int i = 0; i < 10; i++) {
        ReferenceChainsTestAccessor::updatePacing(5 * 1000000ULL); // 5ms
        EXPECT_EQ(startBudget, ReferenceChainsTestAccessor::effectiveBudget());
        EXPECT_EQ(startCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());
    }

    tracker->stop();
}

TEST_F(ReferenceChainsTest, PacingShrinksBudgetAndWidensCadenceWhenOverCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int initialBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 initialCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // A pass taking 10x the pause-time ceiling, fed repeatedly (a constant input - the plan's own
    // "does not oscillate indefinitely" scenario).
    int lastBudget = initialBudget;
    u64 lastCadence = initialCadence;
    for (int i = 0; i < 20; i++) {
        ReferenceChainsTestAccessor::updatePacing(50 * 1000000ULL); // 50ms
        int budget = ReferenceChainsTestAccessor::effectiveBudget();
        u64 cadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_LE(budget, lastBudget); // never grows while still over ceiling
        EXPECT_GE(cadence, lastCadence); // never shrinks while still over ceiling
        lastBudget = budget;
        lastCadence = cadence;
    }

    // Moved in the correct direction...
    EXPECT_LT(lastBudget, initialBudget);
    EXPECT_GT(lastCadence, initialCadence);
    // ...and converged to a fixed point rather than oscillating: one more identical input produces
    // no further change.
    ReferenceChainsTestAccessor::updatePacing(50 * 1000000ULL);
    EXPECT_EQ(lastBudget, ReferenceChainsTestAccessor::effectiveBudget());
    EXPECT_EQ(lastCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, PacingGrowsBudgetBackAndRelaxesCadenceWhenUnderCeiling) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=4000:pausetarget=5"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Start from a controlled below-ceiling/above-baseline point (as if an earlier over-ceiling run
    // had already shrunk/widened them - see the previous test) with a freshly reset controller,
    // rather than chaining directly off a constant-input sequence like the previous test's own:
    // _pause_pid's integral state would otherwise still be recovering from that sequence's windup
    // for many iterations after switching to a smaller-magnitude error, muddying this test's
    // per-step "moves in the correct direction every step" assertions with a transient this test is
    // not about.
    ReferenceChainsTestAccessor::setEffectiveBudget(2400);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(
        2 * ReferenceChainsTestAccessor::baselineCadenceNs());
    ReferenceChainsTestAccessor::resetPacingController();
    int shrunkBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 widenedCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

    // Now feed passes comfortably under the ceiling, repeatedly (a constant input, to check
    // convergence rather than oscillation).
    int lastBudget = shrunkBudget;
    u64 lastCadence = widenedCadence;
    for (int i = 0; i < 200; i++) {
        ReferenceChainsTestAccessor::updatePacing(0); // effectively instant
        int budget = ReferenceChainsTestAccessor::effectiveBudget();
        u64 cadence = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_GE(budget, lastBudget); // never shrinks while comfortably under
        EXPECT_LE(cadence, lastCadence); // never widens while comfortably under
        lastBudget = budget;
        lastCadence = cadence;
    }

    // Moved in the correct direction... and, since 50 identical comfortably-under-target passes is
    // well past BORROW_WARMUP_PASSES, past the configured ceiling too - budget-borrowing lets it
    // converge at the borrowed ceiling (configured budget * multiplier) instead of stalling at the
    // plain configured budget.
    EXPECT_GT(lastBudget, shrunkBudget);
    EXPECT_EQ(4000 * ReferenceChainsTestAccessor::borrowCeilingMultiplier(), lastBudget);
    EXPECT_LT(lastCadence, widenedCadence);
    // ...and converged: one more identical input produces no further change.
    ReferenceChainsTestAccessor::updatePacing(0);
    EXPECT_EQ(lastBudget, ReferenceChainsTestAccessor::effectiveBudget());
    EXPECT_EQ(lastCadence, ReferenceChainsTestAccessor::effectiveCadenceNs());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, MaybeRevokeBorrowForRootEnumPassPreservesBorrowAtBoundary) {
    Arguments args;
    // BORROW_UNDER_TARGET_FRACTION (referenceChains.h) is 0.5, so with pausetarget=10 the
    // comfortably-under-target boundary is exactly 5ms.
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainsTestAccessor::setBorrowedBudget(500);
    ReferenceChainsTestAccessor::setConsecutiveUnderTargetPasses(5);

    // Exactly at the boundary: comfortably_under_target's `<=` check must still treat this as
    // comfortably under, so the borrow is preserved.
    ReferenceChainsTestAccessor::maybeRevokeBorrowForRootEnumPass(5 * 1000000ULL);
    EXPECT_EQ(500, ReferenceChainsTestAccessor::borrowedBudget());
    EXPECT_EQ(5, ReferenceChainsTestAccessor::consecutiveUnderTargetPasses());

    tracker->stop();
}

TEST_F(ReferenceChainsTest, MaybeRevokeBorrowForRootEnumPassRevokesJustPastBoundary) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:budget=1000:pausetarget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainsTestAccessor::setBorrowedBudget(500);
    ReferenceChainsTestAccessor::setConsecutiveUnderTargetPasses(5);
    ReferenceChainsTestAccessor::setEffectiveBudget(1500); // as if borrow had raised the ceiling

    // Just past the boundary: no longer comfortably under target, so the grant is revoked
    // immediately, including re-clamping _effective_budget down to the plain (non-borrowed) budget
    // rather than leaving it borrow-inflated until the next ordinary pass's updatePacing() call.
    ReferenceChainsTestAccessor::maybeRevokeBorrowForRootEnumPass(6 * 1000000ULL);
    EXPECT_EQ(0, ReferenceChainsTestAccessor::borrowedBudget());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::consecutiveUnderTargetPasses());
    EXPECT_EQ(1000, ReferenceChainsTestAccessor::effectiveBudget());

    tracker->stop();
}

// PainBudget (painBudget.h) - standalone, no ReferenceChainTracker singleton

TEST(PainBudgetTest, ClearBeforeAnythingIsEverSpent) {
    PainBudget budget(0.01);
    EXPECT_TRUE(budget.canStartNow(1000));
}

TEST(PainBudgetTest, SpendCreatesDebtThatBlocksAnImmediateSecondCall) {
    PainBudget budget(0.01); // 1%
    ASSERT_TRUE(budget.canStartNow(1000)); // establishes the drain baseline
    budget.spend(100); // 100ms of debt
    // No time has elapsed since the baseline call above - the debt cannot have drained at all yet.
    EXPECT_FALSE(budget.canStartNow(1000));
}

TEST(PainBudgetTest, DebtDrainsProportionallyToElapsedTimeAndRefillRate) {
    PainBudget budget(0.01); // 1% -> 1ms of debt needs 100ms elapsed to clear
    ASSERT_TRUE(budget.canStartNow(0));
    budget.spend(10); // 10ms of debt -> needs 1000ms elapsed to fully clear
    EXPECT_FALSE(budget.canStartNow(500ULL * 1000000ULL));  // 500ms elapsed - not enough
    EXPECT_TRUE(budget.canStartNow(1500ULL * 1000000ULL));  // 1500ms total - enough
}

TEST(PainBudgetTest, ZeroRefillRateNeverClearsDebt) {
    PainBudget budget(0.0);
    ASSERT_TRUE(budget.canStartNow(0));
    budget.spend(1);
    // An enormous elapsed time still drains nothing at a 0 refill rate.
    EXPECT_FALSE(budget.canStartNow(1000000000000ULL));
}

// Search restart (referenceChains.h's own header comment: gating a

class SearchRestartTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    jvmtiEnv *orig_jvmti = nullptr;

    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);

        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &mock_SetEventNotificationMode;
        jvmti_tbl.GetLoadedClasses = &mock_GetLoadedClasses;
        jvmti_tbl.FollowReferences = &mock_FollowReferences;
        jvmti_tbl.IterateOverReachableObjects = &mock_IterateOverReachableObjects;
        jvmti_tbl.GetAvailableProcessors = &mock_GetAvailableProcessors;
        mock_jvmti.functions = &jvmti_tbl;
        orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&mock_jvmti);
    }

    void TearDown() override {
        VMTestAccessor::setJvmti(orig_jvmti);
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        // UrgentOOMProjectionBypassesCandidateGate below sets this - reset it here (TearDown always
        // runs, even after a fatal ASSERT_* return) rather than as a trailing statement in that
        // test body, so a failed assertion can't leak a stale max-heap value into the next test
        // sharing this singleton.
        LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
    }

    // No loaded classes to resolve - resolveLoadedClasses() reports 0 and does nothing further.
    static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count,
                                                     jclass **out) {
        *count = 0;
        *out = nullptr;
        return JVMTI_ERROR_NONE;
    }

    // ReferenceChainTracker::start() -> autoTuneDefaults() queries this whenever LivenessTracker
    // reports a max heap > 0 - which UrgentOOMProjectionBypassesCandidateGate below sets.
    static jvmtiError JNICALL mock_GetAvailableProcessors(jvmtiEnv *,
                                                           jint *nprocs) {
        *nprocs = 1;
        return JVMTI_ERROR_NONE;
    }

    // Never invokes the callback - models a heap with nothing reachable from any root, so the very
    // first pass completes immediately (0 admitted edges, not truncated).
    static jvmtiError JNICALL mock_FollowReferences(
        jvmtiEnv *, jint, jclass, jobject, const jvmtiHeapCallbacks *,
        const void *) {
        return JVMTI_ERROR_NONE;
    }

    // runPassManualWalk()'s root enumeration - never invokes the root callback, same "nothing
    // reachable from any root" heap model as mock_FollowReferences() above, so the first pass still
    // completes immediately with 0 admitted edges.
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
        jvmtiEnv *, jvmtiHeapRootCallback, jvmtiStackReferenceCallback,
        jvmtiObjectReferenceCallback, const void *) {
        return JVMTI_ERROR_NONE;
    }

    // Same seeding helper as PollWatchedTargetsTest above (20 strictly- increasing samples -
    // satisfies selectLeakCandidates()'s min-fill, growth/floor magnitude, and sustained-trend
    // hysteresis requirements).
    void seedGrowingCandidate(u32 klass_id, jweak rep) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            // Per-(klass, tid) qualification: selectLeakCandidates() also requires a qualifying
            // allocating thread.
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(nullptr, klass_id, rep);
    }
};

TEST_F(SearchRestartTest, WithoutGenerationsSignalRestartStaysUnconditional) {
    // gc_generations off (this fixture's SetUp default): canAffordNewSearch() has no candidate
    // signal to gate on at all, so a terminal search is immediately eligible to restart - preserves
    // this tracker's pre-restart behavior for a referencechains-without-generations setup (this
    // class's own header comment, last paragraph).
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    tracker->stop();
}

TEST_F(SearchRestartTest, GenerationsEnabledButNoCandidateBlocksFirstSearch) {
    // A brand-new tracker must not pay for the initial whole-heap walk/tagging pass either when
    // there is no leak candidate yet - shouldRunPass()'s !_search_started branch now shares
    // canAffordNewSearch() with the restart gate below (this class's own header comment).
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_EQ(0, tracker->passesRun());

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2));

    tracker->stop();
}

TEST_F(SearchRestartTest, GenerationsEnabledButNoCandidateBlocksRestart) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // No leak candidate flagged - nothing to justify the cost of a restart.
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(SearchRestartTest, RestartsOnceACandidateAppearsAndResetsPerSearchState) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());
    ASSERT_EQ(1, tracker->passesRun());

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1)); // restartSearch() runs inline
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    EXPECT_EQ(0, tracker->passesRun()); // restartSearch() zeroed per-search state

    // The next runPass() call takes the "first pass of a search" branch again, exactly like a
    // brand-new tracker.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(1, tracker->passesRun());

    tracker->stop();
}

TEST_F(SearchRestartTest, PainBudgetBlocksARestartUntilItDrains) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:painbudget=1")); // 1%
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    // First-ever search: called via runPass() directly here, bypassing shouldRunPass()'s
    // canAffordNewSearch() gate entirely - the candidate seeded above would satisfy that gate
    // anyway (this class's own header comment).
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #1: _safepoint_pain_budget has never had anything spent into it yet, so this is
    // always immediately affordable regardless of this first search's own cost - the cost a search
    // incurs only debits the *next* restart's affordability (restartSearch()'s own spend-then-reset
    // order), not its own.
    ASSERT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Pretend this second search cost 1000ms of safepoint time - a mocked FollowReferences call in
    // this fixture takes ~0 real wall-clock time, so this accessor stands in for what a real,
    // expensive pass would have accumulated into _search_pain_ms on its own.
    ReferenceChainsTestAccessor::setSearchPainMs(1000);

    // Restart #2: the terminal gate charges the finished search's OWN 1000ms cost BEFORE checking
    // affordability (canAffordNewSearch() must see the cost of the search that just ended, or an
    // expensive search would earn one free immediate successor).
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(2));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Well past the drain point - the debt has cleared, restart #2 proceeds.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1ULL + 200000000000ULL));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

// hasLeakSignal()'s OOM_URGENT_THRESHOLD_S fast path (referenceChains.h/.cpp): a heap-wide leak
// growing fast enough to project exhaustion sooner than the threshold must start a search
// immediately, without waiting for any klass to clear selectLeakCandidates()'s own per-klass
// ring-fill/hysteresis gate - this is the aggressive-leak gap
// GenerationsEnabledButNoCandidateBlocksFirstSearch above documents for the non-urgent case.
TEST_F(SearchRestartTest, UrgentOOMProjectionBypassesCandidateGate) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    // Same worked example as livenessTracker_ut.cpp's
    // SecondsToOOMTest.RisingFloorProjectsExpectedSeconds: 700MiB rise over 7s against a 2800MiB
    // max heap projects to 10s - comfortably under OOM_URGENT_THRESHOLD_S (5 minutes).
    LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)(2800 * MiB));
    for (int i = 0; i < 10; i++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            1000 * MiB + (u64)i * 100 * MiB, (u64)i * SEC_NS);
    }

    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());

    tracker->stop();
}

// Durability re-verification (correctness hardening).

