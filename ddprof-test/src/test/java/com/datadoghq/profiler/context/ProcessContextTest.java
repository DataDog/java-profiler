package com.datadoghq.profiler.context;

import com.datadoghq.profiler.OTelContext;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static org.junit.jupiter.api.Assertions.*;

public class ProcessContextTest {

    @Test
    public void testProcessContextMappingCreation() throws IOException {
        Assumptions.assumeTrue(Platform.isLinux());

        String env = "test-env";
        String hostname = "test-hostname";
        String runtimeId = "test-instance-123";
        String service = "test-service";
        String version = "1.0.0";
        String tracerVersion = "3.5.0";

        OTelContext.getInstance().setProcessContext(env, hostname, runtimeId, service, version, tracerVersion, new String[0]);

        OtelMappingInfo mapping = findOtelMapping();
        assertNotNull(mapping, "OTEL mapping should exist after setProcessContext");

        verifyMappingPermissions(mapping);

        // With no user keys, the published map is exactly the reserved slot.
        OTelContext.ProcessContext readContext = OTelContext.getInstance().readProcessContext();
        assertNotNull(readContext);
        assertArrayEquals(
            new String[] {"datadog.local_root_span_id"},
            readContext.attributeKeyMap);
    }

    private static class OtelMappingInfo {
        final String startAddress;
        final String endAddress;
        final String permissions;

        OtelMappingInfo(String startAddress, String endAddress, String permissions) {
            this.startAddress = startAddress;
            this.endAddress = endAddress;
            this.permissions = permissions;
        }
    }

    private OtelMappingInfo findOtelMapping() throws IOException {
        Path mapsFile = Paths.get("/proc/self/maps");
        if (!Files.exists(mapsFile)) {
            return null;
        }

        // Match any mapping containing OTEL_CTX (memfd, anon, anon_shmem variants)
        Pattern otelPattern = Pattern.compile("^([0-9a-f]+)-([0-9a-f]+)\\s+(\\S+)\\s+\\S+\\s+\\S+\\s+\\S+\\s*.*OTEL_CTX.*$");

        try (BufferedReader reader = Files.newBufferedReader(mapsFile)) {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher matcher = otelPattern.matcher(line);
                if (matcher.matches()) {
                    return new OtelMappingInfo(
                        matcher.group(1),
                        matcher.group(2),
                        matcher.group(3)
                    );
                }
            }
        }
        return null;
    }

    private void verifyMappingPermissions(OtelMappingInfo mapping) {
        assertTrue(mapping.permissions.contains("r"),
            "OTEL mapping should have read permission, got: " + mapping.permissions);
        assertFalse(mapping.permissions.contains("x"),
            "OTEL mapping should not have execute permission, got: " + mapping.permissions);
    }

    @Test
    public void testProcessContextRoundTrip() {
        Assumptions.assumeTrue(Platform.isLinux());

        String env = "test-env";
        String hostname = "test-hostname";
        String runtimeId = "test-instance-123";
        String service = "test-service";
        String version = "1.0.0";
        String tracerVersion = "3.5.0";

        OTelContext context = OTelContext.getInstance();
        context.setProcessContext(env, hostname, runtimeId, service, version, tracerVersion,
            new String[] {"http.route", "db.system"});

        OTelContext.ProcessContext readContext = context.readProcessContext();

        assertNotNull(readContext);
        assertEquals(env, readContext.deploymentEnvironmentName);
        assertEquals(hostname, readContext.hostName);
        assertEquals(runtimeId, readContext.serviceInstanceId);
        assertEquals(service, readContext.serviceName);
        assertEquals(version, readContext.serviceVersion);
        assertEquals("java", readContext.telemetrySdkLanguage);
        assertEquals(tracerVersion, readContext.telemetrySdkVersion);
        assertEquals("dd-trace-java", readContext.telemetrySdkName);
        // The reserved local_root_span_id slot precedes the caller-provided keys.
        assertArrayEquals(
            new String[] {"datadog.local_root_span_id", "http.route", "db.system"},
            readContext.attributeKeyMap);
    }

    @Test
    public void testNullAttributeKeyElementAbortsPublish() {
        Assumptions.assumeTrue(Platform.isLinux());

        OTelContext context = OTelContext.getInstance();

        // Publish a known-good context first.
        context.setProcessContext("env-a", "host-a", "rt-a", "svc-a", "1.0.0", "3.5.0",
            new String[] {"http.route"});

        OTelContext.ProcessContext before = context.readProcessContext();
        assertNotNull(before);
        assertEquals("svc-a", before.serviceName);

        // A null element in the keys array aborts the entire publish: the previously
        // published context must remain untouched, not just have the bad key dropped.
        context.setProcessContext("env-b", "host-b", "rt-b", "svc-b", "2.0.0", "4.0.0",
            new String[] {"http.route", null, "db.system"});

        OTelContext.ProcessContext after = context.readProcessContext();
        assertNotNull(after);
        assertEquals("svc-a", after.serviceName,
            "null element must abort the publish, leaving the previous context intact");
        assertArrayEquals(
            new String[] {"datadog.local_root_span_id", "http.route"},
            after.attributeKeyMap);
    }

    @Test
    public void testAttributeKeysClippedToCapacity() {
        Assumptions.assumeTrue(Platform.isLinux());

        // Native DD_TAGS_CAPACITY: at most this many user keys are published, preceded
        // by the reserved datadog.local_root_span_id slot; any extra keys are clipped.
        final int capacity = 10;

        String[] keys = new String[capacity + 5];
        for (int i = 0; i < keys.length; i++) {
            keys[i] = "key" + i;
        }

        OTelContext context = OTelContext.getInstance();
        context.setProcessContext("test-env", "test-hostname", "test-instance-123",
            "test-service", "1.0.0", "3.5.0", keys);

        OTelContext.ProcessContext readContext = context.readProcessContext();
        assertNotNull(readContext);

        // Expect the reserved slot followed by exactly the first `capacity` user keys.
        String[] expected = new String[capacity + 1];
        expected[0] = "datadog.local_root_span_id";
        for (int i = 0; i < capacity; i++) {
            expected[i + 1] = "key" + i;
        }
        assertArrayEquals(expected, readContext.attributeKeyMap,
            "keys beyond DD_TAGS_CAPACITY must be clipped, keeping the first " + capacity);
    }

}
