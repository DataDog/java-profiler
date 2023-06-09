package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class WallclockThreadFilterTest extends AbstractProfilerTest {

    @Test
    public void test() throws InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9() || (Platform.isJ9() && Platform.isJavaVersion(8)));
        registerCurrentThreadForWallClockProfiling();
        Thread.sleep(100);
        stopProfiler();
        IItemCollection events = verifyEvents("datadog.MethodSample");
        for (IItemIterable wallclockSamples : events) {
            IMemberAccessor<String, IItem> javaThreadNameAccessor = JdkAttributes.EVENT_THREAD_NAME
                    .getAccessor(wallclockSamples.getType());
            IMemberAccessor<IQuantity, IItem> javaThreadIdAccessor = JdkAttributes.EVENT_THREAD_ID
                    .getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String javaThreadName = javaThreadNameAccessor.getMember(sample);
                assertEquals(Thread.currentThread().getName(), javaThreadName);
                long javaThreadId = javaThreadIdAccessor.getMember(sample).longValue();
                assertEquals(Thread.currentThread().getId(), javaThreadId);
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms,filter=0";
    }
}
