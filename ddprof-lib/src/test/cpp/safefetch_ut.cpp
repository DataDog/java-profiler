/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <climits>
#include <cstring>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "safeAccess.h"
#include "os.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Test name for crash handler
static constexpr char SAFEFETCH_TEST_NAME[] = "SafeFetchTest";


static void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
static void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);


void signal_handle_wrapper(int signo, siginfo_t* siginfo, void* context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (signo == SIGBUS && orig_busHandler != nullptr) {
       orig_busHandler(signo, siginfo, context);
    } else if (signo == SIGSEGV && orig_segvHandler != nullptr) {
       orig_segvHandler(signo, siginfo, context);
    } else {
       // If no original handler, use crash handler for debugging
       gtestCrashHandler(signo, siginfo, context, SAFEFETCH_TEST_NAME);
    }
  }
}

class SafeFetchTest : public ::testing::Test {
protected:
    void SetUp() override {
       orig_segvHandler = OS::replaceSigsegvHandler(signal_handle_wrapper);
       orig_busHandler = OS::replaceSigbusHandler(signal_handle_wrapper);
    }

    void TearDown() override {
       OS::replaceSigsegvHandler(orig_segvHandler);
       OS::replaceSigbusHandler(orig_busHandler);
    }
};


TEST_F(SafeFetchTest, validAccess32) {
  int i = 42;
  int* p = &i;
  int res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, i);
  i = INT_MAX;
  res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, i);
  i = INT_MIN;
  res = SafeAccess::safeFetch32(p, 0);
  EXPECT_EQ(res, i);
}


TEST_F(SafeFetchTest, invalidAccess32) {
  int* p = nullptr;
  int res = SafeAccess::safeFetch32(p, -1);
  EXPECT_EQ(res, -1);
  res = SafeAccess::safeFetch32(p, -2);
  EXPECT_EQ(res, -2);
}

TEST_F(SafeFetchTest, validAccess64) {
  int64_t i = 42;
  int64_t* p = &i;
  int64_t res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, i);
  i = LONG_MIN;
  res = SafeAccess::safeFetch64(p, -19);
  EXPECT_EQ(res, i);
  i = LONG_MAX;
  res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, i);
}

TEST_F(SafeFetchTest, invalidAccess64) {
  int64_t* p = nullptr;
  int64_t res = SafeAccess::safeFetch64(p, -1);
  EXPECT_EQ(res, -1);
  res = SafeAccess::safeFetch64(p, -2);
  EXPECT_EQ(res, -2);
}

TEST_F(SafeFetchTest, validAccessPtr) {
  char c = 'a';
  void* p = (void*)&c;
  void** pp = &p;
  void* res = SafeAccess::loadPtr(pp, nullptr);
  EXPECT_EQ(res, p);
}

TEST_F(SafeFetchTest, invalidAccessPtr) {
  int a, b;
  void* ap = (void*)&a;
  void* bp = (void*)&b;
  void** pp = nullptr;
  void* res = SafeAccess::loadPtr(pp, ap);
  EXPECT_EQ(res, ap);
  res = SafeAccess::loadPtr(pp, bp);
  EXPECT_EQ(res, bp);
}

TEST_F(SafeFetchTest, isReadable) {
  char c = 'x';
  EXPECT_TRUE(SafeAccess::isReadable(&c));
  EXPECT_FALSE(SafeAccess::isReadable(nullptr));
}

/**
 * Tests that safeFetch32 correctly handles mprotected memory.
 *
 * This test simulates the musl-specific memory layout where certain memory
 * regions are protected. Without the NOINLINE fix, the compiler may inline
 * the load under -O3, causing faults to occur at the wrong PC and bypassing
 * the safefetch fault handler.
 *
 * Expected behavior:
 * - With NOINLINE fix: Returns error value (-999)
 * - Without NOINLINE fix under -O3: Crashes
 */
TEST_F(SafeFetchTest, mprotectedMemory32) {
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  int* ptr = static_cast<int*>(page);
  *ptr = 0xDEADBEEF;
  ASSERT_EQ(mprotect(page, 4096, PROT_NONE), 0);

  // This MUST return error value, not crash
  int result = SafeAccess::safeFetch32(ptr, -999);
  EXPECT_EQ(result, -999);

  munmap(page, 4096);
}

/**
 * Tests that safeFetch64 correctly handles mprotected memory.
 * Same rationale as mprotectedMemory32 above.
 */
