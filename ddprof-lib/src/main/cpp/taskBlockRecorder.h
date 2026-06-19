/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_RECORDER_H
#define _TASK_BLOCK_RECORDER_H

#include "context.h"
#include "context_api.h"
#include "counters.h"
#include "event.h"
#include "profiler.h"
#include "tsc.h"

void initializeTaskBlockDurationThreshold();
bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks);

static inline bool hasTraceContext(const Context& ctx) {
  return ctx.spanId != 0;
}

static inline void attachTaskBlockStackReference(int tid, TaskBlockEvent& event) {
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
  if (!snapshot.has_stack_reference) {
    return;
  }
  event._callTraceId = snapshot.call_trace_id;
  event._correlationId = snapshot.correlation_id;
}

static inline void setTaskBlockStackReference(TaskBlockEvent& event,
                                              u64 call_trace_id,
                                              u64 correlation_id,
                                              OSThreadState observed_state) {
  event._callTraceId = call_trace_id;
  event._correlationId = correlation_id;
  event._observedBlockingState = observed_state;
}

static inline bool hasTaskBlockStackReference(const TaskBlockEvent& event) {
  return event._callTraceId != 0 || event._correlationId != 0;
}

// Synchronous path for callers that captured the context at block entry.
static inline bool recordTaskBlockWithContextIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                         const Context& ctx, u64 blocker,
                                                         u64 unblocking_span_id) {
  if (hasTraceContext(ctx)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  attachTaskBlockStackReference(tid, event);
  if (!hasTaskBlockStackReference(event)) {
    return false;
  }
  if (Profiler::instance()->recordTaskBlockLive(tid, &event)) {
    Counters::increment(TASK_BLOCK_EMITTED);
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
                                                      u64 call_trace_id = 0,
                                                      u64 correlation_id = 0,
                                                      OSThreadState observed_state = OSThreadState::UNKNOWN) {
  if (hasTraceContext(ctx)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  if (call_trace_id != 0 || correlation_id != 0 ||
      observed_state != OSThreadState::UNKNOWN) {
    setTaskBlockStackReference(event, call_trace_id, correlation_id,
                               observed_state);
  } else {
    attachTaskBlockStackReference(tid, event);
  }
  if (!hasTaskBlockStackReference(event)) {
    return false;
  }
  if (Profiler::instance()->recordTaskBlockLive(tid, &event)) {
    Counters::increment(TASK_BLOCK_EMITTED);
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
                                                             u64 call_trace_id = 0,
                                                             u64 correlation_id = 0,
                                                             OSThreadState observed_state = OSThreadState::UNKNOWN) {
  if (hasTraceContext(ctx)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  if (call_trace_id != 0 || correlation_id != 0 ||
      observed_state != OSThreadState::UNKNOWN) {
    setTaskBlockStackReference(event, call_trace_id, correlation_id,
                               observed_state);
  } else {
    attachTaskBlockStackReference(tid, event);
  }
  if (!hasTaskBlockStackReference(event)) {
    return false;
  }
  return Profiler::instance()->recordTaskBlockAsync(tid, &event);
}

#endif // _TASK_BLOCK_RECORDER_H
