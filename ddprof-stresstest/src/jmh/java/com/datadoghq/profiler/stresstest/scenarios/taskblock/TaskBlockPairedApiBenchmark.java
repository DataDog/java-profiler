/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.EMITTED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.TOO_SHORT;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.check;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.delta;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.Recording;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.LockSupport;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Level;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.OutputTimeUnit;
import org.openjdk.jmh.annotations.Param;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.TearDown;
import org.openjdk.jmh.annotations.Threads;
import org.openjdk.jmh.annotations.Warmup;
import org.openjdk.jmh.infra.BenchmarkParams;

/**
 * Measures the public paired API, {@link JavaProfiler#beginTaskBlock()} and {@link
 * JavaProfiler#endTaskBlock(long, long, long)}, which dd-trace-java calls around {@code
 * Thread.sleep}.
 *
 * <ul>
 *   <li>{@code shortPair}: begin then end with nothing in between. The interval is below the 1 ms
 *       emission threshold, so this is the cost every instrumented call pays when it does not
 *       block.
 *   <li>{@code endEmitting}: only the {@code endTaskBlock} call that closes an interval of {@code
 *       blockMicros}; with TaskBlock on it captures a stack and writes one JFR event. The interval
 *       is opened, and waited out, in an untimed per-invocation setup.
 * </ul>
 *
 * <p>Baseline: {@code config=none}, where the library is loaded but no recording runs and both
 * calls return immediately. {@code config=wall} is wall-clock without TaskBlock; {@code
 * config=taskblock} turns TaskBlock on. The trial teardown fails unless every interval was armed
 * and recorded as {@code config} implies.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@Threads(1)
@State(Scope.Thread)
public class TaskBlockPairedApiBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  private JavaProfiler profiler;
  private Recording recording;
  private long calls;
  private long armed;
  private long recorded;

  @Setup(Level.Trial)
  public void setup() throws Exception {
    profiler = TaskBlockBenchmarkSupport.loadProfiler();
    recording = Recording.start(profiler, config);
  }

  /** Checks that the measured path armed and recorded what {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    System.out.printf(
        "[taskblock-bench] benchmark=%s calls=%d armed=%d recorded=%d%n",
        benchmark, calls, armed, recorded);
    check(calls > 0, benchmark + " made no calls");
    if (!recording.taskBlockActive()) {
      check(armed == 0 && recorded == 0, benchmark + " armed or recorded with TaskBlock off");
      check(
          delta(deltas, EMITTED) == 0, benchmark + " emitted TaskBlock events with TaskBlock off");
      return;
    }
    check(armed == calls, benchmark + " armed " + armed + " of " + calls + " intervals");
    if ("shortPair".equals(benchmark)) {
      // A preempted pair can exceed 1 ms; anything above 1% means the short path is not short.
      check(recorded * 100 <= calls, benchmark + " recorded " + recorded + " short intervals");
      check(delta(deltas, TOO_SHORT) > 0, benchmark + " never reached the duration check");
    } else {
      check(recorded * 2 >= calls, benchmark + " recorded " + recorded + " of " + calls);
    }
  }

  @Benchmark
  public boolean shortPair() {
    long token = profiler.beginTaskBlock();
    boolean result = profiler.endTaskBlock(token, 0, 0);
    calls++;
    if (token != 0) armed++;
    if (result) recorded++;
    return result;
  }

  @Benchmark
  public boolean endEmitting(OpenInterval interval) {
    boolean result = profiler.endTaskBlock(interval.token, 0, 0);
    calls++;
    if (interval.token != 0) armed++;
    if (result) recorded++;
    return result;
  }

  /**
   * Opens a paired interval and waits it out before each {@code endEmitting} call. It takes the
   * profiler singleton itself: injecting the benchmark state here would make JMH create a second
   * one.
   */
  @State(Scope.Thread)
  public static class OpenInterval {
    /** Length of the interval; above the 1 ms emission threshold. */
    @Param({"1200"})
    public long blockMicros;

    private JavaProfiler profiler;
    long token;

    @Setup(Level.Trial)
    public void load() throws Exception {
      profiler = TaskBlockBenchmarkSupport.loadProfiler();
    }

    @Setup(Level.Invocation)
    public void open() {
      token = profiler.beginTaskBlock();
      parkAtLeast(TimeUnit.MICROSECONDS.toNanos(blockMicros));
    }
  }

  /** Parks until {@code nanos} have elapsed; {@code parkNanos} may return early. */
  static void parkAtLeast(long nanos) {
    long deadline = System.nanoTime() + nanos;
    for (long left = nanos; left > 0; left = deadline - System.nanoTime()) {
      LockSupport.parkNanos(left);
    }
  }
}
