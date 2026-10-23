/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <tuple>
#include <vector>
#include <ucontext.h>
#include "codeCache.h"
#include "counters.h"
#include "dwarf.h"
#include "event.h"
#include "gtest_crash_handler.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.inline.h"
#include "jvmThread.h"
#include "libraries.h"
#include "os.h"
#include "profiler.h"

// Install the same thread-local state that a JVM attach normally publishes.
class VMTestAccessor {
    bool _hotspot = VM::_hotspot;
    jfieldID _tid = JVMThread::_tid;
    void* _thread = JVMThread::_jvm_thread.isKeyValid() ? pthread_getspecific(JVMThread::key()) : nullptr;
public:
    explicit VMTestAccessor(void* thread) {
        VM::_hotspot = true;
        JVMThread::_tid = reinterpret_cast<jfieldID>(1);
        if (!JVMThread::_jvm_thread.isKeyValid()) {
            pthread_key_t key;
            int result = pthread_key_create(&key, nullptr);
            assert(result == 0);
            result = pthread_setspecific(key, thread);
            assert(result == 0);
            bool initialized = JVMThread::_jvm_thread.initialize(thread);
            assert(initialized);
        }
        pthread_setspecific(JVMThread::key(), thread);
    }
    ~VMTestAccessor() {
        pthread_setspecific(JVMThread::key(), _thread);
        JVMThread::_tid = _tid;
        VM::_hotspot = _hotspot;
    }
};

class HotspotSupportTestAccessor {
public:
    static int walk(void* context, ASGCT_CallFrame* frames, int capacity,
                    StackWalkFeatures features, bool* truncated) {
        return HotspotSupport::walkVM(context, frames, capacity, features,
                                      WALL_CLOCK_SAMPLE, 0, truncated);
    }
};

namespace {
struct Anchor { uintptr_t sp; const void* pc; uintptr_t fp; };
struct TestJavaThread { Anchor anchor; void* vframe; };
struct Klass { jmethodID* ids; };
struct Pool { Klass* holder; };
struct ConstMethod { Pool* pool; unsigned short id; };
struct Method { ConstMethod* const_method; };
struct Blob {
    const char* name;
    int size;
    int frame_size;
    short complete;
    Method* method;
    const char* code;
    int scopes[2];
};
struct Heap { const void* low; const void* high; const void* segmap; };
}

// Synthetic VM metadata feeds the real Java-frame and anchor-recovery branches;
// no recovery policy or output frames are mocked.
class VMStructsTestAccessor {
    std::vector<std::pair<int*, int>> _offsets;
    std::vector<std::pair<uint64_t*, uint64_t>> _sizes;
    const void* _low = VMStructs::_code_heap_low;
    const void* _high = VMStructs::_code_heap_high;
    char* _heap = VMStructs::_code_heap[0];
    VMNMethod* _interpreter = VMStructs::_interpreter_nm;

    void set(int& field, int value) {
        _offsets.emplace_back(&field, field);
        field = value;
    }
    void size(uint64_t& field, uint64_t value) {
        _sizes.emplace_back(&field, field);
        field = value;
    }
public:
    VMStructsTestAccessor(Heap* heap, VMNMethod* interpreter) {
        set(VMStructs::_thread_anchor_offset, offsetof(TestJavaThread, anchor));
        set(VMStructs::_thread_vframe_offset, offsetof(TestJavaThread, vframe));
        set(VMStructs::_anchor_sp_offset, offsetof(Anchor, sp));
        set(VMStructs::_anchor_pc_offset, offsetof(Anchor, pc));
        set(VMStructs::_anchor_fp_offset, offsetof(Anchor, fp));
        set(VMStructs::_method_constmethod_offset, offsetof(Method, const_method));
        set(VMStructs::_constmethod_constants_offset, offsetof(ConstMethod, pool));
        set(VMStructs::_constmethod_idnum_offset, offsetof(ConstMethod, id));
        set(VMStructs::_pool_holder_offset, offsetof(Pool, holder));
        set(VMStructs::_jmethod_ids_offset, offsetof(Klass, ids));
        set(VMStructs::_nmethod_name_offset, offsetof(Blob, name));
        set(VMStructs::_blob_size_offset, offsetof(Blob, size));
        set(VMStructs::_frame_size_offset, offsetof(Blob, frame_size));
        set(VMStructs::_frame_complete_offset, offsetof(Blob, complete));
        set(VMStructs::_nmethod_method_offset, offsetof(Blob, method));
        set(VMStructs::_code_address, offsetof(Blob, code));
        set(VMStructs::_code_offset, -1);
        set(VMStructs::_nmethod_entry_address, offsetof(Blob, code));
        set(VMStructs::_nmethod_entry_offset, -1);
        set(VMStructs::_scopes_pcs_offset, offsetof(Blob, scopes));
        set(VMStructs::_interpreter_frame_bcp_offset, -4);
        set(VMStructs::_code_heap_memory_offset, 0);
        set(VMStructs::_vs_low_offset, offsetof(Heap, low));
        set(VMStructs::_vs_high_offset, offsetof(Heap, high));
        set(VMStructs::_code_heap_segmap_offset, offsetof(Heap, segmap));
        set(VMStructs::_code_heap_segment_shift, 8);
        set(VMStructs::_heap_block_used_offset, 0);
        size(VMStructs::_VMThread_size, sizeof(TestJavaThread));
        size(VMStructs::_VMJavaFrameAnchor_size, sizeof(Anchor));
        size(VMStructs::_VMNMethod_size, sizeof(Blob));
        size(VMStructs::_VMMethod_size, sizeof(Method));
        size(VMStructs::_VMConstMethod_size, sizeof(ConstMethod));
        VMStructs::_code_heap_low = heap->low;
        VMStructs::_code_heap_high = heap->high;
        VMStructs::_code_heap[0] = reinterpret_cast<char*>(heap);
        VMStructs::_interpreter_nm = interpreter;
    }
    ~VMStructsTestAccessor() {
        for (auto& field : _offsets) *field.first = field.second;
        for (auto& field : _sizes) *field.first = field.second;
        VMStructs::_code_heap_low = _low;
        VMStructs::_code_heap_high = _high;
        VMStructs::_code_heap[0] = _heap;
        VMStructs::_interpreter_nm = _interpreter;
    }
};

