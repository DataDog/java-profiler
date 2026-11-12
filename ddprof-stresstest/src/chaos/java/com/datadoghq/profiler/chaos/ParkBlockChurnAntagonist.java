/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;

/**
 * Races short-lived blocking owners against registry retirement and slot reuse; sleep and park
 * invoke native hooks explicitly, while waits and monitor contention remain unowned observations.
 */
public final class ParkBlockChurnAntagonist implements Antagonist {

  /** A worker still alive after this long is reported as stalled rather than abandoned. */
  private static final long STALL_TIMEOUT_MILLIS = 30_000L;

  private final int concurrentThreads;
  private final int blockMillis;
  private final ThreadFactory workerThreadFactory;

  private volatile boolean running;
  private Thread driver;
  private List<Thread> activeBatch = Collections.emptyList();
  private final AtomicLong totalBlocks = new AtomicLong();
  private final AtomicLong armedSleepingRuns = new AtomicLong();
  private final AtomicLong parkCalls = new AtomicLong();
  private final AtomicReference<Throwable> failure = new AtomicReference<>();
  private final Object monitor = new Object();
  private Object profiler;
  private Method debugCounters;
  private MethodHandle blockEnter;
  private MethodHandle blockExit;
  private MethodHandle parkEnter;
  private MethodHandle parkExit;
  private Map<String, Long> countersBefore;

  /** Single scheduler for mid-block interrupts; the driver is its sole submitter. */
  private ScheduledExecutorService interruptor;

  private Thread interruptorThread;

  /** Creates the default batch of short-lived blocking workers. */
  public ParkBlockChurnAntagonist() {
    this(48, 3);
  }

  /** Creates a blocking workload with the requested batch size and block duration. */
  public ParkBlockChurnAntagonist(int concurrentThreads, int blockMillis) {
    this(concurrentThreads, blockMillis, Thread::new);
  }

  /** Allows tests to gate real workers without replacing the driver or hook calls. */
  ParkBlockChurnAntagonist(
      int concurrentThreads, int blockMillis, ThreadFactory workerThreadFactory) {
    this.concurrentThreads = concurrentThreads;
    this.blockMillis = blockMillis;
    this.workerThreadFactory = workerThreadFactory;
  }

  @Override
  public String name() {
    return "park-block-churn";
  }

  /** Resolves the real profiler hooks before starting any background workers. */
  @Override
  public void start() {
    try {
      Class<?> profilerClass = resolveProfilerClass();
      profiler = profilerClass.getMethod("getInstance").invoke(null);
      debugCounters = profilerClass.getMethod("getDebugCounters");
      blockEnter = bindHook("blockEnter", int.class);
      blockExit = bindHook("blockExit", long.class);
      parkEnter = bindHook("parkEnter");
      parkExit = bindHook("parkExit", long.class, long.class);
    } catch (Exception e) {
      throw new IllegalStateException("Cannot bind profiler owned-block hooks", e);
    }
    countersBefore = readCounters();
    interruptor =
        Executors.newSingleThreadScheduledExecutor(
            r -> {
              Thread t = new Thread(r, "chaos-park-block-churn-interruptor");
              interruptorThread = t;
              t.setDaemon(true);
              return t;
            });
    running = true;
    driver =
        new Thread(
            () -> {
              try {
                loop();
              } catch (Throwable t) {
                failure.compareAndSet(null, t);
                running = false;
              } finally {
                interruptor.shutdownNow();
              }
            },
            "chaos-park-block-churn");
    driver.setDaemon(true);
    driver.start();
  }

  /** Waits within one budget for owned threads, reporting incomplete or failed cleanup. */
  @Override
  public void stopGracefully(Duration timeout) {
    long deadline = System.nanoTime() + timeout.toNanos();
    running = false;
    try {
      joinUntil(driver, deadline);
      if (driver.isAlive()) {
        throw new IllegalStateException("park-block-churn driver did not stop", failure.get());
      }
      boolean terminated =
          interruptor.awaitTermination(
              Math.max(0L, deadline - System.nanoTime()), TimeUnit.NANOSECONDS);
      if (interruptorThread != null) joinUntil(interruptorThread, deadline);
      if (!terminated || (interruptorThread != null && interruptorThread.isAlive())) {
        throw new IllegalStateException("park-block-churn interruptor did not stop", failure.get());
      }
    } catch (InterruptedException e) {
      failure.compareAndSet(null, e);
      Thread.currentThread().interrupt();
      throw new IllegalStateException("Interrupted stopping park-block-churn", e);
    }
    // The terminated driver has finished publishing this batch, including on exceptional exit.
    for (Thread worker : activeBatch) {
      if (worker.isAlive()) {
        throw new IllegalStateException(
            "Unreaped park/block worker: " + worker.getName(), failure.get());
      }
    }
    if (failure.get() != null)
      throw new IllegalStateException("Owned-block worker failed", failure.get());
    System.out.println(
        "[chaos] park-block-churn completed="
            + totalBlocks.get()
            + " armed_sleeps="
            + armedSleepingRuns.get()
            + " park_calls="
            + parkCalls.get()
            + " suppressed="
            + counterDelta("wc_signals_suppressed_sampled_run"));
  }

