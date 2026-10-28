/*
 * Copyright The async-profiler authors
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __aarch64__

#include <errno.h>
#include <string.h>
#include <sys/syscall.h>
#include "stackFrame.h"
#include "safeAccess.h"
#include "counters.h"


#ifdef __APPLE__
#  define REG(l, m)  _ucontext->uc_mcontext->__ss.__##m
#else
#  define REG(l, m)  _ucontext->uc_mcontext.l
#endif


uintptr_t& StackFrame::pc() {
    return (uintptr_t&)REG(pc, pc);
}

uintptr_t& StackFrame::sp() {
    return (uintptr_t&)REG(sp, sp);
}

uintptr_t& StackFrame::fp() {
    return (uintptr_t&)REG(regs[29], fp);
}

uintptr_t& StackFrame::retval() {
    return (uintptr_t&)REG(regs[0], x[0]);
}

uintptr_t StackFrame::link() const {
    return (uintptr_t)REG(regs[30], lr);
}

uintptr_t StackFrame::arg0() const {
    return (uintptr_t)REG(regs[0], x[0]);
}

uintptr_t StackFrame::arg1() const {
    return (uintptr_t)REG(regs[1], x[1]);
}

uintptr_t StackFrame::arg2() const {
    return (uintptr_t)REG(regs[2], x[2]);
}

uintptr_t StackFrame::arg3() const {
    return (uintptr_t)REG(regs[3], x[3]);
}

uintptr_t StackFrame::jarg0() const {
    return arg1();
}

uintptr_t StackFrame::method() const {
    return (uintptr_t)REG(regs[12], x[12]);
}

uintptr_t StackFrame::senderSP() const {
    return (uintptr_t)REG(regs[19], x[19]);
}

void StackFrame::ret() {
    pc() = link();
}

NOSANALIGSANITIZE void StackFrame::adjustSP(const void* entry, const void* pc, uintptr_t& sp) {
    instruction_t* ip = (instruction_t*)pc;
    if (ip > entry && (ip[-1] == 0xa9bf27ff || (ip - (const instruction_t*)entry >= 2 && ip[-1] == 0xd63f0100 && ip[-2] == 0xa9bf27ff))) {
        // When calling a leaf native from Java, JVM puts a dummy frame link onto the stack,
        // thus breaking the invariant: sender_sp == current_sp + frame_size.
        // Since JDK 21, there are more instructions between `blr` and `add`,
        // ignore them now for the sake of simplicity.
        //   stp  xzr, x9, [sp, #-16]!
        //   blr  x8
        //   ...
        //   add  sp, sp, #0x10
        sp += 16;
        return;
    }

    if (ip <= entry) return;
    bool direct_call = (ip[-1] & 0xfc000000) == 0x94000000; // bl
    bool indirect_call = (ip[-1] & 0xfffffc1f) == 0xd63f0000; // blr
    bool pops_pair = (ip[0] & 0xffff83e0) == 0xa8c103e0; // ldp ..., [sp], #16
    bool pops_single = (ip[0] & 0xffffffe0) == 0xf84107e0; // ldr ..., [sp], #16
    if (!(direct_call || indirect_call) || !(pops_pair || pops_single)) return;

    // C1 subtype-check callers push two arguments before far_call and pop
    // them at its return PC. call_VM_leaf_base similarly saves x8/x12.
    // These words are outside the nmethod frame size. Require the matching
    // push, allowing only far_call's address setup between it and the call.
    unsigned int call_reg = (ip[-1] >> 5) & 31;
    for (int back = 2; back <= 5 && ip - (const instruction_t*)entry >= back; back++) {
        instruction_t insn = ip[-back];
        if ((insn & 0xffff83e0) == 0xa9bf03e0) { // stp ..., [sp, #-16]!
            // FP/LR saves are part of the fixed frame, not outgoing arguments.
            if ((insn & 31) >= 29 || ((insn >> 10) & 31) >= 29) return;
            sp += 16;
            // C1 object-arraycopy saves its arrays before passing subtype-check
            // arguments. Both CBNZ paths pop the same outer pair after the
            // immediate argument pop, so another 16 bytes are still live.
            if (pops_pair && ((insn ^ ip[0]) & 0x7c1f) == 0) {
                instruction_t branch = SafeAccess::safeFetch32((int*)(ip + 1), 0);
                int offset = (int32_t)(branch << 8) >> 11;
                if ((branch & 0x7f00001f) == (0x35000000 | (ip[0] & 31)) && offset >= 4 && offset <= 1024 &&
                    SafeAccess::safeFetch32((int*)(ip + 2), 0) == (int32_t)ip[0] &&
                    SafeAccess::safeFetch32((int*)((uintptr_t)(ip + 1) + offset), 0) == (int32_t)ip[0]) {
                    sp += 16;
                }
            }
            return;
        }
        bool address_setup = (insn & 0xff80001f) == (0xd2800000 | call_reg) // movz
                || (insn & 0xff80001f) == (0xf2800000 | call_reg) // movk
                || (insn & 0x9f00001f) == (0x90000000 | call_reg) // adrp
                || (insn & 0xffc003ff) == (0x91000000 | call_reg << 5 | call_reg); // add
        if (!indirect_call || !address_setup) return;
    }
}

bool StackFrame::skipFaultInstruction() {
    return false;
}

NOSANALIGSANITIZE bool StackFrame::checkInterruptedSyscall() {
#ifdef __APPLE__
    // We are not interested in syscalls that do not check error code, e.g. semaphore_wait_trap
    if (*(instruction_t*)pc() == 0xd65f03c0) {
        return true;
    }
    // If carry flag is set, the error code is in low byte of x0
    if (REG(pstate, cpsr) & (1 << 29)) {
        return (retval() & 0xff) == EINTR || (retval() & 0xff) == ETIMEDOUT;
    } else {
        return retval() == (uintptr_t)-EINTR;
    }
#else
    if (retval() == (uintptr_t)-EINTR) {
        // Workaround for JDK-8237858: restart the interrupted poll / epoll_wait manually
        uintptr_t nr = (uintptr_t)REG(regs[8], x[8]);
        if (nr == SYS_ppoll || (nr == SYS_epoll_pwait && (int)arg3() == -1)) {
            // Check against unreadable page for the loop below
            const uintptr_t max_distance = 24;
            if ((pc() & 0xfff) < max_distance && SafeAccess::load32((int32_t*)(pc() - max_distance)) == 0) {
                return true;
            }
            // Try to restore the original value of x0 saved in another register
            for (uintptr_t prev_pc = pc() - 4; pc() - prev_pc <= max_distance; prev_pc -= 4) {
                instruction_t insn = *(instruction_t*)prev_pc;
                unsigned int reg = (insn >> 16) & 31;
                if ((insn & 0xffe0ffff) == 0xaa0003e0 && reg >= 6) {
                    // mov x0, reg
                    REG(regs[0], x[0]) = REG(regs[reg], x[reg]);
                    pc() -= sizeof(instruction_t);
                    break;
                }
            }
        }
        return true;
    }
    return false;
#endif
}

bool StackFrame::isSyscall(instruction_t* pc) {
    // svc #0 or svc #80
    return (*pc & 0xffffefff) == 0xd4000001;
}

#endif // __aarch64__
