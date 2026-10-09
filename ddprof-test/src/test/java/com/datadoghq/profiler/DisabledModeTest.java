/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler;


import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

/**
 * Disabled mode: {@code -agentpath:...=enabled=false} must initialize nothing and reject every
 * lifecycle transition, even when the same arguments also ask the agent to start recording.
 */
public class DisabledModeTest extends AbstractProcessProfilerTest {

    @Test
    void agentEnabledFalseInitializesNothing(@TempDir Path tmp) throws Exception {
        assumeFalse(Platform.isJ9() || Platform.isZing());

        Path agentLib = LibraryLoader.resolveLibraryPath(System.getProperty("java.io.tmpdir"));
        Path jfr = tmp.resolve("disabled.jfr");
        String agentArgs = "enabled=false,start,cpu=10ms,wall=10ms,file=" + jfr;

        AtomicReference<String> disabledLine = new AtomicReference<>();
        AtomicBoolean gotInstance = new AtomicBoolean(false);
        AtomicBoolean bridgeInitialized = new AtomicBoolean(false);

        LaunchResult result = launch("profiler-disabled",
            Collections.singletonList("-agentpath:" + agentLib.toAbsolutePath() + "=" + agentArgs),
            agentLib.toAbsolutePath().toString(),
            l -> {
                if (l.startsWith("[disabled] ")) {
                    disabledLine.set(l);
                }
                gotInstance.compareAndSet(false, l.contains("[disabled-no-exception]"));
                // TEST_LOG line, emitted by debug builds only.
                bridgeInitialized.compareAndSet(false, l.contains("[TEST::INFO] VM::initProfilerBridge"));
                return LineConsumerResult.CONTINUE;
            },
            null);

        assertTrue(result.inTime);
        assertEquals(0, result.exitCode);
        assertFalse(gotInstance.get(), "JavaProfiler.getInstance() succeeded in disabled mode");
        assertEquals("[disabled] Profiler is disabled", disabledLine.get());
        assertFalse(bridgeInitialized.get(), "VM::initProfilerBridge ran in disabled mode");
        assertFalse(Files.exists(jfr), "a recording was written in disabled mode");
    }
}
