/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _JVMSUPPORT_INLINE_H
#define _JVMSUPPORT_INLINE_H

#include "hotspot/hotspotSupport.h"
#include "jvmSupport.h"
#include "vmEntry.h"

bool JVMSupport::canUnwind(const StackFrame& frame, const void*& pc) {
    if (VM::isHotspot()) {
        return HotspotSupport::canUnwind(frame, pc);
    } else {
        return false;
    }
}

bool JVMSupport::isJitCode(const void* pc) {
    if (VM::isHotspot()) {
        return HotspotSupport::isJitCode(pc);
    } else {
        return false;
    }
}

// Resolve method pointer to jmethodID
jmethodID JVMSupport::resolve(const void* method) {
    if (VM::isHotspot()) {
        return HotspotSupport::resolve(method);
    } else {
        assert(false && "Should not reach here");
        return nullptr;
    }
}

bool JVMSupport::isHidden(jint modifiers) {
    static constexpr jint ACC_SYNTHETIC = 0x1000;
    static constexpr jint ACC_BRIDGE = 0x0040;
    static constexpr jint JVM_ACC_HIDDEN = 0x800;
    static constexpr jint hidden_mask = (ACC_SYNTHETIC | ACC_BRIDGE | JVM_ACC_HIDDEN);
    return modifiers != 0 && // JVMTI GetClassModifiers returns 0 for ordinary package-private classes
           ((modifiers & hidden_mask) != 0);
}

#endif // _JVMSUPPORT_INLINE_H
