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


#endif // _JVMSUPPORT_INLINE_H
