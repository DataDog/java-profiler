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
    private static final long PARK_NANOS = 2_000_000_000L;
    private static final long MIN_COLLAPSED_WEIGHT = 700L;
    private static final long MIN_SAMPLE_COUNT = 9L;

    @Test
    public void testSleep() {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        long ts = System.nanoTime();
        long waitTime = PARK_NANOS;
        do {
            LockSupport.parkNanos(waitTime);
            waitTime -= (System.nanoTime() - ts);
            ts = System.nanoTime();
        } while (waitTime > 1_000);
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        assertTrue(events.hasItems());
        long collapsedWeight = events.getAggregate(Aggregators.sum(WEIGHT)).longValue();
        long sampleCount = events.getAggregate(Aggregators.count()).longValue();
        assertTrue(collapsedWeight >= MIN_COLLAPSED_WEIGHT,
                "collapsed wall-clock weight was " + collapsedWeight);
        assertTrue(sampleCount > MIN_SAMPLE_COUNT,
                "wall-clock MethodSample count was " + sampleCount);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }
}
