package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;

import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junitpioneer.jupiter.RetryingTest;

public class CollapsingSleepTest extends AbstractProfilerTest {

    @RetryingTest(3)
    public void testSleep() throws InterruptedException {
        registerCurrentThreadForWallClockProfiling();
        Thread.sleep(1000);
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        assertTrue(events.hasItems());
        assertTrue(events.getAggregate(Aggregators.sum(WEIGHT)).longValue() > 900);
        assertTrue(events.getAggregate(Aggregators.count()).longValue() > 9);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~10ms";
    }
}
