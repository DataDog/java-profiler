package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;
import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies Approach 1: the timer loop reads osThreadState() before sending SIGVTALRM and
 * skips threads in SLEEPING/MONITOR_WAIT/CONDVAR_WAIT/OBJECT_WAIT states (wallprecheck=true,
 * the default). A thread parked for 300 ms at a 1 ms interval should receive nearly zero
 * signals, while SleepTest (wallprecheck=false) confirms sampling still works when disabled.
 */
public class PrecheckTest extends AbstractProfilerTest {

    @Test
    public void testSleepingThreadIsNotSampled() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();

        // Park for 300 ms — enough for ~300 timer ticks at 1 ms interval.
        LockSupport.parkNanos(300_000_000L);

        stopProfiler();

        // The timer thread reads osThreadState() and skips the SIGVTALRM for sleeping threads,
        // so sample count should be near zero (a handful may slip through at park entry/exit).
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        // Confirm the suppression counter incremented (only available in COUNTERS-enabled builds).
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_skipped_sleeping")) {
            assertTrue(counters.get("wc_signals_skipped_sleeping") > 0,
                    "wc_signals_skipped_sleeping should be > 0 for a 300 ms park");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";  // wallprecheck=true by default
    }
}
