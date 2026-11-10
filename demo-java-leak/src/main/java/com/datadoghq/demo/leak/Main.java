/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.util.Locale;
import java.util.concurrent.Executors;

/**
 * Entry point of the demo leak app: a self-contained HTTP service that steadily leaks
 * request-scoped state.
 *
 * <p>The app takes no arguments. It starts a {@code HttpServer} on an ephemeral port and then runs
 * a single self-traffic loop that issues HTTP requests to its own server, so both the traffic and
 * the leak go through the real handler path - no external client is needed. The loop never exits;
 * shutdown is by process kill.
 *
 * <p>Leak-shape rationale, in the spirit of {@code ReferenceChainLeakDemo} in {@code
 * ddprof-stresstest} - every choice below exists because leaving it out produces zero
 * reference-chain events, silently:
 *
 * <ul>
 *   <li>{@code System.gc()} is forced every round. The profiler's per-klass population trend only
 *       advances on garbage-collection-finish callbacks, and a quiet heap under {@code -Xmx512m}
 *       may not GC often enough on its own to feed the trend.
 *   <li>The {@link RequestCache} has no cap and no eviction. A flat or capped population stops
 *       being a rising trend, and a periodically-reset population produces flat stretches that push
 *       the trend slope back to zero.
 *   <li>Growth is paced, and each round the {@link HeapWatermark} is checked: when post-GC
 *       occupancy crosses {@link HeapWatermark#HIGH_WATERMARK} the whole cache is dropped in one
 *       {@link RequestCache#flush()} step, so the JVM never exhausts the heap, and growth resumes
 *       from an empty cache. Each growth phase lasts on the order of an hour - far longer than the
 *       roughly fifteen GC epochs the trend qualification needs at one forced GC per round - so the
 *       leak cycles are long, steady windows rather than noise.
 * </ul>
 */
public final class Main {

  // Pacing: one retained entry costs roughly 408 bytes of heap (~272 B RequestState object,
  // ~56 B id string, ~32 B HashMap node per map - the entries map and the listener
  // registry - ~16 B listener closure), so growing from a near-empty heap to the 75% high
  // watermark of -Xmx512m (~384 MiB of retained entries) takes about 1M entries. At
  // REQUESTS_PER_ROUND requests per ROUND_INTERVAL_MS round
  // (250 per second) a full growth phase lasts roughly 70 minutes - over the ~1 h target
  // and far longer than the ~15 s the trend qualification needs at this GC rate. The rate
  // also stays low relative to the target pod's 2 CPUs: each request is a tiny localhost
  // round trip.
  private static final int REQUESTS_PER_ROUND = 250;
  private static final long ROUND_INTERVAL_MS = 1_000L;

  // Status line cadence: once per LOG_EVERY_ROUNDS rounds, i.e. about once a minute.
  private static final int LOG_EVERY_ROUNDS = 60;

  private Main() {}

  /**
   * Starts the HTTP server on an ephemeral port and enters the self-traffic loop, which never
   * returns. The loop serves the app's own requests, leaks one request state per handled request,
   * forces a GC every round and flushes the cache when post-GC occupancy crosses the high
   * watermark.
   */
  public static void main(String[] args) throws IOException {
    // sun.net.httpserver.nodelay (documented on the jdk.httpserver module) sets
    // TCP_NODELAY on every accepted connection; the default (false) lets Nagle's
    // algorithm hold the 3-byte response body back until the delayed-ACK timer fires,
    // stalling each keep-alive response by ~40 ms. At the demo's 250 req/s self-traffic
    // that is ~10 s of stalls per round - ten times the 1 s round interval. The server
    // reads the property once at class load, so it must be set before the first
    // HttpServer.create below.
    System.setProperty("sun.net.httpserver.nodelay", "true");
    RequestCache cache = new RequestCache();
    HttpServer server = HttpServer.create(new InetSocketAddress(0), 0);
    server.createContext("/", new HttpLeakHandler(cache));
    // Two handler threads: the app keeps one self-request in flight at a time, and the
    // second slot keeps an external probe (for example a smoke-test curl) from queueing
    // behind it.
    server.setExecutor(Executors.newFixedThreadPool(2));
    server.start();
    int port = server.getAddress().getPort();
    System.out.println(
        "[leak-demo] serving on port "
            + port
            + ", self-traffic "
            + REQUESTS_PER_ROUND
            + " requests per "
            + ROUND_INTERVAL_MS
            + " ms, no exit path");
    selfTrafficLoop(cache, port);
  }

