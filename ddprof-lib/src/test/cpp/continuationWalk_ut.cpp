/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <array>
#include <cstddef>
#include <cstring>
#include <new>
#include <ucontext.h>
#include "callTraceHashTable.h"
#include "codeCache.h"
#include "counters.h"
#include "dwarf.h"
#include "flightRecorder.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/hotspotStackFrame.h"
#include "hotspot/jitCodeCache.h"
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

// The native walker inspects instructions at these synthetic PCs.
alignas(16) const char SYNTHETIC_CODE[0x1000] = {};
const char* const CODE_BASE = SYNTHETIC_CODE;
const char* const LEAF_PC = CODE_BASE + 0x108;
const char* const BOUNDARY_PC = CODE_BASE + 0x208;
const char* const CARRIER_PC = CODE_BASE + 0x308;
const char* const THREAD_ENTRY_PC = CODE_BASE + 0x408;

bool isThreadEntry(const char* name) { return strcmp(name, "continuation_thread_entry") == 0; }

template<typename T> class ScopedValue {
    T& _slot;
    T _previous;

public:
    ScopedValue(T& slot, T value) : _slot(slot), _previous(slot) { _slot = value; }
    ~ScopedValue() { _slot = _previous; }
    ScopedValue(const ScopedValue&) = delete;
    ScopedValue& operator=(const ScopedValue&) = delete;
};

