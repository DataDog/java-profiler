/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstring>
#include <functional>
#include <mutex>
#include <thread>
#include <unistd.h>
#include <map>
#include <stdexcept>
#include <vector>
#include "codeCache.h"
#include "engine.h"
#include "flightRecorder.h"
#include "profiler.h"
#include "tsc.h"
#include "wallClockCounters.h"
#include "wallClock.h"

class VMTestAccessor {
public:
  static jvmtiEnv*& jvmti() { return VM::_jvmti; }
  static JavaVM*& vm() { return VM::_vm; }
  static CodeCache*& libjvm() { return VM::_libjvm; }
};

class ProfilerTestAccessor {
public:
  static Engine*& cpu() { return Profiler::instance()->_cpu_engine; }
  static Engine*& wall() { return Profiler::instance()->_wall_engine; }
  static Recording*& recording() { return Profiler::instance()->_jfr._rec; }
  static State exchangeState(State state) { return Profiler::instance()->_state.exchange(state); }
  static u32 lockIndex(int tid) { return Profiler::instance()->getLockIndex(tid); }
  static SpinLock& stripeLockAt(u32 index) { return Profiler::instance()->_locks[index]; }
  static SpinLock& stripeLock(int tid) { return stripeLockAt(lockIndex(tid)); }
  static bool recordTaskBlock(u32 stripe, int tid, TaskBlockEvent* event) {
    return Profiler::instance()->_jfr.recordTaskBlock(stripe, tid, event);
  }
  static SpinLock& recLock() { return Profiler::instance()->_jfr._rec_lock; }
};

class RecordingTestAccessor {
public:
  static constexpr size_t kPruneFloor = Recording::kMinWallEpochPruneThreshold;
  static size_t epochCount(const Recording& recording) { return recording._wall_epochs.size(); }
  static bool hasEpoch(const Recording& recording, u64 start) { return recording._wall_epochs.count(start) != 0; }
};

// Recording needs VM services even when serializing native-only events.
// These mocks expose no Java classes; real JVM attribution is tested in Java.
class WallEpochRecordingTest : public ::testing::TestWithParam<bool> {
protected:
  jvmtiInterface_1_ jvmti_functions{};
  _jvmtiEnv jvmti{&jvmti_functions};
  JNIInvokeInterface_ vm_functions{};
  JavaVM_ vm{&vm_functions};
  CodeCache libjvm{"wall-epoch-test"};
  Engine engine;
  jvmtiEnv* saved_jvmti;
  JavaVM* saved_vm;
  CodeCache* saved_libjvm;
  Engine* saved_cpu;
  Engine* saved_wall;
  Profiler* profiler = Profiler::instance();
  ThreadFilter::SlotID slot = -1;
  WallSampleRequest request;
  Recording* target = nullptr;
  u64 rejected_epoch = 0;

  void SetUp() override {
    saved_jvmti = VMTestAccessor::jvmti();
    saved_vm = VMTestAccessor::vm();
    saved_libjvm = VMTestAccessor::libjvm();
    saved_cpu = ProfilerTestAccessor::cpu();
    saved_wall = ProfilerTestAccessor::wall();
    jvmti_functions.GetAvailableProcessors = +[](jvmtiEnv*, jint* count) { *count = 1; return JVMTI_ERROR_NONE; };
    jvmti_functions.GetLoadedClasses = +[](jvmtiEnv*, jint* count, jclass** classes) {
      *count = 0; *classes = nullptr; return JVMTI_ERROR_NONE;
    };
    jvmti_functions.Deallocate = +[](jvmtiEnv*, unsigned char* memory) { free(memory); return JVMTI_ERROR_NONE; };
    jvmti_functions.GetAllThreads = +[](jvmtiEnv*, jint* count, jthread** threads) {
      *count = 0; *threads = nullptr; return JVMTI_ERROR_NONE;
    };
    vm_functions.GetEnv = +[](JavaVM*, void** env, jint) {
      static JNIEnv_ jni{};
      *env = &jni; return JNI_OK;
    };
    VMTestAccessor::jvmti() = &jvmti;
    VMTestAccessor::vm() = &vm;
    VMTestAccessor::libjvm() = &libjvm;
    ProfilerTestAccessor::cpu() = &engine;
    ProfilerTestAccessor::wall() = &engine;
    JfrMetadata::reset();
    JfrMetadata::initialize({});
    profiler->blockTracker()->setUnownedContextSnapshotsNeeded(true);
    profiler->threadFilter()->init("0");
    WallClockBlockTracker::EpochStarts leaked;
    profiler->blockTracker()->collectUnownedEpochStarts(leaked);
    ASSERT_TRUE(leaked.empty()) << "A previous test left unowned tails pending";
    slot = profiler->threadFilter()->registerThread(OS::threadId());
    ASSERT_GE(slot, 0);
    Context context{};
    ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
        slot, CallTraceStorage::DROPPED_TRACE_ID, OSThreadState::SLEEPING, context));
    request.slot_id = slot;
    request.tid = OS::threadId();
    request.trace_epoch = profiler->recordingEpoch();
    request.registry_epoch = profiler->threadFilter()->recordingEpoch();
    request.lifecycle_generation = profiler->threadFilter()->slotForId(slot)->lifecycleGeneration();
    request.context_captured = true;
    request.flush_tail = true;
    profiler->sampleWriteHookArgForTest = this;
    profiler->sampleWriteHookForTest = +[](u32, u64 trace, Event* raw, const Context* context, void* arg) {
      auto* self = static_cast<WallEpochRecordingTest*>(arg);
      auto* event = static_cast<ExecutionEvent*>(raw);
      if (event->_execution_mode != ExecutionMode::UNKNOWN) return true;
      if (event->_sample_ticks == self->rejected_epoch) return false;
      self->target->recordMethodSample(self->target->buffer(0), self->request.tid, trace, 0, event, context);
      return true;
    };
  }

  void TearDown() override {
    profiler->sampleWriteHookForTest = nullptr;
    profiler->sampleWriteHookArgForTest = nullptr;
    if (slot >= 0) profiler->threadFilter()->unregisterThread(slot, request.tid);
    // The test's Recording ends without stop(): drop unwritten tails as stop() does,
    // or retired slots replay them into the next test's Recording.
    profiler->blockTracker()->resetUnownedBlockedTails();
    profiler->threadFilter()->deactivateRecording();
    profiler->blockTracker()->setUnownedContextSnapshotsNeeded(false);
    JfrMetadata::reset();
    ProfilerTestAccessor::cpu() = saved_cpu;
    ProfilerTestAccessor::wall() = saved_wall;
    VMTestAccessor::libjvm() = saved_libjvm;
    VMTestAccessor::vm() = saved_vm;
    VMTestAccessor::jvmti() = saved_jvmti;
  }

  void checkOrdinaryAfterEpochRotation(bool fail_deferral);
  void checkStopRecoversFullStripe(int tid);

  WallSampleResult flushTail() {
    ExecutionEvent event;
    event._thread_state = OSThreadState::RUNNABLE;
    event._execution_mode = ExecutionMode::JAVA;
    return profiler->recordWallSample(nullptr, 1, CallTraceStorage::DROPPED_TRACE_ID, &event, request);
  }
};

