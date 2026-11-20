/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Verifies producer compatibility with retained identities and context-window transitions. */
public class TaskBlockProducerCompatibilityTest extends AbstractProfilerTest {
  private static final int SLEEPING = 7;
  private static final long BLOCKER = 0x7401L;
  private static final long UNBLOCKING_SPAN_ID = 0x7402L;

  /** A surviving worker can record again even when its previous producer exit was missed. */
  @ParameterizedTest
  @ValueSource(strings = {"paired", "block", "park"})
  public void abandonedIntervalDoesNotPreventRecordingAfterRestart(String producer)
      throws Exception {
    Assumptions.assumeTrue(
        !"paired".equals(producer) || TaskBlockAssertions.platformThreadClassificationSupported(),
        "paired API classification fails closed on non-HotSpot JDK 19+");
    ExecutorService worker = Executors.newSingleThreadExecutor();
    Path recording = Files.createTempFile("taskblock-producer-restart-", ".jfr");
    boolean started = false;
    try {
      long oldToken = worker.submit(() -> enter(producer)).get(5, TimeUnit.SECONDS);
      assertTrue(oldToken != 0, "The original interval must be armed");
      stopProfiler();
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording);
      started = true;
      // Void block/park exits cannot report rejection; only the paired close is retried.
      TaskBlockRecorderTestSupport.recordWithinAttempts(
          profiler::getDebugCounters,
          TaskBlockRecorderTestSupport.Credit.LOWER_BOUND,
          producer + " interval after restart",
          () ->
              worker
                  .submit(
                      () -> {
                        // Refresh through a different hook first: producer TLS must independently
                        // notice the recording epoch even if registry membership is current.
                        profiler.addThread();
                        profiler.removeThread();
                        long token = enter(producer);
                        assertTrue(
                            token != 0, "An abandoned interval must not strand producer TLS");
                        if ("paired".equals(producer)) {
                          assertFalse(
                              profiler.endTaskBlock(oldToken, BLOCKER, UNBLOCKING_SPAN_ID),
                              "The previous recording's token must not close the new interval");
                        }
                        Thread.sleep(30L);
                        return exit(producer, token);
                      })
                  .get(5, TimeUnit.SECONDS));
      profiler.stop();
      started = false;

      JfrEvents events = verifyEvents(recording, "datadog.TaskBlock", true);
      TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
      TaskBlockAssertions.assertContainsStackTrace(events);
      TaskBlockAssertions.assertContainsJavaType(events, "TaskBlockProducerCompatibilityTest");
    } finally {
      worker.shutdownNow();
      worker.awaitTermination(5, TimeUnit.SECONDS);
      if (started) profiler.stop();
      Files.deleteIfExists(recording);
    }
  }

  /** Context entry retires a generic hook without poisoning a subsequent public API interval. */
  @Test
  public void pairedApiRecoversAfterAbandonedGenericHookCrossesContextWindow() throws Exception {
    Assumptions.assumeTrue(
        TaskBlockAssertions.platformThreadClassificationSupported(),
        "paired API classification fails closed on non-HotSpot JDK 19+");
    ExecutorService worker = Executors.newSingleThreadExecutor();
    try {
      TaskBlockRecorderTestSupport.recordWithinAttempts(
          profiler::getDebugCounters,
          TaskBlockRecorderTestSupport.Credit.LOWER_BOUND,
          "paired interval after retired generic hook",
          () ->
              worker
                  .submit(
                      () -> {
                        assertTrue(ProfilerOwnedBlockHooks.blockEnter(profiler, SLEEPING) != 0);
                        profiler.addThread();
                        profiler.removeThread();
                        long token = profiler.beginTaskBlock();
                        assertTrue(
                            token != 0,
                            "The registry retired the old generic run on context entry");
                        Thread.sleep(30L);
                        return profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID);
                      })
                  .get(5, TimeUnit.SECONDS));
    } finally {
      worker.shutdownNow();
      worker.awaitTermination(5, TimeUnit.SECONDS);
    }
    stopProfiler();
    TaskBlockAssertions.assertContains(
        verifyEvents("datadog.TaskBlock"), 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  /** Opens a producer interval on the calling worker; parks use a boolean ownership marker. */
  private long enter(String producer) {
    switch (producer) {
      case "paired":
        return profiler.beginTaskBlock();
      case "block":
        return ProfilerOwnedBlockHooks.blockEnter(profiler, SLEEPING);
      case "park":
        return ProfilerOwnedBlockHooks.parkEnter(profiler) ? 1L : 0L;
      default:
        throw new IllegalArgumentException(producer);
    }
  }

  /**
   * Closes the selected producer with metadata that must survive into its JFR event. Returns the
   * paired close's result; void block/park exits report true and rely on the event check.
   */
  private boolean exit(String producer, long token) {
    switch (producer) {
      case "paired":
        return profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID);
      case "block":
        ProfilerOwnedBlockHooks.blockExit(profiler, token, BLOCKER, UNBLOCKING_SPAN_ID);
        return true;
      case "park":
        ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
        return true;
      default:
        throw new IllegalArgumentException(producer);
    }
  }
}
