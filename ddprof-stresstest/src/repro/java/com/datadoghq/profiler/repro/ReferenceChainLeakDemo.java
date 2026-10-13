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
 *   referencechains=true:hops=64:budget=10000:ttl=120000:framecap=2000000:\
 *   pausetarget=5000:painbudget=100,jfr,file=repro.jfr \
 *   -jar refchains_repro.jar repro.jfr /path/to/libjavaProfiler.so
 * </pre>
 *
 * <p>Takes the JFR output path as {@code args[0]} (must match {@code file=} above) and the
 * agent's own {@code .so} path as {@code args[1]} (must match the {@code -agentpath} value
 * above), and periodically calls {@link JavaProfiler#dump}. Both are load-bearing: the dump call
 * is the only code path that drains {@code ReferenceChainTracker}'s pending chain-event queue
 * into the JFR file (nothing drains it on a timer), and passing the {@code .so} path explicitly
 * makes {@code getInstance()} attach to the already-loaded {@code -agentpath} agent instead of
 * extracting the jar's bundled copy to a temp file - a second, never-{@code start()}-ed
 * {@code Profiler} singleton whose {@code dump()} calls would be silent no-ops. Each periodic
 * dump goes to its own file, {@code <jfr-dump-path>.snapshot.<round>}, because a drained chain
 * event is written exactly once: reusing one snapshot path would permanently lose every earlier
 * window's chains. A bounded run's final dump goes to {@code <jfr-dump-path>.snapshot} (the path
 * the sweep scripts read); inspect all snapshot files together for the complete chain evidence.
 *
 * <p>An optional {@code args[2]} duration in seconds switches from the default "run forever"
 * manual mode to a bounded session that dumps once more and prints a single {@code [metrics]}
 * line at exit (throughput, round latency, heap growth) - see
 * {@code utils/compare-refchains-repro.sh}, which runs this app twice (referencechains on vs.
 * off) over the same duration and diffs those lines against each run's safepoint/GC logs.
 *</p>
 * <p>Deliberately omits {@code firstpassbudget}: the tracker auto-scales its first pass's budget
 * from the plain {@code budget} value ({@code AUTO_FIRST_PASS_BUDGET_MULTIPLIER}, capped at
 * {@code AUTO_FIRST_PASS_BUDGET_CAP}, referenceChains.h) rather than reusing {@code budget} as-is
 * for that first, cold root-seeded walk - reusing it directly truncates every pass before it gets
 * anywhere near this app's {@code CachedEntry} population. Pass {@code firstpassbudget=N}
 * explicitly only to override that auto-scaled default.
 *
 * <p>Grows an ever-referenced, never-evicted {@code HashMap}-backed cache (same shape as
 * ddprof-test's {@code LeakingCacheScenario}). Two deliberate choices, both found by running
 * without them and never seeing a chain get discovered:
 *
 * <ul>
 *   <li><b>Explicit {@code System.gc()} every round.</b> {@code LivenessTracker}'s
 *   population-growth trend needs at least {@code KLASS_POPULATION_MIN_FILL_FOR_TREND} (10)
 *   distinct GC epochs of samples before it attempts a slope, and {@code _gc_epoch} only advances
 *   on a {@code GarbageCollectionFinish} callback. A slow allocation rate against a large default
 *   heap can go many minutes without a GC, so the trend never moves on its own.</li>
 *   <li><b>No hard stop.</b> A cache that grows to a fixed cap and then sits flat stops being a
 *   growing population the instant it stops growing - {@code computeKlassPopulationSlope} compares
 *   the earliest vs. most recent third of its 30-epoch ring, so a long enough flat period pushes
 *   the slope back to zero. This app keeps growing forever, self-throttling against a heap-usage
 *   watermark (see {@link #run}) so the trend stays real without ever exhausting the heap.</li>
 * </ul>
 *
 * <p>Seeds the cache on the very first line of {@code main} - before validating arguments,
 * loading/attaching to the agent library, printing anything, or sleeping - so the agent's one-shot, root-seeded first pass (which fires roughly a second after
 * the agent's background thread starts, i.e. before {@code Agent_OnLoad} even returns control to
 * {@code main}) has a real chance of finding {@code cache} already non-empty. See
 * {@code LeakingCacheScenario}'s comment for why that ordering is load-bearing.
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

    private static final String USAGE =
            "usage: ReferenceChainLeakDemo <jfr-dump-path> <agent-so-path> [duration-seconds] "
                    + "(both required args must match the -agentpath:<agent-so-path>=...jfr,file=<jfr-dump-path> values; "
                    + "duration-seconds - a non-negative whole number of seconds - runs a bounded, "
                    + "metrics-reporting session instead of forever)";

    public static void main(String[] args) throws Exception {
        // Must stay first - see the class header: seeding races the agent's one-shot,
        // root-seeded first pass.
        Map<String, CachedEntry> cache = new HashMap<>();
        seed(cache, 300);
        if (args.length < 2) {
            System.err.println(USAGE);
            System.exit(1);
        }
        long durationSeconds = args.length >= 3 ? parseDurationSeconds(args[2]) : -1;
        run(cache, Paths.get(args[0]), args[1], durationSeconds);
    }

    // Malformed input (e.g. an empty/garbled $DURATION from the wrapper scripts) must print the
    // usage and exit non-zero, not die with an uncaught NumberFormatException. Also rejects
    // values whose deadline (seconds * 1e9 ns, see run()) would overflow a long.
    private static long parseDurationSeconds(String arg) {
        long seconds;
        try {
            seconds = Long.parseLong(arg.trim());
        } catch (NumberFormatException e) {
            seconds = -1;
        }
        if (seconds < 0 || seconds > Long.MAX_VALUE / 1_000_000_000L) {
            System.err.println("invalid duration-seconds '" + arg + "'");
            System.err.println(USAGE);
            System.exit(1);
        }
        return seconds;
    }

    // FlightRecorder::dump() (flightRecorder.cpp) rejects dumping the continuous recording to
    // its own file= path ("Can not dump recording to itself"), so drains must target a
    // different path; this is that path's suffix. Periodic drains append ".<round>" so each
    // window's drained chain events survive (see this class's header comment); the final
    // bounded-run drain uses the bare suffix.
    private static final String SNAPSHOT_SUFFIX = ".snapshot";

    // Tracked so a bounded run (durationSeconds >= 0) can report throughput/latency/memory
    // deltas at exit for A/B comparison against a referencechains=false baseline - see
    // utils/compare-refchains-repro.sh.
    private static long roundCount = 0;
    private static long totalEntriesAdded = 0;
    private static long totalRoundNanos = 0;
    private static long maxRoundNanos = 0;

    private static void run(Map<String, CachedEntry> cache, Path recordingPath, String agentSoPath, long durationSeconds) throws InterruptedException {
        // Must differ from recordingPath itself - see SNAPSHOT_SUFFIX's comment. Final
        // (bounded-run) drain target; periodic drains use snapshotPath + "." + round.
        Path snapshotPath = recordingPath.resolveSibling(recordingPath.getFileName() + SNAPSHOT_SUFFIX);
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

        System.out.println("[repro] pid=" + pid()
                + " - growing cache " + (durationSeconds >= 0 ? ("for " + durationSeconds + "s") : "forever")
                + ", forcing a GC every round so the profiler's "
                + "population-growth trend detection has real epochs to work with; watch "
                + "heapUsedMb/heapMaxMb and attach/dump once a chain shows up");

        long startNanos = System.nanoTime();
        long deadlineNanos = durationSeconds >= 0 ? startNanos + durationSeconds * 1_000_000_000L : Long.MAX_VALUE;
        long startHeapUsedMb = heapUsedMb();

        long nextKey = 300;
        int round = 0;
        while (System.nanoTime() < deadlineNanos) {
            long roundStartNanos = System.nanoTime();
            round++;
            double heapFraction = heapUsedFraction();
            int batchSize = heapFraction >= HIGH_WATERMARK ? THROTTLED_BATCH_SIZE : NORMAL_BATCH_SIZE;
            long roundIntervalMs = heapFraction >= HIGH_WATERMARK ? THROTTLED_ROUND_INTERVAL_MS : ROUND_INTERVAL_MS;

            if (heapFraction < CRITICAL_WATERMARK) {
                for (int i = 0; i < batchSize; i++) {
                    String key = "leak-" + (nextKey++);
                    cache.put(key, new CachedEntry(key));
                }
                totalEntriesAdded += batchSize;
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
                // Distinct file per drain: an event drained here is written only to this file.
                Path roundSnapshotPath =
                        snapshotPath.resolveSibling(snapshotPath.getFileName() + "." + round);
                profiler.dump(roundSnapshotPath);
                System.out.println("[repro] dumped " + roundSnapshotPath);
            }

            long roundNanos = System.nanoTime() - roundStartNanos;
            roundCount++;
            totalRoundNanos += roundNanos;
            maxRoundNanos = Math.max(maxRoundNanos, roundNanos);

            Thread.sleep(roundIntervalMs);
        }

        if (durationSeconds >= 0) {
            profiler.dump(snapshotPath);
            System.out.println("[repro] dumped " + snapshotPath);
            reportMetrics(startNanos, startHeapUsedMb);
        }
    }

    // Printed with a distinct "[metrics]" prefix so utils/compare-refchains-repro.sh can grep
    // it out of the two runs' stdout (referencechains=true vs. false) and diff throughput/
    // latency/memory-growth directly, without needing to touch the safepoint/GC logs for those.
    private static void reportMetrics(long startNanos, long startHeapUsedMb) {
        long wallNanos = System.nanoTime() - startNanos;
        double wallSeconds = wallNanos / 1_000_000_000.0;
        double avgRoundMs = roundCount == 0 ? 0 : (totalRoundNanos / (double) roundCount) / 1_000_000.0;
        double maxRoundMs = maxRoundNanos / 1_000_000.0;
        double entriesPerSec = wallSeconds > 0 ? totalEntriesAdded / wallSeconds : 0;
        long heapGrowthMb = heapUsedMb() - startHeapUsedMb;

        System.out.println("[metrics] wallSeconds=" + String.format("%.1f", wallSeconds)
                + " rounds=" + roundCount
                + " entriesAdded=" + totalEntriesAdded
                + " entriesPerSec=" + String.format("%.1f", entriesPerSec)
                + " avgRoundMs=" + String.format("%.3f", avgRoundMs)
                + " maxRoundMs=" + String.format("%.3f", maxRoundMs)
                + " heapUsedMbStart=" + startHeapUsedMb
                + " heapUsedMbEnd=" + heapUsedMb()
                + " heapGrowthMb=" + heapGrowthMb);
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
        long max = heap.getMax();
        if (max <= 0) {
            // Heap max undefined (-1) in some container/ergonomics setups: fall back to
            // Runtime.maxMemory(), and if that is unbounded too (Long.MAX_VALUE), report the high
            // watermark so growth runs throttled - never treat "unknown limit" as "empty heap".
            long runtimeMax = Runtime.getRuntime().maxMemory();
            if (runtimeMax <= 0 || runtimeMax == Long.MAX_VALUE) {
                return HIGH_WATERMARK;
            }
            max = runtimeMax;
        }
        return (double) heap.getUsed() / (double) max;
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
