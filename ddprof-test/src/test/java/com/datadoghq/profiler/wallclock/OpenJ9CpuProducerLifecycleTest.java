/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfEnvironmentVariable;

/** Independent genuine OpenJ9 CPU control, without depending on test-name setup ordering. */
@EnabledIfEnvironmentVariable(named = "DDPROF_EXPECTED_VM", matches = "openj9")
public class OpenJ9CpuProducerLifecycleTest extends RealVmProducerTest {
  /** Requires positive-weight resolved CPU samples from the same worker after restart. */
  @Test
  public void genuineOpenJ9CpuSamplesSurviveRestart() throws Exception {
    verifyRetainedWorkerAcrossRestart();
  }

  @Override
  protected boolean expectsOpenJ9() {
    return true;
  }

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms,filter=";
  }

  @Override
  protected String sampleEventType() {
    return "datadog.ExecutionSample";
  }
}
