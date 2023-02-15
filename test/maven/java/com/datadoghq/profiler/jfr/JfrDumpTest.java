package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.AbstractProfilerTest;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

public abstract class JfrDumpTest extends AbstractProfilerTest {

    public void runTest(String eventName) throws Exception {
        runTest(eventName, "method1", "method2", "method3");
    }

    public void runTest(String eventName, String ... patterns) throws Exception {
        for (int j = 0; j < 10; j++) {
            Path recording = Files.createTempFile("dump-", ".jfr");
            try {
                for (int i = 0; i < 50; i++) {
                    method1();
                    method2();
                    method3();
                }
                dump(recording);
                verifyStackTraces(recording, eventName, patterns);
            } finally {
                Files.deleteIfExists(recording);
            }
        }
        for (int i = 0; i < 500; i++) {
            method1();
            method2();
            method3();
        }
        stopProfiler();
        verifyStackTraces(eventName, patterns);
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
