/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;

/** Verifies owned-block prechecks when legacy {@code filter=} samples every thread. */
public class UnfilteredWallPrecheckTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final long SLEEP_MILLIS = 300;
  private static final String PRE_EXISTING_THREAD_NAME = "unfiltered-precheck-existing";
  private static final String SUPPRESSED_OWNED_BLOCK_COUNTER = "wc_signals_suppressed_owned_block";
  private static final String REGISTRATION_COUNTER = "thread_registry_hook_reregistration";
  private static final String UNOWNED_SUPPRESSED_COUNTER = "wc_unowned_blocked_suppressed";

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

  /** Context-window membership excludes owned-block suppression in an unfiltered recording. */
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
  public void parkedPreExistingThreadOutsideContextWindowIsOwnedBlockSuppressed() throws Exception {
    long suppressedBefore = suppressedSignals();
    runPreExistingParkedWorker();

    stopProfiler();
    assertSuppressedSamples(PRE_EXISTING_THREAD_NAME);
    assertOwnedBlockSuppressionObserved(suppressedBefore);
  }

  /**
   * Verifies represented observations after an owned block. Stackful ASGCT combines suppressed
   * observations into weighted events; delegated collection retains one unit per event.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void unownedSleepAfterOwnedBlockPreservesSampleWeight() throws Exception {
    assertTrue(
        runPreExistingUnownedSleepingWorker() != 0,
        "Expected the setup block to register the worker");

    boolean delegated = profiler.getStatus().contains("WallClock Engine : WallClock (JVMTI)");
    stopProfiler();

    long samples = 0;
    long weight = 0;
    long sleepingWeight = 0;
    for (JfrEvent sample : verifyEvents("datadog.MethodSample")) {
      if (!PRE_EXISTING_THREAD_NAME.equals(sample.getThreadName("eventThread"))) continue;
      assertEquals(Long.valueOf(preExistingThread.getId()), sample.getThreadJavaId("eventThread"));
      assertNotNull(sample.getLong("weight"));
      assertTrue(sample.getLong("weight") > 0);
      samples++;
      weight += sample.getLong("weight");
      assertNotNull(sample.getEnumName(THREAD_STATE));
      if (delegated) {
        assertTrue(sample.getStackTrace().isEmpty(), "Delegated samples have no local stack");
        assertTrue(
            sample.getLong("correlationId", 0L) > 0,
            "Delegated native samples must have a stack-request correlation ID");
      } else {
        String stack = sample.getStackTraceString();
        // HotSpot 25 sleep_nanos uses OSThreadWaitState(false), reported as PARKED.
        // Require the actual sleep workload, not a VM-version-dependent OS state name.
        if (stack != null
            && stack.contains("java.lang.Thread.sleep")
            && stack.contains("runPreExistingUnownedSleepingWorker")) {
          sleepingWeight += sample.getLong("weight");
        }
      }
    }
    // Weight counts received sampling signals, including coalesced unowned observations;
    // it is not elapsed time divided by the requested interval (timers can deliver late).
    assertTrue(samples > 0 && weight >= samples, "Missing positive-weight unowned samples");
    assertTrue(
        weight >= 10, "Expected ordinary MethodSample weight after owned exit, got: " + weight);
    if (!delegated) {
      assertTrue(
          sleepingWeight >= 10,
          "Expected resolved sleeping-workload sample weight after owned exit, got: "
              + sleepingWeight);
    }
    System.out.println(
        "UNOWNED_POPULATION workerJavaId="
            + preExistingThread.getId()
            + " samples="
            + samples
            + " weight="
            + weight
            + " sleepingWeight="
            + sleepingWeight
            + " stackEvidence="
            + (delegated ? "native-request-only" : "resolved-local"));
    if (usesWeightedUnownedFallback()) {
      assertTrue(
          profiler.getDebugCounters().getOrDefault("wc_unowned_blocked_recorded", 0L) > 0,
          "ASGCT unowned fallback must record weighted observations");
      assertTrue(weight > samples, "Coalesced unowned observations must retain their weight");
    } else {
      assertEquals(samples, weight, "Delegated unowned samples must retain unit weight");
      assertEquals(
          Long.valueOf(0L), profiler.getDebugCounters().get("wc_unowned_blocked_recorded"));
      assertEquals(
          Long.valueOf(0L), profiler.getDebugCounters().get("wc_unowned_blocked_suppressed"));
    }
  }

  /** Whether this engine combines suppressed unowned observations into weighted events. */
  protected boolean usesWeightedUnownedFallback() {
    return true;
  }

  /**
   * Verifies ordinary sampling for a post-start thread with TLS but no registry entry, as also
   * occurs at capacity.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void unregisteredThreadUsesNormalSampling() throws Exception {
    long registrationsBefore = registrationCount();
    String threadName = "unfiltered-precheck-unregistered";
    FutureTask<Void> sleep =
        new FutureTask<>(
            () -> {
              Thread.sleep(SLEEP_MILLIS);
              return null;
            });
    Thread worker = new Thread(sleep, threadName);
    worker.start();
    sleep.get();
    if (registrationsBefore >= 0) {
      assertEquals(
          registrationsBefore,
          registrationCount(),
          "Ordinary sampling should not allocate a registry slot");
    }

    stopProfiler();
    long sampleCount = samplesForThread(threadName);
    assertTrue(
        sampleCount >= 10,
        "Expected ordinary samples without a registry entry, got: " + sampleCount);
  }

  /**
   * Verifies that post-start threads reserve a registry slot only on their first owned-block hook.
   *
   * @throws Exception if the worker cannot complete
   */
  @RetryingTest(3)
  public void postStartSleepingThreadLazilyRegistersOwnedBlock() throws Exception {
    long suppressedBefore = suppressedSignals();
    String threadName = "unfiltered-precheck-post-start";
    long registrationsBefore = registrationCount();
    assertTrue(
        runPostStartSleepingWorker(threadName) != 0,
        "Expected the owned-block hook to register and arm SLEEPING state");
    if (registrationsBefore >= 0) {
      assertTrue(
          registrationCount() > registrationsBefore,
          "The first owned-block hook should register lazily; ThreadStart must not reserve a slot");
    }

    stopProfiler();
    assertSuppressedSamples(threadName);
    assertOwnedBlockSuppressionObserved(suppressedBefore);
  }

  /**
   * Verifies that a traced thread does not arm an owned block run and that the skip is counted.
   *
   * @throws Exception if the worker cannot complete
   */
  @Test
  public void tracedBlockEnterIsSkippedAndCounted() throws Exception {
    FutureTask<Long> traced =
        new FutureTask<>(
            () -> {
              profiler.setTraceContext(0x5200L, 0x5201L, 0L, 0x5201L, -1, null, -1, null);
              try {
                return ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
              } finally {
                profiler.clearTraceContext();
              }
            });
    Thread worker = new Thread(traced, "unfiltered-precheck-traced");
    worker.start();
    assertEquals(0L, traced.get().longValue(), "A traced thread must not arm an owned block run");

    stopProfiler();
    assertTrue(
        getRecordedCounterValue("block_enter_skipped_trace_context") > 0,
        "The trace-context skip in blockEnter must be counted");
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

  private long runPreExistingUnownedSleepingWorker() throws Exception {
    return preExistingWorker
        .submit(
            () -> {
              assertSame(preExistingThread, Thread.currentThread());
              long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
              ProfilerOwnedBlockHooks.blockExit(profiler, token);
              Thread.sleep(SLEEP_MILLIS);
              return token;
            })
        .get();
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
                  // Keep the worker runnable; Thread.yield is available with --release 8.
                  Thread.yield();
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

  private long registrationCount() {
    return profiler.getDebugCounters().getOrDefault(REGISTRATION_COUNTER, -1L);
  }

  private long suppressedSignals() {
    return profiler.getDebugCounters().getOrDefault(SUPPRESSED_OWNED_BLOCK_COUNTER, -1L);
  }

  private void assertSuppressedSamples(String threadName) {
    long sampleCount = samplesForThread(threadName);
    assertTrue(sampleCount >= 1, "Expected the owned block's first MethodSample to be retained");
    assertTrue(
        sampleCount < 10,
        "Expected samples after the first owned-block sample to be suppressed, got: "
            + sampleCount);
  }

  private long samplesForThread(String threadName) {
    long count = 0;
    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName("eventThread"))) {
        count++;
      }
    }
    return count;
  }
}