// The code heap contains the boundary PC, but none of its heaps owns an nmethod
// there. Native frames before/after it use an explicit SP-based unwind row.
// This drives the real nm == NULL branch and successful carrier recovery without
// depending on a particular installed JVM's continuation metadata exports.
class ContinuationWalkTest : public ::testing::Test, protected VMStructs {
protected:
    static constexpr int MAX_DEPTH = 8;
    struct AnchorLayout { uintptr_t sp; uintptr_t fp; const void* pc; };
    struct ThreadLayout { void* entry; AnchorLayout anchor; void* vframe; } thread{};
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
        old_entry_thread_offset = _cont_entry_thread_offset;
        _cont_entry_thread_offset = -1;
        old_return_pc = _cont_entry_return_pc;
        old_entry_offset = _cont_entry_offset;
        old_frame_size_offset = _frame_size_offset;
        old_entry_nm = _enter_special_nm;
        old_anchor_offset = _thread_anchor_offset;
        old_anchor_sp = _anchor_sp_offset;
        old_anchor_fp = _anchor_fp_offset;
        old_anchor_pc = _anchor_pc_offset;
        old_vframe_offset = _thread_vframe_offset;
        old_anchor_size = TYPE_SIZE_NAME(VMJavaFrameAnchor);
        old_entry_size = TYPE_SIZE_NAME(VMContinuationEntry);
        old_thread_size = TYPE_SIZE_NAME(VMThread);
        old_java_thread_size = TYPE_SIZE_NAME(VMJavaThread);
        ASSERT_EQ(0, pthread_key_create(&owned_key, nullptr));
        ASSERT_EQ(0, pthread_setspecific(owned_key, &thread));
        VMTestAccessor::install(true, 27);
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        // No Java frames need decoding: only the thread's exported entry field
        // is read. Suppress vtable/anchor introspection on this synthetic thread.
        ProfiledThread::current()->setJavaThread(false);
        thread.entry = nullptr;
        JVMThreadTestAccessor::install(owned_key, (jfieldID)1);
        _cont_entry_offset = offsetof(ThreadLayout, entry);
        _frame_size_offset = 0;
        _enter_special_nm = VMNMethod::cast_raw(&entry_frame_size);
        _thread_anchor_offset = offsetof(ThreadLayout, anchor);
        _anchor_sp_offset = offsetof(AnchorLayout, sp);
        _anchor_fp_offset = offsetof(AnchorLayout, fp);
        _anchor_pc_offset = offsetof(AnchorLayout, pc);
        _thread_vframe_offset = offsetof(ThreadLayout, vframe);
        TYPE_SIZE_NAME(VMJavaFrameAnchor) = sizeof(AnchorLayout);
        TYPE_SIZE_NAME(VMThread) = sizeof(ThreadLayout);
        TYPE_SIZE_NAME(VMJavaThread) = sizeof(ThreadLayout);
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
        _cont_entry_thread_offset = old_entry_thread_offset;
        _cont_entry_return_pc = old_return_pc;
        _cont_entry_offset = old_entry_offset;
        _frame_size_offset = old_frame_size_offset;
        _enter_special_nm = old_entry_nm;
        _thread_anchor_offset = old_anchor_offset;
        _anchor_sp_offset = old_anchor_sp;
        _anchor_fp_offset = old_anchor_fp;
        _anchor_pc_offset = old_anchor_pc;
        _thread_vframe_offset = old_vframe_offset;
        TYPE_SIZE_NAME(VMJavaFrameAnchor) = old_anchor_size;
        TYPE_SIZE_NAME(VMContinuationEntry) = old_entry_size;
        TYPE_SIZE_NAME(VMThread) = old_thread_size;
        TYPE_SIZE_NAME(VMJavaThread) = old_java_thread_size;
        JVMThreadTestAccessor::install(old_key, old_tid);
        if (owned_key != INVALID_KEY) pthread_key_delete(owned_key);
        VMTestAccessor::install(old_hotspot, old_version);
        ProfiledThread::release();
    }

    int walk(bool carrier_frames, bool* truncated, bool frozen = false,
             bool valid_carrier = true, int max_depth = MAX_DEPTH, bool with_anchor = false) {
        // walkVM bounds SP relative to its own stack frame, so a heap-allocated
        // fixture member cannot represent the sampled thread's stack reliably.
        alignas(16) uintptr_t stack[32]{};
        thread.entry = &stack[6];
        thread.anchor = {(uintptr_t)&stack[2], 0, LEAF_PC};
        if (with_anchor) ProfiledThread::current()->setJavaThread(true);
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
        frame.pc() = (uintptr_t)(with_anchor ? BOUNDARY_PC : LEAF_PC);
        frame.sp() = (uintptr_t)stack;
        frame.fp() = (uintptr_t)&stack[8];
        StackWalkFeatures features{};
        features.carrier_frames = carrier_frames;
        return HotspotSupportTestAccessor::walk(&context, frames, features, max_depth, truncated);
    }

    enum class EntryPhase {
        BeforeSave, AfterSave, BeforeAllocation, Complete, BeforeSpRestore, AfterDeallocation, AfterRestore, AfterAllocation
    };
    enum class EntryCase {
        Native, CompiledNonPointerFp, NativeNonPointerFp, BlobNonPointerFp,
        InvalidPc, MisalignedSp, OutOfBoundsSp, InvalidFrameSize, ReturnPc, UnsupportedPrologue, ExportedParentEntry, PointerAuthentication,
        ExceptionMove, ExceptionBranch, AuthenticatedExceptionMove, AuthenticatedExceptionBranch,
        ExceptionMoveWithoutBranch, ExceptionBranchWithoutMove, InterpretedEntry, UnsupportedInterpretedEntry,
        LeafSpillBeforeSave, LeafSpillMove, LeafSpillCall, LeafSpillRestore, LeafSpillAfterRestore,
        LeafSpillOneMove, LeafSpillMovn, LeafSpillLogicalImmediate, LeafSpillFourMoves, LeafSpillNativePrefix,
        LeafSpillNativePrefixExportedNull, LeafSpillNativePrefixExportedParent, LeafSpillNativePrefixExportedTrackedChild,
        LeafSpillNativePrefixExportedInvalidSize, LeafSpillUnknownSequence,
        BarrierInterior, BarrierInteriorRoot, BarrierInteriorNativePrefix,
        X64ExceptionNativePrefixExportedNull, X64ExceptionNativePrefixExportedParent
    };

    // Generated prologue/setup and normal cleanup excerpts, captured from
    // Temurin 25.0.2 macOS aarch64 and 21.0.12.1 Linux x64 (PAC disabled).
    // These follow gen_continuation_enter/setup/cleanup in HotSpot's
    // cpu/{aarch64,x86}/sharedRuntime_*.cpp. The body between them is omitted.
    // Metadata and registers are synthetic; the production walker decodes them.
    void assertCarrierFromEntry(EntryPhase phase, EntryCase test_case = EntryCase::Native) {
        bool x64_exception_prefix = test_case == EntryCase::X64ExceptionNativePrefixExportedNull ||
                test_case == EntryCase::X64ExceptionNativePrefixExportedParent;
        bool tracked_child = test_case == EntryCase::LeafSpillNativePrefixExportedTrackedChild;
        bool invalid_exported_size = test_case == EntryCase::LeafSpillNativePrefixExportedInvalidSize;
        bool leaf_native_prefix = test_case == EntryCase::LeafSpillNativePrefix ||
                test_case == EntryCase::LeafSpillNativePrefixExportedNull || test_case == EntryCase::LeafSpillNativePrefixExportedParent || tracked_child || invalid_exported_size;
        alignas(16) uintptr_t stack_storage[52]{};
        uintptr_t* stack = stack_storage + 4; // room for a native frame and the temporary VM-leaf spill
        struct ConstMethod { void* constants = nullptr; unsigned short idnum = 0; unsigned short slots = 0; } const_method;
        struct Method { ConstMethod* const_method; } method{&const_method};
        struct NMethod {
            const char* name = "native nmethod";
            int frame_size = 10;
            int size = sizeof(NMethod);
            short frame_complete;
            const void* code_begin;
            const void* entry;
            Method* method;
            signed char level = 4;
            int scopes[2] = {offsetof(NMethod, code), offsetof(NMethod, code)};
            uint32_t code[32]{};
        };
        struct Blob { uintptr_t used = 1; NMethod nm; };
        static_assert(offsetof(Blob, nm) == sizeof(uintptr_t), "CodeHeap header precedes the blob");
        static_assert(sizeof(Blob) <= 512, "Each blob occupies one CodeHeap segment");
        bool barrier_interior = test_case == EntryCase::BarrierInterior || test_case == EntryCase::BarrierInteriorRoot ||
                test_case == EntryCase::BarrierInteriorNativePrefix;
        alignas(16) unsigned char local_heap_memory[1024]{};
        // Runtime-stub registrations are never removed. Keep each registered
        // range alive and distinct so later cases cannot overlap a stale entry.
        alignas(16) static unsigned char barrier_heap_memory[3][1024]{};
        unsigned char* heap_memory = barrier_interior
                ? barrier_heap_memory[(int)test_case - (int)EntryCase::BarrierInterior] : local_heap_memory;
        Blob& blob = *new (heap_memory) Blob;
        Blob& carrier = *new (heap_memory + 512) Blob;
#ifdef __aarch64__
        const uint32_t instructions[] = {
            0xa9bf7bfd,  // stp x29, x30, [sp, #-16]!
            0x910003fd,  // mov x29, sp
            0xd10103ff,  // sub sp, sp, #64
            0xf942d388,  // ldr x8, [x28, #1440]
            0xf90007e8,  // str x8, [sp, #8]
            0x910003e8,  // mov x8, sp
            0xf902d388,  // str x8, [x28, #1440]
            0xf9000be1,  // str x1, [sp, #16]: frame complete
            // Normal cleanup, following the omitted wrapper body.
            0xf94017e8, 0xf902d788, // restore parent fastpath
            0xf9401be8, 0xf902df88, // restore parent held-monitor count
            0xf94007e9, 0xf902d389, // restore parent ContinuationEntry
            0x910103fd,  // add x29, sp, #64
            0x910003bf,  // mov sp, x29
            0xa8c17bfd,  // ldp x29, x30, [sp], #16
            0xd65f03c0,  // ret
        };
        const int offsets[] = {0, 4, 8, 28, 60, 64, 68, 12};
#else
        const unsigned char instructions[] = {
            0x55,                    // push rbp
            0x48, 0x8b, 0xec,        // mov rbp, rsp
            0x48, 0x83, 0xec, 0x40,  // sub rsp, 64
            0x49, 0x8b, 0x87, 0x38, 0x05, 0x00, 0x00, // load parent ContinuationEntry
            0x48, 0x89, 0x44, 0x24, 0x08,             // save parent
            0x49, 0x89, 0xa7, 0x38, 0x05, 0x00, 0x00, // publish entry
            0x48, 0x89, 0x74, 0x24, 0x10,             // frame complete
            // Normal cleanup, following the omitted wrapper body.
            0x48, 0x8b, 0x5c, 0x24, 0x28,
            0x49, 0x89, 0x9f, 0x40, 0x05, 0x00, 0x00, // restore parent fastpath
            0x48, 0x8b, 0x5c, 0x24, 0x30,
            0x49, 0x89, 0x9f, 0x50, 0x05, 0x00, 0x00, // restore parent monitor count
            0x48, 0x8b, 0x5c, 0x24, 0x08,
            0x49, 0x89, 0x9f, 0x38, 0x05, 0x00, 0x00, // restore parent entry
            0x48, 0x83, 0xc4, 0x40,  // add rsp, 64
            0x5d,                    // pop rbp
            0xc3,                    // ret
        };
        const int offsets[] = {0, 1, 4, 27, 68, 72, 73, 8};
#endif
        memcpy(blob.nm.code, instructions, sizeof(instructions));
#ifdef __x86_64__
        if (x64_exception_prefix) {
            const unsigned char exception[] = {
                0x48, 0x83, 0xc4, 0x40, 0x5d, // cleanup and pop rbp
                0x49, 0x8b, 0xff, 0x48, 0x8b, 0x34, 0x24, // resolver arguments
                0x50, 0xe8, 0, 0, 0, 0, // push exception and call resolver
                0x48, 0x8b, 0xd8, 0x58, 0x5a, 0xff, 0xe3 // restore exception/PC, jump
            };
            memcpy((char*)blob.nm.code + 80, exception, sizeof(exception));
        }
#endif
        if (barrier_interior) {
            auto prefix = barrierInstructions();
            memcpy(blob.nm.code, prefix.data(), prefix.size());
            blob.nm.name = "StubRoutines";
        }
        blob.nm.frame_complete = offsets[(int)EntryPhase::Complete];
        blob.nm.code_begin = blob.nm.entry = blob.nm.code;
        carrier.nm.name = test_case == EntryCase::BlobNonPointerFp ? "RuntimeBlob" : "nmethod";
        carrier.nm.frame_size = 4;
        carrier.nm.frame_complete = 0;
        carrier.nm.code_begin = carrier.nm.entry = carrier.nm.code;
        carrier.nm.method = &method;
        if (barrier_interior) carrier.nm.frame_size = 10;
#ifdef __aarch64__
        carrier.nm.code[0] = 0xd503201f; // nop, not an epilogue
#else
        carrier.nm.code[0] = 0x90909090;
#endif
        int prefix = 0;
#ifdef __aarch64__
        bool exception_exit = test_case == EntryCase::ExceptionMove || test_case == EntryCase::ExceptionBranch ||
                test_case == EntryCase::AuthenticatedExceptionMove || test_case == EntryCase::AuthenticatedExceptionBranch ||
                test_case == EntryCase::ExceptionMoveWithoutBranch || test_case == EntryCase::ExceptionBranchWithoutMove;
        if (test_case == EntryCase::PointerAuthentication || test_case == EntryCase::AuthenticatedExceptionMove ||
                test_case == EntryCase::AuthenticatedExceptionBranch) {
            memmove(blob.nm.code + 1, blob.nm.code, sizeof(instructions));
            blob.nm.code[0] = 0xd503231f; // paciaz before saving FP/LR
            blob.nm.code[18] = 0xd503239f; // autiaz after restoring FP/LR
            blob.nm.code[19] = 0xd65f03c0;
            prefix = 4;
            blob.nm.frame_complete += prefix;
        }
        if (exception_exit) {
            // gen_continuation_enter's exception exit follows leave() with
            // mov x3, lr; br x1 instead of the normal ret instruction.
            int tail = prefix == 0 ? 17 : 19;
            blob.nm.code[tail] = test_case == EntryCase::ExceptionBranchWithoutMove ? 0xd503201f : 0xaa1e03e3;
            blob.nm.code[tail + 1] = test_case == EntryCase::ExceptionMoveWithoutBranch ? 0xd61f0040 : 0xd61f0020;
        }
        bool leaf_spill = test_case >= EntryCase::LeafSpillBeforeSave && test_case <= EntryCase::LeafSpillUnknownSequence;
        if (leaf_spill) {
            // call_VM_leaf_base: save scratch/method, load resolver, call, restore.
            const uint32_t leaf[] = {0xa9bf33e8, 0xd2824688, 0xf2aacf08, 0xf2c24688,
                                     0xd63f0100, 0xa8c133e8, 0xd503201f};
            memcpy(blob.nm.code + 7, leaf, sizeof(leaf));
            if (test_case == EntryCase::LeafSpillOneMove || test_case == EntryCase::LeafSpillMovn ||
                    test_case == EntryCase::LeafSpillLogicalImmediate) {
                blob.nm.code[8] = test_case == EntryCase::LeafSpillMovn ? 0x92824688 :
                        test_case == EntryCase::LeafSpillLogicalImmediate ? 0xb2401fe8 : 0xd2824688;
                blob.nm.code[9] = 0xd63f0100;
                blob.nm.code[10] = 0xa8c133e8;
                blob.nm.code[11] = 0xd503201f;
            } else if (test_case == EntryCase::LeafSpillFourMoves) {
                blob.nm.code[11] = 0xf2e24688;
                blob.nm.code[12] = 0xd63f0100;
                blob.nm.code[13] = 0xa8c133e8;
                blob.nm.code[14] = 0xd503201f;
            }
            if (test_case == EntryCase::LeafSpillUnknownSequence) blob.nm.code[11] = 0xd503201f;
        }
#endif
        if (test_case == EntryCase::UnsupportedPrologue) blob.nm.code[0] = 0;
        if (test_case == EntryCase::InterpretedEntry || test_case == EntryCase::UnsupportedInterpretedEntry) {
            // The interpreted entry precedes the verified compiled entry. Its
            // frame is established before the compiled frame-complete offset.
            memcpy(blob.nm.code + 24, instructions, 12);
            blob.nm.entry = blob.nm.code + 24;
            blob.nm.frame_complete += 24 * sizeof(uint32_t);
            if (test_case == EntryCase::UnsupportedInterpretedEntry) blob.nm.code[0] = 0;
        }
        struct Heap { const void* low; const void* high; unsigned char* map; };
        unsigned char map[] = {0, 0};
        Heap heap{heap_memory, heap_memory + sizeof(local_heap_memory), map};
        ScopedValue<int> memory(_code_heap_memory_offset, 0);
        ScopedValue<int> segmap(_code_heap_segmap_offset, offsetof(Heap, map));
        ScopedValue<int> low(_vs_low_offset, offsetof(Heap, low));
        ScopedValue<int> high(_vs_high_offset, offsetof(Heap, high));
        ScopedValue<int> shift(_code_heap_segment_shift, 9);
        ScopedValue<int> used(_heap_block_used_offset, 0);
        ScopedValue<int> name(_nmethod_name_offset, offsetof(NMethod, name));
        ScopedValue<int> frame_size(_frame_size_offset, offsetof(NMethod, frame_size));
        ScopedValue<int> size(_blob_size_offset, offsetof(NMethod, size));
        ScopedValue<int> frame_complete(_frame_complete_offset, offsetof(NMethod, frame_complete));
        ScopedValue<int> code_offset(_code_offset, -1);
        ScopedValue<int> code_address(_code_address, offsetof(NMethod, code_begin));
        ScopedValue<int> entry_offset(_nmethod_entry_offset, -1);
        ScopedValue<int> entry_address(_nmethod_entry_address, offsetof(NMethod, entry));
        ScopedValue<int> method_offset(_nmethod_method_offset, offsetof(NMethod, method));
        ScopedValue<int> level(_nmethod_level_offset, offsetof(NMethod, level));
        ScopedValue<int> scopes(_scopes_pcs_offset, offsetof(NMethod, scopes));
        ScopedValue<int> immutable(_nmethod_immutable_offset, -1);
        ScopedValue<int> constmethod(_method_constmethod_offset, offsetof(Method, const_method));
        ScopedValue<int> constants(_constmethod_constants_offset, offsetof(ConstMethod, constants));
        ScopedValue<int> idnum(_constmethod_idnum_offset, offsetof(ConstMethod, idnum));
        ScopedValue<int> slots(_constmethod_stack_arg_slots_offset, offsetof(ConstMethod, slots));
        bool exported_parent = test_case == EntryCase::ExportedParentEntry || test_case == EntryCase::LeafSpillNativePrefixExportedParent ||
                test_case == EntryCase::X64ExceptionNativePrefixExportedParent;
        bool exported_entry = exported_parent || test_case == EntryCase::LeafSpillNativePrefixExportedNull || tracked_child || invalid_exported_size || x64_exception_prefix;
        ScopedValue<int> cont_entry_offset(_cont_entry_offset, exported_entry ? offsetof(ThreadLayout, entry) : -1);
        ScopedValue<int> parent_offset(_cont_entry_parent_offset, 0);
        ScopedValue<uint64_t> entry_size(TYPE_SIZE_NAME(VMContinuationEntry), exported_entry ? (invalid_exported_size ? 80 : 64) : 0);
        if (exported_entry) thread.entry = exported_parent ? &stack[16] : nullptr;
        ScopedValue<uint64_t> type_size(TYPE_SIZE_NAME(VMNMethod), sizeof(NMethod));
        ScopedValue<uint64_t> method_size(TYPE_SIZE_NAME(VMMethod), sizeof(Method));
        ScopedValue<uint64_t> constmethod_size(TYPE_SIZE_NAME(VMConstMethod), sizeof(ConstMethod));
        ScopedValue<char*> heap0(_code_heap[0], reinterpret_cast<char*>(&heap));
        ScopedValue<char*> heap1(_code_heap[1], nullptr);
        ScopedValue<char*> heap2(_code_heap[2], nullptr);
        ScopedValue<const void*> heap_low(_code_heap_low, heap.low);
        ScopedValue<const void*> heap_high(_code_heap_high, heap.high);
        ScopedValue<VMNMethod*> entry_nm(_enter_special_nm, reinterpret_cast<VMNMethod*>(barrier_interior ? &carrier.nm : &blob.nm));
        ScopedValue<const void*> return_barrier(_cont_return_barrier, barrier_interior ? blob.nm.code : _cont_return_barrier);
        ScopedValue<int> inferred_entry_offset(_cont_entry_thread_offset, barrier_interior ? 0 : _cont_entry_thread_offset);
        if (barrier_interior) {
            thread.entry = stack;
            JitCodeCache::DynamicCodeGenerated(nullptr, "cont return barrier", blob.nm.code, sizeof(blob.nm.code));
        }
        const void* sampled_pc = (const char*)blob.nm.code + offsets[(int)phase] + prefix;
#ifdef __x86_64__
        if (x64_exception_prefix) sampled_pc = (const char*)blob.nm.code + 98; // resolver return PC
#endif
#ifdef __aarch64__
        if (exception_exit && prefix != 0) sampled_pc = (const char*)sampled_pc + sizeof(uint32_t); // after autiaz
        if (test_case == EntryCase::ExceptionBranch || test_case == EntryCase::AuthenticatedExceptionBranch ||
                test_case == EntryCase::ExceptionBranchWithoutMove) sampled_pc = (const char*)sampled_pc + sizeof(uint32_t);
        if (leaf_spill) {
            int instruction = test_case == EntryCase::LeafSpillBeforeSave ? 0 :
                    test_case == EntryCase::LeafSpillMove || test_case == EntryCase::LeafSpillUnknownSequence ? 1 :
                    test_case == EntryCase::LeafSpillCall ? 4 :
                    test_case == EntryCase::LeafSpillRestore || leaf_native_prefix ? 5 : 6;
            if (test_case >= EntryCase::LeafSpillOneMove && test_case <= EntryCase::LeafSpillFourMoves) instruction = 1;
            sampled_pc = blob.nm.code + 7 + instruction;
        }
#endif
        ScopedValue<const void*> return_pc(_cont_entry_return_pc,
                test_case == EntryCase::ReturnPc ? sampled_pc : tracked_child ? blob.nm.code + 31 : _cont_entry_return_pc);
        VMTestAccessor::install(true, exported_entry ? 27 : 21);

        bool nonpointer_fp = test_case == EntryCase::CompiledNonPointerFp ||
                test_case == EntryCase::NativeNonPointerFp || test_case == EntryCase::BlobNonPointerFp;
        uintptr_t saved_fp = nonpointer_fp ? 1 : (uintptr_t)&stack[24];
        uintptr_t carrier_pc = test_case == EntryCase::CompiledNonPointerFp || test_case == EntryCase::BlobNonPointerFp
                ? (uintptr_t)carrier.nm.code : (uintptr_t)CARRIER_PC;
        if (test_case == EntryCase::InvalidPc) carrier_pc = 1;
        stack[8] = saved_fp;
        stack[9] = carrier_pc;
        stack[10] = (uintptr_t)&stack[26];
        stack[11] = (uintptr_t)THREAD_ENTRY_PC;
        stack[12] = (uintptr_t)&stack[26];
        stack[13] = (uintptr_t)THREAD_ENTRY_PC;
        if (test_case == EntryCase::X64ExceptionNativePrefixExportedParent) {
            // The published parent is independently walkable. Following it
            // would fabricate ancestry for the already unlinked child.
            stack[24] = (uintptr_t)&stack[40];
            stack[25] = (uintptr_t)CARRIER_PC;
            stack[26] = (uintptr_t)&stack[42];
            stack[27] = (uintptr_t)THREAD_ENTRY_PC;
        }
        int sp_slot = phase == EntryPhase::Complete || phase == EntryPhase::BeforeSpRestore ||
                phase == EntryPhase::AfterAllocation ? 0 : 8;
#ifdef __aarch64__
        if (leaf_spill && test_case != EntryCase::LeafSpillBeforeSave && test_case != EntryCase::LeafSpillAfterRestore) sp_slot = -2;
#endif
        uintptr_t sampled_fp = (uintptr_t)&stack[8];
        if (phase == EntryPhase::AfterSave) sampled_fp = saved_fp;
        if (phase == EntryPhase::BeforeSave || phase == EntryPhase::AfterRestore) {
            sampled_fp = saved_fp;
            stack[8] = 0; // Below sampled SP; may be overwritten by signal delivery.
#ifdef __aarch64__
            sp_slot = 10;
            stack[9] = 0;
#else
            sp_slot = 9; // Return address remains on stack until ret.
#endif
        }
        if (test_case == EntryCase::ReturnPc) sampled_fp = 1;
        if (test_case == EntryCase::InvalidFrameSize) blob.nm.frame_size = 2;
        ucontext_t context{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 machine_context{};
        context.uc_mcontext = &machine_context;
#endif
#ifdef __aarch64__
#ifdef __APPLE__
        machine_context.__ss.__lr = carrier_pc;
#else
        context.uc_mcontext.regs[30] = carrier_pc;
#endif
#endif
        StackFrame frame(&context);
        frame.pc() = (uintptr_t)sampled_pc;
        frame.sp() = (uintptr_t)&stack[sp_slot];
        if (test_case == EntryCase::MisalignedSp) frame.sp() += 8;
        if (test_case == EntryCase::OutOfBoundsSp) frame.sp() = (UINTPTR_MAX / 2) & ~(uintptr_t)15;
        frame.fp() = sampled_fp;
#ifdef __x86_64__
        if (x64_exception_prefix) {
            // Cleanup popped the entry's RBP, then pushed the exception at
            // stack[8]. The native callee saves that restored caller RBP and
            // the resolver return PC below it; unwinding restores SP=stack+8.
            stack[6] = saved_fp;
            stack[7] = (uintptr_t)sampled_pc;
            stack[8] = 1; // exception oop, not a saved frame pointer
            frame.pc() = (uintptr_t)LEAF_PC;
            frame.sp() = (uintptr_t)&stack[6];
            frame.fp() = (uintptr_t)&stack[6];
        } else
#endif
        if (leaf_native_prefix || x64_exception_prefix || test_case == EntryCase::BarrierInteriorNativePrefix) {
            stack[-4] = sampled_fp;
            stack[-3] = (uintptr_t)sampled_pc;
            frame.pc() = (uintptr_t)LEAF_PC;
            frame.sp() = (uintptr_t)(stack - 4);
        }
        if (tracked_child) {
            // Cross a child first, recover its parent's unlinked resolver frame,
            // then reach the grandparent boundary. Replaying the parent fails.
            thread.entry = stack;
            stack[0] = (uintptr_t)&stack[14];
            stack[8] = (uintptr_t)&stack[40];
            stack[9] = (uintptr_t)LEAF_PC;
            stack[10] = (uintptr_t)&stack[40];
            stack[11] = (uintptr_t)sampled_pc;
            stack[14] = (uintptr_t)&stack[26];
            stack[22] = (uintptr_t)&stack[40];
            stack[23] = (uintptr_t)_cont_entry_return_pc;
            stack[34] = (uintptr_t)&stack[40];
            stack[35] = (uintptr_t)CARRIER_PC;
            stack[36] = (uintptr_t)&stack[40];
            stack[37] = (uintptr_t)THREAD_ENTRY_PC;
            frame.pc() = (uintptr_t)_cont_entry_return_pc;
            frame.sp() = (uintptr_t)stack;
            frame.fp() = (uintptr_t)&stack[8];
        }
        StackWalkFeatures features{};
        features.carrier_frames = test_case != EntryCase::BarrierInteriorRoot;
        bool truncated = false;
        int depth = HotspotSupportTestAccessor::walk(&context, frames, features, MAX_DEPTH, &truncated);
        if (barrier_interior) {
            if (test_case == EntryCase::BarrierInteriorNativePrefix) assertCarrier(depth);
            else {
                ASSERT_EQ(1, depth);
                ASSERT_EQ(BCI_NATIVE_FRAME, frames[0].bci);
                EXPECT_STREQ(features.carrier_frames ? "continuation_carrier" : "JVM Continuation", (const char*)frames[0].method_id);
            }
            EXPECT_TRUE(truncated);
            return;
        }
        if (invalid_exported_size || x64_exception_prefix) {
            ASSERT_EQ(2, depth);
            ASSERT_EQ(BCI_ERROR, frames[1].bci);
            EXPECT_STREQ("break_cont_entry_fp", (const char*)frames[1].method_id);
            EXPECT_TRUE(truncated);
            return;
        }
        if (leaf_native_prefix) {
            assertCarrier(depth);
            EXPECT_FALSE(truncated);
            return;
        }
        ASSERT_EQ(1, depth);
        if (test_case == EntryCase::NativeNonPointerFp || test_case == EntryCase::BlobNonPointerFp ||
                test_case == EntryCase::InvalidPc || test_case == EntryCase::MisalignedSp ||
                test_case == EntryCase::OutOfBoundsSp || test_case == EntryCase::InvalidFrameSize ||
                test_case == EntryCase::UnsupportedPrologue || test_case == EntryCase::ExceptionMoveWithoutBranch ||
                test_case == EntryCase::ExceptionBranchWithoutMove || test_case == EntryCase::UnsupportedInterpretedEntry ||
                test_case == EntryCase::LeafSpillUnknownSequence) {
            ASSERT_EQ(BCI_ERROR, frames[0].bci);
            EXPECT_STREQ(test_case == EntryCase::MisalignedSp || test_case == EntryCase::OutOfBoundsSp ||
                         test_case == EntryCase::InvalidFrameSize || test_case == EntryCase::UnsupportedPrologue ||
                         test_case == EntryCase::UnsupportedInterpretedEntry ? "break_cont_entry_fp" : "break_cont_carrier_sp",
                         (const char*)frames[0].method_id);
            EXPECT_TRUE(truncated);
        } else if (test_case == EntryCase::CompiledNonPointerFp) {
            EXPECT_EQ(FrameType::encode(FRAME_JIT_COMPILED, 0), frames[0].bci);
            EXPECT_EQ(JMETHODID_NOT_WALKABLE, frames[0].method_id);
            EXPECT_FALSE(truncated);
        } else {
            ASSERT_EQ(BCI_NATIVE_FRAME, frames[0].bci)
                    << (frames[0].bci == BCI_ERROR ? (const char*)frames[0].method_id : "unexpected frame type");
            EXPECT_STREQ("continuation_carrier", (const char*)frames[0].method_id);
            EXPECT_FALSE(truncated);
        }
    }

    void assertCarrier(int depth) {
        ASSERT_EQ(2, depth);
        EXPECT_EQ(BCI_NATIVE_FRAME, frames[0].bci);
        EXPECT_EQ(BCI_NATIVE_FRAME, frames[1].bci);
        EXPECT_STREQ("continuation_sampled_leaf", (const char*)frames[0].method_id);
        EXPECT_STREQ("continuation_carrier", (const char*)frames[1].method_id);
    }

    static std::array<unsigned char, 8> barrierInstructions() {
#ifdef __aarch64__
        return {0x88, 0x03, 0x40, 0xf9, 0x1f, 0x01, 0x00, 0x91}; // ldr x8, [x28]; mov sp, x8
#else
        return {0x49, 0x8b, 0xa7, 0, 0, 0, 0, 0x90}; // mov rsp, [r15 + 0]
#endif
    }

    int discoverBarrierOffset(const unsigned char* code, size_t size, uint64_t thread_size) {
        ScopedValue<const void*> barrier(_cont_return_barrier, code);
        ScopedValue<const void*> low(_code_heap_low, code);
        ScopedValue<const void*> high(_code_heap_high, code == nullptr ? nullptr : code + size);
        ScopedValue<uint64_t> thread_type(TYPE_SIZE_NAME(VMJavaThread), thread_size);
        initContEntryThreadOffset();
        return VMStructs::contEntryThreadOffset();
    }

    // At the first return-barrier instruction there is no preceding Java frame
    // from which walkVM can obtain stack arguments. HotSpot's barrier loads the
    // ContinuationEntry from JavaThread before resetting SP (JDK 21 and 25).
    // Three stack arguments occupy four aligned words below that entry.
    enum class BarrierEntryCase {
        Valid, NullEntry, MisalignedEntry, EntryBelowSp, EntryAboveStack, InvalidFrameSize,
        UnreliableSampledFp, BadCarrierPc, BadCarrierFp, UnrecognizedBarrier
    };

    void assertCarrierFromSampledReturnBarrier(int stack_args, bool exported_entry,
                                              bool carrier_frames = true, bool native_prefix = false,
                                              BarrierEntryCase test_case = BarrierEntryCase::Valid) {
        ASSERT_TRUE(stack_args == 0 || stack_args == 3);
        alignas(16) uintptr_t stack[32]{};
        alignas(16) auto barrier_code = barrierInstructions();
        if (test_case == BarrierEntryCase::UnrecognizedBarrier) barrier_code[0] = 0;
        static_assert(offsetof(ThreadLayout, entry) == 0, "Barrier load names the thread's entry field");
        ScopedValue<const void*> barrier(_cont_return_barrier, barrier_code.data());
        ScopedValue<const void*> low(_code_heap_low, barrier_code.data());
        ScopedValue<const void*> high(_code_heap_high, barrier_code.data() + barrier_code.size());
        ScopedValue<char*> heap0(_code_heap[0], nullptr);
        ScopedValue<char*> heap1(_code_heap[1], nullptr);
        ScopedValue<char*> heap2(_code_heap[2], nullptr);
        ScopedValue<int> entry_offset(_cont_entry_offset, exported_entry ? offsetof(ThreadLayout, entry) : -1);
        ScopedValue<uint64_t> entry_size(TYPE_SIZE_NAME(VMContinuationEntry), exported_entry ? 64 : 0);
        VMTestAccessor::install(true, exported_entry ? 27 : 21);
        initContEntryThreadOffset();
        ASSERT_EQ(test_case == BarrierEntryCase::UnrecognizedBarrier ? -1 : 0, VMStructs::contEntryThreadOffset());
        entry_frame_size = 10; // 64-byte ContinuationEntry and saved FP/PC
        int barrier_sp_slot = native_prefix ? 2 : 0;
        int entry_slot = barrier_sp_slot + (stack_args == 0 ? 0 : 4);
        thread.entry = &stack[entry_slot];
        if (stack_args != 0) {
            stack[barrier_sp_slot] = 7;
            stack[barrier_sp_slot + 1] = 8;
            stack[barrier_sp_slot + 2] = 9;
        }
        // The empty ContinuationEntryPD occupies the first word; flags and
        // argsize are the two 32-bit fields in word four on these HotSpot builds.
        stack[entry_slot + 4] = ((uint64_t)stack_args << 32) | 1;
        stack[entry_slot + 8] = (uintptr_t)&stack[24];
        stack[entry_slot + 9] = (uintptr_t)CARRIER_PC;
        stack[entry_slot + 10] = (uintptr_t)&stack[26];
        stack[entry_slot + 11] = (uintptr_t)THREAD_ENTRY_PC;
        if (test_case == BarrierEntryCase::NullEntry) thread.entry = nullptr;
        if (test_case == BarrierEntryCase::MisalignedEntry) thread.entry = &stack[entry_slot + 1];
        if (test_case == BarrierEntryCase::EntryBelowSp) thread.entry = (void*)((uintptr_t)stack - 16);
        if (test_case == BarrierEntryCase::EntryAboveStack) thread.entry = (void*)(UINTPTR_MAX & ~(uintptr_t)15);
        if (test_case == BarrierEntryCase::InvalidFrameSize) entry_frame_size = 258;
        if (test_case == BarrierEntryCase::BadCarrierPc) stack[entry_slot + 9] = 1;
        if (test_case == BarrierEntryCase::BadCarrierFp) stack[entry_slot + 8] = 1;
        if (native_prefix) {
            stack[0] = (uintptr_t)&stack[entry_slot + 8];
            stack[1] = (uintptr_t)barrier_code.data();
        }

        ucontext_t context{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 machine_context{};
        context.uc_mcontext = &machine_context;
#endif
#ifdef __aarch64__
#ifdef __APPLE__
        machine_context.__ss.__lr = (uintptr_t)barrier_code.data();
#else
        context.uc_mcontext.regs[30] = (uintptr_t)barrier_code.data();
#endif
#endif
        StackFrame frame(&context);
        frame.pc() = native_prefix ? (uintptr_t)LEAF_PC : (uintptr_t)barrier_code.data();
        frame.sp() = (uintptr_t)stack;
        frame.fp() = (uintptr_t)&stack[entry_slot + 8];
        if (test_case == BarrierEntryCase::UnreliableSampledFp) frame.fp() = 1;
        StackWalkFeatures features{};
        features.carrier_frames = carrier_frames;
        bool truncated = false;
        int depth = HotspotSupportTestAccessor::walk(&context, frames, features, MAX_DEPTH, &truncated);
        int carrier_index = native_prefix ? 1 : 0;
        ASSERT_EQ(carrier_index + 1, depth);
        if (native_prefix) EXPECT_STREQ("continuation_sampled_leaf", (const char*)frames[0].method_id);
        if (test_case != BarrierEntryCase::Valid && test_case != BarrierEntryCase::UnreliableSampledFp) {
            ASSERT_EQ(BCI_ERROR, frames[carrier_index].bci);
            EXPECT_STREQ(test_case == BarrierEntryCase::BadCarrierPc || test_case == BarrierEntryCase::BadCarrierFp
                    ? "break_cont_carrier_sp" : "break_cont_entry_fp", (const char*)frames[carrier_index].method_id);
            EXPECT_TRUE(truncated);
            return;
        }
        ASSERT_EQ(BCI_NATIVE_FRAME, frames[carrier_index].bci)
                << (frames[carrier_index].bci == BCI_ERROR ? (const char*)frames[carrier_index].method_id : "unexpected frame type");
        EXPECT_STREQ(carrier_frames ? "continuation_carrier" : "JVM Continuation", (const char*)frames[carrier_index].method_id);
        EXPECT_TRUE(truncated);
    }

    bool old_hotspot;
    int old_version;
    pthread_key_t old_key;
    pthread_key_t owned_key = INVALID_KEY;
    jfieldID old_tid;
    const void *old_low, *old_high, *old_barrier, *old_return_pc;
    int old_entry_thread_offset;
    int old_entry_offset;
    int old_frame_size_offset;
    int old_anchor_offset, old_anchor_sp, old_anchor_fp, old_anchor_pc, old_vframe_offset;
    uint64_t old_anchor_size;
    VMNMethod* old_entry_nm;
    uint64_t old_entry_size;
    uint64_t old_thread_size;
    uint64_t old_java_thread_size;
};

TEST_F(ContinuationWalkTest, SpeculativeCrossingRetainsCarrierAndSerializesTruncation) {
    bool truncated = false;
    auto before = Counters::getCounter(WALKVM_CONT_SPECULATIVE_HIT);
    int depth = walk(true, &truncated);
    assertCarrier(depth);
    EXPECT_EQ(before + 1, Counters::getCounter(WALKVM_CONT_SPECULATIVE_HIT));
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

TEST_F(ContinuationWalkTest, SampledReturnBarrierWithoutStackArgumentsRetainsCarrier) {
    assertCarrierFromSampledReturnBarrier(0, false);
}

TEST_F(ContinuationWalkTest, SampledReturnBarrierWithStackArgumentsRetainsCarrier) {
    assertCarrierFromSampledReturnBarrier(3, false);
}

TEST_F(ContinuationWalkTest, NativeFrameLeadingToReturnBarrierWithoutJavaMetadataRetainsCarrier) {
    for (int stack_args : {0, 3}) assertCarrierFromSampledReturnBarrier(stack_args, false, true, true);
}

TEST_F(ContinuationWalkTest, SampledReturnBarrierWithExportedEntryRetainsCarrier) {
    for (bool native_prefix : {false, true}) {
        for (int stack_args : {0, 3}) assertCarrierFromSampledReturnBarrier(stack_args, true, true, native_prefix);
    }
}

TEST_F(ContinuationWalkTest, SampledReturnBarrierWithoutCarrierFramesKeepsTruncatedRoot) {
    for (bool native_prefix : {false, true}) {
        for (int stack_args : {0, 3}) assertCarrierFromSampledReturnBarrier(stack_args, false, false, native_prefix);
    }
}

TEST_F(ContinuationWalkTest, ReturnBarrierDecoderAcceptsGeneratedThreadLoad) {
#ifdef __aarch64__
    const unsigned char jdk21[] = {0x88, 0x9b, 0x42, 0xf9, 0x1f, 0x01, 0x00, 0x91};
    const unsigned char jdk25[] = {0x88, 0xd3, 0x42, 0xf9, 0x1f, 0x01, 0x00, 0x91};
    EXPECT_EQ(1328, HotspotStackFrame::continuationEntryThreadOffset(jdk21, sizeof(jdk21)));
    EXPECT_EQ(1440, HotspotStackFrame::continuationEntryThreadOffset(jdk25, sizeof(jdk25)));
#else
    const unsigned char wide[] = {0x49, 0x8b, 0xa7, 0x30, 0x05, 0, 0};
    const unsigned char short_disp[] = {0x49, 0x8b, 0x67, 0x70};
    const unsigned char no_disp[] = {0x49, 0x8b, 0x27};
    EXPECT_EQ(1328, HotspotStackFrame::continuationEntryThreadOffset(wide, sizeof(wide)));
    EXPECT_EQ(112, HotspotStackFrame::continuationEntryThreadOffset(short_disp, sizeof(short_disp)));
    EXPECT_EQ(0, HotspotStackFrame::continuationEntryThreadOffset(no_disp, sizeof(no_disp)));
#endif
}

TEST_F(ContinuationWalkTest, ReturnBarrierDecoderRejectsTruncatedOrUnknownInstructions) {
    auto code = barrierInstructions();
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(nullptr, code.size()));
#ifdef __aarch64__
    constexpr size_t prefix_size = 8;
#else
    constexpr size_t prefix_size = 7;
#endif
    for (size_t size = 0; size < prefix_size; size++) {
        EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), size));
    }
