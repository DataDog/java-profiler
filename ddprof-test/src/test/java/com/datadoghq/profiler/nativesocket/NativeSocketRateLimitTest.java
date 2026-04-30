/*
 * Copyright 2026 Datadog, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.UnitLookup;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Verifies that the sampler is active: when a large number of I/O operations are
 * performed over a single persistent connection, only a fraction are recorded
 * (events << operations), and the weight field is > 1 on at least some events,
 * reflecting statistical significance.
 *
 * The target rate is ~5000 events/min; for a 10-second window that is ~833 events.
 * We generate far more byte volume than that and assert the event count is
 * substantially less than the operation count, and that at least one event
 * carries weight > 1.
 *
 * A persistent connection is reused across all iterations to avoid the TCP
 * handshake overhead that would make the test slow and unreliable on CI.
 */
public class NativeSocketRateLimitTest extends AbstractProfilerTest {

    private static final IAttribute<IQuantity> WEIGHT_ATTR =
            Attribute.attr("weight", "weight", "weight", UnitLookup.NUMBER);

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        return "natsock";
    }

    @RetryingTest(3)
    public void eventCountIsSubstantiallyLessThanOperationCount() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        // Generate a high volume of byte-sized writes over a single connection.
        // ~5000 iterations * 4 KB = 20 MB total — far above the ~5000-event/min rate limit.
        int operations = doHighRateTcpTransfer(4096, 5000);
        System.out.println("Total TCP operations performed: " + operations);

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        long eventCount = 0;
        boolean foundWeightAboveOne = false;

        for (IItemIterable items : events) {
            IMemberAccessor<IQuantity, IItem> weightAccessor =
                    WEIGHT_ATTR.getAccessor(items.getType());
            for (IItem item : items) {
                eventCount++;
                if (weightAccessor != null) {
                    IQuantity w = weightAccessor.getMember(item);
                    if (w != null && w.doubleValue() > 1.0) {
                        foundWeightAboveOne = true;
                    }
                }
            }
        }

        System.out.println("Recorded NativeSocketEvent count: " + eventCount);

        // Recorded events must be far fewer than raw operations (subsampling is active).
        // Target rate is ~5000 events/min; for a 10-second window ~833 events is the ceiling.
        // Using operations/2 (10000) provides a generous upper bound that must still be met.
        assertTrue(eventCount < operations / 2,
                "Too many events sampled (rate limiting not working): event count (" + eventCount
                        + ") should be less than operations/2 (" + operations / 2 + ")");

        // At least some events must have weight > 1, indicating byte-weighted sampling
        assertTrue(foundWeightAboveOne,
                "Expected at least one event with weight > 1 (byte-weighted inverse-transform sampling)");
    }

    /**
     * Sends {@code iterations} writes of {@code payloadSize} bytes over a single
     * persistent TCP connection and reads the echo back.  Reusing the connection
     * avoids per-iteration TCP handshake overhead that would otherwise make the
     * workload too slow to reliably hit the rate limit within the recording window.
     *
     * @return total number of individual send/recv calls performed (4 per iteration)
     */
    private int doHighRateTcpTransfer(int payloadSize, int iterations) throws Exception {
        byte[] payload = new byte[payloadSize];

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
        // Each iteration: 1 send + 1 recv on client; 1 recv + 1 send on server
        return iterations * 4;
    }
}
