/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

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
    private static final IAttribute<IQuantity> WEIGHT =
            Attribute.attr("weight", "Sample weight", UnitLookup.NUMBER);
    private static volatile int tailWeightSpinSink;

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        leaveClearedInitializedContext();
        registerCurrentThreadForWallClockProfiling();

        long token = profiler.blockEnter(OSTHREAD_STATE_SLEEPING);
        assertTrue(token != 0, "Expected native blockEnter to arm SLEEPING state");
        try {
            Thread.sleep(300);
        } finally {
            profiler.blockExit(token);
        }

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
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
                .getAggregate(Aggregators.count()).longValue();
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

        profiler.setContext(0x5100L, 0x5101L, 0L, 0x5101L);
        try {
            Thread.sleep(300);
        } finally {
            profiler.clearContext();
        }

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount >= 10,
                "Expected normal MethodSample volume for traced sleep, got: " + sampleCount);

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_sampled_run")) {
            assertEquals(0L, counters.get("wc_signals_suppressed_sampled_run"),
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
     * Recreates the steady state left after a previous test initialized and then removed the Java
     * ThreadContext: the native ProfiledThread still owns an initialized OTEP record, but the
     * record is cleared and invalid.
     */
    private void leaveClearedInitializedContext() {
        profiler.setContext(0x7700L, 0x7701L, 0L, 0x7701L);
        profiler.clearContext();
        profiler.resetThreadContext();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallprecheck=true";
    }

    protected String getPrecheckDisabledProfilerCommand() {
        return "wall=1ms,wallprecheck=false,filter=0";
    }

    private WeightedSamples weightedSamplesForThread(String threadName) {
        long count = 0;
        long weight = 0;
        IItemCollection events = verifyEvents("datadog.MethodSample", false);
        for (IItemIterable batch : events) {
            IMemberAccessor<String, IItem> threadNameAccessor =
                    JdkAttributes.EVENT_THREAD_NAME.getAccessor(batch.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(batch.getType());
            if (threadNameAccessor == null || weightAccessor == null) {
                continue;
            }
            for (IItem item : batch) {
                if (threadName.equals(threadNameAccessor.getMember(item))) {
                    count++;
                    weight += weightAccessor.getMember(item).longValue();
                }
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
