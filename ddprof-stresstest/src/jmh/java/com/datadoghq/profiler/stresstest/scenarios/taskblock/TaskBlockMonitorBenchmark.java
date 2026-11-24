/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.EMITTED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.NONE;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.TOO_SHORT;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.check;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.checkBetween;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.delta;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.Recording;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.LockSupport;
import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Group;
import org.openjdk.jmh.annotations.GroupThreads;
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
import org.openjdk.jmh.infra.Blackhole;

/**
 * Measures the JVMTI {@code MonitorContendedEnter/Entered} and {@code MonitorWait/Waited} TaskBlock
 * producers. TaskBlock recording enables those events; {@code Object.wait} is native-owned here
 * because {@code JavaProfiler.getInstance()} does not delegate it to Java instrumentation.
 *
 * <ul>
 *   <li>{@code uncontended}: an uncontended {@code synchronized} block. No callback fires; any
 *       difference is the cost of the events being enabled at all.
 *   <li>{@code contended}: four threads on one lock with short critical sections. Callbacks fire on
 *       every contended entry, below the 1 ms threshold, so no event is written.
 *   <li>{@code pingPong} group: two threads alternating through {@code wait}/{@code notify}, so
 *       every operation pays one short {@code MonitorWait/Waited} pair.
 *   <li>{@code timedWait}: {@code wait(blockMillis)} that times out and emits one event per call.
 *   <li>{@code contendedLong} group: a holder keeps the lock for {@code blockMillis}, so about one
 *       waiter entry per hold blocks and emits a contended-enter event. Waiter entries between
 *       holds are uncontended, so its score is a regression check, not a per-event cost.
 * </ul>
 *
 * <p>Baseline: {@code config=none}, which never loads the library, so no JVMTI capability is added.
 * {@code config=wall} loads it and samples wall-clock without TaskBlock; {@code config=taskblock}
 * enables the monitor events. The trial teardown fails unless the producers reached the duration
 * check or emitted as {@code config} implies.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@State(Scope.Benchmark)
public class TaskBlockMonitorBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  /** Wait or hold time of the emitting benchmarks; above the 1 ms emission threshold. */
  @Param({"2"})
  public long blockMillis;

  /** Allowance for JMH or JVM threads that block once or twice during the trial. */
  private static final long SLACK = 16;

  private final Object lock = new Object();
  private final AtomicLong holds = new AtomicLong();
  private final AtomicLong threadLocalCalls = new AtomicLong();
  private JavaProfiler profiler;
  private Recording recording;
  private boolean pingTurn = true;
  private long lockedCalls;

  @Setup(Level.Trial)
  public void setup() throws Exception {
    profiler = NONE.equals(config) ? null : TaskBlockBenchmarkSupport.loadProfiler();
    recording = Recording.start(profiler, config);
  }

  /** Checks that the monitor producers ran, or stayed silent, as {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    long ops;
    synchronized (lock) {
      ops = lockedCalls + threadLocalCalls.get();
    }
    System.out.printf("[taskblock-bench] benchmark=%s calls=%d%n", benchmark, ops);
    check(ops > 0, benchmark + " made no calls");
    if (NONE.equals(config)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    long tooShort = delta(deltas, TOO_SHORT);
    if (!recording.taskBlockActive()) {
      check(emitted == 0 && tooShort == 0, benchmark + " reached TaskBlock with TaskBlock off");
      return;
    }
    if ("contended".equals(benchmark)) {
      check(tooShort > 0, benchmark + " never reached the duration check");
    } else if ("pingPong".equals(benchmark)) {
      // Each operation waits at most once and may also contend once; both are short.
      checkBetween("pingPong events", tooShort + emitted, ops / 4, 2 * ops + SLACK);
    } else if ("timedWait".equals(benchmark)) {
      check(emitted * 2 >= ops, benchmark + " emitted " + emitted + " of " + ops);
    } else if ("contendedLong".equals(benchmark)) {
      // Holds are the only long blocks: the holder is excluded, so the waiter emits at most one
      // event per hold.
      checkBetween("emitted", emitted, holds.get() / 2, holds.get() + SLACK);
    }
  }

  /**
   * Per-thread lock, so the monitor is never contended. Publishes its calls per iteration: JMH runs
   * every iteration teardown before the benchmark state's trial teardown reads the total.
   */
  @State(Scope.Thread)
  public static class ThreadLock {
    final Object lock = new Object();
    long calls;

    @TearDown(Level.Iteration)
    public void publish(TaskBlockMonitorBenchmark benchmark) {
      benchmark.threadLocalCalls.addAndGet(calls);
      calls = 0;
    }
  }

  /** Marks the holder's JMH worker thread ineligible once, so its own blocking cannot count. */
  @State(Scope.Thread)
  public static class HolderThread {
    private boolean excluded;

    void exclude(TaskBlockMonitorBenchmark benchmark) {
      if (!excluded && benchmark.recording.taskBlockActive()) {
        TaskBlockBenchmarkSupport.excludeFromTaskBlock(benchmark.profiler);
      }
      excluded = true;
    }
  }

  @Benchmark
  @Threads(1)
  public long uncontended(ThreadLock local) {
    synchronized (local.lock) {
      return ++local.calls;
    }
  }

  @Benchmark
  @Threads(4)
  public void contended() {
    synchronized (lock) {
      Blackhole.consumeCPU(200);
      lockedCalls++;
    }
  }

  @Benchmark
  @Group("pingPong")
  @GroupThreads(1)
  public void ping() throws InterruptedException {
    handOff(true);
  }

  @Benchmark
  @Group("pingPong")
  @GroupThreads(1)
  public void pong() throws InterruptedException {
    handOff(false);
  }

  /**
   * Waits for this side's turn, then passes it to the other side. The 10 ms bound lets the last
   * operation finish when the other thread has already left the iteration.
   */
  private void handOff(boolean ping) throws InterruptedException {
    synchronized (lock) {
      long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(10);
      while (pingTurn != ping && System.nanoTime() < deadline) {
        lock.wait(10);
      }
      pingTurn = !ping;
      lock.notify();
      lockedCalls++;
    }
  }

  @Benchmark
  @Threads(1)
  public void timedWait(ThreadLock local) throws InterruptedException {
    synchronized (local.lock) {
      local.lock.wait(blockMillis);
      local.calls++;
    }
  }

  /** Holds the lock for {@code blockMillis}, then briefly parks so the waiter can win it. */
  @Benchmark
  @Group("contendedLong")
  @GroupThreads(1)
  public void holder(HolderThread thread) {
    thread.exclude(this);
    holds.incrementAndGet();
    synchronized (lock) {
      long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(blockMillis);
      while (System.nanoTime() < deadline) {
        Blackhole.consumeCPU(100);
      }
    }
    LockSupport.parkNanos(TimeUnit.MICROSECONDS.toNanos(50));
  }

  @Benchmark
  @Group("contendedLong")
  @GroupThreads(1)
  public void waiter() {
    synchronized (lock) {
      lockedCalls++;
    }
  }
}
