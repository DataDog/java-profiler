/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockRecorder.h"

#include "context_api.h"
#include "jvmSupport.h"
#include "threadLocalData.inline.h"
#include "tsc.h"

#include <atomic>

static const u64 kMinTaskBlockNanos = 1000000;
static std::atomic<u64> g_min_task_block_ticks{0};

static u64 computeMinTaskBlockTicks() {
  return (TSC::frequency() * kMinTaskBlockNanos) / NANOTIME_FREQ;
}

void initializeTaskBlockDurationThreshold() {
  g_min_task_block_ticks.store(computeMinTaskBlockTicks(), std::memory_order_release);
}

bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  u64 min_ticks = g_min_task_block_ticks.load(std::memory_order_acquire);
  if (min_ticks == 0) min_ticks = computeMinTaskBlockTicks();
  return end_ticks > start_ticks && end_ticks - start_ticks >= min_ticks;
}

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           jthread thread, int start_depth, u64 block_token,
                           u64 blocker, u64 unblocking_span_id) {
  u64 start_ticks = 0;
  Context context{};
  if (!current->taskBlockExit(block_token, start_ticks, context)) {
    return false;
  }

  return finishTaskBlockAtExit(
      current, thread_filter, thread, start_depth, block_token, start_ticks,
      context, blocker, unblocking_span_id);
}

bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter, jthread thread,
                           int start_depth, u64 block_token, u64 start_ticks,
                           const Context& context, u64 blocker,
                           u64 unblocking_span_id, u64 end_ticks) {
  if (end_ticks == 0) end_ticks = TSC::ticks();
  Profiler* profiler = Profiler::instance();
  bool recording_enabled = profiler->taskBlockEnabled();
  TaskBlockActivity activity;

  ThreadFilter::SlotID slot_id = ThreadFilter::tokenSlotId(block_token);
  u64 generation = ThreadFilter::tokenGeneration(block_token);
  ThreadFilter::SlotID current_slot = current->filterSlotId();
  if (current_slot < 0) {
    current_slot = thread_filter->slotIdByTid(current->tid());
  }
  BlockRunSnapshot snapshot;
  bool exited = current_slot == slot_id &&
      thread_filter->snapshotAndExitBlockedRun(slot_id, generation, &snapshot);

  if (!activity.active()) {
    // TaskBlockActivity's constructor already incremented TASK_BLOCK_DROPPED_ROTATION.
    return false;
  }
  if (!recording_enabled || !exited) {
    return false;
  }
  if (!snapshot.context_eligible) {
    Counters::increment(TASK_BLOCK_SKIPPED_CONTEXT_WINDOW);
    return false;
  }

  return recordTaskBlockIfEligible(
      current->tid(), thread, start_depth, start_ticks, end_ticks, context,
      blocker, unblocking_span_id, snapshot.active_state, true);
}

static u64 monitorBlockerHash(jvmtiEnv *jvmti, jobject object) {
  if (object == NULL) return 0;
  jint hash = 0;
  if (jvmti->GetObjectHashCode(object, &hash) != JVMTI_ERROR_NONE) return 0;
  return static_cast<u64>(static_cast<uint32_t>(hash));
}

