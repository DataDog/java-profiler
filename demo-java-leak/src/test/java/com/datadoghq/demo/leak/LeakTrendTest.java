/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryPoolMXBean;
import java.lang.management.MemoryType;
import java.lang.management.MemoryUsage;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

/**
 * The demo's leak cycle, end to end, on the real components and under the app's heap
 * budget ({@code -Xmx512m}, wired into this module's test task): a real {@code
 * jdk.httpserver} serving the app's own {@link HttpLeakHandler} self-traffic, one forced
 * GC per round - the pacing the app uses, because a sampled per-klass population only
 * becomes a rising trend across GC epochs - and post-GC occupancy read through {@link
 * HeapWatermark}'s {@code MemoryPoolMXBean} collection-usage path.
 *
 * <p>The assertions are the trend gates the demo exists to satisfy: post-GC occupancy
 * must rise monotonically across at least 10 consecutive GC cycles and must reach those
 * cycles well inside 5 minutes; the watermark flush must fire when post-GC occupancy
 * crosses {@link HeapWatermark#HIGH_WATERMARK} and drop every retained entry in one step;
 * and growth must resume after the flush. A weak-reference cache, a silent eviction path
 * or a broken watermark each fail a hard assertion here - nothing is printed.
 */
final class LeakTrendTest {

  // ~19 MiB of retained state per round at ~400 B per recorded request: large enough
  // that each round's growth dominates post-GC reporting noise, small enough that the
  // watermark is reached in minutes of loopback self-traffic. This mirrors Main's loop
  // shape with a round size scaled for a bounded test instead of an hour-long growth
  // phase; Main's own loop constants are not injectable and pace for production.
  private static final int REQUESTS_PER_ROUND = 50_000;

  // The trend qualification the tests must preserve: at least 10 consecutive GC cycles
  // with rising post-GC occupancy before the flush, and enough rounds after the flush to
  // prove growth resumed.
  private static final int PRE_FLUSH_MONOTONIC_SAMPLES = 10;
  private static final int POST_FLUSH_MONOTONIC_SAMPLES = 5;

  // Hard stop for a loop that would otherwise spin forever if the watermark never
  // fires; the @Timeout annotation is the outer bound.
  private static final int MAX_ROUNDS = 200;

  private static final long FIVE_MINUTES_MILLIS = TimeUnit.MINUTES.toMillis(5);

