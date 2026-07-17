/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

/**
 * Genuinely separate-process end-to-end coverage for the reference-chains target-selection
 * mechanism, complementing {@link ReferenceChainTrackingTest}'s in-process coverage: runs a real
 * "leaking Java app" (an ever-growing, never-evicted {@code HashMap}-backed cache - see
 * {@link LeakingCacheScenario}) in a genuinely separate child JVM, launched the same way
 * {@code JavaProfilerTest}/{@code JVMAccessTest} already launch child processes, and asserts on
 * that child's own reported result rather than reading a JFR file back out of this test's own
 * process.
 *
 * <p><b>Why a separate process, not another {@code @Test} in {@code ReferenceChainTrackingTest}:</b>
 * an earlier attempt added a second success-path {@code @Test} method there, using this exact
 * same {@code HashMap}-based leak shape, sharing that class's in-process {@code AbstractProfilerTest}
 * dynamic-attach lifecycle. It failed reliably whenever it ran after
 * {@code ReferenceChainTrackingTest}'s own {@code ChainLink} test in the same JVM - not a
 * test-ordering bug, but a genuine, non-obvious property of {@code ReferenceChainTracker}:
 * {@code runPass()} (referenceChains.cpp) performs exactly one root-seeded {@code FollowReferences}
 * walk per search's *entire lifetime* ({@code _search_started}); every later pass only expands
 * frontier entries that walk already discovered ({@code expandFrontier()}) - it never
 * re-examines GC roots or revisits an already-{@code EXPANDED} entry for newly-added children.
 * Since {@code ReferenceChainTracker} is a process-wide singleton, only the *first* test to ever
 * call {@code runPass()} in a given JVM gets a real root-seeded walk; every subsequent test's own,
 * independently-rooted local variables are structurally invisible to the mechanism afterward, no
 * matter how they are built. A genuinely separate child JVM per scenario sidesteps this
 * entirely: each process gets its own fresh {@code ReferenceChainTracker} singleton, and
 * therefore its own guaranteed first-ever root walk.
 */
public class ExternalProcessReferenceChainTest extends AbstractProcessProfilerTest {

  @Test
  void shouldReconstructReferrerChainInSeparateProcess() throws Exception {
    // Mirrors ReferenceChainTrackingTest.isPlatformSupported()'s own guard - FollowReferences/
    // tag-based frontier walking assumes a HotSpot-shaped JVMTI heap implementation.
    assumeFalse(Platform.isJavaVersion(8));
    assumeFalse(Platform.isJ9());
    assumeFalse(Platform.isZing());

    Path scratchDumpPath = Files.createTempFile("referencechains-external-process", ".jfr");
    // LeakingCacheScenario.run() (inside the child) creates this file on its own first dump() -
    // an empty placeholder here would make that first dump() attempt fail confusingly.
    Files.deleteIfExists(scratchDumpPath);
    // "start" requires a "jfr,file=..." clause (found the hard way: JavaProfiler.execute()
    // throws "Flight Recorder output file is not specified" without one) even though this
    // scenario never reads its content - only the explicit dump() calls
    // LeakingCacheScenario.run() makes to scratchDumpPath matter.
    Path continuousJfrPath = Files.createTempFile("referencechains-external-process-continuous", ".jfr");
    try {
      // budget=200000 (up from the in-process test's 4000, found via TEST_LOG instrumentation
      // in referenceChains.cpp/livenessTracker.cpp): a genuinely fresh external JVM's
      // reachable-from-roots graph (full JUnit/JMC/Gradle-worker classpath, bootstrapped from
      // scratch - no benefit from a warm, already-running shared worker JVM) is far larger than
      // the in-process test's, and each pass's own JVMTI walk cost scales with cumulative
      // frontier size, not with this scenario's own allocation rate - budget=4000 stayed
      // truncated=1 at 76000+ admitted edges after 19 real passes and never got close to this
      // scenario's own cache before the test's own timeout. _budget is the pacing controller's
      // hard ceiling (see updatePacing()'s own comment, referenceChains.cpp) - pausetarget alone
      // cannot compensate for a ceiling set too low, only pacing *within* it.
      String startCommand = "start,memory=64:l,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:pausetarget=60000"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      // Packed into one args[1] string - see ExternalLauncher's own "leak-cache" mode comment
      // for why (avoids extending AbstractProcessProfilerTest.launch()'s generic (target,
      // commands) contract with a 3rd argument every other mode would have to ignore).
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      // Propagates this JVM's own ddprof_test.config (set by ProfilerTestPlugin.kt on the
      // ddprof-test Test task itself, not inherited by a ProcessBuilder-launched child on its
      // own) so LeakingCacheScenario can use the same debug-only seeded-representative fallback
      // ReferenceChainTrackingTest already relies on instead of depending purely on real
      // allocation-sampling timing.
      List<String> jvmArgs = Collections.singletonList(
          "-Dddprof_test.config=" + System.getProperty("ddprof_test.config"));

      AtomicReference<String> resultLine = new AtomicReference<>();
      LaunchResult result = launch("leak-cache", jvmArgs, packedCommand,
          Collections.emptyMap(),
          // Generous: a whole separate JVM's startup/classloading cost, on top of the same
          // up-to-25-round population-growth loop plus grace period that takes ~20s in-process
          // (ReferenceChainTrackingTest's own history).
          90,
          line -> {
            if (line.startsWith(LeakingCacheScenario.FOUND_MARKER)
                || line.equals(LeakingCacheScenario.NOT_FOUND_MARKER)
                || line.startsWith(LeakingCacheScenario.NO_HASHMAP_INTERNALS_MARKER)) {
              resultLine.set(line);
            }
            return LineConsumerResult.CONTINUE;
          },
          null);

      assertTrue(result.inTime, "Child process did not exit within the wait timeout");
      assertEquals(0, result.exitCode, "Child process exited with a non-zero code");
      assertNotNull(resultLine.get(),
          "Child process never printed a recognizable result marker on stdout");
      assertEquals(
          LeakingCacheScenario.FOUND_MARKER + LeakingCacheScenario.CachedPayload.class.getName(),
          resultLine.get(),
          "Expected a successfully reconstructed chain whose leaf is CachedPayload, threading "
              + "through java.util.HashMap's own internal storage - got: " + resultLine.get());
    } finally {
      Files.deleteIfExists(scratchDumpPath);
      Files.deleteIfExists(continuousJfrPath);
    }
  }
}
