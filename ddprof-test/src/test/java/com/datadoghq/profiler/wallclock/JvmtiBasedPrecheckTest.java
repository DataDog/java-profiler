/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.Platform;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Assumptions;

/** Runs wallprecheck through HotSpot delegated RequestStackTrace sampling. */
public class JvmtiBasedPrecheckTest extends PrecheckTest {
  private boolean jvmtiDelegationAvailable;
  private long requestedBefore;

  /** Requires a real periodic delegated request before even an instantaneous rejection test. */
  @Override
  protected void before() throws Exception {
    // Require the selected delegated engine, not just extension availability.
    Assumptions.assumeTrue(
        profiler.getStatus().contains("WallClock Engine : WallClock (JVMTI)"),
        "HotSpot RequestStackTrace JVMTI wall engine was not selected");
    requestedBefore = profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L);
    // Instantaneous hook-rejection tests can finish before the first periodic wall signal.
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(5);
    long requested = requestedBefore;
    while (requested <= requestedBefore && System.nanoTime() < deadline) {
      Thread.sleep(1L);
      requested = profiler.getDebugCounters().getOrDefault("jvmti_stacks_requested", 0L);
    }
    assertTrue(
        requested > requestedBefore,
        "The delegated wall engine did not issue a stack request within five seconds");
    jvmtiDelegationAvailable = true;
  }

  @Override
  protected void after() throws Exception {
    if (!jvmtiDelegationAvailable) {
      return;
    }
    Map<String, Long> counters = profiler.getDebugCounters();
    long requestedAfter = counters.getOrDefault("jvmti_stacks_requested", 0L);
    assertTrue(
        requestedAfter > requestedBefore,
        "Expected wallclock jvmtistacks path to request delegated stack traces");
    assertEquals(Long.valueOf(0L), counters.get("jvmti_stacks_failed_other"));
  }

  @Override
  protected boolean isPlatformSupported() {
    return !Platform.isJ9();
  }

  @Override
  protected void withTestAssumptions() {
    Assumptions.assumeTrue(Platform.isJavaVersionAtLeast(11));
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true,jvmtistacks=true";
  }

  @Override
  protected String getPrecheckDisabledProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=false,jvmtistacks=true";
  }
}
