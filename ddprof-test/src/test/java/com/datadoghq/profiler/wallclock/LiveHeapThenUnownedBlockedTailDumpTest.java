/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Assumptions;

/** Verifies wall-tail trace preservation after the live-heap liveness checker is registered. */
public class LiveHeapThenUnownedBlockedTailDumpTest extends UnownedBlockedTailDumpTest {
  /** Requires a JVM that supports live-heap allocation sampling. */
  @Override
  protected boolean isPlatformSupported() {
    return super.isPlatformSupported() && Platform.isJavaVersionAtLeast(11);
  }

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
      profiler.stop();
    } finally {
      if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
        Files.deleteIfExists(liveRecording);
      }
    }
  }
}
