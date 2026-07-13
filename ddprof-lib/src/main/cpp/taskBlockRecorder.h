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

void initializeTaskBlockDurationThreshold();
bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks);

// Allocation-free guard for the dump rotation protocol. Callers that already
// hold an activity pass true so nested recorder helpers reuse the outer guard.
class TaskBlockActivity {
 private:
  Profiler* _profiler;
  bool _active;
  bool _owns_activity;

 public:
  explicit TaskBlockActivity(bool already_active = false)
      : _profiler(Profiler::instance()),
        _active(already_active || _profiler->tryEnterTaskBlockActivity()),
        _owns_activity(!already_active && _active) {
    if (!_active) {
      Counters::increment(TASK_BLOCK_DROPPED_ROTATION);
    }
  }

  ~TaskBlockActivity() {
    if (_owns_activity) {
      _profiler->leaveTaskBlockActivity();
    }
  }

  bool active() const { return _active; }
};

static inline bool hasTraceContext(const Context& ctx) {
  return ctx.spanId != 0;
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

// Off-thread/deferred path. The caller must pass stack metadata and observed
// state captured from the same blocked-run snapshot before the target thread
// exits that run. Re-reading thread state here would observe the recorder thread
// or a later target-thread state, not the blocked interval being recorded.
static inline bool recordTaskBlockWithStackReferenceIfEligible(
    int tid, u64 start_ticks, u64 end_ticks, const Context& ctx, u64 blocker,
    u64 unblocking_span_id, u64 call_trace_id, u64 correlation_id,
    OSThreadState observed_state, bool activity_already_held = false) {
  TaskBlockActivity activity(activity_already_held);
  if (!activity.active()) {
    return false;
  }
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
    OSThreadState observed_state, bool activity_already_held = false) {
  TaskBlockActivity activity(activity_already_held);
  if (!activity.active()) {
    return false;
  }
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
