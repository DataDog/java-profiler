/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"
#include "recordingWriteFailureFixture.h"
#include "tsc.h"
#include <memory>

class RecordingTestAccessor {
public:
  // Match post-start hot writes: real flush failures retain bytes instead of throwing.
  static void activateHotWrites(Recording* recording) { recording->_cold_io = false; }
};

class FlightRecorderTestAccessor {
  FlightRecorder* _recorder;

public:
  FlightRecorderTestAccessor(FlightRecorder* recorder, Recording* recording)
      : _recorder(recorder) {
    recorder->_rec = recording;
  }
  ~FlightRecorderTestAccessor() { _recorder->_rec = nullptr; }
  FlightRecorderTestAccessor(const FlightRecorderTestAccessor&) = delete;
  FlightRecorderTestAccessor& operator=(const FlightRecorderTestAccessor&) = delete;
};

class ProfilerTestAccessor {
public:
  static FlightRecorder* recorder(Profiler* profiler) { return &profiler->_jfr; }
  static u32 stripe(Profiler* profiler, int tid) { return profiler->getLockIndex(tid); }
  static void prepareStop(Profiler* profiler, Engine* cpu, Engine* wall, Engine* alloc) {
    profiler->_cpu_engine = cpu;
    profiler->_wall_engine = wall;
    profiler->_alloc_engine = alloc;
    profiler->_activated_mask = EM_CPU | EM_WALL | EM_ALLOC;
    profiler->_state.store(RUNNING, std::memory_order_release);
  }
  static State state(Profiler* profiler) { return profiler->state(); }
};

class VMTestAccessor {
  jvmtiInterface_1_ _functions{};
  _jvmtiEnv _environment{};
  jvmtiEnv* _previous;

public:
  VMTestAccessor() : _previous(VM::_jvmti) {
    // There is no JVM in this binary; thread-name refresh has no Java threads.
    _functions.GetAllThreads = +[](jvmtiEnv*, jint*, jthread**) {
      return JVMTI_ERROR_WRONG_PHASE;
    };
    _environment.functions = &_functions;
    VM::_jvmti = &_environment;
  }
  ~VMTestAccessor() { VM::_jvmti = _previous; }
  VMTestAccessor(const VMTestAccessor&) = delete;
  VMTestAccessor& operator=(const VMTestAccessor&) = delete;
};

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
    request.context.spanId = 22;
    request.context.rootSpanId = 222;
    request.context.setTag(0, 22);
    ASGCT_CallFrame frame{};
    frame.method_id = reinterpret_cast<jmethodID>(0x1234);
    origin = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    frame.method_id = reinterpret_cast<jmethodID>(0x1235);
    current = profiler->callTraceStorageForTest()->put(1, &frame, false, 1);
    ASSERT_GT(origin >> 32, 0ULL);
    ASSERT_GT(current >> 32, 0ULL);
    Context context{};
    context.spanId = 11;
    context.rootSpanId = 111;
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

  void expectOriginRetained(u64 pending_weight = 1) {
    auto* block = profiler->blockTracker()->slotForId(request.slot_id);
    EXPECT_EQ(origin, block->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(pending_weight, block->unowned_blocked_pending_weight.load());
    EXPECT_EQ(OSThreadState::SLEEPING, block->unowned_blocked_state.load());
    Context context{};
    u64 publication = 0;
    ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(request.slot_id, context, publication));
    EXPECT_EQ(11ULL, context.spanId);
    EXPECT_EQ(111ULL, context.rootSpanId);
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

TEST_F(WallTailRecordingTest, ProducerFlushRetainsOriginWhenStripeIsContended) {
  auto held = profiler->recordingLocksForTest();
  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  expectOriginRetained();
}

TEST_F(WallTailRecordingTest, ProducerFlushRetainsOriginWhenOutputFails) {
  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  expectOriginRetained();
  auto held = profiler->recordingLocksForTest();
}

TEST_F(WallTailRecordingTest, ActiveOutputFlushFailureRetainsEpochUnitsContextAndTraceRoot) {
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  FlightRecorderTestAccessor active(ProfilerTestAccessor::recorder(profiler.get()), recording.get());
  RecordingBuffer* buffer = recording->buffer(ProfilerTestAccessor::stripe(profiler.get(), request.tid));
  buffer->skip(JFR_EVENT_FLUSH_THRESHOLD - 1);
  ASSERT_TRUE(recording->outputGood());
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
      request.slot_id, request.sampling_epoch_start));
  u64 second_epoch = request.sampling_epoch_start + 100;
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, second_epoch));
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, second_epoch));
  ASSERT_TRUE(output.failWrites());

  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  EXPECT_FALSE(recording->outputGood());
  EXPECT_GE(buffer->offset(), JFR_EVENT_FLUSH_THRESHOLD);
  expectOriginRetained(4);
  WallClockBlockTracker::WeightSegment segments[WallClockBlockTracker::kMaxWeightSegments];
  ASSERT_EQ(2u, profiler->blockTracker()->copyUnownedWeightSegments(request.slot_id, segments));
  EXPECT_EQ(request.sampling_epoch_start, segments[0].epoch_start);
  EXPECT_EQ(2ULL, segments[0].weight);
  EXPECT_EQ(second_epoch, segments[1].epoch_start);
  EXPECT_EQ(2ULL, segments[1].weight);
  int before = buffer->offset();
  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  EXPECT_EQ(before, buffer->offset());
  expectOriginRetained(4);
  auto held = profiler->recordingLocksForTest();
  CallTraceIdSet roots;
  profiler->blockTracker()->collectLiveTraceIds(roots);
  EXPECT_EQ(1u, roots.count(origin)) << "failed delivery must retain the original trace root";
}

