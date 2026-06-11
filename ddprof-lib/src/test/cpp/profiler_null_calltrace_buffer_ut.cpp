/*
 * Copyright 2026, Datadog, Inc
 */

#include <gtest/gtest.h>
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Regression tests for the PROF-14679 null-calltrace-buffer crash.
//
// Profiler::_calltrace_buffer[i] is NULL from the constructor until
// Profiler::start() allocates it. Before the fix, both recordJVMTISample and
// recordExternalSample dereferenced the slot without checking for null,
// producing a SIGSEGV whenever sampling fired before or between starts.
// After the fix both functions null-check the slot under the shard lock and
// return early (incrementing the skip counter) when the buffer is absent.
//
// These tests exercise that early-return path by calling the functions on the
// singleton whose _calltrace_buffer slots are still NULL (no start() was
// called). Pre-fix: SIGSEGV -> test binary killed -> CI failure.
// Post-fix: graceful return -> test passes.

static constexpr char PROFILER_NULL_BUFFER_TEST_NAME[] = "ProfilerNullCalltraceBufferTest";
class ProfilerNullBufferGlobalSetup {
public:
  ProfilerNullBufferGlobalSetup()  { installGtestCrashHandler<PROFILER_NULL_BUFFER_TEST_NAME>(); }
  ~ProfilerNullBufferGlobalSetup() { restoreDefaultSignalHandlers(); }
};
static ProfilerNullBufferGlobalSetup profiler_null_buffer_global_setup;

// thread=nullptr is safe: GetStackTrace is never reached when the buffer is null.
TEST(ProfilerNullCalltraceBufferTest, RecordJvmtiSampleNullBufferDoesNotCrash) {
    Profiler::instance()->recordJVMTISample(
        /*counter=*/1, /*tid=*/1, /*thread=*/nullptr,
        BCI_ALLOC, /*event=*/nullptr, /*deferred=*/false);
}

TEST(ProfilerNullCalltraceBufferTest, RecordExternalSampleNullBufferDoesNotCrash) {
    ASGCT_CallFrame frame{};
    Profiler::instance()->recordExternalSample(
        /*weight=*/1, /*tid=*/1, /*num_frames=*/1,
        &frame, /*truncated=*/false, BCI_ALLOC, /*event=*/nullptr);
}

TEST(ProfilerNullCalltraceBufferTest, RecordSampleReturnsFalseWithoutActiveRecording) {
    ExecutionEvent event;
    bool recorded = Profiler::instance()->recordSample(
        /*ucontext=*/nullptr, /*weight=*/1, /*tid=*/1,
        BCI_WALL, /*call_trace_id=*/1, &event);

    EXPECT_FALSE(recorded);
}
