package com.datadoghq.profiler.endpoints;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.BitSet;
import java.util.Map;
import java.util.UUID;
import java.util.stream.IntStream;

import static com.datadoghq.profiler.MoreAssertions.assertBoundedBy;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class EndpointTest extends AbstractProfilerTest {

    @Test
    public void testEndpoints() {
        Endpoint[] endpoints = IntStream.range(0, 1000)
                .mapToObj(i -> new Endpoint(i, i + "", i % 2 == 0 ? "op" + i : null))
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
        record(new Endpoint(0, UUID.randomUUID().toString(), UUID.randomUUID().toString()), false, sizeLimit);

        Map<String, Long> debugCounters = profiler.getDebugCounters();
        assertEquals(endpoints.length, debugCounters.get("dictionary_endpoints_keys"));
        stopProfiler();
        JfrEvents events = verifyEvents("datadog.Endpoint");
        BitSet recovered = new BitSet();
        for (JfrEvent event : events) {
            long rootSpanId = event.getLong(LOCAL_ROOT_SPAN_ID, -1);
            String operation = event.getString(OPERATION);
            Endpoint endpoint = endpoints[(int) rootSpanId];
            recovered.set((int) rootSpanId);
            String message = endpoint.toString();
            String recordedEndpoint = event.getString("endpoint");
            assertEquals(endpoint.endpoint, recordedEndpoint, message);
            assertEquals(endpoint.rootSpanId, rootSpanId, message);
            assertEquals(endpoint.operation, operation, message);
        }
        for (int i = 0; i < endpoints.length; i++) {
            assertTrue(recovered.get(i), i + " not tested");
        }
        assertEquals(Arrays.stream(endpoints).mapToInt(ep -> ep.endpoint.length() + 1).sum(), debugCounters.get("dictionary_endpoints_keys_bytes"));
        // SBTable geometry (post-StringDictionary refactor): ROWS=128, CELLS=3.
        // 1000 keys distribute ~8 entries per row, so nearly every row in the
        // active buffer overflows, allocating one new SBTable per row → up to
        // ~129 pages per buffer (1 root + 128 overflow). With 3 buffers and
        // potential dump-cycle rotation, 512 is a safe upper bound.
        assertBoundedBy(debugCounters.get("dictionary_endpoints_pages"), 512,
                "endpoint storage too many SBTable pages");
        // dictionary_endpoints_bytes covers SBTable nodes plus arena Chunk(s).
        // Worst case for 1000 short keys: 3 buffers × (sizeof(SBTable) +
        // sizeof(Chunk)) ≈ 2.3 MB; bound at 4 MB for safety.
        assertBoundedBy(debugCounters.get("dictionary_endpoints_bytes"), 4L * 1024 * 1024,
                "endpoint storage too many bytes");
    }

    private void record(Endpoint endpoint, boolean shouldAccept, int sizeLimit) {
        assertEquals(shouldAccept, profiler.recordTraceRoot(endpoint.rootSpanId, endpoint.endpoint, endpoint.operation, sizeLimit));
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    static class Endpoint {
        private final long rootSpanId;
        private final String endpoint;
        private final String operation;

        Endpoint(long rootSpanId, String endpoint, String operation) {
            this.rootSpanId = rootSpanId;
            this.endpoint = endpoint;
            this.operation = operation;
        }

        @Override
        public String toString() {
            return "Endpoint{" +
                    "rootSpanId=" + rootSpanId +
                    ", endpoint='" + endpoint + '\'' +
                    ", operation='" + operation + '\'' +
                    '}';
        }
    }
}
