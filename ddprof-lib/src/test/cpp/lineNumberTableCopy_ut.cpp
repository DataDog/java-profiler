/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Tests the one-time validation Lookup::fillJavaMethodInfo() applies to the
// (pointer, size) pair GetLineNumberTable() returns for a possibly stale
// jmethodID, before it holds the table as a SharedLineNumberTable.

#include <gtest/gtest.h>
#include <cstring>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>

#include "flightRecorder.h"
#include "os.h"
#include "safeAccess.h"

namespace {

// Mirrors MAX_LINE_NUMBER_TABLE_ENTRIES in flightRecorder.cpp (not exported).
// JVM spec 4.7.3 caps code_length at 65535 bytes, so no table has more entries.
constexpr jint kMaxLineNumberTableEntries = 65535;

// Mirrors the validation in Lookup::fillJavaMethodInfo(), which cannot run
// here because it needs a live JNIEnv, jvmtiEnv and jmethodID.
bool isLineNumberTableReadable(jvmtiLineNumberEntry *table, jint size) {
  bool is_table_valid = (size >= 0 && size <= kMaxLineNumberTableEntries);
  return table != nullptr && is_table_valid &&
         (size > 0 ? SafeAccess::isReadableRange(
                          table, static_cast<size_t>(size) *
                                     sizeof(jvmtiLineNumberEntry))
                    : SafeAccess::isReadable(table));
}

// SafeAccess probes turn a fault at the safefetch trampoline into a return
// value only through these handlers. Install both: the trampoline faults with
// SIGSEGV or SIGBUS depending on the platform.
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

// Writes `count` entries at `buffer`, standing in for the array that
// GetLineNumberTable() returns.
jvmtiLineNumberEntry *makeFakeLineNumberTable(void *buffer, int count) {
  jvmtiLineNumberEntry *table = static_cast<jvmtiLineNumberEntry *>(buffer);
  for (int i = 0; i < count; i++) {
    table[i].start_location = i * 4;
    table[i].line_number = i + 1;
  }
  return table;
}

// Owns one anonymous read/write page and unmaps it on scope exit, including
// after a fatal ASSERT; munmap() succeeds on a PROT_NONE page as well.
class ScopedPage {
public:
  ScopedPage()
      : _addr(mmap(NULL, OS::page_size, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) {}
  ~ScopedPage() {
    if (_addr != MAP_FAILED) {
      munmap(_addr, OS::page_size);
    }
  }
  ScopedPage(const ScopedPage &) = delete;
  ScopedPage &operator=(const ScopedPage &) = delete;

  void *addr() const { return _addr; }
  size_t size() const { return OS::page_size; }

private:
  void *_addr;
};

} // namespace

// Reading an unreadable table without the validation crashes the process,
// which is why fillJavaMethodInfo() must validate before caching the pair and
// MethodInfo::getLineNumber() later reads it unchecked.
TEST(LineNumberTableCopyRawTest, UnguardedAccessCrashesWhenSourceUnreadable) {
  EXPECT_DEATH(
      {
        ScopedPage page;
        if (page.addr() == MAP_FAILED) {
          _exit(1); // a failed mmap still ends the child with non-zero status
        }
        jvmtiLineNumberEntry *line_number_table =
            makeFakeLineNumberTable(page.addr(), 4);
        mprotect(page.addr(), page.size(), PROT_NONE);

        volatile jint sink = line_number_table[0].line_number; // faults here
        (void)sink;
      },
      "");
}

// The probe rejects a PROT_NONE source and accepts the same pointer once it is
// readable, so it reports current state. PROT_NONE, not munmap(): a concurrent
// mmap may reuse an unmapped address, but ScopedPage keeps this one mapped.
TEST_F(LineNumberTableCopyTest, RejectsUnreadableSourceUntilReadable) {
  ScopedPage page;
  ASSERT_NE(page.addr(), MAP_FAILED);

  jint line_number_table_size = 4;
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(page.addr(), line_number_table_size);

  ASSERT_EQ(0, mprotect(page.addr(), page.size(), PROT_NONE));
  EXPECT_FALSE(
      isLineNumberTableReadable(line_number_table, line_number_table_size));

  ASSERT_EQ(0, mprotect(page.addr(), page.size(), PROT_READ));
  EXPECT_TRUE(
      isLineNumberTableReadable(line_number_table, line_number_table_size));
}

// A valid table must pass, or every dump loses line numbers, and
// SharedLineNumberTable must hold the validated pointer itself, not a copy.
TEST_F(LineNumberTableCopyTest, AcceptsValidSourceAndHoldsItDirectly) {
  jint line_number_table_size = 8;
  jvmtiLineNumberEntry stack_table[8];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, line_number_table_size);

  ASSERT_TRUE(
      isLineNumberTableReadable(line_number_table, line_number_table_size));

  // ~SharedLineNumberTable() calls jvmti->Deallocate(), so it is built on the
  // stack and its pointer cleared before it runs on this stack buffer.
  SharedLineNumberTable held(line_number_table_size, line_number_table);
  EXPECT_EQ(line_number_table, held._table);
  EXPECT_EQ(line_number_table_size, held._size);
  held._table = nullptr;
}

// HotSpot returns size == 0 with a non-null pointer for methods without line
// info. isReadableRange() asserts size > 0, so a zero-size table must take the
// single-address isReadable() probe instead of aborting debug builds.
TEST_F(LineNumberTableCopyTest, AcceptsZeroSizeTableWithoutRangeCheckAssert) {
  jvmtiLineNumberEntry entry{};
  EXPECT_TRUE(isLineNumberTableReadable(&entry, 0));
}

// A stale jmethodID can corrupt the size as well as the pointer. A negative
// size must be rejected before it reaches a byte count or a SafeAccess probe.
TEST_F(LineNumberTableCopyTest, RejectsNegativeSize) {
  jvmtiLineNumberEntry stack_table[4];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, 4);

  EXPECT_FALSE(isLineNumberTableReadable(line_number_table, -1));
}

// A size above kMaxLineNumberTableEntries must be rejected even when the
// pointer itself is readable.
TEST_F(LineNumberTableCopyTest, RejectsOversizedTable) {
  jvmtiLineNumberEntry stack_table[4];
  jvmtiLineNumberEntry *line_number_table =
      makeFakeLineNumberTable(stack_table, 4);

  EXPECT_FALSE(isLineNumberTableReadable(line_number_table,
                                          kMaxLineNumberTableEntries + 1));
}
