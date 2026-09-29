
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
    std::atomic<int> restarts{0};
    std::atomic<int> aborted_passes{0};

    u64 gc_start_before = tracker->gcStartEpoch();
    u64 gc_finish_before = tracker->gcFinishEpoch();

    std::thread pass_thread([&] {
        int total_passes = 0;
        for (int searches = 0;
             searches < kMaxSearches && total_passes < kMaxPasses;
             /* advanced by the restart below */) {
            total_passes++;
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
                total_passes++;
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
        // stopThread()'s observable part: the abort request, held long enough
        // that passes running concurrently observe it at their next callback
        // batch, then cleared the way startThread() does for the next
        // recording. Timed holds instead of a pass-boundary handshake: a
        // real stopThread() fires at an arbitrary moment, and holding the
        // request for a fixed window guarantees the request/walk overlap the
        // handshake could miss when passes complete in microseconds.
        for (int i = 0; i < kAbortCycles; i++) {
            ReferenceChainsTestAccessor::setAbortPassRequestedForTest(true);
            usleep(1000);
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
