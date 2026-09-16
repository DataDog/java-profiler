/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _MALLOCFOOTPRINT_H
#define _MALLOCFOOTPRINT_H

#include <cstddef>

#if defined(__linux__)
  #include <malloc.h>
  #define DD_HAVE_MALLOC_USABLE_SIZE 1
#elif defined(__APPLE__)
  #include <malloc/malloc.h>
  #define DD_HAVE_MALLOC_SIZE 1
#endif

// Real resident cost of a heap allocation, as opposed to the size that was
// requested.
//
// The profiler's NM_* gauges record requested (logical) bytes, which is what
// makes them comparable against sizeof() arithmetic. RSS, however, is paid in
// allocator chunks: the request is rounded up to an alignment quantum and
// carries a per-chunk header. Reconciliation previously multiplied logical bytes
// by a single blanket factor measured on one workload, which is wrong whenever
// the allocation-size mix differs -- overhead is a function of *per-allocation*
// size, not of total bytes. A 512 KB chunk pays ~0.003 %; a 96-byte tree node
// pays 16.7 %.
//
// This measures it instead: usable size comes from the allocator, and the
// per-chunk header is probed once at first use rather than assumed.
class MallocFootprint {
private:
  // Determined empirically: allocate several same-size blocks and take the
  // smallest positive address stride between any two. That stride is
  // usable + header, so header = stride - usable.
  //
  // Probed rather than hardcoded because the allocator in force at runtime is
  // not knowable at compile time -- an LD_PRELOAD'd tcmalloc or jemalloc leaves
  // __GLIBC__ defined while adding no per-object header at all (their metadata
  // is out of band). Assuming glibc's 8 bytes would then invent overhead that
  // does not exist, at one allocation's worth per allocation.
  static size_t probeHeaderBytes() {
#ifdef DD_HAVE_MALLOC_USABLE_SIZE
    const int N = 16;
    const size_t SZ = 48;
    void *p[N];
    for (int i = 0; i < N; i++) {
      p[i] = malloc(SZ);
      if (p[i] == NULL) {  // give up cleanly rather than guess
        for (int j = 0; j < i; j++) free(p[j]);
        return 0;
      }
    }
    size_t usable = malloc_usable_size(p[0]);
    long best = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        long d = (char *)p[j] - (char *)p[i];
        if (d > 0 && (best == 0 || d < best)) {
          best = d;
        }
      }
    }
    for (int i = 0; i < N; i++) free(p[i]);
    long header = best - (long)usable;
    // Sanity-bound the result. A negative or implausibly large value means the
    // blocks were not laid out contiguously (a size-class allocator, or an
    // arena boundary landed mid-probe), in which case 0 is the honest answer:
    // report only the rounding we can see, and understate rather than invent.
    if (header < 0 || header > 64) {
      return 0;
    }
    return (size_t)header;
#else
    return 0;
#endif
  }

public:
  // Per-chunk header size for the allocator actually in force. Probed once;
  // the C++11 function-local static makes initialisation thread-safe. NOT
  // async-signal-safe (it allocates), so first use must not be from a signal
  // handler -- every current call site is on a normal thread.
  static size_t headerBytes() {
    static const size_t header = probeHeaderBytes();
    return header;
  }

  // Bytes this allocation actually costs: allocator-reported usable size plus
  // the per-chunk header. Page rounding for large mmap'd chunks is already
  // inside the usable size, so it must not be added again.
  static size_t of(void *p, size_t requested) {
    if (p == NULL) {
      return 0;
    }
#ifdef DD_HAVE_MALLOC_USABLE_SIZE
    return malloc_usable_size(p) + headerBytes();
#elif defined(DD_HAVE_MALLOC_SIZE)
    return malloc_size(p) + headerBytes();
#else
    return requested;  // no introspection available: report no overhead
#endif
  }

  // Overhead alone -- the part RSS pays for that the logical counters miss.
  static size_t overheadOf(void *p, size_t requested) {
    size_t total = of(p, requested);
    return total > requested ? total - requested : 0;
  }
};

#endif // _MALLOCFOOTPRINT_H
