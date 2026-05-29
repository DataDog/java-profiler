package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;

import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Verifies that once-per-run suppression ({@code wallprecheck=true}) and the park API
 * ({@code parkEnter}/{@code parkExit}) work together correctly.
 */
public class WallclockMitigationsCombinedTest extends AbstractProfilerTest {

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
                            try {
                                Thread.sleep(280);
                            } catch (InterruptedException ignored) {
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

        IItemCollection taskBlocks = verifyEvents("datadog.TaskBlock");
        assertTrue(
                taskBlocks.getAggregate(Aggregators.count()).longValue() > 0,
                "Expected TaskBlock events from parked interval");

        IItemCollection methodSamples = verifyEvents("datadog.MethodSample");
        assertTrue(
                methodSamples.getAggregate(Aggregators.count()).longValue() > 0,
                "Expected runnable MethodSample events while mitigations are enabled");

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
