/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

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
    // budget=2 keeps every search multi-pass (the graph does not fit in one
    // pass's expand budget), so passes are actually in flight while the churn
    // threads run. firstpassbudget must be ample so the root enumeration can
    // COMPLETE: under the R4/R5 termination law a search may not terminate
    // while roots remain unenumerated (_root_enum_incomplete), and with a
    // 2-unit enum budget every attempt truncates - no terminal outcome could
    // ever be reached (same adaptation as MultiPassResumptionReconstructsChain
    // AcrossPasses / ChainCompletesWithoutAbandonment in referenceChainsBfsTests.inc).
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=64:budget=2:firstpassbudget=1000"));
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

    // Consecutive RUNNING passes before the pass thread sleeps out the root-enumeration
    // interval floor (see the RUNNING branch below for why).
    constexpr int kRunningStreakBeforeEnumFloorWait = 200;
    int running_streak = 0;

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

    // No stop_flag: the pass loop's only exits are its own bounds (kMaxSearches/kMaxPasses) and
    // the !ok early-exit. The abort thread must not stop it - its 30 windows can complete faster
    // than the first search terminates (the abort flag's duty cycle truncates every walk in
    // between), and stopping then would end the churn with zero terminal outcomes.
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
             total_passes.load(std::memory_order_relaxed) < kMaxPasses;
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
                // R4/R5: while _root_enum_incomplete, a search may not terminate until a
                // root-enumeration attempt completes. The floor is wall-clock
                // (rootEnumMinIntervalNs()) and this loop drives runPass() back-to-back, so
                // once pass 1's window-aborted enumeration set the flag, only a later pass
                // run after the floor elapses can clear it. Sleep the floor out periodically
                // (only while no abort window is open) so the search can reach the terminal
                // outcome the restarts guard below requires; the abort windows exhaust after
                // kAbortCycles, so the retries are bounded.
                if (++running_streak >= kRunningStreakBeforeEnumFloorWait &&
                    !ReferenceChainsTestAccessor::abortPassRequested()) {
                    running_streak = 0;
                    usleep(ReferenceChainsTestAccessor::rootEnumMinIntervalNs() / 1000 + 1000);
                }
                continue;
            }
            running_streak = 0;
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

    // Under the non-TSan configs at least one search must reach a terminal
    // outcome - otherwise the churn exercised nothing. Under TSan the
    // instrumented passes plus the search's initial 1s cadence can burn the
    // whole kMaxPasses budget inside the first search (observed: 1 failure in
    // 50 shuffled repeats, no TSan report, no crash), so a budget exhaustion
    // there is a documented skip, not a product failure. The same budget
    // exhaustion happens on optimized non-TSan builds when the abort windows
    // dominate the pass reads (measured: 19/50 on release, 0/30 on debug):
    // passes run so fast relative to the windows that the root-enum retry is
    // starved for the whole budget and no search terminates. Skipping needs
    // the churn's own fingerprint - abort domination - so a genuine
    // never-terminates bug (low aborted_passes) still gates.
#if TSAN_ENABLED
    if (total_passes.load(std::memory_order_relaxed) >= kMaxPasses &&
        restarts.load(std::memory_order_relaxed) == 0) {
        GTEST_SKIP() << "TSan slowdown exhausted the pass budget before a search terminated";
    }
#else
    if (total_passes.load(std::memory_order_relaxed) >= kMaxPasses &&
        restarts.load(std::memory_order_relaxed) == 0 &&
        aborted_passes.load(std::memory_order_relaxed) >=
            total_passes.load(std::memory_order_relaxed) / 2) {
        GTEST_SKIP() << "abort windows starved the pass budget before any search terminated ("
                     << "passes=" << total_passes.load(std::memory_order_relaxed)
                     << " aborted=" << aborted_passes.load(std::memory_order_relaxed) << ")";
    }
