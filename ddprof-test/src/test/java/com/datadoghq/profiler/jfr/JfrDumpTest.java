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

        // Wait for profiler to reach RUNNING state before workload begins
        // Use 2000ms timeout to account for slow systems and CI load
        waitForProfilerReady(2000);

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

    protected static volatile int value;

    /**
     * Override this method in subclasses to provide profiler-specific workload.
     * Default implementation provides CPU-bound work suitable for CPU profiling.
     */
    protected void method1() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
    }

    /**
     * Override this method in subclasses to provide profiler-specific workload.
     * Default implementation provides CPU-bound work suitable for CPU profiling.
     */
    protected void method2() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
    }

    /**
     * Override this method in subclasses to provide profiler-specific workload.
     * Default implementation provides CPU-bound work suitable for CPU profiling.
     */
    protected void method3() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
    }
}
