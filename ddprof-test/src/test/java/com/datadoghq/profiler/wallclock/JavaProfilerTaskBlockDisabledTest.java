/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

/** Verifies that TaskBlock does not change legacy/context wall-clock scope. */
public class JavaProfilerTaskBlockDisabledTest extends AbstractProfilerTest {
  private static final int OSTHREAD_STATE_SLEEPING = 7;

  @Test
  public void pairedApiIsInactiveOutsideAllThreadScope() {
    assertEquals(0L, profiler.beginTaskBlock(OSTHREAD_STATE_SLEEPING));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=0,wallprecheck=true";
  }
}
