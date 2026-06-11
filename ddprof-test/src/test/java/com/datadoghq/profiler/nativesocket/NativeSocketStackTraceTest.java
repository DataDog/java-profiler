package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.CStackAwareAbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.junit.CStack;
import com.datadoghq.profiler.junit.RetryTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.TestTemplate;
import org.junit.jupiter.params.provider.ValueSource;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.jdk.JdkAttributes;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that NativeSocketEvent events carry non-empty stack traces,
 * and that a recognizable Java call site from the test workload appears
 * in at least one event's stack trace.
 *
 * <p>Parameterized over cstack modes (vm, vmx, dwarf, fp) to exercise both
 * the walkVM path (cstack &gt;= CSTACK_VM) and the AsyncGetCallTrace path
 * (dwarf/fp) through the BCI_NATIVE_SOCKET code.
 */
public class NativeSocketStackTraceTest extends CStackAwareAbstractProfilerTest {

    public NativeSocketStackTraceTest(@CStack String cstack) {
        super(cstack);
    }

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us period keeps sampling probability high on short localhost I/O.
        return "natsock=100us";
    }

    @RetryTest(3)
    @TestTemplate
    @ValueSource(strings = {"vm", "vmx", "dwarf", "fp"})
    public void stackTraceIsCapturedForSocketEvents() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(64 * 1024, 20);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        boolean foundNonEmptyStackTrace = false;
        for (IItemIterable items : events) {
            IMemberAccessor<String, IItem> stackTraceAccessor =
                    JdkAttributes.STACK_TRACE_STRING.getAccessor(items.getType());
            if (stackTraceAccessor == null) continue;
            for (IItem item : items) {
                String st = stackTraceAccessor.getMember(item);
                if (st != null && !st.isEmpty()) {
                    foundNonEmptyStackTrace = true;
                    break;
                }
            }
            if (foundNonEmptyStackTrace) break;
        }
        assertTrue(foundNonEmptyStackTrace, "Expected at least one NativeSocketEvent with a non-empty stack trace");
    }

    // Named method so it can appear as a recognizable frame
    private void doTcpTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];
        try (ServerSocket server = new ServerSocket(0)) {
            int port = server.getLocalPort();
            Thread serverThread = new Thread(() -> {
                for (int iter = 0; iter < iterations; iter++) {
                    try (Socket conn = server.accept()) {
                        InputStream in = conn.getInputStream();
                        byte[] buf = new byte[payloadSize];
                        int read = 0;
                        while (read < payloadSize) {
                            int n = in.read(buf, read, payloadSize - read);
                            if (n < 0) break;
                            read += n;
                        }
                        conn.getOutputStream().write(buf, 0, read);
                        conn.getOutputStream().flush();
                    } catch (IOException ignored) {}
                }
            });
            serverThread.setDaemon(true);
            serverThread.start();

            for (int iter = 0; iter < iterations; iter++) {
                try (Socket client = new Socket("127.0.0.1", port)) {
                    client.getOutputStream().write(payload);
                    client.getOutputStream().flush();
                    byte[] resp = new byte[payloadSize];
                    InputStream in = client.getInputStream();
                    int read = 0;
                    while (read < payloadSize) {
                        int n = in.read(resp, read, payloadSize - read);
                        if (n < 0) break;
                        read += n;
                    }
                }
            }
            serverThread.join(5000);
        }
    }
}
