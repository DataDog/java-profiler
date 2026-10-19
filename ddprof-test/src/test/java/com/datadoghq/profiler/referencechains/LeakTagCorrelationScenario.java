/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IItem;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.IItemIterable;
import org.openjdk.jmc.common.item.IMemberAccessor;
import org.openjdk.jmc.common.item.IType;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_BASE;
import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_POOL_SIZE;

/**
 * The "leak-tag correlation" use case, run inside a genuinely separate child JVM by
 * {@code ExternalLauncher}'s {@code leak-correlation} mode: a growing static-field
 * collection leak, coexisting with (a) concurrent, ephemeral, stack-local allocations of
 * another class and (b) a large live object graph, must end up reported as a
 * {@code datadog.ReferenceChain} event whose {@code targetTag} is a leak-tag-pool tag,
 * matching a {@code datadog.HeapLiveObject} event's {@code leakTag} for the same object -
 * the chain-to-live-heap-sample correlation the whole leak-tag pool exists to provide.
 *
 * <p>Each ingredient reproduces, in miniature, a condition of large deployments that
 * smaller local tests do not reach:
 * <ul>
 *   <li><b>Scale</b> ({@link #FILLER}): ~100k live filler objects grow the JVMTI tag map
 *   enough that {@code GetObjectsWithTags} has a real per-call cost floor, the BFS
 *   frontier/backlog has real depth, and per-pass deadlines actually bind - the regime
 *   where batch-size control, fair-share queue drain, and rotation starvation bugs live.
 *   Built (like the leak itself) BEFORE the profiler starts, per
 *   {@code LeakingCacheScenario}'s own comment: the one-shot root-seeded walk fires ~1s
 *   after start and must never catch the fixture half-built.</li>
 *   <li><b>Noise</b> ({@link NoisePayload} on the noise thread): short-lived allocations
 *   held only by a live thread's stack frame during that same one-shot walk - admitted
 *   as {@code stack_local}-rooted depth-1 frontier entries, exactly the transient-root
 *   noise shape the discovered-chain gate exists to suppress. The scenario asserts no
 *   such chain is ever emitted; a regression in the gate emits one and fails this
 *   scenario with {@link #TRANSIENT_CHAIN_MARKER}.</li>
 *   <li><b>Correlation</b> (the actual acceptance signal): a leaked {@code byte[]}
 *   chunk's chain must carry a {@code targetTag} in the leak-tag pool's range -
 *   mirrored here from {@code LEAK_TAG_BASE}/{@code LEAK_TAG_POOL_SIZE}
 *   (referenceChains.h) - and at least one {@code datadog.HeapLiveObject} event for a
 *   {@code byte[]} must carry the same value in {@code leakTag} (joined on
 *   {@code (tag, leakTagIncarnation)}, since leak tags are recycled). On -DDEBUG builds the
 *   chain must also be the one {@code getReferenceChainResolvedTargetTagForTest0} resolves for
 *   a live {@link #LEAK_SINK} chunk (instance identity, not just class), and after that owner
 *   chunk is dropped and its tag released, its chain must stop being emitted under that
 *   {@code (tag, leakTagIncarnation)}.</li>
 * </ul>
 *
 * <p>Same separate-process rationale as {@code LeakingCacheScenario}'s own class comment
 * (the one-shot root-seeded walk is a per-process resource), and same seed-before-start
 * and debug-seam patterns as {@code StaticFieldGrowingCollectionScenario}.
 */
public final class LeakTagCorrelationScenario {
  private LeakTagCorrelationScenario() {}

  /**
   * The leak: a static collection appended to for the process's whole life - the
   * canonical unmaintained-singleton retention shape, DELIBERATELY a growing
   * {@code ArrayList} and not a fixed holder. An ArrayList's backing
   * {@code elementData} array is REPLACED on growth, and an EXPANDED frontier node's
   * children set is frozen at expansion time (expandFrontier()'s own comment), so
   * discovering contents added after a resize is exactly the hard production case
   * this scenario must prove works: the live holder's re-walk has to admit each new
   * backing array, and only then can its new chunks be admitted and leak-tag
   * intercepted.
   */
  static final List<byte[]> LEAK_SINK = new ArrayList<>();

