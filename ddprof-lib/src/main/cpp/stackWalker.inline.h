/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STACKWALKER_INLINE_H
#define _STACKWALKER_INLINE_H

#include "frame.h"
#include "stackWalker.h"
#include "safeAccess.h"

#include <ucontext.h>

inline constexpr uintptr_t MAX_WALK_SIZE = 0x100000;
inline constexpr intptr_t MAX_FRAME_SIZE_WORDS = StackWalkValidation::MAX_FRAME_SIZE / sizeof(void*);  // 0x8000 = 32768 words

// AArch64: on Linux, frame link is stored at the top of the frame,
// while on macOS, frame link is at the bottom.
inline uintptr_t defaultSenderSP(uintptr_t sp, uintptr_t fp) {
#ifdef __APPLE__
    return sp + 2 * sizeof(void*);
#else
    return fp;
#endif
}

inline void fillFrame(ASGCT_CallFrame& frame, ASGCT_CallFrameType type, const char* name) {
    frame.bci = type;
    frame.method_id = (jmethodID)name;
}

// Overload for RemoteFrameInfo* (passed as void* to support both char* and RemoteFrameInfo*)
inline void fillFrame(ASGCT_CallFrame& frame, int bci, void* method_id_ptr) {
    frame.bci = bci;
    frame.method_id = (jmethodID)method_id_ptr;
}

inline void fillFrame(ASGCT_CallFrame& frame, ASGCT_CallFrameType type, u32 class_id) {
    frame.bci = type;
    frame.method_id = (jmethodID)(uintptr_t)class_id;
}

inline void fillFrame(ASGCT_CallFrame& frame, FrameTypeId type, int bci, jmethodID method) {
    frame.bci = FrameType::encode(type, bci);
    frame.method_id = method;
}

// A return address is the address of the instruction *after* the call, so it
// does not reliably fall inside the calling function or the DWARF/SFrame row
// that describes the call site. Any byte inside the call instruction resolves
// correctly on both variable-width (x86_64) and fixed-width ISAs, so callers
// that consume `pc` for symbolication or FDE lookup must use this adjusted
// value; callers that need the exact resume/executed address (JIT handoff,
// no-progress guards, pc arithmetic) must keep using the raw walking pc.
//
// Only walkFP/walkDwarf produce adjusted addresses. walkVM/walkKernel still
// hand out raw addresses and are therefore still subject to the boundary
// misattribution this function fixes: CodeCache::binarySearch's fallback
// rescues only the padding-gap and zero-size-symbol cases, not zero-gap
// adjacency (see BinarySearchPicksNextSymbolAtZeroGapBoundary).
inline const void* attributionPC(const void* pc, bool pc_is_return_address) {
    return pc_is_return_address ? (const void*)((const char*)pc - 1) : pc;
}

// The walking pc and "was it loaded from a return-address slot?" are one
// value: every consumer needs both to decide between the raw and the
// attribution address. Held as two independent locals, a newly added
// `pc = ...` inherits whatever the flag happened to be and silently
// reintroduces the boundary misattribution, so the pair is only reachable
// through the named mutators below -- adding a new pc source is a
// compile-time decision, not a silent default.
class WalkPc {
  public:
    WalkPc() : _pc(nullptr), _is_return_address(false) {}

    // The exact resume/executed address: pc arithmetic, no-progress guards,
    // dead-zone checks, JIT detection and the handoff to the JVM.
    const void* raw() const { return _pc; }

    // The address to symbolize with or to select an unwind row with.
    const void* attribution() const { return attributionPC(_pc, _is_return_address); }

    bool isReturnAddress() const { return _is_return_address; }

    // A pc read out of a return-address slot, a link register, or a
    // DW_CFA_val_expression on the return-address register column.
    void setReturnAddress(const void* pc) {
        _pc = pc;
        _is_return_address = true;
    }

    // A pc that is itself the interrupted/executing address, e.g. a
    // ucontext's pc register.
    void setExactAddress(const void* pc) {
        _pc = pc;
        _is_return_address = false;
    }

    // The leaf seed taken from callerPC(), whose nature is per-arch: a real
    // return address on most ISAs, a leaf-seed instruction address on
    // aarch64 (see CALLER_PC_IS_RETURN_ADDRESS in arch.h).
    void setSeed(const void* pc, bool is_return_address) {
        _pc = pc;
        _is_return_address = is_return_address;
    }

  private:
    const void* _pc;
    bool _is_return_address;
};

#endif // _STACKWALKER_INLINE_H
