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

import java.lang.invoke.MethodHandle;
import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
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

    private final int concurrentThreads;
    private final int blockMillis;

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong totalBlocks = new AtomicLong();
    private final AtomicLong armedSleepingRuns = new AtomicLong();
    private final AtomicLong parkCalls = new AtomicLong();
    private final AtomicReference<Throwable> failure = new AtomicReference<>();
    private final Object monitor = new Object();
    private MethodHandle getDebugCounters;
    private MethodHandle blockEnter;
    private MethodHandle blockExit;
    private MethodHandle parkEnter;
    private MethodHandle parkExit;
    private Map<String, Long> countersBefore;

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
            Object profiler = ProfilerAccess.getInstance();
            blockEnter = ProfilerAccess.bind(profiler, "blockEnter", int.class);
            blockExit = ProfilerAccess.bind(profiler, "blockExit", long.class, long.class, long.class);
            parkEnter = ProfilerAccess.bind(profiler, "parkEnter");
            parkExit = ProfilerAccess.bind(profiler, "parkExit", long.class, long.class);
            getDebugCounters = ProfilerAccess.bind(profiler, "getDebugCounters");
        } catch (Exception e) {
            throw new IllegalStateException("Cannot bind profiler owned-block hooks", e);
        }
        countersBefore = debugCounters();
        running = true;
        driver = new Thread(() -> {
            try {
                loop();
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
                running = false;
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
                + " suppressed=" + counterDelta("wc_signals_suppressed_owned_block"));
    }

    /** Requires native hooks, unfiltered timer lookups, and timer-side suppression to run. */
    public void verifyPrecheckCoverage() {
        if (armedSleepingRuns.get() == 0 || parkCalls.get() == 0) {
            throw new IllegalStateException("Owned sleep and park hooks did not both run");
        }
        for (String counter : new String[] {
                "wc_precheck_registry_lookups", "wc_precheck_candidates_rejected",
                "wc_signals_suppressed_owned_block"}) {
            long delta = counterDelta(counter);
            if (delta <= 0) {
                throw new IllegalStateException("No precheck coverage for " + counter
                        + " (delta=" + delta + "); use a COUNTERS-enabled native build");
            }
        }
    }

    /** Reads counters from the same profiler instance as the owned-block hooks. */
    @SuppressWarnings("unchecked")
    private Map<String, Long> debugCounters() {
        try {
            return (Map<String, Long>) getDebugCounters.invokeExact();
        } catch (Throwable t) {
            throw new IllegalStateException("Cannot read profiler counters", t);
        }
    }

    private long counterDelta(String name) {
        long before = countersBefore.getOrDefault(name, -1L);
        long after = debugCounters().getOrDefault(name, -1L);
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
            for (Thread t : batch) {
                try {
                    t.join(1_000L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            round++;
        }
    }

    /** Wakes {@code t} mid-block so its exit hook races against interruption. */
    private void interruptShortly(Thread t) {
        Thread interruptor = new Thread(() -> {
            try {
                Thread.sleep(1L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
            t.interrupt();
        });
        interruptor.setDaemon(true);
        interruptor.start();
    }

    private void block(int mode) {
        try {
            switch (mode) {
                case 0:
                    sleepOwned(blockMillis);
                    break;
                case 1:
                    boolean ownsPark = (boolean) parkEnter.invokeExact();
                    parkCalls.incrementAndGet();
                    try {
                        LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(blockMillis));
                    } finally {
                        if (ownsPark) parkExit.invokeExact(0L, 0L);
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
            blockExit.invokeExact(token, 0L, 0L);
        }
    }
}
