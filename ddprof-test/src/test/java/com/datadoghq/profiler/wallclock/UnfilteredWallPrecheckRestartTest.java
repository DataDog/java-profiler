/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import org.junit.jupiter.api.Test;

/** Verifies that unfiltered wall registry activation does not leak across recordings. */
public class UnfilteredWallPrecheckRestartTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;

  /** Exercises enabled, disabled, CPU-only, and re-enabled tracking in one process. */
  @Test
  public void recordingRestartsReconfigureUnfilteredTracking() throws Exception {
    assertOwnedBlockArmed();
    stopProfiler();

    runRecording("wall=1ms,filter=,wallprecheck=false", false);
    runRecording("cpu=1ms,filter=,wallprecheck=true", false);
    runRecording("wall=1ms,filter=,wallprecheck=true", true);
  }

  /** Verifies epoch refresh and lazy registration for workers that survive a stopped gap. */
  @Test
  public void workerLifecyclesRemainSafeAcrossStoppedGap() throws Exception {
    ExecutorService survivingWorker = Executors.newSingleThreadExecutor();
    ExecutorService stoppedGapWorker = null;
    Path recording = null;
    boolean restarted = false;
    try {
      long oldToken = enterBlock(survivingWorker);
      assertNotEquals(0L, oldToken, "Expected the initial worker run to be armed");

      stopProfiler();
      stoppedGapWorker = Executors.newSingleThreadExecutor();
      // Force creation while JVMTI lifecycle callbacks are disabled.
      assertEquals(0L, enterBlock(stoppedGapWorker));

      recording = Files.createTempFile("unfiltered-wall-worker-restart-", ".jfr");
      profiler.execute(
          "start," + getProfilerCommand() + ",jfr,file=" + recording.toAbsolutePath());
      restarted = true;

      long newToken = enterBlock(survivingWorker);
      assertNotEquals(0L, newToken, "Expected the surviving worker to refresh its slot");
      exitBlock(survivingWorker, oldToken);
      assertEquals(
          0L,
          enterBlock(survivingWorker),
          "A token from the previous recording cleared the current worker run");
      exitBlock(survivingWorker, newToken);

      long stoppedGapToken = enterBlock(stoppedGapWorker);
      assertNotEquals(
          0L, stoppedGapToken, "Expected the stopped-gap worker to register lazily after restart");
      exitBlock(stoppedGapWorker, stoppedGapToken);
    } finally {
      if (restarted) {
        profiler.stop();
      }
      survivingWorker.shutdownNow();
      if (stoppedGapWorker != null) {
        stoppedGapWorker.shutdownNow();
      }
      if (recording != null) {
        Files.deleteIfExists(recording);
      }
    }
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9();
  }

  private void assertOwnedBlockArmed() {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertNotEquals(0L, token, "Expected unfiltered wall precheck to arm the owned block");
    ProfilerOwnedBlockHooks.blockExit(profiler, token);
  }

  private void runRecording(String command, boolean expectArmed) throws Exception {
    Path recording = Files.createTempFile("unfiltered-wall-restart-", ".jfr");
    profiler.execute("start," + command + ",jfr,file=" + recording.toAbsolutePath());
    try {
      long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
      if (expectArmed) {
        assertNotEquals(0L, token, "Expected unfiltered wall tracking after restart");
        ProfilerOwnedBlockHooks.blockExit(profiler, token);
      } else {
        assertEquals(0L, token, "Registry tracking leaked into " + command);
      }
    } finally {
      profiler.stop();
      Files.deleteIfExists(recording);
    }
  }

  private long enterBlock(ExecutorService worker) throws Exception {
    Future<Long> result =
        worker.submit(
            () -> ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING));
    return result.get();
  }

  private void exitBlock(ExecutorService worker, long token) throws Exception {
    worker.submit(() -> ProfilerOwnedBlockHooks.blockExit(profiler, token)).get();
  }
}
