package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.io.File;
import java.nio.file.Files;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class JavaProfilerTest {
    @Test
    void sanityInitailizationTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue(config != null && config.equals("debug"));

        String javaHome = System.getenv("JAVA_TEST_HOME");
        if (javaHome == null) {
            javaHome = System.getenv("JAVA_HOME");
        }
        if (javaHome == null) {
            javaHome = System.getProperty("java.home");
        }
        assertNotNull(javaHome);

        File outFile = Files.createTempFile("jvmaccess", ".out").toFile();
        outFile.deleteOnExit();
        File errFile = Files.createTempFile("jvmaccess", ".err").toFile();
        errFile.deleteOnExit();

        ProcessBuilder pb = new ProcessBuilder(javaHome + "/bin/java", "-cp", System.getProperty("java.class.path"), ExternalLauncher.class.getName(), "profiler");
        pb.redirectOutput(outFile);
        pb.redirectError(errFile);
        Process p = pb.start();
        int val = p.waitFor();

        boolean initLibraryFound = false;
        boolean initProfilerFound = false;
        for (String line : Files.readAllLines(outFile.toPath())) {
            initLibraryFound |= line.contains("[TEST::INFO] VM::initLibrary");
            initProfilerFound |= line.contains("[TEST::INFO] VM::initProfilerBridge");
            System.out.println("[out] " + line);
        }

        System.out.println();

        for (String line : Files.readAllLines(errFile.toPath())) {
            System.out.println("[err] " + line);
        }

        assertEquals(0, val);

        assertTrue(initLibraryFound, "initLibrary not found");
        assertTrue(initProfilerFound, "initProfilerBridge found");
    }
}
