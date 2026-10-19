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
import java.util.HashMap;
import java.util.Map;

/**
 * The "leaking Java app" body run inside a separate child JVM by {@code ExternalLauncher}'s
 * {@code leak-cache} mode, driven by {@code ExternalProcessReferenceChainTest}. Deliberately not a
 * JUnit test: it must run alone in its own process so the process-wide {@code ReferenceChainTracker}
 * singleton's one-shot root-seeded BFS walk belongs to this scenario only (see
 * {@code ExternalProcessReferenceChainTest}'s class comment). The leak shape is an ever-growing,
 * never-evicted {@code HashMap}-backed cache.
 *
 * <p><b>Why {@code cache} is populated <em>before</em> the profiler is started:</b>
 * {@code threadLoop()} (referenceChains.cpp) sleeps {@code _effective_cadence_ns} - 1 second,
 * initially - before its first {@code shouldRunPass()} check, which always returns {@code true}
 * on that first check ({@code !_search_started}). So the one-and-only root-seeded walk fires
 * roughly one second after {@code startThread()}, or earlier if woken by a GC-finish signal. On a
 * cold JVM, allocating only after starting the profiler lost that race essentially every time:
 * the walk caught {@code cache} still empty, permanently blocking discovery of everything added
 * afterward (a frontier entry once marked {@code EXPANDED} is never revisited for new children -
 * see {@code expandFrontier()}). Seeding before {@code profiler.execute()} removes the race.
 */
public final class LeakingCacheScenario {
  private LeakingCacheScenario() {}

  // Arbitrary klass id - LivenessTracker treats it as an opaque key (see KlassPopulationEntry)
  // and this process runs no other reference-chains scenario, so it cannot collide.
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987301;

  // LivenessTracker's hysteresis gate (livenessTracker.h's KLASS_POPULATION_MIN_FILL_FOR_TREND=10 /
  // LEAK_TREND_HYSTERESIS_BASE=5) only starts incrementing consecutive_positive once ring_fill
  // reaches 10, so exactly 10 seedKlassPopulationSample0() calls cap consecutive_positive at 1 -
  // short of what selectLeakCandidates() requires before hasLeakSignal() reports a candidate, which
  // generations=true needs to authorize the BFS thread's first real pass.
  private static final int SEED_EPOCHS_FOR_HYSTERESIS = 15;

  /**
   * Durable holder for the cache fixture. The discovered-chain gate suppresses
   * chains shallower than the first real holder hop that are rooted at a TRANSIENT
   * root (stack/JNI local) - a frame-held "leak" is not a leak - so the cache must
   * be retained through a static field rather than only {@code run()}'s local.
   */
  private static final Map<String, CachedPayload> CACHE = new HashMap<>();

  /** Printed to stdout, followed by the matched leaf class's name, on success. */
  public static final String FOUND_MARKER = "[chain-found] ";

  /** Printed to stdout (with no class name suffix) if no match was ever observed. */
  public static final String NOT_FOUND_MARKER = "[chain-not-found]";

  /**
   * Printed to stdout (with the offending chain appended) if a match was found but its
   * chain did not pass through {@code java.util.HashMap}'s internal storage.
   */
  public static final String NO_HASHMAP_INTERNALS_MARKER = "[chain-found-no-hashmap-internals] ";

  /**
   * Printed to stdout (with an "N/M" re-emitted-dump count appended) if the chain was
   * reconstructed but did <em>not</em> re-emit into one or more subsequent JFR dumps - i.e. the
   * "snapshot-and-keep" contract of {@code ReferenceChainTracker::drainPendingChainEvents()}
   * (referenceChains.cpp) failed to hold across dumps.
   */
  public static final String CHAIN_NOT_PERSISTED_MARKER = "[chain-not-persisted] ";

  /**
   * Seeds {@code cache}, *then* starts the profiler (see the class comment for why that order is
   * load-bearing), then grows the cache, dumping to {@code scratchDumpPath} after every round
   * until a {@code datadog.ReferenceChain} event whose {@code chain[0]} is {@link CachedPayload}
   * appears, and prints exactly one result line to stdout. The profiler is started here rather
   * than in {@code ExternalLauncher} so {@code cache} can be seeded first.
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
        // Debug-only seeded short-circuit: decouples the assertion from whether probabilistic
        // allocation sampling notices CachedPayload's trend within the fixed round budget, by
        // clearing hasLeakSignal()'s hysteresis gate outright. "seed-0" stays reachable via
        // cache for the whole run, so it is a valid representative on any round.
        // Representative BEFORE seeding: setKlassPopulationRepresentativeForTest0 aliases the
        // synthetic id to the representative's real klass id, so the seeds below land in the
        // real population entry (candidate matching is keyed by real id).
        ReferenceChainTestHooks.setKlassPopulationRepresentativeForTest0(CACHED_PAYLOAD_TEST_KLASS_ID, cache.get("seed-0"));
        if (!seededTestKlassTrend) {
          // The qualifying tid is THIS thread's - the creator of "seed-0". The per-round
          // allocator threads are one-shot, so none of their tids carries a sustained
          // per-tid signal.
          int leakTid = ReferenceChainTestHooks.getTid();
          for (int epoch = 1; epoch <= SEED_EPOCHS_FOR_HYSTERESIS; epoch++) {
            ReferenceChainTestHooks.seedKlassPopulationSample0(CACHED_PAYLOAD_TEST_KLASS_ID, epoch * 10, epoch);
            ReferenceChainTestHooks.seedTidTrendSample0(CACHED_PAYLOAD_TEST_KLASS_ID, leakTid, epoch * 3, epoch);
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

    // Across-dumps persistence: Profiler::dump() re-snapshots the resolved-chain cache without
    // clearing it (drainPendingChainEvents(), "snapshot-and-keep, not a drain"), so a still-live
    // sample's chain must re-emit into every dump. `cache` keeps the sample live; each dump
    // targets a brand-new file, so a match there can only come from re-emission.
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

  /** Key namespace "seed-" is disjoint from the round loop's "leak-". */
  private static void seedInitialBatch(Map<String, CachedPayload> cache, int count) {
    for (int i = 0; i < count; i++) {
      String key = "seed-" + i;
      cache.put(key, new CachedPayload(key));
    }
  }

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
      for (IItemIterable iterable : chains) {
        IType<IItem> type = iterable.getType();
        IMemberAccessor<?, IItem> chainAccessor =
            ReferenceChainAssertions.findAccessor(type, "chain");
        if (chainAccessor == null) {
          System.out.println("[debug] no chain accessor found");
          continue;
        }
        for (IItem item : iterable) {
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
   * Leak fixture. The 32 {@code long} fields exist so far fewer entries reach
   * {@code ObjectSampler}'s 256KiB sampling floor - plain fields, not a nested array, because a
   * companion array would be a second allocation competing for the size-weighted sampler's
   * attention.
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