#ifdef __aarch64__
    code[0] ^= 1; // wrong destination register
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), code.size()));
    code = barrierInstructions();
    code[1] ^= 1; // wrong JavaThread register
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), code.size()));
    code = barrierInstructions();
    code[4] ^= 1; // not mov sp, x8
#else
    code[0] = 0x48; // rdi rather than the r15 JavaThread base
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), code.size()));
    code = barrierInstructions();
    code[2] = 0xaf; // rbp rather than rsp
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), code.size()));
    code = barrierInstructions();
    code[6] = 0xff; // negative disp32
#endif
    EXPECT_EQ(-1, HotspotStackFrame::continuationEntryThreadOffset(code.data(), code.size()));
}

TEST_F(ContinuationWalkTest, ReturnBarrierDiscoveryRejectsMissingOrOutOfRangeMetadata) {
    auto code = barrierInstructions();
    EXPECT_EQ(0, discoverBarrierOffset(code.data(), code.size(), sizeof(ThreadLayout)));
    EXPECT_EQ(-1, discoverBarrierOffset(nullptr, 0, sizeof(ThreadLayout)));
    EXPECT_EQ(-1, discoverBarrierOffset(code.data(), code.size() - 1, sizeof(ThreadLayout)));
    EXPECT_EQ(-1, discoverBarrierOffset(code.data(), code.size(), sizeof(void*) - 1));
#ifdef __aarch64__
    code[1] = 7; // eight-byte offset
#else
    code[3] = 8;
#endif
    EXPECT_EQ(8, discoverBarrierOffset(code.data(), code.size(), 2 * sizeof(void*)));
    EXPECT_EQ(-1, discoverBarrierOffset(code.data(), code.size(), sizeof(void*)));
    code[0] = 0;
    EXPECT_EQ(-1, discoverBarrierOffset(code.data(), code.size(), 2 * sizeof(void*)));
    VMTestAccessor::install(true, 20);
    code = barrierInstructions();
    EXPECT_EQ(-1, discoverBarrierOffset(code.data(), code.size(), sizeof(ThreadLayout)));
}

