/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Checks real ASGCT stack resolution while an unowned blocked worker spans repeated dumps. */
public class UnownedWallTailRotationTest extends AbstractProfilerTest {
  private static final String WORKER = "unowned-tail";
  private static volatile long spinSink;

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(!Platform.isJ9() && Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallprecheck=true,jvmtistacks=false";
  }

  /**
   * Uses actual suppression as a phase precondition, not a sleep-derived sample total. Native
   * transaction tests separately control exact decisions, deferred weights and rejected writes.
   */
  @Test
  public void workerStacksResolveAcrossRepeatedDumps() throws Exception {
    Map<String, Long> before = profiler.getDebugCounters();
    CountDownLatch ready = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    AtomicBoolean running = new AtomicBoolean(true);
    AtomicReference<Throwable> workerFailure = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                profiler.setTraceContext(0x7800L, 0x7801L, 0L, 0x7801L, -1, null, -1, null);
                profiler.clearTraceContext();
                registerCurrentThreadForWallClockProfiling();
                ready.countDown();
                awaitRelease(release);
                spinUntilStopped(running);
              } catch (Throwable failure) {
                workerFailure.set(failure);
                ready.countDown();
              } finally {
                profiler.removeThread();
              }
            },
            WORKER);
    Path[] snapshots = new Path[3];
    worker.start();
    try {
      assertTrue(ready.await(10, TimeUnit.SECONDS), "Worker did not register");
      awaitSuppressedUnownedSample(before, workerFailure);
      int blockedSamples = 0;
      for (int i = 0; i < snapshots.length; i++) {
        snapshots[i] = Files.createTempFile("unowned-tail-dump-" + i, ".jfr");
        dump(snapshots[i]);
        // Immediate successive dumps need not contain a new MethodSample.
        blockedSamples +=
            assertWorkerStacksResolve(verifyEvents(snapshots[i], "datadog.MethodSample", false));
      }
      assertTrue(blockedSamples > 0, "No blocked worker samples across the dumps");
      release.countDown();
      // This is a runnable workload, not a timing-derived exact-weight oracle.
      Thread.sleep(300);
    } finally {
      release.countDown();
      running.set(false);
      worker.join(10_000);
      for (Path snapshot : snapshots) {
        if (snapshot != null && !Boolean.getBoolean("ddprof_test.keep_jfrs")) {
          Files.deleteIfExists(snapshot);
        }
      }
    }
    assertFalse(worker.isAlive(), "Worker survived cleanup");
    assertNull(workerFailure.get(), "Worker failed");
    stopProfiler();
    JfrEvents samples = verifyEvents("datadog.MethodSample", true);
    assertTrue(assertWorkerStacksResolve(samples) > 0, "No worker samples after release");
    boolean sawRunnable = false;
    for (JfrEvent sample : samples) {
      if (WORKER.equals(sample.getThreadName("eventThread"))
          && sample.getStackTraceString().contains("spinUntilStopped")) {
        sawRunnable = true;
      }
    }
    assertTrue(sawRunnable, "Ordinary sampling did not resume for the runnable worker");
    Map<String, Long> after = profiler.getDebugCounters();
    assertEquals(0L, after.getOrDefault("jvmti_stacks_requested", 0L).longValue());
    assertEquals(
        before.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L),
        after.getOrDefault("wc_unowned_blocked_trace_preservation_failed", 0L),
        "Normal rotation must not replace a cached stack with the dropped-stack marker");
  }

  /**
   * Waits for a real recorded blocked stack and subsequent suppression on the only added worker.
   */
  private void awaitSuppressedUnownedSample(
      Map<String, Long> before, AtomicReference<Throwable> workerFailure) throws Exception {
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
    while (System.nanoTime() < deadline) {
      assertNull(workerFailure.get(), "Worker failed before suppression");
      Map<String, Long> counters = profiler.getDebugCounters();
      if (counters.getOrDefault("wc_unowned_blocked_recorded", 0L)
              > before.getOrDefault("wc_unowned_blocked_recorded", 0L)
          && counters.getOrDefault("wc_unowned_blocked_suppressed", 0L)
              > before.getOrDefault("wc_unowned_blocked_suppressed", 0L)) {
        return;
      }
      Thread.sleep(1);
    }
    throw new AssertionError("ASGCT unowned blocked sampling/suppression was not exercised");
  }

  /**
   * Verifies actual decoded thread, stack and represented weight, without inventing exact totals.
   */
  private int assertWorkerStacksResolve(JfrEvents samples) {
    int workerSamples = 0;
    for (JfrEvent sample : samples) {
      if (WORKER.equals(sample.getThreadName("eventThread"))) {
        workerSamples++;
        assertFalse(sample.getStackTrace().isEmpty(), "Unresolved worker stack after rotation");
        assertTrue(sample.getLong(WEIGHT, 0) > 0, "Worker sample lost its represented weight");
      }
    }
    return workerSamples;
  }

  /** Keeps an unowned blocked Java call path available to the actual signal-driven stack walker. */
  private static void awaitRelease(CountDownLatch release) throws InterruptedException {
    release.await();
  }

  /** Keeps the worker runnable after release so the handler can attempt the retained tail. */
  private static void spinUntilStopped(AtomicBoolean running) {
    long value = 1;
    while (running.get()) {
      value = value * 1664525 + 1013904223;
      spinSink = value;
    }
  }
}
