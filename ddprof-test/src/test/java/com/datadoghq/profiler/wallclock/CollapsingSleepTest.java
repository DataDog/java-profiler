package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import java.util.concurrent.locks.LockSupport;

public class CollapsingSleepTest extends AbstractProfilerTest {

    @Test
    public void testSleep() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        long ts = System.nanoTime();
        long waitTime = 1_000_000_000L; // 1mil ns == 1s
        do {
            LockSupport.parkNanos(waitTime);
            waitTime -= (System.nanoTime() - ts);
            ts = System.nanoTime();
        } while (waitTime > 1_000);
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        assertTrue(events.hasItems());
        assertTrue(events.getAggregate(Aggregators.sum(WEIGHT)).longValue() > 900);
        assertTrue(events.getAggregate(Aggregators.count()).longValue() > 9);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }
}
