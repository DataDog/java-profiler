/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.junit.jupiter.api.Test;

import java.util.function.BooleanSupplier;

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.assumeDebugBuild;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Pins the two scheduling gates that bound the reference-chain tracker's JVMTI heap-walk
 * frequency on services with a high young-GC rate:
 * <ul>
 *   <li><b>Minimum pass spacing</b> ({@code shouldRunPass()}): every authorization lane - GC
 *   epoch, canary back-to-back, fallback cadence - waits out {@code _effective_cadence_ns} since
 *   the previous pass; otherwise pass rate tracks the GC rate.</li>
 *   <li><b>Adaptive root-enumeration interval</b> ({@code shouldRunRootEnum()}): re-enumeration
 *   waits out {@code ROOT_ENUM_MIN_INTERVAL_NS} extended by the last attempt's measured
 *   in-safepoint cost; otherwise a next-pass retry of a truncated attempt turns every pass into
 *   a deopt-all pass.</li>
 * </ul>
 *
 * <p>Only runs under the debug native build - the backing native methods do not exist in a
 * release build, same pattern as {@link ReferenceChainTestSeamsTest}.
 */
public class ReferenceChainSchedulingTest extends AbstractProfilerTest {

  // A cadence far above any timing jitter in these tests: with the spacing gate seeded to "the
  // previous pass just ended", the gate stays closed for the whole assertion window, and the BFS
  // thread - which reads the same cadence for its idle sleep - stays quiesced while the seeded
  // state is in force.
  private static final long CADENCE_MS = 10_000;
  // Long enough for any BFS iteration already in flight when a test seeds its state to finish
  // (post-reset the thread runs no pass: the search is not started and there is no leak signal,
  // so an iteration is two atomic loads and a sleep decision).
  private static final long QUIESCE_MS = 1_200;
  // Java mirrors of referenceChains.h's root-enumeration constants - no seam exposes them:
  // ROOT_ENUM_MIN_INTERVAL_NS, ROOT_ENUM_INTERVAL_NS_PER_COST_MS, ROOT_ENUM_MAX_INTERVAL_NS.
  // A native retune must update these mirrors. rootEnumBaseIntervalMatchesNative and the
  // floor-equality probes below pin all three against the live library, so a stale mirror fails
  // loudly instead of silently re-seeding the wrong regime.
  private static final long NS_PER_MS = 1_000_000L;
  private static final long ROOT_ENUM_MIN_INTERVAL_NS = 2_000_000_000L;
  private static final long ROOT_ENUM_NS_PER_COST_MS = 20_000_000L;
  private static final long ROOT_ENUM_MAX_INTERVAL_NS = 30_000_000_000L;
  // Seed ages either side of the base interval, and costs that extend / cap the floor.
  private static final long ROOT_ENUM_BEFORE_BASE_MS =
      ROOT_ENUM_MIN_INTERVAL_NS / NS_PER_MS - 1_000;
  private static final long ROOT_ENUM_PAST_BASE_MS =
      ROOT_ENUM_MIN_INTERVAL_NS / NS_PER_MS + 1_000;
  private static final long ROOT_ENUM_EXTENDING_COST_MS = 500;
  private static final long ROOT_ENUM_CAPPING_COST_MS = 5_000;
  // Seed age just past the cap: with the capping cost the floor is ROOT_ENUM_MAX_INTERVAL_NS, so
  // this age must open the gate (kills an uncapped floor).
  private static final long ROOT_ENUM_PAST_CAP_MS =
      ROOT_ENUM_MAX_INTERVAL_NS / NS_PER_MS + 1_000;

