package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

public class QueueingWallTimeTest extends AbstractProfilerTest {

    @Test
    public void test() {
        method1(201);
        method2(300_001);
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        long totalWeight = 0;
        for (IItemIterable wallclockSamples : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(wallclockSamples.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String stackTrace = stackTraceAccessor.getMember(sample);
                long weight = weightAccessor.getMember(sample).longValue();
                if (stackTrace.contains("method1")) {
                    assertEquals(20, weight);
                    assertEquals("STATE_QUEUEING", stateAccessor.getMember(sample));
                    totalWeight += weight;
                } else if (stackTrace.contains("method2")) {
                    assertEquals(30, weight);
                    assertEquals("STATE_QUEUEING", stateAccessor.getMember(sample));
                    totalWeight += weight;
                }
            }
        }
        assertEquals(50, totalWeight);
    }

    void method1(long millis) {
        profiler.recordQueueingTime(millis, TimeUnit.MILLISECONDS);
    }

    void method2(long micros) {
        profiler.recordQueueingTime(micros, TimeUnit.MICROSECONDS);
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=10ms,filter=0";
    }
}
