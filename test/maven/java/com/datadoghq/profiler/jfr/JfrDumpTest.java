package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.AbstractProfilerTest;

import java.io.File;

public abstract class JfrDumpTest extends AbstractProfilerTest {

    public void runTest(String eventName) {
        for (int i = 0; i < 100; i++) {
            method1();
            method2();
            method3();
        }
        stopProfiler();
        verifyStackTraces(eventName, "method1", "method2", "method3");
    }

    private static volatile int value;

    private static void method1() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
    }

    private static void method2() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
    }

    private static void method3() {
        for (int i = 0; i < 1000; ++i) {
            for (String s : new File("/tmp").list()) {
                value += s.hashCode();
            }
        }
    }
}