namespace {
constexpr char TEST_NAME[] = "AnchorRecoveryTest";
const char* const NATIVE_PC = reinterpret_cast<const char*>(0x5a5c00000100ULL);
const char* const ROOT_PC = NATIVE_PC + 256;
const void* const GAP_PC = reinterpret_cast<const void*>(0x5a5d00000100ULL);
constexpr int JAVA_FRAME_WORDS = 8;

class AnchorRecoveryTest : public ::testing::TestWithParam<std::tuple<bool, bool>> {
protected:
    TestJavaThread _thread{};
    alignas(16) char _code_heap[256]{};
    unsigned char _segmap[1]{};
    Heap _heap{_code_heap, _code_heap + sizeof(_code_heap), _segmap};
    jmethodID _ids[2]{};
    Klass _klass{_ids};
    Pool _pool{&_klass};
    ConstMethod _const_method{&_pool, 0};
    Method _method{&_const_method};
    Method* _method_slot = &_method;
    VMTestAccessor* _vm = nullptr;
    VMStructsTestAccessor* _layout = nullptr;
    SigAction _segv = nullptr;
    SigAction _bus = nullptr;
    ASGCT_CallFrame _frames[17]{};
    bool _truncated = false;
    const void* _terminal_pc = GAP_PC;
    bool _bridge_gap = false;

    bool interpreted() const { return std::get<0>(GetParam()); }

    static void SetUpTestSuite() {
        static CodeCache native_lib("anchor_recovery_test", -1, NATIVE_PC, ROOT_PC + 16, NATIVE_PC);
        native_lib.add(NATIVE_PC, 16, "anchor_recovery_native");
        native_lib.add(ROOT_PC - 4, 20, "anchor_recovery_root");
        native_lib.sort();
        native_lib.mark([](const char* name) { return strcmp(name, "anchor_recovery_root") == 0; }, MARK_THREAD_ENTRY);
        static const FrameDesc step{0, DW_REG_SP | (JAVA_FRAME_WORDS * sizeof(uintptr_t)) << 8,
                                    DW_SAME_FP, -int(sizeof(uintptr_t)), 0};
        native_lib.setDwarfTable(nullptr, 0, step);
        ASSERT_TRUE(Libraries::instance()->addLibraryForTest(&native_lib));
    }

    void SetUp() override {
        installGtestCrashHandler<TEST_NAME>();
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        ProfiledThread::current()->setJavaThread(true);
        _segv = OS::replaceSigsegvHandler(Profiler::segvHandler);
        _bus = OS::replaceSigbusHandler(Profiler::busHandler);
        _vm = new VMTestAccessor(&_thread);
        _ids[0] = reinterpret_cast<jmethodID>(1);
        _ids[1] = reinterpret_cast<jmethodID>(&_method_slot);
        _code_heap[0] = 1; // HeapBlock::_used
        auto* blob = reinterpret_cast<Blob*>(_code_heap + sizeof(uintptr_t));
        *blob = Blob{"nmethod", 248, JAVA_FRAME_WORDS, 0, &_method, _code_heap + 128, {0, 0}};
        _layout = new VMStructsTestAccessor(&_heap, interpreted() ? reinterpret_cast<VMNMethod*>(blob) : nullptr);
        ASSERT_TRUE(JVMThread::isInitialized());
        ASSERT_EQ(&_thread, JVMThread::current());
        ASSERT_TRUE(VMThread::current()->isThreadAccessible());
        ASSERT_EQ(reinterpret_cast<VMJavaFrameAnchor*>(&_thread.anchor), VMThread::current()->anchor());
        ASSERT_EQ(reinterpret_cast<VMNMethod*>(blob), CodeHeap::findNMethod(_code_heap + 144));
    }

