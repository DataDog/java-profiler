/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JavaProfiler;
import com.datadoghq.profiler.ReferenceChainTestHooks;
import org.openjdk.jmc.common.IMCType;
import org.openjdk.jmc.common.item.IItemCollection;
import org.openjdk.jmc.common.item.ItemFilters;
import org.openjdk.jmc.flightrecorder.JfrLoaderToolkit;

import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

/**
 * The actual "leaking Java app" body run inside a separate child JVM by {@code ExternalLauncher}'s
 * {@code leak-cache} mode, driven by {@code ExternalProcessReferenceChainTest}. Deliberately not a
 * JUnit test itself - no shared-JVM {@code ReferenceChainTracker} singleton with any other test;
 * the whole point is to run alone in its own process so the one-shot root-seeded BFS walk always
 * belongs to this scenario (see {@code ExternalProcessReferenceChainTest}'s comment for why an
 * earlier in-process attempt failed).
 *
 * <p><b>Why {@code cache} is seeded and populated <em>before</em> the profiler is even started:</b>
 * {@code threadLoop()} sleeps one initial cadence *before* its very first {@code shouldRunPass()}
 * check, and that first check always returns {@code true} ({@code !_search_started}) - so the
 * process's one-and-only root-seeded walk fires roughly one second after {@code startThread()}, or
 * earlier if woken by a GC-finish signal (which can race the thread's own startup). An initial
 * in-process attempt created {@code cache} only *after* starting the profiler; against a cold JVM
 * that lost the race essentially every time - the one-shot walk caught {@code cache} still empty,
 * and a frontier entry once marked {@code EXPANDED} is never revisited for new children. Seeding
 * before {@code profiler.execute()} removes the race entirely.
 */
public final class LeakingCacheScenario {
  private LeakingCacheScenario() {}

  // Arbitrary, scenario-chosen klass id - this process's own LivenessTracker population table
  // treats it as an opaque key, and this process never runs any other reference-chains scenario.
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987301;

  // See ReferenceChainTrackingTest.SEED_EPOCHS_FOR_HYSTERESIS for the derivation: 10
  // (KLASS_POPULATION_MIN_FILL_FOR_TREND) + 5 (LEAK_TREND_HYSTERESIS_BASE) - 1 = 14 seed calls
  // is the minimum that clears selectLeakCandidates()'s consecutive_positive gate; 15 gives
  // margin. generations=true needs that gate cleared to authorize the BFS thread's first pass.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  /**
   * Durable holder for the cache fixture. The discovered-chain gate suppresses chains shallower
   * than the first real holder hop that are rooted at a TRANSIENT root (stack/JNI local) - a
   * frame-held "leak" is by definition not a leak - so the cache must be retained through a
   * static field; {@code run()}'s local {@code cache} variable below aliases this static.
   */
  private static final Map<String, CachedPayload> CACHE = new HashMap<>();

  /** Printed to stdout, followed by the matched leaf class's name, on success. */
  public static final String FOUND_MARKER = "[chain-found] ";

  /** Printed to stdout (with no class name suffix) if no match was ever observed. */
  public static final String NOT_FOUND_MARKER = "[chain-not-found]";

  /**
   * Printed to stdout (with the offending class name appended) if a match was found but its chain
   * did not pass through {@code java.util.HashMap}'s own internal storage - asserted in the
   * parent process rather than here, keeping this scenario's stdout contract to "found/not-found".
   */
  public static final String NO_HASHMAP_INTERNALS_MARKER = "[chain-found-no-hashmap-internals] ";

  /**
   * Printed to stdout (with an "N/M" re-emitted-dump count appended) if the chain was
   * reconstructed but did <em>not</em> re-emit into one or more subsequent, independently written
   * JFR dumps - i.e. the "snapshot-and-keep" contract of {@code drainPendingChainEvents()} failed
   * to hold across dumps. Asserted by {@code ExternalProcessReferenceChainTest}.
   */
  public static final String CHAIN_NOT_PERSISTED_MARKER = "[chain-not-persisted] ";

