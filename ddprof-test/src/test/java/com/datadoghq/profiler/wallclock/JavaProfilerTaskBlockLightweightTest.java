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
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** End-to-end coverage for stackless TaskBlock events in lightweight mode. */
public class JavaProfilerTaskBlockLightweightTest extends AbstractProfilerTest {
  private static final long BLOCKER = 0x7401L;
  private static final long UNBLOCKING_SPAN_ID = 0x7402L;
  private static final String WORKER = "taskblock-lightweight";

  @ParameterizedTest(name = "coordinatorWaitMillis={0}")
  @ValueSource(longs = {0L, 20L})
  public void suppressedWallSamplesAreReplacedByAStacklessTaskBlock(long coordinatorWaitMillis)
      throws Exception {
    long suppressedBefore =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    AtomicLong workerId = new AtomicLong();
    // Coordinator waits must not add their own completed TaskBlock to this unfiltered recording.
    profiler.addThread();
    try {
      // JVMTI monitor TaskBlocks on other threads share task_block_record_failed.
      TaskBlockRecorderTestSupport.recordWithinAttempts(
          profiler::getDebugCounters,
          TaskBlockRecorderTestSupport.Credit.LOWER_BOUND,
          "stackless interval",
          () -> runSuppressedBlock(coordinatorWaitMillis, workerId));
      stopProfiler();
    } finally {
      profiler.removeThread();
    }
    JfrEvents all = verifyEvents("datadog.TaskBlock");
    Long coordinatorId = Thread.currentThread().getId();
    assertEquals(
        0L,
        all.filter(event -> coordinatorId.equals(event.getThreadJavaId("eventThread"))).count(),
        "the context-registered coordinator's Object.wait must not emit a TaskBlock");
    // JVM-wide monitor TaskBlocks can share the recording; scope exact checks to the worker.
    JfrEvents events = all.filter(event -> WORKER.equals(event.getThreadName("eventThread")));
    assertEquals(1L, events.count());
    JfrEvent event = events.iterator().next();
    assertNotNull(event.getThreadJavaId("eventThread"));
    assertEquals(Long.valueOf(workerId.get()), event.getThreadJavaId("eventThread"));
    TaskBlockAssertions.assertContainsNoStackTrace(events);
    TaskBlockAssertions.assertNoAnchorFields(events);
    TaskBlockAssertions.assertNoCorrelationId(events);
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertContainsObservedState(events, "SLEEPING");
    // The interval spans at least the 10 ms sleep before release; the upper
    // bound covers the 5 s waits and rejects a start/end mix-up in encoding.
    TaskBlockAssertions.assertContainsDuration(events, 10L, 15_000L);
    assertTrue(getRecordedCounterValue("wc_signals_suppressed_owned_block") > suppressedBefore);
    assertTrue(getRecordedCounterValue("task_block_emitted") >= 1L);
    assertEquals(0L, getRecordedCounterValue("task_block_stack_capture_failed"));
  }

  /**
   * Runs one suppressed interval and returns endTaskBlock's result. A rejected attempt emits no
   * event, so the worker's exactly-one event check after stop spans all attempts.
   */
  private boolean runSuppressedBlock(long coordinatorWaitMillis, AtomicLong workerId)
      throws Exception {
    CountDownLatch armed = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    AtomicBoolean recorded = new AtomicBoolean();
    AtomicReference<Throwable> error = new AtomicReference<>();
    long suppressedBefore =
        profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    Thread worker =
        new Thread(
            () -> {
              try {
                long token = profiler.beginTaskBlock();
                assertTrue(token != 0, "Expected TaskBlock interval to be armed");
                armed.countDown();
                assertTrue(release.await(5, TimeUnit.SECONDS));
                recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
              } catch (Throwable t) {
                error.set(t);
              }
            },
            WORKER);

    try {
      worker.start();
      assertTrue(armed.await(5, TimeUnit.SECONDS));
      if (coordinatorWaitMillis > 0L) {
        // Repeat spurious wakeups until one Object.wait exceeds the TaskBlock duration threshold.
        Object monitor = new Object();
        long waitedNanos;
        synchronized (monitor) {
          do {
            long started = System.nanoTime();
            monitor.wait(coordinatorWaitMillis);
            waitedNanos = System.nanoTime() - started;
          } while (waitedNanos < TimeUnit.MILLISECONDS.toNanos(coordinatorWaitMillis));
        }
        assertTrue(waitedNanos >= TimeUnit.MILLISECONDS.toNanos(coordinatorWaitMillis));
      }
      waitForCounterAbove("wc_signals_suppressed_owned_block", suppressedBefore, 5_000L);
      // The periodic signal may arrive less than 1 ms after beginTaskBlock().
      Thread.sleep(10L);
      release.countDown();
      worker.join(5_000L);
      assertFalse(worker.isAlive());
      if (error.get() != null) throw new AssertionError(error.get());
      workerId.set(worker.getId());
      return recorded.get();
    } finally {
      release.countDown();
      worker.join(5_000L);
    }
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

  @Override
  protected boolean isPlatformSupported() {
    return TaskBlockAssertions.isSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true,lightweight=yes";
  }
}
