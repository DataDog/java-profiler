/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "taskBlockSegments.h"

#include <algorithm>
#include <climits>
#include <utility>

#include "counters.h"
#include "jvmThread.h"
#include "event.h"
#include "signalSafety.h"
#include "taskBlockRecorder.h"
#include "tsc.h"
#include "vmEntry.h"

OpenTaskBlockSegments::~OpenTaskBlockSegments() {
  if (_stacks != nullptr) {
    VM::jvmti()->Deallocate(reinterpret_cast<unsigned char*>(_stacks));
  }
}

void OpenTaskBlockSegments::collect(ThreadFilter* registry, WallClockBlockTracker* tracker) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  selectCandidates(registry, tracker, TSC::ticks());
  captureStacks();
}

#ifdef UNIT_TEST
void OpenTaskBlockSegments::collectWithoutStacksForTest(ThreadFilter* registry,
                                                        WallClockBlockTracker* tracker,
                                                        u64 now_ticks) {
  _stackless = true;
  selectCandidates(registry, tracker, now_ticks);
}
#endif

void OpenTaskBlockSegments::selectCandidates(ThreadFilter* registry, WallClockBlockTracker* tracker,
                                             u64 now_ticks) {
  for (ThreadFilter::SlotID slot = 0; slot < ThreadFilter::kMaxThreads; ++slot) {
    WallClockBlockTracker::OpenSegment segment;
    if (!tracker->readOpenSegment(slot, segment) ||
        checkTaskBlockDuration(segment.start, now_ticks) != TaskBlockDurationCheck::ELIGIBLE) {
      continue;
    }
    ThreadFilter::Slot* identity = registry->slotForId(slot);
    int tid = identity != nullptr ? identity->nativeTid() : -1;
    if (tid < 0 || registry->activeSlotForId(slot, tid) == nullptr) continue;
    _candidates.push_back({slot, tid, segment, -1});
  }
}

void OpenTaskBlockSegments::captureStacks() {
  jvmtiEnv* jvmti = VM::jvmti();
  JNIEnv* jni = VM::jni();
  if (_candidates.empty() || jvmti == nullptr || jni == nullptr) return;
  jint count = 0;
  jthread* all = nullptr;
  if (jvmti->GetAllThreads(&count, &all) != JVMTI_ERROR_NONE) return;

  // Sorted (tid, candidate) pairs; candidate counts can exceed a linear-scan budget.
  std::vector<std::pair<int, int>> by_tid;
  by_tid.reserve(_candidates.size());
  for (size_t i = 0; i < _candidates.size(); i++) {
    by_tid.emplace_back(_candidates[i].tid, static_cast<int>(i));
  }
  std::sort(by_tid.begin(), by_tid.end());
  std::vector<jthread> threads;
  for (jint i = 0; i < count; i++) {
    jthread thread = all[i];
    if (thread == nullptr) continue;
    int tid = JVMThread::nativeThreadId(jni, thread);
    if (jni->ExceptionCheck()) jni->ExceptionClear();
    auto it = std::lower_bound(by_tid.begin(), by_tid.end(), std::make_pair(tid, INT_MIN));
    if (tid >= 0 && it != by_tid.end() && it->first == tid && _candidates[it->second].stack < 0) {
      _candidates[it->second].stack = static_cast<int>(threads.size());
      threads.push_back(thread);
    } else {
      jni->DeleteLocalRef(thread);
    }
  }
  jvmti->Deallocate(reinterpret_cast<unsigned char*>(all));

  if (!threads.empty()) {
    jint frames = _max_depth < INT_MAX ? _max_depth + 1 : _max_depth;
    if (jvmti->GetThreadListStackTraces(static_cast<jint>(threads.size()), threads.data(), frames,
                                        &_stacks) != JVMTI_ERROR_NONE) {
      _stacks = nullptr;
    }
  }
  // The captured frames do not reference the jthreads; stack_info.thread is unused.
  for (jthread thread : threads) jni->DeleteLocalRef(thread);
  if (_stacks == nullptr) {
    for (Candidate& candidate : _candidates) candidate.stack = -1;
  }
}

bool OpenTaskBlockSegments::blockedInJvmti(const Candidate& candidate) const {
  if (_stackless) return true;
  if (candidate.stack < 0) return false;
  // A runnable Java thread is not blocked: its paired interval was abandoned
  // or is about to end, so its exit or recovery decides the remaining time.
  const jvmtiStackInfo& info = _stacks[candidate.stack];
  return info.frame_count > 0 &&
         (info.state & (JVMTI_THREAD_STATE_WAITING | JVMTI_THREAD_STATE_BLOCKED_ON_MONITOR_ENTER |
                        JVMTI_THREAD_STATE_IN_NATIVE)) != 0;
}

int OpenTaskBlockSegments::emit(TaskBlockSegmentSink* sink, ThreadFilter* registry,
                                WallClockBlockTracker* tracker, u64 dump_ticks, bool final_dump) {
  int emitted = 0;
  for (const Candidate& candidate : _candidates) {
    WallClockBlockTracker::OpenSegment segment;
    if (!tracker->readOpenSegment(candidate.slot, segment) ||
        segment.control != candidate.segment.control || !blockedInJvmti(candidate)) {
      continue;
    }
    ThreadFilter::Slot* identity = registry->activeSlotForId(candidate.slot, candidate.tid);
    WallClockBlockTracker::BlockState* block = tracker->slotForId(candidate.slot);
    OSThreadState state = block != nullptr ? block->activeBlockState() : OSThreadState::UNKNOWN;
    // Same rejections as the exit: a context crossing or a too-short segment.
    if (identity == nullptr || state == OSThreadState::UNKNOWN ||
        block->blockGeneration() != segment.generation() ||
        !block->activeBlockRemainedOutsideContextWindow(identity) ||
        checkTaskBlockDuration(segment.start, dump_ticks) != TaskBlockDurationCheck::ELIGIBLE) {
      continue;
    }
    TaskBlockEvent event{};
    const jvmtiFrameInfo* frames = candidate.stack >= 0 ? _stacks[candidate.stack].frame_buffer : nullptr;
    int num_frames = candidate.stack >= 0 ? _stacks[candidate.stack].frame_count : 0;
    // A trace stored for a segment that then loses its CAS is unreferenced, not wrong.
    if (!sink->storeTrace(candidate.tid, frames, num_frames, event._callTraceId)) {
      Counters::increment(TASK_BLOCK_STACK_CAPTURE_FAILED);
      continue;
    }
    if (!tracker->advanceOpenSegment(candidate.slot, segment, dump_ticks, final_dump)) continue;
    event._start = segment.start;
    event._end = dump_ticks;
    event._observedBlockingState = state;
    event._continued = true;
    if (sink->record(candidate.tid, &event)) {
      Counters::increment(TASK_BLOCK_EMITTED);
      emitted++;
    } else {
      Counters::increment(TASK_BLOCK_RECORD_FAILED);
    }
  }
  if (final_dump) {
    // Stop ends every open segment so no later exit reports pre-stop time.
    for (ThreadFilter::SlotID slot = 0; slot < ThreadFilter::kMaxThreads; ++slot) {
      WallClockBlockTracker::OpenSegment segment;
      if (tracker->readOpenSegment(slot, segment)) {
        tracker->advanceOpenSegment(slot, segment, dump_ticks, true);
      }
    }
  }
  return emitted;
}
