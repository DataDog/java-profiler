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

import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that the remoteAddress field in NativeSocketEvent is a non-empty
 * string of the form "<ip>:<port>" matching the known server endpoint.
 */
public class NativeSocketRemoteAddressTest extends AbstractProfilerTest {

    private static final IAttribute<String> REMOTE_ADDRESS =
            Attribute.attr("remoteAddress", "remoteAddress", "Remote address", UnitLookup.PLAIN_TEXT);

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us period keeps sampling probability high enough that the 16
        // short-lived connections reliably produce at least one event whose
        // remoteAddress points at the known server port.
        return "natsock=100us";
    }

    @RetryingTest(3)
    public void remoteAddressIsIpColonPort() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        int serverPort = doTcpTransfer(64 * 1024, 16);
        System.out.println("Server port: " + serverPort);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        boolean foundMatchingAddress = false;
        for (IItemIterable items : events) {
            IMemberAccessor<String, IItem> addrAccessor =
                    REMOTE_ADDRESS.getAccessor(items.getType());
            assertNotNull(addrAccessor, "remoteAddress accessor must exist");
            for (IItem item : items) {
                String addr = addrAccessor.getMember(item);
                assertNotNull(addr, "remoteAddress must not be null");
                assertFalse(addr.isEmpty(), "remoteAddress must not be empty");
                // Must match ip:port pattern
                assertTrue(addr.matches("^[\\d.]+:\\d+$") || addr.matches("^\\[.*\\]:\\d+$"),
                        "remoteAddress '" + addr + "' does not match expected ip:port format");
                if (addr.endsWith(":" + serverPort)) {
                    foundMatchingAddress = true;
                }
            }
        }
        assertTrue(foundMatchingAddress,
                "Expected at least one event with remoteAddress pointing to server port " + serverPort);
    }

    /** Returns the server's bound port. */
    private int doTcpTransfer(int payloadSize, int iterations) throws Exception {
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
            return port;
        }
    }
}