class WallEpochFile {
  char path[64] = "/tmp/ddprof-wall-epochs-XXXXXX";
public:
  int fd = mkstemp(path);
  const char* filename() const { return path; }
  ~WallEpochFile() { if (fd >= 0) close(fd); unlink(path); }
  WallEpochFile() = default;
  WallEpochFile(const WallEpochFile&) = delete;
  WallEpochFile& operator=(const WallEpochFile&) = delete;
};

struct DecodedWallEpochs {
  std::map<u64, std::vector<u64>> epochs;
  std::map<u64, u64> weights;
  std::unordered_set<u64> sample_threads;
  std::unordered_set<u64> pool_threads;
};

// Decode event boundaries and scalar fields independently of Recording's encoders.
// Each file is parsed alone; no earlier dump or test-held scale supplies metadata.
static DecodedWallEpochs decodeWallEpochs(int fd) {
  const off_t size = lseek(fd, 0, SEEK_END);
  if (size < 68) throw std::runtime_error("Missing standalone JFR header");
  std::vector<unsigned char> bytes(size);
  if (pread(fd, bytes.data(), bytes.size(), 0) != size) throw std::runtime_error("Cannot read JFR");
  auto fixed64 = [&](size_t offset) {
    u64 value = 0;
    for (size_t i = 0; i < 8; ++i) value = (value << 8) | bytes.at(offset + i);
    return value;
  };
  auto var64 = [&](size_t& offset) {
    u64 value = 0;
    for (unsigned shift = 0; shift < 64; shift += 7) {
      unsigned char byte = bytes.at(offset++);
      value |= static_cast<u64>(byte & 0x7f) << shift;
      if ((byte & 0x80) == 0) return value;
    }
    throw std::runtime_error("Invalid JFR varint");
  };
  if (fixed64(8) != static_cast<u64>(size)) throw std::runtime_error("Unsealed JFR");
  DecodedWallEpochs decoded;
  const u64 cpool = fixed64(16);
  for (size_t offset = 68; offset < cpool;) {
    const size_t start = offset;
    const u64 length = var64(offset);
    if (length == 0 || length > cpool - start) throw std::runtime_error("Invalid event boundary");
    const u64 type = var64(offset);
    if (type == T_WALLCLOCK_SAMPLE_EPOCH) {
      u64 epoch = var64(offset);
      std::vector<u64> fields;
      for (int i = 0; i < 7; ++i) fields.push_back(var64(offset));
      if (!decoded.epochs.emplace(epoch, fields).second) throw std::runtime_error("Duplicate epoch metadata");
    } else if (type == T_METHOD_SAMPLE) {
      const u64 epoch = var64(offset);
      decoded.sample_threads.insert(var64(offset));
      var64(offset); // stack
      offset += 2; // state and mode are bytes
      decoded.weights[epoch] += var64(offset);
    }
    if (offset > start + length) throw std::runtime_error("Event fields exceed event size");
    offset = start + length;
  }
  size_t offset = cpool;
  var64(offset); // checkpoint size
  if (var64(offset) != T_CPOOL) throw std::runtime_error("Missing checkpoint");
  for (int i = 0; i < 4; ++i) var64(offset); // time, duration, delta, flush
  if (var64(offset) < 5) throw std::runtime_error("Missing fixed constant pools");
  auto skip_string = [&] {
    unsigned char encoding = bytes.at(offset++);
    if (encoding == 0) return;
    if (encoding != 3) throw std::runtime_error("Expected UTF-8 constant pool string");
    const u64 length = var64(offset);
    if (length > bytes.size() - offset) throw std::runtime_error("Invalid constant pool string");
    offset += length;
  };
  for (u64 type : {T_FRAME_TYPE, T_THREAD_STATE, T_EXECUTION_MODE, T_LOG_LEVEL}) {
    if (var64(offset) != type) throw std::runtime_error("Missing fixed constant pool");
    const u64 count = var64(offset);
    for (u64 i = 0; i < count; ++i) {
      var64(offset);
      skip_string();
    }
  }
  if (var64(offset) != T_THREAD) throw std::runtime_error("Missing thread pool");
  const u64 thread_count = var64(offset);
  for (u64 i = 0; i < thread_count; ++i) {
    const u64 tid = var64(offset);
    if (!decoded.pool_threads.insert(tid).second) throw std::runtime_error("Duplicate thread pool entry");
    skip_string();
    if (var64(offset) != tid) throw std::runtime_error("Thread pool OS ID mismatch");
    skip_string();
    var64(offset); // Java thread ID
  }
  return decoded;
}

