/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"
#include "tsc.h"
#include <memory>

class WallTailRecordingTest : public ::testing::Test {
protected:
  std::unique_ptr<Profiler> profiler;
  WallSampleRequest request;
  u64 origin = 0;
  u64 current = 0;

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
    context.setTag(0, 11);
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