  /** Requires native hooks, unfiltered timer lookups, and timer-side suppression to run. */
  public void verifyPrecheckCoverage() {
    if (armedSleepingRuns.get() == 0 || parkCalls.get() == 0) {
      throw new IllegalStateException("Owned sleep and park hooks did not both run");
    }
    for (String counter :
        new String[] {
          "wc_precheck_registry_lookups",
          "wc_precheck_candidates_rejected",
          "wc_signals_suppressed_sampled_run"
        }) {
      long delta = counterDelta(counter);
      if (delta <= 0) {
        throw new IllegalStateException(
            "No precheck coverage for "
                + counter
                + " (delta="
                + delta
                + "); use a COUNTERS-enabled native build");
      }
    }
  }

  /** Agent shared classdata is invisible to the application's class loader. */
  private Class<?> resolveProfilerClass() throws ReflectiveOperationException {
    ClassLoader loader = getClass().getClassLoader();
    try {
      Class<?> agent = Class.forName("datadog.trace.bootstrap.Agent", false, loader);
      Field field = agent.getDeclaredField("AGENT_CLASSLOADER");
      field.setAccessible(true);
      loader = (ClassLoader) field.get(null);
    } catch (ClassNotFoundException standalone) {
      // Standalone native tests have no agent and expose the profiler on their own classpath.
    }
    return Class.forName("com.datadoghq.profiler.JavaProfiler", true, loader);
  }

  /** Binds hooks to the same private-loader instance that owns the native recording. */
  private MethodHandle bindHook(String name, Class<?>... parameterTypes)
      throws ReflectiveOperationException {
    Method method = profiler.getClass().getDeclaredMethod(name, parameterTypes);
    method.setAccessible(true);
    return MethodHandles.lookup().unreflect(method).bindTo(profiler);
  }

  @SuppressWarnings("unchecked")
  private Map<String, Long> readCounters() {
    try {
      return (Map<String, Long>) debugCounters.invoke(profiler);
    } catch (ReflectiveOperationException e) {
      throw new IllegalStateException("Cannot read profiler debug counters", e);
    }
  }

  private long counterDelta(String name) {
    long before = countersBefore.getOrDefault(name, -1L);
    long after = readCounters().getOrDefault(name, -1L);
    return before < 0 || after < 0 ? -1 : after - before;
  }

  private void loop() {
    int round = 0;
    while (running) {
      List<Thread> batch = new ArrayList<>(concurrentThreads);
      activeBatch = batch;
      for (int i = 0; i < concurrentThreads && running; i++) {
        final int mode = (round + i) % 4;
        Thread t = workerThreadFactory.newThread(() -> block(mode));
        t.setDaemon(true);
        batch.add(t);
        t.start();
        if ((i & 0x3) == 0) {
          interruptShortly(t);
        }
      }
      if (!awaitBatch(batch)) {
        return;
      }
      round++;
    }
  }

  /** True means drained and still running; exceptional false records a cleanup failure. */
  boolean awaitBatch(List<Thread> batch) {
    return awaitBatch(batch, TimeUnit.MILLISECONDS.toNanos(STALL_TIMEOUT_MILLIS));
  }

  /** Uses the production drain path with a shorter budget for deterministic timeout tests. */
  boolean awaitBatch(List<Thread> batch, long timeoutNanos) {
    long deadline = System.nanoTime() + timeoutNanos;
    for (Thread t : batch) {
      try {
        joinUntil(t, deadline);
      } catch (InterruptedException e) {
        failure.compareAndSet(null, e);
        running = false;
        Thread.currentThread().interrupt();
        return false;
      }
      if (t.isAlive()) {
        failure.compareAndSet(
            null,
            new IllegalStateException(
                "park/block worker stalled: " + t.getName() + " state=" + t.getState()));
        running = false;
        return false;
      }
    }
    return running && failure.get() == null;
  }

  /** Never rounds an expired or positive submillisecond budget into an indefinite join. */
  private static void joinUntil(Thread thread, long deadline) throws InterruptedException {
    while (thread.isAlive()) {
      long remaining = deadline - System.nanoTime();
      if (remaining <= 0) return;
      long waitNanos = Math.min(remaining, TimeUnit.SECONDS.toNanos(1));
      thread.join(
          TimeUnit.NANOSECONDS.toMillis(waitNanos),
          (int) (waitNanos % TimeUnit.MILLISECONDS.toNanos(1)));
    }
  }

  /** Wakes {@code t} mid-block so its exit hook races against interruption. */
  private void interruptShortly(Thread t) {
    interruptor.schedule(t::interrupt, 1L, TimeUnit.MILLISECONDS);
  }

  private void block(int mode) {
    try {
      switch (mode) {
        case 0:
          sleepOwned(blockMillis);
          break;
        case 1:
          parkEnter.invokeExact();
          parkCalls.incrementAndGet();
          try {
            LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(blockMillis));
          } finally {
            parkExit.invokeExact(0L, 0L);
          }
          break;
        case 2:
          synchronized (monitor) {
            monitor.wait(blockMillis);
          }
          break;
        default:
          // Contend the monitor rather than taking the Object.wait path of case 2.
          synchronized (monitor) {
            sleepOwned(1L);
          }
          break;
      }
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    } catch (Throwable t) {
      failure.compareAndSet(null, t);
      running = false;
    }
    totalBlocks.incrementAndGet();
  }

  /** Always closes the owned sleep interval, including interrupted sleeps. */
  private void sleepOwned(long millis) throws Throwable {
    long token = (long) blockEnter.invokeExact(7); // OSThreadState::SLEEPING
    if (token != 0) armedSleepingRuns.incrementAndGet();
    try {
      Thread.sleep(millis);
    } finally {
      blockExit.invokeExact(token);
    }
  }
}
