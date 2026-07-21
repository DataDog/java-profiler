/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */
package com.datadoghq.profiler.repro;

import com.datadoghq.profiler.JavaProfiler;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryUsage;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

/**
 * Standalone demo app for manually reproducing the reference-chains feature end-to-end.
 * Meant to be launched directly with the native agent loaded at JVM startup, e.g.
 *
 * <pre>
 * java -agentpath:/path/to/libjavaProfiler.so=start,memory=64:l,generations=true,\
 *   referencechains=true:hops=64:budget=4000:ttl=120000:framecap=2000000:\
 *   pausetarget=5000:painbudget=100,jfr,file=repro.jfr \
 *   -jar refchains_repro.jar repro.jfr /path/to/libjavaProfiler.so
 * </pre>
 *
 * <p>Takes the JFR output path as {@code args[0]} (must match {@code file=} above) and the
 * agent's own {@code .so} path as {@code args[1]} (must match the {@code -agentpath} value
 * above), and periodically calls {@link JavaProfiler#dump}. Both are load-bearing:
 * <ul>
 *   <li>The dump call itself: {@code Profiler::dump()} (profiler.cpp) is the only code path
 *   that drains {@code ReferenceChainTracker}'s pending chain-event queue and actually writes
 *   {@code datadog.ReferenceChain} into the JFR file - nothing drains that queue on a timer,
 *   and in production it's dd-trace-java's own periodic recording-chunk rotation that calls
 *   {@code dump()}. Without it, chain events get built and enqueued (visible via {@code
 *   TEST_LOG}) but are silently discarded when the process exits.
 *   <li>Passing the {@code .so} path explicitly to {@link JavaProfiler#getInstance(String,
 *   String)}: with no {@code libLocation}, {@code getInstance()} extracts the jar's own
 *   bundled copy of the library to a fresh temp file and {@code System.load()}s <em>that</em>
 *   instead of attaching to the one {@code -agentpath} already loaded - a second, never-{@code
 *   start()}-ed {@code Profiler} singleton whose {@code dump()} calls are silent no-ops.
 *   Passing the same path lets the dynamic linker dedup the load onto the already-running
 *   singleton, the same way dd-trace-java attaches to its own {@code -agentpath} agent.
 * </ul>
 *
 * <p>Deliberately omits {@code firstpassbudget}: the tracker auto-scales its
 * first pass's budget from the plain {@code budget} value
 * ({@code ReferenceChainTracker::AUTO_FIRST_PASS_BUDGET_MULTIPLIER}, capped at
 * {@code AUTO_FIRST_PASS_BUDGET_CAP}, referenceChains.h) rather than reusing
 * {@code budget} as-is for that first, cold root-seeded walk - reusing it directly
 * truncates every pass before it gets anywhere near this app's {@code CachedEntry}
 * population, and the target's JVMTI tag stays 0 forever. Pass
 * {@code firstpassbudget=N} explicitly only to override that auto-scaled default.
 *
 * <p>Grows an ever-referenced, never-evicted {@code HashMap}-backed cache (same shape as
 * ddprof-test's {@code LeakingCacheScenario}/the chaos harness's {@code
 * ReferenceChainLeakAntagonist}). Two things this app does deliberately, both found the hard
 * way by running it without them and never seeing a chain get discovered:
 *
 * <ul>
 *   <li><b>Explicit {@code System.gc()} every round.</b> {@code LivenessTracker}'s
 *   population-growth trend ({@code computeKlassPopulationSlope}, livenessTracker.cpp) needs at
 *   least {@code KLASS_POPULATION_MIN_FILL_FOR_TREND} (10) distinct GC epochs of population
 *   samples before it will even attempt a slope, and {@code _gc_epoch} only advances on a
 *   {@code GarbageCollectionFinish} JVMTI callback - i.e. on an actual GC. Left to whatever GCs
 *   the JVM decides to run on its own, a slow, modest allocation rate against a large default
 *   heap can go many minutes without a single GC, so the epoch count - and therefore the trend -
 *   never moves. Forcing a GC every round (same pattern {@code LeakingCacheScenario}'s round
 *   loop and {@code ReferenceChainTrackingTest} already rely on) turns epoch progress into
 *   something this app controls directly instead of leaving it to chance.
 *   <li><b>No hard stop.</b> A cache that grows to a fixed cap and then sits flat stops being a
 *   growing population the instant it stops growing - {@code computeKlassPopulationSlope}
 *   compares the earliest vs. most recent third of its 30-epoch ring, so a long enough flat
 *   period after the cap pushes the slope back to zero (or the real growth epochs age out of the
 *   ring before the search ever gets scheduled/its own pain-budget cooldown clears). This app
 *   keeps growing forever instead, self-throttling its own pace against a heap-usage watermark
 *   (see {@link #run}) so it stays a real, positive, continuously-observable trend without ever
 *   growing fast/large enough to actually exhaust the heap.
 * </ul>
 *
 * <p>Seeds the cache with an initial batch on the very first line of {@code main} - before
 * printing anything or sleeping - so the agent's one-shot, root-seeded first pass (which fires
 * roughly a second after the agent's own background thread starts, i.e. before {@code
 * Agent_OnLoad} even returns control to this class's {@code main}) has a real chance of finding
 * {@code cache} already non-empty. See {@code LeakingCacheScenario}'s own comment for the full
 * story of why that ordering is load-bearing.
 */
