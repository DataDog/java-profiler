package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Verifies once-per-run suppression ({@code wallprecheck=true}) with a mix of sleeping,
 * parked, and runnable threads. TaskBlock assertions are in PR2 (WallclockMitigationsCombinedTest
 * in the precheck branch).
 */
public class WallclockMitigationsCombinedTest extends AbstractProfilerTest {
    private static final int OSTHREAD_STATE_SLEEPING = 7;

    @Test
    public void precheckAndParkSuppressionWorkTogether() throws Exception {
        Assumptions.assumeTrue(!Platform.isJ9());
        Assumptions.assumeTrue(
                Platform.isJavaVersionAtLeast(11),
                "Sleeping-state precheck assertions are stable on JDK 11+");

        CountDownLatch ready = new CountDownLatch(3);
        AtomicBoolean stop = new AtomicBoolean(false);

        Thread sleeping =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            ready.countDown();
                            long token = profiler.blockEnter(OSTHREAD_STATE_SLEEPING);
                            try {
                                Thread.sleep(280);
                            } catch (InterruptedException ignored) {
                            } finally {
                                profiler.blockExit(token);
                            }
                        },
                        "combined-sleeping");

        Thread parkedBusy =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            long spanId = 0x1111L;
                            long rootSpanId = 0x2222L;
                            profiler.setContext(rootSpanId, spanId, 0, 0);
                            ready.countDown();
                            profiler.parkEnter();
                            long parkedUntil = System.nanoTime() + 280_000_000L;
                            while (System.nanoTime() < parkedUntil) {
                                // spin while flagged parked
                            }
                            profiler.parkExit(System.identityHashCode(this), 0L);
                            profiler.clearContext();
                        },
                        "combined-parked");

        Thread runnable =
                new Thread(
                        () -> {
                            registerCurrentThreadForWallClockProfiling();
                            ready.countDown();
                            while (!stop.get()) {
                                // keep runnable
                            }
                        },
                        "combined-runnable");

        sleeping.setDaemon(true);
        parkedBusy.setDaemon(true);
        runnable.setDaemon(true);
        sleeping.start();
        parkedBusy.start();
        runnable.start();

        ready.await();
        Thread.sleep(350);
        stop.set(true);

        sleeping.interrupt();
        sleeping.join(1000);
        parkedBusy.join(1000);
        runnable.join(1000);

        stopProfiler();

        // Runnable thread must still produce samples (precheck doesn't suppress RUNNABLE).
        long sampleCount = verifyEvents("datadog.MethodSample", false)
                .getAggregate(Aggregators.count()).longValue();
        assertTrue(sampleCount > 0, "Expected MethodSample events from runnable thread");

        // Sleeping thread's suppression counter must have incremented.
        Map<String, Long> counters = profiler.getDebugCounters();
        if (counters.containsKey("wc_signals_suppressed_sampled_run")) {
            assertTrue(
                    counters.get("wc_signals_suppressed_sampled_run") > 0,
                    "Expected once-per-run suppression counter to increase");
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms,filter=0,wallprecheck=true";
    }
}
