/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Test;

/** The virtual park hook is a no-op on platform threads, on every JDK. */
public class VirtualParkHookPlatformThreadTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x5701L;

  @Test
  public void platformThreadCallRecordsNothingAndKeepsPlatformEntries() throws Exception {
    // Without this, a missing Java gate would be masked by the native start-of-recording check.
    Thread.sleep(100);
    assertFalse(
        ProfilerOwnedBlockHooks.virtualParkExit(
            profiler, TimeUnit.MILLISECONDS.toNanos(50), BLOCKER, 0));
    assertEquals(0L, profiler.getDebugCounters().getOrDefault("task_block_virtual_emitted", 0L));
    // Platform control: its eventThread is still keyed and named by the OS thread.
    long control = 0x5702L;
    assertTrue(ProfilerOwnedBlockHooks.parkEnter(profiler));
    try {
      Thread.sleep(20);
    } finally {
      ProfilerOwnedBlockHooks.parkExit(profiler, control, 0);
    }
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertFalse(TaskBlockAssertions.containsBlocker(events, BLOCKER));
    int matching = 0;
    for (JfrEvent event : events) {
      if (event.getLong("blocker", Long.MIN_VALUE) != control) continue;
      @SuppressWarnings("unchecked")
      Map<String, Object> thread = (Map<String, Object>) event.get("eventThread");
      assertTrue(((Number) thread.get("osThreadId")).longValue() > 0);
      assertEquals(Thread.currentThread().getName(), thread.get("osName"));
      assertEquals(
          Thread.currentThread().getId(), ((Number) thread.get("javaThreadId")).longValue());
      matching++;
    }
    assertEquals(1, matching);
  }

  @Override
  protected boolean isPlatformSupported() {
    return TaskBlockAssertions.parkSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }
}
