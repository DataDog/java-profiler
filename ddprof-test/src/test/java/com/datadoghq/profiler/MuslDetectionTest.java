package com.datadoghq.profiler;

import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class MuslDetectionTest {

    @Test
    public void testIsMusl() throws IOException {
        Assumptions.assumeTrue(Platform.isLinux(), "not running on linux");
        String libc = System.getenv("LIBC");
        Assumptions.assumeTrue(libc != null, "not running in CI, so LIBC envvar not set");
        boolean isMusl = "musl".equalsIgnoreCase(libc);
        assertEquals(isMusl, JavaProfiler.isMuslProcSelfMaps());
        assertEquals(isMusl, JavaProfiler.isMuslJavaExecutable());
        assertEquals(isMusl, JavaProfiler.isMusl());
    }
}
