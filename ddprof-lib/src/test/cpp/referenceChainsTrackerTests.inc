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
        // The seeded population belongs to the current class map.
        LivenessTracker::instance()->classMapGenerationSetForTest(
            Profiler::instance()->classMap()->generation());

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
        return ref; // identity passthrough: fake jobjects are not real JNI refs
    }

    static void JNICALL mock_DeleteLocalRef(JNIEnv *, jobject) {
        // no-op: this fixture's fake jobject values are not real JNI refs.
    }

    // Fake jobjects carry no class identity; a fixed jclass and signature let
    // pollWatchedTargets()'s diagnostic class-name lookup complete.
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

    // Seeds a growing population for `klass_id` with representative `rep`. 20 strictly-increasing
    // samples clear selectLeakCandidates()'s min-fill and hysteresis gates with margin rather than
    // sitting on the 10-sample boundary.
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

    // Klass 1 stays flagged (the ranking doesn't know a chain was emitted); repeat polls must not
    // add duplicates.
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

// A new recording must not inherit the previous one's cached chains or queued abandoned events:
// both would carry StringDictionary ids from the wiped class dictionary. Restarts through the real
// stop()/start() path, not resetSearchStateForTest(), which would clear this state itself.
TEST_F(PollWatchedTargetsTest, RestartDropsPriorRecordingsChainsAndAbandonedEvents) {
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

    // A search abandoned at the tail of recording 1, its event still queued for dump().
    ReferenceChainsTestAccessor::markSearchAbandonedForTest(SearchAbandonReason::TTL);
    ReferenceChainsTestAccessor::enqueueAbandonedEventForTest();
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::pendingAbandonedEventCountForTest());

    tracker->stop();
    ASSERT_FALSE(tracker->start(args));

    std::vector<ReferenceChainEvent> chain_events;
    tracker->drainPendingChainEvents(&chain_events);
    std::vector<ReferenceChainAbandonedEvent> abandoned_events;
    tracker->drainPendingAbandonedEvents(&abandoned_events);
    EXPECT_EQ(0u, chain_events.size())
        << "a new recording must not re-emit the previous recording's resolved chains";
    EXPECT_EQ(0u, abandoned_events.size())
        << "a new recording must not emit the previous recording's abandoned-search events";

    // The new recording's own resolve path is intact.
    ASSERT_TRUE(tracker->frontierTable()->insert(
        9, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 9;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 9);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());

    tracker->stop();
}

// stop() itself must drop the cached chains and queued abandoned events: dump() drains them after
// a recording ends, and a following recording that never calls start() (reference chains or
// allocation sampling off) would otherwise re-emit them against a reset class map.
TEST_F(PollWatchedTargetsTest, StopDropsCachedChainsAndAbandonedEvents) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ReferenceChainEvent cached;
    cached._target_tag = 7;
    ReferenceChainsTestAccessor::cacheChain(7, std::move(cached), 7, 0);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());

    ReferenceChainsTestAccessor::markSearchAbandonedForTest(SearchAbandonReason::TTL);
    ReferenceChainsTestAccessor::enqueueAbandonedEventForTest();
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::pendingAbandonedEventCountForTest());

    tracker->stop();

    std::vector<ReferenceChainEvent> chain_events;
    tracker->drainPendingChainEvents(&chain_events);
    std::vector<ReferenceChainAbandonedEvent> abandoned_events;
    tracker->drainPendingAbandonedEvents(&abandoned_events);
    EXPECT_EQ(0u, chain_events.size())
        << "a stopped tracker must not re-emit its resolved chains";
    EXPECT_EQ(0u, abandoned_events.size())
        << "a stopped tracker must not emit queued abandoned-search events";
}

// The representative's chain is cached under the representative's own frontier tag, so its
// freshness must be judged on that entry. With no discovered instance recorded for the slot, the
// first poll that sees the representative tagged must build and cache its chain.
TEST_F(PollWatchedTargetsTest, RepresentativeChainBuiltWithoutDiscoveredInstances) {
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

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(0, ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(0));
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7))
        << "the representative's chain must be built even before any "
           "discovered-instance chain exists for its slot";

    tracker->stop();
}

