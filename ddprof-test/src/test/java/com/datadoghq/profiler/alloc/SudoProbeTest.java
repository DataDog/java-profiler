// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

/**
 * Pins the bounded sudo-probe contract: a probe command that never exits must be stopped by the
 * wait bound (destroyed, reported false) instead of hanging the test JVM, and a succeeding command
 * must be reported true.
 */
public class SudoProbeTest {

  @Test
  public void boundStopsANeverExitingProbe() {
    long started = System.nanoTime();
    boolean ok = AllocationProfilerTest.runBoundedProbe("sh", "-c", "sleep 60");
    long elapsedMs = (System.nanoTime() - started) / 1_000_000L;
    assertFalse(ok, "a never-exiting probe must not be reported as available");
    // The probe can only return false here via the timeout bound; an unbounded wait would
    // blow past any slack window.
    assertTrue(
        elapsedMs < 15_000, "probe waited " + elapsedMs + "ms, exceeding the 10s bound + slack");
    assertTrue(
        elapsedMs >= 9_000,
        "probe returned after " + elapsedMs + "ms, before the bound was reached");
  }

  @Test
  public void succeedingProbeReturnsTrue() {
    assertTrue(AllocationProfilerTest.runBoundedProbe("sh", "-c", "exit 0"));
  }
}
