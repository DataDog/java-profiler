/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <unistd.h>
#include <map>
#include <stdexcept>
#include <vector>
#include "codeCache.h"
#include "engine.h"
#include "flightRecorder.h"
#include "profiler.h"
#include "tsc.h"

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
};

class RecordingTestAccessor {
public:
  static size_t epochCount(const Recording& recording) { return recording._wall_epochs.size(); }
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
    if (slot >= 0) profiler->threadFilter()->unregisterThread(slot, OS::threadId());
    profiler->threadFilter()->deactivateRecording();
    profiler->blockTracker()->setUnownedContextSnapshotsNeeded(false);
    JfrMetadata::reset();
    ProfilerTestAccessor::cpu() = saved_cpu;
    ProfilerTestAccessor::wall() = saved_wall;
    VMTestAccessor::libjvm() = saved_libjvm;
    VMTestAccessor::vm() = saved_vm;
    VMTestAccessor::jvmti() = saved_jvmti;
  }

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
  ~WallEpochFile() { if (fd >= 0) close(fd); unlink(path); }
  WallEpochFile() = default;
  WallEpochFile(const WallEpochFile&) = delete;
  WallEpochFile& operator=(const WallEpochFile&) = delete;
};

struct DecodedWallEpochs {
  std::map<u64, std::vector<u64>> epochs;
  std::map<u64, u64> weights;
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
      var64(offset); // thread
      var64(offset); // stack
      offset += 2; // state and mode are bytes
      decoded.weights[epoch] += var64(offset);
    }
    if (offset > start + length) throw std::runtime_error("Event fields exceed event size");
    offset = start + length;
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
    epoch.addNumSuppressedSampledRun(7 + i);
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

INSTANTIATE_TEST_SUITE_P(PopulationChanges, WallEpochRecordingTest, ::testing::Bool());
