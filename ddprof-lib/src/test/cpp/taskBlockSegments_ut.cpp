/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include "counters.h"
#include "event.h"
#include "profiler.h"
#include "taskBlockRecorder.h"
#include "taskBlockSegments.h"
#include "threadFilter.h"
#include "threadLocalData.inline.h"
#include "wallClockBlockTracker.h"
#include "../../main/cpp/gtest_crash_handler.h"

class ProfilerTestAccessor {
 public:
  static bool exchangeTaskBlockEnabled(bool enabled) {
    return Profiler::instance()->_task_block_enabled.exchange(enabled, std::memory_order_acq_rel);
  }
};

namespace {

constexpr char kTestName[] = "TaskBlockSegmentsTest";
// With a 1 GHz source, one tick is one nanosecond and the threshold is 1e6 ticks.
constexpr u64 kMs = 1000000;
constexpr int kTid = 31001;

u64 nanosecondFrequency() { return 1000000000ULL; }

struct RecordedSegment {
  int tid;
  TaskBlockEvent event;
};

class RecordingSink : public TaskBlockSegmentSink {
 public:
  std::vector<RecordedSegment> segments;
  bool fail_trace = false;
  int trace_calls = 0;
  bool storeTrace(int tid, const jvmtiFrameInfo* frames, int num_frames, u64& id) override {
    trace_calls++;
    id = fail_trace ? 0 : 77;
    return !fail_trace;
  }
  bool record(int tid, TaskBlockEvent* event) override {
    segments.push_back({tid, *event});
    return true;
  }
};

std::atomic<int> g_exit_records{0};
TaskBlockEvent g_exit_event{};

Profiler::TaskBlockRecordResult captureExitEvent(int, jthread, int, TaskBlockEvent* event) {
  g_exit_event = *event;
  g_exit_records.fetch_add(1, std::memory_order_relaxed);
  return Profiler::TaskBlockRecordResult::RECORDED;
}

class TaskBlockSegmentsTest : public ::testing::Test {
 protected:
  ThreadFilter filter;
  WallClockBlockTracker tracker;
  ThreadFilter::SlotID slot = -1;
  bool previous_enabled = false;

  void SetUp() override {
    installGtestCrashHandler<kTestName>();
    setTaskBlockFrequencySourceForTest(nanosecondFrequency);
    resetTaskBlockDurationThresholdForTest();
    filter.setBlockTracker(&tracker);
    filter.init("", true);
    slot = filter.registerThread(kTid);
    ASSERT_GE(slot, 0);
    Counters::reset();
  }

  void TearDown() override {
    Profiler::setTaskBlockRecordOverrideForTest(nullptr);
    ProfilerTestAccessor::exchangeTaskBlockEnabled(previous_enabled);
    setTaskBlockFrequencySourceForTest(nullptr);
    initializeTaskBlockDurationThreshold();
    restoreDefaultSignalHandlers();
  }

  u64 enter(u64 start_ticks, BlockRunOwner owner = BlockRunOwner::TASK_BLOCK) {
    u64 token = tracker.enterBlockedRun(&filter, slot, OSThreadState::SLEEPING, owner, start_ticks);
    EXPECT_NE(0ULL, token);
    return token;
  }

  int dump(RecordingSink& sink, u64 dump_ticks, bool final_dump = false) {
    OpenTaskBlockSegments segments(64);
    segments.collectWithoutStacksForTest(&filter, &tracker, dump_ticks);
    return segments.emit(&sink, &filter, &tracker, dump_ticks, final_dump);
  }

  BlockRunSnapshot exitRun(u64 token) {
    BlockRunSnapshot snapshot;
    EXPECT_TRUE(tracker.snapshotAndExitBlockedRun(
        &filter, slot, WallClockBlockTracker::tokenGeneration(token), &snapshot));
    return snapshot;
  }
};

}  // namespace

