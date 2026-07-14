/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.flightrecorder.JfrAttributes;

import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

/** Shared structural and semantic assertions for {@code datadog.TaskBlock} events. */
final class TaskBlockAssertions {
    private static final IAttribute<IQuantity> BLOCKER =
            attr("blocker", "blocker", "Blocker Identity Hash", NUMBER);
    private static final IAttribute<IQuantity> UNBLOCKING_SPAN_ID =
            attr("unblockingSpanId", "unblockingSpanId", "Unblocking Span ID", NUMBER);
    private static final IAttribute<IQuantity> ANCHOR_SAMPLE_ID =
            attr("anchorSampleId", "anchorSampleId", "Anchor MethodSample ID", NUMBER);
    private static final IAttribute<IQuantity> SUPPRESSED_SAMPLE_COUNT =
            attr("suppressedSampleCount", "suppressedSampleCount", "Suppressed Sample Count", NUMBER);
    private static final IAttribute<IQuantity> CORRELATION_ID =
            attr("correlationId", "correlationId", "Async Stack Trace Correlation ID", NUMBER);
    private static final IAttribute<IQuantity> METHOD_SAMPLE_ID =
            attr("sampleId", "sampleId", "Sample ID", NUMBER);
    private static final IAttribute<String> OBSERVED_BLOCKING_STATE =
            attr("observedBlockingState", "observedBlockingState", "Observed Blocking State", PLAIN_TEXT);
    private static final IAttribute<IQuantity> EPOCH_TASK_BLOCK_EMITTED =
            attr("numTaskBlockEmitted", "numTaskBlockEmitted", "Task-block events emitted", NUMBER);
    private static final IAttribute<IQuantity> EPOCH_TASK_BLOCK_SKIPPED_TRACE_CONTEXT =
            attr("numTaskBlockSkippedTraceContext", "numTaskBlockSkippedTraceContext",
                    "Task-block events skipped because trace context was present", NUMBER);
    private static final IAttribute<IQuantity> EPOCH_TASK_BLOCK_SKIPPED_TOO_SHORT =
            attr("numTaskBlockSkippedTooShort", "numTaskBlockSkippedTooShort",
                    "Task-block events skipped because duration was too short", NUMBER);

    private TaskBlockAssertions() {}

    static void assertContains(
            IItemCollection events, long rootSpanId, long spanId, long blocker, long unblockingSpanId) {
        assertTrue(
                contains(events, rootSpanId, spanId, blocker, unblockingSpanId),
                "Expected TaskBlock with rootSpanId=" + rootSpanId
                        + ", spanId=" + spanId
                        + ", blocker=" + blocker
                        + ", unblockingSpanId=" + unblockingSpanId);
    }

    static void assertContainsObservedState(IItemCollection events, String observedState) {
        Set<String> observedStates = observedStates(events);
        assertTrue(
                observedStates.contains(observedState),
                "Expected TaskBlock with observedBlockingState=" + observedState
                        + ", observed states were " + observedStates);
    }

    static void assertContainsAnyObservedState(IItemCollection events) {
        assertTrue(
                containsAnyObservedState(events),
                "Expected TaskBlock with an observedBlockingState field");
    }

    static void assertContainsBlocker(IItemCollection events, long blocker) {
        Set<Long> blockers = values(events, BLOCKER);
        assertTrue(
                blockers.contains(blocker),
                "Expected TaskBlock with blocker=" + blocker + ", observed blockers were " + blockers);
    }

    static boolean containsBlocker(IItemCollection events, long blocker) {
        return values(events, BLOCKER).contains(blocker);
    }

    static void assertBlockerEventThreadDiffers(
            IItemCollection events, long blocker, long logicalThreadId) {
        int checked = 0;
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> blockerAccessor = BLOCKER.getAccessor(iterable.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor =
                    JfrAttributes.EVENT_THREAD.getAccessor(iterable.getType());
            if (blockerAccessor == null || threadAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (blockerAccessor.getMember(item).longValue() != blocker) {
                    continue;
                }
                IMCThread eventThread = threadAccessor.getMember(item);
                assertNotNull(eventThread, "TaskBlock eventThread must not be null");
                assertNotEquals(
                        Long.valueOf(logicalThreadId),
                        eventThread.getThreadId(),
                        "Native TaskBlock must identify the physical carrier, not the virtual thread");
                checked++;
            }
        }
        assertTrue(checked > 0, "Expected TaskBlock eventThread for blocker=" + blocker);
    }

    static void assertNoAnchorFields(IItemCollection taskBlockEvents) {
        for (IItemIterable iterable : taskBlockEvents) {
            assertNull(
                    ANCHOR_SAMPLE_ID.getAccessor(iterable.getType()),
                    "TaskBlock must not expose anchorSampleId");
            assertNull(
                    SUPPRESSED_SAMPLE_COUNT.getAccessor(iterable.getType()),
                    "TaskBlock must not expose suppressedSampleCount");
        }
    }

    static void assertContainsStackTrace(IItemCollection taskBlockEvents) {
        int checked = 0;
        for (IItemIterable iterable : taskBlockEvents) {
            IMemberAccessor<IMCStackTrace, IItem> stackTraceAccessor =
                    AbstractProfilerTest.STACK_TRACE.getAccessor(iterable.getType());
            assertTrue(stackTraceAccessor != null, "TaskBlock must expose stackTrace");
            for (IItem item : iterable) {
                checked++;
                IMCStackTrace stackTrace = stackTraceAccessor.getMember(item);
                assertTrue(stackTrace != null, "TaskBlock stackTrace must not be null");
                assertTrue(!stackTrace.getFrames().isEmpty(), "TaskBlock stackTrace must not be empty");
            }
        }
        assertTrue(checked > 0, "Expected at least one TaskBlock with a non-empty stackTrace");
    }

