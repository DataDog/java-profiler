
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
// activated) no projection is offered, so urgency never latches: a fresh
// process's warmup growth curve projects an imminent OOM just as a real leak
// does (the staging incident: a fresh process latched urgency and ran a
// candidate-less whole-heap search to the TTL).
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

    // Recording 1: the first urgent non-emergency observation snapshots
    // 500MiB and does not admit.
    lt->heapFloorRecordForTest(500 * MiB, 1, 0);
    EXPECT_FALSE(ReferenceChainsTestAccessor::updateUrgentAdmissionForTest(1500.0, true));

    tracker->stop();
    ASSERT_FALSE(tracker->start(args));

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
