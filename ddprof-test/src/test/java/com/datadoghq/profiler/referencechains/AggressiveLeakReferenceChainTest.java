/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
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
 * empty. Staging recordings showed the pre-fix behavior - the urgent latch entitled a
 * candidate-less search that cannot exit early and ran whole-heap BFS passes to the auto-tuned
 * TTL with zero chains to show for it.
 *
 * <p>Reproducing a genuine near-OOM heap in this shared, no-{@code forkEvery} test JVM is
 * impractical (see {@link ReferenceChainTrackingTest}'s own header comment on the JVM this class
 * shares with every other {@code ddprof-test} class). The debug-only
 * {@code heapFloorRecordForTest0()}/{@code setMaxHeapBytesForTest0()} seams (javaApi.cpp) instead
 * seed {@code LivenessTracker}'s aggregate heap-floor-ring history and its max-heap-bytes cache
 * directly, so {@code secondsToOOM()}'s projection can be driven under
 * {@code OOM_URGENT_THRESHOLD_S} (referenceChains.h) deterministically, decoupled from this JVM's
 * real {@code -Xmx} and from real GC timing. {@code shouldRunPassForTest0()} then evaluates
 * {@code ReferenceChainTracker::shouldRunPass()} - the gate {@code hasLeakSignal()} feeds -
 * directly, rather than running a real pass, so this class never depends on
 * {@code selectLeakCandidates()} ranking anything, a real JVMTI heap walk, or a JFR event.
 */
public class AggressiveLeakReferenceChainTest extends AbstractProfilerTest {

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
   * see it. {@code resetKlassPopulationForTest0()} also zeroes LivenessTracker's heap-floor ring
   * (head/fill - {@code klassPopulationResetForTest()}, livenessTracker.h), so
   * {@code secondsToOOM()} reports "insufficient fill" until real GC samples build up again; it
   * runs while heap-floor recording is still disabled so no real sample can interleave.
   * {@code resetReferenceChainSearchForTest0()} then clears any urgency latch plus the search
   * state an earlier evaluation started - after the ring reset, so the BFS thread cannot
   * re-latch from the stale projection. Recording is re-enabled last.
   */
  private static void restoreHeapFloorDefaults() {
    ReferenceChainTestHooks.setMaxHeapBytesForTest0(-1);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(true);
  }

  /**
   * Seeds ten heap-floor-ring samples rising fast enough that {@code secondsToOOM()}'s projection
   * lands well under {@code OOM_URGENT_THRESHOLD_S} (300s), with LivenessTracker's per-klass
   * population table left empty throughout - {@code selectLeakCandidateKlassIds0()} returns
   * nothing at any point in this test. Then asserts the search-restart gate stays closed on the
   * live BFS thread: the aggregate urgent-OOM projection must never start a candidate-less
   * search.
   *
   * <p>The gate is asserted both through the live BFS thread (no pass may run within the wait
   * window) and through a direct {@code shouldRunPassForTest0()} call after a search reset. The
   * direct call is race-free under the candidate-gate contract - the old one-shot urgency
   * entitlement ({@code _urgent_search_spent}) that made a direct call lose a race against the
   * BFS thread was removed together with the bypass itself, and the gate's answer no longer
   * depends on evaluation order.
   */
  @Test
  public void shouldNotOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate()
      throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
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

      int[] candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "This test's own precondition: no per-klass candidate should exist, so a pass running "
              + "below could only come from the aggregate urgent-OOM projection");

      // Idle BFS cadence is ~1s/pass. No pass may run: with zero per-klass candidates the gate
      // has no indication, and urgency alone must not supply one.
      int passesBefore = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
      long deadline = System.currentTimeMillis() + 5_000;
      while (System.currentTimeMillis() < deadline) {
        assertTrue(ReferenceChainTestHooks.referenceChainPassesRunForTest0() == passesBefore,
            "The BFS thread must stay idle: an urgent-OOM projection with zero per-klass leak "
                + "candidates must not start a search");
        Thread.sleep(50);
      }

      // Same assertion through the predicate itself, on a freshly reset search so any mutation
      // the live thread's evaluations made lands on clean state (see the flat-floor control
      // below for why the reset must not touch the population). This direct call is race-free:
      // the gate's answer no longer depends on evaluation order.
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
      assertFalse(ReferenceChainTestHooks.shouldRunPassForTest0(),
          "Expected the search-restart gate to stay closed: the urgent-OOM projection is not a "
              + "leak indication - only selectLeakCandidates() is");

      candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "The idle window must have kept the per-klass population table empty - the "
              + "aggregate urgent-OOM projection was the only signal this test seeded");
    } finally {
      restoreHeapFloorDefaults();
    }
  }

  /**
   * Same empty per-klass population table as above, but a flat heap floor (no growth at all) -
   * {@code secondsToOOM()} has nothing to project from, so this test's own gate must stay closed.
   * Without this control, a stubbed-out {@code secondsToOOM()} that always signals urgency would
   * pass the test above just as well.
   */
  @Test
  public void shouldNotOpenSearchGateOnFlatHeapFloorWithNoLeakCandidate() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      ReferenceChainTestHooks.setMaxHeapBytesForTest0(1000L * 1024 * 1024);
      for (int i = 0; i < 10; i++) {
        ReferenceChainTestHooks.heapFloorRecordForTest0(200L * 1024 * 1024, i * 1_000_000_000L);
      }

      int[] candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "This test's own precondition: no per-klass candidate should exist either");

      // shouldRunPassForTest0() is NOT a pure predicate (see JavaProfiler's own javadoc): under the
      // native engine lock it may account a finished search's pain, restart terminal search state,
      // or advance urgency bookkeeping. Reset the search right before it so any mutation
      // lands on a fresh tracker (_search_started == false) instead of whatever search an earlier
      // class in this shared JVM left behind. Only the search is reset here, not the population:
      // resetKlassPopulationForTest0() also zeroes the heap-floor ring seeded above, which would
      // turn this control into a trivial "insufficient fill" pass.
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
      boolean gateOpen = ReferenceChainTestHooks.shouldRunPassForTest0();
      assertFalse(gateOpen,
          "Expected the search-restart gate to stay closed: no heap growth and no per-klass "
              + "candidate give hasLeakSignal() nothing to trust");
    } finally {
      restoreHeapFloorDefaults();
    }
  }

  /**
   * Kills a no-op'd {@code heapFloorResetForTest0()} mutation: every other call site resets in
   * a finally block that no assertion observes, so without this test a reset whose body was
   * dropped (or whose JNI entry was left as the release stub) would leave the whole suite
   * green while leaking one test's seeded samples into the next test's JVM. The rising-then-
   * empty pair is asserted directly through {@code heapFloorRising()} - the same read the
   * aggregate gate uses - so the reset's effect is checked, not assumed.
   */
  @Test
  public void shouldEmptyHeapFloorRingOnReset() {
    assumeDebugBuild();
    ReferenceChainTestHooks.setHeapFloorRecordingForTest0(false);
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      // Same rising seeds as shouldOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate:
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
      // Same order as the other tests: ring reset first, still disabled.
      ReferenceChainTestHooks.heapFloorResetForTest0();
      ReferenceChainTestHooks.setHeapFloorRecordingForTest0(true);
    }
  }
}
