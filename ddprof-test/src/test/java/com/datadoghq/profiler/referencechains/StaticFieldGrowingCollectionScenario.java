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
import java.lang.reflect.Field;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;

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
   * life. The backing ArrayList is pre-sized so it never reallocates during the scenario: the
   * elementData array checked as EXPANDED before lateChunk is appended is the very array that ends
   * up holding lateChunk.
   */
  static final List<byte[]> LEAK_BUFFER =
      Collections.synchronizedList(new ArrayList<>(StaticFieldGrowingCollectionScenario.LEAK_BUFFER_CAPACITY));

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

  private static final int TOTAL_ROUNDS = 25;

  // Tail attempts (below) rotate the watched chunk they append to LEAK_BUFFER, so the backing
  // ArrayList's pre-sized capacity must cover them too - see LEAK_BUFFER_CAPACITY's own comment
  // for why elementData must never reallocate.
  private static final int TAIL_ATTEMPTS = 40;

  // How many consecutive tail attempts the SAME freshly-appended chunk stays the watched target
  // before rotating to a new one - see the tail loop's own comment for why a chunk must be given
  // several attempts (its discovery matures across walk cycles, slower than one 1.5s attempt)
  // and why a chunk that still has not resolved is assumed record-dead and abandoned.
  private static final int TAIL_CHUNK_ATTEMPTS = 8;

  // Seeds + lateChunk + one per round + one per tail rotation (sized for the worst case of one
  // per attempt so the budgets above can be retuned without touching this):
  // LEAK_BUFFER's elementData never reallocates.
  private static final int LEAK_BUFFER_CAPACITY =
      SEED_CHUNKS + 1 + TOTAL_ROUNDS + TAIL_ATTEMPTS;

  // FrontierEntryState::EXPANDED (referenceChainFrontier.h), as reported by
  // JavaProfiler.getReferenceChainFrontierStateForTest0().
  private static final int FRONTIER_STATE_EXPANDED = 1;

  // JavaProfiler.getReferenceChainFrontierStateForTest0()'s "no frontier entry" sentinel.
  private static final int FRONTIER_STATE_NONE = -1;

  /** Printed to stdout, followed by the matched leaf class's name, on success. */
  public static final String FOUND_MARKER = "[chain-found] ";

  /**
   * Printed to stdout, followed by {@code true}/{@code false}, once the scenario has decided
   * whether it takes the native test-seam path (every -DDEBUG build: debug/asan/tsan).
   */
  public static final String SEAM_PATH_MARKER = "[seam-path] ";

  /** Printed to stdout (with no class name suffix) if no match was ever observed. */
  public static final String NOT_FOUND_MARKER = "[chain-not-found]";

  /**
   * Seeds {@link #LEAK_BUFFER}, starts the profiler, then keeps appending new {@code byte[]}
   * chunks to the same list instance - the exact shape implicated in the live hotdog-pod stall -
   * watching specifically for a chain to a chunk appended *after* the static field's one-time
   * sweep, until a {@code datadog.ReferenceChain} event for it appears or {@code TOTAL_ROUNDS} is
   * exhausted.
   */
  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath) throws Exception {
    for (int i = 0; i < SEED_CHUNKS; i++) {
      LEAK_BUFFER.add(new byte[CHUNK_BYTES]);
    }
    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    // The seams used below are compiled into every -DDEBUG native build - debug, asan and tsan
    // (javaApi.cpp's #ifdef DEBUG block; ConfigurationPresets.kt) - so the seam path must be
    // enabled on all three. Same predicate as LeakTagCorrelationReferenceChainTest's rotation
    // gate; release builds get the no-op stubs.
    String testConfig = System.getProperty("ddprof_test.config");
    boolean debugBuild = testConfig != null
        && ("debug".equals(testConfig) || testConfig.endsWith("san"));
    System.out.println(SEAM_PATH_MARKER + debugBuild);
    int hysteresisEpoch = 0;
    // Declared at method scope: the per-round maintenance seeding below (in
    // its own debugBuild block) reuses this tid.
    int leakTid = 0;
    // Snapshotted BEFORE seeding anything, while the BFS thread's search has not run a single
    // pass yet (referenceChainPassesRunForTest0() reads 0 here) - see the wait loop below for why
    // this exact value, not just "nonzero", is what the wait needs to advance past.
    int initialPasses = debugBuild ? JavaProfiler.referenceChainPassesRunForTest0() : -1;

    if (debugBuild) {
      // Pins the frontier-state seam's -1 sentinel: an untagged object (tag 0) has no frontier
      // entry. Probed before any seeding - no pass can run until shouldRunPass() sees a leak
      // signal - so the BFS root walk cannot have tagged the probe yet.
      int untaggedState = JavaProfiler.getReferenceChainFrontierStateForTest0(new Object());
      if (untaggedState != FRONTIER_STATE_NONE) {
        throw new IllegalStateException("frontier-state seam returned " + untaggedState
            + " for an untagged probe object, expected " + FRONTIER_STATE_NONE);
      }
      // Wire a representative for the seeded klass BEFORE the seeds (set-representative-first
      // is the load-bearing order: klassPopulationSetRepresentativeForTest() re-keys the
      // synthetic entry to the representative's real klass id, and only a representative lets
      // the entry mint stable_class_tag). Without a representative topKlassesByGenerationCount()
      // skips the entry (no live instance was ever resolved), _watched_leak_klass_count stays
      // 0, and runPass() declares the search COMPLETED after every pass - and the terminal
      // pass itself then releases every frontier tag (releaseSearchTags()) while
      // restartSearch() re-runs the identical walk. The frontier-state seam below blocks on
      // _engine_lock mid-pass, so it can only read between passes - where the tags are already
      // released - and the EXPANDED wait below can never observe its condition (observed as
      // "holders never all reached EXPANDED within 45s" with states [-1, -1, -1]).
      // The representative MUST be a byte[] chunk - the leaked klass itself - never the
      // list holding it: the representative's real klass becomes the candidate klass, and only
      // candidate-klass instances get leak-tagged by tagLeakInstances() and recorded by the
      // leak-tag interception path whose chains the seam below reads. A non-byte[]
      // representative (e.g. LEAK_BUFFER's own SynchronizedList klass, which has no tracked
      // instances in this child JVM) mints no leak tags at all, and lateChunk is never
      // discovered (observed as 0/6 runs, the seam returning 0 forever). Watching byte[] does
      // flood _leak_parent_fanout with unrelated JVM-wide Object[] parents (~9.5k
      // entries/search observed), starving the leak-accumulation rotation prong - but discovery
      // does not depend on that prong: the static-anchor descend walk re-walks LEAK_BUFFER's
      // whole subtree every search and intercepts every leak-tagged chunk in it (observed
      // 10/10 searches), so lateChunk's chain is rebuilt once per search generation regardless.
      // The seed chunk is held strongly by the static field, so the tracker's weak
      // representative ref stays live.
      JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_BUFFER_TEST_KLASS_ID,
          LEAK_BUFFER.get(0));
      // Seed enough hysteresis-qualifying epochs to unlock ReferenceChainTracker::hasLeakSignal()/
      // shouldRunPass() - AFTER the representative above (set-representative-first is required,
      // see that call's own comment). hasLeakSignal() only asks selectLeakCandidates() for a
      // nonzero count -
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

    // Wait until LEAK_BUFFER's holders are ReferenceChainTracker-EXPANDED - strictly before this
    // scenario creates the one chunk whose chain it is actually going to watch for. This is the
    // entire point of this scenario: proving that an element appended to a static field's
    // collection AFTER that field's List is already EXPANDED gets discovered via a LATER
    // re-expansion of that stale entry, not via the very first pass that admitted it.
    // admitStaticFieldRoots() and expandFrontier() are two steps of the SAME runPass() call, and
    // neither the static-field sweep's completion nor a changed pass counter proves the holders
    // were expanded (see the debug branch below), so the wait reads their frontier state directly.
    // Release (non-DEBUG) builds have no such seam and fall back to a generous sleep - acceptable
    // there because the non-debug path never pins a specific representative anyway (see the
    // debugBuild branch below): it just waits on real, much-slower allocation sampling to notice
    // the growth on its own, so a few extra seconds of margin either way changes nothing about
    // what the eventual match would prove.
    if (debugBuild) {
      // A changed pass counter alone is not proof that LEAK_BUFFER's holders were expanded:
      // truncated passes also bump it, and admitStaticFieldRoots() only processes a bounded
      // chunk of classes per call. So the wait synchronizes on the holders' ACTUAL frontier state
      // instead: the SynchronizedList, its backing ArrayList and that ArrayList's elementData
      // array must all be EXPANDED before lateChunk exists - only then can lateChunk be reached
      // exclusively via a later re-expansion. The pass-counter check stays as a precondition
      // (and gates the reflective holder reads until the first pass - with its root
      // enumeration - has finished).
      Field backingListField;
      Field elementDataField;
      try {
        backingListField =
            Class.forName("java.util.Collections$SynchronizedList").getDeclaredField("list");
        backingListField.setAccessible(true);
        elementDataField = ArrayList.class.getDeclaredField("elementData");
        elementDataField.setAccessible(true);
      } catch (ReflectiveOperationException | RuntimeException e) {
        throw new IllegalStateException("cannot reach LEAK_BUFFER's backing ArrayList/elementData"
            + " - run with --add-opens java.base/java.util=ALL-UNNAMED", e);
      }
      // admitStaticFieldRoots() sweeps every loaded class - a cold external JVM's full
      // JUnit/JMC/Gradle-worker classpath (thousands of classes) can need several retries
      // against pause-time-SLO pacing, and the expansion backlog ahead of LEAK_BUFFER's holders
      // is FIFO - generous margin for the same reason ExternalProcessReferenceChainTest's own
      // budget/pausetarget are raised this far above the in-process test's defaults. Wall-clock
      // deadline: the seam reads can contend with a running pass's locks. Not scaled for
      // asan/tsan: the parent's 150s launch timeout must still cover this wait + rounds + the 60s
      // tail.
      long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(45);
      boolean holdersExpanded = false;
      while (!holdersExpanded && System.nanoTime() < deadline) {
        holdersExpanded = JavaProfiler.referenceChainPassesRunForTest0() != initialPasses
            && leakBufferHoldersExpanded(backingListField, elementDataField);
        if (!holdersExpanded) {
          Thread.sleep(100);
        }
      }
      if (!holdersExpanded) {
        throw new IllegalStateException(
            "LEAK_BUFFER's holders never all reached EXPANDED within 45s (passesRun="
                + JavaProfiler.referenceChainPassesRunForTest0() + ", initial=" + initialPasses
                + ", frontier states [list, backing ArrayList, elementData]="
                + describeHolderStates(backingListField, elementDataField)
                + ") - cannot safely create the chunk this scenario is supposed to discover only "
                + "via a later re-expansion of an already-EXPANDED static-field entry");
      }
    } else {
      Thread.sleep(3000);
    }
    // Snapshotted right after the wait above confirms the holders are EXPANDED - any
    // later change (advance, or reset-to-lower via a restart) proves a walk that started strictly
    // after lateChunk existed.
    int passesRunBeforeLateChunk = debugBuild ? JavaProfiler.referenceChainPassesRunForTest0() : -1;
    // lateChunk is deliberately NOT held in a local: the main thread's stack is a root-walk root,
    // so a live local lets the root enumeration admit (and, once the canary candidate aliases to
    // byte[] and a GC runs tagLeakInstances(), leak-tag) lateChunk directly - the resulting
    // stack-local-rooted chain never resolves into the static-field chain this scenario watches,
    // and the pre-existing tag blocks the elementData re-walk from admitting lateChunk under the
    // stale entry at all (observed as buildChainEvent "target_tag not in frontier" for the whole
    // run). Re-fetch the chunk from LEAK_BUFFER on every use instead - the only durable path to
    // it is the static field, so its discovery proves the stale-entry re-expansion.
    final int LATE_CHUNK_INDEX = SEED_CHUNKS;
    LEAK_BUFFER.add(new byte[CHUNK_BYTES]);

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
    for (int round = 1; round <= TOTAL_ROUNDS && match == null; round++) {
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
        JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_BUFFER_TEST_KLASS_ID,
            LEAK_BUFFER.get(LATE_CHUNK_INDEX));
        JavaProfiler.pollReferenceChainTargets0();

        // Only TRUST a match once passesRun() has genuinely changed since the snapshot taken right
        // before lateChunk was created - either advanced (the same, never-restarted search ran a
        // later pass) or reset to a lower value (restartSearch() ran, which only ever happens on a
        // threadLoop tick strictly after that snapshot, since time only moves forward). Either way
        // proves the match came from a walk that started after lateChunk existed, ruling out the
        // one race this whole seam exists to rule out: the very first, still-in-flight pass finding
        // lateChunk by accident because admitStaticFieldRoots() and expandFrontier() are two steps
        // of that SAME call, and Java can observe the former's completion before the latter runs.
        //
        // The match is pinned to lateChunk's OWN chain: any byte[] chain (the seed chunks created
        // before the first pass, discovered instances, other representatives) is not enough. The
        // tag is read BEFORE dumping - the dump snapshots the same resolved-chain cache - and a
        // round where the current search has not resolved lateChunk's chain yet is skipped.
        if (JavaProfiler.referenceChainPassesRunForTest0() != passesRunBeforeLateChunk) {
          long lateChunkTargetTag = JavaProfiler.getReferenceChainResolvedTargetTagForTest0(
              LEAK_BUFFER.get(LATE_CHUNK_INDEX));
          if (lateChunkTargetTag != 0) {
            profiler.dump(scratchDumpPath);
            match = findMatch(scratchDumpPath, lateChunkTargetTag);
          }
        }
      }

      // Release (non-DEBUG) builds have no identity seam: class-only matching, as before.
      if (match == null && !debugBuild) {
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath, 0);
      }
      if (match == null && !debugBuild) {
        Thread.sleep(300);
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath, 0);
      }
    }

    // A cold external JVM's one-shot root-seeded walk over its whole reachable graph (full
    // JUnit/JMC/Gradle-worker classpath) takes far longer than this scenario's own round loop -
    // found the hard way: a first attempt at this scenario's tail wait (5 x 1s) gave up and
    // printed NOT_FOUND_MARKER mere moments before the tracker's own runPass() actually
    // completed (searchState=COMPLETED) and successfully built the chain. Mirrors
    // ExternalProcessReferenceChainTest's own comment on why budget/pausetarget are raised this
    // far for exactly this reason.
    int watchedIndex = -1;
    int attemptsOnWatchedChunk = 0;
    for (int attempt = 0; match == null && attempt < TAIL_ATTEMPTS; attempt++) {
      Thread.sleep(1500);
      // Same passesRun()-advanced check as the round loop above (-DDEBUG builds only:
      // debug/asan/tsan) - by this point in a real run it has virtually always already flipped,
      // but there is no reason to drop the guarantee here just because the round loop above
      // didn't need it.
      long requiredTargetTag = 0;
      if (debugBuild) {
        if (JavaProfiler.referenceChainPassesRunForTest0() == passesRunBeforeLateChunk) {
          continue;
        }
        // The tail watches, one at a time, chunks appended to LEAK_BUFFER well after that
        // collection was first EXPANDED - exactly the discovery this scenario exists to prove.
        // Watching a chunk allocated once at scenario start (lateChunk above) is not durable:
        // the whole leak-tag pipeline keys on the chunk's allocation-tracking record, records
        // are only minted at allocation, and the tracking table's churn can evict an old
        // chunk's record for the rest of the run - observed as the representative resolving
        // that chunk correctly but reading tag=0 for 2000+ consecutive polls (no leak tag ever
        // minted, so no interception and no chain ever built for it). A FRESHLY appended chunk
        // has a guaranteed-live record: the explicit poll below tags it immediately, the next
        // static-anchor descend intercepts it, and a later attempt's poll resolves its chain.
        // But discovery takes several walk cycles (interception, then a later poll's chain
        // build) - measured at more than one 1.5s attempt - so the SAME chunk must stay the
        // watched target for several attempts before rotating to a new one; rotating every
        // attempt reads a just-allocated chunk that has not matured yet and abandons each
        // chunk right before it would resolve (observed as 0/8 runs). If a chunk still has
        // not resolved after TAIL_CHUNK_ATTEMPTS attempts, its record most likely died the
        // same death lateChunk's can - rotate. Same no-local discipline as lateChunk above:
        // each watched chunk is reachable only through LEAK_BUFFER, so any walk that reaches
        // it comes through elementData, never through a stack-local root.
        if (watchedIndex < 0 || attemptsOnWatchedChunk >= TAIL_CHUNK_ATTEMPTS) {
          LEAK_BUFFER.add(new byte[CHUNK_BYTES]);
          watchedIndex = LEAK_BUFFER.size() - 1;
          attemptsOnWatchedChunk = 0;
        }
        attemptsOnWatchedChunk++;
        JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_BUFFER_TEST_KLASS_ID,
            LEAK_BUFFER.get(watchedIndex));
        JavaProfiler.pollReferenceChainTargets0();
        requiredTargetTag = JavaProfiler.getReferenceChainResolvedTargetTagForTest0(
            LEAK_BUFFER.get(watchedIndex));
        if (requiredTargetTag == 0) {
          continue;
        }
      }
      profiler.dump(scratchDumpPath);
      match = findMatch(scratchDumpPath, requiredTargetTag);
    }

    if (match == null) {
      System.out.println(NOT_FOUND_MARKER);
      return;
    }
    System.out.println(FOUND_MARKER + match.chain.get(0).getFullName());
  }

  /**
   * {@code requiredTargetTag == 0}: the first byte[] chain (class-only, non-debug builds).
   * Otherwise: only the byte[] chain whose targetTag identifies that one instance.
   */
  private static ReferenceChainAssertions.ChainMatch findMatch(Path scratchDumpPath,
      long requiredTargetTag) throws Exception {
    if (!Files.exists(scratchDumpPath)) {
      return null;
    }
    IItemCollection events;
    try (InputStream in = Files.newInputStream(scratchDumpPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    }
    IItemCollection chains = events.apply(ItemFilters.type("datadog.ReferenceChain"));
    return requiredTargetTag == 0
        ? ReferenceChainAssertions.findMatchForClass(chains, byte[].class)
        : ReferenceChainAssertions.findMatchForClassAndTargetTag(
            chains, byte[].class, requiredTargetTag);
  }

  /**
   * Frontier states of LEAK_BUFFER, its backing ArrayList and that list's elementData array.
   * The holders are fetched fresh on every call and never kept beyond it - a static field or a
   * long-lived local would add a second root path to them.
   */
  private static int[] holderStates(Field backingListField, Field elementDataField)
      throws IllegalAccessException {
    Object backing = backingListField.get(LEAK_BUFFER);
    Object elementData = elementDataField.get(backing);
    return new int[] {
      JavaProfiler.getReferenceChainFrontierStateForTest0(LEAK_BUFFER),
      JavaProfiler.getReferenceChainFrontierStateForTest0(backing),
      JavaProfiler.getReferenceChainFrontierStateForTest0(elementData)
    };
  }

  private static boolean leakBufferHoldersExpanded(Field backingListField, Field elementDataField)
      throws IllegalAccessException {
    for (int state : holderStates(backingListField, elementDataField)) {
      if (state != FRONTIER_STATE_EXPANDED) {
        return false;
      }
    }
    return true;
  }

  private static String describeHolderStates(Field backingListField, Field elementDataField)
      throws IllegalAccessException {
    return Arrays.toString(holderStates(backingListField, elementDataField));
  }
}
