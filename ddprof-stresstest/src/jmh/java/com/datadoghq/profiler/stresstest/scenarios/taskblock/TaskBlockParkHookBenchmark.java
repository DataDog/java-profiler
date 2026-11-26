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
import com.datadoghq.profiler.TaskBlockBenchmarkHooks;
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
 * Measures the park hooks dd-trace-java's {@code LockSupport} advice calls around {@code park}.
 *
 * <ul>
 *   <li>{@code park}: {@code unpark(self)} then {@code park()}, which returns at once on the
 *       permit. The baseline for {@code hookedPark}.
 *   <li>{@code hookedPark}: the same park between {@code parkEnter} and {@code parkExit}. The
 *       difference to {@code park} is the hook cost of a park that does not block.
 *   <li>{@code exitEmitting}: only the {@code parkExit} call that closes a park of {@code
 *       blockMicros}; with TaskBlock on it captures a stack and writes one JFR event. The park is
 *       entered and waited out in an untimed per-invocation setup.
 * </ul>
 *
 * <p>Baseline: {@code config=none}, where the library is loaded but no recording runs. {@code
 * config=wall} is wall-clock without TaskBlock; {@code config=taskblock} turns TaskBlock on. The
 * trial teardown fails unless the hooks owned and emitted as {@code config} implies.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@Threads(1)
@State(Scope.Thread)
public class TaskBlockParkHookBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  private JavaProfiler profiler;
  private Recording recording;
  private Thread self;
  private long calls;
  private long owned;

  @Setup(Level.Trial)
  public void setup() throws Exception {
    profiler = TaskBlockBenchmarkSupport.loadProfiler();
    self = Thread.currentThread();
    recording = Recording.start(profiler, config);
  }

  /** Checks that the hooks owned and emitted what {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    System.out.printf(
        "[taskblock-bench] benchmark=%s calls=%d owned=%d%n", benchmark, calls, owned);
    check(calls > 0, benchmark + " made no calls");
    if ("park".equals(benchmark)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    if (!recording.taskBlockActive()) {
      check(emitted == 0, benchmark + " emitted TaskBlock events with TaskBlock off");
      return;
    }
    check(owned == calls, benchmark + " owned " + owned + " of " + calls + " parks");
    if ("hookedPark".equals(benchmark)) {
      check(emitted * 100 <= calls, benchmark + " emitted " + emitted + " short parks");
      check(delta(deltas, TOO_SHORT) > 0, benchmark + " never reached the duration check");
    } else {
      check(emitted * 2 >= calls, benchmark + " emitted " + emitted + " of " + calls);
    }
  }

  @Benchmark
  public void park() {
    LockSupport.unpark(self);
    LockSupport.park();
    calls++;
  }

  @Benchmark
  public void hookedPark() {
    boolean entered = TaskBlockBenchmarkHooks.parkEnter(profiler);
    LockSupport.unpark(self);
    LockSupport.park();
    if (entered) {
      TaskBlockBenchmarkHooks.parkExit(profiler);
      owned++;
    }
    calls++;
  }

  @Benchmark
  public void exitEmitting(EnteredPark park) {
    if (park.entered) {
      TaskBlockBenchmarkHooks.parkExit(profiler);
      owned++;
    }
    calls++;
  }

  /**
   * Enters a park and waits it out before each {@code exitEmitting} call. It takes the profiler
   * singleton itself: injecting the benchmark state here would make JMH create a second one.
   */
  @State(Scope.Thread)
  public static class EnteredPark {
    /** Length of the park; above the 1 ms emission threshold. */
    @Param({"1200"})
    public long blockMicros;

    private JavaProfiler profiler;
    boolean entered;

    @Setup(Level.Trial)
    public void load() throws Exception {
      profiler = TaskBlockBenchmarkSupport.loadProfiler();
    }

    @Setup(Level.Invocation)
    public void enter() {
      entered = TaskBlockBenchmarkHooks.parkEnter(profiler);
      TaskBlockPairedApiBenchmark.parkAtLeast(TimeUnit.MICROSECONDS.toNanos(blockMicros));
    }
  }
}
