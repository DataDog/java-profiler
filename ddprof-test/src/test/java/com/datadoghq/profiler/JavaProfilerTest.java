package com.datadoghq.profiler;

import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class JavaProfilerTest extends AbstractProcessProfilerTest {
    @Test
    void sanityInitailizationTest() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));

        AtomicInteger initFlag = new AtomicInteger(0);
        boolean val = launch("profiler", Collections.emptyList(), "", l -> {
            if (l.contains("[TEST::INFO] VM::initLibrary")) {
                initFlag.set(initFlag.get() | 1);
            } else if (l.contains("[TEST::INFO] VM::initProfilerBridge")) {
                initFlag.set(initFlag.get() | 2);
            }
            // found both expected sections; can terminate the test now
            return initFlag.get() != 3;
        }, null);

        assertTrue(val);
    }

    @Test
    void testJ9DefaultSanity() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));
        assumeFalse(Platform.isMac()); // crashy on mac
        assumeTrue(Platform.isJ9());

        Path jfr = Files.createTempFile("j9", ".jfr");
        jfr.toFile().deleteOnExit();

        String sampler = "jvmti";
        if (Platform.isJavaVersion(8) && Platform.isJavaVersionAtLeast(8, 0, 432)) {
            sampler = "asgct";
        } else if (Platform.isJavaVersion(11) && Platform.isJavaVersionAtLeast(11, 0, 25)) {
            sampler = "asgct";
        } else if (Platform.isJavaVersion(17) && Platform.isJavaVersionAtLeast(17, 0, 13)) {
            sampler = "asgct";
        }

        AtomicReference<String> usedSampler = new AtomicReference<>("");
        AtomicBoolean hasWall = new AtomicBoolean(false);
        boolean val = launch("profiler", Collections.emptyList(), "start,cpu,file=" + jfr, l -> {
            if (l.contains("J9[cpu]")) {
                usedSampler.set(l.split("=")[1]);
                return false;
            } else if (l.contains("J9[wall]")) {
                hasWall.set(true);
                return false;
            }
            return true;
        }, null);
        assertTrue(val);
        assertEquals(sampler, usedSampler.get());
        assertFalse(hasWall.get());
    }

    @Test
    void testJ9ForceJvmtiSanity() throws Exception {
        String config = System.getProperty("ddprof_test.config");
        assumeTrue("debug".equals(config));
        assumeFalse(Platform.isMac()); // crashy on mac
        assumeTrue(Platform.isJ9());

        Path jfr = Files.createTempFile("j9", ".jfr");
        jfr.toFile().deleteOnExit();

        String sampler = "jvmti";

        AtomicReference<String> usedSampler = new AtomicReference<>("");
        AtomicBoolean hasWall = new AtomicBoolean(false);
        List<String> args = new ArrayList<>();
        args.add("-XX:+KeepJNIIDs");
        args.add("-Ddd.profiling.ddprof.j9.sampler=jvmti");
        boolean val = launch("profiler", args, "start,cpu,file=" + jfr, l -> {
            if (l.contains("J9[cpu]")) {
                usedSampler.set(l.split("=")[1]);
                return false;
            } else if (l.contains("J9[wall]")) {
                hasWall.set(true);
                return false;
            }
            return true;
        }, null);
        assertTrue(val);
        assertEquals(sampler, usedSampler.get());
        assertFalse(hasWall.get());
    }
}
