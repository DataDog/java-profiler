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
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_BASE;
import static com.datadoghq.profiler.referencechains.ReferenceChainAssertions.LEAK_TAG_POOL_SIZE;

/**
 * The thread-local taxonomy of the leak-tag correlation use case, run inside a
 * separate child JVM by {@code ExternalLauncher}'s {@code threadlocal-leak} mode:
 * a growing {@code byte[]} collection held ONLY through the leaking thread's
 * own {@code ThreadLocal} map - never by any static field - must end up
 * reported as a {@code datadog.ReferenceChain} event whose {@code targetTag}
 * is a leak-tag-pool tag, matching a {@code datadog.HeapLiveObject} event's
 * {@code leakTag} for the same object.
 *
 * <p>This is the taxonomy shape {@code ReferenceChainTracker}'s thread-scoped
 * walk exists for (walkCandidateThreadLocals(), referenceChains.cpp): the
 * retained chunks are reachable only through the Thread object's
 * {@code threadLocals} -> ThreadLocalMap -> table -> Entry -> value path, so
 * the scenario proves that holder shape keeps working end-to-end - the
 * thread-object registry, the anchor admission and the descend gates do not
 * break the plain chain + correlation contract. The transient-root gate and
 * the noise-chain suppression are {@code LeakTagCorrelationScenario}'s own
 * contracts and are deliberately not re-asserted here.
 *
 * <p>Same separate-process, seed-before-start, per-round hysteresis
 * maintenance and debug-seam patterns as {@code LeakTagCorrelationScenario}'s
 * own class comment (the one-shot root-seeded walk is a per-process
 * resource, and a one-shot seeded ramp ages out of LivenessTracker's
 * hysteresis once real fold samples interleave).
 *
 * <p>Schedule shape (see {@link #FILLER}): every round appends one chunk to
 * the leak thread's ThreadLocal sink — the chunk supply must span the whole
 * window because the correlation needs the walk to intercept a leak-tagged
 * chunk inside the thread's ThreadLocalMap, and starving the tail rounds
 * starves that interception surface (observed as {@code tl-correlation-not-found}
 * on JDK 11 for the late-thread variant). The scale filler, in contrast, is
 * kept small: the first (root-enumeration) pass charges its whole
 * non-safepoint walk time to the tracker's CPU pain budget, and no further
 * pass runs until that debt is repaid; until then the only {@code byte[]}
 * chains are that first pass's out-of-pool discovered instances. A smaller
 * walked heap shortens the debt so the second pass - the one that builds the
 * in-pool chain - lands well inside the 25-round + 5-grace window on slow CI
 * cells (an ~8.5 s debt at 96,000 nodes was repaid only at about dump 25 of
 * 30 locally).
 */
public final class ThreadLocalLeakScenario {
  private ThreadLocalLeakScenario() {}

  /**
   * The leak sink, touched ONLY by the leaking thread. Deliberately NOT
   * static-retained: the only durable path to the chunks must run through
   * the leaking thread's ThreadLocalMap.
   */
  private static final ThreadLocal<List<byte[]>> SINK =
      ThreadLocal.withInitial(() -> new ArrayList<>());

  /**
   * Scale ingredient - same rationale as LeakTagCorrelationScenario.FILLER,
   * but a quarter of its size (375 x 64 = 24,000 nodes, not 96,000).
   * Invariant: the filler is the bulk of the heap the first pass walks (the
   * byte[] chunks are reference-free leaves), and that pass's non-safepoint
   * time is the CPU pain-budget debt the second pass waits out - the one
   * that builds the in-pool chain. The filler must stay small enough that the
   * debt is repaid well inside the 25-round + 5-grace window on slow CI
   * cells (an ~8.5 s debt at 96,000 nodes repaid only at about dump 25 of 30
   * locally); it still gives the frontier and the tag map real depth.
   */
  static final Object[][] FILLER = new Object[375][];

