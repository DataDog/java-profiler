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
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Grows an ever-referenced, never-evicted cache to give the reference-chains
 * feature (LivenessTracker/ReferenceChainTracker) a real, steadily growing
 * population to detect and walk. Growth is capped, not open-ended: once
 * {@link #CAP_ENTRIES} is reached the cache stops growing and the antagonist
 * just holds it there for the rest of the run, so a long chaos duration
 * (hours) still produces the same bounded leak instead of eventually OOMing
 * the JVM out from under the other antagonists sharing its heap.
 *
 * <p>Same object shape as {@code LeakingCacheScenario.CachedPayload}
 * (ddprof-test's reference-chain integration test) — plain long fields
 * rather than a nested array, so a single instance clears the allocation
 * sampler's real size floor without a second, competing heap allocation per
 * entry.
 */
public final class ReferenceChainLeakAntagonist implements Antagonist {

    // ~64MiB of CachedEntry payloads at steady state (entries are a little
    // over 300 bytes with object header/field overhead) — enough for the
    // liveness tracker's population-growth trend detection to have a real,
    // sustained trend to lock onto, without meaningfully competing with the
    // other antagonists' own memory budget for the run's whole duration.
    private static final int CAP_ENTRIES = 200_000;
    private static final int BATCH_SIZE = 200;
    private static final long BATCH_INTERVAL_MS = 50L;

    private final Map<String, CachedEntry> cache = new ConcurrentHashMap<>();
    private volatile boolean running;
    private Thread growthDriver;
    private long nextKey;

    @Override
    public String name() {
        return "reference-chain-leak";
    }

    @Override
    public void start() {
        running = true;
        growthDriver = new Thread(this::growthLoop, "chaos-refchain-leak");
        growthDriver.setDaemon(true);
        growthDriver.start();
    }

    @Override
    public void stopGracefully(Duration timeout) {
        running = false;
        try {
            growthDriver.join(timeout.toMillis());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void growthLoop() {
        while (running && cache.size() < CAP_ENTRIES) {
            for (int i = 0; i < BATCH_SIZE && cache.size() < CAP_ENTRIES; i++) {
                String key = "refchain-leak-" + (nextKey++);
                cache.put(key, new CachedEntry(key));
                MemoryGovernor.pace();
            }
            try {
                Thread.sleep(BATCH_INTERVAL_MS);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
        // Cap reached: keep the reference alive (do nothing) for the rest of
        // the run instead of exiting the thread, so `cache` stays reachable
        // via this antagonist's own field for as long as the harness runs.
        while (running) {
            try {
                Thread.sleep(1_000L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }
        }
    }

    static final class CachedEntry {
        final String key;
        long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
        long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;

        CachedEntry(String key) {
            this.key = key;
        }
    }
}
