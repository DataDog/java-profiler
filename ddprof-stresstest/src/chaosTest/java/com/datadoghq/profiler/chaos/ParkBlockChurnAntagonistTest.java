/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.chaos;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.JavaProfiler;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.Duration;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

/** Runs the real chaos workload against native recordings without tracer instrumentation. */
@Timeout(15)
class ParkBlockChurnAntagonistTest {
    private JavaProfiler profiler;
    private Path recording;
    private boolean started;

    @BeforeEach
    void setUp() throws Exception {
        Assumptions.assumeFalse(System.getProperty("java.vm.name", "").contains("J9"),
                "Unfiltered owned-block prechecks are unsupported by the J9 wall engine");
        profiler = JavaProfiler.getInstance();
        recording = Files.createTempFile("chaos-owned-block-", ".jfr");
    }

    @AfterEach
    void tearDown() throws Exception {
        try {
            if (started) profiler.stop();
        } finally {
            if (recording != null) Files.deleteIfExists(recording);
        }
    }

    /** The native hooks and timer must provide coverage without any Java agent attached. */
    @Test
    void explicitHooksExerciseUnfilteredPrechecks() throws Exception {
        ParkBlockChurnAntagonist workload = runWorkload("wall=1ms,filter=,wallprecheck=true");
        workload.verifyPrecheckCoverage();
    }

    /** Calling hooks alone must not make disabled suppression appear to be covered. */
    @ParameterizedTest
    @ValueSource(strings = {
            "wall=1ms,filter=,wallprecheck=false",
            "wall=1ms,filter=0,wallprecheck=false"
    })
    void disabledPrechecksCannotPassCoverage(String command) throws Exception {
        ParkBlockChurnAntagonist workload = runWorkload(command);
        IllegalStateException failure = assertThrows(IllegalStateException.class,
                workload::verifyPrecheckCoverage);
        if (command.contains("filter=0")) {
            // Context-filtered recordings arm the hooks even with prechecks off.
            // Require rejection on the missing timer activity, beyond hook invocation.
            assertTrue(failure.getMessage().contains("wc_precheck_registry_lookups"),
                    failure.getMessage());
        }
    }

    /** Creates repeated real thread lifecycles while sampling, and joins them before returning. */
    private ParkBlockChurnAntagonist runWorkload(String command) throws Exception {
        profiler.execute("start," + command + ",jfr,file=" + recording.toAbsolutePath());
        started = true;
        ParkBlockChurnAntagonist workload = new ParkBlockChurnAntagonist(12, 20);
        workload.start();
        try {
            Thread.sleep(1000);
        } finally {
            workload.stopGracefully(Duration.ofSeconds(5));
        }
        return workload;
    }
}
