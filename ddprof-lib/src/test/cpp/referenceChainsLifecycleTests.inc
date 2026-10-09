
// ---------------------------------------------------------------------------
// Lifecycle churn (C4): stop/restart-shaped interleavings against an in-flight
// BFS pass. The real BFS thread cannot run here (threadLoop()'s
// VM::attachThread() dereferences VM::_vm unconditionally and the gtest binary
// has no JVM), so a test thread stands in for it by calling runPass() directly
// - the same entry point threadLoop() drives - and a second thread replays
// stopThread()'s observable part: the abort request an in-flight pass honors
// at its next walk callback (setAbortPassRequestedForTest()), held until the
// pass boundary the real pthread_join() would provide. GC callbacks run
// concurrently the way JVMTI delivers them in production: on their own
// thread, at any point relative to the pass.
//
// Deliberately NOT exercised here: stop()/start() racing a pass. Profiler
// never overlaps them (Profiler::stop() joins the BFS thread before start()
// can run again), so such a race would be a non-production shape whose
// findings could not be actioned.
//
// Invariants (beyond TSan/ASan cleanliness):
//   I1. runPass() always returns (an abort request never wedges the walk) and
//       a restarted search starts from zeroed accounting - passes_run,
//       _leak_tags_assigned/_leak_tags_resolved, and the frontier table's
//       published size are all reset by restartSearch() (referenceChains.cpp's
//       restart reset sites).
//   I2. The recording boundary (stop()/start()) clears the previous
//       recording's resolved chains - no stale chain survives into the next
//       recording's accounting.
//   I3. GCCallbackGuard reentrancy: GarbageCollectionStart/Finish running
//       concurrently with passes never trips the !t_inGCCallback asserts on
//       tagObject()/getTag()/clearTag() - i.e. the GC path itself makes no
//       JVMTI Heap-category calls (a DEBUG-build abort here is the detector).
//   I4. GC epochs stay monotone and start-ordered: gcStartEpoch() never lags
//       gcFinishEpoch(), and both only advance.
// ---------------------------------------------------------------------------

class ReferenceChainsLifecycleTest : public ::testing::Test,
                                     public ReferenceChainsMockHeap {
protected:
    void SetUp() override { setUp(); }
    void TearDown() override { tearDown(); }
};

