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
// Fails closed (returns false) when the 1 ms threshold computes to 0 ticks
// (TSC::frequency() below 1 kHz, e.g. 0), so sub-millisecond blocks cannot
// pass the filter.
bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks);

#ifdef UNIT_TEST
// Clears the cached threshold so the next exceedsMinTaskBlockDuration() call
// takes its lazy recompute path.
void resetTaskBlockDurationThresholdForTest();
// Replaces TSC::frequency() as the threshold's frequency source; nullptr
// restores TSC::frequency().
using TaskBlockFrequencySource = u64 (*)();
void setTaskBlockFrequencySourceForTest(TaskBlockFrequencySource source);
#endif

// Recovers a TASK_BLOCK interval whose endTaskBlock0 was never reached (for
// example, an exception thrown without a finally block). Clears the pending
// TLS token and closes its block run with the generation-checked
// exitBlockedRun(), which is a no-op if the slot has since started another
// run. The run is closed only when the token's slot is current_slot: a
// different slot means a registry reset already cleared the run and the slot
// may now belong to another thread. Counts TASK_BLOCK_RECOVERED_ABANDONED.
// Returns true when an abandoned interval was found.
bool recoverAbandonedTaskBlock(ProfiledThread* current,
                               WallClockBlockTracker* tracker,
                               ThreadFilter::SlotID current_slot);

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 blocker,
                           u64 unblocking_span_id);

// Completes block-run lifecycle cleanup for an already-exited producer and
// records its event only when dump/stop rotation admits the recording work.
// Cleanup is deliberately performed even when admission is rejected so an
// application thread never waits for rotation and suppression cannot be left
// armed.
bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
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