    void TearDown() override {
        delete _layout;
        delete _vm;
        OS::replaceSigsegvHandler(_segv);
        OS::replaceSigbusHandler(_bus);
        ProfiledThread::release();
        restoreDefaultSignalHandlers();
    }

    // Two Java frames followed by an unmapped native PC. Initial recovery
    // starts with native output only; late recovery has already emitted both
    // Java frames before it encounters the same gap.
    int walk(bool initial_gap, bool backward = false, int capacity = 16) {
        alignas(16) uintptr_t stack[128]{};
        const void* java_pc = _code_heap + 144;
        uintptr_t gap_fp = _bridge_gap ? reinterpret_cast<uintptr_t>(&stack[80]) : 0;
        _thread.anchor = Anchor{reinterpret_cast<uintptr_t>(&stack[32]), java_pc, 0};
        if (interpreted()) {
            _thread.anchor.fp = reinterpret_cast<uintptr_t>(&stack[40]);
            for (int index : {40, 64}) {
                stack[index - 4] = reinterpret_cast<uintptr_t>(&_const_method + 1);
                stack[index - 3] = reinterpret_cast<uintptr_t>(&_method);
                stack[index - 1] = reinterpret_cast<uintptr_t>(&stack[index + 8]);
                stack[index] = index == 40 ? reinterpret_cast<uintptr_t>(&stack[64]) : gap_fp;
                stack[index + FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(index == 40 ? java_pc : _terminal_pc);
            }
        } else {
            stack[40 - FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(java_pc);
            stack[48 - FRAME_PC_SLOT - 1] = gap_fp;
            stack[48 - FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(_terminal_pc);
        }
        if (_bridge_gap) {
            const FrameDesc& step = FrameDesc::fallback_default_frame();
            uintptr_t cfa = gap_fp + (step.cfa >> 8);
            *reinterpret_cast<uintptr_t*>(cfa + step.fp_off) = reinterpret_cast<uintptr_t>(&stack[96]);
            *reinterpret_cast<const void**>(cfa + step.pc_off) = ROOT_PC;
        }
        int native_sp = backward ? 96 : 8;
        stack[native_sp + JAVA_FRAME_WORDS - 1] = reinterpret_cast<uintptr_t>(initial_gap ? GAP_PC : java_pc);
        ucontext_t context{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 registers{};
        context.uc_mcontext = &registers;
#endif
        StackFrame frame(&context);
        frame.pc() = reinterpret_cast<uintptr_t>(NATIVE_PC);
        frame.sp() = reinterpret_cast<uintptr_t>(&stack[native_sp]);
        frame.fp() = 0;
        StackWalkFeatures features{};
        features.mixed = features.carrier_frames = std::get<1>(GetParam());
        return HotspotSupportTestAccessor::walk(&context, _frames, capacity, features, &_truncated);
    }

    int javaFrames(int depth) const {
        int count = 0;
        for (int i = 0; i < depth; i++) {
            count += _frames[i].method_id == _ids[1];
        }
        return count;
    }
};

TEST_P(AnchorRecoveryTest, LateNativeGapDoesNotReplayJavaCallers) {
    int depth = walk(false);
    EXPECT_EQ(2, javaFrames(depth)) << "the consumed Java-frame anchor must not replay callers";
}

TEST_P(AnchorRecoveryTest, InitialForwardRecoveryStillFindsJavaCallers) {
    int depth = walk(true);
    EXPECT_EQ(2, javaFrames(depth));
}

TEST_P(AnchorRecoveryTest, InitialBackwardRecoveryStillFindsJavaCallers) {
    int depth = walk(true, true);
    EXPECT_EQ(2, javaFrames(depth)) << "native unwinding may overshoot Java frames before any were captured";
}

TEST_P(AnchorRecoveryTest, ExactCapacityDoesNotFillWithReplayedFrames) {
    int depth = walk(false, false, 3);
    EXPECT_EQ(3, depth);
    EXPECT_EQ(2, javaFrames(depth));
}

TEST_P(AnchorRecoveryTest, CleanStackRemainsComplete) {
    _terminal_pc = ROOT_PC;
    int depth = walk(false);
    EXPECT_EQ(2, javaFrames(depth));
    EXPECT_FALSE(_truncated);
}

TEST_P(AnchorRecoveryTest, LateGapStillUsesFramePointersToReachRoot) {
    _bridge_gap = true;
    long long roots = Counters::getCounter(THREAD_ENTRY_MARK_DETECTIONS);
    int depth = walk(false);
    EXPECT_EQ(2, javaFrames(depth));
    EXPECT_EQ(roots + 1, Counters::getCounter(THREAD_ENTRY_MARK_DETECTIONS));
}

INSTANTIATE_TEST_SUITE_P(
    VmAndVmx, AnchorRecoveryTest,
    ::testing::Combine(::testing::Bool(), ::testing::Bool()),
    [](const ::testing::TestParamInfo<AnchorRecoveryTest::ParamType>& info) {
        return std::string(std::get<0>(info.param) ? "Interpreted" : "Compiled") +
               (std::get<1>(info.param) ? "Vmx" : "Vm");
    });
}
