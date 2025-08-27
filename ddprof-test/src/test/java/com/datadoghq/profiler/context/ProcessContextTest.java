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
        
        String serviceName = "test-service";
        String serviceId = "test-instance-123";
        String environment = "test-env";
        
        OTelContext.getInstance().setProcessContext(serviceName, serviceId, environment);
        
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
        
        long startAddr = Long.parseUnsignedLong(mapping.startAddress, 16);
        long endAddr = Long.parseUnsignedLong(mapping.endAddress, 16);
        long size = endAddr - startAddr;
        assertTrue(size > 0, "OTEL mapping size should be positive, got: " + size + " bytes");
    }

    @Test
    public void testMappingStructureCompliance() throws IOException {
        Assumptions.assumeTrue(Platform.isLinux());
        
        String serviceName = "test-service-structure";
        String serviceId = "test-instance-456";  
        String environment = "test-env-structure";
        
        OTelContext.getInstance().setProcessContext(serviceName, serviceId, environment);
        
        OtelMappingInfo mapping = findOtelMapping();
        assertNotNull(mapping, "OTEL mapping should exist");
        
        verifyMappingStructure(mapping, serviceName, serviceId, environment);
    }

    @Test
    public void testNativeReadBackFunctionality() {
        Assumptions.assumeTrue(Platform.isLinux());
        
        String serviceName = "test-service-read";
        String serviceId = "test-instance-789";
        String environment = "test-env-read";
        
        OTelContext context = OTelContext.getInstance();
        context.setProcessContext(serviceName, serviceId, environment);
        
        OTelContext.ProcessContext readContext = context.readProcessContext();
        
        assertNotNull(readContext, "Should be able to read back the published context");
        assertEquals(serviceName, readContext.serviceName, "Service name should match");
        assertEquals(serviceId, readContext.serviceInstanceId, "Service instance ID should match");
        assertEquals(environment, readContext.deploymentEnvironmentName, "Environment name should match");
    }
    
    private void verifyMappingStructure(OtelMappingInfo mapping, String expectedServiceName, 
                                       String expectedServiceId, String expectedEnvironment) throws IOException {
        long startAddr = Long.parseUnsignedLong(mapping.startAddress, 16);
        long endAddr = Long.parseUnsignedLong(mapping.endAddress, 16);
        long size = endAddr - startAddr;
        
        assertTrue(size >= 24, "Mapping size should be at least 24 bytes, got: " + size);
        
        try (RandomAccessFile memFile = new RandomAccessFile("/proc/self/mem", "r")) {
            memFile.seek(startAddr);
            
            byte[] mappingBytes = new byte[24];
            int bytesRead = memFile.read(mappingBytes);
            assertEquals(24, bytesRead, "Should read 24 bytes");
            
            String signature = new String(mappingBytes, 0, 8);
            assertEquals("OTEL_CTX", signature, "Signature should be OTEL_CTX");
            
            int version = ((mappingBytes[8] & 0xFF)) |
                         ((mappingBytes[9] & 0xFF) << 8) |
                         ((mappingBytes[10] & 0xFF) << 16) |
                         ((mappingBytes[11] & 0xFF) << 24);
            assertEquals(1, version, "Version should be 1");
            
            int payloadSize = ((mappingBytes[12] & 0xFF)) |
                             ((mappingBytes[13] & 0xFF) << 8) |
                             ((mappingBytes[14] & 0xFF) << 16) |
                             ((mappingBytes[15] & 0xFF) << 24);
            assertTrue(payloadSize > 0, "Payload size should be positive");
            
            int expectedSize = 3 + 3 + "service.name".length() + 3 + expectedServiceName.length() +
                              3 + "service.instance.id".length() + 3 + expectedServiceId.length() + 
                              3 + "deployment.environment.name".length() + 3 + expectedEnvironment.length();
            
            assertEquals(expectedSize, payloadSize, "Payload size should match expected size");
            
            boolean hasPayload = false;
            for (int i = 16; i < 24; i++) {
                if (mappingBytes[i] != 0) {
                    hasPayload = true;
                    break;
                }
            }
            assertTrue(hasPayload, "Payload pointer should be non-zero");
            
        } catch (IOException e) {
            fail("Failed to read OTEL mapping structure: " + e.getMessage());
        }
    }
}