/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * PROF-15341 follow-up: {@code ReferenceChainTrackingTest} exercises {@code LivenessTracker}'s
 * probabilistic allocation-sampling-driven slope detection and {@code ReferenceChainTracker}'s
 * root-seeded BFS discovery together, in one real-JVM run - reliable only when both mechanisms
 * happen to line up within the same bounded retry window. This class decouples them via the
 * debug-build-only test seams on {@link JavaProfiler} (backed by {@code LivenessTracker}'s
 * existing {@code *ForTest} seams and a new {@code ReferenceChainTracker::tagAsRootForTest()},
 * see javaApi.cpp), so each mechanism can be verified end-to-end in isolation:
 * <ul>
 *   <li>{@link #shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope()} - asserts a slope signal
 *   would fire from directly-seeded population history, with no allocation sampling involved.</li>
 *   <li>{@link #shouldReconstructChainForDirectlyTaggedRoot()} - asserts the BFS/chain-
 *   reconstruction/event-emission path fires for a directly-tagged, known live object, with no
 *   dependency on {@code selectLeakCandidates()} organically picking the right klass.</li>
 * </ul>
 *
 * <p>Only runs under the debug native build ({@code testdebug}) - the backing native methods do
 * not exist in a release build (see javaApi.cpp's {@code #ifdef DEBUG} guard), mirroring
 * {@code JVMAccessTest}'s own {@code "debug".equals(System.getProperty("ddprof_test.config"))}
 * pattern for the same reason.
 */
public class ReferenceChainTestSeamsTest extends AbstractProfilerTest {

  // Arbitrary, test-chosen klass ids - LivenessTracker's population table treats them as opaque
  // keys (see KlassPopulationEntry's own comment), so these need not resolve to any real class.
  private static final int SLOPE_TEST_KLASS_ID = 987001;
  private static final int CHAIN_TEST_KLASS_ID = 987002;

  @Override
  protected String getProfilerCommand() {
    // generations=true: gates LivenessTracker's population tracking (gcGenerationsEnabled()) -
    // required for selectLeakCandidates() to return anything at all, real or seeded.
    // referencechains=true: constructs ReferenceChainTracker's FrontierTable so
    // tagAsReferenceChainRoot0()/runReferenceChainPass0() have a table to insert into.
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=1024";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue("debug".equals(System.getProperty("ddprof_test.config")));
  }

  /**
   * Seeds ten epochs of strictly increasing population counts for {@link #SLOPE_TEST_KLASS_ID}
   * directly into LivenessTracker's ring buffer - bypassing real allocation sampling entirely -
   * then asserts {@code selectLeakCandidates()} ranks it as a leak candidate. This is the "assert
   * a slope signal would be generated" seam: it proves the ranking logic itself works without
   * depending on the real JVMTI heap sampler ever surfacing this specific klass.
   */
  @Test
  public void shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope() {
    assumeDebugBuild();
    JavaProfiler.resetKlassPopulationForTest0();
    JavaProfiler.setGcGenerationsEnabled0(true);

    // KLASS_POPULATION_MIN_FILL_FOR_TREND = 10 (livenessTracker.h) - computeKlassPopulationSlope()
    // ignores any entry with fewer samples than this, so 10 strictly increasing counts are needed
    // to make the trend both eligible and unambiguously positive.
    for (int epoch = 1; epoch <= 10; epoch++) {
      JavaProfiler.seedKlassPopulationSample0(SLOPE_TEST_KLASS_ID, epoch * 10, epoch);
    }

    int[] candidates = JavaProfiler.selectLeakCandidateKlassIds0();
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

  /**
   * Tags a real, live, caller-chosen object directly as a reference-chain frontier root
   * (bypassing ReferenceChainTracker's normal root-seeded discovery walk), wires it in as a
   * seeded leak candidate's representative, then drives one BFS pass and one poll cycle
   * synchronously. This is the "trigger the refchain on a known live heap sample" seam: it
   * proves {@code runPass()}/{@code pollWatchedTargets()}/{@code buildChainEvent()} correctly
   * produce a chain event for a target this test controls directly, decoupled from whether
   * LivenessTracker's probabilistic sampler would have picked the same object on its own.
   */
  @Test
  public void shouldReconstructChainForDirectlyTaggedRoot() {
    assumeDebugBuild();
    JavaProfiler.resetKlassPopulationForTest0();
    JavaProfiler.setGcGenerationsEnabled0(true);
    // Guards against inheriting a FrontierTable an earlier test in this same, no-forkEvery
    // JVM left permanently full/tiny - e.g. ReferenceChainTrackingTest's own
    // shouldReportAbandonedSearchOnTinyFrontierCap deliberately drives the shared table to
    // framecap=1 and leaves it that way. Same defensive pattern that class's own tests already
    // use (see its header comment); without it, tagAsReferenceChainRoot0()'s insert() below can
    // fail against a table this test never sized itself.
    JavaProfiler.resetReferenceChainSearchForTest0();

    Object target = new Object();

    long tag = JavaProfiler.tagAsReferenceChainRoot0(target);
    assertTrue(tag > 0, "Expected tagAsReferenceChainRoot0 to assign a valid frontier tag");

    for (int epoch = 1; epoch <= 10; epoch++) {
      JavaProfiler.seedKlassPopulationSample0(CHAIN_TEST_KLASS_ID, epoch * 10, epoch);
    }
    JavaProfiler.setKlassPopulationRepresentativeForTest0(CHAIN_TEST_KLASS_ID, target);

    boolean sawPassRun = JavaProfiler.runReferenceChainPass0();
    assertTrue(sawPassRun, "Expected runReferenceChainPass0 to run (reference chains enabled)");

    JavaProfiler.pollReferenceChainTargets0();

    int eventCount = JavaProfiler.drainReferenceChainEventCount0();
    assertTrue(eventCount > 0,
        "Expected pollWatchedTargets() to have queued at least one chain event for the "
            + "directly-tagged, seeded-representative target");
    assertTrue(!target.equals(null)); // keeps target reachable until here
  }
}
