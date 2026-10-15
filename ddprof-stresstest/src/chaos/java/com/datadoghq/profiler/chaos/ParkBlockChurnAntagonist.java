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

import java.time.Duration;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.LockSupport;

/**
 * Continuously spawns short-lived threads that block (Thread.sleep,
 * LockSupport.parkNanos, Object.wait, contended synchronized) and then die,
 * some interrupted mid-block. dd-trace-java's instrumentation of these calls
 * drives the native park/block JNI hooks (JavaProfiler#parkEnter/#parkExit/
 * #blockEnter/#blockExit), which none of the other antagonists exercise.
 *
 * <p>Targets: registry slot reuse racing an in-flight blocked-run generation
 * token (ThreadFilter::registerThread/unregisterThread vs.
 * WallClockBlockTracker::enterBlockedRun/exitBlockedRun), block-exit running
 * after JVMTI ThreadEnd has already reclaimed the slot, and interrupted
 * parks (early/EINTR-style wakeups) racing the same exit path.
 */
public final class ParkBlockChurnAntagonist implements Antagonist {

    private final int concurrentThreads;
    private final int blockMillis;

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong totalBlocks = new AtomicLong();
    private final Object monitor = new Object();

    public ParkBlockChurnAntagonist() {
        this(48, 3);
    }

    public ParkBlockChurnAntagonist(int concurrentThreads, int blockMillis) {
        this.concurrentThreads = concurrentThreads;
        this.blockMillis = blockMillis;
    }

    @Override
    public String name() {
        return "park-block-churn";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-park-block-churn");
        driver.setDaemon(true);
        driver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            driver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
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
                    Thread.sleep(blockMillis);
                    break;
                case 1:
                    LockSupport.parkNanos(TimeUnit.MILLISECONDS.toNanos(blockMillis));
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
                        Thread.sleep(1L);
                    }
                    break;
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        totalBlocks.incrementAndGet();
    }
}
