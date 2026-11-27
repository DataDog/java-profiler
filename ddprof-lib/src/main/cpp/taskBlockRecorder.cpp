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

#if defined(DEBUG) || defined(UNIT_TEST)
static TaskBlockDiagnosticRecord taskBlockExitIdentity(ProfiledThread* current, ThreadFilter* registry, u64 block_token, u64 blocker) {
  TaskBlockDiagnosticRecord diagnostic = current->taskBlockDiagnosticOrigin();
  if (diagnostic.words[TaskBlockDiagnosticRecord::TOKEN] != block_token) {
    diagnostic.words[TaskBlockDiagnosticRecord::ORIGIN_EPOCH] = 0;
    diagnostic.words[TaskBlockDiagnosticRecord::LIFECYCLE] = 0;
    diagnostic.words[TaskBlockDiagnosticRecord::OWNER] = 0;
    diagnostic.words[TaskBlockDiagnosticRecord::STATE] = 0;
    diagnostic.words[TaskBlockDiagnosticRecord::START] = 0;
    diagnostic.words[TaskBlockDiagnosticRecord::VALID] &= ~(TaskBlockDiagnosticRecord::HAS_ORIGIN | TaskBlockDiagnosticRecord::HAS_IDENTITY);
  }
  diagnostic.words[TaskBlockDiagnosticRecord::TID] = current->tid();
  diagnostic.words[TaskBlockDiagnosticRecord::TOKEN] = block_token;
  diagnostic.words[TaskBlockDiagnosticRecord::BLOCKER] = blocker;
  diagnostic.words[TaskBlockDiagnosticRecord::CURRENT_EPOCH] = registry->recordingEpoch();
  diagnostic.words[TaskBlockDiagnosticRecord::CURRENT_SLOT] = static_cast<u64>(current->filterSlotId());
  auto* slot = registry->slotForId(current->filterSlotId());
  if (slot != nullptr) {
    diagnostic.words[TaskBlockDiagnosticRecord::SLOT_EPOCH] = slot->recordingEpoch();
    diagnostic.words[TaskBlockDiagnosticRecord::OBSERVED_LIFECYCLE] = slot->lifecycleGeneration();
    diagnostic.words[TaskBlockDiagnosticRecord::VALID] |= TaskBlockDiagnosticRecord::HAS_SLOT;
  }
  return diagnostic;
}
#endif

bool recordTaskBlockAtExit(ProfiledThread* current, ThreadFilter* thread_filter,
                           WallClockBlockTracker* tracker, jthread thread,
                           int start_depth, u64 block_token, u64 blocker,
                           u64 unblocking_span_id) {
#if defined(DEBUG) || defined(UNIT_TEST)
  TaskBlockDiagnosticRecord diagnostic{};
  TaskBlockDiagnosticRecord* diagnostic_ptr = &diagnostic;
  diagnostic = taskBlockExitIdentity(current, thread_filter, block_token, blocker);
#endif
  TASK_BLOCK_DIAGNOSTIC(EXIT_CALLED, diagnostic_ptr, 0);
  u64 start_ticks = 0;
  Context context{};
  if (!current->taskBlockExit(block_token, start_ticks, context)) {
#if defined(DEBUG) || defined(UNIT_TEST)
    if (block_token == 0) {
      TASK_BLOCK_DIAGNOSTIC(EXIT_ZERO_TOKEN, diagnostic_ptr, 0);
    } else {
      TASK_BLOCK_DIAGNOSTIC(EXIT_TLS_TOKEN_MISMATCH, diagnostic_ptr, current->taskBlockTokenForDiagnostic());
    }
#endif
    return false;
  }
  TASK_BLOCK_DIAGNOSTIC(EXIT_TLS_EXTRACTED, diagnostic_ptr, start_ticks);

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
  Profiler* profiler = Profiler::instance();
#if defined(DEBUG) || defined(UNIT_TEST)
  TaskBlockDiagnosticRecord diagnostic{};
  TaskBlockDiagnosticRecord* diagnostic_ptr = &diagnostic;
  diagnostic = taskBlockExitIdentity(current, thread_filter, block_token, blocker);
  diagnostic.words[TaskBlockDiagnosticRecord::START] = start_ticks;
  diagnostic.words[TaskBlockDiagnosticRecord::END] = end_ticks;
  diagnostic.words[TaskBlockDiagnosticRecord::BLOCKER] = blocker;
  diagnostic.words[TaskBlockDiagnosticRecord::CURRENT_EPOCH] = thread_filter->recordingEpoch();
#endif
  TASK_BLOCK_DIAGNOSTIC(EXIT_VALIDATION_BEGIN, diagnostic_ptr, 0);
  TaskBlockActivity activity(false TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic_ptr));
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
      TASK_BLOCK_DIAGNOSTIC(EXIT_CACHED_SLOT_FALLBACK, diagnostic_ptr, current_slot);
    }
  }
