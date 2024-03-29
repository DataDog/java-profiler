package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.Aggregators;
import org.openjdk.jmc.common.item.IItemCollection;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

public class CollapsingSleepTest extends AbstractProfilerTest {

    @Test
    public void testSleep() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
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