  /**
   * Scale ingredient: a static tree of plain objects, unreachable from anywhere but this
   * field - exists only to give the frontier/backlog and the JVMTI tag map real depth.
   */
  static final Object[][] FILLER = new Object[1500][];

  // Arbitrary, scenario-chosen klass ids - see LeakingCacheScenario.CACHED_PAYLOAD_TEST_KLASS_ID's
  // own comment; distinct from the other scenarios' ids (987301/987302) since all may run in the
  // same suite, each in its own separate child JVM.
  private static final int LEAK_KLASS_ID = 987303;
  private static final int NOISE_KLASS_ID = 987304;

  // See LeakingCacheScenario.SEED_EPOCHS_FOR_HYSTERESIS's own comment for the full derivation.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  private static final int SEED_CHUNKS = 10;

  /**
   * Per-round trend-maintenance epoch counter (debug builds only) - same
   * pattern and rationale as StaticFieldGrowingCollectionScenario's own:
   * a one-shot seeded ramp ages out of LivenessTracker's hysteresis once
   * enough real fold samples interleave (observed live: the byte[] candidate
   * dropped right after the first leak-tag interceptions, stranding the
   * correlated discoveries with no poll loop to build their chains), so
   * each round pushes one fresh rising epoch to keep the candidates alive.
   */
  private static int hysteresisEpoch = 0;

  private static void addChunk() {
    LEAK_SINK.add(new byte[CHUNK_BYTES]);
  }

  /**
   * Transient handoff channel for the noise representative - deliberately a local of
   * {@code run()} (captured by the noise thread's lambda), NOT a static field: any static
   * field holding a {@link NoisePayload} would make that one instance genuinely,
   * durably static-retained, and the profiler would be RIGHT to emit a static-rooted chain
   * for it - found the hard way on this scenario's very first run, which correctly reported
   * {@code NoisePayload@depth0:static_field}. After the handoff the only JVM-heap reference
   * to the representative is the noise thread's live frame, which is exactly the
   * transient-rooted retention this class exists to exercise.
   */
  private static final class NoiseHandoff {
    volatile NoisePayload representative;
    // The noise thread's own profiler tid - published alongside the payload so
    // the seeding below can qualify exactly that thread for the noise klass
    // (selectLeakCandidates()'s per-(klass, tid) gate matches the tid that
    // actually allocated the noise instances, and that is this thread).
    volatile int tid;

    void publish(NoisePayload payload, int tid) {
      // tid FIRST (volatile ordering): a caller that sees `representative` set
      // is then also guaranteed to see the tid published with it.
      this.tid = tid;
      representative = payload;
    }

    NoisePayload take() {
      NoisePayload payload = representative;
      representative = null; // drop this path's only reference - retention stays transient
      return payload;
    }
  }

  /** Printed to stdout, followed by the correlated targetTag, on full success. */
  public static final String FOUND_MARKER = "[correlation-found] ";

  /** Printed to stdout if no leaked byte[] chain was ever observed. */
  public static final String NOT_FOUND_MARKER = "[correlation-not-found]";

  /**
   * Printed to stdout (with the offending tag) if a leaked byte[] chain was emitted but its
   * targetTag never landed in the leak-tag pool's range - the chain-to-live-heap
   * correlation's first half failing.
   */
  public static final String TAG_OUT_OF_POOL_MARKER = "[correlation-tag-out-of-pool] ";

  /**
   * Printed to stdout (with the targetTag) if a correlated byte[] chain was emitted but
   * no datadog.HeapLiveObject event for a byte[] ever carried the same leakTag - the
   * correlation's second half failing (tagging and live-heap recording disagreeing on
   * which instances are the tracked leak candidates).
   */
  public static final String NO_LIVE_OBJECT_MARKER = "[correlation-no-live-object] ";

