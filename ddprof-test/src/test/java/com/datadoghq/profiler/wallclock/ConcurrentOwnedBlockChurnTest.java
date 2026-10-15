/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.util.ArrayList;
import java.util.List;
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
 * chaos {@code park-block-churn} antagonist (crash-only signal), this asserts on actual sample
 * counts and debug counters, so it also catches silent over-/under-suppression regressions.
 */
public class ConcurrentOwnedBlockChurnTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;
  private static final long BLOCK_MILLIS = 60;
  private static final int WORKERS_PER_ROUND = 24;
  private static final int ROUNDS = 8;
  private static final String SUPPRESSED_RUN_COUNTER = "wc_signals_suppressed_sampled_run";

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
   * sampling every signal (under-suppression) or losing every armed run (over-suppression).
   *
   * @throws InterruptedException if a worker join is interrupted
   */
  @RetryingTest(3)
  public void churnedOwnedBlocksAreSuppressedRoughlyOncePerRun() throws InterruptedException {
    for (int round = 0; round < ROUNDS; round++) {
      List<Thread> workers = new ArrayList<>(WORKERS_PER_ROUND);
      for (int i = 0; i < WORKERS_PER_ROUND; i++) {
        Thread worker = new Thread(this::runOwnedBlock, WORKER_NAME_PREFIX + round + "-" + i);
        worker.setDaemon(true);
        workers.add(worker);
      }
      for (Thread worker : workers) {
        worker.start();
      }
      for (Thread worker : workers) {
        worker.join();
      }
    }

    stopProfiler();

    long totalArmed = armedRuns.get();
    assertTrue(totalArmed > 0, "Expected at least some owned-block runs to arm");

    long workerSamples = countWorkerSamples();
    assertTrue(
        workerSamples > 0,
        "Expected at least one sample across " + totalArmed + " armed owned-block runs");
    assertTrue(
        workerSamples <= totalArmed * 3,
        "Expected roughly one sample per armed run (under-suppression / a slot-reuse "
            + "race leaking extra samples), got "
            + workerSamples
            + " samples for "
            + totalArmed
            + " armed runs");

    long suppressedAfter = suppressedSignals();
    if (suppressedAfter >= 0) {
      assertTrue(
          suppressedAfter > 0,
          "Expected the owned-block once-per-run suppression counter to have fired at least "
              + "once under sustained churn");
    }
  }

  private void runOwnedBlock() {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
    if (token != 0) {
      armedRuns.incrementAndGet();
    }
    try {
      Thread.sleep(BLOCK_MILLIS);
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    } finally {
      ProfilerOwnedBlockHooks.blockExit(profiler, token);
    }
  }

  private long countWorkerSamples() {
    long count = 0;
    JfrEvents events = verifyEvents("datadog.MethodSample", false);
    for (JfrEvent item : events) {
      String threadName = item.getThreadName("eventThread");
      if (threadName != null && threadName.startsWith(WORKER_NAME_PREFIX)) {
        count++;
      }
    }
    return count;
  }

  private long suppressedSignals() {
    return profiler.getDebugCounters().getOrDefault(SUPPRESSED_RUN_COUNTER, -1L);
  }
}
