/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STACKFRAME_H
#define _STACKFRAME_H

#include <stddef.h>
#include <stdint.h>
#include <ucontext.h>
#include "arch.h"
class StackFrame {
  protected:
    ucontext_t* _ucontext;

    static bool withinCurrentStack(uintptr_t address) {
        // Check that the address is not too far from the stack pointer of current context
        void* real_sp;
        return address - (uintptr_t)&real_sp <= 0xffff;
    }

  public:
    explicit StackFrame(void* ucontext) {
        _ucontext = (ucontext_t*)ucontext;
    }

    void restore(uintptr_t saved_pc, uintptr_t saved_sp, uintptr_t saved_fp) {
        if (_ucontext != nullptr) {
            pc() = saved_pc;
            sp() = saved_sp;
            fp() = saved_fp;
        }
    }

    // Captures pc/sp/fp for a later restore() -- the null-safe save/restore
    // boilerplate needed around code that mutates the real ucontext in place
    // (e.g. HotspotSupport::getJavaTraceAsync()'s PROBE_SP loop, or
    // unwindStub()/unwindCompiled() writing pc()/sp()/fp() by reference).
    // Capturing is a no-op when ucontext is null (pc()/sp()/fp() themselves
    // are not null-safe); restore() delegates to StackFrame::restore() above,
    // which already is.
    //
    // Must be restored via an explicit restore() call, never a destructor:
    // Profiler::checkFault()'s siglongjmp bypasses destructors, so RAII alone
    // can't reach code here -- the same reason JmpCtxScope::restore() must be
    // called explicitly (see guards.h).
    class RegisterSnapshot {
      public:
        explicit RegisterSnapshot(void* ucontext) : _ucontext(ucontext) {
            if (_ucontext != nullptr) {
                StackFrame frame(_ucontext);
                _pc = frame.pc();
                _sp = frame.sp();
                _fp = frame.fp();
            }
        }

        void restore() const {
            StackFrame(_ucontext).restore(_pc, _sp, _fp);
        }

        uintptr_t pc() const { return _pc; }
        uintptr_t sp() const { return _sp; }
        uintptr_t fp() const { return _fp; }

      private:
        void* _ucontext;
        uintptr_t _pc = 0, _sp = 0, _fp = 0;
    };

    uintptr_t stackAt(int slot) {
        return ((uintptr_t*)sp())[slot];
    }

    uintptr_t& pc();
    uintptr_t& sp();
    uintptr_t& fp();

    uintptr_t& retval();
    uintptr_t link() const;
    uintptr_t arg0() const;
    uintptr_t arg1() const;
    uintptr_t arg2() const;
    uintptr_t arg3() const;
    uintptr_t jarg0() const;
    uintptr_t method() const;
    uintptr_t senderSP() const;

    void ret();

    void adjustSP(const void* entry, const void* pc, uintptr_t& sp);

    bool skipFaultInstruction();

    bool checkInterruptedSyscall();

    // Check if PC points to a syscall instruction
    static bool isSyscall(instruction_t* pc);
};

#endif // _STACKFRAME_H
