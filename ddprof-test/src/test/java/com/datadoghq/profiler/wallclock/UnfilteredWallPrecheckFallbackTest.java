/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertFalse;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import org.junit.jupiter.api.Test;

/**
 * Regression test for the {@code Profiler::start()} fallback that closes thread-registry
 * admission when the wall engine fails to activate in unfiltered wall-precheck tracking mode, so
 * unrelated engines that did start successfully (e.g. {@code cpu=}) don't keep paying registry
 * overhead for the rest of the recording.
 */
public class UnfilteredWallPrecheckFallbackTest extends AbstractProfilerTest {

  @Override
  protected void beforeProfilerStart() throws Exception {
    super.beforeProfilerStart();
    // In effect only for this test's start() call; cleared at the top of the test method below.
    JavaProfilerTestSupport.setForceWallStartFailureForTest(true);
  }

  @Override
  protected String getProfilerCommand() {
    // Empty filter + wallprecheck=true selects unfiltered wall-precheck tracking
    // (Profiler::start()'s track_unfiltered_wall). cpu proves an unrelated engine
    // keeps running despite the wall engine's forced start failure. Bare (interval-less)
    // event names so AbstractProfilerTest.checkConfig()'s interval assertions -- which
    // only apply when an explicit "cpu=" / "wall=" interval was requested -- are skipped;
    // the wall engine's configured interval is never published because start() fails
    // before reaching that point.
    return "cpu,wall,filter=,wallprecheck=true";
  }

  @Test
  public void wallEngineFailureClosesRegistryAdmission() {
    JavaProfilerTestSupport.setForceWallStartFailureForTest(false);
    assertFalse(
        JavaProfilerTestSupport.isThreadRegistryActiveForTest(),
        "wall engine failed to activate in unfiltered-wall-precheck mode; registry admission"
            + " must be closed so unrelated engines (cpu=) don't keep paying registry overhead");
  }
}
