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
 * second, competing heap allocation per entry. The state itself carries no removal
 * callback: the cache's own listener registry holds a closure capturing each state, which
 * is the Java analog of a cache library whose per-entry eviction callbacks pin the entries
 * they observe - the second retention path besides the entries map.
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
}
