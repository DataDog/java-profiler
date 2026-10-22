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
    private MethodHandle setTraceContext;
    private MethodHandle clearTraceContext;
    private MethodHandle setContextValue;
    private MethodHandle clearContextValue;

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

    /** Resolves context hooks before launching workers so class-loading failures fail startup. */
    @Override
    public void start() {
        try {
            Object profiler = ProfilerAccess.getInstance();
            setTraceContext = ProfilerAccess.bind(profiler, "setTraceContext",
                    long.class, long.class, long.class, long.class,
                    int.class, CharSequence.class, int.class, CharSequence.class);
            clearTraceContext = ProfilerAccess.bind(profiler, "clearTraceContext");
            setContextValue = ProfilerAccess.bind(profiler, "setContextValue", int.class, String.class);
            clearContextValue = ProfilerAccess.bind(profiler, "clearContextValue", int.class);
        } catch (ReflectiveOperationException e) {
            throw new IllegalStateException("Cannot bind profiler context hooks", e);
        }
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
        try {
            long spanId = Thread.currentThread().getId() + 1;
            long localRootSpanId = spanId * 31L;
            long traceIdLow = spanId * 6364136223846793005L + 1442695040888963407L;

            while (running) {
                // Span activation resets all custom slots.
                setTraceContext.invokeExact(localRootSpanId, spanId, 0L, traceIdLow,
                        -1, (CharSequence) null, -1, (CharSequence) null);
                for (int i = 0; i < SLOT_COUNT; i++) {
                    checkSetContextValue((boolean) setContextValue.invokeExact(i, ROUTES[i % ROUTES.length]), i);
                }
                for (int i = 0; i < SLOT_COUNT; i += 2) {
                    clearContextValue.invokeExact(i);
                }
                for (int i = 0; i < SLOT_COUNT; i += 2) {
                    int route = (i + ThreadLocalRandom.current().nextInt(ROUTES.length)) % ROUTES.length;
                    checkSetContextValue((boolean) setContextValue.invokeExact(i, ROUTES[route]), i);
                }
                clearTraceContext.invokeExact();
            }
        } catch (Throwable t) {
            t.printStackTrace(System.err);
            Runtime.getRuntime().halt(1);
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
