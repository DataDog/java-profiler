/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

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
    ExecutorService worker = Executors.newSingleThreadExecutor();
    Path recording = Files.createTempFile("taskblock-producer-restart-", ".jfr");
    boolean started = false;
    try {
      long oldToken = worker.submit(() -> enter(producer)).get(5, TimeUnit.SECONDS);
      assertTrue(oldToken != 0, "The original interval must be armed");
      stopProfiler();
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording);
      started = true;
      worker.submit(() -> {
        // Refresh through a different hook first: producer TLS must independently
        // notice the recording epoch even if registry membership is already current.
        profiler.addThread();
        profiler.removeThread();
        long token = enter(producer);
        assertTrue(token != 0, "An abandoned interval must not strand producer TLS");
        if ("paired".equals(producer)) {
          assertFalse(profiler.endTaskBlock(oldToken, BLOCKER, UNBLOCKING_SPAN_ID),
              "The previous recording's token must not close the new interval");
        }
        Thread.sleep(30L);
        exit(producer, token);
        return null;
      }).get(5, TimeUnit.SECONDS);
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
    ExecutorService worker = Executors.newSingleThreadExecutor();
    try {
      worker.submit(() -> {
        assertTrue(ProfilerOwnedBlockHooks.blockEnter(profiler, SLEEPING) != 0);
        profiler.addThread();
        profiler.removeThread();
        long token = profiler.beginTaskBlock();
        assertTrue(token != 0, "The registry retired the old generic run on context entry");
        Thread.sleep(30L);
        assertTrue(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
        return null;
      }).get(5, TimeUnit.SECONDS);
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

  /** Closes the selected producer with metadata that must survive into its JFR event. */
  private void exit(String producer, long token) {
    switch (producer) {
      case "paired":
        assertTrue(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
        break;
      case "block":
        ProfilerOwnedBlockHooks.blockExit(profiler, token, BLOCKER, UNBLOCKING_SPAN_ID);
        break;
      case "park":
        ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
        break;
      default:
        throw new IllegalArgumentException(producer);
    }
  }
}
