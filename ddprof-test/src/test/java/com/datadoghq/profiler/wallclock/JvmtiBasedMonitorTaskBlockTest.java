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
    // Require the selected delegated engine, not just extension availability.
    Assumptions.assumeTrue(
        profiler.getStatus().contains("WallClock Engine : WallClock (JVMTI)"),
        "HotSpot RequestStackTrace JVMTI wall engine was not selected");
  }

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true,jvmtistacks=true";
  }

  /** Counter reset on start makes requests here evidence of the restarted session. */
  @Override
  protected void assertRestartedConfiguration(Map<String, Long> counters) {
    long requested = counters.getOrDefault("jvmti_stacks_requested", 0L);
    Assertions.assertTrue(
        requested > 0,
        "restarted recording did not use the JVMTI stack path: jvmti_stacks_requested "
            + requested);
  }
}
