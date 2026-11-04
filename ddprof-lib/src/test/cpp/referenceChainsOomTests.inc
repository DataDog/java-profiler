/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// ---------------------------------------------------------------------------
// OOM-ramp hysteresis (C5): isUrgent()'s latch/release machine and
// shouldRunPass()'s canary-refill raise, driven deterministically.
//
// No threads: the heap trajectory is faked by
// seeding LivenessTracker's usage rings with synthetic timestamps
// (heapFloorRecordForTest() + setMaxHeapBytesForTest() + setGcGenerationsForTest()),
// and both machines under test take their clock as an argument (isUrgent()
// reads live state; shouldRunPass(now_ns) takes now_ns). For a perfectly
// linear usage ramp of RATE bytes per SAMPLE_SPACING_S sample against max
// heap M, the projection (livenessTracker.cpp's regression form) reduces to
// secondsToOOM() == (M - last_used) * SAMPLE_SPACING_S / RATE, so each
// scenario seeds the exact urgency reading it wants and re-seeds between
// observations - the production loop re-reads the projection once per ~1s
// iteration the same way.
//
// The 15s sample spacing is arbitrary, kept for readable arithmetic. Warmup
// is filtered by secondsToOOM()'s age-based burn-in (OOM_PROJECTION_BURN_IN_NS
// after the leak signal first activated), not by the time span of the sample
// ring, so SetUp() backdates the burn-in stamp against the real monotonic
// clock - the only wall-clock read in these scenarios.
// ---------------------------------------------------------------------------

#include <algorithm>

#include "livenessTracker.h"

class OomUrgencyTest : public ::testing::Test {
protected:
    static constexpr u64 SEC_NS = 1000000000ULL;
    static constexpr u64 MiB = 1ULL << 20;
    static constexpr u64 MAX_HEAP = 1024 * MiB;
    // Bytes of heap growth per sample - the projection's slope is
    // RATE / SAMPLE_SPACING_S per second.
    static constexpr u64 RATE = MiB;
    // Arbitrary - see the file comment above.
    static constexpr u64 SAMPLE_SPACING_S = 15;

    void SetUp() override {
        ReferenceChainsTestAccessor::resetUrgencyForTest();
        LivenessTracker::instance()->setGcGenerationsForTest(true);
        LivenessTracker::instance()->setMaxHeapBytesForTest((jlong)MAX_HEAP);
        LivenessTracker::instance()->setLeakSignalActivatedNsForTest(backdatedStamp());
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
        // 0 = "never activated"; the next start() re-stamps it through the CAS from 0.
        LivenessTracker::instance()->setLeakSignalActivatedNsForTest(0);
    }

    // A burn-in stamp one second past OOM_PROJECTION_BURN_IN_NS (modular u64).
    static u64 backdatedStamp() {
        return OS::nanotime() - LivenessTracker::OOM_PROJECTION_BURN_IN_NS - SEC_NS;
    }