  @Test
  @Timeout(value = 10, unit = TimeUnit.MINUTES)
  void postGcOccupancyTrendsUpFlushesAtWatermarkAndRegrows() throws Exception {
    RequestCache cache = new RequestCache();
    HttpServer server = HttpServer.create(new InetSocketAddress(0), 0);
    server.createContext("/", new HttpLeakHandler(cache));
    ExecutorService handlerPool = Executors.newFixedThreadPool(2);
    server.setExecutor(handlerPool);
    server.start();
    HeapWatermark watermark = new HeapWatermark();
    HttpClient client = HttpClient.newHttpClient();
    HttpRequest request =
        HttpRequest.newBuilder(URI.create("http://127.0.0.1:" + server.getAddress().getPort() + "/"))
            .GET()
            .build();

    long testStartNanos = System.nanoTime();
    List<Sample> preFlush = new ArrayList<>();
    List<Sample> postFlush = new ArrayList<>();
    // Retention expected between flushes: one entry per handled request, no more, no
    // less - re-checked after every round.
    long expectedRetained = 0;
    boolean flushed = false;
    double fractionAtFlush = -1.0;
    try {
      for (int round = 1; round <= MAX_ROUNDS; round++) {
        issueRequests(client, request, REQUESTS_PER_ROUND);
        expectedRetained += REQUESTS_PER_ROUND;
        // One forced GC per round, exactly like the app: the sample below must be the
        // post-GC view, and the trend the demo feeds only advances on GC finish.
        System.gc();
        double fraction = watermark.heapUsedFraction();
        if (flushed) {
          postFlush.add(new Sample(fraction, elapsedMillis(testStartNanos)));
        } else {
          preFlush.add(new Sample(fraction, elapsedMillis(testStartNanos)));
          if (watermark.shouldFlush()) {
            fractionAtFlush = fraction;
            flushed = true;
            int dropped = cache.flush();
            assertEquals(expectedRetained, dropped, "flush must drop every retained entry");
            assertEquals(0, cache.retainedCount());
            expectedRetained = 0;
          }
        }
        assertEquals(expectedRetained, cache.retainedCount(), "retention after round " + round);
        if (flushed
            && longestStrictlyIncreasingRun(postFlush) >= POST_FLUSH_MONOTONIC_SAMPLES) {
          break;
        }
      }
    } finally {
      server.stop(0);
      handlerPool.shutdown();
    }
    if (!flushed) {
      fail(
          "watermark flush never occurred within "
              + MAX_ROUNDS
              + " rounds (last post-GC fraction "
              + (preFlush.isEmpty() ? -1.0 : preFlush.get(preFlush.size() - 1).fraction())
              + ")");
    }

    // Growth phase: post-GC occupancy rises across >= 10 consecutive GC cycles, reached
    // within 5 minutes.
    int preFlushRun = longestStrictlyIncreasingRun(preFlush);
    assertTrue(
        preFlushRun >= PRE_FLUSH_MONOTONIC_SAMPLES,
        "expected at least "
            + PRE_FLUSH_MONOTONIC_SAMPLES
            + " consecutive rising post-GC samples, best run was "
            + preFlushRun
            + " over "
            + preFlush.size()
            + " samples");
    long tenCyclesMillis =
        millisWhenStrictlyIncreasingRunReached(preFlush, PRE_FLUSH_MONOTONIC_SAMPLES);
    assertTrue(
        tenCyclesMillis < FIVE_MINUTES_MILLIS,
        PRE_FLUSH_MONOTONIC_SAMPLES
            + " consecutive rising post-GC samples took "
            + tenCyclesMillis
            + " ms, limit "
            + FIVE_MINUTES_MILLIS
            + " ms");

    // Flush: the decision fired at or above the watermark and occupancy dropped.
    assertTrue(
        fractionAtFlush >= HeapWatermark.HIGH_WATERMARK,
        "flush fired at post-GC fraction " + fractionAtFlush);
    assertTrue(
        !postFlush.isEmpty(), "growth must resume after the flush (no samples observed)");
    assertTrue(
        postFlush.get(0).fraction() < fractionAtFlush,
        "first post-flush post-GC fraction "
            + postFlush.get(0).fraction()
            + " must be below the flush-time fraction "
            + fractionAtFlush);
    // Resumed growth: the post-flush samples rise across consecutive GC cycles again.
    int postFlushRun = longestStrictlyIncreasingRun(postFlush);
    assertTrue(
        postFlushRun >= POST_FLUSH_MONOTONIC_SAMPLES,
        "expected at least "
            + POST_FLUSH_MONOTONIC_SAMPLES
            + " consecutive rising post-GC samples after the flush, best run was "
            + postFlushRun
            + " over "
            + postFlush.size()
            + " samples");

    // Across the whole cycle, including the flush, no per-entry removal ever fired.
    assertEquals(0, cache.removalsObserved(), "no eviction may fire across a full cycle");
    assertNull(cache.lastRemovedId());
  }