#endif
    EXPECT_GE(restarts.load(), 1)
        << "no search ever reached a terminal outcome"
        << " (total_passes=" << total_passes.load(std::memory_order_relaxed)
        << " aborted_passes=" << aborted_passes.load(std::memory_order_relaxed)
        << " search_state=" << (int)ReferenceChainsTestAccessor::searchStateForTest()
        << " passes_run=" << ReferenceChainsTestAccessor::passesRunForTest()
        << " root_enum_last_ns=" << ReferenceChainsTestAccessor::rootEnumRawStateForTest().first
        << ")";

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
    ReferenceChainsTestAccessor::setUrgencyEpisodeForTest(/*latched=*/true, /*ticks=*/2);
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

    // With no leak-signal source (this fixture's SetUp), canAffordNewSearch() always refuses, so
    // the terminal search stays terminal. Arm the signal (generations tracking alone is a
    // sufficient source) AND seed a growing candidate: the restart gate requires both the signal
    // source and a live leak indication (hasLeakSignal()'s selectLeakCandidates() probe);
    // TearDown restores the no-signal state.
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    int fake_object_storage = 0;
    {
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                /*klass_id=*/1, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                /*klass_id=*/1, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, /*klass_id=*/1, (jweak)&fake_object_storage);
    }
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
    // dictionary contents are gone and its id namespace restarts at 1). Arm the leak signal AND
    // seed a growing candidate for the restart step only - the restart gate requires both the
    // signal source (generations or liveheap) and a live leak indication; the no-signal state
    // this fixture runs in would keep the search terminal. TearDown restores it.
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    {
        int fake_object_storage = 0;
        int slot;
        bool created;
        for (u16 i = 1; i <= 20; i++) {
            LivenessTracker::instance()->klassPopulationRecordForTest(
                /*klass_id=*/1, i, i, &slot, &created);
            LivenessTracker::instance()->tidTrendRecordForTest(
                /*klass_id=*/1, /*tid=*/4242, (u32)i, (u64)i);
        }
        LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
            nullptr, /*klass_id=*/1, (jweak)&fake_object_storage);
    }
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(2000));
    EXPECT_EQ(SearchState::RUNNING,
              ReferenceChainsTestAccessor::searchStateForTest());
    EXPECT_EQ(0, tracker->frontierTable()->size());
    FrontierEntry entry{};
    EXPECT_FALSE(tracker->frontierTable()->lookup(101, &entry));

    tracker->stop();
}

// ---------------------------------------------------------------------------------------------
// Anchor-observation journal lifecycle: lease ownership, epoch invalidation and the join gate.
// A scope is kept alive only around the traversal group it owns; scopes that outlive a lifecycle
// boundary below are deliberate stand-ins for a straggler holding a stale token.
// ---------------------------------------------------------------------------------------------

namespace {

using T9LAcc = ReferenceChainsTestAccessor;

// Restores the shared singleton/mock state on every exit, including a failed ASSERT.
struct T9LTestGuard {
    ReferenceChainsMockHeap &fixture;
    explicit T9LTestGuard(ReferenceChainsMockHeap &f) : fixture(f) {}
    ~T9LTestGuard() {
        T9LAcc::setAbortPassRequestedForTest(false);
#ifdef DEBUG
        T9LAcc::clearJoinResultForTest();
#endif
        fixture.jvmti_tbl.IterateOverReachableObjects =
            &ReferenceChainsMockHeap::mock_IterateOverReachableObjects;
        fixture.fail_get_objects_with_tags = false;
        ReferenceChainTracker::instance()->stop();
    }
};

// A pass context bound to a caller-owned scope, as every production traversal caller builds it.
struct T9LScopedPass {
    ReferenceChainAnchorObservationScope scope;
    ReferenceChainPassContext ctx;

    T9LScopedPass(ReferenceChainTracker *tracker, FrontierTable *frontier) : scope(tracker), ctx(scope) {
        ctx.tracker = tracker;
        ctx.frontier = frontier;
        ctx.hop_cap = 64;
        ctx.budget = 100000;
        ctx.edges_admitted = 0;
        ctx.truncated = false;
        ctx.frontier_cap_hit = false;
    }
};

constexpr jlong kT9LClassTag = -3501;

void t9lInsertRootAttachedDurable(FrontierTable *frontier, jlong tag) {
    ASSERT_TRUE(T9LAcc::insertFrontierEntry(frontier, tag, 0, 0, FrontierEntryState::FRONTIER,
                                            JVMTI_HEAP_REFERENCE_JNI_GLOBAL, 0, kT9LClassTag));
}

AnchorObservation t9lAtRiskRecord(jlong tag, u32 klass_id) {
    AnchorObservation record{};
    record.tag = tag;
    record.at_risk_klass_id = klass_id;
    record.actions = AnchorObservation::AT_RISK;
    return record;
}

AnchorObservation t9lReenlistRecord(jlong tag) {
    AnchorObservation record{};
    record.tag = tag;
    record.own_class_tag = kT9LClassTag;
    record.actions = AnchorObservation::REENLIST_ELIGIBLE;
    return record;
}

// Root enumeration whose first report is accepted, after which the stop request arrives (what
// stopThread()'s abort flag does to an in-flight pass) and the second report is refused.
struct T9LCooperativeStop {
    static inline jlong first_tag = 0;
    static inline jlong second_tag = 0;
    static inline int first_control = -1;
    static inline int second_control = -1;
    static inline jlong first_tag_after = 0;
    static inline jlong second_tag_after = 0;
};

jvmtiError JNICALL t9lCooperativeStopIterate(jvmtiEnv *, jvmtiHeapRootCallback root_cb,
                                             jvmtiStackReferenceCallback, jvmtiObjectReferenceCallback,
                                             const void *user_data) {
    void *ctx = const_cast<void *>(user_data);
    jlong first = T9LCooperativeStop::first_tag;
    T9LCooperativeStop::first_control = root_cb(JVMTI_HEAP_ROOT_JNI_GLOBAL, 0, 0, &first, ctx);
    T9LCooperativeStop::first_tag_after = first;
    T9LAcc::setAbortPassRequestedForTest(true);
    jlong second = T9LCooperativeStop::second_tag;
    T9LCooperativeStop::second_control = root_cb(JVMTI_HEAP_ROOT_JNI_GLOBAL, 0, 0, &second, ctx);
    T9LCooperativeStop::second_tag_after = second;
    return JVMTI_ERROR_NONE;
}

} // namespace

