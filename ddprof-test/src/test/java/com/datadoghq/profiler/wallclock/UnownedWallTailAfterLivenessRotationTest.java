/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JfrEvent;
import java.nio.file.Files;
import java.nio.file.Path;

/** Checks wall-stack preservation after a real recording has registered the heap collector. */
public class UnownedWallTailAfterLivenessRotationTest extends UnownedWallTailRotationTest {
  /** Leaves time for the dumps before the ten-signal cadence refreshes the cached blocked stack. */
  @Override
  protected String getProfilerCommand() {
    return "wall=100ms,wallprecheck=true,jvmtistacks=false";
  }

  /**
   * Leaves the production heap callback registered but disabled in the subsequent wall recording.
   */
  @Override
  protected void beforeProfilerStart() throws Exception {
    Path heapRecording = Files.createTempFile("unowned-tail-prior-liveness-", ".jfr");
    try {
      profiler.execute("start,memory=1m:l,jfr,file=" + heapRecording.toAbsolutePath());
      profiler.stop();
      int heapConfigs = 0;
      for (JfrEvent config : verifyEvents(heapRecording, "datadog.DatadogProfilerConfig", true)) {
        assertTrue(config.getLong("memleakInterval", 0) > 0, "Heap tracking did not start");
        assertTrue(config.getLong("memleakCapacity", 0) > 0, "Heap tracker was not initialized");
        heapConfigs++;
      }
      assertEquals(1, heapConfigs, "Missing heap recording configuration");
    } finally {
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(heapRecording);
      }
    }
  }
}
