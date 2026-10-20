/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Assumptions;

/** Verifies wall-tail trace preservation after the live-heap liveness checker is registered. */
public class LiveHeapThenUnownedBlockedTailDumpTest extends UnownedBlockedTailDumpTest {
  /**
   * Starts and stops a live-heap recording before each wall recording. Its liveness checker remains
   * registered and must preserve IDs contributed by the wall-tail checker even with no live objects.
   */
  @Override
  protected void beforeProfilerStart() throws Exception {
    Assumptions.assumeTrue(isDebugBuild(), "Requires the debug-only synchronous sampling driver");
    Path liveRecording = Files.createTempFile("live-heap-before-wall-tail-", ".jfr");
    try {
      profiler.execute("start,memory=256:L,jfr,file=" + liveRecording.toAbsolutePath());
    } finally {
      profiler.stop();
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(liveRecording);
      }
    }
  }
}
