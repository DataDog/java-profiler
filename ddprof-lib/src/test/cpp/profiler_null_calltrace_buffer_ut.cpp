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

class VMTestAccessor {
public:
    static JavaVM* vm() { return VM::_vm; }
    static void setVm(JavaVM* vm) { VM::_vm = vm; }
};

class ProfilerTestAccessor {
public:
    static u64 skipped() { return Profiler::instance()->_failures[-ticks_skipped]; }
    static bool bufferIsNull(int stripe) { return Profiler::instance()->_calltrace_buffer[stripe] == nullptr; }
    static bool omitStacktraces() { return Profiler::instance()->_omit_stacktraces; }
    static void setOmitStacktraces(bool omit) { Profiler::instance()->_omit_stacktraces = omit; }
    static void releaseRecordingMemory() { Profiler::instance()->releaseRecordingMemory(); }
};

namespace {
// No thread is attached: releaseRecordingMemory() gets a null JNIEnv, which the
// never-initialized LivenessTracker does not use.
jint JNICALL detachedGetEnv(JavaVM*, void** env, jint) { *env = nullptr; return JNI_EDETACHED; }
}

// thread=nullptr is safe: GetStackTrace is never reached when the buffer is null.
TEST(ProfilerNullCalltraceBufferTest, RecordJvmtiSampleNullBufferDoesNotCrash) {
    Profiler::instance()->recordJVMTISample(
        /*counter=*/1, /*tid=*/1, /*thread=*/nullptr,
        BCI_ALLOC, /*event=*/nullptr, /*deferred=*/false,
        Profiler::instance()->recordingEpoch());
}

TEST(ProfilerNullCalltraceBufferTest, RecordExternalSampleNullBufferDoesNotCrash) {
    ASGCT_CallFrame frame{};
    Profiler::instance()->recordExternalSample(
        /*weight=*/1, /*tid=*/1, /*num_frames=*/1,
        &frame, /*truncated=*/false, BCI_ALLOC, /*event=*/nullptr);
}

// Without a stripe buffer the walk has nowhere to put frames: the sample is
// dropped and counted, not dereferenced.
TEST(ProfilerNullCalltraceBufferTest, RecordSampleNullBufferDropsSample) {
    for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
        ASSERT_TRUE(ProfilerTestAccessor::bufferIsNull(i));
    }
    ASSERT_FALSE(ProfilerTestAccessor::omitStacktraces());
    u64 skipped = ProfilerTestAccessor::skipped();

    EXPECT_FALSE(Profiler::instance()->recordSample(
        /*ucontext=*/nullptr, /*counter=*/1, /*tid=*/1, BCI_CPU,
        /*call_trace_id=*/0, /*event=*/nullptr, /*recorded_call_trace_id=*/nullptr));

    EXPECT_EQ(skipped + 1, ProfilerTestAccessor::skipped());
}

// An allocation callback that read the epoch before a stop() must not emit
// into the next recording. With stacktraces omitted the sample needs no buffer,
// so only the epoch check can drop it.
TEST(ProfilerNullCalltraceBufferTest, ReleaseRecordingMemoryInvalidatesEarlierEpoch) {
    JNIInvokeInterface_ vm_table{};
    vm_table.GetEnv = detachedGetEnv;
    JavaVM vm{&vm_table};
    JavaVM* saved_vm = VMTestAccessor::vm();
    bool saved_omit = ProfilerTestAccessor::omitStacktraces();
    VMTestAccessor::setVm(&vm);
    ProfilerTestAccessor::setOmitStacktraces(true);
    Profiler* profiler = Profiler::instance();
    u32 before = profiler->recordingEpoch();
    u64 skipped = ProfilerTestAccessor::skipped();

    profiler->recordJVMTISample(1, 1, nullptr, BCI_ALLOC, nullptr, /*deferred=*/true, before);
    EXPECT_EQ(skipped, ProfilerTestAccessor::skipped()) << "a current epoch must be accepted";
    // A parked thread's wall-clock trace id, cached in the recording being released.
    ProfiledThread* parked = ProfiledThread::forTid(1);
    parked->lookupWallclockCallTraceId(0x1000, 0x2000, before, true, 0, 0);
    parked->recordCallTraceId(42);
    ASSERT_EQ(42u, parked->lookupWallclockCallTraceId(0x1000, 0x2000, before, true, 0, 0));

    ProfilerTestAccessor::releaseRecordingMemory();
    u32 after = profiler->recordingEpoch();
    EXPECT_NE(before, after);
    // The storage holding trace 42 is gone: the next start() must not reuse it.
    EXPECT_EQ(0u, parked->lookupWallclockCallTraceId(0x1000, 0x2000, after, true, 0, 0));

    profiler->recordJVMTISample(1, 1, nullptr, BCI_ALLOC, nullptr, /*deferred=*/true, before);
    EXPECT_EQ(skipped + 1, ProfilerTestAccessor::skipped()) << "a stale epoch must be dropped";
    profiler->recordJVMTISample(1, 1, nullptr, BCI_ALLOC, nullptr, /*deferred=*/true, after);
    EXPECT_EQ(skipped + 1, ProfilerTestAccessor::skipped());

    ProfilerTestAccessor::setOmitStacktraces(saved_omit);
    VMTestAccessor::setVm(saved_vm);
}
