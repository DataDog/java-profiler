/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "jfrMetadata.h"
#include "mallocArenaEvents.h"

namespace {

// Decodes the JFR varint encoding written by Buffer::putVar32/putVar64: seven
// bits per byte, low bits first, at most 8 such bytes, then a 9th byte that
// carries 8 bits.
class Reader {
 public:
  Reader(const char* data, int size) : _p((const unsigned char*)data), _end(_p + size) {}

  u64 varint() {
    u64 v = 0;
    for (int i = 0; i < 9; i++) {
      EXPECT_LT(_p, _end);
      unsigned char b = *_p++;
      if (i == 8) {
        return v | ((u64)b << 56);
      }
      v |= (u64)(b & 0x7f) << (7 * i);
      if ((b & 0x80) == 0) {
        return v;
      }
    }
    return v;
  }

  // The 5-byte size prefix is never longer than 5 bytes.
  u32 var32() {
    u32 v = 0;
    for (int i = 0; i < 5; i++) {
      EXPECT_LT(_p, _end);
      unsigned char b = *_p++;
      v |= (u32)(b & 0x7f) << (7 * i);
      if ((b & 0x80) == 0) {
        break;
      }
    }
    return v;
  }

  long long lng() { return (long long)varint(); }
  int integer() { return (int)var32(); }

  std::string str() {
    EXPECT_LT(_p, _end);
    EXPECT_EQ(*_p++, 3);  // UTF-8 string encoding marker
    u32 len = var32();
    EXPECT_LE(_p + len, _end);
    std::string s((const char*)_p, len);
    _p += len;
    return s;
  }

  int bool8() { return *_p++; }
  bool atEnd() const { return _p == _end; }
  const unsigned char* pos() const { return _p; }

 private:
  const unsigned char* _p;
  const unsigned char* _end;
};

MallocArenaEvaluation makeEvaluation() {
  MallocArenaEvaluation e = {};
  e.cond1 = true;
  e.cond2 = true;
  e.active = true;
  e.recommendedArenaMax = 16;
  e.nativeHeadroom = 3ULL << 30;
  e.headroomSource = "limit-minus-heap";
  e.heapExceedsLimit = false;
  e.conditionMeasure = "free-held";
  e.measureBytes = 900ULL << 20;
  return e;
}

MallocArenaWarningRecord makeWarning() {
  MallocArenaWarningRecord r = {};
  r.arenaCount = 40;
  r.arenaLimit = 64;
  r.arenaLimitSource = "default";
  r.onlineCpus = 8;
  r.cpuQuotaMilli = 1500;
  r.memoryLimit = 4LL << 30;
  r.memoryLimitSource = "cgroup-v2";
  r.maxHeap = 1LL << 30;
  r.freeHeldBytes = 900LL << 20;
  r.nonMainArenaBytes = 1200LL << 20;
  r.thresholdPercent = 25;
  r.threadPrivateArenas = 31;
  r.largestArenaBytes = 64LL << 20;
  r.largestArenaMaxBytes = 128LL << 20;
  r.glibcVersion = "2.35";
  r.layout = "2.27-2.42";
  r.walkStatus = "ok";
  r.evaluation = makeEvaluation();
  return r;
}

MallocArenaStatsRecord makeStats() {
  MallocArenaStatsRecord r = {};
  r.arenaCount = 12;
  r.nonMainArenaBytes = 300LL << 20;
  r.freeHeldBytes = 100LL << 20;
  r.largestArenaBytes = 64LL << 20;
  r.cpuQuotaMilli = 2000;
  r.memoryLimit = 8LL << 30;
  r.maxHeap = 2LL << 30;
  r.walkStatus = "ok";
  return r;
}

// Reads the size prefix and checks it against the bytes written.
Reader beginRead(const Buffer& buf, JfrType type, u64 ticks) {
  Reader in(buf.data(), buf.offset());
  const unsigned char* begin = in.pos();
  u32 size = in.var32();
  EXPECT_EQ(size, (u32)buf.offset());
  EXPECT_EQ(in.pos() - begin, 5);
  EXPECT_EQ(in.varint(), (u64)type);
  EXPECT_EQ(in.varint(), ticks);
  return in;
}

}  // namespace

TEST(MallocArenaEventsTest, TypeIds) {
  EXPECT_EQ((int)T_MALLOC_ARENA_WARNING, 131);
  EXPECT_EQ((int)T_MALLOC_ARENA_STATS, 132);
}

TEST(MallocArenaEventsTest, StatsRoundTrip) {
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeStats(buf.get(), 123456789ULL, makeStats());

  Reader in = beginRead(*buf, T_MALLOC_ARENA_STATS, 123456789ULL);
  EXPECT_EQ(in.integer(), 12);
  EXPECT_EQ(in.lng(), 300LL << 20);
  EXPECT_EQ(in.lng(), 100LL << 20);
  EXPECT_EQ(in.lng(), 64LL << 20);
  EXPECT_EQ(in.integer(), 2000);
  EXPECT_EQ(in.lng(), 8LL << 30);
  EXPECT_EQ(in.lng(), 2LL << 30);
  EXPECT_EQ(in.str(), "ok");
  EXPECT_TRUE(in.atEnd());
}

TEST(MallocArenaEventsTest, StatsSentinelsRoundTrip) {
  MallocArenaStatsRecord r = makeStats();
  r.freeHeldBytes = -1;
  r.maxHeap = -1;
  r.walkStatus = "no-seed";
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeStats(buf.get(), 1, r);

  Reader in = beginRead(*buf, T_MALLOC_ARENA_STATS, 1);
  in.integer();
  in.lng();
  EXPECT_EQ(in.lng(), -1);
  in.lng();
  in.integer();
  in.lng();
  EXPECT_EQ(in.lng(), -1);
  EXPECT_EQ(in.str(), "no-seed");
  EXPECT_TRUE(in.atEnd());
}

