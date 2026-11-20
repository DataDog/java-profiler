/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.Platform;
import java.util.concurrent.FutureTask;
import org.junit.jupiter.api.Test;

/** Verifies that deferred blocked weight cannot cross a context-window boundary. */
public class UnownedWallPrecheckContextTest extends AbstractProfilerTest {
  private static volatile long sink;

  /** Checks serialized context attributes as well as stack identity and sample weight. */
  @Test
  public void unownedTailDoesNotAcquireTheNextContextsAttributes() throws Exception {
    FutureTask<Void> workload =
        new FutureTask<>(
            () -> {
              profiler.clearTraceContext();
              for (int i = 0; i < 60; i++) {
                assertTrue(profiler.setContextValue(0, "old-context"));
                profiler.addThread();
                oldContextSleep();
                profiler.removeThread();
                assertTrue(profiler.setContextValue(0, "new-context"));
                profiler.addThread();
                newContextWork();
                profiler.removeThread();
              }
              profiler.clearTraceContext();
              return null;
            });
    Thread worker = new Thread(workload, "unowned-context-tail");
    worker.start();
    worker.join();
    workload.get();
    stopProfiler();

    assertTrue(
        profiler.getDebugCounters().get("wc_unowned_blocked_suppressed") > 0,
        "The workload must accumulate deferred unowned weight");
    long oldSamples = 0;
    long newSamples = 0;
    for (JfrEvent sample : verifyEvents("datadog.MethodSample")) {
      if (!"unowned-context-tail".equals(sample.getThreadName("eventThread"))) continue;
      String stack = sample.getStackTraceString();
      if (stack.contains("oldContextSleep")) {
        oldSamples++;
        assertEquals(
            "old-context",
            sample.getString("tag1"),
            "Deferred old-stack weight was serialized with the next context");
        assertTrue(sample.getLong(WEIGHT, 0) > 0);
      } else if (stack.contains("newContextWork")) {
        newSamples++;
        assertEquals("new-context", sample.getString("tag1"));
        assertEquals(
            1L, sample.getLong(WEIGHT, 0), "Runnable samples must not inherit blocked weight");
      }
    }
    assertTrue(oldSamples > 0, "Expected old-context sleeping samples");
    assertTrue(newSamples > 0, "Expected new-context runnable samples");
  }

  /** Leaves a partially accumulated unowned blocked tail before context deactivation. */
  private static void oldContextSleep() throws InterruptedException {
    Thread.sleep(6);
  }

  /** Provides runnable samples in the later context, which can trigger a deferred tail flush. */
  private static void newContextWork() {
    long until = System.nanoTime() + 3_000_000L;
    while (System.nanoTime() < until) sink++;
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallprecheck=true,filter=0";
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9() && Platform.isJavaVersionAtLeast(11);
  }
}
