package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/** Base class for native-socket profiler tests that need a persistent TCP workload. */
abstract class NativeSocketTestBase extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us initial period keeps P high enough that fast localhost I/O
        // reliably produces events across small test workloads.
        return "natsock=100us";
    }

    /**
     * Sends {@code iterations} writes of {@code payloadSize} bytes over a single
     * persistent TCP connection and reads the echo back. Reusing the connection
     * fills the TCP send buffer after ~32 iterations (at 4 KB/write, 128 KB OS buffer),
     * causing subsequent writes to block for >1 ms and driving the Poisson sampler
     * probability close to 1.0 for those calls.
     */
    protected void doTcpTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];
        for (int i = 0; i < payloadSize; i++) payload[i] = (byte) (i & 0xFF);

        try (ServerSocket server = new ServerSocket(0)) {
            int port = server.getLocalPort();
            Thread serverThread = new Thread(() -> {
                try (Socket conn = server.accept()) {
                    InputStream in = conn.getInputStream();
                    OutputStream out = conn.getOutputStream();
                    byte[] buf = new byte[payloadSize];
                    for (int iter = 0; iter < iterations; iter++) {
                        int read = 0;
                        while (read < payloadSize) {
                            int n = in.read(buf, read, payloadSize - read);
                            if (n < 0) return;
                            read += n;
                        }
                        out.write(buf, 0, payloadSize);
                        out.flush();
                    }
                } catch (IOException ignored) {}
            });
            serverThread.setDaemon(true);
            serverThread.start();

            try (Socket client = new Socket("127.0.0.1", port)) {
                OutputStream out = client.getOutputStream();
                InputStream in = client.getInputStream();
                byte[] resp = new byte[payloadSize];
                for (int iter = 0; iter < iterations; iter++) {
                    out.write(payload);
                    out.flush();
                    int read = 0;
                    while (read < payloadSize) {
                        int n = in.read(resp, read, payloadSize - read);
                        if (n < 0) break;
                        read += n;
                    }
                }
            }
            serverThread.join(10000);
        }
    }
}