  @Test
  void heapWatermarkSkipsPoolsWithoutCollectionUsageAndFallsBackToCurrentUsage()
      throws Exception {
    long beanUsed = 64L << 20;
    long beanMax = 512L << 20;
    MemoryMXBean memory = memoryBean(new MemoryUsage(-1, beanUsed, 256L << 20, beanMax));
    // A heap pool whose collection usage is unsupported (null) must be skipped; with no
    // pool left reporting, the fraction falls back to the MemoryMXBean's current heap
    // usage over its max.
    MemoryPoolMXBean heapWithoutUsage =
        pool("heap-no-collection-usage", MemoryType.HEAP, null);
    HeapWatermark watermark = inject(memory, List.of(heapWithoutUsage));
    assertEquals((double) beanUsed / beanMax, watermark.heapUsedFraction(), 1e-9);
    assertFalse(watermark.shouldFlush(), "64 of 512 MiB is far below the watermark");
  }

  @Test
  void heapWatermarkConsidersOnlyHeapPools() throws Exception {
    // The pool-type filter runs in the constructor, before any of the fraction code, so
    // it is verified on the real wiring: every pool the watermark kept must be a heap
    // pool. (The degenerate-branch tests below inject an already-filtered list.)
    HeapWatermark watermark = new HeapWatermark();
    Field heapPools = HeapWatermark.class.getDeclaredField("heapPools");
    heapPools.setAccessible(true);
    @SuppressWarnings("unchecked")
    List<MemoryPoolMXBean> pools = (List<MemoryPoolMXBean>) heapPools.get(watermark);
    assertFalse(pools.isEmpty(), "a JVM always reports heap pools");
    for (MemoryPoolMXBean pool : pools) {
      assertEquals(MemoryType.HEAP, pool.getType(), "pool " + pool.getName());
    }
  }

  @Test
  void heapWatermarkSumsHeapPoolCollectionUsageAndFallsBackToRuntimeMax() throws Exception {
    // Heap max undefined (-1): the fraction must be paced against Runtime.maxMemory().
    MemoryMXBean memory = memoryBean(new MemoryUsage(-1, 8L << 20, 64L << 20, -1));
    long edenUsed = 96L << 20;
    long oldUsed = 160L << 20;
    MemoryPoolMXBean eden = pool("eden", MemoryType.HEAP, new MemoryUsage(-1, edenUsed, edenUsed, edenUsed));
    MemoryPoolMXBean old = pool("old", MemoryType.HEAP, new MemoryUsage(-1, oldUsed, oldUsed, oldUsed));
    HeapWatermark watermark = inject(memory, List.of(eden, old));
    double expected = (double) (edenUsed + oldUsed) / Runtime.getRuntime().maxMemory();
    assertEquals(expected, watermark.heapUsedFraction(), 1e-9);
    // The flush decision must follow the computed fraction, whichever side of the
    // watermark the test JVM's max heap puts it on.
    assertEquals(expected >= HeapWatermark.HIGH_WATERMARK, watermark.shouldFlush());
  }

  @Test
  void heapWatermarkFlushDecisionMatchesTheWatermarkBoundary() throws Exception {
    long max = 512L << 20;
    // Exactly at the watermark: the decision is >=, so this must flush.
    long atWatermark = (long) (max * HeapWatermark.HIGH_WATERMARK);
    HeapWatermark atLimit =
        inject(
            memoryBean(new MemoryUsage(-1, 16L << 20, max, max)),
            List.of(pool("old", MemoryType.HEAP, new MemoryUsage(-1, atWatermark, max, max))));
    assertTrue(atLimit.shouldFlush(), "post-GC fraction at the watermark must flush");
    // One byte below: must not flush.
    HeapWatermark belowLimit =
        inject(
            memoryBean(new MemoryUsage(-1, 16L << 20, max, max)),
            List.of(pool("old", MemoryType.HEAP, new MemoryUsage(-1, atWatermark - 1, max, max))));
    assertFalse(belowLimit.shouldFlush(), "post-GC fraction below the watermark must not flush");
  }

