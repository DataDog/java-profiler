/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import org.junit.jupiter.api.Test;

/** Verifies that unsupported J9 wall sampling does not activate unfiltered precheck tracking. */
public class J9WallClockPrecheckCapabilityTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;

  /** Ensures owned-block hooks stay inactive when the selected wall engine cannot consume them. */
  @Test
  public void unsupportedEngineDoesNotActivateRegistry() {
    long token = ProfilerOwnedBlockHooks.blockEnter(profiler, OSTHREAD_STATE_SLEEPING);

    assertEquals(0L, token, "J9WallClock must not activate unfiltered precheck tracking");
  }

  @Override
  protected boolean isPlatformSupported() {
    return Platform.isJ9();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,wallsampler=jvmti,filter=,wallprecheck=true";
  }
}
