/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.atomic.AtomicLong;

/**
 * The leak: an unbounded cache of request-scoped {@link RequestState} objects.
 *
 * <p>Every handled request is recorded here and stays recorded: there is no eviction, no
 * expiry and no size cap, so the retained population only grows and each entry survives
 * every GC. That is deliberate - the profiler's reference-chain tracker nominates a class
 * as a leak candidate only when its per-klass population shows a rising trend across many
 * GC epochs, and a flat or periodically-reset population produces zero chain events
 * silently. Each entry is retained two ways: directly, by the map's strong reference, and
 * through a registered removal-listener closure on the state that captures the instance.
 *
 * <p>Invariant: retention is only removed by {@link #flush()}. No other code path removes,
 * replaces or expires an entry.
 *
 * <p>Thread safety: methods are synchronized. The app itself keeps exactly one request in
 * flight at a time, but the HTTP server's small executor pool can overlap an external
 * request (for example a smoke-test curl) with the app's self-traffic, and a plain {@code
 * HashMap} must not see concurrent writes.
 */
public final class RequestCache {

  private final Map<String, RequestState> entries = new HashMap<>();

  // Eviction bookkeeping the per-entry removal callbacks would do. Both stay at their
  // initial values for the lifetime of the app: the callbacks never fire (see record),
  // which is exactly the observable proof that no eviction ever happened.
  private final AtomicLong removalsObserved = new AtomicLong();
  private volatile String lastRemovedId;

  /**
   * Records the request state for {@code id}: creates it, registers a removal-listener
   * closure that captures the instance, and stores it in the map. Invariant: retention is
   * only removed by {@link #flush()} - this method never removes, replaces or expires an
   * entry.
   *
   * @param id request-scoped key; must not collide with an id recorded since the last
   *     {@link #flush()}, otherwise the earlier entry would be silently replaced and
   *     retention would stop growing with the request count
   * @throws IllegalStateException if {@code id} is already retained
   */
  public synchronized void record(String id) {
    Objects.requireNonNull(id, "id");
    if (entries.containsKey(id)) {
      throw new IllegalStateException("request id already retained: " + id);
    }
    RequestState state = new RequestState(id);
    state.registerRemovalListener(
        () -> {
          // What a real removal listener would do on eviction. This callback never fires:
          // the cache never evicts, and flush() clears the map in one step without running
          // per-entry callbacks. The body must reference `state` so the closure is
          // capturing - a non-capturing lambda would pin nothing.
          removalsObserved.incrementAndGet();
          lastRemovedId = state.id();
        });
    entries.put(id, state);
  }

  /**
   * Number of request states currently retained. Only grows between calls to {@link
   * #flush()}; retention is only removed by {@code flush()}, never by eviction or a size
   * cap, so this count never falls back while the app keeps handling requests.
   */
  public synchronized int retainedCount() {
    return entries.size();
  }

  /**
   * Drops every retained entry in one step and returns how many were dropped. This is the
   * only code path that removes retention. It does not run the per-entry removal callbacks:
   * eviction bookkeeping is per-entry work that would cost one callback per retained request,
   * and the flush exists to drop everything at once. After a flush the retained population
   * restarts from zero and re-qualifies as a rising trend over the following GC epochs.
   */
  public synchronized int flush() {
    int retained = entries.size();
    entries.clear();
    return retained;
  }

  /**
   * Number of removal callbacks that have fired. Stays {@code 0} for the lifetime of the
   * app: the cache never evicts and {@link #flush()} does not run callbacks, so any
   * non-zero value would mean something started evicting entries and the leak shape is
   * broken. Logged by {@code Main} in its periodic status line.
   */
  public long removalsObserved() {
    return removalsObserved.get();
  }

  /**
   * The id of the entry whose removal callback fired last, or {@code null} if none ever
   * did. Diagnostic companion to {@link #removalsObserved()}: it stays {@code null} for the
   * lifetime of the app.
   */
  public String lastRemovedId() {
    return lastRemovedId;
  }
}
