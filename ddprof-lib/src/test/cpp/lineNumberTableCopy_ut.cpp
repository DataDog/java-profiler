/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Reproduces a crash reported in production:
//
//   __memcpy_evex_unaligned_erms
//   Lookup::resolveMethod(_asgct_callframe&)
//   ...
//   Recording::writeStackTraces(Buffer*, Lookup*)
//   ...
//   Profiler::dump / FlightRecorder::dump
//
// Lookup::fillJavaMethodInfo() calls jvmtiEnv::GetLineNumberTable(method, ...)
// on a jmethodID that can be stale (see the TOCTOU race documented right
// there: "GetMethodDeclaringClass may return a jclass wrapping a
// stale/garbage oop when the class was unloaded between sample capture and
// dump" -- a race against class unloading, not tied to any one JVM vendor;
// crash telemetry showed GetClassSignature/GetMethodName returning
// JVMTI_ERROR_NONE with unmapped string pointers despite the spec saying they
// should be valid, and GetLineNumberTable() is called on that exact same
// jmethodID with nothing exempting it from the same failure mode). The
// original, unguarded version of this code trusted the returned
// pointer/size outright and crashed dereferencing them.
//
// The fix went through two shapes before landing on the current one:
//   1. An unguarded memcpy() of the returned buffer into a private copy --
//      crashed exactly like production.
//   2. A SafeAccess::isReadableRange() probe followed by a plain memcpy() --
//      closed most of the gap, but still faulted if the source ever became
//      invalid between the probe and the copy.
// The current implementation (flightRecorder.cpp, Lookup::fillJavaMethodInfo)
// does not copy the table at all. Per the JVMTI spec, GetLineNumberTable()
// hands back a freshly-allocated, caller-owned array decoupled from the
// Method's lifetime -- a spec-compliant implementation cannot invalidate it
// out from under the caller once returned -- so instead of copying, the code
// validates the (pointer, size) pair exactly once and then holds the raw
// pointer directly for the method's cached lifetime, via
// std::shared_ptr<SharedLineNumberTable> (see flightRecorder.h), freed with
// jvmti->Deallocate() when the row is finally evicted. That one-time
// validation is what these tests exercise:
//
//   bool is_table_valid = (size >= 0 && size <= MAX_LINE_NUMBER_TABLE_ENTRIES);
//   bool is_table_readable = (table != nullptr && is_table_valid &&
//                             (size > 0 ? SafeAccess::isReadableRange(table, size * sizeof(entry))
//                                       : SafeAccess::isReadable(table)));
//
// MAX_LINE_NUMBER_TABLE_ENTRIES (65535) sanity-bounds the reported size
// before it drives a byte-count computation: JVM spec SS4.7.3 caps a method's
// bytecode (code_length) at 65535 bytes (u2), so a well-formed table can
// never have more entries than that, and a corrupted jmethodID is just as
// likely to hand back a corrupted size as a corrupted pointer. The ternary on
// `size > 0` matters in its own right: GetLineNumberTable() legitimately
// returns size == 0 with a non-null malloc'd pointer on Hotspot, and
// SafeAccess::isReadableRange() asserts size > 0, so a zero-length table must
// be probed with the single-address SafeAccess::isReadable() instead, not
// isReadableRange(ptr, 0).
//
// These tests isolate the validation step from JVMTI/JNI (which
// fillJavaMethodInfo requires and which is impractical to fake in a plain
// gtest) by exercising the exact validation shape above against buffers
// standing in for whatever GetLineNumberTable() might hand back -- a valid
// table, an unmapped one, a zero-size one, and corrupted size values --
// regardless of the precise reason the JVMTI call produced them.

#include <gtest/gtest.h>
#include <cstring>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "flightRecorder.h"
#include "os.h"
#include "safeAccess.h"

