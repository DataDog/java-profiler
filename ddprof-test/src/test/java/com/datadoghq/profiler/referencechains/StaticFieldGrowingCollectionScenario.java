/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JavaProfiler;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Mimics the real leak shape found in the {@code prof-analyzer-hotdog-jb} pod's leak generator
 * ({@code ProfileAnalyzer}'s {@code LEAK_BUFFER}, profiling-backend repo, branch-local diff): a
 * {@code static final List<byte[]>} field whose *instance* is admitted exactly once by
 * {@code admitStaticFieldRoots()} (referenceChains.cpp) when the owning class first loads, and
 * which is then only ever mutated in place (elements appended) - never reassigned - for the rest
 * of the process's life. This is the "new elements added to an already-discovered collection"
 * shape, as opposed to {@code LeakingCacheScenario}'s local-variable cache (a stack-local GC
 * root, not a static field) - see this scenario's own use to confirm whether
 * {@code collectStaleExpandedEntriesForRotation()}'s rotation mechanism actually re-expands
 * {@link #LEAK_BUFFER} to pick up elements added after its one-time static-field sweep.
 *
 * <p>Same seed-before-start rationale as {@code LeakingCacheScenario}'s own comment: {@link
 * #LEAK_BUFFER} is seeded with a few chunks before the profiler (and therefore {@code
 * ReferenceChainTracker}'s BFS thread) is even started, so the process's one-shot root-seeded
 * walk can never catch it empty.
 */
public final class StaticFieldGrowingCollectionScenario {
  private StaticFieldGrowingCollectionScenario() {}

  /**
   * Mirrors production's {@code ProfileAnalyzer.LEAK_BUFFER}: a static field holding a
   * {@code synchronizedList<byte[]>}, appended to (never reassigned) for the process's whole
   * life.
   */
  static final List<byte[]> LEAK_BUFFER = Collections.synchronizedList(new ArrayList<>());

  // Arbitrary, scenario-chosen klass id - see LeakingCacheScenario.CACHED_PAYLOAD_TEST_KLASS_ID's
  // own comment; distinct from that scenario's id since both may run in the same suite (each in
  // its own separate child JVM/LivenessTracker population table, but kept distinct regardless).
  private static final int LEAK_BUFFER_TEST_KLASS_ID = 987302;

  // See LeakingCacheScenario.SEED_EPOCHS_FOR_HYSTERESIS's own comment for the full derivation:
  // LivenessTracker's hysteresis gate needs this many qualifying epochs before
  // selectLeakCandidates() reports a candidate at all.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  // Clears ObjectSampler's real sampling floor on its own - unlike LeakingCacheScenario's
  // CachedPayload (long fields only, no byte[]), this scenario's leaked object *is* the byte[]
  // itself, so there is no second, competing companion allocation.
  private static final int CHUNK_BYTES = 300_000;

  private static final int SEED_CHUNKS = 10;

  /** Printed to stdout, followed by the matched leaf class's name, on success. */
  public static final String FOUND_MARKER = "[chain-found] ";

  /** Printed to stdout (with no class name suffix) if no match was ever observed. */
  public static final String NOT_FOUND_MARKER = "[chain-not-found]";

