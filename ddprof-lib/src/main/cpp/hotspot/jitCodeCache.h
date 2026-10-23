/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HOTSPOT_JITCODECACHE_H
#define _HOTSPOT_JITCODECACHE_H

#include <atomic>

#include "codeCache.h"
#include "mutex.h"
#include "spinLock.h"

#include "hotspot/vmStructs.h"

#ifdef __aarch64__
// Precomputed per-stub unwind metadata derived from the generated machine code
// received through JVMTI DynamicCodeGenerated (aarch64 only; see
// hotspot/stubUnwindInfo.h).
struct StubUnwindInfo;

// Registry entry: one per registered runtime stub, inserted in start-address
// order under the exclusive _stubs_lock and never removed (CodeCache never
// removes blobs either). _info is fixed at registration time and the
// pointed-to object is never freed, so readers see a stable snapshot under the
// shared lock. The array holding the entries is replaced when it grows.
struct StubUnwindEntry {
    const void* _start;
    const StubUnwindInfo* _info;
};
#endif

// The class tracks JIT-compiled code and ranges
class JitCodeCache {
private:
    friend class JitCodeCacheTestAccessor;

    // Readers (signal handlers) take it shared with a bounded spin; writers
    // take it exclusively only to publish what they prepared outside it.
    static SpinLock _stubs_lock;
    // Orders DynamicCodeGenerated() writers; never taken in a signal handler.
    static Mutex _stubs_write_lock;
    static CodeCache _runtime_stubs;
    static std::atomic<const void *> _call_stub_begin;
    static std::atomic<const void *> _call_stub_end;
#ifdef __aarch64__
    static StubUnwindEntry* _stub_unwind;
    static int _stub_unwind_count;
    static int _stub_unwind_capacity;
#endif

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
    
    // Finds the runtime stub containing address and copies its start and name
    // out under the shared _stubs_lock (the names are never freed). Returns
    // false when address is not inside any stub, or without searching when
    // the lock is held exclusively or the shared spin budget runs out (counted
    // as STUB_LOOKUP_LOCK_UNAVAILABLE). Safe to call from a signal handler.
    static bool findRuntimeStub(const void *address, const void **start,
                                const char **name);

#ifdef __aarch64__
    // Finds the runtime stub containing address and returns a consistent view
    // of its start/name plus the precomputed StubUnwindInfo (NULL when the stub
    // was not classified -- including excluded names such as call_stub -- or
    // when address is not inside any stub; returns false in that case).
    // Takes _stubs_lock shared with the same bounded spin as
    // findRuntimeStub() and also returns false when the lock is unavailable.
    // Copies everything out before releasing the lock; the info objects
    // themselves are never freed (same lifetime as the stub names).
    static bool findRuntimeStubInfo(const void* address, const void** start,
                                    const char** name, const StubUnwindInfo** info);
#endif

    // Heap usage of the runtime-stubs code cache, via CodeCache::memoryUsage().
    // Read under the shared stubs lock because DynamicCodeGenerated() mutates
    // _runtime_stubs (commitAdd()) concurrently. Not for signal handlers: it
    // waits without bound.
    static long long runtimeStubsMemoryUsage();
    static bool isJitCode(const void* pc) {
        return CodeHeap::contains(pc);
    }
};

#endif // _HOTSPOT_JITCODECACHE_H
