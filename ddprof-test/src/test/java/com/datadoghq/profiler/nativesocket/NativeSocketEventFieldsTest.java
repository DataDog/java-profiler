package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.JfrStackTrace;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that each NativeSocketEvent carries all required fields with valid values:
 * eventThread, stackTrace, duration, operation (SEND/RECV), remoteAddress (ip:port),
 * bytesTransferred (> 0), weight (> 0).
 */
public class NativeSocketEventFieldsTest extends NativeSocketTestBase {

    private static final String REMOTE_ADDRESS = "remoteAddress";
    private static final String BYTES_TRANSFERRED = "bytesTransferred";
    private static final String DURATION = "duration";

    @RetryingTest(3)
    public void allRequiredFieldsPresentAndValid() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(4096, 128);

        stopProfiler();

        JfrEvents events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        boolean foundSend = false;
        boolean foundRecv = false;

        for (JfrEvent item : events) {
            assertTrue(item.has(OPERATION), "operation field must be present");
            assertTrue(item.has(REMOTE_ADDRESS), "remoteAddress field must be present");
            assertTrue(item.has(BYTES_TRANSFERRED), "bytesTransferred field must be present");
            assertTrue(item.has(WEIGHT), "weight field must be present");
            assertTrue(item.has(DURATION), "duration field must be present");
            assertTrue(item.has("eventThread"), "eventThread field must be present");
            assertTrue(item.has(STACK_TRACE), "stackTrace field must be present");

            String operation = item.getString(OPERATION);
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

            String remoteAddress = item.getString(REMOTE_ADDRESS);
            assertNotNull(remoteAddress, "remoteAddress must not be null");
            // AF_UNIX SOCK_STREAM sockets produce an empty remoteAddress; skip
            // the ip:port format check for those events.
            if (!remoteAddress.isEmpty()) {
                assertTrue(remoteAddress.contains(":"),
                        "remoteAddress must be in ip:port format, got: " + remoteAddress);
            }

            Long bytes = item.getLong(BYTES_TRANSFERRED);
            assertNotNull(bytes, "bytesTransferred must not be null");
            assertTrue(bytes > 0,
                    "bytesTransferred must be > 0, got: " + bytes);

            Double weight = item.getDouble(WEIGHT);
            assertNotNull(weight, "weight must not be null");
            assertTrue(weight > 0.0,
                    "weight must be > 0, got: " + weight);

            Long duration = item.getLong(DURATION);
            assertNotNull(duration, "duration must not be null");

            String threadName = item.getThreadName("eventThread");
            assertNotNull(threadName, "eventThread must not be null");
        }

        assertTrue(foundSend, "Expected at least one SEND event");
        assertTrue(foundRecv, "Expected at least one RECV event");
    }
}
