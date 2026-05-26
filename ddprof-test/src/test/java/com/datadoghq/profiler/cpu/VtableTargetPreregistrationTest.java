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

    // The vtable_target feature inserts a synthetic <vtable_receiver> frame immediately
    // below a vtable stub frame in the call stack. The receiver class (Circle/Square/Triangle)
    // is resolved from _class_map and emitted as the class name for the synthetic frame.
    // If preregisterLoadedClasses() was not called (the bug), bounded_lookup returns INT_MAX,
    // no synthetic frame is inserted, and the receiver class name never appears next to a
    // vtable stub in the JFR output.
    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamples() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        waitForProfilerReady(2000);
        int result = profiledWork(new Circle(), new Square(), new Triangle());
        System.err.println(result);
        stopProfiler();

        IItemCollection events = verifyEvents("datadog.ExecutionSample");
        boolean foundVtableWithReceiver = false;
        for (IItemIterable cpuSamples : events) {
            IMemberAccessor<String, IItem> frameAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(cpuSamples.getType());
            if (frameAccessor == null) continue;
            for (IItem sample : cpuSamples) {
                String stackTrace = frameAccessor.getMember(sample);
                if (stackTrace != null
                        && stackTrace.contains(".vtable stub()")
                        && stackTrace.contains("<vtable_receiver>")
                        && (stackTrace.contains("Circle")
                                || stackTrace.contains("Square")
                                || stackTrace.contains("Triangle"))) {
                    foundVtableWithReceiver = true;
                    break;
                }
            }
            if (foundVtableWithReceiver) break;
        }
        assertTrue(foundVtableWithReceiver,
                "No CPU sample contained a vtable stub frame, a <vtable_receiver> synthetic frame, " +
                "and a receiver class (Circle/Square/Triangle); preregisterLoadedClasses() may not " +
                "have run at CPU-only profiler start, or resolveMethod BCI_ALLOC is broken");
    }
}
