package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.nio.file.Files;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class JVMAccessTest {
    @BeforeAll
    static void setUp() {
        assumeFalse(Platform.isJ9() || Platform.isZing()); // J9 and Zing do not support vmstructs
    }

    @Test
    void sanityInitailizationTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));

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

        ProcessBuilder pb = new ProcessBuilder(javaHome + "/bin/java", "-cp", System.getProperty("java.class.path"), ExternalLauncher.class.getName(), "library");
        pb.redirectOutput(outFile);
        pb.redirectError(errFile);
        Process p = pb.start();
        int val = p.waitFor();
        assertEquals(0, val);

        boolean initLibraryFound = false;
        boolean initProfilerFound = false;
        for (String line : Files.readAllLines(outFile.toPath())) {
            initLibraryFound |= line.contains("[TEST::INFO] VM::initLibrary");
            if (line.contains("[TEST::INFO] VM::initProfilerBridge")) {
                // profiler is not expected to get initialized here; first occurrence means the test failed
                initProfilerFound = true;
                break;
            }
        }
        assertTrue(initLibraryFound, "initLibrary not found");
        assertFalse(initProfilerFound, "initProfilerBridge found");
    }

    @Test
    void jvmVersionTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));

        String javaVersion = System.getenv("JAVA_VERSION");
        assumeTrue(javaVersion != null);
        if (javaVersion.startsWith("8u")) {
            // convert 8u432 to nomralized 8.0.432 format which is expected
            javaVersion = "8.0." + javaVersion.split("u")[1];
        }

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

        ProcessBuilder pb = new ProcessBuilder(javaHome + "/bin/java", "-cp", System.getProperty("java.class.path"), ExternalLauncher.class.getName(), "library");
        pb.redirectOutput(outFile);
        pb.redirectError(errFile);
        Process p = pb.start();
        int val = p.waitFor();
        assertEquals(0, val);

        String foundVersion = null;
        for (String line : Files.readAllLines(outFile.toPath())) {
            System.err.println(line);
            if (line.contains("[TEST::INFO] jvm_version#")) {
                foundVersion = line.split("#")[1];
                break;
            }
        }
        assertNotNull(foundVersion, "java version not found in logs");
        assertEquals(javaVersion, foundVersion, "invalid java version");
    }

    @Test
    void testGetFlag() {
        JVMAccess.Flags flags = JVMAccess.getInstance().flags();
        // non-existent flag
        assertNull(flags.getStringFlag("test"));

        // The test relies on the gradle test task setting the JVM flags to expected values
        assertEquals("build/hs_err_pid%p.log", flags.getStringFlag("ErrorFile")); // set to 'build/hs_err_pid%p.log' in the test task
        assertTrue(flags.getBooleanFlag("ResizeTLAB")); // set to 'true' in the test task
        assertEquals(512 * 1024 * 1024, flags.getIntFlag("MaxHeapSize")); // set to 512m in the test task
    }

    @Test
    void testGetFlagMismatch() {
        JVMAccess.Flags flags = JVMAccess.getInstance().flags();

        assertNull(flags.getStringFlag("ResizeTLAB")); // default is 'null'
        assertFalse(flags.getBooleanFlag("ErrorFile")); // default is 'false'
        assertEquals(0, flags.getFloatFlag("MaxHeapSize")); // default is '0'
    }

    @Test
    void testMutableFlags() {
        JVMAccess.Flags flags = JVMAccess.getInstance().flags();
        String errorFile = "/tmp/hs_err_pid%p.log";
        flags.setStringFlag("ErrorFile", errorFile);
        assertEquals(errorFile, flags.getStringFlag("ErrorFile"));
    }

    @Test
    void testMutableFlagsMismatch() {
        JVMAccess.Flags flags = JVMAccess.getInstance().flags();
        String val = flags.getStringFlag("ErrorFile");
        flags.setBooleanFlag("ErrorFile", true);
        // make sure the flag value is not changed and overwritten with rubbish
        assertEquals(val, flags.getStringFlag("ErrorFile"));
    }
}
