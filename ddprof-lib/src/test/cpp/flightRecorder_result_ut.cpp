/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "engine.h"
#include "event.h"
#include "flightRecorder.h"
#include "profiler.h"
#include "wallClock.h"

#include <gtest/gtest.h>
#include <memory>
#include <unordered_set>

TEST(FlightRecorderResultTest, RecordEventReturnsFalseWithoutActiveRecording) {
  FlightRecorder recorder;
  ExecutionEvent event;

  EXPECT_FALSE(recorder.recordEvent(/*lock_index=*/0, /*tid=*/1,
                                    /*call_trace_id=*/42, BCI_WALL, &event));
}

TEST(FlightRecorderResultTest, RecordEventDelegatedReturnsFalseWithoutActiveRecording) {
  FlightRecorder recorder;
  ExecutionEvent event;

  EXPECT_FALSE(recorder.recordEventDelegated(/*lock_index=*/0, /*tid=*/1,
                                             /*correlation_id=*/42, BCI_WALL,
                                             &event));
}

TEST(FlightRecorderResultTest, RecordEventDelegatedReturnsFalseForUnsupportedEventType) {
  FlightRecorder recorder;
  AllocEvent event;

  EXPECT_FALSE(recorder.recordEventDelegated(/*lock_index=*/0, /*tid=*/1,
                                             /*correlation_id=*/42, BCI_ALLOC,
                                             &event));
}

class RecordingTestAccessor {
public:
  static void collectThreads(Recording* recording, int stripe, std::unordered_set<int>& tids) {
    recording->_thread_ids[stripe][recording->_active_index.load()].collect(tids);
  }
};

class FlightRecorderTestAccessor {
public:
  static void setRecording(FlightRecorder* recorder, Recording* recording) {
    recorder->_rec = recording;
  }
};

namespace {
u64 readVar64(const Buffer* buffer, int& offset) {
  u64 value = 0;
  int shift = 0;
  unsigned char byte;
  do {
    byte = static_cast<unsigned char>(buffer->data()[offset++]);
    value |= static_cast<u64>(byte & 0x7f) << shift;
    shift += 7;
  } while (byte & 0x80);
  return value;
}
} // namespace

TEST(FlightRecorderResultTest, TaskBlockOverflowNeverSerializesAnUndefinedThread) {
  auto recording = std::make_unique<Recording>();
  FlightRecorder recorder;
  FlightRecorderTestAccessor::setRecording(&recorder, recording.get());
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  event._observedBlockingState = OSThreadState::SLEEPING;
  for (int tid = 1; tid <= 256; ++tid) {
    EXPECT_TRUE(recorder.recordTaskBlock(0, tid, &event));
  }
  Buffer* buffer = recording->buffer(0);
  int before = buffer->offset();
  EXPECT_FALSE(recorder.recordTaskBlock(0, 257, &event));
  EXPECT_EQ(before, buffer->offset()) << "overflow must reject before any event bytes are written";
  EXPECT_TRUE(recorder.recordTaskBlock(0, 1, &event)) << "a full table still represents existing tids";
  std::unordered_set<int> tids;
  RecordingTestAccessor::collectThreads(recording.get(), 0, tids);
  EXPECT_EQ(256u, tids.size());
  // Decode the real serializer's eventThread field, not just insertion status.
  int events = 0;
  for (int start = 0; start < buffer->offset();) {
    int cursor = start;
    u64 size = readVar64(buffer, cursor);
    readVar64(buffer, cursor); // type
    readVar64(buffer, cursor); // start
    readVar64(buffer, cursor); // duration
    int tid = static_cast<int>(readVar64(buffer, cursor));
    EXPECT_EQ(1u, tids.count(tid)) << "undefined serialized eventThread=" << tid;
    ASSERT_GT(size, 0u);
    start += size;
    ++events;
  }
  EXPECT_EQ(257, events);
  FlightRecorderTestAccessor::setRecording(&recorder, nullptr);
}

class ProfilerTestAccessor {
public:
  static void setOmit(Profiler* profiler, bool omit) { profiler->_omit_stacktraces = omit; }
  static FlightRecorder* recorder(Profiler* profiler) { return &profiler->_jfr; }
};

TEST(FlightRecorderResultTest, LightweightShortBurstsSerializeEveryUnitOfWeight) {
  auto recording = std::make_unique<Recording>();
  Profiler* profiler = Profiler::instance();
  FlightRecorder* recorder = ProfilerTestAccessor::recorder(profiler);
  FlightRecorderTestAccessor::setRecording(recorder, recording.get());
  bool previous_omit = profiler->omitStacktraces();
  ProfilerTestAccessor::setOmit(profiler, true);
  ThreadFilter* filter = profiler->threadFilter();
  filter->init("", true);
  constexpr int tid = 54321;
  auto current = std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)>(
      ProfiledThread::forTid(tid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(filter->registerThread(tid));
  auto* slot = profiler->blockTracker()->slotForId(current->filterSlotId());
  ASSERT_NE(nullptr, slot);
  for (int burst = 0; burst < 3; ++burst) {
    for (int observation = 0; observation < 7; ++observation) {
      ExecutionEvent event;
      event._thread_state = observation < 6 ? OSThreadState::SLEEPING : OSThreadState::RUNNABLE;
      event._execution_mode = ExecutionMode::NATIVE;
      u64 weight;
      if (!BaseWallClock::wallPrecheckForTest(current.get(), true, event._thread_state, weight, true)) {
        event._weight = weight;
        WallSampleRequest request;
        request.tid = tid;
        request.trace_epoch = profiler->recordingEpoch();
        EXPECT_TRUE(profiler->recordWallSample(nullptr, 1, 0, &event, request).ordinary_recorded);
      }
    }
  }
  u64 serialized_weight = 0;
  int events = 0;
  for (int stripe = 0; stripe < CONCURRENCY_LEVEL; ++stripe) {
    Buffer* buffer = recording->buffer(stripe);
    for (int start = 0; start < buffer->offset();) {
      int cursor = start;
      u64 size = readVar64(buffer, cursor);
      readVar64(buffer, cursor); // type
      readVar64(buffer, cursor); // time
      EXPECT_EQ(tid, readVar64(buffer, cursor));
      EXPECT_EQ(0ULL, readVar64(buffer, cursor)) << "lightweight samples must remain stackless";
      cursor += 2; // thread state and execution mode
      serialized_weight += readVar64(buffer, cursor);
      EXPECT_GT(size, 0u);
      if (size == 0) break;
      start += size;
      ++events;
    }
  }
  EXPECT_EQ(21, events);
  EXPECT_EQ(21ULL, serialized_weight);
  EXPECT_EQ(0ULL, slot->unowned_blocked_pending_weight.load());
  profiler->blockTracker()->resetAll();
  filter->deactivateRecording();
  ProfilerTestAccessor::setOmit(profiler, previous_omit);
  FlightRecorderTestAccessor::setRecording(recorder, nullptr);
}
