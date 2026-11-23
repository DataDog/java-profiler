/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "counters.h"
#include "event.h"
#include "flightRecorder.h"
#include "jfrMetadata.h"
#include "profiler.h"

#include <gtest/gtest.h>
#include <climits>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <unistd.h>
#include <vector>

class RecordingTestAccessor {
public:
  static void setRecordingTid(Recording* recording, int tid) { recording->_tid = tid; }
  static void writeThreads(Recording* recording, Buffer* buffer) { recording->writeThreads(buffer); }
};

class FlightRecorderTestAccessor {
public:
  static void setRecording(FlightRecorder* recorder, Recording* recording) {
    recorder->_rec = recording;
  }
};

class ProfilerTestAccessor {
public:
  static void setThreadInfo(int tid, const char* name, u64 java_thread_id) {
    Profiler::instance()->_thread_info.set(tid, name, java_thread_id);
  }
  static void clearThreadInfo() { Profiler::instance()->_thread_info.clearAll(); }
};

namespace {

constexpr int RECORDING_TID = 4242;

u64 readVar64(const char* data, int& offset) {
  u64 value = 0;
  int shift = 0;
  unsigned char byte;
  do {
    byte = static_cast<unsigned char>(data[offset++]);
    value |= static_cast<u64>(byte & 0x7f) << shift;
    shift += 7;
  } while (byte & 0x80);
  return value;
}

struct DecodedString {
  bool null;
  std::string value;
};

u64 readVar64(const Buffer* buffer, int& offset) { return readVar64(buffer->data(), offset); }

DecodedString readString(const char* data, int& offset) {
  int encoding = static_cast<unsigned char>(data[offset++]);
  if (encoding == 0) return {true, ""};
  EXPECT_EQ(3, encoding) << "unexpected string encoding";
  u64 length = readVar64(data, offset);
  std::string value(data + offset, length);
  offset += static_cast<int>(length);
  return {false, value};
}

struct PoolEntry {
  DecodedString os_name;
  u64 os_thread_id;
  DecodedString java_name;
  u64 java_thread_id;
  std::string bytes;  // the entry's raw encoding, key included
};

std::map<u64, PoolEntry> decodeThreadPool(const std::string& pool) {
  const char* buffer = pool.data();
  int offset = 0;
  EXPECT_EQ(static_cast<u64>(T_THREAD), readVar64(buffer, offset));
  u64 count = readVar64(buffer, offset);
  std::map<u64, PoolEntry> entries;
  for (u64 i = 0; i < count; ++i) {
    int begin = offset;
    u64 key = readVar64(buffer, offset);
    PoolEntry entry;
    entry.os_name = readString(buffer, offset);
    entry.os_thread_id = readVar64(buffer, offset);
    entry.java_name = readString(buffer, offset);
    entry.java_thread_id = readVar64(buffer, offset);
    entry.bytes.assign(buffer + begin, offset - begin);
    EXPECT_TRUE(entries.emplace(key, entry).second) << "duplicate thread-pool key " << key;
  }
  EXPECT_EQ(static_cast<int>(pool.size()), offset) << "thread pool has trailing bytes";
  return entries;
}

// The platform-entry encoding writeThreads() produced before virtual threads had entries.
std::string platformEntryBytes(int tid, const char* name, u64 java_thread_id) {
  auto buffer = std::make_unique<RecordingBuffer>();
  buffer->putVar64(tid);
  buffer->putUtf8(name, strlen(name));
  buffer->putVar64(tid);
  if (java_thread_id == 0) {
    buffer->put8(0);
  } else {
    buffer->putUtf8(name, strlen(name));
  }
  buffer->putVar64(java_thread_id);
  return std::string(buffer->data(), buffer->offset());
}

VirtualThreadIdentity identity(u64 id, const char* name) {
  return VirtualThreadIdentity{id, name, name != nullptr ? strlen(name) : 0};
}

class ThreadPoolTest : public ::testing::Test {
protected:
  std::unique_ptr<FILE, int (*)(FILE*)> _output{tmpfile(), fclose};
  std::unique_ptr<Recording> _recording;
  std::unique_ptr<RecordingBuffer> _pool = std::make_unique<RecordingBuffer>();

  void SetUp() override {
    ASSERT_NE(nullptr, _output);
    _recording = std::make_unique<Recording>(fileno(_output.get()));
    RecordingTestAccessor::setRecordingTid(_recording.get(), RECORDING_TID);
    ProfilerTestAccessor::clearThreadInfo();
    Counters::reset();
  }

  void TearDown() override { ProfilerTestAccessor::clearThreadInfo(); }

