/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __x86_64__

#include <string.h> 
#include "hotspot/hotspotStackFrame.h"

__attribute__((no_sanitize("address"))) bool HotspotStackFrame::unwindStub(instruction_t* entry, const char* name, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    instruction_t* ip = (instruction_t*)pc;
    if (ip == entry || *ip == 0xc3
        || strncmp(name, "itable", 6) == 0
        || strncmp(name, "vtable", 6) == 0
        || strcmp(name, "InlineCacheBuffer") == 0)
    {
        pc = ((uintptr_t*)sp)[0] - 1;
        sp += 8;
        return true;
    } else if (entry != NULL && ([&] { unsigned int val; memcpy(&val, entry, sizeof(val)); return val; }()) == 0xec8b4855) {
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


static inline bool isFrameComplete(instruction_t* entry, instruction_t* ip) {
    // Frame is fully constructed after rsp is decremented by the frame size.
    // Check if there is such an instruction anywhere between
    // the method entry and the current instruction pointer.
    for (ip -= 4; ip >= entry; ip--) {
        if (ip[0] == 0x48 && ip[2] == 0xec && (ip[1] & 0xfd) == 0x81) {  // sub rsp, frame_size
            return true;
        }
    }
    return false;
}

static inline bool isPollReturn(instruction_t* ip) {
    // JDK 17+
    //   pop    %rbp
    //   cmp    0x348(%r15),%rsp
    //   ja     offset_32
    //   ret
    if (ip[0] == 0x49 && ip[1] == 0x3b && (ip[2] == 0x67 || ip[2] == 0xa7) && ip[-1] == 0x5d) {
        // cmp, preceded by pop rbp
        return true;
    } else if (ip[0] == 0x0f && ip[1] == 0x87 && ip[6] == 0xc3) {
        // ja, followed by ret
        return true;
    }

    // JDK 11
    //   pop    %rbp
    //   mov    0x108(%r15),%r10
    //   test   %eax,(%r10)
    //   ret
    if (ip[0] == 0x4d && ip[1] == 0x8b && ip[2] == 0x97 && ip[-1] == 0x5d) {
        // mov, preceded by pop rbp
        return true;
    } else if (ip[0] == 0x41 && ip[1] == 0x85 && ip[2] == 0x02 && ip[3] == 0xc3) {
        // test, followed by ret
        return true;
    }

    // JDK 8
    //   pop    %rbp
    //   test   %eax,offset(%rip)
    //   ret
    if (ip[0] == 0x85 && ip[1] == 0x05 && ip[6] == 0xc3) {
        // test, followed by ret
        return true;
    }

    return false;
}

bool HotspotStackFrame::unwindCompiled(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    instruction_t* ip = (instruction_t*)pc;
    instruction_t* entry = (instruction_t*)nm->entry();
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
    } else if ((ip[0] == 0x41 && ip[1] == 0x81 && ip[2] == 0x7f && *(u32*)(ip + 4) == 1) ||
               (ip >= entry + 8 && ip[-8] == 0x41 && ip[-7] == 0x81 && ip[-6] == 0x7f && *(u32*)(ip - 4) == 1)) {
        // cmp [r15 + #off], 1
        // nmethod_entry_barrier: frame is fully constructed here
        sp += nm->frameSize() * sizeof(void*);
        fp = ((uintptr_t*)sp)[-2];
        pc = ((uintptr_t*)sp)[-1];
        return true;
    }
    return false;
}

bool HotspotStackFrame::unwindPrologue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    //  0:   mov    %eax,-0x14000(%rsp)
    //  7:   push   %rbp
    //  8:   mov    %rsp,%rbp  ; for native methods only
    // 11:   sub    $0x50,%rsp
    instruction_t* ip = (instruction_t*)pc;
    instruction_t* entry = (instruction_t*)nm->entry();
    if (ip <= entry || *ip == 0x55 || nm->frameSize() == 0) {  // push rbp
        pc = ((uintptr_t*)sp)[0] - 1;
        sp += 8;
        return true;
    } else if (ip <= entry + 15 && ip[-1] == 0x55) {  // right after push rbp
        pc = ((uintptr_t*)sp)[1] - 1;
        sp += 16;
        return true;
    } else if (ip <= entry + 31 && isFrameComplete(entry, ip)) {
        sp += nm->frameSize() * sizeof(void*);
        fp = ((uintptr_t*)sp)[-2];
        pc = ((uintptr_t*)sp)[-1];
        return true;
    }
    return false;
}

bool HotspotStackFrame::unwindEpilogue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    //  add    $0x40,%rsp
    //  pop    %rbp
    //  {poll_return}
    //  ret
    instruction_t* ip = (instruction_t*)pc;
    if (*ip == 0xc3 || isPollReturn(ip)) {  // ret
        pc = ((uintptr_t*)sp)[0] - 1;
        sp += 8;
        return true;
    } else if (*ip == 0x5d) {  // pop rbp
        fp = ((uintptr_t*)sp)[0];
        pc = ((uintptr_t*)sp)[1] - 1;
        sp += 16;
        return true;
    }
    return false;
}

bool HotspotStackFrame::unwindAtomicStub(const StackFrame& frame, const void*& pc) {
    return false;
}

#endif // __x86_64__