TEST_F(ReferenceChainsLifecycleTest, ChurnDuringConcurrentPassesStaysConsistent) {
    Arguments args;
    // budget=2 with a first-pass budget of 2 keeps every search multi-pass
    // (the graph does not fit in one pass's expand budget), so passes are
    // actually in flight while the churn threads run.
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=64:budget=2:firstpassbudget=2"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A chain deep enough that budget=2 expansion takes several passes, with
    // a class-tagged holder so the static-field sweep has traffic too.
    int nodes[8];
    for (int i = 0; i < 8; i++) {
        nodes[i] = addNode();
    }
    addClass((void *)(uintptr_t)0x3000, "Lcom/rc/churn/Holder;");
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[0], nodes[1], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[1], nodes[2], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[2], nodes[3], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[3], nodes[4], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[4], nodes[5], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[5], nodes[6], -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodes[6], nodes[7], -1},
    };

    constexpr int kMaxSearches = 40;
    // Hard bound on runPass() calls so a wedged walk cannot hang the test:
    // the walk itself is what I1 asserts about, and a hang fails the test via
    // the harness timeout either way.
    constexpr int kMaxPasses = 2000;
    constexpr int kGcCycles = 200;
    constexpr int kAbortCycles = 30;

    std::atomic<bool> stop_flag{false};
    std::atomic<bool> pass_done{false};
    std::atomic<int> restarts{0};
    std::atomic<int> aborted_passes{0};
    // Pass counter shared with the abort thread is not needed for the handshake (that one waits
    // on aborted_passes); this one only carries the kMaxPasses wedge bound across the lambda.
    std::atomic<int> total_passes{0};

    u64 gc_start_before = tracker->gcStartEpoch();
    u64 gc_finish_before = tracker->gcFinishEpoch();
    // Opened by the abort thread right after its first flag store; the pass thread waits for it
    // before its first pass. Without this, a fast runner can push the pass thread through all
    // kMaxSearches before the abort thread's first store lands (the CI failure mode): the
    // pass thread then exits with pass_done set, every window short-circuits, and the "abort
    // was exercised" guard fails with zero overlap despite no defect. With it, pass 1 always
    // runs under an open window, so at least one post-pass read observes the request by
    // construction.
    std::atomic<bool> first_window_open{false};

    std::thread pass_thread([&] {
        // Deterministic window 1: do not start passes until the abort thread's first store is
        // visible (see first_window_open's comment). Bounded so a dead abort thread cannot hang
        // the test.
        int wait_spins = 0;
        while (!first_window_open.load(std::memory_order_relaxed) && wait_spins < 1000) {
            usleep(100);
            wait_spins++;
        }
        for (int searches = 0;
             searches < kMaxSearches &&
             total_passes.load(std::memory_order_relaxed) < kMaxPasses &&
             !stop_flag.load(std::memory_order_relaxed);
             /* advanced by the restart below */) {
            total_passes.fetch_add(1, std::memory_order_relaxed);
            bool truncated = true;
            // I1: always returns - an abort request makes the walk give up at
            // its next callback, never wedges. The abort thread holds requests
            // for ~1ms at a time, so requests land mid-walk and between passes
            // alike, the way a real stopThread() can fire at any point.
            bool ok = tracker->runPass(&mock_jvmti, &mock_jni, &truncated);
            if (!ok) {
                // Disabled/no-frontier early exit - nothing sensible is
                // running anymore; stop churning.
                stop_flag.store(true, std::memory_order_relaxed);
                break;
            }
            // The request is held far longer than one pass, so a read here is
            // true iff this pass ran under an abort request - and every
            // callback batch after the set point returned JVMTI_VISIT_ABORT,
            // i.e. the walk really was cut short.
            if (ReferenceChainsTestAccessor::abortPassRequested()) {
                aborted_passes.fetch_add(1, std::memory_order_relaxed);
            }
            u8 state = ReferenceChainsTestAccessor::searchStateForTest();
            if (state == SearchState::RUNNING) {
                continue;
            }
            // Terminal outcome. runPass()'s terminal branch retries the tag
            // release on the NEXT call - mirror threadLoop()/shouldRunPass():
            // only restart once the release is confirmed.
            if (!ReferenceChainsTestAccessor::tagsReleased()) {
                bool release_ok =
                    tracker->runPass(&mock_jvmti, &mock_jni, &truncated);
                total_passes.fetch_add(1, std::memory_order_relaxed);
                if (!release_ok || !ReferenceChainsTestAccessor::tagsReleased()) {
                    // Release still unconfirmed (a failing mock release is a
                    // dedicated test's business) - retry on the next spin.
                    continue;
                }
            }
            ReferenceChainsTestAccessor::restartSearchForTest();
            // I1: the restarted search starts from zeroed accounting. Only
            // this thread touches these fields between the restart and the
            // read, so the asserts are race-free by construction.
            EXPECT_EQ(0, ReferenceChainsTestAccessor::passesRunForTest());
            EXPECT_EQ(0, ReferenceChainsTestAccessor::leakTagsAssigned());
            EXPECT_EQ(0, ReferenceChainsTestAccessor::leakTagsResolved());
            EXPECT_EQ(0u, tracker->frontierTable()->size());
            restarts.fetch_add(1, std::memory_order_relaxed);
            searches++;
        }
        stop_flag.store(true, std::memory_order_relaxed);
        pass_done.store(true, std::memory_order_relaxed);
    });

    std::thread gc_thread([&] {
        // I3: each cycle holds GCCallbackGuard on THIS thread only. If the
        // implementation ever made a JVMTI Heap-category call from the guard,
        // the DEBUG asserts in tagObject()/getTag()/clearTag() would abort
        // the process while the pass thread walks concurrently.
        for (int i = 0; i < kGcCycles; i++) {
            ReferenceChainTracker::GarbageCollectionStart(nullptr);
            ReferenceChainTracker::GarbageCollectionFinish(nullptr);
        }
    });

    std::thread abort_thread([&] {
        // stopThread()'s observable part: the abort request, held until a pass's post-pass read
        // has actually observed it, then cleared the way startThread() does for the next
        // recording. The hold is a handshake on the pass thread's aborted_passes counter, not a
        // timed window: a fixed usleep hold made the flag/pass overlap a race - a fast runner
        // could push the pass thread through all kMaxSearches before the first window opened,
        // leaving aborted_passes at 0 and failing the "abort was exercised" guard below. With
        // the handshake, a window only closes once the guard's own counter moved, so the guard
        // holds by construction; the walk still runs - and gets cut short - under the flag the
        // same way it does under a real stopThread(). Bounded spin: a wedged walk (what the
        // kMaxPasses bound guards against) cannot hang the abort thread either - it gives up on
        // the window after the spin budget.
        for (int i = 0; i < kAbortCycles; i++) {
            if (pass_done.load(std::memory_order_relaxed)) {
                break;
            }
            int before = aborted_passes.load(std::memory_order_relaxed);
            ReferenceChainsTestAccessor::setAbortPassRequestedForTest(true);
            if (i == 0) {
                first_window_open.store(true, std::memory_order_relaxed);
            }
            int spins = 0;
            while (
                aborted_passes.load(std::memory_order_relaxed) == before &&
                !pass_done.load(std::memory_order_relaxed) && spins < 1000) {
                usleep(100);
                spins++;
            }
            ReferenceChainsTestAccessor::setAbortPassRequestedForTest(false);
            usleep(100);
        }
        ReferenceChainsTestAccessor::setAbortPassRequestedForTest(false);
        stop_flag.store(true, std::memory_order_relaxed);
    });

    pass_thread.join();
    gc_thread.join();
    abort_thread.join();

    // The abort path was actually exercised - otherwise this test proves
    // nothing about stop-during-pass. The request is held ~1ms per cycle
    // while the pass thread spins runPass(), so at least one pass must have
    // run with the request visible at its callback batches.
    EXPECT_GE(aborted_passes.load(), 1)
        << "abort request never coincided with a pass's callback batches";

    // I4: epochs only advanced, starts never lag finishes.
    EXPECT_GE(tracker->gcStartEpoch(), gc_start_before + 1);
    EXPECT_GE(tracker->gcFinishEpoch(), gc_finish_before + 1);
    EXPECT_GE(tracker->gcStartEpoch(), tracker->gcFinishEpoch());

    EXPECT_GE(restarts.load(), 1) << "no search ever reached a terminal outcome";

    // I2: the recording boundary clears the previous recording's resolved
    // chains. Inject one the way a finished search would have left it, then
    // run the stop()/start() cycle Profiler::stop()/start() performs.
    // (Single-threaded here - the churn threads are joined; start() racing a
    // pass is not a production shape.)
    ReferenceChainEvent event{};
    ReferenceChainsTestAccessor::cacheChain(77, event, 77, 123);
    ASSERT_EQ(1u, ReferenceChainsTestAccessor::resolvedChainCount());
    tracker->stop();
    tracker->start(args);
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::resolvedChainCount());

    // And the post-boundary tracker still walks: a fresh search completes
    // normally after all the churn. The churn threads may have exited with a
    // search mid-flight (tags still assigned) - the production recording
    // boundary tolerates exactly that (stop() does not release tags; the next
    // start()'s search does via its terminal gate) - but this test's mock
    // graph has no fresh search to hand them to, so reset to the standard
    // test isolation before driving the final search.
    ReferenceChainsTestAccessor::reset();
    ASSERT_FALSE(tracker->start(args));
    bool truncated = true;
    int passes_issued = 0;
    while (ReferenceChainsTestAccessor::searchStateForTest() == SearchState::RUNNING &&
           passes_issued < 64) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
        passes_issued++;
    }
    EXPECT_EQ(SearchState::COMPLETED, ReferenceChainsTestAccessor::searchStateForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());

    tracker->stop();
}

