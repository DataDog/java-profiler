/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfilerTestSupport;
import java.util.Map;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/**
 * Regression test for {@code Profiler::stop()} gating engine teardown on the
 * activated-engine mask rather than the requested-engine mask. Before this fix,
 * a mixed-success {@code start()} (one engine requested but never activated,
 * another requested and activated) still invoked {@code stop()} on the engine
 * that was never activated.
 *
 * <p>Detection uses the existing {@code wall_stop_while_not_activated} debug
 * counter (read via the already-public {@code JavaProfiler.getDebugCounters()})
 * rather than a dedicated JNI hook: {@code Profiler::start()} calls
 * {@code Counters::reset()} unconditionally, so the counter is implicitly
 * zeroed by this test's own {@code setupProfiler()} call before the assertion.
 */
public class NeverActivatedEngineStopTest extends AbstractProfilerTest {

  private static final String COUNTER_NAME = "wall_stop_while_not_activated";

  @Override
  protected void beforeProfilerStart() throws Exception {
    super.beforeProfilerStart();
    // In effect only for this test's start() call; cleared at the top of the test method below.
    JavaProfilerTestSupport.setForceWallStartFailureForTest(true);
    // The forced-start-failure toggle is a DEBUG-only native hook (no-op in
    // release builds). Self-skip when it isn't armed so the test doesn't fail
    // spuriously in release: without a real wall-engine start failure, the wall
    // engine activates normally and the assertion below cannot hold.
    Assumptions.assumeTrue(
        JavaProfilerTestSupport.isForceWallStartFailureArmedForTest(),
        "force-wall-start-failure test hook is a no-op outside DEBUG native builds;"
            + " the Profiler::stop() gating fix under test only fires when the wall engine"
            + " can be made to fail, which requires the DEBUG-only hook -- skipping");
  }

  @Override
  protected String getProfilerCommand() {
    // cpu proves an unrelated engine activates and keeps running despite the wall
    // engine's forced start failure. Bare (interval-less) event names so
    // AbstractProfilerTest.checkConfig()'s interval assertions -- which only apply
    // when an explicit "cpu=" / "wall=" interval was requested -- are skipped.
    return "cpu,wall";
  }

  @Test
  public void wallEngineNeverActivatedIsNeverStopped() {
    JavaProfilerTestSupport.setForceWallStartFailureForTest(false);
    stopProfiler();
    Map<String, Long> counters = profiler.getDebugCounters();
    assertEquals(
        0L,
        counters.getOrDefault(COUNTER_NAME, 0L),
        "wall engine failed to activate in start(); Profiler::stop() must not call"
            + " BaseWallClock::stop() on an engine that never activated");
  }
}
