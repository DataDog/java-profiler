package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledOnOs;
import org.junit.jupiter.api.condition.OS;

import java.nio.file.Files;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Verifies that {@link JVMAccess} loads only libJavaSupport.so and does NOT load libjavaProfiler.so.
 */
class SupportOnlyLoadTest {

    @Test
    @EnabledOnOs(OS.LINUX)
    void jvmAccessDoesNotLoadProfilerLibrary() throws Exception {
        // Snapshot maps BEFORE initializing JVMAccess. The profiler may already be
        // mapped if it was loaded as a JVM agent by other tests in the same JVM;
        // in that case we cannot attribute the mapping to JVMAccess, so skip.
        boolean profilerAlreadyMapped = Files.lines(Paths.get("/proc/self/maps"))
            .anyMatch(line -> line.contains("libjavaProfiler"));
        org.junit.jupiter.api.Assumptions.assumeFalse(profilerAlreadyMapped,
            "libjavaProfiler.so already mapped (loaded as agent) — skipping isolation check");

        JVMAccess access = JVMAccess.getInstance();
        org.junit.jupiter.api.Assumptions.assumeTrue(access.isActive(),
            "JVMAccess not active on this JVM — skipping map check");

        boolean profilerMappedAfter = Files.lines(Paths.get("/proc/self/maps"))
            .anyMatch(line -> line.contains("libjavaProfiler"));
        assertFalse(profilerMappedAfter,
            "libjavaProfiler.so must NOT be mapped when only JVMAccess is used");
    }

    @Test
    void jvmAccessCanReadJvmFlag() {
        JVMAccess access = JVMAccess.getInstance();
        // healthCheck0 returns false on J9/Zing (no HotSpot vmstructs)
        org.junit.jupiter.api.Assumptions.assumeTrue(access.isActive(),
            "JVMAccess not active — VMStructs unavailable (J9/Zing)");
        long maxHeap = access.flags().getIntFlag("MaxHeapSize");
        assertTrue(maxHeap > 0, "MaxHeapSize must be positive");
    }
}