TEST_F(TaskBlockSegmentsTest, DumpReportsElapsedPartAndExitClaimsTheRest) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;

  ASSERT_EQ(1, dump(sink, start + 3 * kMs));
  ASSERT_EQ(1u, sink.segments.size());
  EXPECT_EQ(kTid, sink.segments[0].tid);
  EXPECT_EQ(start, sink.segments[0].event._start);
  EXPECT_EQ(start + 3 * kMs, sink.segments[0].event._end);
  EXPECT_TRUE(sink.segments[0].event._continued);
  EXPECT_EQ(77ULL, sink.segments[0].event._callTraceId);
  EXPECT_EQ(OSThreadState::SLEEPING, sink.segments[0].event._observedBlockingState);
  EXPECT_EQ(0ULL, sink.segments[0].event._unblockingSpanId);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_EMITTED));

  BlockRunSnapshot snapshot = exitRun(token);
  EXPECT_TRUE(snapshot.segment_claimed);
  EXPECT_TRUE(snapshot.segment_advanced);
  EXPECT_EQ(start + 3 * kMs, snapshot.segment_start);
}

TEST_F(TaskBlockSegmentsTest, ExitWithoutDumpClaimsEntrySegmentUnadvanced) {
  u64 token = enter(5 * kMs);
  BlockRunSnapshot snapshot = exitRun(token);
  EXPECT_TRUE(snapshot.segment_claimed);
  EXPECT_FALSE(snapshot.segment_advanced);
  EXPECT_EQ(5 * kMs, snapshot.segment_start);
  WallClockBlockTracker::OpenSegment segment;
  EXPECT_FALSE(tracker.readOpenSegment(slot, segment)) << "the exit closes the segment";
}

TEST_F(TaskBlockSegmentsTest, SubMillisecondSegmentIsCarriedToTheNextDump) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;

  EXPECT_EQ(0, dump(sink, start + kMs - 1)) << "an interval under 1 ms emits nothing";
  ASSERT_EQ(1, dump(sink, start + 2 * kMs));
  EXPECT_EQ(0, dump(sink, start + 2 * kMs + kMs / 2)) << "a 0.5 ms segment is carried";
  ASSERT_EQ(1, dump(sink, start + 4 * kMs));
  ASSERT_EQ(2u, sink.segments.size());
  EXPECT_EQ(start, sink.segments[0].event._start);
  EXPECT_EQ(start + 2 * kMs, sink.segments[1].event._start)
      << "the carried part starts where the previous segment ended";
  EXPECT_EQ(start + 4 * kMs, sink.segments[1].event._end);
  EXPECT_EQ(start + 4 * kMs, exitRun(token).segment_start);
}

TEST_F(TaskBlockSegmentsTest, ChangedTokenBetweenCollectAndEmitIsSkipped) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  OpenTaskBlockSegments segments(64);
  segments.collectWithoutStacksForTest(&filter, &tracker, start + 2 * kMs);
  exitRun(token);
  u64 next = enter(start + 3 * kMs);
  RecordingSink sink;
  EXPECT_EQ(0, segments.emit(&sink, &filter, &tracker, start + 6 * kMs, false));
  EXPECT_TRUE(sink.segments.empty());
  BlockRunSnapshot snapshot = exitRun(next);
  EXPECT_FALSE(snapshot.segment_advanced) << "the new run must not inherit the old candidate";
  EXPECT_EQ(start + 3 * kMs, snapshot.segment_start);
}

TEST_F(TaskBlockSegmentsTest, FailedTraceStoreLeavesSegmentOpen) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  sink.fail_trace = true;
  EXPECT_EQ(0, dump(sink, start + 2 * kMs));
  EXPECT_EQ(1, sink.trace_calls);
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_STACK_CAPTURE_FAILED));
  BlockRunSnapshot snapshot = exitRun(token);
  EXPECT_FALSE(snapshot.segment_advanced);
  EXPECT_EQ(start, snapshot.segment_start);
}

TEST_F(TaskBlockSegmentsTest, ContextWindowCrossingIsNotReportedAtDump) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  ThreadFilter::Slot* identity = filter.slotForId(slot);
  ASSERT_TRUE(identity->enterContextWindow());
  ASSERT_TRUE(identity->exitContextWindow());
  RecordingSink sink;
  EXPECT_EQ(0, dump(sink, start + 2 * kMs));
  EXPECT_FALSE(exitRun(token).segment_advanced);
}