// ---------------------------------------------------------------------------
// Recording-boundary search teardown: Profiler::stop() -> ReferenceChainTracker::stop()
// must end an in-flight search (referenceChains.cpp's stop() teardown) so the next
// recording starts from a brand-new-search shape - a fresh TTL clock, no urgency
// carry-over, no candidate/discovered canary state, and a frontier that goes through the
// existing release-then-restart sequence (which resets its content) before any chain is
// built from it. Without the teardown, a search left RUNNING at the boundary continues
// into the next recording with a _search_start_ns that predates the stop (the stopped gap
// counts toward the new recording's TTL and can abandon "its" search with a spurious
// abandonment event), the previous recording's urgency episode stays latched, and frontier
// entries keep referrer_klass ids from a _class_map generation Profiler::start() has since
// wiped - so a chain built from a surviving entry names whichever class the new recording
// assigned that id to.
// ---------------------------------------------------------------------------

class ReferenceChainsRecordingBoundaryTest : public ::testing::Test,
                                            public ReferenceChainsMockHeap {
protected:
    void SetUp() override {
        setUp();
        // setUp() already resets the tracker; pin the LivenessTracker-facing knobs too (an
        // earlier suite in this binary may have left generations enabled, which would gate
        // shouldRunPass()'s restart on a seeded candidate).
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        LivenessTracker::instance()->classMapGenerationSetForTest(
            Profiler::instance()->classMap()->generation());
    }
    void TearDown() override {
        LivenessTracker::instance()->klassPopulationResetForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(false);
        tearDown();
    }
};

