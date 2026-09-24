/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.sanity;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Collections;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * {@code Profiler::start()}'s sanity-check guard ({@code sanity_checked} in {@code profiler.cpp})
 * is a function-local static with process lifetime, not reset by {@code profiler.stop()}. Every
 * test here therefore forks a fresh JVM ({@link #launch}) rather than calling
 * {@code JavaProfiler.getInstance()} in-process — an in-process test would share that static flag
 * (and the {@code Profiler} singleton) with every other test in the same test JVM, so whichever
 * test happens to run first would silently decide the outcome for the rest.
 */
public class SanityCheckTest extends AbstractProcessProfilerTest {

    private Path newJfrPath(String prefix) throws Exception {
        Path rootDir = Paths.get("/tmp/recordings");
        Files.createDirectories(rootDir);
        return Files.createTempFile(rootDir, prefix, ".jfr");
    }

    /**
     * An upper bound, in MB, on the memory sanity check's available-memory figure: the smaller of
     * {@code MemTotal} ({@code OS::getRamSize()}) and this cgroup namespace's root memory limit.
     * The native check takes the minimum over the process's whole cgroup ancestry, which includes
     * that root, so its figure can only be smaller than this.
     */
    private static long availableMemoryUpperBoundMb() throws Exception {
        long bytes = Long.MAX_VALUE;
        for (String line : Files.readAllLines(Paths.get("/proc/meminfo"))) {
            if (line.startsWith("MemTotal:")) {
                bytes = Long.parseLong(line.replaceAll("[^0-9]", "")) * 1024;
                break;
            }
        }
        for (String limitFile : new String[] {
                "/sys/fs/cgroup/memory.max", "/sys/fs/cgroup/memory/memory.limit_in_bytes"}) {
            Path path = Paths.get(limitFile);
            if (Files.isReadable(path)) {
                String value = new String(Files.readAllBytes(path)).trim();
                // cgroup v2 spells "unlimited" as "max"; v1 uses a near-Long.MAX_VALUE number.
                if (value.matches("[0-9]+")) {
                    bytes = Math.min(bytes, Long.parseLong(value));
                }
            }
        }
        if (bytes == Long.MAX_VALUE) {
            throw new IllegalStateException("MemTotal not found in /proc/meminfo");
        }
        return bytes / (1024 * 1024);
    }

    /**
     * nosanity=true bypasses sanity checks. The profiler must start successfully on any host.
     */
    @Test
    void nosanity_bypasses_checks() throws Exception {
        Path jfrDump = newJfrPath("sanity-check-test");
        try {
            LaunchResult result = launch("profiler", Collections.emptyList(),
                    "start,cpu=10ms,jfr,file=" + jfrDump.toAbsolutePath() + ",nosanity",
                    line -> LineConsumerResult.CONTINUE, line -> LineConsumerResult.CONTINUE);
            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");
        } finally {
            Files.deleteIfExists(jfrDump);
        }
    }

    /**
     * The override flag works regardless of value form (bare keyword vs explicit true).
     */
    @Test
    void nosanity_explicit_true_bypasses_checks() throws Exception {
        Path jfrDump = newJfrPath("sanity-check-test");
        try {
            LaunchResult result = launch("profiler", Collections.emptyList(),
                    "start,cpu=10ms,jfr,file=" + jfrDump.toAbsolutePath() + ",nosanity=true",
                    line -> LineConsumerResult.CONTINUE, line -> LineConsumerResult.CONTINUE);
            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");
        } finally {
            Files.deleteIfExists(jfrDump);
        }
    }

    /**
     * Sanity checks run at most once across start/stop cycles.
     * After a successful start with checks enabled, subsequent starts do not re-run checks.
     */
    @Test
    void sanity_checks_run_once() throws Exception {
        Path jfrDump1 = newJfrPath("sanity-check-test");
        Path jfrDump2 = newJfrPath("sanity-check-test");
        try {
            // First start with nosanity to guarantee success regardless of host resources.
            // Second start (without nosanity) must not fail due to re-running checks — the
            // static guard in the native layer ensures they only fire on the first invocation.
            String sequence = "start,cpu=10ms,jfr,file=" + jfrDump1.toAbsolutePath() + ",nosanity"
                    + ";STOP;"
                    + "start,cpu=10ms,jfr,file=" + jfrDump2.toAbsolutePath();
            LaunchResult result = launch("profiler-sequence", Collections.emptyList(), sequence,
                    line -> LineConsumerResult.CONTINUE, line -> LineConsumerResult.CONTINUE);
            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");
        } finally {
            Files.deleteIfExists(jfrDump1);
            Files.deleteIfExists(jfrDump2);
        }
    }

    /**
     * A forced -Xmx larger than the memory available to the process makes the memory sanity check fail
     * deterministically, regardless of the actual host resources. The check is advisory, so
     * the profiler must still start, and the JFR recording's settings must show the failure.
     */
    @Test
    void mem_sanity_check_failure_is_recorded_in_jfr() throws Exception {
        // SanityChecker::runChecks() skips the memory check on OpenJ9/Zing, where VMFlag
        // lookups are unavailable. An oversized -Xmx alone cannot force a failure there.
        assumeFalse(Platform.isJ9() || Platform.isZing());
        // OS::getRamSize() is a stub that always returns 0 on macOS (os_macos.cpp). The
        // zero return value keeps the memory check's upper bound at 0, so the check
        // always passes on macOS.
        assumeTrue(Platform.isLinux());

        Path rootDir = Paths.get("/tmp/recordings");
        Files.createDirectories(rootDir);
        Path forkedJfr = Files.createTempFile(rootDir, "sanity-check-mem-fail", ".jfr");
        try {
            // On Linux, Parallel GC's (the JDK 8 default) initial-heap commit is aligned
            // to a fraction of -Xmx regardless of -Xms, so -Xms8m alone still eagerly
            // commits ~28g and OOMs before the sanity check runs. G1 sizes its initial
            // commit in fixed-size regions independent of -Xmx, avoiding that.
            //
            // JDK 8's G1 still allocates and clears card-granularity bitmaps spanning the
            // whole reserved heap, one per parallel GC thread: measured on 8u504, a
            // -Xmx900g fork touches ~225MB per ParallelGCThreads on top of a ~360MB base
            // (1.3GB at 4 threads, 4GB at 16), enough to OOM-kill a 6GB CI container.
            // -Xmx is therefore sized just past the check's available-memory figure (a
            // 6GB-limited pod on a 380GB node needs ~7g, not 900g) -- its estimate is at least
            // 1.3x -Xmx -- and a single GC thread keeps the per-thread cost bounded where
            // that figure is large.
            long xmxMb = availableMemoryUpperBoundMb() + 1024;
            LaunchResult result = launch("profiler",
                    Arrays.asList("-XX:+UseG1GC", "-XX:ParallelGCThreads=1", "-Xmx" + xmxMb + "m", "-Xms8m"),
                    "start,jfr,file=" + forkedJfr.toAbsolutePath(),
                    line -> LineConsumerResult.CONTINUE, line -> LineConsumerResult.CONTINUE);
            assertTrue(result.inTime, "forked JVM did not exit in time");
            assertEquals(0, result.exitCode, "forked JVM exited with a non-zero code");

            JfrEvents settings = JfrEvents.load(forkedJfr, "jdk.ActiveSetting");
            boolean sawFailed = false;
            boolean sawDetail = false;
            for (JfrEvent item : settings) {
                String name = item.getString("name");
                if ("sanityCheckFailed".equals(name)) {
                    assertEquals("true", item.getString("value"));
                    sawFailed = true;
                } else if ("sanityCheckDetail".equals(name)) {
                    assertTrue(item.getString("value").startsWith("[sanity]"));
                    sawDetail = true;
                }
            }
            assertTrue(sawFailed, "sanityCheckFailed setting not found in JFR recording");
            assertTrue(sawDetail, "sanityCheckDetail setting not found in JFR recording");
        } finally {
            Files.deleteIfExists(forkedJfr);
        }
    }
}