TEST_P(WallEpochRecordingTest, ClosedOriginsFollowPendingSegmentsAcrossDumpsAndPartialWrites) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  const u64 first = TSC::ticks();
  const u64 second = first + 1000;
  const u32 pools[] = {GetParam() ? 160U : 16U, GetParam() ? 16U : 160U};
  for (int i = 0; i < 2; ++i) {
    const u64 start = i == 0 ? first : second;
    for (int weight = 0; weight < (i == 0 ? 3 : 5); ++weight) {
      ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, start));
    }
    WallClockEpochEvent epoch(start);
    epoch.endEpoch(23 + i);
    epoch.updateNumSamplableThreads(pools[i]);
    epoch.updateNumSuccessfulSamples(8);
    epoch.updateNumFailedSamples(1);
    epoch.updateNumExitedThreads(2);
    epoch.updateNumPermissionDenied(3);
    epoch.addNumSuppressedOwnedBlock(7 + i);
    recording.recordWallClockEpoch(recording.buffer(0), &epoch);
  }
  WallClockEpochEvent unused(second + 1000);
  recording.recordWallClockEpoch(recording.buffer(0), &unused);
  for (int dump = 0; dump < 2; ++dump) {
    WallEpochFile snapshot;
    ASSERT_GE(snapshot.fd, 0);
    recording.switchChunk(snapshot.fd);
    EXPECT_TRUE(decodeWallEpochs(snapshot.fd).weights.empty());
    EXPECT_EQ(2U, RecordingTestAccessor::epochCount(recording));
  }
  rejected_epoch = second;
  EXPECT_FALSE(flushTail().tail_recorded);
  EXPECT_EQ(5ULL, profiler->blockTracker()->slotForId(slot)->unowned_blocked_pending_weight.load());
  WallEpochFile partial;
  ASSERT_GE(partial.fd, 0);
  recording.switchChunk(partial.fd);
  auto partial_events = decodeWallEpochs(partial.fd);
  ASSERT_EQ(1U, partial_events.weights.size());
  EXPECT_EQ(3ULL, partial_events.weights.at(first));
  EXPECT_EQ(1U, RecordingTestAccessor::epochCount(recording));
  rejected_epoch = 0;
  EXPECT_TRUE(flushTail().tail_recorded);
  EXPECT_FALSE(flushTail().tail_recorded) << "Committed segments must not replay";
  WallEpochFile final;
  ASSERT_GE(final.fd, 0);
  recording.switchChunk(final.fd);
  auto final_events = decodeWallEpochs(final.fd);
  ASSERT_EQ(1U, final_events.weights.size());
  EXPECT_EQ(5ULL, final_events.weights.at(second));
  EXPECT_EQ(0U, final_events.epochs.count(first));
  EXPECT_EQ(0U, RecordingTestAccessor::epochCount(recording));
  double scaled = 0;
  for (const auto* events : {&partial_events, &final_events}) {
    for (const auto& sample : events->weights) {
      ASSERT_EQ(1U, events->epochs.count(sample.first)) << "Missing originating epoch in standalone JFR";
      const auto& fields = events->epochs.at(sample.first);
      const int index = sample.first == first ? 0 : 1;
      EXPECT_EQ((std::vector<u64>{static_cast<u64>(23 + index), pools[index], 8, 1, 2, 3,
                                  static_cast<u64>(7 + index)}), fields);
      scaled += sample.second * static_cast<double>(fields[1]) / fields[2];
    }
  }
  EXPECT_DOUBLE_EQ(3.0 * pools[0] / 8 + 5.0 * pools[1] / 8, scaled);
}

