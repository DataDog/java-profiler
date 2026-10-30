/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.junit.jupiter.api.Test;

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.assumeDebugBuild;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * PROF-15341 follow-up: {@code ReferenceChainTrackingTest} drives slope detection and chain
 * reconstruction together and only passes when both happen to line up. This class decouples
 * them via the debug-build-only test seams on {@code JavaProfiler}, reached via
 * {@link ReferenceChainTestHooks} (backed by {@code LivenessTracker}'s existing
 * {@code *ForTest} seams and {@code ReferenceChainTracker::tagAsRootForTest()}, see javaApi.cpp):
 * <ul>
 *   <li>{@link #shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope()} - slope signal from
 *   directly-seeded population history, no allocation sampling involved.</li>
 *   <li>{@link #shouldReconstructChainForDirectlyTaggedRoot()} - BFS/chain-reconstruction/
 *   event-emission for a directly-tagged, known live object, without depending on
 *   {@code selectLeakCandidates()} organically picking the right klass.</li>
 * </ul>
 *
 * <p>Only runs under the debug native build ({@code testdebug}) - the backing native methods do
 * not exist in a release build (see javaApi.cpp's {@code #ifdef DEBUG} guard), same pattern as
 * {@code JVMAccessTest}.
 */
public class ReferenceChainTestSeamsTest extends AbstractProfilerTest {

  // Arbitrary, test-chosen klass ids. setKlassPopulationRepresentativeForTest() aliases the
  // representative's REAL class id onto the seeded synthetic id, so the chain test must target
  // a class whose real population entry does not already exist - otherwise the real entry's
  // genuine history outranks the seeded ramp.
  private static final int SLOPE_TEST_KLASS_ID = 987001;
  private static final int CHAIN_TEST_KLASS_ID = 987002;

  private static final class ChainTarget {}

  // The target must be reachable ONLY through this static holder (nulled in a finally so the
  // next test in this no-forkEvery JVM does not inherit the reference). Binding it to a live
  // local would make it a STACK_LOCAL root for the whole test body, and the noise gate
  // (suppressChainEvent) drops depth<2 chains rooted in a transient stack slot - holding it
  // statically (the canonical leak shape) is required for the chain event to be emitted at all.
  private static Object chainTargetHolder;

  @Override
  protected String getProfilerCommand() {
    // framecap=2000000 (not 1024): the first BFS pass runs IterateOverReachableObjects, which
    // admits every GC root in the whole JVM into the frontier; a small framecap fills with that
    // ambient count before the tagged root gets to expandFrontier(), hitting FRONTIER_CAP with
    // no chain event queued. Same value as ReferenceChainTrackingTest's success-path tests.
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  /** Seeds twenty epochs of strictly increasing population counts, then asserts
   *  {@code selectLeakCandidates()} ranks the klass as a leak candidate - proving the ranking
   *  logic works without the real JVMTI heap sampler ever surfacing this klass. */
  @Test
  public void shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope() {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.setGcGenerationsEnabled0(true);

    // selectLeakCandidates() requires consecutive_positive to reach LEAK_TREND_HYSTERESIS_BASE
    // = 5 epochs on top of KLASS_POPULATION_MIN_FILL_FOR_TREND = 10, so at least 14 strictly
    // increasing samples are needed; 20 gives headroom.
    for (int epoch = 1; epoch <= 20; epoch++) {
      ReferenceChainTestHooks.seedKlassPopulationSample0(SLOPE_TEST_KLASS_ID, epoch * 10, epoch);
      // Fixed synthetic tid suffices: this test only asserts the klass-level candidate list.
      ReferenceChainTestHooks.seedTidTrendSample0(SLOPE_TEST_KLASS_ID, 4242, epoch * 3, epoch);
    }

    int[] candidates = ReferenceChainTestHooks.selectLeakCandidateKlassIds0();
    boolean found = false;
    for (int klassId : candidates) {
      if (klassId == SLOPE_TEST_KLASS_ID) {
        found = true;
        break;
      }
    }
    assertTrue(found, "Expected klass id " + SLOPE_TEST_KLASS_ID
        + " to be selected as a leak candidate after a seeded positive-slope population history");
  }

  /** Tags a live object directly as a frontier root (bypassing the normal root-seeded
   *  discovery walk), wires it in as a seeded leak candidate's representative, then drives
   *  pass/poll cycles synchronously - proving {@code runPass()}/{@code pollWatchedTargets()}/
   *  {@code buildChainEvent()} produce a chain event for a target this test controls directly. */
  @Test
  public void shouldReconstructChainForDirectlyTaggedRoot() {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.setGcGenerationsEnabled0(true);
    // Guards against inheriting a FrontierTable an earlier test in this same, no-forkEvery
    // JVM left permanently full/tiny - e.g. ReferenceChainTrackingTest's
    // shouldReportAbandonedSearchOnTinyFrontierCap drives the shared table to framecap=1 and
    // leaves it that way; without the reset, insert() below can fail.
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();

    chainTargetHolder = new ChainTarget();
    try {
      // Representative BEFORE seeding: setting it registers the synthetic->real id alias, so
      // the seeding below lands re-keyed under the target's real class id.
      ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(
          CHAIN_TEST_KLASS_ID, chainTargetHolder);

      // See shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope()'s comment above for why 20
      // (not just KLASS_POPULATION_MIN_FILL_FOR_TREND = 10) is needed to clear the hysteresis gate.
      for (int epoch = 1; epoch <= 20; epoch++) {
        ReferenceChainTestHooks.seedKlassPopulationSample0(CHAIN_TEST_KLASS_ID, epoch * 10, epoch);
        // Belt-and-braces: seed THIS thread's real tid so any path hinging on leak tagging
        // of the target as a tracked instance finds a qualifying tid.
        ReferenceChainTestHooks.seedTidTrendSample0(
            CHAIN_TEST_KLASS_ID, ReferenceChainTestHooks.getTid(), epoch * 3, epoch);
      }

      // One poll BEFORE the direct tag: the first poll admits the seeded klass as a watched
      // candidate, and tagAsRootForTest's recordDiscoveredInstance only lands when a candidate
      // slot already watches the klass - the marker-tag path the original pre-poll tag rode is
      // gone in the leak-tag redesign.
      ReferenceChainTestHooks.pollReferenceChainTargets0();

      long tag = ReferenceChainTestHooks.tagAsReferenceChainRoot0(chainTargetHolder);
      assertTrue(tag > 0, "Expected tagAsReferenceChainRoot0 to assign a valid frontier tag");

      // One pass is NOT enough: admitStaticFieldRoots() sweeps loaded classes in chunks and
      // the first pass truncates before reaching this test's class - the durable static-field
      // root discovery that upgrades the target's root_kind only happens on the pass whose
      // chunk covers ChainTarget's holder class. 40 gives the full sweep lap (~10 passes for
      // ~4000 loaded classes) several round trips of headroom; the engine lock keeps the BFS
      // thread from racing these calls.
      int eventCount = 0;
      for (int pass = 0; pass < 40 && eventCount == 0; pass++) {
        boolean sawPassRun = ReferenceChainTestHooks.runReferenceChainPass0();
        assertTrue(sawPassRun || pass > 0,
            "Expected the first runReferenceChainPass0 to run (reference chains enabled)");
        ReferenceChainTestHooks.pollReferenceChainTargets0();
        eventCount = ReferenceChainTestHooks.drainReferenceChainEventCount0();
      }
      assertTrue(eventCount > 0,
          "Expected pollWatchedTargets() to have queued at least one chain event for the "
              + "directly-tagged, seeded-representative target");
    } finally {
      chainTargetHolder = null; // shared-JVM hygiene
    }
  }
}
