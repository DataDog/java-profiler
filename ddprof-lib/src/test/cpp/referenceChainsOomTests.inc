
// ---------------------------------------------------------------------------
// OOM-ramp hysteresis (C5): isUrgent()'s latch/release machine and
// shouldRunPass()'s canary-refill raise, driven deterministically.
//
// No threads and no wall-clock dependence: the heap trajectory is faked by
// seeding LivenessTracker's usage rings with synthetic timestamps
// (heapFloorRecordForTest() + setMaxHeapBytesForTest() + setGcGenerationsForTest()),
// and both machines under test take their clock as an argument (isUrgent()
// reads live state; shouldRunPass(now_ns) takes now_ns). For a perfectly
// linear usage ramp of R bytes per 1s sample against max heap M, the
// projection (livenessTracker.cpp's regression form) reduces to
// secondsToOOM() == (M - last_used) / R, so each scenario seeds the exact
// urgency reading it wants and re-seeds between observations - the
// production loop re-reads the projection once per ~1s iteration the same
// way.
// ---------------------------------------------------------------------------

#include <algorithm>

#include "livenessTracker.h"

class OomUrgencyTest : public ::testing::Test {
protected:
    static constexpr u64 SEC_NS = 1000000000ULL;
    static constexpr u64 MiB = 1ULL << 20;
    static constexpr u64 MAX_HEAP = 1024 * MiB;
    // Bytes of heap growth per 1s sample - the projection's slope.
    static constexpr u64 RATE = MiB;

    void SetUp() override {
        ReferenceChainsTestAccessor::resetUrgencyForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);
        LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)MAX_HEAP);
#ifdef DEBUG
        // No real GC may interleave a sample into the ring while a scenario's
        // synthetic trajectory is mid-description.
        LivenessTracker::instance()->setHeapFloorRecordingForTest(false);
#endif
    }

    void TearDown() override {
        ReferenceChainsTestAccessor::resetUrgencyForTest();
        LivenessTracker::instance()->setMaxHeapBytesForTest(-1);
        LivenessTracker::instance()->setGcGenerationsForTest(false);
    }

    // Overwrites the whole usage ring with a linear ramp whose projection is
    // exactly `seconds` (see the file comment), and returns the projection
    // the tracker actually computes so every scenario can assert the driver
    // delivered what it intended. `flat` seeds a constant usage instead,
    // which secondsToOOM() reports as -1 (no rising trend - the
    // recent-half corroboration rejects the flat regression).
    double project(double seconds, bool flat = false) {
        u64 last_used = MAX_HEAP - (u64)(seconds * (double)RATE);
        for (int i = 0; i < 30; i++) {
            u64 used = flat ? MAX_HEAP / 2
                             : last_used - RATE * (u64)(29 - i);
            LivenessTracker::instance()->heapFloorRecordForTest(
                used, _clock_ns, 0);
            _clock_ns += SEC_NS;
        }
        return LivenessTracker::instance()->secondsToOOM();
    }

    u64 _clock_ns = 0;
};

// A projection crossing below OOM_URGENT_THRESHOLD_S latches urgency on the
// first sub-threshold observation; a far projection leaves it off.
TEST_F(OomUrgencyTest, LatchEngagesOnFirstSubThresholdObservation) {
    EXPECT_NEAR(project(700.0), 700.0, 1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());

    EXPECT_NEAR(project(299.0), 299.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// The hysteresis's core contract: once latched, projections oscillating
// anywhere in the [threshold, release) mid-band must not unlatch, and every
// mid-band observation resets the release-tick accumulator.
TEST_F(OomUrgencyTest, MidBandOscillationNeverFlaps) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());

    for (double s : {350.0, 599.0, 320.0, 599.0, 450.0, 599.0, 301.0, 599.0}) {
        ASSERT_NEAR(project(s), s, 1.0);
        EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest())
            << "flapped at projection " << s;
        EXPECT_EQ(0, ReferenceChainsTestAccessor::urgentReleaseTicksForTest())
            << "mid-band observation at " << s << " did not reset the ticks";
    }
}

// A single observation past the release bar must NOT release; only
// URGENT_RELEASE_CONSECUTIVE (5) consecutive clear observations do, and any
// mid-band reading in between restarts the count.
TEST_F(OomUrgencyTest, ReleaseRequiresConsecutiveClearObservations) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());

    // One clear reading, then mid-band noise: the count restarts.
    EXPECT_NEAR(project(700.0), 700.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_EQ(1, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    EXPECT_NEAR(project(350.0), 350.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());

    // Four consecutive clear readings hold the latch (ticks 1..4); the fifth
    // releases it.
    for (int i = 1; i <= 4; i++) {
        EXPECT_NEAR(project(700.0), 700.0, 1.0);
        EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest())
            << "released after only " << i << " clear observations";
        EXPECT_EQ(i, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    }
    EXPECT_NEAR(project(700.0), 700.0, 1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
}

// A negative projection (unknown / no rising trend - the flat-ring encoding
// secondsToOOM() uses) counts toward release exactly like a comfortably
// distant one: five consecutive unknowns release the latch.
TEST_F(OomUrgencyTest, UnknownProjectionCountsTowardRelease) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());

    for (int i = 1; i <= 4; i++) {
        EXPECT_DOUBLE_EQ(-1.0, project(0.0, /*flat=*/true));
        EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest())
            << "released after only " << i << " unknown observations";
        EXPECT_EQ(i, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    }
    EXPECT_DOUBLE_EQ(-1.0, project(0.0, /*flat=*/true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// After a release, mid-band projections stay unlatched (no residual state),
// and a fresh sub-threshold crossing re-latches with a fresh search
// entitlement (_urgent_search_spent reset).
TEST_F(OomUrgencyTest, RelatchAfterReleaseGetsFreshEntitlement) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    // Four clear readings hold the latch; the fifth releases it.
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(project(700.0), 700.0, 1.0);
        ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    }
    ASSERT_NEAR(project(700.0), 700.0, 1.0);
    ASSERT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());

    // Mid-band after release: nothing latches.
    EXPECT_NEAR(project(450.0), 450.0, 1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());

    // Re-cross the threshold: re-latch, and the entitlement to spend one
    // urgency-authorized search is restored.
    EXPECT_NEAR(project(299.0), 299.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentSearchSpentForTest());
}

