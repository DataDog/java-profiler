package com.datadoghq.profiler.nativelibs;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Test;

import java.nio.file.Paths;

public class CaviumTest extends AbstractProfilerTest {

    @Test
    public void testLoadCaviumLibrary() {
        Paths.get("/opt").forEach(System.err::println);
        try {
            System.load("/opt/cloudhsm/lib/libcaviumjca.so");
        } catch (Error ignore) {
        }
        // should not crash
    }

    @Override
    protected String getProfilerCommand() {
        return "cpu=10m";
    }
}
