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
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Maintains 4 scheduled thread pools that cross-submit tasks to simulate
 * I/O-callback fan-out from Netty/gRPC event loops. Every 5 s one pool is
 * torn down and recreated — a burst of thread-end events while in-flight
 * tasks are running on sibling pools.
 *
 * <p>Targets: signal-vs-thread-end race during pool shutdown; JVMTI stack
 * walk on executor threads being torn down while the scheduler ticks.
 */
public final class BoundedThreadPoolAntagonist implements Antagonist {

    private static final int POOL_COUNT = 4;
    private static final int POOL_SIZE = 4;
    private static final long TASK_PERIOD_MS = 50L;
    private static final long RECYCLE_INTERVAL_MS = 5_000L;

    private final ScheduledExecutorService[] pools = new ScheduledExecutorService[POOL_COUNT];
    private volatile boolean running;
    private Thread recycler;
    private final AtomicLong sink = new AtomicLong();

    @Override
    public String name() {
        return "bounded-pool";
    }

    @Override
    public void start() {
        running = true;
        for (int i = 0; i < POOL_COUNT; i++) {
            pools[i] = newPool(i);
        }
        for (int i = 0; i < POOL_COUNT; i++) {
            schedulePoolTasks(i);
        }
        recycler = new Thread(this::recycleLoop, "chaos-bounded-pool-recycler");
        recycler.setDaemon(true);
        recycler.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        recycler.interrupt();
        try {
            recycler.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        for (ScheduledExecutorService pool : pools) {
            if (pool != null) {
                pool.shutdownNow();
            }
        }
    }

    private ScheduledExecutorService newPool(final int index) {
        ScheduledThreadPoolExecutor pool = new ScheduledThreadPoolExecutor(
                POOL_SIZE,
                new ThreadFactory() {
                    @Override
                    public Thread newThread(Runnable r) {
                        Thread t = new Thread(r, "chaos-bounded-pool-" + index);
                        t.setDaemon(true);
                        return t;
                    }
                });
        pool.setRemoveOnCancelPolicy(true);
        return pool;
    }

    private void schedulePoolTasks(final int poolIdx) {
        ScheduledExecutorService pool = pools[poolIdx];
        final int nextIdx = (poolIdx + 1) % POOL_COUNT;
        pool.scheduleAtFixedRate(
                new Runnable() {
                    @Override
                    public void run() {
                        if (!running) return;
                        long seed = System.nanoTime();
                        sink.addAndGet(burn(seed));
                        ScheduledExecutorService sibling = pools[nextIdx];
                        if (sibling != null && !sibling.isShutdown()) {
                            try {
                                final long s = seed;
                                sibling.submit(new Runnable() {
                                    @Override
                                    public void run() {
                                        sink.addAndGet(burn(s ^ 0xdeadbeefL));
                                    }
                                });
                            } catch (RejectedExecutionException ignored) {
                                // sibling shut down concurrently
                            }
                        }
                    }
                },
                TASK_PERIOD_MS, TASK_PERIOD_MS, TimeUnit.MILLISECONDS);
    }

    private void recycleLoop() {
        int victim = 0;
        while (running) {
            try {
                Thread.sleep(RECYCLE_INTERVAL_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
            if (!running) return;
            ScheduledExecutorService old = pools[victim];
            pools[victim] = null;
            if (old != null) {
                old.shutdownNow();
            }
            ScheduledExecutorService fresh = newPool(victim);
            pools[victim] = fresh;
            schedulePoolTasks(victim);
            victim = (victim + 1) % POOL_COUNT;
        }
    }

    private static long burn(long seed) {
        long r = seed;
        for (int i = 0; i < 500; i++) {
            r = r * 6364136223846793005L + 1442695040888963407L;
        }
        return r;
    }
}
