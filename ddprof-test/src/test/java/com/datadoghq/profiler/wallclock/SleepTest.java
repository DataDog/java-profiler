package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class SleepTest extends AbstractProfilerTest {

    @Test
    public void testSleep() throws InterruptedException {
        registerCurrentThreadForWallClockProfiling();
        long ts = System.nanoTime();
        do {
            Thread.sleep(1000);
        } while (System.nanoTime() - ts < 1_000_000_000L);
        stopProfiler();
        assertTrue(verifyEvents("datadog.MethodSample").getAggregate(Aggregators.count()).longValue() > 90);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }
}