    // Overwrites the whole usage ring with a linear ramp whose projection is
    // exactly `seconds` (see the file comment), and returns the projection
    // the tracker actually computes so every scenario can assert the driver
    // delivered what it intended. `flat` seeds a constant usage instead,
    // which secondsToOOM() reports as -1 (no rising trend - the
    // recent-half corroboration rejects the flat regression).
    double project(double seconds, bool flat = false) {
        // remaining * SAMPLE_SPACING_S / RATE == seconds  =>
        // remaining == seconds * RATE / SAMPLE_SPACING_S
        u64 last_used = MAX_HEAP - (u64)(seconds * (double)RATE /
                                         (double)SAMPLE_SPACING_S);
        for (int i = 0; i < 30; i++) {
            u64 used = flat ? MAX_HEAP / 2
                             : last_used - RATE * (u64)(29 - i);
            LivenessTracker::instance()->heapFloorRecordForTest(
                used, _clock_ns, 0);
            _clock_ns += SAMPLE_SPACING_S * SEC_NS;
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

// The latch machine runs in publishUrgencyState(), once per iteration on
// threadLoop()'s single projection - not in hasLeakSignal(), which sits
// behind canAffordNewSearch()'s cooldown and would otherwise freeze the
// latch (possibly stale-latched after the heap recovered) for as long as
// the cooldown blocks restarts. Drives the machine through the production
// entry point the loop uses, including the release after 5 clear
// observations.
TEST_F(OomUrgencyTest, LatchMachineRunsThroughPublishUrgencyState) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(299.0, true);
    ASSERT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());

    // Five consecutive clear observations through the production entry point
    // release the latch, one tick at a time.
    for (int i = 1; i <= 4; i++) {
        ReferenceChainsTestAccessor::publishUrgencyStateForTest(700.0, false);
        EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest())
            << "released after only " << i << " clear observations";
        EXPECT_EQ(i, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    }
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(700.0, false);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_EQ(0, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
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
// and a fresh sub-threshold crossing re-latches cleanly.
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

    // Re-cross the threshold: re-latch.
    EXPECT_NEAR(project(299.0), 299.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// During the burn-in (OOM_PROJECTION_BURN_IN_NS after the leak signal first
// activated) no projection is offered, so urgency never latches: a warmup
// growth curve projects an imminent OOM just as a real leak does, and a
// burn-in-less gate would latch urgency and start a candidate-less
// whole-heap search that runs to the TTL.
TEST_F(OomUrgencyTest, BurnInDoesNotLatchUrgency) {
    LivenessTracker::instance()->setLeakSignalActivatedNsForTest(OS::nanotime());
    // Earlier scenarios advanced the shared seeding clock far past this test's
    // 0-based timestamps - clear the ring so it holds exactly this test's
    // 10 samples.
    LivenessTracker::instance()->klassPopulationResetForTest();
    constexpr u64 RATE_1S = 100 * MiB; // 100MiB/s - projects ~10s once past burn-in
    for (int i = 0; i < 10; i++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            MAX_HEAP - 1000 * MiB + (u64)i * RATE_1S, (u64)i * SEC_NS, 0);
    }
    EXPECT_LT(LivenessTracker::instance()->secondsToOOM(), 0.0)
        << "projection must be withheld during burn-in";
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());

    // Control: the same seeds are urgent-grade once the burn-in has passed,
    // so the negative half above is not trivially satisfied.
    LivenessTracker::instance()->setLeakSignalActivatedNsForTest(backdatedStamp());
    double seconds = LivenessTracker::instance()->secondsToOOM();
    ASSERT_GE(seconds, 0.0);
    ASSERT_LT(seconds, 300.0) << "scenario must project inside the urgent band";
}

// Regression: near OOM, back-to-back GCs record heap-floor samples less than a
// second apart, so the whole ring spans only seconds. Past the burn-in such a
// GC-compressed history must still project and latch urgency on the first
// sub-threshold reading (the removed span-based guard compared a ~10s
// earliest-to-recent span against the 300s horizon and never latched here).
TEST_F(OomUrgencyTest, GcCompressedWindowLatchesAfterBurnIn) {
    LivenessTracker::instance()->klassPopulationResetForTest();
    // project()'s linear ramp with the spacing compressed from 15s to 0.5s:
    // RATE (1MiB) every 0.5s is 2MiB/s; 200MiB of headroom projects to 100s.
    // project() itself is not used - its shared clock and 15s spacing would
    // defeat the compression.
    u64 last_used = MAX_HEAP - 200 * MiB;
    for (int i = 0; i < 30; i++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            last_used - RATE * (u64)(29 - i), (u64)i * SEC_NS / 2, 0);
    }
    double seconds = LivenessTracker::instance()->secondsToOOM();
    ASSERT_GE(seconds, 0.0);
    ASSERT_LT(seconds, 300.0) << "scenario must project inside the urgent band";
    EXPECT_NEAR(seconds, 100.0, 1.0);

    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest())
        << "a GC-compressed ring past the burn-in must latch urgency";
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// A burn-in -1 is "no projection" like any other negative reading: it counts
// toward release, neither holding the latch as urgent nor as mid-band.
TEST_F(OomUrgencyTest, BurnInProjectionCountsTowardRelease) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest());

    LivenessTracker::instance()->setLeakSignalActivatedNsForTest(OS::nanotime());
    for (int i = 1; i <= 4; i++) {
        EXPECT_LT(project(299.0), 0.0);
        EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentForTest())
            << "released after only " << i << " burn-in observations";
        EXPECT_EQ(i, ReferenceChainsTestAccessor::urgentReleaseTicksForTest());
    }
    EXPECT_LT(project(299.0), 0.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// threadLoop() reads secondsToOOM() once per iteration and passes that value
// down the restart gate: shouldRunPass(u64, double) -> canAffordNewSearch(u64,
// double) -> hasLeakSignal(double) -> isUrgent(double). Each overload must
// latch on the PASSED projection, never re-read the live ring, so every
// decision of one iteration sees the same sample. Each block seeds a live
// projection that disagrees with the passed one. Return values of the
// candidate-dependent gates are not asserted - only the latch they drive.
TEST_F(OomUrgencyTest, UrgencyDecisionsConsumeThePassedProjection) {
    // Restores the tracker's search/pain-budget state on every exit path.
    struct ResetTracker {
        ~ResetTracker() { ReferenceChainsTestAccessor::reset(); }
    } reset_tracker;

    // isUrgent(double).
    ASSERT_LT(project(0.0, /*flat=*/true), 0.0) << "live ring must report no projection";
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(200.0));
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest())
        << "isUrgent(double) must latch on the passed projection";
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ASSERT_NEAR(project(200.0), 200.0, 1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(-1.0));
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest())
        << "isUrgent(double) must not re-read the live (urgent) projection";

    // hasLeakSignal(double) - and everything forwarding into it
    // (canAffordNewSearch, shouldRunPass) - only READS the latch: the machine
    // advances once per iteration in publishUrgencyState(), never from the
    // gates behind canAffordNewSearch()'s cooldown (a stale latch frozen for
    // the cooldown's duration was the regression this contract pins against).
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ASSERT_LT(project(0.0, /*flat=*/true), 0.0);
    ReferenceChainsTestAccessor::hasLeakSignalForTest(200.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest())
        << "hasLeakSignal() must not advance the latch machine";
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ASSERT_NEAR(project(200.0), 200.0, 1.0);
    ReferenceChainsTestAccessor::hasLeakSignalForTest(-1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());

    // canAffordNewSearch(u64, double) and shouldRunPass(u64, double): reset()
    // leaves a fresh PainBudget (balance 0, canStartNow() true) and the search
    // not started, so both reach hasLeakSignal().
    ReferenceChainsTestAccessor::reset();
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ASSERT_LT(project(0.0, /*flat=*/true), 0.0);
    ReferenceChainsTestAccessor::canAffordNewSearch(OS::nanotime(), 200.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest())
        << "canAffordNewSearch() must not advance the latch machine";
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime(), 200.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest())
        << "shouldRunPass() must not advance the latch machine";

    ReferenceChainsTestAccessor::reset();
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ASSERT_NEAR(project(200.0), 200.0, 1.0);
    ReferenceChainsTestAccessor::canAffordNewSearch(OS::nanotime(), -1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    ReferenceChainsTestAccessor::resetUrgencyForTest();
    ReferenceChainsTestAccessor::shouldRunPass(OS::nanotime(), -1.0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// Urgent-admission growth gate (updateUrgentAdmission()): inside the OOM ramp
// band, the 100% tracking boost additionally requires fresh heap growth
// evidence outside the emergency band (< OOM_URGENT_THRESHOLD_S). The
// projection is a least-squares regression over a 30-sample window, so a
// single spike sample keeps it inside the band for several recovery GCs after
// the heap has physically stopped growing - admitting on band residence alone
// would buy tracker-table churn for a recovered spike. threadLoop() computes
// the projection once per iteration and hands it in, so these scenarios pass
// the projection the same way and drive the ring directly through
// heapFloorRecordForTest().
// ---------------------------------------------------------------------------

// A non-emergency in-band projection admits only once the newest heap-floor
// sample has grown past the episode's entry snapshot - one GC later for a
// real leak - and stops admitting as soon as a newer sample falls back below
// it, even while the projection still reads in-band.
TEST_F(OomUrgencyTest, AdmissionBoostRequiresGrowthPastEntryBaseline) {
    // Seeds a ramp projecting 1500s: inside the ramp band (1800s), well
    // outside the emergency band. The ramp's last sample is the peak.
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);

    // First in-band observation establishes the baseline; no growth evidence
    // relative to it yet, so no boost.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // One more sample above the snapshot: real growth -> boost.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1490.0, true));

    // A newer sample back below the entry snapshot: growth evidence gone, the
    // boost must drop even though the (passed-in) projection still reads deep
    // inside the band.
    LivenessTracker::instance()->heapFloorRecordForTest(peak - RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1490.0, true));
}

// Boundary of the growth gate: a newer sample exactly equal to the entry
// snapshot is not growth evidence (a plateaued heap re-recording the same
// floor). Only a strictly larger sample admits, so a `>` -> `>=` slip in
// updateUrgentAdmission() fails here.
TEST_F(OomUrgencyTest, AdmissionBoostRejectsSampleEqualToEntryBaseline) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    ASSERT_EQ(peak, LivenessTracker::instance()->newestHeapFloorSample())
        << "scenario requires the entry snapshot to be the ramp peak";

    // Entry snapshot = peak.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // Follow-up sample exactly at the snapshot: equality is not growth.
    LivenessTracker::instance()->heapFloorRecordForTest(peak, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "a sample equal to the entry baseline is not growth evidence";

    // Control: one RATE past the snapshot admits, so the negative above is
    // not trivially satisfied.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// The regression-smoothing counterexample: a single spike sample keeps the
// smoothed projection inside the band for several recovery GCs after the heap
// has physically recovered. The scenario proves both halves: the projection
// genuinely keeps firing (asserted via secondsToOOM()) while the boost stays
// off for every recovery observation, because no sample grows past the
// entry snapshot (the spike's peak).
TEST_F(OomUrgencyTest, RecoveredSpikeStaysUnboostedWhileProjectionLags) {
    ASSERT_NEAR(project(700.0), 700.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(700.0 * (double)RATE / (double)SAMPLE_SPACING_S);

    // Entry snapshot = the spike's peak.
    ASSERT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(700.0, true));

    // Recovery: each GC lands one RATE below the previous. The recent-half
    // corroboration keeps the projection positive through these (the spike
    // dominates the newest-15 regression until most of the recent half is
    // recovery samples); the lagging projection must not admit any of them.
    for (int r = 1; r <= 6; r++) {
        LivenessTracker::instance()->heapFloorRecordForTest(
            peak - (u64)r * RATE, _clock_ns, 0);
        _clock_ns += SAMPLE_SPACING_S * SEC_NS;
        double seconds = LivenessTracker::instance()->secondsToOOM();
        ASSERT_GE(seconds, 0.0)
            << "recovery sample " << r
            << ": scenario requires the smoothed projection to lag the recovery";
        ASSERT_LT(seconds, 1800.0)
            << "recovery sample " << r
            << ": scenario requires the projection to stay inside the ramp band";
        EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(seconds, true))
            << "recovery sample " << r << " must not be admitted on a lagging projection";
    }
}

