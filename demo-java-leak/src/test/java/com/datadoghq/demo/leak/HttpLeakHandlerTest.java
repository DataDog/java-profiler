/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import static org.junit.jupiter.api.Assertions.assertEquals;

import com.sun.net.httpserver.HttpServer;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

/**
 * Drives {@link HttpLeakHandler} over a real in-process {@code jdk.httpserver}, the same way the
 * app serves its own traffic.
 *
 * <p>Each test asserts that every handled request retains exactly one state in the leaking cache
 * and answers 200 - so a handler that stops retaining, double-records, or reuses an id across a
 * {@link RequestCache#flush()} cycle (which makes {@code record} throw and fails the exchange)
 * fails one of these assertions.
 */
@Timeout(value = 2, unit = TimeUnit.MINUTES)
final class HttpLeakHandlerTest {

  static {
    // TCP_NODELAY on every accepted connection (sun.net.httpserver.nodelay, read once at
    // jdk.httpserver's ServerConfig class load): the handler writes the headers and the
    // 3-byte body separately, so with Nagle + delayed ACK each keep-alive response can
    // stall ~40 ms. Must be set before the first HttpServer.create below.
    System.setProperty("sun.net.httpserver.nodelay", "true");
  }

  private RequestCache cache;
  private HttpServer server;
  private ExecutorService handlerPool;
  private HttpClient client;
  private HttpRequest request;

  @BeforeEach
  void startServer() throws IOException {
    cache = new RequestCache();
    server = HttpServer.create(new InetSocketAddress(0), 0);
    server.createContext("/", new HttpLeakHandler(cache));
    handlerPool = Executors.newFixedThreadPool(2);
    server.setExecutor(handlerPool);
    server.start();
    client = HttpClient.newHttpClient();
    request =
        HttpRequest.newBuilder(
                URI.create("http://127.0.0.1:" + server.getAddress().getPort() + "/"))
            .GET()
            .build();
  }

  @AfterEach
  void stopServer() {
    server.stop(0);
    handlerPool.shutdown();
  }

  @Test
  void eachHandledRequestRetainsExactlyOneStateAndAnswers200() throws Exception {
    for (int i = 1; i <= 12; i++) {
      HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
      assertEquals(200, response.statusCode(), "request " + i);
      assertEquals("ok\n", response.body(), "response body must stay the constant payload");
      assertEquals(
          "text/plain; charset=utf-8",
          response.headers().firstValue("Content-Type").orElse(null),
          "request " + i);
      // Exactly one retained entry per handled request: the handler must keep retaining
      // and must never double-record.
      assertEquals(i, cache.retainedCount(), "after request " + i);
    }
  }

  @Test
  void requestIdsStayUniqueAcrossFlushCycles() throws Exception {
    for (int i = 0; i < 3; i++) {
      assertEquals(200, client.send(request, HttpResponse.BodyHandlers.discarding()).statusCode());
    }
    assertEquals(3, cache.retainedCount());
    assertEquals(3, cache.flush());
    assertEquals(0, cache.retainedCount());
    // The handler's id counter must never repeat, including across flushes: a reused id
    // makes record() throw, the exchange fails, and the request is not answered 200.
    for (int i = 0; i < 3; i++) {
      assertEquals(
          200,
          client.send(request, HttpResponse.BodyHandlers.discarding()).statusCode(),
          "post-flush request " + i);
    }
    assertEquals(3, cache.retainedCount());
  }

  @Test
  void concurrentRequestsEachRetainExactlyOneState() throws Exception {
    int requests = 32;
    List<Callable<Integer>> calls = new ArrayList<>(requests);
    for (int i = 0; i < requests; i++) {
      calls.add(() -> client.send(request, HttpResponse.BodyHandlers.discarding()).statusCode());
    }
    List<Future<Integer>> statuses;
    // Client-side threads overlap requests on the two handler threads, so the id counter
    // and the cache are exercised under real interleaving. The timed invokeAll is the
    // authoritative hang bound: a wedged handler would otherwise block here forever.
    ExecutorService callers = Executors.newFixedThreadPool(8);
    try {
      statuses = callers.invokeAll(calls, 30, TimeUnit.SECONDS);
    } finally {
      callers.shutdown();
    }
    for (int i = 0; i < requests; i++) {
      assertEquals(200, statuses.get(i).get(30, TimeUnit.SECONDS), "concurrent request " + i);
    }
    assertEquals(requests, cache.retainedCount());
  }
}
