package com.datadoghq.profiler.socket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.NUMBER;

/**
 * Tests for native socket event recording via the Java API.
 */
public class NativeSocketEventTest extends AbstractProfilerTest {
    private static final IAttribute<IQuantity> FD_ATTR =
            attr("fd", "", "", NUMBER);
    private static final IAttribute<IQuantity> BYTES_ATTR =
            attr("bytesTransferred", "", "", NUMBER);
    private static final IAttribute<IQuantity> OPERATION_ATTR =
            attr("operation", "", "", NUMBER);

    @Override
    protected String getProfilerCommand() {
        return "cpu=10ms";
    }

    @Test
    public void testRecordSocketEvent() throws Exception {
        long start = profiler.getCurrentTicks();
        Thread.sleep(1);
        long end = profiler.getCurrentTicks();

        // Record a recv event
        profiler.recordNativeSocketEvent(start, end, 42, 1024, JavaProfiler.SOCKET_OP_RECV);

        // Record a send event
        start = profiler.getCurrentTicks();
        Thread.sleep(1);
        end = profiler.getCurrentTicks();
        profiler.recordNativeSocketEvent(start, end, 42, 512, JavaProfiler.SOCKET_OP_SEND);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        int count = 0;
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> fdAccessor = FD_ATTR.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> bytesAccessor = BYTES_ATTR.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> opAccessor = OPERATION_ATTR.getAccessor(it.getType());
            for (IItem item : it) {
                long fd = fdAccessor.getMember(item).longValue();
                long bytes = bytesAccessor.getMember(item).longValue();
                long op = opAccessor.getMember(item).longValue();
                assertEquals(42, fd);
                assertTrue(bytes > 0);
                assertTrue(op >= JavaProfiler.SOCKET_OP_RECV && op <= JavaProfiler.SOCKET_OP_WRITEV);
                count++;
            }
        }
        assertEquals(2, count, "Expected exactly 2 socket events (recv + send)");
    }

    @Test
    public void testAllOperationTypes() throws Exception {
        for (int op = JavaProfiler.SOCKET_OP_RECV; op <= JavaProfiler.SOCKET_OP_WRITEV; op++) {
            long start = profiler.getCurrentTicks();
            Thread.sleep(1);
            long end = profiler.getCurrentTicks();
            profiler.recordNativeSocketEvent(start, end, 10 + op, 100 * (op + 1), op);
        }

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        int count = 0;
        boolean[] seenOps = new boolean[6];
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> opAccessor = OPERATION_ATTR.getAccessor(it.getType());
            for (IItem item : it) {
                int op = (int) opAccessor.getMember(item).longValue();
                seenOps[op] = true;
                count++;
            }
        }
        assertEquals(6, count, "Expected 6 socket events, one per operation type");
        for (int i = 0; i < 6; i++) {
            assertTrue(seenOps[i], "Missing operation type " + i);
        }
    }

    @Test
    public void testContextPropagation() throws Exception {
        profiler.setContext(123, 456);
        long start = profiler.getCurrentTicks();
        Thread.sleep(1);
        long end = profiler.getCurrentTicks();
        profiler.recordNativeSocketEvent(start, end, 7, 256, JavaProfiler.SOCKET_OP_RECV);
        profiler.clearContext();

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        for (IItemIterable it : events) {
            IMemberAccessor<IQuantity, IItem> spanAccessor = SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> rootAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(it.getType());
            for (IItem item : it) {
                assertEquals(123, spanAccessor.getMember(item).longValue());
                assertEquals(456, rootAccessor.getMember(item).longValue());
            }
        }
    }

    @Test
    public void testInvalidParametersAreRejected() throws Exception {
        // Record one valid event
        long start = profiler.getCurrentTicks();
        Thread.sleep(1);
        long end = profiler.getCurrentTicks();
        profiler.recordNativeSocketEvent(start, end, 5, 100, JavaProfiler.SOCKET_OP_RECV);

        // Record invalid events — all should be silently dropped
        profiler.recordNativeSocketEvent(start, end, -1, 100, JavaProfiler.SOCKET_OP_RECV);  // negative fd
        profiler.recordNativeSocketEvent(start, end, 5, -1, JavaProfiler.SOCKET_OP_RECV);    // negative bytes
        profiler.recordNativeSocketEvent(start, end, 5, 100, -1);                             // negative op
        profiler.recordNativeSocketEvent(start, end, 5, 100, 6);                              // op out of range

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        int count = 0;
        for (IItemIterable it : events) {
            for (IItem item : it) {
                count++;
            }
        }
        assertEquals(1, count, "Only the valid event should be recorded");
    }
}
