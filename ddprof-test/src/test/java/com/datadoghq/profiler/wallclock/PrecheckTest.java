package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies once-per-run signal suppression (opt-in via {@code wallprecheck=true}): the wall-clock
 * SIGVTALRM handler reads {@code VMThread::osThreadState()} and arms a per-thread filter on the
 * first signal of a {@code SLEEPING} / {@code CONDVAR_WAIT} run. The first signal emits a
 * {@code MethodSample} (so the parked thread's stack is captured); subsequent signals on the same
 * thread are suppressed until the OS state leaves the skip set. Legacy JDKs report {@code
 * Thread.sleep} as {@code SLEEPING}; JDK 21+ uses a condvar wait path for sleep (often {@code
 * CONDVAR_WAIT}), same broad category as {@code LockSupport.park}.
 *
 * <p>A thread in {@code Thread.sleep} for 300 ms at a 1 ms wall interval should produce a handful
 * of {@code MethodSample} events (one entry sample plus residual boundary samples), not ~300. The
 * suppression counter {@code wc_signals_suppressed_sampled_run} accounts for the dropped signals.
 *
 * <p>Runs only on JDK 11+: JDK 8 HotSpot often does not expose consistent OSThread states for sleep
 * in vmStructs, so the once-per-run filter cannot engage reliably on JDK 8 CI.
 *
 * <p>CI should execute this test on at least one JDK 21+ runner so {@code CONDVAR_WAIT}-based sleep
 * suppression stays covered alongside JDK 11–20 ({@code SLEEPING}) configurations.
 */
public class PrecheckTest extends AbstractProfilerTest {

    @Test
    public void testSleepingThreadIsNotSampled() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        // Wall precheck reads VMThread::osThreadState() -> SLEEPING / CONDVAR_WAIT (wallClock.cpp).
        // JDK 8 frequently misreports vs JDK 11+ across vendors/libcs (Oracle, musl, glibc), so
        // nearly every wall tick still produces a MethodSample on JDK 8.
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        registerCurrentThreadForWallClockProfiling();

        // Sleep for 300 ms — without suppression we'd see ~300 ticks at 1 ms interval. With the
        // once-per-run filter, only the entry signal of the sleep run emits a MethodSample.
        Thread.sleep(300);

        stopProfiler();

        // Once-per-run filter: handler emits at the first SIGVTALRM of the SLEEPING / CONDVAR_WAIT
        // run, then suppresses the rest. We expect a small handful (entry + boundary jitter), not 300.
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount < 10,
                "Expected nearly no MethodSample events for a sleeping thread with wallprecheck=true, got: " + sampleCount);

        // Confirm the suppression counter incremented (only available in COUNTERS-enabled builds).
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
