/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
package com.datadoghq.profiler.nativemem;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * Creates glibc per-thread malloc arenas that hold free memory: each thread allocates blocks
 * through a reflective {@code Unsafe}, frees all but every 8th, and stays alive until {@link
 * #close()} so it keeps its arena. The surviving blocks pin the heap.
 */
final class MallocArenaChurn implements AutoCloseable {
  private static final int BLOCK_BYTES = 1024;
  private static final int SURVIVOR_STRIDE = 8;
  private static final Object UNSAFE;
  private static final Method ALLOCATE;
  private static final Method FREE;

  static {
    try {
      Class<?> unsafeClass = Class.forName("sun.misc.Unsafe");
      Field f = unsafeClass.getDeclaredField("theUnsafe");
      f.setAccessible(true);
      UNSAFE = f.get(null);
      ALLOCATE = unsafeClass.getMethod("allocateMemory", long.class);
      FREE = unsafeClass.getMethod("freeMemory", long.class);
    } catch (ReflectiveOperationException e) {
      throw new ExceptionInInitializerError(e);
    }
  }

  private final Thread[] threads;
  private final CountDownLatch allocated;
  private final CountDownLatch release = new CountDownLatch(1);

  MallocArenaChurn(int threadCount, int blocksPerThread) {
    threads = new Thread[threadCount];
    allocated = new CountDownLatch(threadCount);
    for (int i = 0; i < threadCount; i++) {
      threads[i] = new Thread(() -> work(blocksPerThread), "arena-churn-" + i);
      threads[i].setDaemon(true);
    }
  }

  /** Starts the threads and waits until each one has finished allocating and freeing. */
  void start() throws InterruptedException {
    for (Thread t : threads) {
      t.start();
    }
    if (!allocated.await(120, TimeUnit.SECONDS)) {
      throw new IllegalStateException("arena churn threads did not finish allocating");
    }
  }

  /** Lets the threads free the surviving blocks and waits for them to exit. */
  @Override
  public void close() throws InterruptedException {
    release.countDown();
    for (Thread t : threads) {
      t.join(30_000);
    }
  }

  private void work(int blocks) {
    long[] addresses = new long[blocks];
    for (int i = 0; i < blocks; i++) {
      addresses[i] = allocate(BLOCK_BYTES);
    }
    for (int i = 0; i < blocks; i++) {
      if (i % SURVIVOR_STRIDE != 0) {
        free(addresses[i]);
        addresses[i] = 0;
      }
    }
    allocated.countDown();
    try {
      release.await();
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
    }
    for (long address : addresses) {
      if (address != 0) {
        free(address);
      }
    }
  }

  private static long allocate(long bytes) {
    try {
      return (Long) ALLOCATE.invoke(UNSAFE, bytes);
    } catch (ReflectiveOperationException e) {
      throw new IllegalStateException(e);
    }
  }

  private static void free(long address) {
    try {
      FREE.invoke(UNSAFE, address);
    } catch (ReflectiveOperationException e) {
      throw new IllegalStateException(e);
    }
  }
}
