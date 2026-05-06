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

import datadog.trace.api.Trace;

import java.time.Duration;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Drives nested {@link Trace}-annotated invocations from a pool of worker
 * threads. Under a {@code dd-java-agent}-instrumented JVM the tracer drives
 * {@code JavaProfiler.setContext}/{@code clearContext} on every span
 * activation, so a high enter/exit rate stresses that path against signal
 * delivery and stack walking.
 *
 * <p>{@code dd-trace-api} is a {@code compileOnly} dependency — at runtime
 * the patched {@code dd-java-agent} provides the (relocated) classes and
 * intercepts the annotation.
 */
public final class TraceContextAntagonist implements Antagonist {

    private final int workerCount;
    private final ExecutorService pool;
    private volatile boolean running;
    private final AtomicLong sink = new AtomicLong();

    public TraceContextAntagonist() {
        this(8);
    }

    public TraceContextAntagonist(int workerCount) {
        this.workerCount = workerCount;
        this.pool = Executors.newFixedThreadPool(workerCount, r -> {
            Thread t = new Thread(r, "chaos-trace-context");
            t.setDaemon(true);
            return t;
        });
    }

    @Override
    public String name() {
        return "trace-context";
    }

    @Override
    public void start() {
        running = true;
        for (int i = 0; i < workerCount; i++) {
            pool.submit(this::workerLoop);
        }
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        pool.shutdown();
        try {
            pool.awaitTermination(timeout.toMillis(), TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void workerLoop() {
        long r = ThreadLocalRandom.current().nextLong();
        while (running) {
            r = outer(r);
        }
        sink.addAndGet(r);
    }

    @Trace(operationName = "chaos.outer", resourceName = "chaos.outer")
    private long outer(long seed) {
        long r = seed;
        for (int i = 0; i < 64; i++) {
            r = inner(r);
        }
        return r;
    }

    @Trace(operationName = "chaos.inner", resourceName = "chaos.inner")
    private long inner(long seed) {
        return seed * 1103515245L + 12345L;
    }
}
