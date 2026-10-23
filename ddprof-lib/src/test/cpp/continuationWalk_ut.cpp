/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <ucontext.h>
#include "callTraceHashTable.h"
#include "codeCache.h"
#include "counters.h"
#include "dwarf.h"
#include "flightRecorder.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.h"
#include "jvmThread.h"
#include "libraries.h"
#include "stackFrame.h"
#include "threadLocalData.inline.h"

class JVMThreadTestAccessor {
public:
    static jfieldID tid() { return JVMThread::_tid; }
    static void install(pthread_key_t key, jfieldID tid) {
        JVMThread::_tid = tid;
        JVMThread::_jvm_thread._key = key;
    }
};

class VMTestAccessor {
public:
    static bool hotspot() { return VM::_hotspot; }
    static int version() { return VM::_hotspot_version; }
    static void install(bool hotspot, int version) {
        VM::_hotspot = hotspot;
        VM::_hotspot_version = version;
    }
};

class HotspotSupportTestAccessor {
public:
    static int walk(void* context, ASGCT_CallFrame* frames, StackWalkFeatures features,
                    int max_depth, bool* truncated) {
        return HotspotSupport::walkVM(context, frames, max_depth, features,
                                     EXECUTION_SAMPLE, 0, truncated);
    }
};

class RecordingTestAccessor {
public:
    static void writeHeader(Buffer* buffer, const CallTrace* trace, const MethodInfo* root) {
        Recording::writeStackTraceHeader(buffer, trace, root);
    }
};

namespace {

const char* const CODE_BASE = (const char*)0x5a6c00000000ULL;
const char* const LEAF_PC = CODE_BASE + 0x108;
const char* const BOUNDARY_PC = CODE_BASE + 0x208;
const char* const CARRIER_PC = CODE_BASE + 0x308;
const char* const THREAD_ENTRY_PC = CODE_BASE + 0x408;

bool isThreadEntry(const char* name) { return strcmp(name, "continuation_thread_entry") == 0; }

// The code heap contains the boundary PC, but none of its heaps owns an nmethod
// there. Native frames before/after it use an explicit SP-based unwind row.
// This drives the real nm == NULL branch and successful carrier recovery without
// depending on a particular installed JVM's continuation metadata exports.
class ContinuationWalkTest : public ::testing::Test, protected VMStructs {
protected:
    static constexpr int MAX_DEPTH = 8;
    struct ThreadLayout { void* entry; } thread{};
    alignas(16) uintptr_t stack[32]{};
    int entry_frame_size = 8;
    ASGCT_CallFrame frames[MAX_DEPTH + 1]{};

    static void SetUpTestSuite() {
        static CodeCache library("continuation_walk", -1, CODE_BASE, CODE_BASE + 0x1000);
        library.add(CODE_BASE + 0x100, 0x20, "continuation_sampled_leaf");
        library.add(CODE_BASE + 0x300, 0x20, "continuation_carrier");
        library.add(CODE_BASE + 0x400, 0x20, "continuation_thread_entry");
        library.mark(isThreadEntry, MARK_THREAD_ENTRY);
        library.sort();
        static const FrameDesc row{0, DW_REG_SP | (2 * sizeof(uintptr_t) << 8),
                                   -2 * (int)sizeof(uintptr_t), -(int)sizeof(uintptr_t), 0};
        library.setDwarfTable(nullptr, 0, row);
        ASSERT_TRUE(Libraries::instance()->addLibraryForTest(&library));
    }

