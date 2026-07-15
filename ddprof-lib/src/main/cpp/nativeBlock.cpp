/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeBlock.h"

#if defined(__linux__)

#include "context_api.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "threadLocalData.h"
#include "tsc.h"

#include <atomic>
#include <errno.h>

#ifdef UNIT_TEST
static std::atomic<NativeBlockScope::HookObserver> _native_block_observer{nullptr};

void NativeBlockScope::setHookObserverForTest(HookObserver observer) {
  _native_block_observer.store(observer, std::memory_order_release);
}

static void observeNativeBlockPhase(const char* phase, NativeBlockKind kind, int blocker_id) {
  NativeBlockScope::HookObserver observer =
      _native_block_observer.load(std::memory_order_acquire);
  if (observer != nullptr) {
    observer(phase, kind, blocker_id);
  }
}
#endif

NativeBlockScope::NativeBlockScope(NativeBlockKind kind, int blocker_id,
                                   OSThreadState state)
    : _blocker(blocker(kind, blocker_id)), _state(state) {
  int saved_errno = errno;
#ifdef UNIT_TEST
  observeNativeBlockPhase("enter", kind, blocker_id);
#endif

  Profiler* profiler = Profiler::instance();
  if (!profiler->taskBlockEnabled()) {
    errno = saved_errno;
    return;
  }

  ThreadFilter* thread_filter = profiler->threadFilter();
  if (!thread_filter->registryActive()) {
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
#ifdef UNIT_TEST
  observeNativeBlockPhase("exit", static_cast<NativeBlockKind>(_blocker >> 32),
                          static_cast<int>(_blocker & 0xffffffff));
#endif
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

  Profiler* profiler = Profiler::instance();
  bool recording_enabled = profiler->taskBlockEnabled();
  bool activity = profiler->tryEnterTaskBlockActivity();
  if (!activity) {
    profiler->waitForTaskBlockRotation();
  }
  ThreadFilter* thread_filter = profiler->threadFilter();
  BlockRunSnapshot snapshot{};
  snapshot.active_state = _state;
  snapshot.owner = BlockRunOwner::NATIVE;
  if (!thread_filter->registryActive() ||
      !thread_filter->snapshotAndExitBlockedRun(_slot_id, _generation, &snapshot)) {
    if (activity) {
      profiler->leaveTaskBlockActivity();
    } else {
      Counters::increment(TASK_BLOCK_DROPPED_ROTATION);
    }
    return;
  }

  if (!activity) {
    Counters::increment(TASK_BLOCK_DROPPED_ROTATION);
    return;
  }

  if (recording_enabled) {
    recordTaskBlockIfEligible(_tid, nullptr, 0, _start_ticks, end_ticks,
                              _context, _blocker, 0,
                              snapshot.active_state, true);
  }
  profiler->leaveTaskBlockActivity();
}

#endif // __linux__
