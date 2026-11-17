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
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 blocker,
                           u64 unblocking_span_id);

// Completes lifecycle cleanup even when dump/stop denies recording activity.
// end_ticks == 0 reads the native clock; nonzero supplies a lifecycle-test timestamp.
bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 start_ticks,
                           const Context& context, u64 blocker,
                           u64 unblocking_span_id, u64 end_ticks = 0);

class TaskBlockActivity {
 private:
  Profiler* _profiler;
  bool _active;
  bool _owns_activity;

 public:
  explicit TaskBlockActivity(bool already_active = false
                             TASK_BLOCK_DIAGNOSTIC_ONLY(, const TaskBlockDiagnosticRecord* diagnostic = nullptr))
      : _profiler(Profiler::instance()),
        _active(already_active || _profiler->tryEnterTaskBlockActivity(TASK_BLOCK_DIAGNOSTIC_ONLY(diagnostic))),
        _owns_activity(!already_active && _active) {
#if defined(DEBUG) || defined(UNIT_TEST)
    if (already_active) TASK_BLOCK_DIAGNOSTIC(ACTIVITY_REUSED, diagnostic, 0);
#endif
  }

  ~TaskBlockActivity() {
    if (_owns_activity) _profiler->leaveTaskBlockActivity();
  }

  TaskBlockActivity(const TaskBlockActivity&) = delete;
  TaskBlockActivity& operator=(const TaskBlockActivity&) = delete;

  bool active() const { return _active; }
};

static inline bool taskBlockPassesBasicEligibility(u64 start_ticks, u64 end_ticks,
                                                   const Context& ctx
                                                   TASK_BLOCK_DIAGNOSTIC_ONLY(, const TaskBlockDiagnosticRecord* diagnostic = nullptr)) {
  if (ctx.spanId != 0) {
    TASK_BLOCK_DIAGNOSTIC(REJECT_TRACE_CONTEXT, diagnostic, ctx.spanId);
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return false;
  }
  if (!exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
#if defined(DEBUG) || defined(UNIT_TEST)
    if (end_ticks <= start_ticks) {
      TASK_BLOCK_DIAGNOSTIC(REJECT_DURATION_NOT_POSITIVE, diagnostic, 0);
    } else {
      TASK_BLOCK_DIAGNOSTIC(REJECT_DURATION_BELOW_MINIMUM, diagnostic, 0);
    }
#endif
    Counters::increment(TASK_BLOCK_SKIPPED_TOO_SHORT);
    return false;
  }
  TASK_BLOCK_DIAGNOSTIC(BASIC_ELIGIBLE, diagnostic, 0);
  return true;
}

static inline bool recordTaskBlockIfEligible(
    int tid, jthread thread, int start_depth, u64 start_ticks, u64 end_ticks,
    const Context& ctx, u64 blocker, u64 unblocking_span_id,
    OSThreadState observed_state, bool activity_already_held = false
    TASK_BLOCK_DIAGNOSTIC_ONLY(, const TaskBlockDiagnosticRecord* diagnostic = nullptr)) {
#if defined(DEBUG) || defined(UNIT_TEST)
  TaskBlockDiagnosticRecord interval = diagnostic == nullptr ? TaskBlockDiagnosticRecord{} : *diagnostic;
  interval.words[TaskBlockDiagnosticRecord::TID] = tid;
  interval.words[TaskBlockDiagnosticRecord::START] = start_ticks;
  interval.words[TaskBlockDiagnosticRecord::END] = end_ticks;
  interval.words[TaskBlockDiagnosticRecord::BLOCKER] = blocker;
  interval.words[TaskBlockDiagnosticRecord::STATE] = static_cast<u64>(observed_state);
  interval.words[TaskBlockDiagnosticRecord::VALID] |= TaskBlockDiagnosticRecord::HAS_INTERVAL;
  diagnostic = &interval;
#endif
  TaskBlockActivity activity(activity_already_held TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic));
  if (!activity.active() ||
      !taskBlockPassesBasicEligibility(start_ticks, end_ticks, ctx TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic))) {
    return false;
  }
  TaskBlockEvent event{};
  event._start = start_ticks;
  event._end = end_ticks;
  event._blocker = blocker;
  event._unblockingSpanId = unblocking_span_id;
  event._ctx = ctx;
  event._observedBlockingState = observed_state;
#if defined(DEBUG) || defined(UNIT_TEST)
  TaskBlockStage rejection = TaskBlockStage::COUNT;
#endif
  Profiler::TaskBlockRecordResult result =
      Profiler::instance()->recordTaskBlock(tid, thread, start_depth, &event TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic, &rejection));
  if (result == Profiler::TaskBlockRecordResult::RECORDED) {
    TASK_BLOCK_DIAGNOSTIC(TERMINAL_BUFFER_ACCEPTED, diagnostic, 0);
    Counters::increment(TASK_BLOCK_EMITTED);
    return true;
  }
#if defined(DEBUG) || defined(UNIT_TEST)
  if (result == Profiler::TaskBlockRecordResult::STACK_CAPTURE_FAILED) {
    TASK_BLOCK_DIAGNOSTIC(TERMINAL_STACK_CAPTURE_FAILED, diagnostic, static_cast<u64>(rejection));
  } else {
    TASK_BLOCK_DIAGNOSTIC(TERMINAL_RECORD_FAILED, diagnostic, static_cast<u64>(rejection));
  }
#endif
  Counters::increment(
      result == Profiler::TaskBlockRecordResult::STACK_CAPTURE_FAILED
          ? TASK_BLOCK_STACK_CAPTURE_FAILED
          : TASK_BLOCK_RECORD_FAILED);
  return false;
}

#endif // _TASK_BLOCK_RECORDER_H
