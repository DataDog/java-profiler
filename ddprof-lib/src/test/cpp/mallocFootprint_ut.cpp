/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include <map>
#include "common.h"
#include "mallocFootprint.h"
#include "nativeMem.h"
#include "countingAllocator.h"

// Allocator overhead is a function of PER-ALLOCATION size, not of total bytes.
// That is the whole reason a single blanket multiplier cannot be correct across
// categories: the same total can be one large chunk paying ~0 % or thousands of
// small nodes paying ~17 %. These tests pin that, and pin that the profiler now
// measures it rather than assuming a factor.

// True when the allocator in force exposes enough for overhead to be observed
// at all. Sanitizer builds substitute their own allocator, whose usable size is
// the requested size and which lays blocks out so the header probe yields 0 --
// so it correctly reports no overhead, and the magnitude assertions below have
// nothing to measure. Reporting zero there is the honest answer, not a bug.
static bool allocatorExposesOverhead() {
  void *p = malloc(96);
  if (p == NULL) return false;
  size_t oh = MallocFootprint::overheadOf(p, 96);
  free(p);
  return oh > 0;
}

class MallocFootprintTest : public ::testing::Test {
protected:
  long long _baseline[NM_NUM_CATEGORIES];
  void SetUp() override {
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
      _baseline[c] = NativeMem::live((NativeMemCategory)c);
    }
    NativeMem::reset();
  }
  void TearDown() override {
    NativeMem::reset();
    for (int c = 0; c < NM_NUM_CATEGORIES; c++) {
      NativeMem::setLive((NativeMemCategory)c, _baseline[c]);
    }
  }
};

// An LD_PRELOAD'd tcmalloc or jemalloc adds no header while __GLIBC__ stays
// defined, so the header must fit the allocator in force; anywhere it must at
// least be sane. FragmentedHeapStillYieldsGlibcHeader pins the glibc value.
TEST_F(MallocFootprintTest, HeaderProbeReturnsSaneValue) {
  size_t h = MallocFootprint::headerBytes();
  EXPECT_LE(h, 64u) << "probe returned an implausible header size";
  printf("[FOOTPRINT] probed per-chunk header = %zu bytes\n", h);

  void *p = malloc(96);
  ASSERT_NE(nullptr, p);
  size_t fp = MallocFootprint::of(p, 96);
  // Reported via MallocFootprint rather than the allocator call directly: the
  // usable-size entry point is named differently per platform, and the class
  // already owns that distinction.
  printf("[FOOTPRINT] request=96 footprint=%zu overhead=%zu\n", fp,
         MallocFootprint::overheadOf(p, 96));
  EXPECT_GE(fp, 96u) << "footprint cannot be below the requested size";
  free(p);
}

// The glibc layout rule on 64-bit sizes: glibc chunks match, exact or handed out
// whole; size-class and sanitizer sizes (multiples of 16 here) do not.
TEST_F(MallocFootprintTest, GlibcUsableSizeRule) {
  if (sizeof(size_t) != 8) {
    GTEST_SKIP() << "values below assume a 64-bit size_t";
  }
  EXPECT_TRUE(MallocFootprint::glibcUsable(48, 56));    // 64-byte chunk
  EXPECT_TRUE(MallocFootprint::glibcUsable(56, 56));    // 64-byte chunk, filled
  EXPECT_TRUE(MallocFootprint::glibcUsable(100, 104));  // 112-byte chunk
  EXPECT_TRUE(MallocFootprint::glibcUsable(112, 136));  // 144-byte chunk, not split
  EXPECT_FALSE(MallocFootprint::glibcUsable(48, 48));   // size class / sanitizer
  EXPECT_FALSE(MallocFootprint::glibcUsable(112, 112));
  EXPECT_FALSE(MallocFootprint::glibcUsable(48, 60));   // large enough, misaligned
  EXPECT_FALSE(MallocFootprint::glibcUsable(48, 40));   // smaller than the request
}

