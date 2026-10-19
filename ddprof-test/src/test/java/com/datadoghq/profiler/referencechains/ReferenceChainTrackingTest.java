/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.nio.file.Files;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.lang.reflect.Method;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * End-to-end coverage for {@code ReferenceChainTracker} (referenceChains.h/.cpp) against a real
 * JVM, real GCs and a real JVMTI heap walk. {@code Profiler::dump()} emits
 * {@code datadog.ReferenceChainAbandoned} once the search has ended in
 * {@code SearchState::ABANDONED}; {@code pollWatchedTargets()} emits {@code datadog.ReferenceChain}
 * for ranked {@code selectLeakCandidates()} klasses whose representative a {@code runPass()} walk
 * has already tagged ({@code getTag() > 0} - a read, never a {@code SetTag} seed).
 *
 * <p><b>Why {@code @TestMethodOrder}:</b> {@code ReferenceChainTracker} is a process-wide
 * singleton. Leaving {@code SearchState::RUNNING} releases every tag the search assigned
 * ({@code releaseSearchTags()}), and its {@code FrontierTable} is sized only by the first
 * {@code start()} in this JVM ({@code if (_frontier == nullptr)} guard; no {@code forkEvery}, see
 * {@code ProfilerTestPlugin.kt}). {@link #shouldReportAbandonedSearchOnTinyFrontierCap()} drives
 * the search to {@code ABANDONED}, while both success-path tests need it {@code RUNNING} to see
 * non-zero tags and have no fallback for losing that race, so they run first
 * ({@code @Order(1)}/{@code @Order(2)}). Their relative order does not matter: they target
 * different klasses ({@link ChainLink} vs {@link CachedPayload}) and neither exhausts the search.
 */
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@Tag("slow")
public class ReferenceChainTrackingTest extends AbstractProfilerTest {

  // Arbitrary klass ids for the debug-only population-seeding seams. Distinct from each other and
  // from ReferenceChainTestSeamsTest's ids to avoid collisions in the shared, no-forkEvery JVM.
  private static final int CHAIN_LINK_TEST_KLASS_ID = 987201;
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987202;

  // Static, not local: the discovered-chain gate suppresses shallow chains rooted at a transient
  // root (stack/JNI local), and ChainLinks at depth 1 of a locally-held list are exactly that
  // shape. (CachedPayload chains go three hops through HashMap internals, which the gate lets
  // through regardless of root kind.) Cleared in the test's finally so it does not keep its
  // population reachable for later tests in this shared JVM.
  private static List<Object> gcRootHolder;

  // consecutive_positive only starts incrementing once ring_fill reaches
  // KLASS_POPULATION_MIN_FILL_FOR_TREND=10 (ringThirdsStats()'s fill < min_fill guard resets it to
  // 0 before that), and selectLeakCandidates() needs it at LEAK_TREND_HYSTERESIS_BASE=5 (or 3 when
  // heapFloorRising() corroborates). hasLeakSignal() - which shouldRunPass() gates even the first
  // pass on under generations=true - consults that. 10 + 5 - 1 = 14 seeded epochs is the minimum;
  // +1 for margin.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  // Dedicated id for shouldReportAbandonedSearchOnTinyFrontierCap()'s seeding, for the same
  // collision-avoidance reason as the ids above.
  private static final int ABANDON_TEST_KLASS_ID = 987203;

  // T_REFERENCE_CHAIN in jfrMetadata.h - the jdk.ActiveSetting "id" written by flightRecorder.cpp's
  // writeBoolSetting(buf, T_REFERENCE_CHAIN, "enabled", ...). Must stay in sync with that enum.
  private static final long REFERENCE_CHAIN_EVENT_ID = 129;

  @Override
  protected String getProfilerCommand() {
    String testName = testInfo != null
        ? testInfo.getTestMethod().map(Method::getName).orElse("")
        : "";
    if ("shouldReconstructReferrerChainToGcRoot".equals(testName)
        || "shouldReconstructReferrerChainThroughUnboundedCacheLeak".equals(testName)) {
      // generations=true: pollWatchedTargets() does nothing unless
      // LivenessTracker::gcGenerationsEnabled() is true; referencechains=... alone stays
      // whole-graph-only. A large framecap avoids FRONTIER_CAP abandonment against this JVM's
      // real root-reachable graph, and a long ttl avoids TTL abandonment mid-test - either would
      // call releaseSearchTags() and zero every tag this test depends on.
      //
      // pausetarget=5000: measured FollowReferences/GetObjectsWithTags latency starts ~150ms and
      // climbs past 1s as cumulative progress grows (each pass re-scans the discovered set).
      // Against the default 5ms ceiling (DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS) updatePacing()
      // settles at MIN_EFFECTIVE_BUDGET=50 edges/pass and MAX_EFFECTIVE_CADENCE_NS=4s, too slow
      // for this test's wall-clock budget; a merely generous ceiling only postpones that. A
      // ceiling above the expected peak per-pass cost keeps _effective_budget at budget=4000.
      //
      // painbudget=100: the @Order(2) test needs a search restart (canAffordNewSearch()) after
      // the @Order(1) search terminates. PainBudget (painBudget.h) gates that on
      // pain_spent_ms / refill_rate of cooldown, which at the default 1% refill can run to
      // minutes - past this test's bounded retry loop. Nothing else here competes for the budget.
      //
      // firstpassbudget=200000: root enumeration (runPassManualWalk()'s
      // IterateOverReachableObjects) otherwise shares budget=4000, which was observed exhausting
      // on other roots' subtrees before ever admitting an edge from this thread's stack (where
      // the cache test's HashMap lives). Raising only the root-enumeration budget leaves the
      // steady-state expansion pacing (updatePacing()) untouched.
      //
      // memory=64:l:1.0 - the explicit 100% live-sample ratio is load-bearing: the default 10%
      // (_live_samples_ratio, arguments.h) makes LivenessTracker::track() drop 90% of tracked
      // instances, thinning the representative and trend pools (observed as intermittent
      // "representative died/evicted" and zero-tag runs). Tracking volume is still capped by the
      // 256KiB sampling-interval floor, so the table stays small.
      return "memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=4000:ttl=120000:framecap=2000000:pausetarget=5000:painbudget=100:firstpassbudget=200000";
    }
    // shouldReportAbandonedSearchOnTinyFrontierCap needs the frontier table, not the per-pass
    // budget, to run out first: heapReferenceCallback() checks the budget before
    // FrontierTable::insert(), so budget<=framecap completes normally instead of abandoning. A
    // larger budget lets a second root-referenced object hit the full table, which runPass()
    // abandons on.
    //
    // framecap=1 only sizes the table if this is the first start() in the JVM
    // (`if (_frontier == nullptr)` guard); otherwise @Order(1)'s framecap=2000000 wins. ttl=100 is
    // the fallback trigger: _search_start_ns is set when the shared search first started, so on an
    // inherited oversized table the ttl check fires almost immediately. Either path produces
    // datadog.ReferenceChainAbandoned, which is all this method asserts on.
    //
    // painbudget=100: restartSearch()/resetSearchStateForTest() both call
    // _pain_budget.spend(_search_pain_ms) unconditionally, so the reset below inherits the
    // previous long-running search's pain debt; at the default 1% refill, draining it back to
    // canStartNow()==true takes minutes, past this method's retry budget.
    //
    // memory=64:l:1.0 is load-bearing: Profiler::start() only starts the ReferenceChainTracker
    // when allocation sampling activated (activated & EM_ALLOC); a bare referencechains=... falls
    // back to cpu-only and never runs the search. No generations=true: LivenessTracker::initialize()
    // then clears _gc_generations, so hasLeakSignal() returns true without any population trend.
    if ("shouldReportAbandonedSearchOnTinyFrontierCap".equals(testName)) {
      return "memory=64:l:1.0,referencechains=true:hops=32:budget=500:framecap=1:ttl=100:painbudget=100";
    }
    // shouldExposeReferenceChainsSettingWhenEnabled: a referencechains-only command. Arguments::parse()
    // implicitly falls back to cpu profiling, whose ActiveSetting is also "enabled"="true", so the
    // test also matches on the ActiveSetting "id" (T_REFERENCE_CHAIN, REFERENCE_CHAIN_EVENT_ID).
    return "referencechains=true:hops=32:budget=500:ttl=2000:framecap=256";
  }

  @Override
  protected boolean isPlatformSupported() {
    // FollowReferences/tag-based frontier walking (referenceChains.cpp) assumes a
    // HotSpot-shaped JVMTI heap implementation; excluded platforms mirror
    // LivenessTrackingTest's own guard (memleak/LivenessTrackingTest.java).
    return !(Platform.isJavaVersion(8) || Platform.isJ9() || Platform.isZing());
  }

  /**
   * Verifies the {@code referencechains=...} flag round-trips through
   * {@code Arguments} parsing (arguments.cpp's {@code CASE("referencechains")}) into the
   * {@code datadog.ReferenceChain} JFR setting (flightRecorder.cpp's
   * {@code writeBoolSetting(buf, T_REFERENCE_CHAIN, "enabled", args._reference_chains)}).
   */
  @Test
  public void shouldExposeReferenceChainsSettingWhenEnabled() {
    stopProfiler();
    JfrEvents settings = verifyEvents("jdk.ActiveSetting");
    boolean sawEnabledSetting = false;
    for (JfrEvent item : settings) {
      if (item.getLong("id", -1) == REFERENCE_CHAIN_EVENT_ID
          && "enabled".equals(item.getString("name"))
          && "true".equals(item.getString("value"))) {
        sawEnabledSetting = true;
        break;
      }
    }
    assertTrue(sawEnabledSetting, "datadog.ReferenceChain#enabled setting was not found");
  }

  /**
   * Allocates a growing, statically-held population of {@link ChainLink} instances with a GC and
   * dump between rounds until {@code selectLeakCandidates()} trusts the trend, then waits for
   * {@code pollWatchedTargets()} to emit the candidate's chain once a {@code runPass()} walk has
   * tagged it.
   *
   * <p>Each round needs an explicit {@link #dump(Path)}: {@code cleanup_table()}'s per-klass
   * population accounting only runs (unforced) via {@code flush_table()} from
   * {@code LivenessTracker::flush()}, which is called only from {@code Profiler::dump()} - there
   * is no timer-driven flush. {@code System.gc()} bumps {@code _gc_epoch} synchronously in the
   * {@code GarbageCollectionFinish} callback, so no sleep is needed between the GC and the dump.
   */
  @Test
  @Order(1)
  public void shouldReconstructReferrerChainToGcRoot() throws Exception {
    // Seed one element *before* resetting the search: ArrayList's backing array starts as the
    // shared empty sentinel, and expandFrontier() freezes a node's children when it is expanded
    // and never re-examines it. An unrelated GC can wake the restarted BFS thread before round 1's
    // addAll(); expanding the holder while still empty would leave every later ChainLink
    // unreachable (seen in CI as tag=0 on every poll). Every later grow() copies index 0, so
    // whichever array the walk snapshots is non-empty.
    gcRootHolder = new ArrayList<>();
    gcRootHolder.add(new ChainLink("gc-root-seed"));
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // @Order(1) only orders this class: another test class in this no-forkEvery JVM may have
      // left the singleton search non-RUNNING, after which runPass() never takes its root-seeded
      // walk again. The population reset is needed for the same reason: _klass_population
      // survives stop()/start(), and a leftover klass already past the hysteresis gate would let
      // the first pass start regardless of this method's own seeding, masking whether it is
      // sufficient. Debug-only: these native seams do not exist in a release build.
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
    // Every ChainLink is allocated by one persistent thread - see PersistentAllocator.
    PersistentAllocator allocator = new PersistentAllocator("togcroot-leak-allocator");

    Path scratchDumpPath = Paths.get("referencechains-population-scratch.jfr");
    try {
      // KLASS_POPULATION_MIN_FILL_FOR_TREND = 10 needs 10 epochs that actually observe a surviving
      // ChainLink sample, and sampling is probabilistic, so the loop grows per-round counts and
      // checks every round instead of committing to a fixed count. Staying under
      // KLASS_POPULATION_RING_SIZE = 30 keeps every round within the slope window. Capped at 16
      // because the shared fork (-Xmx512m, no forkEvery) hit "Java heap space" at 25.
      //
      // Growth is clamped at round 10: later rounds only add retries against the lock-contention
      // race below (the trend is already eligible), and unclamped growth was what exhausted the
      // heap.
      //
      // Sized against ObjectSampler::check()'s 256KiB minimum interval, not "memory=64" (which
      // only affects LivenessTracker's table capacity). ChainLink's padding keeps the instance
      // count - and so the graph the BFS walk must traverse - small. Other klasses (e.g. byte[])
      // may also be flagged, so matching is by ChainLink specifically.
      ReferenceChainAssertions.JfrChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;
      for (int round = 1; round <= totalRounds && match == null; round++) {
        int newInstances = Math.min(round, 10) * 600;
        List<Object> newLinks = new ArrayList<>(newInstances);
        allocator.run(() -> {
          for (int i = 0; i < newInstances; i++) {
            newLinks.add(new ChainLink("leak-" + newInstances + "-" + i));
          }
        });
        gcRootHolder.addAll(newLinks);
        System.gc();
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);

        if (match == null && ReferenceChainAssertions.isDebugInstrumentedBuild()) {
          // Under generations=true, shouldRunPass() gates even the first pass on hasLeakSignal(),
          // which this early falls through to selectLeakCandidates()'s hysteresis gate for some
          // klass. Seeding SEED_EPOCHS_FOR_HYSTERESIS epochs clears it, authorizing the BFS
          // thread's next wake to run the root-seeded walk. The poll below is therefore
          // best-effort: it only reconstructs once the representative's getTag() > 0, so the
          // retries give the background thread's own post-pass pollWatchedTargets() time to run.
          //
          // Seed exactly once: recordKlassPopulationSampleLocked() always appends a ring slot, so
          // reseeding would turn the ramp into a sawtooth and destroy the positive slope.
          //
          // Representative before seeding: setting it aliases the synthetic id to the
          // representative's real klass id, so the seeds land in the real population entry
          // (seeds under a bare synthetic id satisfy only hasLeakSignal()'s candidate count).
          ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(CHAIN_LINK_TEST_KLASS_ID, gcRootHolder.get(0));
          if (!seededTestKlassTrend) {
            // The allocator thread owns every ChainLink allocation, so its tid is the qualifying
            // one; the seeds accelerate the organic per-tid growth it produces every round.
            int leakTid = allocator.tid();
            // Seed counts match the organic ramp (+1 per epoch): hasQualifyingGrowth() compares
            // third-window means over seeds followed by real folds, and inflated seeds (epoch*10)
            // made the slope go negative (-20..-40 observed) once real samples displaced them.
            // With matched scale ([1..15, 1, 2, 3, ...]) every window pairing stays positive.
            for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
              ReferenceChainTestHooks.seedKlassPopulationSample0(CHAIN_LINK_TEST_KLASS_ID, epoch, epoch);
              ReferenceChainTestHooks.seedTidTrendSample0(CHAIN_LINK_TEST_KLASS_ID, leakTid, epoch, epoch);
            }
            seededTestKlassTrend = true;
          }
          ReferenceChainTestHooks.pollReferenceChainTargets0();
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }

        if (match == null) {
          // A quiet window with no dump() in flight: Profiler::dump() holds every _locks[] entry
          // exclusively during _jfr.dump() (rotateDictsAndRun()'s lockAll()/unlockAll()), and
          // writeReferenceChain() needs a slot to record anything, so back-to-back dumps leave
          // pollWatchedTargets() no window. No gc() before this dump, so cleanup_table()'s
          // epoch-advance stays a no-op and the trend is undisturbed.
          Thread.sleep(300);
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }
      }

      // Grace period: the trend only became eligible partway through the loop, and the same lock
      // contention can delay the write past the last dump().
      for (int attempt = 0; match == null && attempt < 5; attempt++) {
        Thread.sleep(1000);
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
      }

      assertNotNull(match,
          "Never observed a datadog.ReferenceChain event whose chain[0] is " + ChainLink.class
              + " after " + gcRootHolder.size() + " retained ChainLink instances across up to "
              + totalRounds + " population-growth rounds plus a grace period");
      // chain[0] is the target's own class, not its holder's: reconstructChain() appends each
      // entry's referrer_klass leaf-to-root, and referrer_klass is the discovered object's own
      // class (see referenceChainJfrRoundtrip_ut.cpp). Hops above chain[0] are JDK collection
      // internals this test does not control, so they are not asserted.
      assertEquals(ChainLink.class.getName(), match.chain.get(0));
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");
      assertTrue(!gcRootHolder.isEmpty()); // keeps every allocated ChainLink reachable until here
    } finally {
      gcRootHolder = null; // shared-JVM hygiene - see the static holder's own comment
      allocator.close();
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * Same target-selection mechanism as {@link #shouldReconstructReferrerChainToGcRoot()}, against
   * a common real-world leak shape: an ever-growing, never-evicted {@link java.util.HashMap} cache
   * of {@link CachedPayload} values. Also asserts the chain threads through HashMap's internal
   * storage, proving the walk handles real JDK collection internals.
   *
   * <p><b>Why {@code cache} is a local variable, not a {@code static} field:</b>
   * {@code expandFrontier()} freezes a node's children when it is expanded and never re-examines
   * it. A {@code static} field is a root from class-load time, so an early pass would almost
   * certainly expand it while still empty and block discovery of everything added later.
   */
  @Test
  @Order(2)
  public void shouldReconstructReferrerChainThroughUnboundedCacheLeak() throws Exception {
    // Seed one entry before the resets, for the same empty-sentinel/frozen-children reason as
    // gcRootHolder's seeding: HashMap's table is only allocated on the first put().
    Map<String, CachedPayload> cache = new HashMap<>();
    cache.put("cache-leak-seed", new CachedPayload("cache-leak-seed"));
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // The natural restart after the @Order(1) search ends is gated on canAffordNewSearch() and
      // not guaranteed within this method's retry budget, so force a fresh search. The population
      // reset is also needed: resetReferenceChainSearchForTest0() leaves LivenessTracker's rings
      // alone, and ChainLink's leftover positive slope could outrank CachedPayload.
      // Debug-only: these native seams do not exist in a release build.
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
    // Every CachedPayload is allocated by one persistent thread - see PersistentAllocator.
    PersistentAllocator allocator = new PersistentAllocator("cache-leak-allocator");
    Path scratchDumpPath = Paths.get("referencechains-cache-leak-scratch.jfr");
    try {
      // Same round-growth/retry shape (and caps) as shouldReconstructReferrerChainToGcRoot().
      ReferenceChainAssertions.JfrChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;

      // Keys are pre-generated: a String key (and its byte[]) allocated alongside each
      // CachedPayload would compete for the size-weighted sampler. Allocating them all up front
      // lets their own population trend flatten before CachedPayload's starts growing.
      int maxEntries = 0;
      for (int round = 1; round <= totalRounds; round++) {
        maxEntries += Math.min(round, 10) * 600;
      }
      String[] keys = new String[maxEntries];
      for (int i = 0; i < keys.length; i++) {
        keys[i] = "leak-" + i;
      }

      int nextKey = 0;
      for (int round = 1; round <= totalRounds && match == null; round++) {
        // Same *600 rate as the ChainLink test: the two classes are near-identical in size, and a
        // lower rate let CachedPayload's ring stall short of KLASS_POPULATION_MIN_FILL_FOR_TREND.
        int newEntries = Math.min(round, 10) * 600;
        int keyOffset = nextKey;
        allocator.run(() -> {
          for (int i = 0; i < newEntries; i++) {
            String key = keys[keyOffset + i];
            cache.put(key, new CachedPayload(key));
          }
        });
        nextKey += newEntries;
        System.gc();
        dump(scratchDumpPath);
        JfrEvents events1 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
        match = ReferenceChainAssertions.findMatchForClass(events1, CachedPayload.class);

        if (match == null && ReferenceChainAssertions.isDebugInstrumentedBuild()) {
          // Same seed-once, representative-first, best-effort-poll rationale as
          // shouldReconstructReferrerChainToGcRoot().
          ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(CACHED_PAYLOAD_TEST_KLASS_ID, cache.get(keys[0]));
          if (!seededTestKlassTrend) {
            // The allocator thread owns every CachedPayload allocation, and the seeds use the
            // organic ramp's scale - both for the reasons shouldReconstructReferrerChainToGcRoot()
            // gives.
            int leakTid = allocator.tid();
            for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
              ReferenceChainTestHooks.seedKlassPopulationSample0(CACHED_PAYLOAD_TEST_KLASS_ID, epoch, epoch);
              ReferenceChainTestHooks.seedTidTrendSample0(CACHED_PAYLOAD_TEST_KLASS_ID, leakTid, epoch, epoch);
            }
            seededTestKlassTrend = true;
          }
          ReferenceChainTestHooks.pollReferenceChainTargets0();
          dump(scratchDumpPath);
          JfrEvents events2 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
          match = ReferenceChainAssertions.findMatchForClass(events2, CachedPayload.class);
        }

        if (match == null) {
          // Same lock-contention race shouldReconstructReferrerChainToGcRoot()'s own comment
          // describes - a quiet retry gives pollWatchedTargets() a window to win a _locks[]
          // slot against Profiler::dump()'s own exclusive hold.
          Thread.sleep(300);
          dump(scratchDumpPath);
          JfrEvents events3 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
          match = ReferenceChainAssertions.findMatchForClass(events3, CachedPayload.class);
        }
      }

      for (int attempt = 0; match == null && attempt < 5; attempt++) {
        Thread.sleep(1000);
        dump(scratchDumpPath);
        JfrEvents events4 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
        match = ReferenceChainAssertions.findMatchForClass(events4, CachedPayload.class);
      }

      assertNotNull(match,
          "Never observed a datadog.ReferenceChain event whose chain[0] is " + CachedPayload.class
              + " after " + cache.size() + " cached entries across up to " + totalRounds
              + " population-growth rounds plus a grace period");
      assertEquals(CachedPayload.class.getName(), match.chain.get(0));
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");

      // The point of this test over shouldReconstructReferrerChainToGcRoot(): confirm the walk
      // actually passed through the cache's own internal storage, not some other, coincidental
      // retainer - cache is the only thing keeping any CachedPayload instance reachable.
      boolean sawHashMapInternals = false;
      for (String type : match.chain) {
        if (type.startsWith("java.util.HashMap")) {
          sawHashMapInternals = true;
          break;
        }
      }
      assertTrue(sawHashMapInternals,
          "Expected the reconstructed chain to pass through java.util.HashMap's own internal "
              + "storage (cache is a HashMap) - chain was: " + match.chain);
      assertTrue(!cache.isEmpty()); // keeps every cached CachedPayload reachable until here
    } finally {
      allocator.close();
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * Drives the shared search to {@code SearchState::ABANDONED} - via {@code framecap=1} when this
   * method sizes the {@code FrontierTable}, otherwise via the {@code ttl=100} fallback (see
   * {@code getProfilerCommand()}) - and asserts a {@code datadog.ReferenceChainAbandoned} event is
   * written on {@code dump()}, without asserting which reason produced it.
   *
   * <p>{@code @Order(3)}: abandoning the singleton search would break the two success-path tests.
   * The debug-build reset makes the fresh-search precondition explicit: if an earlier test's
   * trend never fired, the search may still be {@code RUNNING} with a large frontier.
   *
   * <p><b>Why the population seeding:</b> {@code resetReferenceChainSearchForTest0()} alone was
   * observed never running a first pass. With this command ({@code memory=64:l:1.0}, no
   * {@code generations=true}) {@code LivenessTracker::initialize()} clears generations, so
   * {@code hasLeakSignal()} returns true unconditionally; the seeding is defensive in case the
   * command re-enables generations, in which case {@code shouldRunPass()} falls through to
   * {@code selectLeakCandidates()} with nothing left from the cache test's population reset. No
   * representative is set: a qualifying entry counts toward {@code hasLeakSignal()} regardless,
   * and {@code resolveCandidateRepresentative()} is null-safe.
   *
   * <p><b>Why a {@code System.gc()} + throwaway {@code dump()} precede the seeding:</b>
   * {@code cleanup_table()} wipes {@code _klass_population} once when the class map's
   * generation changes (which this method's fresh {@code start()} causes), but only after the
   * {@code if (!is_epoch_owner && !forced) return;} guard, which an unforced dump-triggered call
   * passes only when a new GC epoch is pending. Without a GC first, the wipe would be deferred to
   * the next forced cleanup (on the BFS thread's wake after the GCs below) and discard the seed.
   * The success-path tests get this for free from their round-1 GC + dump.
   */
  @Test
  @Order(3)
  public void shouldReportAbandonedSearchOnTinyFrontierCap() throws Exception {
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // GC + throwaway dump before seeding - see javadoc.
      System.gc();
      Path warmupDumpPath = Paths.get("referencechains-abandoned-test-warmup.jfr");
      try {
        dump(warmupDumpPath);
      } finally {
        Files.deleteIfExists(warmupDumpPath);
      }
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      // Gate-only seeding: no tagged instance needs to match, so any tid would do.
      int abandonTid = ReferenceChainTestHooks.getTid();
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        ReferenceChainTestHooks.seedKlassPopulationSample0(ABANDON_TEST_KLASS_ID, epoch * 10, epoch);
        ReferenceChainTestHooks.seedTidTrendSample0(ABANDON_TEST_KLASS_ID, abandonTid, epoch * 3, epoch);
      }
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
    List<Object> gcRootHolder = new ArrayList<>();
    gcRootHolder.add(new ChainLink("middle", new ChainLink("leaf")));

    // GarbageCollectionFinish (onGCFinish(), referenceChains.cpp) wakes the BFS thread
    // early, but that wakeup can race the thread's own startup (VM::attachThread()
    // completing before its first OS::sleep() call) and be missed. Don't rely on the
    // signal alone: sleep comfortably past ReferenceChainTracker::PASS_CADENCE_NS (1s,
    // referenceChains.h) too, so the thread's fixed-cadence fallback trigger
    // (shouldRunPass()) guarantees at least one pass runs regardless of that race.
    for (int i = 0; i < 3; i++) {
      System.gc();
      Thread.sleep(100);
    }
    Thread.sleep(1500);

    Path dumpPath = Paths.get("referencechains-abandoned-test.jfr");
    try {
      // The pass still has to be woken and reach the frontier-cap/ttl cutoff within whatever time
      // the shared JVM grants it; a single fixed sleep-then-assert failed when it landed a beat
      // early. Retry spaced far enough apart to tolerate a slow wake or a larger inherited heap.
      JfrEvents abandoned = null;
      for (int attempt = 0; attempt < 8; attempt++) {
        dump(dumpPath);
        abandoned = verifyEvents(dumpPath, "datadog.ReferenceChainAbandoned", false);
        if (abandoned.hasItems()) {
          break;
        }
        Thread.sleep(1000);
      }
      assertTrue(abandoned != null && abandoned.hasItems(),
          "Expected at least one datadog.ReferenceChainAbandoned event after 3 GCs, an initial "
              + "1500ms grace period, and 8 retries 1s apart");
    } finally {
      Files.deleteIfExists(dumpPath);
    }
    assertTrue(!gcRootHolder.isEmpty()); // keeps gcRootHolder reachable until the dump above
  }

  /**
   * Referrer-type fixture for the success-path and abandonment-path tests. The 32 {@code long}
   * fields cut the instance count needed per sampled megabyte. Plain fields, not an array: an
   * array would be a separate allocation competing for the size-weighted sampler.
   */
  private static final class ChainLink {
    final String name;
    final Object next;
    long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;

    ChainLink(String name) {
      this(name, null);
    }

    ChainLink(String name, Object next) {
      this.name = name;
      this.next = next;
    }
  }

  /**
   * Cache-value fixture for {@link #shouldReconstructReferrerChainThroughUnboundedCacheLeak()}.
   * Padded with plain {@code long} fields for the same reason as {@link ChainLink}; a
   * {@code byte[]} field was observed taking every sample away from {@code CachedPayload}.
   */
  private static final class CachedPayload {
    final String key;
    long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;

    CachedPayload(String key) {
      this.key = key;
    }
  }
}