// ---------------------------------------------------------------------------
// The canary-refill half: shouldRunPass() raises the CPU pain budget's
// refill rate CANARY_PAIN_BUDGET_REFILL_MULTIPLIER-fold exactly while a
// canary chase is open (candidates exist and not all are found), and puts it
// back when the chase closes. The backoff gate part of the same region is
// also asserted: it holds passes while the ramp is inactive and is bypassed
// while _oom_ramp_active (threadLoop() hands the ramp state in every
// iteration).
//
// start() enables the tracker's JVMTI events through VM::jvmti(), so the
// tests install a stub jvmtiEnv whose SetEventNotificationMode is a no-op -
// the same pattern as the mock harness fixtures in
// referenceChainsTrackerTests.inc.
// ---------------------------------------------------------------------------

class ReferenceChainsCanaryRefillTest : public ::testing::Test {
protected:
    void SetUp() override {
        jvmti_tbl = jvmtiInterface_1_{};
        jvmti_tbl.SetEventNotificationMode = &stub_SetEventNotificationMode;
        stub_env.functions = &jvmti_tbl;
        _orig_jvmti = VMTestAccessor::getJvmti();
        VMTestAccessor::setJvmti(&stub_env);
    }

    void TearDown() override { VMTestAccessor::setJvmti(_orig_jvmti); }

    static jvmtiError JNICALL
    stub_SetEventNotificationMode(jvmtiEnv *, jvmtiEventMode, jvmtiEvent,
                                  jobject, ...) {
        return JVMTI_ERROR_NONE;
    }

    jvmtiInterface_1_ jvmti_tbl;
    jvmtiEnv stub_env;
    jvmtiEnv *_orig_jvmti = nullptr;
};

TEST_F(ReferenceChainsCanaryRefillTest, RefillRaiseTracksOpenChaseExactly) {
    ReferenceChainsTestAccessor::reset();
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));

    // The refill logic lives past shouldRunPass()'s first-pass branch, so
    // mark the search started the way a first runPass() would have.
    ReferenceChainsTestAccessor::setSearchStartedForTest(true);
    double base = ReferenceChainsTestAccessor::basePainBudgetRefillRateForTest();
    EXPECT_DOUBLE_EQ(0.01, base); // default painbudget=1 percent

    u64 now = 1000;
    // No candidates: the applied rate is the configured one. The return
    // value here is cadence-dependent, not part of the invariant - only the
    // applied refill rate is.
    ReferenceChainsTestAccessor::shouldRunPass(now);
    EXPECT_DOUBLE_EQ(base, ReferenceChainsTestAccessor::cpuPainBudgetRefillRateForTest());

    // Chase opens (2 candidates, 1 found): the raise engages.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0x1);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(now));
    EXPECT_DOUBLE_EQ(std::min(base * ReferenceChainTracker::CANARY_PAIN_BUDGET_REFILL_MULTIPLIER, 1.0),
                     ReferenceChainsTestAccessor::cpuPainBudgetRefillRateForTest());

    // Repeated observations while the chase stays open keep it raised - the
    // raise is a property of the chase's state, not a one-shot edge.
    now += 1000000000ULL;
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(now));
    EXPECT_DOUBLE_EQ(std::min(base * ReferenceChainTracker::CANARY_PAIN_BUDGET_REFILL_MULTIPLIER, 1.0),
                     ReferenceChainsTestAccessor::cpuPainBudgetRefillRateForTest());

    // Chase closes (all candidates found): back to the configured rate.
    // (Return value again cadence-dependent - only the refill matters.)
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0x3);
    ReferenceChainsTestAccessor::shouldRunPass(now);
    EXPECT_DOUBLE_EQ(base, ReferenceChainsTestAccessor::cpuPainBudgetRefillRateForTest());

    tracker->stop();
    ReferenceChainsTestAccessor::reset();
}

TEST_F(ReferenceChainsCanaryRefillTest, BackoffGateHoldsUnlessOomRampActive) {
    ReferenceChainsTestAccessor::reset();
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setSearchStartedForTest(true);

    // Open chase with the backoff engaged: mult=4 x ema=100ms = 400ms
    // spacing, and only 50ms since the last pass.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0x1);
    u64 now = 6000000000ULL; // 6s into the test's synthetic clock
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        4, 100, now - 50 * 1000000ULL);

    ReferenceChainsTestAccessor::setOomRampActive(false);
    EXPECT_FALSE(ReferenceChainsTestAccessor::shouldRunPass(now));

    // The OOM ramp bypasses the gate (threadLoop() hands the ramp state in
    // before every decision): the same now_ns passes.
    ReferenceChainsTestAccessor::setOomRampActive(true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::shouldRunPass(now));

    ReferenceChainsTestAccessor::setOomRampActive(false);
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(1, 0, 0);
    ReferenceChainsTestAccessor::setCandidateCountForTest(0);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0);
    tracker->stop();
    ReferenceChainsTestAccessor::reset();
}
