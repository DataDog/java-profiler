/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import java.util.HashSet;
import java.util.Set;
import org.openjdk.jmc.common.IMCFrame;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

/** Assertions for the synchronous {@code datadog.TaskBlock} event contract. */
final class TaskBlockAssertions {
  private static final IAttribute<IQuantity> BLOCKER =
      attr("blocker", "blocker", "Blocker Identity Hash", NUMBER);
  private static final IAttribute<IQuantity> UNBLOCKING_SPAN_ID =
      attr("unblockingSpanId", "unblockingSpanId", "Unblocking Span ID", NUMBER);
  private static final IAttribute<IQuantity> ANCHOR_SAMPLE_ID =
      attr("anchorSampleId", "anchorSampleId", "Anchor MethodSample ID", NUMBER);
  private static final IAttribute<IQuantity> SUPPRESSED_SAMPLE_COUNT =
      attr("suppressedSampleCount", "suppressedSampleCount", "Suppressed Sample Count", NUMBER);
  private static final IAttribute<String> OBSERVED_BLOCKING_STATE =
      attr("observedBlockingState", "observedBlockingState", "Observed Blocking State", PLAIN_TEXT);
  private static final IAttribute<IQuantity> CORRELATION_ID =
      attr("correlationId", "correlationId", "Async Stack Trace Correlation ID", NUMBER);

  private TaskBlockAssertions() {}

  static void assertContains(IItemCollection events, long rootSpanId, long spanId,
      long blocker, long unblockingSpanId) {
    for (IItemIterable iterable : events) {
      IMemberAccessor<IQuantity, IItem> root =
          AbstractProfilerTest.LOCAL_ROOT_SPAN_ID.getAccessor(iterable.getType());
      IMemberAccessor<IQuantity, IItem> span =
          AbstractProfilerTest.SPAN_ID.getAccessor(iterable.getType());
      IMemberAccessor<IQuantity, IItem> blockerAccessor =
          BLOCKER.getAccessor(iterable.getType());
      IMemberAccessor<IQuantity, IItem> unblocking =
          UNBLOCKING_SPAN_ID.getAccessor(iterable.getType());
      if (root == null || span == null || blockerAccessor == null || unblocking == null) continue;
      for (IItem item : iterable) {
        if (root.getMember(item).longValue() == rootSpanId
            && span.getMember(item).longValue() == spanId
            && blockerAccessor.getMember(item).longValue() == blocker
            && unblocking.getMember(item).longValue() == unblockingSpanId) {
          return;
        }
      }
    }
    throw new AssertionError("Expected TaskBlock blocker=" + blocker
        + ", unblockingSpanId=" + unblockingSpanId);
  }

  static void assertContainsObservedState(IItemCollection events, String expected) {
    Set<String> states = new HashSet<>();
    for (IItemIterable iterable : events) {
      IMemberAccessor<String, IItem> accessor =
          OBSERVED_BLOCKING_STATE.getAccessor(iterable.getType());
      if (accessor == null) continue;
      for (IItem item : iterable) states.add(accessor.getMember(item));
    }
    assertTrue(states.contains(expected), () -> "Observed states: " + states);
  }

  static void assertContainsStackTrace(IItemCollection events) {
    int count = 0;
    for (IItemIterable iterable : events) {
      IMemberAccessor<IMCStackTrace, IItem> accessor =
          AbstractProfilerTest.STACK_TRACE.getAccessor(iterable.getType());
      assertTrue(accessor != null, "TaskBlock must expose stackTrace");
      for (IItem item : iterable) {
        IMCStackTrace stack = accessor.getMember(item);
        assertTrue(stack != null && !stack.getFrames().isEmpty());
        count++;
      }
    }
    assertTrue(count > 0, "Expected a TaskBlock with a non-empty stack");
  }

  static void assertContainsJavaType(IItemCollection events, String expected) {
    for (IItemIterable iterable : events) {
      IMemberAccessor<IMCStackTrace, IItem> accessor =
          AbstractProfilerTest.STACK_TRACE.getAccessor(iterable.getType());
      if (accessor == null) continue;
      for (IItem item : iterable) {
        IMCStackTrace stack = accessor.getMember(item);
        if (stack == null) continue;
        for (IMCFrame frame : stack.getFrames()) {
          if (frame.getMethod() != null
              && frame.getMethod().getType() != null
              && frame.getMethod().getType().getFullName().contains(expected)) {
            return;
          }
        }
      }
    }
    throw new AssertionError("Expected TaskBlock stack type containing " + expected);
  }

  static void assertNoCorrelationId(IItemCollection events) {
    for (IItemIterable iterable : events) {
      assertNull(CORRELATION_ID.getAccessor(iterable.getType()));
    }
  }

  static void assertNoAnchorFields(IItemCollection events) {
    for (IItemIterable iterable : events) {
      assertNull(ANCHOR_SAMPLE_ID.getAccessor(iterable.getType()));
      assertNull(SUPPRESSED_SAMPLE_COUNT.getAccessor(iterable.getType()));
    }
  }
}
