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
  u64 task_block_skipped_trace_context;
  u64 task_block_skipped_too_short;
  u64 suppressed_sampled_run;
};

static_assert(std::atomic<long long>::is_always_lock_free,
              "WallClockCounters fields must be lock-free for signal-handler safety");

// Holds signal-handler-safe atomic counters for wall-clock sampling statistics.
// Increments use relaxed lock-free atomics; drains use atomic exchange, so each
// increment is counted in either the current drain or a later one.
class WallClockCounters {
private:
  inline static std::atomic<long long> _task_block_emitted{0};
  inline static std::atomic<long long> _task_block_skipped_trace_context{0};
  inline static std::atomic<long long> _task_block_skipped_too_short{0};
  inline static std::atomic<long long> _suppressed_sampled_run{0};

  /**
   * Drains one counter to zero. These counters are best-effort diagnostics:
   * increments use relaxed ordering on the signal-handler hot path. Atomic
   * read-modify-write operations on the same counter still have a single
   * modification order, so increments are not lost; a concurrent increment is
   * simply ordered either before this exchange (counted in this drain) or after
   * it (counted in the next drain). Values are intended for observability of
   * trends, not exact interval accounting.
   *
   * The acquire tag on the exchange is retained as a cheap one-way fence on the
   * draining thread so that subsequent reads on this thread are not reordered
   * before the drain. It does NOT form a release/acquire pair with the relaxed
   * increments - those carry no ordering of their own.
   */
  static u64 drainCounter(std::atomic<long long>& counter) {
    return (u64)counter.exchange(0, std::memory_order_acquire);
  }

public:
  static void incrementTaskBlockEmitted() {
    _task_block_emitted.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementTaskBlockSkippedTraceContext() {
    _task_block_skipped_trace_context.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementTaskBlockSkippedTooShort() {
    _task_block_skipped_too_short.fetch_add(1, std::memory_order_relaxed);
  }

  static void incrementSuppressedSampledRun() {
    _suppressed_sampled_run.fetch_add(1, std::memory_order_relaxed);
  }

  static u64 drainSuppressedSampledRun() {
    return (u64)_suppressed_sampled_run.exchange(0, std::memory_order_acq_rel);
  }

  static void reset() {
    _suppressed_sampled_run.store(0, std::memory_order_relaxed);
  }

  static WallClockCounterSnapshot drain() {
    return {
        drainCounter(_task_block_emitted),
        drainCounter(_task_block_skipped_trace_context),
        drainCounter(_task_block_skipped_too_short),
        drainCounter(_suppressed_sampled_run)};
  }
};

#endif // _WALLCLOCK_COUNTERS_H
