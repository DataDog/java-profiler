/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;

/** Verifies synchronous park production when delegated wall-clock stacks are enabled. */
public class JvmtiBasedParkTaskBlockTest extends ParkTaskBlockTest {
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
}
