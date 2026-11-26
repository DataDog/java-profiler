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
import java.util.Arrays;
import java.util.Locale;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
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
 * Measures how TaskBlock recording on a contended monitor delays the critical section. The JMH
 * thread, excluded by a trace context, holds the monitor for {@code holdMicros}, releases it, waits
 * until a waiter has taken it, then re-enters. A blocked waiter's capture runs after it acquires
 * the lock, so it delays that re-entry.
 *
 * <p>The teardown prints {@code handoffUs} (release to the waiter's first user instruction) and
 * {@code holderWaitUs} p50/mean (release to the holder's re-entry), over holds taken by a waiter
 * that had waited at least {@code BLOCKED_NANOS} to enter, so it really blocked.
 *
 * <p>The teardown fails unless {@code taskblock} emitted at least half as many TaskBlocks as holds
 * and {@code wall} none.
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

  /** Hold time; well above 1 ms so a waiter's blocked time clears the emission threshold. */
  @Param({"2000"})
  public long holdMicros;

  /** Allowance for the in-flight hold and for JMH or JVM threads that block once or twice. */
  private static final long SLACK = 16;

  /** Pause that lets the next hold start before a waiter re-enters. */
  private static final long WAITER_PAUSE_NANOS = 100_000;

  /** Minimum wait that proves a waiter blocked: a fraction of the hold, far above a lock spin. */
  private static final long BLOCKED_NANOS = 500_000;

  private static final long TAKE_TIMEOUT_NANOS = TimeUnit.SECONDS.toNanos(1);
  private static final int MAX_SAMPLES = 1 << 16;

  private final AtomicReference<Throwable> failure = new AtomicReference<>();
  private final Object lock = new Object();
  private final AtomicLong handoffNanos = new AtomicLong();
  private final AtomicLong handoffs = new AtomicLong();
  private JavaProfiler profiler;
  private Recording recording;
  private Thread[] threads;
  private volatile boolean running;
  private volatile boolean measuring;

  /** Set by the holder just before release; the first waiter inside clears it. */
  private volatile long releaseStamp;

  /** Whether the waiter that took the lock after the last release had blocked to enter. */
  private volatile boolean takenBlocked;

  private final AtomicLong holds = new AtomicLong();
  private final long[] holderWaits = new long[MAX_SAMPLES];
  private final AtomicInteger stored = new AtomicInteger();

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
        long tried = System.nanoTime();
        synchronized (lock) {
          long now = System.nanoTime();
          long released = releaseStamp;
          if (released != 0) {
            boolean blocked = now - tried >= BLOCKED_NANOS;
            if (blocked && measuring) {
              handoffNanos.addAndGet(now - released);
              handoffs.incrementAndGet();
            }
            takenBlocked = blocked;
            releaseStamp = 0;
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
    long released;
    synchronized (lock) {
      // Busy wait: the holder must stay runnable and never enter a park hook while it holds.
      long deadline = System.nanoTime() + TimeUnit.MICROSECONDS.toNanos(holdMicros);
      while (System.nanoTime() < deadline) {
        // spin
      }
      holds.incrementAndGet();
      takenBlocked = false;
      released = System.nanoTime();
      releaseStamp = released;
    }
    // Re-entering at once would let the holder barge; wait until a waiter has the lock.
    long giveUp = released + TAKE_TIMEOUT_NANOS;
    while (releaseStamp != 0 && System.nanoTime() < giveUp) {
      // spin
    }
    synchronized (lock) {
      long now = System.nanoTime();
      if (measuring && releaseStamp == 0 && takenBlocked) {
        int index = stored.get();
        if (index < MAX_SAMPLES) {
          holderWaits[index] = now - released;
          stored.set(index + 1);
        }
      }
    }
  }

  /** Reports the means and checks emission as {@code config} implies. */
  @TearDown(Level.Trial)
  public void tearDown(BenchmarkParams params) throws Exception {
    running = false;
    for (Thread thread : threads) {
      thread.join(TimeUnit.SECONDS.toMillis(5));
      check(!thread.isAlive(), "Contender did not stop");
    }
    if (recording.taskBlockActive()) {
      profiler.clearTraceContext();
    }
    String benchmark = TaskBlockBenchmarkSupport.benchmarkName(params);
    Map<String, Long> deltas = recording.stop(benchmark);
    long count = handoffs.get();
    long[] samples = Arrays.copyOf(holderWaits, stored.get());
    Arrays.sort(samples);
    System.out.printf(
        Locale.ROOT,
        "[taskblock-bench] contended benchmark=%s config=%s waiters=%d holds=%d handoffs=%d"
            + " handoffUs=%.1f holderWaitSamples=%d holderWaitP50Us=%.1f holderWaitMeanUs=%.1f%n",
        benchmark,
        config,
        waiters,
        holds.get(),
        count,
        count == 0 ? Double.NaN : handoffNanos.get() / 1e3 / count,
        samples.length,
        samples.length == 0 ? Double.NaN : samples[(samples.length - 1) / 2] / 1e3,
        samples.length == 0 ? Double.NaN : Arrays.stream(samples).average().getAsDouble() / 1e3);
    check(failure.get() == null, "Contender failed: " + failure.get());
    check(holds.get() > 0, benchmark + " made no holds");
    if (TaskBlockBenchmarkSupport.NONE.equals(config)) {
      return;
    }
    long emitted = delta(deltas, EMITTED);
    if (!recording.taskBlockActive()) {
      check(emitted == 0, benchmark + " emitted TaskBlock events with TaskBlock off");
      return;
    }
    // A blocked waiter emits one event per hold at most; with several waiters each may emit.
    checkBetween("emitted", emitted, holds.get() / 2, holds.get() * waiters + SLACK);
  }
}
