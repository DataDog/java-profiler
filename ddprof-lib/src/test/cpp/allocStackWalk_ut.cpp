/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <functional>
#include <vector>
#include <ucontext.h>
#include "hotspot/vmStructs.inline.h"
#include "jvmThread.h"
#include "profiler.h"
#include "threadLocalData.inline.h"

class VMTestAccessor {
public:
    static bool hotspot() { return VM::_hotspot; }
    static void hotspot(bool value) { VM::_hotspot = value; }
};

class JVMThreadTestAccessor {
public:
    static jfieldID tid() { return JVMThread::_tid; }
    static void install(pthread_key_t key, jfieldID tid) {
        JVMThread::_tid = tid;
        JVMThread::_jvm_thread._key = key;
    }
};

class HotspotSupportTestAccessor {
public:
    static int walk(void* context, ASGCT_CallFrame* frames, uintptr_t sp, uintptr_t fp, const void* pc) {
        StackWalkFeatures features{};
        return HotspotSupport::walkVM(context, frames, 2, features, ALLOC_SAMPLE,
                                     pc, true, sp, fp, 0, nullptr, true);
    }
};

// Three generated blobs model an allocation stub followed by two Java callers.
// Their return PCs deliberately point at ret instructions; the frames remain live.
class AllocStackWalkTest : public ::testing::Test, protected VMStructs {
protected:
    struct Anchor { uintptr_t sp; uintptr_t fp; const void* pc; };
    struct Thread { Anchor anchor; void* vframe; } thread{};
    struct Holder { jmethodID* ids; } holder{};
    struct Pool { Holder* holder; } pool{};
    struct ConstMethod { Pool* pool; unsigned short number; } constants[2]{};
    struct Method { ConstMethod* constants; } methods[2]{};
    struct Blob {
        const char* name;
        int frame_size;
        short complete;
        const void* code;
        Method* method;
        int scopes[2];
        int size;
        instruction_t instructions[8];
    };
    struct alignas(256) Block { uintptr_t used; Blob blob; } blocks[3]{};
    struct Heap { void* low; void* high; void* map; } heap{};
    unsigned char segmap[3]{};
    jmethodID ids[3]{};
    alignas(16) uintptr_t stack[32]{};
    ASGCT_CallFrame frames[3]{};
    std::vector<std::function<void()>> restores;
    pthread_key_t owned_key = INVALID_KEY;
    pthread_key_t old_key = INVALID_KEY;
    jfieldID old_tid = nullptr;
    bool old_hotspot = false;

    template<typename T> void set(T& field, T value) {
        T previous = field;
        restores.emplace_back([&field, previous] { field = previous; });
        field = value;
    }

