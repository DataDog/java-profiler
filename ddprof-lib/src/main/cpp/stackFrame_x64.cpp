/*
 * Copyright 2017 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef __x86_64__

#include <errno.h>
#include <string.h>
#include <sys/syscall.h>
#include "stackFrame.h"


#ifdef __APPLE__
#  define REG(l, m)  _ucontext->uc_mcontext->__ss.__##m
#else
#  define REG(l, m)  _ucontext->uc_mcontext.gregs[REG_##l]
#endif


uintptr_t& StackFrame::pc() {
    return (uintptr_t&)REG(RIP, rip);
}

uintptr_t& StackFrame::sp() {
    return (uintptr_t&)REG(RSP, rsp);
}

uintptr_t& StackFrame::fp() {
    return (uintptr_t&)REG(RBP, rbp);
}

uintptr_t& StackFrame::retval() {
    return (uintptr_t&)REG(RAX, rax);
}

uintptr_t StackFrame::link() {
    // No link register on x86
    return 0;
}

uintptr_t StackFrame::arg0() {
    return (uintptr_t)REG(RDI, rdi);
}

uintptr_t StackFrame::arg1() {
    return (uintptr_t)REG(RSI, rsi);
}

uintptr_t StackFrame::arg2() {
    return (uintptr_t)REG(RDX, rdx);
}

uintptr_t StackFrame::arg3() {
    return (uintptr_t)REG(RCX, rcx);
}

uintptr_t StackFrame::jarg0() {
    return arg1();
}

uintptr_t StackFrame::method() {
    return (uintptr_t)REG(RBX, rbx);
}

uintptr_t StackFrame::senderSP() {
    return (uintptr_t)REG(R13, r13);
}

void StackFrame::ret() {
    pc() = stackAt(0);
    sp() += 8;
}


bool StackFrame::unwindStub(instruction_t* entry, const char* name, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    instruction_t* ip = (instruction_t*)pc;
    if (ip == entry || *ip == 0xc3
        || strncmp(name, "itable", 6) == 0
        || strncmp(name, "vtable", 6) == 0
        || strcmp(name, "InlineCacheBuffer") == 0)
    {
        pc = ((uintptr_t*)sp)[0] - 1;
        sp += 8;
        return true;
    } else if (entry != NULL && *(unsigned int*)entry == 0xec8b4855) {
        // The stub begins with
        //   push rbp
        //   mov  rbp, rsp
        if (ip == entry + 1) {
            pc = ((uintptr_t*)sp)[1] - 1;
            sp += 16;
            return true;
        } else if (withinCurrentStack(fp)) {
            sp = fp + 16;
            fp = ((uintptr_t*)sp)[-2];
            pc = ((uintptr_t*)sp)[-1] - 1;
            return true;
        }
    }
    return false;
}

bool StackFrame::unwindCompiled(instruction_t* entry, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    instruction_t* ip = (instruction_t*)pc;
    if (ip <= entry
        || *ip == 0xc3                                                          // ret
        || *ip == 0x55                                                          // push rbp
        || ip[-1] == 0x5d                                                       // after pop rbp
        || (ip[0] == 0x41 && ip[1] == 0x85 && ip[2] == 0x02 && ip[3] == 0xc3))  // poll return
    {
        // Subtract 1 for PC to point to the call instruction,
        // otherwise it may be attributed to a wrong bytecode
        pc = ((uintptr_t*)sp)[0] - 1;
        sp += 8;
        return true;
    } else if (*ip == 0x5d) {
        // pop rbp
        fp = ((uintptr_t*)sp)[0];
        pc = ((uintptr_t*)sp)[1] - 1;
        sp += 16;
        return true;
    } else if (ip <= entry + 15 && ((uintptr_t)ip & 0xfff) && ip[-1] == 0x55) {
        // push rbp
        pc = ((uintptr_t*)sp)[1] - 1;
        sp += 16;
        return true;
    } else if (ip <= entry + 7 && ip[0] == 0x48 && ip[1] == 0x89 && ip[2] == 0x6c && ip[3] == 0x24) {
        // mov [rsp + #off], rbp
        sp += ip[4] + 16;
        pc = ((uintptr_t*)sp)[-1] - 1;
        return true;
    }
    return false;
}

bool StackFrame::checkInterruptedSyscall() {
#ifdef __APPLE__
    // We are not interested in syscalls that do not check error code, e.g. semaphore_wait_trap
    if (*(instruction_t*)pc() == 0xc3) {
        return true;
    }
    // If CF is set, the error code is in low byte of eax,
    // some other syscalls (ulock_wait) do not set CF when interrupted
    if (REG(EFL, rflags) & 1) {
        return (retval() & 0xff) == EINTR || (retval() & 0xff) == ETIMEDOUT;
    } else {
        return retval() == (uintptr_t)-EINTR; 
    }
#else
    if (retval() == (uintptr_t)-EINTR) {
        // Workaround for JDK-8237858: restart the interrupted poll() manually.
        // Check if the previous instruction is mov eax, SYS_poll with infinite timeout or
        // mov eax, SYS_ppoll with any timeout (ppoll adjusts timeout automatically)
        uintptr_t pc = this->pc();
        if ((pc & 0xfff) >= 7 && *(instruction_t*)(pc - 7) == 0xb8) {
            int nr = *(int*)(pc - 6);
            if (nr == SYS_ppoll
                || (nr == SYS_poll && (int)REG(RDX, rdx) == -1)
                || (nr == SYS_epoll_wait && (int)REG(R10, r10) == -1)
                || (nr == SYS_epoll_pwait && (int)REG(R10, r10) == -1)) {
                this->pc() = pc - 7;
            }
        }
        return true;
    }
    return false;
#endif
}

bool StackFrame::isSyscall(instruction_t* pc) {
    return pc[0] == 0x0f && pc[1] == 0x05;
}

#endif // __x86_64__
