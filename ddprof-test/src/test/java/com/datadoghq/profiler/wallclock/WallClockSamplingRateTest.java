/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicBoolean;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies that wallclock sampling produces sample counts consistent with the 200ms default period.
 *
 * <p>Uses the bare {@code wall} keyword (no explicit interval) so the native default
 * {@code DEFAULT_WALL_INTERVAL} is used end-to-end. The JFR {@code DatadogProfilerConfig} event is
 * validated automatically by {@link AbstractProfilerTest#stopProfiler()} asserting that the
 * recorded wall interval matches {@link AbstractProfilerTest#DEFAULT_WALL_INTERVAL}.
 *
 * <p>Upper bound formula: with period {@code P} ms and at most {@code T} threads sampled per tick,
 * the sample count over {@code D} ms is bounded by {@code (D/P + 1) * T}. The {@code +1} absorbs
 * one extra tick that may fire due to timing imprecision at test boundaries.
 */
public class WallClockSamplingRateTest extends AbstractProfilerTest {

  /**
   * Default number of threads sampled per wall-clock tick. Must match
   * {@code DEFAULT_WALL_THREADS_PER_TICK} in {@code ddprof-lib/src/main/cpp/arguments.h}.
   */
  static final int THREADS_PER_TICK = 16;

  private static final int TEST_DURATION_MS = 4_000;

  /**
   * More threads than {@link #THREADS_PER_TICK} so the profiler selects a subset each tick,
   * exercising the per-tick thread-selection path.
   */
  private static final int THREAD_COUNT = THREADS_PER_TICK + 4;

  /**
   * Verifies that the total sample count over {@link #TEST_DURATION_MS} stays within the
   * theoretical upper bound, and exceeds a meaningful lower bound confirming the profiler fired
   * consistently throughout the test window.
   *
   * <p>With {@link #THREAD_COUNT} sleeping threads ({@code > THREADS_PER_TICK}), the profiler
   * selects at most {@link #THREADS_PER_TICK} threads each tick, so total samples cannot exceed
   * {@code (TEST_DURATION_MS / periodMs + 1) * THREADS_PER_TICK}.
   */
  @RetryingTest(3)
  public void testSampleCountUpperBound() throws InterruptedException {
    AtomicBoolean running = new AtomicBoolean(true);
    CountDownLatch allStarted = new CountDownLatch(THREAD_COUNT);
    List<Thread> threads = new ArrayList<>(THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
      Thread t =
          new Thread(
              () -> {
                registerCurrentThreadForWallClockProfiling();
                allStarted.countDown();
                while (running.get()) {
                  try {
                    Thread.sleep(TEST_DURATION_MS * 2L);
                  } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                  }
                }
              });
      t.setDaemon(true);
      threads.add(t);
      t.start();
    }
    allStarted.await();

    Thread.sleep(TEST_DURATION_MS);
    stopProfiler();

    running.set(false);
    for (Thread t : threads) {
      t.interrupt();
    }

    long periodMs = DEFAULT_WALL_INTERVAL.toMillis();
    long samples =
        verifyEvents("datadog.MethodSample").getAggregate(Aggregators.count()).longValue();

    // +1 tick to absorb the first partial tick at profiler start and last at stop
    long maxSamples = (TEST_DURATION_MS / periodMs + 1) * THREADS_PER_TICK;
    // Lower bound: at least half the expected ticks fired with at least one thread sampled
    long minSamples = (TEST_DURATION_MS / periodMs / 2);
    assertTrue(
        samples >= minSamples,
        "Too few samples: "
            + samples
            + " < "
            + minSamples
            + " (period="
            + periodMs
            + "ms, threadsPerTick="
            + THREADS_PER_TICK
            + ")");
    assertTrue(
        samples <= maxSamples,
        "Sample count "
            + samples
            + " exceeds upper bound "
            + maxSamples
            + " (period="
            + periodMs
            + "ms, threadsPerTick="
            + THREADS_PER_TICK
            + ")");
  }

  /**
   * Returns the bare {@code wall} keyword so the native {@code DEFAULT_WALL_INTERVAL} (200ms) is
   * used end-to-end, testing that the default is correctly applied and recorded in JFR.
   */
  @Override
  protected String getProfilerCommand() {
    return "wall";
  }
}
