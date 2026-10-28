/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include <map>
#include <memory>
#ifdef __GLIBC__
#include <climits>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#endif
#include "mallocFootprint.h"
#include "mallocFootprintChecks.h"
#include "nativeMem.h"
#include "countingAllocator.h"

// Allocator overhead is a function of PER-ALLOCATION size, not of total bytes.
// That is the whole reason a single blanket multiplier cannot be correct across
// categories: the same total can be one large chunk paying ~0 % or thousands of
// small nodes paying ~17 %. These tests pin that, and pin that the profiler now
// measures it rather than assuming a factor.

struct FreeAllocation {
  void operator()(void *p) const { free(p); }
};
using Allocation = std::unique_ptr<void, FreeAllocation>;

// Read the allocator API independently of MallocFootprint::of/overheadOf so
// omitting usable-size rounding or counting the header twice fails the test.
static size_t expectedFootprint(void *p, size_t requested) {
#ifdef DD_HAVE_MALLOC_USABLE_SIZE
  return malloc_usable_size(p) + MallocFootprint::headerBytes();
#elif defined(DD_HAVE_MALLOC_SIZE)
  return malloc_size(p) + MallocFootprint::headerBytes();
#else
  return requested;
#endif
}

// True when the allocator in force exposes enough for overhead to be observed
// at all. Sanitizer builds substitute their own allocator, whose usable size is
// the requested size and which lays blocks out so the header probe yields 0 --
// so it correctly reports no overhead, and the magnitude assertions below have
// nothing to measure. Reporting zero there is the honest answer, not a bug.
static bool allocatorExposesOverhead() {
  Allocation p(malloc(96));
  return p && expectedFootprint(p.get(), 96) > 96;
}

#ifdef __GLIBC__
// buildNativeLibs builds this standalone executable without profiler global
// constructors or sanitizer allocators. Its first header probe sees the layout
// it prepares, independently of the cached estimate in this gtest process.
static void runHeaderProbe(const char *layout, int expected_exit_code = 0) {
  char executable[PATH_MAX];
  const ssize_t len = readlink("/proc/self/exe", executable, sizeof(executable) - 1);
  ASSERT_GT(len, 0);
  ASSERT_LT(len, (ssize_t)sizeof(executable) - 1) << "Executable path may be truncated";
  executable[len] = '\0';
  char *slash = strrchr(executable, '/');
  ASSERT_NE(nullptr, slash) << "Executable path has no directory separator";
  *slash = '\0';
  char helper[PATH_MAX];
  ASSERT_LT(snprintf(helper, sizeof(helper),
      "%s/../../../test/resources/native-libs/malloc-footprint-probe/malloc-footprint-probe",
      executable), (int)sizeof(helper));
  ASSERT_EQ(0, access(helper, X_OK)) << "Missing test resource " << helper;
  ASSERT_EXIT({
    if (setenv("GLIBC_TUNABLES", "glibc.malloc.tcache_count=0", 1) != 0 ||
        unsetenv("LD_PRELOAD") != 0) _exit(126);
    execl(helper, helper, layout, (char *)nullptr);
    _exit(127);
  }, ::testing::ExitedWithCode(expected_exit_code), "");
}

TEST(MallocFootprintProbeDeathTest, ContiguousBlocksDiscoverNonzeroHeader) {
  runHeaderProbe("contiguous");
}

TEST(MallocFootprintProbeDeathTest, FragmentedBlocksRetainRoundingWithZeroHeader) {
  runHeaderProbe("fragmented");
}

TEST(MallocFootprintProbeDeathTest, UnknownLayoutsAreRejected) {
  for (const char *layout : {"", "contiguos", "fragment", "unknown"}) {
    runHeaderProbe(layout, 1);
  }
}
#endif

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

