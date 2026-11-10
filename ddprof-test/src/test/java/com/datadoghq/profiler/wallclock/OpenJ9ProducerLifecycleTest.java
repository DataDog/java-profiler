/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfEnvironmentVariable;

/** Requires genuine OpenJ9 rather than an external job or container label. */
@EnabledIfEnvironmentVariable(named = "DDPROF_EXPECTED_VM", matches = "openj9")
public class OpenJ9ProducerLifecycleTest extends RealVmProducerTest {
  /** Verifies ordinary wall stacks and unsupported paired admission across restart. */
  @Test
  public void genuineOpenJ9RecordingAndJniLifecycleSurviveRestart() throws Exception {
    verifyRetainedWorkerAcrossRestart();
  }

  @Override
  protected boolean expectsOpenJ9() {
    return true;
  }
}
