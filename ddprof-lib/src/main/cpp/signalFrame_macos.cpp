/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __APPLE__

#include "signalFrame.h"

SignalFrame::Result SignalFrame::decode(const void* pc, uintptr_t sp, uintptr_t bottom,
                                        const CodeCache* library, SignalFrame& result) {
    return Result::NOT_SIGNAL;
}

#endif // __APPLE__
