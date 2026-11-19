/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"
#include "tsc.h"
#include <memory>
#include <future>
#include <chrono>
#include <thread>

class ProfilerTestAccessor {
public:
  static void prepareStop(Profiler& profiler, Engine* engine) {
    profiler._cpu_engine = engine;
    profiler._wall_engine = engine;
    profiler._state.store(RUNNING, std::memory_order_release);
  }
  static bool running(Profiler& profiler) { return profiler.state() == RUNNING; }
  static FlightRecorder& recorder(Profiler& profiler) { return profiler._jfr; }
  static u32 stripe(Profiler& profiler, int tid) { return profiler.getLockIndex(tid); }
};

class FlightRecorderTestAccessor {
public:
  static Recording* exchangeRecording(FlightRecorder& recorder, Recording* recording) {
    Recording* previous = recorder._rec;
    recorder._rec = recording;
    return previous;
  }
};

namespace {
class ScopedTailRecording {
  std::unique_ptr<Recording> _recording;
  FlightRecorder& _recorder;
  Recording* _previous;

public:
  explicit ScopedTailRecording(FlightRecorder& recorder)
      : _recording(std::make_unique<Recording>()), _recorder(recorder),
        _previous(FlightRecorderTestAccessor::exchangeRecording(recorder, _recording.get())) {}
  ~ScopedTailRecording() {
    FlightRecorderTestAccessor::exchangeRecording(_recorder, _previous);
  }
  RecordingBuffer* buffer(u32 stripe) { return _recording->buffer(stripe); }
  ScopedTailRecording(const ScopedTailRecording&) = delete;
  ScopedTailRecording& operator=(const ScopedTailRecording&) = delete;
};
} // namespace

class WallTailRecordingTest : public ::testing::Test {
protected:
  std::unique_ptr<Profiler> profiler;
  WallSampleRequest request;
  u64 origin = 0;
  u64 current = 0;
  struct TailWrite {
    u64 trace;
    ExecutionEvent sample;
    Context context;
  };
  std::vector<TailWrite> writes;
  u64 rejected_epoch = 0;

  void captureWrites() {
    profiler->sampleWriteHookArgForTest = this;
    profiler->sampleWriteHookForTest = [](u32, u64 trace, Event* event,
                                         const Context* context, void* arg) {
      auto* self = static_cast<WallTailRecordingTest*>(arg);
      const auto& sample = *static_cast<ExecutionEvent*>(event);
      if (sample._sample_ticks == self->rejected_epoch) return false;
      self->writes.push_back({trace, sample, *context});
      return true;
    };
  }

  void expectWrite(const TailWrite& write, u64 epoch, u64 weight) {
    EXPECT_EQ(origin, write.trace);
    EXPECT_EQ(epoch, write.sample._sample_ticks);
    EXPECT_EQ(weight, write.sample._weight);
    EXPECT_EQ(OSThreadState::SLEEPING, write.sample._thread_state);
    EXPECT_EQ(ExecutionMode::UNKNOWN, write.sample._execution_mode);
    EXPECT_EQ(111ULL, write.context.spanId);
    EXPECT_EQ(222ULL, write.context.rootSpanId);
    for (int i = 0; i < DD_TAGS_CAPACITY; ++i) EXPECT_EQ(11U + i, write.context.getTag(i));
  }

