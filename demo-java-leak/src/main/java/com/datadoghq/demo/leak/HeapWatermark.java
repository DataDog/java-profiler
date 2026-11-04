/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryPoolMXBean;
import java.lang.management.MemoryType;
import java.lang.management.MemoryUsage;
import java.util.List;

/**
 * Post-GC heap-occupancy watermark driving the demo's flush cycle.
 *
 * <p>Reads heap usage as of the most recent GC - the {@code MemoryPoolMXBean} collection
 * usage of the heap pools - rather than instantaneous usage, because the flush decision runs
 * right after the app's forced {@code System.gc()} and must judge the post-GC view the next
 * round of growth starts from. The cache is flushed whenever that post-GC occupancy reaches
 * {@link #HIGH_WATERMARK}, which keeps post-GC occupancy below the watermark under {@code
 * -Xmx512m} so the JVM never exhausts the heap, while each growth phase between flushes
 * lasts far longer than the GC-epoch span the reference-chain trend qualification needs.
 *
 * <p>An undefined heap max ({@code -1}, as reported in some container and ergonomics setups)
 * is handled the same way as {@code ReferenceChainLeakDemo.heapUsedFraction()} in {@code
 * ddprof-stresstest}: fall back to {@code Runtime.maxMemory()}, and if that is unbounded
 * too, report {@link #HIGH_WATERMARK} - never treat an unknown limit as an empty heap.
 */
public final class HeapWatermark {

  /**
   * Post-GC heap-occupancy fraction at which the app drops the whole cache in one flush.
   */
  public static final double HIGH_WATERMARK = 0.75;

  private final MemoryMXBean memoryBean;
  private final List<MemoryPoolMXBean> heapPools;
  private final long runtimeMax;

  /** Creates a watermark reading the JVM's current heap memory beans. */
  public HeapWatermark() {
    this(Runtime.getRuntime().maxMemory());
  }

  /**
   * Creates a watermark with an injected runtime max instead of the JVM's {@code
   * Runtime.maxMemory()}. Package-private so tests can force the unbounded-runtime-max
   * fallback (a healthy {@code -Xmx}-bounded JVM never reports an unbounded max); it is
   * deliberately not part of the public API.
   */
  HeapWatermark(long runtimeMax) {
    this.runtimeMax = runtimeMax;
    this.memoryBean = ManagementFactory.getMemoryMXBean();
    this.heapPools =
        ManagementFactory.getMemoryPoolMXBeans().stream()
            .filter(pool -> pool.getType() == MemoryType.HEAP)
            .toList();
  }

  /**
   * Heap used as a fraction of the heap max, measured post-GC: the sum of the heap pools'
   * collection usage, where each pool reports usage as of its most recent collection. Pools
   * that do not report collection usage (a pool can return {@code null} or negative values
   * for unsupported counters) are skipped; if none reports, the {@code MemoryMXBean}'s
   * current heap usage is the closest available figure - and the app forces a GC every
   * round, so it is normally the post-GC view anyway.
   *
   * <p>The max comes from the {@code MemoryMXBean}'s heap usage, falling back to {@code
   * Runtime.maxMemory()} when it is undefined. When even that is unbounded, the method
   * returns {@link #HIGH_WATERMARK} rather than zero, so growth is paced against the
   * watermark instead of mistaking an unknown limit for an empty heap.
   *
   * @return post-GC used fraction of the heap max; at least {@link #HIGH_WATERMARK} when
   *     the limit is unknown
   */
  public double heapUsedFraction() {
    long usedAfterGc = -1;
    for (MemoryPoolMXBean pool : heapPools) {
      MemoryUsage afterGc = pool.getCollectionUsage();
      if (afterGc != null && afterGc.getUsed() >= 0) {
        if (usedAfterGc < 0) {
          usedAfterGc = 0;
        }
        usedAfterGc += afterGc.getUsed();
      }
    }
    long max = memoryBean.getHeapMemoryUsage().getMax();
    if (max <= 0) {
      long runtimeMax = this.runtimeMax;
      if (runtimeMax <= 0 || runtimeMax == Long.MAX_VALUE) {
        return HIGH_WATERMARK;
      }
      max = runtimeMax;
    }
    if (usedAfterGc < 0) {
      usedAfterGc = memoryBean.getHeapMemoryUsage().getUsed();
    }
    return (double) usedAfterGc / (double) max;
  }

  /**
   * Whether the cache should be flushed this round: post-GC heap occupancy has reached
   * {@link #HIGH_WATERMARK}.
   */
  public boolean shouldFlush() {
    return heapUsedFraction() >= HIGH_WATERMARK;
  }
}