// threadLoop()'s publish step (publishUrgencyState()) must feed
// setUrgentTracking() the growth-gated admission decision, not the raw band
// comparison: on a recovered spike the ramp stays active while the 100%
// boost stays off. Observed through LivenessTracker's real admission gate:
// after admissionResetForTest() (ratio 0, no watched tids) only the urgency
// boost can admit a tid.
TEST_F(OomUrgencyTest, PublishedBoostFollowsGrowthGateNotRawBand) {
    LivenessTracker *lt = LivenessTracker::instance();
    struct Restore {
        ~Restore() {
            ReferenceChainsTestAccessor::publishUrgencyStateForTest(-1.0, false);
            LivenessTracker::instance()->admissionResetForTest();
            LivenessTracker::instance()->setSubsampleRatioForTest(0.1);
        }
    } restore;
    lt->admissionResetForTest();
    const jint TID = 1234;

    ASSERT_NEAR(project(700.0), 700.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(700.0 * (double)RATE / (double)SAMPLE_SPACING_S);

    // Entry: ramp active (raw band), boost off (snapshot only).
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(700.0, true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::oomRampActiveForTest());
    EXPECT_FALSE(lt->admitForTrackingForTest(TID)) << "entry observation must not boost";

    // Lagging recovery: ramp stays on, boost stays off.
    for (int r = 1; r <= 6; r++) {
        lt->heapFloorRecordForTest(peak - (u64)r * RATE, _clock_ns, 0);
        _clock_ns += SAMPLE_SPACING_S * SEC_NS;
        double seconds = lt->secondsToOOM();
        ASSERT_GE(seconds, 300.0)
            << "recovery sample " << r << ": must stay out of the emergency band";
        ASSERT_LT(seconds, 1800.0)
            << "recovery sample " << r << ": must stay inside the ramp band";
        ReferenceChainsTestAccessor::publishUrgencyStateForTest(seconds, true);
        EXPECT_TRUE(ReferenceChainsTestAccessor::oomRampActiveForTest()) << r;
        EXPECT_FALSE(lt->admitForTrackingForTest(TID))
            << "recovery sample " << r << ": boost must follow the growth gate, not the raw band";
    }

    // Non-vacuity control: growth past the peak boosts. An explicit in-band,
    // non-emergency projection is passed - any value < OOM_URGENT_THRESHOLD_S
    // (including -1 with urgent=true) would admit through the emergency band
    // regardless of growth.
    lt->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(1490.0, true);
    EXPECT_TRUE(lt->admitForTrackingForTest(TID)) << "growth past the high-water mark must boost";

    // Episode end: both drop.
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(-1.0, false);
    EXPECT_FALSE(ReferenceChainsTestAccessor::oomRampActiveForTest());
    EXPECT_FALSE(lt->admitForTrackingForTest(TID));
}

// The emergency band (< OOM_URGENT_THRESHOLD_S) waives the growth-evidence
// hold: minutes from death means capturing whatever the sampler offers,
// including the very first observation and a heap whose newest sample is
// below the entry snapshot.
TEST_F(OomUrgencyTest, EmergencyBandAdmitsWithoutGrowthEvidence) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));

    // A declining heap does not flip the boost off inside the band.
    u64 newest = MAX_HEAP - (u64)(299.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    LivenessTracker::instance()->heapFloorRecordForTest(newest - RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
}

// A latched urgent episode reading "no projection" (-1, secondsToOOM()'s
// burn-in/not-rising/underfilled encoding) is not an emergency: the
// emergency band carries the same >= 0 lower bound as isUrgent(double), so
// updateUrgentAdmission() takes the growth-gated path instead of the
// evidence-free 100% admission boost.
TEST_F(OomUrgencyTest, NoProjectionInLatchedEpisodeDoesNotArmEmergencyAdmission) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(299.0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    // Real emergency-band entry: admitted, and the growth baseline is seeded
    // at the newest sample; the freshness pair stays untouched.
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
    ASSERT_EQ(0u, ReferenceChainsTestAccessor::admissionSampleSeqForTest());

    // One no-projection reading: the latch holds (release needs consecutive
    // clear observations), so the episode is still urgent.
    ASSERT_TRUE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(-1.0));
    u64 newest_seq = 0;
    ASSERT_NE(0u, LivenessTracker::instance()->newestHeapFloorSample(&newest_seq));
    ASSERT_NE(LivenessTracker::HEAP_FLOOR_SEQ_UNSTABLE, newest_seq);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(-1.0, true))
        << "a negative projection is 'no projection', not the emergency band";
    // The growth-gated path evaluated the sample (the emergency branch never
    // touches the freshness pair): no growth past the seeded baseline.
    EXPECT_EQ(newest_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::admissionDecisionForTest());

    // No new sample: the non-admitting decision is held, not re-armed.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(-1.0, true));
    EXPECT_EQ(newest_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest());
}

// The emergency band seeds the growth baseline at entry: the burn-in can hide
// the projection until it is already short, and without a seed the first
// ramp-band observation would re-snapshot and drop the boost mid-growth.
TEST_F(OomUrgencyTest, EmergencyBandEntrySeedsGrowthBaseline) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    u64 entry = MAX_HEAP - (u64)(299.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    ASSERT_EQ(entry, LivenessTracker::instance()->newestHeapFloorSample());

    // Emergency-band entry: admitted, and the baseline is seeded at `entry`.
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));

    // The projection rises above the threshold into the ramp band while the
    // heap keeps growing: one RATE above the seeded baseline admits.
    LivenessTracker::instance()->heapFloorRecordForTest(entry + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true))
        << "ramp-band observation after emergency entry must compare against the "
           "seeded baseline, not re-snapshot";

    // Control: with the heap flat (no growth past the seeded baseline), the
    // same ramp-band projection does not admit.
    LivenessTracker::instance()->heapFloorRecordForTest(entry, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true));
}

// Boundary of the emergency band: a projection of exactly OOM_URGENT_THRESHOLD_S
// (300s) is ramp band, not emergency. updateUrgentAdmission() keeps the
// growth-evidence hold (first observation snapshots and does not admit; only a
// strictly larger newer sample admits), and isUrgent() does not latch. A
// `<` -> `<=` slip at either threshold comparison fails here.
TEST_F(OomUrgencyTest, ProjectionAtUrgentThresholdIsRampBandAndDoesNotLatch) {
    ASSERT_NEAR(project(300.0), 300.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(300.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    ASSERT_EQ(peak, LivenessTracker::instance()->newestHeapFloorSample())
        << "scenario requires the entry snapshot to be the ramp peak";

    // Exactly at the threshold: no emergency waiver, so the first observation
    // only snapshots the entry baseline.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(300.0, true))
        << "a projection equal to OOM_URGENT_THRESHOLD_S must not take the emergency band";

    // Equal newer sample: not growth.
    LivenessTracker::instance()->heapFloorRecordForTest(peak, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(300.0, true))
        << "an equal newer sample is not growth evidence";

    // Strictly larger newer sample: ramp-band growth admits (non-vacuity).
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(300.0, true))
        << "ramp-band growth must admit at the threshold projection";

    // isUrgent(): 300.0 does not latch; just below does.
    ASSERT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(300.0))
        << "a projection equal to OOM_URGENT_THRESHOLD_S must not latch urgency";
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgentLatchedForTest());
    EXPECT_TRUE(ReferenceChainsTestAccessor::isUrgentWithProjectionForTest(299.9));
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgentLatchedForTest());
}