// Scopes overlapping the owner's group are non-owning: they cannot reserve, cannot latch overflow
// or a static retry on the owner's journal, cannot flush its records, and their destruction does
// not release the owner's lease.
TEST_F(ReferenceChainsBfsTest, OverlappingAnchorScopeCannotReserveOverflowFlushOrReleaseOwner) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);

    const u64 gen = T9LAcc::durableAnchorResweepGenForTest();
    {
        ReferenceChainAnchorObservationScope owner(tracker);
        ASSERT_TRUE(owner.ownsLease());
        {
            ReferenceChainAnchorObservationScope other(tracker);
            EXPECT_FALSE(other.ownsLease());
            {
                AnchorObservationReservation reservation = other.reserve();
                EXPECT_FALSE(reservation.held());
                reservation.commit(t9lAtRiskRecord(901, 7)); // a refused reservation records nothing
            }
            other.markOverflow(/*static_attachment=*/true);
            EXPECT_TRUE(other.observeReturn()) << "a non-owning scope has no journal: abort, don't lose";
            other.flush();
        }
        EXPECT_EQ(0u, T9LAcc::journalCountForTest());
        EXPECT_FALSE(owner.observeReturn()) << "the overlapping scope latched overflow on the owner";

        {
            AnchorObservationReservation reservation = owner.reserve();
            ASSERT_TRUE(reservation.held());
            reservation.commit(t9lAtRiskRecord(901, 7));
        }
        ASSERT_EQ(1u, T9LAcc::journalCountForTest());
        {
            // The owner's destructor-free lease is still the only one: a later overlapping scope
            // (after the earlier one was destroyed) is non-owning too, and flushing it replays nothing.
            ReferenceChainAnchorObservationScope later(tracker);
            EXPECT_FALSE(later.ownsLease()) << "destroying a non-owning scope released the owner's lease";
            later.flush();
        }
        EXPECT_EQ(1u, T9LAcc::journalCountForTest()) << "a non-owning flush consumed the owner's record";
        EXPECT_FALSE(T9LAcc::staticAnchorFifoContainsForTest(901));

        owner.flush();
        EXPECT_TRUE(T9LAcc::staticAnchorFifoContainsForTest(901));
        EXPECT_EQ(0u, T9LAcc::journalCountForTest());
    }
    EXPECT_EQ(gen, T9LAcc::durableAnchorResweepGenForTest())
        << "a non-owning markOverflow(static) must not request a resweep";
    ReferenceChainAnchorObservationScope next(tracker);
    EXPECT_TRUE(next.ownsLease()) << "the owner's destruction must release its lease";
}

