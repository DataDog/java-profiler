/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "engine.h"
#include "event.h"
#include "flightRecorder.h"
#include "profiler.h"
#include "recordingWriteFailureFixture.h"
#include "wallClock.h"

#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
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
  // Match post-start hot writes: real flush failures retain bytes instead of throwing.
  static void activateHotWrites(Recording* recording) { recording->_cold_io = false; }

  // A failed append quarantines the output, as a failed hot write would.
  static void appendByte(Recording* recording) {
    RecordingBuffer* buffer = recording->buffer(0);
    buffer->put8(0);
    recording->flush(buffer);
  }

  static void collectThreads(Recording* recording, int stripe, std::unordered_set<int>& tids) {
    recording->_thread_ids[stripe][recording->_active_index.load()].collect(tids);
  }
};

class FlightRecorderTestAccessor {
  FlightRecorder* _recorder;

public:
  FlightRecorderTestAccessor(FlightRecorder* recorder, Recording* recording, int uncertain_fd = -1)
      : _recorder(recorder) {
    setRecording(recorder, recording);
    recorder->_uncertain_create_fd = uncertain_fd;
  }
  ~FlightRecorderTestAccessor() {
    setRecording(_recorder, nullptr);
    _recorder->_uncertain_create_fd = -1;
  }
  FlightRecorderTestAccessor(const FlightRecorderTestAccessor&) = delete;
  FlightRecorderTestAccessor& operator=(const FlightRecorderTestAccessor&) = delete;

  static void setRecording(FlightRecorder* recorder, Recording* recording) {
    recorder->_rec = recording;
  }
  static void setFilename(FlightRecorder* recorder, const char* filename) {
    recorder->_filename = filename;
  }
  static bool recoverThreadTableCapacity(FlightRecorder& recorder) {
    return recorder.recoverThreadTableCapacity();
  }
};

TEST(FlightRecorderResultTest, OutputQuarantineExcludesInactiveAndHealthyRecordings) {
  FlightRecorder recorder;
  EXPECT_FALSE(recorder.outputQuarantined());
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  FlightRecorderTestAccessor active(&recorder, recording.get());
  EXPECT_FALSE(recorder.outputQuarantined());
}

TEST(FlightRecorderResultTest, UncertainCreationCloseIsQuarantinedWithoutRecording) {
  FlightRecorder recorder;
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  FlightRecorderTestAccessor uncertain(&recorder, nullptr, output.fd());
  EXPECT_TRUE(recorder.outputQuarantined());
}

namespace {
// A source file with one appended byte, plus a scratch directory for dump targets.
class DumpPaths {
  char _dir[64] = "/tmp/ddprof-dump-XXXXXX";
  bool _created = mkdtemp(_dir) != nullptr;

public:
  std::string source = std::string(_dir) + "/source.jfr";
  std::string target = std::string(_dir) + "/target.jfr";
  bool valid() const { return _created; }
  ~DumpPaths() {
    unlink(target.c_str());
    unlink(source.c_str());
    rmdir(_dir);
  }
};

off_t fileSize(const std::string& path) {
  struct stat st{};
  return stat(path.c_str(), &st) == 0 ? st.st_size : -1;
}

Error dump(FlightRecorder& recorder, const std::string& path) {
  return recorder.dump(path.c_str(), static_cast<int>(path.size()));
}
} // namespace

TEST(FlightRecorderResultTest, DumpRejectsHardLinkToSourceWithoutTruncatingIt) {
  DumpPaths paths;
  ASSERT_TRUE(paths.valid());
  int fd = open(paths.source.c_str(), O_CREAT | O_RDWR, 0644);
  ASSERT_GE(fd, 0);
  auto recording = std::make_unique<Recording>(fd);
  RecordingTestAccessor::activateHotWrites(recording.get());
  RecordingTestAccessor::appendByte(recording.get());
  const off_t size = fileSize(paths.source);
  ASSERT_GT(size, 0);
  ASSERT_EQ(0, link(paths.source.c_str(), paths.target.c_str()));
  FlightRecorder recorder;
  FlightRecorderTestAccessor active(&recorder, recording.get());
  FlightRecorderTestAccessor::setFilename(&recorder, paths.source.c_str());

  Error error = dump(recorder, paths.target);
  ASSERT_TRUE(error);
  EXPECT_STREQ("Could not qualify recording dump destination", error.message());
  EXPECT_EQ(size, fileSize(paths.source)) << "an alias target must not truncate the source";
  EXPECT_TRUE(recording->outputGood());

  error = dump(recorder, paths.source);
  ASSERT_TRUE(error);
  EXPECT_STREQ("Can not dump recording to itself. Provide a different file name!", error.message());
}

