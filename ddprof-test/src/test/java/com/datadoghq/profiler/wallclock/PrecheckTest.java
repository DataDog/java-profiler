/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

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
}