    static void assertContainsEventThread(IItemCollection taskBlockEvents) {
        int checked = 0;
        for (IItemIterable iterable : taskBlockEvents) {
            IMemberAccessor<IMCThread, IItem> threadAccessor =
                    JfrAttributes.EVENT_THREAD.getAccessor(iterable.getType());
            assertNotNull(threadAccessor, "TaskBlock must expose eventThread");
            for (IItem item : iterable) {
                checked++;
                assertNotNull(threadAccessor.getMember(item), "TaskBlock eventThread must not be null");
            }
        }
        assertTrue(checked > 0, "Expected at least one TaskBlock with an eventThread");
    }

    static void assertContainsCorrelationId(IItemCollection taskBlockEvents) {
        Set<Long> correlationIds = nonZeroValues(taskBlockEvents, CORRELATION_ID);
        assertTrue(correlationIds.size() > 0, "Expected at least one non-zero TaskBlock correlationId");
    }

    static void assertMethodSampleSchemaHasCorrelationIdButNoSampleId(IItemCollection methodSampleEvents) {
        int checked = 0;
        for (IItemIterable iterable : methodSampleEvents) {
            checked++;
            assertTrue(
                    CORRELATION_ID.getAccessor(iterable.getType()) != null,
                    "MethodSample must expose correlationId");
            assertNull(
                    METHOD_SAMPLE_ID.getAccessor(iterable.getType()),
                    "MethodSample must not expose sampleId");
        }
        assertTrue(checked > 0, "Expected at least one MethodSample type to inspect");
    }

    static void assertWallClockEpochDoesNotExposeTaskBlockCounters(IItemCollection epochEvents) {
        int checked = 0;
        for (IItemIterable iterable : epochEvents) {
            checked++;
            assertNull(
                    EPOCH_TASK_BLOCK_EMITTED.getAccessor(iterable.getType()),
                    "WallClockSamplingEpoch must not expose numTaskBlockEmitted");
            assertNull(
                    EPOCH_TASK_BLOCK_SKIPPED_TRACE_CONTEXT.getAccessor(iterable.getType()),
                    "WallClockSamplingEpoch must not expose numTaskBlockSkippedTraceContext");
            assertNull(
                    EPOCH_TASK_BLOCK_SKIPPED_TOO_SHORT.getAccessor(iterable.getType()),
                    "WallClockSamplingEpoch must not expose numTaskBlockSkippedTooShort");
        }
        assertTrue(checked > 0, "Expected at least one WallClockSamplingEpoch type to inspect");
    }

    static boolean containsSpan(IItemCollection events, long spanId) {
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> spanAccessor =
                    AbstractProfilerTest.SPAN_ID.getAccessor(iterable.getType());
            if (spanAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (spanAccessor.getMember(item).longValue() == spanId) {
                    return true;
                }
            }
        }
        return false;
    }

    private static boolean contains(
            IItemCollection events, long rootSpanId, long spanId, long blocker, long unblockingSpanId) {
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> rootSpanAccessor =
                    AbstractProfilerTest.LOCAL_ROOT_SPAN_ID.getAccessor(iterable.getType());
            IMemberAccessor<IQuantity, IItem> spanAccessor =
                    AbstractProfilerTest.SPAN_ID.getAccessor(iterable.getType());
            IMemberAccessor<IQuantity, IItem> blockerAccessor = BLOCKER.getAccessor(iterable.getType());
            IMemberAccessor<IQuantity, IItem> unblockingSpanAccessor =
                    UNBLOCKING_SPAN_ID.getAccessor(iterable.getType());
            if (rootSpanAccessor == null || spanAccessor == null || blockerAccessor == null
                    || unblockingSpanAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (rootSpanAccessor.getMember(item).longValue() == rootSpanId
                        && spanAccessor.getMember(item).longValue() == spanId
                        && blockerAccessor.getMember(item).longValue() == blocker
                        && unblockingSpanAccessor.getMember(item).longValue() == unblockingSpanId) {
                    return true;
                }
            }
        }
        return false;
    }

    static Set<String> observedStates(IItemCollection events) {
        Set<String> states = new HashSet<>();
        for (IItemIterable iterable : events) {
            IMemberAccessor<String, IItem> stateAccessor =
                    OBSERVED_BLOCKING_STATE.getAccessor(iterable.getType());
            if (stateAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                String state = stateAccessor.getMember(item);
                if (state != null) {
                    states.add(state);
                }
            }
        }
        return states;
    }

    private static boolean containsAnyObservedState(IItemCollection events) {
        for (IItemIterable iterable : events) {
            IMemberAccessor<String, IItem> stateAccessor =
                    OBSERVED_BLOCKING_STATE.getAccessor(iterable.getType());
            if (stateAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (stateAccessor.getMember(item) != null) {
                    return true;
                }
            }
        }
        return false;
    }

    private static Set<Long> nonZeroValues(IItemCollection events, IAttribute<IQuantity> attribute) {
        Set<Long> values = values(events, attribute);
        values.remove(0L);
        return values;
    }

    private static Set<Long> values(IItemCollection events, IAttribute<IQuantity> attribute) {
        Set<Long> values = new HashSet<>();
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> accessor = attribute.getAccessor(iterable.getType());
            if (accessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                long value = accessor.getMember(item).longValue();
                values.add(value);
            }
        }
        return values;
    }
}
