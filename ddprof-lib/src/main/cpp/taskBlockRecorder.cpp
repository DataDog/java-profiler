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

#ifdef UNIT_TEST
static std::atomic<TaskBlockFrequencySource> g_test_frequency_source{nullptr};

void resetTaskBlockDurationThresholdForTest() {
  g_min_task_block_ticks.store(0, std::memory_order_release);
}

void setTaskBlockFrequencySourceForTest(TaskBlockFrequencySource source) {
  g_test_frequency_source.store(source, std::memory_order_release);
}
#endif

static u64 taskBlockTscFrequency() {
#ifdef UNIT_TEST
  TaskBlockFrequencySource source =
      g_test_frequency_source.load(std::memory_order_acquire);
  if (source != nullptr) return source();
#endif
  return TSC::frequency();
}

static u64 computeMinTaskBlockTicks() {
  return (taskBlockTscFrequency() * kMinTaskBlockNanos) / NANOTIME_FREQ;
}

void initializeTaskBlockDurationThreshold() {
  g_min_task_block_ticks.store(computeMinTaskBlockTicks(), std::memory_order_release);
}

TaskBlockDurationCheck checkTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  u64 min_ticks = g_min_task_block_ticks.load(std::memory_order_acquire);
  if (min_ticks == 0) min_ticks = computeMinTaskBlockTicks();
  // The threshold is 0 when TSC::frequency() is below 1 kHz, for example 0
  // when uncalibrated. Comparing against 0 would accept every block, so
  // reject instead. A separate result lets the caller count this as
  // TASK_BLOCK_THRESHOLD_INVALID, not as TASK_BLOCK_SKIPPED_TOO_SHORT.
  if (min_ticks == 0) return TaskBlockDurationCheck::THRESHOLD_INVALID;
  return end_ticks > start_ticks && end_ticks - start_ticks >= min_ticks
             ? TaskBlockDurationCheck::ELIGIBLE
             : TaskBlockDurationCheck::TOO_SHORT;
}

bool recoverAbandonedTaskBlock(ProfiledThread* current,
                               WallClockBlockTracker* tracker,
                               ThreadFilter::SlotID current_slot) {
  u64 abandoned = current->abandonTaskBlock();
  if (abandoned == 0) return false;
  Counters::increment(TASK_BLOCK_RECOVERED_ABANDONED);
  ThreadFilter::SlotID slot_id = -1;
  u64 generation = 0;
  if (WallClockBlockTracker::decodeBlockRunToken(abandoned, slot_id, generation) &&
      slot_id == current_slot) {
    tracker->exitBlockedRun(slot_id, generation);
  }
  return true;
}

u64 enterOwnedBlockRun(ProfiledThread* current, ThreadFilter::SlotID slot_id,
                       OSThreadState state, BlockRunOwner owner) {
  Profiler* profiler = Profiler::instance();
  ThreadFilter* registry = profiler->threadFilter();
  WallClockBlockTracker* tracker = profiler->blockTracker();
  WallClockBlockTracker::BlockState* slot = tracker->slotForId(slot_id);
  if (slot == nullptr) return 0;

  bool fallback_enabled = slot->pauseUnownedBlockedFallback();
  if (fallback_enabled &&
      slot->unowned_blocked_pending_weight.load(std::memory_order_acquire) != 0) {
    // Signal handlers normally own this write path. A producer needs the
    // same stop/dump exclusion before replaying a cached trace into JFR.
    TaskBlockActivity activity;
    if (!activity.active() || !registry->unfilteredWallTrackingActive() ||
        registry->activeSlotForId(slot_id, current->tid()) == nullptr) {
      slot->resumeUnownedBlockedFallback();
      return 0;
    }
    CriticalSection cs(current);
    // The stripe-held writer retains the original context and epoch segments.
    // Admission must not erase pending provenance when a write cannot commit.
    if (!profiler->recordUnownedBlockedTail(current->tid(), slot_id)) {
      slot->resumeUnownedBlockedFallback();
      return 0;
    }
  }

  u64 token = tracker->enterBlockedRun(registry, slot_id, state, owner);
  if (token == 0 && fallback_enabled) slot->resumeUnownedBlockedFallback();
  return token;
}

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 blocker,
                           u64 unblocking_span_id) {
  u64 start_ticks = 0;
  Context context{};
  if (!current->taskBlockExit(block_token, start_ticks, context)) {
    return false;
  }

  return finishTaskBlockAtExit(
      current, thread_filter, tracker, thread, start_depth, block_token,
      start_ticks, context, blocker, unblocking_span_id);
}

