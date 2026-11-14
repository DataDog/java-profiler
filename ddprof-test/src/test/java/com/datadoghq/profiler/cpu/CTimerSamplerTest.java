/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.cpu;

import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import java.util.concurrent.ExecutionException;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;

public class CTimerSamplerTest extends CStackAwareAbstractProfilerTest {

  private ProfiledCode profiledCode;

  public CTimerSamplerTest(@CStack String cstack) {
    super(cstack);
  }

  @Override
  protected void before() {
    profiledCode = new ProfiledCode(profiler);
  }

  @RetryTest(10)
  @TestTemplate
  @ValueSource(strings = {"vm", "vmx", "fp", "dwarf"})
  public void test(@CStack String cstack) throws ExecutionException, InterruptedException {
    // timer_create is available on Linux only
    assumeTrue(Platform.isLinux());
    for (int i = 0, id = 1; i < 100; i++, id += 3) {
      profiledCode.method1(id);
    }
    stopProfiler();

    verifyCStackSettings();

    // Streamed rather than materialized: cpu=100us over this workload can produce tens of
    // thousands of samples; streamEvents counts them without retaining them in memory.
    long sampleCount = streamEvents("datadog.ExecutionSample", sample -> {});
    assertTrue(sampleCount > 0, "datadog.ExecutionSample was empty");
  }

  @Override
  protected void after() throws Exception {
    profiledCode.close();
  }

  @Override
  protected String getProfilerCommand() {
    // cpu=100us signal-based sampling is much more expensive under ASAN (the signal
    // handler itself is ASAN-instrumented), which can inflate the sample count and,
    // via the per-sample stack-trace materialization above, the test heap. Sample
    // coarser under ASAN.
    return isAsan() ? "cpu=1ms,event=ctimer" : "cpu=100us,event=ctimer";
  }
}
