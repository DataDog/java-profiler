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
 * Grows an ever-referenced cache to give the reference-chains
 * feature (LivenessTracker/ReferenceChainTracker) a real, steadily growing
 * population to detect and walk. Memory stays bounded: once the live entry
 * count reaches {@link #CAP_ENTRIES} the antagonist switches to a bounded
 * recycle cycle - it evicts the oldest {@link #RECYCLE_EVICT_ENTRIES} entries
 * and then regrows to the cap - so the population keeps going through rising
 * legs for the whole run instead of freezing at a flat count (a cache that
 * grows to a fixed size and then sits flat stops being a growing population:
 * the trend detection's earliest-vs-recent ring comparison reads a ~zero slope
 * and the feature gets no leak signal for the rest of a multi-hour run). The
 * recycle fraction keeps at least 3/4 of the cap alive at all times, so a long
 * chaos duration still produces a bounded leak instead of eventually OOMing
 * the JVM out from under the other antagonists sharing its heap.
 *
 * <p>Same object shape as {@code LeakingCacheScenario.CachedPayload}
 * (ddprof-test's reference-chain integration test) — plain long fields
 * rather than a nested array, so a single instance clears the allocation
 * sampler's real size floor without a second, competing heap allocation per
 * entry.
 */
public final class ReferenceChainLeakAntagonist implements Antagonist {

    // ~64MiB of CachedEntry payloads at the cap (entries are a little
    // over 300 bytes with object header/field overhead) — enough for the
    // liveness tracker's population-growth trend detection to have a real,
    // sustained trend to lock onto, without meaningfully competing with the
    // other antagonists' own memory budget for the run's whole duration.
    private static final int CAP_ENTRIES = 200_000;

    // Entries evicted per recycle cycle once the cap is reached (25% of the
    // cap): large enough that each regrow leg is a visible rising population
    // trend, small enough that 3/4 of the population stays alive at all times.
    private static final int RECYCLE_EVICT_ENTRIES = 50_000;

    private static final int BATCH_SIZE = 200;
    private static final long BATCH_INTERVAL_MS = 50L;

    private final Map<String, CachedEntry> cache = new ConcurrentHashMap<>();
    private volatile boolean running;
    private Thread growthDriver;
    private long nextKey;
    private long evictKey;
    private long liveEntries;

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
        // liveEntries, not cache.size(): ConcurrentHashMap.size() sums every counter cell, too
        // costly per put/remove. Exact here - this thread is the only writer, keys are unique
        // and evictions only remove what a previous put added, so the counter always matches.
        while (running) {
            if (liveEntries >= CAP_ENTRIES) {
                // Cap reached: recycle phase - evict the oldest entries, then the loop's
                // growth phase regrows them with fresh keys, giving the population trend
                // detection a repeated rising signal instead of a flat count.
                long evictTarget = Math.min(evictKey + RECYCLE_EVICT_ENTRIES, nextKey);
                for (; running && evictKey < evictTarget; evictKey++) {
                    cache.remove("refchain-leak-" + evictKey);
                    liveEntries--;
                    MemoryGovernor.pace();
                }
            }
            while (running && liveEntries < CAP_ENTRIES) {
                for (int i = 0; i < BATCH_SIZE && liveEntries < CAP_ENTRIES; i++) {
                    String key = "refchain-leak-" + (nextKey++);
                    cache.put(key, new CachedEntry(key));
                    liveEntries++;
                    MemoryGovernor.pace();
                }
                try {
                    Thread.sleep(BATCH_INTERVAL_MS);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    return;
                }
            }
            try {
                Thread.sleep(BATCH_INTERVAL_MS);
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
