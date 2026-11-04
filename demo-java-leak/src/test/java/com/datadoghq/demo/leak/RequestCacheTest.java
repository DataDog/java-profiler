/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.reflect.Field;
import java.util.Map;
import org.junit.jupiter.api.Test;

/**
 * Tests the leak mechanism itself: an unbounded, strongly-referencing {@link
 * RequestCache}.
 *
 * <p>Every count assertion is exact equality, not {@code >=}: the invariant under test is
 * that retention is only removed by {@link RequestCache#flush()}, so a silent eviction
 * path, a size cap, or a weak/soft-reference map swap each fails some assertion here -
 * a weak map loses entries between the {@code System.gc()} and the observation, an
 * eviction path drops entries before the flush.
 */
final class RequestCacheTest {

  private static final String PREFIX = "request-cache-test-";

  @Test
  void retainedCountGrowsExactlyWithRecordedRequests() {
    RequestCache cache = new RequestCache();
    int recorded = 0;
    for (int batchSize : new int[] {1, 100, 5_000, 123_457}) {
      for (int i = 0; i < batchSize; i++) {
        cache.record(PREFIX + recorded++);
      }
      assertEquals(recorded, cache.retainedCount(), "after batch of " + batchSize);
    }
  }

  @Test
  void retainedCountDoesNotFallBackAcrossGc() {
    RequestCache cache = new RequestCache();
    for (int i = 0; i < 100_000; i++) {
      cache.record(PREFIX + i);
    }
    assertEquals(100_000, cache.retainedCount());
    System.gc();
    // A WeakHashMap-style map drops entries on the first collection after the strong
    // references go away; two post-GC observations pin the invariant down from both sides.
    assertEquals(100_000, cache.retainedCount(), "first post-GC observation");
    System.gc();
    assertEquals(100_000, cache.retainedCount(), "second post-GC observation");
    assertEquals(0, cache.removalsObserved(), "a GC must never evict a retained entry");
    assertNull(cache.lastRemovedId());
  }

  @Test
  void flushIsTheOnlyRemovalPathAndGrowthResumesAfterIt() {
    RequestCache cache = new RequestCache();
    for (int i = 0; i < 10_000; i++) {
      cache.record(PREFIX + i);
    }
    System.gc();
    assertEquals(10_000, cache.retainedCount(), "no removal may happen before the flush");
    int flushed = cache.flush();
    assertEquals(10_000, flushed, "flush must drop every retained entry");
    assertEquals(0, cache.retainedCount());
    // flush drops everything in one step without running the per-entry removal
    // callbacks: a non-zero value here means per-entry eviction crept into the flush.
    assertEquals(0, cache.removalsObserved());
    assertNull(cache.lastRemovedId());
    // Growth resumes from an empty cache, and ids from before the flush may be reused:
    // the duplicate check only spans retained entries.
    for (int i = 0; i < 500; i++) {
      cache.record(PREFIX + i);
    }
    assertEquals(500, cache.retainedCount());
    assertEquals(500, cache.flush());
  }

  @Test
  void duplicateIdRejected() {
    RequestCache cache = new RequestCache();
    cache.record("dup");
    IllegalStateException e =
        assertThrows(IllegalStateException.class, () -> cache.record("dup"));
    assertTrue(e.getMessage().contains("dup"), "message must name the colliding id");
    assertEquals(1, cache.retainedCount(), "a rejected record must not corrupt the cache");
  }

  @Test
  void nullIdRejected() {
    RequestCache cache = new RequestCache();
    assertThrows(NullPointerException.class, () -> cache.record(null));
    assertEquals(0, cache.retainedCount());
  }

  @Test
  void recordedEntryCarriesCapturingRemovalListener() throws Exception {
    RequestCache cache = new RequestCache();
    cache.record("listener-entry");
    // RequestCache registers its per-entry closure on the RequestState it stores, and the
    // cache exposes no accessor for it; the entries map is the only observation point.
    Map<String, RequestState> entries = entriesOf(cache);
    assertEquals(1, entries.size());
    RequestState state = entries.get("listener-entry");
    assertNotNull(state.removalListener(), "every recorded entry must register its listener");
    // Firing the closure is what eviction would do: it must observe the entry it captures,
    // which fails if the lambda is made non-capturing.
    state.removalListener().run();
    assertEquals(1, cache.removalsObserved());
    assertEquals("listener-entry", cache.lastRemovedId());
    // The callback is bookkeeping, not removal: retention is unchanged by a callback run.
    assertEquals(1, cache.retainedCount());
  }

  @Test
  void firedListenerReportsTheEntryItCaptured() throws Exception {
    RequestCache cache = new RequestCache();
    cache.record("listener-entry-a");
    cache.record("listener-entry-b");
    // Two distinct ids: a single-entry test cannot tell a closure that captures its own
    // entry's state from one that reports a constant (or another entry's) id, because
    // only one id would be in play. Firing ONLY entry A's listener pins which instance
    // the closure captured.
    Map<String, RequestState> entries = entriesOf(cache);
    assertEquals(2, entries.size());
    entries.get("listener-entry-a").removalListener().run();
    assertEquals("listener-entry-a", cache.lastRemovedId());
    assertEquals(1, cache.removalsObserved());
    // The callback is bookkeeping, not removal: firing one listener must not evict
    // either entry (retention is only removed by flush()).
    assertEquals(2, cache.retainedCount());
  }

  @Test
  void requestStateContract() {
    assertEquals("id-1", new RequestState("id-1").id());
    assertNull(new RequestState("id-2").removalListener(), "nothing registered yet");
    assertThrows(NullPointerException.class, () -> new RequestState(null));
    RequestState state = new RequestState("id-3");
    Runnable listener = () -> {};
    state.registerRemovalListener(listener);
    assertEquals(listener, state.removalListener(), "registration must keep the same closure");
    assertThrows(NullPointerException.class, () -> state.registerRemovalListener(null));
  }

  @SuppressWarnings("unchecked")
  private static Map<String, RequestState> entriesOf(RequestCache cache) throws Exception {
    Field entries = RequestCache.class.getDeclaredField("entries");
    entries.setAccessible(true);
    return (Map<String, RequestState>) entries.get(cache);
  }
}