TEST_F(ReferenceChainsRecordingBoundaryTest,
       StopWithSearchInFlightEndsSearchAndClearsBoundaryState) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A search still in flight when the profiler stops: started, RUNNING, a TTL clock that
    // predates the stop, a latched urgency episode, and live canary candidate state.
    ReferenceChainsTestAccessor::setInFlightSearchForTest(1ULL << 40);
    ReferenceChainsTestAccessor::setUrgencyEpisodeForTest(/*latched=*/true, /*ticks=*/2,
                                                          /*spent=*/true);
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0x1);
    ReferenceChainsTestAccessor::setCandidateFrontierTagForTest(0, 42);

    tracker->stop();

    // The search was ended at the boundary - terminal with the recording-end reason - and no
    // abandonment event was enqueued for it: the recording ended, which is not a search-level
    // outcome the JFR stream should report.
    EXPECT_EQ(SearchState::ABANDONED,
              ReferenceChainsTestAccessor::searchStateForTest());
    EXPECT_EQ(SearchAbandonReason::RECORDING_END,
              ReferenceChainsTestAccessor::searchAbandonReasonForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingAbandonedEventCountForTest());
    // The TTL clock is zeroed: the stopped gap must not count toward the next recording's TTL.
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::searchStartNsForTest());
    // The urgency episode does not carry over into the next recording.
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentSearchSpentForTest());
    // The canary/discovered candidate state is cleared with the search that owned it.
    EXPECT_EQ(0, ReferenceChainsTestAccessor::candidateCountForTest());
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::candidateFoundBitsForTest());
    // Unchanged boundary shape: stop() still does not release the search's tags itself - the
    // next recording's first pass does, via the terminal gate.
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());
}

TEST_F(ReferenceChainsRecordingBoundaryTest,
       RestartAfterBoundaryReleasesTagsThenStartsFreshSearch) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // In-flight search at the boundary (no frontier entries, so the terminal gate's release
    // finds nothing to release and confirms immediately).
    ReferenceChainsTestAccessor::setInFlightSearchForTest(1ULL << 40);
    tracker->stop();
    ASSERT_EQ(SearchState::ABANDONED,
              ReferenceChainsTestAccessor::searchStateForTest());
    ASSERT_FALSE(ReferenceChainsTestAccessor::tagsReleased());

    // The next recording: the boundary state survives start() - the search stays terminal -
    // and the FIRST pass must go through the terminal gate (release the previous search's
    // tags before anything else), not continue the old search.
    ASSERT_FALSE(tracker->start(args));
    EXPECT_EQ(SearchState::ABANDONED,
              ReferenceChainsTestAccessor::searchStateForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(1000));
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni));
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    EXPECT_EQ(SearchState::ABANDONED,
              ReferenceChainsTestAccessor::searchStateForTest());
    // The release pass was the terminal no-op: no walk ran.
    EXPECT_EQ(0, tracker->passesRun());

    // With generations disabled (this fixture's SetUp), canAffordNewSearch() is unconditional,
    // so the next shouldRunPass() restarts the search - exactly like a brand-new tracker.
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2000));
    EXPECT_EQ(SearchState::RUNNING,
              ReferenceChainsTestAccessor::searchStateForTest());
    // Fresh TTL clock: the restarted search has not stamped its own start yet.
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::searchStartNsForTest());
    // No spurious abandonment event was emitted for a search the new recording never started.
    EXPECT_EQ(0u, ReferenceChainsTestAccessor::pendingAbandonedEventCountForTest());

    tracker->stop();
}

