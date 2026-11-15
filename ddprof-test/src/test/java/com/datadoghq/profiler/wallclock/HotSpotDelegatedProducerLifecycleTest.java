/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfEnvironmentVariable;

/** Requires original JVM stacks joined to native samples, not just successful native requests. */
@EnabledIfEnvironmentVariable(named = "DDPROF_EXPECTED_VM", matches = "hotspot")
public class HotSpotDelegatedProducerLifecycleTest extends RealVmProducerTest {
  private Object jvmRecording;
  private Path jvmRecordingPath;
  private boolean jvmDumpAttempted;

  /** Requires real completed JVM stacks and direct TaskBlocks in both retained-worker sessions. */
  @Test
  public void originalJvmStacksAndDirectTaskBlocksSurviveRestart() throws Exception {
    verifyRetainedWorkerAcrossRestart();
  }

  /** CPUTimeSample enables RequestStackTrace's sampler; reflection preserves Java 8 compilation. */
  @Override
  protected void beforeProducerWork() throws Exception {
    super.beforeProducerWork();
    assertNull(jvmRecording, "The previous session's JVM recorder must be closed");
    Class<?> recordingClass = Class.forName("jdk.jfr.Recording");
    jvmRecordingPath =
        Files.createTempFile(Paths.get("/tmp/recordings"), "jvm-original-stacks-", ".jfr");
    jvmRecording = recordingClass.getConstructor().newInstance();
    jvmDumpAttempted = false;
    recordingClass.getMethod("enable", String.class).invoke(jvmRecording, "jdk.AsyncStackTrace");
    Object cpuSettings =
        recordingClass.getMethod("enable", String.class).invoke(jvmRecording, "jdk.CPUTimeSample");
    Class.forName("jdk.jfr.EventSettings")
        .getMethod("with", String.class, String.class)
        .invoke(cpuSettings, "throttle", "500/s");
    recordingClass.getMethod("start").invoke(jvmRecording);
  }

  /**
   * Joins actual JVM events by userData; dropped requests never become completed-stack evidence.
   */
  @Override
  protected void verifyAdditionalRecording(Path nativeRecording, long workerId) throws Exception {
    retainJvmRecording();
    try {
      JfrEvents originals = verifyEvents(jvmRecordingPath, "jdk.AsyncStackTrace", true);
      Map<Long, List<JfrEvent>> byCorrelation = new HashMap<>();
      JfrEvent donor = null;
      int originalCount = 0;
      int failed = 0;
      int biased = 0;
      for (JfrEvent original : originals) {
        originalCount++;
        assertNotNull(original.getBoolean("failed"));
        assertNotNull(original.getBoolean("biased"));
        if (original.getBoolean("failed")) {
          failed++;
          continue;
        }
        if (original.getBoolean("biased")) biased++;
        Long id = original.getLong("userData");
        assertNotNull(id, "A completed JVM stack must preserve its actual request ID");
        assertTrue(id > 0);
        byCorrelation.computeIfAbsent(id, unused -> new ArrayList<>()).add(original);
        String stack = original.getStackTraceString();
        if (stack != null
            && stack.contains("RealVmProducerTest.exerciseUnrelatedWork")
            && DONOR_NAME.equals(original.getThreadName("eventThread"))) {
          donor = original;
        }
      }
      JfrEvents samples =
          nativeRecording == null
              ? verifyEvents(sampleEventType())
              : verifyEvents(nativeRecording, sampleEventType(), true);
      int workerSamples = 0;
      int matched = 0;
      int unmatched = 0;
      int completed = 0;
      JfrEvent controlSample = null;
      JfrEvent controlOriginal = null;
      for (JfrEvent sample : samples) {
        if (!Long.valueOf(workerId).equals(sample.getThreadJavaId("eventThread"))) continue;
        workerSamples++;
        List<JfrEvent> matches = byCorrelation.get(sample.getLong("correlationId"));
        if (matches == null) {
          unmatched++;
          continue;
        }
        assertEquals(
            1, matches.size(), "A request ID must identify at most one completed JVM stack");
        JfrEvent original = matches.get(0);
        assertEquals(
            sample.getThreadJavaId("eventThread"),
            original.getThreadJavaId("eventThread"),
            "A native correlation ID must not select another JVM event owner");
        matched++;
        String stack = original.getStackTraceString();
        if (Boolean.TRUE.equals(original.getBoolean("biased"))
            || stack == null
            || !stack.contains("RealVmProducerTest.exerciseProducer")) continue;
        assertCompletedAssociation(sample, matches, workerId);
        completed++;
        controlSample = sample;
        controlOriginal = original;
      }
      System.out.println(
          "JVM_ORIGINAL_POPULATION recording="
              + jvmRecordingPath
              + " originals="
              + originalCount
              + " failed="
              + failed
              + " biased="
              + biased
              + " workerSamples="
              + workerSamples
              + " matched="
              + matched
              + " unmatched="
              + unmatched
              + " completedUnbiasedWorkload="
              + completed
              + " workerJavaId="
              + workerId);
      assertTrue(completed > 0, "Native requests are not proof of a completed original JVM stack");
      Map<String, Long> counters = profiler.getDebugCounters();
      assertEquals(Long.valueOf(1L), counters.get("jvmti_stacks_init_ok"));
      assertEquals(Long.valueOf(0L), counters.get("jvmti_stacks_failed_other"));
      Long nonJavaDrops = counters.get("jvmti_stacks_dropped_non_java");
      assertNotNull(nonJavaDrops);
      assertTrue(nonJavaDrops > 0, "Native wall targets must be rejected before the JVM extension");
      System.out.println("JVM_ORIGINAL_ADMISSION initialized=1 nonJavaDrops=" + nonJavaDrops);
      assertNotNull(donor, "Missing actual JVM wrong-owner/unrelated-stack negative-control event");
      assertNotNull(controlSample);
      assertNotNull(controlOriginal);
      verifyAssociationNegativeControls(controlSample, controlOriginal, donor, workerId);
    } finally {
      closeJvmRecording();
    }
  }