// A current-generation chain cached for some other tag of the slot (a discovered instance) says
// nothing about the representative's own entry: if that entry is missing (never built, or
// invalidated by improveChain()/reparentToDurableRoot()), the poll must rebuild it.
TEST_F(PollWatchedTargetsTest, RepresentativeChainRebuiltWhenOnlyDiscoveredChainIsFresh) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::candidateKlassIdForTest(0));

    const u64 kSearchNs = 12345;
    ReferenceChainsTestAccessor::setSearchStartNsForTest(kSearchNs);
    ReferenceChainEvent discovered;
    discovered._target_tag = 9;
    ReferenceChainsTestAccessor::cacheChain(9, std::move(discovered), 9, kSearchNs);
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 9);

    ASSERT_TRUE(tracker->frontierTable()->insert(
        7, 0, 1, 0, FrontierEntryState::EDGE));
    tags[obj] = 7;

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7))
        << "a fresh discovered-instance chain must not mask the "
           "representative's own missing chain";

    tracker->stop();
}

// Dead representative, candidate already found at frontier tag L: the chain is rebuilt from L's
// frontier entry, so it carries every hop up to the root and the root's kind - not just the
// candidate's own class.
TEST_F(PollWatchedTargetsTest, DeadRepresentativeRebuildsFullChainFromFoundTag) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*klass_id=*/3, /*rep=*/(jweak)obj);
    dead_refs.insert(obj);
    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    ASSERT_EQ(3u, ReferenceChainsTestAccessor::candidateKlassIdForTest(0));
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    // root(STATIC, tag 1) -> A (tag 2) -> B (tag 3) -> L (tag 4).
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::EXPANDED,
        JVMTI_HEAP_REFERENCE_STATIC_FIELD, /*referrer_klass=*/11));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 1, 1, FrontierEntryState::EXPANDED, 0, /*referrer_klass=*/22));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 2, 2, FrontierEntryState::EXPANDED, 0, /*referrer_klass=*/33));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 4, 3, 3, FrontierEntryState::EXPANDED, 0, /*referrer_klass=*/3));
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(1ULL << 0);
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 4);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    ASSERT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(4));
    std::vector<ReferenceChainEvent> events;
    tracker->drainPendingChainEvents(&events);
    ASSERT_EQ(1u, events.size());
    const ReferenceChainEvent &event = events[0];
    ASSERT_EQ(4u, event._hops.size());
    EXPECT_EQ(3u, event._hops[0].klass_id);
    EXPECT_EQ(33u, event._hops[1].klass_id);
    EXPECT_EQ(22u, event._hops[2].klass_id);
    EXPECT_EQ(11u, event._hops[3].klass_id);
    EXPECT_EQ(3u, event._depth);
    EXPECT_EQ((u8)JVMTI_HEAP_REFERENCE_STATIC_FIELD, event._root_kind);

    tracker->stop();
}

TEST_F(PollWatchedTargetsTest, NoOpWhenGcGenerationsDisabled) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Overrides SetUp(): exercises pollWatchedTargets()'s LivenessTracker leak-signal gate (the
    // effective generations-or-liveheap flag), not just the tracker's own _enabled.
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

// pollWatchedTargets() must gate on the effective leak-signal flag, not the raw generations option:
// a search started on a liveheap-only source (hasLeakSignal() keys on leakSignalEnabled()) still
// needs its candidates polled here.
TEST_F(PollWatchedTargetsTest, PollsCandidatesWithLiveheapOnlySignalSource) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Overrides SetUp(): liveheap-only source - generations off, effective leak signal on.
    LivenessTracker::instance()->setLeakSignalSourcesForTest(/*generations=*/false,
                                                             /*liveness=*/true);
    ASSERT_FALSE(LivenessTracker::instance()->gcGenerationsEnabled());
    ASSERT_TRUE(LivenessTracker::instance()->leakSignalEnabled());

    int fake_object_storage = 0;
    jobject obj = reinterpret_cast<jobject>(&fake_object_storage);
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)obj);
    ASSERT_TRUE(tracker->frontierTable()->insert(
        /*tag=*/7, /*parent_tag=*/0, /*referrer_klass=*/1, /*depth=*/0,
        FrontierEntryState::EDGE));
    tags[obj] = 7;
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 7);

    tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);

    EXPECT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "a liveheap-only leak signal must still poll candidates";
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(7));

    tracker->stop();
}

class ResolvedChainCacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
        // Leak-tag ownership-period tests below drive the shared pool; keep its state isolated.
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }

    void TearDown() override {
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }

    // A cached chain targeting leak tag `leak_tag`, stamped with the ownership period `stamp`
    // (what buildChainEvent() copies from the frontier entry).
    static ReferenceChainEvent makeLeakEvent(jlong leak_tag, u32 stamp) {
        ReferenceChainEvent event = makeEvent((u64)leak_tag);
        event._leak_tag_incarnation = stamp;
        return event;
    }

    static bool drainContainsTarget(u64 target_tag) {
        std::vector<ReferenceChainEvent> out;
        ReferenceChainsTestAccessor::drain(&out);
        for (const auto &e : out) {
            if (e._target_tag == target_tag) {
                return true;
            }
        }
        return false;
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

TEST_F(ResolvedChainCacheTest, DeferredInvalidationFiltersDeduplicatesAndDrainsExactTags) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(1), 1, 0);
    ReferenceChainsTestAccessor::cacheChain(2, makeEvent(2), 2, 0);
    ReferenceChainsTestAccessor::cacheChain(3, makeEvent(3), 3, 0);
    std::vector<jlong> snapshot =
        ReferenceChainsTestAccessor::snapshotResolvedChainTags();
    ASSERT_EQ(3u, snapshot.size());

    ReferenceChainsTestAccessor::deferResolvedChainInvalidation(2, snapshot);
    ReferenceChainsTestAccessor::deferResolvedChainInvalidation(2, snapshot);
    ReferenceChainsTestAccessor::deferResolvedChainInvalidation(999, snapshot);
    EXPECT_EQ(1u,
              ReferenceChainsTestAccessor::pendingChainInvalidationCount());

    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    EXPECT_FALSE(ReferenceChainsTestAccessor::hasResolvedChainForTag(2));
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(1));
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(3));
    ASSERT_EQ(2u, dump.size());
    EXPECT_EQ(0u,
              ReferenceChainsTestAccessor::pendingChainInvalidationCount());
    EXPECT_EQ(0u,
              ReferenceChainsTestAccessor::drainingChainInvalidationCount());
}

TEST_F(ResolvedChainCacheTest, DeferredInvalidationIsBoundedByCacheAndKeepsCapacity) {
    const int cap = ReferenceChainsTestAccessor::maxResolvedChains();
    for (int i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::cacheChain(i + 1, makeEvent(i + 1),
                                                i + 1, 0);
    }
    std::vector<jlong> snapshot =
        ReferenceChainsTestAccessor::snapshotResolvedChainTags();
    ASSERT_EQ((size_t)cap, snapshot.size());
    for (jlong tag : snapshot) {
        ReferenceChainsTestAccessor::deferResolvedChainInvalidation(tag,
                                                                     snapshot);
    }
    for (jlong tag : snapshot) {
        ReferenceChainsTestAccessor::deferResolvedChainInvalidation(tag,
                                                                     snapshot);
    }
    EXPECT_EQ((size_t)cap,
              ReferenceChainsTestAccessor::pendingChainInvalidationCount());

    ReferenceChainsTestAccessor::drainPendingChainInvalidations();
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_GE(ReferenceChainsTestAccessor::pendingChainInvalidationCapacity(),
              (size_t)cap);
    EXPECT_GE(ReferenceChainsTestAccessor::drainingChainInvalidationCapacity(),
              (size_t)cap);
}

TEST_F(ResolvedChainCacheTest, RestartDropsPendingTagsBeforeNumericTagReuse) {
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(1), 1, 0);
    std::vector<jlong> snapshot =
        ReferenceChainsTestAccessor::snapshotResolvedChainTags();
    ReferenceChainsTestAccessor::deferResolvedChainInvalidation(1, snapshot);
    ASSERT_EQ(1u,
              ReferenceChainsTestAccessor::pendingChainInvalidationCount());

    ReferenceChainsTestAccessor::restartSearchForTest();
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(101), 1, 1);
    ReferenceChainsTestAccessor::drainPendingChainInvalidations();
    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(1));
    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(1u, dump.size());
    EXPECT_EQ(101u, dump[0]._target_tag);
}

// At MAX_RESOLVED_CHAINS a brand-new klass is dropped and counted in
// REFERENCE_CHAIN_EVENTS_DROPPED rather than evicting a live sample's chain; refreshing an
// already-cached klass still succeeds.
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

    // A refresh reuses the klass's existing slot.
    ReferenceChainsTestAccessor::cacheChain(/*source_tag=*/0, makeEvent(999),
                                            /*source_tag=*/999, 0);
    EXPECT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_EQ(999, ReferenceChainsTestAccessor::resolvedChainSourceTag(0));
    EXPECT_EQ(droppedBefore + 1, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED))
        << "an in-place refresh must not count as a drop";
}

