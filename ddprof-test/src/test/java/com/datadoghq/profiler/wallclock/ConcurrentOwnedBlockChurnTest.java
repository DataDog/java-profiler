/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

/**
 * Verifies owned-block once-per-run suppression stays correct under real thread churn, unlike
 * {@link UnfilteredWallPrecheckTest} and {@link UnfilteredWallPrecheckRestartTest}, which each
 * pin down one deterministic worker/interleaving. Many short-lived threads concurrently register
 * a registry slot, arm an owned SLEEPING block, block, and die (forcing JVMTI ThreadEnd / slot
 * reuse) while the wall-clock engine is sampling every thread ({@code filter=}), so this
 * specifically races {@code ThreadFilter} slot reuse against {@code WallClockBlockTracker}
 * enter/exit - the coupling introduced by splitting the tracker out of the registry. Unlike the
 * chaos {@code park-block-churn} antagonist, this asserts on actual sample counts and debug
 * counters, so it also catches silent over-/under-suppression regressions.
 */
public class ConcurrentOwnedBlockChurnTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final long BLOCK_MILLIS = 250;
  private static final int WORKERS_PER_ROUND = 24;
  private static final int ROUNDS = 8;
  private static final String SUPPRESSED_OWNED_BLOCK_COUNTER = "wc_signals_suppressed_owned_block";

  private static final String WORKER_NAME_PREFIX = "owned-block-churn-";

  private final AtomicLong armedRuns = new AtomicLong();

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
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

  /**
   * Spawns many short-lived owned-block workers across several rounds, then verifies suppression
   * collapsed the resulting signals into roughly one sample per armed run rather than either
   * sampling every signal (under-suppression) or losing most armed runs (over-suppression).
   *
   * @throws Exception if workers fail, time out, or cannot be joined
   */
  @RetryingTest(3)
  public void churnedOwnedBlocksAreSuppressedRoughlyOncePerRun() throws Exception {
    long suppressedBefore = suppressedSignals();
    for (int round = 0; round < ROUNDS; round++) {
      runRound(round);
    }

    stopProfiler();

    long totalArmed = armedRuns.get();
    assertEquals(ROUNDS * WORKERS_PER_ROUND, totalArmed, "Every worker must arm its own run");

    Map<String, Long> samples = countOwnedBlockSamples();
    for (int round = 0; round < ROUNDS; round++) {
      int sampledWorkers = 0;
      List<String> missing = new ArrayList<>();
      for (int worker = 0; worker < WORKERS_PER_ROUND; worker++) {
        String name = WORKER_NAME_PREFIX + round + "-" + worker;
        long count = samples.getOrDefault(name, 0L);
        assertTrue(count <= 3, "Repeated samples escaped suppression for " + name + ": " + count);
        if (count > 0) {
          sampledWorkers++;
        } else {
          missing.add(name);
        }
      }
      // The common start and 250 ms window give every worker repeated sampling
      // opportunities. Allow some scheduling/stack-walk failures on slow CI,
      // but require coverage in every round so early successes cannot hide
      // sample loss after slot reuse. Each sample must contain runOwnedBlock;
      // samples from the startup latch cannot satisfy this lower bound.
      assertTrue(
          sampledWorkers >= WORKERS_PER_ROUND * 3 / 4,
          "Too few owned runs sampled in round "
              + round
              + ": "
              + sampledWorkers
              + "/"
              + WORKERS_PER_ROUND
              + "; missing="
              + missing);
    }

    long suppressedAfter = suppressedSignals();
    if (suppressedBefore >= 0) {
      assertTrue(
          suppressedAfter > suppressedBefore,
          "Expected the owned-block once-per-run suppression counter to have fired at least "
              + "once under sustained churn");
    }
  }

  /** Releases a complete worker batch together and propagates failures to the test thread. */
  private void runRound(int round) throws Exception {
    CountDownLatch ready = new CountDownLatch(WORKERS_PER_ROUND);
    CountDownLatch start = new CountDownLatch(1);
    List<Thread> workers = new ArrayList<>(WORKERS_PER_ROUND);
    List<FutureTask<Void>> tasks = new ArrayList<>(WORKERS_PER_ROUND);
    try {
      for (int i = 0; i < WORKERS_PER_ROUND; i++) {
        FutureTask<Void> task =
            new FutureTask<>(
                () -> {
                  ready.countDown();
                  start.await();
                  runOwnedBlock();
                  return null;
                });
        Thread worker = new Thread(task, WORKER_NAME_PREFIX + round + "-" + i);
        worker.setDaemon(true);
        tasks.add(task);
        workers.add(worker);
        worker.start();
      }
      assertTrue(ready.await(10, TimeUnit.SECONDS), "Workers did not reach the start barrier");
      start.countDown();
      long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(10);
      for (FutureTask<Void> task : tasks) {
        task.get(Math.max(1, deadline - System.nanoTime()), TimeUnit.NANOSECONDS);
      }
    } finally {
      start.countDown();
      for (Thread worker : workers) {
        if (worker.isAlive()) worker.interrupt();
      }
      for (Thread worker : workers) {
        worker.join(TimeUnit.SECONDS.toMillis(1));
        assertTrue(!worker.isAlive(), "Worker failed to terminate: " + worker.getName());
      }
    }
  }

  /** Holds one owned interval; only stacks containing this method count as coverage. */
  private void runOwnedBlock() throws InterruptedException {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    assertNotEquals(0L, token, "Worker failed to arm its block: " + Thread.currentThread().getName());
    armedRuns.incrementAndGet();
    try {
      Thread.sleep(BLOCK_MILLIS);
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }
  }

  /** Counts each worker's owned-run samples, excluding latch waits and thread teardown. */
  private Map<String, Long> countOwnedBlockSamples() {
    Map<String, Long> counts = new HashMap<>();
    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    for (JfrEvent item : events) {
      String threadName = item.getThreadName("eventThread");
      if (threadName != null && threadName.startsWith(WORKER_NAME_PREFIX)) {
        for (JfrFrame frame : item.getStackTrace().frames()) {
          if (ConcurrentOwnedBlockChurnTest.class.getName().equals(frame.className())
              && "runOwnedBlock".equals(frame.methodName())) {
            counts.merge(threadName, 1L, Long::sum);
            break;
          }
        }
      }
    }
    return counts;
  }

  private long suppressedSignals() {
    return profiler.getDebugCounters().getOrDefault(SUPPRESSED_OWNED_BLOCK_COUNTER, -1L);
  }
}
