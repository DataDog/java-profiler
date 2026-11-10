/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.nio.file.Path;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfEnvironmentVariable;

/** Real HotSpot ASGCT fallback and paired JNI control for the OpenJ9 fixture. */
@EnabledIfEnvironmentVariable(named = "DDPROF_EXPECTED_VM", matches = "hotspot")
public class HotSpotProducerLifecycleTest extends RealVmProducerTest {
  /** Verifies ordinary local stacks and exact paired JNI production across restart. */
  @Test
  public void hotspotRecordingAndJniLifecycleSurviveRestart() throws Exception {
    verifyRetainedWorkerAcrossRestart();
  }

  /** A non-opted-in Java API start must leave the delegated extension uninitialized. */
  @Override
  protected void verifyAdditionalRecording(Path nativeRecording, long workerId) {
    Long initializationCount = profiler.getDebugCounters().get("jvmti_stacks_init_ok");
    assertEquals(Long.valueOf(0L), initializationCount);
    System.out.println("REAL_JVMTI_NON_OPTED_INIT count=" + initializationCount);
  }

  @Override
  protected boolean expectsOpenJ9() {
    return false;
  }
}
