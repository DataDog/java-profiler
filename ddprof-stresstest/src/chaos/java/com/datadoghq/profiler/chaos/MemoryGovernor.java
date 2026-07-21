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

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryUsage;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Shared memory-pressure gate for antagonists whose allocation/thread-churn
 * rate can outrun GC/cleanup and threaten either the container's cgroup
 * ceiling or the JVM heap itself (alloc-storm, direct-memory, dump-storm,
 * weakref-wave, hidden-class-churn, context-hop, bounded-pool,
 * consumer-group).
 *
 * <p>A single background thread samples two independent signals every tick:
 * cgroup memory usage/limit (v2 {@code memory.current}/{@code memory.max},
 * falling back to v1 {@code memory.usage_in_bytes}/{@code
 * memory.limit_in_bytes}) and JVM heap usage ({@link
 * java.lang.management.MemoryMXBean#getHeapMemoryUsage()}). Either signal
 * crossing its high watermark sets the shared {@code throttled} flag;
 * clearing it requires both signals to be back below their low watermark
 * (hysteresis, so a single antagonist bouncing near one ceiling doesn't
 * flap the gate for antagonists driving the other). A signal that has no
 * readable ceiling (no cgroup limit, or a JVM without {@code -Xmx}) is
 * treated as permanently low rather than guessed at.
 *
 * <p>Antagonists poll {@link #pace()} once per loop iteration — a volatile
 * read plus, only while throttled, a short sleep. Above a second, higher
 * critical watermark, {@code pace()} sleeps much longer and fires a one-off
 * {@link System#gc()} to force reclaim before OOME hits — plain throttling
 * wasn't always enough to stop a heap OOME once several antagonists kept
 * allocating past the regular watermark (job 1861234807).
 *
 * <p>Even a 500ms background sampler was too coarse for an antagonist that
 * filled the heap from 16% to 97% between two consecutive samples (job
 * 1861521304) — by the time the sampler noticed, it was too late to react.
 * {@code pace()} therefore also peeks at heap usage directly every {@link
 * #INLINE_CHECK_STRIDE}th call, amortizing the cost of the check across
 * many hot-loop iterations while reacting within that many allocations
 * instead of within a fixed wall-clock interval. This inline path only ever
 * escalates (sets {@code throttled}/{@code critical}); de-escalating still
 * requires the background sampler's cgroup+heap hysteresis, since a single
 * antagonist's local view can't tell whether the other signal has cleared.
 */
final class MemoryGovernor {

    private static final double CGROUP_HIGH_WATERMARK = 0.85;
    private static final double CGROUP_LOW_WATERMARK = 0.70;
    // Heap-space OOME is less recoverable than a cgroup kill (no headroom to
    // shed off-heap first), so back off earlier and require more slack.
    private static final double HEAP_HIGH_WATERMARK = 0.80;
    private static final double HEAP_LOW_WATERMARK = 0.65;
    // Critical tier: same signals, higher bar. Crossing this calls for a
    // harder brake than pace()'s regular 5ms sleep, plus a one-time GC nudge.
    private static final double CGROUP_CRITICAL_WATERMARK = 0.93;
    private static final double HEAP_CRITICAL_WATERMARK = 0.90;
    private static final long SAMPLE_INTERVAL_MS = 100;
    private static final long THROTTLE_SLEEP_MS = 5;
    private static final long CRITICAL_THROTTLE_SLEEP_MS = 50;
    // Power of two so the stride check is a cheap mask instead of a modulo.
    private static final long INLINE_CHECK_STRIDE = 64;

    private static final Path[] USAGE_PATHS = {
            Paths.get("/sys/fs/cgroup/memory.current"),
            Paths.get("/sys/fs/cgroup/memory/memory.usage_in_bytes"),
    };
    private static final Path[] LIMIT_PATHS = {
            Paths.get("/sys/fs/cgroup/memory.max"),
            Paths.get("/sys/fs/cgroup/memory/memory.limit_in_bytes"),
    };

    // CAS-guarded so a watermark crossing is escalated exactly once even when
    // several antagonist threads observe it in the same instant (both via the
    // background sampler and the per-thread inline path below).
    private static final AtomicBoolean throttled = new AtomicBoolean();
    private static final AtomicBoolean critical = new AtomicBoolean();
    // Last cgroup reading from the background sampler, for the inline path's
    // log line only — the inline path itself never reads cgroup state (that
    // requires a file read, too costly to do on every antagonist's hot loop).
    private static volatile double lastCgroupFraction;
    // Per-thread rather than a shared counter: this is incremented on every
    // pace() call across every antagonist's hot loop, so a single shared
    // AtomicLong would become a cache-line contention point. Exactness across
    // threads isn't needed — each thread just needs to trigger the inline
    // check roughly every INLINE_CHECK_STRIDE calls.
    private static final ThreadLocal<long[]> paceCallCounter = ThreadLocal.withInitial(() -> new long[1]);

    private MemoryGovernor() {
    }

    /** Starts the background sampler. Cgroup and/or heap signals no-op individually if unreadable. Call once from Main. */
    static void start() {
        Path usagePath = firstReadable(USAGE_PATHS);
        long limitBytes = firstLimit(LIMIT_PATHS);
        if (usagePath == null || limitBytes <= 0) {
            usagePath = null;
            limitBytes = -1;
        }
        Path finalUsagePath = usagePath;
        long finalLimitBytes = limitBytes;
        Thread sampler = new Thread(() -> sampleLoop(finalUsagePath, finalLimitBytes), "chaos-memory-governor");
        sampler.setDaemon(true);
        sampler.start();
    }

    /** Called from an antagonist's hot allocation loop. No-op unless throttled. */
    static void pace() {
        long[] counter = paceCallCounter.get();
        if ((++counter[0] & (INLINE_CHECK_STRIDE - 1)) == 0) {
            inlineHeapCheck();
        }
        if (critical.get()) {
            try {
                Thread.sleep(CRITICAL_THROTTLE_SLEEP_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        } else if (throttled.get()) {
            try {
                Thread.sleep(THROTTLE_SLEEP_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

    /**
     * Fast path called from {@link #pace()} every {@link
     * #INLINE_CHECK_STRIDE}th call. Escalates on the caller's own thread as
     * soon as heap usage crosses a watermark, instead of waiting for the
     * next 500ms sampler tick.
     */
    private static void inlineHeapCheck() {
        MemoryUsage heap = ManagementFactory.getMemoryMXBean().getHeapMemoryUsage();
        if (heap.getMax() <= 0) {
            return;
        }
        double heapFraction = (double) heap.getUsed() / (double) heap.getMax();
        if (heapFraction >= HEAP_CRITICAL_WATERMARK && critical.compareAndSet(false, true)) {
            log(lastCgroupFraction, heapFraction, "critical (inline)");
            System.gc();
        } else if (heapFraction >= HEAP_HIGH_WATERMARK && throttled.compareAndSet(false, true)) {
            log(lastCgroupFraction, heapFraction, "throttling (inline)");
        }
    }

    private static void sampleLoop(Path usagePath, long limitBytes) {
        while (true) {
            try {
                Thread.sleep(SAMPLE_INTERVAL_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
            try {
                update(usagePath, limitBytes);
            } catch (IOException | NumberFormatException | OutOfMemoryError e) {
                // Transient read/allocation failure; keep last known state and retry next tick.
            }
        }
    }

    private static void update(Path usagePath, long limitBytes) throws IOException {
        double cgroupFraction = 0.0;
        if (usagePath != null) {
            cgroupFraction = (double) readLong(usagePath) / (double) limitBytes;
        }
        lastCgroupFraction = cgroupFraction;
        double heapFraction = 0.0;
        MemoryUsage heap = ManagementFactory.getMemoryMXBean().getHeapMemoryUsage();
        if (heap.getMax() > 0) {
            heapFraction = (double) heap.getUsed() / (double) heap.getMax();
        }

        boolean high = cgroupFraction >= CGROUP_HIGH_WATERMARK || heapFraction >= HEAP_HIGH_WATERMARK;
        boolean low = cgroupFraction <= CGROUP_LOW_WATERMARK && heapFraction <= HEAP_LOW_WATERMARK;
        boolean crit = cgroupFraction >= CGROUP_CRITICAL_WATERMARK || heapFraction >= HEAP_CRITICAL_WATERMARK;
        if (high && throttled.compareAndSet(false, true)) {
            log(cgroupFraction, heapFraction, "throttling");
        } else if (low && throttled.compareAndSet(true, false)) {
            log(cgroupFraction, heapFraction, "released");
        }
        // else: in the dead zone between watermarks — keep current state.

        if (crit && critical.compareAndSet(false, true)) {
            log(cgroupFraction, heapFraction, "critical");
            // One-shot nudge on the crossing, not every sample tick, so a
            // sustained critical state doesn't turn into a GC storm on top
            // of the memory pressure it's meant to relieve.
            System.gc();
        } else if (low && critical.compareAndSet(true, false)) {
            log(cgroupFraction, heapFraction, "critical-released");
        }
    }

    private static void log(double cgroupFraction, double heapFraction, String state) {
        System.out.println("[chaos] memory-governor " + state
                + " cgroup=" + String.format("%.2f", cgroupFraction)
                + " heap=" + String.format("%.2f", heapFraction));
    }

    private static Path firstReadable(Path[] candidates) {
        for (Path p : candidates) {
            if (Files.isReadable(p)) {
                return p;
            }
        }
        return null;
    }

    private static long firstLimit(Path[] candidates) {
        for (Path p : candidates) {
            if (Files.isReadable(p)) {
                try {
                    return readLong(p);
                } catch (IOException | NumberFormatException e) {
                    // "max" (v2, unlimited) or unreadable; try the next candidate.
                }
            }
        }
        return -1;
    }

    private static long readLong(Path path) throws IOException {
        String s = new String(Files.readAllBytes(path), StandardCharsets.US_ASCII).trim();
        return Long.parseLong(s);
    }
}