TEST_F(TaskBlockSegmentsTest, FinalDumpReportsAndClosesEveryOpenSegment) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  ASSERT_EQ(1, dump(sink, start + 2 * kMs, true));
  EXPECT_TRUE(sink.segments[0].event._continued);
  WallClockBlockTracker::OpenSegment segment;
  EXPECT_FALSE(tracker.readOpenSegment(slot, segment));
  EXPECT_FALSE(exitRun(token).segment_claimed) << "stop already reported the open part";
}

TEST_F(TaskBlockSegmentsTest, FinalDumpClosesShortSegmentWithoutReportingIt) {
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  EXPECT_EQ(0, dump(sink, start + kMs / 2, true));
  EXPECT_TRUE(sink.segments.empty());
  EXPECT_FALSE(exitRun(token).segment_claimed);
}

TEST_F(TaskBlockSegmentsTest, RunEndingPathsCloseTheSegment) {
  RecordingSink sink;
  u64 token = enter(10 * kMs);
  ASSERT_TRUE(tracker.exitBlockedRun(slot, WallClockBlockTracker::tokenGeneration(token)));
  EXPECT_EQ(0, dump(sink, 20 * kMs)) << "exitBlockedRun";
  enter(30 * kMs, BlockRunOwner::JAVA);
  tracker.clearActiveBlockRun(slot);
  EXPECT_EQ(0, dump(sink, 40 * kMs)) << "clearActiveBlockRun";
  enter(50 * kMs);
  tracker.resetSlot(slot);
  EXPECT_EQ(0, dump(sink, 60 * kMs)) << "resetSlot";
  enter(70 * kMs);
  tracker.resetAll();
  EXPECT_EQ(0, dump(sink, 80 * kMs)) << "resetAll";
  EXPECT_TRUE(sink.segments.empty());
}

TEST_F(TaskBlockSegmentsTest, ContextClearKeepsPairedTaskBlockSegmentOpen) {
  enter(10 * kMs);
  tracker.clearActiveBlockRun(slot);
  RecordingSink sink;
  EXPECT_EQ(1, dump(sink, 20 * kMs));
}

// The exit reports the last segment from the claimed start, with continued=false
// even when that segment is under 1 ms, because the whole interval passed it.
TEST_F(TaskBlockSegmentsTest, ExitEmitsShortLastSegmentOfLongInterval) {
  previous_enabled = ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
  Profiler::setTaskBlockRecordOverrideForTest(captureExitEvent);
  g_exit_records.store(0);
  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(kTid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot);
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  ASSERT_EQ(1, dump(sink, start + 2 * kMs));

  Context context{};
  const u64 end = start + 2 * kMs + kMs / 4;
  EXPECT_TRUE(finishTaskBlockAtExit(current.get(), &filter, &tracker, nullptr, 0, token, start,
                                    context, 0x11, 0x22, end));
  ASSERT_EQ(1, g_exit_records.load());
  EXPECT_EQ(start + 2 * kMs, g_exit_event._start);
  EXPECT_EQ(end, g_exit_event._end);
  EXPECT_FALSE(g_exit_event._continued);
  EXPECT_EQ(0x22ULL, g_exit_event._unblockingSpanId);
}

TEST_F(TaskBlockSegmentsTest, ExitAfterFinalDumpEmitsNothing) {
  previous_enabled = ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
  Profiler::setTaskBlockRecordOverrideForTest(captureExitEvent);
  g_exit_records.store(0);
  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(kTid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot);
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  ASSERT_EQ(1, dump(sink, start + 2 * kMs, true));
  Context context{};
  EXPECT_FALSE(finishTaskBlockAtExit(current.get(), &filter, &tracker, nullptr, 0, token, start,
                                     context, 0, 0, start + 5 * kMs));
  EXPECT_EQ(0, g_exit_records.load());
  EXPECT_EQ(BlockRunOwner::NONE, tracker.slotForId(slot)->activeBlockOwner());
}

