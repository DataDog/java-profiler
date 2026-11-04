/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import java.util.Objects;

/**
 * Request-scoped state object retained by the demo's leaking {@link RequestCache}.
 *
 * <p>The field shape is deliberate and matches {@code ReferenceChainLeakDemo.CachedEntry} in
 * {@code ddprof-stresstest}: a key string plus plain {@code long} fields, not a nested array,
 * so a single instance clears the allocation sampler's real size floor on its own, without a
 * second, competing heap allocation per entry. Every instance also carries a registered
 * removal-listener closure that captures the instance ({@link #registerRemovalListener}), the
 * Java analog of a cache library whose per-entry eviction callbacks pin the entries they
 * observe.
 *
 * <p>Leak-shape rationale: because the cache never evicts, every instance survives each GC,
 * so the retained population of this class grows monotonically across GC epochs. That rising
 * per-klass trend is the mechanism the profiler's reference-chain tracker keys on: a class
 * becomes a chain target only after its sampled population ring fills with rising values
 * over many GC epochs (the GC-epoch counter advances only on garbage-collection finish), so
 * this class is exactly the population the demo needs to keep rising.
 */
public final class RequestState {

  // Plain long fields, not a nested array: one instance then clears the allocation
  // sampler's size floor by itself (same shape as ReferenceChainLeakDemo.CachedEntry in
  // ddprof-stresstest). They are deliberately left at their default 0 - the object exists
  // to be retained, and its fields are never written or read.
  private long p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
  private long p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30,
      p31;

  private final String id;

  // Registered once by the cache on the server's handler thread and read back from other
  // threads only for verification, hence volatile.
  private volatile Runnable removalListener;

  /**
   * Creates the state for the request identified by {@code id}.
   *
   * @param id unique request-scoped key this state is recorded under
   */
  public RequestState(String id) {
    this.id = Objects.requireNonNull(id, "id");
  }

  /** The unique request-scoped key this state was recorded under. */
  public String id() {
    return id;
  }

  /**
   * Registers the cache's removal callback for this entry. The closure handed in captures
   * this instance, so the entry is retained through the listener as well as through the
   * cache map - the second, closure-based retention path of the leak shape.
   *
   * @param listener removal callback capturing this instance
   */
  public void registerRemovalListener(Runnable listener) {
    this.removalListener = Objects.requireNonNull(listener, "listener");
  }

  /**
   * The registered removal callback, or {@code null} before registration. Verification
   * accessor for the closure-based retention path: the returned closure must be capturing
   * (non-null for every recorded entry) while the cache never evicts, so it never fires.
   */
  public Runnable removalListener() {
    return removalListener;
  }
}
