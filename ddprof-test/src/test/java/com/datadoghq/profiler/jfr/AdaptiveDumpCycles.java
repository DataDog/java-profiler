// Copyright 2026, Datadog, Inc.

package com.datadoghq.profiler.jfr;

import java.nio.file.Files;
import java.nio.file.Path;

/**
 * The adaptive dump-verify cycle of {@link JfrDumpTest}: workload batches start at {@link
 * #INITIAL_BATCH} and halve after a cycle that verified without growth; an under-sampled dump
 * retries with a doubled batch. When the batch cap is exhausted the asserting verifier is invoked
 * and must throw — if it returns, the cycle fails with a bounded error instead of looping, so a
 * persistently broken sampler or an unreadable recording always surfaces as a test failure, never
 * as a hang.
 */
public final class AdaptiveDumpCycles {

  /** Workload iterations for the first cycle: the historical fixed density. */
  public static final int INITIAL_BATCH = 50;

  /** Growth bound for under-sampled batches, so a broken sampler fails instead of looping. */
  public static final int MAX_BATCH = 400;

  /** Runs the declared workload for one batch; the batch size is the sampling density. */
  public interface Workload {
    void run(int iterations) throws Exception;
  }

  /** Dumps the live profiler state into {@code recording}. */
  public interface Dumper {
    void dump(Path recording) throws Exception;
  }

  /** Non-failing oracle: {@code true} iff the recording satisfies the declared contract. */
  public interface Probe {
    boolean verified(Path recording) throws Exception;
  }

  /** Asserting oracle: must throw when the recording does not satisfy the contract. */
  public interface Assertor {
    void assertVerified(Path recording) throws Exception;
  }

  private AdaptiveDumpCycles() {}

  public static void run(
      int dumpCnt, Workload workload, Dumper dumper, Probe probe, Assertor assertor)
      throws Exception {
    int batch = INITIAL_BATCH;
    for (int j = 0; j < dumpCnt; j++) {
      Path recording = Files.createTempFile("dump-", ".jfr");
      try {
        boolean grew = false;
        workload.run(batch);
        dumper.dump(recording);
        while (!probe.verified(recording)) {
          if (batch >= MAX_BATCH) {
            // Growth bound exhausted: surface the real failure through the asserting oracle.
            assertor.assertVerified(recording);
            // The asserting oracle returned normally where the probe failed: bounded
            // failure instead of an unbounded retry loop.
            throw new IllegalStateException(
                "verification passed where the probe failed at MAX_BATCH=" + MAX_BATCH);
          }
          Files.deleteIfExists(recording);
          recording = Files.createTempFile("dump-", ".jfr");
          batch = Math.min(batch * 2, MAX_BATCH);
          grew = true;
          workload.run(batch);
          dumper.dump(recording);
        }
        if (!grew) {
          batch = Math.max(1, batch / 2);
        }
      } finally {
        Files.deleteIfExists(recording);
      }
    }
  }
}
