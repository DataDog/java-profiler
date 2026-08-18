/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies once-per-run signal suppression ({@code wallprecheck=true}): a sleeping thread
 * should produce a handful of {@code MethodSample} events (entry + boundary jitter), not ~300.
 * Requires JDK 11+ — JDK 8 HotSpot reports inconsistent OSThread states for sleep.
 */
public class PrecheckTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final String TAIL_WEIGHT_THREAD = "precheck-tail-weight";
    private static final int TAIL_WEIGHT_ITERATIONS = 50;
    private static final int TAIL_WEIGHT_SLEEP_MILLIS = 6;
    private static final long TAIL_WEIGHT_RUNNABLE_NANOS = 2_000_000L;
    private static volatile int tailWeightSpinSink;

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        leaveClearedInitializedContext();
        registerCurrentThreadForWallClockProfiling();

        long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
        assertTrue(token != 0, "Expected native blockEnter to arm SLEEPING state");
        try {
            Thread.sleep(300);
        } finally {
            ProfilerOwnedBlockHooks.blockExit(profiler, token);
        }

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .count();
        // Explicitly owned once-per-run filter: entry signal emits, subsequent signals are
        // suppressed until blockExit clears the owned run.
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_sampled_run")) {
            assertTrue(counters.get("wc_signals_suppressed_sampled_run") > 0,
                    "wc_signals_suppressed_sampled_run should be > 0 for a 300 ms Thread.sleep()");
        }
    }

    @Test
    public void unownedSleepingThreadIsNotExactOncePerRunSuppressed() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        leaveClearedInitializedContext();
        registerCurrentThreadForWallClockProfiling();

        Thread.sleep(300);

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .count();
        assertTrue(sampleCount >= 10,
                "Unowned Thread.sleep must not be exact once-per-run suppressed; got: " + sampleCount);
    }

    @Test
    public void unownedSleepingTailWeightIsPreserved() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Thread sleeper = new Thread(() -> {
            registerCurrentThreadForWallClockProfiling();
            try {
                for (int i = 0; i < TAIL_WEIGHT_ITERATIONS; i++) {
                    Thread.sleep(TAIL_WEIGHT_SLEEP_MILLIS);
                    long runnableUntil = System.nanoTime() + TAIL_WEIGHT_RUNNABLE_NANOS;
                    while (System.nanoTime() < runnableUntil) {
                        tailWeightSpinSink++;
                        // Brief runnable gap forces the unowned blocked state to flush.
                    }
                }
            } catch (InterruptedException ignored) {
            }
        }, TAIL_WEIGHT_THREAD);

        sleeper.start();
        sleeper.join();

        stopProfiler();

        WeightedSamples weightedSamples = weightedSamplesForThread(TAIL_WEIGHT_THREAD);
        assertTrue(weightedSamples.count > 0,
                "Expected MethodSample events for " + TAIL_WEIGHT_THREAD);
        long expectedTailContribution = TAIL_WEIGHT_ITERATIONS;
        assertTrue(weightedSamples.weight >= weightedSamples.count + expectedTailContribution,
                "Expected preserved suppressed tail weight for " + TAIL_WEIGHT_THREAD
                        + ", count=" + weightedSamples.count
                        + ", weight=" + weightedSamples.weight
                        + ", expectedTailContribution=" + expectedTailContribution);
    }

    @Test
    public void tracedSleepingThreadIsSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        Map<String, Long> countersBefore = profiler.getDebugCounters();
        profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
        try {
            Thread.sleep(300);
        } finally {
            profiler.clearTraceContext();
        }

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .count();
        assertTrue(sampleCount >= 10,
                "Expected normal MethodSample volume for traced sleep, got: " + sampleCount);

        if (countersBefore.containsKey("wc_signals_suppressed_sampled_run")) {
            long suppressedBefore = countersBefore.get("wc_signals_suppressed_sampled_run");
            long suppressedAfter = profiler.getDebugCounters()
                    .getOrDefault("wc_signals_suppressed_sampled_run", 0L);
            assertEquals(suppressedBefore, suppressedAfter,
                    "wc_signals_suppressed_sampled_run must not increment for traced sleep");
        }
    }

    @Test
    public void suppressionCounterIsZeroWhenPrecheckDisabled() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        // Stop the wallprecheck=true recording started by @BeforeEach before starting a new one.
        stopProfiler();

        Map<String, Long> before = profiler.getDebugCounters();
        if (!before.containsKey("wc_signals_suppressed_sampled_run")) {
            return; // counter not available in this build
        }
        long suppressedBefore = before.get("wc_signals_suppressed_sampled_run");

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "PrecheckTest_disabled_", ".jfr");
        profiler.execute("start," + getPrecheckDisabledProfilerCommand()
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        Thread.sleep(300);
        profiler.stop();

        long suppressedAfter = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_sampled_run", 0L);
        Files.deleteIfExists(recordingB);

        assertEquals(suppressedBefore, suppressedAfter,
                "wc_signals_suppressed_sampled_run must not increment when wallprecheck=false");
    }

    /**
     * Recreates the steady state left after a previous test activated and then cleared the trace
     * context: the native ProfiledThread still owns an initialized OTEP record, but the record is
     * cleared and invalid.
     */
    private void leaveClearedInitializedContext() {
        profiler.setTraceContext(0x7700L, 0x7701L, 0L, 0x7701L, -1, null, -1, null);
        profiler.clearTraceContext();
    }

    @Override
    protected String getProfilerCommand() {
        // This suite verifies sampling and suppression for threads outside a
        // tracing-context window. It relies on the default context-filter
        // scope (filter="0") plus each worker thread explicitly registering
        // itself via registerCurrentThreadForWallClockProfiling()/addThread().
        return "wall=1ms,wallprecheck=true";
    }

    protected String getPrecheckDisabledProfilerCommand() {
        return "wall=1ms,wallprecheck=false";
    }

    private WeightedSamples weightedSamplesForThread(String threadName) {
        long count = 0;
        long weight = 0;
        JfrEvents events = verifyEvents("datadog.MethodSample", false);
        for (JfrEvent item : events) {
            if (threadName.equals(item.getThreadName("eventThread"))) {
                count++;
                weight += item.getLong(WEIGHT, 0);
            }
        }
        return new WeightedSamples(count, weight);
    }

    private static final class WeightedSamples {
        final long count;
        final long weight;

        WeightedSamples(long count, long weight) {
            this.count = count;
            this.weight = weight;
        }
    }
}