#if defined(DEBUG) || defined(UNIT_TEST)
  diagnostic.words[TaskBlockDiagnosticRecord::CURRENT_EPOCH] = thread_filter->recordingEpoch();
  diagnostic.words[TaskBlockDiagnosticRecord::CURRENT_SLOT] = static_cast<u64>(current_slot);
  auto* identity_slot = thread_filter->slotForId(current_slot);
  if (identity_slot != nullptr) {
    diagnostic.words[TaskBlockDiagnosticRecord::SLOT_EPOCH] = identity_slot->recordingEpoch();
    diagnostic.words[TaskBlockDiagnosticRecord::OBSERVED_LIFECYCLE] = identity_slot->lifecycleGeneration();
    diagnostic.words[TaskBlockDiagnosticRecord::VALID] |= TaskBlockDiagnosticRecord::HAS_SLOT;
  }
  if (current_slot < 0) {
    TASK_BLOCK_DIAGNOSTIC(OWNER_SLOT_UNAVAILABLE, diagnostic_ptr, 0);
  } else if (current_slot != slot_id) {
    TASK_BLOCK_DIAGNOSTIC(OWNER_SLOT_MISMATCH, diagnostic_ptr, slot_id);
  }
#endif
  BlockRunSnapshot snapshot;
  bool exited = current_slot == slot_id &&
      tracker->snapshotAndExitBlockedRun(thread_filter, slot_id, generation,
                                         &snapshot TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic_ptr));
#ifdef UNIT_TEST
  Profiler::runTaskBlockActivityHookForTest(
      Profiler::TaskBlockActivityStage::AFTER_EXIT);
#endif

  if (!activity.active()) {
    // tryEnterTaskBlockActivity() already counted the admission rejection.
    TASK_BLOCK_DIAGNOSTIC(EXIT_ACTIVITY_REJECTED, diagnostic_ptr, 0);
    return false;
  }
  if (!recording_enabled) {
    TASK_BLOCK_DIAGNOSTIC(EXIT_RECORDING_DISABLED, diagnostic_ptr, 0);
    return false;
  }
  if (!exited) {
    TASK_BLOCK_DIAGNOSTIC(EXIT_VALIDATION_REJECTED, diagnostic_ptr, 0);
    return false;
  }
  if (!snapshot.context_eligible) {
    TASK_BLOCK_DIAGNOSTIC(EXIT_CONTEXT_WINDOW_INELIGIBLE, diagnostic_ptr, 0);
    Counters::increment(TASK_BLOCK_SKIPPED_CONTEXT_WINDOW);
    return false;
  }

  TASK_BLOCK_DIAGNOSTIC(EXIT_ELIGIBLE, diagnostic_ptr, 0);
  return recordTaskBlockIfEligible(
      current->tid(), thread, start_depth, start_ticks,
      end_ticks == 0 ? TSC::ticks() : end_ticks, context,
      blocker, unblocking_span_id, snapshot.active_state, true TASK_BLOCK_DIAGNOSTIC_ONLY(, diagnostic_ptr));
}
