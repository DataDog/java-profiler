/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockRecorder.h"

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

bool exceedsMinTaskBlockDuration(u64 start_ticks, u64 end_ticks) {
  u64 min_ticks = g_min_task_block_ticks.load(std::memory_order_acquire);
  if (min_ticks == 0) min_ticks = computeMinTaskBlockTicks();
  // The threshold is 0 when TSC::frequency() is below 1 kHz, for example 0
  // when uncalibrated. Comparing against 0 would accept every block, so
  // reject instead; the caller counts the rejection as
  // TASK_BLOCK_SKIPPED_TOO_SHORT.
  if (min_ticks == 0) return false;
  return end_ticks > start_ticks && end_ticks - start_ticks >= min_ticks;
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
                           u64 unblocking_span_id) {
  Profiler* profiler = Profiler::instance();
  bool recording_enabled = profiler->taskBlockEnabled();
  TaskBlockActivity activity;

  ThreadFilter::SlotID slot_id = WallClockBlockTracker::tokenSlotId(block_token);
  u64 generation = WallClockBlockTracker::tokenGeneration(block_token);
  // beginTaskBlock0 resolves its slot through ThreadFilter::ensureCurrentThreadSlot(),
  // which self-heals a cached-but-stale slot_id (e.g. after a recording restart
  // reset the registry) back to this tid's real slot. The block duration between
  // enter and exit can span such a reset, so re-validate here too instead of
  // trusting the cached value directly - otherwise a stale cache makes the slot
  // comparison below meaningless and silently drops the event uncounted.
  ThreadFilter::SlotID current_slot = thread_filter->ensureCurrentThreadSlot(current);
  BlockRunSnapshot snapshot;
  bool exited = current_slot == slot_id &&
      tracker->snapshotAndExitBlockedRun(thread_filter, slot_id, generation,
                                         &snapshot);

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
      current->tid(), thread, start_depth, start_ticks, TSC::ticks(), context,
      blocker, unblocking_span_id, snapshot.active_state, true);
}
