/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Verifies TaskBlock production from Java-owned platform-thread park hooks. */
public class ParkTaskBlockTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x3102L;
  private static final long UNBLOCKING_SPAN_ID = 0x3103L;

  @Test
  public void platformParkEmitsTaskBlockOutsideContextWindow() {
    assertTrue(
        ProfilerOwnedBlockHooks.parkEnter(profiler), "Platform park hook must acquire an owner");
    try {
      parkForMillis(200);
    } finally {
      ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
    }
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertNoAnchorFields(events);
    assertTaskBlockStackReference(events);
    assertExactPlatformPark(events, "platformParkEmitsTaskBlockOutsideContextWindow");
  }

  @Test
  public void contextWindowParkDoesNotEmitTaskBlock() {
    registerCurrentThreadForWallClockProfiling();
    profiler.setTraceContext(0x3100L, 0x3101L, 0L, 0x3101L, -1, null, -1, null);
    try {
      ProfilerOwnedBlockHooks.parkEnter(profiler);
      try {
        parkForMillis(200);
      } finally {
        ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
      }
    } finally {
      profiler.clearTraceContext();
      profiler.removeThread();
    }
    stopProfiler();

    assertFalse(
        verifyEvents("datadog.TaskBlock", false).hasItems(),
        "A park inside the context window must remain ordinary wall-clock data");
  }

  @Test
  public void virtualParkDoesNotMutateCarrierProducerState() throws Exception {
    Method startVirtualThread;
    try {
      startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    } catch (NoSuchMethodException unavailableBeforeJdk21) {
      Assumptions.assumeTrue(false, "virtual threads require JDK 21");
      return;
    }

    long virtualBlocker = 0x3201L;
    AtomicReference<Throwable> failure = new AtomicReference<>();
    Thread virtual =
        (Thread)
            startVirtualThread.invoke(
                null,
                (Runnable)
                    () -> {
                      try {
                        assertFalse(
                            ProfilerOwnedBlockHooks.parkEnter(profiler),
                            "Virtual park hook must not acquire carrier ownership");
                        try {
                          parkForMillis(20);
                        } finally {
                          ProfilerOwnedBlockHooks.parkExit(profiler, virtualBlocker, 0);
                        }
                        assertFalse(
                            ProfilerOwnedBlockHooks.parkEnter(profiler),
                            "Virtual rejection must survive park/unpark");
                        ProfilerOwnedBlockHooks.parkExit(profiler, virtualBlocker, 0);
                      } catch (Throwable error) {
                        failure.set(error);
                      }
                    });
    virtual.join(5_000);
    assertFalse(virtual.isAlive());
    if (failure.get() != null) throw new AssertionError(failure.get());

    // Positive control on a platform thread, well above the 1ms threshold: proves the park
    // producer is alive, so the virtual-thread short-circuit assertion is not vacuous.
    assertTrue(
        ProfilerOwnedBlockHooks.parkEnter(profiler),
        "Virtual rejection must leave platform ownership available");
    try {
      parkForMillis(200);
    } finally {
      ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
    }
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertTrue(
        TaskBlockAssertions.containsBlocker(events, BLOCKER),
        "platform control park was not produced");
    assertFalse(
        TaskBlockAssertions.containsBlocker(events, virtualBlocker),
        "virtual-thread park must not reach the carrier producer");
    assertExactPlatformPark(events, "virtualParkDoesNotMutateCarrierProducerState");
    assertTaskBlockStackReference(events);
    TaskBlockAssertions.assertNoAnchorFields(events);
  }

  @Test
  public void platformParkSuppressesSignalsAndClearsOwnership() throws Exception {
    long baseline =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    long afterFirstPark = runSuppressedPark(baseline);
    runSuppressedPark(afterFirstPark);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  protected void assertTaskBlockStackReference(JfrEvents events) {
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "ParkTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
  }

  /** Both platform controls must resolve the exact caller and its own completed park interval. */
  private static void assertExactPlatformPark(JfrEvents events, String workload) {
    int matching = 0;
    for (JfrEvent event : events) {
      if (event.getLong("blocker", Long.MIN_VALUE) != BLOCKER) continue;
      assertEquals(Thread.currentThread().getName(), event.getThreadName("eventThread"));
      assertEquals(
          Long.valueOf(Thread.currentThread().getId()), event.getThreadJavaId("eventThread"));
      assertEquals(Long.valueOf(0L), event.getLong("spanId"));
      assertEquals(Long.valueOf(0L), event.getLong("localRootSpanId"));
      assertEquals(Long.valueOf(UNBLOCKING_SPAN_ID), event.getLong("unblockingSpanId"));
      assertEquals("PARKED", event.getString("observedBlockingState"));
      assertNotNull(event.getLong("duration"));
      assertTrue(event.getLong("duration") > 0);
      assertNotNull(event.getStackTraceString());
      assertTrue(
          event.getStackTraceString().contains(workload),
          "The park event must resolve its own caller's workload stack");
      matching++;
    }
    assertEquals(1, matching, "Exactly one event per completed platform park");
  }

  private static void parkForMillis(long millis) {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(millis);
    long remaining;
    while ((remaining = deadline - System.nanoTime()) > 0) {
      LockSupport.parkNanos(remaining);
    }
  }

  private long runSuppressedPark(long baseline) throws Exception {
    CountDownLatch armed = new CountDownLatch(1);
    AtomicBoolean release = new AtomicBoolean();
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                ProfilerOwnedBlockHooks.parkEnter(profiler);
                armed.countDown();
                while (!release.get()) {
                  Thread.yield();
                }
              } catch (Throwable t) {
                error.set(t);
              } finally {
                ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
              }
            },
            "taskblock-park-suppression");

    worker.start();
    assertTrue(armed.await(5, TimeUnit.SECONDS));
    try {
      waitForCounterAbove("wc_signals_suppressed_owned_block", baseline, 5_000L);
    } finally {
      release.set(true);
    }
    worker.join(5_000L);
    assertFalse(worker.isAlive());
    if (error.get() != null) throw new AssertionError(error.get());
    return profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
  }

  private void waitForCounterAbove(String name, long baseline, long timeoutMillis)
      throws Exception {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(timeoutMillis);
    while (System.nanoTime() < deadline) {
      if (profiler.getDebugCounters().getOrDefault(name, 0L) > baseline) return;
      Thread.sleep(10L);
    }
    throw new AssertionError("Counter did not increase: " + name);
  }
}
