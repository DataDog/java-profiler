package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Path;

import org.junit.jupiter.api.Assumptions;

public abstract class JfrDumpTest extends AbstractProfilerTest {

    public void runTest(String eventName) throws Exception {
        runTest(eventName, "method1", "method2", "method3");
    }

    public void runTest(String eventName, String ... patterns) throws Exception {
        Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
        Assumptions.assumeFalse(Platform.isJ9());

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
        long ts = System.nanoTime();
        for (int i = 0; i < 1000; ++i) {
            int cntr = 10;
            for (String s : new File("/tmp").list()) {
                value += s.substring(0, Math.min(s.length(), 16) ).hashCode();
                if (--cntr < 0) {
                    break;
                }
            }
            if ((System.nanoTime() - ts) > 20000000L) {
                break;
            }
        }
    }
}
