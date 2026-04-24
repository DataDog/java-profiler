package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies the wallprecheck feature (wallprecheck=true, the default): the timer loop reads
 * osThreadState() before sending SIGVTALRM and skips threads in SLEEPING state (Thread.sleep).
 * A thread sleeping for 300 ms at a 1 ms interval should receive nearly zero signals.
 *
 * <p>Runs only on JDK 11+: JDK 8 HotSpot often does not expose a consistent SLEEPING OSThread
 * state for Thread.sleep in vmStructs, so precheck cannot suppress signals reliably on JDK 8 CI.
 */
public class PrecheckTest extends AbstractProfilerTest {

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        // Wall precheck uses VMThread::osThreadState() -> SLEEPING (wallClock.cpp). JDK 8
        // frequently misreports vs JDK 11+ across vendors/libcs (Oracle, musl, glibc), so
        // nearly all wall ticks still signal — CI sees hundreds of MethodSamples.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        // Sleep for 300 ms — enough for ~300 timer ticks at 1 ms interval.
        Thread.sleep(300);

        stopProfiler();

        // The timer thread reads osThreadState() and skips SIGVTALRM for SLEEPING threads,
        // so sample count should be near zero (a handful may slip through at sleep entry/exit).
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        // Confirm the suppression counter incremented (only available in COUNTERS-enabled builds).
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_skipped_sleeping")) {
            assertTrue(counters.get("wc_signals_skipped_sleeping") > 0,
                    "wc_signals_skipped_sleeping should be > 0 for a 300 ms Thread.sleep()");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";  // wallprecheck=true by default
    }
}