// A full cache holding only chains from an earlier search generation must make room for a chain
// the current generation resolves: the earlier generation's entries are evicted and no longer
// drained, and the new chain is cached without counting a drop.
TEST_F(ResolvedChainCacheTest, FullCacheEvictsPreviousGenerationForCurrentChain) {
    const int cap = ReferenceChainsTestAccessor::maxResolvedChains();
    const u64 kGenA = 100;
    const u64 kGenB = 200;
    for (int i = 0; i < cap; i++) {
        ReferenceChainsTestAccessor::cacheChain((jlong)i, makeEvent((u64)i), (jlong)i, kGenA);
    }
    ASSERT_EQ((size_t)cap, ReferenceChainsTestAccessor::resolvedChainCount());
    long long droppedBefore = Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED);

    const jlong kNewTag = 10000;
    ReferenceChainsTestAccessor::cacheChain(kNewTag, makeEvent((u64)kNewTag), kNewTag, kGenB);

    EXPECT_TRUE(ReferenceChainsTestAccessor::hasResolvedChainForTag(kNewTag));
    EXPECT_EQ(droppedBefore, Counters::getCounter(REFERENCE_CHAIN_EVENTS_DROPPED));
    std::vector<ReferenceChainEvent> dump;
    ReferenceChainsTestAccessor::drain(&dump);
    ASSERT_EQ(1u, dump.size()) << "earlier-generation chains must no longer be drained";
    EXPECT_EQ((u64)kNewTag, dump[0]._target_tag);
}

// Test-seam locking (frontierStateForTest()/resolvedChainTargetTagForTest()): both seams are
// called from a Java test thread while the BFS thread mutates the frontier / search generation
// under _engine_lock, so they must serialize on that same lock. _engine_lock is recursive, so the
// blocking is only observable from a second thread.
namespace {
// Polls `done` for up to `timeout_ms`; true once it is set.
bool waitForSeamThread(const std::atomic<bool> &done, int timeout_ms) {
    for (int waited = 0; waited < timeout_ms; waited += 10) {
        if (done.load()) {
            return true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return done.load();
}
} // namespace

// Every value the frontier-state seam can return, and every -1 sentinel path.
TEST_F(ReferenceChainsBfsTest, FrontierStateSeamReportsStatesAndSentinels) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_NE(nullptr, frontier);

    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::FRONTIER, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 2, 0, 0, FrontierEntryState::EXPANDED, 0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 3, 0, 0, FrontierEntryState::ABANDONED, 0));

    EXPECT_EQ(0, tracker->frontierStateForTest(1));
    EXPECT_EQ(1, tracker->frontierStateForTest(2));
    EXPECT_EQ(3, tracker->frontierStateForTest(3));

    EXPECT_EQ(-1, tracker->frontierStateForTest(0)) << "untagged";
    EXPECT_EQ(-1, tracker->frontierStateForTest(-7)) << "negative tag";
    EXPECT_EQ(-1, tracker->frontierStateForTest(999)) << "no frontier entry";
    EXPECT_EQ(-1, tracker->frontierStateForTest(ReferenceChainTracker::LEAK_TAG_BASE))
        << "leak tag";
    EXPECT_EQ(-1, tracker->frontierStateForTest(ReferenceChainTracker::LEAK_TAG_BASE + 5))
        << "leak tag";

    tracker->stop();
    // No frontier table at all: -1, not a crash.
    ReferenceChainsTestAccessor::reset();
    EXPECT_EQ(-1, tracker->frontierStateForTest(1));
}

// frontierStateForTest() must wait for a holder of _engine_lock (a running pass) and report the
// state that holder left behind - while the pure tag guard stays a non-blocking fast path.
TEST_F(ReferenceChainsBfsTest, FrontierStateSeamSerializesWithEngineLock) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_NE(nullptr, frontier);
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 1, 0, 0, FrontierEntryState::FRONTIER, 0));

    tracker->_engine_lock.lock();
    std::atomic<bool> done{false};
    std::atomic<int> result{-2};
    std::thread seam([&] {
        result.store(tracker->frontierStateForTest(1));
        done.store(true);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_FALSE(done.load()) << "seam must block while _engine_lock is held";

    // Fast path: the tag guard never touches engine state, so it must not block.
    std::atomic<bool> fast_done{false};
    std::atomic<int> fast_result{-2};
    std::thread fast([&] {
        fast_result.store(tracker->frontierStateForTest(0));
        fast_done.store(true);
    });
    EXPECT_TRUE(waitForSeamThread(fast_done, 2000)) << "tag guard must not take _engine_lock";

    // Simulates a pass expanding the entry while it holds _engine_lock.
    frontier->markExpanded(1);
    tracker->_engine_lock.unlock();

    EXPECT_TRUE(waitForSeamThread(done, 10000));
    seam.join();
    fast.join();
    EXPECT_EQ(1, result.load());
    EXPECT_EQ(-1, fast_result.load());

    tracker->stop();
}

// The search-generation guard of resolvedChainTargetTagForTest(): every 0 path and the match.
TEST_F(ResolvedChainCacheTest, ResolvedTargetTagSeamChecksGeneration) {
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeEvent(77), 5, 1000);
    EXPECT_EQ(77, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(5));
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(6))
        << "no cached chain";
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(0));
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(-1));

    const jlong leakTag = ReferenceChainTracker::LEAK_TAG_BASE;
    ReferenceChainsTestAccessor::cacheChain(leakTag, makeEvent(88), leakTag, 1000);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(leakTag))
        << "leak tags are never resolved-chain keys for this seam";

    ReferenceChainsTestAccessor::setSearchStartNsForTest(2000);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(5))
        << "chain cached by an earlier search generation";

    ReferenceChainsTestAccessor::setSearchStartNsForTest(0);
    ReferenceChainsTestAccessor::cacheChain(7, makeEvent(99), 7, 0);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(7))
        << "no search in flight: 0 even though source_search_ns == 0 matches";
}

