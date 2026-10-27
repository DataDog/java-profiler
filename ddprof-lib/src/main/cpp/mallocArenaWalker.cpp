/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __linux__
#include <features.h>  // defines __GLIBC__ when glibc is the C library
#endif

#include "mallocArenaWalker.h"

#include <stdio.h>
#include <string.h>

#if defined(__linux__) && defined(__GLIBC__)
#include <gnu/libc-version.h>
#include <stdlib.h>

#include "safeAccess.h"
#include "signalSafety.h"
#endif

static const char* const STATUS_NAMES[ARENA_WALK_STATUS_COUNT] = {
    "ok",
    "unsupported-platform",
    "unsupported-jvm",
    "replaced-allocator",
    "hugetlb-tunable",
    "no-seed",
    "no-layout",
    "fault",
    "implausible",
    "bad-next",
    "second-main",
    "no-main",
    "too-many",
};

// Known malloc_state layouts on 64-bit targets.
static const ArenaLayout LAYOUTS[ARENA_LAYOUT_COUNT] = {
    {2152, 0, 2168, 2176, "2.17-2.22"},
    {2152, 2168, 2176, 2184, "2.23-2.26"},
    {2160, 2176, 2184, 2192, "2.27-2.42"},
    {2072, 2088, 2096, 2104, "2.43+"},
};

const char* arenaWalkStatusName(ArenaWalkStatus status) {
  if ((unsigned)status >= (unsigned)ARENA_WALK_STATUS_COUNT) {
    return "unknown";
  }
  return STATUS_NAMES[status];
}

const ArenaLayout* arenaLayoutAt(int idx) {
  if (idx < 0 || idx >= ARENA_LAYOUT_COUNT) {
    return nullptr;
  }
  return &LAYOUTS[idx];
}

int preferredArenaLayout(int major, int minor) {
  if (major == 2 && minor < 23) return 0;
  if (major == 2 && minor < 27) return 1;
  if (major == 2 && minor < 43) return 2;
  return 3;
}

static void initResult(ArenaWalkResult* out, ArenaWalkStatus status) {
  memset(out, 0, sizeof(*out));
  out->status = status;
  out->threadPrivateArenas = -1;
  out->layoutIndex = -1;
}

#if defined(__linux__) && defined(__GLIBC__)

// HEAP_MAX_SIZE of glibc on 64-bit targets without the hugetlb tunable:
// 2 * DEFAULT_MMAP_THRESHOLD_MAX. Non-main-arena heaps are aligned to it.
static const uintptr_t HEAP_MAX_SIZE = (uintptr_t)64 << 20;
// Low bits of a chunk's size field.
static const size_t CHUNK_IS_MMAPPED = 0x2;
static const size_t CHUNK_NON_MAIN_ARENA = 0x4;

// The first validated seed stays valid for the process lifetime: glibc never
// frees an arena. The heap_info size is published before the seed, so a
// reader that sees a seed also sees its size.
static uintptr_t seed_arena = 0;
static size_t seed_heap_info_size = 0;
// Index of the layout that passed a full walk, -1 before calibration.
static int calibrated_layout = -1;

template <typename T>
static inline bool readAt(uintptr_t addr, T* out) {
  return SafeAccess::safeCopy(out, (const void*)addr, sizeof(T));
}

// Removes the top-byte address tag (MTE/TBI) that aarch64 malloc may put on
// returned pointers.
static inline uintptr_t untag(uintptr_t p) {
#if defined(__aarch64__)
  return p & (((uintptr_t)1 << 56) - 1);
#else
  return p;
#endif
}

// Caches the arena of a chunk allocated by this thread, unless that chunk
// lives in main_arena or an mmapped chunk. Returns true when a seed is cached.
static bool ensureSeed() {
  if (__atomic_load_n(&seed_arena, __ATOMIC_ACQUIRE) != 0) {
    return true;
  }
  void* p = malloc(64);
  bool ok = false;
  if (p != nullptr) {
    uintptr_t chunk = untag((uintptr_t)p);
    size_t hdr = 0;
    if (readAt(chunk - sizeof(size_t), &hdr) && !(hdr & CHUNK_IS_MMAPPED) &&
        (hdr & CHUNK_NON_MAIN_ARENA)) {
      uintptr_t heap = chunk & ~(HEAP_MAX_SIZE - 1);
      uintptr_t ar = 0;
      // heap_info.ar_ptr is the first field of heap_info.
      if (readAt(heap, &ar) && ar > heap) {
        size_t hi = ar - heap;
        // sizeof(heap_info) is 32 before glibc 2.35 and 48 since.
        if (hi == 32 || hi == 48) {
          __atomic_store_n(&seed_heap_info_size, hi, __ATOMIC_RELEASE);
          __atomic_store_n(&seed_arena, ar, __ATOMIC_RELEASE);
          ok = true;
        }
      }
    }
    free(p);
  }
  return ok;
}

// A non-main arena is created as a = h->ar_ptr = (mstate)(h + 1) at the start
// of its first heap, so its address passes this check. main_arena is a static
// object and fails it.
static bool isNonMainArena(uintptr_t a, size_t heapInfoSize) {
  uintptr_t heap = a & ~(HEAP_MAX_SIZE - 1);
  uintptr_t back = 0;
  if (a - heap != heapInfoSize) return false;
  if (!readAt(heap, &back)) return false;
  return back == a;
}