void WallEpochRecordingTest::checkOrdinaryAfterEpochRotation(bool fail_deferral) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  struct SamplingEpochRestore {
    u64 saved = WallClockCounters::samplingEpochStart();
    ~SamplingEpochRestore() { WallClockCounters::beginSamplingEpoch(saved); }
  } restore;
  const u64 first = TSC::ticks();
  WallClockCounters::beginSamplingEpoch(first);
  request.sampling_epoch_start = first;
  request.unowned_sample = true;
  request.flush_tail = false;
  ASSERT_TRUE(profiler->blockTracker()->readUnownedContext(
      slot, request.context, request.context_publication));
  ASSERT_EQ(0ULL, profiler->blockTracker()->slotForId(slot)->unowned_blocked_pending_weight.load());
  if (fail_deferral) {
    auto locks = profiler->recordingLocksForTest();
    ASSERT_FALSE(profiler->deferUnownedWallSample(request));
  }
  ASSERT_EQ(first, request.sampling_epoch_start);
  ASSERT_FALSE(request.force_unowned_ordinary);
  const u64 second = TSC::ticks();
  ASSERT_GT(second, first);
  {
    auto locks = profiler->recordingLocksForTest();
    WallClockEpochEvent epoch(first);
    epoch.endEpoch(11);
    recording.recordWallClockEpoch(recording.buffer(0), &epoch);
    WallClockCounters::beginSamplingEpoch(second);
    WallEpochFile snapshot;
    ASSERT_GE(snapshot.fd, 0);
    recording.switchChunk(snapshot.fd);
    ASSERT_EQ(1U, decodeWallEpochs(snapshot.fd).epochs.count(first));
    ASSERT_EQ(0U, RecordingTestAccessor::epochCount(recording));
  }
  profiler->sampleWriteHookForTest = +[](u32, u64 trace, Event* raw, const Context* context, void* arg) {
    auto* self = static_cast<WallEpochRecordingTest*>(arg);
    self->target->recordMethodSample(self->target->buffer(0), self->request.tid, trace, 0,
                                    static_cast<ExecutionEvent*>(raw), context);
    return true;
  };
  EXPECT_TRUE(flushTail().ordinary_recorded);
  WallClockEpochEvent epoch(second);
  epoch.endEpoch(17);
  recording.recordWallClockEpoch(recording.buffer(0), &epoch);
  WallEpochFile final;
  ASSERT_GE(final.fd, 0);
  recording.switchChunk(final.fd);
  const auto events = decodeWallEpochs(final.fd);
  ASSERT_EQ(1U, events.weights.size());
  EXPECT_EQ(0U, events.weights.count(first)) << "Pruned epoch must not be resurrected by an ordinary write";
  ASSERT_EQ(1U, events.epochs.count(second));
  for (const auto& sample : events.weights) {
    EXPECT_EQ(1ULL, sample.second);
    EXPECT_GT(sample.first, second) << "A weight-1 observation must keep its ordinary serialization timestamp";
  }
}

TEST_P(WallEpochRecordingTest, FailedDeferralCannotWritePrunedEpochAfterDump) {
  checkOrdinaryAfterEpochRotation(true);
}

TEST_P(WallEpochRecordingTest, ZeroPendingPeriodicRequestKeepsOrdinaryTimestampAfterDump) {
  checkOrdinaryAfterEpochRotation(false);
}

struct RecorderRestore {
  Recording* saved_recording = ProfilerTestAccessor::recording();
  u64 saved_epoch = WallClockCounters::samplingEpochStart();
  ~RecorderRestore() {
    WallClockCounters::beginSamplingEpoch(saved_epoch);
    ProfilerTestAccessor::recording() = saved_recording;
  }
};

// Closes epochs through the timer's Profiler path; returns the next epoch start.
static u64 closeEpochs(Profiler* profiler, int tid, u64 start, u64 count) {
  for (u64 i = 0; i < count; ++i, ++start) {
    WallClockEpochEvent epoch(start);
    epoch.endEpoch(1);
    profiler->recordWallClockEpoch(tid, &epoch, start + 1, false);
  }
  return start;
}

TEST_P(WallEpochRecordingTest, ClosedEpochsWithoutRetainedSegmentsDoNotAccumulate) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  RecorderRestore restore;
  ProfilerTestAccessor::recording() = &recording;
  const u64 retained = TSC::ticks();
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, retained));
  constexpr u64 kClosedEpochs = 3 * RecordingTestAccessor::kPruneFloor;
  const u64 next = closeEpochs(profiler, request.tid, retained, kClosedEpochs);
  EXPECT_EQ(next, WallClockCounters::samplingEpochStart());
  EXPECT_LT(RecordingTestAccessor::epochCount(recording), RecordingTestAccessor::kPruneFloor)
      << "Closed epochs without retained segments must be pruned between dumps";
  EXPECT_TRUE(RecordingTestAccessor::hasEpoch(recording, retained))
      << "An epoch referenced by a retained segment must survive close-time pruning";
}

