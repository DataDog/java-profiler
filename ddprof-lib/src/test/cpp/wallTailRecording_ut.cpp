/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "profiler.h"
#include "recordingWriteFailureFixture.h"
#include "tsc.h"
#include <memory>
#include <future>
#include <array>
#include <chrono>
#include <thread>
#include <tuple>



class RecordingTestAccessor {
public:
  // Match post-start hot writes: real flush failures retain bytes instead of throwing.
  static void activateHotWrites(Recording* recording) { recording->_cold_io = false; }
  static u32 threadTableOverflow(const Recording* recording) {
    return recording->_thread_table_overflow.load(std::memory_order_acquire);
  }
};

class FlightRecorderTestAccessor {
  FlightRecorder* _recorder;

public:
  static Recording* exchangeRecording(FlightRecorder& recorder, Recording* recording) {
    Recording* previous = recorder._rec;
    recorder._rec = recording;
    return previous;
  }
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
  static void flushUnownedTailsAtStop(Profiler& profiler) { profiler.flushUnownedTailsAtStop(); }
  static FlightRecorder& recorder(Profiler& profiler) { return profiler._jfr; }
  static u32 stripe(Profiler& profiler, int tid) { return profiler.getLockIndex(tid); }
  static FlightRecorder* recorder(Profiler* profiler) { return &profiler->_jfr; }
  static u32 stripe(Profiler* profiler, int tid) { return profiler->getLockIndex(tid); }
  static void prepareStop(Profiler* profiler, Engine* cpu, Engine* wall, Engine* alloc) {
    profiler->_cpu_engine = cpu;
    profiler->_wall_engine = wall;
    profiler->_alloc_engine = alloc;
    profiler->_activated_mask = EM_CPU | EM_WALL | EM_ALLOC;
    profiler->_intern_open.store(true, std::memory_order_release);
    profiler->_state.store(RUNNING, std::memory_order_release);
  }
  static State state(Profiler* profiler) { return profiler->state(); }
};

namespace {
class ScopedTailRecording {
  RecordingWriteFailureFixture _output;
  std::unique_ptr<Recording> _recording;
  FlightRecorder& _recorder;
  Recording* _previous;

public:
  explicit ScopedTailRecording(FlightRecorder& recorder)
      : _recording(std::make_unique<Recording>(_output.fd())), _recorder(recorder),
        _previous(FlightRecorderTestAccessor::exchangeRecording(recorder, _recording.get())) {}
  ~ScopedTailRecording() {
    FlightRecorderTestAccessor::exchangeRecording(_recorder, _previous);
  }
  bool valid() const { return _output.valid(); }
  RecordingBuffer* buffer(u32 stripe) { return _recording->buffer(stripe); }
  ScopedTailRecording(const ScopedTailRecording&) = delete;
  ScopedTailRecording& operator=(const ScopedTailRecording&) = delete;
};
} // namespace

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
    request.context.spanId = 22;
    request.context.rootSpanId = 222;
    request.context.setTag(0, 22);
    ASGCT_CallFrame frame{};
    frame.method_id = reinterpret_cast<jmethodID>(0x1234);
    // The storage is allocated only for a recording.
    ASSERT_TRUE(profiler->callTraceStorageForTest()->acquire());
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

  void expectOriginRetained(u64 pending_weight = 1) {
    auto* block = profiler->blockTracker()->slotForId(request.slot_id);
    EXPECT_EQ(origin, block->unowned_blocked_call_trace_id.load());
    EXPECT_EQ(pending_weight, block->unowned_blocked_pending_weight.load());
    EXPECT_EQ(OSThreadState::SLEEPING, block->unowned_blocked_state.load());
    Context context{};
    u64 publication = 0;
    ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(request.slot_id, context, publication));
    EXPECT_EQ(111ULL, context.spanId);
    EXPECT_EQ(222ULL, context.rootSpanId);
    for (int i = 0; i < DD_TAGS_CAPACITY; ++i) EXPECT_EQ(11U + i, context.getTag(i));
  }
};

