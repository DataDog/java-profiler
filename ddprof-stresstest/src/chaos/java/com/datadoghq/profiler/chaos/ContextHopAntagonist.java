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
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Chains {@link CompletableFuture} stages across three distinct thread pools
 * (A→B→C→A). Each stage sets a {@link ThreadLocal} to a random value, burns
 * briefly, then clears it before submitting the next stage.
 *
 * <p>Eight self-renewing chains run concurrently.
 *
 * <p>Targets: RefCountGuard slot contention racing cross-pool handoff;
 * wall-clock signal hitting a thread between ThreadLocal set and remove.
 */
public final class ContextHopAntagonist implements Antagonist {

    private static final int CHAIN_COUNT = 8;
    private static final ThreadLocal<Long> CONTEXT = new ThreadLocal<Long>();

    private final ExecutorService poolA;
    private final ExecutorService poolB;
    private final ExecutorService poolC;
    private volatile boolean running;
    private final AtomicLong sink = new AtomicLong();

    public ContextHopAntagonist() {
        poolA = newPool("A");
        poolB = newPool("B");
        poolC = newPool("C");
    }

    @Override
    public String name() {
        return "context-hop";
    }

    @Override
    public void start() {
        running = true;
        for (int i = 0; i < CHAIN_COUNT; i++) {
            startChain(i);
        }
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        poolA.shutdown();
        poolB.shutdown();
        poolC.shutdown();
        long slice = timeout.toMillis() / 3;
        try {
            poolA.awaitTermination(slice, TimeUnit.MILLISECONDS);
            poolB.awaitTermination(slice, TimeUnit.MILLISECONDS);
            poolC.awaitTermination(slice, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void startChain(final int chainId) {
        if (!running) return;
        MemoryGovernor.pace();
        final long seed = ThreadLocalRandom.current().nextLong() ^ ((long) chainId << 32);
        CompletableFuture
                .runAsync(new Runnable() {
                    @Override public void run() { hop(seed); }
                }, poolA)
                .thenRunAsync(new Runnable() {
                    @Override public void run() { hop(seed * 2L); }
                }, poolB)
                .thenRunAsync(new Runnable() {
                    @Override public void run() { hop(seed * 3L); }
                }, poolC)
                .thenRunAsync(new Runnable() {
                    @Override public void run() { startChain(chainId); }
                }, poolA)
                .exceptionally(t -> null);
    }

    private void hop(long value) {
        CONTEXT.set(value);
        try {
            long r = value;
            for (int i = 0; i < 200; i++) {
                r = r * 1103515245L + 12345L;
            }
            sink.addAndGet(r);
        } finally {
            CONTEXT.remove();
        }
    }

    private static ExecutorService newPool(final String label) {
        return Executors.newFixedThreadPool(4, new ThreadFactory() {
            @Override
            public Thread newThread(Runnable r) {
                Thread t = new Thread(r, "chaos-context-hop-" + label);
                t.setDaemon(true);
                return t;
            }
        });
    }
}
