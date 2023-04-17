package com.datadoghq.profiler.endpoints;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.unit.IQuantity;

import java.util.Arrays;
import java.util.BitSet;
import java.util.Map;
import java.util.UUID;
import java.util.stream.IntStream;

import static com.datadoghq.profiler.MoreAssertions.*;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

public class EndpointTest extends AbstractProfilerTest {

    @Test
    public void testEndpoints() {
        Endpoint[] endpoints = IntStream.range(0, 1000)
                .mapToObj(i -> new Endpoint(i, i + ""))
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
        record(new Endpoint(0, UUID.randomUUID().toString()), false, sizeLimit);

        stopProfiler();
        IItemCollection events = verifyEvents("datadog.Endpoint");
        IAttribute<String> endpointAttribute = attr("endpoint", "endpoint", "endpoint",
                PLAIN_TEXT);
        BitSet recovered = new BitSet();
        for (IItemIterable it : events) {
            IMemberAccessor<String, IItem> endpointAccessor = endpointAttribute.getAccessor(it.getType());
            IMemberAccessor<IQuantity, IItem> rootSpanIdAccessor = LOCAL_ROOT_SPAN_ID.getAccessor(it.getType());
            for (IItem event : it) {
                long rootSpanId = rootSpanIdAccessor.getMember(event).longValue();
                Endpoint endpoint = endpoints[(int) rootSpanId];
                recovered.set((int) rootSpanId);
                String message = endpoint.toString();
                String recordedEndpoint = endpointAccessor.getMember(event);
                assertEquals(endpoint.endpoint, recordedEndpoint, message);
                assertEquals(endpoint.rootSpanId, rootSpanId, message);
            }
        }
        for (int i = 0; i < endpoints.length; i++) {
            assertTrue(recovered.get(i), i + " not tested");
        }
        Map<String, Long> debugCounters = profiler.getDebugCounters();
        assertEquals(endpoints.length, debugCounters.get("dictionary:endpoints:keys"));
        assertEquals(Arrays.stream(endpoints).mapToInt(ep -> ep.endpoint.length() + 1).sum(), debugCounters.get("dictionary:endpoints:keys:bytes"));
        assertBoundedBy(debugCounters.get("dictionary:endpoints:pages"), 300, "endpoint storage too many pages");
        assertBoundedBy(debugCounters.get("dictionary:endpoints:bytes"), 300 * DICTIONARY_PAGE_SIZE, "endpoint storage too many pages");
    }

    private void record(Endpoint endpoint, boolean shouldAccept, int sizeLimit) {
        assertEquals(shouldAccept, profiler.recordTraceRoot(endpoint.rootSpanId, endpoint.endpoint, sizeLimit));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    static class Endpoint {
        private final long rootSpanId;
        private final String endpoint;

        Endpoint(long rootSpanId, String endpoint) {
            this.rootSpanId = rootSpanId;
            this.endpoint = endpoint;
        }

        @Override
        public String toString() {
            return "Endpoint{" +
                    "rootSpanId=" + rootSpanId +
                    ", endpoint='" + endpoint + '\'' +
                    '}';
        }
    }
}