TEST_F(WallTailRecordingTest, ThreadTableOverflowRetainsTailUntilARepresentableChunk) {
  FlightRecorder& recorder = ProfilerTestAccessor::recorder(*profiler);
  {
    ScopedTailRecording output(recorder);
    ASSERT_TRUE(output.valid());
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
    ASSERT_TRUE(output.valid());
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

class QuarantinedWallTailStopTest : public WallTailRecordingTest,
                                    public ::testing::WithParamInterface<std::tuple<bool, bool, bool>> {};

TEST_P(QuarantinedWallTailStopTest, QuarantinedStopShutsDownEnginesRetainsCustodyAndRejectsRestart) {
  class StopObserver : public Engine {
  public:
    unsigned stops = 0;
    bool enabled = true;
    void enableEvents(bool value) override { enabled = value; }
    void stop() override { ++stops; }
  } cpu, wall, alloc;
  const bool quarantine_before_stop = std::get<0>(GetParam());
  const bool pending_tail = std::get<1>(GetParam());
  const bool pending_capacity = std::get<2>(GetParam());
  VMTestAccessor vm;
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  auto* recorder = ProfilerTestAccessor::recorder(profiler.get());
  FlightRecorderTestAccessor active(recorder, recording.get());
  RecordingBuffer* buffer = recording->buffer(ProfilerTestAccessor::stripe(profiler.get(), request.tid));
  const u64 second_epoch = request.sampling_epoch_start + 100;
  if (pending_tail) {
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(
        request.slot_id, request.sampling_epoch_start));
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, second_epoch));
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(request.slot_id, second_epoch));
  } else {
    ASSERT_TRUE(profiler->recordUnownedBlockedTail(request.tid, request.slot_id));
  }
  u32 overflow_stripe = (ProfilerTestAccessor::stripe(profiler.get(), request.tid) + 1) % CONCURRENCY_LEVEL;
  if (pending_capacity) {
    TaskBlockEvent block{};
    block._start = 1;
    block._end = 2;
    for (int tid = 1; tid <= ThreadIdTable::capacity(); ++tid) {
      ASSERT_TRUE(recorder->recordTaskBlock(overflow_stripe, tid, &block));
    }
    ExecutionEvent event;
    event._thread_state = OSThreadState::SLEEPING;
    ASSERT_FALSE(recorder->recordWallSample(
        overflow_stripe, ThreadIdTable::capacity() + 1, origin, &event, request.context));
    ASSERT_TRUE(recording->outputGood());
  }
  const u32 expected_overflow = pending_capacity ? 1U << overflow_stripe : 0;
  ASSERT_EQ(expected_overflow, RecordingTestAccessor::threadTableOverflow(recording.get()));
  buffer->skip(JFR_EVENT_FLUSH_THRESHOLD - 1 - buffer->offset());
  std::array<StringDictionary*, 3> dictionaries{{
      profiler->classMap(), profiler->stringLabelMap(), profiler->contextValueMap()}};
  std::array<u32, 3> dictionary_ids{};
  std::array<u64, 3> dictionary_generations{};
  constexpr char retained_value[] = "RetainedTailValue";
  for (size_t i = 0; i < dictionaries.size(); ++i) {
    dictionary_ids[i] = dictionaries[i]->lookup(retained_value, sizeof(retained_value) - 1);
    ASSERT_NE(0U, dictionary_ids[i]);
    dictionary_generations[i] = dictionaries[i]->generation();
  }
  ASSERT_TRUE(output.failWrites());
  if (quarantine_before_stop) {
    ExecutionEvent event;
    event._thread_state = OSThreadState::SLEEPING;
    ASSERT_FALSE(recorder->recordWallSample(
        ProfilerTestAccessor::stripe(profiler.get(), request.tid), request.tid,
        origin, &event, request.context));
    ASSERT_FALSE(recording->outputGood());
  } else {
    ASSERT_TRUE(recording->outputGood());
  }
  const int bytes_before_stop = buffer->offset();
  ProfilerTestAccessor::prepareStop(profiler.get(), &cpu, &wall, &alloc);

  Error error = profiler->stop();
  ASSERT_TRUE(error);
  EXPECT_STREQ("Incomplete recording output retained; restart refused", error.message());
  EXPECT_TRUE(recorder->outputQuarantined());
  EXPECT_EQ(expected_overflow, RecordingTestAccessor::threadTableOverflow(recording.get()));
  EXPECT_EQ(ERROR, ProfilerTestAccessor::state(profiler.get()));
  EXPECT_FALSE(profiler->internOpen()) << "retained dictionaries must not admit late interning";
  EXPECT_EQ(1U, cpu.stops);
  EXPECT_EQ(1U, wall.stops);
  EXPECT_EQ(1U, alloc.stops);
  EXPECT_FALSE(cpu.enabled);
  EXPECT_FALSE(wall.enabled);
  EXPECT_FALSE(profiler->taskBlockEnabled());
  EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
  EXPECT_EQ(0ULL, profiler->threadFilter()->recordingEpoch());
  EXPECT_TRUE(recorder->active());
  ASSERT_GE(buffer->offset(), JFR_EVENT_FLUSH_THRESHOLD);
  const int retained_bytes = buffer->offset();
  if (quarantine_before_stop) EXPECT_EQ(bytes_before_stop, retained_bytes);
  else EXPECT_GT(retained_bytes, bytes_before_stop);
  WallClockBlockTracker::WeightSegment segments[WallClockBlockTracker::kMaxWeightSegments];
  if (pending_tail) {
    expectOriginRetained(4);
    ASSERT_EQ(2u, profiler->blockTracker()->copyUnownedWeightSegments(request.slot_id, segments));
    EXPECT_EQ(request.sampling_epoch_start, segments[0].epoch_start);
    EXPECT_EQ(2ULL, segments[0].weight);
    EXPECT_EQ(second_epoch, segments[1].epoch_start);
    EXPECT_EQ(2ULL, segments[1].weight);
  } else {
    EXPECT_EQ(0u, profiler->blockTracker()->copyUnownedWeightSegments(request.slot_id, segments));
  }
  CallTraceIdSet roots;
  profiler->blockTracker()->collectLiveTraceIds(roots);
  EXPECT_EQ(pending_tail ? 1U : 0U, roots.count(origin));
  for (size_t i = 0; i < dictionaries.size(); ++i) {
    EXPECT_EQ(dictionary_ids[i],
              dictionaries[i]->standby()->lookup(retained_value, sizeof(retained_value) - 1));
  }

  Arguments args;
  for (bool reset : {false, true}) {
    Error restart = profiler->start(args, reset);
    ASSERT_TRUE(restart);
    EXPECT_STREQ("Profiler encountered fatal error", restart.message());
    EXPECT_EQ(ERROR, ProfilerTestAccessor::state(profiler.get()));
    for (size_t i = 0; i < dictionaries.size(); ++i) {
      EXPECT_EQ(dictionary_generations[i], dictionaries[i]->generation());
    }
    if (pending_tail) expectOriginRetained(4);
  }
  EXPECT_TRUE(profiler->stop());
  EXPECT_EQ(1U, cpu.stops);
  EXPECT_EQ(1U, wall.stops);
  EXPECT_EQ(1U, alloc.stops);
  EXPECT_EQ(retained_bytes, buffer->offset());
}

