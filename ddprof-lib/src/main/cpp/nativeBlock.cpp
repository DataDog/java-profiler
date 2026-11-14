/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeBlock.h"

#if defined(__linux__)

#include "context_api.h"
#include "errnoGuard.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "threadLocalData.h"
#include "threadLocalData.inline.h"
#include "tsc.h"

#include <atomic>

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
  ErrnoGuard errno_guard;
#ifdef UNIT_TEST
  observeNativeBlockPhase("enter", kind, blocker_id);
#endif

  Profiler* profiler = Profiler::instance();
  if (!profiler->taskBlockEnabled()) {
    return;
  }

  ThreadFilter* thread_filter = profiler->threadFilter();
  if (!thread_filter->registryActive()) {
    return;
  }

  ProfiledThread* current = ProfiledThread::current();
  if (current == nullptr || current->threadType() != ProfiledThread::TYPE_JAVA_THREAD) {
    return;
  }

  if (current->isJvmInternalThread()) {
    Counters::increment(TASK_BLOCK_SKIPPED_JVM_INTERNAL_THREAD);
    return;
  }

  Context context = ContextApi::snapshot();
  if (context.spanId != 0) {
    Counters::increment(TASK_BLOCK_SKIPPED_TRACE_CONTEXT);
    return;
  }

  TaskBlockActivity activity;
  if (!activity.active()) return;
  ThreadFilter::SlotID slot_id = thread_filter->ensureOwnerSlot(*current);
  if (slot_id < 0) return;
  current->refreshBlockState(thread_filter->slotForId(slot_id)->recordingEpoch());
  u64 token = enterOwnedBlockRun(current, slot_id, state, BlockRunOwner::NATIVE);
  if (token == 0) return;

  _active = true;
  _tid = current->tid();
  _slot_id = slot_id;
  _generation = WallClockBlockTracker::tokenGeneration(token);
  _start_ticks = TSC::ticks();
  _context = context;
}

NativeBlockScope::~NativeBlockScope() {
  ErrnoGuard errno_guard;
#ifdef UNIT_TEST
  observeNativeBlockPhase("exit", static_cast<NativeBlockKind>(_blocker >> 32),
                          static_cast<int>(_blocker & 0xffffffff));
#endif
  if (!_active) {
    return;
  }
  finish(TSC::ticks());
}

void NativeBlockScope::finish(u64 end_ticks) {
  if (!_active) {
    return;
  }
  _active = false;

  ProfiledThread* current = ProfiledThread::current();
  if (current == nullptr || current->tid() != _tid) return;
  Profiler* profiler = Profiler::instance();
  finishTaskBlockAtExit(current, profiler->threadFilter(), profiler->blockTracker(),
                        nullptr, 0,
                        WallClockBlockTracker::encodeBlockRunToken(_slot_id, _generation),
                        _start_ticks, _context, _blocker, 0, end_ticks);
}

#endif // __linux__