// A generation change made under _engine_lock (restartSearch()/runPass()) while the seam waits must
// be observed: the seam samples _search_start_ns only once it holds _engine_lock.
TEST_F(ResolvedChainCacheTest, ResolvedTargetTagSeamSamplesGenerationUnderEngineLock) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeEvent(77), 5, 1000);

    tracker->_engine_lock.lock();
    std::atomic<bool> done{false};
    std::atomic<jlong> result{-2};
    std::thread seam([&] {
        result.store(tracker->resolvedChainTargetTagForTest(5));
        done.store(true);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_FALSE(done.load()) << "seam must block while _engine_lock is held";
    ReferenceChainsTestAccessor::setSearchStartNsForTest(2000);
    tracker->_engine_lock.unlock();

    EXPECT_TRUE(waitForSeamThread(done, 10000));
    seam.join();
    EXPECT_EQ(0, result.load()) << "stale-generation chain returned after a concurrent restart";
}

// Lock order _engine_lock -> _resolved_chains_lock: with only _resolved_chains_lock held, the seam
// takes _engine_lock, waits on the cache lock, and completes once it is released.
TEST_F(ResolvedChainCacheTest, ResolvedTargetTagSeamLockOrder) {
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeEvent(77), 5, 1000);

    ReferenceChainsTestAccessor::lockResolvedChainsForTest();
    std::atomic<bool> done{false};
    std::atomic<jlong> result{-2};
    std::thread seam([&] {
        result.store(tracker->resolvedChainTargetTagForTest(5));
        done.store(true);
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_FALSE(done.load()) << "seam must wait on _resolved_chains_lock";
    ReferenceChainsTestAccessor::unlockResolvedChainsForTest();

    EXPECT_TRUE(waitForSeamThread(done, 10000));
    seam.join();
    EXPECT_EQ(77, result.load());
}

// Leak-tag identity is (tag, ownership-period stamp): a chain cached during the tag's current
// ownership is answered by the seam and emitted by the dump.
TEST_F(ResolvedChainCacheTest, LeakTagChainOfCurrentOwnerIsResolvedAndEmitted) {
    LivenessTracker *lt = LivenessTracker::instance();
    jlong leak = lt->acquireLeakTagForTest();
    ASSERT_TRUE(ReferenceChainTracker::isLeakTag(leak));
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeLeakEvent(leak, lt->leakTagIncarnation(leak)),
                                            5, 1000);
    EXPECT_EQ(leak, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(leak));
    EXPECT_TRUE(drainContainsTarget((u64)leak));
}

// ABA: the chain's object dies (tag released), and the tag is recycled for a new
// object. The old chain must not be attributed to the new owner by the seam nor emitted into the
// dump, and the dump evicts it (ownership stamps only advance, so it can never become valid).
TEST_F(ResolvedChainCacheTest, LeakTagChainOfDeadOwnerIsNeitherResolvedNorEmitted) {
    LivenessTracker *lt = LivenessTracker::instance();
    jlong leak = lt->acquireLeakTagForTest();
    ASSERT_TRUE(ReferenceChainTracker::isLeakTag(leak));
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeLeakEvent(leak, lt->leakTagIncarnation(leak)),
                                            5, 1000);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());

    // Owner dies: released, not yet re-acquired.
    lt->releaseLeakTagForTest(leak);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(leak));
    EXPECT_FALSE(drainContainsTarget((u64)leak));
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount())
        << "the dump must evict the dead owner's chain";

    // A new object receives the recycled tag (LIFO).
    jlong reused = lt->acquireLeakTagForTest();
    ASSERT_EQ(leak, reused);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(reused))
        << "the dead owner's chain was attributed to the tag's new owner";
    EXPECT_FALSE(drainContainsTarget((u64)reused));
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    // Once the new owner's own chain is cached, it is the one that matches.
    ReferenceChainsTestAccessor::cacheChain(
        6, makeLeakEvent(reused, lt->leakTagIncarnation(reused)), 6, 1000);
    EXPECT_EQ(reused, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(reused));
    std::vector<ReferenceChainEvent> out;
    ReferenceChainsTestAccessor::drain(&out);
    ASSERT_EQ(1u, out.size()) << "only the current owner's chain is emitted";
    EXPECT_EQ(lt->leakTagIncarnation(reused), out[0]._leak_tag_incarnation);
}