  // Distinct from the other scenarios' ids (987301-987304) - each scenario
  // runs in its own child JVM, but a distinct id keeps logs unambiguous.
  private static final int LEAK_KLASS_ID = 987305;

  // See LeakTagCorrelationScenario.SEED_EPOCHS_FOR_HYSTERESIS' own comment.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;
  private static final int SEED_CHUNKS = 10;

  private static int hysteresisEpoch = 0;

  /**
   * Chunk size that clears ObjectSampler's 256KiB sampling floor on its own
   * (see LeakTagCorrelationScenario.CHUNK_BYTES' own comment): every chunk
   * allocation must be sampled so it becomes a tracked, taggable
   * live-heap instance.
   */
  private static final int CHUNK_BYTES = 1_000_000;

  /**
   * Handoff for the leak thread's profiler tid and one seed chunk - the
   * main thread seeds LivenessTracker's per-(klass, tid) qualification with
   * the REAL allocating thread's tid, and that tid lives on the leak thread.
   * The chunk reference is dropped by take() so the main thread never keeps a
   * second path to the sink alive.
   */
  private static final class LeakHandoff {
    volatile int tid;
    volatile byte[] seedChunk;

    void publish(int tid, byte[] chunk) {
      this.tid = tid;
      this.seedChunk = chunk;
    }

    byte[] take() {
      byte[] chunk = seedChunk;
      seedChunk = null;
      return chunk;
    }

    /**
     * Required in both thread-start modes: neither starting the thread
     * before {@code profiler.execute()} nor after it guarantees it has
     * published by the time run() consumes the handoff. Must be called
     * before take() (it polls seedChunk, which take() clears).
     */
    boolean awaitPublication(long timeoutMs) throws InterruptedException {
      long deadline = System.nanoTime()
          + TimeUnit.MILLISECONDS.toNanos(timeoutMs);
      while (seedChunk == null && System.nanoTime() < deadline) {
        Thread.sleep(10);
      }
      return seedChunk != null;
    }
  }

  /** Printed to stdout, followed by the correlated targetTag, on full success. */
  public static final String FOUND_MARKER = "[tl-correlation-found] ";

  /** Printed to stdout if no leaked byte[] chain was ever observed. */
  public static final String NOT_FOUND_MARKER = "[tl-correlation-not-found]";

  /** Printed to stdout (with the tag) if a chain's targetTag is out of pool range. */
  public static final String TAG_OUT_OF_POOL_MARKER = "[tl-correlation-tag-out-of-pool] ";

  /** Printed to stdout (with the tag) if no HeapLiveObject matched the chain's tag. */
  public static final String NO_LIVE_OBJECT_MARKER = "[tl-correlation-no-live-object] ";

  /**
   * Printed to stdout if the leak thread never published its tid and seed chunk - a fixture
   * failure, reported apart from a correlation miss.
   */
  public static final String HANDOFF_TIMEOUT_MARKER = "[tl-correlation-handoff-timeout]";

  private static final class ScanResult {
    ReferenceChainAssertions.ChainMatch payloadChain;
    boolean payloadChainInPool;
    // ReferenceChain.leakTagIncarnation of payloadChain; -1 when the field is absent.
    long payloadChainIncarnation = -1;
    int liveObjectMatchesForChainTag;
  }

  public static void run(JavaProfiler profiler, String startCommand,
                         Path scratchDumpPath) throws Exception {
    run(profiler, startCommand, scratchDumpPath, false);
  }

