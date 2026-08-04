package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.CountDownLatch;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that SEND and RECV operations are tracked as independent events.
 * Generates a workload where only one side performs writes so that events
 * can be attributed unambiguously to the sending or receiving thread.
 */
public class NativeSocketSendRecvSeparateTest extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us initial sampling period: a single 256KB localhost write
        // completes in ~100-500us giving P ~= 0.6-1.0 per call, so both
        // SEND and RECV directions are sampled reliably over 32 iterations.
        return "natsock=100us";
    }

    @RetryingTest(3)
    public void sendAndRecvTrackedWithSeparateCounts() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        // Large volume of data to ensure sampler captures both directions
        doUnidirectionalTransfer(256 * 1024, 32);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        long sendCount = 0;
        long recvCount = 0;

        for (IItemIterable items : events) {
            IMemberAccessor<String, IItem> opAccessor = OPERATION.getAccessor(items.getType());
            assertNotNull(opAccessor);
            for (IItem item : items) {
                String op = opAccessor.getMember(item);
                // Java sockets reach libc via write()/read(); send()/recv() also possible.
                // Group by direction: outbound (SEND, WRITE) vs inbound (RECV, READ).
                if ("SEND".equals(op) || "WRITE".equals(op))      sendCount++;
                else if ("RECV".equals(op) || "READ".equals(op))  recvCount++;
            }
        }

        System.out.println("Outbound (SEND/WRITE) events: " + sendCount
                         + ", Inbound (RECV/READ) events: " + recvCount);
        assertTrue(sendCount > 0, "Expected at least one outbound (SEND/WRITE) event, got 0");
        assertTrue(recvCount > 0, "Expected at least one inbound (RECV/READ) event, got 0");
    }

    private void doUnidirectionalTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];
        CountDownLatch serverReady = new CountDownLatch(1);

        try (ServerSocket server = new ServerSocket(0)) {
            int port = server.getLocalPort();
            Thread serverThread = new Thread(() -> {
                serverReady.countDown();
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
                    } catch (IOException ignored) {}
                }
            });
            serverThread.setDaemon(true);
            serverThread.start();
            serverReady.await();

            for (int iter = 0; iter < iterations; iter++) {
                try (Socket client = new Socket("127.0.0.1", port)) {
                    client.getOutputStream().write(payload);
                    client.getOutputStream().flush();
                }
            }
            serverThread.join(5000);
        }
    }
}