// A deferral on another stripe read the closing epoch before its successor was
// published. Pruning must wait for its commit instead of dropping the epoch first.
TEST_P(WallEpochRecordingTest, ClosePruneWaitsForInFlightDeferral) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  RecorderRestore restore;
  ProfilerTestAccessor::recording() = &recording;
  const u64 first = TSC::ticks();
  const u64 closing = closeEpochs(profiler, request.tid, first,
                                  RecordingTestAccessor::kPruneFloor - 1);
  ASSERT_EQ(RecordingTestAccessor::kPruneFloor - 1, RecordingTestAccessor::epochCount(recording));
  const u32 timer_stripe = ProfilerTestAccessor::lockIndex(request.tid);
  SpinLock& deferral_stripe = ProfilerTestAccessor::stripeLockAt((timer_stripe + 1) % CONCURRENCY_LEVEL);
  std::atomic<bool> holding{false};
  std::atomic<bool> closed{false};
  std::thread deferral([&] {
    ExclusiveLockGuard stripe(&deferral_stripe);
    const u64 read_epoch = WallClockCounters::samplingEpochStart();
    holding.store(true, std::memory_order_release);
    // The close publishes the successor without this stripe; only the prune waits.
    while (WallClockCounters::samplingEpochStart() == read_epoch) std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_FALSE(closed.load(std::memory_order_acquire)) << "Prune finished while a deferral held a stripe";
    EXPECT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, read_epoch));
  });
  while (!holding.load(std::memory_order_acquire)) std::this_thread::yield();
  ASSERT_EQ(closing, WallClockCounters::samplingEpochStart());
  closeEpochs(profiler, request.tid, closing, 1);
  closed.store(true, std::memory_order_release);
  deferral.join();
  EXPECT_LT(RecordingTestAccessor::epochCount(recording), RecordingTestAccessor::kPruneFloor)
      << "The threshold-reaching close must prune";
  EXPECT_TRUE(RecordingTestAccessor::hasEpoch(recording, closing))
      << "A closed epoch read by an in-flight deferral must survive pruning";
}

class WallEpochTimer : public BaseWallClock {
public:
  std::atomic<int> passes{0};
  const char* name() override { return "Wall epoch custody test"; }
  bool awaitPasses(int count) {
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
    while (passes.load(std::memory_order_acquire) < count) {
      if (std::chrono::steady_clock::now() >= deadline) return false;
      std::this_thread::yield();
    }
    return true;
  }
private:
  void timerLoop() override {
    auto collect = [](std::vector<ThreadEntry>& entries) {
      for (int tid = 1; tid <= 32; ++tid) entries.push_back({tid, nullptr, -1, 0, 0});
    };
    auto sample = [](ThreadEntry, int&, int&, int&, int&, bool) {
      return WallClockCandidateOutcome::SIGNAL_SENT;
    };
    auto clean = [&] { passes.fetch_add(1, std::memory_order_release); };
    timerLoopCommon<ThreadEntry>(collect, sample, clean, 16, _interval);
  }
};

class ScopedWallEpochTimer {
  Recording* saved_recording = ProfilerTestAccessor::recording();
  State saved_state = ProfilerTestAccessor::exchangeState(RUNNING);
  using SignalHandler = void (*)(int);
  SignalHandler saved_handler = std::signal(WAKEUP_SIGNAL, +[](int) {});
  bool saved_enabled = BaseWallClock::eventsEnabled();
  u64 saved_epoch = WallClockCounters::samplingEpochStart();
public:
  WallEpochTimer timer;
  explicit ScopedWallEpochTimer(Recording* recording) {
    ProfilerTestAccessor::recording() = recording;
    timer.enableEvents(true);
  }
  ~ScopedWallEpochTimer() {
    timer.stop();
    timer.enableEvents(saved_enabled);
    WallClockCounters::beginSamplingEpoch(saved_epoch);
    ProfilerTestAccessor::recording() = saved_recording;
    ProfilerTestAccessor::exchangeState(saved_state);
    std::signal(WAKEUP_SIGNAL, saved_handler);
  }
};

