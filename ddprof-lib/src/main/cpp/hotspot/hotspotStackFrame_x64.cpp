/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __x86_64__

#include <string.h>
#include "hotspot/hotspotStackFrame.h"
// See the note in hotspotStackFrame_aarch64.cpp: the VMNMethod accessors need vmStructs.inline.h
// for crashProtectionActive() / cast_to() so assertion-enabled builds link.
#include "hotspot/vmStructs.inline.h"

__attribute__((no_sanitize("address"))) bool HotspotStackFrame::unwindStub(instruction_t* entry, const char* name, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp, const StubUnwindInfo* info) {
    (void)info;  // precomputed stub metadata exists only on aarch64
    instruction_t* ip = (instruction_t*)pc;
    if (ip == entry || *ip == 0xc3
        || strncmp(name, "itable", 6) == 0
        || strncmp(name, "vtable", 6) == 0
        || strcmp(name, "InlineCacheBuffer") == 0)
    {
        pc = ((uintptr_t*)sp)[0];
        sp += 8;
        return true;
    } else if (entry != NULL && ([&] { unsigned int val; memcpy(&val, entry, sizeof(val)); return val; }()) == 0xec8b4855) {
        // The stub begins with
        //   push rbp
        //   mov  rbp, rsp
        if (ip == entry + 1) {
            pc = ((uintptr_t*)sp)[1];
            sp += 16;
            return true;
        } else if (withinCurrentStack(fp)) {
            sp = fp + 16;
            fp = ((uintptr_t*)sp)[-2];
            pc = ((uintptr_t*)sp)[-1];
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
        pc = ((uintptr_t*)sp)[0];
        sp += 8;
        return true;
    } else if (*ip == 0x5d) {
        // pop rbp
        fp = ((uintptr_t*)sp)[0];
        pc = ((uintptr_t*)sp)[1];
        sp += 16;
        return true;
    } else if (ip <= entry + 15 && ((uintptr_t)ip & 0xfff) && ip[-1] == 0x55) {
        // push rbp
        pc = ((uintptr_t*)sp)[1];
        sp += 16;
        return true;
    } else if (ip <= entry + 7 && ip[0] == 0x48 && ip[1] == 0x89 && ip[2] == 0x6c && ip[3] == 0x24) {
        // mov [rsp + #off], rbp
        sp += ip[4] + 16;
        pc = ((uintptr_t*)sp)[-1];
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

int HotspotStackFrame::continuationEntryThreadOffset(const unsigned char* code, size_t size) {
    if (code == nullptr || size < 3 || code[0] != 0x49 || code[1] != 0x8b) return -1;
    // mov rsp, [r15 + offset], with no displacement, disp8 or disp32.
    if (code[2] == 0x27) return 0;
    if (code[2] == 0x67 && size >= 4) return code[3] < 0x80 ? code[3] : -1;
    if (code[2] != 0xa7 || size < 7 || code[6] >= 0x80) return -1;
    return code[3] | (code[4] << 8) | (code[5] << 16) | (code[6] << 24);
}

int HotspotStackFrame::continuationEntryFrameWords(VMNMethod* nm, const void* pc) {
    int words = nm->frameSize();
    instruction_t* ip = (instruction_t*)pc;
    instruction_t* entry = (instruction_t*)nm->entry();
    if (words < 4 || words > 256 || (words & 1) != 0 || ip < entry) return -1;

    if (!nm->isFrameCompleteAt(pc)) {
        // MacroAssembler::enter followed by continuation_enter_setup's sub SP.
        if (entry[0] != 0x55 || entry[1] != 0x48 ||
            !((entry[2] == 0x8b && entry[3] == 0xec) ||
              (entry[2] == 0x89 && entry[3] == 0xe5)) ||
            entry[4] != 0x48 || entry[6] != 0xec) return -1;
        unsigned int storage;
        int allocated;
        if (entry[5] == 0x83) {
            storage = entry[7];
            allocated = 8;
        } else if (entry[5] == 0x81) {
            storage = entry[7] | (entry[8] << 8) | (entry[9] << 16) | ((unsigned int)entry[10] << 24);
            allocated = 11;
        } else {
            return -1;
        }
        if (storage != (words - 2) * sizeof(uintptr_t)) return -1;
        if (ip == entry) return 1;       // before push FP; return PC is at SP
        if (ip == entry + 1 || ip == entry + 4) return 2;
        return ip >= entry + allocated ? words : -1;
    }

    if (*ip == 0x5d) return 2;           // pop FP: storage already deallocated
    if (*ip == 0xc3) return 1;           // ret: FP already restored
    return words;
}

bool HotspotStackFrame::unwindPrologue(VMNMethod* nm, uintptr_t& pc, uintptr_t& sp, uintptr_t& fp) {
    //  0:   mov    %eax,-0x14000(%rsp)
    //  7:   push   %rbp
    //  8:   mov    %rsp,%rbp  ; for native methods only
    // 11:   sub    $0x50,%rsp
    instruction_t* ip = (instruction_t*)pc;
    instruction_t* entry = (instruction_t*)nm->entry();
    if (ip <= entry || *ip == 0x55 || nm->frameSize() == 0) {  // push rbp
        pc = ((uintptr_t*)sp)[0];
        sp += 8;
        return true;
    } else if (ip <= entry + 15 && ip[-1] == 0x55) {  // right after push rbp
        pc = ((uintptr_t*)sp)[1];
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
        pc = ((uintptr_t*)sp)[0];
        sp += 8;
        return true;
    } else if (*ip == 0x5d) {  // pop rbp
        fp = ((uintptr_t*)sp)[0];
        pc = ((uintptr_t*)sp)[1];
        sp += 16;
        return true;
    }
    return false;
}

bool HotspotStackFrame::unwindAtomicStub(const StackFrame& frame, const void*& pc) {
    return false;
}

#endif // __x86_64__
