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
import static org.junit.jupiter.api.Assertions.assertFalse;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.file.Files;
import java.nio.file.Path;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Test;

/**
 * Regression test for {@link AbstractProfilerTest#setupProfiler}: when a test leaves the
 * process-wide profiler started, the base class must recover instead of failing every later test in
 * the JVM with {@code IllegalStateException: Profiler already started}. The static initializer
 * starts the profiler behind the base class's back, so without the recovery the setup of the single
 * test below fails and this class goes red; if that precondition cannot be established the class
 * fails instead of passing vacuously.
 */
public class ProfilerSetupRecoveryTest extends AbstractProfilerTest {

  @Override
  protected String getProfilerCommand() {
    return "cpu=10ms";
  }

  private static final Path STARTED_JFR;

  static {
    try {
      STARTED_JFR = Files.createTempFile("profiler-setup-recovery", ".jfr");
    } catch (IOException e) {
      throw new UncheckedIOException(e);
    }
    try {
      JavaProfiler.getInstance().execute("start,cpu=10ms,jfr,file=" + STARTED_JFR.toAbsolutePath());
    } catch (IllegalStateException e) {
      // Only "already started" (another test left it running) still establishes
      // the precondition; anything else must fail the class, not pass it vacuously.
      String msg = e.getMessage();
      if (msg == null || !msg.contains("already started")) {
        discardStartedJfr();
        throw e;
      }
    } catch (IOException e) {
      discardStartedJfr();
      throw new UncheckedIOException(e);
    } catch (Throwable e) {
      // JNI/class-loading failures (LinkageError & co) must also clean up: JUnit
      // skips @AfterAll when a static initializer throws. IOException is handled
      // above, so precise rethrow leaves only unchecked types here.
      discardStartedJfr();
      throw e;
    }
  }

  // JUnit skips @AfterAll when a static initializer throws, so the failure paths
  // above must clean up the temp file themselves or it leaks into /tmp.
  private static void discardStartedJfr() {
    try {
      JavaProfiler.getInstance().stop();
    } catch (Exception ignored) {
      // best effort: the singleton may not be running
    }
    if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
      try {
        Files.deleteIfExists(STARTED_JFR);
      } catch (IOException ignored) {
        // best effort
      }
    }
  }

  @AfterAll
  static void deleteStartedJfr() throws IOException {
    // The profiler writing this file was stopped by setupProfiler's recovery.
    if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) {
      Files.deleteIfExists(STARTED_JFR);
    }
  }

  @Test
  public void setupRecoversFromStuckSingleton() throws Exception {
    // setupProfiler must have actually recovered: stopped is resynced to false only
    // after a successful recovery (stop + retry), and a dump succeeds only on a
    // running profiler. A no-op recovery (stop without retry) fails here instead of
    // poisoning every later test class in this JVM.
    assertFalse(stopped);
    assertDoesNotThrow(() -> profiler.dump(jfrDump));
  }
}
