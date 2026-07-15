/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import java.util.Map;
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
    return "wall=1ms,wallscope=all,wallprecheck=true,jvmtistacks=true";
  }
}
