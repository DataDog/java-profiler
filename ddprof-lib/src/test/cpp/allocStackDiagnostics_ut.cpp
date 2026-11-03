/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <algorithm>
#include <array>
#include <vector>
#include "counters.h"
#include "hotspot/vmStructs.inline.h"
#include "jvmThread.h"
#include "profiler.h"
#include "threadLocalData.inline.h"

class VMTestAccessor {
public:
    struct State { JavaVM* vm; jvmtiEnv* jvmti; bool hotspot; int java_version; int hotspot_version; };
    static State state() { return {VM::_vm, VM::_jvmti, VM::_hotspot, VM::_java_version, VM::_hotspot_version}; }
    static void state(State s) {
        VM::_vm = s.vm; VM::_jvmti = s.jvmti; VM::_hotspot = s.hotspot;
        VM::_java_version = s.java_version; VM::_hotspot_version = s.hotspot_version;
    }
};

class JVMThreadTestAccessor {
public:
    static jfieldID tid() { return JVMThread::_tid; }
    static void install(pthread_key_t key, jfieldID tid) {
        JVMThread::_tid = tid; JVMThread::_jvm_thread._key = key;
    }
};

class ProfilerTestAccessor {
public:
    struct State {
        int depth;
        AllocStack mode;
        bool omit;
        std::array<CallTraceBuffer*, CONCURRENCY_LEVEL> buffers;
        std::array<size_t, CONCURRENCY_LEVEL> capacity;
    };
    static State state() {
        Profiler* p = Profiler::instance();
        State s{p->_max_stack_depth, p->_alloc_stack, p->_omit_stacktraces, {}, {}};
        for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
            s.buffers[i] = p->_calltrace_buffer[i]; s.capacity[i] = p->_calltrace_buffer_capacity[i];
        }
        return s;
    }
    static void state(const State& s) {
        Profiler* p = Profiler::instance();
        p->_max_stack_depth = s.depth; p->_alloc_stack = s.mode; p->_omit_stacktraces = s.omit;
        for (int i = 0; i < CONCURRENCY_LEVEL; i++) {
            p->_calltrace_buffer[i] = s.buffers[i]; p->_calltrace_buffer_capacity[i] = s.capacity[i];
        }
    }
    static void processTraces(std::function<void(const CallTraceSet&)> processor) {
        Profiler::instance()->_call_trace_storage.processTraces(processor);
    }
    // The storage holds no tables until a recording starts (acquire()); these
    // tests record samples without starting the profiler.
    static void acquireStorage() { Profiler::instance()->_call_trace_storage.acquire(); }
    static void releaseStorage() { Profiler::instance()->_call_trace_storage.release(); }
    static void verify(const ASGCT_CallFrame* frames, int count, int max_depth) {
        std::vector<jvmtiFrameInfo> scratch(CallTraceBuffer::verificationDepth(max_depth));
        Profiler::verifyAllocStack(frames, count, reinterpret_cast<jthread>(1), max_depth, scratch.data());
    }
};

namespace {
std::vector<jvmtiFrameInfo> expected;
jvmtiError stack_error = JVMTI_ERROR_NONE;
int stack_calls = 0;
JNINativeInterface_ jni_table{};
JNIEnv jni_env{&jni_table};

jint JNICALL getEnv(JavaVM*, void** out, jint) { *out = &jni_env; return JNI_OK; }
jvmtiError JNICALL getStackTrace(jvmtiEnv*, jthread, jint start, jint limit,
                                 jvmtiFrameInfo* out, jint* count) {
    stack_calls++;
    if (stack_error != JVMTI_ERROR_NONE) return stack_error;
    *count = std::min(limit, static_cast<jint>(expected.size()) - start);
    for (int i = 0; i < *count; i++) out[i] = expected[start + i];
    return JVMTI_ERROR_NONE;
}

ASGCT_CallFrame frame(int method = 1, int bci = 7) {
    ASGCT_CallFrame f{};
    f.method_id = reinterpret_cast<jmethodID>(method);
    f.bci = FrameType::encode(FRAME_JIT_COMPILED, bci);
    return f;
}
}

class AllocStackDiagnosticsTest : public ::testing::Test, protected VMStructs {
protected:
    VMTestAccessor::State old_vm{};
    ProfilerTestAccessor::State old_profiler{};
    JNIInvokeInterface_ vm_table{};
    JavaVM vm{&vm_table};
    jvmtiInterface_1_ jvmti_table{};
    jvmtiEnv jvmti{&jvmti_table};
    pthread_key_t old_key = INVALID_KEY, key = INVALID_KEY;
    jfieldID old_tid = nullptr;
    uint64_t old_thread_size = 0, old_anchor_size = 0;
    offset old_anchor_offset = -1, old_sp_offset = -1;
    uintptr_t anchor_sp = 0;
    std::vector<CallTraceBuffer> buffer;

