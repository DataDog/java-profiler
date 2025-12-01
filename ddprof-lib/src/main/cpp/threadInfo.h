/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _THREADINFO_H
#define _THREADINFO_H

#include "spinLock.h"
#include "os_dd.h"
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <cstring>

/**
 * Signal-safe thread information storage.
 *
 * This class is designed to be safely accessed from signal handlers.
 * Uses:
 * - Pre-allocated fixed-size arrays (no dynamic allocation)
 * - SpinLock instead of pthread_mutex (signal-safe)
 * - Fixed-size char buffers for thread names
 * - Linear probing hash table for fast lookups
 */
class ThreadInfo {
private:
  // Thread name max length (including null terminator)
  static constexpr int MAX_THREAD_NAME_LEN = 256;

  // Maximum threads per stripe (power of 2 for fast modulo)
  static constexpr int THREADS_PER_STRIPE = 128;

  // Number of stripes for lock striping (power of 2)
  static constexpr int NUM_STRIPES = 64;

  // Maximum probe distance for linear probing
  static constexpr int MAX_PROBE_DISTANCE = 32;

  /**
   * Thread entry stored in the hash table.
   * Cache-line aligned to prevent false sharing between entries.
   * Note: The struct spans multiple cache lines due to the 256-byte name,
   * but alignment ensures each entry starts on a cache line boundary.
   */
  struct alignas(DEFAULT_CACHE_LINE_SIZE) ThreadEntry {
    int tid;                                    // Thread ID (0 = empty slot)
    u64 java_thread_id;                         // Java thread ID
    char name[MAX_THREAD_NAME_LEN];             // Thread name

    ThreadEntry() : tid(0), java_thread_id(0), name{0} {}

    void clear() {
      tid = 0;
      java_thread_id = 0;
      name[0] = '\0';
    }

    bool isEmpty() const {
      return tid == 0;
    }
  };

  /**
   * One stripe of the hash table with its own lock.
   */
  struct Stripe {
    SpinLock lock;
    ThreadEntry entries[THREADS_PER_STRIPE];

    Stripe() : lock(0) {}
  };

  Stripe _stripes[NUM_STRIPES];

  // Hash function to distribute TIDs across stripes
  inline int getStripe(int tid) const {
    return tid & (NUM_STRIPES - 1);  // Fast modulo for power-of-2
  }

  // Hash function within a stripe
  inline int getSlot(int tid) const {
    // Use multiplicative hashing for better distribution
    return ((unsigned int)tid * 2654435761u) & (THREADS_PER_STRIPE - 1);
  }

public:
  // disallow copy and assign to avoid issues with the locks
  ThreadInfo(const ThreadInfo &) = delete;
  ThreadInfo &operator=(const ThreadInfo &) = delete;

  ThreadInfo() {}

  /**
   * Set thread information.
   * Signal-safe: uses spinlocks and pre-allocated storage.
   */
  void set(int tid, const char *name, u64 java_thread_id);

  /**
   * Get thread information.
   * Signal-safe: uses spinlocks and no dynamic allocation.
   * Returns pair of (name, java_thread_id). name is nullptr if not found.
   */
  std::pair<std::shared_ptr<std::string>, u64> get(int tid);

  /**
   * Update thread name if not already present.
   * Uses resolver function to lazily compute the name.
   */
  void updateThreadName(int tid, std::function<std::string(int)> resolver);

  /**
   * Get total number of registered threads across all stripes.
   */
  int size();

  /**
   * Clear thread entries not in the live_thread_ids set.
   */
  void clearAll(std::set<int> &live_thread_ids);

  /**
   * Clear all thread entries.
   */
  void clearAll();

  /**
   * Report thread count metrics.
   */
  void reportCounters();

  /**
   * For testing: get Java thread ID for a native thread.
   */
  int getThreadId(int tid);
};

#endif // _THREADINFO_H
