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
import com.datadoghq.profiler.ThreadContext;
import java.nio.charset.StandardCharsets;
import java.time.Duration;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Drives the reapply-by-id-and-bytes hot path continuously from multiple threads while the
 * profiler's wall-clock signal fires, racing the {@code detach}/{@code attach} window.
 *
 * <p>Each worker thread loops: span-activate (wiping slots) → reapply snapshot. This mirrors
 * dd-trace-java's {@code reapplyAppContext} pattern and exercises the single-window invariant
 * (no partial publish visible to a signal handler) under high thread count and signal pressure.
 *
 * <p>The only failure signal is a JVM crash or a reapply returning {@code false} while the record
 * is active — the latter is logged and counted but does not abort the run (false positives from
 * genuine attrs_data overflow are possible with many threads).
 */
public final class ReapplyContextAntagonist implements Antagonist {

    private static final String[] ROUTES = {
        "GET /api/users",
        "POST /api/orders",
        "GET /api/health",
        "PUT /api/users/{id}",
        "DELETE /api/sessions"
    };

    private final int workerCount;
    private final ExecutorService pool;
    private volatile boolean running;
    private final AtomicLong sink = new AtomicLong();
    private final AtomicLong reapplyFailures = new AtomicLong();

    public ReapplyContextAntagonist() {
        this(8);
    }

    public ReapplyContextAntagonist(int workerCount) {
        this.workerCount = workerCount;
        this.pool =
                Executors.newFixedThreadPool(
                        workerCount,
                        r -> {
                            Thread t = new Thread(r, "chaos-reapply-context");
                            t.setDaemon(true);
                            return t;
                        });
    }

    @Override
    public String name() {
        return "reapply-context";
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
        long failures = reapplyFailures.get();
        if (failures > 0) {
            System.out.println(
                    "[chaos] reapply-context: " + failures + " unexpected reapply failures");
        }
    }

    private void workerLoop() {
        JavaProfiler profiler;
        try {
            profiler = JavaProfiler.getInstance();
        } catch (Exception e) {
            System.err.println("[chaos] reapply-context: failed to get profiler: " + e);
            return;
        }
        ThreadContext ctx = profiler.getThreadContext();

        // Prime the per-thread encoding cache and capture a stable snapshot.
        long spanId = Thread.currentThread().getId() + 1;
        long localRootSpanId = spanId * 31L;
        ctx.put(localRootSpanId, spanId, 0, spanId);
        for (int i = 0; i < ROUTES.length; i++) {
            ctx.setContextAttribute(i, ROUTES[i]);
        }
        int[] constantIds = new int[10];
        ctx.copyCustoms(constantIds);
        byte[][] utf8 = new byte[10][];
        for (int i = 0; i < ROUTES.length; i++) {
            utf8[i] = ROUTES[i].getBytes(StandardCharsets.UTF_8);
        }

        long r = spanId;
        while (running) {
            // Span activation wipes all custom slots.
            ctx.put(localRootSpanId, spanId, 0, spanId);
            // Reapply restores them — this is the hot path under test.
            if (!ctx.setContextAttributesByIdAndBytes(constantIds, utf8)) {
                reapplyFailures.incrementAndGet();
            }
            // Burn a little CPU so wall-clock signals have something to sample.
            r = r * 1103515245L + 12345L;
            sink.addAndGet(r);
        }
    }
}
