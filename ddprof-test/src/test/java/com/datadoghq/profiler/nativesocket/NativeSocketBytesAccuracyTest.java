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
import java.net.ServerSocket;
import java.net.Socket;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that time-weighted sampling produces a statistically reasonable
 * estimate of total I/O time. With time-weighted inverse-transform sampling
 * the invariant is:
 * <pre>
 *   E[ sum(weight * duration) ] = total_io_time
 * </pre>
 *
 * We verify that {@code sum(weight * duration_ns)} is positive and within a
 * generous 100x tolerance of the actual test duration, confirming that the
 * weight field reflects duration-based probability rather than a degenerate
 * value.
 */
public class NativeSocketBytesAccuracyTest extends AbstractProfilerTest {

    private static final IAttribute<IQuantity> DURATION_ATTR =
            Attribute.attr("duration", "duration", "Duration", UnitLookup.TIMESPAN);
    private static final IAttribute<IQuantity> WEIGHT_ATTR =
            Attribute.attr("weight", "weight", "weight", UnitLookup.NUMBER);

    @Override
    protected boolean isPlatformSupported() {
        return Platform.isLinux() && !Platform.isMusl();
    }

    @Override
    protected String getProfilerCommand() {
        // 100us period keeps sampling probability high on short localhost I/O.
        return "natsock=100us";
    }

    @RetryingTest(5)
    public void timeWeightedEstimateIsWithinReasonableBounds() throws Exception {
        Assumptions.assumeTrue(Platform.isLinux(), "nativesocket tracking is Linux-only");

        int payloadSize = 256 * 1024;
        int iterations = 100;

        long wallStart = System.nanoTime();
        doTcpSend(payloadSize, iterations);
        long wallEnd = System.nanoTime();
        long wallNs = wallEnd - wallStart;

        stopProfiler();

        IItemCollection events = verifyEvents("datadog.NativeSocketEvent");
        assertTrue(events.hasItems(), "No NativeSocketEvent events found");

        double scaledDurationNs = 0.0;
        long sendEventCount = 0;
        for (IItemIterable items : events) {
            IMemberAccessor<String, IItem> opAccessor = OPERATION.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> durationAccessor = DURATION_ATTR.getAccessor(items.getType());
            IMemberAccessor<IQuantity, IItem> weightAccessor = WEIGHT_ATTR.getAccessor(items.getType());
            if (opAccessor == null || durationAccessor == null || weightAccessor == null) continue;
            for (IItem item : items) {
                if ("SEND".equals(opAccessor.getMember(item))) {
                    IQuantity dur = durationAccessor.getMember(item);
                    IQuantity weight = weightAccessor.getMember(item);
                    if (dur != null && weight != null) {
                        double durationNs = dur.doubleValueIn(UnitLookup.NANOSECOND);
                        scaledDurationNs += durationNs * weight.doubleValue();
                        sendEventCount++;
                    }
                }
            }
        }

        System.out.println("Wall time of transfers: " + wallNs + " ns");
        System.out.println("Scaled I/O time (sum of duration*weight): " + scaledDurationNs + " ns");
        System.out.println("SEND event count: " + sendEventCount);

        assertTrue(sendEventCount > 0, "No SEND events recorded");
        assertTrue(scaledDurationNs > 0.0, "sum(weight * duration) must be positive");

        // Generous 100x tolerance: scaled estimate must not exceed 100x wall time.
        // Lower bound is not enforced because very short I/O calls may all fall
        // below the sampling threshold in a brief recording window.
        assertTrue(scaledDurationNs <= wallNs * 100.0,
                String.format("sum(weight * duration) = %.0f ns is implausibly large (wall=%d ns)",
                        scaledDurationNs, wallNs));
    }

    private void doTcpSend(int payloadSize, int iterations) throws Exception {
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
                    } catch (IOException ignored) {}
                }
            });
            serverThread.setDaemon(true);
            serverThread.start();

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
