/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.JavaProfiler;
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
 * The actual "leaking Java app" body run inside a genuinely separate child JVM by
 * {@code ExternalLauncher}'s {@code leak-cache} mode, driven by
 * {@code ExternalProcessReferenceChainTest}. Deliberately not a JUnit test itself - no
 * {@code AbstractProfilerTest}/dynamic-attach lifecycle, no shared-JVM {@code ReferenceChainTracker}
 * singleton with any other test - this class's whole point is to run alone in its own process, so
 * the one-shot root-seeded BFS walk (see this class's own comment on why a previous attempt at
 * folding this scenario into {@code ReferenceChainTrackingTest} as a second {@code @Test} method
 * failed) always belongs to this scenario and only this scenario.
 *
 * <p>Same realistic-leak shape as {@code ReferenceChainTrackingTest}'s own (now-removed) in-process
 * attempt: an ever-growing, never-evicted {@code HashMap}-backed cache, held by a local variable.
 *
 * <p><b>Why {@code cache} is seeded and populated <em>before</em> the profiler is even started
 * (found the hard way, against a real separate-process run):</b> {@code threadLoop()}
 * (referenceChains.cpp) calls {@code OS::sleep(_effective_cadence_ns)} - 1 second, initially -
 * *before* its very first {@code shouldRunPass()} check, and {@code shouldRunPass()} always
 * returns {@code true} on that first-ever check ({@code !_search_started}). So the process's
 * one-and-only root-seeded walk fires roughly one second after {@code startThread()}, or earlier
 * if woken by a GC-finish signal - a race {@code ReferenceChainTrackingTest}'s own
 * {@code shouldReportAbandonedSearchOnTinyFrontierCap()} comment already documents ("that wakeup
 * can race the thread's own startup ... and be missed"). An initial in-process attempt at this
 * exact scenario created {@code cache} and started allocating only *after* starting the profiler
 * (mirroring {@code ReferenceChainTrackingTest}'s {@code gcRootHolder}, which happened to work by
 * luck of scheduling in a warm, already-running JVM) - against a genuinely fresh, cold JVM this
 * lost the race essentially every time: the one-shot walk caught {@code cache} still empty,
 * permanently blocking discovery of everything added to it afterward (a frontier entry once
 * marked {@code EXPANDED} is never revisited for new children - see {@code expandFrontier()}'s
 * own comment). Seeding {@code cache} with real data *before* {@code profiler.execute()} is even
 * called removes the race entirely: no matter how fast the walk fires, {@code cache} is never
 * empty when it does.
 */
public final class LeakingCacheScenario {
  private LeakingCacheScenario() {}

  // Arbitrary, scenario-chosen klass id - this process's own LivenessTracker population table
  // treats it as an opaque key (see KlassPopulationEntry's own comment) and this process never
  // runs any other reference-chains scenario, so no collision risk with e.g.
  // ReferenceChainTrackingTest's/ReferenceChainTestSeamsTest's own klass ids in their own,
  // separate JVMs.
  private static final int CACHED_PAYLOAD_TEST_KLASS_ID = 987301;

  /** Printed to stdout, followed by the matched leaf class's name, on success. */
  public static final String FOUND_MARKER = "[chain-found] ";

  /** Printed to stdout (with no class name suffix) if no match was ever observed. */
  public static final String NOT_FOUND_MARKER = "[chain-not-found]";

  /**
   * Printed to stdout (with the offending class name appended) if a match was found but its
   * chain did not pass through {@code java.util.HashMap}'s own internal storage - see
   * {@code ExternalProcessReferenceChainTest} for why this is asserted in the parent process
   * rather than here (keeping this scenario's own stdout contract to "found/not-found" and
   * leaving richer chain-shape assertions to the JUnit side, the same separation of concerns
   * {@code ReferenceChainJfrParserTest} already uses for the lower-level JFR-format proof).
   */
  public static final String NO_HASHMAP_INTERNALS_MARKER = "[chain-found-no-hashmap-internals] ";

  /**
   * Seeds {@code cache} with an initial batch, *then* starts the profiler (see this class's own
   * comment for why that order is load-bearing), then runs the same population-growth loop
   * {@code ReferenceChainTrackingTest} pioneered - dumping to {@code scratchDumpPath} after every
   * round (and a short grace period beyond the last round) until a {@code datadog.ReferenceChain}
   * event whose {@code chain[0]} is {@link CachedPayload} appears - then prints exactly one
   * result line to stdout. Called from {@code ExternalLauncher} (a different package - hence
   * {@code public}), which owns the generic child-process bootstrap (JVMTI/library init, process
   * exit) this scenario deliberately stays agnostic of; starting the profiler itself happens
   * here, not in {@code ExternalLauncher}, specifically so {@code cache} can be seeded first.
   */
  public static void run(JavaProfiler profiler, String startCommand, Path scratchDumpPath) throws Exception {
    Map<String, CachedPayload> cache = new HashMap<>();
    seedInitialBatch(cache, 300);
    System.out.println("[debug] startCommand=" + startCommand);
    System.out.println("[debug] scratchDumpPath=" + scratchDumpPath);
    if (startCommand != null && !startCommand.isEmpty()) {
      profiler.execute(startCommand);
    }
    System.out.println("[debug] profiler.execute() returned");

    boolean debugBuild = "debug".equals(System.getProperty("ddprof_test.config"));
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
        // Same debug-only, seeded-representative short-circuit as ReferenceChainTrackingTest's
        // own shouldReconstructReferrerChainThroughUnboundedCacheLeak() (see that method's own
        // comment): decouples this scenario's assertion from whether the real, probabilistic
        // allocation-sampling-driven slope detection happens to notice CachedPayload's own
        // population trend within this scenario's fixed round/timeout budget. "seed-0" (from
        // seedInitialBatch()) is reachable via cache for the scenario's entire lifetime, so it
        // is a safe, always-valid representative regardless of which round this fires on.
        if (!seededTestKlassTrend) {
          for (int epoch = 1; epoch <= 10; epoch++) {
            JavaProfiler.seedKlassPopulationSample0(CACHED_PAYLOAD_TEST_KLASS_ID, epoch * 10, epoch);
          }
          seededTestKlassTrend = true;
        }
        JavaProfiler.setKlassPopulationRepresentativeForTest0(CACHED_PAYLOAD_TEST_KLASS_ID, cache.get("seed-0"));
        JavaProfiler.pollReferenceChainTargets0();
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
    System.out.println(FOUND_MARKER + match.chain.get(0).getFullName());
  }

  /**
   * Populates {@code cache} with {@code count} entries under a key namespace ("seed-") disjoint
   * from the round loop's own ("leak-") - called before the profiler (and therefore
   * {@code ReferenceChainTracker}'s BFS thread) even starts, so the process's one-shot
   * root-seeded walk can never catch {@code cache} empty (see this class's own comment on why
   * that race is otherwise real).
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
   * Realistic-leak fixture - identical shape to {@code ReferenceChainTrackingTest}'s own
   * (now-removed) in-process attempt. The 32 {@code long} fields exist purely so a given number
   * of megabytes needs far fewer entries to reach {@code ObjectSampler}'s real 256KiB sampling
   * floor - deliberately plain fields, not a nested array (a same-instance companion array would
   * be a *second*, separate heap allocation the size-weighted allocation sampler would compete
   * for, taking sampling attention away from {@code CachedPayload} itself).
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
