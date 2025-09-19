package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;

import java.util.concurrent.locks.LockSupport;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class SleepTest extends AbstractProfilerTest {

    @Test
    public void testSleep() {
        registerCurrentThreadForWallClockProfiling();
        long ts = System.nanoTime();
        long waitTime = 1_000_000_000L; // 1mil ns == 1s
        do {
            LockSupport.parkNanos(waitTime);
            waitTime -= (System.nanoTime() - ts);
            ts = System.nanoTime();
        } while (waitTime > 1_000);
        stopProfiler();
        assertTrue(verifyEvents("datadog.MethodSample").getAggregate(Aggregators.count()).longValue() > 90);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=1ms";
    }
}