TEST_F(ContinuationWalkTest, SampledReturnBarrierRejectsInvalidEntryAndCarrierMetadata) {
    for (BarrierEntryCase test_case : {
            BarrierEntryCase::NullEntry, BarrierEntryCase::MisalignedEntry, BarrierEntryCase::EntryBelowSp,
            BarrierEntryCase::EntryAboveStack, BarrierEntryCase::InvalidFrameSize,
            BarrierEntryCase::BadCarrierPc, BarrierEntryCase::BadCarrierFp, BarrierEntryCase::UnrecognizedBarrier}) {
        for (int stack_args : {0, 3}) assertCarrierFromSampledReturnBarrier(stack_args, false, true, false, test_case);
    }
}

TEST_F(ContinuationWalkTest, SampledReturnBarrierDoesNotRequireSampledFp) {
    for (int stack_args : {0, 3}) {
        assertCarrierFromSampledReturnBarrier(stack_args, false, true, false, BarrierEntryCase::UnreliableSampledFp);
    }
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

TEST_F(ContinuationWalkTest, FrozenRootDoesNotReplayJavaAnchor) {
    _cont_return_barrier = BOUNDARY_PC;
    auto before = Counters::getCounter(WALKVM_ANCHOR_FALLBACK);
    bool truncated = false;
    EXPECT_EQ(1, walk(false, &truncated, true, true, MAX_DEPTH, true));
    EXPECT_STREQ("JVM Continuation", (const char*)frames[0].method_id);
    EXPECT_TRUE(truncated);
    EXPECT_EQ(before, Counters::getCounter(WALKVM_ANCHOR_FALLBACK));
}

TEST_F(ContinuationWalkTest, ThawedRootDoesNotReplayJavaAnchor) {
    _cont_entry_return_pc = BOUNDARY_PC;
    auto before = Counters::getCounter(WALKVM_ANCHOR_FALLBACK);
    bool truncated = false;
    EXPECT_EQ(1, walk(false, &truncated, false, true, MAX_DEPTH, true));
    EXPECT_STREQ("JVM Continuation", (const char*)frames[0].method_id);
    EXPECT_FALSE(truncated);
    EXPECT_EQ(before, Counters::getCounter(WALKVM_ANCHOR_FALLBACK));
}

TEST_F(ContinuationWalkTest, CarrierWalkDoesNotReplayJavaAnchor) {
    for (bool frozen : {false, true}) {
        _cont_return_barrier = frozen ? BOUNDARY_PC : nullptr;
        _cont_entry_return_pc = frozen ? nullptr : BOUNDARY_PC;
        TYPE_SIZE_NAME(VMContinuationEntry) = (frozen ? 6 : 2) * sizeof(uintptr_t);
        auto before = Counters::getCounter(WALKVM_ANCHOR_FALLBACK);
        bool truncated = false;
        EXPECT_EQ(1, walk(true, &truncated, frozen, true, MAX_DEPTH, true));
        EXPECT_STREQ("continuation_carrier", (const char*)frames[0].method_id);
        EXPECT_EQ(frozen, truncated);
        EXPECT_EQ(before, Counters::getCounter(WALKVM_ANCHOR_FALLBACK));
    }
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

TEST_F(ContinuationWalkTest, EntryNMethodWithCompleteFrameRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::Complete);
}

TEST_F(ContinuationWalkTest, EntryNMethodBeforeStackAllocationRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::BeforeAllocation);
}

