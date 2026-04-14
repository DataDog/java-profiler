/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_JITCODECACHE_H
#define _HOTSPOT_JITCODECACHE_H

#include <atomic>

#include "codeCache.h"
#include "spinLock.h"

// The class tracks JIT-compiled code and ranges
class JitCodeCache {
private:
    static SpinLock _stubs_lock;
    static CodeCache _runtime_stubs;
    static std::atomic<const void *> _call_stub_begin;
    static std::atomic<const void *> _call_stub_end;

public:
    static void JNICALL CompiledMethodLoad(jvmtiEnv *jvmti, jmethodID method,
                                         jint code_size, const void *code_addr,
                                         jint map_length,
                                         const jvmtiAddrLocationMap *map,
                                         const void *compile_info);
    static void JNICALL DynamicCodeGenerated(jvmtiEnv *jvmti, const char *name,
                                           const void *address, jint length);
                                           
    static inline bool isCallStub(const void *address) {
        const void* stub_end = _call_stub_end.load(std::memory_order_acquire);
        return stub_end != nullptr &&
            address >= _call_stub_begin.load(std::memory_order_relaxed) &&
            address < stub_end;    
    }
    
    static CodeBlob* findRuntimeStub(const void *address);
};

#endif // _HOTSPOT_JITCODECACHE_H
