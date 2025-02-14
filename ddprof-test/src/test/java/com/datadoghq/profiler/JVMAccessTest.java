package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.Collections;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class JVMAccessTest extends AbstractProcessProfilerTest {
    @BeforeAll
    static void setUp() {
        assumeFalse(Platform.isJ9() || Platform.isZing()); // J9 and Zing do not support vmstructs
    }

    @Test
    void sanityInitailizationTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));

        AtomicBoolean initLibraryFound = new AtomicBoolean(false);
        AtomicBoolean initProfilerFound = new AtomicBoolean(false);

        boolean rslt = launch("library", Collections.emptyList(), null, 
            l -> {
                initLibraryFound.set(initLibraryFound.get() | l.contains("[TEST::INFO] VM::initLibrary"));
                initProfilerFound.set(initProfilerFound.get() | l.contains("[TEST::INFO] VM::initProfilerBridge"));
                return true;
            },
            null
        );

        assertTrue(rslt);

        assertTrue(initLibraryFound.get(), "initLibrary not found");
        assertFalse(initProfilerFound.get(), "initProfilerBridge found");
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

        AtomicReference<String> foundVersion = new AtomicReference<>(null);

        boolean rslt = launch("library", Collections.emptyList(), null, l -> {
            if (l.contains("[TEST::INFO] jvm_version#")) {
                foundVersion.set(l.split("#")[1]);
                return false;
            }
            return true;
        }, null);

        assertTrue(rslt);

        assertNotNull(foundVersion.get(), "java version not found in logs");
        assertEquals(javaVersion, foundVersion.get(), "invalid java version");
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
