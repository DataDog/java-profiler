package com.datadoghq.profiler.context;

import com.datadoghq.profiler.JavaProfiler;
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

        OTelContext.getInstance().setProcessContext(env, hostname, runtimeId, service, version, tracerVersion);

        OtelMappingInfo mapping = findOtelMapping();
        assertNotNull(mapping, "OTEL mapping should exist after setProcessContext");

        verifyMappingPermissions(mapping);
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
    public void testNativeReadBackFunctionality() {
        Assumptions.assumeTrue(Platform.isLinux());

        String env = "test-env";
        String hostname = "test-hostname";
        String runtimeId = "test-instance-123";
        String service = "test-service";
        String version = "1.0.0";
        String tracerVersion = "3.5.0";

        OTelContext context = OTelContext.getInstance();
        context.setProcessContext(env, hostname, runtimeId, service, version, tracerVersion);

        OTelContext.ProcessContext readContext = context.readProcessContext();

        assertEquals(env, readContext.deploymentEnvironmentName, "Environment name should match");
        assertEquals(hostname, readContext.hostName, "Host name should match");
        assertEquals(runtimeId, readContext.serviceInstanceId, "Service instance ID should match");
        assertEquals(service, readContext.serviceName, "Service name should match");
        assertEquals(version, readContext.serviceVersion, "Service version should match");
        assertEquals("java", readContext.telemetrySdkLanguage, "Tracer language should match");
        assertEquals(tracerVersion, readContext.telemetrySdkVersion, "Tracer version should match");
        assertEquals("dd-trace-java", readContext.telemetrySdkName, "Tracer name should match");
    }

    /**
     * Tests that registerAttributeKeys correctly updates the process context.
     * registerAttributeKeys reads the existing process context and republishes it
     * with thread_ctx_config set. This test verifies that all original process
     * context fields are preserved after that republish.
     */
    @Test
    public void testRegisterAttributeKeysSetsProcessContext() {
        Assumptions.assumeTrue(Platform.isLinux());

        String env = "attr-keys-env";
        String hostname = "attr-keys-host";
        String runtimeId = "attr-keys-instance";
        String service = "attr-keys-service";
        String version = "2.0.0";
        String tracerVersion = "4.1.0";

        OTelContext context = OTelContext.getInstance();
        context.setProcessContext(env, hostname, runtimeId, service, version, tracerVersion);

        // registerAttributeKeys reads the existing process context and republishes
        // it with thread_ctx_config populated. All original fields must survive.
        context.registerAttributeKeys("http.route", "db.system");

        OTelContext.ProcessContext readContext = context.readProcessContext();

        assertNotNull(readContext, "Process context must still be readable after registerAttributeKeys");
        assertEquals(env, readContext.deploymentEnvironmentName, "Environment name must survive registerAttributeKeys");
        assertEquals(hostname, readContext.hostName, "Host name must survive registerAttributeKeys");
        assertEquals(runtimeId, readContext.serviceInstanceId, "Service instance ID must survive registerAttributeKeys");
        assertEquals(service, readContext.serviceName, "Service name must survive registerAttributeKeys");
        assertEquals(version, readContext.serviceVersion, "Service version must survive registerAttributeKeys");
        assertEquals("java", readContext.telemetrySdkLanguage, "Tracer language must survive registerAttributeKeys");
        assertEquals(tracerVersion, readContext.telemetrySdkVersion, "Tracer version must survive registerAttributeKeys");
        assertEquals("dd-trace-java", readContext.telemetrySdkName, "Tracer name must survive registerAttributeKeys");
        assertArrayEquals(
            new String[] {"datadog.local_root_span_id", "http.route", "db.system"},
            readContext.attributeKeyMap,
            "attribute_key_map should expose the reserved LRS slot followed by registered keys");
    }

    /**
     * Verifies that starting the profiler with attributes=... auto-publishes the
     * OTEP attribute_key_map without an explicit OTelContext.registerAttributeKeys()
     * call. This is the gap fixed in the ivoanjo/fix-otel-thread-ctx branch.
     */
    @Test
    public void testStartAttributesAutoRegistersKeys() throws IOException {
        Assumptions.assumeTrue(Platform.isLinux());

        OTelContext context = OTelContext.getInstance();
        // Publish a process context first so readProcessContext() returns non-null.
        context.setProcessContext("auto-env", "auto-host", "auto-instance", "auto-service", "1.0.0", "auto-tracer-1.0.0");

        JavaProfiler profiler = JavaProfiler.getInstance();
        Path jfrFile = Files.createTempFile("auto-attrs", ".jfr");
        try {
            profiler.execute(String.format("start,cpu=1ms,attributes=http.route;db.system,jfr,file=%s", jfrFile.toAbsolutePath()));
            try {
                OTelContext.ProcessContext readContext = context.readProcessContext();
                assertNotNull(readContext, "Process context must be readable");
                assertArrayEquals(
                    new String[] {"datadog.local_root_span_id", "http.route", "db.system"},
                    readContext.attributeKeyMap,
                    "attributes=... in start command should auto-publish attribute_key_map");
            } finally {
                profiler.stop();
            }
        } finally {
            Files.deleteIfExists(jfrFile);
        }
    }

}
