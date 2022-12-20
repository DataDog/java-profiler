package com.datadoghq.profiler.context;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.JfrAttributes;

import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class ContextTest extends AbstractProfilerTest {

    @Test
    public void testReadContext() throws Exception {
        int tid = profiler.getNativeThreadId();
        profiler.addThread(tid);
        profiler.setContext(tid, 42, 84);
        profiler.setPoolParallelism(tid, 89);
        // sleep to get some wall samples
        Thread.sleep(10);
        // do some work to get some cpu samples
        long value = 0;
        for (int i = 0; i < 10_000_000; i++) {
           value ^= ThreadLocalRandom.current().nextLong();
        }
        System.err.println(value);
        Thread.sleep(10);
        stopProfiler();
        // call after stopping the profiler to avoid breaking the assert below
        profiler.clearPoolParallelism(tid);
        IItemCollection cpuSamples = verifyEvents("datadog.ExecutionSample");
        for (IItemIterable cpuSample : cpuSamples) {
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(cpuSample.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(cpuSample.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor = JfrAttributes.EVENT_THREAD.getAccessor(cpuSample.getType());
            for (IItem sample : cpuSample) {
                if (threadAccessor.getMember(sample).getThreadName().equals(Thread.currentThread().getName())) {
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                    assertEquals(84, rootSpanId);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    assertEquals(42, spanId);
                }
            }
        }
        IItemCollection wallSamples = verifyEvents("datadog.MethodSample");
        for (IItemIterable wallSample : wallSamples) {
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(wallSample.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(wallSample.getType());
            IMemberAccessor<IQuantity, IItem> parallelismAccessor = PARALLELISM.getAccessor(wallSample.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor = JfrAttributes.EVENT_THREAD.getAccessor(wallSample.getType());
            for (IItem sample : wallSample) {
                if (threadAccessor.getMember(sample).getThreadName().equals(Thread.currentThread().getName())) {
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                    assertEquals(84, rootSpanId);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    assertEquals(42, spanId);
                    int parallelism = (int) parallelismAccessor.getMember(sample).longValue();
                    assertEquals(89, parallelism);
                }
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms,wall=~1ms";
    }
}
