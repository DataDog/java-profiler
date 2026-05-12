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

/**
 * Continuously spawns batches of short-lived threads that race signal delivery,
 * stack walking, and RefCountGuard slot allocation/release.
 *
 * <p>Targets: signal-vs-teardown races in the wall/cpu engines, slot reuse under
 * contention, calltrace storage put() racing thread destruction.
 */
public final class ThreadChurnAntagonist implements Antagonist {

    private final int concurrentThreads;
    private final int threadLifetimeMillis;

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong totalWork = new AtomicLong();

    public ThreadChurnAntagonist() {
        this(64, 5);
    }

    public ThreadChurnAntagonist(int concurrentThreads, int threadLifetimeMillis) {
        this.concurrentThreads = concurrentThreads;
        this.threadLifetimeMillis = threadLifetimeMillis;
    }

    @Override
    public String name() {
        return "thread-churn";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-thread-churn");
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
        while (running) {
            List<Thread> batch = new ArrayList<>(concurrentThreads);
            for (int i = 0; i < concurrentThreads && running; i++) {
                final long seed = System.nanoTime() + i;
                Thread t = new Thread(() -> totalWork.addAndGet(burn(seed)));
                t.setDaemon(true);
                t.start();
                batch.add(t);
            }
            for (Thread t : batch) {
                try {
                    t.join(1_000L);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
        }
    }

    private long burn(long seed) {
        long endNanos = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(threadLifetimeMillis);
        long r = seed;
        while (System.nanoTime() < endNanos) {
            for (int i = 0; i < 1000; i++) {
                r = (r * 1103515245L + 12345L) & 0x7fffffffL;
            }
        }
        return r;
    }
}
