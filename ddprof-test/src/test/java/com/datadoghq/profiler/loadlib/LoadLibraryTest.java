// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.loadlib;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import java.lang.management.ClassLoadingMXBean;
import java.lang.management.ManagementFactory;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;

public class LoadLibraryTest extends AbstractProfilerTest {

  @RetryingTest(3)
  public void testLoadLibrary() throws InterruptedException {
    Assumptions.assumeFalse(Platform.isJ9());
    // Wait for the engines to be ready, then late-load libmanagement.so via the first
    // ClassLoadingMXBean touch below. Sampling window sized so the cpu=1ms engine reliably
    // captures Java_sun_management frames (RetryingTest(3) tolerates a transient miss).
    waitForProfilerReady(2000);
    // Late load of libmanagement.so
    ClassLoadingMXBean bean = ManagementFactory.getClassLoadingMXBean();

    long n = 0;
    long tsLimit = System.nanoTime() + 1_500_000_000L; // 1.5 seconds
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
