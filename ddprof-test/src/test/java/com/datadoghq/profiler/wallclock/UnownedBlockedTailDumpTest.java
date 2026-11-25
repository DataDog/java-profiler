/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

/** Reproduces missing tail stacks using real sampling writes, JFR dumps, and constant pools. */
public class UnownedBlockedTailDumpTest extends AbstractProfilerTest {
  /**
   * Exercises each dump boundary without relying on timer scheduling or worker sleep durations. The
   * debug driver controls only OS-state inputs, stack capture, and where the dump runs.
   */
  @ParameterizedTest(name = "dumpAfterPrimary={0}, resetBeforeTail={1}")
  @CsvSource({"true, false", "false, false", "false, true"})
  public void deferredTailRetainsItsStackAcrossDump(
      boolean dumpAfterPrimary, boolean resetBeforeTail) throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires the debug-only synchronous sampling driver");
    profiler.clearTraceContext();
    long threadId = Thread.currentThread().getId();
    Path snapshot = Files.createTempFile("unowned-tail-before-", ".jfr");
    try {
      // A reused test thread can retain logical membership after its trace context is cleared.
      profiler.addThread();
      profiler.clearTraceContext();
      assertEquals(
          "precheck did not select an unowned sample",
          assertThrows(
                  IllegalStateException.class,
                  () -> record(snapshot, dumpAfterPrimary, resetBeforeTail),
                  "An active logical context must bypass unowned fallback")
              .getMessage());
      profiler.removeThread();
      assertTrue(
          record(snapshot, dumpAfterPrimary, resetBeforeTail),
          "Failed to record the primary samples or dump the first chunk");
      stopProfiler();

      // Positive controls: the initial blocked stack and the later fresh stack
      // resolve correctly. The deferred tail reuses the preserved trace ID.
      assertSampleStack(
          verifyEvents(snapshot, "datadog.MethodSample", true), threadId, "SLEEPING", "JAVA");
      assertSampleStack(verifyEvents("datadog.MethodSample"), threadId, "RUNNABLE", "JAVA");
      if (resetBeforeTail) {
        for (JfrEvent event : verifyEvents("datadog.MethodSample")) {
          if (Long.valueOf(threadId).equals(event.getThreadJavaId("eventThread"))) {
            assertTrue(
                !"UNKNOWN".equals(event.getString("mode")),
                "A reset tail must not emit a stale trace ID");
          }
        }
      } else {
        assertSampleStack(verifyEvents("datadog.MethodSample"), threadId, "SLEEPING", "UNKNOWN");
      }
    } finally {
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(snapshot);
      }
    }
  }

  /**
   * Forces each try-and-drop step of the driver to drop: one drop is retried away, a persistent one
   * names the step, and a deterministic failure is reported without retrying.
   */
  @ParameterizedTest(name = "step={0}")
  @CsvSource({
    "0, JVMTI stack capture dropped",
    "1, ordinary wall sample dropped",
    "2, blocked observation was not deferred"
  })
  public void droppedDriverStepsRetryThenNameTheStep(int step, String reason) throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires the debug-only synchronous sampling driver");
    profiler.clearTraceContext();
    Path snapshot = Files.createTempFile("unowned-tail-drop-", ".jfr");
    try {
      // An earlier test on this reused thread can leave logical membership behind.
      profiler.removeThread();
      JavaProfilerTestSupport.exchangeUnownedWallTailAcrossDumpDropsForTest(step, 1);
      assertTrue(record(snapshot, false, false));
      assertEquals(
          0,
          JavaProfilerTestSupport.exchangeUnownedWallTailAcrossDumpDropsForTest(step, 0),
          "The forced drop was not reached");

      JavaProfilerTestSupport.exchangeUnownedWallTailAcrossDumpDropsForTest(
          step, Integer.MAX_VALUE);
      assertEquals(
          reason,
          assertThrows(IllegalStateException.class, () -> record(snapshot, false, false))
              .getMessage());
      assertTrue(
          JavaProfilerTestSupport.exchangeUnownedWallTailAcrossDumpDropsForTest(step, 0)
              < Integer.MAX_VALUE - 1,
          "A persistent drop must be retried before it is reported");

      // The retry window is two seconds; a retried deterministic failure would outlast it.
      profiler.addThread();
      long start = System.nanoTime();
      assertEquals(
          "precheck did not select an unowned sample",
          assertThrows(IllegalStateException.class, () -> record(snapshot, false, false))
              .getMessage());
      assertTrue(
          System.nanoTime() - start < TimeUnit.SECONDS.toNanos(1),
          "A non-drop failure must not be retried");
    } finally {
      JavaProfilerTestSupport.exchangeUnownedWallTailAcrossDumpDropsForTest(step, 0);
      profiler.removeThread();
      Files.deleteIfExists(snapshot);
    }
  }

  private static boolean record(Path snapshot, boolean dumpAfterPrimary, boolean resetBeforeTail) {
    return JavaProfilerTestSupport.recordUnownedWallTailAcrossDumpForTest(
        snapshot.toAbsolutePath().toString(), dumpAfterPrimary, resetBeforeTail);
  }

  /** Checks that the matching weighted sample resolves the Java stack captured by the driver. */
  private void assertSampleStack(
      Iterable<JfrEvent> events, long threadId, String state, String mode) {
    int matching = 0;
    for (JfrEvent event : events) {
      if (Long.valueOf(threadId).equals(event.getThreadJavaId("eventThread"))
          && state.equals(event.getString("state"))
          && mode.equals(event.getString("mode"))) {
        matching++;
        assertEquals(1L, event.getLong(WEIGHT, 0));
        String stack = event.getStackTraceString();
        assertTrue(
            stack != null && stack.contains("UnownedBlockedTailDumpTest"),
            "Missing stack for " + state + "/" + mode + " sample");
      }
    }
    assertTrue(matching > 0, "Missing " + state + "/" + mode + " sample");
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1s,filter=,wallprecheck=true";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9() && !Platform.isZing();
  }
}
