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
// Lookup::fillJavaMethodInfo() (inlined into resolveMethod() under -O2/-O3)
// calls jvmtiEnv::GetLineNumberTable(method, ...) and then copied the
// result with an unguarded:
//
//   memcpy(owned_table, line_number_table, bytes);
//
// (flightRecorder.cpp now guards this copy with SafeAccess::isReadableRange()
// -- see below -- so the line numbers of the unguarded version are no longer
// present in the file; this file's tests reproduce that removed pattern.)
//
// Unlike the class_name/method_name/method_sig strings returned by the
// preceding JVMTI calls (which ARE probed with SafeAccess::isReadableRange
// before use, see PR #537 / commit ef13aa29f), the line_number_table pointer
// is used directly.
//
// Per the JVMTI spec, GetLineNumberTable() hands back a freshly-allocated,
// caller-owned array (hence the Deallocate() call after the copy) that is
// decoupled from the Method's lifetime -- a spec-compliant implementation
// cannot invalidate it out from under the caller. The actual risk, per the
// comments already in fillJavaMethodInfo, is the TOCTOU race documented
// right there: "GetMethodDeclaringClass may return a jclass wrapping a
// stale/garbage oop when the class was unloaded between sample capture and
// dump" -- a race against class unloading, not tied to any one JVM vendor.
// That same comment block notes crash telemetry showed GetClassSignature/
// GetMethodName returning JVMTI_ERROR_NONE with unmapped string pointers
// despite the spec saying they should be valid (a separate OpenJ9-specific
// jmethodID-corruption mode is also handled a few lines above, but is not
// the only source of this). The production crash motivating this file was
// on a stock HotSpot JDK 11, confirming the race is not OpenJ9-specific.
// GetLineNumberTable() is called on the exact same jmethodID as
// GetMethodDeclaringClass/GetClassSignature/GetMethodName, with nothing
// about it that would exempt it from that same observed failure mode.
//
// These tests isolate the copy step from JVMTI/JNI (which fillJavaMethodInfo
// requires and which is impractical to fake in a plain gtest) by exercising
// the exact copy pattern against a pointer whose backing memory is gone --
// standing in for "GetLineNumberTable() returned a bad pointer" regardless
// of the precise reason. The result at the memcpy call site is identical
// either way, so this is sufficient to prove both the crash and the fix.

#include <gtest/gtest.h>
#include <cstring>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "flightRecorder.h"
#include "os.h"
#include "safeAccess.h"

namespace {

// SafeAccess::isReadableRange()/isReadable() rely on a SIGSEGV handler
// registered via OS::replaceSigsegvHandler() to catch the fault at a known
// trampoline address and turn it into a safe return value (see
// safefetch_ut.cpp for the same pattern). Without it, a fault inside the
// safefetch trampoline is an ordinary unhandled SIGSEGV.
void (*orig_segvHandler)(int signo, siginfo_t *siginfo, void *ucontext);

void lineNumberTableSegvHandler(int signo, siginfo_t *siginfo, void *context) {
  if (!SafeAccess::handle_safefetch(signo, context)) {
    if (orig_segvHandler != nullptr) {
      orig_segvHandler(signo, siginfo, context);
    }
  }
}

class LineNumberTableCopyTest : public ::testing::Test {
protected:
  void SetUp() override {
    orig_segvHandler = OS::replaceSigsegvHandler(lineNumberTableSegvHandler);
  }

  void TearDown() override { OS::replaceSigsegvHandler(orig_segvHandler); }
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

// Reproducer: the code shape that used to be in flightRecorder.cpp's
// fillJavaMethodInfo() before the fix, with no readability guard before the
// memcpy. Demonstrates that once the source page is gone, the copy step used
// by resolveMethod() crashes the process rather than failing gracefully.
TEST(LineNumberTableCopyRawTest, UnguardedCopyCrashesWhenSourceUnmapped) {
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
        // the time the copy runs.
        munmap(page, page_size);

        // This mirrors the pre-fix fillJavaMethodInfo() shape verbatim: no
        // readability check on line_number_table before the copy.
        size_t bytes =
            (size_t)line_number_table_size * sizeof(jvmtiLineNumberEntry);
        void *owned_table = malloc(bytes);
        memcpy(owned_table, line_number_table, bytes); // <-- crashes here
        free(owned_table);
      },
      "");
}

// Documents the fix: guarding the same copy with
// SafeAccess::isReadableRange() (the same primitive already used to probe
// class_name/method_name/method_sig in fillJavaMethodInfo) turns the crash
// into a clean, detectable failure with no memory touched past the guard.
TEST_F(LineNumberTableCopyTest, GuardedCopySkipsSafelyWhenSourceUnmapped) {
  long page_size = sysconf(_SC_PAGESIZE);
  void *page = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  ASSERT_NE(page, MAP_FAILED);

  jint line_number_table_size = 4;
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(page, line_number_table_size);

  ASSERT_EQ(0, munmap(page, page_size));

  size_t bytes = (size_t)line_number_table_size * sizeof(jvmtiLineNumberEntry);
  void *owned_table = nullptr;
  if (SafeAccess::isReadableRange(line_number_table, bytes)) {
    owned_table = malloc(bytes);
    memcpy(owned_table, line_number_table, bytes);
  }

  EXPECT_EQ(nullptr, owned_table);
  free(owned_table);
}

// Sanity check: the guard must not reject a genuinely valid table, or every
// real dump would silently lose line-number info.
TEST_F(LineNumberTableCopyTest, GuardedCopyStillWorksForValidSource) {
  jint line_number_table_size = 8;
  jvmtiLineNumberEntry stack_table[8];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, line_number_table_size);

  size_t bytes = (size_t)line_number_table_size * sizeof(jvmtiLineNumberEntry);
  void *owned_table = nullptr;
  if (SafeAccess::isReadableRange(line_number_table, bytes)) {
    owned_table = malloc(bytes);
    memcpy(owned_table, line_number_table, bytes);
  }

  ASSERT_NE(nullptr, owned_table);
  EXPECT_EQ(0, memcmp(owned_table, line_number_table, bytes));
  free(owned_table);
}
