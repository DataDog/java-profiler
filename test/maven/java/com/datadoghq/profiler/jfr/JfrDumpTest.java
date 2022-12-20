package com.datadoghq.profiler.jfr;

import com.datadoghq.profiler.AbstractProfilerTest;
import one.profiler.JavaProfiler;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class JfrDumpTest extends AbstractProfilerTest {

    @AfterEach
    public void after() throws IOException {
        Files.deleteIfExists(Paths.get(dumpPath));
    }

    @Test
    @Timeout(value = 30)
    public void runTest() throws Exception {
        Path dump = Files.createTempFile("jfr-dump-test", ".jfr");
        dumpPath = dump.toAbsolutePath().toString();
        dumpAfterSecs = 1;

        ts = System.nanoTime();
        while (dumps < 1) {
            method1();
            method2();
            method3();
        }
        //  TODO verify Duration=1s with JDK8 compatability somehow
    }

    private static volatile int value;

    private static void method1() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
            tryDump();
        }
    }

    private static void method2() {
        for (int i = 0; i < 1000000; ++i) {
            ++value;
            tryDump();
        }
    }

    private static void method3() throws Exception {
        for (int i = 0; i < 1000; ++i) {
            for (String s : new File("/tmp").list()) {
                value += s.hashCode();
            }
            tryDump();
        }
    }

    private static String dumpPath;
    private static int dumpAfterSecs;
    private static long ts;

    private static int dumps;

    private static void tryDump() {
        if (dumpPath != null && ts > 0) {
            if (System.nanoTime() - ts > (dumpAfterSecs * 1_000_000_000L)) {
                if (!JavaProfiler.getInstance().dumpJfr(Paths.get(dumpPath))) {
                    throw new IllegalStateException("Unable to dump JFR data to " + dumpPath);
                }
                dumps++;
                ts = -1;
            }
        }
    }

    @Override
    protected String getProfilerCommand() {
        return "wall=5ms";
    }
}
