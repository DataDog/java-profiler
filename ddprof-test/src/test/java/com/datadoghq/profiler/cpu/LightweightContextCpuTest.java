package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.context.Tracing;
import org.junit.jupiter.api.Assumptions;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.*;

import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class LightweightContextCpuTest extends AbstractProfilerTest {

    private ProfiledCode profiledCode;

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    public void test() throws ExecutionException, InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();
        Set<Long> sampledSpanIds = profiledCode.allSampledSpanIds();
        IItemCollection events = verifyEvents("datadog.ExecutionSample");

        int numNonZeroContexts = 0;
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(cpuSamples.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(cpuSamples.getType());
            IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                assertNull(stackTrace);
                long spanId = spanIdAccessor.getMember(sample).longValue();
                long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                numNonZeroContexts += (spanId != 0 && rootSpanId != 0 ? 1 : 0);
                if (spanId > 0) {
                    assertTrue(sampledSpanIds.contains(spanId));
                }
                String state = stateAccessor.getMember(sample);
                assertDoesNotThrow(() -> Thread.State.valueOf(state));
                assertEquals(Thread.State.RUNNABLE, Thread.State.valueOf(state));
            }
        }
        assertTrue(numNonZeroContexts > 0, "no context");
        Map<String, Long> debugCounters = profiler.getDebugCounters();
        // these are here to verify these counters produce reasonable values so they can be used for memory leak detection
        assertInRange(debugCounters.get("calltrace_storage_traces"), 10, 10000);
        assertInRange(debugCounters.get("calltrace_storage_bytes"), 1024, 8 * 1024 * 1024);
        // this allocator is only used for calltrace storage and eagerly allocates chunks of 8MiB
        assertEquals(8 * 1024 * 1024, debugCounters.get("linear_allocator_bytes"));
        assertEquals(1, debugCounters.get("linear_allocator_chunks"));
    }

    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=100us,lightweight=yes";
    }
}
