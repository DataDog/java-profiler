/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.demo.leak;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicLong;

/**
 * The demo's only HTTP endpoint: every handled request leaks.
 *
 * <p>Each request gets a unique request-scoped id (a per-handler monotonic counter), and the
 * handler hands the resulting state to {@link RequestCache#record} - so the leak grows
 * through the real handler path, one retained entry per handled request. The response is a
 * tiny constant 200 body, so all response traffic stays fixed-size and the only growing
 * state is the retained request population.
 *
 * <p>Thread safety: the id counter is atomic and the cache synchronizes its methods, so
 * handler threads may run concurrently.
 */
public final class HttpLeakHandler implements HttpHandler {

  // Constant response payload: the response side must never grow, only the retained
  // request population does.
  private static final byte[] RESPONSE_BODY = "ok\n".getBytes(StandardCharsets.UTF_8);

  private final RequestCache cache;
  private final AtomicLong requestSequence = new AtomicLong();

  /**
   * Creates a handler that records every request it serves into {@code cache}.
   *
   * @param cache the leaking cache every handled request is recorded into
   */
  public HttpLeakHandler(RequestCache cache) {
    this.cache = cache;
  }

  /**
   * Handles one request: builds the unique request-scoped id, records it in the cache (the
   * leak), and answers with the fixed 200 body. The id is unique for this handler instance
   * for the lifetime of the process - the counter never repeats, so no id collides with a
   * retained entry, including across {@link RequestCache#flush()} cycles.
   */
  @Override
  public void handle(HttpExchange exchange) throws IOException {
    try {
      String id = "req-" + requestSequence.incrementAndGet();
      cache.record(id);
      exchange.getResponseHeaders().set("Content-Type", "text/plain; charset=utf-8");
      exchange.sendResponseHeaders(200, RESPONSE_BODY.length);
      try (OutputStream response = exchange.getResponseBody()) {
        response.write(RESPONSE_BODY);
      }
    } finally {
      exchange.close();
    }
  }
}