    void SetUp() override {
        old_hotspot = VMTestAccessor::hotspot();
        old_version = VMTestAccessor::version();
        old_key = JVMThread::key();
        old_tid = JVMThreadTestAccessor::tid();
        old_low = _code_heap_low;
        old_high = _code_heap_high;
        old_barrier = _cont_return_barrier;
        old_return_pc = _cont_entry_return_pc;
        old_entry_offset = _cont_entry_offset;
        old_frame_size_offset = _frame_size_offset;
        old_entry_nm = _enter_special_nm;
        old_entry_size = TYPE_SIZE_NAME(VMContinuationEntry);
        old_thread_size = TYPE_SIZE_NAME(VMThread);
        ASSERT_EQ(0, pthread_key_create(&owned_key, nullptr));
        ASSERT_EQ(0, pthread_setspecific(owned_key, &thread));
        VMTestAccessor::install(true, 27);
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        // No Java frames need decoding: only the thread's exported entry field
        // is read. Suppress vtable/anchor introspection on this synthetic thread.
        ProfiledThread::current()->setJavaThread(false);
        thread.entry = &stack[6];
        JVMThreadTestAccessor::install(owned_key, (jfieldID)1);
        _cont_entry_offset = offsetof(ThreadLayout, entry);
        _frame_size_offset = 0;
        _enter_special_nm = VMNMethod::cast_raw(&entry_frame_size);
        TYPE_SIZE_NAME(VMThread) = sizeof(ThreadLayout);
        TYPE_SIZE_NAME(VMContinuationEntry) = 0;
        _code_heap_low = CODE_BASE + 0x200;
        _code_heap_high = CODE_BASE + 0x220;
        _cont_return_barrier = nullptr;
        _cont_entry_return_pc = CODE_BASE + 0x210; // deliberately does not match
    }

    void TearDown() override {
        _code_heap_low = old_low;
        _code_heap_high = old_high;
        _cont_return_barrier = old_barrier;
        _cont_entry_return_pc = old_return_pc;
        _cont_entry_offset = old_entry_offset;
        _frame_size_offset = old_frame_size_offset;
        _enter_special_nm = old_entry_nm;
        TYPE_SIZE_NAME(VMContinuationEntry) = old_entry_size;
        TYPE_SIZE_NAME(VMThread) = old_thread_size;
        JVMThreadTestAccessor::install(old_key, old_tid);
        if (owned_key != INVALID_KEY) pthread_key_delete(owned_key);
        VMTestAccessor::install(old_hotspot, old_version);
        ProfiledThread::release();
    }

