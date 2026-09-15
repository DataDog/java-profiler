/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstdlib>
#include <vector>

#if defined(__linux__) && defined(__GLIBC__) &&                                \
    (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 33))
  #include <malloc.h>
  #define DD_HAVE_MALLINFO2 1
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

#ifdef DD_HAVE_MALLINFO2

static const size_t SBTABLE_SIZE = 6144;   // sizeof(SBTable), measured
static const int    FLUSH_BLOCKS = 26450;  // allocations in one observed flush

// Churn alone does NOT strand memory. 26,450 blocks allocated contiguously and
// then all freed coalesce into one large free region at the arena top, which
// glibc returns to the OS -- measured: arena 163 MB back down to 905 KB. So a
// flush burst is not, by itself, an explanation for retained memory. The next
// test shows what is actually required.
TEST(MallocArenaStats, ContiguousChurnIsReturnedToTheOS) {
  {
    std::vector<void *> warm;
    for (int i = 0; i < 1000; i++) warm.push_back(malloc(SBTABLE_SIZE));
    for (void *p : warm) free(p);
  }

  struct mallinfo2 before = mallinfo2();

  std::vector<void *> blocks;
  blocks.reserve(FLUSH_BLOCKS);
  for (int i = 0; i < FLUSH_BLOCKS; i++) {
    void *p = malloc(SBTABLE_SIZE);
    ASSERT_NE(nullptr, p);
    *(volatile char *)p = 1;  // touch it, as the real code would
    blocks.push_back(p);
  }
  struct mallinfo2 peak = mallinfo2();
  for (void *p : blocks) free(p);
  struct mallinfo2 after = mallinfo2();

  EXPECT_GE(peak.uordblks - before.uordblks,
            (size_t)FLUSH_BLOCKS * SBTABLE_SIZE)
      << "in-use accounting did not reflect the held blocks";
  EXPECT_LT(after.uordblks, peak.uordblks);

  // The arena shrinks back: the coalesced free region is returned, so this
  // pattern leaves nothing meaningful in the free-but-held term.
  EXPECT_LT((long long)after.arena, (long long)peak.arena / 2)
      << "expected the coalesced top region to be returned to the OS";

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
  std::vector<void *> survivors, churn;
  for (int i = 0; i < 20000; i++) {
    void *a = malloc(SBTABLE_SIZE);
    void *b = malloc(SBTABLE_SIZE);
    ASSERT_NE(nullptr, a);
    ASSERT_NE(nullptr, b);
    *(volatile char *)a = 1;
    *(volatile char *)b = 1;
    survivors.push_back(a);   // kept live, so it pins the region
    churn.push_back(b);       // freed below
  }
  for (void *p : churn) free(p);

  struct mallinfo2 pre_trim = mallinfo2();
  malloc_trim(0);
  struct mallinfo2 post_trim = mallinfo2();

  EXPECT_GT(post_trim.fordblks, 0u)
      << "trim reclaimed everything; interleaving failed to strand chunks";

  printf("[TRIM] free_held before trim: %.2f MiB, after trim: %.2f MiB "
         "(reclaimed %.2f MiB)\n",
         (double)pre_trim.fordblks / (1024 * 1024),
         (double)post_trim.fordblks / (1024 * 1024),
         (double)((long long)pre_trim.fordblks - (long long)post_trim.fordblks) /
             (1024 * 1024));

  for (void *p : survivors) free(p);
}

#else

TEST(MallocArenaStats, SkippedWithoutMallinfo2) {
  GTEST_SKIP() << "mallinfo2 requires glibc 2.33+; arena counters report zero "
                  "on this platform";
}

#endif
