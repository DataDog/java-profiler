// Copyright 2026, Datadog, Inc.

#include "common.h"  // ASAN_ENABLED (toolchain-agnostic sanitizer detection)

#include "gtest/gtest.h"
#include "linearAllocator.h"
#include "nativeMem.h"

#ifdef ASAN_ENABLED
#include <sanitizer/asan_interface.h>

// The stale-after-clear partial-granule miss: ASan's shadow granularity is 8
// bytes, so an allocation ending mid-granule leaves its final granule
// partially addressable. clear() then cannot fully poison the tail, and a
// stale access to the allocation's last bytes reads as addressable shadow.
// alloc() rounds every bump to the granule in ASan builds, so every byte of
// every former allocation must read as poisoned after clear().
// These tests compile only in ASan builds; in other configurations the file
// contributes no tests.

static const size_t CHUNK_SIZE = 64 * 1024;

class LinearAllocatorAsanPoisonTest : public ::testing::Test {
protected:
  // Static-duration objects elsewhere in the binary record into these same
  // categories before main() runs; restore their baseline in TearDown so
  // their destructors don't underflow a category this fixture zeroed.
  // (Same rationale as LinearAllocatorNativeMemTest in
  // linearAllocator_nativemem_ut.cpp.)
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

TEST_F(LinearAllocatorAsanPoisonTest, StaleTailOfUnalignedAllocationIsPoisonedAfterClear) {
  LinearAllocator allocator(CHUNK_SIZE);
  // 26 bytes: end offset is not 8-aligned -- the shape that hid stale tails
  // before rounding. A separator allocation makes the first chunk's used
  // range end mid-granule too.
  char *first = (char *)allocator.alloc(26);
  char *separator = (char *)allocator.alloc(1);
  ASSERT_NE(nullptr, first);
  ASSERT_NE(nullptr, separator);

  allocator.clear();

  EXPECT_TRUE(__asan_address_is_poisoned(first))
      << "the first byte of a former allocation must read as poisoned";
  EXPECT_TRUE(__asan_address_is_poisoned(first + 25))
      << "the last byte of an unaligned allocation must read as poisoned -- "
         "the partial-granule shadow tail is closed by granule rounding";
}

TEST_F(LinearAllocatorAsanPoisonTest, AllocatedRegionIsAddressableAndAligned) {
  LinearAllocator allocator(CHUNK_SIZE);
  char *p = (char *)allocator.alloc(26);
  ASSERT_NE(nullptr, p);

  // The granule-aligned offset invariant clear()'s whole-granule poison
  // relies on: every returned pointer is 8-aligned.
  EXPECT_EQ(0, (uintptr_t)p % 8) << "alloc() must hand out 8-aligned pointers in ASan builds";

  for (size_t i = 0; i < 26; i++) {
    EXPECT_FALSE(__asan_address_is_poisoned(p + i))
        << "byte " << i << " of a live allocation must be addressable";
  }
  // Write-read proves addressability end to end, not just shadow state.
  p[0] = 1;
  p[25] = 2;
  EXPECT_EQ(1, p[0]);
  EXPECT_EQ(2, p[25]);
}

TEST_F(LinearAllocatorAsanPoisonTest, RoundedAccountingStaysSymmetric) {
  // alloc() records the rounded size so the ledger matches the offs-based
  // decrements in clear() and freeChunks(). Two 26-byte allocations consume
  // 2 * 32 bytes; the accounting must be exact, not approximate.
  LinearAllocator allocator(CHUNK_SIZE);
  ASSERT_NE(nullptr, allocator.alloc(26));
  ASSERT_NE(nullptr, allocator.alloc(26));
  EXPECT_EQ(64, NativeMem::live(NM_CALLTRACE))
      << "ASan builds count granule-rounded bytes (2 x 26 -> 2 x 32)";

  ChunkList detached = allocator.detachChunks();
  EXPECT_EQ(64, NativeMem::live(NM_CALLTRACE))
      << "detaching frees nothing";
  LinearAllocator::freeChunks(detached);
  EXPECT_EQ(0, NativeMem::live(NM_CALLTRACE))
      << "freeChunks() un-records exactly the rounded bytes alloc() recorded";
}

TEST_F(LinearAllocatorAsanPoisonTest, ReuseAfterClearIsUnpoisoned) {
  // clear() leaves poison for use-after-clear detection; a fresh allocation
  // over the same region must be fully addressable again (no false positive
  // on reuse).
  LinearAllocator allocator(CHUNK_SIZE);
  char *first = (char *)allocator.alloc(26);
  ASSERT_NE(nullptr, first);
  allocator.clear();

  char *second = (char *)allocator.alloc(32);
  ASSERT_NE(nullptr, second);
  EXPECT_EQ(0, (uintptr_t)second % 8);
  for (size_t i = 0; i < 32; i++) {
    EXPECT_FALSE(__asan_address_is_poisoned(second + i))
        << "byte " << i << " of a reallocated region must be addressable";
  }
  second[0] = 7;
  second[31] = 9;
  EXPECT_EQ(7, second[0]);
  EXPECT_EQ(9, second[31]);
}

#endif // ASAN_ENABLED

#ifndef ASAN_ENABLED
// The TU must reference the gtest runtime in every configuration: GNU ld
// resolves libgtest.a members left-to-right, so an empty TU leaves
// gtest_main.o's own testing:: references undefined.
TEST(LinearAllocatorAsanPoison, RequiresAsanBuild) {
  GTEST_SKIP() << "granule rounding is compiled only in ASan builds";
}
#endif
