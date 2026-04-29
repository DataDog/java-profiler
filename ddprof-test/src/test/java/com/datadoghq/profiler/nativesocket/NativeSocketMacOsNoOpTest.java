package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItemCollection;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * On macOS the nativesocket feature is a no-op stub.
 * Verifies that the profiler starts without error when 'nativesocket' is specified
 * and that no NativeSocketEvent events appear in the recording.
 */
public class NativeSocketMacOsNoOpTest extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isMac();
    }

    @Override
    protected String getProfilerCommand() {
        return "natsock";
    }

    @RetryingTest(3)
    public void noEventsOnMacOS() throws Exception {
        Assumptions.assumeTrue(Platform.isMac(), "This test targets macOS no-op behaviour");

        // Profiler started in @BeforeEach without error; verify it is actually running
        String status = profiler.getStatus();
        assertTrue(status.contains("Running          : true"),
                "Profiler should be running after start with nativesocket on macOS; status: " + status);

        doTcpTransfer(32 * 1024, 8);

        stopProfiler();

        // verifyEvents with failOnEmpty=false: must not throw even if empty
        IItemCollection events = verifyEvents("datadog.NativeSocketEvent", false);
        assertNotNull(events);
        assertFalse(events.hasItems(),
                "NativeSocketEvent must not be emitted on macOS (no-op stub)");
    }

    private void doTcpTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];
        try (ServerSocket server = new ServerSocket(0)) {
            int port = server.getLocalPort();
            Thread serverThread = new Thread(() -> {
                for (int iter = 0; iter < iterations; iter++) {
                    try (Socket conn = server.accept()) {
                        try {
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
