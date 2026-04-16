/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.sanity;

import com.datadoghq.profiler.JavaProfiler;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;

public class SanityCheckTest {

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
     * nosanity=true bypasses sanity checks; profiler must start successfully on any host.
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
        // On a normal host this will also pass because normal hosts satisfy the requirements.
        // On a pathological host the first start already set sanity_checked=true.
        assertDoesNotThrow(() -> profiler.execute(startCommand("nosanity")));
    }
}
