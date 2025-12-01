/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "threadInfo.h"
#include "counters.h"
#include <cstring>

void ThreadInfo::set(int tid, const char *name, u64 java_thread_id) {
  if (tid <= 0 || name == nullptr) {
    return;  // Invalid input
  }

  int stripe_idx = getStripe(tid);
  Stripe& stripe = _stripes[stripe_idx];

  ExclusiveLockGuard guard(&stripe.lock);

  int slot = getSlot(tid);
  int probe_count = 0;

  // Linear probing to find empty slot or existing entry
  while (probe_count < MAX_PROBE_DISTANCE) {
    ThreadEntry& entry = stripe.entries[slot];

    if (entry.isEmpty() || entry.tid == tid) {
      // Found empty slot or existing entry - update it
      entry.tid = tid;
      entry.java_thread_id = java_thread_id;
      strncpy(entry.name, name, MAX_THREAD_NAME_LEN - 1);
      entry.name[MAX_THREAD_NAME_LEN - 1] = '\0';  // Ensure null termination
      return;
    }

    // Probe next slot
    slot = (slot + 1) & (THREADS_PER_STRIPE - 1);
    probe_count++;
  }

  // If we get here, the hash table stripe is too full
  // This is a design limit - could log a warning if needed
}

std::pair<std::shared_ptr<std::string>, u64> ThreadInfo::get(int tid) {
  if (tid <= 0) {
    return std::make_pair(nullptr, 0);
  }

  int stripe_idx = getStripe(tid);
  Stripe& stripe = _stripes[stripe_idx];

  SharedLockGuard guard(&stripe.lock);

  int slot = getSlot(tid);
  int probe_count = 0;

  // Linear probing to find the entry
  while (probe_count < MAX_PROBE_DISTANCE) {
    const ThreadEntry& entry = stripe.entries[slot];

    if (entry.isEmpty()) {
      // Hit empty slot - entry doesn't exist
      return std::make_pair(nullptr, 0);
    }

    if (entry.tid == tid) {
      // Found it - create shared_ptr to string copy
      return std::make_pair(
        std::make_shared<std::string>(entry.name),
        entry.java_thread_id
      );
    }

    // Probe next slot
    slot = (slot + 1) & (THREADS_PER_STRIPE - 1);
    probe_count++;
  }

  // Not found after max probes
  return std::make_pair(nullptr, 0);
}

int ThreadInfo::getThreadId(int tid) {
  if (tid <= 0) {
    return -1;
  }

  int stripe_idx = getStripe(tid);
  Stripe& stripe = _stripes[stripe_idx];

  SharedLockGuard guard(&stripe.lock);

  int slot = getSlot(tid);
  int probe_count = 0;

  while (probe_count < MAX_PROBE_DISTANCE) {
    const ThreadEntry& entry = stripe.entries[slot];

    if (entry.isEmpty()) {
      return -1;
    }

    if (entry.tid == tid) {
      return entry.java_thread_id;
    }

    slot = (slot + 1) & (THREADS_PER_STRIPE - 1);
    probe_count++;
  }

  return -1;
}

void ThreadInfo::clearAll() {
  // Clear all stripes
  for (int i = 0; i < NUM_STRIPES; i++) {
    ExclusiveLockGuard guard(&_stripes[i].lock);
    for (int j = 0; j < THREADS_PER_STRIPE; j++) {
      _stripes[i].entries[j].clear();
    }
  }
}

void ThreadInfo::clearAll(std::set<int> &live_thread_ids) {
  // Clear entries not in live_thread_ids across all stripes
  for (int i = 0; i < NUM_STRIPES; i++) {
    ExclusiveLockGuard guard(&_stripes[i].lock);

    if (live_thread_ids.empty()) {
      // Fast path: clear everything
      for (int j = 0; j < THREADS_PER_STRIPE; j++) {
        _stripes[i].entries[j].clear();
      }
    } else {
      // Honor the threads referenced from the liveness tracker
      for (int j = 0; j < THREADS_PER_STRIPE; j++) {
        ThreadEntry& entry = _stripes[i].entries[j];
        if (!entry.isEmpty() && live_thread_ids.find(entry.tid) == live_thread_ids.end()) {
          entry.clear();
        }
      }
    }
  }
}

int ThreadInfo::size() {
  int total = 0;
  for (int i = 0; i < NUM_STRIPES; i++) {
    SharedLockGuard guard(&_stripes[i].lock);
    for (int j = 0; j < THREADS_PER_STRIPE; j++) {
      if (!_stripes[i].entries[j].isEmpty()) {
        total++;
      }
    }
  }
  return total;
}

void ThreadInfo::updateThreadName(int tid, std::function<std::string(int)> resolver) {
  if (tid <= 0) {
    return;
  }

  int stripe_idx = getStripe(tid);
  Stripe& stripe = _stripes[stripe_idx];

  ExclusiveLockGuard guard(&stripe.lock);

  int slot = getSlot(tid);
  int probe_count = 0;

  // First, check if entry already exists
  while (probe_count < MAX_PROBE_DISTANCE) {
    ThreadEntry& entry = stripe.entries[slot];

    if (entry.isEmpty()) {
      // Found empty slot - create new entry
      std::string name = resolver(tid);
      if (!name.empty()) {
        entry.tid = tid;
        entry.java_thread_id = 0;  // Unknown at this point
        strncpy(entry.name, name.c_str(), MAX_THREAD_NAME_LEN - 1);
        entry.name[MAX_THREAD_NAME_LEN - 1] = '\0';
      }
      return;
    }

    if (entry.tid == tid) {
      // Entry already exists - don't update
      return;
    }

    slot = (slot + 1) & (THREADS_PER_STRIPE - 1);
    probe_count++;
  }

  // Hash table stripe is too full - can't add
}

void ThreadInfo::reportCounters() {
  int total_entries = 0;
  for (int i = 0; i < NUM_STRIPES; i++) {
    SharedLockGuard guard(&_stripes[i].lock);
    for (int j = 0; j < THREADS_PER_STRIPE; j++) {
      if (!_stripes[i].entries[j].isEmpty()) {
        total_entries++;
      }
    }
  }
  // Report the same counter for both IDs and names since they're stored together
  Counters::set(THREAD_IDS_COUNT, total_entries);
  Counters::set(THREAD_NAMES_COUNT, total_entries);
}
