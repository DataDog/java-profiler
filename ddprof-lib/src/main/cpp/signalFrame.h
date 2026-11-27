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
    // The SA_RESTORER trampoline the kernel returns through after a handler for
    // signo, as rt_sigaction reports it; nullptr where the decoder cannot use it.
    static const void* kernelRestorer(int signo);
    // decode() recovers at the vDSO restorer and at this one (nullptr: none).
    static void trustRestorer(const void* restorer);
    static const void* trustedRestorer();
#endif
};

#endif // _SIGNALFRAME_H
