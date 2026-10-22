/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JavaProfiler;
import java.lang.invoke.MethodHandle;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Exercises standalone resolution and the packaged harness under an actual patched Java agent. */
class ProfilerAccessTest {
    /** Standalone bindings must use the singleton already loaded by the test classpath. */
    @Test
    void standaloneBindingsUseExistingProfiler() throws Throwable {
        JavaProfiler profiler = JavaProfiler.getInstance();
        Object resolved = ProfilerAccess.getInstance();
        assertSame(profiler, resolved);
        MethodHandle setContextValue = ProfilerAccess.bind(resolved, "setContextValue", int.class, String.class);
        MethodHandle clearContextValue = ProfilerAccess.bind(resolved, "clearContextValue", int.class);
        assertTrue((boolean) setContextValue.invokeExact(0, "chaos-loader-test"));
        clearContextValue.invokeExact(0);
    }

    /** Both CI modes must run the two profiler-aware workloads without an application ddprof jar. */
    @ParameterizedTest
    @ValueSource(booleans = {false, true})
    @Timeout(90)
    void packagedHarnessUsesAgentProfiler(boolean tracing) throws Exception {
        String agent = System.getProperty("chaos.agent.jar");
        Assumptions.assumeTrue(agent != null, "Supply -PchaosAgentJar=<patched-agent.jar> for agent integration");
        Path output = Files.createTempFile("chaos-agent-loader-", ".log");
        Process process = null;
        try {
            process = new ProcessBuilder(
                    Paths.get(System.getProperty("java.home"), "bin", "java").toString(),
                    "-javaagent:" + agent,
                    "-Ddd.trace.enabled=" + tracing,
                    "-Ddd.profiling.enabled=true",
                    "-Ddd.profiling.start-force-first=true",
                    "-Ddd.profiling.ddprof.wall.enabled=true",
                    "-Ddd.telemetry.enabled=false",
                    "-Ddd.remote_config.enabled=false",
                    "-Xmx256m",
                    "-jar", System.getProperty("chaos.harness.jar"),
                    "--duration", "2s", "--antagonists", "reapply-context-value,park-block-churn")
                    .redirectErrorStream(true).redirectOutput(output.toFile()).start();
            assertTrue(process.waitFor(60, TimeUnit.SECONDS), "Patched-agent chaos process did not terminate: " + output);
            String log = new String(Files.readAllBytes(output), StandardCharsets.UTF_8);
            assertEquals(0, process.exitValue(), log);
            assertTrue(log.contains("antagonist started: reapply-context-value"), log);
            assertTrue(log.contains("park-block-churn completed="), log);
            assertTrue(log.contains("completed cleanly"), log);
        } finally {
            if (process != null && process.isAlive()) {
                process.destroyForcibly();
                process.waitFor(5, TimeUnit.SECONDS);
            }
            Files.deleteIfExists(output);
        }
    }
}
