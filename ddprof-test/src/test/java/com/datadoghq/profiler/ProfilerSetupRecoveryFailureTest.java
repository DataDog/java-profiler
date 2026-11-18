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
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Arrays;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInfo;

/**
 * Regression test for the failure paths of {@link AbstractProfilerTest#setupProfiler}'s recovery.
 * The recovery triggers only on {@code IllegalStateException: already started}; a different start
 * failure (here {@code event=noop} → "No profiling events specified") must propagate untouched,
 * while a genuine recovery keeps the original exception as primary and attaches secondary failures
 * as suppressed.
 */
public class ProfilerSetupRecoveryFailureTest extends AbstractProfilerTest {

  // Instance field: JUnit creates one instance per test method.
  private volatile boolean noopCommand = false;

  @Override
  protected String getProfilerCommand() {
    return noopCommand ? "event=noop" : "cpu=10ms";
  }

  @Test
  public void recoveryRestartsWhenAlreadyStarted(TestInfo testInfo) throws Exception {
    // The profiler is already running from @BeforeEach: recovery stops and restarts.
    assertDoesNotThrow(() -> setupProfiler(testInfo));
    assertFalse(stopped);
  }

  @Test
  public void invalidCommandDoesNotTriggerRecovery(TestInfo testInfo) throws Exception {
    stopProfiler();
    noopCommand = true;
    // Start fails with "No profiling events specified" while the singleton is
    // stopped. That is a test-authoring bug, not a poisoned singleton: the recovery
    // must not fire, so the failure propagates unmodified and the singleton state
    // is untouched.
    IllegalStateException thrown =
        assertThrows(IllegalStateException.class, () -> setupProfiler(testInfo));
    assertTrue(
        thrown.getMessage() != null && thrown.getMessage().contains("No profiling events"),
        "primary: " + thrown.getMessage());
    assertEquals(
        0,
        thrown.getSuppressed().length,
        "no recovery side effects expected: " + Arrays.toString(thrown.getSuppressed()));
    assertTrue(stopped, "recovery must not touch the singleton");
  }

  @Test
  public void retryFailureKeepsOriginalPrimary(TestInfo testInfo) throws Exception {
    noopCommand = true;
    // Start fails ("already started"), recovery stop() succeeds, the noop retry fails.
    IllegalStateException thrown =
        assertThrows(IllegalStateException.class, () -> setupProfiler(testInfo));
    String msg = thrown.getMessage();
    assertTrue(msg != null && msg.contains("already started"), "primary: " + msg);
    assertTrue(
        Arrays.stream(thrown.getSuppressed())
            .anyMatch(
                t ->
                    t instanceof IllegalStateException
                        && String.valueOf(t.getMessage()).contains("No profiling events")),
        "retry failure must be suppressed: " + Arrays.toString(thrown.getSuppressed()));
    // Recovery's stop() ran and the retry did not start it: really stopped. The
    // recovery itself resynced the stopped flag, so the base cleanup is a no-op.
    assertThrows(IllegalStateException.class, () -> profiler.stop());
  }
}