// The glibc tests below skip when glibc is not recognised; this keeps a broken
// recognition from turning them into silent skips on a plain glibc build.
TEST_F(MallocFootprintTest, PlainGlibcIsRecognised) {
#if !defined(__GLIBC__) || defined(ASAN_ENABLED) || defined(TSAN_ENABLED)
  GTEST_SKIP() << "not a plain glibc build";
#else
  // A preloaded allocator, or glibc's malloc checking, changes the layout.
  if (getenv("LD_PRELOAD") != NULL || getenv("MALLOC_CHECK_") != NULL) {
    GTEST_SKIP() << "allocator replaced or in a glibc debug mode";
  }
  EXPECT_TRUE(MallocFootprint::glibcChunks());
#endif
}

// With freed same-size chunks scattered between live ones, the stride probe
// finds no adjacent pair; glibc must still be recognised and get its header.
TEST_F(MallocFootprintTest, FragmentedHeapStillYieldsGlibcHeader) {
  if (!MallocFootprint::glibcChunks()) {
    GTEST_SKIP() << "allocator in force is not glibc";
  }
  const int N = 512;
  void *blocks[N];
  bool allocated = true;
  for (int i = 0; i < N; i++) {
    blocks[i] = malloc(48);
    allocated = allocated && blocks[i] != NULL;
  }
  for (int i = 1; i < N; i += 2) {
    free(blocks[i]);
    blocks[i] = NULL;
  }
  size_t stride = MallocFootprint::strideHeaderBytes();
  size_t probed = MallocFootprint::probeHeaderBytes();
  for (int i = 0; i < N; i += 2) {
    free(blocks[i]);
  }
  ASSERT_TRUE(allocated);
  if (stride == sizeof(size_t)) {  // the stride probe still found two adjacent blocks
    GTEST_SKIP() << "the heap did not fragment as intended";
  }
  EXPECT_EQ(sizeof(size_t), probed);
}

// The central claim: overhead as a FRACTION collapses as allocation size grows.
// A blanket multiplier calibrated on small allocations therefore over-charges
// large ones badly -- which is precisely the case for the 512 KB string-arena
// chunks and the JFR buffers.
TEST_F(MallocFootprintTest, OverheadFractionCollapsesWithAllocationSize) {
  if (!allocatorExposesOverhead()) {
    GTEST_SKIP() << "allocator exposes no overhead (sanitizer build)";
  }
  struct { size_t size; const char *what; } cases[] = {
      {96,               "MethodMap node"},
      {6 * 1024,         "SBTable"},
      {512 * 1024,       "string-arena chunk"},
      {2 * 1024 * 1024,  "large buffer"},
  };
  double small_pct = -1, large_pct = -1;
  for (auto &c : cases) {
    void *p = malloc(c.size);
    ASSERT_NE(nullptr, p);
    size_t oh = MallocFootprint::overheadOf(p, c.size);
    double pct = 100.0 * (double)oh / (double)c.size;
    printf("[FOOTPRINT] %-20s request=%-8zu overhead=%-4zu (%.4f %%)\n",
           c.what, c.size, oh, pct);
    if (c.size == 96) small_pct = pct;
    if (c.size == 512 * 1024) large_pct = pct;
    free(p);
  }
  ASSERT_GE(small_pct, 0);
  ASSERT_GE(large_pct, 0);
  // A small node pays a double-digit percentage...
  EXPECT_GT(small_pct, 10.0)
      << "a 96-byte allocation should pay a double-digit overhead percentage";
  // ...while a 512 KB chunk pays well under one percent. A blanket factor
  // calibrated on the former over-charges the latter by more than an order of
  // magnitude, which is the quantitative reason one factor cannot serve both.
  EXPECT_LT(large_pct, 1.0)
      << "a 512 KB chunk must not be charged a double-digit percentage";
  EXPECT_GT(small_pct, large_pct * 10);

  // Large-allocation overhead is not even a function of the request size.
  // glibc serves large requests either from an arena or by mmap, and the
  // crossover is a DYNAMIC threshold that rises as large blocks are freed. So
  // the identical 512 KB request measures 4088 bytes of overhead (mmap: page
  // rounding on the final page) in one allocator state and 16 bytes (arena:
  // header only) in another, purely as a function of allocation history.
  //
  // This is the decisive argument for measuring rather than computing: no
  // arithmetic formula over the requested size -- align16(S + 8) or anything
  // else -- can be right for large allocations, because the answer depends on
  // state the caller cannot see.
  size_t seen_min = (size_t)-1, seen_max = 0;
  for (int i = 0; i < 8; i++) {
    void *p = malloc(512 * 1024);
    ASSERT_NE(nullptr, p);
    size_t oh = MallocFootprint::overheadOf(p, 512 * 1024);
    if (oh < seen_min) seen_min = oh;
    if (oh > seen_max) seen_max = oh;
    free(p);
  }
  printf("[FOOTPRINT] identical 512 KB request, 8 attempts: overhead %zu..%zu\n",
         seen_min, seen_max);
  // Whatever the allocator chose, it must stay far below the double-digit
  // percentage a small-allocation-derived factor would charge.
  EXPECT_LT(100.0 * (double)seen_max / (double)(512 * 1024), 1.0);
}

