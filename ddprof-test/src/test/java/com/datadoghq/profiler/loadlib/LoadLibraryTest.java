package com.datadoghq.profiler.loadlib;

import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junitpioneer.jupiter.RetryingTest;

import java.lang.management.ClassLoadingMXBean;
import java.lang.management.ManagementFactory;

public class LoadLibraryTest extends AbstractProfilerTest {

    @RetryingTest(3)
    public void testLoadLibrary() throws InterruptedException {
        Assumptions.assumeFalse(Platform.isJ9());
        for (int i = 0; i < 200; i++) {
            Thread.sleep(10);
        }
        // Late load of libmanagement.so
        ClassLoadingMXBean bean = ManagementFactory.getClassLoadingMXBean();

        long n = 0;
        long tsLimit = System.nanoTime() + 3_000_000_000L; //  3 seconds
        while (System.nanoTime() < tsLimit) {
            n += bean.getLoadedClassCount();
            n += bean.getTotalLoadedClassCount();
            n += bean.getUnloadedClassCount();
        }
        System.out.println("=== accumulated: " + n);
        stopProfiler();
        verifyStackTraces("datadog.ExecutionSample", "Java_sun_management");
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=1ms";
    }
}
