/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** End-to-end coverage for the paired synchronous TaskBlock API. */
public class JavaProfilerTaskBlockApiTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final long BLOCKER = 0x7301L;
  private static final long UNBLOCKING_SPAN_ID = 0x7302L;

  /** The instrumented block hook must reject real JDK housekeeping threads. */
  @Test
  public void blockEnterRejectsJvmInternalThreadBeforeProjection() throws Exception {
    assertJvmInternalAdmissionRejected(false);
  }

  /** The public paired API must enforce the same housekeeping-thread containment. */
  @Test
  public void beginTaskBlockRejectsJvmInternalThreadBeforeProjection() throws Exception {
    assertJvmInternalAdmissionRejected(true);
  }

  @Test
  public void pairedApiEmitsTaskBlockWithStack() throws Exception {
    assertTrue(runEligibleBlock(BLOCKER));
    stopProfiler();

    JfrEvents events = verifyEvents("datadog.TaskBlock");
    TaskBlockAssertions.assertNoAnchorFields(events);
    TaskBlockAssertions.assertContainsStackTrace(events);
    TaskBlockAssertions.assertContainsJavaType(events, "JavaProfilerTaskBlockApiTest");
    TaskBlockAssertions.assertNoCorrelationId(events);
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertContainsObservedState(events, "SLEEPING");
    // The worker sleeps 200 ms inside the interval; the lower bound leaves
    // room for timer jitter and the upper bound rejects a start/end mix-up.
    TaskBlockAssertions.assertContainsDuration(events, 150L, 5_000L);
  }

  @ParameterizedTest
  @ValueSource(strings = {"start", "resume"})
  public void rejectedDuplicateStartOrResumePreservesActiveTaskBlockRecording(String action)
      throws Exception {
    IllegalStateException rejected =
        assertThrows(
            IllegalStateException.class,
            () -> profiler.execute(action + "," + getProfilerCommand()));
    assertEquals("Profiler already started", rejected.getMessage());

    assertTrue(runEligibleBlock(BLOCKER));
    stopProfiler();

    TaskBlockAssertions.assertContains(
        verifyEvents("datadog.TaskBlock"), 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
  }

  @Test
  public void invalidAndNestedTokensDoNotLoseCurrentOwner() throws Exception {
    AtomicBoolean recorded = new AtomicBoolean();
    runWorker(
        () -> {
          long first = profiler.beginTaskBlock();
          assertTrue(first != 0);
          long token = profiler.beginTaskBlock();
          assertTrue(token != 0, "a nested begin must supersede the open interval");
          assertNotEquals(first, token);
          assertFalse(
              profiler.endTaskBlock(first, BLOCKER, UNBLOCKING_SPAN_ID),
              "the superseded token must no longer close an interval");
          assertFalse(profiler.endTaskBlock(token + 1, BLOCKER, UNBLOCKING_SPAN_ID));
          Thread.sleep(200L);
          recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
        });
    assertTrue(recorded.get());
  }

  @Test
  public void abandonedIntervalDoesNotDisableTaskBlockForThread() throws Exception {
    AtomicLong abandoned = new AtomicLong();
    AtomicBoolean recorded = new AtomicBoolean();
    AtomicBoolean abandonedEnd = new AtomicBoolean(true);
    runWorker(
        () -> {
          try {
            abandoned.set(profiler.beginTaskBlock());
            throw new IllegalStateException("exit without endTaskBlock");
          } catch (IllegalStateException expected) {
            // Simulates a caller that skips endTaskBlock on an exception path.
          }
          long token = profiler.beginTaskBlock();
          assertTrue(token != 0, "an abandoned interval must not disable TaskBlock for the thread");
          Thread.sleep(200L);
          recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
          abandonedEnd.set(profiler.endTaskBlock(abandoned.get(), BLOCKER, UNBLOCKING_SPAN_ID));
        });
    assertTrue(abandoned.get() != 0);
    assertTrue(recorded.get());
    assertFalse(abandonedEnd.get());

    stopProfiler();
    assertTrue(getRecordedCounterValue("task_block_recovered_abandoned") > 0);
  }

  @Test
  public void tooShortIntervalStillClearsLifecycle() throws Exception {
    AtomicBoolean recorded = new AtomicBoolean(true);
    AtomicLong secondToken = new AtomicLong();
    runWorker(
        () -> {
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
    runWorker(
        () -> {
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
          assertFalse(profiler.endTaskBlock(crossedToken, BLOCKER, UNBLOCKING_SPAN_ID));

          tokenAfterWindow.set(profiler.beginTaskBlock());
          profiler.endTaskBlock(tokenAfterWindow.get(), BLOCKER, UNBLOCKING_SPAN_ID);
        });
    assertTrue(
        tokenAfterWindow.get() != 0, "context rejection must still clear the prior lifecycle");

    stopProfiler();
    assertTrue(
        getRecordedCounterValue("task_block_skipped_context_window") > 0,
        "context-window crossing must be counted separately from trace-context rejection");
    assertEquals(
        0L,
        getRecordedCounterValue("task_block_skipped_trace_context"),
        "context-window crossing must not be attributed to the trace-context counter");
  }

  @Test
  public void traceContextRejectsAtEntry() throws Exception {
    AtomicLong token = new AtomicLong(-1L);
    runWorker(
        () -> {
          profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
          try {
            token.set(profiler.beginTaskBlock());
          } finally {
            profiler.clearTraceContext();
          }
        });
    assertEquals(0L, token.get(), "a traced interval must not arm timer-side suppression");
  }

  @Test
  public void traceContextRejectionKeepsOpenInterval() throws Exception {
    AtomicLong nested = new AtomicLong(-1L);
    AtomicBoolean recorded = new AtomicBoolean();
    runWorker(
        () -> {
          long token = profiler.beginTaskBlock();
          assertTrue(token != 0);
          profiler.setTraceContext(0x5200L, 0x5201L, 0L, 0x5201L, -1, null, -1, null);
          try {
            nested.set(profiler.beginTaskBlock());
          } finally {
            profiler.clearTraceContext();
          }
          Thread.sleep(200L);
          recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
        });
    assertEquals(0L, nested.get());
    assertTrue(
        recorded.get(), "a begin rejected for an active trace context must keep the open interval");

    stopProfiler();
    assertTrue(getRecordedCounterValue("task_block_skipped_trace_context") > 0);
    assertEquals(0L, getRecordedCounterValue("task_block_recovered_abandoned"));
  }

  @Test
  public void mismatchedThreadIsRejectedAtBeginAndEnd() throws Exception {
    AtomicLong beginToken = new AtomicLong(-1L);
    AtomicBoolean endResult = new AtomicBoolean(true);
    AtomicLong ownToken = new AtomicLong();
    Thread other = new Thread(() -> {}, "taskblock-mismatch-other");

    runWorker(
        () -> {
          beginToken.set(ProfilerOwnedBlockHooks.beginTaskBlockForThread(profiler, other));

          ownToken.set(profiler.beginTaskBlock());
          assertTrue(ownToken.get() != 0);
          endResult.set(
              ProfilerOwnedBlockHooks.endTaskBlockForThread(
                  profiler, other, ownToken.get(), BLOCKER, UNBLOCKING_SPAN_ID));
          Thread.sleep(50L);
          assertTrue(
              profiler.endTaskBlock(ownToken.get(), BLOCKER, UNBLOCKING_SPAN_ID),
              "A mismatched end must leave the real owner's interval usable");
          assertFalse(profiler.endTaskBlock(ownToken.get(), BLOCKER, UNBLOCKING_SPAN_ID));
        });

    assertEquals(
        0L,
        beginToken.get(),
        "beginTaskBlock0 must reject a jthread that does not identify the calling thread");
    assertFalse(
        endResult.get(),
        "endTaskBlock0 must reject a jthread that does not identify the calling thread");

    stopProfiler();
    assertTrue(getRecordedCounterValue("task_block_skipped_thread_mismatch") > 0);
    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertEquals(1, TaskBlockAssertions.countBlockerEvents(events, BLOCKER));
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertNoCorrelationId(events);
  }

  /** Null is safe JNI input and must not clear an already armed own-thread interval. */
  @Test
  public void nullThreadIsRejectedWithoutConsumingOwnToken() throws Exception {
    runWorker(
        () -> {
          assertEquals(0L, ProfilerOwnedBlockHooks.beginTaskBlockForThread(profiler, null));
          long token = profiler.beginTaskBlock();
          assertTrue(token != 0);
          assertFalse(
              ProfilerOwnedBlockHooks.endTaskBlockForThread(
                  profiler, null, token, BLOCKER, UNBLOCKING_SPAN_ID));
          Thread.sleep(50L);
          assertTrue(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
          assertFalse(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
        });
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertEquals(1, TaskBlockAssertions.countBlockerEvents(events, BLOCKER));
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertNoCorrelationId(events);
  }

  @Test
  public void virtualThreadCannotMutateCarrierTaskBlockState() throws Exception {
    Method startVirtualThread;
    try {
      startVirtualThread = Thread.class.getMethod("startVirtualThread", Runnable.class);
    } catch (NoSuchMethodException unavailableBeforeJdk21) {
      Assumptions.assumeTrue(false, "virtual threads require JDK 21");
      return;
    }

    AtomicReference<Throwable> failure = new AtomicReference<>();
    long virtualBlocker = BLOCKER + 1;
    Thread virtual =
        (Thread)
            startVirtualThread.invoke(
                null,
                (Runnable)
                    () -> {
                      try {
                        assertEquals(0L, profiler.beginTaskBlock());
                        Thread.sleep(20L);
                        assertEquals(
                            0L, profiler.beginTaskBlock(), "Rejection must survive remount");
                        assertFalse(profiler.endTaskBlock(1L, virtualBlocker, UNBLOCKING_SPAN_ID));
                      } catch (Throwable error) {
                        failure.set(error);
                      }
                    });
    virtual.join(5_000L);
    assertFalse(virtual.isAlive());
    if (failure.get() != null) throw new AssertionError(failure.get());

    runWorker(
        () -> {
          long platformToken = profiler.beginTaskBlock();
          assertTrue(
              platformToken != 0, "virtual-thread rejection must not strand carrier ownership");
          Thread.sleep(50L);
          assertTrue(profiler.endTaskBlock(platformToken, BLOCKER, UNBLOCKING_SPAN_ID));
        });
    stopProfiler();
    JfrEvents events = verifyEvents("datadog.TaskBlock");
    assertFalse(TaskBlockAssertions.containsBlocker(events, virtualBlocker));
    assertEquals(1, TaskBlockAssertions.countBlockerEvents(events, BLOCKER));
    TaskBlockAssertions.assertContains(events, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
    TaskBlockAssertions.assertNoCorrelationId(events);
  }

  /** Dump rotation preserves the full interval until its single exit-time TaskBlock. */
  @Test
  public void liveDumpPreservesCompletedTaskBlockInterval() throws Exception {
    String workerName = "taskblock-live-dump";
    CountDownLatch armed = new CountDownLatch(1);
    CountDownLatch release = new CountDownLatch(1);
    AtomicBoolean recorded = new AtomicBoolean();
    AtomicLong logicalStart = new AtomicLong();
    AtomicLong logicalEnd = new AtomicLong();
    AtomicReference<Throwable> error = new AtomicReference<>();
    long before = profiler.getDebugCounters().getOrDefault("wc_signals_suppressed_owned_block", 0L);
    Thread worker =
        new Thread(
            () -> {
              try {
                logicalStart.set(System.nanoTime());
                long token = profiler.beginTaskBlock();
                assertTrue(token != 0);
                armed.countDown();
                assertTrue(release.await(5, TimeUnit.SECONDS));
                recorded.set(profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID));
                logicalEnd.set(System.nanoTime());
              } catch (Throwable t) {
                error.set(t);
              }
            },
            workerName);

    worker.start();
    assertTrue(armed.await(5, TimeUnit.SECONDS));
    waitForCounterAbove("wc_signals_suppressed_owned_block", before, 5_000L);
    Thread.sleep(150L);
    Path snapshot =
        Files.createTempFile(
            java.nio.file.Paths.get("/tmp/recordings"), "taskblock-live-dump-", ".jfr");
    try {
      dump(snapshot);
      JfrEvents prefix = verifyEvents(snapshot, "datadog.TaskBlock", false);
      assertEquals(0, TaskBlockAssertions.countEventsForThread(prefix, workerName));

      Thread.sleep(150L);
      release.countDown();
      worker.join(5_000L);
      assertFalse(worker.isAlive());
      if (error.get() != null) throw new AssertionError(error.get());
      assertTrue(recorded.get());

      stopProfiler();
      JfrEvents suffix = verifyEvents("datadog.TaskBlock");
      assertEquals(1, TaskBlockAssertions.countEventsForThread(suffix, workerName));
      TaskBlockAssertions.assertContainsStackTrace(suffix);
      TaskBlockAssertions.assertNoCorrelationId(suffix);

      TaskBlockAssertions.assertContains(suffix, 0L, 0L, BLOCKER, UNBLOCKING_SPAN_ID);
      double completedDuration = TaskBlockAssertions.durationNanosForThread(suffix, workerName);
      long logicalDuration = logicalEnd.get() - logicalStart.get();
      assertTrue(
          completedDuration >= logicalDuration * 0.75,
          "rotation lost TaskBlock duration: completed="
              + completedDuration
              + ", logical="
              + logicalDuration);
      assertTrue(
          completedDuration <= logicalDuration * 1.25,
          "rotation duplicated TaskBlock duration: completed="
              + completedDuration
              + ", logical="
              + logicalDuration);
    } finally {
      release.countDown();
      worker.join(5_000L);
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(snapshot);
      else System.out.println("TASK_BLOCK snapshot recording=" + snapshot.toAbsolutePath());
    }
  }

  /** Uses the JDK Cleaner's real InnocuousThread, without setting profiler flags or context. */
  private void assertJvmInternalAdmissionRejected(boolean pairedApi) throws Exception {
    Class<?> cleanerClass;
    try {
      cleanerClass = Class.forName("java.lang.ref.Cleaner");
    } catch (ClassNotFoundException beforeJdk9) {
      Assumptions.assumeTrue(false, "The default InnocuousThread Cleaner requires JDK 9");
      return;
    }
    AtomicLong ordinaryToken = new AtomicLong();
    runWorker(() -> ordinaryToken.set(enterAndCloseBlock(pairedApi)));
    assertNotEquals(
        0L, ordinaryToken.get(), "The ordinary unfiltered admission path must be armed");

    CountDownLatch completed = new CountDownLatch(1);
    AtomicBoolean reached = new AtomicBoolean();
    AtomicReference<Throwable> error = new AtomicReference<>();
    Object cleaner = cleanerClass.getMethod("create").invoke(null);
    Method register = cleanerClass.getMethod("register", Object.class, Runnable.class);
    registerCleanerAction(
        cleaner,
        register,
        () -> {
          try {
            assertEquals(
                "jdk.internal.misc.InnocuousThread", Thread.currentThread().getClass().getName());
            reached.set(true);
            long skippedBefore =
                profiler
                    .getDebugCounters()
                    .getOrDefault("task_block_skipped_jvm_internal_thread", 0L);
            long token = enterAndCloseBlock(pairedApi);
            long skippedAfter =
                profiler
                    .getDebugCounters()
                    .getOrDefault("task_block_skipped_jvm_internal_thread", 0L);
            assertEquals(0L, token, "A real JVM-internal thread must not acquire a block owner");
            assertTrue(skippedAfter > skippedBefore, "The counted JVM-internal guard must fire");
          } catch (Throwable t) {
            error.set(t);
          } finally {
            completed.countDown();
          }
        });
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
    while (completed.getCount() != 0 && System.nanoTime() < deadline) {
      System.gc();
      completed.await(50L, TimeUnit.MILLISECONDS);
    }
    assertEquals(0L, completed.getCount(), "The JDK Cleaner action must actually execute");
    assertTrue(reached.get(), "The admission scenario must run on an InnocuousThread");
    if (error.get() != null) throw new AssertionError(error.get());
  }

  /** Ends the referent's stack lifetime before the caller requests collection. */
  private static void registerCleanerAction(Object cleaner, Method register, Runnable action)
      throws Exception {
    register.invoke(cleaner, new Object(), action);
  }

  /** Closes even an unexpectedly admitted token before an assertion can fail. */
  private long enterAndCloseBlock(boolean pairedApi) {
    long token =
        pairedApi
            ? profiler.beginTaskBlock()
            : ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    if (token != 0) {
      if (pairedApi) profiler.endTaskBlock(token, BLOCKER, UNBLOCKING_SPAN_ID);
      else ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }
    return token;
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private boolean runEligibleBlock(long blocker) throws Exception {
    AtomicBoolean result = new AtomicBoolean();
    runWorker(
        () -> {
          long token = profiler.beginTaskBlock();
          if (token == 0) throw new AssertionError("interval was not armed");
          Thread.sleep(200L);
          result.set(profiler.endTaskBlock(token, blocker, UNBLOCKING_SPAN_ID));
        });
    return result.get();
  }

  private void runWorker(ThrowingRunnable action) throws Exception {
    AtomicReference<Throwable> error = new AtomicReference<>();
    Thread worker =
        new Thread(
            () -> {
              try {
                action.run();
              } catch (Throwable t) {
                error.set(t);
              }
            },
            "taskblock-paired-api");
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