    void SetUp() override {
        old_vm = VMTestAccessor::state();
        old_profiler = ProfilerTestAccessor::state();
        vm_table.GetEnv = getEnv;
        jvmti_table.GetStackTrace = getStackTrace;
        VMTestAccessor::state({&vm, &jvmti, true, 17, 17});
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        ProfiledThread::current()->setJavaThread(true);
        old_key = JVMThread::key(); old_tid = JVMThreadTestAccessor::tid();
        ASSERT_EQ(0, pthread_key_create(&key, nullptr));
        ASSERT_EQ(0, pthread_setspecific(key, &anchor_sp));
        JVMThreadTestAccessor::install(key, reinterpret_cast<jfieldID>(1));
        old_thread_size = TYPE_SIZE_NAME(VMThread); old_anchor_size = TYPE_SIZE_NAME(VMJavaFrameAnchor);
        old_anchor_offset = _thread_anchor_offset; old_sp_offset = _anchor_sp_offset;
        TYPE_SIZE_NAME(VMThread) = sizeof(anchor_sp); TYPE_SIZE_NAME(VMJavaFrameAnchor) = sizeof(anchor_sp);
        _thread_anchor_offset = 0; _anchor_sp_offset = 0;
        buffer.resize(CallTraceBuffer::capacity(8, ALLOCSTACK_VM));
        auto state = old_profiler;
        state.depth = 8; state.mode = ALLOCSTACK_VM; state.omit = false;
        state.buffers.fill(buffer.data()); state.capacity.fill(buffer.size());
        ProfilerTestAccessor::state(state);
        ProfilerTestAccessor::acquireStorage();
        Counters::set(ALLOC_STACK_VERIFIED, 0); Counters::set(ALLOC_STACK_MISMATCH, 0);
        Counters::set(ALLOC_STACK_VM_FALLBACK, 0); Counters::set(ALLOC_STACK_VM, 0);
        stack_error = JVMTI_ERROR_NONE; stack_calls = 0;
        expected = {{reinterpret_cast<jmethodID>(1), 7}};
    }

    void TearDown() override {
        ProfilerTestAccessor::releaseStorage();
        ProfilerTestAccessor::state(old_profiler);
        _thread_anchor_offset = old_anchor_offset; _anchor_sp_offset = old_sp_offset;
        TYPE_SIZE_NAME(VMThread) = old_thread_size; TYPE_SIZE_NAME(VMJavaFrameAnchor) = old_anchor_size;
        JVMThreadTestAccessor::install(old_key, old_tid);
        if (key != INVALID_KEY) pthread_key_delete(key);
        ProfiledThread::release();
        VMTestAccessor::state(old_vm);
    }

    void assertCounts(long long checked, long long mismatches) {
        EXPECT_EQ(checked, Counters::getCounter(ALLOC_STACK_VERIFIED));
        EXPECT_EQ(mismatches, Counters::getCounter(ALLOC_STACK_MISMATCH));
    }
};

TEST_F(AllocStackDiagnosticsTest, MatchingFramesCountOneCheckWithoutMismatch) {
    ASGCT_CallFrame f = frame();
    ProfilerTestAccessor::verify(&f, 1, 8);
    assertCounts(1, 0);
}

TEST_F(AllocStackDiagnosticsTest, MethodMismatchAloneIsDetected) {
    ASGCT_CallFrame f = frame(2, 7);
    ProfilerTestAccessor::verify(&f, 1, 8);
    assertCounts(1, 1);
}

TEST_F(AllocStackDiagnosticsTest, BytecodeMismatchAloneIsDetected) {
    ASGCT_CallFrame f = frame(1, 8);
    ProfilerTestAccessor::verify(&f, 1, 8);
    assertCounts(1, 1);
}

TEST_F(AllocStackDiagnosticsTest, CountMismatchBelowTheComparisonLimitIsDetected) {
    ASGCT_CallFrame frames[2] = {frame(), frame()};
    ProfilerTestAccessor::verify(frames, 2, 8);
    assertCounts(1, 1);
    expected.push_back(expected[0]);
    ProfilerTestAccessor::verify(frames, 1, 8);
    assertCounts(2, 2);
}

TEST_F(AllocStackDiagnosticsTest, FilledComparisonWindowChecksOnlyItsPrefix) {
    std::vector<ASGCT_CallFrame> frames(1025, frame());
    expected.resize(1024, expected[0]);
    ProfilerTestAccessor::verify(frames.data(), frames.size(), 2048);
    assertCounts(1, 0);
}

TEST_F(AllocStackDiagnosticsTest, FailedJvmtiCallDoesNotCountAsChecked) {
    stack_error = JVMTI_ERROR_INTERNAL;
    ASGCT_CallFrame f = frame();
    ProfilerTestAccessor::verify(&f, 1, 8);
    assertCounts(0, 0);
}

TEST_F(AllocStackDiagnosticsTest, ZeroFramePlatformWalkCountsJvmtiFallback) {
    u64 trace = Profiler::instance()->recordJVMTISample(1, 1, reinterpret_cast<jthread>(1),
                                                     BCI_ALLOC, nullptr, true);
    EXPECT_NE(0u, trace);
    EXPECT_EQ(1, stack_calls);
    EXPECT_EQ(1, Counters::getCounter(ALLOC_STACK_VM_FALLBACK));
    EXPECT_EQ(0, Counters::getCounter(ALLOC_STACK_VM));
    EXPECT_FALSE(ProfiledThread::current()->isProtected());
}

TEST_F(AllocStackDiagnosticsTest, JvmtiTruncationRequiresAFrameBeyondTheLimit) {
    for (int count : {8, 9}) {
        expected.resize(count, expected[0]);
        auto state = ProfilerTestAccessor::state();
        state.mode = ALLOCSTACK_JVMTI;
        ProfilerTestAccessor::state(state);
        u64 id = Profiler::instance()->recordJVMTISample(1, 1, reinterpret_cast<jthread>(1),
                                                        BCI_ALLOC, nullptr, true);
        bool found = false;
        ProfilerTestAccessor::processTraces([&](const CallTraceSet& traces) {
            for (const CallTrace* trace : traces) {
                if (trace->trace_id == id) {
                    found = true;
                    EXPECT_EQ(8, trace->num_frames);
                    EXPECT_EQ(count > 8, trace->truncated);
                }
            }
        });
        EXPECT_TRUE(found);
    }
}
