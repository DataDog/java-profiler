/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

/**
 * The check command validates a profiler command without starting anything. While a recording runs
 * it is rejected, and the recording must carry on. After stop() it validates the command and leaves
 * the profiler idle.
 */
public class CheckCommandTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    return "cpu=1ms";
  }

  @Test
  public void checkIsRejectedWhileRecording() throws Exception {
    IllegalStateException e =
        assertThrows(IllegalStateException.class, () -> profiler.execute("check,cpu=1ms"));
    assertEquals("Profiler already started", e.getMessage());
    assertTrue(profiler.execute("status").contains("Profiling is running"));
  }

  @Test
  public void checkSucceedsWhenIdle() throws Exception {
    stopProfiler();
    assertTrue(profiler.execute("check,cpu=1ms").startsWith("OK"));
    assertTrue(profiler.execute("status").contains("Profiler is not active"));
  }

  @Test
  public void checkPreflightRejectsNonCpuEventWithCpu() {
    stopProfiler();
    // A timer-family CPU engine is selected for cpu=N with a non-CPU event
    // and rejects the resolved interval; with no other requested mode the
    // preflight fails the configuration, matching start().
    IllegalStateException e =
        assertThrows(
            IllegalStateException.class,
            () -> profiler.execute("check,event=wall,cpu=1ms"));
    assertEquals("interval must be positive", e.getMessage());
  }

  @Test
  public void checkPreflightKeepsMixedModeViable() throws Exception {
    stopProfiler();
    // start() recovers from the CPU engine rejection when the wall engine
    // carries the recording, so the preflight reports the wall path as OK.
    assertTrue(
        profiler.execute("check,event=wall,cpu=1ms,wall=10ms").startsWith("OK"));
  }

  @Test
  public void checkPreflightAcceptsWallWithoutCpu() throws Exception {
    stopProfiler();
    // No CPU engine runs for event=wall without cpu, so the interval gate
    // is not armed.
    assertTrue(profiler.execute("check,event=wall").startsWith("OK"));
  }
}