// The growth baseline is a high-water mark: every admitted sample raises it,
// so a heap that plateaus above the episode's entry level loses the boost -
// comparing against a frozen entry snapshot would keep admitting a heap that
// has stopped growing - and non-admitted samples never lower it.
TEST_F(OomUrgencyTest, PlateauAboveEntryBaselineLosesBoost) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);

    // Entry snapshot = peak; one RATE of growth admits and raises the bar.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // The heap settles flat at a level above the entry snapshot but below the
    // raised bar: no growth, no boost.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE / 2, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "a plateau above the entry level is not growth evidence";

    // A non-admitted sample must not move the high-water mark: a later sample
    // equal to the previous peak (peak + RATE) is still not growth. Raising
    // the baseline on every sample would have dragged it down to
    // peak + RATE / 2 and admitted this one.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "a non-admitted sample must not lower the growth baseline";

    // Growth resuming past the previous peak re-admits.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + 2 * RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// Leaving the band clears the entry snapshot: the next episode re-snapshots
// against its own entry state instead of inheriting the previous episode's
// baseline (which could admit on no growth at all if the heap is now above
// the old snapshot for unrelated reasons).
TEST_F(OomUrgencyTest, BandExitResetsGrowthBaseline) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    ASSERT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    ASSERT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // An out-of-band observation clears the baseline.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(-1.0, false));

    // New episode: the first observation re-snapshots (no inherited growth),
    // then one growing sample admits again.
    ASSERT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + 2 * RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// The ramp-band growth gate is evaluated once per NEW heap-floor sample (one
// per GC), but threadLoop() calls it every iteration (~1s). Admitting raises
// the baseline to the admitted sample, so re-comparing that same sample on
// the next iteration would read "no growth" and turn the boost into a
// one-iteration pulse per growing GC. The decision must be held until a
// genuinely new sample arrives.
TEST_F(OomUrgencyTest, AdmissionHeldUntilNextHeapFloorSample) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // No new sample: the admission must hold across iterations, also while the
    // (passed-in) projection drifts inside the ramp band.
    for (double s : {1500.0, 1490.0, 1480.0, 1500.0}) {
        EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(s, true))
            << "admission must hold until a new heap-floor sample arrives (projection " << s
            << ")";
    }

    // A new sample below the raised high-water mark closes the held state, and
    // the closed state is held as well.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE / 2, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// A non-admitting evaluation is held just like an admitting one: repeated
// iterations without a new sample must not spuriously re-admit.
TEST_F(OomUrgencyTest, NonAdmittingDecisionHeldUntilNextSample) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    // New sample equal to the raised mark: not growth.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    for (int i = 0; i < 3; i++) {
        EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
            << "repeat " << i << ": a held non-admitting decision must not re-admit";
    }

    // Non-vacuity: growth past the high-water mark re-admits.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + 2 * RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// The first observation of an episode snapshots the baseline and does not
// admit; repeating it without a new sample must neither admit nor move the
// baseline.
TEST_F(OomUrgencyTest, FirstObservationStaysUnadmittedWithoutNewSample) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    for (int i = 0; i < 3; i++) {
        EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
            << "repeat " << i;
    }
    // Control: the baseline is still the entry sample.
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// Emergency admission is not growth evidence and does not consume sample
// freshness: a ramp-band observation of the very sample the emergency band
// seeded evaluates it (equality is not growth) and holds that false - a stale
// true must not be retained from the emergency call.
TEST_F(OomUrgencyTest, EmergencySeedThenRampSameSampleStaysUnadmitted) {
    ASSERT_NEAR(project(299.0), 299.0, 1.0);
    u64 entry = MAX_HEAP - (u64)(299.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    ASSERT_EQ(entry, LivenessTracker::instance()->newestHeapFloorSample());
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));

    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true))
        << "the emergency-seeded sample is not growth past itself";
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true));

    LivenessTracker::instance()->heapFloorRecordForTest(entry + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true));
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true))
        << "admission must hold until a new heap-floor sample arrives";
}

// An emergency-band observation in the middle of a held ramp-band admission
// admits (as always) and neither resets nor re-evaluates the retained ramp
// decision.
TEST_F(OomUrgencyTest, EmergencyBandDoesNotDisturbRetainedRampDecision) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "the retained ramp decision must survive an emergency-band observation";

    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// The reset tests below re-enter through the emergency band on purpose: every
// reset site also zeroes the growth baseline, so a ramp-band re-entry with no
// new sample would take the first-observation branch (which overwrites the
// freshness pair) and return false either way. The emergency band seeds the
// baseline WITHOUT touching the freshness pair, so only a leaked pair can make
// the following ramp-band call (same sample) return the stale true.

// Episode end (!urgent) must drop the retained admission along with the
// baseline.
TEST_F(OomUrgencyTest, EpisodeEndDropsRetainedAdmission) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(-1.0, false));

    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "the !urgent branch must clear the retained admission decision and sample seq";
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    LivenessTracker::instance()->heapFloorRecordForTest(peak + 2 * RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// resetUrgencyForTest() must clear the retained admission as well.
TEST_F(OomUrgencyTest, UrgencyResetSeamClearsRetainedAdmission) {
    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    LivenessTracker::instance()->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    ReferenceChainsTestAccessor::resetUrgencyForTest();

    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true))
        << "resetUrgencyForTest() must clear the retained admission decision and sample seq";

    LivenessTracker::instance()->heapFloorRecordForTest(peak + 2 * RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(400.0, true));
}

