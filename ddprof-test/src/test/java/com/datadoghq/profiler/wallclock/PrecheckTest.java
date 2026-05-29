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

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        Thread.sleep(300);

        stopProfiler();

        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        // Once-per-run filter: entry signal emits, subsequent signals are suppressed.
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_sampled_run")) {
            assertTrue(counters.get("wc_signals_suppressed_sampled_run") > 0,
                    "wc_signals_suppressed_sampled_run should be > 0 for a 300 ms Thread.sleep()");
        }
    }

    @Test
    public void suppressionCounterIsZeroWhenPrecheckDisabled() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        // Run the same 300ms sleep but with wallprecheck=false in a second recording.
        Map<String, Long> before = profiler.getDebugCounters();
        if (!before.containsKey("wc_signals_suppressed_sampled_run")) {
            return; // counter not available in this build
        }
        long suppressedBefore = before.get("wc_signals_suppressed_sampled_run");

        Path recordingB = Files.createTempFile(Paths.get("/tmp/recordings"),
                "PrecheckTest_disabled_", ".jfr");
        profiler.execute("start,wall=1ms,wallprecheck=false,filter=0"
                + ",attributes=tag1;tag2;tag3,jfr,file=" + recordingB.toAbsolutePath());
        Thread.sleep(300);
        profiler.stop();

        long suppressedAfter = profiler.getDebugCounters()
                .getOrDefault("wc_signals_suppressed_sampled_run", 0L);
        Files.deleteIfExists(recordingB);

        assertEquals(suppressedBefore, suppressedAfter,
                "wc_signals_suppressed_sampled_run must not increment when wallprecheck=false");
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallprecheck=true";
    }
}
