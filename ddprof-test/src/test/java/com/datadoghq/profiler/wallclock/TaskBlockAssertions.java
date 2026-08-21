/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/** Assertions for the synchronous {@code datadog.TaskBlock} event contract. */
final class TaskBlockAssertions {
  private static final String BLOCKER = "blocker";
  private static final String UNBLOCKING_SPAN_ID = "unblockingSpanId";
  private static final String ANCHOR_SAMPLE_ID = "anchorSampleId";
  private static final String SUPPRESSED_SAMPLE_COUNT = "suppressedSampleCount";
  private static final String OBSERVED_BLOCKING_STATE = "observedBlockingState";
  private static final String CORRELATION_ID = "correlationId";

  private TaskBlockAssertions() {}

  static void assertContains(JfrEvents events, long rootSpanId, long spanId,
      long blocker, long unblockingSpanId) {
    for (JfrEvent item : events) {
      if (item.getLong(AbstractProfilerTest.LOCAL_ROOT_SPAN_ID, Long.MIN_VALUE) == rootSpanId
          && item.getLong(AbstractProfilerTest.SPAN_ID, Long.MIN_VALUE) == spanId
          && item.getLong(BLOCKER, Long.MIN_VALUE) == blocker
          && item.getLong(UNBLOCKING_SPAN_ID, Long.MIN_VALUE) == unblockingSpanId) {
        return;
      }
    }
    throw new AssertionError("Expected TaskBlock blocker=" + blocker
        + ", unblockingSpanId=" + unblockingSpanId);
  }

  static void assertContainsObservedState(JfrEvents events, String expected) {
    Set<String> states = new HashSet<>();
    for (JfrEvent item : events) {
      states.add(item.getString(OBSERVED_BLOCKING_STATE));
    }
    assertTrue(states.contains(expected), () -> "Observed states: " + states);
  }

  static void assertContainsStackTrace(JfrEvents events) {
    int count = 0;
    for (JfrEvent item : events) {
      assertTrue(!item.getStackTrace().isEmpty());
      count++;
    }
    assertTrue(count > 0, "Expected a TaskBlock with a non-empty stack");
  }

  static void assertContainsNoStackTrace(JfrEvents events) {
    int count = 0;
    for (JfrEvent item : events) {
      assertTrue(item.getStackTrace().isEmpty());
      count++;
    }
    assertTrue(count > 0, "Expected a TaskBlock without a stack");
  }

  static void assertContainsJavaType(JfrEvents events, String expected) {
    for (JfrEvent item : events) {
      if (!item.has(AbstractProfilerTest.STACK_TRACE)) continue;
      for (JfrFrame frame : item.getStackTrace().frames()) {
        String className = frame.className();
        if (className != null && className.contains(expected)) {
          return;
        }
      }
    }
    throw new AssertionError("Expected TaskBlock stack type containing " + expected);
  }

  static void assertNoCorrelationId(JfrEvents events) {
    for (JfrEvent item : events) {
      assertNull(item.get(CORRELATION_ID));
    }
  }

  static void assertNoAnchorFields(JfrEvents events) {
    for (JfrEvent item : events) {
      assertNull(item.get(ANCHOR_SAMPLE_ID));
      assertNull(item.get(SUPPRESSED_SAMPLE_COUNT));
    }
  }
}
