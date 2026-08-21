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

import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
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
  private static final String EVENT_THREAD = "eventThread";
  private static final String DURATION = "duration";

  private TaskBlockAssertions() {}

  static boolean containsBlocker(JfrEvents events, long blocker) {
    for (JfrEvent item : events) {
      if (item.getLong(BLOCKER, Long.MIN_VALUE) == blocker) {
        return true;
      }
    }
    return false;
  }

  static int countBlockerEvents(JfrEvents events, long blocker) {
    int count = 0;
    for (JfrEvent item : events) {
      if (item.getLong(BLOCKER, Long.MIN_VALUE) == blocker) {
        count++;
      }
    }
    return count;
  }

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
      assertTrue(item.getLong(CORRELATION_ID, Long.MIN_VALUE) == 0,
          "Direct-stack TaskBlock must have correlationId=0");
    }
  }

  static void assertNoAnchorFields(JfrEvents events) {
    for (JfrEvent item : events) {
      assertNull(item.get(ANCHOR_SAMPLE_ID));
      assertNull(item.get(SUPPRESSED_SAMPLE_COUNT));
    }
  }

  static boolean containsObservedStateForEventThread(
      JfrEvents events, String observedState, String threadName) {
    for (JfrEvent item : events) {
      if (observedState.equals(item.getString(OBSERVED_BLOCKING_STATE))
          && threadName.equals(item.getThreadName(EVENT_THREAD))) {
        return true;
      }
    }
    return false;
  }

  static boolean containsEventThread(JfrEvents events, String threadName) {
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName(EVENT_THREAD))) {
        return true;
      }
    }
    return false;
  }

  static int countEventsForThread(JfrEvents events, String threadName) {
    int count = 0;
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName(EVENT_THREAD))) {
        count++;
      }
    }
    return count;
  }

  static double durationNanosForThread(JfrEvents events, String threadName) {
    double durationNanos = 0;
    for (JfrEvent item : events) {
      if (threadName.equals(item.getThreadName(EVENT_THREAD))) {
        durationNanos += item.getLong(DURATION, 0L);
      }
    }
    return durationNanos;
  }

  static boolean containsSpan(JfrEvents events, long spanId) {
    for (JfrEvent item : events) {
      if (item.getLong(AbstractProfilerTest.SPAN_ID, Long.MIN_VALUE) == spanId) {
        return true;
      }
    }
    return false;
  }

  static void assertBlockerEventThreadDiffers(
      JfrEvents events, long blocker, long logicalThreadId) {
    int checked = 0;
    for (JfrEvent item : events) {
      if (item.getLong(BLOCKER, Long.MIN_VALUE) != blocker) continue;
      Long eventThreadId = item.getThreadJavaId(EVENT_THREAD);
      assertNotNull(eventThreadId, "TaskBlock eventThread must not be null");
      assertNotEquals(Long.valueOf(logicalThreadId), eventThreadId,
          "Native TaskBlock must identify the physical carrier, not the virtual thread");
      checked++;
    }
    assertTrue(checked > 0, "Expected TaskBlock eventThread for blocker=" + blocker);
  }

  static Set<Long> distinctBlockers(JfrEvents events) {
    Set<Long> blockers = new HashSet<>();
    for (JfrEvent item : events) {
      blockers.add(item.getLong(BLOCKER, Long.MIN_VALUE));
    }
    return blockers;
  }
}
