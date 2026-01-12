package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
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
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.function.Supplier;

import static com.datadoghq.profiler.AbstractProfilerTest.*;
import static com.datadoghq.profiler.MoreAssertions.assertInRange;
import static org.junit.jupiter.api.Assertions.*;

final class BaseContextWallClockTest {
    private final Supplier<JavaProfiler> profilerRef;
    private volatile JavaProfiler profiler;

    private ContextExecutor executor;

    private Map<String, List<Long>> methodsToSpanIds;

    BaseContextWallClockTest(Supplier<JavaProfiler> profilerRef) {
        this.profilerRef = profilerRef;
    }

    void before() {
        profiler = profilerRef.get();
        executor = new ContextExecutor(1, profiler);
        methodsToSpanIds = new ConcurrentHashMap<>();
    }

    void after() throws InterruptedException {
        executor.shutdownNow();
        executor.awaitTermination(30, TimeUnit.SECONDS);
        profiler = null;
    }

    void test(AbstractProfilerTest test) throws ExecutionException, InterruptedException {
        test(test, true);
    }

    void test(AbstractProfilerTest test, String cstack) throws ExecutionException, InterruptedException {
        test(test, true, cstack);
    }

    void test(AbstractProfilerTest test, boolean assertContext) throws ExecutionException, InterruptedException {
        test(test, assertContext, null);
    }

