/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "hotspot/frozenStackWalker.h"
#include "hotspot/hotspotSupport.h"
#include "hotspot/vmStructs.inline.h"
#include "stackWalker.inline.h"

namespace {

struct ChunkLayout {
    int carrier_cont;
    int cont_parent;
    int cont_tail;
    int parent;
    int size;
    int sp;
    int bottom;
    int argsize;
    int stack;
    uintptr_t oop_base;
    int oop_shift;
    bool supported;
};

ChunkLayout layout = {};

int readOffset(CodeCache* libjvm, const char* name) {
    const int* address = (const int*)libjvm->findSymbol(name);
    if (address == nullptr || *address <= 0 || *address > 4096) return -1;
    return *address;
}

uintptr_t readOop(uintptr_t object, int offset) {
    if (layout.oop_shift >= 0) {
        unsigned int narrow = __atomic_load_n((unsigned int*)(object + offset), __ATOMIC_ACQUIRE);
        return narrow == 0 ? 0 : layout.oop_base + ((uintptr_t)narrow << layout.oop_shift);
    }
    return __atomic_load_n((uintptr_t*)(object + offset), __ATOMIC_ACQUIRE);
}

// Interpreted frames in a chunk store FP, last_sp, sender_sp and locals as
// word offsets, rather than the native-stack pointers used by walkVM.
// See OpenJDK's StackChunkFrameStream::{fp,next_for_interpreter_frame}.
bool relativePointer(uintptr_t base, intptr_t words, uintptr_t low, uintptr_t high, uintptr_t& result) {
    if (words < -(intptr_t)((base - low) / sizeof(uintptr_t)) ||
            words > (intptr_t)((high - base) / sizeof(uintptr_t))) return false;
    result = base + words * sizeof(uintptr_t);
    return true;
}

bool appendCompiled(VMNMethod* nm, const void* pc, uintptr_t unextended_sp, uintptr_t low,
                    uintptr_t frame_end, ASGCT_CallFrame* frames,
                    volatile int& depth, int max_depth, bool details) {
    const void* original_pc = nm->originalPC(pc, unextended_sp, low, frame_end);
    if (original_pc == nullptr || (original_pc != pc && CodeHeap::findNMethod(original_pc) != nm)) return false;
    int level = nm->level();
    FrameTypeId type = details && level >= 1 && level <= 3 ? FRAME_C1_COMPILED : FRAME_JIT_COMPILED;
    int scope_offset = nm->findScopeOffset(original_pc);
    // A deoptimized Java frame needs a decoded scope to account for its inline callers.
    if (original_pc != pc && scope_offset <= 0) return false;
    if (scope_offset > 0) {
        ScopeDesc scope(nm);
        do {
            scope_offset = scope.decode(scope_offset);
            VMMethod* method = scope.method();
            if (method == nullptr) return false;
            jmethodID id = method->validatedId();
            if (id == JMETHODID_NOT_WALKABLE) return false;
            FrameTypeId frame_type = details && scope_offset > 0 ? FRAME_INLINED : type;
            HotspotSupport::fillJavaFrame(frames[depth++], frame_type, scope.bci(), id, method);
        } while (scope_offset > 0 && depth < max_depth);
        return scope_offset <= 0;
    }
    VMMethod* method = nm->method();
    if (method == nullptr) return false;
    jmethodID id = method->validatedId();
    if (id == JMETHODID_NOT_WALKABLE) return false;
    HotspotSupport::fillJavaFrame(frames[depth++], type, 0, id, method);
    return true;
}

} // namespace