public final class ReferenceChainLeakDemo {

    // Heap-usage watermarks gating growth pace, mirroring the chaos harness's own
    // MemoryGovernor - a much simpler version since this app has only one grower to pace,
    // not several antagonists sharing a budget.
    private static final double HIGH_WATERMARK = 0.70;
    private static final double CRITICAL_WATERMARK = 0.85;

    private static final int NORMAL_BATCH_SIZE = 2_000;
    private static final int THROTTLED_BATCH_SIZE = 100;
    private static final long ROUND_INTERVAL_MS = 300L;
    private static final long THROTTLED_ROUND_INTERVAL_MS = 2_000L;

    // How often to call JavaProfiler.dump() to drain any pending reference-chain
    // events into the JFR file - see this class's own header comment for why this
    // call, not just this app's own memory growth, is load-bearing for the repro.
    private static final int DUMP_EVERY_N_ROUNDS = 10;

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.err.println("usage: ReferenceChainLeakDemo <jfr-dump-path> <agent-so-path> "
                    + "(both must match the -agentpath:<agent-so-path>=...jfr,file=<jfr-dump-path> values)");
            System.exit(1);
        }
        run(Paths.get(args[0]), args[1]);
    }

    private static void run(Path dumpPath, String agentSoPath) throws InterruptedException {
        // Must pass the exact .so path -agentpath already loaded: JavaProfiler.getInstance()
        // with no libLocation extracts the jar's own bundled copy to a fresh temp file and
        // System.load()s *that* instead, producing a second, never-started Profiler singleton
        // completely disconnected from the real profiling session - dump() calls against it
        // are silent no-ops. Passing the same path here lets the dynamic linker dedup the
        // load to the already-mapped library, i.e. the real, already-running singleton.
        JavaProfiler profiler;
        try {
            profiler = JavaProfiler.getInstance(agentSoPath, null);
        } catch (Exception e) {
            throw new IllegalStateException(
                    "JavaProfiler.getInstance() failed - was this launched with "
                            + "-agentpath:libjavaProfiler.so=start,...?", e);
        }

        Map<String, CachedEntry> cache = new HashMap<>();
        seed(cache, 300);

        System.out.println("[repro] pid=" + pid()
                + " - growing cache forever, forcing a GC every round so the profiler's "
                + "population-growth trend detection has real epochs to work with; watch "
                + "heapUsedMb/heapMaxMb and attach/dump once a chain shows up");

        long nextKey = 300;
        int round = 0;
        while (true) {
            round++;
            double heapFraction = heapUsedFraction();
            int batchSize = heapFraction >= HIGH_WATERMARK ? THROTTLED_BATCH_SIZE : NORMAL_BATCH_SIZE;
            long roundIntervalMs = heapFraction >= HIGH_WATERMARK ? THROTTLED_ROUND_INTERVAL_MS : ROUND_INTERVAL_MS;

            if (heapFraction < CRITICAL_WATERMARK) {
                for (int i = 0; i < batchSize; i++) {
                    String key = "leak-" + (nextKey++);
                    cache.put(key, new CachedEntry(key));
                }
            } else {
                System.out.println("[repro] heap usage critical (" + pct(heapFraction)
                        + ") - pausing growth this round, attach/dump now if you haven't");
            }

            // Forces a GC every round regardless of watermark state, so _gc_epoch (and
            // therefore the population-growth ring) keeps advancing even while paused/
            // throttled - see this class's own header comment for why that's load-bearing.
            System.gc();

            if (round % 10 == 0 || heapFraction >= HIGH_WATERMARK) {
                System.out.println("[repro] round=" + round + " cache.size()=" + cache.size()
                        + " heapUsedMb=" + heapUsedMb() + " heapFraction=" + pct(heapFraction));
            }

            if (round % DUMP_EVERY_N_ROUNDS == 0) {
                profiler.dump(dumpPath);
            }

            Thread.sleep(roundIntervalMs);
        }
    }

    private static void seed(Map<String, CachedEntry> cache, int count) {
        for (int i = 0; i < count; i++) {
            String key = "seed-" + i;
            cache.put(key, new CachedEntry(key));
        }
    }

    private static String pid() {
        String name = ManagementFactory.getRuntimeMXBean().getName();
        int at = name.indexOf('@');
        return at >= 0 ? name.substring(0, at) : name;
    }

    private static long heapUsedMb() {
        return ManagementFactory.getMemoryMXBean().getHeapMemoryUsage().getUsed() / (1024 * 1024);
    }

    private static double heapUsedFraction() {
        MemoryUsage heap = ManagementFactory.getMemoryMXBean().getHeapMemoryUsage();
        return heap.getMax() > 0 ? (double) heap.getUsed() / (double) heap.getMax() : 0.0;
    }

    private static String pct(double fraction) {
        return String.format("%.1f%%", fraction * 100.0);
    }

    /**
     * Same shape as {@code LeakingCacheScenario.CachedPayload}/{@code
     * ReferenceChainLeakAntagonist.CachedEntry}: plain long fields, not a nested array, so a
     * single instance clears the allocation sampler's real size floor without a second,
     * competing heap allocation per entry.
     */
    static final class CachedEntry {
        final String key;
        long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
        long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;

        CachedEntry(String key) {
            this.key = key;
        }
    }
}
