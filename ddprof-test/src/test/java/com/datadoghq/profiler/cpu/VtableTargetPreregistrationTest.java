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

import static org.junit.jupiter.api.Assertions.assertTrue;

public class VtableTargetPreregistrationTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    abstract static class Shape {
        abstract int area();
    }

    static class Circle extends Shape {
        private final int r;
        Circle(int r) { this.r = r; }
        @Override public int area() { return r * r; }
    }

    static class Square extends Shape {
        private final int s;
        Square(int s) { this.s = s; }
        @Override public int area() { return s * s; }
    }

    static class Triangle extends Shape {
        private final int b;
        Triangle(int b) { this.b = b; }
        @Override public int area() { return b * b / 2; }
    }

    private int profiledWork(Shape... shapes) {
        int result = 0;
        for (int i = 0; i < 1_000_000; i++) {
            for (Shape shape : shapes) {
                result += shape.area();
            }
        }
        return result;
    }

    @RetryingTest(3)
    public void testClassMapPopulatedOnCpuStart() {
        stopProfiler();
        assertTrue(getRecordedCounterValue("dictionary_classes_keys") > 0,
                "dictionary_classes_keys must be > 0: preregisterLoadedClasses() was not called on profiler start");
    }

    // jvmtiError is the expected synthetic receiver-class frame that vtable_target inserts;
    // contrast with SmokeCpuTest which asserts its absence for non-vtable workloads.
    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamples() {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9());
        int result = profiledWork(new Circle(3), new Square(4), new Triangle(5));
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
                "No CPU sample contained both a vtable stub frame and a jvmtiError receiver frame");
    }
}