TEST_F(ContinuationWalkTest, EntryNMethodAfterStackDeallocationRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::AfterDeallocation);
}

TEST_F(ContinuationWalkTest, EntryNMethodBeforeSavingRegistersRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::BeforeSave);
}

TEST_F(ContinuationWalkTest, EntryNMethodAfterSavingBeforeSettingFpRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::AfterSave);
}

TEST_F(ContinuationWalkTest, EntryNMethodBeforeRestoringSpRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::BeforeSpRestore);
}

TEST_F(ContinuationWalkTest, EntryNMethodAfterRestoringRegistersRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::AfterRestore);
}

TEST_F(ContinuationWalkTest, VerifiedReturnPcDoesNotRequireSampledFp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::ReturnPc);
}

TEST_F(ContinuationWalkTest, CompiledCarrierAcceptsNonPointerSavedFp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::CompiledNonPointerFp);
}

TEST_F(ContinuationWalkTest, NativeCarrierRejectsNonPointerSavedFp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::NativeNonPointerFp);
}

TEST_F(ContinuationWalkTest, NonNMethodCarrierRejectsNonPointerSavedFp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::BlobNonPointerFp);
}

TEST_F(ContinuationWalkTest, EntryNMethodRejectsInvalidCarrierPc) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::InvalidPc);
}

