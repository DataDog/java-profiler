package com.datadoghq.profiler.endpoints;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.*;
import org.openjdk.jmc.common.unit.IQuantity;
import org.openjdk.jmc.common.unit.QuantityConversionException;
import org.openjdk.jmc.common.unit.UnitLookup;

import java.util.BitSet;
import java.util.Comparator;
import java.util.List;
import java.util.UUID;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

import static java.util.concurrent.TimeUnit.MILLISECONDS;
import static java.util.concurrent.TimeUnit.NANOSECONDS;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

public class EndpointTest extends AbstractProfilerTest {

    @Test
    public void testEndpoints() {
        Endpoint[] endpoints = IntStream.range(0, 1000)
                .mapToObj(i -> new Endpoint(
                        MILLISECONDS.toNanos(System.currentTimeMillis()),
                        MILLISECONDS.toNanos(i),
                        i,
                        i + ""))
                .toArray(Endpoint[]::new);
        int sizeLimit = endpoints.length;
        // insert up to limit
        for (Endpoint endpoint : endpoints) {
            record(endpoint, true, sizeLimit);
        }
        // idempotency
        for (Endpoint endpoint : endpoints) {
            record(endpoint, true, sizeLimit);
        }
        // reject above size limit
        record(new Endpoint(System.nanoTime(), 10, 0, UUID.randomUUID().toString()),
                false, sizeLimit);

        stopProfiler();
        IItemCollection events = verifyEvents("datadog.Endpoint");
        IAttribute<String> endpointAttribute = attr("endpoint", "endpoint", "endpoint",
                PLAIN_TEXT);
        BitSet recovered = new BitSet();
        for (IItemIterable it : events) {
            IMemberAccessor<String, IItem> endpointAccessor = endpointAttribute.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> durationAccessor = DURATION.getAccessor(it.getType());
            for (IItem event : it) {
                long rootSpanId = rootSpanIdAccessor.getMember(event).longValue();
                Endpoint endpoint = endpoints[(int) rootSpanId];
                recovered.set((int) rootSpanId);
                String message = endpoint.toString();
                String recordedEndpoint = endpointAccessor.getMember(event);
                assertEquals(endpoint.endpoint, recordedEndpoint, message);
                assertEquals(endpoint.rootSpanId, rootSpanId, message);
                assertEquals(UnitLookup.MILLISECOND, durationAccessor.getMember(event).getUnit());
                long durationMillis = durationAccessor.getMember(event).longValue();
                long originalDurationMillis = NANOSECONDS.toMillis(endpoint.durationNanos);
                assertEquals(originalDurationMillis, durationMillis, message);
            }
        }
        for (int i = 0; i < endpoints.length; i++) {
            assertTrue(recovered.get(i), i + " not tested");
        }
    }

    private void record(Endpoint endpoint, boolean shouldAccept, int sizeLimit) {
        assertEquals(shouldAccept, profiler.recordTraceRoot(endpoint.startNanos, endpoint.durationNanos, NANOSECONDS,
                endpoint.rootSpanId, endpoint.endpoint, sizeLimit));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    static class Endpoint {
        private final long startNanos;
        private final long durationNanos;
        private final long rootSpanId;
        private final String endpoint;

        Endpoint(long startNanos, long durationNanos, long rootSpanId, String endpoint) {
            this.startNanos = startNanos;
            this.durationNanos = durationNanos;
            this.rootSpanId = rootSpanId;
            this.endpoint = endpoint;
        }

        @Override
        public String toString() {
            return "Endpoint{" +
                    "startNanos=" + startNanos +
                    ", durationNanos=" + durationNanos +
                    ", rootSpanId=" + rootSpanId +
                    ", endpoint='" + endpoint + '\'' +
                    '}';
        }
    }
}
