/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <vector>

#include "flightRecorder.h"
#include "mallocInfo.h"

// malloc_trim is a glibc extension: musl also defines __linux__, but its
// <malloc.h> does not declare malloc_trim, so the guard must be __GLIBC__.
// __GLIBC__ comes from <features.h>, included explicitly so the guard does not
// depend on another header pulling it in transitively. Gtest musl builds always
// pass -D__musl__ (GtestTaskBuilder), so the #error fires only when a Linux
// build has lost __GLIBC__ (e.g. the features.h include was removed or moved
// below the guard), instead of silently compiling trimArenas() to a no-op.
#if defined(__linux__)
  #include <features.h> // defines __GLIBC__ on glibc; present on musl too
#endif
#if defined(__GLIBC__)
  #include <malloc.h> // malloc_trim
#elif defined(__linux__) && !defined(__musl__)
  #error "Linux libc is neither glibc (__GLIBC__) nor musl (-D__musl__); fix the malloc_trim guard"
#endif

// Friend of Recording (see flightRecorder.h), giving this test access to the
// private glibcMallocActive() helper. Same pattern as
// VMTestAccessor/ProfilerTestAccessor used elsewhere in this test suite.
class RecordingTestAccessor {
public:
  static bool glibcMallocActive() { return Recording::glibcMallocActive(); }
};

// Regression test for a review finding on the arena counters: LD_PRELOAD'ing
// tcmalloc or jemalloc replaces malloc()/free() process-wide while leaving
// __GLIBC__ defined (it comes from features.h, not from which allocator is
// actually linked), so mallinfo2() would otherwise keep reporting glibc's own
// idle arena during exactly the allocator-comparison runs
// (.gitlab/reliability's ALLOCATOR=jemalloc/tcmalloc matrix) where that is
// wrong. Detection must therefore key off a symbol each replacement actually
// exports, not off __GLIBC__.
//
// The gtest configurations cover both outcomes. ASan/TSan builds run under
// the sanitizer's own allocator, whose mallinfo2() interceptor reports all
// zeros, so detection must report glibc inactive there. Plain builds run on
// glibc malloc, so detection must report it active -- which also guards
// against probing for a symbol that something already linked into every
// gtest binary defines, which would silently disable the counters everywhere.
//
// The LD_PRELOAD'd jemalloc/tcmalloc case is not simulated here: gtest
// executables are not linked with --export-dynamic, so a symbol this test
// defined itself would not be visible to dlsym(RTLD_DEFAULT, ...). That case
// runs in .gitlab/reliability's ALLOCATOR=jemalloc/tcmalloc CI matrix, where
// mallctl()/tc_malloc_size() come from an actually preloaded shared object.
#if defined(ASAN_ENABLED) || defined(TSAN_ENABLED)
TEST(GlibcMallocActive, ReportsInactiveUnderSanitizerAllocator) {
  EXPECT_FALSE(RecordingTestAccessor::glibcMallocActive());
}
#else
TEST(GlibcMallocActive, ReportsActiveWithNoReplacementAllocatorLoaded) {
  EXPECT_EQ(nullptr, dlsym(RTLD_DEFAULT, "mallctl"));
  EXPECT_EQ(nullptr, dlsym(RTLD_DEFAULT, "tc_malloc_size"));
  EXPECT_TRUE(RecordingTestAccessor::glibcMallocActive());
}
#endif

// These tests validate the *premise* of the MALLOC_FREE_HELD_BYTES counter
// rather than its plumbing: that allocation churn of the shape the profiler
// actually produces leaves memory stranded inside glibc's arenas, retained
// rather than returned to the OS.
//
// The shape is taken from a measured JFR chunk flush:
// StringDictionaryBuffer::insert_with_id allocates 26,450 blocks of exactly
// 6,144 bytes (sizeof(SBTable)) during a single flush, then frees them. If that
// churn strands a significant number of free chunks, it is a candidate
// explanation for memory the profiler's own per-category counters cannot see --
// and, crucially, it is process-wide allocator behaviour rather than profiler
// memory, which is why it is reported as a separate counter and not as an NM_*
// category (see nativeMem.h).
//
// The tests run against the same runtime-resolved mallinfo2 path the
// production code uses (mallocArenaSnapshot, see mallocInfo.h) -- they are
// never compiled out by header versions: on a runtime without mallinfo2
// (glibc < 2.33, musl, macOS) they skip, mirroring the counters staying unset.

