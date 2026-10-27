/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Verifies that TaskBlock hooks fail closed on JVMs whose platform-thread classification is not
 * trusted (non-HotSpot JVMs on JDK 19+).
 */
public class JavaProfilerTaskBlockNonHotspotTest extends AbstractProfilerTest {
  /** A platform thread must not arm an interval when classification is not trusted. */
  @Test
  public void platformThreadCannotArmTaskBlock() {
    // Positive control: blockEnter() does not check platform-thread classification. With an
    // empty filter, it arms a run only when unfiltered wall tracking is active (which also enables
    // TaskBlock recording) and this thread has a registry slot. A non-zero token therefore shows
    // that beginTaskBlock() can return 0 below only because classification is not trusted.
    long control = ProfilerOwnedBlockHooks.blockEnter(profiler, TaskBlockAssertions.OSTHREAD_STATE_SLEEPING);
    Assumptions.assumeTrue(control != 0,
        "the wall engine on this JVM does not enable TaskBlock tracking for this thread");
    ProfilerOwnedBlockHooks.blockExit(profiler, control);

    assertEquals(0L, profiler.beginTaskBlock());
  }

  @Override
  protected boolean isPlatformSupported() {
    return !TaskBlockAssertions.platformThreadClassificationSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }
}