    int walk(bool carrier_frames, bool* truncated, bool frozen = false,
             bool valid_carrier = true, int max_depth = MAX_DEPTH) {
        // First native frame recovers a boundary PC plus the bottom VT FP.
        // A frozen crossing must not depend on the saved FP being a pointer.
        stack[0] = frozen ? 1 : (uintptr_t)&stack[8];
        stack[1] = (uintptr_t)BOUNDARY_PC;
        int entry_fp = frozen ? 12 : 8;
        entry_frame_size = frozen ? 12 : 8;
        stack[entry_fp] = valid_carrier ? (uintptr_t)&stack[24] : 0;
        stack[entry_fp + FRAME_PC_SLOT] = (uintptr_t)CARRIER_PC;
        int carrier_sp = entry_fp + FRAME_PC_SLOT + 1;
        stack[carrier_sp] = (uintptr_t)&stack[26];
        stack[carrier_sp + 1] = (uintptr_t)THREAD_ENTRY_PC;
        ucontext_t context{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 machine_context{};
        context.uc_mcontext = &machine_context;
#endif
        StackFrame frame(&context);
        frame.pc() = (uintptr_t)LEAF_PC;
        frame.sp() = (uintptr_t)stack;
        frame.fp() = (uintptr_t)&stack[8];
        StackWalkFeatures features{};
        features.carrier_frames = carrier_frames;
        return HotspotSupportTestAccessor::walk(&context, frames, features, max_depth, truncated);
    }

    void assertCarrier(int depth) {
        ASSERT_EQ(2, depth);
        EXPECT_EQ(BCI_NATIVE_FRAME, frames[0].bci);
        EXPECT_EQ(BCI_NATIVE_FRAME, frames[1].bci);
        EXPECT_STREQ("continuation_sampled_leaf", (const char*)frames[0].method_id);
        EXPECT_STREQ("continuation_carrier", (const char*)frames[1].method_id);
    }

    bool old_hotspot;
    int old_version;
    pthread_key_t old_key;
    pthread_key_t owned_key = INVALID_KEY;
    jfieldID old_tid;
    const void *old_low, *old_high, *old_barrier, *old_return_pc;
    int old_entry_offset;
    int old_frame_size_offset;
    VMNMethod* old_entry_nm;
    uint64_t old_entry_size;
    uint64_t old_thread_size;
};

TEST_F(ContinuationWalkTest, SpeculativeCrossingRetainsCarrierAndSerializesTruncation) {
    bool truncated = false;
    auto before = Counters::getCounter(WALKVM_CONT_SPECULATIVE_HIT);
    auto frozen_failed = Counters::getCounter(WALKVM_FROZEN_FAILED);
    auto frozen_recovered = Counters::getCounter(WALKVM_FROZEN_RECOVERED);
    int depth = walk(true, &truncated);
    assertCarrier(depth);
    EXPECT_EQ(before + 1, Counters::getCounter(WALKVM_CONT_SPECULATIVE_HIT));
    EXPECT_EQ(frozen_failed, Counters::getCounter(WALKVM_FROZEN_FAILED));
    EXPECT_EQ(frozen_recovered, Counters::getCounter(WALKVM_FROZEN_RECOVERED));
    ASSERT_TRUE(truncated);

    // A successful carrier walk may ultimately end at a Java Thread.run root.
    // Feed that resolved root and the actual walker's flag to the production
    // stack-pool header encoder, not a second copy of its completeness rule.
    CallTrace trace(truncated, depth, 42);
    MethodInfo root;
    root._type = FRAME_INTERPRETED;
    root._is_entry = true;
    Buffer buffer;
    RecordingTestAccessor::writeHeader(&buffer, &trace, &root);
    ASSERT_EQ(3, buffer.offset());
    EXPECT_EQ(42, (unsigned char)buffer.data()[0]);
    EXPECT_EQ(1, (unsigned char)buffer.data()[1]);
    EXPECT_EQ(depth, (unsigned char)buffer.data()[2]);
}

TEST_F(ContinuationWalkTest, VerifiedThawedCrossingRetainsCarrierWithoutTruncation) {
    _cont_entry_return_pc = BOUNDARY_PC;
    bool truncated = false;
    assertCarrier(walk(true, &truncated));
    EXPECT_FALSE(truncated);
}

TEST_F(ContinuationWalkTest, VerifiedFrozenCrossingRetainsCarrierAndTruncates) {
    _cont_return_barrier = BOUNDARY_PC;
    // This fixture decodes no Java frames, so it cannot supply stack arguments
    // for SP-based recovery. Use the exported entry layout for this crossing;
    // the Java partial-thaw regressions exercise recovery without that layout.
    TYPE_SIZE_NAME(VMContinuationEntry) = 6 * sizeof(uintptr_t);
    bool truncated = false;
    assertCarrier(walk(true, &truncated, true));
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, FrozenBoundaryWithoutJavaFrameMetadataRejectsSpRecovery) {
    _cont_return_barrier = BOUNDARY_PC;
    bool truncated = false;
    ASSERT_EQ(2, walk(true, &truncated, true));
    EXPECT_EQ(BCI_ERROR, frames[1].bci);
    EXPECT_STREQ("break_cont_entry_fp", (const char*)frames[1].method_id);
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, FrozenBoundaryWithoutEntryMetadataRejectsFpFallback) {
    _cont_return_barrier = BOUNDARY_PC;
    _enter_special_nm = nullptr;
    bool truncated = false;
    ASSERT_EQ(2, walk(true, &truncated, true));
    EXPECT_EQ(BCI_ERROR, frames[1].bci);
    EXPECT_STREQ("break_cont_entry_fp", (const char*)frames[1].method_id);
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, ExportedEntryLayoutRetainsCarrierAndTruncates) {
    TYPE_SIZE_NAME(VMContinuationEntry) = 2 * sizeof(uintptr_t);
    bool truncated = false;
    assertCarrier(walk(true, &truncated));
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, FrozenBoundaryWithoutCarrierFramesTruncates) {
    _cont_return_barrier = BOUNDARY_PC;
    bool truncated = false;
    ASSERT_EQ(2, walk(false, &truncated, true));
    EXPECT_STREQ("JVM Continuation", (const char*)frames[1].method_id);
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, VerifiedThawedBoundaryPreservesExistingTruncation) {
    _cont_entry_return_pc = BOUNDARY_PC;
    bool truncated = true;
    assertCarrier(walk(true, &truncated));
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, SpeculativeCarrierFailureIsTruncated) {
    bool truncated = false;
    ASSERT_EQ(2, walk(true, &truncated, false, false));
    EXPECT_EQ(BCI_ERROR, frames[1].bci);
    EXPECT_STREQ("break_cont_carrier_sp", (const char*)frames[1].method_id);
    EXPECT_TRUE(truncated);
}

TEST_F(ContinuationWalkTest, SpeculativeCrossingAcceptsNullTruncationPointer) {
    assertCarrier(walk(true, nullptr));
}

} // namespace
