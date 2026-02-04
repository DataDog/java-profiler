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
        // Mixed workload to support all profiler types (CPU, allocation, wall clock):
        // 1. CPU work: Tight loop with volatile operations to ensure CPU profiler sampling
        //    ~5ms on modern CPUs, provides ~5 sample opportunities for cpu=1ms profiler
        for (int i = 0; i < 500_000; i++) {
            value++;
        }

        // 2. Allocations: Create objects to trigger allocation profiler (memory=32:a)
        //    8KB allocation is large enough to bypass TLAB and trigger sampling
        byte[] data = new byte[8192];
        value += data.length;

        // 3. Blocking: Sleep to be captured by wall clock profiler (wall=5ms)
        //    10ms provides 2 sample opportunities at 5ms interval
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private static void method2() {
        // Mixed workload to support all profiler types (CPU, allocation, wall clock):
        // 1. CPU work: Tight loop with volatile operations to ensure CPU profiler sampling
        //    ~5ms on modern CPUs, provides ~5 sample opportunities for cpu=1ms profiler
        for (int i = 0; i < 500_000; i++) {
            value++;
        }

        // 2. Allocations: Create objects to trigger allocation profiler (memory=32:a)
        //    8KB allocation is large enough to bypass TLAB and trigger sampling
        byte[] data = new byte[8192];
        value += data.length;

        // 3. Blocking: Sleep to be captured by wall clock profiler (wall=5ms)
        //    10ms provides 2 sample opportunities at 5ms interval
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private static void method3() {
        // Mixed workload to support all profiler types (CPU, allocation, wall clock):
        // 1. CPU work: Tight loop with volatile operations to ensure CPU profiler sampling
        //    ~5ms on modern CPUs, provides ~5 sample opportunities for cpu=1ms profiler
        for (int i = 0; i < 500_000; i++) {
            value++;
        }

        // 2. Allocations: Create many String objects to trigger allocation profiler (memory=32:a)
        //    Replicate the allocation pattern from the original File I/O code
        //    500 iterations × ~10 string allocations = ~5000 allocations, exceeds 32KB threshold
        for (int i = 0; i < 500; i++) {
            // Create string array and substring operations similar to original File.list() pattern
            String[] data = new String[10];
            for (int j = 0; j < 10; j++) {
                data[j] = "test_allocation_string_" + i + "_" + j;
                value += data[j].substring(0, Math.min(data[j].length(), 16)).hashCode();
            }
        }

        // 3. Blocking: Sleep to be captured by wall clock profiler (wall=5ms)
        //    10ms provides 2 sample opportunities at 5ms interval
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