  /**
   * The app's whole life, one round at a time. Each round issues the round's self-traffic, forces a
   * GC, checks the watermark, and sleeps out the rest of the round interval. The forced GC must
   * precede the watermark check: the watermark reads post-GC usage, and the profiler's GC-epoch
   * counter (which the population trend keys on) only advances on garbage-collection-finish
   * callbacks. Never returns.
   */
  private static void selfTrafficLoop(RequestCache cache, int port) {
    HttpClient client = HttpClient.newHttpClient();
    HttpRequest request =
        HttpRequest.newBuilder(URI.create("http://127.0.0.1:" + port + "/"))
            .GET()
            .timeout(Duration.ofSeconds(5))
            .build();
    HeapWatermark watermark = new HeapWatermark();
    long round = 0;
    // Persistent-failure escalation: a dead handler thread or a wedged executor must not
    // keep burning a full round of failing requests without notice. One WARN per failure
    // episode; a clean round ends the episode so a new one re-warns.
    int consecutiveFailureRounds = 0;
    boolean persistentFailureWarned = false;
    while (true) {
      long roundStartNanos = System.nanoTime();
      round++;
      int failures = issueRequests(client, request, REQUESTS_PER_ROUND);
      if (failures > 0) {
        System.out.println("[leak-demo] round=" + round + " self-request failures=" + failures);
        consecutiveFailureRounds++;
        if (consecutiveFailureRounds >= 2 && !persistentFailureWarned) {
          System.out.println(
              "[leak-demo] WARN round="
                  + round
                  + " self-request failures persist across consecutive rounds ("
                  + failures
                  + " in the latest round)");
          persistentFailureWarned = true;
        }
      } else {
        consecutiveFailureRounds = 0;
        persistentFailureWarned = false;
      }
      System.gc();
      if (watermark.shouldFlush()) {
        int flushed = cache.flush();
        System.out.println("[leak-demo] flushed " + flushed + " retained entries");
      }
      if (round % LOG_EVERY_ROUNDS == 0) {
        System.out.println(
            "[leak-demo] round="
                + round
                + " retained="
                + cache.retainedCount()
                + " removals="
                + cache.removalsObserved()
                + " heapUsedFraction="
                + String.format(Locale.ROOT, "%.3f", watermark.heapUsedFraction()));
      }
      sleepUntilNextRound(roundStartNanos);
    }
  }

  /**
   * Issues {@code count} sequential GETs to the app's own server, so every recorded state goes
   * through the real handler path. Returns the number of requests that did not complete with a 200.
   * Failures never stop the loop: they are reported once per round they occur in, a round is
   * abandoned early once more than ten of its requests fail (a round that degraded that far will
   * not feed the trend anyway), and the app itself has no exit path by design.
   */
  private static int issueRequests(HttpClient client, HttpRequest request, int count) {
    int failures = 0;
    for (int i = 0; i < count; i++) {
      try {
        HttpResponse<Void> response = client.send(request, HttpResponse.BodyHandlers.discarding());
        if (response.statusCode() != 200) {
          failures++;
          if (failures > 10) {
            // A round already degraded past ten failures will not feed the trend anyway;
            // abandon it early instead of burning the rest of the round's requests.
            break;
          }
        }
      } catch (IOException e) {
        failures++;
        if (failures > 10) {
          // Same early abandonment for I/O failures: with the 5s request timeout this
          // bounds a wedged-but-accepting server to at most ~11 timeouts (~55 s) a round.
          break;
        }
      } catch (InterruptedException e) {
        failures++;
        // Interruption is not a shutdown signal for this app (shutdown is by process
        // kill), and the InterruptedException already cleared the flag, so the loop
        // simply continues with the round's remaining requests.
      }
    }
    return failures;
  }

  /**
   * Sleeps out the remainder of the round interval, measured from the round's start, so a slow
   * round (for example a long GC) does not further delay the next one: when the round overran the
   * interval, the next round starts immediately and pacing self-corrects.
   */
  private static void sleepUntilNextRound(long roundStartNanos) {
    long elapsedMillis = (System.nanoTime() - roundStartNanos) / 1_000_000L;
    long sleepMillis = ROUND_INTERVAL_MS - elapsedMillis;
    if (sleepMillis > 0) {
      try {
        Thread.sleep(sleepMillis);
      } catch (InterruptedException e) {
        // Not a shutdown signal for this app: clear the flag and keep the loop running.
        Thread.interrupted();
      }
    }
  }
}
