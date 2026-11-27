/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SIGNALFRAME_H
#define _SIGNALFRAME_H

#include <stdint.h>

class CodeCache;

struct SignalFrame {
    enum class Result { NOT_SIGNAL, INVALID, RECOVERED };

    void* context;
    const void* pc;
    uintptr_t sp;
    uintptr_t fp;

    // Async-signal-safe ABI fallback for frames without signal CFI.
    // Only RECOVERED populates the output; INVALID identifies an unusable restorer.
    // Unsupported platforms return NOT_SIGNAL without probing code or stack memory.
    static Result decode(const void* pc, uintptr_t sp, uintptr_t bottom,
                         const CodeCache* library, SignalFrame& result);

#ifdef __linux__
    // The kernel's struct sigaction; musl's libc struct has no sa_restorer field.
    struct KernelSigaction {
        void* handler;
        unsigned long flags;
        void* restorer;
        uint64_t mask;
    };
    static constexpr unsigned long KERNEL_SA_RESTORER = 0x04000000UL;

    // The SA_RESTORER trampoline the kernel returns through after signo's handler, if that
    // handler is still `handler`; nullptr otherwise or where the decoder cannot use it.
    static const void* kernelRestorer(int signo, const void* handler);
    // decode() recovers at the vDSO restorer and at this one (nullptr: none). One slot
    // suffices: every handler installed through the same libc shares its restorer.
    static void trustRestorer(const void* restorer);
    static const void* trustedRestorer();
#endif
};

#endif // _SIGNALFRAME_H
