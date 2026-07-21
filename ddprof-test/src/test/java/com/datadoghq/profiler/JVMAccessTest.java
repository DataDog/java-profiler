package com.datadoghq.profiler;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.lang.management.ManagementFactory;
import java.nio.file.Path;
import java.util.Collections;
import java.util.List;
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
                return LineConsumerResult.CONTINUE;
            },
            null
        ).inTime;

        assertTrue(rslt);

        assertTrue(initLibraryFound.get(), "initLibrary not found");
        assertFalse(initProfilerFound.get(), "initProfilerBridge found");
    }

    /**
     * Regression test for the Agent_OnLoad (static {@code -agentpath:}) startup path: unlike the
     * {@code library}/{@code profiler} targets used elsewhere in this file, which load the native
     * library via {@code System.load} ({@code JNI_OnLoad} -> {@code VM::initLibrary}), an
     * {@code -agentpath:} JVM argument makes {@code Agent_OnLoad} -> {@code VM::initProfilerBridge}
     * the *first* native entry point invoked, with no prior call to {@code VM::ready()}.
     * {@code initProfilerBridge()} looks up the {@code DebugNonSafepoints} VM flag via
     * {@code VMFlag::find()}, gated on {@code CodeHeap::available()} -- both depend on
     * {@code VMStructs} offsets/addresses populated by {@code VMStructs::init()}. If that
     * initialization has been deferred to the asynchronous {@code VMInit} callback without also
     * covering this call site, {@code CodeHeap::available()} reads {@code false} (its backing
     * address is still unset) and the code takes the JDK-8173361 workaround path instead of ever
     * calling {@code VMFlag::find()} -- silently disabling {@code CompiledMethodLoad} events and
     * skipping the {@code DebugNonSafepoints} detection, even on a JVM where both should have
     * succeeded.
     */
    @Test
    void agentOnLoadVMFlagDetectionTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));

        Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));

        AtomicReference<String> workaroundLine = new AtomicReference<>(null);
        AtomicReference<String> flagLine = new AtomicReference<>(null);

        boolean rslt = launch("noop",
            Collections.singletonList("-agentpath:" + agentLib.toAbsolutePath()),
            null,
            l -> {
                if (l.contains("[TEST::INFO] CompiledMethodLoad workaround:")) {
                    workaroundLine.set(l);
                    return LineConsumerResult.STOP;
                }
                if (l.contains("[TEST::INFO] DebugNonSafepoints flag")) {
                    flagLine.set(l);
                    return LineConsumerResult.STOP;
                }
                return LineConsumerResult.CONTINUE;
            },
            null
        ).inTime;

        assertTrue(rslt);
        assertNull(workaroundLine.get(),
            "VM::initProfilerBridge() took the JDK-8173361 CompiledMethodLoad workaround path (" +
            workaroundLine.get() + ") instead of reaching the DebugNonSafepoints lookup -- " +
            "CodeHeap::available() was false, meaning VMStructs was not initialized yet during " +
            "Agent_OnLoad (startup-ordering regression)");
        assertNotNull(flagLine.get(), "expected DebugNonSafepoints flag lookup log line was not observed");
        assertTrue(flagLine.get().contains("flag found"),
            "VMFlag::find(\"DebugNonSafepoints\") returned NULL during Agent_OnLoad: " + flagLine.get());
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
                return LineConsumerResult.STOP;
            }
            return LineConsumerResult.CONTINUE;
        }, null).inTime;

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
        // Derive the expected heap from this JVM's own -Xmx argument rather than hardcoding a
        // value, so the test stays valid regardless of what the build task passes per config.
        assertEquals(configuredMaxHeapBytes(), flags.getIntFlag("MaxHeapSize"));
        assertNotNull(flags.getStringFlag("OnError"));
    }

    private static long configuredMaxHeapBytes() {
        // HotSpot honors the last -Xmx flag on the command line when duplicates are
        // present (e.g. ASan configs append a config-specific -Xmx after the
        // standard one), so scan from the end to find the effective value.
        List<String> jvmArgs = ManagementFactory.getRuntimeMXBean().getInputArguments();
        for (int i = jvmArgs.size() - 1; i >= 0; i--) {
            String arg = jvmArgs.get(i);
            if (arg.startsWith("-Xmx")) {
                return parseMemorySize(arg.substring("-Xmx".length()));
            }
        }
        throw new IllegalStateException("Test JVM was not launched with -Xmx: " + jvmArgs);
    }

    private static long parseMemorySize(String value) {
        try {
            char unit = Character.toLowerCase(value.charAt(value.length() - 1));
            switch (unit) {
                case 'k': return Long.parseLong(value.substring(0, value.length() - 1)) * 1024L;
                case 'm': return Long.parseLong(value.substring(0, value.length() - 1)) * 1024L * 1024L;
                case 'g': return Long.parseLong(value.substring(0, value.length() - 1)) * 1024L * 1024L * 1024L;
                default: return Long.parseLong(value);
            }
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Invalid -Xmx memory size: " + value, e);
        }
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