  /**
   * Issues {@code count} sequential GETs to the app's own server, failing fast on the
   * first request that does not complete with a 200: the trend assertions below compare
   * retained counts against handled requests, so a failed request must abort here with
   * its cause instead of producing a confusing count mismatch later.
   */
  private static void issueRequests(HttpClient client, HttpRequest request, int count) {
    for (int i = 0; i < count; i++) {
      try {
        HttpResponse<Void> response =
            client.send(request, HttpResponse.BodyHandlers.discarding());
        if (response.statusCode() != 200) {
          throw new AssertionError("self-request " + i + " answered " + response.statusCode());
        }
      } catch (IOException e) {
        throw new AssertionError("self-request " + i + " failed", e);
      } catch (InterruptedException e) {
        Thread.interrupted();
        throw new AssertionError("self-request " + i + " interrupted", e);
      }
    }
  }

  /** Longest run of samples where each fraction is strictly greater than the previous. */
  private static int longestStrictlyIncreasingRun(List<Sample> samples) {
    int best = 0;
    int run = 0;
    for (int i = 0; i < samples.size(); i++) {
      run = i > 0 && samples.get(i).fraction() > samples.get(i - 1).fraction() ? run + 1 : 1;
      best = Math.max(best, run);
    }
    return best;
  }

  /**
   * Elapsed milliseconds at the moment the strictly-increasing run first reached {@code
   * target} samples, or {@code -1} if it never did. The samples carry their own
   * timestamps, so the 5-minute budget is measured against the moment the run completed,
   * not against when the assertion runs.
   */
  private static long millisWhenStrictlyIncreasingRunReached(List<Sample> samples, int target) {
    int run = 0;
    for (int i = 0; i < samples.size(); i++) {
      run = i > 0 && samples.get(i).fraction() > samples.get(i - 1).fraction() ? run + 1 : 1;
      if (run == target) {
        return samples.get(i).elapsedMillis();
      }
    }
    return -1;
  }

  private static long elapsedMillis(long startNanos) {
    return (System.nanoTime() - startNanos) / 1_000_000L;
  }

  private record Sample(double fraction, long elapsedMillis) {}

  /**
   * Replaces a fresh watermark's platform beans with the given fakes. {@link
   * HeapWatermark} wires the {@code ManagementFactory} beans in its constructor and the
   * app deliberately has no injection surface, so the degenerate-limit branches (a pool
   * that reports no collection usage, an undefined heap max) - which a healthy JVM never
   * reports - are only reachable by swapping the two private fields.
   */
  private static HeapWatermark inject(MemoryMXBean memory, List<MemoryPoolMXBean> pools)
      throws Exception {
    HeapWatermark watermark = new HeapWatermark();
    setField(watermark, "memoryBean", memory);
    setField(watermark, "heapPools", pools);
    return watermark;
  }

  private static void setField(Object target, String name, Object value) throws Exception {
    Field field = target.getClass().getDeclaredField(name);
    field.setAccessible(true);
    field.set(target, value);
  }

  private static MemoryMXBean memoryBean(MemoryUsage heapUsage) {
    return fake(
        MemoryMXBean.class,
        (proxy, method, args) -> {
          if ("getHeapMemoryUsage".equals(method.getName())) {
            return heapUsage;
          }
          throw new UnsupportedOperationException(method.getName());
        });
  }

  private static MemoryPoolMXBean pool(String name, MemoryType type, MemoryUsage collectionUsage) {
    return fake(
        MemoryPoolMXBean.class,
        (proxy, method, args) -> {
          switch (method.getName()) {
            case "getName":
              return name;
            case "getType":
              return type;
            case "getCollectionUsage":
              return collectionUsage;
            case "toString":
              return name;
            case "hashCode":
              return System.identityHashCode(proxy);
            case "equals":
              return proxy == args[0];
            default:
              throw new UnsupportedOperationException(method.getName());
          }
        });
  }

  private static <T> T fake(Class<T> type, InvocationHandler handler) {
    return type.cast(
        Proxy.newProxyInstance(
            LeakTrendTest.class.getClassLoader(), new Class<?>[] {type}, handler));
  }
}
