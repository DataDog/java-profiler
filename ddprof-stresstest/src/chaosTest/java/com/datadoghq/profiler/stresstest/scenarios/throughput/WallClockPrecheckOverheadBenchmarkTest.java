/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.stresstest.scenarios.throughput;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JavaProfiler;
import java.lang.reflect.Field;
import java.util.concurrent.CountDownLatch;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Exercises benchmark setup against real owned-block hooks before measurement. */
@Timeout(40)
class WallClockPrecheckOverheadBenchmarkTest {
  @BeforeEach
  void supportedEngine() {
    Assumptions.assumeFalse(System.getProperty("java.vm.name", "").contains("J9"));
  }

  @AfterEach
  void noWorkersLeftBehind() {
    for (Thread thread : Thread.getAllStackTraces().keySet()) {
      assertFalse(
          thread.getName().startsWith("wall-precheck-benchmark-"),
          "Benchmark setup/teardown leaked " + thread.getName());
    }
  }

  @ParameterizedTest
  @ValueSource(booleans = {false, true})
  void setupWaitsForActualSuppressionWhenEnabled(boolean precheck) throws Exception {
    WallClockPrecheckOverheadBenchmark benchmark = benchmark(precheck);
    try {
      benchmark.setup();
      if (precheck) {
        assertTrue(
            JavaProfiler.getInstance().getDebugCounters().get("wc_signals_suppressed_sampled_run")
                > 0);
      }
    } finally {
      benchmark.tearDown();
    }
  }

  @Test
  void workerAwaitFailureIsPropagatedAndCleanedUp() throws Exception {
    WallClockPrecheckOverheadBenchmark benchmark = benchmark(false);
    setStartLatch(
        benchmark,
        new CountDownLatch(1) {
          @Override
          public void await() throws InterruptedException {
            throw new InterruptedException("worker setup interrupted");
          }
        });
    IllegalStateException failure = assertThrows(IllegalStateException.class, benchmark::setup);
    assertTrue(failure.getCause() instanceof InterruptedException, failure.toString());
  }

  @Test
  void zeroOwnedTokenFailsSetupAndCleansUp() throws Exception {
    WallClockPrecheckOverheadBenchmark benchmark = benchmark(true);
    JavaProfiler profiler = JavaProfiler.getInstance();
    setStartLatch(
        benchmark,
        new CountDownLatch(1) {
          @Override
          public void await() throws InterruptedException {
            super.await();
            profiler.stop();
          }
        });
    IllegalStateException failure = assertThrows(IllegalStateException.class, benchmark::setup);
    assertTrue(failure.getCause().getMessage().contains("returned no token"), failure.toString());
  }

  private static WallClockPrecheckOverheadBenchmark benchmark(boolean precheck) {
    WallClockPrecheckOverheadBenchmark benchmark = new WallClockPrecheckOverheadBenchmark();
    benchmark.precheck = precheck;
    benchmark.threadCount = 1;
    return benchmark;
  }

  /** Controls the real worker's pre-hook boundary without adding a production test seam. */
  private static void setStartLatch(
      WallClockPrecheckOverheadBenchmark benchmark, CountDownLatch latch) throws Exception {
    Field field = WallClockPrecheckOverheadBenchmark.class.getDeclaredField("profilerStarted");
    field.setAccessible(true);
    field.set(benchmark, latch);
  }
}
