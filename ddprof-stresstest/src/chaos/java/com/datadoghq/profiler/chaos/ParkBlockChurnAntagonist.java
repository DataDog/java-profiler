/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.chaos;

import com.datadoghq.profiler.JavaProfiler;
import java.lang.invoke.MethodHandle;
import java.lang.invoke.MethodHandles;
import java.lang.reflect.Method;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;

/**
 * Continuously spawns short-lived threads that block (Thread.sleep,
 * LockSupport.parkNanos, Object.wait, contended synchronized) and then die,
 * some interrupted mid-block. Sleep and park calls explicitly invoke the profiler's
 * package-scoped hooks through bound method handles, independently of tracer instrumentation.
 * Object.wait and monitor contention remain unowned blocking observations.
 *
 * <p>Targets: registry slot reuse racing an in-flight blocked-run generation
 * token (ThreadFilter::registerThread/unregisterThread vs.
 * WallClockBlockTracker::enterBlockedRun/exitBlockedRun), and timer lookups racing
 * teardown and slot reuse. Use the {@code testOwnedBlockPrecheck} Gradle task to require actual
 * unfiltered registry lookups and signal suppression, rather than just hook calls.
 */
public final class ParkBlockChurnAntagonist implements Antagonist {

    /** A worker still alive after this long is reported as stalled rather than abandoned. */
    private static final long STALL_TIMEOUT_MILLIS = 30_000L;

    private final int concurrentThreads;
    private final int blockMillis;

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong totalBlocks = new AtomicLong();
    private final AtomicLong armedSleepingRuns = new AtomicLong();
    private final AtomicLong parkCalls = new AtomicLong();
    private final AtomicReference<Throwable> failure = new AtomicReference<>();
    private final Object monitor = new Object();
    private JavaProfiler profiler;
    private MethodHandle blockEnter;
    private MethodHandle blockExit;
    private MethodHandle parkEnter;
    private MethodHandle parkExit;
    private Map<String, Long> countersBefore;
    /** Single scheduler for mid-block interrupts; the driver is its sole submitter. */
    private ScheduledExecutorService interruptor;

    /** Creates the default batch of short-lived blocking workers. */
    public ParkBlockChurnAntagonist() {
        this(48, 3);
    }

    /** Creates a blocking workload with the requested batch size and block duration. */
    public ParkBlockChurnAntagonist(int concurrentThreads, int blockMillis) {
        this.concurrentThreads = concurrentThreads;
        this.blockMillis = blockMillis;
    }

    @Override
    public String name() {
        return "park-block-churn";
    }

    /** Resolves the real profiler hooks before starting any background workers. */
    @Override
    public void start() {
        try {
            profiler = JavaProfiler.getInstance();
            blockEnter = bindHook("blockEnter", int.class);
            blockExit = bindHook("blockExit", long.class);
            parkEnter = bindHook("parkEnter");
            parkExit = bindHook("parkExit", long.class, long.class);
        } catch (Exception e) {
            throw new IllegalStateException("Cannot bind profiler owned-block hooks", e);
        }
        countersBefore = profiler.getDebugCounters();
        interruptor = Executors.newSingleThreadScheduledExecutor(r -> {
            Thread t = new Thread(r, "chaos-park-block-churn-interruptor");
            t.setDaemon(true);
            return t;
        });
        running = true;
        driver = new Thread(() -> {
            try {
                loop();
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
                running = false;
            } finally {
                interruptor.shutdownNow();
            }
        }, "chaos-park-block-churn");
        driver.setDaemon(true);
        driver.start();
    }

    /** Stops the workload and propagates background hook failures to the harness. */
    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            driver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new IllegalStateException("Interrupted stopping park-block-churn", e);
        }
        if (driver.isAlive()) throw new IllegalStateException("park-block-churn did not stop");
        if (failure.get() != null) throw new IllegalStateException("Owned-block worker failed", failure.get());
        System.out.println("[chaos] park-block-churn completed=" + totalBlocks.get()
                + " armed_sleeps=" + armedSleepingRuns.get() + " park_calls=" + parkCalls.get()
                + " suppressed=" + counterDelta("wc_signals_suppressed_sampled_run"));
    }

    /** Requires native hooks, unfiltered timer lookups, and timer-side suppression to run. */
    public void verifyPrecheckCoverage() {
        if (armedSleepingRuns.get() == 0 || parkCalls.get() == 0) {
            throw new IllegalStateException("Owned sleep and park hooks did not both run");
        }
        for (String counter : new String[] {
                "wc_precheck_registry_lookups", "wc_precheck_candidates_rejected",
                "wc_signals_suppressed_sampled_run"}) {
            long delta = counterDelta(counter);
            if (delta <= 0) {
                throw new IllegalStateException("No precheck coverage for " + counter
                        + " (delta=" + delta + "); use a COUNTERS-enabled native build");
            }
        }
    }

    /** Resolves hooks on JavaProfiler's runtime class, including the injected agent's loader. */
    private MethodHandle bindHook(String name, Class<?>... parameterTypes) throws ReflectiveOperationException {
        Method method = JavaProfiler.class.getDeclaredMethod(name, parameterTypes);
        method.setAccessible(true);
        return MethodHandles.lookup().unreflect(method).bindTo(profiler);
    }

    private long counterDelta(String name) {
        long before = countersBefore.getOrDefault(name, -1L);
        long after = profiler.getDebugCounters().getOrDefault(name, -1L);
        return before < 0 || after < 0 ? -1 : after - before;
    }

    private void loop() {
        int round = 0;
        while (running) {
            List<Thread> batch = new ArrayList<>(concurrentThreads);
            for (int i = 0; i < concurrentThreads && running; i++) {
                final int mode = (round + i) % 4;
                Thread t = new Thread(() -> block(mode));
                t.setDaemon(true);
                t.start();
                batch.add(t);
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

    /**
     * Joins every worker of {@code batch} before the next batch is spawned, so at most one batch
     * is alive at any time. A worker still alive after {@link #STALL_TIMEOUT_MILLIS} is recorded
     * as a failure and stops the workload instead of being stacked under new batches.
     *
     * @return true when the whole batch exited; false when the loop must stop
     */
    private boolean awaitBatch(List<Thread> batch) {
        long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(STALL_TIMEOUT_MILLIS);
        for (Thread t : batch) {
            try {
                while (t.isAlive()) {
                    t.join(1_000L);
                    if (!running) {
                        return false;
                    }
                    if (t.isAlive() && System.nanoTime() - deadline > 0) {
                        failure.compareAndSet(null, new IllegalStateException(
                                "park/block worker stalled: " + t.getName() + " state=" + t.getState()));
                        running = false;
                        return false;
                    }
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return false;
            }
        }
        return true;
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
                    // Contend the same monitor from many concurrent threads so
                    // some entrants queue up on MONITOR_WAIT rather than the
                    // OBJECT_WAIT path exercised by case 2.
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