TEST(MallocArenaEventsTest, WarningRoundTripInFieldOrder) {
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeWarning(buf.get(), 42, "raised", makeWarning());

  Reader in = beginRead(*buf, T_MALLOC_ARENA_WARNING, 42);
  EXPECT_EQ(in.str(), "raised");                  // state
  EXPECT_EQ(in.integer(), 40);                    // arenaCount
  EXPECT_EQ(in.integer(), 64);                    // arenaLimit
  EXPECT_EQ(in.str(), "default");                 // arenaLimitSource
  EXPECT_EQ(in.integer(), 8);                     // onlineCpus
  EXPECT_EQ(in.integer(), 1500);                  // cpuQuotaMilli
  EXPECT_EQ(in.lng(), 4LL << 30);                 // memoryLimit
  EXPECT_EQ(in.str(), "cgroup-v2");               // memoryLimitSource
  EXPECT_EQ(in.lng(), 1LL << 30);                 // maxHeap
  EXPECT_EQ(in.lng(), 3LL << 30);                 // nativeHeadroom
  EXPECT_EQ(in.str(), "limit-minus-heap");        // headroomSource
  EXPECT_EQ(in.bool8(), 0);                       // heapExceedsLimit
  EXPECT_EQ(in.lng(), 900LL << 20);               // freeHeldBytes
  EXPECT_EQ(in.lng(), 1200LL << 20);              // nonMainArenaBytes
  EXPECT_EQ(in.str(), "free-held");               // conditionMeasure
  EXPECT_EQ(in.integer(), 25);                    // thresholdPercent
  EXPECT_EQ(in.integer(), 31);                    // threadPrivateArenas
  EXPECT_EQ(in.lng(), 64LL << 20);                // largestArenaBytes
  EXPECT_EQ(in.lng(), 128LL << 20);               // largestArenaMaxBytes
  EXPECT_EQ(in.integer(), 16);                    // recommendedArenaMax
  EXPECT_EQ(in.str(), "2.35");                    // glibcVersion
  EXPECT_EQ(in.str(), "2.27-2.42");               // layout
  EXPECT_EQ(in.str(), "ok");                      // walkStatus
  EXPECT_TRUE(in.atEnd());
}

TEST(MallocArenaEventsTest, WarningSentinelsAndFlagRoundTrip) {
  MallocArenaWarningRecord r = makeWarning();
  r.maxHeap = -1;
  r.freeHeldBytes = -1;
  r.threadPrivateArenas = -1;
  r.evaluation.heapExceedsLimit = true;
  r.evaluation.conditionMeasure = "committed";
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeWarning(buf.get(), 7, "worsened", r);

  Reader in = beginRead(*buf, T_MALLOC_ARENA_WARNING, 7);
  EXPECT_EQ(in.str(), "worsened");
  in.integer(); in.integer(); in.str(); in.integer(); in.integer();
  in.lng(); in.str();
  EXPECT_EQ(in.lng(), -1);   // maxHeap
  in.lng(); in.str();
  EXPECT_EQ(in.bool8(), 1);  // heapExceedsLimit
  EXPECT_EQ(in.lng(), -1);   // freeHeldBytes
  in.lng();
  EXPECT_EQ(in.str(), "committed");
  in.integer();
  EXPECT_EQ(in.integer(), -1);  // threadPrivateArenas
  in.lng(); in.lng(); in.integer(); in.str(); in.str(); in.str();
  EXPECT_TRUE(in.atEnd());
}

TEST(MallocArenaEventsTest, LongStringsAreBoundedAndNullIsEmpty) {
  MallocArenaWarningRecord r = makeWarning();
  std::string longName(100, 'x');
  r.glibcVersion = longName.c_str();
  r.layout = NULL;
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeWarning(buf.get(), 7, "raised", r);
  EXPECT_LT(buf->offset(), BUFFER_LIMIT);

  Reader in = beginRead(*buf, T_MALLOC_ARENA_WARNING, 7);
  in.str(); in.integer(); in.integer(); in.str(); in.integer(); in.integer();
  in.lng(); in.str(); in.lng(); in.lng(); in.str(); in.bool8(); in.lng();
  in.lng(); in.str(); in.integer(); in.integer(); in.lng(); in.lng();
  in.integer();
  EXPECT_EQ(in.str(), std::string(MallocArenaEvents::MAX_STRING_BYTES, 'x'));
  EXPECT_EQ(in.str(), "");
  EXPECT_EQ(in.str(), "ok");
  EXPECT_TRUE(in.atEnd());
}

TEST(MallocArenaEventsTest, WarningExceeds127Bytes) {
  MallocArenaWarningRecord r = makeWarning();
  std::string name(MallocArenaEvents::MAX_STRING_BYTES, 'y');
  r.glibcVersion = name.c_str();
  r.layout = name.c_str();
  std::unique_ptr<Buffer> buf(new Buffer());
  MallocArenaEvents::writeWarning(buf.get(), 1, "raised", r);
  // A one-byte size prefix would not hold this event.
  EXPECT_GT(buf->offset(), 127);
}

TEST(MallocArenaEventsTest, MetadataRegistersBothTypes) {
  JfrMetadata::reset();
  JfrMetadata::initialize({});
  bool warning = false;
  bool stats = false;
  for (const std::string& s : JfrMetadata::strings()) {
    warning |= s == "datadog.MallocArenaWarning";
    stats |= s == "datadog.MallocArenaStats";
  }
  EXPECT_TRUE(warning);
  EXPECT_TRUE(stats);
  JfrMetadata::reset();
}
