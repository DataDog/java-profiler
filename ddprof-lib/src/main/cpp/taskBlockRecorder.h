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

static inline bool taskBlockPassesBasicEligibility(u64 start_ticks, u64 end_ticks,
                                                   const Context& ctx) {
  if (hasTraceContext(ctx)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  return true;
}

static inline bool recordTaskBlockLive(int tid, TaskBlockEvent& event) {
  if (Profiler::instance()->recordTaskBlockLive(tid, &event)) {
    Counters::increment(TASK_BLOCK_EMITTED);
    return true;
  }
  Counters::increment(TASK_BLOCK_RECORD_FAILED);
  return false;
}

// Same-thread path for callers that captured the context at block entry. Stack
// metadata is attached from ProfiledThread::current(), so the caller must be the
// target thread.
static inline bool recordTaskBlockWithContextIfEligible(int tid, u64 start_ticks, u64 end_ticks,
                                                         const Context& ctx, u64 blocker,
                                                         u64 unblocking_span_id) {
  if (!taskBlockPassesBasicEligibility(start_ticks, end_ticks, ctx)) {
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
    Counters::increment(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE);
    return false;
  }
  return recordTaskBlockLive(tid, event);
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

// Off-thread/deferred path. The caller must pass stack metadata and observed
// state captured from the same blocked-run snapshot before the target thread
// exits that run. Re-reading thread state here would observe the recorder thread
// or a later target-thread state, not the blocked interval being recorded.
static inline bool recordTaskBlockWithStackReferenceIfEligible(
    int tid, u64 start_ticks, u64 end_ticks, const Context& ctx, u64 blocker,
    u64 unblocking_span_id, u64 call_trace_id, u64 correlation_id,
    OSThreadState observed_state) {
  if (!taskBlockPassesBasicEligibility(start_ticks, end_ticks, ctx)) {
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  setTaskBlockStackReference(event, call_trace_id, correlation_id,
                             observed_state);
  if (!hasTaskBlockStackReference(event)) {
    Counters::increment(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE);
    return false;
  }
  return recordTaskBlockLive(tid, event);
}

// Async path for native monitor and native I/O callbacks. The producer must
// snapshot stack metadata and observed state before exiting the blocked run; this
// helper does not inspect ProfiledThread::current().
static inline bool recordTaskBlockAsyncWithStackReferenceIfEligible(
    int tid, u64 start_ticks, u64 end_ticks, const Context& ctx, u64 blocker,
    u64 unblocking_span_id, u64 call_trace_id, u64 correlation_id,
    OSThreadState observed_state) {
  if (!taskBlockPassesBasicEligibility(start_ticks, end_ticks, ctx)) {
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  setTaskBlockStackReference(event, call_trace_id, correlation_id,
                             observed_state);
  if (!hasTaskBlockStackReference(event)) {
    Counters::increment(TASK_BLOCK_SKIPPED_NO_STACK_REFERENCE);
    return false;
  }
  return Profiler::instance()->recordTaskBlockAsync(tid, &event);
}

#endif // _TASK_BLOCK_RECORDER_H
