/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.sanity;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collections;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class SanityCheckTest extends AbstractProcessProfilerTest {

    private JavaProfiler profiler;
    private Path jfrDump;

    private String startCommand(String extra) throws IOException {
        Path rootDir = Paths.get("/tmp/recordings");
        Files.createDirectories(rootDir);
        jfrDump = Files.createTempFile(rootDir, "sanity-check-test", ".jfr");
        String base = "start,cpu=10ms,jfr,file=" + jfrDump.toAbsolutePath();
        return extra == null || extra.isEmpty() ? base : base + "," + extra;
    }

    @AfterEach
    void cleanup() throws Exception {
        if (profiler != null) {
            try {
                profiler.stop();
            } catch (IllegalStateException ignored) {
                // already stopped or never started
            }
        }
        if (jfrDump != null) {
            Files.deleteIfExists(jfrDump);
        }
    }

    /**
     * nosanity=true bypasses sanity checks. The profiler must start successfully on any host.
     */
    @Test
    void nosanity_bypasses_checks() throws Exception {
        profiler = JavaProfiler.getInstance();
        assertDoesNotThrow(() -> profiler.execute(startCommand("nosanity")));
    }

    /**
     * The override flag works regardless of value form (bare keyword vs explicit true).
     */
    @Test
    void nosanity_explicit_true_bypasses_checks() throws Exception {
        profiler = JavaProfiler.getInstance();
        assertDoesNotThrow(() -> profiler.execute(startCommand("nosanity=true")));
    }

    /**
     * Sanity checks run at most once across start/stop cycles.
     * After a successful start with checks enabled, subsequent starts do not re-run checks.
     */
    @Test
    void sanity_checks_run_once() throws Exception {
        profiler = JavaProfiler.getInstance();
        // First start with nosanity to guarantee success regardless of host resources.
        profiler.execute(startCommand("nosanity"));
        profiler.stop();
        // Second start (without nosanity) must not fail due to re-running checks — the
        // static guard in the native layer ensures they only fire on the first invocation.
        assertDoesNotThrow(() -> profiler.execute(startCommand(null)));
    }

    /**
     * A forced -Xmx far larger than any real host's RAM makes the memory sanity check fail
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
            LaunchResult result = launch("profiler", Collections.singletonList("-Xmx900g"),
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