bool finishTaskBlockAtExit(ProfiledThread* current,
                           ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 start_ticks,
                           const Context& context, u64 blocker,
                           u64 unblocking_span_id, u64 end_ticks) {
  if (end_ticks == 0) end_ticks = TSC::ticks();
  Profiler* profiler = Profiler::instance();
  TaskBlockActivity activity;
  bool recording_enabled = profiler->taskBlockEnabled();

  ThreadFilter::SlotID slot_id = WallClockBlockTracker::tokenSlotId(block_token);
  u64 generation = WallClockBlockTracker::tokenGeneration(block_token);
  // A stopped registry still owns its native identities. End that cached run
  // without allocating; active recordings instead revalidate owner projection.
  ThreadFilter::SlotID current_slot = thread_filter->ensureOwnerSlot(*current);
  if (current_slot < 0 && !thread_filter->registryActive()) {
    auto* identity = thread_filter->slotForId(current->filterSlotId());
    if (identity != nullptr && identity->nativeTid() == current->tid()) {
      current_slot = current->filterSlotId();
    }
  }
  BlockRunSnapshot snapshot;
  bool exited = current_slot == slot_id &&
      tracker->snapshotAndExitBlockedRun(thread_filter, slot_id, generation,
                                         &snapshot);
#ifdef UNIT_TEST
  Profiler::runTaskBlockActivityHookForTest(
      Profiler::TaskBlockActivityStage::AFTER_EXIT);
#endif

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

#ifdef UNIT_TEST
static u64 g_monitor_ticks_for_test = 0;

void setMonitorTaskBlockTicksForTest(u64 ticks) {
  g_monitor_ticks_for_test = ticks;
}
#endif

static inline u64 monitorTicks() {
#ifdef UNIT_TEST
  if (g_monitor_ticks_for_test != 0) return g_monitor_ticks_for_test;
#endif
  return TSC::ticks();
}

static u64 monitorBlockerHash(jvmtiEnv *jvmti, jobject object) {
  if (object == NULL) return 0;
  jint hash = 0;
  if (jvmti->GetObjectHashCode(object, &hash) != JVMTI_ERROR_NONE) return 0;
  return static_cast<u64>(static_cast<uint32_t>(hash));
}

// Entry takes no jvmtiEnv: monitorBlockExit resolves the blocker hash after filtering.
// GetObjectHashCode mutates HotSpot's object mark word, so short intervals avoid it.
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

  ThreadFilter *tf = profiler->threadFilter();
  ThreadFilter::SlotID slot_id = tf->ensureOwnerSlot(*current);
  if (!tf->unfilteredWallTrackingActive() || slot_id < 0) return;
  current->refreshBlockState(tf->slotForId(slot_id)->recordingEpoch());
  if (!current->monitorEnter(monitorTicks(), context, /*blocker=*/0, state)) {
    u64 token = current->monitorBlockToken();
    bool current_owner = false;
    if (token != 0) {
      ThreadFilter::SlotID slot_id = WallClockBlockTracker::tokenSlotId(token);
      ThreadFilter::Slot *slot = current->filterSlotId() == slot_id
          ? tf->activeSlotForId(slot_id, current->tid())
          : nullptr;
      if (slot != nullptr) {
        WallClockBlockTracker::BlockState *block_state = profiler->blockTracker()->slotForId(slot_id);
        current_owner = block_state != nullptr &&
            block_state->activeBlockState() != OSThreadState::UNKNOWN &&
            block_state->activeBlockOwner() == BlockRunOwner::JVMTI &&
            block_state->blockGeneration() == WallClockBlockTracker::tokenGeneration(token);
      }
    }
    if (current_owner) {
      return;
    }
    current->clearMonitorBlock();
    if (!current->monitorEnter(monitorTicks(), context, /*blocker=*/0, state)) {
      return;
    }
  }

  u64 token = enterOwnedBlockRun(current, slot_id, state, BlockRunOwner::JVMTI);
  if (token == 0) {
    ThreadFilter::Slot *slot = tf->slotForId(slot_id);
    if (slot != nullptr && slot->inContextWindow()) {
      Counters::increment(TASK_BLOCK_SKIPPED_CONTEXT_WINDOW);
    }
    current->clearMonitorBlock();
    return;
  }
  current->setMonitorBlockToken(token);
}

static void monitorBlockExit(jvmtiEnv *jvmti, JNIEnv *jni, jthread thread,
                             jobject object, OSThreadState state) {
  Profiler *profiler = Profiler::instance();
  ProfiledThread *current = ProfiledThread::current();
  if (current == nullptr) return;
  if (!JVMSupport::isPlatformThread(jni, thread)) return;

  u64 start_ticks = 0;
  Context context{};
  // The entry side no longer records a blocker; it is resolved lazily below.
  u64 blocker = 0;
  u64 token = 0;
  if (!current->monitorExit(state, start_ticks, context, blocker, token) ||
      token == 0) {
    return;
  }

  // Filter before GetObjectHashCode can mutate the object's mark word.
  // Share end_ticks with taskBlockPassesBasicEligibility to avoid boundary drift.
  u64 end_ticks = monitorTicks();
  if (profiler->taskBlockEnabled() && profiler->nativeMonitorTaskBlockEnabled() &&
      context.spanId == 0 &&
      checkTaskBlockDuration(start_ticks, end_ticks) == TaskBlockDurationCheck::ELIGIBLE) {
    blocker = monitorBlockerHash(jvmti, object);
  }

  finishTaskBlockAtExit(current, profiler->threadFilter(),
                        profiler->blockTracker(), thread, 0, token,
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