void FrozenStackWalker::init() {
    layout.supported = false;
    if (_libjvm == nullptr || VM::java_version() < 21 || VM::java_version() > 27) return;
#if !defined(__x86_64__) && !defined(__aarch64__)
    return;
#endif
    // G1/Serial/Parallel relocate objects at safepoints. A sampled Java thread
    // cannot reach a safepoint while its signal handler is reading these oops.
    // Concurrently relocating collectors require load barriers not provided here.
    bool collector_supported = false;
    for (const char* name : {"UseG1GC", "UseSerialGC", "UseParallelGC"}) {
        VMFlag* flag = VMFlag::find(name, {VMFlag::Type::Bool});
        if (flag != nullptr && flag->get()) collector_supported = true;
    }
    TEST_LOG("Frozen stack prerequisites: collector=%d thread_oop=%d handle=%d", collector_supported,
             _thread_oop_offset, _oop_handle_offset);
    if (!collector_supported || _thread_oop_offset < 0 || _oop_handle_offset < 0) return;

    layout.carrier_cont = readOffset(_libjvm, "_ZN16java_lang_Thread20_continuation_offsetE");
    layout.cont_parent = readOffset(_libjvm, "_ZN28jdk_internal_vm_Continuation14_parent_offsetE");
    layout.cont_tail = readOffset(_libjvm, "_ZN28jdk_internal_vm_Continuation12_tail_offsetE");
    layout.parent = readOffset(_libjvm, "_ZN26jdk_internal_vm_StackChunk14_parent_offsetE");
    layout.size = readOffset(_libjvm, "_ZN26jdk_internal_vm_StackChunk12_size_offsetE");
    layout.sp = readOffset(_libjvm, "_ZN26jdk_internal_vm_StackChunk10_sp_offsetE");
    layout.bottom = readOffset(_libjvm, "_ZN26jdk_internal_vm_StackChunk14_bottom_offsetE");
    layout.argsize = readOffset(_libjvm, "_ZN26jdk_internal_vm_StackChunk15_argsize_offsetE");
    layout.stack = readOffset(_libjvm, "_ZN23InstanceStackChunkKlass16_offset_of_stackE");
    layout.oop_shift = -1;
    VMFlag* compressed = VMFlag::find("UseCompressedOops", {VMFlag::Type::Bool});
    if (compressed == nullptr) return;
    if (compressed->get()) {
        if (_narrow_oop_base_addr == nullptr || _narrow_oop_shift_addr == nullptr) return;
        layout.oop_base = *(uintptr_t*)_narrow_oop_base_addr;
        layout.oop_shift = *(int*)_narrow_oop_shift_addr;
        if (layout.oop_shift < 0 || layout.oop_shift > 16) return;
    }
    layout.supported = layout.carrier_cont > 0 && layout.cont_parent > 0 && layout.cont_tail > 0
            && layout.parent > 0 && layout.size > 0 && layout.sp > 0 && layout.stack > 0
            && layout.stack % sizeof(uintptr_t) == 0 && (layout.bottom > 0 || layout.argsize > 0);
    TEST_LOG("Frozen stack layout: supported=%d carrier=%d tail=%d parent=%d size=%d sp=%d bottom=%d argsize=%d stack=%d oop_shift=%d",
             layout.supported, layout.carrier_cont, layout.cont_tail, layout.parent, layout.size, layout.sp,
             layout.bottom, layout.argsize, layout.stack, layout.oop_shift);
}

