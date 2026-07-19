/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.nio.file.Files;
import java.nio.file.Path;
import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** End-to-end coverage for the paired synchronous TaskBlock API. */
public class JavaProfilerTaskBlockApiTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x7301L;
  private static final long UNBLOCKING_SPAN_ID = 0x7302L;

  @Test
  public void pairedApiEmitsTaskBlockWithStack() throws Exception {
    assertTrue(runEligibleBlock(BLOCKER));
    stopProfiler();

    IItemCollection events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertNoAnchorFields(events);
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "JavaProfilerTaskBlockApiTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertContainsObservedState(events, "SLEEPING");
  }

  @Test
  public void invalidAndNestedTokensDoNotLoseCurrentOwner() throws Exception {
    AtomicBoolean recorded = new AtomicBoolean();
    runWorker(() -> {
      long token = profiler.beginTaskBlock();
      assertTrue(token != 0);
      assertEquals(0L, profiler.beginTaskBlock());
      assertFalse(profiler.endTaskBlock(token + 1, BLOCKER, UNBLOCKING_SPAN_ID));
      Thread.sleep(200L);
      recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
    });
    assertTrue(recorded.get());
  }

  @Test
  public void tooShortIntervalStillClearsLifecycle() throws Exception {
    AtomicBoolean recorded = new AtomicBoolean(true);
    AtomicLong secondToken = new AtomicLong();
    runWorker(() -> {
      long token = profiler.beginTaskBlock();
      recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
      secondToken.set(profiler.beginTaskBlock());
      profiler.endTaskBlock(secondToken.get(), BLOCKER, UNBLOCKING_SPAN_ID);
    });

    assertFalse(recorded.get());
    assertTrue(secondToken.get() != 0);
    stopProfiler();
    assertTrue(getRecordedCounterValue("task_block_skipped_too_short") > 0);
  }

  @Test
  public void contextWindowAdmissionAndCrossingAreEnforced() throws Exception {
    AtomicLong tokenAfterWindow = new AtomicLong();
    runWorker(() -> {
      profiler.addThread();
      try {
        assertEquals(0L, profiler.beginTaskBlock());
      } finally {
        profiler.removeThread();
      }

      long crossedToken = profiler.beginTaskBlock();
      assertTrue(crossedToken != 0);
      profiler.addThread();
      profiler.removeThread();
      Thread.sleep(20L);
      assertFalse(profiler.endTaskBlock(
          crossedToken, BLOCKER, UNBLOCKING_SPAN_ID));

      tokenAfterWindow.set(profiler.beginTaskBlock());
      profiler.endTaskBlock(tokenAfterWindow.get(), BLOCKER, UNBLOCKING_SPAN_ID);
    });
    assertTrue(tokenAfterWindow.get() != 0,
        "context rejection must still clear the prior lifecycle");
  }

  @Test
  public void traceContextRejectsAtEntry() throws Exception {
    AtomicLong token = new AtomicLong(-1L);
    runWorker(() -> {
      profiler.setContext(0x5100L, 0x5101L, 0L, 0x5101L);
      try {
        token.set(profiler.beginTaskBlock());
      } finally {
        profiler.clearContext();
      }
    });
    assertEquals(0L, token.get(),
        "a traced interval must not arm timer-side suppression");
  }

  @Test
  public void virtualThreadCannotMutateCarrierTaskBlockState() throws Exception {
    Method startVirtualThread;
    try {
      startVirtualThread =
          Thread.class.getMethod("startVirtualThread", Runnable.class);
    } catch (NoSuchMethodException unavailableBeforeJdk21) {
      Assumptions.assumeTrue(false, "virtual threads require JDK 21");
      return;
    }

    AtomicLong token = new AtomicLong(-1L);
    Thread virtual = (Thread) startVirtualThread.invoke(null, (Runnable) () ->
        token.set(profiler.beginTaskBlock()));
    virtual.join(5_000L);
    assertFalse(virtual.isAlive());
    assertEquals(0L, token.get());

    AtomicLong platformToken = new AtomicLong();
    runWorker(() -> {
      platformToken.set(profiler.beginTaskBlock());
      profiler.endTaskBlock(platformToken.get(), BLOCKER, UNBLOCKING_SPAN_ID);
    });
    assertTrue(platformToken.get() != 0,
        "virtual-thread rejection must not strand carrier ownership");
  }

  @Test
  public void liveDumpDoesNotRequireAnEntrySample() throws Exception {
    CountDownLatch armed = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    AtomicBoolean recorded = new AtomicBoolean();
    AtomicReference<Throwable> error = new AtomicReference<>();
    long before = profiler.getDebugCounters()
        .getOrDefault("wc_signals_suppressed_owned_block", 0L);
    Thread worker = new Thread(() -> {
      try {
        long token = profiler.beginTaskBlock();
        assertTrue(token != 0);
        armed.countDown();
        assertTrue(release.await(5, TimeUnit.SECONDS));
        recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
      } catch (Throwable t) {
        error.set(t);
      }
    }, "taskblock-live-dump");

    worker.start();
    assertTrue(armed.await(5, TimeUnit.SECONDS));
    waitForCounterAbove("wc_signals_suppressed_owned_block", before, 5_000L);
    Path snapshot = Files.createTempFile("taskblock-live-dump-", ".jfr");
    try {
      dump(snapshot);
    } finally {
      Files.deleteIfExists(snapshot);
    }
    release.countDown();
    worker.join(5_000L);
    assertFalse(worker.isAlive());
    if (error.get() != null) throw new AssertionError(error.get());
    assertTrue(recorded.get());

    stopProfiler();
    TaskBlockAssertions.assertContainsStackTrace(verifyEvents("datadog.TaskBlock"));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private boolean runEligibleBlock(long blocker) throws Exception {
    AtomicBoolean result = new AtomicBoolean();
    runWorker(() -> {
      long token = profiler.beginTaskBlock();
      if (token == 0) throw new AssertionError("interval was not armed");
      Thread.sleep(200L);
      result.set(profiler.endTaskBlock(token, blocker, UNBLOCKING_SPAN_ID));
    });
    return result.get();
  }

  private void runWorker(ThrowingRunnable action) throws Exception {
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread worker = new Thread(() -> {
      try {
        action.run();
      } catch (Throwable t) {
        error.set(t);
      }
    }, "taskblock-paired-api");
    worker.start();
    worker.join(5_000L);
    assertFalse(worker.isAlive());
    if (error.get() != null) throw new AssertionError(error.get());
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

  @FunctionalInterface
  private interface ThrowingRunnable {
    void run() throws Exception;
  }
}
