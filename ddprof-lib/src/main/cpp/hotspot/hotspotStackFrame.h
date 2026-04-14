/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSTACKFRAME_H
#define _HOTSPOT_HOTSPOTSTACKFRAME_H

#include "stackFrame.h"
#include "hotspot/vmStructs.h"

class HotspotStackFrame : public StackFrame {
public:
    explicit HotspotStackFrame(void* ucontext): StackFrame(ucontext) {
    }

    bool unwindCompiled(VMNMethod* nm) {
        return unwindCompiled(nm, pc(), sp(), fp());
    }

    bool unwindStub(instruction_t* entry, const char* name) {
        return unwindStub(entry, name, pc(), sp(), fp());
    }

    bool unwindStub(instruction_t* entry, const char* name, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);

    // TODO: this function will be removed once `vm` becomes the default stack walking mode
    bool unwindCompiled(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);

    bool unwindPrologue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);
    bool unwindEpilogue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);
};

#endif // _HOTSPOT_HOTSPOTSTACKFRAME_H