// publishUrgencyState() must forward the retained decision: the 100% boost
// observed through LivenessTracker's admission gate stays on between GCs.
TEST_F(OomUrgencyTest, PublishedBoostHeldUntilNextHeapFloorSample) {
    LivenessTracker *lt = LivenessTracker::instance();
    struct Restore {
        ~Restore() {
            ReferenceChainsTestAccessor::publishUrgencyStateForTest(-1.0, false);
            LivenessTracker::instance()->admissionResetForTest();
            LivenessTracker::instance()->setSubsampleRatioForTest(0.1);
        }
    } restore;
    lt->admissionResetForTest();
    const jint TID = 1234;

    ASSERT_NEAR(project(1500.0), 1500.0, 1.0);
    u64 peak = MAX_HEAP - (u64)(1500.0 * (double)RATE / (double)SAMPLE_SPACING_S);

    ReferenceChainsTestAccessor::publishUrgencyStateForTest(1500.0, true);
    EXPECT_FALSE(lt->admitForTrackingForTest(TID)) << "entry observation must not boost";

    lt->heapFloorRecordForTest(peak + RATE, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    ReferenceChainsTestAccessor::publishUrgencyStateForTest(1490.0, true);
    EXPECT_TRUE(lt->admitForTrackingForTest(TID)) << "growth must boost";

    for (int i = 0; i < 2; i++) {
        ReferenceChainsTestAccessor::publishUrgencyStateForTest(1490.0, true);
        EXPECT_TRUE(ReferenceChainsTestAccessor::oomRampActiveForTest()) << i;
        EXPECT_TRUE(lt->admitForTrackingForTest(TID))
            << "repeat " << i << ": boost must persist until the next GC sample";
    }

    ReferenceChainsTestAccessor::publishUrgencyStateForTest(-1.0, false);
    EXPECT_FALSE(lt->admitForTrackingForTest(TID));
}

// newestHeapFloorSample(&seq) contract: seq identifies one recorded sample,
// strictly increases per sample (also for equal used/timestamp values), is
// stable on re-read, is 0 for an empty ring, and survives the ring resets -
// so a reset ring followed by a new sample never reproduces a cached seq.
TEST_F(OomUrgencyTest, HeapFloorSequenceIsMonotonicAcrossResets) {
    LivenessTracker *lt = LivenessTracker::instance();
    lt->heapFloorResetForTest();
    u64 seq = 123;
    EXPECT_EQ(0u, lt->newestHeapFloorSample(&seq));
    EXPECT_EQ(0u, seq) << "an empty ring must write 0 to seq_out";

    lt->heapFloorRecordForTest(500 * MiB, 7, 0);
    u64 s1 = 0;
    EXPECT_EQ(500 * MiB, lt->newestHeapFloorSample(&s1));
    EXPECT_NE(0u, s1);
    EXPECT_EQ(500 * MiB, lt->newestHeapFloorSample());

    lt->heapFloorRecordForTest(500 * MiB, 7, 0);
    u64 s2 = 0;
    EXPECT_EQ(500 * MiB, lt->newestHeapFloorSample(&s2));
    EXPECT_GT(s2, s1) << "identity is per sample, not per value/timestamp";

    u64 s2_again = 0;
    lt->newestHeapFloorSample(&s2_again);
    EXPECT_EQ(s2, s2_again) << "a re-read must report the same sample";

    lt->heapFloorResetForTest();
    lt->heapFloorRecordForTest(500 * MiB, 7, 0);
    u64 s3 = 0;
    lt->newestHeapFloorSample(&s3);
    EXPECT_GT(s3, s2) << "heapFloorResetForTest() must not reset the sample counter";

    lt->klassPopulationResetForTest();
    lt->heapFloorRecordForTest(500 * MiB, 7, 0);
    u64 s4 = 0;
    lt->newestHeapFloorSample(&s4);
    EXPECT_GT(s4, s3) << "klassPopulationResetForTest() must not reset the sample counter";

    for (int i = 0; i < 31; i++) {
        lt->heapFloorRecordForTest(500 * MiB + (u64)i, 7, 0);
    }
    u64 s5 = 0;
    EXPECT_EQ(500 * MiB + 30, lt->newestHeapFloorSample(&s5));
    EXPECT_EQ(31u, s5 - s4) << "one increment per sample, newest slot after a ring wrap";

    lt->heapFloorResetForTest();
}

#ifdef DEBUG
// Context for the heap-floor read hook (setHeapFloorReadHookForTest()): each
// invocation records one full ring wrap of samples between the reader's
// payload load and its validating seq re-load; fire_once limits that to the
// first invocation.
struct HeapFloorReadHookCtx {
    int calls = 0;     // hook invocations (one per reader attempt)
    int records = 0;   // invocations that actually recorded a ring wrap
    bool fire_once = false;
    u64 clock = 0;
};

static void heapFloorReadHookThunk(void *arg) {
    HeapFloorReadHookCtx *ctx = static_cast<HeapFloorReadHookCtx *>(arg);
    int n = ctx->calls++;
    if (ctx->fire_once && n > 0) {
        return;
    }
    ctx->records++;
    LivenessTracker *lt = LivenessTracker::instance();
    // A full wrap returns the head to the slot the reader is holding - the
    // torn-read interleaving the gate must survive.
    constexpr int RING_SIZE = LivenessTracker::heapFloorRingSizeForTest();
    constexpr u64 WRAP_BASE = 1100ULL << 20;
    for (int i = 0; i < RING_SIZE; i++) {
        lt->heapFloorRecordForTest(WRAP_BASE + ((u64)i << 20), ctx->clock, 0);
        ctx->clock += 1;
    }
}
#endif

// When the read hook interleaves a full ring wrap inside newestHeapFloorSample()
// (the torn-read window), the admission gate must evaluate - and consume the
// seq of - only a coherent pair. A torn read would pair sample 1's payload
// with a newer sample's seq; consuming that seq would hide the true newest
// sample from every later call with an unchanged ring.
TEST_F(OomUrgencyTest, AdmissionNeverConsumesSeqOfUnevaluatedSample) {
#ifdef DEBUG
    LivenessTracker *lt = LivenessTracker::instance();
    lt->heapFloorResetForTest();
    // The hook must never outlive this test, on any exit path.
    struct ClearHook {
        ~ClearHook() { LivenessTracker::setHeapFloorReadHookForTest(nullptr, nullptr); }
    } clear_hook;

    lt->heapFloorRecordForTest(1000 * MiB, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    u64 baseline_seq = 0;
    ASSERT_EQ(1000 * MiB, lt->newestHeapFloorSample(&baseline_seq));

    // First ramp-band observation: sets the entry baseline, consumes its seq.
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    ASSERT_EQ(baseline_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest());

    HeapFloorReadHookCtx ctx;
    ctx.fire_once = true;
    LivenessTracker::setHeapFloorReadHookForTest(heapFloorReadHookThunk, &ctx);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "the gate must evaluate the coherent newest sample (1129 MiB), not the torn payload";
    ASSERT_EQ(1, ctx.records) << "the interleaving must have happened exactly once";

    // The consumed seq must be the true newest sample's seq - read here with
    // the hook cleared - never one whose value the gate did not compare.
    LivenessTracker::setHeapFloorReadHookForTest(nullptr, nullptr);
    u64 newest_seq = 0;
    ASSERT_EQ(1129 * MiB, lt->newestHeapFloorSample(&newest_seq));
    ASSERT_NE(baseline_seq, newest_seq) << "the hook must have wrapped the ring";
    EXPECT_EQ(newest_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest());

    // Unchanged ring afterwards: the evaluated decision is held.
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    lt->heapFloorResetForTest();
#else
    GTEST_SKIP() << "the heap-floor read hook is DEBUG-only";
#endif
}

// A read that exhausts the reader's retry bound returns (0,
// HEAP_FLOOR_SEQ_UNSTABLE) - "no sample evaluated": the previous decision
// holds and the sentinel never lands in _admission_sample_seq, for both
// decision values (a dropped true would pulse the boost off for one
// iteration; a re-admitted false would revive a dead boost). The retained
// _admission_decision is checked directly through admissionDecisionForTest()
// after every call, not only via the returned value.
TEST_F(OomUrgencyTest, AdmissionHeldOnUnstableHeapFloorRead) {
#ifdef DEBUG
    LivenessTracker *lt = LivenessTracker::instance();
    lt->heapFloorResetForTest();
    struct ClearHook {
        ~ClearHook() { LivenessTracker::setHeapFloorReadHookForTest(nullptr, nullptr); }
    } clear_hook;

    // Establish a held true decision: entry snapshot, then growth past it.
    lt->heapFloorRecordForTest(1000 * MiB, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    lt->heapFloorRecordForTest(1100 * MiB, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    ASSERT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    u64 true_seq = ReferenceChainsTestAccessor::admissionSampleSeqForTest();
    ASSERT_NE(0u, true_seq);
    ASSERT_TRUE(ReferenceChainsTestAccessor::admissionDecisionForTest())
        << "the growth evaluation must retain a true decision";

    // Every reader attempt fires the hook and wraps the ring, so the retry
    // bound exhausts and the read reports no consistent sample.
    HeapFloorReadHookCtx ctx;
    LivenessTracker::setHeapFloorReadHookForTest(heapFloorReadHookThunk, &ctx);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "an unstable read must hold the true decision, not drop the boost";
    ASSERT_EQ(LivenessTracker::HEAP_FLOOR_READ_ATTEMPTS, ctx.records)
        << "the reader retry bound must have been exhausted";
    u64 sentinel_seq = 0;
    EXPECT_EQ(0u, lt->newestHeapFloorSample(&sentinel_seq));
    EXPECT_EQ(LivenessTracker::HEAP_FLOOR_SEQ_UNSTABLE, sentinel_seq);
    ASSERT_EQ(2 * LivenessTracker::HEAP_FLOOR_READ_ATTEMPTS, ctx.records)
        << "the direct reader check must also have exhausted the bound";
    EXPECT_EQ(true_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest())
        << "the sentinel seq must never be consumed";
    EXPECT_TRUE(ReferenceChainsTestAccessor::admissionDecisionForTest())
        << "an unstable read must leave the retained true decision untouched";

    // Same hold for a false decision: evaluate one flat sample with the hook
    // cleared, then make the ring unreadable again.
    LivenessTracker::setHeapFloorReadHookForTest(nullptr, nullptr);
    lt->heapFloorRecordForTest(1050 * MiB, _clock_ns, 0);
    _clock_ns += SAMPLE_SPACING_S * SEC_NS;
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    u64 false_seq = ReferenceChainsTestAccessor::admissionSampleSeqForTest();
    ASSERT_NE(false_seq, true_seq);
    ASSERT_FALSE(ReferenceChainsTestAccessor::admissionDecisionForTest())
        << "the flat-sample evaluation must retain a false decision";

    LivenessTracker::setHeapFloorReadHookForTest(heapFloorReadHookThunk, &ctx);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "an unstable read must hold the false decision, not re-admit";
    ASSERT_EQ(3 * LivenessTracker::HEAP_FLOOR_READ_ATTEMPTS, ctx.records)
        << "the second unstable read must also have exhausted the bound";
    EXPECT_EQ(false_seq, ReferenceChainsTestAccessor::admissionSampleSeqForTest());
    EXPECT_FALSE(ReferenceChainsTestAccessor::admissionDecisionForTest())
        << "an unstable read must leave the retained false decision untouched";

    LivenessTracker::setHeapFloorReadHookForTest(nullptr, nullptr);
    lt->heapFloorResetForTest();
#else
    GTEST_SKIP() << "the heap-floor read hook is DEBUG-only";
#endif
}

// ---------------------------------------------------------------------------
// The urgency episode's cadence half (applyOomRamp()): an episode owns
// _effective_cadence_ns while it runs; its end must hand the field back at
// the fallback cadence in the same iteration, or the idle loop keeps waking
// at the ramped rate for the rest of the recording.
// ---------------------------------------------------------------------------

// Drives one urgency episode end-to-end: urgent iterations pin the ramped
// cadence (10ms at OOM, ~21.5ms at 300s out), and the first non-urgent
// iteration restores the 1s fallback - not just the first one after boost,
// but on every later iteration too.
TEST_F(OomUrgencyTest, UrgencyExitRestoresFallbackCadence) {
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    const u64 pass_ns = ReferenceChainsTestAccessor::baselineCadenceNs();
    const u64 urgent_ns = ReferenceChainsTestAccessor::urgentCadenceNsForTest();
    struct Restore {
        ReferenceChainsTestAccessor::OomRampState saved;
        ~Restore() {
            // Close any still-open episode first so the budget restore runs,
            // then put the saved scheduling state back.
            ReferenceChainsTestAccessor::applyOomRampForTest(-1.0);
            ReferenceChainsTestAccessor::setEffectiveCadenceNs(
                ReferenceChainsTestAccessor::baselineCadenceNs());
            ReferenceChainsTestAccessor::restoreOomRampStateForTest(saved);
        }
    } restore{ReferenceChainsTestAccessor::saveOomRampStateForTest()};
    // The cadence ramp paces passes, so it applies only while a search runs.
    ReferenceChainsTestAccessor::setSearchRunningForTest(true);

    // Seed a known budget ceiling and pause target: the singleton may never
    // have been start()ed (zeros would make the boost and the ramp vacuous).
    // The 7-field Restore above puts the singleton's own values back.
    const int configured_budget = 1000;
    const int boosted_budget = std::min(configured_budget * 4, MAX_REFERENCE_CHAINS_BUDGET);
    const long configured_pause_ms = 20;
    ReferenceChainsTestAccessor::setBudgetsForTest(configured_budget, configured_budget);
    ReferenceChainsTestAccessor::setPauseTargetsForTest(configured_pause_ms);

    // No episode open: the non-urgent iteration leaves the fallback cadence,
    // the budget ceiling and the pause target alone.
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(pass_ns);
    EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(-1.0));
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest());
    EXPECT_EQ(configured_budget, ReferenceChainsTestAccessor::budgetForTest());
    EXPECT_EQ(configured_pause_ms, ReferenceChainsTestAccessor::effectivePauseTargetMsForTest());

    // At OOM the ramp reaches its urgent ceiling (scenario reached).
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(urgent_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "a 0s projection must pin the urgent cadence floor";
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest())
        << "the first urgent iteration must open the episode";
    EXPECT_EQ(boosted_budget, ReferenceChainsTestAccessor::budgetForTest())
        << "episode entry boosts the budget ceiling 4x (clamped to MAX)";
    EXPECT_EQ(ReferenceChainsTestAccessor::urgentPauseTargetMsForTest(),
              ReferenceChainsTestAccessor::effectivePauseTargetMsForTest())
        << "a 0s projection must ramp the pause target to its urgent ceiling";

    // Mid-ramp: 300s out of the 1800s horizon lands at 21.54ms (+/- 1ms) - a
    // fixed constant, not the formula, so a drifted exponent fails here.
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(300.0));
    EXPECT_NEAR((double)ReferenceChainsTestAccessor::effectiveCadenceNs(),
                21.54e6, 1.0e6)
        << "300s out of the 1800s ramp horizon";
    EXPECT_EQ(boosted_budget, ReferenceChainsTestAccessor::budgetForTest())
        << "the boost applies once per episode, never compounded";
    EXPECT_EQ(76L, ReferenceChainsTestAccessor::effectivePauseTargetMsForTest())
        << "20ms * 5^(1 - 300/1800) = 76.47ms: the pause target tracks the ramp";

    // Episode end: the first non-urgent iteration restores the fallback, and
    // repeated non-urgent iterations keep it there (not a one-shot edge).
    for (int i = 0; i < 100; i++) {
        EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(-1.0));
    }
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "the urgency episode's end must restore the fallback cadence";
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest())
        << "the episode end must clear the boost flag";
    EXPECT_EQ(ReferenceChainsTestAccessor::configuredBudgetForTest(),
              ReferenceChainsTestAccessor::budgetForTest())
        << "the episode end must restore the configured budget";
    EXPECT_EQ(configured_budget, ReferenceChainsTestAccessor::budgetForTest());
    EXPECT_EQ(configured_pause_ms, ReferenceChainsTestAccessor::effectivePauseTargetMsForTest())
        << "the episode end must restore the configured pause target";
}

