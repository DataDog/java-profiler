/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.stresstest.scenarios.taskblock;

import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.EMITTED;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.check;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.checkBetween;
import static com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.delta;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.stresstest.scenarios.taskblock.TaskBlockBenchmarkSupport.Recording;
import java.util.Locale;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
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
import org.openjdk.jmh.infra.IterationParams;
import org.openjdk.jmh.runner.IterationType;

/**
 * Measures how TaskBlock recording on a contended monitor delays the lock's critical section.
 *
 * <p>The JMH thread is the holder, excluded from TaskBlock by a trace context: each op holds one
 * monitor for {@code holdMicros} (above the 1 ms emission threshold) and pauses briefly without it,
 * so the JMH score is the holder's time per hold (inverse throughput). {@code waiters} ordinary
 * threads contend for the same monitor. A blocked waiter's TaskBlock is emitted by a JVMTI monitor
 * event that fires after the waiter acquires the lock and before it returns to user code, so its
 * stack capture runs inside the critical section.
 *
 * <p>Two means over the measurement iterations are printed in the teardown ({@code
 * [taskblock-bench] contended ...}): {@code handoffUs}, from the holder's release to the first user
 * instruction of the waiter that acquired next, and {@code holderAcquireUs}, how long the holder
 * waits to take the lock back.
 *
 * <p>{@code config=none} loads the library without a recording, {@code wall} is wall-clock without
 * TaskBlock and {@code taskblock} turns it on. The teardown fails unless the {@code taskblock}
 * variant emitted at least half as many TaskBlocks as holds and the others none.
 */
@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.MICROSECONDS)
@Fork(value = 1, warmups = 0)
@Warmup(iterations = 3, time = 2)
@Measurement(iterations = 5, time = 3)
@Threads(1)
@State(Scope.Benchmark)
public class TaskBlockContendedHoldBenchmark {
  @Param({"none", "wall", "taskblock"})
  public String config;

  @Param({"1", "4"})
  public int waiters;

  /** Time the monitor is held per op; above the 1 ms emission threshold. */
  @Param({"1200"})
  public long holdMicros;

  /** Allowance for the in-flight hold and for JMH or JVM threads that block once or twice. */
  private static final long SLACK = 16;

  /** Pause between holds and between waiter acquisitions, so waiters get a turn and block again. */
  private static final long HOLDER_PAUSE_NANOS = 50_000;

  private static final long WAITER_PAUSE_NANOS = 100_000;

  private final AtomicReference<Throwable> failure = new AtomicReference<>();
  private final Object lock = new Object();
  private final AtomicLong handoffNanos = new AtomicLong();
  private final AtomicLong handoffs = new AtomicLong();
  private JavaProfiler profiler;
  private Recording recording;
  private Thread[] threads;
  private volatile boolean running;
  private volatile boolean measuring;

  /** Written by the holder just before it releases and cleared by the first waiter inside. */
  private volatile long releaseStamp;

  private long holderAcquireNanos;
  private long holds;
  private long measuredHolds;

  @Setup(Level.Trial)
  public void setup() throws Exception {
    profiler = TaskBlockBenchmarkSupport.loadProfiler();
    recording = Recording.start(profiler, config);
    // This setup runs on the single JMH thread that is the holder; its blocks must not emit.
    TaskBlockBenchmarkSupport.excludeFromTaskBlock(recording.taskBlockActive() ? profiler : null);
    running = true;
    threads = new Thread[waiters];
    for (int i = 0; i < waiters; i++) {
      threads[i] = new Thread(this::contend, "taskblock-contender-" + i);
      threads[i].setDaemon(true);
      threads[i].start();
    }
  }

  /** Keeps only the figures of measurement iterations. */
  @Setup(Level.Iteration)
  public void startIteration(IterationParams iteration) {
    measuring = iteration.getType() == IterationType.MEASUREMENT;
  }

  private void contend() {
    try {
      while (running) {
        synchronized (lock) {
          // Taken right after the (possibly TaskBlock-instrumented) enter returns.
          long now = System.nanoTime();
          long released = releaseStamp;
          if (released != 0) {
            releaseStamp = 0;
            if (measuring) {
              handoffNanos.addAndGet(now - released);
              handoffs.incrementAndGet();
            }
          }
        }
        LockSupport.parkNanos(WAITER_PAUSE_NANOS);
      }
    } catch (Throwable t) {
      failure.compareAndSet(null, t);
    }
  }

  @Benchmark
  public void hold() {
    long start = System.nanoTime();
    synchronized (lock) {
      if (measuring) {
        holderAcquireNanos += System.nanoTime() - start;
        measuredHolds++;
      }
      // Busy wait: the holder must stay runnable and never enter a park hook while it holds.
      long deadline = System.nanoTime() + TimeUnit.MICROSECONDS.toNanos(holdMicros);
      while (System.nanoTime() < deadline) {
        // spin
      }
      holds++;
      releaseStamp = System.nanoTime();
    }
    LockSupport.parkNanos(HOLDER_PAUSE_NANOS);
  }

  /** Reports the means and checks emission as {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    running = false;
    for (Thread thread : threads) {
      thread.join(TimeUnit.SECONDS.toMillis(5));
    }
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    long count = handoffs.get();
    System.out.printf(
        Locale.ROOT,
        "[taskblock-bench] contended benchmark=%s config=%s waiters=%d holds=%d handoffs=%d"
            + " handoffUs=%.1f holderAcquireUs=%.1f%n",
        benchmark,
        config,
        waiters,
        holds,
        count,
        count == 0 ? Double.NaN : handoffNanos.get() / 1e3 / count,
        measuredHolds == 0 ? Double.NaN : holderAcquireNanos / 1e3 / measuredHolds);
    check(failure.get() == null, "Contender failed: " + failure.get());
    check(holds > 0, benchmark + " made no holds");
    if (TaskBlockBenchmarkSupport.NONE.equals(config)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    if (!recording.taskBlockActive()) {
      check(emitted == 0, benchmark + " emitted TaskBlock events with TaskBlock off");
      return;
    }
    // A blocked waiter emits one event per hold at most; with several waiters each may emit.
    checkBetween("emitted", emitted, holds / 2, holds * waiters + SLACK);
  }
}
