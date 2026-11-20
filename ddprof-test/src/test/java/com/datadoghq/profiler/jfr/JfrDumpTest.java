// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import org.junit.jupiter.api.Assumptions;

public abstract class JfrDumpTest extends CStackAwareAbstractProfilerTest {
  public JfrDumpTest(@CStack String cstack) {
    super(cstack);
  }

  public void runTest(String eventName) throws Exception {
    runTest(eventName, "method1", "method2", "method3");
  }

  public void runTest(String eventName, String... patterns) throws Exception {
    runTest(eventName, 5, patterns);
  }

  public void runTest(String eventName, int dumpCnt, String... patterns) throws Exception {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
    Assumptions.assumeFalse(Platform.isJ9());

    waitForProfilerReady(2000);

    AdaptiveDumpCycles.run(
        dumpCnt,
        this::runWorkload,
        this::dump,
        recording -> tryVerifyStackTraces(recording, eventName, patterns),
        recording -> verifyStackTraces(recording, eventName, patterns));
    // The dump snapshots drain their own windows from the live stream, so the continuous
    // recording cannot be assumed to hold the dump-cycle events; the post-stop verification
    // needs its own sampling window at the settled historical density right before stop().
    runWorkload(AdaptiveDumpCycles.INITIAL_BATCH);
    stopProfiler();
    verifyStackTraces(eventName, patterns);
  }

  private void runWorkload(int iterations) {
    for (int i = 0; i < iterations; i++) {
      method1();
      method2();
      method3();
    }
  }

  protected static volatile int value;

  /**
   * Override this method in subclasses to provide profiler-specific workload. Default
   * implementation provides CPU-bound work suitable for CPU profiling.
   */
  protected void method1() {
    for (int i = 0; i < 1000000; ++i) {
      ++value;
    }
  }

  /**
   * Override this method in subclasses to provide profiler-specific workload. Default
   * implementation provides CPU-bound work suitable for CPU profiling.
   */
  protected void method2() {
    for (int i = 0; i < 1000000; ++i) {
      ++value;
    }
  }

  /**
   * Override this method in subclasses to provide profiler-specific workload. Default
   * implementation provides CPU-bound work suitable for CPU profiling.
   */
  protected void method3() {
    for (int i = 0; i < 1000000; ++i) {
      ++value;
    }
  }
}
