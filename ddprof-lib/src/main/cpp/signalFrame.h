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
};

#endif // _SIGNALFRAME_H
