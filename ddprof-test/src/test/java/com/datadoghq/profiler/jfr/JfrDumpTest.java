package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.junit.RetryTest;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.Platform;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import org.junit.jupiter.api.Assumptions;

public abstract class JfrDumpTest extends CStackAwareAbstractProfilerTest {
    public JfrDumpTest(@CStack String cstack) {
        super(cstack);
    }

    public void runTest(String eventName) throws Exception {
        runTest(eventName, "method1", "method2", "method3");
    }

    public void runTest(String eventName, String ... patterns) throws Exception {
        runTest(eventName, 10, patterns);
    }

    public void runTest(String eventName, int dumpCnt, String ... patterns) throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        Assumptions.assumeFalse(Platform.isJ9());

        for (int j = 0; j < dumpCnt; j++) {
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
        // Fixed iteration count for deterministic workload (was time-based with 20ms timeout)
        for (int i = 0; i < 200; ++i) {
            int cntr = 10;
            // Null-safe iteration over /tmp directory
            String[] files = new File("/tmp").list();
            if (files != null) {
                for (String s : files) {
                    if (s != null && !s.isEmpty()) {
                        value += s.substring(0, Math.min(s.length(), 16)).hashCode();
                        if (--cntr < 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
}
