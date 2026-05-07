/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _WALLCLOCK_COUNTERS_H
#define _WALLCLOCK_COUNTERS_H

#include "arch.h"

struct WallClockCounterSnapshot {
  u64 skipped_parked_spanless;
  u64 skipped_parked_active_span;
  u64 task_block_emitted;
  u64 task_block_skipped_span_zero;
  u64 task_block_skipped_too_short;
};

class WallClockCounters {
private:
  inline static volatile long long _skipped_parked_spanless = 0;
  inline static volatile long long _skipped_parked_active_span = 0;
  inline static volatile long long _task_block_emitted = 0;
  inline static volatile long long _task_block_skipped_span_zero = 0;
  inline static volatile long long _task_block_skipped_too_short = 0;

  static u64 drain(volatile long long& counter) {
    return (u64)__atomic_exchange_n(&counter, 0, __ATOMIC_RELAXED);
  }

public:
  static void incrementSkippedParkedSpanless() {
    atomicIncRelaxed(_skipped_parked_spanless);
  }

  static void incrementSkippedParkedActiveSpan() {
    atomicIncRelaxed(_skipped_parked_active_span);
  }

  static void incrementTaskBlockEmitted() {
    atomicIncRelaxed(_task_block_emitted);
  }

  static void incrementTaskBlockSkippedSpanZero() {
    atomicIncRelaxed(_task_block_skipped_span_zero);
  }

  static void incrementTaskBlockSkippedTooShort() {
    atomicIncRelaxed(_task_block_skipped_too_short);
  }

  static WallClockCounterSnapshot drain() {
    return {
        drain(_skipped_parked_spanless),
        drain(_skipped_parked_active_span),
        drain(_task_block_emitted),
        drain(_task_block_skipped_span_zero),
        drain(_task_block_skipped_too_short)};
  }
};

#endif // _WALLCLOCK_COUNTERS_H