  void SetUp() override {
    ProfiledThread::initCurrentThreadSignalSafe();
    profiler = std::make_unique<Profiler>();
    profiler->blockTracker()->setUnownedContextSnapshotsNeeded(true);
    auto* registry = profiler->threadFilter();
    registry->init(nullptr, true);
    request.tid = 1234;
    request.slot_id = registry->registerThread(request.tid);
    ASSERT_GE(request.slot_id, 0);
    request.lifecycle_generation = registry->slotForId(request.slot_id)->lifecycleGeneration();
    request.registry_epoch = registry->recordingEpoch();
    request.trace_epoch = profiler->recordingEpoch();
    request.sampling_epoch_start = TSC::ticks();
    request.context_captured = true;
    request.flush_tail = true;
    request.unowned_sample = true;
    request.observed_state = OSThreadState::CONDVAR_WAIT;
    request.context.setTag(0, 22);
    ASGCT_CallFrame frame{};
    frame.method_id = reinterpret_cast<jmethodID>(0x1234);
    origin = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    frame.method_id = reinterpret_cast<jmethodID>(0x1235);
    current = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    ASSERT_GT(origin >> 32, 0ULL);
    ASSERT_GT(current >> 32, 0ULL);
    Context context{};
    context.spanId = 111;
    context.rootSpanId = 222;
    for (int i = 0; i < DD_TAGS_CAPACITY; ++i) context.setTag(i, 11 + i);
    ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
        request.slot_id, origin, OSThreadState::SLEEPING, context));
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
        request.slot_id, request.sampling_epoch_start));
  }

  WallSampleResult record() {
    ExecutionEvent event;
    event._thread_state = OSThreadState::CONDVAR_WAIT;
    return profiler->recordWallSample(nullptr, 1, current, &event, request);
  }

  void expectOriginRetained() {
    auto* block = profiler->blockTracker()->slotForId(request.slot_id);
    EXPECT_EQ(origin, block->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(1ULL, block->unowned_blocked_pending_weight.load());
    EXPECT_EQ(OSThreadState::SLEEPING, block->unowned_blocked_state.load());
    Context context{};
    u64 publication = 0;
    ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(request.slot_id, context, publication));
    EXPECT_EQ(11U, context.getTag(0));
  }
};

TEST_F(WallTailRecordingTest, ThreadTableOverflowRetainsTailUntilARepresentableChunk) {
  FlightRecorder& recorder = ProfilerTestAccessor::recorder(*profiler);
  {
    ScopedTailRecording output(recorder);
    u32 stripe = ProfilerTestAccessor::stripe(*profiler, request.tid);
    TaskBlockEvent event{};
    event._start = 1;
    event._end = 2;
    for (int tid = 1; tid <= 256; ++tid) {
      ASSERT_TRUE(recorder.recordTaskBlock(stripe, tid, &event));
    }
    ASSERT_GT(request.tid, 256) << "the retained tail's tid must be absent from the full table";
    int before = output.buffer(stripe)->offset();
    EXPECT_FALSE(profiler->threadFilter()->flushUnownedTails());
    EXPECT_EQ(before, output.buffer(stripe)->offset());
    expectOriginRetained();
    WallClockBlockTracker::WeightSegment segments[WallClockBlockTracker::kMaxWeightSegments];
    ASSERT_EQ(1U, profiler->blockTracker()->copyUnownedWeightSegments(request.slot_id, segments));
    EXPECT_EQ(request.sampling_epoch_start, segments[0].epoch_start);
    EXPECT_EQ(1ULL, segments[0].weight);
  }
  {
    ScopedTailRecording output(recorder);
    u32 stripe = ProfilerTestAccessor::stripe(*profiler, request.tid);
    EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
    EXPECT_GT(output.buffer(stripe)->offset(), 0);
    EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(request.slot_id)
                        ->unowned_blocked_pending_weight.load());
  }
}

TEST_F(WallTailRecordingTest, ContendedPrimaryDoesNotPublishAnUnrecordedTrace) {
  auto held = profiler->recordingLocksForTest();
  EXPECT_FALSE(record().ordinary_recorded);
  expectOriginRetained();
}

TEST_F(WallTailRecordingTest, ContendedTailRetainsOriginWithoutWaiting) {
  auto held = profiler->recordingLocksForTest();
  EXPECT_FALSE(record().tail_recorded);
  expectOriginRetained();
}

TEST_F(WallTailRecordingTest, InactiveRecordingDoesNotPublishAnUnrecordedTrace) {
  EXPECT_FALSE(record().ordinary_recorded);
  expectOriginRetained();
}

