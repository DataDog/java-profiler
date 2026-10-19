/*
 * Copyright 2026, Datadog, Inc.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

package com.datadoghq.profiler.referencechains;

import com.datadoghq.profiler.ReferenceChainTestHooks;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.TimeUnit;

/**
 * A single long-lived thread that runs caller-supplied allocation batches on demand.
 *
 * <p>Tests use one persistent thread so every instance of the leak klass is allocated by the
 * same thread: a fresh short-lived thread per round gets a new tid each time, and the per-tid
 * trend qualification ages out before the population trend can establish itself (the flake the
 * {@code @Order(1)} test documents). Callers must also seed with this thread's tid, obtained
 * from {@link #tid()} - captured on the allocator thread itself, never the caller's.
 *
 * <p>{@link #run(Runnable)} blocks until the batch completes and rethrows any failure from the
 * allocator thread, so allocations are finished (and any exception surfaced) before the caller
 * proceeds to {@code System.gc()} or a dump.
 */
final class PersistentAllocator implements AutoCloseable {
  // Poison task handed to the worker by close(); identity compared, never run.
  private static final Runnable CLOSE = () -> { };

  private static final long HANDOFF_TIMEOUT_SECONDS = 30;

  private final SynchronousQueue<Runnable> handoff = new SynchronousQueue<>();
  // Worker-to-caller completion slot: an Object marker = success, a Throwable = the batch's
  // failure. It is buffered (one slot) because the protocol is single-in-flight, and the
  // worker's offer() must retain the signal even when the batch finishes in the window
  // between the handoff rendezvous and the caller entering poll(): a SynchronousQueue would
  // drop that bare offer and turn a completed batch (or its rethrown failure) into a
  // 30-second poll timeout.
  private final ArrayBlockingQueue<Object> completion = new ArrayBlockingQueue<>(1);
  private final Thread thread;
  private volatile int tid;
  private volatile boolean closed;

  PersistentAllocator(String name) {
    thread = new Thread(this::loop, name);
    // Daemon: a test that dies before close() must not hold the JVM open on handoff.take().
    thread.setDaemon(true);
    thread.start();
    // The caller may call tid() immediately after construction (seed-before-wait ordering);
    // do not return until the allocator thread has published it.
    long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(HANDOFF_TIMEOUT_SECONDS);
    while (tid == 0 && thread.isAlive()) {
      if (System.nanoTime() - deadline > 0) {
        throw new IllegalStateException("allocator thread " + name + " never published its tid");
      }
      Thread.yield();
    }
    if (tid == 0) {
      throw new IllegalStateException("allocator thread " + name + " died before publishing its tid");
    }
  }

  /** The allocator thread's OS tid, captured by that thread itself at startup. */
  int tid() {
    return tid;
  }

  /**
   * Runs {@code task} on the allocator thread, blocking until it completes. A task that throws
   * is rethrown on the caller's thread, so a failed batch fails the test instead of stalling
   * the next round on partially-allocated state.
   */
  void run(Runnable task) {
    if (closed || !thread.isAlive()) {
      throw new IllegalStateException("allocator thread " + thread.getName() + " is no longer running");
    }
    try {
      // A previous run() that timed out left its outcome in the slot (the worker
      // finishes the abandoned task and offers into the then-empty queue). Drop it
      // before the handoff so it can never be attributed to this task: the worker is
      // parked at handoff.take() at this point, so nothing new can arrive between
      // the clear and the rendezvous.
      completion.clear();
      if (!handoff.offer(task, HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS)) {
        throw new IllegalStateException("allocator thread " + thread.getName() + " did not accept a task");
      }
      Object outcome = completion.poll(HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS);
      if (outcome == null) {
        throw new IllegalStateException("allocator thread " + thread.getName() + " never finished a task");
      }
      if (outcome instanceof RuntimeException) {
        throw (RuntimeException) outcome;
      }
      if (outcome instanceof Error) {
        throw (Error) outcome;
      }
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      throw new IllegalStateException("interrupted while waiting for allocator thread " + thread.getName(), e);
    }
  }

  /** Stops the allocator thread and waits for it to exit. Idempotent. */
  @Override
  public void close() {
    if (closed) {
      return;
    }
    closed = true;
    try {
      if (thread.isAlive() && handoff.offer(CLOSE, HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS)) {
        // Drain the exit acknowledgement so close() returns only after the thread is done.
        completion.poll(HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS);
      }
      thread.join(TimeUnit.SECONDS.toMillis(HANDOFF_TIMEOUT_SECONDS));
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
  }

  private void loop() {
    tid = ReferenceChainTestHooks.getTid();
    try {
      while (true) {
        Runnable task = handoff.take();
        if (task == CLOSE) {
          completion.offer(new Object()); // exit acknowledgement; no further work arrives
          return;
        }
        Object outcome = null;
        try {
          task.run();
        } catch (RuntimeException | Error t) {
          outcome = t;
        }
        completion.offer(outcome != null ? outcome : new Object());
      }
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
  }
}