TEST_F(ContinuationWalkTest, EntryNMethodRejectsMisalignedSp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::MisalignedSp);
}

TEST_F(ContinuationWalkTest, EntryNMethodRejectsOutOfBoundsSp) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::OutOfBoundsSp);
}

TEST_F(ContinuationWalkTest, EntryNMethodRejectsInvalidFrameSize) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::InvalidFrameSize);
}

TEST_F(ContinuationWalkTest, EntryNMethodAfterAllocationBeforePublicationRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::AfterAllocation);
}

TEST_F(ContinuationWalkTest, EntryNMethodRejectsUnsupportedPrologue) {
    assertCarrierFromEntry(EntryPhase::BeforeAllocation, EntryCase::UnsupportedPrologue);
}

TEST_F(ContinuationWalkTest, InterpretedEntryRetainsCarrierBeforeCompiledEntry) {
    for (EntryPhase phase : {EntryPhase::BeforeSave, EntryPhase::AfterSave,
            EntryPhase::BeforeAllocation, EntryPhase::AfterAllocation, EntryPhase::Complete}) {
        assertCarrierFromEntry(phase, EntryCase::InterpretedEntry);
    }
}

TEST_F(ContinuationWalkTest, InterpretedEntryRejectsUnsupportedPrologue) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::UnsupportedInterpretedEntry);
}

