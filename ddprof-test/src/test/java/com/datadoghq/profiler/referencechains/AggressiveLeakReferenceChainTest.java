/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
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
   * Seeds ten heap-floor-ring samples rising fast enough that {@code secondsToOOM()}'s projection
   * lands well under {@code OOM_URGENT_THRESHOLD_S} (300s), with LivenessTracker's per-klass
   * population table left empty throughout - {@code selectLeakCandidateKlassIds0()} returns
   * nothing at any point in this test. Asserts the search-restart gate still opens, proving the
   * urgent-OOM projection alone - not a per-klass candidate - is what let it through.
   */
  @Test
  public void shouldOpenSearchGateOnAggressiveHeapWideGrowthWithNoLeakCandidate() {
    assumeDebugBuild();
    JavaProfiler.resetKlassPopulationForTest0();
    JavaProfiler.resetReferenceChainSearchForTest0();
    try {
      // 1000 MiB fake max heap, rising from 100 MiB to 991 MiB over 9 (fake) seconds: ~99 MiB/s,
      // 9 MiB of headroom left at the last sample -> projected time-to-OOM ~= 9/99 s, far under
      // OOM_URGENT_THRESHOLD_S = 300s.
      JavaProfiler.setMaxHeapBytesForTest0(1000L * 1024 * 1024);
      for (int i = 0; i < 10; i++) {
        long usedBytes = (100L + i * 99L) * 1024 * 1024;
        long timestampNs = i * 1_000_000_000L;
        JavaProfiler.heapFloorRecordForTest0(usedBytes, timestampNs);
      }

      int[] candidates = JavaProfiler.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "This test's own precondition: no per-klass candidate should exist, so a true result "
              + "below can only come from the aggregate urgent-OOM bypass");

      assertTrue(JavaProfiler.shouldRunPassForTest0(),
          "Expected the search-restart gate to open from the urgent heap-wide OOM projection "
              + "alone, with zero per-klass leak candidate");
    } finally {
      JavaProfiler.setMaxHeapBytesForTest0(-1);
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
    JavaProfiler.resetKlassPopulationForTest0();
    JavaProfiler.resetReferenceChainSearchForTest0();
    try {
      JavaProfiler.setMaxHeapBytesForTest0(1000L * 1024 * 1024);
      for (int i = 0; i < 10; i++) {
        JavaProfiler.heapFloorRecordForTest0(200L * 1024 * 1024, i * 1_000_000_000L);
      }

      int[] candidates = JavaProfiler.selectLeakCandidateKlassIds0();
      assertTrue(candidates == null || candidates.length == 0,
          "This test's own precondition: no per-klass candidate should exist either");

      assertFalse(JavaProfiler.shouldRunPassForTest0(),
          "Expected the search-restart gate to stay closed: no heap growth and no per-klass "
              + "candidate give hasLeakSignal() nothing to trust");
    } finally {
      JavaProfiler.setMaxHeapBytesForTest0(-1);
    }
  }
}
