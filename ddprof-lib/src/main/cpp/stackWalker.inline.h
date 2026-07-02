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

#endif // _STACKWALKER_INLINE_H
