/*
 * Copyright The async-profiler authors
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_CLASSLOADER_H
#define _HOTSPOT_CLASSLOADER_H

#include "hotspot/vmStructs.h"

class VMClassLoader {
public:
    // Is the method belongs to a class that is loaded by bootstrap class loader
    static inline bool isLoadedByBootstrapClassLoader(const VMMethod* method);
};

#endif // _HOTSPOT_CLASSLOADER_H