// A stop()/start() cycle reusing numeric tag 1 invalidates every outstanding token: the stale
// scope's flush is discarded before any tag lookup (its positive, non-empty payload would index
// the NEW recording's tag 1), cannot touch the new owner's journal, and its destruction cannot
// release the new lease.
TEST_F(ReferenceChainsBfsTest, StaleAnchorScopeAfterStopStartCannotReplayOrReleaseNewLease) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);

    t9lInsertRootAttachedDurable(tracker->frontierTable(), 1);
    auto stale = std::make_unique<ReferenceChainAnchorObservationScope>(tracker);
    ASSERT_TRUE(stale->ownsLease());
    {
        AnchorObservationReservation r1 = stale->reserve();
        ASSERT_TRUE(r1.held());
        r1.commit(t9lReenlistRecord(1));
    }
    {
        AnchorObservationReservation r2 = stale->reserve();
        ASSERT_TRUE(r2.held());
        r2.commit(t9lAtRiskRecord(902, 3));
    }
    ASSERT_EQ(2u, T9LAcc::journalCountForTest());
    const u64 epoch_before = T9LAcc::journalEpochForTest();

    tracker->stop();
    ASSERT_GT(T9LAcc::journalEpochForTest(), epoch_before);
    EXPECT_EQ(0u, T9LAcc::journalCountForTest());
    ASSERT_FALSE(tracker->start(args));
    // The new recording reuses numeric tag 1 for a different object.
    t9lInsertRootAttachedDurable(tracker->frontierTable(), 1);
    EXPECT_FALSE(T9LAcc::anchorIndexContainsForTest(1));

    auto fresh = std::make_unique<ReferenceChainAnchorObservationScope>(tracker);
    ASSERT_TRUE(fresh->ownsLease()) << "the epoch bump must clear the stale lease";
    {
        AnchorObservationReservation reservation = fresh->reserve();
        ASSERT_TRUE(reservation.held());
        reservation.commit(t9lAtRiskRecord(903, 4));
    }
    ASSERT_EQ(1u, T9LAcc::journalCountForTest());

    {
        AnchorObservationReservation reservation = stale->reserve();
        EXPECT_FALSE(reservation.held());
    }
    stale->markOverflow(/*static_attachment=*/true);
    stale->flush();
    EXPECT_FALSE(T9LAcc::anchorIndexContainsForTest(1)) << "a stale payload was replayed";
    EXPECT_FALSE(T9LAcc::staticAnchorFifoContainsForTest(902));
    EXPECT_EQ(1u, T9LAcc::journalCountForTest()) << "the stale scope touched the new journal";
    EXPECT_FALSE(fresh->observeReturn());
    stale.reset(); // must not release the new owner's lease
    {
        ReferenceChainAnchorObservationScope overlapping(tracker);
        EXPECT_FALSE(overlapping.ownsLease()) << "a stale token released the new lease";
    }

    fresh->flush();
    EXPECT_TRUE(T9LAcc::staticAnchorFifoContainsForTest(903));
    EXPECT_FALSE(T9LAcc::staticAnchorFifoContainsForTest(902));
    EXPECT_FALSE(T9LAcc::anchorIndexContainsForTest(1));
}

// The accepted prefix is applied when a cooperative stop aborts the walk, and the refused report
// leaves its object untouched.
TEST_F(ReferenceChainsBfsTest, CooperativeStopAppliesAcceptedPrefixBeforePassReturns) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);

    const jlong leak_base = T9LAcc::leakTagBase();
    T9LCooperativeStop::first_tag = leak_base;
    T9LCooperativeStop::second_tag = leak_base + 1;
    jvmti_tbl.IterateOverReachableObjects = &t9lCooperativeStopIterate;
    T9LAcc::setRootEnumRawStateForTest(0, 0);

    bool truncated = false;
    tracker->runPass(&mock_jvmti, &mock_jni, &truncated);
    EXPECT_EQ((int)JVMTI_ITERATION_CONTINUE, T9LCooperativeStop::first_control);
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, T9LCooperativeStop::second_control);
    const jlong admitted = T9LCooperativeStop::first_tag_after;
    ASSERT_GT(admitted, 0);
    EXPECT_NE(leak_base, admitted) << "the accepted report must have converted its leak tag";
    EXPECT_EQ(leak_base + 1, T9LCooperativeStop::second_tag_after) << "the refused report was applied";
    EXPECT_TRUE(T9LAcc::anchorIndexContainsForTest(admitted))
        << "the accepted prefix was not flushed on the stop path";
    EXPECT_EQ(1u, T9LAcc::anchorIndexSizeForTest());
    EXPECT_EQ(0u, T9LAcc::journalCountForTest());
}

