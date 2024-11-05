package com.datadoghq.profiler;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class JVMAccessTest {
    private static JVMAccess jvmAccess;

    @BeforeAll
    static void setUp() {
        Assumptions.assumeTrue(Platform.isJ9()); // J9 does not support vmstructs
        jvmAccess = JVMAccess.getInstance();
    }

    @Test
    void testGetFlag() {
        JVMAccess.Flags flags = jvmAccess.flags();
        // non-existent flag
        assertNull(flags.getStringFlag("test"));

        // The test relies on the gradle test task setting the JVM flags to expected values
        assertEquals("build/hs_err_pid%p.log", flags.getStringFlag("ErrorFile")); // set to 'build/hs_err_pid%p.log' in the test task
        assertTrue(flags.getBooleanFlag("ResizeTLAB")); // set to 'true' in the test task
        assertEquals(512 * 1024 * 1024, flags.getIntFlag("MaxHeapSize")); // set to 512m in the test task
    }

    @Test
    void testGetFlagMismatch() {
        JVMAccess.Flags flags = jvmAccess.flags();

        assertNull(flags.getStringFlag("ResizeTLAB")); // default is 'null'
        assertFalse(flags.getBooleanFlag("ErrorFile")); // default is 'false'
        assertEquals(0, flags.getFloatFlag("MaxHeapSize")); // default is '0'
    }

    @Test
    void testMutableFlags() {
        JVMAccess.Flags flags = jvmAccess.flags();
        String errorFile = "/tmp/hs_err_pid%p.log";
        flags.setStringFlag("ErrorFile", errorFile);
        assertEquals(errorFile, flags.getStringFlag("ErrorFile"));
    }

    @Test
    void testMutableFlagsMismatch() {
        JVMAccess.Flags flags = jvmAccess.flags();
        String val = flags.getStringFlag("ErrorFile");
        flags.setBooleanFlag("ErrorFile", true);
        // make sure the flag value is not changed and overwritten with rubbish
        assertEquals(val, flags.getStringFlag("ErrorFile"));
    }

    @Test
    void testImmutableFlags() {
        JVMAccess.Flags flags = jvmAccess.flags();
        flags.setBooleanFlag("ResizeTLAB", false);
        // this flag is immutable; it must retain its original value
        assertTrue(flags.getBooleanFlag("ResizeTLAB"));
    }
}
