/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProfilerTest;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Locale;
import java.util.concurrent.TimeUnit;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * Functional check for the process-wide malloc arena counters
 * ({@code malloc_arena_bytes}, {@code malloc_in_use_bytes} and siblings).
 *
 * <p>These counters are produced from glibc's {@code mallinfo2()}, which the
 * native code resolves at runtime with {@code dlsym(RTLD_DEFAULT, "mallinfo2")}
 * (see {@code mallocInfo.cpp}). Resolving at runtime is what keeps the counters
 * alive in binaries whose build headers predate glibc 2.33 -- the shipped
 * release libraries are built against glibc 2.28 headers (el8), where a
 * compile-time gate used to compile the whole path out and left every counter
 * at zero. This test pins the observable end of that: on a runtime glibc that
 * provides {@code mallinfo2()} (2.33+) a running JVM must always report
 * non-zero arena and in-use figures, while on runtimes without it (older
 * glibc, musl) the counters stay unset at zero.
 *
 * <p>The test is skipped, through a JUnit assumption, when glibc malloc is
 * detectably not the allocator in force (the asan/tsan sanitizer test configs,
 * an LD_PRELOAD'd jemalloc/tcmalloc), because the native code leaves the
 * counters at zero there regardless of the glibc version.
 */
public class MallocArenaCountersTest extends AbstractProfilerTest {

    @Override
    protected String getProfilerCommand() {
        return "wall=~1ms";
    }

    @Test
    public void shouldPublishNonZeroMallocArenaCountersWhenMallinfo2IsAvailable() throws Exception {
        busyLoop();
        stopProfiler();

        // The counters live in a fixed table, so they are always emitted --
        // -1 would mean the ProfilerCounter events never made it into the
        // recording at all, which is a harness failure, not a counter state.
        long arena = getRecordedCounterValue("malloc_arena_bytes");
        long inUse = getRecordedCounterValue("malloc_in_use_bytes");
        assertNotEquals(-1, arena, "malloc_arena_bytes not present in the recording");
        assertNotEquals(-1, inUse, "malloc_in_use_bytes not present in the recording");
        long trimmable = getRecordedCounterValue("malloc_trimmable_bytes");
        long mmapped = getRecordedCounterValue("malloc_mmap_bytes");
        assertNotEquals(-1, trimmable, "malloc_trimmable_bytes not present in the recording");
        assertNotEquals(-1, mmapped, "malloc_mmap_bytes not present in the recording");

        // The native side leaves every arena counter at 0 when glibc malloc is not
        // the allocator in force (Recording::glibcMallocActive(): sanitizer
        // runtimes, LD_PRELOAD'd jemalloc/tcmalloc), so the glibc-version oracle
        // below does not apply there.
        String reason = nonGlibcAllocatorReason();
        Assumptions.assumeTrue(reason == null,
                "glibc malloc not active (" + reason + "); arena counters legitimately stay 0");

        int[] glibc = runtimeGlibcVersion();
        boolean mallinfo2Available = glibc != null && (glibc[0] > 2 || (glibc[0] == 2 && glibc[1] >= 33));
        if (!mallinfo2Available) {
            // musl and pre-2.33 glibc runtimes: the counters stay unset (0),
            // mirroring the dlsym lookup failing in the native code.
            assertEquals(0, arena, "malloc_arena_bytes must stay unset without mallinfo2");
            assertEquals(0, inUse, "malloc_in_use_bytes must stay unset without mallinfo2");
            assertEquals(0, trimmable, "malloc_trimmable_bytes must stay unset without mallinfo2");
            assertEquals(0, mmapped, "malloc_mmap_bytes must stay unset without mallinfo2");
            return;
        }

        // A running JVM has always handed out memory from glibc's arenas, so a
        // zero here means the mallinfo2 path was disabled -- exactly the bug
        // this guards against (compile-time gating compiled it out of the el8
        // release builds). Configurations where glibc malloc is detectably not
        // in force were skipped above. trimmable/mmapped are not asserted
        // positive: neither is guaranteed non-zero at flush time.
        assertTrue(arena > 0, "malloc_arena_bytes must be non-zero on glibc "
                + glibc[0] + "." + glibc[1] + ", was " + arena);
        assertTrue(inUse > 0, "malloc_in_use_bytes must be non-zero on glibc "
                + glibc[0] + "." + glibc[1] + ", was " + inUse);
    }

    /**
     * Returns why glibc malloc cannot be the allocator in force for this JVM, or
     * {@code null} when nothing detectable says otherwise. Mirrors the cases in
     * which the native glibcMallocActive() check disables the arena counters.
     */
    private String nonGlibcAllocatorReason() {
        String config = System.getProperty("ddprof_test.config", "");
        if ("asan".equals(config) || "tsan".equals(config)) {
            return "sanitizer test config " + config;
        }
        if (isAsan()) {
            return "ASAN_OPTIONS set";
        }
        if (isTsan()) {
            return "TSAN_OPTIONS set";
        }
        String preload = System.getenv("LD_PRELOAD");
        if (preload != null) {
            String p = preload.toLowerCase(Locale.ROOT);
            for (String lib : new String[] {"jemalloc", "tcmalloc", "libasan", "libtsan",
                    "clang_rt.asan", "clang_rt.tsan"}) {
                if (p.contains(lib)) {
                    return "LD_PRELOAD=" + preload;
                }
            }
        }
        return null;
    }

    /** Keeps the sampler busy briefly so native buffers are populated for the counters to report. */
    private void busyLoop() {
        long deadline = System.nanoTime() + 100_000_000L; // ~100ms
        double sink = 0;
        while (System.nanoTime() < deadline) {
            for (int i = 0; i < 10_000; i++) {
                sink += Math.sqrt(i);
            }
        }
        // Guard against dead-code elimination of the busy loop.
        assertTrue(!Double.isNaN(sink));
    }

    /**
     * Detects the runtime glibc version by running {@code ldd --version} and
     * taking the last {@code major.minor} pair from its first line (e.g.
     * {@code ldd (Ubuntu GLIBC 2.35-0ubuntu3.10) 2.35} or
     * {@code ldd (GNU libc) 2.17}). Returns {@code null} when the runtime is
     * not glibc (musl prints a version without a GLIBC marker; the probe is
     * not attempted at all on non-Linux platforms). stderr is merged into
     * stdout (musl's ldd prints its banner to stderr), the wait is bounded, and
     * the child is always destroyed, whatever the exit path.
     */
    private static int[] runtimeGlibcVersion() throws Exception {
        if (!System.getProperty("os.name", "").startsWith("Linux")) {
            return null;
        }
        Process process = new ProcessBuilder("ldd", "--version").redirectErrorStream(true).start();
        String firstLine;
        try {
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()))) {
                firstLine = reader.readLine();
            }
            process.waitFor(10, TimeUnit.SECONDS); // result ignored; finally reaps it either way
        } finally {
            process.destroyForcibly();
        }
        if (firstLine == null) {
            return null;
        }
        if (firstLine.contains("musl") || firstLine.contains("FreeBSD")) {
            return null;
        }
        Matcher matcher = Pattern.compile("(\\d+)\\.(\\d+)").matcher(firstLine);
        int[] version = null;
        while (matcher.find()) {
            version = new int[] {Integer.parseInt(matcher.group(1)), Integer.parseInt(matcher.group(2))};
        }
        return version;
    }
}
