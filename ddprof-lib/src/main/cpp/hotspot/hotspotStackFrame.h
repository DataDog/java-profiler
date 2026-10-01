/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_HOTSPOTSTACKFRAME_H
#define _HOTSPOT_HOTSPOTSTACKFRAME_H

#include "counters.h"
#include "stackFrame.h"
#include "hotspot/vmStructs.h"

class HotspotStackFrame : public StackFrame {
public:
    explicit HotspotStackFrame(void* ucontext): StackFrame(ucontext) {
    }

    class RegisterSnapshot : public StackFrame::RegisterSnapshot {
        private:
            // volatile: saveJavaAnchor() mutates these (called from
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

            virtual ~RegisterSnapshot() {
                restore();
            }

            void saveJavaAnchor(VMJavaFrameAnchor* anchor, const void* pc) {
                assert(anchor != nullptr);
                _anchor = anchor;
                _anchor_pc = pc;
            }

            virtual void restore() override {
                StackFrame::RegisterSnapshot::restore();
                if (_anchor != nullptr) {
                    // Safe store, cannot fault
                    bool ret = _anchor->setLastJavaPC<true /*safe store*/>(_anchor_pc);
                    assert(ret && "Failed to restore lastJavaPC");
                    if (!ret) {
                        Counters::increment(ANCHOR_RESTORE_FAILED);
                    }
                    _anchor = nullptr;
                }
        }
    };

    // UNWIND HELPER CONTRACT
    //
    // On success each of these replaces `pc` with the sender's *raw* return
    // address -- the address control returns to, exactly as it sat in the
    // stack slot or the link register. None of them applies the attribution
    // adjustment; that is the caller's decision, because only the caller
    // knows what it is about to do with the address.
    //
    // Returning the raw address on every architecture and every branch lets a
    // caller rely on one meaning without knowing the target. Some consumers
    // need the genuine return address: isContReturnBarrier,
    // isContEntryReturnPc and isEntryFrame compare it for equality against
    // known addresses, so a value already reduced by one never matches.
    // Consumers that symbolize derive the attribution address from the raw one
    // (see attributionPC in stackWalker.inline.h); applying the adjustment
    // inside a helper would make that a second subtraction.
    //
    // unwindHelperContract_ut.cpp pins this.
    //
    // The overloads below without explicit registers write the sender into the
    // real ucontext for an AsyncGetCallTrace retry, which has no WalkPc to
    // apply the attribution adjustment afterwards. On x86_64 HotSpot
    // attributes the recovered caller to the instruction the pc points at, so
    // the raw return address would select the bytecode after the call; step
    // back into the call here. aarch64 passes the raw return address to
    // AsyncGetCallTrace unchanged.
    bool unwindCompiled(VMNMethod* nm) {
        bool ok = unwindCompiled(nm, pc(), sp(), fp());
        return ok && stepIntoCallForAsgct();
    }

    bool unwindStub(instruction_t* entry, const char* name) {
        bool ok = unwindStub(entry, name, pc(), sp(), fp());
        return ok && stepIntoCallForAsgct();
    }

    bool unwindStub(instruction_t* entry, const char* name, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);

    // TODO: this function will be removed once `vm` becomes the default stack walking mode
    bool unwindCompiled(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);

    bool unwindPrologue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);
    bool unwindEpilogue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp);

    static bool unwindAtomicStub(const StackFrame& frame, const void*& pc);

private:
    bool stepIntoCallForAsgct() {
#if defined(__x86_64__)
        pc() -= 1;
#endif
        return true;
    }
};

#endif // _HOTSPOT_HOTSPOTSTACKFRAME_H

