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

/**
 * Verifies that NativeSocketEvent events are absent when the 'nativesocket'
 * profiler argument is not specified.
 */
public class NativeSocketDisabledTest extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux();
    }

    @Override
    protected String getProfilerCommand() {
        // cpu-only profiling, no nativesocket
        return "cpu=10ms";
    }

    @RetryingTest(3)
    public void noSocketEventsWithoutFeatureEnabled() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doTcpTransfer(64 * 1024, 8);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent", false);
        assertFalse(events.hasItems(),
                "NativeSocketEvent events must not appear when nativesocket argument is absent");
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
