/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockRecorder.h"

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
                           ThreadFilter::SlotID slot_id, u64 generation,
                           u64 blocker, u64 unblocking_span_id) {
  u64 start_ticks = 0;
  Context context{};
  if (!current->taskBlockExit(block_token, start_ticks, context)) {
    return false;
  }

  if (slot_id != ThreadFilter::tokenSlotId(block_token) ||
      generation != ThreadFilter::tokenGeneration(block_token)) {
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
                           u64 unblocking_span_id) {
  Profiler* profiler = Profiler::instance();
  bool recording_enabled = profiler->taskBlockEnabled();
  bool activity = profiler->tryEnterTaskBlockActivity();

  ThreadFilter::SlotID slot_id = ThreadFilter::tokenSlotId(block_token);
  u64 generation = ThreadFilter::tokenGeneration(block_token);
  ThreadFilter::SlotID current_slot = current->filterSlotId();
  if (current_slot < 0) {
    current_slot = thread_filter->slotIdByTid(current->tid());
  }
  BlockRunSnapshot snapshot;
  bool exited = current_slot == slot_id &&
      thread_filter->snapshotAndExitBlockedRun(slot_id, generation, &snapshot);

  if (!activity) {
    Counters::increment(TASK_BLOCK_DROPPED_ROTATION);
    return false;
  }
  if (!recording_enabled || !exited) {
    profiler->leaveTaskBlockActivity();
    return false;
  }
  if (!snapshot.context_eligible) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    profiler->leaveTaskBlockActivity();
    return false;
  }

  bool recorded = recordTaskBlockIfEligible(
      current->tid(), thread, start_depth, start_ticks, TSC::ticks(), context,
      blocker, unblocking_span_id, snapshot.active_state, true);
  profiler->leaveTaskBlockActivity();
  return recorded;
}
