package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies OS-thread-state precheck ({@code wallprecheck=true}, the default): the wall-clock timer
 * thread reads {@code VMThread::osThreadState()} before {@code SIGVTALRM} and skips sending the
 * signal when HotSpot reports {@code SLEEPING} or {@code CONDVAR_WAIT}. Legacy JDKs report {@code
 * Thread.sleep} as {@code SLEEPING}; JDK 21+ uses a condvar wait path for sleep (often {@code
 * CONDVAR_WAIT}), same broad category as {@code LockSupport.park}.
 *
 * <p>A thread in {@code Thread.sleep} for 300 ms at a 1 ms wall interval should receive nearly zero
 * wall samples (handful at sleep boundaries).
 *
 * <p>Runs only on JDK 11+: JDK 8 HotSpot often does not expose consistent OSThread states for sleep
 * in vmStructs, so precheck cannot suppress signals reliably on JDK 8 CI.
 */
public class PrecheckTest extends AbstractProfilerTest {

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        // Wall precheck uses VMThread::osThreadState() -> SLEEPING / CONDVAR_WAIT (wallClock.cpp).
        // JDK 8 frequently misreports vs JDK 11+ across vendors/libcs (Oracle, musl, glibc), so
        // nearly all wall ticks still signal — CI sees hundreds of MethodSamples.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        // Sleep for 300 ms — enough for ~300 timer ticks at 1 ms interval.
        Thread.sleep(300);

        stopProfiler();

        // Timer thread skips SIGVTALRM when OS state is SLEEPING or CONDVAR_WAIT (sleep/park paths).
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        // Confirm the suppression counter incremented (only available in COUNTERS-enabled builds).
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_skipped_precheck_os")) {
            assertTrue(counters.get("wc_signals_skipped_precheck_os") > 0,
                    "wc_signals_skipped_precheck_os should be > 0 for a 300 ms Thread.sleep()");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";  // wallprecheck=true by default
    }
}
