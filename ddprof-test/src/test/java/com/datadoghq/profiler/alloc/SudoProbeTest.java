// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.alloc;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.File;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

/**
 * Pins the sudo-probe contract: a probe that never exits must be stopped by the wait bound instead
 * of hanging the test JVM, a succeeding command must be reported available, and an unlaunchable or
 * inconclusive command must be reported unavailable so the caller skips.
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
  public void succeedingProbeIsAvailable() {
    assertTrue(AllocationProfilerTest.runBoundedProbe("sh", "-c", "exit 0"));
  }

  @Test
  public void unlaunchableProbeIsNotAvailable() throws Exception {
    // An existing but non-executable file makes start() fail: an inconclusive probe must
    // report unavailable, never the available outcome the skip decision would rely on.
    File nonExecutable = File.createTempFile("sudo-probe-nonexec", null);
    nonExecutable.deleteOnExit();
    assertTrue(nonExecutable.setExecutable(false));
    assertFalse(AllocationProfilerTest.runBoundedProbe(nonExecutable.getAbsolutePath()));
  }

  @Test
  public void sudoOnPathFindsAnExecutableSudo(@TempDir File dir) throws Exception {
    File sudo = new File(dir, "sudo");
    assertTrue(sudo.createNewFile());
    assertTrue(sudo.setExecutable(true));
    assertTrue(AllocationProfilerTest.sudoOnPath(dir.getAbsolutePath()));
  }

  @Test
  public void sudoOnPathMissesADirectoryWithoutExecutableSudo(@TempDir File dir) throws Exception {
    File sudo = new File(dir, "sudo");
    assertTrue(sudo.createNewFile());
    assertFalse(AllocationProfilerTest.sudoOnPath(dir.getAbsolutePath()));
    assertFalse(AllocationProfilerTest.sudoOnPath(dir.getAbsolutePath() + File.pathSeparator));
  }

  @Test
  public void sudoOnPathTreatsAnEmptyComponentAsTheWorkingDirectory(@TempDir File dir)
      throws Exception {
    // POSIX executable lookup resolves an empty PATH component against the current directory:
    // the scan must see a prompting sudo there, not classify it as absent.
    assertFalse(AllocationProfilerTest.sudoOnPath(dir.getAbsolutePath() + File.pathSeparator, dir));
    File sudo = new File(dir, "sudo");
    assertTrue(sudo.createNewFile());
    assertTrue(sudo.setExecutable(true));
    assertTrue(AllocationProfilerTest.sudoOnPath(dir.getAbsolutePath() + File.pathSeparator, dir));
  }

  @Test
  public void unknownPathFallsBackToProbing() {
    assertTrue(AllocationProfilerTest.sudoOnPath(null));
    assertTrue(AllocationProfilerTest.sudoOnPath(" "));
  }
}
