package com.datadoghq.profiler.nativesocket;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.item.Attribute;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.UnitLookup;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that UDP (DatagramSocket / sendto / recvfrom) transfers do NOT
 * produce NativeSocketEvent events. Only TCP blocking send/recv are in scope.
 *
 * This test performs only UDP transfers and expects zero NativeSocketEvent
 * events in the recording.
 */
public class NativeSocketUdpExcludedTest extends AbstractProfilerTest {

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us period strengthens the negative assertion: any UDP traffic
        // that accidentally leaks through the TCP filter would be far more
        // likely to produce a sampled event at this tighter interval.
        return "natsock=100us";
    }

    @RetryingTest(3)
    public void udpTransfersProduceNoSocketEvents() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        doUdpTransfer(1024, 500);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent", false);
        assertNotNull(events);
        assertFalse(events.hasItems(),
                "NativeSocketEvent must not be produced for UDP (sendto/recvfrom) transfers");
    }

    private void doUdpTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];
        InetAddress loopback = InetAddress.getLoopbackAddress();

        try (DatagramSocket server = new DatagramSocket(0, loopback)) {
            int port = server.getLocalPort();
            Thread serverThread = new Thread(() -> {
                byte[] buf = new byte[payloadSize];
                DatagramPacket pkt = new DatagramPacket(buf, buf.length);
                for (int iter = 0; iter < iterations; iter++) {
                    try {
                        server.receive(pkt);
                    } catch (Exception ignored) {}
                }
            });
            serverThread.setDaemon(true);
            serverThread.start();

            try (DatagramSocket client = new DatagramSocket()) {
                DatagramPacket pkt = new DatagramPacket(payload, payload.length, loopback, port);
                for (int iter = 0; iter < iterations; iter++) {
                    client.send(pkt);
                }
            }
            serverThread.join(5000);
        }
    }
}
