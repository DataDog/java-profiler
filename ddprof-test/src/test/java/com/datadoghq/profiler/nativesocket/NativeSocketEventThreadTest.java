package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.IMCThread;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.flightrecorder.JfrAttributes;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that the eventThread field on NativeSocketEvent is populated and
 * names a non-empty thread name, indicating the I/O was attributed to the
 * calling thread.
 */
public class NativeSocketEventThreadTest extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us period keeps sampling probability high on short localhost I/O.
        return "natsock=100us";
    }

    @RetryingTest(3)
    public void eventThreadIsPopulated() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(64 * 1024, 16);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        for (IItemIterable items : events) {
            IMemberAccessor<IMCThread, IItem> threadAccessor =
                    JfrAttributes.EVENT_THREAD.getAccessor(items.getType());
            assertNotNull(threadAccessor, "eventThread accessor must be present");
            for (IItem item : items) {
                IMCThread thread = threadAccessor.getMember(item);
                assertNotNull(thread, "eventThread must not be null");
                String name = thread.getThreadName();
                assertNotNull(name, "thread name must not be null");
                assertFalse(name.isEmpty(), "thread name must not be empty");
            }
        }
    }

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
