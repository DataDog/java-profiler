/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

class PodInAJarTest : public ReferenceChainsBfsTest {
protected:
    struct PodTopology {
        int holder_class_node = -1;
        int wrapper_node = -1;
        int list_node = -1;
        int leak_cls_idx = -1;
        int wrapper_cls_idx = -1;
        int list_cls_idx = -1;
        std::vector<int> chunk_nodes;
        std::vector<jlong> chunk_leak_tags;
        std::vector<int> flood_class_nodes;
        std::vector<int> flood_nodes;
        std::vector<int> filler_nodes;
    };

    static constexpr int kChunks = 6; // < MAX_DISCOVERED_INSTANCES_PER_CLASS
    static constexpr u64 kCycleNs = 2000000000ULL; // 2s fake-clock step

    void SetUp() override {
        ReferenceChainsBfsTest::SetUp();
        // resolveCandidateRepresentative() NewLocalRef()s the stored representative; the Bfs
        // fixture never wires that JNI slot (PollWatchedTargetsTest has its own).
        jni_tbl.NewLocalRef = &mock_NewLocalRefPassthrough;
        // NOTE: no liveness calls here - the Bfs tests run without them, and liveness state changes
        // (setGcGenerationsForTest) alter the pass machinery's behavior; each harness test resets
        // liveness explicitly where it wants it (resetLivenessForPod below).
    }

    static jobject JNICALL mock_NewLocalRefPassthrough(JNIEnv *, jobject ref) {
        return ref;
    }

