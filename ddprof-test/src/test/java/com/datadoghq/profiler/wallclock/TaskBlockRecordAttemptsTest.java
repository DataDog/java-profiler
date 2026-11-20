/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;
import org.junit.jupiter.api.Test;
import org.opentest4j.AssertionFailedError;

/** Covers the counter-accounted retry contract shared by TaskBlock recorder tests. */
class TaskBlockRecordAttemptsTest {
  private final Map<String, Long> counters = new HashMap<>();
  private final AtomicInteger attempts = new AtomicInteger();

  private void reject(boolean counted) {
    if (counted) counters.merge("task_block_record_failed", 1L, Long::sum);
  }

  @Test
  void firstRecordedAttemptNeedsNoCredit() throws Exception {
    TaskBlockRecorderTestSupport.recordWithinAttempts(
        () -> counters,
        () -> {
          attempts.incrementAndGet();
          return true;
        });
    assertEquals(1, attempts.get());
  }

  @Test
  void countedRejectionIsRetried() throws Exception {
    TaskBlockRecorderTestSupport.recordWithinAttempts(
        () -> counters,
        () -> {
          if (attempts.incrementAndGet() == 1) {
            reject(true);
            return false;
          }
          return true;
        });
    assertEquals(2, attempts.get());
  }

  @Test
  void uncountedRejectionFails() {
    AssertionFailedError failure =
        assertThrows(
            AssertionFailedError.class,
            () ->
                TaskBlockRecorderTestSupport.recordWithinAttempts(
                    () -> counters,
                    () -> {
                      attempts.incrementAndGet();
                      reject(false);
                      return false;
                    }));
    assertTrue(failure.getMessage().contains("not accounted"), failure.getMessage());
    assertEquals(1, attempts.get());
  }

  @Test
  void missingCounterGivesNoCredit() {
    assertThrows(
        AssertionFailedError.class,
        () ->
            TaskBlockRecorderTestSupport.recordWithinAttempts(Collections::emptyMap, () -> false));
  }

  @Test
  void recordedAttemptWithExtraFailureFails() {
    AssertionFailedError failure =
        assertThrows(
            AssertionFailedError.class,
            () ->
                TaskBlockRecorderTestSupport.recordWithinAttempts(
                    () -> counters,
                    () -> {
                      reject(true);
                      return true;
                    }));
    assertTrue(failure.getMessage().contains("also counted"), failure.getMessage());
  }

  @Test
  void attemptsAreBounded() {
    AssertionFailedError failure =
        assertThrows(
            AssertionFailedError.class,
            () ->
                TaskBlockRecorderTestSupport.recordWithinAttempts(
                    () -> counters,
                    () -> {
                      attempts.incrementAndGet();
                      reject(true);
                      return false;
                    }));
    assertTrue(failure.getMessage().contains("bounded attempts"), failure.getMessage());
    assertEquals(TaskBlockRecorderTestSupport.MAX_RECORD_ATTEMPTS, attempts.get());
  }

  private void lowerBound(TaskBlockRecorderTestSupport.Attempt attempt) throws Exception {
    TaskBlockRecorderTestSupport.recordWithinAttempts(
        () -> counters, TaskBlockRecorderTestSupport.Credit.LOWER_BOUND, "lower bound", attempt);
  }

  @Test
  void lowerBoundAcceptsForeignFailuresAroundSuccess() throws Exception {
    lowerBound(
        () -> {
          reject(true);
          reject(true);
          return attempts.incrementAndGet() > 1;
        });
    assertEquals(2, attempts.get());
  }

  @Test
  void lowerBoundStillRejectsUncountedFalse() {
    AssertionFailedError failure =
        assertThrows(
            AssertionFailedError.class,
            () ->
                lowerBound(
                    () -> {
                      attempts.incrementAndGet();
                      return false;
                    }));
    assertTrue(failure.getMessage().contains("not accounted"), failure.getMessage());
    assertEquals(1, attempts.get());
  }

  @Test
  void lowerBoundRequiresCreditForEveryRejection() {
    assertThrows(
        AssertionFailedError.class,
        () ->
            lowerBound(
                () -> {
                  if (attempts.incrementAndGet() == 1) reject(true);
                  return false;
                }));
    assertEquals(2, attempts.get());
  }

  @Test
  void lowerBoundAttemptsAreBounded() {
    AssertionFailedError failure =
        assertThrows(
            AssertionFailedError.class,
            () ->
                lowerBound(
                    () -> {
                      attempts.incrementAndGet();
                      reject(true);
                      return false;
                    }));
    assertTrue(failure.getMessage().contains("bounded attempts"), failure.getMessage());
    assertEquals(TaskBlockRecorderTestSupport.MAX_RECORD_ATTEMPTS, attempts.get());
  }

  @Test
  void exactModeRejectsForeignFailureOnRejection() {
    assertThrows(
        AssertionFailedError.class,
        () ->
            TaskBlockRecorderTestSupport.recordWithinAttempts(
                () -> counters,
                () -> {
                  reject(true);
                  reject(true);
                  return false;
                }));
  }
}
