/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.NativeBuildConfig;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

/**
 * Child-JVM tests for the native-memory startup admission check: admission
 * runs only for native-memory requests, the conflict rejection returns the
 * exact design literal, a mixed request keeps the other engine usable, and
 * inspection never calls a marker. Every scenario runs in a fresh child JVM
 * because a captured saved target is permanent for a process. The ddprof
 * image is the {@link DdprofStandin} test double inside libddproftest.
 */
public class NativememDdprofExclusionTest extends AbstractProcessProfilerTest {
    private static final String DDPROF_LITERAL =
            "Native-memory profiling was not started: an allocation target points to a ddprof hook. "
                    + "Enable only one native-memory allocation profiler for this process.";
    private static final String NO_ENGINE_LITERAL =
            "Neither CPU, wallclock nor allocation profiling could be started";

    @BeforeAll
    static void requireSupportedPlatform() {
        // Linux-only child-JVM scenarios: the stand-in's GOT rewrite is
        // Linux-only. Other hosts skip with this reason; the shared
        // mallocAdmission gtests supply the non-Linux admission coverage.
        assumeTrue(Platform.isLinux() && !Platform.isJ9() && !Platform.isZing(),
                "native-memory admission scenarios require glibc Linux");
    }

    private Path newRecording() throws Exception {
        Path jfr = Files.createTempFile("nativemem-exclusion", ".jfr");
        jfr.toFile().deleteOnExit();
        return jfr;
    }

    private List<String> runScenario(String steps) throws Exception {
        List<String> lines = Collections.synchronizedList(new ArrayList<>());
        // The child JVM needs the JNI test helpers' directory: the parent's
        // java.library.path is set by the Gradle test task for this project.
        List<String> jvmArgs = Collections.singletonList(
                "-Djava.library.path=" + System.getProperty("java.library.path"));
        launch("nativemem-exclusion", jvmArgs, steps, l -> {
            lines.add(l);
            return AbstractProcessProfilerTest.LineConsumerResult.CONTINUE;
        }, null);
        return lines;
    }

    private static String findLine(List<String> lines, String prefix) {
        for (String line : lines) {
            if (line.startsWith(prefix)) {
                return line;
            }
        }
        return null;
    }

    private static void assertMarkersNeverCalled(List<String> lines) {
        String markers = findLine(lines, "[markers] start=");
        assertNotNull(markers, "scenario must report the marker counters");
        assertEquals("[markers] start=0 stop=0", markers,
                "the admission check must never execute a marker function");
    }

    // Without a native-memory request the admission check does not run: no
    // MallocAdmission TEST_LOG line (AC-1, debug configuration).
    @Test
    void cpuOnlyStartDoesNotRunAdmission() throws Exception {
        assumeTrue(NativeBuildConfig.isDebug());
        List<String> lines = runScenario("LOAD;START:start,cpu=10ms,file=" + newRecording() + ";MARKERS");
        assertEquals("[start] ok", findLine(lines, "[start]"), "cpu-only start must be admitted");
        assertFalse(lines.stream().anyMatch(l -> l.contains("MallocAdmission:")),
                "admission must not run for a cpu-only start");
        assertMarkersNeverCalled(lines);
    }

    // A native-memory start runs the admission check: the TEST_LOG line is
    // present and reports an admitted outcome (AC-1, debug configuration).
    @Test
    void nativememStartRunsAdmission() throws Exception {
        assumeTrue(NativeBuildConfig.isDebug());
        List<String> lines = runScenario("LOAD;START:start,nativemem=0,file=" + newRecording() + ";ALLOC:100;STOP;MARKERS");
        assertEquals("[start] ok", findLine(lines, "[start]"));
        assertTrue(lines.stream().anyMatch(l -> l.contains("MallocAdmission:")),
                "admission must run for a nativemem start");
        assertTrue(lines.stream().anyMatch(l -> l.contains("MallocAdmission: outcome=NOT_RECOGNIZED")),
                "an admitted start reports NOT_RECOGNIZED");
        assertMarkersNeverCalled(lines);
    }

    // A native-memory-only conflict returns the exact DDPROF literal as the
    // IllegalStateException message (AC-9), and the stand-in markers are
    // never called by the inspection.
    @Test
    void nativememConflictReturnsExactDdprofLiteral() throws Exception {
        List<String> lines = runScenario("LOAD;LOADPROFILER;INSTALL;START:start,nativemem=0,file=" + newRecording() + ";MARKERS");
        String start = findLine(lines, "[start]");
        assertNotNull(start, "scenario must report the start outcome");
        assertEquals("[start] error=" + DDPROF_LITERAL, start);
        assertMarkersNeverCalled(lines);
    }

    // A mixed request keeps the other engine usable with its events and zero
    // native-memory events from the rejected session (AC-9). Event fields are
    // asserted non-null before any loop over them.
    @Test
    void mixedRequestKeepsCpuEngineUsable() throws Exception {
        Path jfr = Files.createTempFile("nativemem-mixed", ".jfr");
        jfr.toFile().deleteOnExit();
        List<String> lines = runScenario(
                "LOAD;LOADPROFILER;INSTALL;START:start,cpu=10ms,nativemem=0,file=" + jfr
                        + ";CPUWORK;STOP;MARKERS");
        String start = findLine(lines, "[start]");
        assertNotNull(start, "scenario must report the start outcome");
        assertEquals("[start] ok", start,
                "a CPU engine that starts successfully makes the mixed request successful");

        JfrEvents events = JfrEvents.load(jfr, "datadog.ExecutionSample");
        assertTrue(events.iterator().hasNext(), "the CPU engine must emit samples");
        JfrEvent sample = events.iterator().next();
        assertTrue(sample.has("startTime"), "CPU samples must carry startTime");
        assertNotNull(sample.getLong("startTime"), "CPU sample startTime must be non-null");

        JfrEvents nativeEvents = JfrEvents.load(jfr, "datadog.NativeMemoryAllocation");
        assertFalse(nativeEvents.iterator().hasNext(),
                "a rejected native-memory session must produce no native-memory events");
        assertMarkersNeverCalled(lines);
    }

    // A request without any startable engine returns the no-engine branch
    // message (AC-9, ASM-7: event=wall reaches the no-engine branch).
    @Test
    void noEngineBranchReturnsExactLiteral() throws Exception {
        List<String> lines = runScenario("LOAD;LOADPROFILER;INSTALL;START:start,event=wall,nativemem=0,file="
                + newRecording() + ";MARKERS");
        String start = findLine(lines, "[start]");
        assertNotNull(start, "scenario must report the start outcome");
        assertEquals("[start] error=" + NO_ENGINE_LITERAL, start);
        assertMarkersNeverCalled(lines);
    }
}
