/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProcessProfilerTest;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicReference;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assumptions.assumeFalse;

/**
 * Separate-process end-to-end coverage for the reference-chains target-selection mechanism,
 * complementing {@link ReferenceChainTrackingTest}'s in-process coverage: runs a "leaking Java
 * app" (see {@link LeakingCacheScenario}) in a child JVM and asserts on the child's reported
 * result.
 *
 * <p><b>Why a separate process, not another {@code @Test} in {@code ReferenceChainTrackingTest}:</b>
 * {@code runPass()} (referenceChains.cpp) performs exactly one root-seeded {@code FollowReferences}
 * walk per search's *entire lifetime* ({@code _search_started}); every later pass only expands
 * frontier entries that walk already discovered ({@code expandFrontier()}) - it never
 * re-examines GC roots or revisits an already-{@code EXPANDED} entry for newly-added children.
 * Since {@code ReferenceChainTracker} is a process-wide singleton, only the *first* test to call
 * {@code runPass()} in a given JVM gets a root-seeded walk; later tests' independently-rooted
 * locals are invisible to it. A child JVM per scenario gets its own fresh singleton and
 * therefore its own first root walk.
 */
@Tag("slow")
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
    // "start" requires a "jfr,file=..." clause (JavaProfiler.execute() throws "Flight Recorder
    // output file is not specified" without one) even though its content is never read.
    Path continuousJfrPath = Files.createTempFile("referencechains-external-process-continuous", ".jfr");
    try {
      // budget=200000 (up from the in-process test's 4000): a cold external JVM's
      // reachable-from-roots graph (full JUnit/JMC/Gradle-worker classpath) is far larger than
      // the in-process test's, and each pass's JVMTI walk cost scales with cumulative frontier
      // size - budget=4000 stayed truncated=1 at 76000+ admitted edges after 19 passes and never
      // reached the cache before timeout. _budget is the pacing controller's hard ceiling (see
      // updatePacing(), referenceChains.cpp) - pausetarget only paces *within* it.
      // memory=64:l:1.0 - the 100% live-sample ratio removes the default 10% subsampling
      // lottery from the tracked-instance pool; total volume stays capped by the 256KiB
      // interval floor, so the tracking table remains tiny.
      String startCommand = "start,memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:pausetarget=60000"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      // Packed into one args[1] string to avoid extending AbstractProcessProfilerTest.launch()'s
      // generic (target, commands) contract with a 3rd argument.
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      // ddprof_test.config is set on the Test task by ProfilerTestPlugin.kt and is not inherited
      // by a ProcessBuilder-launched child; the scenario needs it for its debug-only seeding.
      List<String> jvmArgs = Collections.singletonList(
          "-Dddprof_test.config=" + System.getProperty("ddprof_test.config"));

      AtomicReference<String> resultLine = new AtomicReference<>();
      LaunchResult result = launch("leak-cache", jvmArgs, packedCommand,
          Collections.emptyMap(),
          // Generous: a separate JVM's startup/classloading cost on top of the up-to-25-round
          // growth loop plus grace period (~20s in-process).
          90,
          line -> {
            if (line.startsWith(LeakingCacheScenario.FOUND_MARKER)
                || line.equals(LeakingCacheScenario.NOT_FOUND_MARKER)
                || line.startsWith(LeakingCacheScenario.NO_HASHMAP_INTERNALS_MARKER)
                || line.startsWith(LeakingCacheScenario.CHAIN_NOT_PERSISTED_MARKER)) {
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

  /**
   * Mirrors {@link #shouldReconstructReferrerChainInSeparateProcess()}, but against {@link
   * StaticFieldGrowingCollectionScenario} instead of {@link LeakingCacheScenario}: a {@code
   * static final List<byte[]>} field appended to (never reassigned) after its owning class has
   * already been swept once by {@code admitStaticFieldRoots()} (referenceChains.cpp), as opposed
   * to {@code LeakingCacheScenario}'s local-variable (stack-root) cache. Checks that
   * {@code collectStaleExpandedEntriesForRotation()} re-expands an already-{@code EXPANDED}
   * static-field-rooted collection to pick up elements added after its one-time sweep.
   */
  @Test
  void shouldReconstructReferrerChainForGrowingStaticFieldCollection() throws Exception {
    assumeFalse(Platform.isJavaVersion(8));
    assumeFalse(Platform.isJ9());
    assumeFalse(Platform.isZing());

    Path scratchDumpPath = Files.createTempFile("referencechains-static-field-external-process", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    Path continuousJfrPath = Files.createTempFile("referencechains-static-field-external-process-continuous", ".jfr");
    try {
      // budget/pausetarget/memory: see shouldReconstructReferrerChainInSeparateProcess().
      // painbudget=100 - the safepoint pain budget exists to protect a production
      // app from back-to-back expensive passes, but here it starves the engine
      // on a loaded box: a cold external JVM's search costs seconds of measured
      // safepoint pain, the default cap (5% of wall-clock) clears that debt in
      // ~a minute, and the tail then watches a terminal engine with all tags
      // released and no new search for its whole window (observed as 1900+
      // consecutive blocked-iteration evaluations and the watched chunk reading
      // tag=0 at every poll - the pass/fail line between otherwise identical
      // runs). 100% only lets debt clear as fast as it accrues; cadence stays
      // bounded by each search's own ~seconds of work, so this cannot spin.
      String startCommand = "start,memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=200000:ttl=120000:framecap=2000000:pausetarget=60000"
          + ":painbudget=100"
          + ",jfr,file=" + continuousJfrPath.toAbsolutePath();
      String packedCommand = startCommand + "|||" + scratchDumpPath.toAbsolutePath();

      List<String> jvmArgs = new ArrayList<>();
      jvmArgs.add("-Dddprof_test.config=" + System.getProperty("ddprof_test.config"));
      // --add-opens: the scenario reflects into Collections$SynchronizedList.list and
      // ArrayList.elementData to check its holders' expansion state before creating lateChunk.
      // JDK 8 has no module system (that reflection needs no opening) and rejects the option.
      if (Platform.isJavaVersionAtLeast(9)) {
        jvmArgs.add("--add-opens=java.base/java.util=ALL-UNNAMED");
      }

      AtomicReference<String> resultLine = new AtomicReference<>();
      AtomicReference<String> seamPathLine = new AtomicReference<>();
      LaunchResult result = launch("leak-static-field", jvmArgs, packedCommand,
          Collections.emptyMap(),
          // Wider than shouldReconstructReferrerChainInSeparateProcess()'s 90s: this scenario's
          // own tail wait (StaticFieldGrowingCollectionScenario.run()) needs up to ~60s on top of
          // the round loop for a cold JVM's first full pass to actually complete - see that
          // method's own comment.
          150,
          line -> {
            if (line.startsWith(StaticFieldGrowingCollectionScenario.FOUND_MARKER)
                || line.equals(StaticFieldGrowingCollectionScenario.NOT_FOUND_MARKER)) {
              resultLine.set(line);
            } else if (line.startsWith(StaticFieldGrowingCollectionScenario.SEAM_PATH_MARKER)) {
              seamPathLine.set(line);
            }
            return LineConsumerResult.CONTINUE;
          },
          null);

      assertTrue(result.inTime, "Child process did not exit within the wait timeout");
      assertEquals(0, result.exitCode, "Child process exited with a non-zero code");
      // The scenario's native test seams are compiled into every -DDEBUG build (debug/asan/tsan),
      // so the strong seam path must be taken on exactly those configs.
      String config = System.getProperty("ddprof_test.config");
      boolean expectSeams = config != null && ("debug".equals(config) || config.endsWith("san"));
      assertEquals(StaticFieldGrowingCollectionScenario.SEAM_PATH_MARKER + expectSeams,
          seamPathLine.get(),
          "scenario's seam-path predicate must match the native -DDEBUG build set");
      assertNotNull(resultLine.get(),
          "Child process never printed a recognizable result marker on stdout");
      assertEquals(
          // "byte[]", not "[B": JMC's IMCType renders array types in Java source notation.
          StaticFieldGrowingCollectionScenario.FOUND_MARKER + "byte[]",
          resultLine.get(),
          "Expected a successfully reconstructed chain to a byte[] chunk appended to the static "
              + "field's list after its one-time admitStaticFieldRoots() sweep - got: " + resultLine.get());
    } finally {
      Files.deleteIfExists(scratchDumpPath);
      Files.deleteIfExists(continuousJfrPath);
    }
  }
}
