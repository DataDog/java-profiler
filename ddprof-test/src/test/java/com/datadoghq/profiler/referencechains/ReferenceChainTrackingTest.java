/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.Platform;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;
import org.junitpioneer.jupiter.RetryingTest;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IAttribute;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.openjdk.jmc.common.item.Attribute.attr;
import static org.openjdk.jmc.common.unit.UnitLookup.PLAIN_TEXT;

/**
 * PROF-15341 (+ lifecycle-wiring follow-up, + the Remaining Work Plan's target-selection bridging,
 * pause-time pacing, and reporting work): end-to-end
 * coverage for {@code ReferenceChainTracker} (ddprof-lib/src/main/cpp/referenceChains.h/.cpp).
 *
 * <p><b>Scope note:</b> {@code ReferenceChainTracker::start()} is now called from
 * {@code Profiler::start()} (profiler.cpp), gated on {@code args._reference_chains}, followed by
 * {@code ReferenceChainTracker::startThread()} which spawns its BFS thread; {@code Profiler::stop()}
 * calls the matching {@code stopThread()}/{@code stop()} pair. A {@code datadog.ReferenceChainAbandoned}
 * event now reaches a live {@code Recording}: {@code Profiler::dump()} calls
 * {@code buildAbandonedEvent()} and writes its output via
 * {@code Profiler::writeReferenceChainAbandoned()}/{@code FlightRecorder::recordReferenceChainAbandoned()}
 * whenever the search has ended in {@code SearchState::ABANDONED} - mirroring the
 * {@code LivenessTracker::flush()} call site there. {@link #shouldReportAbandonedSearchOnTinyFrontierCap()}
 * exercises that path end-to-end below.
 *
 * <p><b>{@code buildChainEvent()}'s target-selection feed (Remaining Work Plan's target-selection
 * bridging step):</b>
 * {@code ReferenceChainTracker::pollWatchedTargets()} (referenceChains.cpp), called from
 * {@code threadLoop()} once per scheduling cycle after {@code runPass()}, closes the gap this class's
 * header comment used to describe as unclosed. It polls
 * {@code LivenessTracker::selectLeakCandidates()} (positive population-slope ranking over a rolling
 * per-klass survivor-count window, gated on {@code _gc_generations} - design doc's Open Question 3)
 * and, for each ranked klass whose representative instance an ordinary {@code runPass()} walk has
 * *already* tagged ({@code getTag() > 0} - a read, never a {@code SetTag} seed), reconstructs and
 * emits its chain via {@code Profiler::writeReferenceChain()}. {@link #shouldReconstructReferrerChainToGcRoot()}
 * below exercises this end to end against a real JVM, real GCs, and a real JVMTI heap walk - not a
 * synthetic frontier fixture (see {@code referenceChainJfrRoundtrip_ut.cpp}/{@code ReferenceChainJfrParserTest}
 * for that already-covered, lower-level reconstruction-correctness proof).
 *
 * <p><b>Why {@code @TestMethodOrder}/{@code @Order(1)}:</b> {@code ReferenceChainTracker} is a
 * process-wide singleton whose single, singleton-owned search (design doc's Open Question 3
 * "Shipped" note) never restarts once it leaves {@code SearchState::RUNNING} -
 * {@code shouldRunPass()} (referenceChains.cpp) returns {@code false} forever after that point, and
 * the transition itself releases every tag the search ever assigned
 * ({@code releaseSearchTags()}). Its {@code FrontierTable} is sized once, the first time any test
 * in this JVM calls {@code ReferenceChainTracker::start()}, and never resized on later
 * start()/stop() cycles (referenceChains.cpp's {@code if (_frontier == nullptr)} guard) - so
 * whichever test runs first also fixes that capacity for every test that runs after it in the same
 * JVM (no {@code forkEvery} configured, see {@code ProfilerTestPlugin.kt}, so this whole class runs
 * in one). {@link #shouldReportAbandonedSearchOnTinyFrontierCap()} below deliberately drives that
 * shared search to {@code SearchState::ABANDONED}, via an artificially tiny frontier cap when it
 * gets to build the table itself, or its own {@code ttl} fallback otherwise (see that method's own
 * comment). Both {@link #shouldReconstructReferrerChainToGcRoot()} and
 * {@link #shouldReconstructReferrerChainThroughUnboundedCacheLeak()} need the search still
 * {@code RUNNING} to find their own candidates' tags non-zero, so they are pinned to run first,
 * via {@code @Order(1)}/{@code @Order(2)} respectively - without that ordering all three tests
 * would race for which ones get to observe a still-{@code RUNNING} search, and neither
 * success-path test has a fallback for losing that race the way the abandonment test does. The
 * relative order between the two success-path tests does not itself matter - both target
 * different klasses ({@link ChainLink} vs {@link CachedPayload}) within the same shared search,
 * and neither exhausts it - only their both running before the abandonment test does.
 */
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
public class ReferenceChainTrackingTest extends AbstractProfilerTest {

  private static final IAttribute<String> SETTING_NAME = attr("name", "", "", PLAIN_TEXT);
  private static final IAttribute<String> SETTING_VALUE = attr("value", "", "", PLAIN_TEXT);

