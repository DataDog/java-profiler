/* Copyright 2026, Datadog, Inc. */
package com.datadoghq.profiler.wallclock;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import com.datadoghq.profiler.NativeBuildConfig;
import java.io.DataOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.function.Supplier;

/** Reads bounded native receipts without using the JFR writer or clearing diagnostic history. */
final class TaskBlockRecorderTestSupport {
  private TaskBlockRecorderTestSupport() {}

  /** Builds without counters report zero, so no rejection credit is available there. */
  static long recordFailures(Map<String, Long> counters) {
    return counters.getOrDefault("task_block_record_failed", 0L);
  }

  static final int MAX_RECORD_ATTEMPTS = 5;

  /** One eligible interval; returns endTaskBlock's result. */
  @FunctionalInterface
  interface Attempt {
    boolean recorded() throws Exception;
  }

  /** How task_block_record_failed deltas may credit rejected attempts. */
  enum Credit {
    /** Only the attempt's JNI endTaskBlock records TaskBlocks: one increment per rejection. */
    EXACT,
    /** JVM-wide park/monitor TaskBlocks also count failures: the delta is only a lower bound. */
    LOWER_BOUND
  }

  /** Exact-credit retry for tests where only the JNI endTaskBlock path records. */
  static void recordWithinAttempts(Supplier<Map<String, Long>> counters, Attempt attempt)
      throws Exception {
    recordWithinAttempts(counters, Credit.EXACT, "eligible interval", attempt);
  }

  /**
   * Repeats an eligible interval until one is recorded, within MAX_RECORD_ATTEMPTS. Every rejected
   * attempt must be covered by a task_block_record_failed increment under the given credit mode.
   */
  static void recordWithinAttempts(
      Supplier<Map<String, Long>> counters, Credit credit, String description, Attempt attempt)
      throws Exception {
    long before = recordFailures(counters.get());
    int rejected = 0;
    while (!attempt.recorded()) {
      rejected++;
      long failures = recordFailures(counters.get()) - before;
      assertTrue(
          credit == Credit.EXACT ? failures == rejected : failures >= rejected,
          description
              + ": endTaskBlock rejection not accounted as task_block_record_failed: rejected="
              + rejected
              + ", record_failed="
              + failures);
      assertTrue(
          rejected < MAX_RECORD_ATTEMPTS,
          description + ": no recorded interval in bounded attempts");
    }
    if (credit == Credit.EXACT) {
      assertEquals(
          rejected,
          recordFailures(counters.get()) - before,
          description + ": recorded interval also counted a recorder failure");
    }
  }

  static native long cursor0();

  static native long[] snapshot0(long cursor);

  static native String[] stageNames0();

  static final class Snapshot {
    static final int HEADER = 13;
    static final int WIDTH = 23;
    final long[] words;
    final String[] stages;
    final int recordsOffset;

    Snapshot(long[] raw, String[] names) {
      words = Objects.requireNonNull(raw, "Missing DEBUG TaskBlock snapshot").clone();
      stages = Objects.requireNonNull(names, "Missing TaskBlock stage names").clone();
      if (words.length < HEADER
          || words[0] != 1
          || words[1] != WIDTH
          || words[2] != 4096
          || words[3] < 0
          || words[4] < 1
          || words[5] < words[3]
          || words[6] < 0
          || words[7] < 0
          || words[8] < 0
          || words[8] > 1
          || words[9] <= 0
          || words[10] < 0
          || words[11] != stages.length
          || words[12] <= 0) {
        throw new IllegalArgumentException("Malformed TaskBlock snapshot header");
      }
      for (String stage : stages) {
        if (stage == null || stage.isEmpty())
          throw new IllegalArgumentException("Missing stage name");
      }
      recordsOffset = HEADER + stages.length;
      long first = Math.max(words[3] + 1, words[4]);
      long count = words[5] - first + 1;
      if (count < 0 || count > words[2] || recordsOffset + count * WIDTH != words.length) {
        throw new IllegalArgumentException("Malformed TaskBlock snapshot width");
      }
      for (int offset = recordsOffset; offset < words.length; offset += WIDTH) {
        long ticket = words[offset];
        long stage = words[offset + 3];
        if (ticket != 0
            && (ticket != first + (offset - recordsOffset) / WIDTH
                || stage < 0
                || stage >= stages.length)) {
          throw new IllegalArgumentException("Malformed TaskBlock receipt");
        }
      }
    }

