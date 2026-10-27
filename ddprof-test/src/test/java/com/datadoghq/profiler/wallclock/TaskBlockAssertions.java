/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrFrame;
import com.datadoghq.profiler.Platform;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
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
  private static final String DURATION = "duration";

  private TaskBlockAssertions() {}

  /**
   * {@code java.vm.name} substrings that the native {@code VM::init()} (vmEntry.cpp) uses to set
   * {@code VM::isHotspot()}. Keep this list in sync with that check.
   */
  private static final String[] HOTSPOT_VM_NAME_MARKERS = {
    "OpenJDK", "HotSpot", "GraalVM", "Dynamic Code Evolution"
  };

  /**
   * Returns whether the native layer can classify the current thread as a platform thread on this
   * JVM. At JDK 19+, {@code JVMSupport::isPlatformThread()} fails closed when {@code
   * !VM::isHotspot()}, so {@code beginTaskBlock()} always returns {@code 0} there.
   *
   * <p>This predicate must not report support on a JVM that the native check rejects. It therefore
   * applies the same {@code java.vm.name} test as {@code VM::isHotspot()} instead of listing known
   * non-HotSpot JVMs: J9, Zing, and any unrecognized VM name are reported as unsupported.
   */
  static boolean platformThreadClassificationSupported() {
    return !Platform.isJavaVersionAtLeast(19)
        || isHotspotVmName(System.getProperty("java.vm.name"));
  }

  private static boolean isHotspotVmName(String vmName) {
    if (vmName == null) return false;
    for (String marker : HOTSPOT_VM_NAME_MARKERS) {
      if (vmName.contains(marker)) return true;
    }
    return false;
  }

  /**
   * Asserts that at least one event has a {@code duration} within {@code [minMillis, maxMillis]}.
   * The JFR parser normalizes the {@code @Timespan(TICKS)} duration to nanoseconds.
   */
  static void assertContainsDuration(JfrEvents events, long minMillis, long maxMillis) {
    List<Long> durations = new ArrayList<>();
    for (JfrEvent item : events) {
      Long millis = item.getNanosAsMillis(DURATION);
      if (millis == null) continue;
      if (millis >= minMillis && millis <= maxMillis) {
        return;
      }
      durations.add(millis);
    }
    throw new AssertionError("Expected TaskBlock duration in [" + minMillis + ", " + maxMillis
        + "] ms, got " + durations);
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
