package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertTrue;

public class VtableReceiverFrameTest extends AbstractProfilerTest {

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
    // is captured as a VMSymbol* in the signal handler and resolved to a class name at
    // dump time via SafeAccess-protected reads. If resolution fails or the synthetic frame
    // is dropped, the receiver class name will not appear next to a vtable stub in JFR.
    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamples() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal());
        waitForProfilerReady(2000);
        int result = profiledWork(new Circle(), new Square(), new Triangle());
        System.err.println(result);
        stopProfiler();

        JfrEvents events = verifyEvents("datadog.ExecutionSample");
        boolean foundVtableWithReceiver = false;
        for (JfrEvent sample : events) {
            String stackTrace = sample.getStackTraceString();
            if (stackTrace != null && stackTrace.contains(".vtable stub()")) {
                System.err.println("=VTABLE STUB TRACE=\n" + stackTrace + "\n=END=");
            }
            // Match on the bare token so the test is robust regardless of how the
            // synthetic method name is escaped/rendered.
            if (stackTrace != null
                    && stackTrace.contains(".vtable stub()")
                    && stackTrace.contains("vtable_receiver")
                    && (stackTrace.contains("Circle")
                            || stackTrace.contains("Square")
                            || stackTrace.contains("Triangle"))) {
                foundVtableWithReceiver = true;
                break;
            }
        }
        assertTrue(foundVtableWithReceiver,
                "No CPU sample contained a vtable stub frame, a vtable_receiver synthetic frame, " +
                "and a receiver class (Circle/Square/Triangle); signal-handler VMSymbol* capture or " +
                "dump-time SafeAccess resolution in Lookup::resolveVTableReceiver is broken");
    }
}