TEST_F(SafeFetchTest, mprotectedMemory64) {
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  int64_t* ptr = static_cast<int64_t*>(page);
  *ptr = 0xDEADBEEFCAFEBABE;
  ASSERT_EQ(mprotect(page, 4096, PROT_NONE), 0);

  int64_t result = SafeAccess::safeFetch64(ptr, -999);
  EXPECT_EQ(result, -999);

  munmap(page, 4096);
}

// ---------------------------------------------------------------------------
// SafeAccess::safeCopy — bulk variant of safeFetch{32,64} that copies a byte
// range via the safecopy_impl assembly stub (byte-granular loads guarded by
// handle_safefetch). Must:
//   - return true and copy the bytes exactly when src is fully readable,
//     including when [src, src+len) sits within a few bytes of an unmapped
//     page boundary (byte-granular reads never over-read past src+len)
//   - return false (no crash) when the requested range itself crosses into
//     an unmapped page
//   - handle unaligned src (no alignment requirement on src)
//   - never write past dst[len-1] regardless of len
//   - copy real data faithfully regardless of its byte values
// ---------------------------------------------------------------------------

TEST_F(SafeFetchTest, safeCopy_happyPath) {
  const char src[] = "java/lang/Object";
  char dst[sizeof(src)] = {0};
  EXPECT_TRUE(SafeAccess::safeCopy(dst, src, sizeof(src) - 1));
  EXPECT_EQ(0, memcmp(dst, src, sizeof(src) - 1));
}

TEST_F(SafeFetchTest, safeCopy_zeroLength) {
  // Even if src is NULL, len=0 must be a no-op success.
  char dst[8] = {0};
  EXPECT_TRUE(SafeAccess::safeCopy(dst, nullptr, 0));
}

TEST_F(SafeFetchTest, safeCopy_shortLength_doesNotOverwriteDst) {
  // The copy must not write beyond len bytes into dst.
  const char src[] = "AB";
  char dst[8];
  memset(dst, 0x5A, sizeof(dst));
  EXPECT_TRUE(SafeAccess::safeCopy(dst, src, 2));
  EXPECT_EQ('A', dst[0]);
  EXPECT_EQ('B', dst[1]);
  // Sentinel bytes 2..7 must be untouched.
  for (int i = 2; i < 8; i++) {
    EXPECT_EQ((char)0x5A, dst[i]) << "dst[" << i << "] was overwritten";
  }
}

TEST_F(SafeFetchTest, safeCopy_unmappedSource_returnsFalse) {
  // Map a page, then unmap it: the address is now firmly invalid. safeCopy
  // must return false rather than SIGSEGV.
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);
  ASSERT_EQ(0, munmap(page, 4096));

  char dst[64] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, page, 32));
}

TEST_F(SafeFetchTest, safeCopy_protNoneSource_returnsFalse) {
  // mprotect-PROT_NONE the page (similar to mprotectedMemory32). safeCopy
  // must return false on the first faulting word, not crash.
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);
  memcpy(page, "ignored", 7);
  ASSERT_EQ(0, mprotect(page, 4096, PROT_NONE));

  char dst[64] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, page, 32));

  // Restore so munmap can run cleanly.
  ASSERT_EQ(0, mprotect(page, 4096, PROT_READ | PROT_WRITE));
  munmap(page, 4096);
}

TEST_F(SafeFetchTest, safeCopy_tailNearUnmappedBoundary_stillSucceeds) {
  // Map two adjacent pages, unmap only the second. Place src so the bytes
  // we ask for end inside the mapped page but the (over-read of the) next
  // 4-byte word would touch the unmapped page. The aligned-load strategy
  // must keep the load within the mapped page → success, not fault.
  long page_size = sysconf(_SC_PAGESIZE);
  ASSERT_GT(page_size, 0);

  void* region = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(region, MAP_FAILED);
  ASSERT_EQ(0, munmap((char*)region + page_size, page_size));

  char* mapped_end = (char*)region + page_size;
  char* src = mapped_end - 2;  // 2 bytes from page boundary, k = 2
  src[0] = 'X';
  src[1] = 'Y';

  char dst[16];
  memset(dst, 0, sizeof(dst));
  EXPECT_TRUE(SafeAccess::safeCopy(dst, src, 2));
  EXPECT_EQ('X', dst[0]);
  EXPECT_EQ('Y', dst[1]);

  munmap(region, page_size);
}