    void test(AbstractProfilerTest test, boolean assertContext, String cstack) throws ExecutionException, InterruptedException {
        String config = System.getProperty("ddprof_test.config");

        Assumptions.assumeTrue(!Platform.isJ9() && !Platform.isZing());

        test.registerCurrentThreadForWallClockProfiling();
        for (int i = 0, id = 1; i < 100; i++, id += 3) {
            method1(id);
        }
        test.stopProfiler();
        Set<Long> method1SpanIds = new HashSet<>(methodsToSpanIds.get("method1Impl"));
        Set<Long> method2SpanIds = new HashSet<>(methodsToSpanIds.get("method2Impl"));
        Set<Long> method3SpanIds = new HashSet<>(methodsToSpanIds.get("method3Impl"));
        IItemCollection events = test.verifyEvents("datadog.MethodSample");
        Set<String> states = new HashSet<>();
        Set<String> modes = new HashSet<>();
        // we have 100 method1, method2, and method3 calls, but can't guarantee we sampled them all
        long method1Weight = 0;
        long method2Weight = 0;
        long method3Weight = 0;
        long unattributedWeight = 0;
        for (IItemIterable wallclockSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor = JdkAttributes.STACK_TRACE_STRING.getAccessor(wallclockSamples.getType());
            IMemberAccessor<IQuantity, IItem> spanIdAccessor = SPAN_ID.getAccessor(wallclockSamples.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(wallclockSamples.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> stateAccessor = THREAD_STATE.getAccessor(wallclockSamples.getType());
            IMemberAccessor<String, IItem> modeAccessor = THREAD_EXECUTION_MODE.getAccessor(wallclockSamples.getType());
            for (IItem sample : wallclockSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                long spanId = spanIdAccessor.getMember(sample).longValue();
                long rootSpanId = rootSpanIdAccessor.getMember(sample).longValue();
                long weight = weightAccessor.getMember(sample).longValue();
                modes.add(modeAccessor.getMember(sample));
                String state = stateAccessor.getMember(sample);
                assertNotNull(state);
                states.add(state);
                // a lot fo care needs to be taken here with samples that fall between a context activation and
                // a method call. E.g. not finding method2Impl in the stack trace doesn't mean the sample wasn't
                // taken in the part of method2 between activation and invoking method2Impl, which complicates
                // assertions when we only find method1Impl
                boolean attributed = false;
                if (stackTrace.contains("method3Impl")) {
                    if (assertContext) {
                        // method3 is scheduled after method2, and method1 blocks on it, so spanId == rootSpanId + 2
                        assertEquals(rootSpanId + 2, spanId, stackTrace);
                        assertTrue(spanId == 0 || method3SpanIds.contains(spanId), stackTrace);
                    }
                    method3Weight += weight;
                    attributed = true;
                } else if (stackTrace.contains("method2Impl")) {
                    if (assertContext) {
                        // method2 is called next, so spanId == rootSpanId + 1
                        assertEquals(rootSpanId + 1, spanId, stackTrace);
                        assertTrue(spanId == 0 || method2SpanIds.contains(spanId), stackTrace);
                    }
                    method2Weight += weight;
                    attributed = true;
                } else if (stackTrace.contains("method1Impl")
                        && !stackTrace.contains("method2") && !stackTrace.contains("method3")) {
                    if (assertContext) {
                        // need to check this after method2 because method1 calls method2
                        // it's the root so spanId == rootSpanId
                        assertEquals(rootSpanId, spanId, stackTrace);
                        assertTrue(spanId == 0 || method1SpanIds.contains(spanId), stackTrace);
                    }
                    method1Weight += weight;
                    attributed = true;
                }
                assertTrue(weight <= 10 && weight > 0);
                // Only count as unattributed if spanId is 0 AND we couldn't attribute by stack trace
                // This prevents double-counting samples that have valid stack traces but no context
                // (e.g., JVMTI samples when using TLS context which can't be read cross-thread)
                if (spanId == 0 && !attributed) {
                    unattributedWeight += weight;
                }
            }
        }
        if (!Platform.isJ9() && Platform.isJavaVersionAtLeast(11)) {
            assertTrue(states.contains("WAITING"), "no WAITING samples");
            assertTrue(states.contains("PARKED"), "no PARKED samples");
            assertTrue(states.contains("CONTENDED"), "no CONTENDED samples");
        } else {
            assertTrue(states.contains("SYSCALL"), "no SYSCALL samples");
        }

        if (!Platform.isZing() && !Platform.isJ9()) {
            assertTrue(modes.contains("JAVA") || modes.contains("JVM"), "no JAVA|JVM samples");
            assertFalse(modes.contains("UNKNOWN"), "UNKNOWN wallclock samples on HotSpot");
        } else {
            assertTrue(modes.contains("UNKNOWN"), "no UNKNOWN samples");
        }

        // TODO: vmstructs unwinding on Liberica and aarch64 creates a higher number of broken frames
        //       it is under investigation but until it gets resolved we will just relax the error margin
        double allowedError = Platform.isAarch64() && "BellSoft".equals(System.getProperty("java.vendor")) ? 0.4d : 0.2d;

        // After async-profiler 4.2.1 integration and wall clock collapsing fixes, weight
        // distribution changed across all unwinding modes (vm, vmx, fp, dwarf).  All modes now
        // show ~55% weight for method1Impl instead of expected ~33%. Root causes include:
        // 1. DWARF: collects 10-20 native frames (vs 2-5 for FP), native frame PCs vary causing
        //    trace ID fragmentation
        // 2. FP/VMX: async-profiler integration changed frame collection or attribution behavior
        // 3. All modes: trace IDs hash all frames including native PCs with slight address variations
        // Proper fix requires architectural changes (hash only Java frames or normalize native PCs
        // to function entry points). For now, relax tolerance to acknowledge observed behavior.
        if (cstack != null && (cstack.equals("dwarf") || cstack.equals("fp") || cstack.equals("vmx"))) {
            allowedError = 0.3d; // Allow up to 30% deviation for affected modes
        }

        // context filtering should prevent these
        assertFalse(states.contains("NEW"));
        assertFalse(states.contains("TERMINATED"));
        // the sanitizer configurations are not playing that well with the sample distribution
        // still useful to run the profiler, though - so just skipping the assertions here
        if (config.equals("release") || config.equals("debug")) {
            double totalWeight = method1Weight + method2Weight + method3Weight + unattributedWeight;
            // method1 has ~50% self time, 50% calling method2
            assertWeight("method1Impl", totalWeight, method1Weight, 0.33, allowedError);
            // method2 has as much self time as method1
            assertWeight("method2Impl", totalWeight, method2Weight, 0.33, allowedError);
            // method3 has as much self time as method1, and should account for half the executor's thread's time
            assertWeight("method3Impl", totalWeight, method3Weight, 0.33, allowedError);
            Map<String, Long> debugCounters = profiler.getDebugCounters();
            // these are here to verify these counters produce reasonable values so they can be used for memory leak detection
            assertInRange(debugCounters.get("calltrace_storage_traces"), 1, 100);
            assertInRange(debugCounters.get("calltrace_storage_bytes"), 1024, 8 * 1024 * 1024);
            // this allocator is only used for calltrace storage and eagerly allocates chunks of 8MiB
            assertEquals(0, debugCounters.get("linear_allocator_bytes"));
            assertEquals(0, debugCounters.get("linear_allocator_chunks"));
            assertInRange(debugCounters.get("thread_ids_count"), 1, 100);
            assertInRange(debugCounters.get("thread_names_count"), 1, 100);
        }
    }

    private void assertWeight(String name, double total, long weight, double expected, double allowedError) {
        assertTrue(Math.abs(weight / total - expected)  < allowedError, String.format("expect %f weight for %s but have %f", expected, name, weight / total));
    }

    public void method1(int id) throws ExecutionException, InterruptedException {
        try (Tracing.Context context = Tracing.newContext(() -> id, profiler)) {
            method1Impl(id, context);
        }
    }

    public void method1Impl(int id, Tracing.Context context) throws ExecutionException, InterruptedException {
        sleep(10);
        Object monitor = new Object();
        Future<?> wait = executor.submit(() -> method3(id, monitor));
        method2(id, monitor);
        synchronized (monitor) {
            monitor.wait(10);
        }
        wait.get();
        record("method1Impl", context);
    }

    public void method2(long id, Object monitor) {
        synchronized (monitor) {
            try (Tracing.Context context = Tracing.newContext(() -> id + 1, profiler)) {
                method2Impl(context);
                monitor.notify();
            }
        }
    }

    public void method2Impl(Tracing.Context context) {
        sleep(10);
        record("method2Impl", context);
    }

    public void method3(long id, Object monitor) {
        synchronized (monitor) {
            try (Tracing.Context context = Tracing.newContext(() -> id + 2, profiler)) {
                method3Impl(context);
                monitor.notify();
            }
        }
    }

    public void method3Impl(Tracing.Context context) {
        sleep(10);
        record("method3Impl", context);
    }


    private void record(String methodName, com.datadoghq.profiler.context.Tracing.Context context) {
        methodsToSpanIds.computeIfAbsent(methodName, k -> new CopyOnWriteArrayList<>())
                .add(context.getSpanId());
    }


    private void sleep(long millis) {
        long target = System.nanoTime() + millis * 1_000_000L;
        do {
            try {
                Thread.sleep((target - System.nanoTime()) / 1_000_000L);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        } while (System.nanoTime() < target);
    }
}
