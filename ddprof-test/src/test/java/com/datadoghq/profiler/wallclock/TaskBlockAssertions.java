package com.datadoghq.profiler.wallclock;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.HashSet;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

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
    private static final IAttribute<String> OBSERVED_BLOCKING_STATE =
            attr("observedBlockingState", "observedBlockingState", "Observed Blocking State", PLAIN_TEXT);

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
        assertTrue(
                containsObservedState(events, observedState),
                "Expected TaskBlock with observedBlockingState=" + observedState);
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

    static void assertContainsCorrelationId(IItemCollection taskBlockEvents) {
        Set<Long> correlationIds = nonZeroValues(taskBlockEvents, CORRELATION_ID);
        assertTrue(correlationIds.size() > 0, "Expected at least one non-zero TaskBlock correlationId");
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

    private static boolean containsObservedState(IItemCollection events, String observedState) {
        for (IItemIterable iterable : events) {
            IMemberAccessor<String, IItem> stateAccessor =
                    OBSERVED_BLOCKING_STATE.getAccessor(iterable.getType());
            if (stateAccessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                if (observedState.equals(stateAccessor.getMember(item))) {
                    return true;
                }
            }
        }
        return false;
    }

    private static Set<Long> nonZeroValues(IItemCollection events, IAttribute<IQuantity> attribute) {
        Set<Long> values = new HashSet<>();
        for (IItemIterable iterable : events) {
            IMemberAccessor<IQuantity, IItem> accessor = attribute.getAccessor(iterable.getType());
            if (accessor == null) {
                continue;
            }
            for (IItem item : iterable) {
                long value = accessor.getMember(item).longValue();
                if (value != 0) {
                    values.add(value);
                }
            }
        }
        return values;
    }
}