// The estimate may be zero when the probe is inconclusive. Regardless of that
// cached result, footprint must include the allocator's usable-size rounding.
TEST_F(MallocFootprintTest, HeaderProbeReturnsSaneValue) {
  size_t h = MallocFootprint::headerBytes();
  EXPECT_LE(h, 64u) << "probe returned an implausible header size";
  printf("[FOOTPRINT] probed per-chunk header = %zu bytes\n", h);

  Allocation p(malloc(96));
  ASSERT_NE(nullptr, p);
  size_t fp = MallocFootprint::of(p.get(), 96);
  printf("[FOOTPRINT] request=96 footprint=%zu overhead=%zu\n", fp,
         MallocFootprint::overheadOf(p.get(), 96));
  EXPECT_EQ(expectedFootprint(p.get(), 96), fp);
  EXPECT_GE(fp, 96u) << "footprint cannot be below the requested size";
  EXPECT_EQ(0u, MallocFootprint::of(nullptr, 96));
  EXPECT_EQ(0u, MallocFootprint::overheadOf(nullptr, 96));
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
    Allocation p(malloc(c.size));
    ASSERT_NE(nullptr, p);
    size_t oh = MallocFootprint::overheadOf(p.get(), c.size);
    EXPECT_EQ(expectedFootprint(p.get(), c.size), MallocFootprint::of(p.get(), c.size));
    EXPECT_EQ(expectedFootprint(p.get(), c.size) - c.size, oh);
    double pct = 100.0 * (double)oh / (double)c.size;
    printf("[FOOTPRINT] %-20s request=%-8zu overhead=%-4zu (%.4f %%)\n",
           c.what, c.size, oh, pct);
    if (c.size == 96) small_pct = pct;
    if (c.size == 512 * 1024) large_pct = pct;
  }
  checkOverheadFractions(small_pct, large_pct);

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
    Allocation p(malloc(512 * 1024));
    ASSERT_NE(nullptr, p);
    size_t oh = MallocFootprint::overheadOf(p.get(), 512 * 1024);
    EXPECT_EQ(expectedFootprint(p.get(), 512 * 1024) - 512 * 1024, oh);
    if (oh < seen_min) seen_min = oh;
    if (oh > seen_max) seen_max = oh;
  }
  printf("[FOOTPRINT] identical 512 KB request, 8 attempts: overhead %zu..%zu\n",
         seen_min, seen_max);
  // Whatever the allocator chose, its overhead fraction must remain small.
  EXPECT_LT(100.0 * (double)seen_max / (double)(512 * 1024), 1.0);
}

struct CountingAllocationDeleter {
  size_t count = 0;
  void operator()(long *p) const {
    CountingAllocator<long, NM_METHOD_MAP>().deallocate(p, count);
  }
};

// Check exact totals after each allocation and each partial release, rather
// than only requiring a nonzero gauge that could still be undercounting.
TEST_F(MallocFootprintTest, CountingAllocatorTracksOverheadSeparately) {
  const size_t counts[] = {1, 4, 12, 13, 768, 65536, 262144};
  const size_t count = sizeof(counts) / sizeof(counts[0]);
  std::unique_ptr<long, CountingAllocationDeleter> ptrs[count];
  long long live = 0, overhead = 0;
  for (size_t i = 0; i < count; i++) {
    const size_t bytes = counts[i] * sizeof(long);
    ptrs[i].get_deleter().count = counts[i];
    ptrs[i].reset(CountingAllocator<long, NM_METHOD_MAP>().allocate(counts[i]));
    live += bytes;
    overhead += expectedFootprint(ptrs[i].get(), bytes) - bytes;
    EXPECT_EQ(live, NativeMem::live(NM_METHOD_MAP));
    EXPECT_EQ(overhead, NativeMem::overhead(NM_METHOD_MAP));
  }
  for (size_t i = count; i-- > 0;) {
    const size_t bytes = counts[i] * sizeof(long);
    live -= bytes;
    overhead -= expectedFootprint(ptrs[i].get(), bytes) - bytes;
    ptrs[i].reset();
    EXPECT_EQ(live, NativeMem::live(NM_METHOD_MAP));
    EXPECT_EQ(overhead, NativeMem::overhead(NM_METHOD_MAP));
  }
}

struct MapAllocationTotals {
  long long live = 0;
  long long overhead = 0;
  size_t allocations = 0;
  size_t frees = 0;
};

// Observe the actual node pointers and sizes after std::map rebinds its
// allocator. Delegate allocation and accounting to the production allocator;
// the expected totals use the allocator API, never NativeMem's gauges.
template <typename T>
struct ObservedCountingAllocator : CountingAllocator<T, NM_METHOD_MAP> {
  using value_type = T;
  MapAllocationTotals *totals;

  explicit ObservedCountingAllocator(MapAllocationTotals &totals) : totals(&totals) {}

  template <typename U>
  ObservedCountingAllocator(const ObservedCountingAllocator<U> &other)
      : CountingAllocator<T, NM_METHOD_MAP>(
            static_cast<const CountingAllocator<U, NM_METHOD_MAP> &>(other)),
        totals(other.totals) {}