// A chain built from a binding whose leak-tag owner already died is refused by the cache: it
// would only occupy a MAX_RESOLVED_CHAINS slot until the next dump evicts it. Recycling the tag
// for a new owner must not revive the dead owner's chain either - the new ownership period's
// stamp does not match the stale one the chain carries.
TEST_F(ResolvedChainCacheTest, DeadOwnerChainIsNotCached) {
    LivenessTracker *lt = LivenessTracker::instance();
    jlong leak = lt->acquireLeakTagForTest();
    ASSERT_TRUE(ReferenceChainTracker::isLeakTag(leak));
    u32 stale_stamp = lt->leakTagIncarnation(leak);
    lt->releaseLeakTagForTest(leak);
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    EXPECT_FALSE(ReferenceChainsTestAccessor::cacheChain(
        5, makeLeakEvent(leak, stale_stamp), 5, 1000))
        << "a chain whose leak-tag owner already died must be refused by the cache";
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());
    EXPECT_FALSE(drainContainsTarget((u64)leak));

    // The recycled tag's new owner must not inherit the dead owner's stamp.
    jlong reused = lt->acquireLeakTagForTest();
    ASSERT_EQ(leak, reused);
    EXPECT_FALSE(ReferenceChainsTestAccessor::cacheChain(
        5, makeLeakEvent(reused, stale_stamp), 5, 1000))
        << "a chain carrying the dead owner's stamp must be refused for the new owner too";
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());
}

// Only the current search's cached chain counts: after a restart moved _search_start_ns, a
// frontier chain cached by the superseded search must not answer the seam (the
// source_search_ns != current gate), and with no active search (start ns 0) nothing answers.
TEST_F(ResolvedChainCacheTest, FrontierChainFromSupersededSearchIsRejected) {
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ASSERT_TRUE(ReferenceChainsTestAccessor::cacheChain(5, makeEvent(77), 5, 1000));
    EXPECT_EQ(77, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(5));

    // Restart: the cached chain belongs to the superseded search.
    ReferenceChainsTestAccessor::setSearchStartNsForTest(2000);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(5))
        << "a frontier chain cached by an earlier search must not answer the seam";

    // No active search: the gate stays closed even though a chain is cached.
    ReferenceChainsTestAccessor::setSearchStartNsForTest(0);
    EXPECT_EQ(0, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(5));
}

// Within one ownership period the leak-tag path is generation-agnostic: a chain an earlier search
// cached for the same owner still answers after a restart.
TEST_F(ResolvedChainCacheTest, LeakTagChainMatchesAcrossGenerationsForSameOwner) {
    LivenessTracker *lt = LivenessTracker::instance();
    jlong leak = lt->acquireLeakTagForTest();
    ASSERT_TRUE(ReferenceChainTracker::isLeakTag(leak));
    ReferenceChainsTestAccessor::setSearchStartNsForTest(1000);
    ReferenceChainsTestAccessor::cacheChain(5, makeLeakEvent(leak, lt->leakTagIncarnation(leak)),
                                            5, 1000);
    ReferenceChainsTestAccessor::setSearchStartNsForTest(2000);
    EXPECT_EQ(leak, ReferenceChainTracker::instance()->resolvedChainTargetTagForTest(leak));
    EXPECT_TRUE(drainContainsTarget((u64)leak));
}

