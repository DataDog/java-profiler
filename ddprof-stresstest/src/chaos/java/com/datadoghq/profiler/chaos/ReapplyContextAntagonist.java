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

import com.datadoghq.profiler.ContextSetter;
import com.datadoghq.profiler.JavaProfiler;
import java.nio.charset.StandardCharsets;
import java.time.Duration;
import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Drives the reapply-by-id-and-bytes hot path continuously from multiple threads while the
 * profiler's wall-clock signal fires, racing the {@code detach}/{@code attach} window.
 *
 * <p>Each worker thread loops: span-activate (wiping slots) → reapply snapshot. This mirrors
 * dd-trace-java's {@code reapplyAppContext} pattern and exercises the single-window invariant
 * (no partial publish visible to a signal handler) under high thread count and signal pressure.
 *
 * <p>The only failure signal is a JVM crash or a reapply returning {@code false}, which throws
 * {@link IllegalStateException} since the record is always valid immediately after
 * {@code setContext}.
 */
public final class ReapplyContextAntagonist implements Antagonist {

    private static final String[] ATTR_NAMES = {
        "http.route", "http.method", "http.status", "db.operation", "rpc.service"
    };

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
    }

    private void workerLoop() {
        JavaProfiler profiler;
        try {
            profiler = JavaProfiler.getInstance();
        } catch (Exception e) {
            System.err.println("[chaos] reapply-context: failed to get profiler: " + e);
            return;
        }
        ContextSetter contextSetter = new ContextSetter(profiler, Arrays.asList(ATTR_NAMES));

        // Prime the per-thread encoding cache and capture a stable snapshot.
        long spanId = Thread.currentThread().getId() + 1;
        long localRootSpanId = spanId * 31L;
        long traceIdLow = spanId * 6364136223846793005L + 1442695040888963407L;
        profiler.setContext(localRootSpanId, spanId, 0, traceIdLow);
        for (int i = 0; i < ROUTES.length; i++) {
            contextSetter.setContextValue(i, ROUTES[i]);
        }
        int[] constantIds = contextSetter.snapshotTags();
        byte[][] utf8 = new byte[ROUTES.length][];
        for (int i = 0; i < ROUTES.length; i++) {
            utf8[i] = ROUTES[i].getBytes(StandardCharsets.UTF_8);
        }

        while (running) {
            // Span activation wipes all custom slots.
            profiler.setContext(localRootSpanId, spanId, 0, traceIdLow);
            // Reapply restores them — this is the hot path under test.
            if (!contextSetter.setContextValuesByIdAndBytes(constantIds, utf8)) {
                throw new IllegalStateException("reapply failed unexpectedly — record should be valid after setContext");
            }
        }
    }
}