// Deliberately takes no jvmtiEnv: no JVMTI call may run on this hot path. The
// blocker identity hash is resolved lazily in monitorBlockExit, and only for
// intervals that pass the minimum-duration filter (GetObjectHashCode mutates the
// object's mark word on HotSpot).
static void monitorBlockEnter(JNIEnv *jni, jthread thread,
                              OSThreadState state) {
  Profiler *profiler = Profiler::instance();
  if (!profiler->taskBlockEnabled() ||
      !profiler->nativeMonitorTaskBlockEnabled() ||
      !JVMSupport::isPlatformThread(jni, thread)) {
    return;
  }
  ProfiledThread *current = ProfiledThread::initCurrentThreadSignalSafe();
  if (current == nullptr) return;
  Context context = ContextApi::snapshot();
  if (context.spanId != 0) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return;
  }

  if (!current->monitorEnter(TSC::ticks(), context, /*blocker=*/0, state)) {
    u64 token = current->monitorBlockToken();
    ThreadFilter *tf = profiler->threadFilter();
    bool current_owner = false;
    if (token != 0) {
      ThreadFilter::SlotID slot_id = ThreadFilter::tokenSlotId(token);
      ThreadFilter::Slot *slot = current->filterSlotId() == slot_id
          ? tf->activeSlotForId(slot_id, current->tid())
          : nullptr;
      if (slot != nullptr) {
        BlockRunSnapshot snapshot = slot->snapshotBlockRun();
        current_owner = snapshot.isActive() &&
            snapshot.owner == BlockRunOwner::JVMTI &&
            snapshot.generation == ThreadFilter::tokenGeneration(token);
      }
    }
    if (current_owner) {
      return;
    }
    current->clearMonitorBlock();
    if (!current->monitorEnter(TSC::ticks(), context, /*blocker=*/0, state)) {
      return;
    }
  }

  ThreadFilter *tf = profiler->threadFilter();
  ThreadFilter::SlotID slot_id = tf->ensureCurrentThreadSlot(current);
  if (!tf->unfilteredWallTrackingActive() || slot_id < 0) {
    current->clearMonitorBlock();
    return;
  }
  u64 token =
      tf->enterBlockedRun(slot_id, state, BlockRunOwner::JVMTI);
  if (token == 0) {
    ThreadFilter::Slot *slot = tf->slotForId(slot_id);
    if (slot != nullptr && slot->inContextWindow()) {
      Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    }
    current->clearMonitorBlock();
    return;
  }
  current->setMonitorBlockToken(token);
}

static void monitorBlockExit(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                             jobject object, OSThreadState state) {
  Profiler *profiler = Profiler::instance();
  if (!profiler->taskBlockEnabled() || !profiler->nativeMonitorTaskBlockEnabled()) {
    return;
  }
  if (!JVMSupport::isPlatformThread(jni, thread)) return;
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) return;

  u64 start_ticks = 0;
  Context context{};
  // The entry side no longer records a blocker; it is resolved lazily below.
  u64 blocker = 0;
  u64 token = 0;
  if (!current->monitorExit(state, start_ticks, context, blocker, token) ||
      token == 0) {
    return;
  }

  // Resolve the blocker identity hash only for intervals that will actually pass
  // the eligibility filter. GetObjectHashCode mutates the object's mark word on
  // HotSpot, so it must not run for short, high-frequency contention that gets
  // discarded anyway. That mutation also permanently disables biased locking for
  // this object, a cost borne by the profiled application, not just the profiler.
  // These conditions mirror taskBlockPassesBasicEligibility, and the same
  // end_ticks is handed down so there is no boundary drift.
  u64 end_ticks = TSC::ticks();
  if (context.spanId == 0 && exceedsMinTaskBlockDuration(start_ticks, end_ticks)) {
    blocker = monitorBlockerHash(jvmti, object);
  }

  finishTaskBlockAtExit(current, profiler->threadFilter(), thread, 0, token,
                        start_ticks, context, blocker, 0, end_ticks);
}

void JNICALL MonitorContendedEnter(jvmtiEnv *jvmti, JNIEnv *jni,
                                   jthread thread, jobject object) {
  monitorBlockEnter(jni, thread, OSThreadState::MONITOR_WAIT);
}

void JNICALL MonitorContendedEntered(jvmtiEnv *jvmti, JNIEnv *jni,
                                     jthread thread, jobject object) {
  monitorBlockExit(jvmti, jni, thread, object, OSThreadState::MONITOR_WAIT);
}

void JNICALL MonitorWait(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                         jobject object, jlong timeout) {
  if (!VM::monitorWaitEventsDelegated()) {
    monitorBlockEnter(jni, thread, OSThreadState::OBJECT_WAIT);
  }
}

void JNICALL MonitorWaited(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                           jobject object, jboolean timed_out) {
  if (!VM::monitorWaitEventsDelegated()) {
    monitorBlockExit(jvmti, jni, thread, object, OSThreadState::OBJECT_WAIT);
  }
}

bool setNativeMonitorTaskBlockEventsEnabled(bool enabled) {
  if (enabled) {
    return VM::nativeMonitorEventsAvailable() &&
        VM::setNativeMonitorEventsEnabled(true);
  }
  VM::setNativeMonitorEventsEnabled(false);
  return false;
}
