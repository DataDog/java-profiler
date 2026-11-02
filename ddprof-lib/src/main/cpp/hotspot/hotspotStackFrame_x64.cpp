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
    instruction_t* code = (instruction_t*)nm->code();
    if (words < 4 || words > 256 || (words & 1) != 0) return -1;
    if (!nm->contains(pc) || !nm->contains(entry) || entry < code || ip < code) return -1;
    if (ip < entry) {
        // The interpreter-only adapter has its own frame setup before the
        // verified compiled entry. Keep the search within that earlier code.
        instruction_t* end = entry < code + 256 ? entry : code + 256;
        instruction_t* save = code;
        for (; save + 7 < end; save++) {
            if (save[0] == 0x55 && save[1] == 0x48 &&
                ((save[2] == 0x8b && save[3] == 0xec) || (save[2] == 0x89 && save[3] == 0xe5)) &&
                save[4] == 0x48 && save[6] == 0xec &&
                (save[5] == 0x83 || (save[5] == 0x81 && save + 10 < end))) break;
        }
        if (save + 7 >= end || ip < save) return -1;
        entry = save;
    }

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

    // gen_continuation_enter emits its exception section after the normal
    // add rsp; pop rbp; ret. That section restores FP, spills the exception
    // around a resolver call, then moves the return PC into RDX. Its register
    // sources cannot be represented by this saved-FP/stack-PC layout helper.
    // Reject it instead of applying the complete frame size to its changing SP.
    size_t completed = ip - entry;
    if (completed > 1024) return -1;
    unsigned int storage = (words - 2) * sizeof(uintptr_t);
    for (size_t offset = 7; offset + 6 <= completed; offset++) {
        instruction_t* scan = entry + offset;
        // Cleanup first restores JavaThread::_cont_entry from RBX. Include
        // that store so an add/pop/ret byte pattern inside movabs is ignored.
        if (scan[-7] != 0x49 || scan[-6] != 0x89 || scan[-5] != 0x9f || scan[0] != 0x48 || scan[2] != 0xc4) continue;
        if (storage < 128 && scan[1] == 0x83 && scan[3] == storage && scan[4] == 0x5d && scan[5] == 0xc3) return -1;
        if (offset + 9 <= completed && scan[1] == 0x81 && scan[3] == (storage & 0xff) &&
                scan[4] == (storage >> 8) && scan[5] == 0 && scan[6] == 0 && scan[7] == 0x5d && scan[8] == 0xc3) return -1;
    }

    if (*ip == 0x5d) return 2;           // pop FP: storage already deallocated
    if (*ip == 0xc3) return 1;           // ret: FP already restored
    return words;
}

// Bounded instruction shapes used only by gen_continuation_enter's VM-leaf
// resolver. Do not turn these into general native unwind heuristics.
static int continuationCallSize(const unsigned char* p, const unsigned char* end) {
    if (end - p >= 5 && p[0] == 0xe8) return 5; // call rel32
    if (end - p >= 12 && p[0] == 0x48 && p[1] == 0xb8 &&
            p[10] == 0xff && p[11] == 0xd0) return 12; // movabs rax; call rax
    return 0;
}

static int continuationBranchSize(const unsigned char* p, const unsigned char* end,
                                  bool conditional, const unsigned char*& target) {
    int size = 0;
    int32_t displacement;
    if (end - p >= 2 && p[0] == (conditional ? 0x74 : 0xeb)) {
        size = 2;
        displacement = (int8_t)p[1];
    } else if (conditional && end - p >= 6 && p[0] == 0x0f && p[1] == 0x84) {
        size = 6;
        memcpy(&displacement, p + 2, sizeof(displacement));
    } else if (!conditional && end - p >= 5 && p[0] == 0xe9) {
        size = 5;
        memcpy(&displacement, p + 1, sizeof(displacement));
    }
    if (size != 0) target = (const unsigned char*)((uintptr_t)p + size + displacement);
    return size;
}