    boolean hasGaps() {
      if (words[3] + 1 < words[4] || words[8] != 0) return true;
      for (int offset = recordsOffset; offset < words.length; offset += WIDTH) {
        if (words[offset] == 0) return true;
      }
      return false;
    }

    List<long[]> records(String stage) {
      if (!Arrays.asList(stages).contains(stage))
        throw new IllegalArgumentException("Unknown stage");
      List<long[]> result = new ArrayList<>();
      for (int offset = recordsOffset; offset < words.length; offset += WIDTH) {
        if (words[offset] != 0 && stage.equals(stages[(int) words[offset + 3]])) {
          result.add(Arrays.copyOfRange(words, offset, offset + WIDTH));
        }
      }
      return result;
    }
  }

  /** Keeps each bounded snapshot; callers persist in finally even when event assertions fail. */
  static final class Evidence implements AutoCloseable {
    final List<Snapshot> snapshots = new ArrayList<>();
    final String candidate = System.getenv("DDPROF_TELEMETRY_CANDIDATE");
    final String profilerVersion;
    long cursor;

    Evidence(String profilerVersion) {
      this.profilerVersion = profilerVersion;
      cursor = cursor0();
      if (cursor < 0) throw new IllegalStateException("TaskBlock diagnostics require DEBUG");
      capture();
    }

    void capture() {
      Snapshot snapshot = new Snapshot(snapshot0(cursor), stageNames0());
      snapshots.add(snapshot);
      cursor = snapshot.words[5];
    }

    boolean isComplete() {
      Snapshot first = snapshots.get(0);
      Snapshot last = snapshots.get(snapshots.size() - 1);
      if (first.words[6] != last.words[6] || first.words[7] != last.words[7]) return false;
      for (Snapshot snapshot : snapshots) if (snapshot.hasGaps()) return false;
      return true;
    }

    Path persist(Path path) throws IOException {
      Files.createDirectories(path.toAbsolutePath().getParent());
      try (DataOutputStream output = new DataOutputStream(Files.newOutputStream(path))) {
        output.writeUTF("TaskBlockDiagnostics-v1");
        output.writeUTF(candidate == null ? "candidate-unavailable" : candidate);
        output.writeUTF(profilerVersion);
        output.writeUTF(
            System.getProperty("java.vm.name") + " " + System.getProperty("java.runtime.version"));
        output.writeUTF(String.valueOf(NativeBuildConfig.name()));
        output.writeLong(System.currentTimeMillis());
        output.writeLong(System.nanoTime());
        output.writeInt(snapshots.size());
        for (Snapshot snapshot : snapshots) {
          output.writeInt(snapshot.stages.length);
          for (String stage : snapshot.stages) output.writeUTF(stage);
          output.writeInt(snapshot.words.length);
          for (long word : snapshot.words) output.writeLong(word);
        }
      }
      System.out.println("TaskBlock diagnostic evidence: " + path.toAbsolutePath());
      return path;
    }

    @Override
    public void close() throws IOException {
      finish("recorder-");
    }

    void finish(String prefix) throws IOException {
      try {
        capture();
      } finally {
        Path directory =
            Paths.get(
                System.getProperty(
                    "ddprof_test.telemetry.directory", "build/task-block-diagnostics"));
        Files.createDirectories(directory);
        persist(Files.createTempFile(directory, prefix, ".bin"));
      }
    }
  }
}
