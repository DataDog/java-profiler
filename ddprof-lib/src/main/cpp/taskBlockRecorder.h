/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_RECORDER_H
#define _TASK_BLOCK_RECORDER_H

#include "context.h"
#include "counters.h"
#include "event.h"
#include "monitorEntryStacks.h"
#include "profiler.h"
#include "tsc.h"

void initializeTaskBlockDurationThreshold();

enum class TaskBlockDurationCheck {
  ELIGIBLE,
  TOO_SHORT,
  // The 1 ms threshold computes to 0 ticks (TSC::frequency() below 1 kHz,
  // e.g. 0), so no block can be checked against it.
  THRESHOLD_INVALID,
};

// Compares the block duration with the 1 ms threshold. Does not count the
// result; taskBlockPassesBasicEligibility() does. Fails closed with
// THRESHOLD_INVALID when the threshold is 0, so sub-millisecond blocks cannot
// pass the filter.
TaskBlockDurationCheck checkTaskBlockDuration(u64 start_ticks, u64 end_ticks);

#ifdef UNIT_TEST
// Clears the cached threshold so the next checkTaskBlockDuration() call
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

#ifdef UNIT_TEST
// Overrides monitor callback timestamps; zero restores the real clock.
void setMonitorTaskBlockTicksForTest(u64 ticks);
#endif

// Starts a producer-owned run after flushing the preceding unowned wall tail.
// Called on the slot's owning thread, so pausing fallback accumulation also
// prevents a profiling signal from adding weight between the flush and admission.
u64 enterOwnedBlockRun(ProfiledThread* current, ThreadFilter::SlotID slot_id,
                       OSThreadState state, BlockRunOwner owner = BlockRunOwner::JAVA
                       TASK_BLOCK_DIAGNOSTIC_ONLY(, TaskBlockDiagnosticRecord* diagnostic = nullptr));

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 blocker,
                           u64 unblocking_span_id);

// Cleans up an exited producer even if dump/stop rotation rejects recording work.
// end_ticks shares the caller's eligibility timestamp; zero samples the clock here.
bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 start_ticks,
                           const Context& context, u64 blocker,
                           u64 unblocking_span_id, u64 end_ticks = 0,
                           const MonitorEntryStackLease* entry_stack = nullptr);

// JVMTI event callbacks for the native monitor-contention/Object.wait task-block
// producer. Registered directly into jvmtiEventCallbacks by vmEntry.cpp.
void JNICALL MonitorContendedEnter(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                                   jobject object);
void JNICALL MonitorContendedEntered(jvmtiEnv *jvmti, JNIEnv *jni,
                                     jthread thread, jobject object);
void JNICALL MonitorWait(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                         jobject object, jlong timeout);
void JNICALL MonitorWaited(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                           jobject object, jboolean timed_out);

// Returns actual native monitor-event enablement for the caller's admission flag.
// Disabling is a no-op when the capability was never enabled.
bool setNativeMonitorTaskBlockEventsEnabled(bool enabled);

class TaskBlockActivity {
 private:
  Profiler* _profiler;
  bool _active;
  bool _owns_activity;

 public:
  // Admission for work that emits no TaskBlock itself, so rejection is not counted.
  struct Quiet {};
  explicit TaskBlockActivity(Quiet)
      : _profiler(Profiler::instance()),
        _active(_profiler->tryEnterTaskBlockActivityQuietly()),
        _owns_activity(_active) {}

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
  switch (checkTaskBlockDuration(start_ticks, end_ticks)) {
    case TaskBlockDurationCheck::ELIGIBLE:
      TASK_BLOCK_DIAGNOSTIC(BASIC_ELIGIBLE, diagnostic, 0);
      return true;
    case TaskBlockDurationCheck::THRESHOLD_INVALID:
      Counters::increment(TASK_BLOCK_THRESHOLD_INVALID);
      return false;
    case TaskBlockDurationCheck::TOO_SHORT:
      break;
  }
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

static inline bool recordTaskBlockIfEligible(
    int tid, jthread thread, int start_depth, u64 start_ticks, u64 end_ticks,
    const Context& ctx, u64 blocker, u64 unblocking_span_id,
    OSThreadState observed_state, bool activity_already_held = false,
    const MonitorEntryStackLease* entry_stack = nullptr
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
      Profiler::instance()->recordTaskBlock(tid, thread, start_depth, &event, entry_stack TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic, &rejection));
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
