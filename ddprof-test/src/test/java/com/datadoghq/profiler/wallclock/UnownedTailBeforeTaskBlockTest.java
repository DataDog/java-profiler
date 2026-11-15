/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import com.datadoghq.profiler.JfrEvent;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Verifies that entering an owned block preserves the preceding weighted wall-clock tail. */
public class UnownedTailBeforeTaskBlockTest extends AbstractProfilerTest {
  /** All producer paths must replay suppressed observations with a stack retained across a dump. */
  @ParameterizedTest
  @ValueSource(ints = {0, 1, 2, 3})
  public void ownedBlockPreservesUnownedTailAcrossDump(int producer) throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires synchronous debug sampling driver");
    long threadId = Thread.currentThread().getId();
    Path snapshot = Files.createTempFile("unowned-before-taskblock-", ".jfr");
    try {
      assertTrue(
          JavaProfilerTestSupport.recordUnownedWallTailBeforeOwnedBlockForTest(
              snapshot.toString(), producer));
      stopProfiler();
      long tailWeight = 0;
      for (JfrEvent event : verifyEvents("datadog.MethodSample")) {
        if (Long.valueOf(threadId).equals(event.getThreadJavaId("eventThread"))
            && "SLEEPING".equals(event.getString("state"))
            && "UNKNOWN".equals(event.getString("mode"))) {
          tailWeight += event.getLong(WEIGHT, 0);
          String stack = event.getStackTraceString();
          assertTrue(
              stack != null && stack.contains("UnownedTailBeforeTaskBlockTest"),
              "The replayed tail must retain its stack across chunk rotation");
        }
      }
      assertEquals(5L, tailWeight, "Every suppressed observation must survive owned admission");
    } finally {
      Files.deleteIfExists(snapshot);
    }
  }

  /** Reused test threads must exit the preceding phase's window before seeding an unowned tail. */
  @Test
  public void reusedTestThreadClearsPreviousContextWindow() throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires synchronous debug sampling driver");
    Path snapshot = Files.createTempFile("unowned-reused-thread-", ".jfr");
    try {
      profiler.addThread();
      profiler.clearTraceContext();
      assertFalse(
          JavaProfilerTestSupport.recordUnownedWallTailBeforeOwnedBlockForTest(
              snapshot.toString(), 0),
          "Clearing trace context must leave the prior phase's logical window active");
      stopProfiler();
      setupProfiler(testInfo);
      assertTrue(
          JavaProfilerTestSupport.recordUnownedWallTailBeforeOwnedBlockForTest(
              snapshot.toString(), 0),
          "Test setup must remove inherited membership on the same reused thread");
    } finally {
      profiler.removeThread();
      Files.deleteIfExists(snapshot);
    }
  }

  @Override
  protected void beforeProfilerStart() {
    // The seed needs an outside window; neither span clearing nor recording stop exits it.
    profiler.removeThread();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1s,filter=,wallprecheck=true";
  }
}
