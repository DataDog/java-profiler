/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_COUNTERS_H
#define _WALLCLOCK_COUNTERS_H

#include "arch.h"
#include <atomic>

struct WallClockCounterSnapshot {
  u64 task_block_emitted;
  u64 task_block_skipped_span_zero;
  u64 task_block_skipped_too_short;
  u64 suppressed_sampled_run;
};

static_assert(std::atomic<long long>::is_always_lock_free,
              "WallClockCounters fields must be lock-free for signal-handler safety");

class WallClockCounters {
private:
  inline static std::atomic<long long> _task_block_emitted{0};
  inline static std::atomic<long long> _task_block_skipped_span_zero{0};
  inline static std::atomic<long long> _task_block_skipped_too_short{0};
  inline static std::atomic<long long> _suppressed_sampled_run{0};

  // Best-effort: increments are RELAXED (signal-handler safe), drain is ACQUIRE
  // (one-way fence on the timer thread). A concurrent increment lands in either
  // this drain or the next — no counts are lost, but interval boundaries are fuzzy.
  static u64 drainCounter(std::atomic<long long>& counter) {
    return (u64)counter.exchange(0, std::memory_order_acquire);
  }

public:
  static void incrementTaskBlockEmitted() {
    _task_block_emitted.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementTaskBlockSkippedSpanZero() {
    _task_block_skipped_span_zero.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementTaskBlockSkippedTooShort() {
    _task_block_skipped_too_short.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementSuppressedSampledRun() {
    _suppressed_sampled_run.fetch_add(1, std::memory_order_relaxed);
  }

  static WallClockCounterSnapshot drain() {
    return {
        drainCounter(_task_block_emitted),
        drainCounter(_task_block_skipped_span_zero),
        drainCounter(_task_block_skipped_too_short),
        drainCounter(_suppressed_sampled_run)};
  }
};

#endif // _WALLCLOCK_COUNTERS_H