  /**
   * @param lateThread when true, the leak thread is started only AFTER the
   *     recording began. This is the regression shape for
   *     {@code Profiler::onThreadStart}'s {@code registerThreadObject()}
   *     wiring (referenceChains.h): a thread born mid-recording is invisible
   *     to {@code registerExistingThreads()}'s one-time snapshot, so with
   *     the wiring broken the (klass, tid) qualification is seeded but
   *     {@code walkCandidateThreadLocals()} finds no Thread object for the
   *     tid and the ThreadLocalMap-held chain is never reached (the child
   *     prints {@link #NOT_FOUND_MARKER}).
   */
  public static void run(JavaProfiler profiler, String startCommand,
                         Path scratchDumpPath, boolean lateThread) throws Exception {
    // Build the whole fixture before the profiler starts - see the class
    // comment and LeakingCacheScenario's seed-before-start rationale.
    for (int row = 0; row < FILLER.length; row++) {
      Object[] column = new Object[64];
      for (int col = 0; col < column.length; col++) {
        column[col] = new FillerNode();
      }
      FILLER[row] = column;
    }

    LeakHandoff handoff = new LeakHandoff();
    // One round = the main thread offers a token; the leak thread takes it and
    // appends one chunk to ITS OWN ThreadLocal sink (same persistent-allocator
    // shape as ReferenceChainTrackingTest's togcroot fixture, so the chunks are
    // always allocated on the same qualifying tid). Every round of the window
    // offers a token - see the class comment's schedule-shape paragraph.
    BlockingQueue<Integer> rounds = new ArrayBlockingQueue<>(32);
    Thread leakThread = new Thread(() -> {
      // No local ever holds the sink: re-fetch it via SINK on every use so
      // the only durable path to the chunks is Thread.threadLocals ->
      // ThreadLocalMap. A live stack local would let root enumeration reach
      // ArrayList -> elementData -> byte[] directly (a depth-2 stack-local
      // chain the transient-root gate does not suppress), bypassing the
      // thread-scoped walk this scenario exists to prove.
      for (int i = 0; i < SEED_CHUNKS; i++) {
        SINK.get().add(new byte[CHUNK_BYTES]);
      }
      handoff.publish(ReferenceChainTestHooks.getTid(), SINK.get().get(0));
      while (true) {
        try {
          if (rounds.poll(50, TimeUnit.MILLISECONDS) == null) {
            continue;
          }
          SINK.get().add(new byte[CHUNK_BYTES]);
        } catch (InterruptedException e) {
          return;
        }
      }
    }, "threadlocal-leak");
    leakThread.setDaemon(true);
    if (!lateThread) {
      leakThread.start();
    }

    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    if (lateThread) {
      leakThread.start();
    }
    if (!handoff.awaitPublication(30000)) {
      System.out.println(HANDOFF_TIMEOUT_MARKER);
      return;
    }

    boolean debugBuild = ReferenceChainAssertions.isDebugInstrumentedBuild();
    int leakTid = 0;
    if (debugBuild) {
      // Representative first, seeds second: the rep's real klass id must
      // own the seeds or they authorize nothing. take() drops the handoff's
      // reference, so the rep chunk stays reachable only via ThreadLocalMap.
      ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(LEAK_KLASS_ID, handoff.take());
      leakTid = handoff.tid;
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        ReferenceChainTestHooks.seedKlassPopulationSample0(LEAK_KLASS_ID, epoch * 10, epoch);
        ReferenceChainTestHooks.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, epoch * 3, epoch);
      }
      // Maintenance continues the seeded ramp (next epoch =
      // SEED_EPOCHS_FOR_HYSTERESIS + 1) instead of restarting at 1 - same as
      // StaticFieldGrowingCollectionScenario.
      hysteresisEpoch = SEED_EPOCHS_FOR_HYSTERESIS;
      // Wait for the BFS thread's first full pass, then poll - same
      // load-bearing wait as LeakTagCorrelationScenario.
      int initialPasses = ReferenceChainTestHooks.referenceChainPassesRunForTest0();
      for (int i = 0; i < 300; i++) {
        if (ReferenceChainTestHooks.referenceChainPassesRunForTest0() != initialPasses) {
          break;
        }
        Thread.sleep(100);
      }
      ReferenceChainTestHooks.pollReferenceChainTargets0();
    } else {
      // Drop the handoff's chunk reference: the lambda (captured by the
      // Thread's runnable) retains `handoff`, so a never-taken seedChunk
      // would be a second, non-ThreadLocalMap path to a chunk.
      handoff.take();
      Thread.sleep(5000);
    }

    ScanResult best = null;
    int totalRounds = 25;
    for (int round = 1; round <= totalRounds; round++) {
      // Every round appends one chunk - the interception-surface invariant in the
      // class comment; do not front-load this growth away.
      if (!rounds.offer(round)) {
        throw new IllegalStateException("rounds queue rejected round " + round);
      }
      if (debugBuild) {
        hysteresisEpoch++;
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
      }
      Thread.sleep(300);
      System.gc();
      profiler.dump(scratchDumpPath);
      // Scan every 3rd round - same scan-churn rationale as
      // LeakTagCorrelationScenario's own comment.
      if (round % 3 == 0) {
        best = keepBest(best, scan(scratchDumpPath));
        if (best != null && best.payloadChainInPool
            && best.liveObjectMatchesForChainTag > 0) {
          break;
        }
      }
    }

    for (int attempt = 0; attempt < 5; attempt++) {
      if (best != null && best.payloadChainInPool && best.liveObjectMatchesForChainTag > 0) {
        break;
      }
      if (debugBuild) {
        hysteresisEpoch++;
        ReferenceChainTestHooks.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        ReferenceChainTestHooks.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
      }
      // No chunk is appended in the grace attempts; the trend maintenance
      // above is what keeps the candidate alive.
      Thread.sleep(1000);
      System.gc();
      profiler.dump(scratchDumpPath);
      best = keepBest(best, scan(scratchDumpPath));
    }

    if (best == null || best.payloadChain == null) {
      System.out.println(NOT_FOUND_MARKER);
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

  private static boolean passesThroughThreadLocalMap(Object[] rawChain) {
    for (Object element : rawChain) {
      if (element instanceof IMCType) {
        String name = ((IMCType) element).getFullName();
        if (name != null && name.contains("ThreadLocalMap")) {
          return true;
        }
      }
    }
    return false;
  }

  private static ScanResult keepBest(ScanResult best, ScanResult scan) {
    if (scan == null) {
      return best;
    }
    // Unlike LeakTagCorrelationScenario.keepBest, the losing scan has nothing
    // to merge: this scenario's ScanResult carries no transient/noise evidence
    // (that is LeakTagCorrelation's contract), and a scan without a payload
    // chain has no other populated field worth keeping. If evidence fields are
    // ever added here, merge them like LeakTagCorrelationScenario's mergeDistinct.
    if (best == null || best.payloadChain == null) {
      return scan;
    }
    if (scan.payloadChain == null) {
      return best;
    }
    // Mirror scan()'s own within-scan preference: an in-pool (correlated)
    // chain outranks an out-of-pool one no matter which scan observed it, so
    // a later out-of-pool chain cannot displace an earlier correlated one.
    if (best.payloadChainInPool != scan.payloadChainInPool) {
      return best.payloadChainInPool ? best : scan;
    }
    return scan;
  }

  /**
   * Scans one dump for a leaked {@code byte[]} chain through a ThreadLocalMap
   * hop, whether its targetTag is in the leak-tag pool, and how many
   * {@code datadog.HeapLiveObject} {@code byte[]} events carry that tag in
   * {@code leakTag}. No transient/noise gate scans - those are
   * LeakTagCorrelationScenario's contracts.
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
        ItemFilters.type("datadog.ReferenceChain"));
    for (IItemIterable iterable : chains) {
      IType<IItem> type = iterable.getType();
      IMemberAccessor<?, IItem> chainAccessor =
          ReferenceChainAssertions.findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor =
          ReferenceChainAssertions.findAccessor(type, "targetTag");
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
        if (!"byte[]".equals(leaf)) {
          continue;
        }
        // Only a chain through the leaking thread's ThreadLocalMap proves the
        // thread-scoped walk; any other byte[] chain must not satisfy this
        // scenario (with thread registration broken it would be the only
        // kind of chain left, and the scenario must report NOT_FOUND).
        if (!passesThroughThreadLocalMap(rawChain)) {
          continue;
        }
        boolean inPool =
            targetTag >= LEAK_TAG_BASE && targetTag < LEAK_TAG_BASE + LEAK_TAG_POOL_SIZE;
        // Prefer the first in-pool (correlated) chain over any out-of-pool
        // one seen earlier - same rationale as
        // LeakTagCorrelationScenario.scan().
        if ((inPool && !result.payloadChainInPool) || result.payloadChain == null) {
          List<IMCType> chain = new ArrayList<>(rawChain.length);
          for (Object element : rawChain) {
            chain.add((IMCType) element);
          }
          result.payloadChain = new ReferenceChainAssertions.ChainMatch(chain, targetTag, 0);
          result.payloadChainInPool = inPool;
          // The (tag, incarnation) pair is the chain's identity; an unresolved
          // -1 stamp must fail loud rather than degrade to tag-only matching,
          // which a recycled tag's chunk could satisfy.
          if (incarnationAccessor == null) {
            throw new IllegalStateException(
                "datadog.ReferenceChain events have no leakTagIncarnation accessor");
          }
          long chainIncarnation =
              ReferenceChainAssertions.numberValue(incarnationAccessor.getMember(item));
          if (chainIncarnation == -1) {
            throw new IllegalStateException(
                "chain leakTagIncarnation is not a numeric value; "
                    + "tag-only correlation is ambiguous across recycled tags");
          }
          result.payloadChainIncarnation = chainIncarnation;
        }
      }
    }

    if (result.payloadChainInPool) {
      IItemCollection liveObjects = events.apply(
          ItemFilters.type("datadog.HeapLiveObject"));
      for (IItemIterable iterable : liveObjects) {
        IType<IItem> type = iterable.getType();
        IMemberAccessor<?, IItem> leakTagAccessor =
            ReferenceChainAssertions.findAccessor(type, "leakTag");
        IMemberAccessor<?, IItem> objectClassAccessor =
            ReferenceChainAssertions.findAccessor(type, "objectClass");
        IMemberAccessor<?, IItem> incarnationAccessor =
            ReferenceChainAssertions.findAccessor(type, "leakTagIncarnation");
        // Fail loud if either identity field is missing: without the tag, every
        // live object reads -1 and never matches the chain's targetTag; without
        // the incarnation, the match degrades to tag-only, which a recycled
        // tag's stale chunk could satisfy. Both must surface as errors, not as
        // an empty correlation with no diagnostic.
        if (incarnationAccessor == null) {
          throw new IllegalStateException(
              "datadog.HeapLiveObject events have no leakTagIncarnation accessor");
        }
        if (leakTagAccessor == null) {
          throw new IllegalStateException(
              "datadog.HeapLiveObject events have no leakTag accessor");
        }
        for (IItem item : iterable) {
          long leakTag =
              ReferenceChainAssertions.numberValue(leakTagAccessor.getMember(item));
          long incarnation =
              ReferenceChainAssertions.numberValue(incarnationAccessor.getMember(item));
          // Leak tags are recycled: the tag alone is ambiguous across chunks.
          // An unresolved -1 incarnation is a hard mismatch, never a tag-only
          // match: a stale chunk that inherited the recycled tag must not
          // count as this chain's live object.
          if (incarnation == -1
              || leakTag != result.payloadChain.targetTag
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

  /** Scale-only object - same rationale as LeakTagCorrelationScenario.FillerNode. */
  static final class FillerNode {
    long p0, p1, p2, p3, p4, p5, p6, p7;
  }
}
