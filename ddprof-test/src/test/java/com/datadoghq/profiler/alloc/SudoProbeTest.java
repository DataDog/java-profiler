// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.File;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Pins the bounded sudo-probe contract: a probe command that never exits must be stopped by the
 * wait bound (destroyed, reported false) instead of hanging the test JVM, and a succeeding command
 * must be reported true.
 */
public class SudoProbeTest {

  @Test
  public void boundStopsANeverExitingProbe() {
    Assumptions.assumeTrue(
        new File("/bin/sh").exists() || new File("/usr/bin/sh").exists(),
        "no POSIX shell to drive the probe");
    long started = System.nanoTime();
    // A shell busy loop: no descendants, so destroyForcibly leaves nothing behind.
    boolean ok = AllocationProfilerTest.runBoundedProbe("sh", "-c", "while :; do :; done");
    long elapsedMs = (System.nanoTime() - started) / 1_000_000L;
    assertFalse(ok, "a never-exiting probe must not be reported as available");
    // The probe can only return false here via the timeout bound; an unbounded wait would
    // blow past any slack window. Wide margins: loaded CI agents schedule slowly.
    assertTrue(
        elapsedMs < 30_000, "probe waited " + elapsedMs + "ms, exceeding the 10s bound + slack");
    assertTrue(
        elapsedMs >= 8_000,
        "probe returned after " + elapsedMs + "ms, before the bound was reached");
  }

  @Test
  public void succeedingProbeReturnsTrue() {
    assertTrue(AllocationProfilerTest.runBoundedProbe("sh", "-c", "exit 0"));
  }
}