TEST(FlightRecorderResultTest, DumpOfQuarantinedSourceDoesNotOpenTarget) {
  DumpPaths paths;
  ASSERT_TRUE(paths.valid());
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  ASSERT_TRUE(output.failWrites());
  RecordingTestAccessor::appendByte(recording.get());
  ASSERT_FALSE(recording->outputGood());
  FlightRecorder recorder;
  FlightRecorderTestAccessor active(&recorder, recording.get());

  Error error = dump(recorder, paths.target);
  ASSERT_TRUE(error);
  EXPECT_STREQ("Incomplete recording output is still owned", error.message());
  EXPECT_NE(0, access(paths.target.c_str(), F_OK)) << "a quarantined source must not create a target";
}

TEST(FlightRecorderResultTest, DumpReportsUnopenableTargetAndInactiveRecording) {
  DumpPaths paths;
  ASSERT_TRUE(paths.valid());
  FlightRecorder recorder;
  Error error = dump(recorder, paths.target);
  ASSERT_TRUE(error);
  EXPECT_STREQ("No active recording", error.message());

  auto output = std::unique_ptr<FILE, int (*)(FILE*)>(tmpfile(), fclose);
  ASSERT_NE(nullptr, output);
  auto recording = std::make_unique<Recording>(dup(fileno(output.get())));
  FlightRecorderTestAccessor active(&recorder, recording.get());
  error = dump(recorder, paths.target + "/missing-dir/target.jfr");
  ASSERT_TRUE(error);
  EXPECT_STREQ("Could not open recording file for dump", error.message());
}

// A FIFO opens read-write but rejects positioned writes, so the header cannot be written.
TEST(FlightRecorderResultTest, StartRejectsOutputThatCannotTakeTheHeader) {
  DumpPaths paths;
  ASSERT_TRUE(paths.valid());
  ASSERT_EQ(0, mkfifo(paths.target.c_str(), 0644));
  Arguments args;
  args._file = paths.target.c_str();
  FlightRecorder recorder;

  Error error = recorder.start(args, true);
  ASSERT_TRUE(error);
  EXPECT_STREQ("Could not initialize complete Flight Recorder output", error.message());
  EXPECT_FALSE(recorder.active());
  EXPECT_FALSE(recorder.outputQuarantined()) << "a closed descriptor leaves nothing owned";
}

TEST(FlightRecorderResultTest, RecordWallSampleReturnsFalseWhenActiveOutputFlushFails) {
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  FlightRecorder recorder;
  FlightRecorderTestAccessor active(&recorder, recording.get());
  RecordingBuffer* buffer = recording->buffer(0);
  buffer->skip(JFR_EVENT_FLUSH_THRESHOLD - 1);
  ASSERT_TRUE(recording->outputGood());
  ASSERT_TRUE(output.failWrites());

  ExecutionEvent event;
  Context context{};
  EXPECT_FALSE(recorder.recordWallSample(0, 1, 42, &event, context));
  EXPECT_FALSE(recording->outputGood());
  EXPECT_TRUE(recorder.outputQuarantined());
  EXPECT_GE(buffer->offset(), JFR_EVENT_FLUSH_THRESHOLD)
      << "the failed real pwrite must leave its serialized bytes owned";
}

