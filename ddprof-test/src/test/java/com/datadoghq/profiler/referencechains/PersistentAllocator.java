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

  // One unit of work handed to the worker; carries the caller-side generation
  // so the worker can echo it back in the Outcome. The CLOSE poison rides in a
  // Job too (generation -1, never a real generation).
  private static final class Job {
    final Runnable task;
    final int generation;

    Job(Runnable task, int generation) {
      this.task = task;
      this.generation = generation;
    }
  }

  // The worker's completion entry; the generation identifies which run()
  // produced it, so a stale outcome left by an abandoned (timed-out) run is
  // discarded by the caller instead of being misattributed to the next task.
  private static final class Outcome {
    final int generation;
    final Object result; // Object marker = success, a Throwable = the batch's failure

    Outcome(int generation, Object result) {
      this.generation = generation;
      this.result = result;
    }
  }

  private final SynchronousQueue<Job> handoff = new SynchronousQueue<>();
  // Worker-to-caller completion slot: an Outcome with the caller's generation
  // = this task's verdict (Object marker = success, a Throwable = the batch's
  // failure). It is buffered (one slot) because the protocol is single-in-flight,
  // and the worker's offer() must retain the signal even when the batch finishes
  // in the window between the handoff rendezvous and the caller entering poll():
  // a SynchronousQueue would drop that bare offer and turn a completed batch
  // (or its rethrown failure) into a 30-second poll timeout.
  private final ArrayBlockingQueue<Outcome> completion = new ArrayBlockingQueue<>(1);
  private final Thread thread;
  private volatile int tid;
  private volatile boolean closed;
  // Monotonic per-run() token; only the caller thread runs tasks through run(),
  // so plain int arithmetic is sufficient.
  private int nextGeneration;

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
      // A previous run() that timed out may still have its outcome parked in
      // the slot (the worker finishes the abandoned task and offers into the
      // then-empty queue). Drop what is already there; the generation check
      // below then discards any stale outcome that lands after this clear -
      // a plain clear alone cannot close that window, because the worker only
      // parks at handoff.take() AFTER offering the abandoned task's outcome.
      completion.clear();
      int generation = nextGeneration++;
      if (!handoff.offer(new Job(task, generation), HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS)) {
        throw new IllegalStateException("allocator thread " + thread.getName() + " did not accept a task");
      }
      long deadline = System.nanoTime() + TimeUnit.SECONDS.toNanos(HANDOFF_TIMEOUT_SECONDS);
      while (true) {
        Outcome outcome = completion.poll(deadline - System.nanoTime(), TimeUnit.NANOSECONDS);
        if (outcome == null) {
          throw new IllegalStateException("allocator thread " + thread.getName() + " never finished a task");
        }
        // Discard an abandoned earlier run()'s outcome and keep waiting for this
        // generation's verdict. The stale entry is always offered before our own:
        // the worker offers it before looping back to handoff.take(), through
        // which alone our Job can be accepted.
        if (outcome.generation != generation) {
          continue;
        }
        if (outcome.result instanceof RuntimeException) {
          throw (RuntimeException) outcome.result;
        }
        if (outcome.result instanceof Error) {
          throw (Error) outcome.result;
        }
        return;
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
      if (thread.isAlive() && handoff.offer(new Job(CLOSE, -1), HANDOFF_TIMEOUT_SECONDS, TimeUnit.SECONDS)) {
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
        Job job = handoff.take();
        if (job.task == CLOSE) {
          completion.offer(new Outcome(job.generation, new Object())); // exit acknowledgement; no further work arrives
          return;
        }
        Object outcome = null;
        try {
          job.task.run();
        } catch (RuntimeException | Error t) {
          outcome = t;
        }
        completion.offer(new Outcome(job.generation, outcome != null ? outcome : new Object()));
      }
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
  }
}