// Chains whose target is a frontier tag (no leak tag) are not subject to the ownership check:
// emitted regardless of what the leak-tag pool does.
TEST_F(ResolvedChainCacheTest, FrontierTargetChainsAreEmittedRegardlessOfPoolState) {
    LivenessTracker *lt = LivenessTracker::instance();
    ReferenceChainsTestAccessor::cacheChain(1, makeEvent(7), 7, 0);
    EXPECT_TRUE(drainContainsTarget(7));
    jlong leak = lt->acquireLeakTagForTest();
    ASSERT_TRUE(ReferenceChainTracker::isLeakTag(leak));
    lt->releaseLeakTagForTest(leak);
    lt->leakTagPoolResetForTest();
    EXPECT_TRUE(drainContainsTarget(7));
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

    // Passes landing exactly on the target are zero error: the controller must never move.
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

    // Constant input at 10x the pause-time ceiling: must converge, not oscillate.
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
    // ...and converged: one more identical input produces no further change.
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

    // Start from a shrunk budget / widened cadence with a freshly reset controller: chaining off an
    // over-ceiling sequence would leave _pause_pid's integral windup breaking the per-step
    // direction assertions below.
    ReferenceChainsTestAccessor::setEffectiveBudget(2400);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(
        2 * ReferenceChainsTestAccessor::baselineCadenceNs());
    ReferenceChainsTestAccessor::resetPacingController();
    int shrunkBudget = ReferenceChainsTestAccessor::effectiveBudget();
    u64 widenedCadence = ReferenceChainsTestAccessor::effectiveCadenceNs();

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

    // Moved in the correct direction, and past the configured ceiling: 200 under-target passes is
    // well past BORROW_WARMUP_PASSES, so it converges at the borrowed ceiling (budget * multiplier).
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

    // Just past the boundary: the grant is revoked and _effective_budget re-clamped immediately,
    // not left borrow-inflated until the next updatePacing().
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
    EXPECT_FALSE(budget.canStartNow(1000000000000ULL));
}

class SearchRestartTest : public ::testing::Test {
protected:
    jvmtiInterface_1_ jvmti_tbl{};
    _jvmtiEnv mock_jvmti{};
    jvmtiEnv *orig_jvmti = nullptr;

    void SetUp() override {
        ReferenceChainsTestAccessor::reset();
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        // The seeded population belongs to the current class map.
        LivenessTracker::instance()->classMapGenerationSetForTest(
            Profiler::instance()->classMap()->generation());

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
        // Max heap, leak-signal gates and burn-in stamp are set by individual tests (e.g.
        // UrgentLatchWithoutCandidateDoesNotStartSearch); restored here so a failed ASSERT_* in
        // one of them can't leak them into the next test.
        LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
        // 0 = "never activated"; the next start() re-stamps it through the CAS from 0.
        LivenessTracker::instance()->setLeakSignalActivatedNsForTest(0);
    }

    // No loaded classes to resolve - resolveLoadedClasses() reports 0 and does nothing further.
    static jvmtiError JNICALL mock_GetLoadedClasses(jvmtiEnv *, jint *count,
                                                     jclass **out) {
        *count = 0;
        *out = nullptr;
        return JVMTI_ERROR_NONE;
    }

    // start() -> autoTuneDefaults() queries this when max heap > 0 (tests that set a fake max
    // heap before start(), e.g. UrgentLatchWithoutCandidateDoesNotStartSearch).
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

    // runPassManualWalk()'s root enumeration; same empty-heap model as mock_FollowReferences().
    static jvmtiError JNICALL mock_IterateOverReachableObjects(
        jvmtiEnv *, jvmtiHeapRootCallback, jvmtiStackReferenceCallback,
        jvmtiObjectReferenceCallback, const void *) {
        return JVMTI_ERROR_NONE;
    }

    // Same as PollWatchedTargetsTest::seedGrowingCandidate().
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

TEST_F(SearchRestartTest, WithoutLeakSignalSourceRestartStaysIdle) {
    // No leak-signal source (SetUp default: neither generations nor liveheap
    // tracking): canAffordNewSearch() can never see a candidate signal, so a
    // terminal search stays terminal - the tracker is idle until a signal
    // source exists. Searching without a signal runs whole-heap BFS passes
    // with zero candidates, which is the waste this gate exists to prevent.
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

TEST_F(SearchRestartTest, GenerationsEnabledButNoCandidateBlocksFirstSearch) {
    // No leak candidate yet: even the first whole-heap walk is skipped, because
    // shouldRunPass()'s !_search_started branch shares canAffordNewSearch() with the restart gate.
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

// hasLeakSignal() must gate on the effective leak-signal flag, not the raw generations option: a
// liveheap-only session (generations off) with a real candidate starts its first search.
TEST_F(SearchRestartTest, LiveheapOnlySourceWithCandidateStartsFirstSearch) {
    LivenessTracker::instance()->setLeakSignalSourcesForTest(/*generations=*/false,
                                                             /*liveness=*/true);
    ASSERT_FALSE(LivenessTracker::instance()->gcGenerationsEnabled());
    ASSERT_TRUE(LivenessTracker::instance()->leakSignalEnabled());
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1)) << "no candidate yet";

    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2))
        << "a liveheap-only leak signal with a candidate must start the search";

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

    // The next runPass() takes the first-pass branch again.
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

    // First-ever search via runPass() directly; the seeded candidate would pass the gate anyway.
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // Restart #1: nothing has been spent into _safepoint_pain_budget yet, so it is immediately
    // affordable.
    ASSERT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    // The mocked walk costs ~0ms; stand in for an expensive search's _search_pain_ms.
    ReferenceChainsTestAccessor::setSearchPainMs(1000);

    // Restart #2: the terminal gate charges the finished search's OWN 1000ms cost BEFORE checking
    // affordability (canAffordNewSearch() must see the cost of the search that just ended, or an
    // expensive search would earn one free immediate successor).
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(2));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());

    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1ULL + 200000000000ULL));
    EXPECT_EQ(SearchState::RUNNING, tracker->searchState());
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, nullptr));
    ASSERT_EQ(SearchState::COMPLETED, tracker->searchState());

    tracker->stop();
}