// JVMTI heap callbacks run on a thread other than the caller's (the VM thread). They only begin
// and commit records under the journal lock; the caller, blocked in the synchronous traversal,
// observes the return and drains.
TEST_F(ReferenceChainsBfsTest, AnchorCallbacksOnWorkerThreadOnlyRecordAndCallerFlushes) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);
    FrontierTable *frontier = tracker->frontierTable();

    const jlong tags[] = {11, 12, 13};
    for (jlong tag : tags) {
        t9lInsertRootAttachedDurable(frontier, tag);
    }
    {
        T9LScopedPass pass(tracker, frontier);
        int controls[3] = {-1, -1, -1};
        std::thread worker([&]() {
            for (int i = 0; i < 3; i++) {
                jlong tag = tags[i];
                controls[i] = T9LAcc::reportHeapRootForTest(JVMTI_HEAP_ROOT_JNI_GLOBAL,
                                                            kT9LClassTag, &tag, &pass.ctx);
            }
        });
        worker.join(); // the synchronous traversal returned
        for (int i = 0; i < 3; i++) {
            EXPECT_EQ((int)JVMTI_ITERATION_CONTINUE, controls[i]);
        }
        EXPECT_FALSE(pass.scope.observeReturn());
        EXPECT_EQ(3u, T9LAcc::journalCountForTest());
        EXPECT_EQ(0u, T9LAcc::anchorIndexSizeForTest()) << "a callback mutated the anchor index";
        pass.scope.flush();
        EXPECT_EQ(0u, T9LAcc::journalCountForTest());
        for (jlong tag : tags) {
            EXPECT_TRUE(T9LAcc::anchorIndexContainsForTest(tag));
        }
    }

    // A callback worker that outruns the capacity aborts at the first record that does not fit;
    // the caller sees the overflow after the join and the flush keeps the accepted prefix. The
    // reports are distinct unindexed roots: a re-report of the already-indexed tags above would
    // stage nothing (its replay would be a no-op) and never fill the journal.
    std::vector<jlong> fill_tags;
    for (u32 i = 0; i <= AnchorObservationBuffer::CAPACITY; i++) {
        fill_tags.push_back(100 + (jlong)i);
        t9lInsertRootAttachedDurable(frontier, fill_tags.back());
    }
    T9LScopedPass full(tracker, frontier);
    u32 accepted = 0;
    int last_control = -1;
    std::thread worker([&]() {
        for (u32 i = 0; i <= AnchorObservationBuffer::CAPACITY; i++) {
            jlong tag = fill_tags[i];
            last_control = T9LAcc::reportHeapRootForTest(JVMTI_HEAP_ROOT_JNI_GLOBAL, kT9LClassTag,
                                                         &tag, &full.ctx);
            if (last_control != JVMTI_ITERATION_CONTINUE) {
                break;
            }
            accepted++;
        }
    });
    worker.join();
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY, accepted);
    EXPECT_EQ((int)JVMTI_ITERATION_ABORT, last_control);
    EXPECT_TRUE(full.scope.observeReturn());
    EXPECT_TRUE(full.ctx.anchor_observation_overflow);
    EXPECT_EQ(AnchorObservationBuffer::CAPACITY, T9LAcc::journalCountForTest());
    full.scope.flush();
    EXPECT_EQ(0u, T9LAcc::journalCountForTest());
    EXPECT_FALSE(full.scope.observeReturn());
}

#ifdef DEBUG
// A failed pthread_join leaves the worker unjoined: start, recording-boundary teardown and the
// test reset all refuse to touch the journal a straggler could still hold, and a retry that
// succeeds lets them proceed.
TEST_F(ReferenceChainsBfsTest, StopThreadJoinFailureKeepsJournalAndRetrySucceeds) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);

    auto holder = std::make_unique<ReferenceChainAnchorObservationScope>(tracker);
    ASSERT_TRUE(holder->ownsLease());
    {
        AnchorObservationReservation reservation = holder->reserve();
        ASSERT_TRUE(reservation.held());
        reservation.commit(t9lAtRiskRecord(904, 5));
    }
    const u64 epoch = T9LAcc::journalEpochForTest();

    T9LAcc::setThreadUnjoinedForTest();
    T9LAcc::setJoinResultForTest(EBUSY);
    EXPECT_FALSE(tracker->stopThread());
    EXPECT_FALSE(T9LAcc::threadJoinedForTest());
    EXPECT_EQ(1, T9LAcc::joinCallCountForTest());

    EXPECT_TRUE((bool)tracker->start(args)) << "start() must refuse while a worker is unjoined";
    tracker->stop();
    tracker->resetSearchStateForTest(&mock_jvmti, &mock_jni);
    EXPECT_EQ(2, T9LAcc::joinCallCountForTest()) << "the reset retried the join once and gave up";
    EXPECT_EQ(epoch, T9LAcc::journalEpochForTest());
    EXPECT_EQ(1u, T9LAcc::journalCountForTest()) << "teardown cleared a journal the worker could hold";
    EXPECT_FALSE(T9LAcc::threadJoinedForTest());

    T9LAcc::setJoinResultForTest(0);
    EXPECT_TRUE(tracker->stopThread());
    EXPECT_TRUE(T9LAcc::threadJoinedForTest());
    EXPECT_EQ(1, T9LAcc::joinCallCountForTest());
    EXPECT_TRUE(tracker->stopThread()) << "an already joined worker needs no second join";
    EXPECT_EQ(1, T9LAcc::joinCallCountForTest());

    tracker->stop();
    EXPECT_GT(T9LAcc::journalEpochForTest(), epoch);
    EXPECT_EQ(0u, T9LAcc::journalCountForTest());
    holder->flush(); // stale token: discarded
    EXPECT_FALSE(T9LAcc::staticAnchorFifoContainsForTest(904));
    holder.reset();
    EXPECT_FALSE((bool)tracker->start(args));
}
#endif

