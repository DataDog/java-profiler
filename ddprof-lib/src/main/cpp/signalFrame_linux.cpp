/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__

#include "signalFrame.h"

#ifdef __aarch64__
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <ucontext.h>
#include "arch.h"
#include "codeCache.h"
#include "safeAccess.h"
#include "stackWalker.h"
#include "vmEntry.h"
#endif

SignalFrame::Result SignalFrame::decode(const void* pc, uintptr_t sp, uintptr_t bottom,
                                        const CodeCache* library, SignalFrame& result) {
#ifdef __aarch64__
    bool vdso = library != nullptr && strcmp(library->name(), "[vdso]") == 0;
    // Unknown code can be unmapped. Only HotSpot/OpenJ9 install our safefetch
    // recovery handlers; other VMs retain their ordinary CFI/FP fallback.
    if (!vdso && !VM::isHotspot() && !VM::isOpenJ9()) return Result::NOT_SIGNAL;

    // Linux omits CFI for __kernel_rt_sigreturn. Match its exact
    // mov w8/x8, #139; svc #0 pair before interpreting the signal stack.
    auto* ip = const_cast<uint32_t*>(static_cast<const uint32_t*>(pc));
    uint32_t instruction = SafeAccess::safeFetch32(reinterpret_cast<int*>(ip), 0);
    bool trampoline = (instruction & 0x7fffffffU) == 0x52801168U &&
                      SafeAccess::safeFetch32(reinterpret_cast<int*>(ip + 1), 0) == 0xd4000001U;
    trampoline |= instruction == 0xd4000001U &&
                  (SafeAccess::safeFetch32(reinterpret_cast<int*>(ip - 1), 0) & 0x7fffffffU) == 0x52801168U;
    if (!trampoline) return Result::NOT_SIGNAL;
    // SA_RESTORER trampolines (musl's __restore_rt, user code) get the same
    // rt_sigframe, but only the vDSO pair proves SP addresses one. Others
    // truncate rather than let their FP chain fabricate callers.
    if (!vdso) return Result::INVALID;

    // Linux arm64 rt_sigframe contains siginfo_t followed by ucontext_t.
    // Use safefetch for saved registers so the helper needs no sanitizer exemption.
    constexpr size_t required = sizeof(siginfo_t) + offsetof(ucontext_t, uc_mcontext.pc) + sizeof(uint64_t);
    if ((sp & 15) != 0 || sp >= bottom || bottom - sp < required) return Result::INVALID;
    auto* context = reinterpret_cast<ucontext_t*>(sp + sizeof(siginfo_t));
    uintptr_t interrupted_sp = SafeAccess::safeFetch64(reinterpret_cast<int64_t*>(&context->uc_mcontext.sp), 0);
    uintptr_t interrupted_fp = SafeAccess::safeFetch64(reinterpret_cast<int64_t*>(&context->uc_mcontext.regs[29]), 0);
    const void* interrupted_pc = stripPointer(reinterpret_cast<const void*>(
        SafeAccess::safeFetch64(reinterpret_cast<int64_t*>(&context->uc_mcontext.pc), 0)));
    if (interrupted_sp <= sp || interrupted_sp >= bottom || (interrupted_sp & 15) != 0 ||
        StackWalkValidation::inDeadZone(interrupted_pc) || (reinterpret_cast<uintptr_t>(interrupted_pc) & 3) != 0) {
        return Result::INVALID;
    }
    result.context = context;
    result.pc = interrupted_pc;
    result.sp = interrupted_sp;
    result.fp = interrupted_fp;
    return Result::RECOVERED;
#else
    return Result::NOT_SIGNAL;
#endif
}

#endif // __linux__
