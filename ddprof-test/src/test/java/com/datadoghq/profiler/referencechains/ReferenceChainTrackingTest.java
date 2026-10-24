/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.AbstractProfilerTest;
import com.datadoghq.profiler.JfrEvent;
import com.datadoghq.profiler.JfrEvents;
import com.datadoghq.profiler.Platform;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.junit.jupiter.api.MethodOrderer;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestMethodOrder;

import java.nio.file.Files;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.AtomicReference;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * PROF-15341 (+ lifecycle-wiring follow-up): end-to-end coverage for
 * {@code ReferenceChainTracker} (ddprof-lib/src/main/cpp/referenceChains.h/.cpp).
 *
 * <p>{@code ReferenceChainTracker::start()} is called from {@code Profiler::start()}, gated on
 * {@code args._reference_chains}, followed by {@code startThread()} which spawns its BFS thread;
 * {@code Profiler::stop()} calls the matching {@code stopThread()}/{@code stop()} pair. A
 * {@code datadog.ReferenceChainAbandoned} event reaches a live {@code Recording}: {@code
 * Profiler::dump()} calls {@code buildAbandonedEvent()} and writes its output whenever the search
 * ended in {@code SearchState::ABANDONED} - mirroring {@code LivenessTracker::flush()}'s call site
 * there. {@link #shouldReportAbandonedSearchOnTinyFrontierCap()} exercises that path end-to-end.
 *
 * <p><b>Target-selection bridging:</b> {@code pollWatchedTargets()} (referenceChains.cpp), called
 * from {@code threadLoop()} once per scheduling cycle after {@code runPass()}, polls
 * {@code LivenessTracker::selectLeakCandidates()} (positive population-slope ranking over a
 * rolling per-klass survivor-count window, gated on {@code _gc_generations}) and, for each ranked
 * klass whose representative instance an ordinary {@code runPass()} walk has *already* tagged
 * ({@code getTag() > 0} - a read, never a {@code SetTag} seed), reconstructs and emits its chain
 * via {@code Profiler::writeReferenceChain()}. {@link #shouldReconstructReferrerChainToGcRoot()}
 * exercises this end to end against a real JVM, real GCs, and a real JVMTI heap walk - the
 * synthetic-frontier reconstruction-correctness proof lives in
 * {@code referenceChainJfrRoundtrip_ut.cpp}/{@code ReferenceChainJfrParserTest}.
 *
 * <p><b>Why {@code @TestMethodOrder}/{@code @Order(1)}:</b> {@code ReferenceChainTracker} is a
 * process-wide singleton whose single search never restarts once it leaves
 * {@code SearchState::RUNNING} - {@code shouldRunPass()} returns {@code false} forever after that
 * point, and the transition releases every tag the search ever assigned. Its {@code FrontierTable}
 * is sized once, the first time any test in this JVM calls {@code ReferenceChainTracker::start()}
 * (the {@code if (_frontier == nullptr)} guard), and never resized on later start()/stop() cycles
 * - so whichever test runs first also fixes that capacity for every test after it (no
 * {@code forkEvery} configured, so this whole class runs in one JVM). The abandonment test
 * deliberately drives that shared search to {@code ABANDONED}; both success-path tests need it
 * still {@code RUNNING} to find their own candidates' tags non-zero, so they are pinned first via
 * {@code @Order(1)}/{@code @Order(2)}. Their relative order between themselves does not matter -
 * they target different klasses within the same shared search and neither exhausts it - only
 * both running before the abandonment test does.
 */
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@Tag("slow")
public class ReferenceChainTrackingTest extends AbstractProfilerTest {

  // Arbitrary, test-chosen klass ids for the debug-only population-seeding seams below -
  // LivenessTracker's population table treats them as opaque keys. Distinct per test purely as
  // cheap insurance against collision in a shared, no-forkEvery test JVM.
  private static final int CHAIN_LINK_TEST_KLASS_ID = 987201;
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987202;

  // Durable (static-field) holder for the gc-root fixture below. The discovered-chain gate
  // suppresses chains shallower than the first real holder hop that are rooted at a TRANSIENT
  // root (stack/JNI local) - a frame-held "leak" is by definition not a leak - and the ChainLink
  // instances sit at depth 1 of a locally-held list, exactly that shape. A static field gives
  // them the real unmaintained-singleton-collection retention shape instead. (The cache fixture
  // needs no such change: CachedPayload chains are three hops deep through HashMap's own
  // internals, which the gate lets through regardless of root kind.) Cleared in the test's
  // finally - a leftover holder would keep its entire population reachable for every later test
  // in this shared JVM.
  private static List<Object> gcRootHolder;

  // The current round's allocation batch, handed to the persistent allocator thread below.
  // Volatile: written here, read by the allocator thread every round - the request queue's
  // happens-before already covers it, but the visibility of a plain field handed across threads
  // is kept explicit rather than relying on queue semantics alone.
  private static volatile List<Object> currentBatch;

  // LivenessTracker's hysteresis gate (KLASS_POPULATION_MIN_FILL_FOR_TREND=10 /
  // LEAK_TREND_HYSTERESIS_BASE=5) only starts incrementing consecutive_positive once ring_fill
  // has reached 10 - every call before that resets it back to 0. A single batch of 10 seed
  // calls therefore caps consecutive_positive at 1, far short of the >=5 that
  // selectLeakCandidates() requires. 10 + 5 - 1 = 14 calls is the minimum for the 5 qualifying
  // calls at ring_fill>=10 (epochs 10-14) to land; +1 for margin against off-by-one uncertainty
  // in that derivation.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  // Dedicated id for shouldReportAbandonedSearchOnTinyFrontierCap()'s own seeding (see that
  // method's own comment) - distinct from CHAIN_LINK_TEST_KLASS_ID/CACHED_PAYLOAD_TEST_KLASS_ID
  // for the same cheap-insurance-against-collision reason those two are distinct from each other.
  private static final int ABANDON_TEST_KLASS_ID = 987203;

  /**
   * The {@code datadog.ReferenceChain} ActiveSetting's {@code id} (flightRecorder.cpp's
   * T_REFERENCE_CHAIN). ActiveSetting events from cpu/wall/memory/nativemem also read
   * "enabled"="true", so the id is the only unambiguous discriminator.
   */
  private static final long REFERENCE_CHAIN_EVENT_ID = 129;

  // Upper bound on any single main-thread wait for the persistent allocator thread: a
  // dead/stuck allocator must fail the test, not hang the shared test fork.
  private static final long ALLOCATOR_HANDOFF_TIMEOUT_MS = 30_000;

  @Override
  protected String getProfilerCommand() {
    String testName = testInfo != null
        ? testInfo.getTestMethod().map(java.lang.reflect.Method::getName).orElse("")
        : "";
    if ("shouldReconstructReferrerChainToGcRoot".equals(testName)
        || "shouldReconstructReferrerChainThroughUnboundedCacheLeak".equals(testName)) {
      // generations=true + a small sampling interval: pollWatchedTargets() does nothing without
      // LivenessTracker::gcGenerationsEnabled(), and the small interval maximizes the chance the
      // ChainLink instances allocated below actually get liveness-tracked. A large framecap avoids
      // an early FRONTIER_CAP abandonment against this JVM's real, not-controlled-by-this-test
      // root-reachable graph, and a long ttl avoids a TTL abandonment mid-test - either would call
      // releaseSearchTags() and permanently zero every tag this test depends on.
      //
      // pausetarget=5000: the pacing controller measures this JVM's real FollowReferences call
      // latency at ~150ms early on, climbing past a full second as this test's own allocation
      // keeps handing the search more to discover (each pass re-scans the whole already-discovered
      // set, so cost grows with cumulative progress, not with this test's allocation rate). Against
      // the default 5ms ceiling every observed pass is "over ceiling even at the floor", so the
      // controller settles at MIN_EFFECTIVE_BUDGET=50 edges/pass and 4s between passes - a real but
      // glacial rate this test's wall-clock budget cannot outwait, and one a merely-generous
      // ceiling (e.g. 500ms) only postpones: once cumulative progress pushes the real per-pass cost
      // past *that* ceiling too, the same throttling recurs. A ceiling comfortably above the
      // highest per-call cost this test's population growth is expected to reach lets the
      // controller keep the configured budget=4000 for the whole run.
      //
      // painbudget=100: the cache-leak test shares this singleton search and needs a restart once
      // the first search reaches a terminal state. PainBudget gates that restart on a cooldown of
      // pain_spent_ms / refill_rate; the default 1% refill can stretch that to minutes for a
      // search this large - far past this test's bounded retry loop. Nothing else in this JVM
      // competes for the pain budget, so keep the gate affordable immediately.
      //
      // firstpassbudget=200000: root/stack-ref enumeration shares budget=4000 with expandFrontier()
      // unless overridden - and in this JVM's real root-reachable graph that left this method's own
      // cache HashMap (a direct stack-local root) at the mercy of whatever order JVMTI enumerates
      // roots in: budget=4000 was observed exhausting itself on other roots' subtrees every single
      // attempt, never once admitting a single edge from this thread's own stack. Overriding just
      // root enumeration's budget gives every enumeration attempt enough headroom to reach this
      // thread's stack without slowing the steady-state expansion passes that follow.
      // memory=64:l:1.0 - the explicit 100% live-sample ratio is load-bearing: without a ratio
      // segment the default is 10% and LivenessTracker::track() drops 90% of tracked instances
      // probabilistically, thinning the pool the representative-minting and candidate trend rings
      // draw from - observed live as intermittent "representative died/evicted" and zero-tag runs.
      // Total tracking volume is still capped by the 256KiB sampling-interval floor, not the
      // ratio, so 100% keeps the tracking table tiny.
      return "memory=64:l:1.0,generations=true,"
          + "referencechains=true:hops=64:budget=4000:ttl=120000:framecap=2000000:pausetarget=5000:painbudget=100:firstpassbudget=200000";
    }
    // shouldReportAbandonedSearchOnTinyFrontierCap needs the frontier table (not the per-pass
    // budget) to run out first: heapReferenceCallback() checks the budget before ever calling
    // FrontierTable::insert(), so a budget as small as the cap itself only exhausts the budget
    // after admitting exactly one object - insert() never gets a chance to fail. A budget
    // comfortably larger than framecap=1 lets a *second* root-referenced object reach insert()
    // and hit the actually-full table, which is what runPass() treats as grounds to abandon.
    //
    // framecap=1 only controls the table's capacity the *first* time start() constructs it in
    // this JVM (the `if (_frontier == nullptr)` guard - the table survives every later start()/
    // stop() cycle at whatever size it was first built with). The @Order(1) test's much larger
    // framecap=2000000 wins that race instead - so this command also supplies a small ttl as a
    // second, independent abandonment trigger. A fresh, genuinely-tiny table (this method running
    // first, e.g. in isolation) still abandons via FRONTIER_CAP; inheriting an already-oversized
    // table falls through to the ttl check, which fires almost immediately regardless of table
    // size because _search_start_ns is set once, the first time the shared search ever started.
    // Either path produces a datadog.ReferenceChainAbandoned event, which is all this method
    // asserts on.
    //
    // painbudget=100: this method's own resetReferenceChainSearchForTest0() spends whatever
    // _search_pain_ms the earlier long-running search left behind into *this* method's PainBudget
    // (restartSearch()/resetSearchStateForTest() both call _pain_budget.spend(_search_pain_ms)
    // unconditionally) - at the default 1% refill, draining that debt would take minutes.
    if ("shouldReportAbandonedSearchOnTinyFrontierCap".equals(testName)) {
      // memory=64:l:1.0 is load-bearing: Profiler::start() only starts the ReferenceChainTracker
      // when allocation sampling activated (activated & EM_ALLOC); a bare referencechains=... falls
      // back to cpu-only and never runs the search. No generations=true: LivenessTracker::initialize()
      // then clears _gc_generations, so hasLeakSignal() returns true without any population trend.
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
   * {@code datadog.ReferenceChain} JFR setting (flightRecorder.cpp:1143's
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
   * Allocates a growing population of {@link ChainLink} instances, forcing GCs between rounds so
   * LivenessTracker observes a rising per-klass survivor count each time, until
   * {@code selectLeakCandidates()} trusts the trend - then waits for {@code pollWatchedTargets()}
   * to notice that candidate has already been tagged by an ordinary walk and reconstruct + emit
   * its chain, asserting on the resulting {@code datadog.ReferenceChain} event.
   *
   * <p>Each round pairs with an explicit {@link #dump(Path)}: LivenessTracker's per-klass
   * population accounting only runs (unforced) from {@code flush_table()}, which only runs from
   * {@code LivenessTracker::flush()}, called *only* from {@code Profiler::dump()} - there is no
   * timer-driven flush. {@code System.gc()} bumps the GC epoch synchronously inside the
   * {@code GarbageCollectionFinish} callback, so it is already visible by the time {@code gc()}
   * returns - no sleep needed between the gc() and the dump() that observes it.
   */
  @Test
  @Order(1)
  public void shouldReconstructReferrerChainToGcRoot() throws Exception {
    // Per-run unique path, not a fixed name in the CWD: parallel workers or a shared checkout can
    // never read each other's recording, and an aborted run leaves nothing a later run inherits.
    // Created first - before any static holder, reset, or allocator thread - so an IOException here
    // leaks nothing; the placeholder is deleted so dump() creates the file itself.
    Path scratchDumpPath = Files.createTempFile("referencechains-population-scratch-", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    // Seed gcRootHolder with one live element *before* resetting the search below: ArrayList's
    // backing array starts as the shared empty-array sentinel and is only replaced on its first
    // grow(). expandFrontier() freezes whatever children it observes for a node the moment that
    // node is expanded - it never re-examines an already-EXPANDED node. If gcRootHolder's node
    // gets expanded while elementData still points at the empty sentinel (some unrelated GC can
    // wake the freshly restarted BFS thread in the gap between the reset and round 1's addAll()),
    // the frozen children set would be permanently empty and no ChainLink added later would ever
    // become reachable - matching a real CI failure where pollWatchedTargets() reported tag=0 for
    // this klass on every poll. Seeding one element first means the backing array is never empty
    // after the search (re)starts: every later grow() copies all prior elements into the new
    // array, so index 0 is always present in whichever array the walk snapshots.
    gcRootHolder = new ArrayList<>();
    gcRootHolder.add(new ChainLink("gc-root-seed"));
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // Being pinned first within this class does not make this the first reference-chain test in
      // the whole shared JVM - another test class can run first and leave the singleton search
      // already non-RUNNING/already-tagged, in which case runPass() never takes its real
      // root-seeded-walk branch again. Force a genuine fresh search so this test's ChainLink
      // population is guaranteed reachable by a real walk. Debug-only: the seam does not exist in
      // a release build.
      //
      // resetKlassPopulationForTest0() first: LivenessTracker's _klass_population table survives
      // stop()/start() cycles, so an earlier test class could leave a klass already past the
      // consecutive_positive hysteresis gate sitting in that table - letting this test's first
      // pass start for a reason unrelated to the seeding below, masking whether that seeding is
      // actually sufficient on its own.
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
      // One persistent allocator thread, reused by every round - NOT a fresh thread per round.
      // SampledObjectAlloc never fires for this JUnit worker thread's own allocations, but
      // reliably fires for threads created after Profiler::start() already ran; and per-tid, the
      // per-(klass, tid) qualification trend accumulates REAL samples for this one thread's tid
      // every round, so qualification is organic and cannot age out mid-test. Per-round spawns
      // gave every round a different short-lived tid, so the seeded ramp was the only qualifying
      // signal - and once its ring slots aged out the candidate dropped out of
      // selectLeakCandidates() with the whole crawl still unfinished.
      LinkedBlockingQueue<Integer> allocRequests = new LinkedBlockingQueue<>();
      Semaphore roundDone = new Semaphore(0);
      AtomicLong allocatorTid = new AtomicLong(-1);
      AtomicReference<Throwable> allocatorFailure = new AtomicReference<>();
      Thread allocator = new Thread(() -> {
        try {
          allocatorTid.set(ReferenceChainTestHooks.getTid());
          Integer requested;
          while ((requested = allocRequests.take()) != null) {
            List<Object> batch = currentBatch;
            for (int i = 0; i < requested; i++) {
              batch.add(new ChainLink("leak-" + requested + "-" + i));
            }
            roundDone.release();
          }
        } catch (InterruptedException e) {
          Thread.currentThread().interrupt(); // test shutdown - see finally below
        } catch (Throwable t) {
          allocatorFailure.set(t); // surfaced by awaitAllocatorTid()/awaitAllocatorRound()
        }
      }, "togcroot-leak-allocator");
      allocator.start();

    try {
      // The seeding block below needs the allocator's tid. Bounded and inside this try so a
      // dead/stuck allocator fails the test (and is still shut down by the finally) instead of
      // hanging the shared fork.
      awaitAllocatorTid(allocator, allocatorTid, allocatorFailure);
      // Up to 16 rounds: KLASS_POPULATION_MIN_FILL_FOR_TREND = 10 needs 10 *epochs that actually
      // observe a surviving ChainLink sample*, not just 10 dump() calls - allocation sampling is
      // probabilistic, so some early, smaller rounds may not land a single ChainLink sample.
      // Growing the per-round count compensates, and the loop keeps going (checking for the event
      // every round) rather than committing to a fixed round count. Staying under
      // KLASS_POPULATION_RING_SIZE = 30 keeps every round's sample within the trend window.
      // Capped at 16 rather than a larger margin: this loop's worst case runs inside the shared
      // forked test JVM every other ddprof-test class shares (-Xmx512m, no forkEvery) - a prior
      // CI run hit "Java heap space" with the cap at 25.
      //
      // Per-round growth is clamped to round 10: rounds past 10 exist only to give
      // pollWatchedTargets() more retries against the lock-contention race below, not to keep
      // building the population trend (already eligible by round 10) - unclamped rounds 11-16
      // each add strictly more retained garbage for no trend benefit.
      //
      // Instance count is sized against ObjectSampler::check(), not this test's "memory=64"
      // request: the *actual* sampling interval is 256KiB regardless of the small value requested
      // (that request only affects LivenessTracker's table-capacity formula). ChainLink's padding
      // fields get enough megabytes sampled from far fewer instances than plain ~40-byte
      // instances would need - keeping this test's contribution to the root-reachable graph (which
      // the BFS walk must also traverse) from ballooning past the walk's wall-clock budget.
      // ChainLink competes on equal footing against incidental klasses (e.g. byte[]) this same
      // mechanism may also flag - the assertions below look for ChainLink among however many
      // events actually appear, rather than assuming it is the only one.
      ReferenceChainAssertions.JfrChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;
      int roundsRun = 0;
      for (int round = 1; round <= totalRounds && match == null; round++) {
        roundsRun = round;
        int newInstances = Math.min(round, 10) * 600;
        List<Object> newLinks = new ArrayList<>(newInstances);
        currentBatch = newLinks; // published before the request - see the allocator's loop
        if (!allocRequests.offer(newInstances)) {
          throw new IllegalStateException(
              "allocRequests queue rejected instance count " + newInstances);
        }
        awaitAllocatorRound(roundDone, allocator, allocatorFailure);
        gcRootHolder.addAll(newLinks);
        System.gc();
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);

        if (match == null && ReferenceChainAssertions.isDebugInstrumentedBuild()) {
          // Debug-only native seams - a no-op in release builds, so release-build coverage of the
          // organic path below is unchanged.
          //
          // With generations=true, shouldRunPass() gates even the search's very first pass on
          // hasLeakSignal(), which falls through to selectLeakCandidates() requiring
          // consecutive_positive >= LEAK_TREND_HYSTERESIS_BASE for *some* klass (see
          // SEED_EPOCHS_FOR_HYSTERESIS's comment for why 10 seeded epochs alone cannot clear that
          // bar). Seeding SEED_EPOCHS_FOR_HYSTERESIS epochs clears it outright, which is what
          // authorizes the background BFS thread's next scheduled wake to run its real pass -
          // nothing before that point has tagged gcRootHolder's own ChainLink yet. The explicit
          // pollReferenceChainTargets0() right below is therefore best-effort: it only reconstructs
          // a chain once the representative's getTag() is actually > 0, which needs that background
          // pass to have already run. The retry loop below (sleep-then-dump fallback, repeated
          // across rounds) gives the now-unblocked background thread room to do that and have its
          // own post-pass poll pick the chain up on its own.
          //
          // Seed exactly once: recordKlassPopulationSampleLocked() always *appends* a fresh ring
          // slot rather than overwriting one for a repeated epoch - reseeding on a later round
          // would append a second ramp right after the first, turning the ring into a non-monotonic
          // sawtooth and destroying the positive-slope signal. Only the poll+dump recheck below
          // needs to repeat across rounds.
          // Representative BEFORE seeding: setKlassPopulationRepresentativeForTest0 resolves the
          // representative's real klass id and aliases the synthetic id to it, so the seeds below
          // land in the real population entry (candidate matching is real-id keyed since the
          // leak-tag pool redesign).
          ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(
              CHAIN_LINK_TEST_KLASS_ID, gcRootHolder.get(0));
          if (!seededTestKlassTrend) {
            // The persistent allocator thread owns every ChainLink allocation, so ITS tid is the
            // qualifying one. Seed counts scale as the organic ramp itself (+1 per epoch), NOT
            // some inflated multiple: hasQualifyingGrowth() takes the difference of third-window
            // means over the whole seed+real series, and seeds of epoch*10 dwarfing the real
            // ~1..15 counts made the slope go NEGATIVE (-20..-40 observed live, the "transition
            // cliff") the moment real samples displaced the seeded tail. With matched-scale seeds
            // every third-window pairing across the transition still yields a positive slope.
            int leakTid = (int) allocatorTid.get();
            for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
              ReferenceChainTestHooks.seedKlassPopulationSample0(
                  CHAIN_LINK_TEST_KLASS_ID, epoch, epoch);
              ReferenceChainTestHooks.seedTidTrendSample0(
                  CHAIN_LINK_TEST_KLASS_ID, leakTid, epoch, epoch);
            }
            seededTestKlassTrend = true;
          }
          ReferenceChainTestHooks.pollReferenceChainTargets0();
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }

        if (match == null) {
          // A quiet window with no dump() in flight: Profiler::dump() holds every entry of _locks[]
          // exclusively for its own _jfr.dump() call - the same array writeReferenceChain() needs a
          // slot from. Back-to-back rounds leave pollWatchedTargets() little to no window to win
          // that race; sleeping briefly here, then dumping again with no intervening gc() (so
          // cleanup_table()'s epoch-advance pass stays a no-op and the population trend is
          // undisturbed), gives it one.
          Thread.sleep(300);
          dump(scratchDumpPath);
          match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
        }
      }

      // Grace period: the trend only became eligible (ring_fill >= 10) partway through the loop
      // above, and the same lock contention can still delay the write past this method's last
      // dump() - retry a few more times before concluding the mechanism genuinely did not fire.
      for (int attempt = 0; match == null && attempt < 5; attempt++) {
        Thread.sleep(1000);
        dump(scratchDumpPath);
        match = ReferenceChainAssertions.findMatchForClass(verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false), ChainLink.class);
      }

      assertNotNull(match,
          "Never observed a datadog.ReferenceChain event whose chain[0] is " + ChainLink.class
              + " after " + gcRootHolder.size() + " retained ChainLink instances across up to "
              + totalRounds + " population-growth rounds plus a grace period"
              + (match == null ? referenceChainDiagnostics(gcRootHolder.get(0), roundsRun) : ""));
      // chain[0] is the *target* object's own class, not its holder's: reconstructChain() appends
      // each visited FrontierEntry's referrer_klass leaf-to-root, and referrer_klass is populated
      // from the *discovered object's own* GetClassSignature at insertion time. The target here is
      // always some currently-live ChainLink instance - the only class the leak-candidate trend
      // was built from - regardless of which instance the representative happens to be. Everything
      // above chain[0] reflects real JDK-internal collection representation rather than anything
      // this test controls, so it is deliberately not asserted beyond "at least one hop".
      assertEquals(ChainLink.class.getName(), match.chain.get(0));
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");
      assertTrue(!gcRootHolder.isEmpty()); // keeps every allocated ChainLink reachable until here
    } finally {
      gcRootHolder = null; // shared-JVM hygiene - see the static holder's own comment
      currentBatch = null;
      // Shut the persistent allocator thread down before leaving: this is a
      // shared, no-forkEvery test JVM, and a leftover allocation thread would
      // keep allocating (and keep its tid trend alive) into every later test.
      allocator.interrupt();
      allocator.join(1000);
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * A second, independent end-to-end scenario for the same target-selection mechanism, using a
   * shape much closer to a real-world leak than {@link ChainLink}'s hand-rolled list: an
   * ever-growing, never-evicted {@link java.util.HashMap}-backed cache holding
   * {@link CachedPayload} values. Also asserts the reconstructed chain actually threads back
   * through {@code java.util.HashMap}'s own internal storage ({@code HashMap$Node}) - that the
   * mechanism correctly walks a real JDK collection's internals, not only purpose-built fixtures.
   *
   * <p><b>Why {@code cache} is a local variable, not a {@code static} field:</b>
   * {@code expandFrontier()} freezes whatever children it observes for a node the moment that node
   * is expanded - it never re-examines an already-{@code EXPANDED} entry for newly-added children.
   * A {@code static} field becomes a root at class-load time, essentially guaranteeing some early
   * pass catches it (and marks it {@code EXPANDED}) while still empty - permanently blocking
   * discovery of anything added afterward. A local variable created fresh at the top of this
   * method, immediately followed by round-1 allocation, gives root enumeration a real chance to
   * catch it only after it already holds live data.
   */
  @Test
  @Order(2)
  public void shouldReconstructReferrerChainThroughUnboundedCacheLeak() throws Exception {
    // Seed cache with one live entry *before* the resets below: HashMap's backing table also
    // starts as a shared, lazily-replaced empty sentinel (allocated on the first put()), so the
    // same one-shot-BFS-freeze hazard documented in shouldReconstructReferrerChainToGcRoot()
    // applies here too.
    Map<String, CachedPayload> cache = new HashMap<>();
    cache.put("cache-leak-seed", new CachedPayload("cache-leak-seed"));
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // Force a genuine fresh search rather than depend on the natural restartSearch() cycle being
      // gated on cadence/pacing budget (canAffordNewSearch()) firing again within this method's
      // retry budget.
      //
      // resetKlassPopulationForTest0() too: without it, a klass ChainLink already accumulated a
      // positive slope for during the @Order(1) test can still outrank CachedPayload as the leak
      // candidate here, and the fresh search ends up reconstructing ChainLink's chain again.
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
    Path scratchDumpPath = Files.createTempFile("referencechains-cache-leak-scratch-", ".jfr");
    Files.deleteIfExists(scratchDumpPath);
    Thread allocator = null;
    try {
      // Same retry shape as shouldReconstructReferrerChainToGcRoot() - see that method's own
      // comment for why the loop self-adjusts rather than committing to a fixed round count, why
      // per-round scale is sized against ObjectSampler's real 256KiB sampling floor rather than
      // this test's own "memory=64" request, and why totalRounds is capped at 16 rather than a
      // larger margin above the 10-round minimum (shared-fork heap headroom).
      //
      // Growth schedule, unlike the gc-root test: the round*600 growth completes at round
      // growthRounds (10) - the population trend is already eligible by then. Rounds 11-16 are
      // quiet poll/maintenance rounds adding only quietTopUpEntries each: enough to keep
      // CachedPayload's population ring advancing (a stalled ring lets the candidate lapse out of
      // selectLeakCandidates()), small enough that the BFS gets those rounds plus the grace
      // period to drain its frontier backlog and reach a leak-tagged CachedPayload inside the
      // HashMap's Node[] - a map that kept growing through all 16 rounds kept that backlog ahead
      // of the walk until the retry budget ran out. Static bound: 10*11/2*600 + 6*600 + 1 seed
      // = 36,601 entries, within the previous all-growth schedule's 69,001.
      ReferenceChainAssertions.JfrChainMatch match = null;
      boolean seededTestKlassTrend = false;
      int totalRounds = 16;
      int growthRounds = 10;
      int quietTopUpEntries = 600;
      int roundsRun = 0;

      // Pre-generate every key up front rather than concatenating a fresh String on every put().
      // The key String (plus its backing byte[]) is the same kind of same-instant,
      // size-weighted-sampler competitor as the byte[] field CachedPayload's comment mentions -
      // just a separate object. Generating all keys before the round loop lets their own
      // klass_population trend flatten out well before CachedPayload's ring starts growing, so
      // the sampler has nothing else in flight to compete with once round 1 begins.
      int maxEntries = 0;
      for (int round = 1; round <= totalRounds; round++) {
        maxEntries += round <= growthRounds ? Math.min(round, 10) * 600 : quietTopUpEntries;
      }
      String[] keys = new String[maxEntries];
      for (int i = 0; i < keys.length; i++) {
        keys[i] = "leak-" + i;
      }

      // One persistent allocator thread for every round - same shape and rationale as the gc-root
      // test's allocator. Decisively, every CachedPayload (including the keys[0] representative
      // set below) carries THIS thread's profiler tid, which is the tid the per-(klass, tid)
      // seeds must name: tagLeakInstances() only tags instances allocated by a qualifying tid.
      // Only this thread mutates cache, and only between a request's take() and its
      // roundDone.release(); the main thread reads cache only after awaitAllocatorRound() returns.
      LinkedBlockingQueue<Integer> allocRequests = new LinkedBlockingQueue<>();
      Semaphore roundDone = new Semaphore(0);
      AtomicLong allocatorTid = new AtomicLong(-1);
      AtomicReference<Throwable> allocatorFailure = new AtomicReference<>();
      allocator = new Thread(() -> {
        try {
          allocatorTid.set(ReferenceChainTestHooks.getTid());
          int next = 0; // allocator-owned key cursor; keys[] was sized for every round up front
          Integer requested;
          while ((requested = allocRequests.take()) != null) {
            for (int i = 0; i < requested; i++) {
              String key = keys[next++];
              cache.put(key, new CachedPayload(key));
            }
            roundDone.release();
          }
        } catch (InterruptedException e) {
          Thread.currentThread().interrupt(); // test shutdown - see finally below
        } catch (Throwable t) {
          allocatorFailure.set(t); // surfaced by awaitAllocatorTid()/awaitAllocatorRound()
        }
      }, "cacheleak-allocator");
      allocator.start();
      awaitAllocatorTid(allocator, allocatorTid, allocatorFailure);

      for (int round = 1; round <= totalRounds && match == null; round++) {
        roundsRun = round;
        // Same *600 growth rate as the gc-root test (not *300, this method's previous value):
        // CachedPayload and ChainLink are near-identical in size, so halving the growth rate here
        // bought no headroom and just let CachedPayload's population ring stall short of
        // KLASS_POPULATION_MIN_FILL_FOR_TREND within the growth rounds. Past growthRounds only the
        // quiet top-up - see the schedule comment above.
        int newEntries = round <= growthRounds ? Math.min(round, 10) * 600 : quietTopUpEntries;
        if (!allocRequests.offer(newEntries)) {
          throw new IllegalStateException("allocRequests queue rejected entry count " + newEntries);
        }
        awaitAllocatorRound(roundDone, allocator, allocatorFailure);
        System.gc();
        dump(scratchDumpPath);
        JfrEvents events1 = verifyEvents(scratchDumpPath, "datadog.ReferenceChain", false);
        match = ReferenceChainAssertions.findMatchForClass(events1, CachedPayload.class);

        if (match == null && ReferenceChainAssertions.isDebugInstrumentedBuild()) {
          // Same deterministic short-circuit as the gc-root test: the seed is what authorizes the
          // background BFS thread's next real pass, so the explicit poll below is best-effort;
          // and seed exactly once, since reseeding would corrupt the ring into a non-monotonic
          // sawtooth. Representative BEFORE seeding - same real-id aliasing rationale.
          ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(
              CACHED_PAYLOAD_TEST_KLASS_ID, cache.get(keys[0]));
          if (!seededTestKlassTrend) {
            // The seeds name the allocator thread's tid: it allocated every CachedPayload,
            // including the keys[0] representative - NOT this JUnit worker's tid, which allocated
            // none of them. Seeds match the organic ramp (epoch, not epoch*10): inflated seeds
            // made the slope go negative (-20..-40 observed) once real samples (about 1..15 per
            // epoch) pushed the seeds out of the trend window - see the gc-root test's identical
            // seeding for the derivation.
            int leakTid = (int) allocatorTid.get();
            for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
              ReferenceChainTestHooks.seedKlassPopulationSample0(
                  CACHED_PAYLOAD_TEST_KLASS_ID, epoch, epoch);
              ReferenceChainTestHooks.seedTidTrendSample0(
                  CACHED_PAYLOAD_TEST_KLASS_ID, leakTid, epoch, epoch);
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
              + " rounds plus a grace period"
              + (match == null ? referenceChainDiagnostics(cache.get(keys[0]), roundsRun) : ""));
      assertEquals(CachedPayload.class.getName(), match.chain.get(0));
      assertTrue(match.targetTag > 0, "targetTag should be a valid, non-zero JVMTI tag");
      assertTrue(match.depth >= 0, "depth should be a non-negative hop count");

      // The point of this test over the gc-root test: confirm the walk actually passed through
      // the cache's own internal storage, not some other, coincidental retainer - cache is the
      // only thing keeping any CachedPayload instance reachable.
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
      if (allocator != null) {
        allocator.interrupt();
        allocator.join(1000);
      }
      Files.deleteIfExists(scratchDumpPath);
    }
  }

  /**
   * Abandonment-path scenario: an artificially tiny frontier cap ({@code framecap=1} for this
   * test method) makes the very first BFS pass hit the frontier cap once a second root-referenced
   * object is discovered, so {@code runPass()} abandons the search rather than silently
   * truncating it - or, if this method lost the race to size the shared {@code FrontierTable},
   * its {@code ttl=100} fallback abandons the search instead (by the time this method runs, that
   * clock always has). Either path exercises the same {@code buildAbandonedEvent()}/
   * {@code Profiler::writeReferenceChainAbandoned()}/{@code recordReferenceChainAbandoned()}
   * write triggered by {@code Profiler::dump()} - this method only asserts that a
   * {@code datadog.ReferenceChainAbandoned} event exists, not which reason produced it.
   *
   * <p>{@code @Order(3)}: this permanently exhausts the singleton's one-and-only search, so it
   * must run after both success-path tests. It also calls {@code resetReferenceChainSearchForTest0()}
   * itself: if either earlier test's organic GC/sampling trend never fired in time (real
   * flakiness, observed in practice), the shared search can still be {@code RUNNING} with a large,
   * non-fresh frontier when this method starts - the fresh-search precondition is something this
   * method establishes, not something it presumes. Debug-only: the seam does not exist in a
   * release build.
   *
   * <p><b>Why this method also seeds a klass population trend, despite requesting no
   * {@code generations=true} of its own:</b> {@code LivenessTracker::_gc_generations} is only ever
   * updated when a {@code start()} command actually requests liveness tracking - a bare
   * {@code referencechains=true:...} command never calls {@code LivenessTracker::start()}, so
   * {@code gcGenerationsEnabled()} stays stuck at whatever the two {@code generations=true} tests
   * above last left it. {@code hasLeakSignal()}, which {@code shouldRunPass()} consults for even
   * the search's first pass, therefore falls through to {@code selectLeakCandidates()} exactly as
   * the tests above do - and with {@code _klass_population} freshly reset, nothing satisfies it.
   * Seeding {@code SEED_EPOCHS_FOR_HYSTERESIS} epochs for a dedicated klass id clears that gate;
   * this method never sets a representative or polls for it, since it has no reconstructed chain
   * of its own to prove - a qualifying entry counts toward {@code hasLeakSignal()}'s candidate
   * count regardless, and {@code resolveCandidateRepresentative()} is null-safe against one that
   * was never set.
   *
   * <p><b>Why the seeding is preceded by a {@code System.gc()} and a throwaway {@code dump()}:</b>
   * {@code cleanup_table()} compares {@code Profiler::classMap()->generation()} against its own
   * cached copy and, on a mismatch - which this method's fresh {@code start()} causes, by clearing
   * that map - wipes {@code _klass_population} back to empty, exactly once per mismatch; but that
   * comparison sits *after* an early-return guard a {@code dump()}-triggered call
   * ({@code forced=false}) only clears when a genuinely new, not-yet-processed GC epoch is
   * pending - a dump() with no GC since the last cleanup pass never reaches the mismatch check at
   * all. The two tests above get this wipe-and-resync for free from their round-1
   * {@code System.gc()}+{@code dump()} pair; seeding before any GC/dump here would leave the seed
   * to be discarded by the next call that does clear the guard - this class's own
   * {@code maybeForceCleanup()} tick (once per {@code threadLoop()} wake, {@code forced=true}
   * unconditionally clears the guard), which fires on this method's own 3 {@code System.gc()}
   * calls below. The explicit pair forces the resync to happen now, before seeding.
   */
  @Test
  @Order(3)
  public void shouldReportAbandonedSearchOnTinyFrontierCap() throws Exception {
    if (ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      // See the javadoc above for why the seeding is needed despite no generations=true of this
      // method's own, and why both a gc() and a throwaway dump() must precede it.
      System.gc();
      Path warmupDumpPath = Files.createTempFile("referencechains-abandoned-test-warmup-", ".jfr");
      Files.deleteIfExists(warmupDumpPath);
      try {
        dump(warmupDumpPath);
      } finally {
        Files.deleteIfExists(warmupDumpPath);
      }
      ReferenceChainTestHooks.resetKlassPopulationForTest0();
      // Gate-only usage: this test drives the search to ABANDONED and asserts on the abandon
      // marker, no tagged instance needs to match - so the tid is this thread's real one but any
      // distinct tid would do.
      int abandonTid = ReferenceChainTestHooks.getTid();
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            ABANDON_TEST_KLASS_ID, epoch * 10, epoch);
        ReferenceChainTestHooks.seedTidTrendSample0(
            ABANDON_TEST_KLASS_ID, abandonTid, epoch * 3, epoch);
      }
      ReferenceChainTestHooks.resetReferenceChainSearchForTest0();
    }
    List<Object> gcRootHolder = new ArrayList<>();
    gcRootHolder.add(new ChainLink("middle", new ChainLink("leaf")));

    // GarbageCollectionFinish wakes the BFS thread early, but that wakeup can race the thread's
    // own startup (VM::attachThread() completing before its first sleep) and be missed. Sleep
    // comfortably past PASS_CADENCE_NS (1s) too, so the fixed-cadence fallback guarantees at
    // least one pass runs regardless of that race.
    for (int i = 0; i < 3; i++) {
      System.gc();
      Thread.sleep(100);
    }
    Thread.sleep(1500);

    Path dumpPath = Files.createTempFile("referencechains-abandoned-test-", ".jfr");
    Files.deleteIfExists(dumpPath);
    try {
      // Even with the seeding above clearing the gate, the first pass still has to actually reach
      // the frontier cap/ttl cutoff inside whatever wall-clock time this shared JVM's scheduling
      // grants it - a single fixed-length sleep-then-dump-then-assert previously failed whenever
      // that one attempt landed a beat early. Retry across a few more dumps before concluding the
      // search genuinely never abandoned.
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
   * Bounded wait for a persistent allocator thread to publish its profiler tid: fails fast with
   * the allocator's own failure cause, or if it exited/stalled without publishing, instead of
   * hanging the shared test fork.
   */
  private static void awaitAllocatorTid(Thread allocator, AtomicLong allocatorTid,
      AtomicReference<Throwable> allocatorFailure) throws InterruptedException {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(ALLOCATOR_HANDOFF_TIMEOUT_MS);
    while (allocatorTid.get() == -1) {
      Throwable failure = allocatorFailure.get();
      if (failure != null) {
        throw new AssertionError(
            allocator.getName() + " failed before publishing its tid", failure);
      }
      if (!allocator.isAlive() && allocatorTid.get() == -1) {
        throw new AssertionError(allocator.getName() + " exited without publishing its tid");
      }
      if (System.nanoTime() - deadline > 0) {
        throw new AssertionError(allocator.getName() + " did not publish its tid within "
            + ALLOCATOR_HANDOFF_TIMEOUT_MS + "ms");
      }
      Thread.sleep(1);
    }
  }

  /**
   * Failure-only diagnostics for a success-path test's {@code assertNotNull(match, ...)} message:
   * call it only once the round and grace loops have ended without a match, so a passing run does
   * no extra work. In a debug-instrumented build it reports the current leak candidates
   * ({@code selectLeakCandidateKlassIds0()}), the representative's frontier state
   * ({@code getReferenceChainFrontierStateForTest0()}, -1 = not in the frontier) and resolved
   * target tag ({@code getReferenceChainResolvedTargetTagForTest0()}), and how many rounds ran.
   * In a release build the seams do not exist, so it returns {@code ""}.
   */
  private static String referenceChainDiagnostics(Object representative, int roundsRun) {
    if (!ReferenceChainAssertions.isDebugInstrumentedBuild()) {
      return "";
    }
    return " [diagnostics: candidates="
        + Arrays.toString(ReferenceChainTestHooks.selectLeakCandidateKlassIds0())
        + " repFrontierState="
        + ReferenceChainTestHooks.getReferenceChainFrontierStateForTest0(representative)
        + " repResolvedTargetTag="
        + ReferenceChainTestHooks.getReferenceChainResolvedTargetTagForTest0(representative)
        + " roundsRun=" + roundsRun + "]";
  }

  /** Bounded wait for one allocator round; same fail-fast policy as awaitAllocatorTid(). */
  private static void awaitAllocatorRound(Semaphore roundDone, Thread allocator,
      AtomicReference<Throwable> allocatorFailure) throws InterruptedException {
    long deadline = System.nanoTime() + TimeUnit.MILLISECONDS.toNanos(ALLOCATOR_HANDOFF_TIMEOUT_MS);
    while (!roundDone.tryAcquire(10, TimeUnit.MILLISECONDS)) {
      Throwable failure = allocatorFailure.get();
      if (failure != null) {
        throw new AssertionError(allocator.getName() + " failed mid-round", failure);
      }
      if (!allocator.isAlive()) {
        if (roundDone.tryAcquire()) {
          return; // released just before exiting
        }
        throw new AssertionError(allocator.getName() + " exited mid-round");
      }
      if (System.nanoTime() - deadline > 0) {
        throw new AssertionError(allocator.getName() + " did not finish its round within "
            + ALLOCATOR_HANDOFF_TIMEOUT_MS + "ms");
      }
    }
  }

  /**
   * Referrer-type fixture shared by both success-path and abandonment-path tests. The 32
   * {@code long} fields exist purely so a given number of megabytes of ChainLink needs far fewer
   * instances - deliberately plain fields, not a nested array: an array field would be a second,
   * separate heap allocation, and the size-weighted allocation sampler would take sampling
   * attention away from ChainLink itself rather than adding to it.
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
   * Realistic-leak fixture for the cache test: an unbounded, never-evicted cache - the single
   * most common real-world leak shape this mechanism is meant to catch. The 32 {@code long}
   * fields are there for the same reason {@link ChainLink}'s are (an earlier version used a
   * {@code byte[]} field and never observed a single CachedPayload sample - the sampler was
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
