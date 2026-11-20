/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <cstddef>
#include <cstring>
#include <memory>
#include <sys/mman.h>
#include <ucontext.h>
#include <unistd.h>
#include <vector>
#include "codeCache.h"
#include "counters.h"
#include "hotspot/frozenStackWalker.h"
#include "hotspot/vmStructs.inline.h"
#include "jvmThread.h"
#include "libraries.h"
#include "profiler.h"
#include "stackFrame.h"
#include "threadLocalData.inline.h"
#include "vmEntry.h"

#ifndef COUNTERS
#error "originAnchorFrozen_ut requires COUNTERS in the matching production cohort and test"
#endif

class VMTestAccessor {
public:
    static void configure() {
        VM::_java_version = 21;
        VM::_hotspot_version = 21;
        VM::_hotspot = true;
        VM::_cont_runtime_classifiable = true;
    }

    static void setContRuntimeClassifiable(bool v) { VM::_cont_runtime_classifiable = v; }
};

class JVMThreadTestAccessor {
public:
    static void install(pthread_key_t key) {
        JVMThread::_tid = reinterpret_cast<jfieldID>(1);
        JVMThread::_jvm_thread._key = key;
    }
};

class HotspotSupportTestAccessor {
public:
    static int walk(void* context, ASGCT_CallFrame* frames, int capacity, bool* truncated) {
        StackWalkFeatures features{}; // cstack=vm: retain the continuation root
        return HotspotSupport::walkVM(context, frames, capacity, features,
                                      EXECUTION_SAMPLE, 0, truncated);
    }
};

