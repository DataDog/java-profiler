/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
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
