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

static inline bool hasTraceContext(const Context& ctx) {
  return ctx.spanId != 0;
}

static inline void attachTaskBlockSuppressionFields(int tid, TaskBlockEvent& event) {
  Profiler* profiler = Profiler::instance();
  ThreadFilter* thread_filter = profiler->threadFilter();
  if (!thread_filter->enabled()) {
    event._observedBlockingState = OSThreadState::UNKNOWN;
    return;
  }
  ProfiledThread* current = ProfiledThread::current();
  if (current == nullptr || current->tid() != tid) {
    event._observedBlockingState = OSThreadState::UNKNOWN;
    return;
  }
  BlockRunSnapshot snapshot = thread_filter->snapshotBlockedRun(current->filterSlotId());
  event._observedBlockingState =
      snapshot.sampled_state != OSThreadState::UNKNOWN ? snapshot.sampled_state
                                                       : snapshot.active_state;
  if (!snapshot.anchored) {
    return;
  }
  event._anchorSampleId = snapshot.anchor_sample_id;
  event._suppressedSampleCount = snapshot.suppressed_sample_count;
}

static inline void setTaskBlockSuppressionFields(TaskBlockEvent& event,
                                                 u64 anchor_sample_id,
                                                 u64 suppressed_sample_count,
                                                 OSThreadState observed_state) {
  event._anchorSampleId = anchor_sample_id;
  event._suppressedSampleCount = suppressed_sample_count;
  event._observedBlockingState = observed_state;
}

// Synchronous path for callers that captured the context at block entry.
static inline bool recordTaskBlockWithContextIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                         const Context& ctx, u64 blocker,
                                                         u64 unblocking_span_id) {
  if (hasTraceContext(ctx)) {
    WallClockCounters::incrementTaskBlockSkippedTraceContext();
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  attachTaskBlockSuppressionFields(tid, event);
  if (Profiler::instance()->recordTaskBlockLive(tid, &event)) {
    WallClockCounters::incrementTaskBlockEmitted();
    return true;
  }
  return false;
}

// Platform-thread synchronous path. Context is captured from OTEP TLS at call
// time so traced intervals can be skipped and custom attributes can be recorded
// for untraced intervals.
static inline bool recordTaskBlockLiveIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                  u64 blocker, u64 unblocking_span_id) {
  Context ctx = ContextApi::snapshot();
  return recordTaskBlockWithContextIfEligible(tid, start_ticks, end_ticks, ctx,
                                             blocker, unblocking_span_id);
}

// Virtual-thread / drain-thread path. Context is passed explicitly because
// the native OTEP TLS is carrier-scoped and cannot be trusted. Custom profiling
// context attributes are not propagated on this path (ctx has zeros for tags).
static inline bool recordTaskBlockDeferredIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                      const Context& ctx, u64 blocker,
                                                      u64 unblocking_span_id,
                                                      u64 anchor_sample_id = 0,
                                                      u64 suppressed_sample_count = 0,
                                                      OSThreadState observed_state = OSThreadState::UNKNOWN) {
  if (hasTraceContext(ctx)) {
    WallClockCounters::incrementTaskBlockSkippedTraceContext();
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  if (anchor_sample_id != 0 || suppressed_sample_count != 0 ||
      observed_state != OSThreadState::UNKNOWN) {
    setTaskBlockSuppressionFields(event, anchor_sample_id, suppressed_sample_count,
                                  observed_state);
  } else {
    attachTaskBlockSuppressionFields(tid, event);
  }
  if (Profiler::instance()->recordTaskBlockDeferred(tid, &event)) {
    WallClockCounters::incrementTaskBlockEmitted();
    return true;
  }
  return false;
}

// Async path for native monitor callbacks. The producer side still performs
// eligibility checks so traced or short intervals do not pressure the queue.
static inline bool recordTaskBlockAsyncWithContextIfEligible(int tid, u64 start_ticks,
                                                             u64 end_ticks, const Context& ctx,
                                                             u64 blocker,
                                                             u64 unblocking_span_id,
                                                             u64 anchor_sample_id = 0,
                                                             u64 suppressed_sample_count = 0,
                                                             OSThreadState observed_state = OSThreadState::UNKNOWN) {
  if (hasTraceContext(ctx)) {
    WallClockCounters::incrementTaskBlockSkippedTraceContext();
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    WallClockCounters::incrementTaskBlockSkippedTooShort();
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  if (anchor_sample_id != 0 || suppressed_sample_count != 0 ||
      observed_state != OSThreadState::UNKNOWN) {
    setTaskBlockSuppressionFields(event, anchor_sample_id, suppressed_sample_count,
                                  observed_state);
  } else {
    attachTaskBlockSuppressionFields(tid, event);
  }
  return Profiler::instance()->recordTaskBlockAsync(tid, &event);
}

#endif // _TASK_BLOCK_RECORDER_H