namespace {

// Mangled names verified against Oracle Graal 21.0.8+12 libjvm symbols.
const char* const kFreezeSymbol = "_ZN10FreezeBase14recurse_freezeER5frameS1_ibb";
const char* const kNativeCallSymbol = "_ZN2os13javaTimeNanosEv";

TEST(ContFreezeThawSymbolTest, FreezeThawRuntimeSymbolsAreClassified) {
    EXPECT_TRUE(isContFreezeThawEntry(kFreezeSymbol));
    EXPECT_TRUE(isContFreezeThawEntry("_Z6freezeI6ConfigIL8oop_kind0E12G1BarrierSetEEiP10JavaThreadPl"));
    EXPECT_TRUE(isContFreezeThawEntry("_Z4thawI6ConfigIL8oop_kind0E12G1BarrierSetEEPlP10JavaThreadi"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN8ThawBase9thaw_slowEP17stackChunkOopDescb"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN6FreezeI6ConfigIL8oop_kind0E12G1BarrierSetEE15try_freeze_fastEv"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZL15freeze_internalI6ConfigIL8oop_kind0E12G1BarrierSetELb0EE13freeze_resultP10JavaThreadPl"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN6ConfigIL8oop_kind0E12G1BarrierSetE4thawEP10JavaThreadN12Continuation9thaw_kindE"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN4ThawI6ConfigIL8oop_kind0E12G1BarrierSetEE9thaw_fastEP17stackChunkOopDesc"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN12Continuation12freeze_entryEv"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN12Continuation10thaw_entryEv"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN12Continuation12prepare_thawEP10JavaThreadb"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZN12Continuation30set_cont_fastpath_thread_stateEP10JavaThread"));
    EXPECT_TRUE(isContFreezeThawEntry("_ZL13freeze_epilogP10JavaThreadR19ContinuationWrapper13freeze_result"));
    // Ordinary native calls, unrelated Continuation helpers and the BSS
    // entry-pointer variables stay unmarked.
    EXPECT_FALSE(isContFreezeThawEntry(kNativeCallSymbol));
    EXPECT_FALSE(isContFreezeThawEntry("_ZN12Continuation3pinEP10JavaThread"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZN12Continuation5unpinEP10JavaThread"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZN12Continuation21is_cont_barrier_frameERK5frame"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZN13SharedRuntime13get_poll_stubEv"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZL12freeze_entry"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZL10thaw_entry"));
    EXPECT_FALSE(isContFreezeThawEntry("_ZN13SharedRuntime18_cont_doYield_stubE"));
}

// The capability requires both executable entry families: data pointers,
// address getters or a single phase prove nothing about the executing runtime.
TEST(ContRuntimeCapabilityTest, RequiresBothExecutableEntryFamilies) {
    constexpr uintptr_t kCapabilityLibBase = 0x5a5e00000000ULL;
    auto classify = [](std::initializer_list<const char*> names) {
        CodeCache lib("capability_symbols", /*lib_index=*/-1,
                      reinterpret_cast<const char*>(kCapabilityLibBase),
                      reinterpret_cast<const char*>(kCapabilityLibBase + 0x1000),
                      reinterpret_cast<const char*>(kCapabilityLibBase));
        uintptr_t address = kCapabilityLibBase;
        for (const char* name : names) {
            lib.add(reinterpret_cast<const void*>(address), 0x10, name);
            address += 0x10;
        }
        lib.sort();
        return VM::markContRuntimeAndClassify(&lib);
    };
    EXPECT_TRUE(classify({"_Z6freezeI6ConfigIL8oop_kind0E12G1BarrierSetEEiP10JavaThreadPlc1",
                          "_Z4thawI6ConfigIL8oop_kind0E12G1BarrierSetEEPlP10JavaThreadic1"}));
    EXPECT_FALSE(classify({"_Z6freezeI6ConfigIL8oop_kind0E12G1BarrierSetEEiP10JavaThreadPlc2"}));
    EXPECT_FALSE(classify({"_Z4thawI6ConfigIL8oop_kind0E12G1BarrierSetEEPlP10JavaThreadic2"}));
    // Exact Temurin 25 and 27 libjvm names: the static entry templates have internal linkage.
    EXPECT_TRUE(classify({"_ZL6freezeI6ConfigIL8oop_kind0E12G1BarrierSetEEiP10JavaThreadPl",
                          "_ZL4thawI6ConfigIL8oop_kind0E12G1BarrierSetEEPlP10JavaThreadi"}));
    EXPECT_FALSE(classify({"_ZL6freezeI6ConfigIL8oop_kind0E12G1BarrierSetEEiP10JavaThreadPl"}));
    EXPECT_FALSE(classify({"_ZL4thawI6ConfigIL8oop_kind0E12G1BarrierSetEEPlP10JavaThreadi"}));
    EXPECT_FALSE(classify({"_ZN13SharedRuntime18_cont_doYield_stubEc3"}));
    EXPECT_FALSE(classify({"_ZN12Continuation12freeze_entryEvc4", "_ZN12Continuation10thaw_entryEvc4"}));
    EXPECT_FALSE(classify({}));
}

#ifndef UNIT_TEST
// Exact-original-cohort builds publish the synthetic library through a
// UNIT_TEST-compiled shim; Gradle builds use addLibraryForTest directly.
extern "C" bool v38_register_native_lib(CodeCache* lib);
#endif
constexpr size_t kNativeLibSpan = 0x1000;
constexpr size_t kFreezeOff = 0x100;
constexpr size_t kNativeCallOff = 0x300;
constexpr size_t kNativeCallOff2 = 0x500;
// DWARF row for the fully-traversed native-call frame: CFA = FP + 0x10, the
// saved caller FP at sp' + 0x10 and the return address at sp' + 0x18.
constexpr int kNativeCfaOff = 0x10;
constexpr int kNativeFpOff = 0x10;
constexpr int kNativePcOff = 0x18;

// A fully-walked native prefix (e.g. System.nanoTime from a mounted Java
// frame) must recover the frozen callers; any anchor-mediated jump, a
// freeze/thaw runtime origin, or unrecognized symbols must reject them.
// The registers are synthetic fixture state, not an authenticated VM capture.
class OriginAnchorFrozenTest : public ::testing::Test, protected VMStructs {
protected:
    static constexpr int CAPACITY = 8;
    // Kernel-chosen anonymous pages: sanitizer shadow layouts reject the
    // fixed synthetic addresses on some architectures, and any real mapping
    // is safe for the signal-frame probe reads the walk performs.
    uintptr_t native_base = 0;
    uintptr_t unresolved_base = 0;
    static constexpr int LEAF_BCI = 27;
    static constexpr int MIDDLE_BCI = 44;
    static constexpr int OLDER_BCI = 74;
    struct Flag { const char* name; void* value; int type; };
    struct Anchor { uintptr_t sp; uintptr_t fp; const void* pc; };
    struct Thread {
        void* entry;
        uintptr_t* oop_handle;
        Anchor anchor;
        void* vframe;
        int state;
        int padding;
    } thread{};
    struct Chunk {
        uintptr_t header;
        Chunk* parent;
        int size, sp, bottom, argsize;
        uintptr_t words[16];
    };
    struct Continuation { uintptr_t header; Continuation* parent; Chunk* tail; } continuation{};
    struct Carrier { uintptr_t header; Continuation* continuation; } carrier{};
    std::unique_ptr<Chunk> chunk{new Chunk{}};
    uintptr_t carrier_oop = reinterpret_cast<uintptr_t>(&carrier);
    struct Holder { jmethodID* ids; } holder{};
    struct Pool { Holder* holder; } pool{};
    struct ConstMethod { Pool* pool; unsigned short number; unsigned short padding; };
    struct MethodData { ConstMethod header; unsigned char bytecode[96]; } constants[4]{};
    struct Method { ConstMethod* constants; } methods[4]{};
    Method* method_slots[4]{};
    jmethodID ids[5]{};
    struct Blob {
        const char* name;
        int frame_size;
        int size;
        void* method;
        int level;
        short frame_complete;
        int scopes_pcs_base[2];
        const void* code;
        const void* entry_address;
        instruction_t instructions[32];
    };
    struct alignas(256) Block { uintptr_t used; Blob blob; } blocks[3]{};
    struct Heap { const void* low; const void* high; unsigned char* map; } heap{};
    unsigned char segmap[3]{};
    CodeCache symbols{"origin anchor frozen layout"};
    CodeCache* native_lib = nullptr;
    bool collector = true, compressed = false;
    Flag flags[2]{{"UseG1GC", &collector, VMFlag::Bool},
                  {"UseCompressedOops", &compressed, VMFlag::Bool}};
    const char* flag_base = reinterpret_cast<const char*>(flags);
    size_t flag_count = 2;
    int offsets[9]{offsetof(Carrier, continuation), offsetof(Continuation, parent),
                   offsetof(Continuation, tail), offsetof(Chunk, parent), offsetof(Chunk, size),
                   offsetof(Chunk, sp), offsetof(Chunk, bottom), offsetof(Chunk, argsize),
                   offsetof(Chunk, words)};

    const void* pc(int block) { return &blocks[block].blob.instructions[4]; }
    // Non-barrier slots in the StubRoutines blob for the entry-frame controls.
    const void* stubPc() { return &blocks[1].blob.instructions[8]; }
    const void* entryPc() { return &blocks[1].blob.instructions[12]; }
    VMNMethod* blob(int block) { return VMNMethod::cast_raw(&blocks[block].blob); }
    const void* nativePc(size_t off) const {
        return reinterpret_cast<const void*>(native_base + off);
    }
    const void* unresolvedPc() const {
        return reinterpret_cast<const void*>(unresolved_base + 0x100);
    }

    // All singleton/TLS metadata is installed only after fork, as in
    // frozenStackWalker_ut.cpp. The parent never publishes a frozen layout.
    void configure() {
        static_assert(sizeof(Block) == 256, "one blob per CodeHeap segment");
        static_assert(offsetof(Block, blob) == sizeof(uintptr_t), "real CodeHeap block header");
        static_assert(offsetof(MethodData, bytecode) == sizeof(ConstMethod), "bytecode follows header");
        dprintf(2, "[child] configure: start\n");
        VMTestAccessor::configure();
        ASSERT_FALSE(FrozenStackWalker::available());
        pthread_key_t key = INVALID_KEY;
        ASSERT_EQ(0, pthread_key_create(&key, nullptr));
        ASSERT_EQ(0, pthread_setspecific(key, &thread));
        JVMThreadTestAccessor::install(key);
        ProfiledThread::initCurrentThread();
        ASSERT_NE(nullptr, ProfiledThread::current());
        ProfiledThread::current()->setJavaThread(true);
        dprintf(2, "[child] configure: tls done\n");
        void* native_range = mmap(nullptr, kNativeLibSpan, PROT_READ | PROT_WRITE,
                                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ASSERT_NE(MAP_FAILED, native_range);
        void* unresolved_range = mmap(nullptr, 0x1000, PROT_READ | PROT_WRITE,
                                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ASSERT_NE(MAP_FAILED, unresolved_range);
        native_base = reinterpret_cast<uintptr_t>(native_range);
        unresolved_base = reinterpret_cast<uintptr_t>(unresolved_range);
        dprintf(2, "[child] configure: mmap ok native=%p unresolved=%p\n", native_range, unresolved_range);
        dprintf(2, "[child] configure: bases ready\n");
        dprintf(2, "[child] configure: pre-nativelib\n");
        native_lib = new CodeCache("origin_anchor_native", /*lib_index=*/-1,
                                   reinterpret_cast<const char*>(native_base),
                                   reinterpret_cast<const char*>(native_base + kNativeLibSpan),
                                   reinterpret_cast<const char*>(native_base));
        native_lib->setTextBase(reinterpret_cast<const char*>(native_base));
        native_lib->add(nativePc(kFreezeOff), 0x20, kFreezeSymbol);
        native_lib->add(nativePc(kNativeCallOff), 0x20, kNativeCallSymbol);
        native_lib->add(nativePc(kNativeCallOff2), 0x20, "clock_gettime");
        native_lib->sort();
        // setDwarfTable keeps the pointer: allocate like the production parser
        // would, not a stack array that would dangle after configure().
        // Binary search needs rows ordered by location: freeze, call, slow.
        FrameDesc* native_rows = static_cast<FrameDesc*>(malloc(3 * sizeof(FrameDesc)));
        const size_t row_offsets[3] = {kFreezeOff, kNativeCallOff, kNativeCallOff2};
        for (int i = 0; i < 3; i++) {
            native_rows[i] = {static_cast<u32>(row_offsets[i]),
                              static_cast<u32>(kNativeCfaOff << 8) | static_cast<u32>(DW_REG_FP),
                              kNativeFpOff, kNativePcOff, 0};
        }
        native_lib->setDwarfTable(native_rows, 3);
        dprintf(2, "[child] configure: nativelib built\n");
        // The production marking path: the same predicate and mark value that
        // VM::initLibrary installs on libjvm.
        native_lib->mark(isContFreezeThawEntry, MARK_CONT_RUNTIME);
#ifdef UNIT_TEST
        ASSERT_TRUE(Libraries::instance()->addLibraryForTest(native_lib));
#else
        ASSERT_TRUE(v38_register_native_lib(native_lib));
#endif
        dprintf(2, "[child] configure: nativelib registered\n");
        dprintf(2, "[child] configure: pre-typemap\n");
        TYPE_SIZE_NAME(VMThread) = sizeof(Thread);
        TYPE_SIZE_NAME(VMJavaThread) = sizeof(Thread);
        TYPE_SIZE_NAME(VMJavaFrameAnchor) = sizeof(Anchor);
        TYPE_SIZE_NAME(VMNMethod) = sizeof(Blob);
        TYPE_SIZE_NAME(VMMethod) = sizeof(Method);
        TYPE_SIZE_NAME(VMConstMethod) = sizeof(ConstMethod);
        _thread_oop_offset = offsetof(Thread, oop_handle);
        _oop_handle_offset = 0;
        _thread_anchor_offset = offsetof(Thread, anchor);
        _thread_state_offset = offsetof(Thread, state);
        _thread_vframe_offset = offsetof(Thread, vframe);
        _thread_exception_offset = _thread_osthread_offset = -1;
        _anchor_sp_offset = offsetof(Anchor, sp);
        _anchor_fp_offset = offsetof(Anchor, fp);
        _anchor_pc_offset = offsetof(Anchor, pc);
        thread.oop_handle = &carrier_oop;
        thread.state = _thread_in_Java;
        carrier.continuation = &continuation;
        continuation.tail = chunk.get();
        _cont_entry_offset = -1;
        _cont_entry_thread_offset = -1;
        _cont_entry_return_pc = nullptr;
        _enter_special_nm = nullptr;
        _cont_return_barrier = pc(1);
        _code_heap_low = blocks;
        _code_heap_high = blocks + 3;
        _code_heap[0] = reinterpret_cast<char*>(&heap);
        _code_heap[1] = _code_heap[2] = nullptr;
        _code_heap_memory_offset = 0;
        _code_heap_segmap_offset = offsetof(Heap, map);
        _vs_low_offset = offsetof(Heap, low);
        _vs_high_offset = offsetof(Heap, high);
        _code_heap_segment_shift = 8;
        _heap_block_used_offset = 0;
        _nmethod_name_offset = offsetof(Blob, name);
        _frame_size_offset = offsetof(Blob, frame_size);
        _blob_size_offset = offsetof(Blob, size);
        _nmethod_method_offset = offsetof(Blob, method);
        _nmethod_level_offset = offsetof(Blob, level);
        _frame_complete_offset = offsetof(Blob, frame_complete); // 0: complete
        _call_stub_return = entryPc();
        _frame_entry_frame_call_wrapper_offset = 6 * static_cast<int>(sizeof(uintptr_t));
        _call_wrapper_anchor_offset = 2 * static_cast<int>(sizeof(uintptr_t));
        // walkVM's compiled-frame branch probes nmethod scope metadata and
        // SignalFrame::decode reads the native PCs: point the scopes pair at
        // an empty range and map the synthetic ranges so both are safe.
        _scopes_pcs_offset = offsetof(Blob, scopes_pcs_base);
        _nmethod_immutable_offset = -1;
        // walkVM's frame-adjust path reads the nmethod entry address; point it
        // at a dedicated slot in the Blob so the load is aligned and valid.
        _nmethod_entry_address = offsetof(Blob, entry_address);
        _code_offset = -1;
        _code_address = offsetof(Blob, code);
        dprintf(2, "[child] configure: pre-blocks\n");
        heap = {blocks, blocks + 3, segmap};
        for (int i = 0; i < 3; i++) {
            blocks[i].used = 1;
            blocks[i].blob.name = i == 0 ? "Interpreter" : i == 1 ? "StubRoutines" : "nmethod";
            blocks[i].blob.size = sizeof(Blob);
            blocks[i].blob.frame_size = i == 1 ? 2 : i == 2 ? 8 : 0;
            blocks[i].blob.method = &methods[3];
            blocks[i].blob.level = 4;
            blocks[i].blob.scopes_pcs_base[0] = 0; // empty PcDesc range
            blocks[i].blob.scopes_pcs_base[1] = 0;
            blocks[i].blob.code = blocks[i].blob.instructions;
            blocks[i].blob.entry_address = blocks[i].blob.instructions + 2;
#ifdef __aarch64__
            for (auto& instruction : blocks[i].blob.instructions) instruction = 0xd503201f;
#else
            memset(blocks[i].blob.instructions, 0x90, sizeof(blocks[i].blob.instructions));
#endif
        }
        // Same barrier-load prefix as continuationWalk_ut.cpp, naming entry
        // at thread offset zero. Validate the prefix with the production decoder.
#ifdef __aarch64__
        const unsigned char barrier_prefix[]{0x88, 0x03, 0x40, 0xf9, 0x1f, 0x01, 0x00, 0x91};
#else
        const unsigned char barrier_prefix[]{0x49, 0x8b, 0xa7, 0, 0, 0, 0, 0x90};
#endif
        static_assert(offsetof(Thread, entry) == 0, "barrier loads this thread entry");
        memcpy(const_cast<void*>(pc(1)), barrier_prefix, sizeof(barrier_prefix));
        dprintf(2, "[child] configure: pre-entry-decode\n");
        initContEntryThreadOffset();
        ASSERT_EQ(0, contEntryThreadOffset());
        dprintf(2, "[child] configure: entry decoded\n");
        _interpreter_nm = blob(0);
        _method_constmethod_offset = offsetof(Method, constants);
        _constmethod_constants_offset = offsetof(ConstMethod, pool);
        _constmethod_idnum_offset = offsetof(ConstMethod, number);
        _pool_holder_offset = offsetof(Pool, holder);
        _jmethod_ids_offset = offsetof(Holder, ids);
        _can_dereference_jmethod_id = true;
        holder.ids = ids;
        pool.holder = &holder;
        ids[0] = reinterpret_cast<jmethodID>(4); // ids[0] is the cache length
        for (int i = 0; i < 4; i++) {
            constants[i].header = {&pool, static_cast<unsigned short>(i), 0};
            methods[i].constants = &constants[i].header;
            method_slots[i] = &methods[i];
            ids[i + 1] = reinterpret_cast<jmethodID>(&method_slots[i]);
            ASSERT_EQ(ids[i + 1], VMMethod::cast_raw(&methods[i])->validatedId());
        }
#ifdef __aarch64__
        _interpreter_frame_bcp_offset = -9; // VMStructs::initOffsets, JDK 21
#else
        _interpreter_frame_bcp_offset = -8;
#endif
        // One oldest heap interpreter frame. sp[-2] is FP-relative to its own
        // slot, whereas locals/last_sp/sender_sp are relative to FP (word 12).
        chunk->size = 16;
        chunk->sp = 2;
        chunk->bottom = 16;
        chunk->words[0] = 12;
        chunk->words[1] = reinterpret_cast<uintptr_t>(pc(0));
        chunk->words[12 + InterpreterFrame::method_offset] = reinterpret_cast<uintptr_t>(&methods[2]);
        chunk->words[12 + InterpreterFrame::bcp_offset()] = reinterpret_cast<uintptr_t>(constants[2].bytecode + OLDER_BCI);
        chunk->words[12 + InterpreterFrame::bcp_offset() + 1] = 15 - 12; // two local/argument words above FP/PC
        chunk->words[12 - 2] = static_cast<uintptr_t>(intptr_t(2 - 12)); // last_sp
        chunk->words[12 + InterpreterFrame::sender_sp_offset] = 16 - 12;
        _libjvm = &symbols;
        _flags_addr = reinterpret_cast<address>(&flag_base);
        _flag_count = reinterpret_cast<address>(&flag_count);
        _flag_name_offset = offsetof(Flag, name);
        _flag_addr_offset = offsetof(Flag, value);
        _flag_type_offset = offsetof(Flag, type);
        TYPE_SIZE_NAME(VMFlag) = sizeof(Flag);
        const char* names[]{
            "_ZN16java_lang_Thread20_continuation_offsetE",
            "_ZN28jdk_internal_vm_Continuation14_parent_offsetE",
            "_ZN28jdk_internal_vm_Continuation12_tail_offsetE",
            "_ZN26jdk_internal_vm_StackChunk14_parent_offsetE",
            "_ZN26jdk_internal_vm_StackChunk12_size_offsetE",
            "_ZN26jdk_internal_vm_StackChunk10_sp_offsetE",
            "_ZN26jdk_internal_vm_StackChunk14_bottom_offsetE",
            "_ZN26jdk_internal_vm_StackChunk15_argsize_offsetE",
            "_ZN23InstanceStackChunkKlass16_offset_of_stackE"};
        dprintf(2, "[child] configure: pre-symbols\n");
        for (int i = 0; i < 9; i++) symbols.add(&offsets[i], sizeof(offsets[i]), names[i]);
        FrozenStackWalker::init();
        ASSERT_TRUE(FrozenStackWalker::available());
        dprintf(2, "[child] configure: done available=%d entryOffset=%d\n",
                static_cast<int>(FrozenStackWalker::available()),
                static_cast<int>(contEntryThreadOffset()));
    }

    enum Control {
        JavaOriginA,               // interpreter interrupted PC
        NativeCallAnchorB,         // e.g. System.nanoTime, fully walked native prefix
        FreezeRuntimeAnchorB2,     // interrupted inside FreezeBase::recurse_freeze
        NativeCallFallbackB3,     // native prefix only reachable via the anchor fallback
        NativeCallUnclassifiableB4, // stripped symbol table: classification unavailable
        OneMountedFrameB5,         // single mounted Java frame returns to the barrier
        GenericAnchorRedirectB6,   // unresolvable callee redirected via a compiled anchor
        SameBlobStubRedirectB7,    // stub-blob anchor redirect with a changed cursor
        EntryFrameRedirectB8,      // entry-frame anchor redirection
        IdenticalCursorB9,        // stub-blob anchor redirect with an identical cursor
        SpOnlyCursorChangeB10,    // stub-blob anchor redirect changing SP alone
        CompiledAnchorRedirectB11, // compiled-nmethod anchor redirect abandons that frame
        NativeCallNoAnchorC,
    };

    // Expected shape per control: the interrupted native frame is emitted for
    // origins with a resolvable name; freeze/thaw-marked origins and any
    // anchor-mediated jump reject the frozen-caller recovery.
    struct Expected {
        bool recovers;
        bool has_native_frame;
        bool has_stub_frame;
        bool has_skip_marker;
        bool has_leaf;
        bool has_middle;
        bool has_compiled_frame;
        int consumed_delta;
        int fallback_delta;
    };
    static const Expected& expected(Control c) {
        static const Expected table[] = {
                /* JavaOriginA */ {true, false, false, false, true, true, false, 1, 0},
                /* NativeCallAnchorB */ {true, true, false, false, true, true, false, 1, 0},
                /* FreezeRuntimeAnchorB2 */ {false, true, false, false, true, true, false, 1, 0},
                /* NativeCallFallbackB3 */ {false, true, false, false, true, true, false, 0, 1},
                /* NativeCallUnclassifiableB4 */ {false, true, false, false, true, true, false, 1, 0},
                /* OneMountedFrameB5 */ {true, true, false, false, true, false, false, 1, 0},
                /* GenericAnchorRedirectB6 */ {false, true, false, true, false, false, true, 0, 0},
                /* SameBlobStubRedirectB7 */ {false, true, true, false, true, true, false, 1, 0},
                /* EntryFrameRedirectB8 */ {false, true, false, false, true, true, false, 1, 0},
                /* IdenticalCursorB9 */ {true, true, true, false, true, true, false, 1, 0},
                /* SpOnlyCursorChangeB10 */ {false, true, true, false, true, true, false, 1, 0},
                /* CompiledAnchorRedirectB11 */ {false, true, false, false, true, true, false, 1, 0},
                /* NativeCallNoAnchorC */ {false, true, false, false, false, false, false, 0, 0},
        };
        return table[static_cast<int>(c)];
    }

    void controls() {
        // Native stack storage must be local: walkVM bounds it from its own SP.
        // All controls share these exact stack/anchor addresses and heap oops.
        alignas(16) uintptr_t stack[40]{};
        stack[16 + InterpreterFrame::method_offset] = reinterpret_cast<uintptr_t>(&methods[0]);
        stack[16 + InterpreterFrame::bcp_offset()] = reinterpret_cast<uintptr_t>(constants[0].bytecode + LEAF_BCI);
        stack[16] = reinterpret_cast<uintptr_t>(&stack[32]); // rbp chain to middle frame
        stack[16 + InterpreterFrame::sender_sp_offset] = reinterpret_cast<uintptr_t>(&stack[20]);
        stack[16 + FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(pc(0)); // return into middle frame
        stack[32 + InterpreterFrame::method_offset] = reinterpret_cast<uintptr_t>(&methods[1]);
        stack[32 + InterpreterFrame::bcp_offset()] = reinterpret_cast<uintptr_t>(constants[1].bytecode + MIDDLE_BCI);
        stack[32] = 0; // not followed: the next PC is the verified return barrier
        stack[32 + InterpreterFrame::sender_sp_offset] = reinterpret_cast<uintptr_t>(&stack[36]);
        stack[32 + FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(pc(1));
        // DWARF chain for the fully-walked native prefix: caller FP and return
        // address of the native frames, read at sp' + 0x10 / + 0x18. B6's
        // second native frame chains to an unresolvable PC instead (below).
        stack[4] = reinterpret_cast<uintptr_t>(&stack[16]);
        stack[5] = reinterpret_cast<uintptr_t>(pc(0));
        // The compiled-anchor frame's sender slot: its frame-size step lands
        // here and the return address is the verified barrier.
        stack[9] = reinterpret_cast<uintptr_t>(pc(1));
        // B7's stub frame-size step reads the leaf frame's FP and PC here.
        stack[2] = reinterpret_cast<uintptr_t>(&stack[16]);
        stack[3] = reinterpret_cast<uintptr_t>(pc(0));
        // B8's entry frame: call wrapper above FP, then the next anchor.
        stack[22] = reinterpret_cast<uintptr_t>(&stack[24]);
        stack[26] = reinterpret_cast<uintptr_t>(&stack[2]);
        stack[27] = reinterpret_cast<uintptr_t>(&stack[16]);
        stack[28] = reinterpret_cast<uintptr_t>(pc(0));
        thread.entry = &stack[20];
        thread.anchor = {reinterpret_cast<uintptr_t>(&stack[2]), reinterpret_cast<uintptr_t>(&stack[16]), pc(0)};
        for (Control control : {JavaOriginA, NativeCallAnchorB, FreezeRuntimeAnchorB2, NativeCallFallbackB3,
                                NativeCallUnclassifiableB4, OneMountedFrameB5, GenericAnchorRedirectB6,
                                SameBlobStubRedirectB7, EntryFrameRedirectB8, IdenticalCursorB9,
                                SpOnlyCursorChangeB10, CompiledAnchorRedirectB11, NativeCallNoAnchorC}) {
            dprintf(2, "[child] begin control %d\n", static_cast<int>(control));
            check(control, stack);
            if (::testing::Test::HasFailure()) return; // A must validate before the rest
        }
    }

    void check(Control control, uintptr_t* stack) {
        SCOPED_TRACE(static_cast<int>(control));
        if (control == NativeCallNoAnchorC) thread.anchor.sp = 0;
        // Per-control geometry: B5 leaf->barrier, B6 compiled anchor over
        // an unresolvable frame, B7 stub-blob anchor with a differing cursor,
        // B8 invalid anchor -> entry-frame redirect, B9 identical cursor,
        // B10 SP-only cursor change, B11 compiled frame replaced by the anchor.
        uintptr_t saved_leaf_pc_slot = 0, saved_chain_pc = 0, saved_chain_fp = 0;
        Anchor saved_anchor{};
        if (control == OneMountedFrameB5) {
            saved_leaf_pc_slot = stack[16 + FRAME_PC_SLOT];
            stack[16 + FRAME_PC_SLOT] = reinterpret_cast<uintptr_t>(pc(1));
        }
        if (control == GenericAnchorRedirectB6) {
            saved_chain_pc = stack[5];
            stack[5] = reinterpret_cast<uintptr_t>(unresolvedPc());
            saved_anchor = thread.anchor;
            thread.anchor = {reinterpret_cast<uintptr_t>(&stack[2]), 0, pc(2)};
        }
        if (control == SameBlobStubRedirectB7) {
            saved_chain_pc = stack[5];
            saved_chain_fp = stack[4];
            stack[5] = reinterpret_cast<uintptr_t>(stubPc());
            stack[4] = reinterpret_cast<uintptr_t>(&stack[40]); // differing cursor
            saved_anchor = thread.anchor;
            thread.anchor.pc = stubPc();
        }
        if (control == IdenticalCursorB9) {
            saved_chain_pc = stack[5];
            stack[5] = reinterpret_cast<uintptr_t>(stubPc());
            saved_anchor = thread.anchor;
            thread.anchor.pc = stubPc(); // cursor identical: pure correction
        }
        if (control == SpOnlyCursorChangeB10) {
            saved_chain_pc = stack[5];
            stack[5] = reinterpret_cast<uintptr_t>(stubPc());
            stack[0] = reinterpret_cast<uintptr_t>(&stack[16]);
            stack[1] = reinterpret_cast<uintptr_t>(pc(0));
            saved_anchor = thread.anchor;
            thread.anchor = {reinterpret_cast<uintptr_t>(&stack[0]),
                             reinterpret_cast<uintptr_t>(&stack[16]), stubPc()};
        }
        if (control == CompiledAnchorRedirectB11) {
            // The native caller returns into a compiled frame that the anchor
            // replaces before it is emitted; that frame cannot be the origin.
            saved_chain_pc = stack[5];
            stack[5] = reinterpret_cast<uintptr_t>(pc(2));
        }
        if (control == EntryFrameRedirectB8) {
            saved_chain_pc = stack[5];
            stack[5] = reinterpret_cast<uintptr_t>(entryPc());
            saved_anchor = thread.anchor;
            thread.anchor.pc = nullptr; // in-loop getFrame must fail
        }
        if (control == NativeCallUnclassifiableB4) VMTestAccessor::setContRuntimeClassifiable(false);
        ucontext_t context{};
#ifdef __APPLE__
        _STRUCT_MCONTEXT64 machine_context{};
        context.uc_mcontext = &machine_context;
#endif
        StackFrame frame(&context);
        bool native_origin = control != JavaOriginA;
        const void* native_origin_pc = nativePc(control == FreezeRuntimeAnchorB2 ? kFreezeOff
                : control == NativeCallFallbackB3 || control == GenericAnchorRedirectB6 ? kNativeCallOff2
                : kNativeCallOff);
        if (control == SameBlobStubRedirectB7) {
            ASSERT_TRUE(blob(1)->contains(stubPc()));
            ASSERT_NE(reinterpret_cast<uintptr_t>(&stack[40]), thread.anchor.fp); // cursor differs
        }
        if (control == EntryFrameRedirectB8) {
            ASSERT_EQ(entryPc(), _call_stub_return);
            ASSERT_EQ(6, &stack[22] - &stack[16]); // call wrapper slot vs FP
        }
        frame.pc() = native_origin ? reinterpret_cast<uintptr_t>(native_origin_pc)
                                    : reinterpret_cast<uintptr_t>(pc(0));
        frame.sp() = reinterpret_cast<uintptr_t>(&stack[native_origin ? 0 : 2]);
        // B/B2/B4/B5/B6/B11 seed a valid frame pointer so the DWARF rows walk the
        // native prefix toward the mounted frames; B3/C must fall back.
        frame.fp() = control == NativeCallFallbackB3 || control == NativeCallNoAnchorC
                ? 0 : native_origin ? reinterpret_cast<uintptr_t>(&stack[0])
                : reinterpret_cast<uintptr_t>(&stack[16]);
        if (control == IdenticalCursorB9 || control == SpOnlyCursorChangeB10) {
            ASSERT_TRUE(blob(1)->contains(stubPc()));
        }
        if (control == CompiledAnchorRedirectB11) {
            ASSERT_TRUE(blob(2)->isNMethod());
            ASSERT_FALSE(blob(2)->contains(thread.anchor.pc)); // redirect leaves the nmethod
        }
        if (native_origin) {
            ASSERT_EQ(nullptr, CodeHeap::findNMethod(reinterpret_cast<void*>(frame.pc())));
            Profiler::NativeFrameResolution resolution =
                    Profiler::instance()->resolveNativeFrameForWalkVM(frame.pc(), false, 0);
            ASSERT_EQ(control == FreezeRuntimeAnchorB2, resolution.mark == MARK_CONT_RUNTIME);
            ASSERT_EQ(BCI_NATIVE_FRAME, resolution.bci);
            ASSERT_NE(nullptr, resolution.method_name);
            if (control == GenericAnchorRedirectB6) {
                ASSERT_EQ(nullptr, Profiler::instance()->libraries()->findLibraryByAddress(unresolvedPc()));
                ASSERT_EQ(0, thread.anchor.fp); // compiled-frame anchor
            }
        }
        ASSERT_TRUE(blob(0)->isInterpreter());
        ASSERT_TRUE(FrozenStackWalker::available());
        ASSERT_TRUE(VMStructs::isContReturnBarrier(pc(1)));
        ASSERT_EQ(_thread_in_Java, VMThread::current()->state());
        ASSERT_EQ(carrier_oop, VMThread::current()->carrierThreadOop());
        ASSERT_EQ(nullptr, continuation.parent);
        ASSERT_EQ(chunk.get(), continuation.tail);
        ASSERT_EQ(nullptr, chunk->parent);
        ASSERT_TRUE(StackWalkValidation::isPlausibleInterpreterFrame(
                reinterpret_cast<uintptr_t>(&stack[16]), reinterpret_cast<uintptr_t>(&stack[2]), InterpreterFrame::bcp_offset()));
        const Expected& exp = expected(control);
        ASGCT_CallFrame frames[CAPACITY + 1]{};
        auto recovered = Counters::getCounter(WALKVM_FROZEN_RECOVERED);
        auto failed = Counters::getCounter(WALKVM_FROZEN_FAILED);
        auto interpreted = Counters::getCounter(WALKVM_FROZEN_INTERPRETED);
        auto barrier = Counters::getCounter(WALKVM_CONT_BARRIER_HIT);
        auto consumed = Counters::getCounter(WALKVM_ANCHOR_CONSUMED);
        auto fallback = Counters::getCounter(WALKVM_ANCHOR_FALLBACK);
        bool truncated = false;
        int depth = HotspotSupportTestAccessor::walk(&context, frames, CAPACITY, &truncated);
        // Death-test children lose buffered stdio on _exit; write(2) survives
        // so CI logs reveal the failing control on remote architectures.
        dprintf(2, "[child] control=%d depth=%d truncated=%d recovered=%d failed=%d\n",
                static_cast<int>(control), depth, truncated,
                static_cast<int>(Counters::getCounter(WALKVM_FROZEN_RECOVERED)),
                static_cast<int>(Counters::getCounter(WALKVM_FROZEN_FAILED)));
        if (control == NativeCallUnclassifiableB4) VMTestAccessor::setContRuntimeClassifiable(true);
        if (control == OneMountedFrameB5) stack[16 + FRAME_PC_SLOT] = saved_leaf_pc_slot;
        if (control == GenericAnchorRedirectB6 || control == EntryFrameRedirectB8) {
            stack[5] = saved_chain_pc;
            thread.anchor = saved_anchor;
        }
        if (control == CompiledAnchorRedirectB11) stack[5] = saved_chain_pc;
        if (control == SameBlobStubRedirectB7) {
            stack[5] = saved_chain_pc;
            stack[4] = saved_chain_fp;
            thread.anchor = saved_anchor;
        }
        if (control == IdenticalCursorB9) {
            stack[5] = saved_chain_pc;
            thread.anchor = saved_anchor;
        }
        if (control == SpOnlyCursorChangeB10) {
            stack[5] = saved_chain_pc;
            stack[0] = 0;
            stack[1] = 0;
            thread.anchor = saved_anchor;
        }
        int expect_depth = (exp.has_native_frame ? 1 : 0) + (exp.has_stub_frame ? 1 : 0)
                + (exp.has_skip_marker ? 1 : 0) + (exp.has_leaf ? 1 : 0) + (exp.has_middle ? 1 : 0)
                + (exp.has_compiled_frame ? 1 : 0) + (exp.recovers ? 1 : 0) + 1; // JVM Continuation root
        if (control != NativeCallNoAnchorC) {
            ASSERT_EQ(expect_depth, depth);
            int i = 0;
            if (exp.has_native_frame) {
                EXPECT_EQ(BCI_NATIVE_FRAME, frames[i].bci);
                // The freeze/thaw mark annotates B2's frame without dropping its symbol.
                EXPECT_STREQ(control == FreezeRuntimeAnchorB2 ? kFreezeSymbol
                             : control == NativeCallFallbackB3 || control == GenericAnchorRedirectB6
                                     ? "clock_gettime" : kNativeCallSymbol,
                             reinterpret_cast<const char*>(frames[i].method_id));
                i++;
            }
            if (exp.has_stub_frame) {
                EXPECT_EQ(BCI_NATIVE_FRAME, frames[i].bci);
                EXPECT_STREQ("StubRoutines", reinterpret_cast<const char*>(frames[i].method_id));
                i++;
            }
            if (exp.has_skip_marker) {
                EXPECT_EQ(BCI_ERROR, frames[i].bci);
                EXPECT_STREQ("[skipped frames]", reinterpret_cast<const char*>(frames[i].method_id));
                i++;
            }
            if (exp.has_compiled_frame) {
                EXPECT_EQ(ids[4], frames[i].method_id);
                EXPECT_EQ(FrameType::encode(FRAME_JIT_COMPILED, 0), frames[i].bci);
                i++;
            }
            if (exp.has_leaf) {
                EXPECT_EQ(ids[1], frames[i].method_id);
                EXPECT_EQ(FrameType::encode(FRAME_INTERPRETED, LEAF_BCI), frames[i].bci);
                i++;
            }
            if (exp.has_middle) {
                EXPECT_EQ(ids[2], frames[i].method_id);
                EXPECT_EQ(FrameType::encode(FRAME_INTERPRETED, MIDDLE_BCI), frames[i].bci);
                i++;
            }
            if (exp.recovers) {
                EXPECT_EQ(ids[3], frames[i].method_id);
                EXPECT_EQ(FrameType::encode(FRAME_INTERPRETED, OLDER_BCI), frames[i].bci);
                i++;
            }
            EXPECT_EQ(i, depth - 1);
            EXPECT_EQ(BCI_NATIVE_FRAME, frames[depth - 1].bci);
            EXPECT_STREQ("JVM Continuation", reinterpret_cast<const char*>(frames[depth - 1].method_id));
            EXPECT_EQ(exp.recovers, !truncated);
            EXPECT_EQ(recovered + exp.recovers, Counters::getCounter(WALKVM_FROZEN_RECOVERED));
            EXPECT_EQ(failed + !exp.recovers, Counters::getCounter(WALKVM_FROZEN_FAILED));
            EXPECT_EQ(interpreted + exp.recovers, Counters::getCounter(WALKVM_FROZEN_INTERPRETED));
            EXPECT_EQ(barrier + 1, Counters::getCounter(WALKVM_CONT_BARRIER_HIT));
            EXPECT_EQ(consumed + exp.consumed_delta, Counters::getCounter(WALKVM_ANCHOR_CONSUMED));
            EXPECT_EQ(fallback + exp.fallback_delta, Counters::getCounter(WALKVM_ANCHOR_FALLBACK));
        } else {
            EXPECT_EQ(1, depth);
            EXPECT_EQ(BCI_NATIVE_FRAME, frames[0].bci);
            EXPECT_STREQ(kNativeCallSymbol, reinterpret_cast<const char*>(frames[0].method_id));
            EXPECT_EQ(recovered, Counters::getCounter(WALKVM_FROZEN_RECOVERED));
            EXPECT_EQ(failed, Counters::getCounter(WALKVM_FROZEN_FAILED));
            EXPECT_EQ(interpreted, Counters::getCounter(WALKVM_FROZEN_INTERPRETED));
            EXPECT_EQ(barrier, Counters::getCounter(WALKVM_CONT_BARRIER_HIT));
            EXPECT_EQ(consumed, Counters::getCounter(WALKVM_ANCHOR_CONSUMED));
            EXPECT_EQ(fallback, Counters::getCounter(WALKVM_ANCHOR_FALLBACK));
        }
        int leaf = 0, middle = 0, older = 0, root = 0;
        for (int i = 0; i < depth; i++) {
            leaf += frames[i].method_id == ids[1];
            middle += frames[i].method_id == ids[2];
            older += frames[i].method_id == ids[3];
            root += frames[i].bci == BCI_NATIVE_FRAME && frames[i].method_id != nullptr &&
                    strcmp(reinterpret_cast<const char*>(frames[i].method_id), "JVM Continuation") == 0;
        }
        EXPECT_EQ(exp.has_leaf, leaf);
        EXPECT_EQ(exp.has_middle, middle);
        EXPECT_EQ(exp.recovers, older);
        EXPECT_EQ(control != NativeCallNoAnchorC, root);
        // Compaction can leave a stale frame past depth; the invariant is the
        // capacity bound, never a written slot beyond the returned depth.
        EXPECT_LE(depth, CAPACITY);
    }

};

// Drives append directly over the configured one-frame chunk: each guard must
// reject without consuming output, and chunk chains are bounded and counted.
TEST_F(OriginAnchorFrozenTest, AppendGuardsRejectUnsafeStatesAndBoundChunkChains) {
    ASSERT_EXIT({
        configure();
        if (::testing::Test::HasFailure()) _exit(1);
        VMThread* vm_thread = VMThread::current();
        ASGCT_CallFrame frames[CAPACITY]{};
        volatile int depth = 0;
        auto append = [&](const void* origin, unsigned int continuation_depth, int max_depth) {
            depth = 0;
            return FrozenStackWalker::append(vm_thread, origin, continuation_depth, frames, depth,
                                             max_depth, false);
        };
        ASSERT_TRUE(append(pc(0), 0, CAPACITY));
        ASSERT_EQ(1, depth);
        EXPECT_EQ(ids[3], frames[0].method_id);
        EXPECT_EQ(FrameType::encode(FRAME_INTERPRETED, OLDER_BCI), frames[0].bci);

        // Early rejects leave the output untouched.
        auto rejects = [&](const void* origin, unsigned int continuation_depth, int max_depth) {
            return !append(origin, continuation_depth, max_depth) && depth == 0;
        };
        EXPECT_TRUE(rejects(pc(0), 1, CAPACITY));
        EXPECT_TRUE(rejects(pc(0), 0, 0));
        EXPECT_TRUE(rejects(pc(1), 0, CAPACITY)); // stub origin
        blocks[2].blob.level = 0;                 // native wrapper / interpreter-level nmethod
        EXPECT_TRUE(rejects(pc(2), 0, CAPACITY));
        blocks[2].blob.level = 4;
        EXPECT_TRUE(append(pc(2), 0, CAPACITY));
        EXPECT_EQ(1, depth);
        EXPECT_EQ(ids[3], frames[0].method_id);
        thread.state = _thread_in_native;
        EXPECT_TRUE(rejects(pc(0), 0, CAPACITY));
        thread.state = _thread_in_Java;

        // Only a single outermost continuation is recovered.
        Continuation outer{};
        continuation.parent = &outer;
        EXPECT_TRUE(rejects(pc(0), 0, CAPACITY));
        continuation.parent = nullptr;

        // Invalid chunk geometry ends recovery before any frame is written.
        chunk->sp = chunk->size + 1;
        EXPECT_TRUE(rejects(pc(0), 0, CAPACITY));
        chunk->sp = 2;

        // A full output buffer stops before writing past max_depth.
        Chunk second{};
        second.size = 16;
        second.sp = 2;
        second.bottom = 16;
        memcpy(second.words, chunk->words, sizeof(second.words));
        chunk->parent = &second;
        EXPECT_FALSE(append(pc(0), 0, 1));
        EXPECT_EQ(1, depth);
        auto parents = Counters::getCounter(WALKVM_FROZEN_PARENT);
        EXPECT_TRUE(append(pc(0), 0, CAPACITY));
        EXPECT_EQ(2, depth);
        EXPECT_EQ(parents + 1, Counters::getCounter(WALKVM_FROZEN_PARENT));

        // A self-linked chunk cannot loop; empty chunks are bounded to 256.
        second.parent = &second;
        EXPECT_FALSE(append(pc(0), 0, CAPACITY));
        std::vector<Chunk> empty(257);
        for (size_t i = 0; i < empty.size(); i++) {
            empty[i].size = empty[i].sp = empty[i].bottom = 16;
            empty[i].parent = i + 1 < empty.size() ? &empty[i + 1] : nullptr;
        }
        second.parent = &empty[0];
        empty[254].parent = nullptr; // chunk, second and 255 empties: 257 chunks
        EXPECT_FALSE(append(pc(0), 0, CAPACITY));
        empty[253].parent = nullptr; // exactly 256 chunks
        EXPECT_TRUE(append(pc(0), 0, CAPACITY));
        EXPECT_EQ(2, depth);
        chunk->parent = nullptr;
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

TEST_F(OriginAnchorFrozenTest, OriginalPcDiscriminatesFrozenRecoveryAfterAnchorRedirect) {
    ASSERT_EXIT({
        configure();
        if (::testing::Test::HasFailure()) _exit(1);
        // One child preserves exact shared heap/anchor geometry across controls.
        controls();
        _exit(::testing::Test::HasFailure() ? 1 : 0);
    }, ::testing::ExitedWithCode(0), "");
}

} // namespace