// The cadence ramp paces passes, so with no search running - not started, or
// terminal awaiting a restart - an urgent iteration holds the 1s fallback:
// the idle wake only probes selectLeakCandidates(), and ramping it would
// spend up to ~100 probes/s. The rest of the episode (budget boost, pause
// target) still applies, and the ramp follows the search state both ways.
TEST_F(OomUrgencyTest, UrgentIdleWakeHoldsFallbackCadence) {
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    const u64 pass_ns = ReferenceChainsTestAccessor::baselineCadenceNs();
    const u64 urgent_ns = ReferenceChainsTestAccessor::urgentCadenceNsForTest();
    struct Restore {
        ReferenceChainsTestAccessor::OomRampState saved;
        ~Restore() {
            ReferenceChainsTestAccessor::applyOomRampForTest(-1.0);
            ReferenceChainsTestAccessor::setEffectiveCadenceNs(
                ReferenceChainsTestAccessor::baselineCadenceNs());
            ReferenceChainsTestAccessor::restoreOomRampStateForTest(saved);
        }
    } restore{ReferenceChainsTestAccessor::saveOomRampStateForTest()};
    const int configured_budget = 1000;
    ReferenceChainsTestAccessor::setBudgetsForTest(configured_budget, configured_budget);
    ReferenceChainsTestAccessor::setPauseTargetsForTest(20);
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(2 * pass_ns);

    // Not started (a fresh tracker or a just-restarted search).
    ReferenceChainsTestAccessor::setSearchNotStartedForTest();
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "no search started: the urgent idle wake must hold the fallback cadence";
    EXPECT_TRUE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest())
        << "the episode still opens with no search running";
    EXPECT_EQ(std::min(configured_budget * 4, MAX_REFERENCE_CHAINS_BUDGET),
              ReferenceChainsTestAccessor::budgetForTest());
    EXPECT_EQ(ReferenceChainsTestAccessor::urgentPauseTargetMsForTest(),
              ReferenceChainsTestAccessor::effectivePauseTargetMsForTest())
        << "the pause-target ramp does not depend on the search state";

    // Terminal, awaiting a restart.
    ReferenceChainsTestAccessor::setSearchRunningForTest(false);
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "terminal search: the urgent idle wake must hold the fallback cadence";

    // Running: the ramp paces passes.
    ReferenceChainsTestAccessor::setSearchRunningForTest(true);
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(urgent_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "a running search must ramp to the urgent cadence floor";

    // The search ends mid-episode: the next urgent iteration drops back.
    ReferenceChainsTestAccessor::setSearchRunningForTest(false);
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "a search ending mid-episode must return the idle wake to the fallback";
}