static const size_t SBTABLE_SIZE = 6144;   // sizeof(SBTable), measured
static const int    FLUSH_BLOCKS = 26450;  // allocations in one observed flush
// Above glibc's dynamic mmap-threshold cap (DEFAULT_MMAP_THRESHOLD_MAX, 32 MiB
// on LP64), so it is always mmap-served and freeing it does not raise the
// threshold. Also well above anything the churn tests can leave free in the
// arena, so it cannot be carved from bins/top instead.
static const size_t MMAPPED_BLOCK = (size_t)256 << 20;

// These premises are about glibc's arena. Under any other allocator the
// churn below never reaches it, so there is nothing to measure.
#define SKIP_UNLESS_GLIBC_MALLOC()                                             \
  if (!RecordingTestAccessor::glibcMallocActive()) {                           \
    GTEST_SKIP() << "glibc malloc is not the allocator in force";              \
  }

#define SKIP_UNLESS_MALLINFO2(out)                                             \
  if (!mallocArenaSnapshot(out)) {                                             \
    GTEST_SKIP() << "mallinfo2 not available at runtime; arena counters "      \
                    "stay unset on this platform";                             \
  }

// malloc_trim is a glibc extension and compiles only on glibc; elsewhere this
// returns false without trimming. It is only reached after
// SKIP_UNLESS_GLIBC_MALLOC and the mallinfo2 probe, i.e. on a glibc >= 2.33
// runtime, so a false return there means the __GLIBC__ guard regressed.
static bool trimArenas() {
#if defined(__GLIBC__)
  malloc_trim(0);
  return true;
#else
  return false;
#endif
}

// Frees every block still held in the vector when the test body exits by any
// path (GTEST_SKIP / ASSERT_* early returns included), so a failing or skipped
// test does not leak 100+ MiB into the rest of the gtest process. Explicit
// free loops that must run at a measured point are followed by .clear().
struct FreeAllOnExit {
  explicit FreeAllOnExit(std::vector<void *> &v) : v_(v) {}
  ~FreeAllOnExit() {
    for (void *p : v_) free(p);
    v_.clear();
  }
  FreeAllOnExit(const FreeAllOnExit &) = delete;
  FreeAllOnExit &operator=(const FreeAllOnExit &) = delete;
  std::vector<void *> &v_;
};

// Pre-fills every field with 0xFF so a field the snapshot fails to copy reads
// SIZE_MAX instead of whatever was on the stack.
static bool sentinelSnapshot(MallocArenaInfo *out) {
  memset(out, 0xFF, sizeof *out);
  return mallocArenaSnapshot(out);
}

// glibc int_mallinfo(): per arena, under that arena's lock, fordblks += avail,
// uordblks += system_mem - avail and arena += system_mem, so
// arena == uordblks + fordblks holds exactly within ONE snapshot, even with
// concurrent allocation. keepcost is chunksize(main_arena.top), which is part
// of the main arena's avail, so keepcost <= fordblks. Together these pin each
// copied field to its glibc meaning: a swapped or dropped copy of
// arena/uordblks/fordblks/keepcost breaks one of them.
static void expectMallinfoInvariants(const MallocArenaInfo &s, const char *where) {
  EXPECT_EQ(s.arena, s.uordblks + s.fordblks) << where << ": arena != in_use + free_held";
  EXPECT_LE(s.keepcost, s.fordblks) << where << ": trimmable top exceeds free_held";
  EXPECT_GT(s.arena, 0u) << where;
  EXPECT_GT(s.uordblks, 0u) << where;
}

TEST(MallocArenaStats, SnapshotFieldsSatisfyGlibcAccountingIdentity) {
  SKIP_UNLESS_GLIBC_MALLOC();
  MallocArenaInfo s;
  if (!sentinelSnapshot(&s)) {
    GTEST_SKIP() << "mallinfo2 not available at runtime";
  }
  expectMallinfoInvariants(s, "idle");
}