TEST_P(WallEpochRecordingTest, OpenEpochSurvivesDumpThenRetirementBeforeNormalClosure) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  ScopedWallEpochTimer running(&recording);
  args._wall = 10000000;
  ASSERT_FALSE(running.timer.start(args));
  ASSERT_TRUE(running.timer.awaitPasses(2));
  u64 origin;
  {
    auto epoch_lock = BaseWallClock::samplingEpochLock();
    origin = WallClockCounters::samplingEpochStart();
    ASSERT_FALSE(RecordingTestAccessor::hasEpoch(recording, origin)) << "Origin must still be open";
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, origin));
  }
  WallEpochFile first;
  ASSERT_GE(first.fd, 0);
  ASSERT_FALSE(profiler->dump(first.filename(), std::strlen(first.filename())));
  {
    auto epoch_lock = BaseWallClock::samplingEpochLock();
    ASSERT_TRUE(RecordingTestAccessor::hasEpoch(recording, origin));
    request.trace_epoch = profiler->recordingEpoch();
    ASSERT_TRUE(flushTail().tail_recorded);
    profiler->threadFilter()->unregisterThread(slot, request.tid);
    slot = -1;
  }
  if (GetParam()) running.timer.stop();
  WallEpochFile final;
  ASSERT_GE(final.fd, 0);
  ASSERT_FALSE(profiler->dump(final.filename(), std::strlen(final.filename())));
  const auto events = decodeWallEpochs(final.fd);
  for (const auto& weight : events.weights) {
    EXPECT_EQ(1U, events.epochs.count(weight.first)) << "Sample epoch lacks metadata in its file";
  }
  ASSERT_EQ(1U, events.weights.size());
  EXPECT_EQ(1ULL, events.weights.at(origin));
  ASSERT_EQ(1U, events.epochs.count(origin));
  const auto& fields = events.epochs.at(origin);
  EXPECT_EQ(32ULL, fields[1]);
  EXPECT_EQ(16ULL, fields[2]);
}

TEST_P(WallEpochRecordingTest, TimerExitClosesFinalWindowBeforeFinalSeal) {
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  Recording recording(recording_fd, args);
  target = &recording;
  ScopedWallEpochTimer running(&recording);
  args._wall = 10000000;
  ASSERT_FALSE(running.timer.start(args));
  ASSERT_TRUE(running.timer.awaitPasses(2));
  u64 origin;
  {
    auto epoch_lock = BaseWallClock::samplingEpochLock();
    origin = WallClockCounters::samplingEpochStart();
    ASSERT_FALSE(RecordingTestAccessor::hasEpoch(recording, origin));
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, origin));
    ASSERT_TRUE(flushTail().tail_recorded);
  }
  running.timer.stop();
  ASSERT_TRUE(RecordingTestAccessor::hasEpoch(recording, origin));
  WallEpochFile final;
  ASSERT_GE(final.fd, 0);
  recording.switchChunk(final.fd);
  const auto events = decodeWallEpochs(final.fd);
  ASSERT_EQ(1U, events.weights.size());
  EXPECT_EQ(1ULL, events.weights.at(origin));
  ASSERT_EQ(1U, events.epochs.count(origin));
  EXPECT_EQ(32ULL, events.epochs.at(origin)[1]);
  EXPECT_EQ(16ULL, events.epochs.at(origin)[2]);
}

