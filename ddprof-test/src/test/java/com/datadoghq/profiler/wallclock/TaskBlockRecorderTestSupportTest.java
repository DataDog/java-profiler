/* Copyright 2026, Datadog, Inc. */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.*;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.NativeBuildConfig;
import com.datadoghq.profiler.ProfilerOwnedBlockHooks;
import java.io.DataInputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import org.junit.jupiter.api.Assumptions;
import org.junit.jupiter.api.Test;

/** Covers the DEBUG snapshot protocol, lifecycle retention and assertion-failure persistence. */
class TaskBlockRecorderTestSupportTest extends AbstractProfilerTest {
  @Test
  void durationRefusalRetainsTokenAndOriginAfterStop() throws Exception {
    Assumptions.assumeTrue(NativeBuildConfig.isDebugInstrumented());
    // A reused JUnit thread can retain context-window membership across recordings.
    profiler.removeThread();
    try (TaskBlockRecorderTestSupport.Evidence evidence =
        new TaskBlockRecorderTestSupport.Evidence(profiler.getVersion())) {
      long token = profiler.beginTaskBlock();
      assertNotEquals(0, token);
      assertFalse(ProfilerOwnedBlockHooks.endTaskBlockAtTicks(token, 100, 101, 0x1266, 0));
      evidence.capture();
      TaskBlockRecorderTestSupport.Snapshot snapshot = evidence.snapshots.get(1);
      assertFalse(snapshot.hasGaps());
      assertTrue(evidence.isComplete());
      List<long[]> refusals = snapshot.records("REJECT_DURATION_BELOW_MINIMUM");
      assertEquals(1, refusals.size());
      long[] refusal = refusals.get(0);
      assertTrue(refusal[1] > 0, "observation ticks");
      assertTrue(refusal[2] > 0, "actor TID");
      assertEquals(refusal[2], refusal[4], "subject TID");
      assertTrue(refusal[5] > 0, "native lifecycle generation");
      assertEquals(token, refusal[6]);
      assertTrue(refusal[7] > 0, "origin epoch");
      assertEquals(refusal[7], refusal[8], "current epoch");
      assertEquals(refusal[7], refusal[9], "slot epoch");
      assertEquals(100, refusal[10]);
      assertEquals(101, refusal[11]);
      assertEquals(0x1266, refusal[12]);
      assertEquals(1, snapshot.records("EXIT_MATCHED_AND_CLEARED").size());
      assertTrue(snapshot.records("BUFFER_ACCEPTED").isEmpty());
      stopProfiler();
      TaskBlockRecorderTestSupport.Snapshot afterStop =
          new TaskBlockRecorderTestSupport.Snapshot(
              TaskBlockRecorderTestSupport.snapshot0(snapshot.words[3]), snapshot.stages);
      assertEquals(token, afterStop.records("REJECT_DURATION_BELOW_MINIMUM").get(0)[6]);
    }
  }

  @Test
  void invalidCursorsFailAndReleaseIsExplicitlyUnavailable() {
    if (!NativeBuildConfig.isDebugInstrumented()) {
      assertEquals(-1, TaskBlockRecorderTestSupport.cursor0());
      assertNull(TaskBlockRecorderTestSupport.snapshot0(0));
      assertNull(TaskBlockRecorderTestSupport.stageNames0());
      return;
    }
    assertThrows(IllegalArgumentException.class, () -> TaskBlockRecorderTestSupport.snapshot0(-1));
    assertThrows(
        IllegalArgumentException.class,
        () -> TaskBlockRecorderTestSupport.snapshot0(Long.MAX_VALUE));
  }

  @Test
  void decoderRejectsMalformedHeadersWidthsAndReceipts() {
    assertThrows(
        NullPointerException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(null, new String[0]));
    assertThrows(
        IllegalArgumentException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(new long[0], new String[0]));
    long[] header = {1, 23, 4096, 0, 1, 0, 0, 0, 0, 1000000000, 1, 1, 12345, 0};
    assertFalse(new TaskBlockRecorderTestSupport.Snapshot(header, new String[] {"TEST"}).hasGaps());
    for (int field : new int[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}) {
      long[] malformed = header.clone();
      malformed[field] = field == 0 || field == 1 || field == 2 || field == 11 ? 999 : -1;
      assertThrows(
          IllegalArgumentException.class,
          () -> new TaskBlockRecorderTestSupport.Snapshot(malformed, new String[] {"TEST"}),
          "field " + field);
    }
    assertThrows(
        IllegalArgumentException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(header, new String[] {null}));
    long[] receipt = new long[37];
    System.arraycopy(header, 0, receipt, 0, header.length);
    receipt[5] = 1;
    assertTrue(new TaskBlockRecorderTestSupport.Snapshot(receipt, new String[] {"TEST"}).hasGaps());
    receipt[14] = 2;
    assertThrows(
        IllegalArgumentException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(receipt, new String[] {"TEST"}));
    receipt[14] = 1;
    receipt[17] = 1;
    assertThrows(
        IllegalArgumentException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(receipt, new String[] {"TEST"}));
    assertThrows(
        IllegalArgumentException.class,
        () -> new TaskBlockRecorderTestSupport.Snapshot(new long[14], new String[] {"TEST"}));
  }

  @Test
  void assertionFailureStillPersistsReadableRawEvidence() throws Exception {
    Assumptions.assumeTrue(NativeBuildConfig.isDebugInstrumented());
    Path evidenceFile = Files.createTempFile("taskblock-finally-", ".bin");
    TaskBlockRecorderTestSupport.Evidence evidence =
        new TaskBlockRecorderTestSupport.Evidence(profiler.getVersion());
    try {
      assertThrows(
          AssertionError.class,
          () -> {
            try {
              throw new AssertionError("event assertion failed");
            } finally {
              evidence.capture();
              evidence.persist(evidenceFile);
            }
          });
      try (DataInputStream input = new DataInputStream(Files.newInputStream(evidenceFile))) {
        assertEquals("TaskBlockDiagnostics-v1", input.readUTF());
        for (int field = 0; field < 4; ++field) assertNotNull(input.readUTF());
        assertTrue(input.readLong() > 0);
        input.readLong();
        assertEquals(2, input.readInt());
        for (int snapshot = 0; snapshot < 2; ++snapshot) {
          String[] stages = new String[input.readInt()];
          for (int stage = 0; stage < stages.length; ++stage) stages[stage] = input.readUTF();
          long[] words = new long[input.readInt()];
          for (int word = 0; word < words.length; ++word) words[word] = input.readLong();
          assertNotNull(new TaskBlockRecorderTestSupport.Snapshot(words, stages));
        }
        assertEquals(-1, input.read());
      }
    } finally {
      Files.deleteIfExists(evidenceFile);
    }
  }

  @Override
  protected boolean isPlatformSupported() {
    return TaskBlockAssertions.isSupported();
  }

  @Override
  protected String getProfilerCommand() {
    return "wall=1ms,filter=,wallprecheck=true";
  }
}