namespace {

// Mirrors MAX_LINE_NUMBER_TABLE_ENTRIES in flightRecorder.cpp (not exported;
// the JVM spec bound it documents is a stable, cross-file constant).
constexpr jint kMaxLineNumberTableEntries = 65535;

// Mirrors the exact validation Lookup::fillJavaMethodInfo() performs on
// jvmtiEnv::GetLineNumberTable()'s output before trusting it (see the header
// comment above). Kept as a free function, rather than calling into
// fillJavaMethodInfo() itself, because that function also requires a live
// JNIEnv/jvmtiEnv/jmethodID that a plain gtest cannot supply.
bool isLineNumberTableReadable(jvmtiLineNumberEntry *table, jint size) {
  bool is_table_valid = (size >= 0 && size <= kMaxLineNumberTableEntries);
  return table != nullptr && is_table_valid &&
         (size > 0 ? SafeAccess::isReadableRange(
                          table, (size_t)size * sizeof(jvmtiLineNumberEntry))
                    : SafeAccess::isReadable(table));
}

// SafeAccess::isReadableRange()/isReadable() rely on SIGSEGV/SIGBUS handlers
// registered via OS::replaceSigsegvHandler()/replaceSigbusHandler() to catch
// the fault at a known trampoline address and turn it into a safe return
// value (see safefetch_ut.cpp for the same pattern). The safefetch trampoline
// can fault with either signal depending on platform, so both must be
// installed; otherwise a fault delivered as the other signal is an ordinary
// unhandled fault.
void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);
void (*orig_busHandler)(int signo, siginfo_t *siginfo, void *ucontext);

void lineNumberTableSegvHandler(int signo, siginfo_t *siginfo, void *context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (signo == SIGBUS) {
      if (orig_busHandler != nullptr) {
        orig_busHandler(signo, siginfo, context);
      }
    } else if (orig_segvHandler != nullptr) {
      orig_segvHandler(signo, siginfo, context);
    }
  }
}

class LineNumberTableCopyTest : public ::testing::Test {
protected:
  void SetUp() override {
    orig_segvHandler = OS::replaceSigsegvHandler(lineNumberTableSegvHandler);
    orig_busHandler = OS::replaceSigbusHandler(lineNumberTableSegvHandler);
  }

  void TearDown() override {
    OS::replaceSigsegvHandler(orig_segvHandler);
    OS::replaceSigbusHandler(orig_busHandler);
  }
};

// Allocates a page-sized region seeded with `count` jvmtiLineNumberEntry
// records, standing in for a buffer jvmtiEnv::GetLineNumberTable() would
// have returned.
jvmtiLineNumberEntry *makeFakeLineNumberTable(void *page, int count) {
  jvmtiLineNumberEntry *table = (jvmtiLineNumberEntry *)page;
  for (int i = 0; i < count; i++) {
    table[i].start_location = i * 4;
    table[i].line_number = i + 1;
  }
  return table;
}

} // namespace

// Reproducer: trusting GetLineNumberTable()'s (pointer, size) outright, with
// no readability check, the way the pre-fix code did (and the way
// MethodInfo::getLineNumber() would if a bad pair were ever cached).
// Demonstrates that once the source page is gone, a direct read crashes the
// process rather than failing gracefully -- this is exactly why the
// validation below must run before the pair is ever handed to
// SharedLineNumberTable.
TEST(LineNumberTableCopyRawTest, UnguardedAccessCrashesWhenSourceUnmapped) {
  EXPECT_DEATH(
      {
        long page_size = sysconf(_SC_PAGESIZE);
        void *page = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (page == MAP_FAILED) {
          _exit(1); // treat as death via non-zero exit if mmap itself fails
        }
        jint line_number_table_size = 4;
        jvmtiLineNumberEntry *line_number_table =
            makeFakeLineNumberTable(page, line_number_table_size);

        // Stand-in for GetLineNumberTable() handing back a bad pointer for a
        // corrupted/stale jmethodID: the backing memory is simply gone by
        // the time it is read.
        munmap(page, page_size);

        // No readability check -- mirrors what MethodInfo::getLineNumber()
        // does to an already-cached table, and what fillJavaMethodInfo did
        // before the fix.
        volatile jint sink = line_number_table[0].line_number; // <-- crashes here
        (void)sink;
      },
      "");
}

