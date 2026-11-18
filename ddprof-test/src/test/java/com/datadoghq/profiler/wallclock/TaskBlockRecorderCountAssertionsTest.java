/* Copyright 2026, Datadog, Inc. */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import org.junit.jupiter.api.Test;

/** Controls the rejection-conditioned count oracle without requiring native recorder contention. */
class TaskBlockRecorderCountAssertionsTest {
  @Test
  void fullCountNeedsNoRejection() {
    TaskBlockRecorderTestSupport.assertCompletedIntervals(5, 5, 0, "full count");
  }

  @Test
  void recorderRejectionAccountsForMissingInterval() {
    TaskBlockRecorderTestSupport.assertCompletedIntervals(4, 5, 1, "one rejection");
  }

  @Test
  void insufficientRejectionsDoNotExcuseMissingIntervals() {
    assertThrows(
        AssertionError.class,
        () -> TaskBlockRecorderTestSupport.assertCompletedIntervals(4, 5, 0, "no rejection"));
    assertThrows(
        AssertionError.class,
        () -> TaskBlockRecorderTestSupport.assertCompletedIntervals(3, 5, 1, "short by one"));
  }

  @Test
  void everyAttemptMayBeRejectedButAllMustBeAccountedFor() {
    TaskBlockRecorderTestSupport.assertCompletedIntervals(0, 5, 5, "all rejected");
    assertThrows(
        AssertionError.class,
        () -> TaskBlockRecorderTestSupport.assertCompletedIntervals(0, 5, 4, "short by one"));
    TaskBlockRecorderTestSupport.assertCompletedIntervals(0, 1, 1, "selector rejection");
  }

  @Test
  void onlyRecordFailedCounterProvidesCredit() {
    Map<String, Long> counters = new HashMap<>();
    for (String name :
        new String[] {
          "task_block_stack_capture_failed", "task_block_skipped_too_short",
          "task_block_dropped_rotation", "task_block_dropped_admission"
        }) {
      counters.put(name, 100L);
    }
    assertEquals(0, TaskBlockRecorderTestSupport.recordFailures(counters));
    counters.put("task_block_record_failed", 1L);
    assertEquals(1, TaskBlockRecorderTestSupport.recordFailures(counters));
    assertEquals(0, TaskBlockRecorderTestSupport.recordFailures(Collections.emptyMap()));
  }
}
