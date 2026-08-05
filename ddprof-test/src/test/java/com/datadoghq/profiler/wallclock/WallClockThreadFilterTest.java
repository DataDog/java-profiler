package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;

public class WallClockThreadFilterTest extends AbstractProfilerTest {

    @RetryingTest(5)
    public void test() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        registerCurrentThreadForWallClockProfiling();
        Thread.sleep(100);
        stopProfiler();
        JfrEvents events = verifyEvents("datadog.MethodSample");
        for (JfrEvent sample : events) {
            String javaThreadName = sample.getThreadName("eventThread");
            assertEquals(Thread.currentThread().getName(), javaThreadName);
            long javaThreadId = sample.getThreadJavaId("eventThread");
            assertEquals(Thread.currentThread().getId(), javaThreadId);
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0";
    }
}
