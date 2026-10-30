/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.junit.jupiter.api.Test;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * E2E coverage for the search-restart gate the reference-chain collector's pass loop polls
 * ({@code ReferenceChainTracker::hasLeakSignal()}, referenceChains.cpp). Complements
 * {@link ReferenceChainTrackingTest}'s organic coverage of a slow leak - a gradually-growing
 * population that clears {@code selectLeakCandidates()}'s per-klass hysteresis gate over many
 * rounds - with the aggregate heap-floor case: a heap-wide growth fast enough that a real
 * deployment would OOM before any single klass's own population history ever clears that same
 * hysteresis gate.
 *
 * <p>This class is a regression guard for the candidate-gate contract: the aggregate urgent-OOM
 * projection alone must NEVER open the gate while the per-klass population table is provably
 * empty: a candidate-less search cannot exit early and would run whole-heap BFS passes to the
 * auto-tuned TTL with zero chains to show for it.
 *
 * <p>Reproducing a genuine near-OOM heap in this shared, no-{@code forkEvery} test JVM is
 * impractical (see {@link ReferenceChainTrackingTest}'s own header comment on the JVM this class
 * shares with every other {@code ddprof-test} class). The debug-only
 * {@code heapFloorRecordForTest0()}/{@code setMaxHeapBytesForTest0()} seams (javaApi.cpp) instead
 * seed {@code LivenessTracker}'s aggregate heap-floor-ring history and its max-heap-bytes cache
 * directly, so {@code secondsToOOM()}'s projection can be driven under
 * {@code OOM_URGENT_THRESHOLD_S} (referenceChains.h) deterministically, decoupled from this JVM's
 * real {@code -Xmx} and from real GC timing. {@code secondsToOOM()} withholds its projection for
 * {@code OOM_PROJECTION_BURN_IN_NS} (5 minutes) after the leak signal first activated, and this
 * class may run inside that window, so each gate test backdates the burn-in stamp with
 * {@code backdateLeakSignalActivationForTest0()} and restores it in its finally block. Positive
 * controls ({@code secondsToOOMForTest0()} for the projection, {@code urgentLatchedForTest0()} for
 * the urgency latch) prove the urgency machine is engaged (or provably not, for the flat-floor
 * control) before any negative gate assertion is trusted. {@code shouldRunPassForTest0()} then
 * evaluates {@code ReferenceChainTracker::shouldRunPass()} - the gate {@code hasLeakSignal()}
 * feeds - directly on a freshly reset search, rather than running a real pass or waiting on the
 * live BFS thread, so this class never depends on {@code selectLeakCandidates()} ranking
 * anything, a real JVMTI heap walk, or a JFR event.
 */
public class AggressiveLeakReferenceChainTest extends AbstractProfilerTest {

  // Mirrors ReferenceChainTracker::OOM_URGENT_THRESHOLD_S (referenceChains.h).
  private static final double OOM_URGENT_THRESHOLD_S = 300.0;

  // Sentinel for restoreHeapFloorDefaults(): skip the burn-in stamp restore (the caller never
  // backdated it). A real stamp is an OS::nanotime() u64 cast to a jlong, so Long.MIN_VALUE
  // cannot collide with one in practice.
  private static final long ACTIVATION_STAMP_UNCHANGED = Long.MIN_VALUE;

  @Override
  protected String getProfilerCommand() {
    // generations=true: arms LivenessTracker's effective leak signal (generations OR liveheap
    // tracking drive the same population mechanisms) - without it hasLeakSignal() returns false
    // trivially, which would make every test below pass regardless of the candidate-gate
    // contract this class exists to exercise. referencechains=true: constructs the
    // FrontierTable/ReferenceChainTracker singleton at all - shouldRunPassForTest0() has
    // nothing to read otherwise.
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    // Mirrors ReferenceChainTrackingTest's own guard - FollowReferences/tag-based frontier walking
    // assumes a HotSpot-shaped JVMTI heap implementation.
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue(ReferenceChainAssertions.isDebugInstrumentedBuild(),
        "heapFloorRecordForTest0/setMaxHeapBytesForTest0/shouldRunPassForTest0 only exist in a "
            + "-DDEBUG native build (debug/asan/tsan - javaApi.cpp's #ifdef DEBUG guard)");
  }