#ifdef __x86_64__
TEST_F(ContinuationWalkTest, ExceptionResolverReturnPcRejectsUnlinkedExportedEntry) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::X64ExceptionNativePrefixExportedNull);
}

TEST_F(ContinuationWalkTest, ExceptionResolverReturnPcDoesNotReplayExportedParent) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::X64ExceptionNativePrefixExportedParent);
}
#endif

TEST_F(ContinuationWalkTest, ReturnBarrierInteriorRetainsContinuationAncestry) {
    for (EntryCase test_case : {EntryCase::BarrierInterior, EntryCase::BarrierInteriorRoot, EntryCase::BarrierInteriorNativePrefix}) {
        assertCarrierFromEntry(EntryPhase::Complete, test_case);
    }
}

TEST_F(ContinuationWalkTest, SampledEntryDoesNotFollowExportedParentDuringTransitions) {
    for (EntryPhase phase : {EntryPhase::BeforeSave, EntryPhase::AfterSave, EntryPhase::BeforeAllocation,
                            EntryPhase::AfterAllocation, EntryPhase::Complete, EntryPhase::BeforeSpRestore,
                            EntryPhase::AfterDeallocation, EntryPhase::AfterRestore}) {
        assertCarrierFromEntry(phase, EntryCase::ExportedParentEntry);
    }
}

