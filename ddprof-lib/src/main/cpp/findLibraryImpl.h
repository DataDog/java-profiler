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
//   CacheEntry*  operator[](int i) const  — entry at index i (may be nullptr)
//
// Requirements on CacheEntry:
//   bool  contains(const void* address) const
//
// Signal-safety: the last-hit index is a plain static volatile int.
// DTLS initialisation for shared libraries calls calloc internally; if a
// profiler signal fires on a thread whose TLS block has not been set up yet
// while that thread is inside malloc, any thread_local access deadlocks on
// the allocator lock.  A plain static volatile int avoids TLS entirely.
// A benign race on the index is acceptable — the worst case is a cache miss
// that falls through to the O(n) linear scan.

template<typename CacheEntry, typename CacheArray>
inline CacheEntry* findLibraryByAddressImpl(const CacheArray& libs, const void* address) {
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
