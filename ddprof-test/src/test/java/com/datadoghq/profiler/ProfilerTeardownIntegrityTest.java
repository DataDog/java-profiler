/*
 * Copyright 2026, Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.Test;

/**
 * Regression test for {@link AbstractProfilerTest#cleanup()}: {@code stopProfiler()} must run even
 * when {@code after()} throws. Without that guarantee a single test throwing out of {@code after()}
 * leaves the process-wide profiler started and every later test in the JVM fails with {@code
 * IllegalStateException: Profiler already started}.
 */
public class ProfilerTeardownIntegrityTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    return "cpu=10ms";
  }

  private static volatile boolean afterThrows;

  @Override
  protected void after() {
    if (afterThrows) {
      throw new RuntimeException("simulated after() failure");
    }
  }

  @Test
  public void profilerIsStoppedEvenWhenAfterThrows() throws Exception {
    Path jfr = Files.createTempFile("profiler-teardown-integrity", ".jfr");
    afterThrows = true;
    try {
      // Deliberately run the teardown mid-test: after() throws, and the finally
      // around stopProfiler() must still have stopped the singleton.
      assertThrows(RuntimeException.class, () -> cleanup());
      assertTrue(stopped, "stopProfiler must run even when after() throws");
      // Behavioral proof that the singleton is really stopped: a fresh start succeeds.
      // Without the finally this fails with IllegalStateException (already started).
      assertDoesNotThrow(
          () -> {
            profiler.execute("start,cpu=10ms,jfr,file=" + jfr.toAbsolutePath());
            // Resync right after the restart so the finally below stops it even if a
            // later statement fails.
            stopped = false;
            // Mid-test cleanup already deleted the original recording (bookkeeping
            // now runs even when after() throws); point checkConfig at the live one.
            jfrDump = jfr;
          });
    } finally {
      afterThrows = false;
      try {
        // Leave the instance stopped so the base class's end-of-test cleanup is a
        // no-op. Stop before delete so the recording is not unlinked mid-write.
        stopProfiler();
      } finally {
        Files.deleteIfExists(jfr);
      }
    }
  }
}