    void SetUp() override {
        old_hotspot = VMTestAccessor::hotspot();
        VMTestAccessor::hotspot(true);
        old_key = JVMThread::key();
        old_tid = JVMThreadTestAccessor::tid();
        ASSERT_EQ(0, pthread_key_create(&owned_key, nullptr));
        ASSERT_EQ(0, pthread_setspecific(owned_key, &thread));
        JVMThreadTestAccessor::install(owned_key, reinterpret_cast<jfieldID>(1));
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        ProfiledThread::current()->setJavaThread(true);
        set(TYPE_SIZE_NAME(VMThread), uint64_t(sizeof(Thread)));
        set(TYPE_SIZE_NAME(VMJavaFrameAnchor), uint64_t(sizeof(Anchor)));
        set(TYPE_SIZE_NAME(VMNMethod), uint64_t(sizeof(Blob)));
        set(TYPE_SIZE_NAME(VMMethod), uint64_t(sizeof(Method)));
        set(_thread_anchor_offset, offset(offsetof(Thread, anchor)));
        set(_thread_vframe_offset, offset(offsetof(Thread, vframe)));
        set(_anchor_sp_offset, offset(offsetof(Anchor, sp)));
        set(_anchor_fp_offset, offset(offsetof(Anchor, fp)));
        set(_anchor_pc_offset, offset(offsetof(Anchor, pc)));
        set(_code_heap_low, static_cast<const void*>(blocks));
        set(_code_heap_high, static_cast<const void*>(blocks + 3));
        set(_code_heap[0], reinterpret_cast<char*>(&heap));
        set(_code_heap[1], static_cast<char*>(nullptr));
        set(_code_heap[2], static_cast<char*>(nullptr));
        set(_code_heap_memory_offset, offset(0));
        set(_code_heap_segmap_offset, offset(offsetof(Heap, map)));
        set(_code_heap_segment_shift, offset(8));
        set(_heap_block_used_offset, offset(0));
        set(_vs_low_offset, offset(offsetof(Heap, low)));
        set(_vs_high_offset, offset(offsetof(Heap, high)));
        set(_interpreter_nm, static_cast<VMNMethod*>(nullptr));
        set(_nmethod_name_offset, offset(offsetof(Blob, name)));
        set(_frame_size_offset, offset(offsetof(Blob, frame_size)));
        set(_frame_complete_offset, offset(offsetof(Blob, complete)));
        set(_code_offset, offset(-1));
        set(_code_address, offset(offsetof(Blob, code)));
        set(_nmethod_entry_offset, offset(-1));
        set(_nmethod_entry_address, offset(offsetof(Blob, code)));
        set(_nmethod_method_offset, offset(offsetof(Blob, method)));
        set(_nmethod_level_offset, offset(-1));
        set(_nmethod_immutable_offset, offset(-1));
        set(_scopes_pcs_offset, offset(offsetof(Blob, scopes)));
        set(_blob_size_offset, offset(offsetof(Blob, size)));
        set(_method_constmethod_offset, offset(offsetof(Method, constants)));
        set(_constmethod_constants_offset, offset(offsetof(ConstMethod, pool)));
        set(_constmethod_idnum_offset, offset(offsetof(ConstMethod, number)));
        set(_pool_holder_offset, offset(offsetof(Pool, holder)));
        set(_jmethod_ids_offset, offset(offsetof(Holder, ids)));
        heap = {blocks, blocks + 3, segmap};
        ids[0] = reinterpret_cast<jmethodID>(2);
        ids[1] = reinterpret_cast<jmethodID>(0x1110);
        ids[2] = reinterpret_cast<jmethodID>(0x2220);
        holder.ids = ids;
        pool.holder = &holder;
        for (int i = 0; i < 2; i++) {
            constants[i] = {&pool, static_cast<unsigned short>(i)};
            methods[i].constants = &constants[i];
        }
        for (int i = 0; i < 3; i++) {
            blocks[i].used = 1;
            Blob& blob = blocks[i].blob;
            blob.name = i == 0 ? "allocation runtime" : "nmethod";
            blob.frame_size = 4;
            blob.size = sizeof(Blob);
            blob.code = blob.instructions;
            blob.method = i == 0 ? nullptr : &methods[i - 1];
#ifdef __aarch64__
            blob.instructions[2] = 0xd65f03c0;
#else
            blob.instructions[2] = 0xc3;
#endif
        }
        stack[4 - FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(pc(1));
        stack[8 - FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(pc(2));
    }

    void TearDown() override {
        for (auto it = restores.rbegin(); it != restores.rend(); ++it) (*it)();
        JVMThreadTestAccessor::install(old_key, old_tid);
        if (owned_key != INVALID_KEY) pthread_key_delete(owned_key);
        ProfiledThread::release();
        VMTestAccessor::hotspot(old_hotspot);
    }

    const void* pc(int blob) { return &blocks[blob].blob.instructions[2]; }

    int walk(bool stub, bool misaligned = false) {
        uintptr_t sp = reinterpret_cast<uintptr_t>(stack + (stub ? 0 : 4));
        if (misaligned) sp++;
        thread.anchor = {sp, 0, pc(stub ? 0 : 1)};
        ucontext_t empty{};
        return HotspotSupportTestAccessor::walk(&empty, frames, sp, 0, thread.anchor.pc);
    }
};

TEST_F(AllocStackWalkTest, ReturnAddressAtRetPreservesBothJavaCallers) {
    ASSERT_EQ(2, walk(false));
    EXPECT_EQ(ids[1], frames[0].method_id);
    EXPECT_EQ(ids[2], frames[1].method_id);
}

TEST_F(AllocStackWalkTest, CompleteAllocationStubUsesSharedFrameSizeUnwindAtDepthZero) {
    ASSERT_EQ(2, walk(true));
    EXPECT_EQ(ids[1], frames[0].method_id);
    EXPECT_EQ(ids[2], frames[1].method_id);
}

TEST_F(AllocStackWalkTest, MisalignedStubSenderIsRejectedBeforeItIsRead) {
    ASSERT_EQ(1, walk(true, true));
    EXPECT_EQ(BCI_ERROR, frames[0].bci);
    EXPECT_STREQ("break_misaligned_sp", reinterpret_cast<const char*>(frames[0].method_id));
}
