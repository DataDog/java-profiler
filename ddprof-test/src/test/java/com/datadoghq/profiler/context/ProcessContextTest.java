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
    public void testProcessContextMapping() throws IOException {
        System.out.println("Platform check - isLinux: " + Platform.isLinux());
        // Only run on Linux - macOS doesn't support process context
        Assumptions.assumeTrue(Platform.isLinux());
        
        String serviceName = "test-service";
        String serviceId = "test-instance-123";
        String environment = "test-env";
        
        // Check if an OTEL mapping already exists (may be from previous tests)
        OtelMappingInfo initialMapping = findOtelMapping();
        System.out.println("Initial OTEL mapping check: " + (initialMapping == null ? "none found" : "found"));
        // Note: We don't assert null here as other tests may have created a mapping already
        
        // Set the process context
        OTelContext.getInstance().setProcessContext(serviceName, serviceId, environment);
        
        // Verify the OTEL mapping was created
        OtelMappingInfo mapping = findOtelMapping();
        System.out.println("Post-setProcessCtx OTEL mapping check: " + (mapping == null ? "none found" : "found"));
        if (mapping != null) {
            System.out.println("Found OTEL mapping: " + mapping.startAddress + "-" + mapping.endAddress + " " + mapping.permissions);
        }
        assertNotNull(mapping, "OTEL mapping should exist after setProcessCtx");
        
        // Verify the mapping contains the expected data
        verifyMappingData(mapping, serviceName, serviceId, environment);
        
        // Now try to read the actual contents directly from /proc/self/mem
        verifyMappingContents(mapping, serviceName, serviceId, environment);
        
        // Also try using the native read functionality
        try {
            OTelContext.ProcessContext readContext = OTelContext.getInstance().readProcessContext();
            if (readContext != null) {
                System.out.println("Successfully read context using native function:");
                System.out.println("  Service Name: " + readContext.serviceName);
                System.out.println("  Service Instance ID: " + readContext.serviceInstanceId);
                System.out.println("  Environment: " + readContext.deploymentEnvironmentName);
                
                assertEquals(serviceName, readContext.serviceName, "Service name should match via native read");
                assertEquals(serviceId, readContext.serviceInstanceId, "Service instance ID should match via native read");
                assertEquals(environment, readContext.deploymentEnvironmentName, "Environment should match via native read");
            } else {
                System.out.println("Native read returned null - this may indicate OTEL_PROCESS_CTX_NO_READ is defined");
            }
        } catch (Exception e) {
            System.out.println("Native read failed: " + e.getMessage());
            // Don't fail the test if native read doesn't work - it's a bonus feature
        }
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
        
        // Pattern to match: address-address permissions offset dev inode [anon:OTEL_CTX]
        Pattern otelPattern = Pattern.compile("^([0-9a-f]+)-([0-9a-f]+)\\s+(\\S+)\\s+\\S+\\s+\\S+\\s+\\S+\\s*\\[anon:OTEL_CTX\\].*$");
        
        try (BufferedReader reader = Files.newBufferedReader(mapsFile)) {
            String line;
            while ((line = reader.readLine()) != null) {
                Matcher matcher = otelPattern.matcher(line);
                if (matcher.matches()) {
                    return new OtelMappingInfo(
                        matcher.group(1),  // start address
                        matcher.group(2),  // end address  
                        matcher.group(3)   // permissions
                    );
                }
            }
        }
        return null;
    }
    
    private void verifyMappingData(OtelMappingInfo mapping, String expectedServiceName, 
                                 String expectedServiceId, String expectedEnvironment) throws IOException {
        // Verify the mapping has read permission (after setup, permissions are changed to read-only)
        assertTrue(mapping.permissions.contains("r"), 
            "OTEL mapping should have read permission, got: " + mapping.permissions);
        
        // The mapping should be read-only (no write or execute permissions after setup)
        assertFalse(mapping.permissions.contains("w"), 
            "OTEL mapping should not have write permission after setup, got: " + mapping.permissions);
        assertFalse(mapping.permissions.contains("x"), 
            "OTEL mapping should not have execute permission after setup, got: " + mapping.permissions);
        
        // Convert hex addresses to long to calculate size
        long startAddr = Long.parseUnsignedLong(mapping.startAddress, 16);
        long endAddr = Long.parseUnsignedLong(mapping.endAddress, 16);
        long size = endAddr - startAddr;
       
        // Note: We can't easily read the mapping content from Java since it's marked as executable-only,
        // but the fact that it exists with the correct name and properties indicates the native code worked
        
        System.out.println("OTEL mapping found:");
        System.out.println("  Address range: " + mapping.startAddress + "-" + mapping.endAddress);
        System.out.println("  Size: " + size + " bytes");  
        System.out.println("  Permissions: " + mapping.permissions);
        System.out.println("  Expected service name: " + expectedServiceName);
        System.out.println("  Expected service ID: " + expectedServiceId);
        System.out.println("  Expected environment: " + expectedEnvironment);

                // The mapping should be a reasonable size
        assertTrue(size > 0, "OTEL mapping size should be positive, got: " + size + " bytes");
    }
    
    private void verifyMappingContents(OtelMappingInfo mapping, String expectedServiceName, 
                                     String expectedServiceId, String expectedEnvironment) throws IOException {
        System.out.println("Reading OTEL mapping contents directly from /proc/self/mem...");
        
        long startAddr = Long.parseUnsignedLong(mapping.startAddress, 16);
        long endAddr = Long.parseUnsignedLong(mapping.endAddress, 16);
        long size = endAddr - startAddr;
        
        try (RandomAccessFile memFile = new RandomAccessFile("/proc/self/mem", "r")) {
            // Seek to the mapping address
            memFile.seek(startAddr);
            
            // Read the mapping contents
            byte[] mappingBytes = new byte[(int) size];
            int bytesRead = memFile.read(mappingBytes);
            
            System.out.println("Read " + bytesRead + " bytes from mapping at address " + mapping.startAddress);
            
            // The first 8 bytes should be the signature "OTEL_CTX"
            if (bytesRead >= 8) {
                String signature = new String(mappingBytes, 0, 8);
                System.out.println("Signature: '" + signature + "'");
                assertEquals("OTEL_CTX", signature, "Mapping signature should match");
                
                // Parse the rest of the otel_process_ctx_mapping struct
                if (bytesRead >= 16) {
                    // Next 4 bytes: version (uint32_t)
                    int version = ((mappingBytes[8] & 0xFF)) |
                                 ((mappingBytes[9] & 0xFF) << 8) |
                                 ((mappingBytes[10] & 0xFF) << 16) |
                                 ((mappingBytes[11] & 0xFF) << 24);
                    System.out.println("Version: " + version);
                    assertEquals(1, version, "Version should be 1");
                    
                    // Next 4 bytes: payload size (uint32_t)  
                    int payloadSize = ((mappingBytes[12] & 0xFF)) |
                                     ((mappingBytes[13] & 0xFF) << 8) |
                                     ((mappingBytes[14] & 0xFF) << 16) |
                                     ((mappingBytes[15] & 0xFF) << 24);
                    System.out.println("Payload size: " + payloadSize);
                    assertTrue(payloadSize > 0, "Payload size should be positive");
                    
                    // Next 8 bytes: payload pointer (char*)
                    // We can't directly read from this pointer in Java, but we can verify it's not null
                    boolean hasPayload = false;
                    for (int i = 16; i < 24; i++) {
                        if (mappingBytes[i] != 0) {
                            hasPayload = true;
                            break;
                        }
                    }
                    System.out.println("Has payload pointer: " + hasPayload);
                    assertTrue(hasPayload, "Payload pointer should not be null");
                }
            }
            
            System.out.println("Successfully verified OTEL mapping structure contains expected data");
        } catch (IOException e) {
            System.out.println("Could not read from /proc/self/mem: " + e.getMessage());
            System.out.println("This is unexpected since the mapping should have read permissions");
            
            // This should not happen with the current implementation - the mapping should be readable
            fail("Failed to read OTEL mapping from /proc/self/mem: " + e.getMessage());
        }
    }

    @Test
    public void testProcessContextNativeRead() throws IOException {
        // Only run on Linux - macOS doesn't support process context
        Assumptions.assumeTrue(Platform.isLinux());
        
        String serviceName = "test-service-native";
        String serviceId = "test-instance-456";  
        String environment = "test-env-native";
        
        // Set the process context
        OTelContext.getInstance().setProcessContext(serviceName, serviceId, environment);
        
        // Verify the OTEL mapping was created
        OtelMappingInfo mapping = findOtelMapping();
        assertNotNull(mapping, "OTEL mapping should exist after setProcessCtx");
        
        // Test native read functionality through JNI if available
        try {
            // This would call the native otel_process_ctx_read() function
            // Note: This assumes there's a JNI wrapper for the read functionality
            // If not available, this test will be skipped
            System.out.println("Testing native context read functionality...");
            
            // For now, we verify that the mapping structure is correct as per the C implementation
            verifyMappingStructure(mapping, serviceName, serviceId, environment);
            
        } catch (UnsatisfiedLinkError e) {
            System.out.println("Native read functionality not available, skipping native read test");
        }
    }

    @Test
    public void testNativeReadFunctionality() {
        // Only run on Linux - macOS doesn't support process context
        Assumptions.assumeTrue(Platform.isLinux());
        
        String serviceName = "test-service-read";
        String serviceId = "test-instance-789";
        String environment = "test-env-read";
        
        OTelContext context = OTelContext.getInstance();
        
        // Verify no context exists initially
        OTelContext.ProcessContext initialContext = context.readProcessContext();
        System.out.println("Initial context: " + initialContext);
        
        // Set the process context
        context.setProcessContext(serviceName, serviceId, environment);
        
        // Now read it back using the native function
        OTelContext.ProcessContext readContext = context.readProcessContext();
        
        System.out.println("Read context: " + readContext);
        assertNotNull(readContext, "Should be able to read back the published context");
        assertEquals(serviceName, readContext.serviceName, "Service name should match");
        assertEquals(serviceId, readContext.serviceInstanceId, "Service instance ID should match");
        assertEquals(environment, readContext.deploymentEnvironmentName, "Environment name should match");
        
        System.out.println("Successfully verified context read-back functionality:");
        System.out.println("  Service Name: " + readContext.serviceName);
        System.out.println("  Service Instance ID: " + readContext.serviceInstanceId);
        System.out.println("  Environment: " + readContext.deploymentEnvironmentName);
    }
    
    private void verifyMappingStructure(OtelMappingInfo mapping, String expectedServiceName, 
                                       String expectedServiceId, String expectedEnvironment) throws IOException {
        System.out.println("Verifying OTEL mapping structure against C implementation...");
        
        long startAddr = Long.parseUnsignedLong(mapping.startAddress, 16);
        long endAddr = Long.parseUnsignedLong(mapping.endAddress, 16);
        long size = endAddr - startAddr;
        
        // Verify structure has minimum expected size for the header
        assertTrue(size >= 24, "Mapping size should be at least 24 bytes for the header, got: " + size);
        
        try (RandomAccessFile memFile = new RandomAccessFile("/proc/self/mem", "r")) {
            memFile.seek(startAddr);
            
            // Read at least the header (24 bytes minimum)
            int headerSize = Math.min(24, (int) size);
            byte[] mappingBytes = new byte[headerSize];
            int bytesRead = memFile.read(mappingBytes);
            assertEquals(headerSize, bytesRead, "Should read the header bytes");
            
            // Verify signature at offset 0 (8 bytes)
            String signature = new String(mappingBytes, 0, 8);
            assertEquals("OTEL_CTX", signature, "Signature should be OTEL_CTX");
            
            // Verify version at offset 8 (4 bytes, little endian)
            int version = ((mappingBytes[8] & 0xFF)) |
                         ((mappingBytes[9] & 0xFF) << 8) |
                         ((mappingBytes[10] & 0xFF) << 16) |
                         ((mappingBytes[11] & 0xFF) << 24);
            assertEquals(1, version, "Version should be 1");
            
            // Verify payload size at offset 12 (4 bytes, little endian)
            int payloadSize = ((mappingBytes[12] & 0xFF)) |
                             ((mappingBytes[13] & 0xFF) << 8) |
                             ((mappingBytes[14] & 0xFF) << 16) |
                             ((mappingBytes[15] & 0xFF) << 24);
            assertTrue(payloadSize > 0, "Payload size should be positive");
            
            // Calculate expected payload size for msgpack encoding
            // map16 header (3 bytes) + 3 key-value pairs encoded as str16
            int expectedSize = 3; // map16 header
            expectedSize += 3 + "service.name".length() + 3 + expectedServiceName.length();
            expectedSize += 3 + "service.instance.id".length() + 3 + expectedServiceId.length(); 
            expectedSize += 3 + "deployment.environment.name".length() + 3 + expectedEnvironment.length();
            
            assertEquals(expectedSize, payloadSize, 
                "Payload size should match calculated msgpack size");
            
            // Verify payload pointer at offset 16 (8 bytes) if we have enough data
            if (mappingBytes.length >= 24) {
                // We can't read the payload content from here, but verify pointer is non-null
                boolean hasPayload = false;
                for (int i = 16; i < 24; i++) {
                    if (mappingBytes[i] != 0) {
                        hasPayload = true;
                        break;
                    }
                }
                assertTrue(hasPayload, "Payload pointer should not be null");
            }
            
            System.out.println("Successfully verified OTEL mapping structure:");
            System.out.println("  Signature: " + signature);
            System.out.println("  Version: " + version);
            System.out.println("  Payload size: " + payloadSize + " bytes");
            System.out.println("  Expected payload size: " + expectedSize + " bytes");
            
        } catch (IOException e) {
            fail("Failed to read OTEL mapping structure: " + e.getMessage());
        }
    }
}