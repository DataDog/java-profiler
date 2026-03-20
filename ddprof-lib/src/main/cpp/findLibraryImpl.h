/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _FINDLIBRARYIMPL_H
#define _FINDLIBRARYIMPL_H

// Signal-handler-safe last-hit-index cache for findLibraryByAddress.
//
// Templated on CacheArray and CacheEntry so that the exact same algorithm
// can be exercised from benchmarks (using lightweight fake types) without
// pulling in JVM headers, while production uses CodeCacheArray/CodeCache.
//
// Requirements on CacheArray:
//   int          count()     const  — number of live entries
//   CacheEntry*  operator[](int i)  — entry at index i (may be nullptr)
//
// Requirements on CacheEntry:
//   bool  contains(const void* address) const

template<typename CacheEntry, typename CacheArray>
static inline CacheEntry* findLibraryByAddressImpl(CacheArray& libs, const void* address) {
    // Not thread_local: DTLS init in shared libraries calls calloc, which
    // deadlocks if a profiler signal fires while the thread is inside malloc.
    // A plain static volatile int is benignly racy — worst case is a cache miss.
    static volatile int last_hit = 0;
    const int count = libs.count();
    int hint = last_hit;
    if (hint < count) {
        CacheEntry* lib = libs[hint];
        if (lib != nullptr && lib->contains(address)) {
            return lib;
        }
    }
    for (int i = 0; i < count; i++) {
        CacheEntry* lib = libs[i];
        if (lib != nullptr && lib->contains(address)) {
            last_hit = i;
            return lib;
        }
    }
    return nullptr;
}

#endif // _FINDLIBRARYIMPL_H