// While a failed tag release keeps the abandoned search's tags live, nothing resets the journal;
// the restart that follows the confirmed release does, so no earlier scope can replay against the
// reused tags.
TEST_F(ReferenceChainsRecordingBoundaryTest,
       TagReleaseRetryKeepsJournalUntilRestartThenInvalidatesStaleScope) {
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true:hops=64:budget=1000:framecap=1:ttl=0"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));
    T9LTestGuard guard(*this);

    int nodeA = addNode();
    script = {
        {JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodeA, -1},
        {JVMTI_HEAP_REFERENCE_FIELD, nodeA, nodeA, -1},
    };
    fail_get_objects_with_tags = true;
    bool truncated = false;
    for (int i = 0; i < ReferenceChainTracker::NO_PROGRESS_PASS_LIMIT + 2; i++) {
        ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    }
    ASSERT_EQ(SearchState::ABANDONED, tracker->searchState());
    ASSERT_FALSE(T9LAcc::tagsReleased());
    const u64 epoch = T9LAcc::journalEpochForTest();

    auto straggler = std::make_unique<ReferenceChainAnchorObservationScope>(tracker);
    ASSERT_TRUE(straggler->ownsLease());
    {
        AnchorObservationReservation reservation = straggler->reserve();
        ASSERT_TRUE(reservation.held());
        reservation.commit(t9lReenlistRecord(1));
    }
    // Failed release retries: no restart, so no journal reset.
    EXPECT_TRUE(T9LAcc::shouldRunPass(1));
    EXPECT_EQ(epoch, T9LAcc::journalEpochForTest());
    EXPECT_EQ(1u, T9LAcc::journalCountForTest());
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());

    // Release succeeds; the restart gate then resets the search and with it the journal epoch.
    fail_get_objects_with_tags = false;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    ASSERT_TRUE(T9LAcc::tagsReleased());
    // The restart gate also needs a leak-signal source and a growing candidate (this fixture's
    // TearDown restores the no-signal state).
    LivenessTracker::instance()->setGcGenerationsForTest(true);
    int fake_object_storage = 0;
    for (u16 i = 1; i <= 20; i++) {
        int slot;
        bool created;
        LivenessTracker::instance()->klassPopulationRecordForTest(/*klass_id=*/1, i, i, &slot, &created);
        LivenessTracker::instance()->tidTrendRecordForTest(/*klass_id=*/1, /*tid=*/4242, (u32)i, (u64)i);
    }
    LivenessTracker::instance()->klassPopulationSetRepresentativeForTest(
        nullptr, /*klass_id=*/1, (jweak)&fake_object_storage);
    EXPECT_TRUE(T9LAcc::shouldRunPass(OS::nanotime() + 3600ULL * 1000000000ULL));
    ASSERT_EQ(SearchState::RUNNING, tracker->searchState()) << "the restart gate did not fire";
    EXPECT_GT(T9LAcc::journalEpochForTest(), epoch);
    EXPECT_EQ(0u, T9LAcc::journalCountForTest());

    // The reused numeric tag 1 now names a new entry; the straggler's stale record must not index it.
    t9lInsertRootAttachedDurable(tracker->frontierTable(), 1);
    straggler->flush();
    EXPECT_FALSE(T9LAcc::anchorIndexContainsForTest(1));
    straggler.reset();
    ReferenceChainAnchorObservationScope next(tracker);
    EXPECT_TRUE(next.ownsLease());
}