  /**
   * Seeds {@code cache} with an initial batch, *then* starts the profiler (order is load-bearing,
   * see the class comment), then runs the same population-growth loop
   * {@code ReferenceChainTrackingTest} pioneered - dumping after every round (plus a grace period)
   * until a {@code datadog.ReferenceChain} event whose {@code chain[0]} is {@link CachedPayload}
   * appears - then prints exactly one result line to stdout. Called from {@code ExternalLauncher}
   * (a different package - hence {@code public}), which owns the generic child-process bootstrap;
   * starting the profiler happens here, not there, specifically so {@code cache} can be seeded
   * first.
   */
  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath) throws Exception {
    Map<String, CachedPayload> cache = CACHE;
    seedInitialBatch(cache, 300);
    System.out.println("[debug] startCommand=" + startCommand);
    System.out.println("[debug] scratchDumpPath=" + scratchDumpPath);
    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }
    System.out.println("[debug] profiler.execute() returned");

    boolean debugBuild = ReferenceChainAssertions.isDebugInstrumentedBuild();
    boolean seededTestKlassTrend = false;
    ReferenceChainAssertions.ChainMatch match = null;
    int totalRounds = 25;
    for (int round = 1; round <= totalRounds && match == null; round++) {
      int newEntries = round * 300;
      int roundNumber = round;
      Thread allocator = new Thread(() -> {
        for (int i = 0; i < newEntries; i++) {
          String key = "leak-" + roundNumber + "-" + i;
          cache.put(key, new CachedPayload(key));
        }
      });
      allocator.start();
      allocator.join();
      System.gc();
      profiler.dump(scratchDumpPath);
      match = findMatch(scratchDumpPath);

      if (match == null && debugBuild) {
        // Same debug-only, seeded-representative short-circuit as ReferenceChainTrackingTest:
        // clears hasLeakSignal()'s hysteresis gate outright, decoupling this scenario's assertion
        // from whether probabilistic slope detection happens to notice CachedPayload's trend
        // within the fixed round/timeout budget. "seed-0" (from seedInitialBatch()) is reachable
        // via cache for the scenario's entire lifetime, so it is always a valid representative.
        // Representative BEFORE seeding: setting it registers the synthetic->real id alias, so
        // the seeds below land in the real population entry (candidate matching is real-id keyed
        // since the leak-tag pool redesign).
        ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(
            CACHED_PAYLOAD_TEST_KLASS_ID, cache.get("seed-0"));
        if (!seededTestKlassTrend) {
          // The qualifying tid is THIS thread's - the creator of "seed-0". The per-round
          // allocator threads are one-shot, so no single one of their tids carries a sustained
          // per-tid signal.
          int leakTid = ReferenceChainTestHooks.getTid();
          for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
            ReferenceChainTestHooks.seedKlassPopulationSample0(
                CACHED_PAYLOAD_TEST_KLASS_ID, epoch * 10, epoch);
            ReferenceChainTestHooks.seedTidTrendSample0(
                CACHED_PAYLOAD_TEST_KLASS_ID, leakTid, epoch * 3, epoch);
          }
          seededTestKlassTrend = true;
        }
        ReferenceChainTestHooks.pollReferenceChainTargets0();
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath);
      }

      if (match == null) {
        Thread.sleep(300);
        profiler.dump(scratchDumpPath);
        match = findMatch(scratchDumpPath);
      }
      if (round == 1 || round == 5 || round == 10 || round == 25) {
        System.out.println("[debug] round=" + round + " cache.size()=" + cache.size());
        debugDumpAllChainLeaves(scratchDumpPath);
      }
    }

    for (int attempt = 0; match == null && attempt < 5; attempt++) {
      Thread.sleep(1000);
      profiler.dump(scratchDumpPath);
      match = findMatch(scratchDumpPath);
    }

    if (match == null) {
      debugDumpAllChainLeaves(scratchDumpPath);
      debugDumpCounters(profiler);
      System.out.println(NOT_FOUND_MARKER);
      return;
    }
    boolean sawHashMapInternals = false;
    for (IMCType type : match.chain) {
      if (type.getFullName().startsWith("java.util.HashMap")) {
        sawHashMapInternals = true;
        break;
      }
    }
    if (!sawHashMapInternals) {
      System.out.println(NO_HASHMAP_INTERNALS_MARKER + match.chain);
      return;
    }

    // Across-dumps persistence: a resolved chain must re-emit into EVERY subsequent dump the
    // sample survives into, not only the dump that first observed it. Profiler::dump()
    // re-snapshots the resolved-chain cache without clearing it on every call
    // ("snapshot-and-keep, not a drain"). `cache` still holds every CachedPayload here, so the
    // sample stays live across these extra dumps; each dump targets a brand-new file, so a chain
    // found there can only be present because it was re-emitted into that dump.
    int persistChecks = 3;
    int persisted = 0;
    for (int i = 1; i <= persistChecks; i++) {
      Path reDumpPath = Files.createTempFile("referencechains-persist-" + i + "-", ".jfr");
      Files.deleteIfExists(reDumpPath);
      try {
        profiler.dump(reDumpPath);
        if (findMatch(reDumpPath) != null) {
          persisted++;
        } else {
          System.out.println("[debug] across-dumps: CachedPayload chain missing from fresh dump #" + i);
        }
      } finally {
        Files.deleteIfExists(reDumpPath);
      }
    }
    if (persisted != persistChecks) {
      System.out.println(CHAIN_NOT_PERSISTED_MARKER + persisted + "/" + persistChecks);
      return;
    }
    System.out.println("[debug] across-dumps: CachedPayload chain re-emitted in all "
        + persistChecks + " fresh dumps");
    System.out.println(FOUND_MARKER + match.chain.get(0).getFullName());
  }

  /**
   * Populates {@code cache} with {@code count} entries under a key namespace ("seed-") disjoint
   * from the round loop's own ("leak-") - before the profiler (and its BFS thread) even starts,
   * so the one-shot root-seeded walk can never catch {@code cache} empty.
   */
  private static void seedInitialBatch(Map<String, CachedPayload> cache, int count) {
    for (int i = 0; i < count; i++) {
      String key = "seed-" + i;
      cache.put(key, new CachedPayload(key));
    }
  }

  /** Temporary diagnostic: print all native debug counters. */
  private static void debugDumpCounters(JavaProfiler profiler) {
    try {
      Map<String, Long> counters = profiler.getDebugCounters();
      System.out.println("[debug] counters (" + counters.size() + " total):");
      counters.entrySet().stream()
          .filter(e -> e.getValue() != 0)
          .sorted(Map.Entry.comparingByKey())
          .forEach(e -> System.out.println("[debug]   " + e.getKey() + " = " + e.getValue()));
    } catch (Exception e) {
      System.out.println("[debug] exception while dumping counters: " + e);
    }
  }

  /** Temporary diagnostic: print every datadog.ReferenceChain event's chain[0] class, if any. */
  private static void debugDumpAllChainLeaves(Path scratchDumpPath) {
    try {
      if (!Files.exists(scratchDumpPath)) {
        System.out.println("[debug] scratch dump path does not exist: " + scratchDumpPath);
        return;
      }
      IItemCollection events;
      try (InputStream in = Files.newInputStream(scratchDumpPath)) {
        events = JfrLoaderToolkit.loadEvents(in);
      }
      IItemCollection chains = events.apply(ItemFilters.type("datadog.ReferenceChain"));
      long total = chains.stream().mapToLong(it -> it.getItemCount()).sum();
      System.out.println("[debug] datadog.ReferenceChain total events: " + total);
      IItemCollection liveObjects = events.apply(ItemFilters.type("datadog.HeapLiveObject"));
      long totalLive = liveObjects.stream().mapToLong(it -> it.getItemCount()).sum();
      System.out.println("[debug] datadog.HeapLiveObject total events: " + totalLive);
      IItemCollection abandoned = events.apply(ItemFilters.type("datadog.ReferenceChainAbandoned"));
      long totalAbandoned = abandoned.stream().mapToLong(it -> it.getItemCount()).sum();
      System.out.println("[debug] datadog.ReferenceChainAbandoned total events: " + totalAbandoned);
      for (org.openjdk.jmc.common.item.IItemIterable iterable : chains) {
        org.openjdk.jmc.common.item.IType<org.openjdk.jmc.common.item.IItem> type = iterable.getType();
        org.openjdk.jmc.common.item.IMemberAccessor<?, org.openjdk.jmc.common.item.IItem> chainAccessor =
            ReferenceChainAssertions.findAccessor(type, "chain");
        if (chainAccessor == null) {
          System.out.println("[debug] no chain accessor found");
          continue;
        }
        for (org.openjdk.jmc.common.item.IItem item : iterable) {
          Object chainValue = chainAccessor.getMember(item);
          if (chainValue instanceof Object[]) {
            Object[] raw = (Object[]) chainValue;
            String leaf = raw.length > 0 && raw[0] instanceof IMCType
                ? ((IMCType) raw[0]).getFullName() : "<empty-or-non-IMCType>";
            System.out.println("[debug] chain leaf: " + leaf);
          }
        }
      }
    } catch (Exception e) {
      System.out.println("[debug] exception while dumping chain leaves: " + e);
    }
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
        events.apply(ItemFilters.type("datadog.ReferenceChain")), CachedPayload.class);
  }

  /**
   * Realistic-leak fixture - identical shape to {@code ReferenceChainTrackingTest.CachedPayload}.
   * The 32 {@code long} fields exist purely so a given number of megabytes needs far fewer entries
   * to reach {@code ObjectSampler}'s real 256KiB sampling floor - deliberately plain fields, not
   * a nested array (a same-instance companion array would be a second, separate heap allocation
   * the size-weighted sampler would compete for, taking attention away from CachedPayload).
   */
  static final class CachedPayload {
    final String key;
    long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
    long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31;

    CachedPayload(String key) {
      this.key = key;
    }
  }
}