// A caller-supplied end that a dump already passed still closes the chain with a one-tick
// segment, so the continued=false event keeps its blocker.
TEST_F(TaskBlockSegmentsTest, ExitEndBeforeRacingDumpStillEmitsClosingEvent) {
  previous_enabled = ProfilerTestAccessor::exchangeTaskBlockEnabled(true);
  Profiler::setTaskBlockRecordOverrideForTest(captureExitEvent);
  g_exit_records.store(0);
  std::unique_ptr<ProfiledThread, void (*)(ProfiledThread*)> current(
      ProfiledThread::forTid(kTid), ProfiledThread::deleteForTest);
  current->setFilterSlotId(slot);
  const u64 start = 10 * kMs;
  u64 token = enter(start);
  RecordingSink sink;
  ASSERT_EQ(1, dump(sink, start + 3 * kMs));
  Context context{};
  EXPECT_TRUE(finishTaskBlockAtExit(current.get(), &filter, &tracker, nullptr, 0, token, start,
                                    context, 0x11, 0, start + 3 * kMs));
  ASSERT_EQ(1, g_exit_records.load());
  EXPECT_EQ(start + 3 * kMs, g_exit_event._start);
  EXPECT_EQ(start + 3 * kMs + 1, g_exit_event._end);
  EXPECT_FALSE(g_exit_event._continued);
  EXPECT_EQ(0x11ULL, g_exit_event._blocker);
}

namespace {
struct Segment {
  u64 generation;
  u64 start;
  u64 end;
};
}  // namespace

// One owner opens and exits runs while a dump thread advances their segments
// as fast as it can. Every tick of every run must be reported exactly once.
TEST_F(TaskBlockSegmentsTest, DumpRacingExitReportsEveryTickExactlyOnce) {
  constexpr int kRuns = 100000;
  std::atomic<u64> clock{1};
  std::atomic<bool> done{false};
  std::vector<Segment> dumped;
  std::vector<Segment> exited;
  std::vector<Segment> runs;
  dumped.reserve(1 << 20);

  std::thread dumper([&] {
    while (!done.load(std::memory_order_acquire)) {
      WallClockBlockTracker::OpenSegment segment;
      if (!tracker.readOpenSegment(slot, segment)) continue;
      u64 end = clock.fetch_add(1, std::memory_order_acq_rel);
      if (tracker.advanceOpenSegment(slot, segment, end, false)) {
        dumped.push_back({segment.generation(), segment.start, end});
      }
    }
  });
  for (int i = 0; i < kRuns; i++) {
    u64 start = clock.fetch_add(1, std::memory_order_acq_rel);
    u64 token = tracker.enterBlockedRun(&filter, slot, OSThreadState::SLEEPING,
                                        BlockRunOwner::TASK_BLOCK, start);
    ASSERT_NE(0ULL, token);
    for (int spin = 0; spin < (i % 64); spin++) clock.fetch_add(1, std::memory_order_relaxed);
    BlockRunSnapshot snapshot;
    u64 generation = WallClockBlockTracker::tokenGeneration(token);
    ASSERT_TRUE(tracker.snapshotAndExitBlockedRun(&filter, slot, generation, &snapshot));
    ASSERT_TRUE(snapshot.segment_claimed);
    u64 end = clock.fetch_add(1, std::memory_order_acq_rel);
    ASSERT_LT(snapshot.segment_start, end);
    exited.push_back({generation, snapshot.segment_start, end});
    runs.push_back({generation, start, end});
  }
  done.store(true, std::memory_order_release);
  dumper.join();

  std::vector<Segment> all = dumped;
  all.insert(all.end(), exited.begin(), exited.end());
  std::sort(all.begin(), all.end(), [](const Segment& a, const Segment& b) {
    return a.generation != b.generation ? a.generation < b.generation : a.start < b.start;
  });
  size_t next = 0;
  for (const Segment& run : runs) {
    u64 cursor = run.start;
    while (next < all.size() && all[next].generation == run.generation) {
      ASSERT_EQ(cursor, all[next].start) << "gap or overlap in generation " << run.generation;
      ASSERT_LT(all[next].start, all[next].end);
      cursor = all[next].end;
      next++;
    }
    ASSERT_EQ(run.end, cursor) << "generation " << run.generation << " lost its tail";
  }
  EXPECT_EQ(all.size(), next) << "a segment belongs to no run";
  EXPECT_GT(dumped.size(), 0u) << "the race was never exercised";
}
