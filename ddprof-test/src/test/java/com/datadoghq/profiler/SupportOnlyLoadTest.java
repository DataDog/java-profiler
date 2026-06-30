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
        JVMAccess access = JVMAccess.getInstance();
        // On non-HotSpot JVMs (J9, Zing) the support library may load but the
        // health check may not succeed; skip the maps assertion in that case.
        org.junit.jupiter.api.Assumptions.assumeTrue(access.isActive(),
            "JVMAccess not active on this JVM — skipping map check");

        boolean profilerMapped = Files.lines(Paths.get("/proc/self/maps"))
            .anyMatch(line -> line.contains("libjavaProfiler"));

        assertFalse(profilerMapped,
            "libjavaProfiler.so must NOT be mapped when only JVMAccess is used");
    }

    @Test
    void jvmAccessCanReadJvmFlag() {
        JVMAccess access = JVMAccess.getInstance();
        assertTrue(access.isActive(), "JVMAccess must load successfully");
        // MaxHeapSize is always present on HotSpot
        long maxHeap = access.flags().getIntFlag("MaxHeapSize");
        assertTrue(maxHeap > 0, "MaxHeapSize must be positive");
    }
}