// Documents the fix: probing with SafeAccess::isReadableRange() before ever
// trusting the pointer turns the crash into a clean, detectable rejection.
TEST_F(LineNumberTableCopyTest, RejectsUnmappedSource) {
  long page_size = sysconf(_SC_PAGESIZE);
  void *page = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  jint line_number_table_size = 4;
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(page, line_number_table_size);

  ASSERT_EQ(0, munmap(page, page_size));

  EXPECT_FALSE(
      isLineNumberTableReadable(line_number_table, line_number_table_size));
}

// Sanity check: the guard must not reject a genuinely valid table, or every
// real dump would silently lose line-number info. Also confirms the current
// design's core property -- the validated pointer is held as-is, with no
// private copy -- by wrapping it in SharedLineNumberTable and checking it is
// the exact same allocation.
TEST_F(LineNumberTableCopyTest, AcceptsValidSourceAndHoldsItDirectly) {
  jint line_number_table_size = 8;
  jvmtiLineNumberEntry stack_table[8];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, line_number_table_size);

  ASSERT_TRUE(
      isLineNumberTableReadable(line_number_table, line_number_table_size));

  // SharedLineNumberTable stores the pointer/size verbatim -- no copy -- and
  // its destructor calls jvmti->Deallocate() rather than free(), so we must
  // not let it run on this stack-allocated buffer; construct it manually
  // instead of via make_shared to check the stored fields without invoking
  // the destructor.
  SharedLineNumberTable held(line_number_table_size, line_number_table);
  EXPECT_EQ(line_number_table, held._table);
  EXPECT_EQ(line_number_table_size, held._size);
  held._table = nullptr; // prevent ~SharedLineNumberTable() from Deallocate()-ing stack memory
}

// Regression test: GetLineNumberTable() legitimately returns size == 0 with a
// non-null malloc'd pointer on Hotspot. SafeAccess::isReadableRange() asserts
// size > 0, so the validation must probe a zero-size table with
// SafeAccess::isReadable() instead of isReadableRange(ptr, 0) -- otherwise
// every method compiled without debug line info would abort the process in
// any build with assertions enabled (this project's gtest/debug configs).
TEST_F(LineNumberTableCopyTest, AcceptsZeroSizeTableWithoutRangeCheckAssert) {
  jvmtiLineNumberEntry entry{};
  EXPECT_TRUE(isLineNumberTableReadable(&entry, 0));
}

// Regression test for the size being corrupted, alongside (or instead of) the
// pointer, for the same reason as the pointer: a stale/garbage jmethemID's
// out-params are just as likely to be corrupted together. A negative size
// must be rejected by the sanity bound before it ever reaches a byte-count
// computation or a SafeAccess probe.
TEST_F(LineNumberTableCopyTest, RejectsNegativeSize) {
  jvmtiLineNumberEntry stack_table[4];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, 4);

  EXPECT_FALSE(isLineNumberTableReadable(line_number_table, -1));
}

// A well-formed LineNumberTable can never exceed MAX_LINE_NUMBER_TABLE_ENTRIES
// entries (JVM spec SS4.7.3 caps code_length at 65535 bytes, u2), so an
// implausibly large size must be rejected outright, independent of whether
// the pointer happens to be readable.
TEST_F(LineNumberTableCopyTest, RejectsOversizedTable) {
  jvmtiLineNumberEntry stack_table[4];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, 4);

  EXPECT_FALSE(isLineNumberTableReadable(line_number_table,
                                          kMaxLineNumberTableEntries + 1));
}
