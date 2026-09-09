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
            // volatile: storeJavaAnchor() mutates these (called from
            // getJavaTraceAsync(), reached through
            // HotspotSupport::withUcontextFaultRecovery()'s work(ctx_snapshot))
            // between that function's sigsetjmp() and a possible siglongjmp()
            // out of a recovered fault; restore() then reads them back at the
            // landing pad to decide whether/how to restore the JavaThread
            // anchor. Per the setjmp/longjmp rules (C11 7.13.2.1p3, inherited
            // by C++), a non-volatile automatic local modified in that window
            // has an indeterminate value after longjmp -- the same hazard
            // ResolvedNames::_long_method_name (hotspotSupport.cpp) guards
            // against for an analogous fault-recovery readback.
            VMJavaFrameAnchor* volatile _anchor;
            const void* volatile        _anchor_pc;
        public:
            explicit RegisterSnapshot(void* ucontext) : StackFrame::RegisterSnapshot(ucontext),
                _anchor(nullptr), _anchor_pc(nullptr) {
            }

            void storeJavaAnchor(VMJavaFrameAnchor* anchor, const void* pc) {
                assert(anchor != nullptr);
                _anchor = anchor;
                _anchor_pc = pc;
            }

            virtual void restore() {
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

