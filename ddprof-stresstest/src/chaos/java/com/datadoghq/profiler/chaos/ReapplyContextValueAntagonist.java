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
import java.time.Duration;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

/**
 * Drives repeated per-slot {@code setContextValue}/{@code clearContextValue} calls continuously
 * from multiple threads, interleaved with {@code setTraceContext} span activations, while the
 * profiler's wall-clock signal fires — racing the all-native record's write/read window.
 *
 * <p>Each worker thread loops: activate a span (resetting custom slots), churn a handful of
 * attribute slots with set/clear calls, deactivate. Unlike the legacy DirectByteBuffer conduit
 * this antagonist's predecessor exercised, there is no cached per-thread buffer to go stale — the
 * only thing under test here is that concurrent single-slot native writes never produce a partial
 * or torn record visible to a signal handler.
 */
public final class ReapplyContextValueAntagonist implements Antagonist {

    private static final String[] ROUTES = {
        "GET /api/users",
        "POST /api/orders",
        "GET /api/health",
        "PUT /api/users/{id}",
        "DELETE /api/sessions"
    };

    private static final int SLOT_COUNT = 5;

    private final int workerCount;
    private final ExecutorService pool;
    private volatile boolean running;

    public ReapplyContextValueAntagonist() {
        this(8);
    }

    public ReapplyContextValueAntagonist(int workerCount) {
        this.workerCount = workerCount;
        this.pool =
                Executors.newFixedThreadPool(
                        workerCount,
                        r -> {
                            Thread t = new Thread(r, "chaos-reapply-context-value");
                            t.setDaemon(true);
                            return t;
                        });
    }

    @Override
    public String name() {
        return "reapply-context-value";
    }

    @Override
    public void start() {
        running = true;
        for (int i = 0; i < workerCount; i++) {
            pool.execute(this::workerLoop);
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
            System.err.println("[chaos] reapply-context-value: failed to get profiler: " + e);
            return;
        }

        long spanId = Thread.currentThread().getId() + 1;
        long localRootSpanId = spanId * 31L;
        long traceIdLow = spanId * 6364136223846793005L + 1442695040888963407L;

        while (running) {
            // Span activation resets all custom slots.
            profiler.setTraceContext(localRootSpanId, spanId, 0, traceIdLow, -1, null, -1, null);
            for (int i = 0; i < SLOT_COUNT; i++) {
                checkSetContextValue(profiler.setContextValue(i, ROUTES[i % ROUTES.length]), i);
            }
            for (int i = 0; i < SLOT_COUNT; i += 2) {
                profiler.clearContextValue(i);
            }
            for (int i = 0; i < SLOT_COUNT; i += 2) {
                int route = (i + ThreadLocalRandom.current().nextInt(ROUTES.length)) % ROUTES.length;
                checkSetContextValue(profiler.setContextValue(i, ROUTES[route]), i);
            }
            profiler.clearTraceContext();
        }
    }

    // Per Main's class javadoc, the harness's only failure signal is a non-zero process exit;
    // an exception here would otherwise die silently on this daemon worker thread (and be
    // swallowed entirely if the task were submitted via ExecutorService.submit and its Future
    // never inspected). Halt immediately so an unexpected failure actually fails the CI job.
    private static void checkSetContextValue(boolean succeeded, int slot) {
        if (!succeeded) {
            System.err.println("[chaos] reapply-context-value: setContextValue failed for slot " + slot);
            Runtime.getRuntime().halt(1);
        }
    }
}