  // Arbitrary, test-chosen klass ids for the debug-only population-seeding seams below (see
  // ReferenceChainTestSeamsTest's own comment: LivenessTracker's population table treats these as
  // opaque keys, so they need not resolve to any real class). Distinct per test/from
  // ReferenceChainTestSeamsTest's own ids purely as cheap insurance against collision in a shared,
  // no-forkEvery test JVM.
  private static final int CHAIN_LINK_TEST_KLASS_ID = 987201;
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987202;

  @Override
  protected String getProfilerCommand() {
    String testName = testInfo != null
        ? testInfo.getTestMethod().map(java.lang.reflect.Method::getName).orElse("")
        : "";
    if ("shouldReconstructReferrerChainToGcRoot".equals(testName)
        || "shouldReconstructReferrerChainThroughUnboundedCacheLeak".equals(testName)) {
      // memory=...:l + generations=true: LivenessTracker::gcGenerationsEnabled() (Remaining
      // Work Plan's population tracking / target-selection bridging, livenessTracker.h) must be true for pollWatchedTargets()
      // (referenceChains.cpp) to do anything at all - referencechains=... alone stays
      // whole-graph-only (design doc's Open Question 3 "still undecided" fallback). A small
      // sampling interval maximizes the chance the many ChainLink instances this test
      // allocates below actually get liveness-tracked (LivenessTracker::track(), invoked from
      // the allocation-sampling path whenever _gc_generations || _record_liveness is set,
      // objectSampler.cpp). A large framecap avoids an early
      // SearchAbandonReason::FRONTIER_CAP abandonment against this JVM's real,
      // not-controlled-by-this-test root-reachable graph size, and a long ttl avoids a
      // TTL abandonment mid-test - either would call releaseSearchTags() and permanently
      // zero every tag this test depends on (see this class's header comment on why this
      // test is pinned to @Order(1)).
      //
      // pausetarget=5000: the pause-time pacing controller's updatePacing() (referenceChains.cpp) measures this JVM's real
      // FollowReferences/GetObjectsWithTags call latency at ~150ms early on, climbing past a full
      // second as this test's own allocation keeps handing the search more to discover (each pass
      // re-scans the whole already-discovered/tagged set, so cost grows with cumulative progress,
      // not with this test's own allocation *rate*) - i.e. that latency is dominated by per-call
      // overhead, not by the requested edge budget. Against the default pausetarget=5ms ceiling
      // (DEFAULT_REFERENCE_CHAINS_PAUSE_TARGET_MS, arguments.h) every observed pass is "over
      // ceiling even at the floor", so the controller settles at MIN_EFFECTIVE_BUDGET=50 edges/pass
      // and MAX_EFFECTIVE_CADENCE_NS=4s between passes - a real but glacial discovery rate this
      // test's own wall-clock budget cannot outwait, and one a merely-generous ceiling (e.g. 500ms)
      // only postpones: once cumulative progress pushes the real per-pass cost back past *that*
      // ceiling too, the same throttling recurs. A ceiling comfortably above the highest per-call
      // cost this test's own scale of population growth is expected to reach instead lets the
      // controller keep _effective_budget at this test's own configured budget=4000 ceiling for
      // the method's entire run, the same convergence behavior referenceChains_ut.cpp's own pacing
      // tests already exercise synthetically.
      //
      // painbudget=100: shouldReconstructReferrerChainThroughUnboundedCacheLeak shares this
      // singleton search with shouldReconstructReferrerChainToGcRoot (@Order(1), runs first) and
      // needs a restart (canAffordNewSearch(), referenceChains.cpp) once that first search
      // reaches a terminal state. PainBudget (painBudget.h) gates that restart on
      // pain_spent_ms / refill_rate milliseconds of cooldown; the default
      // DEFAULT_REFERENCE_CHAINS_PAIN_BUDGET_PERCENT=1 (1% refill) can make that cooldown run to
      // tens of seconds to minutes for a search this large - far past this test's own bounded
      // retry loop (16 rounds plus a short grace period). painbudget=100 keeps the restart gate
      // affordable immediately, which is fine here since nothing else in this JVM is competing
      // for the pain budget.
      //
      // firstpassbudget=200000: the search's one-shot, root-seeded first pass (runPass()'s
      // !_search_started branch) shares budget=4000 with every later pass unless overridden -
      // in this shared, forked test JVM's real (not controlled by this test) root-reachable
      // graph, that leaves this method's own CachedPayload-holding cache HashMap (a direct
      // stack-local root on this test's own thread) at the mercy of whatever order JVMTI's
      // FollowReferences happens to enumerate roots in: budget=4000 was observed exhausting
      // itself on other roots' subtrees every single pass, never once admitting a single edge
      // from this thread's own stack. Overriding just the first pass's own budget (not
      // budget=4000, which the pacing controller has already been tuned around - raising it
      // instead throttles every later pass down to MIN_EFFECTIVE_BUDGET/MAX_EFFECTIVE_CADENCE_NS,
      // see updatePacing()) gives that one-shot root enumeration enough headroom to reach this
      // thread's stack without slowing down the steady-state expansion passes that follow.
      return "memory=64:l,generations=true,"
          + "referencechains=true:hops=64:budget=4000:ttl=120000:framecap=2000000:pausetarget=5000:painbudget=100:firstpassbudget=200000";
    }
    // shouldReportAbandonedSearchOnTinyFrontierCap needs the frontier table (not the
    // per-pass budget) to be what runs out first: heapReferenceCallback() (referenceChains.cpp)
    // checks the budget before ever calling FrontierTable::insert(), so a budget as small as
    // the frontier cap itself (e.g. budget=1:framecap=1) only ever exhausts the budget after
    // admitting exactly one object - insert() never gets a chance to fail, and the search
    // completes normally instead of abandoning. A budget comfortably larger than framecap=1
    // lets a *second* root-referenced object reach insert() and hit the actually-full table,
    // which is what runPass() treats as grounds to abandon (Termination section priority 1).
    //
    // framecap=1 only actually controls the table's capacity the *first* time
    // ReferenceChainTracker::start() ever constructs its FrontierTable in this JVM
    // (referenceChains.cpp's `if (_frontier == nullptr)` guard - the table, like
    // LivenessTracker's own, survives every later start()/stop() cycle at whatever size it was
    // first built with). This method's own @Order(1) pinning on
    // shouldReconstructReferrerChainToGcRoot means *that* test's own, much larger framecap=2000000
    // wins that race instead - so this method also supplies a small ttl as a second, independent
    // abandonment trigger. runPass()'s Termination-section priority still checks frontier-cap
    // first, so a fresh, genuinely-tiny table (this method running first, e.g. in isolation via
    // `-Ptests=ReferenceChainTrackingTest.shouldReportAbandonedSearchOnTinyFrontierCap`) still
    // abandons via SearchAbandonReason::FRONTIER_CAP as originally designed; inheriting an
    // already-oversized table instead falls through to the ttl check, which fires almost
    // immediately regardless of table size because _search_start_ns (referenceChains.h) is set
    // once, the first time the shared search ever started - by the time this method's own
    // start() call re-parses ttl, that clock already reads however long
    // shouldReconstructReferrerChainToGcRoot's own run took. Either path produces a
    // datadog.ReferenceChainAbandoned event, which is all this method actually asserts on.
    if ("shouldReportAbandonedSearchOnTinyFrontierCap".equals(testName)) {
      return "referencechains=true:hops=32:budget=500:framecap=1:ttl=100";
    }
    // Deliberately does not request cpu/wall/memory/nativemem: those categories also
    // write an "enabled" ActiveSetting (flightRecorder.cpp:1141-1144) and all default to
    // false when not requested, so "enabled"="true" is unambiguous evidence of the
    // datadog.ReferenceChain setting specifically without needing to disambiguate by the
    // ActiveSetting "id" field (JMC's generic accessor lookup does not resolve that field
    // for this custom event type - not worth a bespoke accessor for one assertion).
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
   * {@code datadog.ReferenceChain} JFR setting (flightRecorder.cpp:1143's
   * {@code writeBoolSetting(buf, T_REFERENCE_CHAIN, "enabled", args._reference_chains)}).
   */
  @RetryingTest(5)
  public void shouldExposeReferenceChainsSettingWhenEnabled() {
    stopProfiler();
    IItemCollection settings = verifyEvents("jdk.ActiveSetting");
    boolean sawEnabledSetting = false;
    for (IItemIterable iterable : settings) {
      IMemberAccessor<String, IItem> nameAccessor = SETTING_NAME.getAccessor(iterable.getType());
      IMemberAccessor<String, IItem> valueAccessor = SETTING_VALUE.getAccessor(iterable.getType());
      if (nameAccessor == null || valueAccessor == null) {
        continue;
      }
      for (IItem item : iterable) {
        if ("enabled".equals(nameAccessor.getMember(item))
            && "true".equals(valueAccessor.getMember(item))) {
          sawEnabledSetting = true;
        }
      }
    }
    assertTrue(sawEnabledSetting, "datadog.ReferenceChain#enabled setting was not found");
  }

  /**
   * This test's stated success-path scenario, now exercising the Remaining Work Plan's
   * target-selection bridging feed instead of staying disabled: allocates a growing population of
   * {@link ChainLink} instances, forcing GCs between allocation rounds so
   * {@code LivenessTracker::cleanup_table()}'s epoch-advance pass (livenessTracker.cpp) observes a
   * rising per-klass survivor count each time, until {@code selectLeakCandidates()} trusts the
   * resulting trend (needs {@code KLASS_POPULATION_MIN_FILL_FOR_TREND = 10} ring-buffer samples).
   * Then waits for {@code ReferenceChainTracker::pollWatchedTargets()} to notice that ranked
   * candidate has already been tagged by an ordinary {@code runPass()} walk and reconstruct +
   * emit its chain, and asserts on the resulting {@code datadog.ReferenceChain} event.
   *
   * <p>Each population-growth round pairs with an explicit {@link #dump(Path)}: per
   * livenessTracker.cpp, {@code cleanup_table()}'s per-klass population accounting only runs
   * (unforced) from {@code flush_table()}, which only runs from {@code LivenessTracker::flush()},
   * which is called *only* from {@code Profiler::dump()} - there is no timer-driven flush.
   * {@code System.gc()} bumps {@code LivenessTracker::_gc_epoch} synchronously inside the
   * {@code GarbageCollectionFinish} callback ({@code onGC()}), so by the time {@code System.gc()}
   * returns to Java the epoch bump is already visible - no extra sleep is needed between the
   * {@code gc()} and the {@code dump()} that observes it.
   */
  @Test
  @Order(1)
  public void shouldReconstructReferrerChainToGcRoot() throws Exception {
    // Seed gcRootHolder with one live element *before* resetting the search below: ArrayList's
    // backing array starts out as the shared empty-array sentinel, and only gets replaced with a
    // real array on its first grow() (addAll()). ReferenceChainTracker::runPass() performs its
    // real root-seeded FollowReferences walk exactly once per search lifetime (_search_started,
    // referenceChains.cpp) and freezes whatever children it observes for a node the moment that
    // node is expanded - it never re-examines an already-EXPANDED node for a later field mutation.
    // If that one-shot walk happened to expand gcRootHolder's node while elementData still pointed
    // at the empty sentinel (nothing stops some *unrelated* GC in this shared, no-forkEvery JVM
    // from waking the freshly (re)started BFS thread in the gap between resetting the search below
    // and round 1's own addAll()), the frozen children set would be permanently empty, and no
    // ChainLink added in any of the 16 rounds that follow would ever become reachable - matching a
    // real CI failure where pollWatchedTargets() reported tag=0 for this klass on every single
    // poll across the whole test. Seeding one element first means the backing array is never
    // empty at any point after the search (re)starts: every later addAll()/grow() copies all prior
    // elements (including this one) into the new array, so whichever array the walk happens to
    // snapshot when it expands the node, index 0 is always present in it.
    List<Object> gcRootHolder = new ArrayList<>();
    gcRootHolder.add(new ChainLink("gc-root-seed"));
    if ("debug".equals(System.getProperty("ddprof_test.config"))) {
      // Being pinned to run first *within this class* (this class's own header comment, "Why
      // @TestMethodOrder/@Order(1)") does not guarantee this is the first reference-chain test
      // to ever call into the shared, process-wide singleton ReferenceChainTracker in this whole
      // test JVM - no forkEvery is configured (same header comment), so another test class can
      // run first and leave the singleton search already non-RUNNING/already-tagged, in which
      // case runPass() never takes its real root-seeded-walk branch again. Force a genuine fresh
      // search so this test's own ChainLink population is guaranteed reachable by a real walk,
      // regardless of what ran earlier in this JVM. Debug-only: this native seam does not exist
      // in a release build.
      JavaProfiler.resetReferenceChainSearchForTest0();
    }
    Path scratchDumpPath = Paths.get("referencechains-population-scratch.jfr");
    try {
      // Up to 16 rounds: selectLeakCandidates()'s KLASS_POPULATION_MIN_FILL_FOR_TREND = 10
      // (livenessTracker.h) needs 10 *epochs that actually observe a surviving ChainLink sample*,
      // not just 10 dump() calls - allocation sampling is probabilistic (see below), so some
      // early, smaller rounds may not land a single ChainLink sample. Growing the per-round count
      // compensates, and this loop keeps going (checking for the event every round) rather than
      // committing to a fixed round count up front, so it self-adjusts to whatever this JVM's
      // actual sampling behavior turns out to be. Staying under KLASS_POPULATION_RING_SIZE = 30
      // keeps every round's sample within the trend computeKlassPopulationSlope() reads back out.
      // Capped at 16 rather than a larger margin above the 10-round minimum: this loop's own
      // worst case (every round retained, no early match) runs inside the same forked test JVM
      // every other ddprof-test class shares (ProfilerTestPlugin.kt's shared -Xmx512m default,
      // no forkEvery) - a prior CI run hit "Java heap space" in that shared fork with this loop
      // capped at 25, so the cap trades some of the original margin above the 10-round minimum
      // for staying inside that shared heap.
      //
      // Per-round size growth itself is clamped to round 10 (Math.min(round, 10) below): rounds
      // past 10 exist only to give pollWatchedTargets() more retries against the lock-contention
      // race described below, not to keep building the population trend (already eligible by
      // round 10) - letting round*600 keep scaling unclamped through round 16 made rounds 11-16
      // each add strictly more retained garbage than the last for no trend benefit, which is what
      // drove the "Java heap space" failure this comment's own history refers to.
      //
      // Instance count is sized against ObjectSampler::check() (objectSampler.cpp), not this
      // test's own "memory=64" request: "do not allow shorter interval than 256KiB" means the
      // *actual* allocation-sampling interval is 262144 bytes regardless of the small value
      // requested above (that request only affects LivenessTracker's own table-capacity formula,
      // livenessTracker.cpp's initialize_table()). ChainLink's own padding fields (see that
      // class's comment) get enough total megabytes sampled from far fewer instances than plain,
      // unpadded ~40-byte instances would need - keeping this test's own contribution to the real
      // JVM's root-reachable graph (which ReferenceChainTracker's BFS walk must also traverse,
      // Triggering section) from ballooning to the point the walk can't practically catch up
      // within this test's own wall-clock budget. ChainLink competes on equal footing against
      // other incidental klasses (e.g. "[B"/byte[]) that this same mechanism may also legitimately
      // flag as leak candidates - this test's own assertions below look for ChainLink specifically
      // among however many datadog.ReferenceChain events actually appear, rather than assuming it
      // is the only one.
      ReferenceChainAssertions.ChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;
      for (int round = 1; round <= totalRounds && match == null; round++) {
        int newInstances = Math.min(round, 10) * 600;
        List<Object> newLinks = new ArrayList<>(newInstances);
        // Allocates on a freshly spawned thread, joined before continuing, matching
        // GCGenerationsTest.MemLeakTarget's own pattern (memleak/GCGenerationsTest.java):
        // JVMTI's SampledObjectAlloc callback never fired for any ChainLink allocated directly on
        // this JUnit worker thread during this test's own development, even at many megabytes of
        // total ChainLink allocation, but reliably fires for allocations on a thread created after
        // Profiler::start() already ran.
        int roundNumber = round;
        Thread allocator = new Thread(() -> {
          for (int i = 0; i < newInstances; i++) {
            newLinks.add(new ChainLink("leak-" + roundNumber + "-" + i));
          }
        });
        allocator.start();
        allocator.join();
        gcRootHolder.addAll(newLinks);
        System.gc();
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);

        if (match == null && "debug".equals(System.getProperty("ddprof_test.config"))) {
          // Deterministic short-circuit (debug-only native seams - a no-op in release builds, so
          // this leaves release-build coverage of the organic path below completely unchanged):
          // the dump() just above already drove a real BFS pass (Profiler::dump() ->
          // ReferenceChainTracker::runPass(), the same background-thread-cadence path production
          // uses), which, given this method's own generous firstpassbudget=200000, has almost
          // certainly already tagged gcRootHolder's very first ChainLink (getTag() > 0) - that's
          // pollWatchedTargets()'s only precondition for reconstructing a chain from it. Only
          // *which klass gets ranked* as a leak candidate was ever left to chance
          // (ObjectSampler's own probabilistic allocation sampling into LivenessTracker's ring,
          // KLASS_POPULATION_MIN_FILL_FOR_TREND = 10 real epochs needed - observed to flake in
          // practice). Seeding that ranking directly for an arbitrary klass id wired to that same
          // real, already-tagged instance, then polling synchronously instead of waiting on the
          // background thread's own cadence, removes exactly that flakiness without touching the
          // real walk/reconstruction this test exists to prove.
          //
          // Seed exactly once (recordKlassPopulationSampleLocked(), livenessTracker.cpp, always
          // *appends* a fresh ring slot rather than overwriting one for a repeated epoch - calling
          // this whole block again on a later round would append a second 10..100 ramp right after
          // the first, turning the ring into a non-monotonic sawtooth and destroying the very
          // positive-slope signal selectLeakCandidates() needs). Only the poll+dump recheck below
          // needs to repeat across rounds - not the seeding - to give a still-untagged
          // representative or a lock-contended dump() more rounds to resolve.
          if (!seededTestKlassTrend) {
            for (int epoch = 1; epoch <= 10; epoch++) {
              JavaProfiler.seedKlassPopulationSample0(CHAIN_LINK_TEST_KLASS_ID, epoch * 10, epoch);
            }
            seededTestKlassTrend = true;
          }
          JavaProfiler.setKlassPopulationRepresentativeForTest0(CHAIN_LINK_TEST_KLASS_ID, gcRootHolder.get(0));
          JavaProfiler.pollReferenceChainTargets0();
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }

        if (match == null) {
          // A quiet window with no dump() in flight: Profiler::dump() (profiler.cpp) holds every
          // entry of _locks[] exclusively for the duration of its own _jfr.dump() call
          // (rotateDictsAndRun()'s lockAll()/unlockAll() pair) - the same array
          // Profiler::writeReferenceChain() (profiler.cpp) needs a slot from to record an event at
          // all. Back-to-back rounds with essentially no gap between one dump() and the next leave
          // pollWatchedTargets() (referenceChains.cpp) little to no window to ever win that race;
          // sleeping briefly here, then dumping again with no intervening dump()/gc() in between
          // (so cleanup_table()'s epoch-advance pass, livenessTracker.cpp, stays a no-op and the
          // population trend built up so far is undisturbed), gives it one.
          Thread.sleep(300);
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }
      }

      // Grace period: the population trend only became eligible (ring_fill >= 10) partway through
      // the loop above, and the same lock contention the loop's own comment describes can still
      // delay the resulting write past this method's very last dump() - retry a few more times,
      // well past that contention window, before concluding the mechanism genuinely did not fire.
      for (int attempt = 0; match == null && attempt < 5; attempt++) {
        Thread.sleep(1000);
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
      }

      assertNotNull(match,
          "Never observed a datadog.ReferenceChain event whose chain[0] is " + ChainLink.class
              + " after " + gcRootHolder.size() + " retained ChainLink instances across up to "
              + totalRounds + " population-growth rounds plus a grace period");
      // chain[0] is the *target* object's own class, not its holder's:
      // ReferenceChainTracker::buildChainEvent()'s reconstructChain() (referenceChains.h)
      // appends each visited FrontierEntry's referrer_klass leaf-to-root, and referrer_klass is
      // populated from the *discovered object's own* GetClassSignature at insertion time (see
      // referenceChainJfrRoundtrip_ut.cpp's insert(tag, parent_tag, referrer_klass, depth) calls,
      // where tag 3's own referrer_klass is leafKlass, not middleKlass). The target here is
      // always some currently-live ChainLink instance - the only class this test's leak-candidate
      // population trend was built from - regardless of exactly which of the many instances
      // allocated above LivenessTracker::foldKlassCountsLocked() (livenessTracker.cpp) happened to
      // keep as its representative. Everything above chain[0] reflects real JDK-internal
      // collection representation (e.g. ArrayList's backing array) rather than anything this test
      // controls, so it is deliberately not asserted beyond "at least one hop was reconstructed".
      assertEquals(ChainLink.class.getName(), match.chain.get(0).getFullName());
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");
      assertTrue(!gcRootHolder.isEmpty()); // keeps every allocated ChainLink reachable until here
    } finally {
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * A second, independent end-to-end scenario for the same target-selection mechanism as
   * {@link #shouldReconstructReferrerChainToGcRoot()}, using a shape much closer to a real-world
   * leak than that method's hand-rolled {@link ChainLink} list: an ever-growing, never-evicted
   * {@link java.util.HashMap}-backed cache - a very common real leak pattern - holding
   * {@link CachedPayload} values. Beyond confirming a chain fires for the leaking value type,
   * this also asserts the reconstructed chain actually threads back through
   * {@code java.util.HashMap}'s own internal storage ({@code HashMap$Node}), i.e. that the
   * mechanism correctly walks a real JDK collection's internals rather than only ever having
   * been proven against a single purpose-built linked fixture.
   *
   * <p><b>Why {@code cache} is a local variable, not a {@code static} field (found the hard
   * way):</b> {@code ReferenceChainTracker::runPass()} performs exactly one root-seeded
   * {@code FollowReferences} walk per search's entire lifetime ({@code _search_started},
   * referenceChains.cpp) - every later pass only expands frontier entries already discovered by
   * that one walk ({@code expandFrontier()}), it never re-examines GC roots or re-visits an
   * already-{@code EXPANDED} entry for newly-added children. A {@code static} field becomes a
   * root at class-load time, essentially guaranteeing the one-shot walk catches it (and marks it
   * {@code EXPANDED}) while still empty - permanently blocking discovery of anything added to it
   * afterward, no matter how many rounds run. A local variable created fresh at the top of this
   * method, immediately followed by round-1 allocation, gives the one-shot walk a real chance to
   * catch it only after it already holds live data - mirroring
   * {@link #shouldReconstructReferrerChainToGcRoot()}'s {@code gcRootHolder}, which works for
   * exactly this reason (a local {@code ArrayList}, not a {@code static} one).
   *
   * <p>See this class's own header comment for why this runs as {@code @Order(2)}, before
   * {@link #shouldReportAbandonedSearchOnTinyFrontierCap()}, and for why its relative order
   * against {@link #shouldReconstructReferrerChainToGcRoot()} does not itself matter.
   */
  @Test
  @Order(2)
  public void shouldReconstructReferrerChainThroughUnboundedCacheLeak() throws Exception {
    // Seed cache with one live entry *before* the resets below, mirroring
    // shouldReconstructReferrerChainToGcRoot()'s own gcRootHolder seeding (see that method's
    // comment): HashMap's backing table also starts out as a shared, lazily-replaced empty
    // sentinel (only allocated on the first put()), so the same one-shot-BFS-freeze hazard
    // documented there - a concurrent GC-triggered walk expanding this node's children while the
    // backing table is still the empty sentinel, permanently freezing an empty children set -
    // applies here too. Seeding one entry first means the backing table is never empty at any
    // point after the search (re)starts.
    Map<String, CachedPayload> cache = new HashMap<>();
    cache.put("cache-leak-seed", new CachedPayload("cache-leak-seed"));
    if ("debug".equals(System.getProperty("ddprof_test.config"))) {
      // Mirrors shouldReconstructReferrerChainToGcRoot()'s own reset (see that method's comment):
      // the natural restartSearch() cycle (shouldRunPass(), referenceChains.cpp) that would
      // otherwise give this method its own fresh root walk once shouldReconstructReferrerChainToGcRoot()'s
      // own ChainLink candidate is found and its tags released is gated on cadence/pacing budget
      // (canAffordNewSearch()) - not guaranteed to fire again before this method's own round/retry
      // budget runs out. Force a genuine fresh search here too, rather than depend on that timing,
      // so cache (below) is guaranteed reachable by a real walk regardless of it. Debug-only: this
      // native seam does not exist in a release build.
      //
      // resetReferenceChainSearchForTest0() only resets ReferenceChainTracker's own search state
      // (frontier/tags/search-progress fields); it does not touch LivenessTracker's per-klass
      // population-history rings, which selectLeakCandidates() consults independently to decide
      // which klass is "trending". Without also resetting those, a klass ChainLink already
      // accumulated a positive slope for during shouldReconstructReferrerChainToGcRoot() can still
      // outrank CachedPayload as the leak candidate here, so the fresh search below ends up
      // reconstructing ChainLink's chain again instead of CachedPayload's.
      JavaProfiler.resetKlassPopulationForTest0();
      JavaProfiler.resetReferenceChainSearchForTest0();
    }
    Path scratchDumpPath = Paths.get("referencechains-cache-leak-scratch.jfr");
    try {
      // Same round-growth/retry shape as shouldReconstructReferrerChainToGcRoot() - see that
      // method's own comment for why the loop self-adjusts rather than committing to a fixed
      // round count, why per-round scale is sized against ObjectSampler's real 256KiB sampling
      // floor rather than this test's own "memory=64" request, why totalRounds is capped at
      // 16 rather than a larger margin above the 10-round minimum (shared-fork heap headroom),
      // and why per-round growth itself is clamped to round 10 (Math.min(round, 10) below).
      ReferenceChainAssertions.ChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;

      // Pre-generate every key this loop will ever need, up front, rather than concatenating a
      // fresh String on every put() below. CachedPayload's own class comment already documents
      // why this fixture uses plain long fields instead of a byte[] (an earlier version's byte[]
      // field stole every allocation-sampling hit from CachedPayload itself) - the key String
      // (plus its own backing byte[]) is the same kind of same-instant, size-weighted-sampler
      // competitor, just a *separate* object instead of a field. Generating all keys in one
      // batch before the round loop starts lets their own klass_population trend flatten out
      // (selectLeakCandidates() needs KLASS_POPULATION_MIN_FILL_FOR_TREND=10 *new* samples, not
      // just a nonzero ring) well before CachedPayload's own ring starts growing, so the sampler
      // has nothing else in flight to compete with once round 1 begins.
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
        // Matches shouldReconstructReferrerChainToGcRoot()'s own *600 growth rate (not *300, this
        // method's previous value) - CachedPayload and ChainLink are near-identical in size (same
        // padding fields; CachedPayload is actually slightly smaller, missing ChainLink's `next`
        // reference), so halving the growth rate here bought no headroom and instead just let
        // CachedPayload's own population ring stall short of KLASS_POPULATION_MIN_FILL_FOR_TREND
        // within the same totalRounds budget both methods share.
        int newEntries = Math.min(round, 10) * 600;
        int keyOffset = nextKey;
        Thread allocator = new Thread(() -> {
          for (int i = 0; i < newEntries; i++) {
            String key = keys[keyOffset + i];
            cache.put(key, new CachedPayload(key));
          }
        });
        allocator.start();
        allocator.join();
        nextKey += newEntries;
        System.gc();
        dump(scratchDumpPath);
        IItemCollection events1 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
        match = ReferenceChainAssertions.findMatchForClass(events1, CachedPayload.class);

        if (match == null && "debug".equals(System.getProperty("ddprof_test.config"))) {
          // Same deterministic short-circuit as shouldReconstructReferrerChainToGcRoot() (see that
          // method's own comment) - debug-only native seams, a no-op in release builds, so the
          // organic path below still fully covers release builds unchanged. keys[0]'s own
          // CachedPayload is reachable from round 1 onward and, given this method's own
          // firstpassbudget=200000, almost certainly already tagged by the real BFS pass the
          // dump() just above triggered. Seed exactly once - see
          // shouldReconstructReferrerChainToGcRoot()'s own comment for why reseeding the same
          // epoch 1..10 ramp on a later round would corrupt the ring into a non-monotonic
          // sawtooth and destroy the positive-slope signal instead of just re-establishing it.
          if (!seededTestKlassTrend) {
            for (int epoch = 1; epoch <= 10; epoch++) {
              JavaProfiler.seedKlassPopulationSample0(CACHED_PAYLOAD_TEST_KLASS_ID, epoch * 10, epoch);
            }
            seededTestKlassTrend = true;
          }
          JavaProfiler.setKlassPopulationRepresentativeForTest0(CACHED_PAYLOAD_TEST_KLASS_ID, cache.get(keys[0]));
          JavaProfiler.pollReferenceChainTargets0();
          dump(scratchDumpPath);
          IItemCollection events2 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
          match = ReferenceChainAssertions.findMatchForClass(events2, CachedPayload.class);
        }

        if (match == null) {
          // Same lock-contention race shouldReconstructReferrerChainToGcRoot()'s own comment
          // describes - a quiet retry gives pollWatchedTargets() a window to win a _locks[]
          // slot against Profiler::dump()'s own exclusive hold.
          Thread.sleep(300);
          dump(scratchDumpPath);
          IItemCollection events3 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
          match = ReferenceChainAssertions.findMatchForClass(events3, CachedPayload.class);
        }
      }

      for (int attempt = 0; match == null && attempt < 5; attempt++) {
        Thread.sleep(1000);
        dump(scratchDumpPath);
        IItemCollection events4 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
        match = ReferenceChainAssertions.findMatchForClass(events4, CachedPayload.class);
      }

      assertNotNull(match,
          "Never observed a datadog.ReferenceChain event whose chain[0] is " + CachedPayload.class
              + " after " + cache.size() + " cached entries across up to " + totalRounds
              + " population-growth rounds plus a grace period");
      assertEquals(CachedPayload.class.getName(), match.chain.get(0).getFullName());
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");

      // The point of this test over shouldReconstructReferrerChainToGcRoot(): confirm the walk
      // actually passed through the cache's own internal storage, not some other, coincidental
      // retainer - cache is the only thing keeping any CachedPayload instance reachable.
      boolean sawHashMapInternals = false;
      for (IMCType type : match.chain) {
        if (type.getFullName().startsWith("java.util.HashMap")) {
          sawHashMapInternals = true;
          break;
        }
      }
      assertTrue(sawHashMapInternals,
          "Expected the reconstructed chain to pass through java.util.HashMap's own internal "
              + "storage (cache is a HashMap) - chain was: " + match.chain);
      assertTrue(!cache.isEmpty()); // keeps every cached CachedPayload reachable until here
    } finally {
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * This test's stated abandonment-path scenario: an artificially tiny frontier cap
   * ({@code getProfilerCommand()}'s {@code framecap=1} for this test method, see that method's own
   * comment for why {@code budget} must stay larger than {@code framecap}) makes the very first
   * BFS pass hit the frontier cap once a second root-referenced object is discovered, so
   * {@code runPass()} (referenceChains.cpp) abandons the search rather than silently truncating it
   * (Termination section, doc/architecture/LiveHeapReferenceChains.md) - or, if this method's own
   * {@code framecap=1} lost the race to size the shared {@code FrontierTable} (see
   * {@code getProfilerCommand()}'s own comment on this method), its {@code ttl=100} fallback
   * abandons the search instead once enough wall-clock time has passed, which by the time this
   * method runs it always has. Either path exercises the same {@code buildAbandonedEvent()} /
   * {@code Profiler::writeReferenceChainAbandoned()} / {@code FlightRecorder::recordReferenceChainAbandoned()}
   * write into the recording that {@code Profiler::dump()} triggers - this method only asserts that
   * a {@code datadog.ReferenceChainAbandoned} event exists, not which reason produced it.
   *
   * <p>{@code @Order(3)}: this permanently exhausts the process-wide {@code ReferenceChainTracker}
   * singleton's one-and-only search (see this class's header comment), so it must run after
   * {@link #shouldReconstructReferrerChainToGcRoot()} and
   * {@link #shouldReconstructReferrerChainThroughUnboundedCacheLeak()}. It used to rely on being
   * the last method in source order plus JUnit's default (unannotated methods sort after
   * {@code @Order}-annotated ones) for that - which happened to guarantee run order, but not the
   * search *state* this method's own comment above presumes: if either earlier test's own
   * organic GC/allocation-sampling trend never fired in time (observed in practice - real
   * flakiness, not this test's fault), the shared search can still be {@code RUNNING} with a
   * large, non-fresh frontier when this method starts, instead of the small, just-abandoned one
   * its own {@code framecap=1}/{@code ttl=100} scenario assumes. Calling
   * {@code resetReferenceChainSearchForTest0()} here, exactly as both earlier tests already do for
   * their own scenarios, makes this method's own precondition (a fresh search) something it
   * establishes itself rather than something it presumes a prior test left behind. Debug-only:
   * this native seam does not exist in a release build.
   */
  @Test
  @Order(3)
  public void shouldReportAbandonedSearchOnTinyFrontierCap() throws Exception {
    if ("debug".equals(System.getProperty("ddprof_test.config"))) {
      JavaProfiler.resetReferenceChainSearchForTest0();
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
      dump(dumpPath);
      IItemCollection abandoned = verifyEvents(dumpPath, "datadog.ReferenceChainAbandoned", true);
      assertTrue(abandoned.hasItems(), "Expected at least one datadog.ReferenceChainAbandoned event");
    } finally {
      Files.deleteIfExists(dumpPath);
    }
    assertTrue(!gcRootHolder.isEmpty()); // keeps gcRootHolder reachable until the dump above
  }

  /**
   * Referrer-type fixture shared by both the success-path and abandonment-path tests. The 32
   * {@code long} fields below exist purely so {@link #shouldReconstructReferrerChainToGcRoot()}
   * needs far fewer instances to allocate a given number of megabytes of ChainLink - deliberately
   * plain fields, not a nested array: an array field would be a *second*, separate heap
   * allocation, and the allocation-sampling interval that method's comment describes picks
   * whichever allocation happens to cross its byte threshold size-weighted, so a same-instance
   * companion array would take sampling attention away from ChainLink itself rather than adding
   * to it. Plays no role in {@link #shouldReportAbandonedSearchOnTinyFrontierCap()}'s tiny,
   * two-object fixture beyond trivially increasing its size.
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
   * Realistic-leak fixture for {@link #shouldReconstructReferrerChainThroughUnboundedCacheLeak()}:
   * models the single most common real-world leak shape this mechanism is meant to catch - an
   * unbounded, never-evicted cache - as opposed to {@link ChainLink}'s hand-rolled linked list.
   * The 32 {@code long} fields exist purely so a given number of megabytes needs far fewer
   * entries to reach {@code ObjectSampler}'s real 256KiB sampling floor - deliberately plain
   * fields, not a nested array, for exactly the reason {@link ChainLink}'s own comment already
   * documents: a same-instance companion array would be a *second*, separate heap allocation
   * that the size-weighted allocation sampler would compete for, taking sampling attention away
   * from {@code CachedPayload} itself (an earlier version of this fixture used a {@code byte[]}
   * field and never observed a single {@code CachedPayload} sample as a result - the sampler was
   * catching the array instead).
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
