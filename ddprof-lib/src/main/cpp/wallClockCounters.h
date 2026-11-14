/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_COUNTERS_H
#define _WALLCLOCK_COUNTERS_H

#include "arch.h"
#include <atomic>

static_assert(std::atomic<long long>::is_always_lock_free,
              "WallClockCounters fields must be lock-free for signal-handler safety");

// Holds signal-handler-safe atomic counters for wall-clock sampling statistics.
// Increments use relaxed lock-free atomics; drains use atomic exchange, so each
// increment is counted in either the current drain or a later one.
class WallClockCounters {
private:
  inline static std::atomic<long long> _suppressed_owned_block{0};
  inline static std::atomic<u64> _sampling_epoch_start{0};

public:
  // The timer publishes the same start tick it writes in WallClockSamplingEpoch.
  // Retained observations use that window start, not their later flush time.
  static void beginSamplingEpoch(u64 ticks) {
    _sampling_epoch_start.store(ticks, std::memory_order_release);
  }

  static u64 samplingEpochStart() {
    return _sampling_epoch_start.load(std::memory_order_acquire);
  }

  static void incrementSuppressedOwnedBlock() {
    _suppressed_owned_block.fetch_add(1, std::memory_order_relaxed);
  }

  static u64 drainSuppressedOwnedBlock() {
    return (u64)_suppressed_owned_block.exchange(0, std::memory_order_acq_rel);
  }

  static void reset() {
    beginSamplingEpoch(0);
    _suppressed_owned_block.store(0, std::memory_order_relaxed);
  }
};

#endif // _WALLCLOCK_COUNTERS_H