  /**
   * Printed to stdout (with a summary of every violation) if any ReferenceChain event was
   * emitted whose root kind is a transient root (stack/jni local) at depth <= 1 - the
   * discovered-chain gate's exact suppression contract (depth==0 always, depth==1 when
   * transient-rooted); anything matching it reaching the output is a gate regression.
   */
  public static final String TRANSIENT_CHAIN_MARKER = "[correlation-transient-chain-emitted] ";

  /**
   * Printed to stdout (with a summary of the offending chains) if the deliberately ephemeral
   * {@link NoisePayload} - held only by the noise thread's stack frame - ever got a chain
   * emitted, whether via the transient gate or any other path: nothing about it is durably
   * retained, so it must never be reported as a leak.
   */
  public static final String NOISE_CHAIN_MARKER = "[correlation-noise-chain-emitted] ";

  /**
   * Printed (with the tag) if no correlated in-pool byte[] chain was the chain the identity seam
   * resolves for a live {@link #LEAK_SINK} chunk. -DDEBUG builds only.
   */
  public static final String NOT_OWNER_VERIFIED_MARKER = "[correlation-not-owner-verified] ";

  /**
   * Printed (with the tag) if, after the verified owner chunk was dropped, every dump still
   * emitted a byte[] chain under the owner's {@code (tag, leakTagIncarnation)} - the dead
   * owner's cached chain outliving its tag (ownership-stamp regression). -DDEBUG builds only.
   */
  public static final String STALE_OWNER_CHAIN_MARKER = "[correlation-stale-owner-chain] ";

  /** Dumps the stale-owner check waits through for the dropped chunk's tag to be released. */
  private static final int STALE_CHECK_ATTEMPTS = 10;