bool HotspotStackFrame::continuationEntryExceptionLayout(VMNMethod* nm, const void* pc,
        bool return_address, ContinuationEntryLayout& layout) {
    int words = nm->frameSize();
    const unsigned char* entry = (const unsigned char*)nm->entry();
    if (words < 4 || words > 256 || (words & 1) != 0 || !nm->contains(entry) || !nm->contains(pc)) return false;
    size_t available = (uintptr_t)nm + nm->size() - (uintptr_t)entry;
    if (available > 1024) available = 1024;
    const unsigned char* end = entry + available;
    const unsigned char* ip = (const unsigned char*)pc;
    if (ip < entry || ip >= end) return false;

    // Locate the same validated normal epilogue used by the scalar helper.
    // The immediately following section is the separate exception cleanup.
    const unsigned char* normal_add = nullptr;
    const unsigned char* p = nullptr;
    int add_size = 0;
    unsigned int storage = (words - 2) * sizeof(uintptr_t);
    for (size_t offset = 7; offset < available; offset++) {
        const unsigned char* scan = entry + offset;
        if (end - scan < 6 || scan[-7] != 0x49 || scan[-6] != 0x89 || scan[-5] != 0x9f ||
                scan[0] != 0x48 || scan[2] != 0xc4) continue;
        if (storage < 128 && scan[1] == 0x83 && scan[3] == storage && scan[4] == 0x5d && scan[5] == 0xc3) add_size = 4;
        else if (end - scan >= 9 && scan[1] == 0x81 && scan[3] == (storage & 0xff) &&
                scan[4] == (storage >> 8) && scan[5] == 0 && scan[6] == 0 && scan[7] == 0x5d && scan[8] == 0xc3) add_size = 7;
        if (add_size != 0) {
            normal_add = scan;
            p = scan + add_size + 2;
            break;
        }
    }
    if (p == nullptr) return false;

    bool found = false;
    auto phase = [&](const unsigned char* at, int remaining, bool saved_fp, bool call_return = false) {
        if (ip == at && (!return_address || call_return)) {
            layout = {remaining, saved_fp};
            found = true;
        }
    };
    // Product HotSpot cleanup consists only of SP-relative loads and stores
    // to JavaThread: two pairs now, three on JDKs with held-monitor counts.
    // Unknown/debug-build instructions are rejected rather than assumed SP-neutral.
    for (int nops = 0; nops < 8 && p < end && *p == 0x90; nops++, p++) phase(p, words, true);
    int pairs = 0;
    const unsigned char* last_store = nullptr;
    for (; pairs < 3 && end - p >= 12; pairs++) {
        int load_size = p[0] == 0x48 && p[1] == 0x8b && p[2] == 0x5c && p[3] == 0x24 ? 5 :
                end - p >= 15 && p[0] == 0x48 && p[1] == 0x8b && p[2] == 0x9c && p[3] == 0x24 ? 8 : 0;
        if (load_size == 0) break;
        phase(p, words, true);
        p += load_size;
        if (p[0] != 0x49 || p[1] != 0x89 || p[2] != 0x9f) return false;
        phase(p, words, true);
        last_store = p;
        p += 7;
    }
    if (pairs < 2 || last_store == nullptr || memcmp(last_store, normal_add - 7, 7) != 0 ||
            end - p < add_size + 1 || memcmp(p, normal_add, add_size) != 0 || p[add_size] != 0x5d) return false;
    phase(p, words, true); // before releasing entry storage
    p += add_size;
    phase(p++, 2, true);   // before pop rbp

    const unsigned char args[] = {0x49, 0x8b, 0xff, 0x48, 0x8b, 0x34, 0x24, 0x50};
    if (end - p < (int)sizeof(args) || memcmp(p, args, sizeof(args)) != 0) return false;
    phase(p, 1, false);
    phase(p + 3, 1, false);
    phase(p + 7, 1, false); // before push exception
    p += sizeof(args);
    const unsigned char test[] = {0xf7, 0xc4, 0x0f, 0, 0, 0}; // test esp, 15
    const unsigned char byte_test[] = {0x40, 0xf6, 0xc4, 0x0f}; // optimized test spl, 15; REX is required
    int test_size = end - p >= (int)sizeof(test) && memcmp(p, test, sizeof(test)) == 0 ? sizeof(test) :
            end - p >= (int)sizeof(byte_test) && memcmp(p, byte_test, sizeof(byte_test)) == 0 ? sizeof(byte_test) : 0;
    if (test_size == 0) return false;
    phase(p, 2, false); // the overwritten FP slot now holds the exception oop
    p += test_size;
    const unsigned char* direct_call;
    int branch_size = continuationBranchSize(p, end, true, direct_call);
    if (branch_size == 0) return false;
    phase(p, 2, false);
    p += branch_size;
    const unsigned char sub[] = {0x48, 0x83, 0xec, 0x08};
    if (end - p < 4 || memcmp(p, sub, 4) != 0) return false;
    phase(p, 2, false);
    p += 4;
    int call_size = continuationCallSize(p, end);
    if (call_size == 0) return false;
    phase(p, 3, false);
    if (call_size == 12) phase(p + 10, 3, false); // after loading the far-call address
    p += call_size;
    phase(p, 3, false, true); // return from the padding branch's resolver
    const unsigned char add[] = {0x48, 0x83, 0xc4, 0x08};
    if (end - p < 4 || memcmp(p, add, 4) != 0) return false;
    p += 4;
    const unsigned char* tail;
    branch_size = continuationBranchSize(p, end, false, tail);
    if (branch_size == 0) return false;
    phase(p, 2, false);
    p += branch_size;
    if (p != direct_call) return false;
    call_size = continuationCallSize(p, end);
    if (call_size == 0) return false;
    phase(p, 2, false);
    if (call_size == 12) phase(p + 10, 2, false);
    p += call_size;
    if (p != tail) return false;
    const unsigned char finish[] = {0x48, 0x8b, 0xd8, 0x58, 0x5a, 0xff, 0xe3};
    if (end - p < (int)sizeof(finish) || memcmp(p, finish, sizeof(finish)) != 0) return false;
    phase(p, 2, false, true); // return from the aligned resolver
    phase(p + 3, 2, false);  // before pop exception
    phase(p + 4, 1, false);  // before pop return PC
    phase(p + 5, 0, false);  // return PC is now in interrupted RDX
    return found;
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