  /**
   * Undoes this class's synthetic seeding so later tests in this shared, no-forkEvery JVM never
   * see it. This helper is the only place the cleanup ordering lives; every test's finally block
   * ends with it. {@code resetKlassPopulationForTest0()} also zeroes LivenessTracker's heap-floor
   * ring (head/fill - {@code klassPopulationResetForTest()}, livenessTracker.h), so
   * {@code secondsToOOM()} reports "insufficient fill" until real GC samples build up again; it
   * runs while heap-floor recording is still disabled so no real sample can interleave. The
   * burn-in stamp is restored next (unless {@code savedActivationNs} is
   * {@link #ACTIVATION_STAMP_UNCHANGED}) - after the ring reset and before the search reset, so
   * the restarted BFS thread can neither re-latch from a stale ring nor project against a
   * backdated clock. {@code resetReferenceChainSearchForTest0()} then clears any urgency latch
   * plus the search state an earlier evaluation started. Recording is re-enabled last.
   */
  private static void restoreHeapFloorDefaults(long savedActivationNs) {
    ReferenceChainTestHooks.setMaxHeapBytesForTest0(-1);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    if (savedActivationNs != ACTIVATION_STAMP_UNCHANGED) {
      ReferenceChainTestHooks.setLeakSignalActivatedNsForTest0(savedActivationNs);
    }
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(true);
  }

  /** Result of one bracketed direct gate evaluation. */
  private static final class GateEvaluation {
    boolean gateOpen;
    boolean candidateSeen;
    int passesAfter;
    String detail;
  }

  /**
   * Evaluates the search gate directly on a freshly reset search. The reset clears the urgency
   * latch and the pain budget and leaves {@code _search_started} false, so
   * {@code canAffordNewSearch()} reaches {@code hasLeakSignal()}; the gate's answer does not
   * depend on evaluation order relative to the BFS thread. The evaluation is bracketed by
   * candidate and pass-count reads so organic activity from the rest of this shared JVM can be
   * told apart from a contract violation (see {@link #checkNoCandidateFreeActivity}).
   */
  private static GateEvaluation evaluateGateAfterSearchReset() {
    // Sampled BEFORE the reset: a pass whose gate decision was made on an organic candidate
    // executes under the engine lock, so the decision and its pass counter increment can
    // straddle the reset (the counter is zeroed by the reset, and only at pass END - a long
    // in-flight pass is invisible to a stable-counter check). The candidate that legitimized
    // such a pass stays selectable from the population table - deliberately not reset here -
    // so reading it before the reset, while the decision is fresh, is what keeps the
    // candidateSeen bracket honest.
    int[] candidatesBefore = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    int passesBefore = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
    GateEvaluation e = new GateEvaluation();
    e.gateOpen = ReferenceChainTestHooks.shouldRunPassForTest0();
    int[] candidatesAfter = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
    e.passesAfter = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
    e.candidateSeen = !isEmpty(candidatesBefore) || !isEmpty(candidatesAfter);
    e.detail = "candidatesBefore=" + Arrays.toString(candidatesBefore) + " candidatesAfter="
        + Arrays.toString(candidatesAfter) + " passesBefore=" + passesBefore
        + " passesAfter=" + e.passesAfter;
    return e;
  }

  /**
   * Aborts only on an observed per-klass candidate: a candidate legitimately opens the gate, so
   * the candidate-gate contract cannot be isolated in that run. A BFS pass since the search reset
   * (the reset zeroes the pass count) with no candidate in either read means the gate opened
   * without a candidate - e.g. a re-introduced urgency bypass on the restarted BFS thread - and
   * must FAIL, not skip.
   */
  private static void checkNoCandidateFreeActivity(GateEvaluation e) {
    assumeFalse(e.candidateSeen, "Aborting: organic per-klass candidate around the direct "
        + "evaluation (" + e.detail + ") - the candidate-gate contract cannot be isolated in "
        + "this run");
    if (e.passesAfter != 0) {
      fail("A BFS pass ran after the search reset although no per-klass candidate was seen in "
          + "either read - the gate opened without a candidate (" + e.detail + ")");
    }
  }

  private static boolean isEmpty(int[] a) {
    return a == null || a.length == 0;
  }

