package com.datadoghq.profiler.cpu;

import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutionException;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.CStackInjector;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import com.datadoghq.profiler.AbstractProfilerTest;
import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import com.datadoghq.profiler.Platform;

public class ContextCpuTest extends CStackAwareAbstractProfilerTest {

    private ProfiledCode profiledCode;

    public ContextCpuTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected void before() {
        profiledCode = new ProfiledCode(profiler);
    }

    @RetryTest(10)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws ExecutionException, InterruptedException {
        Assumptions.assumeTrue(!Platform.isJ9());
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            profiledCode.method1(id);
        }
        stopProfiler();

        verifyCStackSettings();

        Set<Long> method1SpanIds = profiledCode.spanIdsForMethod("method1Impl");
        Set<Long> method2SpanIds = profiledCode.spanIdsForMethod("method2Impl");
        Set<Long> method3SpanIds = profiledCode.spanIdsForMethod("method3Impl");
        IItemCollection events = verifyEvents("datadog.ExecutionSample");

        // on mac the usage of itimer to drive the sampling provides very unreliable outputs
        if (!Platform.isMac()) {

            // we have 100 method1, method2, and method3 calls, but can't guarantee we sampled them all
            long method1Weight = 0;
            long method2Weight = 0;
            long method3Weight = 0;
            long totalWeight = 0;
            for (IItemIterable cpuSamples : events) {
                IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
                IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(cpuSamples.getType());
                IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(cpuSamples.getType());
                IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(cpuSamples.getType());
                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                    String state = stateAccessor.getMember(sample);
                    assertDoesNotThrow(() -> Thread.State.valueOf(state));
                    assertEquals(Thread.State.RUNNABLE, Thread.State.valueOf(state));
                    if (stackTrace.contains("method3Impl")) {
                        // method3 is scheduled after method2, and method1 blocks on it, so spanId == rootSpanId + 2
                        if (spanId > 0) {
                            assertEquals(rootSpanId + 2, spanId, stackTrace);
                            assertTrue(method3SpanIds.contains(spanId), stackTrace);
                            method3Weight += 1;
                        }
                    } else if (stackTrace.contains("method2Impl")) {
                        // method2 is called next, so spanId == rootSpanId + 1
                        if (spanId > 0) {
                            assertEquals(rootSpanId + 1, spanId, stackTrace);
                            assertTrue(method2SpanIds.contains(spanId), stackTrace);
                            method2Weight += 1;
                        }
                    } else if (stackTrace.contains("method1Impl")
                            && !stackTrace.contains("method2") && !stackTrace.contains("method3")) {
                        // need to check this after method2 because method1 calls method2
                        // it's the root so spanId == rootSpanId
                        assertEquals(rootSpanId, spanId, stackTrace);
                        assertTrue(spanId == 0 || method1SpanIds.contains(spanId), stackTrace);
                        method1Weight += 1;
                    }
                    totalWeight++;
                }
            }
            assertInRange(method1Weight / (double) totalWeight, 0.1, 0.6);
            assertInRange(method2Weight / (double) totalWeight, 0.1, 0.6);
            assertInRange(method3Weight / (double) totalWeight, 0.05, 0.6);
        }
        Map<String, Long> debugCounters = profiler.getDebugCounters();
        // these are here to verify these counters produce reasonable values so they can be used for memory leak detection
        assertInRange(debugCounters.get("calltrace_storage_traces"), 1, 100);
        assertInRange(debugCounters.get("calltrace_storage_bytes"), 1024, 8 * 1024 * 1024);
        // this allocator is only used for calltrace storage and eagerly allocates chunks of 8MiB
        assertEquals(0, debugCounters.get("linear_allocator_bytes"));
        assertEquals(0, debugCounters.get("linear_allocator_chunks"));
    }



    @Override
    protected void after() throws Exception {
        profiledCode.close();
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }
}