TEST_F(WallTailRecordingTest, InactiveRecordingRetainsTailAndReleasesWriterStripe) {
  EXPECT_FALSE(record().tail_recorded);
  expectOriginRetained();
  auto held = profiler->recordingLocksForTest();
}

TEST_F(WallTailRecordingTest, TailCarriesWeightAccumulatedWhileBlocked) {
  constexpr u64 suppressed = 4;
  for (u64 observation = 1; observation < suppressed; ++observation) {
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
        request.slot_id, request.sampling_epoch_start));
  }
  struct TailObservation {
    u64 trace_id;
    u64 weight = 0;
    u64 epoch = 0;
    int writes = 0;
  } observation{origin};
  profiler->sampleWriteHookArgForTest = &observation;
  profiler->sampleWriteHookForTest = +[](u32, u64 id, Event* event,
                                        const Context* context, void* arg) {
    auto* observed = static_cast<TailObservation*>(arg);
    if (id == observed->trace_id) {
      auto* sample = static_cast<ExecutionEvent*>(event);
      observed->weight = sample->_weight;
      observed->epoch = sample->_sample_ticks;
      ++observed->writes;
      EXPECT_EQ(OSThreadState::SLEEPING, sample->_thread_state);
      EXPECT_NE(nullptr, context);
      if (context != nullptr) EXPECT_EQ(11U, context->getTag(0));
    }
    return true;
  };
  auto result = record();
  profiler->sampleWriteHookForTest = nullptr;
  profiler->sampleWriteHookArgForTest = nullptr;
  EXPECT_TRUE(result.ordinary_recorded);
  EXPECT_TRUE(result.tail_recorded);
  EXPECT_EQ(1, observation.writes);
  EXPECT_EQ(suppressed, observation.weight);
  EXPECT_EQ(request.sampling_epoch_start, observation.epoch);
  EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(request.slot_id)
                      ->unowned_blocked_pending_weight.load(std::memory_order_acquire));
}


TEST_F(WallTailRecordingTest, UnregisterEmitsPendingTailWithOriginProvenance) {
  captureWrites();
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, request.sampling_epoch_start));
  profiler->threadFilter()->unregisterThread(request.slot_id, request.tid);
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 2);
  EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(request.slot_id)
                     ->unowned_blocked_pending_weight.load());
}

TEST_F(WallTailRecordingTest, RetireEmitsPendingTailBeforeReclamation) {
  captureWrites();
  profiler->threadFilter()->retireThreadByTid(request.tid);
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
  EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(request.slot_id)
                     ->unowned_blocked_pending_weight.load());
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_EQ(1U, writes.size());
}

class WallTailTeardownTest : public WallTailRecordingTest,
                             public ::testing::WithParamInterface<bool> {
protected:
  void teardownOwner() {
    if (GetParam()) profiler->threadFilter()->retireThreadByTid(request.tid);
    else profiler->threadFilter()->unregisterThread(request.slot_id, request.tid);
  }
};

TEST_P(WallTailTeardownTest, StripeContentionRetainsTailAndPreventsSlotReuse) {
  captureWrites();
  auto* registry = profiler->threadFilter();
  auto* tracker = profiler->blockTracker();
  ASSERT_NE(0ULL, tracker->enterBlockedRun(registry, request.slot_id,
                                          OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK));
  {
    auto held = profiler->recordingLocksForTest();
    teardownOwner();
    expectOriginRetained();
    EXPECT_EQ(BlockRunOwner::NONE, tracker->slotForId(request.slot_id)->activeBlockOwner());
    EXPECT_EQ(-1, registry->slotIdByTid(request.tid));
    EXPECT_NE(request.slot_id, registry->registerThread(2345));
    EXPECT_FALSE(registry->flushUnownedTails());
    EXPECT_TRUE(writes.empty());
  }
  EXPECT_EQ(request.slot_id, registry->registerThread(3456));
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
}

