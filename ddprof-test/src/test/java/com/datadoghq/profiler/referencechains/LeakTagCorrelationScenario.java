/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JavaProfiler;
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
import java.util.List;
import java.util.ArrayList;
import java.util.List;

/**
 * The "leak-tag correlation" use case, run inside a genuinely separate child JVM by
 * {@code ExternalLauncher}'s {@code leak-correlation} mode: a growing static-field
 * collection leak, coexisting with (a) concurrent, ephemeral, stack-local allocations of
 * another class and (b) a large live object graph, must end up reported as a
 * {@code datadog.ReferenceChain} event whose {@code targetTag} is a leak-tag-pool tag,
 * matching a {@code datadog.HeapLiveObject} event's {@code leakTag} for the same object -
 * the chain-to-live-heap-sample correlation the whole leak-tag pool exists to provide.
 *
 * <p>Each ingredient exists to reproduce, in miniature, a condition that only showed
 * against real large deployments before this scenario existed (all observed live on a
 * production-like pod, each escaping every earlier local test):
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
 *   {@code byte[]} must carry the same value in {@code leakTag}.</li>
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
   * intercepted. (An earlier fixed-array version of this fixture sidestepped that
   * requirement and still failed - see the scenario history in the investigation
   * notes - which is what exposed the rotation starvation this fixture now encodes.)
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

  // Mirrored from referenceChains.h (LEAK_TAG_BASE/LEAK_TAG_POOL_SIZE): the pool range a
  // correlated chain's targetTag must fall into, and the range a matching HeapLiveObject's
  // leakTag must fall into. This is the contract under test, asserted against runtime
  // event values - not constants compared to constants.
  private static final long LEAK_TAG_BASE = 0x40000000L;
  private static final long LEAK_TAG_POOL_SIZE = 256;

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

    void publish(NoisePayload payload) {
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

  /** One dump's scan outcome - all fields per the latest dump only. */
  private static final class ScanResult {
    ReferenceChainAssertions.ChainMatch payloadChain;
    boolean payloadChainInPool;
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
      handoff.publish(held[0]);
      long slot = 0;
      while (true) {
        try {
          Thread.sleep(50);
        } catch (InterruptedException e) {
          return;
        }
        // Churn one slot at a time: the population stays live-but-ephemeral (constant live
        // count, nothing durably retained beyond the frame) while still allocating.
        held[(int) (slot++ % held.length)] = new NoisePayload();
      }
    }, "leak-correlation-noise");
    noiseThread.setDaemon(true);
    noiseThread.start();

    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    boolean debugBuild = "debug".equals(System.getProperty("ddprof_test.config"));
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
      JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_KLASS_ID, LEAK_SINK.get(0));
      JavaProfiler.setKlassPopulationRepresentativeForTest0(NOISE_KLASS_ID, handoff.take());
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        JavaProfiler.seedKlassPopulationSample0(LEAK_KLASS_ID, epoch * 10, epoch);
        JavaProfiler.seedKlassPopulationSample0(NOISE_KLASS_ID, epoch * 10, epoch);
      }
      // Wait for the BFS thread to fully complete its first pass (static sweep AND frontier
      // expansion) before any growth round - same load-bearing wait and rationale as
      // StaticFieldGrowingCollectionScenario: the late chunks added afterward must be
      // discovered via rotation re-walks, not by a first pass that has not even run yet.
      int initialPasses = JavaProfiler.referenceChainPassesRunForTest0();
      for (int i = 0; i < 300; i++) {
        if (JavaProfiler.referenceChainPassesRunForTest0() != initialPasses) {
          break;
        }
        Thread.sleep(100);
      }
      JavaProfiler.pollReferenceChainTargets0();
    } else {
      // No debug seams outside debug builds - give the real allocation sampler and the
      // pass loop time to notice the seeded population on their own.
      Thread.sleep(5000);
    }

    // Each dump re-emits every resolved chain (drainPendingChainEvents()'s
    // snapshot-and-keep contract), so a later dump's scan is a superset state - the
    // latest scan with a payload chain observed is always the best evidence.
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
        JavaProfiler.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        JavaProfiler.seedKlassPopulationSample0(
            NOISE_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
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
        best = keepBest(best, scan(scratchDumpPath));
        if (best != null && best.payloadChainInPool
            && best.liveObjectMatchesForChainTag > 0) {
          break; // full correlation achieved - no need to grow further
        }
      }
      Thread.sleep(300);
    }

    for (int attempt = 0; attempt < 5; attempt++) {
      if (best != null && best.payloadChainInPool && best.liveObjectMatchesForChainTag > 0) {
        break;
      }
      if (debugBuild) {
        hysteresisEpoch++;
        JavaProfiler.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        JavaProfiler.seedKlassPopulationSample0(
            NOISE_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
      }
      Thread.sleep(1000);
      System.gc();
      profiler.dump(scratchDumpPath);
      best = keepBest(best, scan(scratchDumpPath));
    }

    if (best == null || best.payloadChain == null) {
      System.out.println(NOT_FOUND_MARKER);
      return;
    }
    if (!best.transientViolations.isEmpty()) {
      System.out.println(TRANSIENT_CHAIN_MARKER + best.transientViolations);
      return;
    }
    if (!best.noiseChains.isEmpty()) {
      System.out.println(NOISE_CHAIN_MARKER + best.noiseChains);
      return;
    }
    if (!best.payloadChainInPool) {
      System.out.println(TAG_OUT_OF_POOL_MARKER + best.payloadChain.targetTag);
      return;
    }
    if (best.liveObjectMatchesForChainTag == 0) {
      System.out.println(NO_LIVE_OBJECT_MARKER + best.payloadChain.targetTag);
      return;
    }
    System.out.println(FOUND_MARKER + best.payloadChain.targetTag);
  }

  /** Latest scan wins; a scan without a payload chain never displaces one that had it. */
  private static ScanResult keepBest(ScanResult best, ScanResult scan) {
    if (scan == null) {
      return best;
    }
    if (scan.payloadChain != null) {
      return scan;
    }
    return best != null ? best : scan;
  }

  /**
   * Scans one dump: the first leaked {@code byte[]} chain (if any), whether its targetTag is
   * in the leak-tag pool, how many {@code datadog.HeapLiveObject} events for a
   * leaked {@code byte[]} carry that same tag in {@code leakTag}, plus the two gate
   * regressions (transient-rooted depth<=1 chains, any {@link NoisePayload} chain).
   */
  private static ScanResult scan(Path scratchDumpPath) throws Exception {
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
          // chain, not a property of every chain). Prefer the first in-pool
          // (correlated) chain over any out-of-pool one seen earlier.
          if ((inPool && !result.payloadChainInPool) || result.payloadChain == null) {
            List<IMCType> chain = new ArrayList<>(rawChain.length);
            for (Object element : rawChain) {
              chain.add((IMCType) element);
            }
            result.payloadChain = new ReferenceChainAssertions.ChainMatch(
                chain, targetTag, depth);
            result.payloadChainInPool = inPool;
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
        for (IItem item : iterable) {
          long leakTag = leakTagAccessor != null
              ? ReferenceChainAssertions.numberValue(leakTagAccessor.getMember(item)) : -1;
          if (leakTag != result.payloadChain.targetTag) {
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