TEST_F(WallTailRecordingTest, QuarantinedStopShutsDownEnginesRetainsCustodyAndRejectsRestart) {
  class StopObserver : public Engine {
  public:
    unsigned stops = 0;
    bool enabled = true;
    void enableEvents(bool value) override { enabled = value; }
    void stop() override { ++stops; }
  } cpu, wall, alloc;
  VMTestAccessor vm;
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  auto* recorder = ProfilerTestAccessor::recorder(profiler.get());
  FlightRecorderTestAccessor active(recorder, recording.get());
  RecordingBuffer* buffer = recording->buffer(ProfilerTestAccessor::stripe(profiler.get(), request.tid));
  buffer->skip(JFR_EVENT_FLUSH_THRESHOLD - 1);
  auto* classes = profiler->classMap();
  constexpr char class_name[] = "RetainedTailClass";
  const u32 class_id = classes->lookup(class_name, sizeof(class_name) - 1);
  ASSERT_NE(0U, class_id);
  const u64 dictionary_generation = classes->generation();
  ASSERT_TRUE(output.failWrites());
  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  ASSERT_FALSE(recording->outputGood());
  ASSERT_GE(buffer->offset(), JFR_EVENT_FLUSH_THRESHOLD);
  const int retained_bytes = buffer->offset();
  ProfilerTestAccessor::prepareStop(profiler.get(), &cpu, &wall, &alloc);

  Error error = profiler->stop();
  ASSERT_TRUE(error);
  EXPECT_STREQ("Incomplete recording output retained; restart refused", error.message());
  EXPECT_TRUE(recorder->outputQuarantined());
  EXPECT_EQ(ERROR, ProfilerTestAccessor::state(profiler.get()));
  EXPECT_EQ(1U, cpu.stops);
  EXPECT_EQ(1U, wall.stops);
  EXPECT_EQ(1U, alloc.stops);
  EXPECT_FALSE(cpu.enabled);
  EXPECT_FALSE(wall.enabled);
  EXPECT_FALSE(profiler->taskBlockEnabled());
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0ULL, profiler->threadFilter()->recordingEpoch());
  EXPECT_TRUE(recorder->active());
  EXPECT_EQ(retained_bytes, buffer->offset());
  expectOriginRetained();
  CallTraceIdSet roots;
  profiler->blockTracker()->collectLiveTraceIds(roots);
  EXPECT_EQ(1U, roots.count(origin));
  EXPECT_EQ(class_id, classes->standby()->lookup(class_name, sizeof(class_name) - 1));

  Arguments args;
  for (bool reset : {false, true}) {
    Error restart = profiler->start(args, reset);
    ASSERT_TRUE(restart);
    EXPECT_STREQ("Profiler encountered fatal error", restart.message());
    EXPECT_EQ(ERROR, ProfilerTestAccessor::state(profiler.get()));
    EXPECT_EQ(dictionary_generation, classes->generation());
    expectOriginRetained();
  }
  EXPECT_TRUE(profiler->stop());
  EXPECT_EQ(1U, cpu.stops);
  EXPECT_EQ(1U, wall.stops);
  EXPECT_EQ(1U, alloc.stops);
  EXPECT_EQ(retained_bytes, buffer->offset());
}

TEST_F(WallTailRecordingTest, ProducerFlushRetriesOnlyFailedEpochWithOriginalContext) {
  u64 second_epoch = request.sampling_epoch_start + 100;
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, second_epoch));
  struct Observation {
    u64 origin;
    u64 first_epoch;
    u64 second_epoch;
    int first_writes = 0;
    int second_writes = 0;
    bool fail_second = true;
  } observed{origin, request.sampling_epoch_start, second_epoch};
  profiler->sampleWriteHookArgForTest = &observed;
  profiler->sampleWriteHookForTest = +[](u32, u64 id, Event* event,
                                       const Context* context, void* arg) {
    auto* observation = static_cast<Observation*>(arg);
    auto* sample = static_cast<ExecutionEvent*>(event);
    EXPECT_EQ(observation->origin, id);
    EXPECT_EQ(1ULL, sample->_weight);
    EXPECT_EQ(OSThreadState::SLEEPING, sample->_thread_state);
    EXPECT_NE(nullptr, context);
    if (context != nullptr) EXPECT_EQ(11U, context->getTag(0));
    if (sample->_sample_ticks == observation->first_epoch) {
      ++observation->first_writes;
      return true;
    }
    EXPECT_EQ(observation->second_epoch, sample->_sample_ticks);
    ++observation->second_writes;
    return !observation->fail_second;
  };
  EXPECT_FALSE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  expectOriginRetained();
  observed.fail_second = false;
  EXPECT_TRUE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  profiler->sampleWriteHookForTest = nullptr;
  profiler->sampleWriteHookArgForTest = nullptr;
  EXPECT_EQ(1, observed.first_writes) << "committed epoch must not be replayed";
  EXPECT_EQ(2, observed.second_writes);
  auto* block = profiler->blockTracker()->slotForId(request.slot_id);
  EXPECT_EQ(0ULL, block->unowned_blocked_pending_weight.load());
  EXPECT_EQ(0ULL, block->unowned_blocked_call_trace_id.load());
}