  /**
   * Seeds {@link #LEAK_BUFFER}, starts the profiler, then keeps appending new {@code byte[]}
   * chunks to the same list instance - the exact shape implicated in the live hotdog-pod stall -
   * watching specifically for a chain to a chunk appended *after* the static field's one-time
   * sweep, until a {@code datadog.ReferenceChain} event for it appears or {@code totalRounds} is
   * exhausted.
   */
  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath) throws Exception {
    for (int i = 0; i < SEED_CHUNKS; i++) {
      LEAK_BUFFER.add(new byte[CHUNK_BYTES]);
    }
    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    boolean debugBuild = "debug".equals(System.getProperty("ddprof_test.config"));
    int hysteresisEpoch = 0;
    // Declared at method scope: the per-round maintenance seeding below (in
    // its own debugBuild block) reuses this tid.
    int leakTid = 0;
    // Snapshotted BEFORE seeding anything, while the BFS thread's search has not run a single
    // pass yet (referenceChainPassesRunForTest0() reads 0 here) - see the wait loop below for why
    // this exact value, not just "nonzero", is what the wait needs to advance past.
    int initialPasses = debugBuild ? JavaProfiler.referenceChainPassesRunForTest0() : -1;

    if (debugBuild) {
      // Seed enough hysteresis-qualifying epochs to unlock ReferenceChainTracker::hasLeakSignal()/
      // shouldRunPass() - WITHOUT wiring in a representative object yet (setKlassPopulationRepresentativeForTest0
      // is not called here). hasLeakSignal() only asks selectLeakCandidates() for a nonzero count -
      // it never reads/dereferences the representative field - so this step's only job is
      // authorizing the BFS thread's first pass to actually start. Doing this BEFORE waiting on
      // passesRun() advancing below is load-bearing, found the hard way: a pass only ever runs
      // once shouldRunPass() sees a leak signal - waiting on passesRun() before seeding anything is
      // a deadlock, not just a slow path.
      // Per-(klass, tid) qualification seeds (see LeakTagCorrelationScenario's own
      // seeding block for the rationale): the qualifying tid must be the thread that
      // allocates the tracked instances - this thread allocates every LEAK_BUFFER
      // chunk, including the lateChunk this scenario watches.
      leakTid = JavaProfiler.getTid();
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        JavaProfiler.seedKlassPopulationSample0(LEAK_BUFFER_TEST_KLASS_ID, epoch * 10, epoch);
        JavaProfiler.seedTidTrendSample0(LEAK_BUFFER_TEST_KLASS_ID, leakTid, epoch * 3, epoch);
      }
      hysteresisEpoch = SEED_EPOCHS_FOR_HYSTERESIS;
    }

    // Wait for the BFS thread to fully complete its own first pass - not just
    // admitStaticFieldRoots()'s one-time sweep of LEAK_BUFFER's *current* contents (an earlier,
    // narrower version of this wait checked exactly that, via a since-removed
    // hasCompletedStaticFieldSweepForTest0() seam), but the WHOLE pass, static-field sweep and
    // expandFrontier()/collectStaleExpandedEntriesForRotation() alike - strictly before this
    // scenario creates the one chunk whose chain it is actually going to watch for. This is the
    // entire point of this scenario: proving that an element appended to a static field's
    // collection AFTER that field's List is already ReferenceChainTracker-EXPANDED gets discovered
    // via a LATER re-expansion of that stale entry, not via the very first pass that admitted it.
    // Waiting on only the static-field sub-step (found the hard way, by actually instrumenting
    // runPassManualWalk() and reading cacheResolvedChain()'s own timestamp against it) is not
    // enough: admitStaticFieldRoots() and expandFrontier() are two steps of the SAME runPass()
    // call, so Java can observe the former's completion while the latter - which is what actually
    // marks LEAK_BUFFER's List entry EXPANDED - is still in flight, still racing lateChunk's
    // creation exactly the way the sleep-based version this replaced did. Waiting for
    // referenceChainPassesRunForTest0() to advance past its pre-seeding snapshot instead only
    // becomes true once that ENTIRE pass (both steps) has finished. Non-debug builds have no such
    // seam and fall back to a generous sleep - acceptable there because the non-debug path never
    // pins a specific representative anyway (see the debugBuild branch below): it just waits on
    // real, much-slower allocation sampling to notice the growth on its own, so a few extra
    // seconds of margin either way changes nothing about what the eventual match would prove.
    if (debugBuild) {
      boolean passCompleted = false;
      // admitStaticFieldRoots() sweeps every loaded class in one FollowReferences call - a cold
      // external JVM's full JUnit/JMC/Gradle-worker classpath (thousands of classes) can need
      // several retries against pause-time-SLO pacing before one completes without truncating (see
      // that method's own header comment on retry-from-scratch-but-cheap-on-already-admitted) -
      // generous margin for the same reason ExternalProcessReferenceChainTest's own budget/
      // pausetarget are raised this far above the in-process test's defaults.
      for (int i = 0; i < 300 && !passCompleted; i++) {
        passCompleted = JavaProfiler.referenceChainPassesRunForTest0() != initialPasses;
        if (!passCompleted) {
          Thread.sleep(100);
        }
      }
      if (!passCompleted) {
        throw new IllegalStateException(
            "ReferenceChainTracker never completed its first pass within 30s - cannot safely "
                + "create the chunk this scenario is supposed to discover only via a later "
                + "re-expansion of an already-EXPANDED static-field entry");
      }
    } else {
      Thread.sleep(3000);
    }
    // Snapshotted right after the wait above confirms the first pass has fully completed - any
    // later change (advance, or reset-to-lower via a restart) proves a walk that started strictly
    // after lateChunk existed.
    int passesRunBeforeLateChunk = debugBuild ? JavaProfiler.referenceChainPassesRunForTest0() : -1;
    byte[] lateChunk = new byte[CHUNK_BYTES];
    LEAK_BUFFER.add(lateChunk);

    // From here on, seeded incrementally, one epoch per round below, rather than as a single
    // upfront burst - found the hard way: profiler.execute()'s start() resets
    // Profiler::classMap()'s generation synchronously, but LivenessTracker::cleanup_table() only
    // observes that new generation (and updates its own _last_class_map_generation) lazily, on the
    // BFS thread's own first tick. A burst seeded entirely before that first tick lands in
    // _klass_population, then gets wiped wholesale the moment that tick's class-map-generation
    // mismatch fires (cleanup_table()'s own comment, livenessTracker.cpp). Seeding one fresh epoch
    // per round instead is self-healing exactly the way the real leak this scenario mirrors is:
    // LEAK_BUFFER keeps growing every round regardless of any one-time startup housekeeping, so
    // however many rounds a wipe costs, the trend simply resumes accumulating from the next
    // round's seed call. (Waiting for the first pass to fully complete above already makes this
    // particular race very unlikely to matter by this point, but there is no reason to give up the
    // self-healing margin now that it costs nothing.)
    ReferenceChainAssertions.ChainMatch match = null;
    int totalRounds = 25;
    for (int round = 1; round <= totalRounds && match == null; round++) {
      // Continues growing LEAK_BUFFER every round after lateChunk - mirrors the real leak's own
      // continuous growth - but lateChunk itself (created above, strictly after the first sweep)
      // stays the fixed target this scenario watches for throughout.
      LEAK_BUFFER.add(new byte[CHUNK_BYTES]);
      System.gc();

      if (match == null && debugBuild) {
        // Seeding/polling every round unconditionally (not gated on passesRun() having advanced)
        // is load-bearing, found the hard way: gating this on the tracker's OWN progress creates a
        // deadlock - ReferenceChainTracker::hasLeakSignal() (which authorizes both a search's first
        // pass and any later restart once the search reaches a terminal state) reads
        // LivenessTracker::selectLeakCandidates(), which needs a continuously-refreshed population
        // trend to keep reporting this candidate; stopping that refresh mid-search (to wait on the
        // search's own progress) can stall the search itself with no path back, since nothing else
        // keeps re-authorizing it. This scenario's target - a growing static-field collection -
        // legitimately produces a continuous real signal in production; seeding continuously here
        // is what actually mirrors that, not an artifact to gate away.
        //
        // Same debug-only seeded-representative short-circuit as LeakingCacheScenario's own -
        // watches lateChunk specifically (added after the static field's first sweep), not
        // whatever the real allocation sampler happens to pick. See SEED_EPOCHS_FOR_HYSTERESIS's
        // own comment for the minimum epoch count this needs - kept uncapped here (not stopped
        // once that minimum is reached) specifically so a wipe that costs an early round or two
        // still leaves enough remaining rounds to reach it, rather than exhausting a fixed budget
        // of calls before ever getting there.
        hysteresisEpoch++;
        JavaProfiler.seedKlassPopulationSample0(
            LEAK_BUFFER_TEST_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        JavaProfiler.seedTidTrendSample0(
            LEAK_BUFFER_TEST_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
        JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_BUFFER_TEST_KLASS_ID, lateChunk);
        JavaProfiler.pollReferenceChainTargets0();

        // Only TRUST a match once passesRun() has genuinely changed since the snapshot taken right
        // before lateChunk was created - either advanced (the same, never-restarted search ran a
        // later pass) or reset to a lower value (restartSearch() ran, which only ever happens on a
        // threadLoop tick strictly after that snapshot, since time only moves forward). Either way
        // proves the match came from a walk that started after lateChunk existed, ruling out the
        // one race this whole seam exists to rule out: the very first, still-in-flight pass finding
        // lateChunk by accident because admitStaticFieldRoots() and expandFrontier() are two steps
        // of that SAME call, and Java can observe the former's completion before the latter runs.
        if (JavaProfiler.referenceChainPassesRunForTest0() != passesRunBeforeLateChunk) {
          profiler.dump(scratchDumpPath);
          match = findMatch(scratchDumpPath);
        }
      }

      if (match == null && !debugBuild) {
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath);
      }
      if (match == null && !debugBuild) {
        Thread.sleep(300);
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath);
      }
    }

    // A cold external JVM's one-shot root-seeded walk over its whole reachable graph (full
    // JUnit/JMC/Gradle-worker classpath) takes far longer than this scenario's own round loop -
    // found the hard way: a first attempt at this scenario's tail wait (5 x 1s) gave up and
    // printed NOT_FOUND_MARKER mere moments before the tracker's own runPass() actually
    // completed (searchState=COMPLETED) and successfully built the chain. Mirrors
    // ExternalProcessReferenceChainTest's own comment on why budget/pausetarget are raised this
    // far for exactly this reason.
    for (int attempt = 0; match == null && attempt < 40; attempt++) {
      Thread.sleep(1500);
      // Same passesRun()-advanced check as the round loop above (debug builds only) - by this
      // point in a real run it has virtually always already flipped, but there is no reason to
      // drop the guarantee here just because the round loop above didn't need it.
      if (debugBuild && JavaProfiler.referenceChainPassesRunForTest0() == passesRunBeforeLateChunk) {
        continue;
      }
      profiler.dump(scratchDumpPath);
      match = findMatch(scratchDumpPath);
    }

    if (match == null) {
      System.out.println(NOT_FOUND_MARKER);
      return;
    }
    System.out.println(FOUND_MARKER + match.chain.get(0).getFullName());
  }

  private static ReferenceChainAssertions.ChainMatch findMatch(Path scratchDumpPath) throws Exception {
    if (!Files.exists(scratchDumpPath)) {
      return null;
    }
    IItemCollection events;
    try (InputStream in = Files.newInputStream(scratchDumpPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    }
    return ReferenceChainAssertions.findMatchForClass(
        events.apply(ItemFilters.type("datadog.ReferenceChain")), byte[].class);
  }
}
