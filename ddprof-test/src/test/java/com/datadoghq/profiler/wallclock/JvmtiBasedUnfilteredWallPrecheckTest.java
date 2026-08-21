/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Map;
import org.junit.jupiter.api.Assumptions;

/** Runs unfiltered owned-block precheck coverage through delegated JVMTI stack collection. */
public class JvmtiBasedUnfilteredWallPrecheckTest extends UnfilteredWallPrecheckTest {
  private boolean jvmtiDelegationAvailable;
  private long requestedBefore;

  @Override
  protected void before() {
    Map<String, Long> counters = profiler.getDebugCounters();
    Assumptions.assumeTrue(
        counters.getOrDefault("jvmti_stacks_init_ok", 0L) > 0,
        "HotSpot RequestStackTrace JVMTI extension is not available");
    jvmtiDelegationAvailable = true;
    requestedBefore = counters.getOrDefault("jvmti_stacks_requested", 0L);
  }

  @Override
  protected void after() {
    if (!jvmtiDelegationAvailable) {
      return;
    }
    long requestedAfter =
        profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L);
    assertTrue(
        requestedAfter > requestedBefore,
        "Expected wallclock jvmtistacks path to request delegated stack traces");
  }

  @Override
  protected String getProfilerCommand() {
    return super.getProfilerCommand() + ",jvmtistacks=true";
  }
}