INSTANTIATE_TEST_SUITE_P(
    OutputFailureTiming, QuarantinedWallTailStopTest,
    ::testing::Values(std::make_tuple(true, true, false), std::make_tuple(false, true, false),
                      std::make_tuple(true, false, false), std::make_tuple(true, true, true),
                      std::make_tuple(false, true, true)),
    [](const ::testing::TestParamInfo<std::tuple<bool, bool, bool>>& info) {
      return std::string(std::get<0>(info.param) ? "BeforeStop" : "DuringTailFlush") +
             (std::get<1>(info.param) ? "PendingTail" : "NoTail") +
             (std::get<2>(info.param) ? "FullThreadTable" : "");
    });

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

TEST_F(WallTailRecordingTest, StopCapacityRecoveryBudgetCountsUnwrittenTailAsDropped) {
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
  const auto dropped = Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP);
  ProfilerTestAccessor::flushUnownedTailsAtStop(*profiler);
  EXPECT_EQ(max_retries + 1, saturation.calls);
  EXPECT_EQ(dropped + 1, Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP));
  EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(request.slot_id)
                     ->unowned_blocked_pending_weight.load());
  captureWrites();
  EXPECT_TRUE(profiler->threadFilter()->flushUnownedTails());
  EXPECT_TRUE(writes.empty()) << "a tail counted as dropped must not be written later";
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