TEST_F(SafeFetchTest, safeCopy_requestedRangeCrossesUnmappedPage_returnsFalse) {
  // Distinct from the case above: here the *requested* range itself
  // crosses into the unmapped page. safeCopy must legitimately fault
  // when it can't read all the bytes the caller asked for.
  long page_size = sysconf(_SC_PAGESIZE);
  ASSERT_GT(page_size, 0);

  void* region = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(region, MAP_FAILED);
  ASSERT_EQ(0, munmap((char*)region + page_size, page_size));

  char* mapped_end = (char*)region + page_size;
  char* src = mapped_end - 2;
  src[0] = 'X';
  src[1] = 'Y';

  // Asking for 8 bytes pushes 6 bytes into the unmapped page → must fault.
  char dst[16] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, src, 8));

  munmap(region, page_size);
}

TEST_F(SafeFetchTest, safeCopy_partialPrefixCopiedBeforeFault) {
  // When the requested range straddles the boundary into an unmapped page,
  // safeCopy returns false but the byte-granular copy still writes every
  // readable byte before the fault. Verify the readable prefix landed in dst.
  long page_size = sysconf(_SC_PAGESIZE);
  ASSERT_GT(page_size, 0);

  void* region = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(region, MAP_FAILED);
  ASSERT_EQ(0, munmap((char*)region + page_size, page_size));

  char* mapped_end = (char*)region + page_size;
  // Place src so exactly `prefix` bytes are readable and the rest fall in
  // the unmapped page.
  const size_t prefix = 5;
  char* src = mapped_end - prefix;
  static const char kPrefix[] = "HELLO";  // 5 known readable bytes
  memcpy(src, kPrefix, prefix);

  // Request more than the readable prefix so the copy faults partway.
  const size_t requested = prefix + 4;
  char dst[16];
  memset(dst, 0x5A, sizeof(dst));
  EXPECT_FALSE(SafeAccess::safeCopy(dst, src, requested));

  // The readable prefix must have been copied faithfully before the fault.
  EXPECT_EQ(0, memcmp(dst, kPrefix, prefix));
  // Bytes past the prefix were never written (fault stopped the copy).
  EXPECT_EQ((char)0x5A, dst[prefix]);

  munmap(region, page_size);
}

TEST_F(SafeFetchTest, safeCopy_unalignedSource_allMisalignments) {
  // The front fixup must correctly extract leading bytes from the
  // previous-aligned-word fetch for every misalignment k ∈ {1, 2, 3}.
  static const char kSentinel[] = "ABCDEFGHIJKLMNOP";  // 16 bytes
  // Use a 4-byte-aligned buffer so we can shift src forward by k.
  alignas(4) char buf[32];
  memcpy(buf + 4, kSentinel, 16);  // place payload at aligned offset 4

  for (size_t k = 1; k <= 3; k++) {
    const char* src = buf + 4 + k;  // misaligned by k
    size_t len = 16 - k;            // copy the rest of the payload
    char dst[16];
    memset(dst, 0, sizeof(dst));
    EXPECT_TRUE(SafeAccess::safeCopy(dst, src, len)) << "k=" << k;
    EXPECT_EQ(0, memcmp(dst, kSentinel + k, len)) << "k=" << k;
  }
}

TEST_F(SafeFetchTest, safeCopy_unalignedShortAtPageEnd_stillSucceeds) {
  // Combine misalignment with proximity to an unmapped boundary: src is
  // misaligned AND only a few bytes from the end of the mapped page.
  // The front fixup reads backward (into the same page) → success.
  long page_size = sysconf(_SC_PAGESIZE);
  ASSERT_GT(page_size, 0);

  void* region = mmap(NULL, 2 * page_size, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(region, MAP_FAILED);
  ASSERT_EQ(0, munmap((char*)region + page_size, page_size));

  char* mapped_end = (char*)region + page_size;
  // mapped_end is 4-byte aligned (pages are 4 KiB-aligned). Place src
  // 3 bytes back from the boundary so k = 1 and only 3 bytes are wanted.
  char* src = mapped_end - 3;
  src[0] = 'P';
  src[1] = 'Q';
  src[2] = 'R';

  char dst[8] = {0};
  EXPECT_TRUE(SafeAccess::safeCopy(dst, src, 3));
  EXPECT_EQ('P', dst[0]);
  EXPECT_EQ('Q', dst[1]);
  EXPECT_EQ('R', dst[2]);

  munmap(region, page_size);
}

TEST_F(SafeFetchTest, safeCopy_dataMatchingSingleSentinel_stillSucceeds) {
  // Real data is copied faithfully regardless of its byte values (the copy
  // no longer uses sentinel values to detect faults).
  uint32_t real_data = 0x55AA55AA;
  char dst[4];
  ASSERT_TRUE(SafeAccess::safeCopy(dst, &real_data, 4));
  EXPECT_EQ(0, memcmp(dst, &real_data, 4));
}
