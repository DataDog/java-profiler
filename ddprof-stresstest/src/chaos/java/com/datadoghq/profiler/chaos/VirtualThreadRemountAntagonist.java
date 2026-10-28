/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import java.lang.reflect.Method;
import java.time.Duration;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.locks.LockSupport;

/**
 * Repeatedly parks a bounded set of virtual threads under deep Java callers, then burns CPU after
 * remounting. Alternating argument layouts and recursion depths exercise partial thaw while the
 * recursive methods progress through interpreted, compiled and OSR execution.
 */
public final class VirtualThreadRemountAntagonist implements Antagonist {
    private static final Method START_VIRTUAL_THREAD = resolveStartVirtualThread();
    private final Worker[] workers;
    private final AtomicReference<Throwable> failure = new AtomicReference<>();
    private volatile boolean running;
    private boolean started;

    /** Creates four workers, with no thread or allocation churn in their recursive hot loops. */
    public VirtualThreadRemountAntagonist() {
        this(4);
    }

    /** Creates between one and sixteen workers; each alternates both argument layouts. */
    public VirtualThreadRemountAntagonist(int workerCount) {
        if (workerCount < 1 || workerCount > 16) throw new IllegalArgumentException("workerCount must be 1..16");
        workers = new Worker[workerCount];
        for (int i = 0; i < workers.length; i++) workers[i] = new Worker(i);
    }

    /** Name accepted by the chaos harness. */
    @Override
    public String name() {
        return "vthread-remount";
    }

    /** Starts the workers once; gracefully skips runtimes without virtual threads. */
    @Override
    public void start() {
        if (started) throw new IllegalStateException("Already started");
        started = true;
        if (START_VIRTUAL_THREAD == null) {
            System.out.println("[chaos] vthread-remount: skipping (virtual threads unavailable)");
            return;
        }
        running = true;
        try {
            for (Worker worker : workers) {
                worker.thread = (Thread) START_VIRTUAL_THREAD.invoke(null, worker);
            }
        } catch (ReflectiveOperationException e) {
            failure.compareAndSet(null, e);
            stopGracefully(Duration.ofSeconds(10));
        }
    }

    /** Unparks and joins every worker within one shared deadline; propagates worker failures. */
    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        for (Worker worker : workers) {
            if (worker.thread != null) worker.thread.interrupt();
        }
        long deadline = System.nanoTime() + timeout.toNanos();
        boolean interrupted = false;
        for (Worker worker : workers) {
            if (worker.thread == null) continue;
            long remaining = deadline - System.nanoTime();
            if (remaining <= 0) break;
            try {
                worker.thread.join(Math.max(1, TimeUnit.NANOSECONDS.toMillis(remaining)));
            } catch (InterruptedException e) {
                interrupted = true;
                break;
            }
        }
        if (interrupted) Thread.currentThread().interrupt();
        for (Worker worker : workers) {
            if (worker.thread != null && worker.thread.isAlive()) {
                throw new IllegalStateException("vthread-remount worker did not stop");
            }
        }
        if (failure.get() != null) throw new IllegalStateException("vthread-remount worker failed", failure.get());
    }

    /** Number of completed register-argument park/remount cycles across all workers. */
    public long registerCycles() {
        long count = 0;
        for (Worker worker : workers) count += worker.registerCycles;
        return count;
    }

    /** Number of completed stack-argument park/remount cycles across all workers. */
    public long stackCycles() {
        long count = 0;
        for (Worker worker : workers) count += worker.stackCycles;
        return count;
    }

    private final class Worker implements Runnable {
        private final int id;
        private Thread thread;
        private volatile long registerCycles;
        private volatile long stackCycles;
        private volatile long checksum;

        private Worker(int id) {
            this.id = id;
        }

        /** Alternates layouts until stopped, retaining any failure for the owner. */
        @Override
        public void run() {
            try {
                long cycle = id;
                while (running) {
                    int depth = 128 + 32 * (int) (cycle & 3);
                    registerWorkload(this, depth, cycle);
                    if (!running) break;
                    stackWorkload(this, depth, cycle);
                    cycle++;
                }
            } catch (Throwable t) {
                failure.compareAndSet(null, t);
                running = false;
            }
        }
    }

    /** This outer caller always exists logically, even if it remains frozen at sampling time. */
    private void registerWorkload(Worker worker, int depth, long seed) {
        worker.checksum = registerFrames(depth, seed);
        worker.registerCycles++;
    }

    /** Keeps recursive callers live while work in the leaf is sampled after a park. */
    private long registerFrames(int depth, long seed) {
        if (depth > 0) return registerFrames(depth - 1, seed) + depth;
        LockSupport.parkNanos(500_000L);
        long deadline = System.nanoTime() + 2_000_000L;
        do {
            for (int i = 0; i < 256; i++) seed = seed * 6364136223846793005L + 1442695040888963407L;
        } while (running && System.nanoTime() < deadline);
        return seed;
    }

    /** Establishes an outer caller for the stack-passed argument variant. */
    private void stackWorkload(Worker worker, int depth, long seed) {
        worker.checksum = stackFrames(depth, seed, 2, 3, 4, 5, 6, 7, 8, 9);
        worker.stackCycles++;
    }

    /** Keeps nine long arguments live across recursive calls, partial thaw and compilation. */
    private long stackFrames(int depth, long a, long b, long c, long d, long e, long f, long g, long h, long i) {
        if (depth > 0) return stackFrames(depth - 1, a, b, c, d, e, f, g, h, i) + depth + b + c + d + e + f + g + h + i;
        LockSupport.parkNanos(500_000L);
        long deadline = System.nanoTime() + 2_000_000L;
        do {
            for (int n = 0; n < 256; n++) a = a * 6364136223846793005L + 1442695040888963407L;
        } while (running && System.nanoTime() < deadline);
        return a + b + c + d + e + f + g + h + i;
    }

    /** Resolves the Java 21 factory while keeping the harness compatible with Java 8. */
    private static Method resolveStartVirtualThread() {
        try {
            return Thread.class.getMethod("startVirtualThread", Runnable.class);
        } catch (NoSuchMethodException e) {
            return null;
        }
    }
}