void WallEpochRecordingTest::checkStopRecoversFullStripe(int tid) {
  if (tid != request.tid) {
    profiler->threadFilter()->unregisterThread(slot, request.tid);
    request.tid = tid;
    slot = profiler->threadFilter()->registerThread(tid);
    ASSERT_GE(slot, 0);
    Context context{};
    ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
        slot, CallTraceStorage::DROPPED_TRACE_ID, OSThreadState::SLEEPING, context));
  }
  WallEpochFile continuous;
  ASSERT_GE(continuous.fd, 0);
  Arguments args;
  args._jfr_options = JFR_SYNC_OPTS;
  const int recording_fd = dup(continuous.fd);
  ASSERT_GE(recording_fd, 0);
  const long long jfr_memory_before = NativeMem::live(NM_JFR_BUFFERS);
  struct StopRecording {
    Recording* previous = ProfilerTestAccessor::recording();
    State state = ProfilerTestAccessor::exchangeState(RUNNING);
    explicit StopRecording(Recording* recording) {
      NativeMem::record(NM_JFR_BUFFERS, sizeof(Recording));
      ProfilerTestAccessor::recording() = recording;
    }
    ~StopRecording() {
      if (ProfilerTestAccessor::recording() != nullptr) {
        delete ProfilerTestAccessor::recording();
        NativeMem::record(NM_JFR_BUFFERS, -static_cast<long long>(sizeof(Recording)));
      }
      ProfilerTestAccessor::recording() = previous;
      ProfilerTestAccessor::exchangeState(state);
    }
  } recording(new Recording(recording_fd, args));
  profiler->sampleWriteHookForTest = nullptr;
  const u32 stripe = ProfilerTestAccessor::lockIndex(request.tid);
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  std::vector<int> occupied_tids;
  for (int tid = 1; occupied_tids.size() < ThreadIdTable::capacity(); ++tid) {
    if (tid == request.tid) continue;
    ASSERT_TRUE(ProfilerTestAccessor::recordTaskBlock(stripe, tid, &event));
    occupied_tids.push_back(tid);
  }
  ASSERT_EQ(occupied_tids.end(), std::find(occupied_tids.begin(), occupied_tids.end(), request.tid));
  const u64 epoch_start = TSC::ticks();
  ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, epoch_start));
  struct TailOwners {
    ThreadFilter* registry;
    std::vector<std::pair<int, int>> slots;
    ~TailOwners() { for (auto entry : slots) registry->unregisterThread(entry.first, entry.second); }
  } tails{profiler->threadFilter(), {}};
  const int extra_tails = GetParam() ? 300 : 0;
  for (int tid = 100000; tails.slots.size() < static_cast<size_t>(extra_tails); ++tid) {
    if (tid == request.tid || ProfilerTestAccessor::lockIndex(tid) != stripe) continue;
    const int id = profiler->threadFilter()->registerThread(tid);
    ASSERT_GE(id, 0);
    tails.slots.emplace_back(id, tid);
    Context context{};
    ASSERT_TRUE(profiler->blockTracker()->publishUnownedTrace(
        id, CallTraceStorage::DROPPED_TRACE_ID, OSThreadState::SLEEPING, context));
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(id, epoch_start));
  }
  WallClockEpochEvent epoch(epoch_start);
  profiler->recordWallClockEpoch(request.tid, &epoch, epoch_start + 1);
  ASSERT_FALSE(profiler->threadFilter()->flushUnownedTails());
  ASSERT_EQ(1ULL, profiler->blockTracker()->slotForId(slot)->unowned_blocked_pending_weight.load());
  Error error = profiler->stop();
  ASSERT_FALSE(error) << error.message();
  EXPECT_FALSE(profiler->isRunning());
  EXPECT_EQ(nullptr, ProfilerTestAccessor::recording());
  EXPECT_EQ(jfr_memory_before, NativeMem::live(NM_JFR_BUFFERS));
  const auto decoded = decodeWallEpochs(continuous.fd);
  ASSERT_EQ(1U, decoded.weights.size());
  EXPECT_EQ(static_cast<u64>(1 + extra_tails), decoded.weights.at(epoch_start));
  EXPECT_EQ(static_cast<size_t>(1 + extra_tails), decoded.sample_threads.size());
  for (u64 tid : decoded.sample_threads) EXPECT_EQ(1U, decoded.pool_threads.count(tid));
  for (int tid : occupied_tids) EXPECT_EQ(1U, decoded.pool_threads.count(tid));
  EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(slot)->unowned_blocked_pending_weight.load());
  for (auto entry : tails.slots) {
    EXPECT_EQ(0ULL, profiler->blockTracker()->slotForId(entry.first)->unowned_blocked_pending_weight.load());
  }
  WallEpochFile next_continuous;
  WallEpochFile next_snapshot;
  ASSERT_GE(next_continuous.fd, 0);
  ASSERT_GE(next_snapshot.fd, 0);
  const int next_fd = dup(next_continuous.fd);
  ASSERT_GE(next_fd, 0);
  Recording next_recording(next_fd, args);
  next_recording.switchChunk(next_snapshot.fd);
  const auto next = decodeWallEpochs(next_snapshot.fd);
  EXPECT_TRUE(next.weights.empty());
  // A new recording still publishes its own native thread.
  for (int tid : occupied_tids) {
    if (tid != OS::threadId()) EXPECT_EQ(0U, next.pool_threads.count(tid));
  }
  for (auto entry : tails.slots) EXPECT_EQ(0U, next.pool_threads.count(entry.second));
}

TEST_P(WallEpochRecordingTest, StopRecoversFullStripeWithoutExplicitDump) {
  checkStopRecoversFullStripe(OS::threadId());
}

TEST_P(WallEpochRecordingTest, StopRecoversFullStripeForLowNativeTid) {
  checkStopRecoversFullStripe(1);
}

INSTANTIATE_TEST_SUITE_P(PopulationChanges, WallEpochRecordingTest, ::testing::Bool());

// Full stop() over a fresh recording that holds one deferred unowned tail.
class WallTailStopTest : public WallEpochRecordingTest {
protected:
  WallEpochFile file;
  u64 epoch_start = 0;
  long long dropped_before = 0;

  Error stopWithPendingTail(const std::function<void()>& before_stop = [] {}) {
    EXPECT_GE(file.fd, 0);
    Arguments args;
    args._jfr_options = JFR_SYNC_OPTS;
    const int recording_fd = dup(file.fd);
    EXPECT_GE(recording_fd, 0);
    struct StopRecording {
      Recording* previous = ProfilerTestAccessor::recording();
      State state = ProfilerTestAccessor::exchangeState(RUNNING);
      explicit StopRecording(Recording* recording) {
        NativeMem::record(NM_JFR_BUFFERS, sizeof(Recording));
        ProfilerTestAccessor::recording() = recording;
      }
      ~StopRecording() {
        if (ProfilerTestAccessor::recording() != nullptr) {
          delete ProfilerTestAccessor::recording();
          NativeMem::record(NM_JFR_BUFFERS, -static_cast<long long>(sizeof(Recording)));
        }
        ProfilerTestAccessor::recording() = previous;
        ProfilerTestAccessor::exchangeState(state);
      }
    } recording(new Recording(recording_fd, args));
    WallClockEpochEvent epoch(epoch_start);
    profiler->recordWallClockEpoch(request.tid, &epoch, epoch_start + 1);
    dropped_before = Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP);
    before_stop();
    Error error = profiler->stop();
    EXPECT_FALSE(profiler->isRunning());
    EXPECT_FALSE(profiler->taskBlockRotationActiveForTest());
    EXPECT_EQ(nullptr, ProfilerTestAccessor::recording()) << "JFR teardown must run";
    return error;
  }

  void SetUp() override {
    WallEpochRecordingTest::SetUp();
    profiler->sampleWriteHookForTest = nullptr;
    epoch_start = TSC::ticks();
    ASSERT_TRUE(profiler->blockTracker()->deferUnownedWeight(slot, epoch_start));
  }

  u64 pendingWeight() {
    return profiler->blockTracker()->slotForId(slot)->unowned_blocked_pending_weight.load();
  }
};