// CountingAllocator must populate the overhead gauge while leaving the live
// gauge as logical bytes, and both must return to zero on release.
TEST_F(MallocFootprintTest, CountingAllocatorTracksOverheadSeparately) {
  if (!allocatorExposesOverhead()) {
    GTEST_SKIP() << "allocator exposes no overhead (sanitizer build)";
  }
  using Map = std::map<long, long, std::less<long>,
                       CountingAllocator<std::pair<const long, long>,
                                         NM_METHOD_MAP>>;
  {
    Map m;
    for (long i = 0; i < 2000; i++) {
      m[i * 7919] = i;
    }
    long long live = NativeMem::live(NM_METHOD_MAP);
    long long oh = NativeMem::overhead(NM_METHOD_MAP);
    printf("[FOOTPRINT] map of 2000 nodes: live=%lld overhead=%lld (%.1f %%)\n",
           live, oh, 100.0 * (double)oh / (double)live);
    EXPECT_GT(live, 0);
    EXPECT_GT(oh, 0) << "overhead gauge was not populated";
    // Nodes are small, so overhead is a substantial fraction -- not a rounding
    // error, and not something a logical-bytes-only counter can see.
    EXPECT_GT(100.0 * (double)oh / (double)live, 1.0);
  }
  EXPECT_EQ(0, NativeMem::live(NM_METHOD_MAP))
      << "live gauge did not return to zero";
  EXPECT_EQ(0, NativeMem::overhead(NM_METHOD_MAP))
      << "overhead gauge did not return to zero; recordFreeBefore is unbalanced";
}

// recordAlloc/recordFreeBefore must balance exactly, including for a size whose
// rounding is non-trivial.
TEST_F(MallocFootprintTest, RecordAllocAndFreeBalance) {
  const size_t SZ = 100;  // not a multiple of the alignment quantum
  void *ptrs[500];
  for (int i = 0; i < 500; i++) {
    ptrs[i] = malloc(SZ);
    ASSERT_NE(nullptr, ptrs[i]);
    NativeMem::recordAlloc(NM_MISC, ptrs[i], SZ);
  }
  EXPECT_EQ((long long)(500 * SZ), NativeMem::live(NM_MISC));
  if (allocatorExposesOverhead()) {
    EXPECT_GT(NativeMem::overhead(NM_MISC), 0);
  }

  for (int i = 0; i < 500; i++) {
    NativeMem::recordFreeBefore(NM_MISC, ptrs[i], SZ);
    free(ptrs[i]);
  }
  EXPECT_EQ(0, NativeMem::live(NM_MISC));
  EXPECT_EQ(0, NativeMem::overhead(NM_MISC));
}
