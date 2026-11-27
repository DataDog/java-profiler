/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Test;

/**
 * Verifies that TaskBlock hooks fail closed on JVMs whose platform-thread classification is not
 * trusted (non-HotSpot JVMs on JDK 19+).
 */
public class JavaProfilerTaskBlockNonHotspotTest extends AbstractProfilerTest {
  /** A platform thread must not arm an interval when classification is not trusted. */
  @Test
  public void platformThreadCannotArmTaskBlock() {
    // The JUnit thread is a platform thread, so false is the fail-closed classification.
    assertFalse(ProfilerOwnedBlockHooks.platformThread(profiler));
    long token = profiler.beginTaskBlock();
    assertEquals(0L, token);
    assertFalse(profiler.endTaskBlock(token, 1L, 0L));
    stopProfiler();
    assertEquals(0L, verifyEvents("datadog.TaskBlock", false).count());
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
