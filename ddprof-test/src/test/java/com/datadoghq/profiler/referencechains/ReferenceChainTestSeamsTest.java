/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * {@code ReferenceChainTrackingTest} exercises {@code LivenessTracker}'s probabilistic slope
 * detection and {@code ReferenceChainTracker}'s root-seeded BFS discovery together, which is
 * reliable only when both line up within the same retry window. This class decouples them via the
 * debug-build-only seams on {@link JavaProfiler} (javaApi.cpp), verifying each in isolation:
 * <ul>
 *   <li>{@link #shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope()} - asserts a slope signal
 *   would fire from directly-seeded population history, with no allocation sampling involved.</li>
 *   <li>{@link #shouldReconstructChainForDirectlyTaggedRoot()} - asserts the BFS/chain-
 *   reconstruction/event-emission path fires for a directly-tagged, known live object, with no
 *   dependency on {@code selectLeakCandidates()} organically picking the right klass.</li>
 * </ul>
 *
 * <p>Only runs under -DDEBUG native builds (debug/asan/tsan) - the backing native methods are
 * no-op stubs in a release build (javaApi.cpp's {@code #ifdef DEBUG} guard).
 */
public class ReferenceChainTestSeamsTest extends AbstractProfilerTest {

  // Arbitrary klass ids, opaque to the population table except when a representative is set:
  // that aliases the representative's real class id onto the synthetic id, so the chain test
  // targets a unique nested class - a real entry with existing (noisy) history, e.g.
  // java.lang.Object's, would outrank the seeded ramp.
  private static final int SLOPE_TEST_KLASS_ID = 987001;
  private static final int CHAIN_TEST_KLASS_ID = 987002;

  /** Unique class for {@link #shouldReconstructChainForDirectlyTaggedRoot()}'s target. */
  private static final class ChainTarget {}

  /**
   * Durable root for {@link #shouldReconstructChainForDirectlyTaggedRoot()}'s target: the
   * noise gate (suppressChainEvent) drops depth&lt;2 chains whose root is transient (stack/JNI
   * local), so a static holder is required for the chain event to be emitted at all.
   */
  private static Object chainTargetHolder;

  @Override
  protected String getProfilerCommand() {
    // generations=true: required for selectLeakCandidates() to return anything, real or seeded.
    // referencechains=true: constructs the FrontierTable the seams insert into.
    // framecap=2000000: the first pass's IterateOverReachableObjects admits every GC root in the
    // JVM, and a small framecap fills with them before the tagged root is expanded, abandoning
    // with FRONTIER_CAP and no chain event.
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  private static void assumeDebugBuild() {
    assumeTrue(ReferenceChainAssertions.isDebugInstrumentedBuild());
  }

  /**
   * Seeds twenty epochs of strictly increasing population counts for {@link #SLOPE_TEST_KLASS_ID}
   * directly into LivenessTracker's ring buffer - bypassing real allocation sampling entirely -
   * then asserts {@code selectLeakCandidates()} ranks it as a leak candidate. This is the "assert
   * a slope signal would be generated" seam: it proves the ranking logic itself works without
   * depending on the real JVMTI heap sampler ever surfacing this specific klass.
   */
  @Test
  public void shouldSelectSeededKlassAsLeakCandidateOnPositiveSlope() {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.setGcGenerationsEnabled0(true);

    // KLASS_POPULATION_MIN_FILL_FOR_TREND = 10 only makes a trend eligible; selectLeakCandidates()
    // also needs LEAK_TREND_HYSTERESIS_BASE = 5 consecutive qualifying epochs, so at least
    // 10 + (5 - 1) = 14 increasing samples are needed; 20 gives headroom.
    for (int epoch = 1; epoch <= 20; epoch++) {
      ReferenceChainTestHooks.seedKlassPopulationSample0(SLOPE_TEST_KLASS_ID, epoch * 10, epoch);
      // selectLeakCandidates() also requires a qualifying allocating thread. No tracked instance
      // needs to match here, so a fixed synthetic tid suffices.
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

  /**
   * Tags a real, live, caller-chosen object directly as a reference-chain frontier root
   * (bypassing ReferenceChainTracker's normal root-seeded discovery walk), wires it in as a
   * seeded leak candidate's representative, then drives one BFS pass and one poll cycle
   * synchronously. This is the "trigger the refchain on a known live heap sample" seam: it
   * proves {@code runPass()}/{@code pollWatchedTargets()}/{@code buildChainEvent()} correctly
   * produce a chain event whose leaf is this test's {@link ChainTarget}, decoupled from whether
   * LivenessTracker's probabilistic sampler would have picked the same object on its own. Only
   * chains with a {@code ChainTarget} leaf count, so a chain another test left cached in this
   * shared JVM cannot satisfy the assertion.
   */
  @Test
  public void shouldReconstructChainForDirectlyTaggedRoot() {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetKlassPopulationForTest0();
    ReferenceChainTestHooks.setGcGenerationsEnabled0(true);
    // Guards against inheriting a full/tiny FrontierTable from an earlier test in this
    // no-forkEvery JVM (e.g. ReferenceChainTrackingTest's framecap=1 abandonment test), against
    // which tagAsReferenceChainRoot0()'s insert() could fail.
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();

    // Referenced only through the static holder, never a local: a local would make the target a
    // stack-local GC root for the whole test body, and the noise gate suppresses chains rooted in
    // a transient stack slot.
    chainTargetHolder = new ChainTarget();

    // Representative before seeding: setting it registers the synthetic->real id alias, so the
    // seeds land under the target's real class id.
    ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(CHAIN_TEST_KLASS_ID, chainTargetHolder);

    // 20 epochs to clear the hysteresis gate - see the slope test above.
    for (int epoch = 1; epoch <= 20; epoch++) {
      ReferenceChainTestHooks.seedKlassPopulationSample0(CHAIN_TEST_KLASS_ID, epoch * 10, epoch);
      // This thread's real tid, since the target was allocated here. Belt-and-braces: the
      // chain's primary path is the directly-tagged root plus the seeded representative.
      ReferenceChainTestHooks.seedTidTrendSample0(
          CHAIN_TEST_KLASS_ID, ReferenceChainTestHooks.getTid(), epoch * 3, epoch);
    }

    // Poll before the direct tag: it admits the seeded klass as a watched candidate, and
    // tagAsRootForTest's recordDiscoveredInstance only lands when a candidate slot already
    // watches the klass.
    ReferenceChainTestHooks.pollReferenceChainTargets0();

    long tag = ReferenceChainTestHooks.tagAsReferenceChainRoot0(chainTargetHolder);
    assertTrue(tag > 0, "Expected tagAsReferenceChainRoot0 to assign a valid frontier tag");

    // One pass is not enough: admitStaticFieldRoots() sweeps loaded classes in budget-bounded
    // chunks, and the target's durable root_kind is only discovered on the pass whose chunk
    // covers ChainTarget's holder class. 40 passes give several full sweep laps of headroom
    // (~10 passes for ~4000 classes). The engine lock (runPassSerialized/
    // pollWatchedTargetsSerialized) keeps the BFS thread from racing these calls.
    int eventCount = 0;
    for (int pass = 0; pass < 40 && eventCount == 0; pass++) {
      boolean sawPassRun = ReferenceChainTestHooks.runReferenceChainPass0();
      assertTrue(sawPassRun || pass > 0,
          "Expected the first runReferenceChainPass0 to run (reference chains enabled)");
      ReferenceChainTestHooks.pollReferenceChainTargets0();
      eventCount = ReferenceChainTestHooks.drainReferenceChainEventCountForLeaf0(chainTargetHolder);
    }
    assertTrue(eventCount > 0,
        "Expected pollWatchedTargets() to have queued at least one chain event whose leaf is "
            + "ChainTarget (the directly-tagged, seeded-representative target)");
    chainTargetHolder = null; // shared-JVM hygiene
  }
}
