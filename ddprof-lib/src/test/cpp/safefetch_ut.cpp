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

#include "counters.h"
#include "guards.h"
#include "threadLocalData.h"
#include "safeAccess.h"
#include "os.h"
#include "safeAccessTestSupport.h"

class SafeFetchTest : public ::testing::Test {
protected:
    ScopedSafeAccessHandler _handler{"SafeFetchTest"};
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

// ---------------------------------------------------------------------------
// SafeAccess::store/store32/storePtr — write-side counterpart of
// safeFetch{32,64}/loadPtr, sharing the same handle_safefetch fault redirect.
// ---------------------------------------------------------------------------

TEST_F(SafeFetchTest, validStore32) {
  int32_t i = 0;
  EXPECT_TRUE(SafeAccess::store32(&i, 42));
  EXPECT_EQ(42, i);
  EXPECT_TRUE(SafeAccess::store32(&i, INT_MIN));
  EXPECT_EQ(INT_MIN, i);
}

TEST_F(SafeFetchTest, invalidStore32) {
  int32_t* p = nullptr;
  EXPECT_FALSE(SafeAccess::store32(p, 42));
}

TEST_F(SafeFetchTest, validStorePtr) {
  void* target = nullptr;
  void** pp = &target;
  char c;
  EXPECT_TRUE(SafeAccess::storePtr(pp, (void*)&c));
  EXPECT_EQ((void*)&c, target);
}

TEST_F(SafeFetchTest, invalidStorePtr) {
  void** pp = nullptr;
  char c;
  EXPECT_FALSE(SafeAccess::storePtr(pp, (void*)&c));
}

TEST_F(SafeFetchTest, validStore) {
  void* target = nullptr;
  void** pp = &target;
  char c;
  EXPECT_TRUE(SafeAccess::store(pp, (void*)&c));
  EXPECT_EQ((void*)&c, target);
}

TEST_F(SafeFetchTest, invalidStore) {
  void** pp = nullptr;
  char c;
  EXPECT_FALSE(SafeAccess::store(pp, (void*)&c));
}

/**
 * Tests that store32 correctly handles a read-only page instead of crashing.
 * PROT_READ (rather than PROT_NONE) isolates that this is specifically a
 * write fault, not merely an unreadable address.
 */
TEST_F(SafeFetchTest, readOnlyMemoryStore32) {
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  int32_t* ptr = static_cast<int32_t*>(page);
  *ptr = 1;
  ASSERT_EQ(mprotect(page, 4096, PROT_READ), 0);

  // This MUST return false, not crash.
  EXPECT_FALSE(SafeAccess::store32(ptr, 2));
  // The page is read-only, so the value must be unchanged.
  ASSERT_EQ(mprotect(page, 4096, PROT_READ | PROT_WRITE), 0);
  EXPECT_EQ(1, *ptr);

  munmap(page, 4096);
}

/**
 * Tests that storePtr correctly handles a read-only page instead of crashing.
 * Same rationale as readOnlyMemoryStore32 above.
 */
TEST_F(SafeFetchTest, readOnlyMemoryStorePtr) {
  void* page = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  void** ptr = static_cast<void**>(page);
  char sentinel;
  *ptr = &sentinel;
  ASSERT_EQ(mprotect(page, 4096, PROT_READ), 0);

  char other;
  EXPECT_FALSE(SafeAccess::storePtr(ptr, &other));
  ASSERT_EQ(mprotect(page, 4096, PROT_READ | PROT_WRITE), 0);
  EXPECT_EQ((void*)&sentinel, *ptr);

  munmap(page, 4096);
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
//     including when [src, src+len) sits within a few bytes of an unreadable
//     page boundary (byte-granular reads never over-read past src+len)
//   - return false (no crash) when the requested range itself crosses into
//     an unreadable page
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
  // Page zero stays unmapped (default vm.mmap_min_addr on Linux, __PAGEZERO on
  // macOS), so unlike a munmap()ed page no concurrent mmap can make it
  // readable. safeCopy must return false rather than SIGSEGV.
  char dst[64] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, nullptr, 32));
}

TEST_F(SafeFetchTest, safeCopy_protNoneSource_returnsFalse) {
  // A source that starts on a PROT_NONE page must fail on its first byte.
  GuardedPage region;
  ASSERT_TRUE(region.ok());

  char dst[64] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, region.guardStart(), 32));
}