TEST_P(WallTailTeardownTest, FailedWriteRetainsTailUntilStopFlushRetry) {
  captureWrites();
  rejected_epoch = request.sampling_epoch_start;
  teardownOwner();
  expectOriginRetained();
  EXPECT_FALSE(profiler->threadFilter()->flushUnownedTails());
  expectOriginRetained();
  EXPECT_TRUE(writes.empty());
  rejected_epoch = 0;
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_EQ(1U, writes.size());
}

INSTANTIATE_TEST_SUITE_P(UnregisterAndRetire, WallTailTeardownTest, ::testing::Bool());

TEST_F(WallTailRecordingTest, StopFlushCommitsOnlySuccessfulEpochSegments) {
  captureWrites();
  auto* tracker = profiler->blockTracker();
  u64 second = request.sampling_epoch_start + 1;
  u64 third = second + 1;
  ASSERT_TRUE(tracker->deferUnownedWeight(request.slot_id, second));
  ASSERT_TRUE(tracker->deferUnownedWeight(request.slot_id, third));
  rejected_epoch = second;
  const auto before = Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED);
  EXPECT_FALSE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_EQ(before + 2, Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED));
  ASSERT_EQ(2U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
  expectWrite(writes[1], third, 1);
  EXPECT_EQ(1ULL, tracker->slotForId(request.slot_id)->unowned_blocked_pending_weight.load());
  rejected_epoch = 0;
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  ASSERT_EQ(3U, writes.size());
  EXPECT_EQ(before + 3, Counters::getCounter(WC_UNOWNED_BLOCKED_TAIL_RECORDED));
  expectWrite(writes[2], second, 1);
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_EQ(3U, writes.size());
}

TEST_F(WallTailRecordingTest, StopFlushDoesNotSynthesizeAnOwnedTaskBlock) {
  captureWrites();
  auto* tracker = profiler->blockTracker();
  u64 token = tracker->enterBlockedRun(profiler->threadFilter(), request.slot_id,
                                       OSThreadState::SLEEPING, BlockRunOwner::TASK_BLOCK);
  ASSERT_NE(0ULL, token);
  EXPECT_TRUE(profiler->beginTaskBlockRotationForTest());
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  profiler->endTaskBlockRotationForTest();
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
  EXPECT_EQ(BlockRunOwner::TASK_BLOCK, tracker->slotForId(request.slot_id)->activeBlockOwner());
  EXPECT_EQ(WallClockBlockTracker::tokenGeneration(token),
            tracker->slotForId(request.slot_id)->blockGeneration());
}

TEST_F(WallTailRecordingTest, StopFailureDoesNotTearDownEnginesOrLeaveRotationClosed) {
  class StopObserver : public Engine {
  public:
    unsigned stops = 0;
    void stop() override { ++stops; }
  } engine;
  captureWrites();
  rejected_epoch = request.sampling_epoch_start;
  ProfilerTestAccessor::prepareStop(*profiler, &engine);
  Error error = profiler->stop();
  ASSERT_TRUE(error);
  EXPECT_STREQ("pending wall-clock tails could not be written; teardown skipped", error.message());
  EXPECT_TRUE(ProfilerTestAccessor::running(*profiler));
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0U, engine.stops);
  expectOriginRetained();
}

