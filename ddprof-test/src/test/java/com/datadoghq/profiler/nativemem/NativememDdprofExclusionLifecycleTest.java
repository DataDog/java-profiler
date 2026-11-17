/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.NativeBuildConfig;
import com.datadoghq.profiler.Platform;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

/**
 * Child-JVM lifecycle tests for cached native-memory admission. They cover a clean fresh/cached
 * restart, rejection after the stand-in rewrites the own GOT, and admission again after the
 * stand-in restores the original slots. Each scenario runs in a separate process because resolver
 * state and saved allocation targets persist for that process lifetime.
 */
public class NativememDdprofExclusionLifecycleTest extends AbstractProcessProfilerTest {
  private static final String DDPROF_LITERAL =
      "Native-memory profiling was not started: an allocation target points to a ddprof hook. "
          + "Enable only one native-memory allocation profiler for this process.";

  @BeforeAll
  static void requireLinux() {
    assumeTrue(
        Platform.isLinux() && !Platform.isJ9() && !Platform.isZing(),
        "native-memory admission lifecycle scenarios require glibc Linux");
  }

  private Path newRecording() throws Exception {
    Path recording = Files.createTempFile("nativemem-lifecycle", ".jfr");
    recording.toFile().deleteOnExit();
    return recording;
  }

  private List<String> runScenario(String steps) throws Exception {
    List<String> lines = Collections.synchronizedList(new ArrayList<>());
    List<String> jvmArgs =
        Collections.singletonList("-Djava.library.path=" + System.getProperty("java.library.path"));
    launch(
        "nativemem-exclusion",
        jvmArgs,
        steps,
        line -> {
          lines.add(line);
          return AbstractProcessProfilerTest.LineConsumerResult.CONTINUE;
        },
        null);
    return lines;
  }

  private static List<String> startLines(List<String> lines) {
    List<String> starts = new ArrayList<>();
    for (String line : lines) {
      if (line.startsWith("[start]")) {
        starts.add(line);
      }
    }
    return starts;
  }

  private static void assertNativeAllocationEvents(Path recording) throws Exception {
    JfrEvents events = JfrEvents.load(recording, "datadog.NativeMemoryAllocation");
    assertTrue(events.iterator().hasNext(), "nativemem=0 must emit allocation events");
    JfrEvent event = events.iterator().next();
    assertTrue(event.has("size"), "native allocation events must carry size");
    assertTrue(event.has("address"), "native allocation events must carry address");
    assertTrue(event.has("weight"), "native allocation events must carry weight");
    Long size = event.getLong("size");
    Long address = event.getLong("address");
    Double weight = event.getDouble("weight");
    assertNotNull(size, "native allocation size must be non-null");
    assertNotNull(address, "native allocation address must be non-null");
    assertNotNull(weight, "native allocation weight must be non-null");
    assertTrue(size > 0, "native allocation size must be positive");
    assertNotEquals(0L, address, "native allocation address must not be zero");
    assertEquals(1.0, weight, 1e-6, "nativemem=0 samples every allocation");
  }

  private static void assertMarkersWereNotCalled(List<String> lines) {
    for (String line : lines) {
      if (line.startsWith("[markers]")) {
        assertEquals(
            "[markers] start=0 stop=0",
            line,
            "admission and forwarding must not call ddprof marker functions");
        return;
      }
    }
    throw new AssertionError("scenario did not report the marker counters");
  }

  // A clean first start and a cached restart both admit and emit allocation
  // events. Loading the marker-bearing test library alone is not a conflict
  // because no allocation target points into it (AC-3 control, AC-8).
  @Test
  void cleanFreshAndCachedRestartsContinueSampling() throws Exception {
    Path first = newRecording();
    Path second = newRecording();
    List<String> lines =
        runScenario(
            "LOAD;LOADPROFILER;"
                + "START:start,nativemem=0,file="
                + first
                + ";ALLOC:1000;STOP;"
                + "START:start,nativemem=0,file="
                + second
                + ";ALLOC:1000;STOP;MARKERS");

    assertEquals(Arrays.asList("[start] ok", "[start] ok"), startLines(lines));
    if (NativeBuildConfig.isDebugInstrumented()) {
      List<String> admissionLines = new ArrayList<>();
      for (String line : lines) {
        if (line.contains("MallocAdmission:")) {
          admissionLines.add(line);
        }
      }
      assertEquals(2, admissionLines.size(), "each native-memory start must run admission");
      assertTrue(
          admissionLines.get(1).contains("MallocAdmission: outcome=NOT_RECOGNIZED"),
          "the cached second start must report its admitted outcome");
    }
    assertNativeAllocationEvents(first);
    assertNativeAllocationEvents(second);
    assertMarkersWereNotCalled(lines);
  }

  // After one admitted session, the stand-in places its marker-bearing
  // forwarding hook in the profiler's own malloc slot. The cached start must
  // reject. Restoring the original slot values must allow a later start and
  // sampling again; the stand-in's saved-slot snapshot must remain unchanged
  // across the rejected attempt (AC-7, AC-8, AC-13).
  @Test
  void cachedConflictRejectsThenRestorationAllowsSampling() throws Exception {
    Path first = newRecording();
    Path rejected = newRecording();
    Path afterRestore = newRecording();
    List<String> lines =
        runScenario(
            "LOAD;LOADPROFILER;"
                + "START:start,nativemem=0,file="
                + first
                + ";ALLOC:1000;STOP;"
                + "INSTALL;SAVEDMALLOC;START:start,nativemem=0,file="
                + rejected
                + ";SAVEDMALLOC;"
                + "RESTORE;START:start,nativemem=0,file="
                + afterRestore
                + ";ALLOC:1000;STOP;MARKERS");

    assertEquals(
        Arrays.asList("[start] ok", "[start] error=" + DDPROF_LITERAL, "[start] ok"),
        startLines(lines));
    assertNativeAllocationEvents(first);
    assertNativeAllocationEvents(afterRestore);

    List<String> savedSnapshots = new ArrayList<>();
    for (String line : lines) {
      if (line.startsWith("[standin-saved]")) {
        savedSnapshots.add(line);
      }
    }
    assertEquals(
        2, savedSnapshots.size(), "stand-in must expose the before/after saved-slot snapshot");
    assertNotEquals(
        "[standin-saved] malloc=0",
        savedSnapshots.get(0),
        "stand-in must capture the allocator target before rewriting the GOT");
    assertEquals(
        savedSnapshots.get(0),
        savedSnapshots.get(1),
        "the rejected admission attempt must not alter the stand-in's saved slot value");
    assertMarkersWereNotCalled(lines);
  }
}
