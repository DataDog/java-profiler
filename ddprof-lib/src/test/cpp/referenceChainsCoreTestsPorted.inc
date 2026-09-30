// Individual regression tests ported verbatim from rc-3's split-TU families
// (referenceChainsTrackerTests.inc / referenceChainsBfsTests.inc /
// referenceChainsCoreTests.inc) - see referenceChains_ut.cpp's tail comment.

#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void removeKnobNode(const char *path) {
    struct stat st;
    if (lstat(path, &st) != 0) {
        return; // already gone
    }
    if (S_ISDIR(st.st_mode)) {
        rmdir(path);
    } else {
        unlink(path);
    }
}

static int countOpenFdsViaProc() {
    DIR *d = opendir("/proc/self/fd");
    if (d == nullptr) {
        return -1;
    }
    int n = 0;
    while (readdir(d) != nullptr) {
        ++n;
    }
    closedir(d);
    return n; // includes ".", ".." and the DIR's own descriptor; consistent across calls
}


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

TEST_F(ReferenceChainsBfsTest, CanaryStuckLimitDoublesPerRestartAndResetsOnCleanCompletion) {
    Arguments args;
    // The whole graph is exhausted within the first pass or two, so the frontier is stalled from
    // then on; the seeded watched-leak klass keeps the search from completing naturally, and the
    // seeded urgency suppresses the ordinary whole-graph stall branch (same frontier-stall
    // precondition, checked first - CANARY_STUCK is deliberately NOT urgent-suppressed, that is
    // the one window where it is reachable).
    ASSERT_FALSE(args.parse(
        "referencechains=true:hops=200:budget=1000:ttl=0:firstpassbudget=1000"));
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    ASSERT_FALSE(tracker->start(args));

    // CANARY_STUCK is only reachable while urgent: the ordinary whole-graph stall branch (same
    // frontier-stall precondition, checked first) is deliberately suppressed by isUrgent(), and
    // at the base limit both conditions would fire on the same pass. Seed a ~224s-to-OOM
    // projection the same way referenceChainsOomTests.inc does (linear ramp over synthetic
    // timestamps); restored at the end so later tests see default heap state.
    constexpr u64 SEC_NS = 1000000000ULL;
    constexpr u64 MiB = 1ULL << 20;
    constexpr u64 MAX_HEAP_TEST = 1024 * MiB;
    LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)MAX_HEAP_TEST);
    LivenessTracker::instance()->setGcGenerationsForTest(true);
#ifdef DEBUG
    LivenessTracker::instance()->setHeapFloorRecordingForTest(false);
#endif
    {
        u64 clock_ns = 0;
        u64 last_used = MAX_HEAP_TEST - 224 * MiB;
        for (int i = 0; i < 30; i++) {
            LivenessTracker::instance()->heapFloorRecordForTest(
                last_used - MiB * (u64)(29 - i), clock_ns, 0);
            clock_ns += SEC_NS;
        }
    }
    ASSERT_NEAR(LivenessTracker::instance()->secondsToOOM(), 224.0, 1.0);

    constexpr int kChainLength = 10;
    std::vector<int> nodes;
    for (int i = 0; i < kChainLength; i++) {
        nodes.push_back(addNode());
    }
    script.push_back({JVMTI_HEAP_REFERENCE_JNI_GLOBAL, -1, nodes[0], -1});
    for (int i = 1; i < kChainLength; i++) {
        script.push_back(
            {JVMTI_HEAP_REFERENCE_FIELD, nodes[i - 1], nodes[i], -1});
    }

    // A canary candidate this graph never contains, plus a watched-leak klass so the exhausted
    // frontier cannot complete the search out from under the CANARY_STUCK detector.
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({1});

    auto driveUntilTerminal = [this, &tracker]() -> int {
        bool truncated = true;
        int passes = 0;
        while (tracker->searchState() == SearchState::RUNNING && passes < 1000) {
            // EXPECT (not ASSERT): gtest assertion macros return void, which cannot appear in an
            // int-returning lambda; the state check below governs the loop either way.
            EXPECT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
            passes++;
        }
        return passes;
    };

    // Chase 1: abandoned by the CANARY_STUCK detector at the base limit.
    int chase1_passes = driveUntilTerminal();
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());
    EXPECT_EQ((u8)SearchAbandonReason::CANARY_STUCK,
              ReferenceChainsTestAccessor::searchAbandonReasonForTest());
    EXPECT_EQ(1, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest() >> 1);

    // Chase 2: a consecutive CANARY_STUCK restart keeps the escalation - the doubled limit must
    // give this chase strictly more passes than chase 1 got before abandoning it.
    ReferenceChainsTestAccessor::restartSearchForTest();
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({1});
    int chase2_passes = driveUntilTerminal();
    EXPECT_EQ(SearchState::ABANDONED, tracker->searchState());
    EXPECT_EQ((u8)SearchAbandonReason::CANARY_STUCK,
              ReferenceChainsTestAccessor::searchAbandonReasonForTest());
    EXPECT_EQ(2, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT << 2,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest());
    EXPECT_GT(chase2_passes, chase1_passes)
        << "the doubled limit must give the second chase more passes, not fewer";

    // A terminal outcome of a different kind resets the escalation: mark the candidate found, so
    // the next pass completes naturally and the fresh-chase limit goes back to the base.
    ReferenceChainsTestAccessor::restartSearchForTest();
    ReferenceChainsTestAccessor::setCandidateCountForTest(1);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(1);
    bool truncated = true;
    ASSERT_TRUE(tracker->runPass(&mock_jvmti, &mock_jni, &truncated));
    EXPECT_EQ(SearchState::COMPLETED, tracker->searchState());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::canaryStuckRestartCount());
    EXPECT_EQ(ReferenceChainTracker::CANARY_NO_PROGRESS_PASS_LIMIT,
              ReferenceChainsTestAccessor::canaryStuckPassLimitForTest());

    // This test deliberately reaches states the fixtures' SetUp reset() cannot fully neutralize
    // for a *latched* tracker: the urgency latch (isUrgent() keeps bypassing the candidate gate
    // until it releases on its own, breaking later tests' gate expectations under shuffled
    // order), the watched-leak-klass list (restartSearch() does not clear it), and whatever
    // candidate/found state the last runPass() left. Restore all of it - the same seam the
    // fixtures use in SetUp, applied to the leaked half.
    LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
    LivenessTracker::instance()->setGcGenerationsForTest(false);
    tracker->stop();
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ReferenceChainsTestAccessor::setWatchedLeakKlassIdsForTest({});
    ReferenceChainsTestAccessor::reset();
}