// Param: true models the wall timer closing an epoch, false a normal-thread stripe writer.
class WallTailStopContentionTest : public WallTailStopTest {};

TEST_P(WallTailStopContentionTest, StopWaitsOutContentionAndWritesTail) {
  std::atomic<bool> held{false};
  std::atomic<bool> released{false};
  std::atomic<bool> reached{false};
  std::thread holder;
  int backoffs = 0;
  profiler->stopTailBackoffHookArgForTest = &backoffs;
  profiler->stopTailBackoffHookForTest = +[](void* arg) { ++*static_cast<int*>(arg); };
  Error error = stopWithPendingTail([&] {
    holder = std::thread([&] {
      std::unique_lock<std::mutex> epoch_lock;
      if (GetParam()) epoch_lock = BaseWallClock::samplingEpochLock();
      SpinLock& lock = GetParam() ? ProfilerTestAccessor::recLock()
                                  : ProfilerTestAccessor::stripeLock(request.tid);
      lock.lock();
      held = true;
      // Hold until stop() has drained its writers and reached the tail flush.
      for (int i = 0; i < 5000 && !profiler->taskBlockRotationActiveForTest(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
      reached = profiler->taskBlockRotationActiveForTest();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      released = true;
      lock.unlock();
    });
    while (!held.load()) std::this_thread::yield();
  });
  const bool waited = released.load();
  holder.join();
  profiler->stopTailBackoffHookForTest = nullptr;
  ASSERT_FALSE(error) << error.message();
  EXPECT_TRUE(reached.load()) << "contention must overlap the stop-time tail flush";
  EXPECT_TRUE(waited) << "stop() must wait out the holder instead of dropping the tail";
  // A first flush attempt racing the holder would fail and back off.
  EXPECT_EQ(0, backoffs) << "stop() must not attempt the flush while the holder runs";
  EXPECT_EQ(0ULL, pendingWeight());
  EXPECT_EQ(dropped_before, Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP));
  const auto decoded = decodeWallEpochs(file.fd);
  ASSERT_EQ(1U, decoded.weights.count(epoch_start));
  EXPECT_EQ(1ULL, decoded.weights.at(epoch_start));
}

INSTANTIATE_TEST_SUITE_P(EpochCloseOrStripeWriter, WallTailStopContentionTest, ::testing::Bool());

// Param: true publishes retiring_tid during the first stop backoff, false never does.
class WallTailStopRetirementGapTest : public WallTailStopTest {};

TEST_P(WallTailStopRetirementGapTest, StopWritesOrCountsTailClaimedBeforeRetiringTidPublication) {
  auto* identity = profiler->threadFilter()->slotForId(slot);
  // Quiescent injection of retireThreadByTid's window between its tid claim and retiring_tid store.
  identity->tid.store(-1, std::memory_order_release);
  struct Retirement {
    decltype(identity) identity;
    int tid;
    bool publish;
    int backoffs = 0;
  } retirement{identity, request.tid, GetParam()};
  profiler->stopTailBackoffHookArgForTest = &retirement;
  profiler->stopTailBackoffHookForTest = +[](void* arg) {
    auto* state = static_cast<Retirement*>(arg);
    if (state->backoffs++ == 0 && state->publish) {
      state->identity->retiring_tid.store(state->tid, std::memory_order_release);
    }
  };
  Error error = stopWithPendingTail();
  profiler->stopTailBackoffHookForTest = nullptr;
  identity->retiring_tid.store(-1, std::memory_order_release);
  identity->tid.store(request.tid, std::memory_order_release);
  ASSERT_FALSE(error) << error.message();
  EXPECT_EQ(GetParam() ? 1 : 3, retirement.backoffs);
  EXPECT_EQ(0ULL, pendingWeight());
  EXPECT_EQ(dropped_before + (GetParam() ? 0 : 1), Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP));
  const auto decoded = decodeWallEpochs(file.fd);
  EXPECT_EQ(GetParam() ? 1U : 0U, decoded.weights.count(epoch_start));
}

INSTANTIATE_TEST_SUITE_P(RetiringTidPublication, WallTailStopRetirementGapTest, ::testing::Bool());

TEST_F(WallTailStopTest, PermanentWriteFailureCountsDroppedTailAndCompletesTeardown) {
  profiler->sampleWriteHookArgForTest = this;
  profiler->sampleWriteHookForTest = +[](u32, u64, Event*, const Context*, void*) { return false; };
  Error error = stopWithPendingTail();
  ASSERT_FALSE(error) << error.message();
  EXPECT_EQ(0ULL, pendingWeight());
  EXPECT_EQ(dropped_before + 1, Counters::getCounter(WC_UNOWNED_TAIL_DROPPED_AT_STOP));
}
