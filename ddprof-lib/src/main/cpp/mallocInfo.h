/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef MALLOC_INFO_H
#define MALLOC_INFO_H

#include <stddef.h>

// The process-wide malloc arena figures the profiler publishes, in the units
// glibc's allocator accounting reports them (see mallocArenaSnapshot()).
struct MallocArenaInfo {
  size_t arena;    // system memory held by all arenas, summed per arena
  size_t hblkhd;   // bytes in mmap'd chunks
  size_t uordblks; // bytes currently handed out to callers
  size_t fordblks; // bytes free but retained inside the arenas
  size_t keepcost; // the main arena's top chunk only
};

// Snapshot the process-wide glibc malloc arena state via mallinfo2(), resolved
// at runtime with dlsym() so a binary built against old glibc headers (the el8
// image ships glibc 2.28 headers) still picks mallinfo2() up from a newer
// runtime glibc. Fills *out and returns true on success; returns false and
// leaves *out untouched when the runtime allocator does not provide
// mallinfo2() (glibc < 2.33 at runtime, musl, macOS) -- callers leave the
// arena counters unset, exactly as they already do on musl.
//
// NOT async-signal-safe: mallinfo2() walks every arena taking each arena lock.
// Flush path only -- must never be reached from the sampling signal handler.
bool mallocArenaSnapshot(MallocArenaInfo *out);

#endif // MALLOC_INFO_H