bool FrozenStackWalker::append(VMThread* thread, const void* sampled_pc, unsigned int continuation_depth,
                              ASGCT_CallFrame* frames, volatile int& depth, int max_depth,
                              bool details) {
    if (!layout.supported || thread == nullptr || thread->state() != _thread_in_Java
            || continuation_depth >= 64 || depth >= max_depth) return false;

    // Freeze/thaw runs without a Java-to-VM transition. During doYield or its
    // runtime calls, copied frames can still be on the carrier as well as in a
    // chunk. Only an interrupted Java body has finished those stack updates.
    VMNMethod* origin = CodeHeap::findNMethod(sampled_pc);
    if (origin == nullptr || (!origin->isInterpreter() &&
            (!origin->isNMethod() || origin->level() <= 0))) return false;

    uintptr_t carrier = thread->carrierThreadOop();
    if (carrier == 0) return false;
    // Continuation.run publishes the innermost mounted continuation in the
    // carrier Thread.cont, including when the current Java thread is virtual.
    uintptr_t continuation = readOop(carrier, layout.carrier_cont);
    for (unsigned int i = 0; i < continuation_depth && continuation != 0; i++) {
        continuation = readOop(continuation, layout.cont_parent);
    }
    if (continuation == 0) return false;
    uintptr_t chunk = readOop(continuation, layout.cont_tail);
    if (chunk == 0) return false;
    int interpreted_frames = 0;
    int compiled_frames = 0;
    int parent_chunks = 0;

    // Empty chunks do not consume output depth. Bound their traversal as well
    // so corrupt parent links cannot loop indefinitely in a signal handler.
    for (int chunks = 0; chunk != 0 && chunks < 256; chunks++) {
        int size = *(int*)(chunk + layout.size);
        int sp_offset = *(int*)(chunk + layout.sp);
        int bottom_offset = layout.bottom > 0 ? *(int*)(chunk + layout.bottom)
                : size - *(int*)(chunk + layout.argsize);
        if (size <= 0 || size > (1 << 24) || sp_offset < 0 || sp_offset > size
                || bottom_offset < 0 || bottom_offset > size) return false;

        uintptr_t low = chunk + layout.stack;
        uintptr_t high = low + (uintptr_t)size * sizeof(uintptr_t);
        uintptr_t end = low + (uintptr_t)bottom_offset * sizeof(uintptr_t);
        uintptr_t sp = low + (uintptr_t)sp_offset * sizeof(uintptr_t);
        uintptr_t unextended_sp = sp;

        while (sp < end) {
            if (depth >= max_depth || sp < low + 2 * sizeof(uintptr_t) || sp > high) return false;
            const void* pc = stripPointer(((const void**)sp)[-1]);
            VMNMethod* nm = CodeHeap::findNMethod(pc);
            if (nm == nullptr) return false;
            if (nm->isInterpreter()) {
                uintptr_t fp;
                uintptr_t fp_slot = sp - 2 * sizeof(uintptr_t);
                if (!relativePointer(fp_slot, *(intptr_t*)fp_slot, low, high, fp)
                        || fp < low + 9 * sizeof(uintptr_t) || fp > high - 2 * sizeof(uintptr_t)) return false;
                VMMethod* method = ((VMMethod**)fp)[InterpreterFrame::method_offset];
                if (method == nullptr) return false;
                jmethodID id = method->validatedId();
                if (id == JMETHODID_NOT_WALKABLE) return false;
                // Method::bcp_from accepts either a bytecode pointer or an index.
                uintptr_t bcp = ((uintptr_t*)fp)[InterpreterFrame::bcp_offset()];
                uintptr_t bci = bcp <= 65535 ? bcp : bcp - (uintptr_t)method->bytecode();
                if (bci > 65535) return false;
                HotspotSupport::fillJavaFrame(frames[depth++], FRAME_INTERPRETED, bci, id, method);
                interpreted_frames++;

                uintptr_t locals;
                // In both supported architectures locals immediately precedes bcp.
                int locals_offset = InterpreterFrame::bcp_offset() + 1;
                if (!relativePointer(fp, ((intptr_t*)fp)[locals_offset], low, high, locals)) return false;
                if (locals + sizeof(uintptr_t) >= end) {
                    sp = end;
                } else {
                    uintptr_t next_sp = fp + 2 * sizeof(uintptr_t);
                    if (next_sp <= sp || !relativePointer(fp, ((intptr_t*)fp)[InterpreterFrame::sender_sp_offset],
                            low, high, unextended_sp)) return false;
                    sp = next_sp;
                }
            } else if (nm->isNMethod()) {
                int frame_size = nm->frameSize();
                if (frame_size <= 0 || frame_size > MAX_FRAME_SIZE_WORDS) return false;
                // If the previous frame was interpreted, its sender_sp is the
                // compiled caller's unextended SP (StackChunkFrameStream::next).
                uintptr_t next_sp = unextended_sp + (uintptr_t)frame_size * sizeof(uintptr_t);
                if (next_sp <= sp || next_sp > high) return false;
                if (!appendCompiled(nm, pc, unextended_sp, low, next_sp,
                                    frames, depth, max_depth, details)) return false;
                compiled_frames++;
                sp = next_sp >= end - 2 * sizeof(uintptr_t) ? end : next_sp;
                unextended_sp = sp;
            } else {
                return false;
            }
            if (sp < end) {
                const void* next_pc = stripPointer(((const void**)sp)[-1]);
                VMNMethod* next = CodeHeap::findNMethod(next_pc);
                if (next != nullptr && next->isInterpreter()) {
                    uintptr_t fp;
                    uintptr_t fp_slot = sp - 2 * sizeof(uintptr_t);
                    if (!relativePointer(fp_slot, *(intptr_t*)fp_slot, low, high, fp)
                            || fp < low + 2 * sizeof(uintptr_t) || fp > high) return false;
                    if (!relativePointer(fp, ((intptr_t*)fp)[-2], low, high, unextended_sp)) return false;
                }
            }
        }
        uintptr_t parent = readOop(chunk, layout.parent);
        if (parent == chunk) return false;
        if (parent != 0) parent_chunks++;
        chunk = parent;
    }
    Counters::increment(WALKVM_FROZEN_INTERPRETED, interpreted_frames);
    Counters::increment(WALKVM_FROZEN_COMPILED, compiled_frames);
    Counters::increment(WALKVM_FROZEN_PARENT, parent_chunks);
    return chunk == 0;
}