    void resetLivenessForPod() {
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);
        LivenessTracker::instance()->leakTagPoolResetForTest();
    }

    void TearDown() override {
        ReferenceChainsBfsTest::TearDown();
        // Hygiene for whatever suite runs next: clear any population this harness seeded.
        LivenessTracker::instance()->klassPopulationResetForTest();
    }

    // Builds the hotdog leak topology: holder-class static -> synchronized wrapper (with its
    // mutex==this self-edge) -> c -> K leak-tagged chunks, plus 2 flood classes x 16 static-held
    // nodes for anchor-tier volume.
    PodTopology buildLeakPod() {
        PodTopology topo;
        // CAPACITY FIXTURE CONTRACT: classes registered via
        // classes.push_back({(void*)&node_tags[node], ...}) capture the node's ADDRESS as the
        // jclass identity - std::vector growth would reallocate node_tags and dangle every captured
        // pointer, silently making indexOfNode() fail for those classes in the static sweep (the
        // holder array seeds no expandable class, the STATIC_FIELD edges never replay, nothing
        // admits).
        node_tags.reserve(600);
        tags_ever_assigned.reserve(600);
        topo.leak_cls_idx = addClass((void *)0x5001, "[B");
        topo.wrapper_cls_idx = addClass(
            (void *)0x5002,
            "Ljava/util/Collections$SynchronizedRandomAccessList;");
        topo.list_cls_idx = addClass((void *)0x5003, "Ljava/util/ArrayList;");

        topo.holder_class_node = addNode();
        topo.wrapper_node = addNode();
        topo.list_node = addNode();
        // The holder class node doubles as the jclass identity (see
        // DiscoversObjectRetainedOnlyByStaticField): register it as a loaded class so the
        // static-field sweep admits the wrapper root-attached.
        classes.push_back({(void *)&node_tags[topo.holder_class_node],
                           "Lcom/rc/pod/Holder;"});
        // Flood classes get their own jclass-identity nodes too, so their statics are separate
        // anchors (not more statics on the holder).
        const char *flood_sigs[2] = {"Lcom/rc/pod/FloodA;",
                                     "Lcom/rc/pod/FloodB;"};
        for (int c = 0; c < 2; c++) {
            topo.flood_class_nodes.push_back(addNode());
            classes.push_back(
                {(void *)&node_tags[topo.flood_class_nodes[c]], flood_sigs[c]});
        }

        for (int i = 0; i < kChunks; i++) {
            topo.chunk_nodes.push_back(addNode());
        }
        for (int i = 0; i < 32; i++) {
            topo.flood_nodes.push_back(addNode());
        }
        // Backlog volume: a 300-edge deep chain under one flood root.
        for (int i = 0; i < 300; i++) {
            topo.filler_nodes.push_back(addNode());
        }

        script = {
            // LEAK_BUFFER: the holder class's static field -> wrapper.
            {JVMTI_HEAP_REFERENCE_STATIC_FIELD, topo.holder_class_node,
             topo.wrapper_node, topo.wrapper_cls_idx},
            // The synchronized wrapper's mutex == this self-edge (round-16 fix-A shape: must not
            // demote the root-attached wrapper).
            {JVMTI_HEAP_REFERENCE_FIELD, topo.wrapper_node, topo.wrapper_node,
             topo.wrapper_cls_idx},
            // wrapper -> c -> chunks.
            {JVMTI_HEAP_REFERENCE_FIELD, topo.wrapper_node, topo.list_node,
             topo.list_cls_idx},
        };
        for (int i = 0; i < kChunks; i++) {
            script.push_back({JVMTI_HEAP_REFERENCE_FIELD, topo.list_node,
                              topo.chunk_nodes[i], topo.leak_cls_idx});
        }
        // Flood volume: each flood class holds 16 statics.
        for (int c = 0; c < 2; c++) {
            for (int i = 0; i < 16; i++) {
                script.push_back({JVMTI_HEAP_REFERENCE_STATIC_FIELD,
                                  topo.flood_class_nodes[c],
                                  topo.flood_nodes[16 * c + i],
                                  topo.leak_cls_idx /* any class; volume only */});
            }
        }
        // The filler chain hangs off flood node 0 (already a static anchor).
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, topo.flood_nodes[0],
                          topo.filler_nodes[0], topo.leak_cls_idx});
        for (int i = 0; i + 1 < (int)topo.filler_nodes.size(); i++) {
            script.push_back({JVMTI_HEAP_REFERENCE_FIELD,
                              topo.filler_nodes[i], topo.filler_nodes[i + 1],
                              topo.leak_cls_idx});
        }
        reseedChunkLeakTags(topo);
        return topo;
    }

    // Leak tags model the poll's tagLeakInstances() assignment (the pod re-tags within minutes of
    // every restart - the verify-not-retag state machine); the walk's leak-tag interception path
    // consumes them for real from the live node tags.
    void reseedChunkLeakTags(const PodTopology &topo) {
        for (int i = 0; i < (int)topo.chunk_nodes.size(); i++) {
            jlong leak_tag = 1073741824LL + 100 + i;
            node_tags[topo.chunk_nodes[i]] = leak_tag;
            tags_ever_assigned[topo.chunk_nodes[i]] = leak_tag;
        }
    }

    // Resolves the leak class's tracker-side klass id from the classTags table via the SAME tag
    // value the mock passes as the chunk edges' class_tag (tags[klass_ptr] - the sweep's negative
    // class tag, set during phase 1's static sweep).
    u32 resolveLeakKlassId(const PodTopology &topo) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        EXPECT_GT(ReferenceChainsTestAccessor::passesRunForTest(), 0)
            << "phase-1 pass never ran";
        jlong class_tag = tags[classes[topo.leak_cls_idx].klass];
        EXPECT_LT(class_tag, 0) << "leak class never sweep-tagged (class_tag="
                                << class_tag << ")";
        return tracker->classTags()->resolve(class_tag);
    }

    // Seeds the leak-side liveness (population growth + qualifying tid + representative = the first
    // chunk), mirroring PollWatchedTargetsTest::seedGrowingCandidate.
    void seedLeakLiveness(u32 klass_id, const PodTopology &topo) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, klass_id, (jweak)&node_tags[topo.chunk_nodes[0]]);
        // The representative's GetTag() identity: the mock tags map is keyed by object pointer;
        // getTag(rep) must report the rep's leak tag (the reseed in
        // reseedChunkLeakTags() above made node_tags hold it - chunk_leak_tags
        // itself is not kept).
        tags[&node_tags[topo.chunk_nodes[0]]] =
            node_tags[topo.chunk_nodes[0]];
        ASSERT_NE(0, tags[&node_tags[topo.chunk_nodes[0]]])
            << "representative's leak tag missing - L1/L2 assertions below "
               "would silently test an untagged representative";
    }

    // One threadLoop iteration, fake clock: the exact body order from
    // ReferenceChainTracker::threadLoop() (shouldRunPass -> runPass -> pollWatchedTargets, poll
    // unconditional).
    bool drivePodCycle(u64 &fake_now) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        bool should_run = tracker->shouldRunPassForTest(fake_now);
        if (should_run) {
            bool truncated = false;
            tracker->runPass(&mock_jvmti, &mock_jni, &truncated);
        }
        tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
        fake_now += kCycleNs;
        return should_run;
    }

    // Seeds a throwaway candidate klass (NO instances, never matches any real class) whose only job
    // is arming the leak signal so the phase-1 pass runs: the dormancy invariant (L8) proved
    // shouldRunPass stays false without a candidate, and the klass-id resolution needs a pass.
    void seedThrowawayLiveness(u32 klass_id) {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                klass_id, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                klass_id, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, klass_id, (jweak)0xBADC0DE);
    }

    // Two-phase pod bring-up. Phase 1: a throwaway candidate arms the leak signal so cycle 1's pass
    // runs - the sweep tags the classes and the walk admits the wrapper subtree, which makes the
    // leak class's tracker-side klass id resolvable (the only reliable source of the id is the
    // system's own resolve() over a real frontier entry).
    void bringUpPod(const PodTopology &topo, u32 &leak_klass_id_out,
                    u64 &fake_now) {
        ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
        // Seed the fake clock from the REAL monotonic clock: the pain budgets' _last_update_ns is
        // OS::nanotime()-based, so a fake epoch starting at ~0 sits before every budget's
        // initialization and canStartNow() blocks every pass (the dormancy test passes either way -
        // no passes at all - so only the pass-running tests caught this).
        fake_now = OS::nanotime();
        resetLivenessForPod();
        seedThrowawayLiveness(/*klass_id=*/999);
        // The candidate arms in the POLL, which runs after shouldRunPass in each cycle - so the
        // first cycle only arms, and a pass actually runs one cycle later.
        bool ran = false;
        for (int i = 0; i < 6 && !ran; i++) {
            ran = drivePodCycle(fake_now);
        }
        leak_klass_id_out = resolveLeakKlassId(topo);
        LivenessTracker::instance()->klassPopulationResetForTest();
        ReferenceChainsTestAccessor::restartSearchForTest();
        reseedChunkLeakTags(topo);
        seedLeakLiveness(leak_klass_id_out, topo);
        // Poll once BEFORE the first pass of the new search: the candidate slot registers in the
        // poll, and the pass's admission auto-mark requires the slot to exist
        // (heapReferenceCallback's auto-mark guards on _candidate_count > 0).
        tracker->pollWatchedTargets(&mock_jvmti, &mock_jni);
    }

    // Captures stdout per distinct ReferenceChainTracker/LivenessTracker line prefix (L4: the
    // log-budget invariant - the round-15 800k/min flood and the round-18 tick stragglers become
    // assertion failures).
    struct StdoutCapture {
        int saved_fd = -1;
        int tmp_fd = -1;
        char path[64] = {0};
        bool done = false;
        StdoutCapture() {
            snprintf(path, sizeof(path), "/tmp/podjar_stdout_XXXXXX");
            tmp_fd = mkstemp(path);
            fflush(stdout);
            saved_fd = dup(1);
            dup2(tmp_fd, 1);
        }
        std::map<std::string, int> perPrefixCounts() {
            if (done) {
                return {};
            }
            done = true;
            fflush(stdout);
            dup2(saved_fd, 1);
            close(saved_fd);
            saved_fd = -1;
            lseek(tmp_fd, 0, SEEK_SET);
            std::map<std::string, int> counts;
            FILE *f = fdopen(tmp_fd, "r");
            char line[512];
            while (fgets(line, sizeof(line), f)) {
                char cls[96], fn[96];
                if (sscanf(line, "[TEST::INFO] %95[^:]::%95[a-zA-Z]", cls,
                           fn) == 2) {
                    counts[std::string(cls) + "::" + fn]++;
                }
            }
            fclose(f);
            unlink(path);
            tmp_fd = -1;
            return counts;
        }
    };
};