  /**
   * Every qualifying original must be unique, completed, unbiased and owned by the actual worker.
   */
  private static void assertCompletedAssociation(
      JfrEvent sample, List<JfrEvent> originals, long workerId) {
    assertEquals(1, originals.size(), "Duplicate JVM completion for the same native sample");
    JfrEvent original = originals.get(0);
    assertEquals(sample.getLong("correlationId"), original.getLong("userData"));
    assertEquals(Long.valueOf(workerId), sample.getThreadJavaId("eventThread"));
    assertEquals(Long.valueOf(workerId), original.getThreadJavaId("eventThread"));
    assertEquals(sample.getThreadName("eventThread"), original.getThreadName("eventThread"));
    assertEquals(Boolean.FALSE, original.getBoolean("failed"));
    assertEquals(Boolean.FALSE, original.getBoolean("biased"));
    assertNotNull(original.getStackTraceString());
    assertTrue(
        original.getStackTraceString().contains("RealVmProducerTest.exerciseProducer"),
        "The original JVM stack must resolve the retained worker's actual producer workload");
  }

  /** Rejects actual recorded substitutions without synthesizing JVM stack frames or thread IDs. */
  private static void verifyAssociationNegativeControls(
      JfrEvent sample, JfrEvent original, JfrEvent donor, long workerId) {
    assertNotEquals(original.getLong("userData"), donor.getLong("userData"));
    for (String field : new String[] {"eventThread", "stackTrace", "userData"}) {
      Object saved = original.raw().get(field);
      try {
        original.raw().put(field, donor.raw().get(field));
        assertThrows(
            AssertionError.class,
            () -> assertCompletedAssociation(sample, Arrays.asList(original), workerId),
            "The original-event oracle must reject recorded " + field + " substitution");
      } finally {
        original.raw().put(field, saved);
      }
    }
    assertThrows(
        AssertionError.class,
        () -> assertCompletedAssociation(sample, Arrays.asList(original, original), workerId),
        "The original-event oracle must reject duplicate real JVM completions");
    assertCompletedAssociation(sample, Arrays.asList(original), workerId);
    System.out.println(
        "JVM_ORIGINAL_ORACLE restored=true wrongOwner=rejected unrelatedStack=rejected"
            + " wrongCorrelation=rejected duplicate=rejected");
  }

  /** Stops and dumps the real JVM recorder, including on a failed native-side oracle. */
  private void retainJvmRecording() throws Exception {
    if (jvmDumpAttempted) return;
    jvmDumpAttempted = true;
    Class<?> recordingClass = jvmRecording.getClass();
    String state = recordingClass.getMethod("getState").invoke(jvmRecording).toString();
    if ("RUNNING".equals(state)) recordingClass.getMethod("stop").invoke(jvmRecording);
    recordingClass.getMethod("dump", Path.class).invoke(jvmRecording, jvmRecordingPath);
    System.out.println("JVM_ORIGINAL recording=" + jvmRecordingPath);
  }

  /** Owns the JVM recorder even when assertions fail before the original-event oracle runs. */
  @AfterEach
  public void closeJvmRecording() throws Exception {
    if (jvmRecording == null) return;
    try {
      retainJvmRecording();
    } finally {
      try {
        jvmRecording.getClass().getMethod("close").invoke(jvmRecording);
      } finally {
        jvmRecording = null;
        if (!Boolean.getBoolean("ddprof_test.keep_jfrs")) Files.deleteIfExists(jvmRecordingPath);
      }
    }
  }

  @Override
  protected boolean expectsOpenJ9() {
    return false;
  }

  @Override
  protected boolean delegatedStacks() {
    return true;
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true,jvmtistacks=true";
  }
}