// hasLeakSignal()'s urgent latch does NOT authorize a candidate-less search: with
// nothing tagged the search can never emit a chain, and while urgent the 30-pass
// no-progress abandonment is suppressed, so it would run to the full TTL doing
// whole-heap BFS. A warmup heap-floor rise can latch urgency with nothing
// tagged, so the candidate requirement must be unconditional. A search starts
// only when a klass clears selectLeakCandidates();
// urgency then applies through the ramp. The burn-in stamp is backdated so
// secondsToOOM()'s age-based burn-in does not mask the latch - this test
// isolates the candidate requirement, not the burn-in.
TEST_F(SearchRestartTest, UrgentLatchWithoutCandidateDoesNotStartSearch) {
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    LivenessTracker::instance()->setLeakSignalActivatedNsForTest(
        OS::nanotime() - LivenessTracker::OOM_PROJECTION_BURN_IN_NS - SEC_NS);
    // Rising floor against a 4000MiB max heap, 29 samples x 60s (the spacing
    // is arbitrary): slope = 100MiB/60s, remaining = 280MiB -> projection =
    // 280 * 60 / 100 = 168s - inside the urgent band.
    LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)(4000 * MiB));
    for (int i = 0; i < 30; i++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            820 * MiB + (u64)i * 100 * MiB, (u64)i * 60 * SEC_NS);
    }

    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // Urgency latched, but no candidate has cleared the leak-signal probe.
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
#ifdef COUNTERS
    long long urgent_no_cand = Counters::getCounter(REFERENCE_CHAIN_URGENT_NO_CANDIDATE);
#endif
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1))
        << "urgent without a candidate must not start a candidate-less search";
    EXPECT_EQ(0, tracker->passesRun());
#ifdef COUNTERS
    // The refusal is observable in production diagnostics, not only in the
    // debug-only TEST_LOG_SUMMARY.
    EXPECT_EQ(urgent_no_cand + 1, Counters::getCounter(REFERENCE_CHAIN_URGENT_NO_CANDIDATE))
        << "one refused latched/zero-candidate evaluation counts exactly once";
    urgent_no_cand = Counters::getCounter(REFERENCE_CHAIN_URGENT_NO_CANDIDATE);
#endif

    // Disabled leak-signal source: hasLeakSignal() returns before isUrgent()
    // and the counter, so nothing is counted.
    LivenessTracker::instance()->setGcGenerationsForTest(false);
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(1));
#ifdef COUNTERS
    EXPECT_EQ(urgent_no_cand, Counters::getCounter(REFERENCE_CHAIN_URGENT_NO_CANDIDATE))
        << "a disabled leak-signal source must not count";
#endif
    LivenessTracker::instance()->setGcGenerationsForTest(true);

    // Once a klass clears the probe, the search starts - and urgency applies
    // through the ramp from that point on.
    int fake_object_storage = 0;
    seedGrowingCandidate(/*source_tag=*/1, /*rep=*/(jweak)&fake_object_storage);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2));
#ifdef COUNTERS
    EXPECT_EQ(urgent_no_cand, Counters::getCounter(REFERENCE_CHAIN_URGENT_NO_CANDIDATE))
        << "a gate opened by a real candidate must not count";
#endif

    // 0 = "never activated"; the next start() re-stamps it through the CAS from 0.
    LivenessTracker::instance()->setLeakSignalActivatedNsForTest(0);
    tracker->stop();
}