  /**
   * Seeds ten heap-floor-ring samples rising fast enough that {@code secondsToOOM()}'s projection
   * lands well under {@code OOM_URGENT_THRESHOLD_S} (300s), with LivenessTracker's per-klass
   * population table left empty throughout. The burn-in stamp is backdated first, so the
   * projection is live in this shared JVM regardless of class ordering. Two positive controls
   * run before the negative assertion: the projection must be inside the urgent band, and the
   * gate evaluation must latch urgency - otherwise a closed gate would prove nothing. Then the
   * directly evaluated search gate must stay closed: the aggregate urgent-OOM projection must
   * never start a candidate-less search.
   *
   * <p>The live BFS thread is deliberately not watched over a wait window: its pass counter also
   * counts passes legitimately started by unrelated per-klass candidates in this shared JVM. The
   * run is aborted (not passed) when an organic candidate appears around the direct evaluation,
   * and fails when a BFS pass ran since the search reset without any candidate - the gate opened
   * without one.
   */
  @Test
  public void shouldNotOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    long savedActivationNs = ReferenceChainTestHooks.backdateLeakSignalActivationForTest0();
    try {
      // 1000 MiB fake max heap, rising from 100 MiB to 991 MiB over 9 (fake) seconds: ~99 MiB/s,
      // 9 MiB of headroom left at the last sample -> projected time-to-OOM ~= 9/99 s, far under
      // OOM_URGENT_THRESHOLD_S = 300s.
      ReferenceChainTestHooks.setMaxHeapBytesForTest0(1000L * 1024 * 1024);
      for (int i = 0; i < 10; i++) {
        long usedBytes = (100L + i * 99L) * 1024 * 1024;
        long timestampNs = i * 1_000_000_000L;
        ReferenceChainTestHooks.heapFloorRecordForTest0(usedBytes, timestampNs);
      }
      assertTrue(ReferenceChainTestHooks.heapFloorRisingForTest0(),
          "Precondition: the seeded samples must read as a sustained rise, so the projection "
              + "below is a genuine urgent-band one - the gate must stay closed for the "
              + "candidate requirement, not because the projection is unknown");

      // Positive control 1: past the backdated burn-in, the seeded rise must project inside the
      // urgent band. Fails fast, with the value, if the burn-in still masks the projection.
      double secondsToOom = ReferenceChainTestHooks.secondsToOOMForTest0();
      assertTrue(secondsToOom >= 0 && secondsToOom < OOM_URGENT_THRESHOLD_S,
          "Positive control: urgent band [0, " + OOM_URGENT_THRESHOLD_S + ")s required; got "
              + secondsToOom + " - the burn-in backdate did not take effect or the seeds no "
              + "longer project, so the closed gate below would prove nothing");

      GateEvaluation e = evaluateGateAfterSearchReset();
      checkNoCandidateFreeActivity(e);

      // Positive control 2: the gate evaluation must have latched urgency from the seeded
      // projection, so the gate is closed by the candidate requirement and not by a dormant
      // urgency machine.
      assertTrue(ReferenceChainTestHooks.urgentLatchedForTest0(),
          "Urgency must be latched after evaluating the gate on an urgent-band projection ("
              + secondsToOom + "s)");

      assertFalse(e.gateOpen,
          "Expected the search gate to stay closed: urgency is latched but no per-klass "
              + "candidate exists - only selectLeakCandidates() is a leak indication ("
              + e.detail + ")");
    } finally {
      restoreHeapFloorDefaults(savedActivationNs);
    }
  }

  /**
   * Control for the test above: same empty per-klass population table and same backdated
   * burn-in, but a flat heap floor (no growth). {@code secondsToOOM()} has nothing to project
   * from - asserted directly through {@code secondsToOOMForTest0()}, and because the burn-in is
   * backdated the "no projection" comes from the flat ring, not from the burn-in - so urgency
   * must not latch and the gate must stay closed. This complements the primary test's
   * urgent-band case with the no-projection case.
   *
   * <p>The gate's closed answer alone cannot tell the two cases apart: under the candidate-gate
   * contract {@code hasLeakSignal()} answers only from {@code selectLeakCandidates()}, so with an
   * empty population table the gate stays closed whatever the projection says. A stubbed or
   * dormant {@code secondsToOOM()} is caught instead by the direct projection reads (urgent band
   * above, none here) and by the urgency-latch reads after each gate evaluation.
   */
  @Test
  public void shouldNotOpenSearchGateOnFlatHeapFloorWithNoLeakCandidate() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    long savedActivationNs = ReferenceChainTestHooks.backdateLeakSignalActivationForTest0();
    try {
      ReferenceChainTestHooks.setMaxHeapBytesForTest0(1000L * 1024 * 1024);
      for (int i = 0; i < 10; i++) {
        ReferenceChainTestHooks.heapFloorRecordForTest0(200L * 1024 * 1024, i * 1_000_000_000L);
      }

      double secondsToOom = ReferenceChainTestHooks.secondsToOOMForTest0();
      assertTrue(secondsToOom < 0,
          "Control precondition: past the backdated burn-in, a flat heap floor must yield no "
              + "projection; got secondsToOOM=" + secondsToOom);

      // Only the search is reset right before the gate call (inside
      // evaluateGateAfterSearchReset()), not the population: resetKlassPopulationForTest0() also
      // zeroes the heap-floor ring seeded above, which would turn this control into a trivial
      // "insufficient fill" pass.
      GateEvaluation e = evaluateGateAfterSearchReset();
      checkNoCandidateFreeActivity(e);

      assertFalse(ReferenceChainTestHooks.urgentLatchedForTest0(),
          "A flat heap floor gives no projection, so it must leave urgency unlatched");
      assertFalse(e.gateOpen,
          "Expected the search-restart gate to stay closed: no heap growth and no per-klass "
              + "candidate give hasLeakSignal() nothing to trust (" + e.detail + ")");
    } finally {
      restoreHeapFloorDefaults(savedActivationNs);
    }
  }

  /**
   * Guards the burn-in stamp handling in {@link #restoreHeapFloorDefaults(long)}: the
   * {@link #ACTIVATION_STAMP_UNCHANGED} sentinel must leave the stamp alone (and never be written
   * as a stamp), and a saved stamp must be restored exactly. Fails if the helper drops the
   * stamp-restore step, restores on the sentinel, or the JNI setter is a no-op.
   */
  @Test
  public void shouldRestoreActivationStampOnlyWhenRequested() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    long savedActivationNs = ReferenceChainTestHooks.backdateLeakSignalActivationForTest0();
    long afterSentinel;
    try {
      // Must leave the backdate in place.
      restoreHeapFloorDefaults(ACTIVATION_STAMP_UNCHANGED);
      ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
      // Reads the stamp the sentinel path left behind (and backdates again; the finally block
      // below restores the original).
      afterSentinel = ReferenceChainTestHooks.backdateLeakSignalActivationForTest0();
    } finally {
      restoreHeapFloorDefaults(savedActivationNs);
    }
    long afterRestore = ReferenceChainTestHooks.backdateLeakSignalActivationForTest0();
    // Undo the probe's own backdate.
    ReferenceChainTestHooks.setLeakSignalActivatedNsForTest0(afterRestore);
    assertNotEquals(ACTIVATION_STAMP_UNCHANGED, afterSentinel,
        "The sentinel must never be written as a stamp");
    assertNotEquals(savedActivationNs, afterSentinel,
        "The sentinel path must not restore the stamp");
    assertEquals(savedActivationNs, afterRestore,
        "restoreHeapFloorDefaults(saved) must restore the stamp");
  }

  /**
   * Kills a no-op'd {@code heapFloorResetForTest0()} mutation: every other call site resets in
   * a finally block that no assertion observes, so without this test a reset whose body was
   * dropped (or whose JNI entry was left as the release stub) would leave the whole suite
   * green while leaking one test's seeded samples into the next test's JVM. The rising-then-
   * empty pair is asserted directly through {@code heapFloorRising()}, the ring's trend read, so
   * the reset's effect is checked, not assumed.
   */
  @Test
  public void shouldEmptyHeapFloorRingOnReset() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      // Same rising seeds as shouldNotOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate:
      // 100 MiB to 991 MiB over 9 fake seconds, which clears heapFloorRising()'s growth and
      // floor bars at exactly the min-fill trend window (fill = 10 samples).
      for (int i = 0; i < 10; i++) {
        long usedBytes = (100L + i * 99L) * 1024 * 1024;
        long timestampNs = i * 1_000_000_000L;
        ReferenceChainTestHooks.heapFloorRecordForTest0(usedBytes, timestampNs);
      }
      assertTrue(ReferenceChainTestHooks.heapFloorRisingForTest0(),
          "Precondition: the seeded samples must read as a sustained rise before the reset");
      ReferenceChainTestHooks.heapFloorResetForTest0();
      assertFalse(ReferenceChainTestHooks.heapFloorRisingForTest0(),
          "heapFloorResetForTest0() must empty the ring: fill = 0 falls below the min-fill "
              + "trend gate heapFloorRising() requires");
    } finally {
      // Ring reset first, while recording is still disabled; the shared helper owns the rest of
      // the ordering (max heap, population ring, search reset, re-enable recording). This test
      // never backdates the burn-in stamp.
      ReferenceChainTestHooks.heapFloorResetForTest0();
      restoreHeapFloorDefaults(ACTIVATION_STAMP_UNCHANGED);
    }
  }
}