TEST_F(WallTailRecordingTest, StopCapacityRecoveryBudgetKeepsUnwrittenTailRetryable) {
  Engine engine;
  FlightRecorder& recorder = ProfilerTestAccessor::recorder(*profiler);
  ScopedTailRecording output(recorder);
  constexpr int max_retries = 1 + ThreadFilter::kMaxThreads / ThreadIdTable::capacity();
  struct Saturation {
    FlightRecorder& recorder;
    int tid;
    unsigned calls = 0;
  } saturation{recorder, request.tid};
  profiler->sampleWriteHookArgForTest = &saturation;
  profiler->sampleWriteHookForTest = [](u32 stripe, u64 trace, Event* event,
                                       const Context* context, void* arg) {
    auto& state = *static_cast<Saturation*>(arg);
    // Stop generating capacity failures after the budget, so removing the bound fails, not hangs.
    if (++state.calls > max_retries + 1) return false;
    TaskBlockEvent block{};
    block._start = 1;
    block._end = 2;
    for (int tid = 1; tid <= ThreadIdTable::capacity(); ++tid) {
      EXPECT_TRUE(state.recorder.recordTaskBlock(stripe, tid, &block));
    }
    EXPECT_FALSE(state.recorder.recordWallSample(
        stripe, state.tid, trace, static_cast<ExecutionEvent*>(event), *context));
    return false;
  };
  ProfilerTestAccessor::prepareStop(*profiler, &engine);
  Error error = profiler->stop();
  ASSERT_TRUE(error);
  EXPECT_EQ(max_retries + 1, saturation.calls);
  EXPECT_TRUE(ProfilerTestAccessor::running(*profiler));
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  expectOriginRetained();
  captureWrites();
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
}

TEST_F(WallTailRecordingTest, ConcurrentRetirementAndStopFlushDoNotDuplicateTail) {
  std::promise<void> entered;
  std::promise<void> release;
  auto resume = release.get_future().share();
  struct Pause {
    std::promise<void>& entered;
    std::shared_future<void>& resume;
    std::atomic<unsigned> calls{0};
  } pause{entered, resume};
  profiler->sampleWriteHookArgForTest = &pause;
  profiler->sampleWriteHookForTest = [](u32, u64, Event*, const Context*, void* arg) {
    auto* pause = static_cast<Pause*>(arg);
    if (pause->calls.fetch_add(1) == 0) {
      pause->entered.set_value();
      pause->resume.wait();
    }
    return true;
  };
  auto retire = std::async(std::launch::async, [&] {
    profiler->threadFilter()->retireThreadByTid(request.tid);
  });
  auto status = entered.get_future().wait_for(std::chrono::seconds(5));
  EXPECT_EQ(std::future_status::ready, status);
  if (status == std::future_status::ready) {
    EXPECT_FALSE(profiler->threadFilter()->flushUnownedTails());
    EXPECT_EQ(1U, pause.calls.load());
  }
  release.set_value();
  retire.get();
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_EQ(1U, pause.calls.load());
}

TEST_F(WallTailRecordingTest, RetiredTailRootSurvivesRotationsUntilSuccessfulFlush) {
  captureWrites();
  rejected_epoch = request.sampling_epoch_start;
  profiler->threadFilter()->retireThreadByTid(request.tid);
  for (int rotation = 0; rotation < 3; ++rotation) {
    bool found = false;
    {
      auto locks = profiler->recordingLocksForTest();
      profiler->processCallTraces([&](const CallTraceSet& traces) {
        for (auto* trace : traces) if (trace->trace_id == origin) found = true;
      });
    }
    EXPECT_TRUE(found);
    expectOriginRetained();
  }
  rejected_epoch = 0;
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
}

TEST_F(WallTailRecordingTest, StopRetainsTailUntilRetiringTidIsPublished) {
  captureWrites();
  auto* registry = profiler->threadFilter();
  auto* identity = registry->slotForId(request.slot_id);
  // Quiescent injection of the claim-before-publication gap, before retirement is queued.
  identity->tid.store(-1, std::memory_order_release);
  EXPECT_FALSE(registry->flushUnownedTails());
  expectOriginRetained();
  EXPECT_TRUE(writes.empty());
  identity->retiring_tid.store(request.tid, std::memory_order_release);
  EXPECT_TRUE(registry->flushUnownedTails());
  ASSERT_EQ(1U, writes.size());
  expectWrite(writes[0], request.sampling_epoch_start, 1);
}
