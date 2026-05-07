/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_RECORDER_H
#define _TASK_BLOCK_RECORDER_H

#include "context.h"
#include "counters.h"
#include "event.h"
#include "profiler.h"
#include "tsc.h"
#include "wallClockCounters.h"

static inline bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  static const u64 kMinTaskBlockNanos = 1000000; // 1 ms
  u64 min_ticks = (TSC::frequency() * kMinTaskBlockNanos) / 1000000000ULL;
  return end_ticks > start_ticks && (end_ticks - start_ticks) >= min_ticks;
}

static inline bool recordTaskBlockIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                             const Context& context, u64 blocker,
                                             u64 unblocking_span_id) {
  if (context.spanId == 0) {
    Counters::increment(TASK_BLOCK_SKIPPED_SPAN_ZERO);
    WallClockCounters::incrementTaskBlockSkippedSpanZero();
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return false;
  }

  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = context;
  if (Profiler::instance()->recordTaskBlock(tid, &event)) {
    Counters::increment(TASK_BLOCK_EMITTED);
    WallClockCounters::incrementTaskBlockEmitted();
    return true;
  }
  return false;
}

#endif // _TASK_BLOCK_RECORDER_H
