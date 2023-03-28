package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.context.ContextExecutor;
import com.datadoghq.profiler.context.Tracing;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
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
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class ContextCpuTest extends AbstractProfilerTest {

    private static volatile long sink;
    private ContextExecutor executor;

    private Map<String, List<Long>> methodsToSpanIds;

    @Override
    protected void before() {
        executor = new ContextExecutor(1, profiler);
        methodsToSpanIds = new ConcurrentHashMap<>();
    }

    @RetryingTest(10)
    public void test() throws ExecutionException, InterruptedException {
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            method1(id);
        }
        stopProfiler();
        Set<Long> method1SpanIds = new HashSet<>(methodsToSpanIds.get("method1Impl"));
        Set<Long> method2SpanIds = new HashSet<>(methodsToSpanIds.get("method2Impl"));
        Set<Long> method3SpanIds = new HashSet<>(methodsToSpanIds.get("method3Impl"));
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
                for (IItem sample : cpuSamples) {
                    String stackTrace = frameAccessor.getMember(sample);
                    long spanId = spanIdAccessor.getMember(sample).longValue();
                    long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
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
    }

    private static void assertInRange(double value, double min, double max) {
        assertTrue(value >= min && value <= max, value + " not in (" + min + "," + max + ")");
    }

    public void method1(int id) throws ExecutionException, InterruptedException {
        try (Tracing.Context context = Tracing.newContext(() -> id, profiler)) {
            method1Impl(id, context);
        }
    }

    public void method1Impl(int id, Tracing.Context context) throws ExecutionException, InterruptedException {
        burnCycles();
        Future<?> wait = executor.submit(() -> method3(id));
        method2(id);
        wait.get();
        record("method1Impl", context);
    }

    public void method2(long id) {
        try (Tracing.Context context = Tracing.newContext(() -> id + 1, profiler)) {
            method2Impl(context);
        }
    }

    public void method2Impl(Tracing.Context context) {
        burnCycles();
        record("method2Impl", context);
    }

    public void method3(long id) {
        try (Tracing.Context context = Tracing.newContext(() -> id + 2, profiler)) {
            method3Impl(context);
        }
    }

    public void method3Impl(Tracing.Context context) {
        burnCycles();
        record("method3Impl", context);
    }


    private void record(String methodName, Tracing.Context context) {
        methodsToSpanIds.computeIfAbsent(methodName, k -> new CopyOnWriteArrayList<>())
                .add(context.getSpanId());
    }

    private void burnCycles() {
        long blackhole = sink;
        for (int i = 0; i < 1_000_000; i++) {
            blackhole ^= ThreadLocalRandom.current().nextLong();
        }
        sink = blackhole;
    }

    @Override
    protected void after() throws InterruptedException {
        executor.shutdownNow();
        executor.awaitTermination(30, TimeUnit.SECONDS);
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1us";
    }
}