TEST_F(SafeFetchTest, safeCopy_tailNearGuardPage_stillSucceeds) {
  // The requested bytes end exactly at the guard page, so any read past
  // src+len faults there and fails the copy.
  GuardedPage region;
  ASSERT_TRUE(region.ok());

  char* mapped_end = region.guardStart();
  char* src = mapped_end - 2;  // 2 bytes from page boundary
  src[0] = 'X';
  src[1] = 'Y';

  char dst[16];
  memset(dst, 0, sizeof(dst));
  EXPECT_TRUE(SafeAccess::safeCopy(dst, src, 2));
  EXPECT_EQ('X', dst[0]);
  EXPECT_EQ('Y', dst[1]);
}

TEST_F(SafeFetchTest, safeCopy_requestedRangeCrossesGuardPage_returnsFalse) {
  // Distinct from the case above: here the *requested* range itself
  // crosses into the guard page. safeCopy must legitimately fault
  // when it can't read all the bytes the caller asked for.
  GuardedPage region;
  ASSERT_TRUE(region.ok());

  char* mapped_end = region.guardStart();
  char* src = mapped_end - 2;
  src[0] = 'X';
  src[1] = 'Y';

  // Asking for 8 bytes pushes 6 bytes into the guard page → must fault.
  char dst[16] = {0};
  EXPECT_FALSE(SafeAccess::safeCopy(dst, src, 8));
}

TEST_F(SafeFetchTest, safeCopy_partialPrefixCopiedBeforeFault) {
  // When the requested range straddles the boundary into the guard page,
  // safeCopy returns false but the byte-granular copy still writes every
  // readable byte before the fault. Verify the readable prefix landed in dst.
  GuardedPage region;
  ASSERT_TRUE(region.ok());

  char* mapped_end = region.guardStart();
  // Place src so exactly `prefix` bytes are readable and the rest fall in
  // the guard page.
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
}

TEST_F(SafeFetchTest, safeCopy_unalignedSource_allMisalignments) {
  // safeCopy has no alignment requirement on src: every offset k ∈ [1, 7]
  // from an 8-byte boundary must copy the bytes exactly.
  static const char kSentinel[] = "ABCDEFGHIJKLMNOP";  // 16 bytes
  alignas(8) char buf[32];
  memcpy(buf + 8, kSentinel, 16);  // payload starts 8-byte aligned

  for (size_t k = 1; k <= 7; k++) {
    const char* src = buf + 8 + k;  // misaligned by k
    size_t len = 16 - k;            // copy the rest of the payload
    char dst[16];
    memset(dst, 0, sizeof(dst));
    EXPECT_TRUE(SafeAccess::safeCopy(dst, src, len)) << "k=" << k;
    EXPECT_EQ(0, memcmp(dst, kSentinel + k, len)) << "k=" << k;
  }
}

TEST_F(SafeFetchTest, safeCopy_sentinelLikeData_stillSucceeds) {
  // A fault is reported by the pc redirect to safecopy_cont, not by a data
  // value, so a sentinel-like pattern must copy faithfully.
  uint32_t real_data = 0x55AA55AA;
  char dst[4];
  ASSERT_TRUE(SafeAccess::safeCopy(dst, &real_data, 4));
  EXPECT_EQ(0, memcmp(dst, &real_data, 4));
}

// ---------------------------------------------------------------------------
// isReadableCString: readable up to a NUL found within max_len bytes.
// ---------------------------------------------------------------------------

// Any bound larger than the strings below; the tests at max_len pass their own.
static constexpr size_t kMaxLen = 65538;

TEST_F(SafeFetchTest, isReadableCString_acceptsNulOnLastReadableByte) {
  GuardedPage region;
  ASSERT_TRUE(region.ok());
  const char* s = region.placeAtEnd("join");
  // A 256-byte range from the string is not readable; the string itself is.
  ASSERT_FALSE(SafeAccess::isReadableRange(s, 256));
  long long faults = Counters::getCounter(SAFECSTRING_FAILED);
  EXPECT_TRUE(SafeAccess::isReadableCString(s, kMaxLen));
  EXPECT_EQ(faults, Counters::getCounter(SAFECSTRING_FAILED)) << "the scan stops at the NUL";
}

