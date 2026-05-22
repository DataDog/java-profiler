package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class VtableTargetPreregistrationTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }

    abstract static class Shape {
        abstract int area();
    }

    // Three implementations force megamorphic vtable dispatch (JIT won't inline).
    // ThreadLocalRandom bodies ensure each variant is non-trivial and CPU-bound.
    static class Circle extends Shape {
        @Override public int area() { return ThreadLocalRandom.current().nextInt() | 1; }
    }

    static class Square extends Shape {
        @Override public int area() { return ThreadLocalRandom.current().nextInt() | 2; }
    }

    static class Triangle extends Shape {
        @Override public int area() { return ThreadLocalRandom.current().nextInt() | 4; }
    }

    private int profiledWork(Shape... shapes) {
        int result = 0;
        for (int i = 0; i < 10_000_000; i++) {
            for (Shape shape : shapes) {
                result += shape.area();
            }
        }
        return result;
    }

    // jvmtiError is the expected synthetic receiver-class frame that vtable_target inserts when
    // the class map is populated (PR #527 fix). The class map is populated by
    // preregisterLoadedClasses() at CPU-only profiler start; if that call is absent (the bug),
    // bounded_lookup returns INT_MAX and no synthetic frame is inserted — jvmtiError never appears.
    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamples() {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        int result = profiledWork(new Circle(), new Square(), new Triangle());
        System.err.println(result);
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        boolean foundVtableWithReceiver = false;
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                if (stackTrace.contains(".vtable stub()") && stackTrace.contains("jvmtiError")) {
                    foundVtableWithReceiver = true;
                    break;
                }
            }
            if (foundVtableWithReceiver) break;
        }
        assertTrue(foundVtableWithReceiver,
                "No CPU sample contained both a vtable stub frame and a jvmtiError receiver frame; " +
                "preregisterLoadedClasses() may not have run at CPU-only profiler start (PR #527 regression)");
    }
}
