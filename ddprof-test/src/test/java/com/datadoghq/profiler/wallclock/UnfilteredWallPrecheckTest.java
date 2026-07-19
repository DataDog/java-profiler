/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

/** Verifies owned-block prechecks when legacy {@code filter=} samples every thread. */
public class UnfilteredWallPrecheckTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final long SLEEP_MILLIS = 300;
  private static final String PRE_EXISTING_THREAD_NAME = "unfiltered-precheck-existing";
  private static final String SUPPRESSED_OWNED_BLOCK_COUNTER =
      "wc_signals_suppressed_owned_block";

  private ExecutorService preExistingWorker;
  private Thread preExistingThread;

  /**
   * Verifies that an untraced thread's owned sleeping run is suppressed.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void sleepingThreadOutsideContextWindowIsOwnedBlockSuppressed() throws Exception {
    long suppressedBefore = suppressedSignals();
    assertTrue(
        runPreExistingSleepingWorker(false) != 0,
        "Expected native blockEnter to arm SLEEPING state");

    stopProfiler();
    assertSuppressedSamples(PRE_EXISTING_THREAD_NAME);
    assertOwnedBlockSuppressionObserved(suppressedBefore);
  }

  /**
   * Verifies that entering the context window prevents owned-block suppression in an
   * unfiltered recording.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void sleepingThreadInsideContextWindowIsNotOverSuppressed() throws Exception {
    assertTrue(
        runPreExistingSleepingWorker(true) != 0,
        "Expected native blockEnter to arm SLEEPING state");

    stopProfiler();

    long sampleCount = samplesForThread(PRE_EXISTING_THREAD_NAME);
    assertTrue(
        sampleCount >= 10,
        "Expected normal MethodSample volume inside the context window, got: " + sampleCount);
  }

  /**
   * Verifies that a pre-existing thread can lazily bind its slot through the park hook.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void parkedPreExistingThreadOutsideContextWindowIsOwnedBlockSuppressed()
      throws Exception {
    long suppressedBefore = suppressedSignals();
    runPreExistingParkedWorker();

    stopProfiler();
    assertSuppressedSamples(PRE_EXISTING_THREAD_NAME);
    assertOwnedBlockSuppressionObserved(suppressedBefore);
  }

  /**
   * Retains coverage for threads whose filter slot is installed by a post-start ThreadStart event.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void postStartSleepingThreadStillUsesThreadStartSlot() throws Exception {
    String threadName = "unfiltered-precheck-post-start";
    long suppressedBefore = suppressedSignals();
    assertTrue(
        runPostStartSleepingWorker(threadName) != 0,
        "Expected ThreadStart registration to arm SLEEPING state");

    stopProfiler();
    assertSuppressedSamples(threadName);
    assertOwnedBlockSuppressionObserved(suppressedBefore);
  }

  @Override
  protected void beforeProfilerStart() throws Exception {
    preExistingWorker =
        Executors.newSingleThreadExecutor(
            task -> {
              Thread worker = new Thread(task, PRE_EXISTING_THREAD_NAME);
              worker.setDaemon(true);
              return worker;
            });
    preExistingThread = preExistingWorker.submit(Thread::currentThread).get();
  }

  /** Stops the worker that was deliberately created before profiler startup. */
  @AfterEach
  public void stopPreExistingWorker() throws InterruptedException {
    if (preExistingWorker == null) {
      return;
    }
    preExistingWorker.shutdownNow();
    assertTrue(
        preExistingWorker.awaitTermination(5, TimeUnit.SECONDS),
        "Pre-existing wall-clock worker did not terminate");
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9();
  }

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(
        Platform.isJavaVersionAtLeast(11),
        "Sleeping-state precheck assertions are stable on JDK 11+");
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }

  private long runPreExistingSleepingWorker(boolean enterContextWindowDuringBlock)
      throws Exception {
    Future<Long> sleep =
        preExistingWorker.submit(
            () -> {
              assertSame(preExistingThread, Thread.currentThread());
              return runSleepingBlock(enterContextWindowDuringBlock);
            });
    return sleep.get();
  }

  private long runPostStartSleepingWorker(String threadName) throws Exception {
    FutureTask<Long> sleep = new FutureTask<>(() -> runSleepingBlock(false));
    Thread worker = new Thread(sleep, threadName);
    worker.start();
    return sleep.get();
  }

  private long runSleepingBlock(boolean enterContextWindowDuringBlock) throws Exception {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    if (enterContextWindowDuringBlock) {
      profiler.addThread();
    }
    try {
      Thread.sleep(SLEEP_MILLIS);
      return token;
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
      if (enterContextWindowDuringBlock) {
        profiler.removeThread();
      }
    }
  }

  private void runPreExistingParkedWorker() throws Exception {
    preExistingWorker
        .submit(
            () -> {
              assertSame(preExistingThread, Thread.currentThread());
              ProfilerOwnedBlockHooks.parkEnter(profiler);
              try {
                long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(SLEEP_MILLIS);
                while (System.nanoTime() < deadline) {
                  // Keep the OS thread runnable so suppression must come from the owned park marker.
                }
              } finally {
                ProfilerOwnedBlockHooks.parkExit(
                    profiler, System.identityHashCode(preExistingThread), 0L);
              }
              return null;
            })
        .get();
  }

  private void assertOwnedBlockSuppressionObserved(long suppressedBefore) {
    if (suppressedBefore >= 0) {
      assertTrue(
          suppressedSignals() > suppressedBefore,
          "Expected owned-block once-per-run suppression counter to increase");
    }
  }

  private long suppressedSignals() {
    return profiler.getDebugCounters().getOrDefault(SUPPRESSED_OWNED_BLOCK_COUNTER, -1L);
  }

  private void assertSuppressedSamples(String threadName) {
    long sampleCount = samplesForThread(threadName);
    assertTrue(
        sampleCount < 10,
        "Expected nearly no samples from owned block thread, got: " + sampleCount);
  }

  private long samplesForThread(String threadName) {
    long count = 0;
    IItemCollection events = verifyEvents("datadog.MethodSample", false);
    for (IItemIterable batch : events) {
      IMemberAccessor<String, IItem> threadNameAccessor =
          JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
      if (threadNameAccessor == null) {
        continue;
      }
      for (IItem item : batch) {
        if (threadName.equals(threadNameAccessor.getMember(item))) {
          count++;
        }
      }
    }
    return count;
  }
}