  // A large pool flushes to the output file; the file holds nothing else.
  std::map<u64, PoolEntry> writePool() {
    _pool->reset();
    off_t flushed_before = lseek(fileno(_output.get()), 0, SEEK_END);
    RecordingTestAccessor::writeThreads(_recording.get(), _pool.get());
    off_t flushed_after = lseek(fileno(_output.get()), 0, SEEK_END);
    std::string pool(static_cast<size_t>(flushed_after - flushed_before), '\0');
    EXPECT_EQ(static_cast<ssize_t>(pool.size()),
              pread(fileno(_output.get()), &pool[0], pool.size(), flushed_before));
    pool.append(_pool->data(), _pool->offset());
    return decodeThreadPool(pool);
  }
};

} // namespace

TEST(VirtualThreadKeyTest, KeysAreDisjointFromEverySignExtendedIntTid) {
  const u64 lowest = Recording::virtualThreadKey(1);
  const u64 highest = Recording::virtualThreadKey(Recording::MAX_VIRTUAL_THREAD_ID - 1);
  EXPECT_GT(lowest, static_cast<u64>(INT_MAX));
  EXPECT_GT(lowest, static_cast<u64>(UINT_MAX)) << "a 32-bit tid must never alias a virtual key";
  EXPECT_LT(highest, static_cast<u64>(static_cast<long long>(INT_MIN)))
      << "a negative tid sign-extends above every virtual key";
  EXPECT_LT(lowest, highest);
  EXPECT_NE(Recording::virtualThreadKey(7), Recording::virtualThreadKey(8));
}

TEST_F(ThreadPoolTest, PlatformOnlyPoolKeepsItsEncoding) {
  ProfilerTestAccessor::setThreadInfo(1234, "platform-worker", 77);
  ASSERT_TRUE(_recording->addThread(0, 1234));
  ASSERT_TRUE(_recording->addThread(5, 99));  // no ThreadInfo: named [tid=99]

  std::map<u64, PoolEntry> entries = writePool();

  ASSERT_EQ(3u, entries.size());
  EXPECT_EQ(platformEntryBytes(1234, "platform-worker", 77), entries[1234].bytes);
  EXPECT_EQ(platformEntryBytes(99, "[tid=99]", 0), entries[99].bytes);
  EXPECT_EQ(platformEntryBytes(RECORDING_TID, "[tid=4242]", 0), entries[RECORDING_TID].bytes);
}

TEST_F(ThreadPoolTest, VirtualEntriesUseTheirOwnKeySpaceBesidePlatformEntries) {
  ProfilerTestAccessor::setThreadInfo(1234, "platform-worker", 77);
  ASSERT_TRUE(_recording->addThread(0, 1234));
  VirtualThreadIdentity same_number = identity(1234, "vt-1234");
  VirtualThreadIdentity unnamed = identity(5, "");
  ASSERT_TRUE(_recording->addVirtualThread(0, same_number));
  ASSERT_TRUE(_recording->addVirtualThread(3, same_number));  // other carrier stripe
  ASSERT_TRUE(_recording->addVirtualThread(1, unnamed));

  std::map<u64, PoolEntry> entries = writePool();

  ASSERT_EQ(4u, entries.size()) << "two platform entries plus two distinct virtual threads";
  EXPECT_EQ(platformEntryBytes(1234, "platform-worker", 77), entries[1234].bytes);
  const PoolEntry& named = entries[Recording::virtualThreadKey(1234)];
  EXPECT_TRUE(named.os_name.null);
  EXPECT_EQ(0u, named.os_thread_id);
  EXPECT_FALSE(named.java_name.null);
  EXPECT_EQ("vt-1234", named.java_name.value);
  EXPECT_EQ(1234u, named.java_thread_id);
  const PoolEntry& empty = entries[Recording::virtualThreadKey(5)];
  EXPECT_EQ(0u, empty.os_thread_id);
  EXPECT_FALSE(empty.java_name.null);
  EXPECT_EQ("", empty.java_name.value);
  EXPECT_EQ(5u, empty.java_thread_id);

  std::map<u64, PoolEntry> next_chunk = writePool();
  EXPECT_EQ(1u, next_chunk.size()) << "virtual entries are per chunk";
  EXPECT_EQ(1u, next_chunk.count(RECORDING_TID));
}

TEST_F(ThreadPoolTest, AddVirtualThreadRejectsIdsOutsideTheKeySpace) {
  EXPECT_FALSE(_recording->addVirtualThread(0, identity(0, "zero")));
  EXPECT_FALSE(_recording->addVirtualThread(0, identity(Recording::MAX_VIRTUAL_THREAD_ID, "max")));
  EXPECT_TRUE(_recording->addVirtualThread(0, identity(Recording::MAX_VIRTUAL_THREAD_ID - 1, "last")));
  VirtualThreadIdentity null_name{9, nullptr, 3};
  EXPECT_TRUE(_recording->addVirtualThread(0, null_name));

  std::map<u64, PoolEntry> entries = writePool();
  EXPECT_EQ(3u, entries.size());
  EXPECT_EQ(1u, entries.count(Recording::virtualThreadKey(Recording::MAX_VIRTUAL_THREAD_ID - 1)));
  EXPECT_EQ("", entries[Recording::virtualThreadKey(9)].java_name.value);
}