TEST_F(SafeFetchTest, isReadableCString_acceptsStringSpanningTwoReadablePages) {
  GuardedPage region(2);
  ASSERT_TRUE(region.ok());
  char* second_page = region.guardStart() - OS::page_size;
  char* s = second_page - 3;
  memcpy(s, "abcdef", 7);  // crosses into the second page, NUL there
  EXPECT_TRUE(SafeAccess::isReadableCString(s, kMaxLen));
}

TEST_F(SafeFetchTest, isReadableCString_acceptsNulAtMaxLenMinusOne) {
  EXPECT_TRUE(SafeAccess::isReadableCString("abc", 4));
}

TEST_F(SafeFetchTest, isReadableCString_rejectsNulAtMaxLen) {
  EXPECT_FALSE(SafeAccess::isReadableCString("abc", 3));
}

TEST_F(SafeFetchTest, isReadableCString_rejectsZeroMaxLen) {
  EXPECT_FALSE(SafeAccess::isReadableCString("", 0));
}

TEST_F(SafeFetchTest, isReadableCString_rejectsNull) {
  long long faults = Counters::getCounter(SAFECSTRING_FAILED);
  EXPECT_FALSE(SafeAccess::isReadableCString(nullptr, kMaxLen));
  EXPECT_EQ(faults, Counters::getCounter(SAFECSTRING_FAILED)) << "null is rejected before any read";
}

TEST_F(SafeFetchTest, isReadableCString_rejectsUnreadableFirstPage) {
  GuardedPage region;
  ASSERT_TRUE(region.ok());
  long long faults = Counters::getCounter(SAFECSTRING_FAILED);
  EXPECT_FALSE(SafeAccess::isReadableCString(region.guardStart(), kMaxLen));
  EXPECT_EQ(faults + 1, Counters::getCounter(SAFECSTRING_FAILED));
}

TEST_F(SafeFetchTest, isReadableCString_rejectsStringRunningIntoGuardPage) {
  GuardedPage region;
  ASSERT_TRUE(region.ok());
  char* s = region.guardStart() - 8;
  memset(s, 'x', 8);  // no NUL before the guard page
  long long faults = Counters::getCounter(SAFECSTRING_FAILED);
  EXPECT_FALSE(SafeAccess::isReadableCString(s, kMaxLen));
  EXPECT_EQ(faults + 1, Counters::getCounter(SAFECSTRING_FAILED)) << "the read of the guard page faults";
}

#ifdef DEBUG
// Debug builds count SafeAccess calls made inside a siglongjmp-protected window.
TEST_F(SafeFetchTest, isReadableCString_countsCallsInsideAProtectedWindow) {
  ProfiledThread* thread = ProfiledThread::initCurrentThreadSignalSafe();
  ASSERT_NE(nullptr, thread);
  long long before = Counters::getCounter(SAFECSTRING_WHILE_PROTECTED);
  EXPECT_TRUE(SafeAccess::isReadableCString("abc", 4));
  EXPECT_EQ(before, Counters::getCounter(SAFECSTRING_WHILE_PROTECTED)) << "outside a window";
  {
    // No sigsetjmp: this fixture's handler never siglongjmps, so ctx is only a
    // marker that makes the thread count as protected.
    JmpCtxScope scope(thread);
    sigjmp_buf ctx;
    scope.install(&ctx);
    EXPECT_TRUE(SafeAccess::isReadableCString("abc", 4));
  }
  EXPECT_EQ(before + 1, Counters::getCounter(SAFECSTRING_WHILE_PROTECTED));
  ProfiledThread::release();
}
#endif

TEST_F(SafeFetchTest, isReadableCString_stopsAtMaxLenBeforeTheGuardPage) {
  GuardedPage region;
  ASSERT_TRUE(region.ok());
  char* s = region.guardStart() - 8;
  memset(s, 'x', 8);  // no NUL; max_len ends exactly at the guard page
  long long faults = Counters::getCounter(SAFECSTRING_FAILED);
  EXPECT_FALSE(SafeAccess::isReadableCString(s, 8));
  EXPECT_EQ(faults, Counters::getCounter(SAFECSTRING_FAILED)) << "no byte past max_len is read";
}