// Churn alone does NOT strand memory. 26,450 blocks allocated contiguously and
// then all freed coalesce into one large free region at the arena top, which
// glibc returns to the OS -- measured: arena 163 MB back down to 905 KB. So a
// flush burst is not, by itself, an explanation for retained memory. The next
// test shows what is actually required.
TEST(MallocArenaStats, ContiguousChurnIsReturnedToTheOS) {
  SKIP_UNLESS_GLIBC_MALLOC();
  {
    std::vector<void *> warm;
    for (int i = 0; i < 1000; i++) warm.push_back(malloc(SBTABLE_SIZE));
    for (void *p : warm) free(p);
  }

  MallocArenaInfo before, peak, after;
  SKIP_UNLESS_MALLINFO2(&before);

  std::vector<void *> blocks;
  blocks.reserve(FLUSH_BLOCKS);
  FreeAllOnExit free_blocks(blocks);
  for (int i = 0; i < FLUSH_BLOCKS; i++) {
    void *p = malloc(SBTABLE_SIZE);
    blocks.push_back(p);      // owned before asserting, so a failure frees it
    ASSERT_NE(nullptr, p);
    *(volatile char *)p = 1;  // touch it, as the real code would
  }
  ASSERT_TRUE(sentinelSnapshot(&peak));
  for (void *p : blocks) free(p);
  blocks.clear();             // already freed; keep the guard from double-freeing
  ASSERT_TRUE(sentinelSnapshot(&after));

  // The deltas are signed on purpose: an unsigned wrap let a uordblks<->fordblks
  // copy swap pass. Under that swap the alloc-side delta becomes the fordblks
  // change between before and peak -- at most a few hundred KiB (top pad plus
  // fresh top), far below the ~155 MiB held -- and the free-side delta may even
  // go negative if the trim threshold is raised. Do not "fix" the sign.
  EXPECT_GE((long long)peak.uordblks - (long long)before.uordblks,
            (long long)FLUSH_BLOCKS * (long long)SBTABLE_SIZE)
      << "in-use accounting did not reflect the held blocks";
  EXPECT_GE((long long)peak.uordblks - (long long)after.uordblks,
            (long long)FLUSH_BLOCKS * (long long)SBTABLE_SIZE)
      << "freeing the held blocks did not drop in-use accounting";
  EXPECT_LT(after.uordblks, peak.uordblks);

  // The arena shrinks back: the coalesced free region is returned, so this
  // pattern leaves nothing meaningful in the free-but-held term.
  EXPECT_LT((long long)after.arena, (long long)peak.arena / 2)
      << "expected the coalesced top region to be returned to the OS";
  expectMallinfoInvariants(peak, "peak");
  expectMallinfoInvariants(after, "after");

  printf("[ARENA] before: arena=%zu in_use=%zu free_held=%zu trimmable=%zu\n",
         before.arena, before.uordblks, before.fordblks, before.keepcost);
  printf("[ARENA] peak:   arena=%zu in_use=%zu free_held=%zu trimmable=%zu\n",
         peak.arena, peak.uordblks, peak.fordblks, peak.keepcost);
  printf("[ARENA] after:  arena=%zu in_use=%zu free_held=%zu trimmable=%zu\n",
         after.arena, after.uordblks, after.fordblks, after.keepcost);
  printf("[ARENA] free_held change: %+.2f MiB (signed)\n",
         (double)((long long)after.fordblks - (long long)before.fordblks) /
             (1024 * 1024));
}

