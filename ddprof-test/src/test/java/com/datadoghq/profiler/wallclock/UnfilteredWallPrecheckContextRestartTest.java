/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

/** Separates logical window membership from active span context across a stopped gap. */
public class UnfilteredWallPrecheckContextRestartTest extends AbstractProfilerTest {
  private static volatile long spinSink;

  /** Uses only supported owner-thread JNI writers; restart must not require a second add. */
  @ParameterizedTest
  @CsvSource({
    "true,none,false",
    "false,none,false",
    "true,clear,false",
    "true,remove,true",
    "false,add,false"
  })
  public void survivingWindowControlsAdmission(boolean span, String action, boolean outside)
      throws Exception {
    ExecutorService worker =
        Executors.newSingleThreadExecutor(task -> new Thread(task, "wall-context"));
    Path recording = Files.createTempFile("wall-context-restart-", ".jfr");
    System.out.println("===> membership recording: " + recording.toAbsolutePath());
    boolean restarted = false;
    try {
      long workerId =
          worker
              .submit(
                  () -> {
                    if (!action.equals("add")) {
                      profiler.addThread();
                    }
                    if (span) {
                      profiler.setTraceContext(7101, 7102, 0, 7103, -1, null, -1, null);
                    }
                    return Thread.currentThread().getId();
                  })
              .get(10, TimeUnit.SECONDS);
      stopProfiler();
      worker
          .submit(
              () -> {
                if (action.equals("clear") || action.equals("remove")) {
                  profiler.clearTraceContext();
                }
                if (action.equals("remove")) {
                  profiler.removeThread();
                } else if (action.equals("add")) {
                  profiler.addThread();
                  profiler.setTraceContext(7101, 7102, 0, 7103, -1, null, -1, null);
                }
              })
          .get(10, TimeUnit.SECONDS);
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording);
      restarted = true;
      long token =
          worker
              .submit(
                  () -> {
                    long result = ProfilerOwnedBlockHooks.blockEnter(profiler, 7);
                    if (result != 0) {
                      ProfilerOwnedBlockHooks.blockExit(profiler, result);
                    }
                    return result;
                  })
              .get(10, TimeUnit.SECONDS);
      if (outside) {
        assertNotEquals(0L, token, "Stopped-gap window exit must allow admission");
      } else {
        assertEquals(0L, token, "A surviving/entered window must reject admission");
      }
      worker
          .submit(UnfilteredWallPrecheckContextRestartTest::sampleOrdinaryWindow)
          .get(10, TimeUnit.SECONDS);
      profiler.stop();
      restarted = false;
      boolean activeSpan = action.equals("add") || (span && action.equals("none"));
      assertOrdinarySamples(recording, workerId, activeSpan ? 7101L : 0L, activeSpan ? 7102L : 0L);
    } finally {
      try {
        worker
            .submit(
                () -> {
                  profiler.clearTraceContext();
                  profiler.removeThread();
                })
            .get(10, TimeUnit.SECONDS);
      } finally {
        if (restarted) {
          profiler.stop();
        }
        worker.shutdownNow();
        assertTrue(worker.awaitTermination(10, TimeUnit.SECONDS));
        // With keepJFRs the test framework retains its original recording;
        // retain this separately restarted recording as well.
        if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          Files.deleteIfExists(recording);
        }
      }
    }
  }

  /** A first inactive add must survive activation without a previous slot or a later re-add. */
  @Test
  public void firstInactiveAddExcludesAdmissionAfterStart() throws Exception {
    firstInactiveWindowControlsAdmission(false);
  }

  /** A genuine inactive remove, not span clearing, permits the fresh owner's first block. */
  @Test
  public void inactiveRemovePermitsAdmissionAfterStart() throws Exception {
    firstInactiveWindowControlsAdmission(true);
  }

  /** Creates the worker only after stop, so no active callback/hook can pre-register it. */
  private void firstInactiveWindowControlsAdmission(boolean remove) throws Exception {
    stopProfiler();
    ExecutorService worker =
        Executors.newSingleThreadExecutor(task -> new Thread(task, "wall-cold-owner"));
    Path recording = Files.createTempFile("wall-context-cold-", ".jfr");
    System.out.println("===> membership recording: " + recording.toAbsolutePath());
    boolean restarted = false;
    try {
      long workerId =
          worker
              .submit(
                  () -> {
                    profiler.addThread();
                    if (remove) {
                      profiler.removeThread();
                    }
                    return Thread.currentThread().getId();
                  })
              .get(10, TimeUnit.SECONDS);
      profiler.execute("start," + getProfilerCommand() + ",jfr,file=" + recording);
      restarted = true;
      long token =
          worker
              .submit(
                  () -> {
                    long result = ProfilerOwnedBlockHooks.blockEnter(profiler, 7);
                    if (result != 0) {
                      ProfilerOwnedBlockHooks.blockExit(profiler, result);
                    }
                    return result;
                  })
              .get(10, TimeUnit.SECONDS);
      if (remove) {
        assertNotEquals(0L, token, "A real inactive remove must permit admission");
      } else {
        assertEquals(0L, token, "First inactive add must exclude admission without a re-add");
      }
      worker
          .submit(UnfilteredWallPrecheckContextRestartTest::sampleOrdinaryWindow)
          .get(10, TimeUnit.SECONDS);
      profiler.stop();
      restarted = false;
      assertOrdinarySamples(recording, workerId, 0L, 0L);
    } finally {
      try {
        worker
            .submit(
                () -> {
                  profiler.clearTraceContext();
                  profiler.removeThread();
                })
            .get(10, TimeUnit.SECONDS);
      } finally {
        if (restarted) {
          profiler.stop();
        }
        worker.shutdownNow();
        assertTrue(worker.awaitTermination(10, TimeUnit.SECONDS));
        if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          Files.deleteIfExists(recording);
        }
      }
    }
  }

  /** Gives the actual sampler a bounded runnable phase, without an exact timing/sample total. */
  private static void sampleOrdinaryWindow() {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(300);
    long value = 1;
    while (System.nanoTime() - deadline < 0) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }

  /** Checks this worker's real ordinary samples, context, weight and distinct capture times. */
  private void assertOrdinarySamples(Path recording, long workerId, long root, long span) {
    JfrEvents config = verifyEvents(recording, "datadog.DatadogProfilerConfig", true);
    for (JfrEvent setting : config) {
      assertEquals(1L, setting.getLong(WALL_INTERVAL, -1), "Expected actual 1ms wall sampling");
    }
    JfrEvents samples = verifyEvents(recording, "datadog.MethodSample", true);
    Set<Long> captureTimes = new HashSet<>();
    int workerSamples = 0;
    for (JfrEvent sample : samples) {
      String stack = sample.getStackTraceString();
      if (Long.valueOf(workerId).equals(sample.getThreadJavaId("eventThread"))
          && stack != null
          && stack.contains("sampleOrdinaryWindow")) {
        workerSamples++;
        assertEquals(root, sample.getLong(LOCAL_ROOT_SPAN_ID, -1), "Wrong worker root span");
        assertEquals(span, sample.getLong(SPAN_ID, -1), "Wrong worker span");
        assertEquals(1L, sample.getLong(WEIGHT, -1), "Ordinary sample must retain weight1");
        Long start = sample.getLong("startTime");
        assertNotNull(start, "Worker sample lacks capture time");
        captureTimes.add(start);
      }
    }
    assertTrue(
        workerSamples >= 2, "Ordinary wall sampling must resume for the same worker/context");
    assertTrue(captureTimes.size() >= 2, "Ordinary worker samples need distinct capture times");
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9();
  }
}
