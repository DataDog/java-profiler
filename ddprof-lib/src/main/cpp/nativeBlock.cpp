/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeBlock.h"

#if defined(__linux__)

#include "context_api.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "thread.h"
#include "tsc.h"

#include <errno.h>

NativeBlockScope::NativeBlockScope(NativeBlockKind kind, int blocker_id,
                                   OSThreadState state)
    : _blocker(blocker(kind, blocker_id)), _state(state) {
  int saved_errno = errno;

  Profiler* profiler = Profiler::instance();
  if (!profiler->taskBlockAsyncActive()) {
    errno = saved_errno;
    return;
  }

  ThreadFilter* thread_filter = profiler->threadFilter();
  if (!thread_filter->enabled()) {
    errno = saved_errno;
    return;
  }

  ProfiledThread* current = ProfiledThread::currentSignalSafe();
  if (current == nullptr || current->threadType() != ProfiledThread::TYPE_JAVA_THREAD) {
    errno = saved_errno;
    return;
  }

  ThreadFilter::SlotID slot_id = current->filterSlotId();
  if (slot_id < 0) {
    errno = saved_errno;
    return;
  }

  Context context = ContextApi::snapshot();
  if (context.spanId != 0) {
    errno = saved_errno;
    return;
  }

  u64 token = thread_filter->enterBlockedRun(slot_id, state, BlockRunOwner::NATIVE);
  if (token == 0) {
    errno = saved_errno;
    return;
  }

  _active = true;
  _tid = current->tid();
  _slot_id = slot_id;
  _generation = ThreadFilter::tokenGeneration(token);
  _start_ticks = TSC::ticks();
  _context = context;
  errno = saved_errno;
}

NativeBlockScope::~NativeBlockScope() {
  if (!_active) {
    return;
  }
  int saved_errno = errno;
  finish(TSC::ticks());
  errno = saved_errno;
}

void NativeBlockScope::finish(u64 end_ticks) {
  if (!_active) {
    return;
  }
  _active = false;

  ThreadFilter* thread_filter = Profiler::instance()->threadFilter();
  BlockRunSnapshot snapshot{};
  snapshot.active_state = _state;
  snapshot.sampled_state = OSThreadState::UNKNOWN;
  snapshot.owner = BlockRunOwner::NATIVE;
  if (!thread_filter->enabled() ||
      !thread_filter->snapshotAndExitBlockedRun(_slot_id, _generation, &snapshot)) {
    return;
  }

  OSThreadState observed_state = snapshot.sampled_state != OSThreadState::UNKNOWN
                                     ? snapshot.sampled_state
                                     : _state;
  recordTaskBlockAsyncWithContextIfEligible(
      _tid, _start_ticks, end_ticks, _context, _blocker, 0,
      snapshot.anchored ? snapshot.anchor_sample_id : 0,
      snapshot.anchored ? snapshot.suppressed_sample_count : 0,
      observed_state);
}

#endif // __linux__
