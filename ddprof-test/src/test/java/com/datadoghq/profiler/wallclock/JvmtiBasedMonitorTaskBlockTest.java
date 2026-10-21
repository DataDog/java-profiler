/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import java.util.Map;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Assumptions;

/** Verifies synchronous monitor production when delegated wall-clock stacks are enabled. */
public class JvmtiBasedMonitorTaskBlockTest extends MonitorTaskBlockTest {
  @Override
  protected void before() {
    Map<String, Long> counters = profiler.getDebugCounters();
    Assumptions.assumeTrue(counters.getOrDefault("jvmti_stacks_init_ok", 0L) > 0,
        "HotSpot RequestStackTrace JVMTI extension is not available");
  }

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true,jvmtistacks=true";
  }

  /**
   * Proves the restarted recording really ran with {@code jvmtistacks=true}: JVMTI stacks
   * must have been requested again after the restart. Catches a regression back to a
   * hardcoded restart command that drops this class's configuration.
   *
   * <p>Starting the restarted recording resets the native counters, so any non-zero count
   * here was accumulated by the restarted recording alone.
   */
  @Override
  protected void assertRestartedConfiguration(Map<String, Long> counters) {
    long requested = counters.getOrDefault("jvmti_stacks_requested", 0L);
    Assertions.assertTrue(requested > 0,
        "restarted recording did not use the JVMTI stack path: jvmti_stacks_requested "
            + requested);
  }
}
