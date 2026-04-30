package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.IMCStackTrace;
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;
import org.openjdk.jmc.flightrecorder.JfrAttributes;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that each NativeSocketEvent carries all required fields with valid values:
 * eventThread, stackTrace, duration, operation (SEND/RECV), remoteAddress (ip:port),
 * bytesTransferred (> 0), weight (> 0).
 */
public class NativeSocketEventFieldsTest extends NativeSocketTestBase {

    private static final IAttribute<String> REMOTE_ADDRESS =
            Attribute.attr("remoteAddress", "remoteAddress", "Remote address", UnitLookup.PLAIN_TEXT);
    private static final IAttribute<IQuantity> BYTES_TRANSFERRED =
            Attribute.attr("bytesTransferred", "bytesTransferred", "Bytes transferred", UnitLookup.MEMORY);
    private static final IAttribute<IQuantity> DURATION =
            Attribute.attr("duration", "duration", "Duration", UnitLookup.TIMESPAN);

    @RetryingTest(3)
    public void allRequiredFieldsPresentAndValid() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(4096, 128);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        boolean foundSend = false;
        boolean foundRecv = false;

        for (IItemIterable items : events) {
            IMemberAccessor<String, IItem> operationAccessor =
                    OPERATION.getAccessor(items.getType());
            IMemberAccessor<String, IItem> remoteAddressAccessor =
                    REMOTE_ADDRESS.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> bytesAccessor =
                    BYTES_TRANSFERRED.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor =
                    WEIGHT.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> durationAccessor =
                    DURATION.getAccessor(items.getType());
            IMemberAccessor<IMCThread, IItem> threadAccessor =
                    JfrAttributes.EVENT_THREAD.getAccessor(items.getType());
            IMemberAccessor<IMCStackTrace, IItem> stackTraceAccessor =
                    STACK_TRACE.getAccessor(items.getType());

            assertNotNull(operationAccessor, "operation field accessor must be present");
            assertNotNull(remoteAddressAccessor, "remoteAddress field accessor must be present");
            assertNotNull(bytesAccessor, "bytesTransferred field accessor must be present");
            assertNotNull(weightAccessor, "weight field accessor must be present");
            assertNotNull(durationAccessor, "duration field accessor must be present");
            assertNotNull(threadAccessor, "eventThread field accessor must be present");
            assertNotNull(stackTraceAccessor, "stackTrace field accessor must be present");

            for (IItem item : items) {
                String operation = operationAccessor.getMember(item);
                assertNotNull(operation, "operation must not be null");
                // op encodes the underlying syscall: SEND/RECV are emitted by send_hook/recv_hook;
                // WRITE/READ are emitted by write_hook/read_hook.  Java sockets typically reach
                // libc via write()/read(), so foundSend covers SEND and WRITE, foundRecv covers
                // RECV and READ — both directions must be observed.
                assertTrue(operation.equals("SEND") || operation.equals("RECV")
                        || operation.equals("WRITE") || operation.equals("READ"),
                        "operation must be one of SEND/RECV/WRITE/READ, got: " + operation);
                if ("SEND".equals(operation) || "WRITE".equals(operation)) foundSend = true;
                if ("RECV".equals(operation) || "READ".equals(operation))  foundRecv = true;

                String remoteAddress = remoteAddressAccessor.getMember(item);
                assertNotNull(remoteAddress, "remoteAddress must not be null");
                assertTrue(remoteAddress.contains(":"),
                        "remoteAddress must be in ip:port format, got: " + remoteAddress);

                IQuantity bytes = bytesAccessor.getMember(item);
                assertNotNull(bytes, "bytesTransferred must not be null");
                assertTrue(bytes.longValue() > 0,
                        "bytesTransferred must be > 0, got: " + bytes);

                IQuantity weight = weightAccessor.getMember(item);
                assertNotNull(weight, "weight must not be null");
                assertTrue(weight.doubleValue() > 0.0,
                        "weight must be > 0, got: " + weight);

                IQuantity duration = durationAccessor.getMember(item);
                assertNotNull(duration, "duration must not be null");

                IMCThread thread = threadAccessor.getMember(item);
                assertNotNull(thread, "eventThread must not be null");
            }
        }

        assertTrue(foundSend, "Expected at least one SEND event");
        assertTrue(foundRecv, "Expected at least one RECV event");
    }
}
