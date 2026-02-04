package com.datadoghq.profiler.jfr;

import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.provider.ValueSource;
import org.junit.jupiter.api.TestTemplate;

import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;

public class WallclockDumpSmokeTest extends JfrDumpTest {
    public WallclockDumpSmokeTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        // Zing forces cstack=no which prevents proper stack trace capture for wall clock profiling
        return !Platform.isZing();
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }

    @Override
    protected void method1() {
        // CPU work for wall clock sampling
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
        // Add brief sleep to ensure wall clock capture
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    @Override
    protected void method2() {
        // CPU work for wall clock sampling
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
        // Add brief sleep to ensure wall clock capture
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    @Override
    protected void method3() {
        // CPU work for wall clock sampling
        for (int i = 0; i < 1000000; ++i) {
            ++value;
        }
        // Add brief sleep to ensure wall clock capture
        try {
            Thread.sleep(1);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    @RetryTest(3)
    @Timeout(value = 60)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
    public void test(@CStack String cstack) throws Exception {
        registerCurrentThreadForWallClockProfiling();
        runTest("datadog.MethodSample");
    }
}
