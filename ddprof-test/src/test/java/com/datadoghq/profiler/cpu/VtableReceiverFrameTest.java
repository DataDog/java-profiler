/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.JfrFrame;

import java.util.List;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;

import java.util.concurrent.ThreadLocalRandom;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class VtableReceiverFrameTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        String method = testInfo.getTestMethod().get().getName();
        if (method.endsWith("Dwarf")) {
            return "cpu=1ms,cstack=dwarf";
        }
        if (method.endsWith("Vm")) {
            return "cpu=1ms,cstack=vm";
        }
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

    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamples() throws Exception {
        assertVtableReceiverFrame();
    }

    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamplesDwarf() throws Exception {
        assertVtableReceiverFrame();
    }

    @RetryingTest(5)
    public void testVtableReceiverFrameInCpuSamplesVm() throws Exception {
        assertVtableReceiverFrame();
    }

    /** Verifies the synthetic method's declaring class, not unrelated Java callers in the trace. */
    private void assertVtableReceiverFrame() throws Exception {
        Assumptions.assumeFalse(Platform.isZing() || Platform.isJ9() || Platform.isGraal());
        waitForProfilerReady(2000);
        int result = profiledWork(new Circle(), new Square(), new Triangle());
        System.err.println(result);
        stopProfiler();

        JfrEvents events = verifyEvents("datadog.ExecutionSample");
        int stubs = 0;
        int receivers = 0;
        boolean foundVtableWithReceiver = false;
        for (JfrEvent sample : events) {
            assertNotNull(sample.get("stackTrace"), "CPU sample is missing its stackTrace field");
            List<JfrFrame> frames = sample.getStackTrace().frames();
            for (int i = 0; i < frames.size(); i++) {
                JfrFrame frame = frames.get(i);
                assertNotNull(frame.methodName(), "CPU stack frame is missing its method name");
                if ("vtable stub".equals(frame.methodName())) {
                    stubs++;
                }
                if ("<vtable_receiver>".equals(frame.methodName())) {
                    receivers++;
                    String receiver = frame.className();
                    assertNotNull(receiver, "Vtable receiver frame is missing its declaring class");
                    if ((Circle.class.getName().equals(receiver)
                            || Square.class.getName().equals(receiver)
                            || Triangle.class.getName().equals(receiver))
                            && i + 1 < frames.size()
                            && "vtable stub".equals(frames.get(i + 1).methodName())) {
                        if (!foundVtableWithReceiver) {
                            System.out.println("Vtable receiver: " + receiver + "." + frame.methodName()
                                    + " -> " + frames.get(i + 1).methodName());
                        }
                        foundVtableWithReceiver = true;
                    }
                }
            }
        }
        System.out.println("Vtable stubs=" + stubs + ", receivers=" + receivers);
        assertTrue(foundVtableWithReceiver,
                "No CPU sample contained a <vtable_receiver> method declared by a workload receiver "
                        + "class (Circle/Square/Triangle) immediately before its vtable stub; "
                        + "signal-handler capture or dump-time resolution is broken");
    }
}
