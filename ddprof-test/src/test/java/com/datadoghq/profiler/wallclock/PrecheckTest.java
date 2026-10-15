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
 * Verifies lifecycle-owned signal suppression ({@code wallprecheck=true}): a sleeping thread
 * should produce at most boundary-race {@code MethodSample} events, not ~300.
 * Requires JDK 11+ — JDK 8 HotSpot reports inconsistent OSThread states for sleep.
 */
public class PrecheckTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;
    private static final int POOL_WORKERS = 4;
    private static final long POOL_SLEEP_MILLIS = 300;
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

        long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
        assertTrue(token != 0, "Expected native blockEnter to arm SLEEPING state");
        try {
            Thread.sleep(300);
        } finally {
            ProfilerOwnedBlockHooks.blockExit(profiler, token);
        }

        stopProfiler();

        long sampleCount = samplesForThread(Thread.currentThread().getName());
        // Lifecycle ownership suppresses deliberate signals from blockEnter until blockExit.
        // A few boundary-race samples remain possible.
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_owned_block")) {
            assertTrue(counters.get("wc_signals_suppressed_owned_block") > 0,
                    "wc_signals_suppressed_owned_block should be > 0 for a 300 ms Thread.sleep()");
        }
    }

    @Test
    public void testBlockEnterRejectedWithActiveTraceContext() {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
        try {
            long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
            assertEquals(0L, token,
                    "Expected blockEnter to reject arming while an active trace context is set");
        } finally {
            profiler.clearTraceContext();
        }
    }

    /**
     * Verifies that {@code samplePoolSize} in {@code datadog.WallClockSamplingEpoch} still counts
     * threads whose owned blocked run is already suppressed. The pool size is taken before the
     * timer rejects those threads, so it keeps counting every candidate.
     *
     * @throws InterruptedException if a worker is interrupted
     */
    @Test
    public void samplePoolSizeCountsSuppressedThreads() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        // Fewer workers than the default reservoir (16 threads per tick), so every
        // unsuppressed worker is signaled and armed on its first tick.
        Thread[] workers = new Thread[POOL_WORKERS];
        for (int i = 0; i < POOL_WORKERS; i++) {
            workers[i] = new Thread(() -> {
                long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);
                try {
                    Thread.sleep(POOL_SLEEP_MILLIS);
                } catch (InterruptedException ignored) {
                } finally {
                    ProfilerOwnedBlockHooks.blockExit(profiler, token);
                }
            }, "precheck-pool-" + i);
            workers[i].start();
        }
        for (Thread worker : workers) {
            worker.join();
        }

        stopProfiler();

        // While all workers sit in suppressed runs, each tick suppresses every one of them.
        // Before the fix those ticks reported a pool size of 0.
        boolean sawFullPoolWhileSuppressing = false;
        for (JfrEvent epoch : verifyEvents("datadog.WallClockSamplingEpoch")) {
            if (epoch.getLong("numSuppressedOwnedBlock", 0) >= POOL_WORKERS
                    && epoch.getLong("samplePoolSize", 0) >= POOL_WORKERS) {
                sawFullPoolWhileSuppressing = true;
                break;
            }
        }
        assertTrue(sawFullPoolWhileSuppressing,
                "Expected an epoch that suppressed all " + POOL_WORKERS
                        + " workers while still counting them in samplePoolSize");
    }

    @Test
    public void unownedSleepingThreadIsNotExactOncePerRunSuppressed() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        leaveClearedInitializedContext();

        Thread.sleep(300);

        stopProfiler();

        long sampleCount = samplesForThread(Thread.currentThread().getName());
        assertTrue(sampleCount > 0,
                "Unowned Thread.sleep must remain sampled; got: " + sampleCount);
        Map<String, Long> counters = profiler.getDebugCounters();
        assertTrue(counters.getOrDefault("wc_unowned_blocked_recorded", 0L) > 0,
                "Expected the weighted unowned-block fallback to record samples");
        assertTrue(counters.getOrDefault("wc_unowned_blocked_suppressed", 0L) > 0,
                "Expected the weighted unowned-block fallback to suppress intermediate samples");
    }

    @Test
    public void unownedSleepingTailWeightIsPreserved() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Thread sleeper = new Thread(() -> {
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
        assertTrue(weightedSamples.weight > weightedSamples.count,
                "Expected preserved suppressed tail weight for " + TAIL_WEIGHT_THREAD
                        + ", count=" + weightedSamples.count
                        + ", weight=" + weightedSamples.weight);
        assertTrue(profiler.getDebugCounters()
                        .getOrDefault("wc_unowned_blocked_suppressed", 0L) > 0,
                "Expected unowned blocked samples to be suppressed and represented by weight");
    }

    @Test
    public void tracedSleepingThreadIsSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        Map<String, Long> countersBefore = profiler.getDebugCounters();
        profiler.setTraceContext(0x5100L, 0x5101L, 0L, 0x5101L, -1, null, -1, null);
        try {
            Thread.sleep(300);
        } finally {
            profiler.clearTraceContext();
        }

        stopProfiler();

        long sampleCount = samplesForThread(Thread.currentThread().getName());
        assertTrue(sampleCount >= 10,
                "Expected normal MethodSample volume for traced sleep, got: " + sampleCount);

        if (countersBefore.containsKey("wc_signals_suppressed_owned_block")) {
            long suppressedBefore = countersBefore.get("wc_signals_suppressed_owned_block");
            long suppressedAfter = profiler.getDebugCounters()
                    .getOrDefault("wc_signals_suppressed_owned_block", 0L);
            assertEquals(suppressedBefore, suppressedAfter,
                    "wc_signals_suppressed_owned_block must not increment for traced sleep");
        }
    }

    @Test
    public void suppressionCounterIsZeroWhenPrecheckDisabled() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));

        // Stop the wallprecheck=true recording started by @BeforeEach before starting a new one.
        stopProfiler();

        Map<String, Long> before = profiler.getDebugCounters();
        if (!before.containsKey("wc_signals_suppressed_owned_block")) {
            return; // counter not available in this build
        }
        long suppressedBefore = before.get("wc_signals_suppressed_owned_block");

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "PrecheckTest_disabled_", ".jfr");
        profiler.execute("start," + getPrecheckDisabledProfilerCommand()
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        Thread.sleep(300);
        profiler.stop();

        long suppressedAfter = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_owned_block", 0L);
        Files.deleteIfExists(recordingB);

        assertEquals(suppressedBefore, suppressedAfter,
                "wc_signals_suppressed_owned_block must not increment when wallprecheck=false");
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
        // tracing-context window. Owned-block suppression only applies to the
        // unfiltered wall-clock scope (explicit empty filter=), and only while
        // the thread stays outside the context window, so threads must not
        // call addThread().
        return "wall=1ms,filter=,wallprecheck=true";
    }

    protected String getPrecheckDisabledProfilerCommand() {
        return "wall=1ms,filter=,wallprecheck=false";
    }

    private long samplesForThread(String threadName) {
        long count = 0;
        JfrEvents events = verifyEvents("datadog.MethodSample", false);
        for (JfrEvent item : events) {
            if (threadName.equals(item.getThreadName("eventThread"))) {
                count++;
            }
        }
        return count;
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
