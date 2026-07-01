/*
 * Copyright 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Isolating regression test for the carrier-owned ThreadContext use-after-free.
 *
 * Root cause (proposed): JavaProfiler.initializeContextTLS0 exposes the native
 * OtelThreadContextRecord embedded inside a ProfiledThread to Java as a
 * DirectByteBuffer:
 *
 *     OtelThreadContextRecord* record = thrd->getOtelContextRecord(); // == &_otel_ctx_record
 *     return env->NewDirectByteBuffer((void*)record, totalSize);
 *
 * NewDirectByteBuffer wraps a raw pointer with NO ownership and NO cleaner, so
 * the buffer does not keep the ProfiledThread alive. All Java context writes go
 * through this buffer (ThreadContext.put / setContextAttribute /
 * compactOtepAttribute -> ctxBuffer.put(index, ...)). DirectByteBuffer.put is
 * bounds-checked against capacity (688) but NOT liveness-checked.
 *
 * When the owning OS thread (a virtual-thread carrier) exits, freeKey ->
 * `delete tls` (or ProfiledThread::release()) frees the ProfiledThread. A Java
 * thread that cached a ThreadContext whose buffer points into that record then
 * keeps writing OTEP attrs_data bytes into freed native memory — which glibc
 * malloc may have already handed to the JVM (e.g. a ThreadsList array). That is
 * the only path by which ThreadContext writes can corrupt JVM-owned C-heap.
 *
 * This test proves the unguarded primitive in isolation: a write through the
 * record pointer AFTER ProfiledThread::release() is a heap-use-after-free. It is
 * deterministic and needs no JDK / no virtual threads — only AddressSanitizer.
 *
 * Under a non-ASan build the test SKIPs with guidance (no false confidence).
 */

#include <gtest/gtest.h>

// AddressSanitizer detection — gcc exposes __SANITIZE_ADDRESS__, clang exposes
// it through __has_feature(address_sanitizer).
#if defined(__SANITIZE_ADDRESS__)
#  define DDPROF_ASAN 1
#elif defined(__has_feature)
#  if __has_feature(address_sanitizer)
#    define DDPROF_ASAN 1
#  endif
#endif

#include "otel_context.h"
#include "thread.h"

#include <cstddef>
#include <cstdint>
#include <unistd.h>

#ifdef DDPROF_ASAN
// The gtest harness runs ASan with `log_path=/tmp/asan.log`, which routes the
// error report to a file instead of the child's stderr. EXPECT_DEATH matches its
// regex against the child's stderr, so without this echo the death test would
// see the process die but find no "heap-use-after-free" text and fail. The ASan
// error-report callback receives the fully formatted report; we mirror it to
// stderr so the matcher works regardless of log_path.
extern "C" void __asan_set_error_report_callback(void (*callback)(const char *));

static void echo_asan_report_to_stderr(const char *report) {
  size_t n = 0;
  while (report[n] != '\0') {
    ++n;
  }
  ssize_t written = ::write(STDERR_FILENO, report, n);
  (void)written;
}
#endif

// Offset 0x18 is the OTEP `valid` byte — squarely inside the 640-byte record and
// therefore inside the ProfiledThread allocation. Writing it before release() is
// a legitimately-owned, in-bounds store; writing it after release() is a
// use-after-free of the same byte. Using an interior byte (not offset 0) makes
// it unambiguous that ASan reports a free of the enclosing block, not an OOB.
static constexpr size_t kValidByteOffset = 0x18;

// ── Positive control: a write through the record while the thread is live is
// safe. This anchors the death test below — it shows the byte we poke is owned
// and in-bounds, so the death test's report is attributable to the free, not to
// an out-of-bounds access. ────────────────────────────────────────────────────
TEST(ContextUafTest, WriteThroughRecordWhileLiveIsSafe) {
  ProfiledThread::initCurrentThread();
  OtelThreadContextRecord *rec = ProfiledThread::current()->getOtelContextRecord();
  ASSERT_NE(nullptr, rec);

  volatile uint8_t *buf = reinterpret_cast<volatile uint8_t *>(rec);
  buf[kValidByteOffset] = 1;             // mirrors a Java ctxBuffer.put(0x18, 1)
  EXPECT_EQ(1, buf[kValidByteOffset]);

  ProfiledThread::release();             // clean teardown — no dangling access
}

// ── Core proof: write through the record AFTER release() is a UAF. ──────────────
//
// EXPECT_DEATH runs the body in a forked child; ASan detects the post-release
// store and aborts the child, and gtest matches "heap-use-after-free" against the
// child's stderr. The death-test style is "threadsafe" because the test binary is
// multithreaded by the time this runs (gtest's default fork-only style can be
// flaky there).
//
// When the bug is FIXED (e.g. a liveness/epoch guard turns the post-free write
// into a no-op), the child no longer dies with that report and this test FLIPS to
// failing — the intended red->green signal for the fix.
TEST(ContextUafDeathTest, WriteThroughRecordAfterReleaseIsUseAfterFree) {
#ifndef DDPROF_ASAN
  GTEST_SKIP()
      << "Requires AddressSanitizer to observe the use-after-free.\n"
         "Build & run with the asan configuration, e.g.:\n"
         "  ./gradlew :ddprof-lib:gtestAsan_context_uaf_ut\n"
         "Under a non-ASan build the post-free write is silent (exactly the\n"
         "production failure mode), so there is nothing to assert here.";
#else
  // Single-threaded binary at this point, so the default fork-only ("fast")
  // death-test style is reliable. Register the report echo before forking; the
  // forked child inherits it.
  __asan_set_error_report_callback(echo_asan_report_to_stderr);
  EXPECT_DEATH(
      {
        ProfiledThread::initCurrentThread();
        OtelThreadContextRecord *rec =
            ProfiledThread::current()->getOtelContextRecord();
        // This raw pointer is exactly the base NewDirectByteBuffer would hand to
        // Java. Java holds it for the lifetime of the *Java* thread, oblivious to
        // the *OS* thread's lifetime.
        volatile uint8_t *buf = reinterpret_cast<volatile uint8_t *>(rec);
        buf[kValidByteOffset] = 1;        // live write — fine

        ProfiledThread::release();        // carrier OS-thread exit frees the record

        buf[kValidByteOffset] = 0;        // ThreadContext write AFTER free -> UAF
        // Unreachable once ASan fires. If a future fix makes the write a no-op,
        // the child exits 0 and EXPECT_DEATH fails — flagging that this proof
        // test needs to become a fix-verification test.
        _exit(0);
      },
      "heap-use-after-free");
#endif
}