static void walkFrom(const ArenaLayout& l, ArenaWalkResult* r, int cap, uintptr_t seed,
                     size_t heapInfoSize) {
  uintptr_t cur = seed;
  int mainSeen = 0;
  u64 attached1 = 0;
  initResult(r, ARENA_WALK_OK);
  r->heapInfoSize = heapInfoSize;
  do {
    if (r->arenaCount >= cap) {
      r->status = ARENA_WALK_TOO_MANY;
      return;
    }
    bool isMain = !isNonMainArena(cur, heapInfoSize);
    if (isMain && mainSeen++) {
      r->status = ARENA_WALK_SECOND_MAIN;
      return;
    }
    size_t sys = 0, max = 0, attached = 0;
    if (!readAt(cur + l.off_sys, &sys) || !readAt(cur + l.off_max, &max)) {
      r->status = ARENA_WALK_FAULT;
      return;
    }
    if (l.off_attached != 0 && !readAt(cur + l.off_attached, &attached)) {
      r->status = ARENA_WALK_FAULT;
      return;
    }
    if (sys == 0 || (sys & 0xfff) != 0 || max < sys) {
      r->status = ARENA_WALK_IMPLAUSIBLE;
      return;
    }
    uintptr_t next = 0;
    if (!readAt(cur + l.off_next, &next) || next == 0) {
      r->status = ARENA_WALK_BAD_NEXT;
      return;
    }
    __atomic_thread_fence(__ATOMIC_ACQUIRE);
    if (isMain) {
      r->mainBytes = sys;
    } else {
      r->nonMainBytes += sys;
    }
    if (sys > r->largestBytes) r->largestBytes = sys;
    if (max > r->largestMaxBytes) r->largestMaxBytes = max;
    if (l.off_attached != 0 && attached == 1) attached1++;
    r->arenaCount++;
    cur = next;
  } while (cur != seed);
  if (mainSeen != 1) {
    r->status = ARENA_WALK_NO_MAIN;
    return;
  }
  if (l.off_attached != 0) {
    r->threadPrivateArenas = (int)attached1;
  }
}

void MallocArenaWalker::walkWithLayout(const ArenaLayout& layout, ArenaWalkResult* out, int cap) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  if (!ensureSeed()) {
    initResult(out, ARENA_WALK_NO_SEED);
    return;
  }
  walkFrom(layout, out, cap, __atomic_load_n(&seed_arena, __ATOMIC_ACQUIRE),
           __atomic_load_n(&seed_heap_info_size, __ATOMIC_ACQUIRE));
}

void MallocArenaWalker::walk(ArenaWalkResult* out, int cap) {
  DEBUG_ASSERT_NOT_IN_SIGNAL();
  if (!ensureSeed()) {
    initResult(out, ARENA_WALK_NO_SEED);
    return;
  }
  uintptr_t seed = __atomic_load_n(&seed_arena, __ATOMIC_ACQUIRE);
  size_t hi = __atomic_load_n(&seed_heap_info_size, __ATOMIC_ACQUIRE);
  int known = __atomic_load_n(&calibrated_layout, __ATOMIC_ACQUIRE);
  if (known >= 0) {
    walkFrom(LAYOUTS[known], out, cap, seed, hi);
    out->layoutIndex = out->status == ARENA_WALK_OK ? known : -1;
    return;
  }
  int major = 0, minor = 0;
  sscanf(gnu_get_libc_version(), "%d.%d", &major, &minor);
  int pref = preferredArenaLayout(major, minor);
  ArenaWalkStatus firstFail = ARENA_WALK_NO_LAYOUT;
  for (int k = 0; k < ARENA_LAYOUT_COUNT; k++) {
    int idx = (pref + k) % ARENA_LAYOUT_COUNT;
    walkFrom(LAYOUTS[idx], out, cap, seed, hi);
    if (out->status == ARENA_WALK_OK) {
      __atomic_store_n(&calibrated_layout, idx, __ATOMIC_RELEASE);
      out->layoutIndex = idx;
      return;
    }
    if (k == 0) firstFail = out->status;
  }
  initResult(out, firstFail);
  out->heapInfoSize = hi;
}

void MallocArenaWalker::resetForTest() {
  __atomic_store_n(&calibrated_layout, -1, __ATOMIC_RELEASE);
  __atomic_store_n(&seed_arena, (uintptr_t)0, __ATOMIC_RELEASE);
  __atomic_store_n(&seed_heap_info_size, (size_t)0, __ATOMIC_RELEASE);
}

#else  // not Linux with glibc

void MallocArenaWalker::walkWithLayout(const ArenaLayout&, ArenaWalkResult* out, int) {
  initResult(out, ARENA_WALK_UNSUPPORTED_PLATFORM);
}

void MallocArenaWalker::walk(ArenaWalkResult* out, int) {
  initResult(out, ARENA_WALK_UNSUPPORTED_PLATFORM);
}

void MallocArenaWalker::resetForTest() {}

#endif
