// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Assumptions;

public abstract class JfrDumpTest extends CStackAwareAbstractProfilerTest {
  public JfrDumpTest(@CStack String cstack) {
    super(cstack);
  }

  /**
   * Workload iterations for the first dump cycle: the historical fixed density. Preserves the gate
   * that a dump taken after a fully initialized profiler and a settled workload verifies.
   */
  private static final int INITIAL_BATCH = 50;

  /** Growth bound for under-sampled batches, so a broken sampler fails instead of looping. */
  private static final int MAX_BATCH = 400;

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

    // Event-driven sizing: each dump needs an event matching every declared frame pattern.
    // Under-sampled dumps retry with a doubled batch capped at MAX_BATCH; failure is asserted
    // when the cap is exhausted. A cycle that passed without growth halves the batch for the
    // next cycle; one that needed growth keeps its batch (halving a marginal batch just
    // re-triggers the growth path on every cycle).
    int batch = INITIAL_BATCH;
    for (int j = 0; j < dumpCnt; j++) {
      Path recording = Files.createTempFile("dump-", ".jfr");
      try {
        boolean grew = false;
        runWorkload(batch);
        dump(recording);
        while (!tryVerifyStackTraces(recording, eventName, patterns)) {
          if (batch >= MAX_BATCH) {
            // Growth bound exhausted: surface the real failure through the asserting verify.
            verifyStackTraces(recording, eventName, patterns);
          }
          Files.deleteIfExists(recording);
          recording = Files.createTempFile("dump-", ".jfr");
          batch = Math.min(batch * 2, MAX_BATCH);
          grew = true;
          runWorkload(batch);
          dump(recording);
        }
        if (!grew) {
          batch = Math.max(1, batch / 2);
        }
      } finally {
        Files.deleteIfExists(recording);
      }
    }
    // The dump snapshots drain their own windows from the live stream, so the continuous
    // recording cannot be assumed to hold the dump-cycle events; the post-stop verification
    // needs its own sampling window at the settled historical density right before stop().
    runWorkload(INITIAL_BATCH);
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