// Outside an episode, a non-urgent iteration must not touch a cadence that
// updatePacing() has adapted (2s here, past the fallback, to prove the write
// path is not merely "leave PASS_CADENCE_NS alone"). Closing an episode is
// the only non-urgent iteration that writes the field.
TEST_F(OomUrgencyTest, NonUrgentIterationKeepsPacedCadence) {
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    const u64 pass_ns = ReferenceChainsTestAccessor::baselineCadenceNs();
    const u64 paced_ns = 2 * pass_ns;
    struct Restore {
        ReferenceChainsTestAccessor::OomRampState saved;
        ~Restore() {
            ReferenceChainsTestAccessor::applyOomRampForTest(-1.0);
            ReferenceChainsTestAccessor::setEffectiveCadenceNs(
                ReferenceChainsTestAccessor::baselineCadenceNs());
            ReferenceChainsTestAccessor::restoreOomRampStateForTest(saved);
        }
    } restore{ReferenceChainsTestAccessor::saveOomRampStateForTest()};
    // The cadence ramp paces passes, so it applies only while a search runs.
    ReferenceChainsTestAccessor::setSearchRunningForTest(true);

    ReferenceChainsTestAccessor::setEffectiveCadenceNs(paced_ns);
    EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(-1.0));
    EXPECT_EQ(paced_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "no episode open: a non-urgent iteration must not rewrite the cadence";
    EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(3600.0))
        << "a projection past the ramp horizon is not urgent";
    EXPECT_EQ(paced_ns, ReferenceChainsTestAccessor::effectiveCadenceNs());

    // Open and close one episode: the closing iteration restores the fallback.
    EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    EXPECT_EQ(ReferenceChainsTestAccessor::urgentCadenceNsForTest(),
              ReferenceChainsTestAccessor::effectiveCadenceNs());
    EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(-1.0));
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "closing the episode must return the cadence to the fallback, not to "
           "the pre-episode adapted value";
}

// Flapping across the ramp horizon's edge: each far-side (1801s) iteration
// restores the fallback, and each near-side (1799s) iteration recomputes
// the ramp value from scratch - identical every time, since the ramp anchors
// on PASS_CADENCE_NS, never on the live (previously restored) cadence.
TEST_F(OomUrgencyTest, RampEdgeFlapRestoresAndRecomputesCadence) {
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    const u64 pass_ns = ReferenceChainsTestAccessor::baselineCadenceNs();
    const u64 urgent_ns = ReferenceChainsTestAccessor::urgentCadenceNsForTest();
    struct Restore {
        ReferenceChainsTestAccessor::OomRampState saved;
        ~Restore() {
            ReferenceChainsTestAccessor::applyOomRampForTest(-1.0);
            ReferenceChainsTestAccessor::setEffectiveCadenceNs(
                ReferenceChainsTestAccessor::baselineCadenceNs());
            ReferenceChainsTestAccessor::restoreOomRampStateForTest(saved);
        }
    } restore{ReferenceChainsTestAccessor::saveOomRampStateForTest()};
    // The cadence ramp paces passes, so it applies only while a search runs.
    ReferenceChainsTestAccessor::setSearchRunningForTest(true);

    // Half the ceiling: the 4x boost must clamp at MAX_REFERENCE_CHAINS_BUDGET
    // on every episode open and restore the configured value on every close.
    const int configured_budget = MAX_REFERENCE_CHAINS_BUDGET / 2;
    ReferenceChainsTestAccessor::setBudgetsForTest(configured_budget, configured_budget);

    u64 first_ramp_ns = 0;
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(1799.0))
            << "flap " << i << ": 1799s is inside the ramp horizon";
        EXPECT_EQ(MAX_REFERENCE_CHAINS_BUDGET, ReferenceChainsTestAccessor::budgetForTest())
            << "flap " << i << ": the 4x boost must clamp at the budget ceiling";
        u64 ramp_ns = ReferenceChainsTestAccessor::effectiveCadenceNs();
        EXPECT_GT(ramp_ns, urgent_ns) << "flap " << i;
        EXPECT_LT(ramp_ns, pass_ns)
            << "flap " << i << ": 1799s must not reach the fallback";
        if (i == 0) {
            first_ramp_ns = ramp_ns;
        } else {
            EXPECT_EQ(first_ramp_ns, ramp_ns)
                << "flap " << i << ": the ramp must recompute, not compound";
        }

        EXPECT_FALSE(ReferenceChainsTestAccessor::applyOomRampForTest(1801.0))
            << "flap " << i << ": 1801s is outside the ramp horizon";
        EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
            << "flap " << i << ": the episode end must restore the fallback";
        EXPECT_EQ(configured_budget, ReferenceChainsTestAccessor::budgetForTest())
            << "flap " << i << ": the episode end must restore the configured budget";
    }
}

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

