/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.atomic.AtomicInteger;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.NullSource;
import org.junit.jupiter.params.provider.ValueSource;

/** Checks stop admission independently of native timing and the process-wide singleton. */
class AbstractProfilerStopRetryTest {
  @Test
  void successfulStopIsNotRepeated() {
    AtomicInteger attempts = new AtomicInteger();
    AbstractProfilerTest.stopRetryingOnTransientFailure(attempts::incrementAndGet);
    assertEquals(1, attempts.get());
  }

  @ParameterizedTest
  @ValueSource(
      strings = {
        "signal handlers did not drain; teardown skipped, retry stop()",
        "task-block rotation did not drain; teardown skipped, retry stop()",
        "pending wall-clock tails could not be written; teardown skipped"
      })
  void retriesOnlyUntilStopSucceeds(String message) {
    AtomicInteger attempts = new AtomicInteger();
    AbstractProfilerTest.stopRetryingOnTransientFailure(
        () -> {
          if (attempts.incrementAndGet() == 1) throw new IllegalStateException(message);
        });
    assertEquals(2, attempts.get());
  }

  @Test
  void tenthAttemptCanSucceed() {
    AtomicInteger attempts = new AtomicInteger();
    AbstractProfilerTest.stopRetryingOnTransientFailure(
        () -> {
          if (attempts.incrementAndGet() < 10) {
            throw new IllegalStateException(
                "pending wall-clock tails could not be written; teardown skipped");
          }
        });
    assertEquals(10, attempts.get());
  }

  @ParameterizedTest
  @ValueSource(
      strings = {
        "signal handlers did not drain; teardown skipped, retry stop()",
        "task-block rotation did not drain; teardown skipped, retry stop()",
        "pending wall-clock tails could not be written; teardown skipped"
      })
  void exhaustionRethrowsLastFailure(String message) {
    AtomicInteger attempts = new AtomicInteger();
    IllegalStateException last = new IllegalStateException(message);
    IllegalStateException actual =
        assertThrows(
            IllegalStateException.class,
            () ->
                AbstractProfilerTest.stopRetryingOnTransientFailure(
                    () -> {
                      if (attempts.incrementAndGet() == 10) throw last;
                      throw new IllegalStateException(message);
                    }));
    assertSame(last, actual);
    assertEquals(10, attempts.get());
  }

  @ParameterizedTest
  @NullSource
  @ValueSource(
      strings = {
        "",
        "Profiler is not active",
        "Profiler is in error state",
        "recording output is quarantined",
        "thread hook calls did not drain; the profiler is stopped",
        "thread hook calls did not drain; the profiler is disabled",
        "task-block rotation did not drain; dump skipped",
        "pending wall-clock tails could not be written"
      })
  void terminalAndUnrecognizedFailuresAreNotRetried(String message) {
    AtomicInteger attempts = new AtomicInteger();
    IllegalStateException terminal = new IllegalStateException(message);
    assertSame(
        terminal,
        assertThrows(
            IllegalStateException.class,
            () ->
                AbstractProfilerTest.stopRetryingOnTransientFailure(
                    () -> {
                      attempts.incrementAndGet();
                      throw terminal;
                    })));
    assertEquals(1, attempts.get());
  }

  @Test
  void retryStopsImmediatelyOnTerminalFailure() {
    AtomicInteger attempts = new AtomicInteger();
    IllegalStateException terminal = new IllegalStateException("recording output is quarantined");
    assertSame(
        terminal,
        assertThrows(
            IllegalStateException.class,
            () ->
                AbstractProfilerTest.stopRetryingOnTransientFailure(
                    () -> {
                      if (attempts.incrementAndGet() == 1) {
                        throw new IllegalStateException(
                            "pending wall-clock tails could not be written; teardown skipped");
                      }
                      throw terminal;
                    })));
    assertEquals(2, attempts.get());
  }

  @Test
  void otherExceptionTypesAreNotRetried() {
    AtomicInteger attempts = new AtomicInteger();
    IllegalArgumentException failure = new IllegalArgumentException("invalid stop");
    assertSame(
        failure,
        assertThrows(
            IllegalArgumentException.class,
            () ->
                AbstractProfilerTest.stopRetryingOnTransientFailure(
                    () -> {
                      attempts.incrementAndGet();
                      throw failure;
                    })));
    assertEquals(1, attempts.get());
  }

  @Test
  void interruptionPreservesFlagAndOriginalFailure() {
    AtomicInteger attempts = new AtomicInteger();
    IllegalStateException failure =
        new IllegalStateException(
            "pending wall-clock tails could not be written; teardown skipped");
    try {
      assertSame(
          failure,
          assertThrows(
              IllegalStateException.class,
              () ->
                  AbstractProfilerTest.stopRetryingOnTransientFailure(
                      () -> {
                        attempts.incrementAndGet();
                        Thread.currentThread().interrupt();
                        throw failure;
                      })));
      assertTrue(Thread.currentThread().isInterrupted());
      assertEquals(1, attempts.get());
    } finally {
      Thread.interrupted();
    }
  }
}
