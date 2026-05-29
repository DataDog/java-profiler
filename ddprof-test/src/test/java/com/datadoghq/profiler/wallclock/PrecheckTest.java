package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;

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

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,wallprecheck=true";
    }
}