// stop() ends the urgency episode at a recording boundary, so it must clear
// updateUrgentAdmission()'s growth baseline along with the latch: the
// heap-floor ring survives the boundary, and a baseline left over from the
// previous recording would let the new recording's first urgent observation
// skip its entry re-snapshot and admit against the old recording's heap level.
// updateUrgentAdmission() reads only the newest heap-floor sample, so no max
// heap is set - and must not be before start(): with a max heap > 0, start()'s
// autoTuneDefaults() calls GetAvailableProcessors, which this stub jvmti lacks.
//
// updateUrgentAdmissionForTest() writes the BFS-thread-only
// _admission_growth_baseline from the gtest main thread. That is race-free only
// because start() does not spawn the BFS thread (threadLoop() needs an attached
// VM - see the end of ReferenceChainTracker::start()), so no threadLoop()
// calls updateUrgentAdmission() concurrently here. The ASSERTs on
// bfsThreadRunning() pin that precondition: a future start() that spawns the
// thread fails here instead of racing.
TEST_F(ReferenceChainsCanaryRefillTest, StopClearsAdmissionGrowthBaseline) {

    constexpr u64 MiB = 1ULL << 20;
    LivenessTracker *lt = LivenessTracker::instance();
    ReferenceChainsTestAccessor::reset(); // also resetUrgencyForTest()
#ifdef DEBUG
    lt->setHeapFloorRecordingForTest(false);
#endif
    lt->heapFloorResetForTest();
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));

    // Restores the shared singletons even when an ASSERT below returns early.
    // stop() on an already-stopped tracker is a no-op (it returns unless
    // enabled()).
    struct Cleanup {
        ReferenceChainTracker *tracker;
        LivenessTracker *lt;
        ~Cleanup() {
            tracker->stop();
            ReferenceChainsTestAccessor::resetUrgencyForTest();
            lt->heapFloorResetForTest(); // while recording is still disabled
#ifdef DEBUG
            lt->setHeapFloorRecordingForTest(true);
#endif
            ReferenceChainsTestAccessor::reset();
        }
    } cleanup{tracker, lt};
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "updateUrgentAdmissionForTest() would race threadLoop()";

    // Recording 1: the first urgent non-emergency observation snapshots
    // 500MiB and does not admit.
    lt->heapFloorRecordForTest(500 * MiB, 1, 0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    tracker->stop();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "updateUrgentAdmissionForTest() would race threadLoop()";

    // Recording 2: the heap is now above the OLD baseline. A fresh episode
    // must re-snapshot (false); a baseline leaked through stop() would admit
    // on 600 > 500.
    lt->heapFloorRecordForTest(600 * MiB, 2, 0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "stop() must clear _admission_growth_baseline";
    // Positive control: growth past the new snapshot admits.
    lt->heapFloorRecordForTest(700 * MiB, 3, 0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// stop() must also clear the retained admission (_admission_sample_seq /
// _admission_decision), not only the growth baseline. The heap-floor ring
// survives the recording boundary, so the admitted sample stays newest; an
// emergency-band first observation in the new recording seeds the baseline
// without touching the freshness pair, and a leaked pair would then make the
// next ramp-band call (no new GC sample) return the old recording's retained
// admission. Same BFS-thread precondition as StopClearsAdmissionGrowthBaseline.
TEST_F(ReferenceChainsCanaryRefillTest, StopClearsRetainedAdmission) {

    constexpr u64 MiB = 1ULL << 20;
    LivenessTracker *lt = LivenessTracker::instance();
    ReferenceChainsTestAccessor::reset(); // also resetUrgencyForTest()
#ifdef DEBUG
    lt->setHeapFloorRecordingForTest(false);
#endif
    lt->heapFloorResetForTest();
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));

    struct Cleanup {
        ReferenceChainTracker *tracker;
        LivenessTracker *lt;
        ~Cleanup() {
            tracker->stop();
            ReferenceChainsTestAccessor::resetUrgencyForTest();
            lt->heapFloorResetForTest(); // while recording is still disabled
#ifdef DEBUG
            lt->setHeapFloorRecordingForTest(true);
#endif
            ReferenceChainsTestAccessor::reset();
        }
    } cleanup{tracker, lt};
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "updateUrgentAdmissionForTest() would race threadLoop()";

    // Recording 1: snapshot 500MiB, admit 600MiB, hold the admission.
    lt->heapFloorRecordForTest(500 * MiB, 1, 0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    lt->heapFloorRecordForTest(600 * MiB, 2, 0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    tracker->stop();
    ASSERT_FALSE(tracker->start(args));
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "updateUrgentAdmissionForTest() would race threadLoop()";

    // Recording 2, no new sample: emergency entry seeds the baseline at
    // 600MiB; the ramp-band call must evaluate (600 > 600 is false), not
    // return recording 1's retained true.
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(299.0, true));
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true))
        << "stop() must clear the retained admission decision and sample seq";

    // Positive control: growth past the seeded baseline admits.
    lt->heapFloorRecordForTest(700 * MiB, 3, 0);
    EXPECT_TRUE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));
}

// stop() is the urgency episode's second closer: an episode still open at the
// recording boundary must not leak its boosted budget ceiling or its ramped
// cadence past it. The closer is guarded on the boost flag, exactly like
// applyOomRamp()'s episode-end branch - outside an episode updatePacing() owns
// the cadence, so stop() must leave a paced cadence alone. Two recordings,
// because stop() returns early once the tracker is disabled. Same BFS-thread
// precondition as StopClearsAdmissionGrowthBaseline.
TEST_F(ReferenceChainsCanaryRefillTest, StopClosesOpenUrgencyEpisode) {
    ReferenceChainsTestAccessor::reset(); // also resetUrgencyForTest()
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    const ReferenceChainsTestAccessor::OomRampState saved =
        ReferenceChainsTestAccessor::saveOomRampStateForTest();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));

    struct Cleanup {
        ReferenceChainTracker *tracker;
        ReferenceChainsTestAccessor::OomRampState saved;
        ~Cleanup() {
            tracker->stop();
            ReferenceChainsTestAccessor::resetUrgencyForTest();
            ReferenceChainsTestAccessor::restoreOomRampStateForTest(saved);
            ReferenceChainsTestAccessor::reset();
        }
    } cleanup{tracker, saved};
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    const u64 pass_ns = ReferenceChainsTestAccessor::baselineCadenceNs();
    const int configured = ReferenceChainsTestAccessor::configuredBudgetForTest();
    ASSERT_GT(configured, 0) << "start() must record a positive configured budget";

    // Recording 1, no episode open: a paced (non-fallback) cadence survives
    // stop() - the closer must not fire without the boost flag.
    ASSERT_FALSE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest());
    ReferenceChainsTestAccessor::setEffectiveCadenceNs(2 * pass_ns);
    tracker->stop();
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning());
    EXPECT_EQ(2 * pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "stop() must not rewrite a cadence updatePacing() owns outside an episode";
    EXPECT_EQ(configured, ReferenceChainsTestAccessor::budgetForTest());

    // Recording 2: start() reseeds the cadence, then an episode opens.
    ASSERT_FALSE(tracker->start(args));
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning())
        << "applyOomRampForTest() would race threadLoop()";
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "start() reseeds the cadence";
    ReferenceChainsTestAccessor::setSearchRunningForTest(true);
    ASSERT_TRUE(ReferenceChainsTestAccessor::applyOomRampForTest(0.0));
    ASSERT_TRUE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest());
    ASSERT_EQ(std::min(configured * 4, MAX_REFERENCE_CHAINS_BUDGET),
              ReferenceChainsTestAccessor::budgetForTest());
    ASSERT_EQ(ReferenceChainsTestAccessor::urgentCadenceNsForTest(),
              ReferenceChainsTestAccessor::effectiveCadenceNs());

    tracker->stop();
    ASSERT_FALSE(ReferenceChainsTestAccessor::bfsThreadRunning());
    EXPECT_FALSE(ReferenceChainsTestAccessor::urgencyBudgetBoostedForTest())
        << "stop() must close the open urgency episode";
    EXPECT_EQ(ReferenceChainsTestAccessor::configuredBudgetForTest(),
              ReferenceChainsTestAccessor::budgetForTest())
        << "stop() must restore the configured budget ceiling";
    EXPECT_EQ(configured, ReferenceChainsTestAccessor::budgetForTest());
    EXPECT_EQ(pass_ns, ReferenceChainsTestAccessor::effectiveCadenceNs())
        << "stop() must restore the fallback cadence";
}

TEST_F(ReferenceChainsCanaryRefillTest, BackoffGateHoldsUnlessOomRampActive) {
    ReferenceChainsTestAccessor::reset();
    ReferenceChainTracker *tracker = ReferenceChainTracker::instance();
    Arguments args;
    ASSERT_FALSE(args.parse("referencechains=true"));
    ASSERT_FALSE(tracker->start(args));
    ReferenceChainsTestAccessor::setSearchStartedForTest(true);

    // Open chase with the backoff engaged: mult=4 x ema=100ms = 400ms
    // spacing, and only 50ms since the last pass. The EMA is in ns.
    ReferenceChainsTestAccessor::setCandidateCountForTest(2);
    ReferenceChainsTestAccessor::setCandidateFoundBitsForTest(0x1);
    u64 now = 6000000000ULL; // 6s into the test's synthetic clock
    ReferenceChainsTestAccessor::setCanaryBackoffForTest(
        4, 100ULL * 1000000ULL, now - 50 * 1000000ULL);

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
