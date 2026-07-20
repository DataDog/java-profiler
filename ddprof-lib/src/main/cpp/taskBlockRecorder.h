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

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           jthread thread, int start_depth, u64 block_token,
                           ThreadFilter::SlotID slot_id, u64 generation,
                           u64 blocker, u64 unblocking_span_id);

// Completes ThreadFilter lifecycle cleanup for an already-exited producer and
// records its event only when dump/stop rotation admits the recording work.
// Cleanup is deliberately performed even when admission is rejected so an
// application thread never waits for rotation and suppression cannot be left
// armed.
bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter, jthread thread,
                           int start_depth, u64 block_token, u64 start_ticks,
                           const Context& context, u64 blocker,
                           u64 unblocking_span_id);

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
    if (!_active) Counters::increment(TASK_BLOCK_DROPPED_ROTATION);
  }

  ~TaskBlockActivity() {
    if (_owns_activity) _profiler->leaveTaskBlockActivity();
  }

  bool active() const { return _active; }
};

static inline bool taskBlockPassesBasicEligibility(u64 start_ticks, u64 end_ticks,
                                                   const Context& ctx) {
  if (ctx.spanId != 0) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  return true;
}

static inline bool recordTaskBlockIfEligible(
    int tid, jthread thread, int start_depth, u64 start_ticks, u64 end_ticks,
    const Context& ctx, u64 blocker, u64 unblocking_span_id,
    OSThreadState observed_state, bool activity_already_held = false) {
  TaskBlockActivity activity(activity_already_held);
  if (!activity.active() ||
      !taskBlockPassesBasicEligibility(start_ticks, end_ticks, ctx)) {
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  event._observedBlockingState = observed_state;
  Profiler::TaskBlockRecordResult result =
      Profiler::instance()->recordTaskBlock(tid, thread, start_depth, &event);
  if (result == Profiler::TaskBlockRecordResult::RECORDED) {
    Counters::increment(TASK_BLOCK_EMITTED);
    return true;
  }
  Counters::increment(
      result == Profiler::TaskBlockRecordResult::STACK_CAPTURE_FAILED
          ? TASK_BLOCK_STACK_CAPTURE_FAILED
          : TASK_BLOCK_RECORD_FAILED);
  return false;
}

#endif // _TASK_BLOCK_RECORDER_H