  T *allocate(size_t n) {
    T *p = CountingAllocator<T, NM_METHOD_MAP>::allocate(n);
    const size_t requested = n * sizeof(T);
    totals->live += requested;
    totals->overhead += expectedFootprint(p, requested) - requested;
    totals->allocations++;
    return p;
  }

  void deallocate(T *p, size_t n) noexcept {
    const size_t requested = n * sizeof(T);
    const size_t overhead = expectedFootprint(p, requested) - requested;
    CountingAllocator<T, NM_METHOD_MAP>::deallocate(p, n);
    totals->live -= requested;
    totals->overhead -= overhead;
    totals->frees++;
  }

  template <typename U>
  struct rebind {
    using ReboundAllocator = typename CountingAllocator<T, NM_METHOD_MAP>::template rebind<U>::other;
    using other = ObservedCountingAllocator<typename ReboundAllocator::value_type>;
  };

  template <typename U>
  bool operator==(const ObservedCountingAllocator<U> &other) const noexcept {
    return totals == other.totals;
  }

  template <typename U>
  bool operator!=(const ObservedCountingAllocator<U> &other) const noexcept {
    return !(*this == other);
  }
};

TEST_F(MallocFootprintTest, MapNodesTrackOverheadAcrossRebindingAndDestruction) {
  MapAllocationTotals totals;
  using Allocator = ObservedCountingAllocator<std::pair<const long, long>>;
  using Map = std::map<long, long, std::less<long>, Allocator>;
  {
    Map m{std::less<long>(), Allocator(totals)};
    for (long i = 0; i < 2000; i++) {
      m[i * 7919] = i;
      EXPECT_EQ(totals.live, NativeMem::live(NM_METHOD_MAP));
      EXPECT_EQ(totals.overhead, NativeMem::overhead(NM_METHOD_MAP));
    }
    EXPECT_EQ(2000u, m.size());
    EXPECT_GE(totals.allocations, m.size());
    EXPECT_GT(totals.live, 0);
    // Check partial releases before letting the destructor free the remaining
    // nodes. Zero observed overhead is valid when the allocator exposes none.
    for (long i = 0; i < 2000; i += 2) {
      EXPECT_EQ(1u, m.erase(i * 7919));
      EXPECT_EQ(totals.live, NativeMem::live(NM_METHOD_MAP));
      EXPECT_EQ(totals.overhead, NativeMem::overhead(NM_METHOD_MAP));
    }
    EXPECT_EQ(1000u, m.size());
    EXPECT_GT(totals.frees, 0u);
  }
  EXPECT_EQ(totals.allocations, totals.frees);
  EXPECT_EQ(0, totals.live);
  EXPECT_EQ(0, totals.overhead);
  EXPECT_EQ(0, NativeMem::live(NM_METHOD_MAP));
  EXPECT_EQ(0, NativeMem::overhead(NM_METHOD_MAP));
}

struct RecordedAllocationDeleter {
  size_t requested = 0;
  void operator()(void *p) const {
    NativeMem::recordFreeBefore(NM_MISC, p, requested);
    free(p);
  }
};

// Retain many differently sized allocations so both usable-size rounding and
// per-allocation header contributions accumulate into the accounting oracle.
TEST_F(MallocFootprintTest, RecordAllocAndFreeBalance) {
  std::unique_ptr<void, RecordedAllocationDeleter> ptrs[500];
  long long live = 0, overhead = 0;
  for (size_t i = 0; i < 500; i++) {
    const size_t size = 33 + i % 100;
    ptrs[i].get_deleter().requested = size;
    ptrs[i].reset(malloc(size));
    ASSERT_NE(nullptr, ptrs[i]);
    NativeMem::recordAlloc(NM_MISC, ptrs[i].get(), size);
    live += size;
    overhead += expectedFootprint(ptrs[i].get(), size) - size;
    EXPECT_EQ(live, NativeMem::live(NM_MISC));
    EXPECT_EQ(overhead, NativeMem::overhead(NM_MISC));
  }
  // Release alternating allocations first to check partially populated totals.
  for (size_t parity = 0; parity < 2; parity++) {
    for (size_t i = parity; i < 500; i += 2) {
      const size_t size = ptrs[i].get_deleter().requested;
      live -= size;
      overhead -= expectedFootprint(ptrs[i].get(), size) - size;
      ptrs[i].reset();
      EXPECT_EQ(live, NativeMem::live(NM_MISC));
      EXPECT_EQ(overhead, NativeMem::overhead(NM_MISC));
    }
  }
}
