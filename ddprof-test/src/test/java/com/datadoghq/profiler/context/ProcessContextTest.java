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
    
    private OtelMappingInfo findOtelMapping() throws IOException {
        Path mapsFile = Paths.get("/proc/self/maps");
        if (!Files.exists(mapsFile)) {
            return null;
        }
        
        Pattern otelPattern = Pattern.compile("^([0-9a-f]+)-([0-9a-f]+)\\s+(\\S+)\\s+\\S+\\s+\\S+\\s+\\S+\\s*\\[anon:OTEL_CTX\\].*$");
        
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
        assertFalse(mapping.permissions.contains("w"),
            "OTEL mapping should not have write permission, got: " + mapping.permissions);
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
}