  /**
   * Scan outcome: payload fields from one dump; transientViolations/noiseChains accumulated
   * across all scans by keepBest().
   */
  private static final class ScanResult {
    ReferenceChainAssertions.ChainMatch payloadChain;
    boolean payloadChainInPool;
    // In-pool and (on -DDEBUG builds) resolved by the identity seam for a live LEAK_SINK chunk.
    boolean payloadChainOwnerVerified;
    // LEAK_SINK index of that chunk at scan time; -1 when not verified or on release builds.
    int payloadOwnerIndex = -1;
    // ReferenceChain.leakTagIncarnation of payloadChain; -1 when the field is absent.
    long payloadChainIncarnation = -1;
    int liveObjectMatchesForChainTag;
    final List<String> transientViolations = new ArrayList<>();
    final List<String> noiseChains = new ArrayList<>();
  }

  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath)
      throws Exception {
    // Build the whole fixture before the profiler starts - see the class comment and
    // LeakingCacheScenario's own seed-before-start rationale.
    for (int i = 0; i < SEED_CHUNKS; i++) {
      addChunk();
    }
    for (int row = 0; row < FILLER.length; row++) {
      Object[] column = new Object[64];
      for (int col = 0; col < column.length; col++) {
        column[col] = new FillerNode();
      }
      FILLER[row] = column;
    }
    NoiseHandoff handoff = new NoiseHandoff();
    Thread noiseThread = new Thread(() -> {
      // Held ONLY by this live frame across the process's whole life, so the one-shot
      // root-seeded walk (a few seconds away) admits them as stack_local-rooted entries.
      NoisePayload[] held = new NoisePayload[64];
      for (int i = 0; i < held.length; i++) {
        held[i] = new NoisePayload();
      }
      // The tid must be captured on THIS thread: the per-(klass, tid) seeding below
      // qualifies the allocating thread, and the noise instances are all allocated here.
      handoff.publish(held[0], ReferenceChainTestHooks.getTid());
      long slot = 0;
      while (true) {
        try {
          Thread.sleep(50);
        } catch (InterruptedException e) {
          return;
        }
        // Churn one slot at a time: the population stays live-but-ephemeral (constant live
        // count, nothing durably retained beyond the frame) while still allocating.
        // held[0] is reserved: it is the published noise representative, and after
        // handoff.take() this frame is its only strong reference (the tracker holds just a
        // weak ref) - churning it would let the representative be collected.
        held[1 + (int) (slot++ % (held.length - 1))] = new NoisePayload();
      }
    }, "leak-correlation-noise");
    noiseThread.setDaemon(true);
    noiseThread.start();

    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    boolean debugBuild = ReferenceChainAssertions.isDebugInstrumentedBuild();
    int leakTid = 0;
    int noiseTid = 0;
    if (debugBuild) {
      // Representatives FIRST, seeds second: since the leak-tag pool redesign, candidate
      // matching, leak-tag assignment (tagLeakInstances scanning the live-heap tracking
      // table), and discovered-instance recording are all keyed on the REAL klass id -
      // setKlassPopulationRepresentativeForTest0 resolves each representative's real id
      // and aliases the synthetic id to it, and the hysteresis seeds below then land in
      // the real entry (seeding first would leave them under the synthetic id, where they
      // authorize nothing but hasLeakSignal's candidate-count check).
      // The leak representative is durably reachable via LEAK_SINK for the rest of the
      // process's life; the noise representative only via the noise thread's frame (the
      // handoff's own reference is dropped by take()) - exactly what makes one a valid
      // leak candidate and the other a gate test.
      // The noise thread publishes asynchronously: wait for it, or take() below could
      // return null (no alias to the real NoisePayload klass) and handoff.tid could be 0
      // (no real allocating tid qualified) - noise suppression would then go unexercised.
      // Plain volatile read, NOT take(): take() drops the handoff's reference.
      long noisePublicationDeadline = System.nanoTime() + 30_000_000_000L;
      while (handoff.representative == null && System.nanoTime() < noisePublicationDeadline) {
        Thread.sleep(10);
      }
      if (handoff.representative == null || handoff.tid <= 0) {
        throw new IllegalStateException("Noise thread did not publish a representative and tid");
      }
      ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(LEAK_KLASS_ID, LEAK_SINK.get(0));
      ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(NOISE_KLASS_ID, handoff.take());
      // Per-(klass, tid) qualification seeds: selectLeakCandidates() now also
      // requires a qualifying ALLOCATING THREAD, and tagLeakInstances() scopes leak
      // tags to exactly those tids' instances - so the seeded qualification must
      // name the REAL allocating tids (this thread for the leak chunks, the noise
      // thread for the noise payloads) or no tracked instance would ever match
      // the tagging scope. Same epoch-aligned ramp shape as the klass seeds
      // (scaled to fit the per-tid u8 ring); the synthetic flag keeps these
      // ramps immune to the real fold's absent-tid decay between rounds.
      leakTid = ReferenceChainTestHooks.getTid();
      noiseTid = handoff.tid;
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        ReferenceChainTestHooks.seedKlassPopulationSample0(LEAK_KLASS_ID, epoch * 10, epoch);
        ReferenceChainTestHooks.seedKlassPopulationSample0(NOISE_KLASS_ID, epoch * 10, epoch);
        ReferenceChainTestHooks.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, epoch * 3, epoch);
        ReferenceChainTestHooks.seedTidTrendSample0(NOISE_KLASS_ID, noiseTid, epoch * 3, epoch);
      }
      // Maintenance continues the seeded ramp instead of restarting at 1.
      hysteresisEpoch = SEED_EPOCHS_FOR_HYSTERESIS;
      // Wait for the BFS thread to fully complete its first pass (static sweep AND frontier
      // expansion) before any growth round - same load-bearing wait and rationale as
      // StaticFieldGrowingCollectionScenario: the late chunks added afterward must be
      // discovered via rotation re-walks, not by a first pass that has not even run yet.
      int initialPasses = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
      for (int i = 0; i < 300; i++) {
        if (ReferenceChainTestHooks.referenceChainPassesRunForTest0() != initialPasses) {
          break;
        }
        Thread.sleep(100);
      }
      ReferenceChainTestHooks.pollReferenceChainTargets0();
    } else {
      // No test seams outside -DDEBUG builds (debug/asan/tsan) - give the real allocation sampler and the
      // pass loop time to notice the seeded population on their own.
      Thread.sleep(5000);
    }

    // Each dump re-emits every resolved chain (drainPendingChainEvents()'s
    // snapshot-and-keep contract), so a later dump's scan is a superset state - the
    // latest scan with a payload chain observed is always the best payload evidence. Gate
    // violations are NOT taken from the latest scan alone: keepBest() accumulates them
    // across every scan (a violating resolved chain may be invalidated/evicted before a
    // later dump, and the gates are 'ever emitted' contracts).
    ScanResult best = null;
    int totalRounds = 25;
    // Slow growth per round is deliberate: each chunk clears the allocation
    // sampler's floor on its own (see CHUNK_BYTES), so every allocation is
    // sampled, tracked, and taggable - the per-round population growth is
    // only the trend signal, not a sampling-volume requirement.
    for (int round = 1; round <= totalRounds; round++) {
      addChunk();
      if (debugBuild) {
        hysteresisEpoch++;
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            NOISE_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(
            LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(
            NOISE_KLASS_ID, noiseTid, hysteresisEpoch * 3, hysteresisEpoch);
      }
      System.gc();
      profiler.dump(scratchDumpPath);
      // Scan only every 3rd round: each scan's JMC parse allocates megabytes
      // on this same JVM, and that churn races the leak chunks for space in
      // LivenessTracker's tracking table (the age-priority tagging then
      // selects old JVM-machinery survivors instead of the young chunks -
      // observed live as tagged=5 stable but zero interceptions). Less
      // scan churn gives the chunks time to accumulate surviving ages and
      // win the tagging priority. Rounds are still dumped every time so
      // the final dump always holds the freshest chains.
      if (round % 3 == 0) {
        // The identity seam is read after the dump: a chain in the dump for a live chunk stays
        // cached (snapshot-and-keep), and chains built since only add keys the dump lacks.
        best = keepBest(best, scan(scratchDumpPath, debugBuild ? liveOwnerTags() : null));
        if (correlated(best)) {
          break; // full correlation achieved - no need to grow further
        }
      }
      Thread.sleep(300);
    }

    for (int attempt = 0; attempt < 5; attempt++) {
      if (correlated(best)) {
        break;
      }
      if (debugBuild) {
        hysteresisEpoch++;
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            NOISE_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(
            LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(
            NOISE_KLASS_ID, noiseTid, hysteresisEpoch * 3, hysteresisEpoch);
      }
      Thread.sleep(1000);
      System.gc();
      profiler.dump(scratchDumpPath);
      best = keepBest(best, scan(scratchDumpPath, debugBuild ? liveOwnerTags() : null));
    }

    // Gate violations are 'ever emitted' contracts, independent of whether a payload chain
    // was found - report them first so a NOT_FOUND result (accepted by the tight-window
    // variant) can never mask a suppression regression.
    if (best != null && !best.transientViolations.isEmpty()) {
      System.out.println(TRANSIENT_CHAIN_MARKER + best.transientViolations);
      return;
    }
    if (best != null && !best.noiseChains.isEmpty()) {
      System.out.println(NOISE_CHAIN_MARKER + best.noiseChains);
      return;
    }
    if (best == null || best.payloadChain == null) {
      System.out.println(NOT_FOUND_MARKER);
      return;
    }
    if (!best.payloadChainInPool) {
      System.out.println(TAG_OUT_OF_POOL_MARKER + best.payloadChain.targetTag);
      return;
    }
    if (!best.payloadChainOwnerVerified) {
      System.out.println(NOT_OWNER_VERIFIED_MARKER + best.payloadChain.targetTag);
      return;
    }
    if (best.liveObjectMatchesForChainTag == 0) {
      System.out.println(NO_LIVE_OBJECT_MARKER + best.payloadChain.targetTag);
      return;
    }
    if (debugBuild) {
      long ownedTag = best.payloadChain.targetTag;
      long ownedIncarnation = best.payloadChainIncarnation;
      // Drop the verified owner: its tracked entry dies, cleanup_table() releases the leak tag
      // (stamp bump), and the next acquire may hand the same tag to another object. The dead
      // owner's chain must never be emitted under its old (tag, stamp) again. The removed chunk
      // is deliberately not kept in a local.
      LEAK_SINK.remove(best.payloadOwnerIndex);
      boolean clean = false;
      for (int attempt = 0; attempt < STALE_CHECK_ATTEMPTS && !clean; attempt++) {
        System.gc();
        Thread.sleep(500);
        profiler.dump(scratchDumpPath);
        clean = !hasByteArrayChain(scratchDumpPath, ownedTag, ownedIncarnation)
            // Without the stamp field the tag alone cannot tell a new owner from the dead one.
            || (ownedIncarnation < 0 && liveOwnerTags().containsKey(ownedTag));
      }
      if (!clean) {
        System.out.println(STALE_OWNER_CHAIN_MARKER + ownedTag);
        return;
      }
    }
    System.out.println(FOUND_MARKER + best.payloadChain.targetTag);
  }

  private static boolean correlated(ScanResult r) {
    return r != null && r.payloadChainInPool && r.payloadChainOwnerVerified
        && r.liveObjectMatchesForChainTag > 0;
  }

  /**
   * Leak tag -> LEAK_SINK index of the chunk whose own cached chain carries it, via the identity
   * seam (0 means no chain resolved for that chunk). Stores indices, never chunk references, so
   * an owner can still die.
   */
  private static Map<Long, Integer> liveOwnerTags() {
    Map<Long, Integer> owners = new HashMap<>();
    for (int i = 0; i < LEAK_SINK.size(); i++) {
      long tag =
          ReferenceChainTestHooks.getReferenceChainResolvedTargetTagForTest0(LEAK_SINK.get(i));
      if (tag != 0) {
        owners.put(tag, i);
      }
    }
    return owners;
  }

  /**
   * Whether the dump holds a byte[] chain with this targetTag and leakTagIncarnation (-1 matches
   * a chain without the field).
   */
  private static boolean hasByteArrayChain(Path scratchDumpPath, long tag, long incarnation)
      throws Exception {
    if (!Files.exists(scratchDumpPath)) {
      return false;
    }
    IItemCollection events;
    try (InputStream in = Files.newInputStream(scratchDumpPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    }
    IItemCollection chains = events.apply(
        org.openjdk.jmc.common.item.ItemFilters.type("datadog.ReferenceChain"));
    for (IItemIterable iterable : chains) {
      IType<IItem> type = iterable.getType();
      IMemberAccessor<?, IItem> chainAccessor = ReferenceChainAssertions.findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor =
          ReferenceChainAssertions.findAccessor(type, "targetTag");
      IMemberAccessor<?, IItem> incarnationAccessor =
          ReferenceChainAssertions.findAccessor(type, "leakTagIncarnation");
      if (chainAccessor == null || targetTagAccessor == null) {
        continue;
      }
      for (IItem item : iterable) {
        Object chainValue = chainAccessor.getMember(item);
        if (!(chainValue instanceof Object[])) {
          continue;
        }
        Object[] rawChain = (Object[]) chainValue;
        if (rawChain.length == 0 || !(rawChain[0] instanceof IMCType)
            || !"byte[]".equals(((IMCType) rawChain[0]).getFullName())) {
          continue;
        }
        long chainIncarnation = incarnationAccessor != null
            ? ReferenceChainAssertions.numberValue(incarnationAccessor.getMember(item)) : -1;
        if (ReferenceChainAssertions.numberValue(targetTagAccessor.getMember(item)) == tag
            && chainIncarnation == incarnation) {
          return true;
        }
      }
    }
    return false;
  }

  /**
   * Payload state comes from the latest scan that saw a payload chain (a scan without one
   * never displaces one that had it). Gate violations (transient/noise chains) are
   * accumulated across ALL scans - they are 'ever emitted' contracts, and a violating
   * resolved chain may be invalidated/evicted before a later dump.
   */
  private static ScanResult keepBest(ScanResult best, ScanResult scan) {
    if (scan == null) {
      return best;
    }
    if (best == null) {
      return scan;
    }
    // Same evidence ranking scan() applies within one dump: an owner-verified
    // in-pool chain (2) outranks an unverified in-pool one (1), which outranks
    // any out-of-pool chain (0). A later scan only wins on equal or better
    // evidence, so noise churn and tag recycling cannot displace the
    // best-evidenced correlation mid-run.
    int bestScore = evidenceScore(best);
    int scanScore = evidenceScore(scan);
    ScanResult result = scanScore > bestScore || (scanScore == bestScore
        && scan.payloadChain != null) ? scan : best;
    ScanResult other = result == scan ? best : scan;
    if (other != null) {
      mergeDistinct(result.transientViolations, other.transientViolations);
      mergeDistinct(result.noiseChains, other.noiseChains);
    }
    return result;
  }

  private static int evidenceScore(ScanResult scan) {
    if (scan.payloadChain == null) {
      return -1;
    }
    return scan.payloadChainInPool ? (scan.payloadChainOwnerVerified ? 2 : 1) : 0;
  }

  private static void mergeDistinct(List<String> into, List<String> from) {
    for (String s : from) {
      if (!into.contains(s)) {
        into.add(s);
      }
    }
  }

  /**
   * Scans one dump: the best leaked {@code byte[]} chain (if any), whether its targetTag is
   * in the leak-tag pool and owned by a live LEAK_SINK chunk, how many
   * {@code datadog.HeapLiveObject} events for a leaked {@code byte[]} carry that same
   * {@code (leakTag, leakTagIncarnation)}, plus the two gate regressions (transient-rooted
   * depth<=1 chains, any {@link NoisePayload} chain).
   *
   * @param liveOwners {@link #liveOwnerTags()} read after this dump, or null on release builds
   *     (no identity seam: any in-pool chain counts as owner-verified)
   */
  private static ScanResult scan(Path scratchDumpPath, Map<Long, Integer> liveOwners)
      throws Exception {
    if (!Files.exists(scratchDumpPath)) {
      return null;
    }
    IItemCollection events;
    try (InputStream in = Files.newInputStream(scratchDumpPath)) {
      events = JfrLoaderToolkit.loadEvents(in);
    }
    ScanResult result = new ScanResult();

    IItemCollection chains = events.apply(
        org.openjdk.jmc.common.item.ItemFilters.type("datadog.ReferenceChain"));
    for (IItemIterable iterable : chains) {
      IType<IItem> type = iterable.getType();
      IMemberAccessor<?, IItem> chainAccessor = ReferenceChainAssertions.findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor =
          ReferenceChainAssertions.findAccessor(type, "targetTag");
      IMemberAccessor<?, IItem> depthAccessor = ReferenceChainAssertions.findAccessor(type, "depth");
      IMemberAccessor<?, IItem> rootKindAccessor =
          ReferenceChainAssertions.findAccessor(type, "rootKind");
      IMemberAccessor<?, IItem> incarnationAccessor =
          ReferenceChainAssertions.findAccessor(type, "leakTagIncarnation");
      for (IItem item : iterable) {
        Object chainValue = chainAccessor.getMember(item);
        if (!(chainValue instanceof Object[])) {
          continue;
        }
        Object[] rawChain = (Object[]) chainValue;
        String leaf = rawChain.length > 0 && rawChain[0] instanceof IMCType
            ? ((IMCType) rawChain[0]).getFullName() : "<empty>";
        long targetTag = targetTagAccessor != null
            ? ReferenceChainAssertions.numberValue(targetTagAccessor.getMember(item)) : -1;
        int depth = depthAccessor != null
            ? (int) ReferenceChainAssertions.numberValue(depthAccessor.getMember(item)) : -1;
        Object rootKind = rootKindAccessor != null ? rootKindAccessor.getMember(item) : null;
        String rootKindName = rootKind != null ? rootKind.toString() : "<none>";
        if (rootKindName.startsWith("first_observed_via:") && depth <= 1) {
          result.transientViolations.add(leaf + "@depth" + depth + ":" + rootKindName);
        }
        if (NoisePayload.class.getName().equals(leaf)) {
          result.noiseChains.add(leaf + "@depth" + depth + ":" + rootKindName);
        }
        if ("byte[]".equals(leaf)) {
          boolean inPool =
              targetTag >= LEAK_TAG_BASE && targetTag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE;
          // Multiple byte[] chains exist in a single dump: every discovered
          // instance of the candidate class gets one, and only the tracked-and-
          // tagged instances carry a pool-range targetTag - the rest legitimately
          // carry their frontier tag (the correlation is additive on top of the
          // chain, not a property of every chain). Prefer the first owner-verified
          // in-pool chain, then any in-pool one, over an out-of-pool one seen earlier.
          boolean ownerVerified =
              inPool && (liveOwners == null || liveOwners.containsKey(targetTag));
          int score = inPool ? (ownerVerified ? 2 : 1) : 0;
          int currentScore = result.payloadChain == null ? -1
              : result.payloadChainInPool ? (result.payloadChainOwnerVerified ? 2 : 1) : 0;
          if (score > currentScore) {
            List<IMCType> chain = new ArrayList<>(rawChain.length);
            for (Object element : rawChain) {
              chain.add((IMCType) element);
            }
            result.payloadChain = new ReferenceChainAssertions.ChainMatch(
                chain, targetTag, depth);
            result.payloadChainInPool = inPool;
            result.payloadChainOwnerVerified = ownerVerified;
            result.payloadOwnerIndex =
                ownerVerified && liveOwners != null ? liveOwners.get(targetTag) : -1;
            result.payloadChainIncarnation = incarnationAccessor != null
                ? ReferenceChainAssertions.numberValue(incarnationAccessor.getMember(item)) : -1;
          }
        }
      }
    }

    if (result.payloadChainInPool) {
      IItemCollection liveObjects = events.apply(
          org.openjdk.jmc.common.item.ItemFilters.type("datadog.HeapLiveObject"));
      for (IItemIterable iterable : liveObjects) {
        IType<IItem> type = iterable.getType();
        IMemberAccessor<?, IItem> leakTagAccessor =
            ReferenceChainAssertions.findAccessor(type, "leakTag");
        IMemberAccessor<?, IItem> objectClassAccessor =
            ReferenceChainAssertions.findAccessor(type, "objectClass");
        IMemberAccessor<?, IItem> incarnationAccessor =
            ReferenceChainAssertions.findAccessor(type, "leakTagIncarnation");
        for (IItem item : iterable) {
          long leakTag = leakTagAccessor != null
              ? ReferenceChainAssertions.numberValue(leakTagAccessor.getMember(item)) : -1;
          long incarnation = incarnationAccessor != null
              ? ReferenceChainAssertions.numberValue(incarnationAccessor.getMember(item)) : -1;
          // Leak tags are recycled: the tag alone is ambiguous across chunks.
          if (leakTag != result.payloadChain.targetTag
              || incarnation != result.payloadChainIncarnation) {
            continue;
          }
          Object objectClass = objectClassAccessor != null
              ? objectClassAccessor.getMember(item) : null;
          if (objectClass instanceof IMCType
              && "byte[]".equals(((IMCType) objectClass).getFullName())) {
            result.liveObjectMatchesForChainTag++;
          }
        }
      }
    }
    return result;
  }

  /**
   * Chunk size that clears ObjectSampler's real 256KiB sampling floor on its own - same
   * rationale as StaticFieldGrowingCollectionScenario.CHUNK_BYTES. Load-bearing here:
   * every chunk allocation must be allocation-sampled so it becomes a live-heap tracked
   * instance (the only instances LivenessTracker's leak-tag pool tags, and the only ones
   * that get datadog.HeapLiveObject events to correlate against). A small leaked object
   * only gets sampled probabilistically, which made the correlation dependent on
   * sampling luck - observed live as pass-standalone/fail-in-suite before this.
   */
  private static final int CHUNK_BYTES = 1_000_000;

  /**
   * The noise object: deliberately ephemeral - held only by the noise thread's live
   * frame, never by any field, so nothing about it is durably retained.
   */
  static final class NoisePayload {
    long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;
  }

  /** Scale-only object: no references, just weight - one frontier entry each. */
  static final class FillerNode {
    long p0, p1, p2, p3, p4, p5, p6, p7;
  }
}
