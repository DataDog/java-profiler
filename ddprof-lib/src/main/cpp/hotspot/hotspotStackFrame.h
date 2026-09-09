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

    class RegisterSnapshot : public StackFrame::RegisterSnapshot {
        private:
            VMJavaFrameAnchor* _anchor;
            const void*        _anchor_pc;
        public:
            explicit RegisterSnapshot(void* ucontext) : StackFrame::RegisterSnapshot(ucontext),
                _anchor(nullptr), _anchor_pc(nullptr) {
            }

            void storeJavaAnchor(VMJavaFrameAnchor* anchor, const void* pc) {
                assert(anchor != nullptr);
                _anchor = anchor;
                _anchor_pc = pc;
            }

            void restore() {
                StackFrame::RegisterSnapshot::restore();
                if (_anchor != nullptr) {
                    _anchor->setLastJavaPC(_anchor_pc);
                    _anchor = nullptr;
                }
        }
    };

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

    static bool unwindAtomicStub(const StackFrame& frame, const void*& pc);
};

#endif // _HOTSPOT_HOTSPOTSTACKFRAME_H