TEST(FlightRecorderResultTest, RecordWallSampleRejectsStickyOutputFailureWithoutBufferGrowth) {
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  RecordingTestAccessor::activateHotWrites(recording.get());
  FlightRecorder recorder;
  FlightRecorderTestAccessor active(&recorder, recording.get());
  RecordingBuffer* buffer = recording->buffer(0);
  buffer->skip(JFR_EVENT_FLUSH_THRESHOLD);
  ASSERT_TRUE(output.failWrites());
  EXPECT_FALSE(recording->flushIfNeeded(buffer));
  ASSERT_FALSE(recording->outputGood());
  int before = buffer->offset();

  ExecutionEvent event;
  Context context{};
  EXPECT_FALSE(recorder.recordWallSample(0, 1, 42, &event, context));
  EXPECT_EQ(before, buffer->offset()) << "sticky failure must reject before serialization";
}

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
  auto output = std::unique_ptr<FILE, int (*)(FILE*)>(tmpfile(), fclose);
  ASSERT_NE(nullptr, output);
  auto recording = std::make_unique<Recording>(fileno(output.get()));
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
  ExecutionEvent tail;
  tail._thread_state = OSThreadState::SLEEPING;
  tail._weight = 7;
  Context context{};
  EXPECT_FALSE(recorder.recordWallSample(0, 257, 42, &tail, context));
  EXPECT_EQ(before, buffer->offset()) << "a rejected wall tail must not append event bytes";
  EXPECT_TRUE(recorder.recordTaskBlock(0, 1, &event)) << "a full table still represents existing tids";
  EXPECT_TRUE(recorder.recordWallSample(0, 1, 42, &tail, context));
  std::unordered_set<int> tids;
  RecordingTestAccessor::collectThreads(recording.get(), 0, tids);
  EXPECT_EQ(256u, tids.size());
  // Decode the real serializer's eventThread field, not just insertion status.
  int events = 0;
  for (int start = 0; start < buffer->offset();) {
    int cursor = start;
    u64 size = readVar64(buffer, cursor);
    u64 type = readVar64(buffer, cursor);
    readVar64(buffer, cursor); // start
    if (type == T_TASK_BLOCK) {
      readVar64(buffer, cursor); // duration
    } else {
      EXPECT_EQ(T_METHOD_SAMPLE, type);
    }
    int tid = static_cast<int>(readVar64(buffer, cursor));
    EXPECT_EQ(1u, tids.count(tid)) << "undefined serialized eventThread=" << tid;
    ASSERT_GT(size, 0u);
    start += size;
    ++events;
  }
  EXPECT_EQ(258, events);
  FlightRecorderTestAccessor::setRecording(&recorder, nullptr);
}

class ProfilerTestAccessor {
public:
  static void setOmit(Profiler* profiler, bool omit) { profiler->_omit_stacktraces = omit; }
  static FlightRecorder* recorder(Profiler* profiler) { return &profiler->_jfr; }
};

TEST(FlightRecorderResultTest, LightweightShortBurstsSerializeEveryUnitOfWeight) {
  auto output = std::unique_ptr<FILE, int (*)(FILE*)>(tmpfile(), fclose);
  ASSERT_NE(nullptr, output);
  auto recording = std::make_unique<Recording>(fileno(output.get()));
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

TEST(FlightRecorderResultTest, CapacityRecoveryRequiresActiveRecordingAndNonzeroOverflowTid) {
  FlightRecorder recorder;
  EXPECT_FALSE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
  RecordingWriteFailureFixture output;
  ASSERT_TRUE(output.valid());
  auto recording = std::make_unique<Recording>(output.fd());
  FlightRecorderTestAccessor active(&recorder, recording.get());
  EXPECT_FALSE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
  ExecutionEvent sample;
  Context context{};
  EXPECT_FALSE(recorder.recordWallSample(0, 0, 42, &sample, context));
  EXPECT_FALSE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
  for (int tid = 1; tid <= ThreadIdTable::capacity(); ++tid) {
    ASSERT_TRUE(recorder.recordWallSample(0, tid, 42, &sample, context));
  }
  EXPECT_TRUE(recorder.recordWallSample(0, 1, 42, &sample, context));
  EXPECT_FALSE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
  EXPECT_FALSE(recorder.recordWallSample(0, ThreadIdTable::capacity() + 1, 42, &sample, context));
  EXPECT_TRUE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
  EXPECT_TRUE(recorder.recordWallSample(0, ThreadIdTable::capacity() + 1, 42, &sample, context));
  EXPECT_FALSE(FlightRecorderTestAccessor::recoverThreadTableCapacity(recorder));
}
