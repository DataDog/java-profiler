/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_RECORDER_H
#define _TASK_BLOCK_RECORDER_H

#include "context.h"
#include "context_api.h"
#include "event.h"
#include "profiler.h"
#include "tsc.h"
#include "wallClockCounters.h"

static inline bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  static const u64 kMinTaskBlockNanos = 1000000; // 1 ms
  u64 min_ticks = (TSC::frequency() * kMinTaskBlockNanos) / 1000000000ULL;
  return end_ticks > start_ticks && (end_ticks - start_ticks) >= min_ticks;
}

// Platform-thread synchronous path. Span context is captured from OTEP TLS at
// call time via ContextApi::snapshot(). Custom profiling attributes are included.
static inline void recordTaskBlockLiveIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                  u64 blocker, u64 unblocking_span_id) {
  Context ctx = ContextApi::snapshot();
  if (ctx.spanId == 0) {
    WallClockCounters::incrementTaskBlockSkippedSpanZero();
    return;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  Profiler::instance()->recordTaskBlockLive(tid, &event);
  WallClockCounters::incrementTaskBlockEmitted();
}

// Virtual-thread / drain-thread path. Span context is passed explicitly because
// the native OTEP TLS is carrier-scoped and cannot be trusted. Custom profiling
// context attributes are not propagated on this path (ctx has zeros for tags).
static inline void recordTaskBlockDeferredIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                      const Context& ctx, u64 blocker,
                                                      u64 unblocking_span_id) {
  if (ctx.spanId == 0) {
    WallClockCounters::incrementTaskBlockSkippedSpanZero();
    return;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  Profiler::instance()->recordTaskBlockDeferred(tid, &event);
  WallClockCounters::incrementTaskBlockEmitted();
}

#endif // _TASK_BLOCK_RECORDER_H