  @Override
  protected String getProfilerCommand() {
    return "generations=true,referencechains=true:hops=32:budget=500:ttl=60000:framecap=2000000";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  /**
   * Evaluates {@code probe} against re-seeded scheduling state, retrying while a concurrently
   * passing BFS thread invalidates the seed: a real pass overwrites {@code _last_pass_ns},
   * {@code _last_pass_gc_finish_epoch}, and the root-enumeration state with live values, and can
   * drive the real search terminal, which can only ever flip a seeded-open gate to the closed
   * reading - so a closed result is final and only an open/matching result needs the retry.
   * The same real pass also produces the closed reading on its own, so a closed-direction probe
   * (a negated gate reading) must be bracketed by a check that the seeded state is still in force
   * (see {@link #rootEnumClosedWithSeedIntact(long)}) - otherwise a closed result caused by a
   * real pass would be accepted instead of retried.
   */
  private static boolean eventuallyTrue(String message, Runnable seed,
                                        BooleanSupplier probe)
      throws InterruptedException {
    for (int i = 0; i < 50; i++) {
      seed.run();
      if (probe.getAsBoolean()) {
        return true;
      }
      Thread.sleep(100);
    }
    assertFalse(true, message + " (state re-seeded 50 times over ~5s, never observed)");
    return false;
  }

  /**
   * Closed-direction root-enum probe (see eventuallyTrue): a closed gate counts only while the
   * seeded floor is still in force. A concurrent real enumeration also closes the gate (it
   * refreshes _last_root_enum_ns to "now"), so a bare closed reading cannot tell the seeded floor
   * apart from that unrelated close. The two JNI calls take the engine lock separately; a real
   * pass landing between them either changes the floor (the equality fails and the probe
   * retries) or leaves it unchanged (the closed reading is still what the seeded floor predicts),
   * so that window can cause a retry, never a false accept.
   */
  private static boolean rootEnumClosedWithSeedIntact(long expectedFloorNs) {
    return !ReferenceChainTestHooks.shouldRunRootEnumForTest0(false)
        && ReferenceChainTestHooks.rootEnumIntervalFloorNsForTest0() == expectedFloorNs;
  }

  /** Seed relations the root-enum tests rely on, checked on the Java mirrors themselves. */
  private static void assertRootEnumSeedAssumptions() {
    long pastBaseNs = ROOT_ENUM_PAST_BASE_MS * NS_PER_MS;
    long extendedNs = ROOT_ENUM_EXTENDING_COST_MS * ROOT_ENUM_NS_PER_COST_MS;
    assertTrue(ROOT_ENUM_BEFORE_BASE_MS > 0, "before-base age must be positive");
    assertTrue(pastBaseNs < extendedNs && extendedNs < ROOT_ENUM_MAX_INTERVAL_NS,
        "extending cost must land strictly between the past-base age and the cap");
    assertTrue(ROOT_ENUM_CAPPING_COST_MS * ROOT_ENUM_NS_PER_COST_MS > ROOT_ENUM_MAX_INTERVAL_NS,
        "capping cost must exceed the cap");
    assertTrue(ROOT_ENUM_MAX_INTERVAL_NS > pastBaseNs, "cap must exceed the past-base age");
    assertTrue(ROOT_ENUM_PAST_CAP_MS * NS_PER_MS > ROOT_ENUM_MAX_INTERVAL_NS,
        "past-cap age must exceed the cap");
  }

  /**
   * Runs real GCs until the live GC-finish epoch is observed to advance (up to 5 attempts), so a
   * {@code -1} epoch shift makes the epoch look advanced instead of clamping to the never-ran
   * value. An epoch already &gt; 0 that did not advance during the loop is still sufficient (the
   * shift lands below live). Skips the test - never passes it vacuously - if the epoch is still 0,
   * e.g. a GC configuration that posts no GarbageCollectionFinish for System.gc().
   */
  private static void ensureGcEpochAdvanced() throws InterruptedException {
    long before = ReferenceChainTestHooks.referenceChainGcFinishEpochForTest0();
    for (int i = 0; i < 5; i++) {
      System.gc();
      if (ReferenceChainTestHooks.referenceChainGcFinishEpochForTest0() > before) {
        return;
      }
      Thread.sleep(100);
    }
    if (ReferenceChainTestHooks.referenceChainGcFinishEpochForTest0() == 0) {
      assumeTrue(false, "no GarbageCollectionFinish observed after 5 System.gc() calls - the "
          + "-1 epoch shift would clamp to the live value and test nothing");
    }
  }

  private static void seedRunningSearch() {
    // forceRunningSearchForTest (not just "search started"): the live BFS thread may be running
    // its own real search (leftover leak signal from earlier tests in this shared JVM) and can
    // drive it terminal between this seed and the gate call - the forced RUNNING state with fresh
    // pain budgets keeps the gate evaluating the running-search lanes deterministically.
    ReferenceChainTestHooks.forceRunningReferenceChainSearchForTest0();
    // Zero candidates: the canary lane is off and the epoch/cadence lanes are what run.
    ReferenceChainTestHooks.setReferenceChainCanaryStateForTest0(0, 0);
  }

  /**
   * Kills the GC-epoch bypass: with the previous pass a moment ago, a freshly completed
   * GC must NOT authorize a pass ahead of the minimum spacing - without the gate the epoch
   * branch of {@code shouldRunPass()} returns true unconditionally, so pass rate tracks the
   * young-GC rate.
   */
  @Test
  public void gcEpochPassWaitsForMinimumPassSpacing() throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      ensureGcEpochAdvanced();
      seedRunningSearch();
      // Quiesce first: the spacing seed blocks every BFS lane, so no pass can overwrite the
      // epoch shift seeded below.
      ReferenceChainTestHooks.setReferenceChainPassSpacingForTest0(0, CADENCE_MS);
      Thread.sleep(QUIESCE_MS);
      assertTrue(ReferenceChainTestHooks.referenceChainGcFinishEpochForTest0() > 0,
          "the -1 epoch shift needs a live GC-finish epoch > 0 to land below live");
      ReferenceChainTestHooks.shiftReferenceChainLastGcEpochForTest0(-1);
      assertFalse(ReferenceChainTestHooks.shouldRunPassForTest0(),
          "A new GC epoch must not authorize a pass sooner than the effective cadence after "
              + "the previous pass");
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** The epoch lane must only be deferred, not disabled: once the spacing has elapsed, the new
   *  epoch authorizes the pass. */
  @Test
  public void gcEpochPassRunsOnceSpacingElapses() throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      ensureGcEpochAdvanced();
      seedRunningSearch();
      eventuallyTrue("A new GC epoch must authorize a pass once the minimum spacing has elapsed",
          () -> {
            seedRunningSearch();
            ReferenceChainTestHooks.setReferenceChainPassSpacingForTest0(
                CADENCE_MS * 2, CADENCE_MS);
            ReferenceChainTestHooks.shiftReferenceChainLastGcEpochForTest0(-1);
          },
          ReferenceChainTestHooks::shouldRunPassForTest0);
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /**
   * Kills the canary lane's unbounded back-to-back rate: a productive chase (backoff multiplier
   * 1) would otherwise skip its spacing gate entirely, chaining passes with no gap and making
   * every pass pay its JVM VM-operation cost. The epoch is shifted stale so only the canary lane
   * could open the gate - the assertion must fail on that lane specifically.
   */
  @Test
  public void canaryBackToBackPassWaitsForMinimumPassSpacing() throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      seedRunningSearch();
      ReferenceChainTestHooks.setReferenceChainPassSpacingForTest0(0, CADENCE_MS);
      Thread.sleep(QUIESCE_MS);
      // One unresolved candidate: the gate takes the canary lane with backoff multiplier 1.
      // Seeded after the quiesce so the BFS thread's per-iteration pollWatchedTargets() (which
      // overwrites the candidate set from real leak signals) cannot clobber it.
      ReferenceChainTestHooks.setReferenceChainCanaryStateForTest0(1, 0);
      ReferenceChainTestHooks.shiftReferenceChainLastGcEpochForTest0(1_000);
      assertFalse(ReferenceChainTestHooks.shouldRunPassForTest0(),
          "A canary chase with fresh backoff (multiplier 1) must still wait out the minimum "
              + "pass spacing before starting the next pass");
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** The canary floor must only defer the chase, not starve it: once the spacing has elapsed,
   *  the chase resumes at multiplier-1 rate. */
  @Test
  public void canaryPassRunsOnceSpacingElapses() throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      seedRunningSearch();
      eventuallyTrue("A canary chase with fresh backoff must run a pass once the minimum "
              + "spacing has elapsed",
          () -> {
            seedRunningSearch();
            ReferenceChainTestHooks.setReferenceChainCanaryStateForTest0(1, 0);
            ReferenceChainTestHooks.setReferenceChainPassSpacingForTest0(
                CADENCE_MS * 2, CADENCE_MS);
          },
          ReferenceChainTestHooks::shouldRunPassForTest0);
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /**
   * The reset contract (resetSearchStateForTest()): it zeroes {@code _last_pass_ns} along with
   * the pass counter, so the minimum-spacing gate is open again right after a reset - a stale
   * previous-pass timestamp must not hold the next test's first pass off. A closed reading with
   * zero passes run since the reset is definitive (no real pass refreshed the timestamp); a
   * closed reading after a real pass is retried.
   */
  @Test
  public void resetReopensMinimumPassSpacingGate() throws InterruptedException {
    assumeDebugBuild();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      for (int attempt = 0; attempt < 10; attempt++) {
        // A closed gate: the previous pass "just ended" under a long cadence.
        ReferenceChainTestHooks.setReferenceChainPassSpacingForTest0(0, CADENCE_MS);
        ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
        seedRunningSearch();
        if (ReferenceChainTestHooks.shouldRunPassForTest0()) {
          return;
        }
        assertTrue(ReferenceChainTestHooks.referenceChainPassesRunForTest0() != 0,
            "the spacing gate must be open right after a reset - _last_pass_ns/"
                + "_effective_cadence_ns were not reset");
        Thread.sleep(100);
      }
      assertFalse(true, "an open spacing gate right after a reset was never observed");
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** Root/stack-ref enumeration waits out its base interval before re-running. */
  @Test
  public void rootEnumWaitsForMinimumInterval() throws InterruptedException {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      eventuallyTrue("Re-enumeration must wait out the base interval since the last attempt",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_BEFORE_BASE_MS, 0),
          () -> rootEnumClosedWithSeedIntact(ROOT_ENUM_MIN_INTERVAL_NS));
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** The base interval must only defer enumeration, not disable it. */
  @Test
  public void rootEnumRunsAfterBaseInterval() throws InterruptedException {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      eventuallyTrue("Re-enumeration must run once the base interval has elapsed",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, 0),
          () -> ReferenceChainTestHooks.shouldRunRootEnumForTest0(false));
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /**
   * Pins the ROOT_ENUM_MIN_INTERVAL_NS mirror against the live library: with no measured cost
   * the native floor is exactly the base interval.
   */
  @Test
  public void rootEnumBaseIntervalMatchesNative() throws InterruptedException {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      eventuallyTrue("The base root-enumeration interval must match ROOT_ENUM_MIN_INTERVAL_NS",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, 0),
          () -> ReferenceChainTestHooks.rootEnumIntervalFloorNsForTest0()
              == ROOT_ENUM_MIN_INTERVAL_NS);
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /**
   * Kills the fixed 2s interval: an attempt that held the VM at a safepoint for a known cost
   * must push the next attempt out proportionally - on a busy service the cost recurs (the JVM
   * re-creates frames with scalar-replaced locals continuously), so only a cost-scaled floor
   * bounds the deopt-all rate.
   */
  @Test
  public void rootEnumIntervalExtendsWithMeasuredSafepointCost() throws InterruptedException {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      // Positive control: the past-base seed alone opens the gate, so the closed reading below
      // is attributable to the cost-extended floor.
      eventuallyTrue("A past-base seed with no measured cost must open the gate",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, 0),
          () -> ReferenceChainTestHooks.shouldRunRootEnumForTest0(false));
      // ROOT_ENUM_EXTENDING_COST_MS of measured in-safepoint cost: floor = max(MIN, cost x
      // PER_COST) - strictly between the past-base age and the cap.
      eventuallyTrue("The interval floor must extend by ROOT_ENUM_INTERVAL_NS_PER_COST_MS per "
              + "measured in-safepoint cost millisecond",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, ROOT_ENUM_EXTENDING_COST_MS),
          () -> ReferenceChainTestHooks.rootEnumIntervalFloorNsForTest0()
              == ROOT_ENUM_EXTENDING_COST_MS * ROOT_ENUM_NS_PER_COST_MS);
      eventuallyTrue("Re-enumeration must wait out the cost-extended interval even though the "
              + "base interval has elapsed",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, ROOT_ENUM_EXTENDING_COST_MS),
          () -> rootEnumClosedWithSeedIntact(
              ROOT_ENUM_EXTENDING_COST_MS * ROOT_ENUM_NS_PER_COST_MS));
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** The cost-scaled interval must stay capped so root refresh never stops entirely. */
  @Test
  public void rootEnumIntervalCapsAtMaximum() throws InterruptedException {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      // Positive control, as in rootEnumIntervalExtendsWithMeasuredSafepointCost.
      eventuallyTrue("A past-base seed with no measured cost must open the gate",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, 0),
          () -> ReferenceChainTestHooks.shouldRunRootEnumForTest0(false));
      // ROOT_ENUM_CAPPING_COST_MS scales past ROOT_ENUM_MAX_INTERVAL_NS uncapped; the cap holds
      // it there.
      eventuallyTrue("The cost-scaled interval must be capped at ROOT_ENUM_MAX_INTERVAL_NS",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, ROOT_ENUM_CAPPING_COST_MS),
          () -> ReferenceChainTestHooks.rootEnumIntervalFloorNsForTest0()
              == ROOT_ENUM_MAX_INTERVAL_NS);
      eventuallyTrue("Re-enumeration must wait out the capped interval",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_BASE_MS, ROOT_ENUM_CAPPING_COST_MS),
          () -> rootEnumClosedWithSeedIntact(ROOT_ENUM_MAX_INTERVAL_NS));
      // An uncapped floor would still hold this age off.
      eventuallyTrue("Re-enumeration must run once the capped interval has elapsed",
          () -> ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(
              ROOT_ENUM_PAST_CAP_MS, ROOT_ENUM_CAPPING_COST_MS),
          () -> ReferenceChainTestHooks.shouldRunRootEnumForTest0(false));
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }

  /** The search's first enumeration is mandatory and must ignore the interval entirely. */
  @Test
  public void firstPassAlwaysRunsRootEnum() {
    assumeDebugBuild();
    assertRootEnumSeedAssumptions();
    ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    try {
      // Worst case: an attempt "just ran" at maximum measured cost - the first pass of a fresh
      // search must still enumerate.
      ReferenceChainTestHooks.setReferenceChainRootEnumStateForTest0(0, ROOT_ENUM_CAPPING_COST_MS);
      assertTrue(ReferenceChainTestHooks.shouldRunRootEnumForTest0(true),
          "The search's first pass must always run root/stack-ref enumeration");
    } finally {
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
  }
}
