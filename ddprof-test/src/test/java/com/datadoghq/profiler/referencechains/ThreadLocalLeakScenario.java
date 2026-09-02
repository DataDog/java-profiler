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
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

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
 */
public final class ThreadLocalLeakScenario {
  private ThreadLocalLeakScenario() {}

  /**
   * The leak sink: a per-thread growing list, touched ONLY by the leaking
   * thread below. Deliberately NOT static-retained anywhere - the whole
   * point is that the only durable path to the chunks runs through the
   * leaking thread's ThreadLocalMap.
   */
  private static final ThreadLocal<List<byte[]>> SINK =
      ThreadLocal.withInitial(() -> new ArrayList<>());

  /** Scale ingredient - same rationale as LeakTagCorrelationScenario.FILLER. */
  static final Object[][] FILLER = new Object[1500][];

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

  // Mirrored from referenceChains.h (LEAK_TAG_BASE/LEAK_TAG_POOL_SIZE).
  private static final long LEAK_TAG_BASE = 0x40000000L;
  private static final long LEAK_TAG_POOL_SIZE = 256;

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
  }

  /** Printed to stdout, followed by the correlated targetTag, on full success. */
  public static final String FOUND_MARKER = "[tl-correlation-found] ";

  /** Printed to stdout if no leaked byte[] chain was ever observed. */
  public static final String NOT_FOUND_MARKER = "[tl-correlation-not-found]";

  /** Printed to stdout (with the tag) if a chain's targetTag is out of pool range. */
  public static final String TAG_OUT_OF_POOL_MARKER = "[tl-correlation-tag-out-of-pool] ";

  /** Printed to stdout (with the tag) if no HeapLiveObject matched the chain's tag. */
  public static final String NO_LIVE_OBJECT_MARKER = "[tl-correlation-no-live-object] ";

  private static final class ScanResult {
    ReferenceChainAssertions.ChainMatch payloadChain;
    boolean payloadChainInPool;
    int liveObjectMatchesForChainTag;
  }

  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath)
      throws Exception {
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
    // always allocated on the same qualifying tid).
    BlockingQueue<Integer> rounds = new ArrayBlockingQueue<>(32);
    Thread leakThread = new Thread(() -> {
      List<byte[]> sink = SINK.get();
      for (int i = 0; i < SEED_CHUNKS; i++) {
        sink.add(new byte[CHUNK_BYTES]);
      }
      handoff.publish(JavaProfiler.getTid(), sink.get(0));
      while (true) {
        try {
          if (rounds.poll(50, TimeUnit.MILLISECONDS) == null) {
            continue;
          }
          sink.add(new byte[CHUNK_BYTES]);
        } catch (InterruptedException e) {
          return;
        }
      }
    }, "threadlocal-leak");
    leakThread.setDaemon(true);
    leakThread.start();

    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }

    boolean debugBuild = "debug".equals(System.getProperty("ddprof_test.config"));
    int leakTid = 0;
    if (debugBuild) {
      // Representative first, seeds second - same aliasing rationale as
      // LeakTagCorrelationScenario (the rep's real klass id must own the
      // seeds or the seeds authorize nothing). The rep chunk stays durably
      // reachable only through the leak thread's ThreadLocalMap - the
      // take() above dropped this handoff's reference.
      JavaProfiler.setKlassPopulationRepresentativeForTest0(LEAK_KLASS_ID, handoff.take());
      leakTid = handoff.tid;
      for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
        JavaProfiler.seedKlassPopulationSample0(LEAK_KLASS_ID, epoch * 10, epoch);
        JavaProfiler.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, epoch * 3, epoch);
      }
      // Wait for the BFS thread's first full pass, then poll - same
      // load-bearing wait as LeakTagCorrelationScenario.
      int initialPasses = JavaProfiler.referenceChainPassesRunForTest0();
      for (int i = 0; i < 300; i++) {
        if (JavaProfiler.referenceChainPassesRunForTest0() != initialPasses) {
          break;
        }
        Thread.sleep(100);
      }
      JavaProfiler.pollReferenceChainTargets0();
    } else {
      Thread.sleep(5000);
    }

    ScanResult best = null;
    int totalRounds = 25;
    for (int round = 1; round <= totalRounds; round++) {
      rounds.offer(round);
      if (debugBuild) {
        hysteresisEpoch++;
        JavaProfiler.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        JavaProfiler.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
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
        JavaProfiler.seedKlassPopulationSample0(
            LEAK_KLASS_ID, hysteresisEpoch * 10, hysteresisEpoch);
        JavaProfiler.seedTidTrendSample0(LEAK_KLASS_ID, leakTid, hysteresisEpoch * 3, hysteresisEpoch);
      }
      rounds.offer(attempt);
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
   * Scans one dump: the first leaked {@code byte[]} chain (if any), whether
   * its targetTag is in the leak-tag pool, and how many
   * {@code datadog.HeapLiveObject} events for a leaked {@code byte[]} carry
   * that same tag in {@code leakTag}. Simplified from
   * LeakTagCorrelationScenario.scan() - no transient/noise gate scans (those
   * are that scenario's own contracts).
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
      IMemberAccessor<?, IItem> chainAccessor =
          ReferenceChainAssertions.findAccessor(type, "chain");
      IMemberAccessor<?, IItem> targetTagAccessor =
          ReferenceChainAssertions.findAccessor(type, "targetTag");
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

  /** Scale-only object - same rationale as LeakTagCorrelationScenario.FillerNode. */
  static final class FillerNode {
    long p0, p1, p2, p3, p4, p5, p6, p7;
  }
}