TEST_F(ThreadPoolTest, LongVirtualThreadNamesAreTruncatedLikeOtherStrings) {
  std::string long_name(MAX_STRING_LENGTH + 100, 'n');
  ASSERT_TRUE(_recording->addVirtualThread(0, identity(3, long_name.c_str())));
  std::map<u64, PoolEntry> entries = writePool();
  EXPECT_EQ(static_cast<size_t>(MAX_STRING_LENGTH),
            entries[Recording::virtualThreadKey(3)].java_name.value.size());
}

TEST_F(ThreadPoolTest, CapacityBoundsNewVirtualEntriesPerChunk) {
  const u32 capacity = Recording::VIRTUAL_THREAD_POOL_CAPACITY;
  for (u32 id = 1; id <= capacity; ++id) {
    ASSERT_TRUE(_recording->addVirtualThread(id % CONCURRENCY_LEVEL, identity(id, "")));
  }
  EXPECT_FALSE(_recording->addVirtualThread(0, identity(capacity + 1, "")));
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_VIRTUAL_THREAD_POOL_FULL));
  EXPECT_TRUE(_recording->addVirtualThread(1, identity(1, ""))) << "a known id stays admissible";
  EXPECT_EQ(1, Counters::getCounter(TASK_BLOCK_VIRTUAL_THREAD_POOL_FULL));

  EXPECT_EQ(capacity + 1, writePool().size());
  EXPECT_TRUE(_recording->addVirtualThread(0, identity(capacity + 1, "")))
      << "writing the pool frees the chunk's capacity";
}

TEST_F(ThreadPoolTest, TaskBlockEventThreadReferencesItsOwnPoolEntry) {
  FlightRecorder recorder;
  FlightRecorderTestAccessor::setRecording(&recorder, _recording.get());
  constexpr int CARRIER_TID = 321;
  VirtualThreadIdentity virtual_thread = identity(CARRIER_TID, "vt");
  TaskBlockEvent virtual_event{};
  virtual_event._start = 1;
  virtual_event._end = 2;
  virtual_event._observedBlockingState = OSThreadState::CONDVAR_WAIT;
  virtual_event._virtualThread = &virtual_thread;
  TaskBlockEvent platform_event = virtual_event;
  platform_event._virtualThread = nullptr;

  EXPECT_TRUE(recorder.recordTaskBlock(0, CARRIER_TID, &virtual_event));
  std::map<u64, PoolEntry> virtual_only = writePool();
  EXPECT_EQ(0u, virtual_only.count(CARRIER_TID)) << "the carrier tid must not enter the pool";
  EXPECT_EQ(1u, virtual_only.count(Recording::virtualThreadKey(CARRIER_TID)));
  EXPECT_TRUE(recorder.recordTaskBlock(0, CARRIER_TID, &platform_event));

  Buffer* events = _recording->buffer(0);
  std::vector<u64> threads;
  for (int start = 0; start < events->offset();) {
    int cursor = start;
    u64 size = readVar64(events, cursor);
    EXPECT_EQ(static_cast<u64>(T_TASK_BLOCK), readVar64(events, cursor));
    readVar64(events, cursor);  // startTime
    readVar64(events, cursor);  // duration
    threads.push_back(readVar64(events, cursor));
    ASSERT_GT(size, 0u);
    start += static_cast<int>(size);
  }
  ASSERT_EQ(2u, threads.size());
  EXPECT_EQ(Recording::virtualThreadKey(CARRIER_TID), threads[0]);
  EXPECT_EQ(static_cast<u64>(CARRIER_TID), threads[1]);
  FlightRecorderTestAccessor::setRecording(&recorder, nullptr);
}

TEST_F(ThreadPoolTest, RejectedVirtualAdmissionWritesNoEventBytes) {
  FlightRecorder recorder;
  FlightRecorderTestAccessor::setRecording(&recorder, _recording.get());
  VirtualThreadIdentity invalid = identity(0, "invalid");
  TaskBlockEvent event{};
  event._start = 1;
  event._end = 2;
  event._observedBlockingState = OSThreadState::CONDVAR_WAIT;
  event._virtualThread = &invalid;
  int before = _recording->buffer(0)->offset();
  EXPECT_FALSE(recorder.recordTaskBlock(0, 1, &event));
  EXPECT_EQ(before, _recording->buffer(0)->offset());
  FlightRecorderTestAccessor::setRecording(&recorder, nullptr);
}