TEST_F(PodInAJarTest, SystemLivenessLeakChainsBuildAndCanaryResolves) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);

    int cycles_run = 0;
    while (cycles_run < 120 &&
           ReferenceChainsTestAccessor::resolvedChainCountForTest() <
               (size_t)kChunks &&
           ReferenceChainsTestAccessor::searchStateForTest() ==
               SearchState::RUNNING) {
        drivePodCycle(fake_now);
        cycles_run++;
    }

    // L1: every leak-tagged chunk's tag appears as a cached chain target (leak-correlated events -
    // the pod's round-16 end-goal state).
    auto targets = ReferenceChainsTestAccessor::resolvedChainTargetsForTest();
    for (int i = 0; i < kChunks; i++) {
        jlong leak_tag = 1073741824LL + 100 + i;
        EXPECT_NE(std::find(targets.begin(), targets.end(), (u64)leak_tag),
                  targets.end())
            << "leak tag " << leak_tag
            << " never became a cached chain target after " << cycles_run
            << " cycles";
    }

    // L2: the canary resolved for the LEAK klass (found bit set on its slot - the round-19
    // criterion; fails on any pre-788d7b2a7 build).
    int leak_slot = -1;
    for (int s2 = 0; s2 < ReferenceChainsTestAccessor::candidateCountForTest();
         s2++) {
        if (ReferenceChainsTestAccessor::candidateKlassIdForTest(s2) ==
            leak_klass_id) {
            leak_slot = s2;
            break;
        }
    }
    ASSERT_GE(leak_slot, 0) << "leak klass never registered a candidate slot";
    EXPECT_TRUE(ReferenceChainsTestAccessor::candidateFoundBitsForTest() &
                (1ULL << leak_slot))
        << "leak candidate slot never marked found despite leak-tag chains";
}

