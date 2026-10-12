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
 * E2E coverage for {@code LivenessTracker::secondsToOOM()}'s urgent-OOM bypass
 * ({@code ReferenceChainTracker::hasLeakSignal()}, referenceChains.cpp). Complements
 * {@link ReferenceChainTrackingTest}'s organic coverage of a slow leak - a gradually-growing
 * population that clears {@code selectLeakCandidates()}'s per-klass hysteresis gate over many
 * rounds - with the opposite, previously-unexercised case: a heap-wide leak growing fast enough
 * that a real deployment would OOM before any single klass's own population history ever clears
 * that same hysteresis gate.
 *
 * <p>Reproducing a genuine near-OOM heap in this shared, no-{@code forkEvery} test JVM is
 * impractical (see {@link ReferenceChainTrackingTest}'s own header comment on the JVM this class
 * shares with every other {@code ddprof-test} class). The debug-only
 * {@code heapFloorRecordForTest0()}/{@code setMaxHeapBytesForTest0()} seams (javaApi.cpp) instead
 * seed {@code LivenessTracker}'s aggregate heap-floor-ring history and its max-heap-bytes cache
 * directly, so {@code secondsToOOM()}'s projection can be driven under
 * {@code OOM_URGENT_THRESHOLD_S} (referenceChains.h) deterministically, decoupled from this JVM's
 * real {@code -Xmx} and from real GC timing. {@code shouldRunPassForTest0()} then reads
 * {@code ReferenceChainTracker::shouldRunPass()} - the search-restart gate {@code hasLeakSignal()}
 * feeds - directly, rather than running a real pass, so this class never depends on
 * {@code selectLeakCandidates()} ranking anything, a real JVMTI heap walk, or a JFR event.
 */
public class AggressiveLeakReferenceChainTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    // generations=true: gates LivenessTracker::gcGenerationsEnabled() - hasLeakSignal() (which
    // shouldRunPassForTest0() ultimately reads) short-circuits to true immediately when this is
    // unset (its own first check, referenceChains.cpp), which would make every test below
    // trivially pass regardless of the urgent-OOM bypass this class exists to exercise.
    // referencechains=true: constructs the FrontierTable/ReferenceChainTracker singleton at all -
    // shouldRunPassForTest0() has nothing to read otherwise.
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    // Mirrors ReferenceChainTrackingTest's own guard - FollowReferences/tag-based frontier walking
    // assumes a HotSpot-shaped JVMTI heap implementation.
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue("debug".equals(System.getProperty("ddprof_test.config")),
        "heapFloorRecordForTest0/setMaxHeapBytesForTest0/shouldRunPassForTest0 only exist in a "
            + "debug native build (javaApi.cpp's #ifdef DEBUG guard)");
  }

  /**
   * Undoes this class's synthetic seeding so later tests in this shared, no-forkEvery JVM never
   * see it. {@code resetKlassPopulationForTest0()} also zeroes LivenessTracker's heap-floor ring
   * (head/fill - {@code klassPopulationResetForTest()}, livenessTracker.h), so
   * {@code secondsToOOM()} reports "insufficient fill" until real GC samples build up again; it
   * runs while heap-floor recording is still disabled so no real sample can interleave.
   * {@code resetReferenceChainSearchForTest0()} then clears any urgency latch and spent one-shot
   * entitlement ({@code _urgent_latched}/{@code _urgent_search_spent}) plus the search state the
   * urgent bypass started - after the ring reset, so the BFS thread cannot re-latch from the
   * stale projection. Recording is re-enabled last.
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
   * nothing at any point in this test. Then waits for the BFS thread to actually run passes,
   * proving the search-restart gate opened from the urgent-OOM projection alone.
   *
   * <p>The gate is asserted through the live BFS thread rather than by calling
   * {@code shouldRunPassForTest0()} directly: opening the gate spends the episode's one-shot
   * urgency entitlement ({@code _urgent_search_spent}) on the FIRST evaluation, and the BFS
   * thread - whose cadence ramps down to ~10ms once urgency latches - races the test's own
   * call for that first evaluation. A direct call therefore only returns true when it wins
   * that race, which made this test flaky by construction. A pass only ever runs after
   * {@code shouldRunPass()} returned true, and with {@code generations=true} plus a provably
   * empty per-klass population table the urgent-OOM projection is the only possible trigger -
   * so "passes ran while zero candidates existed" is the same assertion, without the race.
   */
  @Test
  public void shouldOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate()
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

      int[] candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "This test's own precondition: no per-klass candidate should exist, so passes running "
              + "below can only come from the aggregate urgent-OOM bypass");

      int passesBefore = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
      // Idle BFS cadence is ~1s/pass; urgency ramps it to ~10ms after the latch. 20s covers the
      // first evaluation landing up to one idle cadence after the seeding loop.
      long deadline = System.currentTimeMillis() + 20_000;
      while (ReferenceChainTestHooks.referenceChainPassesRunForTest0() == passesBefore
          && System.currentTimeMillis() < deadline) {
        Thread.sleep(50);
      }
      assertTrue(ReferenceChainTestHooks.referenceChainPassesRunForTest0() > passesBefore,
          "Expected the BFS thread to run passes from the urgent heap-wide OOM projection alone, "
              + "with zero per-klass leak candidate");

      candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "The passes that just ran must still have had zero per-klass candidates - the "
              + "aggregate urgent-OOM projection was the only possible trigger");
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

      assertFalse(ReferenceChainTestHooks.shouldRunPassForTest0(),
          "Expected the search-restart gate to stay closed: no heap growth and no per-klass "
              + "candidate give hasLeakSignal() nothing to trust");
    } finally {
      restoreHeapFloorDefaults();
    }
  }
}
