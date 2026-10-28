/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_FROZENSTACKWALKER_H
#define _HOTSPOT_FROZENSTACKWALKER_H

#include "hotspot/vmStructs.h"

// Reads frozen callers while walkVM's fault recovery is installed. No JNI,
// allocation, heap mutation, or JVM calls are permitted during the walk.
class FrozenStackWalker : private VMStructs {
public:
    // Called under VM::ready's lock. A successful layout is immutable thereafter.
    static void init();
    // Acquires the published layout without allocation or synchronization waits.
    static bool available();
    static bool append(VMThread* thread, const void* sampled_pc, unsigned int continuation_depth,
                       ASGCT_CallFrame* frames, volatile int& depth, int max_depth,
                       bool details);
};

#endif // _HOTSPOT_FROZENSTACKWALKER_H
