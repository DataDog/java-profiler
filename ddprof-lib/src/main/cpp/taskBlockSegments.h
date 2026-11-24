/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TASK_BLOCK_SEGMENTS_H
#define _TASK_BLOCK_SEGMENTS_H

#include <jvmti.h>
#include <vector>

#include "threadFilter.h"
#include "wallClockBlockTracker.h"

struct TaskBlockEvent;

// Writes segments for OpenTaskBlockSegments::emit(); called with every stripe held.
class TaskBlockSegmentSink {
 public:
  virtual ~TaskBlockSegmentSink() = default;
  // Stores the captured frames; trace id 0 with true means no stack is recorded.
  virtual bool storeTrace(int tid, const jvmtiFrameInfo* frames, int num_frames,
                          u64& call_trace_id) = 0;
  virtual bool record(int tid, TaskBlockEvent* event) = 0;
};

// Reports the elapsed part of still-open owned TaskBlock intervals at a dump
// or stop. Owned by one Profiler::dump()/stop() call under _state_lock, which
// makes that call the tracker's single segment advancer.
class OpenTaskBlockSegments {
 public:
  // Records frames as the profiler's _max_stack_depth plus a truncation probe.
  explicit OpenTaskBlockSegments(int max_depth) : _max_depth(max_depth) {}
  ~OpenTaskBlockSegments();
  OpenTaskBlockSegments(const OpenTaskBlockSegments&) = delete;
  OpenTaskBlockSegments& operator=(const OpenTaskBlockSegments&) = delete;

  // Step 1, before any recording stripe: selects open segments of at least
  // 1 ms on live registry slots and captures their threads' stacks in one
  // GetThreadListStackTraces call. Needs a JNI-attached caller.
  void collect(ThreadFilter* registry, WallClockBlockTracker* tracker);

  // Step 2, with every recording stripe held: reports [start, dump_ticks) for
  // each candidate whose segment is unchanged and still eligible, then
  // advances it. final_dump (stop) also closes every other open segment.
  int emit(TaskBlockSegmentSink* sink, ThreadFilter* registry, WallClockBlockTracker* tracker,
           u64 dump_ticks, bool final_dump);

#ifdef UNIT_TEST
  // Gtests have no JVM: candidates then emit with this state and no frames.
  void collectWithoutStacksForTest(ThreadFilter* registry, WallClockBlockTracker* tracker,
                                   u64 now_ticks);
#endif

 private:
  struct Candidate {
    ThreadFilter::SlotID slot;
    int tid;
    WallClockBlockTracker::OpenSegment segment;
    // Index into _stacks, or -1 without a captured stack.
    int stack;
  };
  int _max_depth;
  std::vector<Candidate> _candidates;
  jvmtiStackInfo* _stacks = nullptr;
  bool _stackless = false;

  void selectCandidates(ThreadFilter* registry, WallClockBlockTracker* tracker, u64 now_ticks);
  void captureStacks();
  bool blockedInJvmti(const Candidate& candidate, OSThreadState state) const;
};

#endif // _TASK_BLOCK_SEGMENTS_H