#ifdef __aarch64__
TEST_F(ContinuationWalkTest, EntryVmLeafSpillRetainsCarrier) {
    for (EntryCase test_case : {EntryCase::LeafSpillBeforeSave, EntryCase::LeafSpillMove,
            EntryCase::LeafSpillCall, EntryCase::LeafSpillRestore, EntryCase::LeafSpillAfterRestore}) {
        assertCarrierFromEntry(EntryPhase::Complete, test_case);
    }
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillRequiresRecognizedSequence) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillUnknownSequence);
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillAcceptsGeneratedConstantLoads) {
    for (EntryCase test_case : {EntryCase::LeafSpillOneMove, EntryCase::LeafSpillMovn,
            EntryCase::LeafSpillLogicalImmediate, EntryCase::LeafSpillFourMoves}) {
        assertCarrierFromEntry(EntryPhase::Complete, test_case);
    }
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillWithNativePrefixRetainsCarrier) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillNativePrefix);
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillWithNativePrefixIgnoresUnlinkedExportedEntry) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillNativePrefixExportedNull);
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillWithNativePrefixIgnoresExportedParent) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillNativePrefixExportedParent);
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillWithExportedMetadataAdvancesTrackedChildToParent) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillNativePrefixExportedTrackedChild);
}

TEST_F(ContinuationWalkTest, EntryVmLeafSpillRejectsInconsistentExportedFrameSize) {
    assertCarrierFromEntry(EntryPhase::Complete, EntryCase::LeafSpillNativePrefixExportedInvalidSize);
}

TEST_F(ContinuationWalkTest, ExceptionExitAfterRestoringRegistersRetainsCarrier) {
    for (EntryCase test_case : {EntryCase::ExceptionMove, EntryCase::ExceptionBranch}) {
        assertCarrierFromEntry(EntryPhase::AfterRestore, test_case);
    }
}

TEST_F(ContinuationWalkTest, AuthenticatedExceptionExitAfterRestoringRegistersRetainsCarrier) {
    for (EntryCase test_case : {EntryCase::AuthenticatedExceptionMove, EntryCase::AuthenticatedExceptionBranch}) {
        assertCarrierFromEntry(EntryPhase::AfterRestore, test_case);
    }
}

TEST_F(ContinuationWalkTest, ExceptionExitRequiresBothGeneratedInstructions) {
    for (EntryCase test_case : {EntryCase::ExceptionMoveWithoutBranch, EntryCase::ExceptionBranchWithoutMove}) {
        assertCarrierFromEntry(EntryPhase::AfterRestore, test_case);
    }
}

TEST_F(ContinuationWalkTest, SampledEntryWithPointerAuthenticationRetainsCarrier) {
    for (EntryPhase phase : {EntryPhase::BeforeSave, EntryPhase::AfterSave, EntryPhase::BeforeAllocation,
                            EntryPhase::AfterAllocation, EntryPhase::Complete, EntryPhase::BeforeSpRestore,
                            EntryPhase::AfterDeallocation, EntryPhase::AfterRestore}) {
        assertCarrierFromEntry(phase, EntryCase::PointerAuthentication);
    }
}
#endif

} // namespace