TEST_F(ReferenceChainsRecordingBoundaryTest, NoStaleFrontierIdsAfterRecordingBoundary) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // A frontier entry carrying a referrer_klass dict id from this recording's _class_map
    // generation, backed by a resolvable live tag (mock_GetObjectsWithTags resolves
    // node_tags entries).
    int node = addNode();
    node_tags[node] = 101;
    FrontierTable *frontier = tracker->frontierTable();
    ASSERT_TRUE(ReferenceChainsTestAccessor::insertFrontierEntry(
        frontier, 101, 0, 0, FrontierEntryState::FRONTIER, 0,
        /*referrer_klass=*/777));

    ReferenceChainsTestAccessor::setInFlightSearchForTest(1ULL << 40);
    tracker->stop();
    tracker->start(args);

    // The boundary state survives start(): the search stays terminal, so the next recording
    // is routed through release-then-restart instead of continuing a search whose frontier
    // still holds the wiped generation's ids.
    EXPECT_EQ(SearchState::ABANDONED,
              ReferenceChainsTestAccessor::searchStateForTest());

    // First pass: the terminal gate releases the previous search's live tag ...
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni));
    EXPECT_TRUE(ReferenceChainsTestAccessor::tagsReleased());
    // ... and the restart that follows resets the frontier content, so no chain can ever be
    // built from the previous _class_map generation's ids (which cannot be remapped: the
    // dictionary contents are gone and its id namespace restarts at 1).
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2000));
    EXPECT_EQ(SearchState::RUNNING,
              ReferenceChainsTestAccessor::searchStateForTest());
    EXPECT_EQ(0, tracker->frontierTable()->size());
    FrontierEntry entry{};
    EXPECT_FALSE(tracker->frontierTable()->lookup(101, &entry));

    tracker->stop();
}

// Profiler::stop() releases the tracker's per-recording state after the
// recording is written: every live search tag is cleared, the frontier table
// is freed, and the next start() rebuilds it for a brand-new search.
TEST_F(ReferenceChainsLifecycleTest, ReleaseFreesFrontierAndClearsSearchTags) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=2:firstpassbudget=2"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    // Deep enough that budget=2 leaves the search RUNNING, holding live tags,
    // after the first pass.
    int nodes[8];
    for (int i = 0; i < 8; i++) {
        nodes[i] = addNode();
    }
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1}};
    for (int i = 0; i + 1 < 8; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, nodes[i], nodes[i + 1], -1});
    }
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_EQ(SearchState::RUNNING, ReferenceChainsTestAccessor::searchStateForTest());
    int tagged = 0;
    for (int i = 0; i < 8; i++) {
        tagged += node_tags[nodes[i]] != 0;
    }
    ASSERT_GT(tagged, 0) << "the pass tagged nothing";

    tracker->stop();
    ASSERT_TRUE(tracker->release(&mock_jvmti, &mock_jni));
    EXPECT_EQ(nullptr, tracker->frontierTable());
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(0, node_tags[nodes[i]]) << "node " << i << " kept its search tag";
    }

    ASSERT_FALSE(tracker->start(args));
    EXPECT_NE(nullptr, tracker->frontierTable());
    EXPECT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    tracker->stop();
    EXPECT_TRUE(tracker->release(&mock_jvmti, &mock_jni));
}

// If the search tags cannot be confirmed cleared, release() keeps the frontier
// (it is what identifies the tags still out there) and reports failure.
TEST_F(ReferenceChainsLifecycleTest, ReleaseKeepsFrontierWhenTagsCannotBeCleared) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=2:firstpassbudget=2"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    int nodes[8];
    for (int i = 0; i < 8; i++) {
        nodes[i] = addNode();
    }
    script = {{JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1}};
    for (int i = 0; i + 1 < 8; i++) {
        script.push_back({JVMTI_HEAP_REFERENCE_FIELD, nodes[i], nodes[i + 1], -1});
    }
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_NE(0, node_tags[nodes[0]]);

    tracker->stop();
    fail_get_objects_with_tags = true;
    EXPECT_FALSE(tracker->release(&mock_jvmti, &mock_jni));
    EXPECT_NE(nullptr, tracker->frontierTable());
    EXPECT_FALSE(ReferenceChainsTestAccessor::tagsReleased());

    fail_get_objects_with_tags = false;
    EXPECT_TRUE(tracker->release(&mock_jvmti, &mock_jni));
    EXPECT_EQ(nullptr, tracker->frontierTable());
}
