/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Assumptions;

/** Runs unfiltered owned-block precheck coverage through delegated JVMTI stack collection. */
public class JvmtiBasedUnfilteredWallPrecheckTest extends UnfilteredWallPrecheckTest {
  private boolean jvmtiDelegationAvailable;
  private long requestedBefore;

  @Override
  protected void before() {
    // Require the selected delegated engine, not just extension availability.
    Assumptions.assumeTrue(
        profiler.getStatus().contains("WallClock Engine : WallClock (JVMTI)"),
        "HotSpot RequestStackTrace JVMTI wall engine was not selected");
    jvmtiDelegationAvailable = true;
    requestedBefore = profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L);
  }

  @Override
  protected void after() {
    if (!jvmtiDelegationAvailable) {
      return;
    }
    long requestedAfter = profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L);
    assertTrue(
        requestedAfter > requestedBefore,
        "Expected wallclock jvmtistacks path to request delegated stack traces");
  }

  @Override
  protected boolean usesWeightedUnownedFallback() {
    return false;
  }

  @Override
  protected String getProfilerCommand() {
    return super.getProfilerCommand() + ",jvmtistacks=true";
  }
}
