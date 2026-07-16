/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assumptions;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Verifies TaskBlock production from Java-owned platform-thread park hooks. */
public class ParkTaskBlockTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x3102L;
  private static final long UNBLOCKING_SPAN_ID = 0x3103L;

  @Test
  public void platformParkEmitsTaskBlockOutsideContextWindow() {
    ProfilerOwnedBlockHooks.parkEnter(profiler);
    try {
      parkForMillis(200);
    } finally {
      ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
    }
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertNoAnchorFields(events);
    assertTaskBlockStackReference(events);
    TaskBlockAssertions.assertContains(events, 0, 0, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertContainsObservedState(events, "PARKED");
  }

  @Test
  public void contextWindowParkDoesNotEmitTaskBlock() {
    registerCurrentThreadForWallClockProfiling();
    profiler.setContext(0x3100L, 0x3101L, 0L, 0x3101L);
    try {
      ProfilerOwnedBlockHooks.parkEnter(profiler);
      try {
        parkForMillis(200);
      } finally {
        ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
      }
    } finally {
      profiler.clearContext();
      profiler.removeThread();
    }
    stopProfiler();

    assertFalse(verifyEvents("datadog.TaskBlock", false).hasItems(),
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
    Thread virtual = (Thread) startVirtualThread.invoke(null, (Runnable) () -> {
      ProfilerOwnedBlockHooks.parkEnter(profiler);
      try {
        parkForMillis(20);
      } finally {
        ProfilerOwnedBlockHooks.parkExit(profiler, virtualBlocker, 0);
      }
    });
    virtual.join(5_000);
    assertFalse(virtual.isAlive());

    ProfilerOwnedBlockHooks.parkEnter(profiler);
    try {
      parkForMillis(200);
    } finally {
      ProfilerOwnedBlockHooks.parkExit(profiler, BLOCKER, UNBLOCKING_SPAN_ID);
    }
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    assertFalse(TaskBlockAssertions.containsBlocker(events, virtualBlocker));
    TaskBlockAssertions.assertContains(events, 0, 0, BLOCKER, UNBLOCKING_SPAN_ID);
  }

  @Test
  public void platformParkSuppressesSignalsAndClearsOwnership() throws Exception {
    long baseline = profiler.getDebugCounters()
        .getOrDefault("wc_signals_suppressed_owned_block", 0L);
    long afterFirstPark = runSuppressedPark(baseline);
    runSuppressedPark(afterFirstPark);
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  protected void assertTaskBlockStackReference(IItemCollection events) {
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "ParkTaskBlockTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
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
    Thread worker = new Thread(() -> {
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
    }, "taskblock-park-suppression");

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
    return profiler.getDebugCounters()
        .getOrDefault("wc_signals_suppressed_owned_block", 0L);
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