TEST_F(PodInAJarTest, SystemSearchCompletesNaturally) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);

    int cycles = 0;
    while (cycles < 200 &&
           ReferenceChainsTestAccessor::searchStateForTest() ==
               SearchState::RUNNING) {
        drivePodCycle(fake_now);
        cycles++;
    }

    // L3: a healthy-topology search must end COMPLETED (all candidates found), never ABANDONED
    // (TTL/frontier-cap).
    EXPECT_EQ((u8)SearchState::COMPLETED,
              ReferenceChainsTestAccessor::searchStateForTest())
        << "search did not complete naturally within " << cycles
        << " cycles (state="
        << (int)ReferenceChainsTestAccessor::searchStateForTest() << ")";
    EXPECT_GT(ReferenceChainsTestAccessor::passesRunForTest(), 0);
}

TEST_F(PodInAJarTest, SystemRestartLeavesNothingBehind) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);
    for (int i = 0; i < 120 &&
                 ReferenceChainsTestAccessor::resolvedChainCountForTest() == 0;
         i++) {
        drivePodCycle(fake_now);
    }
    ASSERT_GT(ReferenceChainsTestAccessor::resolvedChainCountForTest(),
              (size_t)0);

    ReferenceChainsTestAccessor::restartSearchForTest();

    // L6: the restart contract as a test instead of discipline.
    EXPECT_GT(ReferenceChainsTestAccessor::resolvedChainCountForTest(),
              (size_t)0)
        << "resolved chains should persist across restarts by design";
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::staticAnchorFifoSizeForTest());
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::staticAnchorFreshQueueSizeForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::anchorIndexIsEmptyForTest());
    for (int s = 0; s < 5; s++) {
        EXPECT_EQ(0,
                  ReferenceChainsTestAccessor::candidateDiscoveredCountForTest(s))
            << "discovered slot " << s << " survived restartSearch()";
    }
}

TEST_F(PodInAJarTest, TopologyCapacityContractStaticAdmits) {
    // The topology-builder capacity contract as a regression: the FULL buildLeakPod topology + one
    // direct pass must admit the wrapper static (and with it the whole leak subtree).
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_GT(tags_ever_assigned[topo.wrapper_node], 0)
        << "wrapper static never admitted (holder_cls_tag="
        << node_tags[topo.holder_class_node]
        << " sweep_gate=" << ReferenceChainsTestAccessor::sweepGateStaticCountForTest()
        << "/" << ReferenceChainsTestAccessor::sweepGateResolvedCountForTest()
        << ")";

    tracker->stop();
}

TEST_F(PodInAJarTest, SystemHealthyAppIsDormant) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // L8: the accidental 3h pod control, encoded - a heap with no leak candidates must produce ZERO
    // searches (the candidate/generations gate holds the machinery dormant on a healthy app).
    PodTopology topo = buildLeakPod();
    // No seedLeakLiveness(): no candidate ever qualifies. bringUpPod is also skipped - it seeds
    // liveness; drive raw cycles instead.
    (void)topo;
    resetLivenessForPod();
    u64 fake_now = OS::nanotime();
    for (int i = 0; i < 20; i++) {
        drivePodCycle(fake_now);
    }
    EXPECT_EQ(0, ReferenceChainsTestAccessor::passesRunForTest())
        << "searches ran on a healthy (candidate-less) app";
    EXPECT_EQ((size_t)0,
              ReferenceChainsTestAccessor::resolvedChainCountForTest());
}

TEST_F(PodInAJarTest, SystemLogBudgetPerPass) {
#ifndef DEBUG
    // The gtest binary compiles the main sources WITHOUT DEBUG (round-16 lesson: TEST_LOG is a
    // no-op here) - the log-budget invariant can only run in a DEBUG-built test binary.
    GTEST_SKIP() << "log budget needs a DEBUG-built gtest binary";
#else
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=10"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    PodTopology topo = buildLeakPod();
    u32 leak_klass_id;
    u64 fake_now;
    bringUpPod(topo, leak_klass_id, fake_now);
    for (int i = 0; i < 3; i++) {
        drivePodCycle(fake_now);
    }

    // L4: capture one full cycle (pass + poll) and bound every distinct line shape.
    StdoutCapture capture;
    drivePodCycle(fake_now);
    auto counts = capture.perPrefixCounts();
    ASSERT_FALSE(counts.empty()) << "no diagnostics captured at level 2";
    for (const auto &kv : counts) {
        EXPECT_LE(kv.second, 300) << "log line shape '" << kv.first
                                  << "' fired " << kv.second
                                  << " times in one pass+poll cycle";
    }
#endif
}

