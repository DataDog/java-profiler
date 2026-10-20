/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Reproduces missing tail stacks using real sampling writes, JFR dumps, and constant pools. */
public class UnownedBlockedTailDumpTest extends AbstractProfilerTest {
  /**
   * Forces each unsafe interleaving without relying on timer scheduling or worker sleep durations.
   * The debug driver controls only OS-state inputs, stack capture, and where the dump runs.
   */
  @ParameterizedTest(name = "dumpAfterPrimary={0}, resetBeforeTail={1}")
  @CsvSource({"true, false", "false, false", "false, true"})
  public void deferredTailRetainsItsStackAcrossDump(boolean beforePublication, boolean resetBeforeTail)
      throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires the debug-only synchronous sampling driver");
    profiler.clearTraceContext();
    long threadId = Thread.currentThread().getId();
    Path snapshot = Files.createTempFile("unowned-tail-before-", ".jfr");
    try {
      assertTrue(JavaProfilerTestSupport.recordUnownedWallTailAcrossDumpForTest(
          snapshot.toAbsolutePath().toString(), beforePublication, resetBeforeTail),
          "Failed to record the primary samples or dump the first chunk");
      stopProfiler();

      // Positive controls: the initial blocked stack and the later fresh stack
      // resolve correctly. Only the deferred tail reuses the retired trace ID.
      assertSampleStack(verifyEvents(snapshot, "datadog.MethodSample", true),
          threadId, "SLEEPING", "JAVA");
      assertSampleStack(verifyEvents("datadog.MethodSample"), threadId, "RUNNABLE", "JAVA");
      if (resetBeforeTail) {
        for (JfrEvent event : verifyEvents("datadog.MethodSample")) {
          if (Long.valueOf(threadId).equals(event.getThreadJavaId("eventThread"))) {
            assertTrue(!"UNKNOWN".equals(event.getString("mode")),
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

  /** Checks that the matching weighted sample resolves the Java stack captured by the driver. */
  private void assertSampleStack(Iterable<JfrEvent> events, long threadId, String state, String mode) {
    int matching = 0;
    for (JfrEvent event : events) {
      if (Long.valueOf(threadId).equals(event.getThreadJavaId("eventThread"))
          && state.equals(event.getString("state"))
          && mode.equals(event.getString("mode"))) {
        matching++;
        assertEquals(1L, event.getLong(WEIGHT, 0));
        String stack = event.getStackTraceString();
        assertTrue(stack != null && stack.contains("UnownedBlockedTailDumpTest"),
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