// Stranding requires LIVE allocations interleaved among the freed ones: they pin
// the region so the free chunks cannot coalesce to the top and be returned.
// Measured here: 117.5 MiB retained, of which malloc_trim reclaims 0.03 MiB.
//
// This is why the counter separates `keepcost` (the trimmable top block) from
// total free-but-held, and why arena slack is a property of the whole process's
// allocation *pattern* rather than of any one subsystem's allocations.
TEST(MallocArenaStats, InterleavedSurvivorsStrandFreeChunksBeyondTrim) {
  SKIP_UNLESS_GLIBC_MALLOC();
  // Probe before allocating anything, so a skip cannot strand the survivors.
  // Scratch only: the measurement must be taken after the churn is freed.
  MallocArenaInfo probe;
  SKIP_UNLESS_MALLINFO2(&probe);

  std::vector<void *> survivors, churn;
  FreeAllOnExit free_survivors(survivors);
  FreeAllOnExit free_churn(churn);
  for (int i = 0; i < 20000; i++) {
    void *a = malloc(SBTABLE_SIZE);
    void *b = malloc(SBTABLE_SIZE);
    survivors.push_back(a);   // kept live, so it pins the region
    churn.push_back(b);       // freed below
    ASSERT_NE(nullptr, a);
    ASSERT_NE(nullptr, b);
    *(volatile char *)a = 1;
    *(volatile char *)b = 1;
  }
  for (void *p : churn) free(p);
  churn.clear();              // already freed; keep the guard from double-freeing

  MallocArenaInfo pre_trim, post_trim;
  ASSERT_TRUE(sentinelSnapshot(&pre_trim));
  ASSERT_TRUE(trimArenas())
      << "malloc_trim not compiled in although glibc malloc with mallinfo2 is "
         "active; the __GLIBC__ guard regressed";
  ASSERT_TRUE(sentinelSnapshot(&post_trim));

  EXPECT_GT(post_trim.fordblks, 0u)
      << "trim reclaimed everything; interleaving failed to strand chunks";

  // keepcost is the main arena's top chunk. malloc_trim(0) shrinks that top to
  // about a page and never grows it, while the interleaved free chunks stay
  // stranded in the bins (counted in fordblks, not in keepcost).
  EXPECT_LE(post_trim.keepcost, pre_trim.keepcost)
      << "malloc_trim grew the trimmable top";
  EXPECT_LT(post_trim.keepcost, post_trim.fordblks)
      << "trimmable top must be a strict part of the stranded free_held";
  EXPECT_LT(post_trim.keepcost, (size_t)1 << 20)
      << "malloc_trim left more than ~a page in the main arena's top";
  expectMallinfoInvariants(pre_trim, "pre_trim");
  expectMallinfoInvariants(post_trim, "post_trim");

  printf("[TRIM] free_held before trim: %.2f MiB, after trim: %.2f MiB "
         "(reclaimed %.2f MiB)\n",
         (double)pre_trim.fordblks / (1024 * 1024),
         (double)post_trim.fordblks / (1024 * 1024),
         (double)((long long)pre_trim.fordblks - (long long)post_trim.fordblks) /
             (1024 * 1024));
  printf("[TRIM] trimmable before trim: %zu, after trim: %zu\n",
         pre_trim.keepcost, post_trim.keepcost);
  // survivors are freed by free_survivors at scope exit, after every check.
}

// A request above the mmap-threshold cap is served by its own mapping: glibc
// accounts it in mp_.mmapped_mem (hblkhd) and nowhere in the arenas. The deltas
// are signed so an unsigned wrap can never satisfy >=; a dropped hblkhd copy
// reads the SIZE_MAX sentinel (-1 as long long) in every snapshot, delta 0.
TEST(MallocArenaStats, MmappedChunkIsReportedInHblkhdOnly) {
  SKIP_UNLESS_GLIBC_MALLOC();
  MallocArenaInfo before, held, released;
  if (!sentinelSnapshot(&before)) {
    GTEST_SKIP() << "mallinfo2 not available at runtime";
  }
  void *big = malloc(MMAPPED_BLOCK);
  if (big == nullptr) {
    GTEST_SKIP() << "could not allocate the mmapped test block";
  }
  // Touch the chunk through a volatile pointer: an untouched malloc/free pair
  // whose result never escapes is eliminated by the optimizer in release
  // builds (-O2), so the allocation never happens and hblkhd never moves.
  // The volatile write makes the allocation observable.
  *(volatile char *)big = 1;
  bool held_ok = sentinelSnapshot(&held);
  free(big);  // before any ASSERT, so no exit path leaks the mapping
  ASSERT_TRUE(held_ok);
  ASSERT_TRUE(sentinelSnapshot(&released));

  EXPECT_GE((long long)held.hblkhd - (long long)before.hblkhd,
            (long long)MMAPPED_BLOCK)
      << "mmapped chunk not reflected in hblkhd";
  EXPECT_LT((long long)held.uordblks - (long long)before.uordblks,
            (long long)(MMAPPED_BLOCK / 2))
      << "mmapped chunk leaked into in-use arena accounting";
  EXPECT_LT((long long)held.arena - (long long)before.arena,
            (long long)(MMAPPED_BLOCK / 2))
      << "mmapped chunk leaked into arena system memory";
  EXPECT_GE((long long)held.hblkhd - (long long)released.hblkhd,
            (long long)MMAPPED_BLOCK)
      << "freeing the mmapped chunk did not lower hblkhd";
  expectMallinfoInvariants(held, "held");
}