TEST(RcDebugLevelTest, ReadFileConcurrentSwapChaos) {
    // C3 knob-file swap chaos: a renamer thread cycles the knob path through
    // every node type it can legally take (valid regular, garbage regular,
    // symlink, directory, missing) while reader threads hammer
    // readRcDebugLevelFile(). The reader contract is deliberately weak -
    // "outcome is one of the documented values, and no descriptor is
    // leaked" - because the path can swap between the open() and any later
    // step inside the reader; the fstat-on-fd guard (see
    // readRcDebugLevelFile) is what keeps every intermediate observation
    // safe, and a swap racing the read must degrade to a normal rejection
    // (-1), never to a crash, a wrong parse, or a stuck descriptor.
    // A foreign-owner regular file (the remaining fstat branch) cannot be
    // staged from an unprivileged test process and stays covered by the
    // static rejection tests.
    char path[] = "/tmp/rc_dbg_chaos_XXXXXX";
    int fd = mkstemp(path);
    ASSERT_GE(fd, 0);
    ASSERT_GE(write(fd, "1\n", 2), 0);
    ASSERT_EQ(close(fd), 0);

    char stage[] = "/tmp/rc_dbg_stage_XXXXXX";
    int sfd = mkstemp(stage);
    ASSERT_GE(sfd, 0);
    ASSERT_GE(write(sfd, "2\n", 2), 0); // valid symlink target
    ASSERT_EQ(close(sfd), 0);
    char stageLink[] = "/tmp/rc_dbg_stage_link_XXXXXX";
    int lfd = mkstemp(stageLink);
    ASSERT_GE(lfd, 0);
    ASSERT_EQ(close(lfd), 0);
    ASSERT_EQ(unlink(stageLink), 0); // mkstemp created a file; the renamer stages a fresh symlink here per cycle
    char stageDir[] = "/tmp/rc_dbg_stage_dir_XXXXXX";
    ASSERT_NE(mkstemp(stageDir), -1);
    ASSERT_EQ(unlink(stageDir), 0); // the renamer stages a fresh directory here per cycle

    const int kSwapCycles = 1000; // per state; the renamer runs the full cycle set
    std::atomic<bool> stop{false};
    // seen[v + 1] counts outcomes: index 0 => -1 (missing/rejected), 1..3 => 0/1/2.
    std::atomic<int> seen[4] = {{0}, {0}, {0}, {0}};
    std::atomic<int> contractViolations{0};

    auto reader = [&]() {
        // Run until the renamer has completed its entire swap sequence (or a
        // runaway cap), so every staged state is guaranteed to be read by
        // someone while it exists.
        for (int i = 0; i < 100000000 && !stop.load(std::memory_order_relaxed); ++i) {
            int lvl = readRcDebugLevelFile(path);
            if (lvl < -1 || lvl > 2) {
                contractViolations.fetch_add(1, std::memory_order_relaxed);
                continue;
            }
            seen[lvl + 1].fetch_add(1, std::memory_order_relaxed);
        }
    };

    auto renamer = [&]() {
        // Staging nodes are re-created every cycle: rename(2) MOVES them onto
        // the knob path, so a one-time setup outside the loop would leave them
        // gone from cycle 1 on. Any staging failure ends the run early with
        // stop raised (so the readers do not spin to their cap) - the state
        // machine below is order-dependent and a failed transition would
        // corrupt every later one. GTEST_NONFATAL_FAILURE_ instead of ASSERT:
        // fatal gtest macros in a non-main thread have undefined flow.
        auto fail = [&](const char *what, int err) {
            GTEST_NONFATAL_FAILURE_((std::string(what) + " failed with errno=" +
                                     std::to_string(err)).c_str());
            stop.store(true, std::memory_order_relaxed);
        };
        for (int cycle = 0; cycle < kSwapCycles && !stop.load(std::memory_order_relaxed); ++cycle) {
            // valid regular file, fresh content each cycle
            unlink(stage);
            int wfd = open(stage, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            if (wfd < 0) {
                fail("open(stage)", errno);
                return;
            }
            const char *v = cycle % 2 == 0 ? "0\n" : "2\n";
            ssize_t ignored = write(wfd, v, 2);
            (void) ignored;
            close(wfd);
            removeKnobNode(path);
            if (rename(stage, path) != 0) {
                fail("rename valid", errno);
                return;
            }

            // garbage regular file
            unlink(stage);
            wfd = open(stage, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            if (wfd < 0) {
                fail("open(stage garbage)", errno);
                return;
            }
            ignored = write(wfd, "x", 1);
            (void) ignored;
            close(wfd);
            removeKnobNode(path);
            if (rename(stage, path) != 0) {
                fail("rename garbage", errno);
                return;
            }

            // symlink (must be rejected by O_NOFOLLOW)
            unlink(stageLink);
            if (symlink(stage, stageLink) != 0) {
                fail("symlink", errno);
                return;
            }
            removeKnobNode(path);
            if (rename(stageLink, path) != 0) {
                fail("rename symlink", errno);
                return;
            }

            // directory (open succeeds, fstat's !S_ISREG must reject)
            if (mkdir(stageDir, 0700) != 0 && errno != EEXIST) {
                fail("mkdir", errno);
                return;
            }
            removeKnobNode(path);
            if (rename(stageDir, path) != 0) {
                fail("rename dir", errno);
                return;
            }

            // missing
            removeKnobNode(path);
        }
        stop.store(true, std::memory_order_relaxed);
    };

    int fdsBefore = countOpenFdsViaProc();

    std::thread r1(reader), r2(reader), r3(reader);
    std::thread ren(renamer);
    ren.join();
    r1.join();
    r2.join();
    r3.join();

    removeKnobNode(path);
    unlink(stage);
    unlink(stageLink);
    removeKnobNode(stageDir);

    EXPECT_EQ(contractViolations.load(), 0) << "reader returned a value outside {-1,0,1,2}";
    // Non-vacuous pass: the readers must have both accepted at least one valid
    // level and exercised at least one rejection (-1). The readers only stop
    // after the renamer's full sequence, so a zero here means the test never
    // actually interleaved, not that the reader is correct.
    EXPECT_GT(seen[1].load() + seen[2].load() + seen[3].load(), 0) << "no valid level ever read";
    EXPECT_GT(seen[0].load(), 0) << "no rejection ever observed";
    int fdsAfter = countOpenFdsViaProc();
    if (fdsBefore >= 0 && fdsAfter >= 0) {
        // Leak direction is growth: every reader iteration would leak one
        // descriptor if any early-return path missed its close(). A benign
        // background close (e.g. an earlier suite's deferred cleanup) can
        // only lower the count, so equality is too strict.
        EXPECT_LE(fdsAfter, fdsBefore) << "descriptor leak: " << fdsBefore << " -> " << fdsAfter;
    }
}

TEST(RcDebugLevelTest, ReadFileRejectsSymlinkedOverride) {
    // The knob path lives under world-writable /tmp: a symlink planted by a
    // local user must not be followed (see readRcDebugLevelFile's lstat
    // guard) - only regular files owned by root or the current user are read.
    char target[] = "/tmp/rc_dbg_target_XXXXXX";
    int fd = mkstemp(target);
    ASSERT_GE(fd, 0);
    ASSERT_GE(write(fd, "2\n", 2), 0);
    close(fd);
    char link[] = "/tmp/rc_dbg_link_XXXXXX";
    int lfd = mkstemp(link);
    ASSERT_GE(lfd, 0);
    close(lfd);
    ASSERT_EQ(unlink(link), 0);
    ASSERT_EQ(symlink(target, link), 0);
    EXPECT_EQ(readRcDebugLevelFile(link), -1) // symlink itself: rejected
        << "symlinked override must not be followed";
    EXPECT_EQ(readRcDebugLevelFile(target), 2); // plain regular file: accepted
    unlink(link);
    unlink(target);
}
