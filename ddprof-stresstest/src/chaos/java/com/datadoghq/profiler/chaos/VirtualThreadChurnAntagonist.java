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

import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Spawns short-lived virtual threads at high rate to exercise mount/unmount on
 * carrier threads and {@code ProfiledThread} recycling racing signal delivery.
 *
 * <p>Reflectively detects {@code Thread.ofVirtual()} (Java 21+); gracefully
 * no-ops on older runtimes.
 */
public final class VirtualThreadChurnAntagonist implements Antagonist {

    private static final Method OF_VIRTUAL = resolveOfVirtual();
    private static final Method BUILDER_START = resolveBuilderStart();

    private final int batchSize;

    private volatile boolean running;
    private Thread driver;
    private final AtomicLong sink = new AtomicLong();

    public VirtualThreadChurnAntagonist() {
        this(256);
    }

    public VirtualThreadChurnAntagonist(int batchSize) {
        this.batchSize = batchSize;
    }

    @Override
    public String name() {
        return "vthread-churn";
    }

    @Override
    public void start() {
        running = true;
        driver = new Thread(this::loop, "chaos-vthread-churn");
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
        if (OF_VIRTUAL == null || BUILDER_START == null) {
            System.out.println("[chaos] vthread-churn: skipping (Thread.ofVirtual not available)");
            return;
        }
        while (running) {
            for (int i = 0; i < batchSize && running; i++) {
                final long seed = System.nanoTime() ^ i;
                try {
                    Object builder = OF_VIRTUAL.invoke(null);
                    BUILDER_START.invoke(builder, (Runnable) () -> sink.addAndGet(burn(seed)));
                } catch (Throwable t) {
                    return;
                }
            }
            // Yield briefly so the scheduler can drain mounts before the next batch.
            try {
                Thread.sleep(1L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    private static long burn(long seed) {
        long r = seed;
        for (int i = 0; i < 10_000; i++) {
            r = r * 6364136223846793005L + 1442695040888963407L;
        }
        // A yield raises the chance of unmount/remount on a different carrier.
        Thread.yield();
        return r;
    }

    private static Method resolveOfVirtual() {
        try {
            return Thread.class.getMethod("ofVirtual");
        } catch (NoSuchMethodException e) {
            return null;
        }
    }

    private static Method resolveBuilderStart() {
        try {
            Class<?> builder = Class.forName("java.lang.Thread$Builder");
            return builder.getMethod("start", Runnable.class);
        } catch (ClassNotFoundException | NoSuchMethodException e) {
            return null;
        }
    }
}
