package com.datadoghq.profiler.context;

import com.datadoghq.profiler.OTelContext;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.RandomAccessFile;
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
    
    /**
     * Finds the OTEL_CTX mapping in /proc/self/maps.
     * Supports both memfd mappings (/memfd:OTEL_CTX) and named anonymous mappings ([anon:OTEL_CTX]).
     */
    private OtelMappingInfo findOtelMapping() throws IOException {
        Path mapsFile = Paths.get("/proc/self/maps");
        if (!Files.exists(mapsFile)) {
            return null;
        }

        // Pattern for named anonymous mapping: [anon:OTEL_CTX]
        Pattern anonPattern = Pattern.compile("^([0-9a-f]+)-([0-9a-f]+)\\s+(\\S+)\\s+\\S+\\s+\\S+\\s+\\S+\\s*\\[anon:OTEL_CTX\\].*$");
        // Pattern for memfd mapping: /memfd:OTEL_CTX (deleted)
        Pattern memfdPattern = Pattern.compile("^([0-9a-f]+)-([0-9a-f]+)\\s+(\\S+)\\s+.*?/memfd:OTEL_CTX.*$");

        try (BufferedReader reader = Files.newBufferedReader(mapsFile)) {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher anonMatcher = anonPattern.matcher(line);
                if (anonMatcher.matches()) {
                    return new OtelMappingInfo(
                        anonMatcher.group(1),
                        anonMatcher.group(2),
                        anonMatcher.group(3)
                    );
                }
                Matcher memfdMatcher = memfdPattern.matcher(line);
                if (memfdMatcher.matches()) {
                    return new OtelMappingInfo(
                        memfdMatcher.group(1),
                        memfdMatcher.group(2),
                        memfdMatcher.group(3)
                    );
                }
            }
        }
        return null;
    }

    private void verifyMappingPermissions(OtelMappingInfo mapping) {
        assertTrue(mapping.permissions.contains("r"),
            "OTEL mapping should have read permission, got: " + mapping.permissions);
        // Per PR #34: mappings stay writable (rw-p or rw-s) for in-place updates
        // Accept both read-only (old) and read-write (new) permissions
        assertTrue(mapping.permissions.matches("r.-.") || mapping.permissions.matches("rw-."),
            "OTEL mapping should have r--p, r--s, rw-p, or rw-s permissions, got: " + mapping.permissions);
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
     * Tests that calling setProcessContext multiple times correctly updates the context.
     * This verifies the v2 update protocol works correctly.
     */
    @Test
    public void testMultipleContextUpdates() {
        Assumptions.assumeTrue(Platform.isLinux());

        OTelContext context = OTelContext.getInstance();

        // First context
        context.setProcessContext("env1", "host1", "instance1", "service1", "1.0.0", "1.0.0");
        OTelContext.ProcessContext ctx1 = context.readProcessContext();
        assertNotNull(ctx1, "First context should be readable");
        assertEquals("env1", ctx1.deploymentEnvironmentName);
        assertEquals("service1", ctx1.serviceName);

        // Update context
        context.setProcessContext("env2", "host2", "instance2", "service2", "2.0.0", "2.0.0");
        OTelContext.ProcessContext ctx2 = context.readProcessContext();
        assertNotNull(ctx2, "Updated context should be readable");
        assertEquals("env2", ctx2.deploymentEnvironmentName);
        assertEquals("service2", ctx2.serviceName);
        assertEquals("2.0.0", ctx2.serviceVersion);

        // Update again
        context.setProcessContext("env3", "host3", "instance3", "service3", "3.0.0", "3.0.0");
        OTelContext.ProcessContext ctx3 = context.readProcessContext();
        assertNotNull(ctx3, "Third context should be readable");
        assertEquals("env3", ctx3.deploymentEnvironmentName);
        assertEquals("service3", ctx3.serviceName);
    }

    /**
     * Tests process context with TLS configuration.
     * This verifies that TLS config is properly encoded into the process context.
     */
    @Test
    public void testProcessContextWithTlsConfig() throws IOException {
        Assumptions.assumeTrue(Platform.isLinux());

        OTelContext context = OTelContext.getInstance();

        // Create TLS config with attribute key map
        // New format: key names in index order (position = key index)
        // Index 0 = "method", Index 1 = "route", Index 2 = "user"
        String[] keyMap = {"method", "route", "user"};
        OTelContext.TlsConfig tlsConfig = new OTelContext.TlsConfig(512, keyMap);

        // Set process context with TLS config
        context.setProcessContext("prod", "myhost", "instance-123", "myservice", "1.0.0", "3.5.0", tlsConfig);

        // Verify basic context is readable
        OTelContext.ProcessContext ctx = context.readProcessContext();
        assertNotNull(ctx, "Context should be readable");
        assertEquals("prod", ctx.deploymentEnvironmentName);
        assertEquals("myservice", ctx.serviceName);

        // Verify mapping exists (TLS config is encoded in payload but not read back)
        OtelMappingInfo mapping = findOtelMapping();
        assertNotNull(mapping, "OTEL mapping should exist with TLS config");
        verifyMappingPermissions(mapping);
    }
}
