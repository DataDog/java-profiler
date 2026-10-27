/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENAWALKER_H
#define _MALLOCARENAWALKER_H

#include <stddef.h>
#include <stdint.h>

#include "arch.h"

// Reason a walk of the glibc arena list did or did not produce a result.
// Every value except OK means the other fields of ArenaWalkResult are not
// trustworthy, with one exception: when walk() tries every layout and none
// succeeds, heapInfoSize still holds the value found at the seed.
// UNSUPPORTED_JVM, REPLACED_ALLOCATOR and HUGETLB_TUNABLE are
// never returned by MallocArenaWalker; the caller sets them when it decides
// not to walk.
enum ArenaWalkStatus {
  ARENA_WALK_OK,
  ARENA_WALK_UNSUPPORTED_PLATFORM,  // not Linux with glibc
  ARENA_WALK_UNSUPPORTED_JVM,       // no SIGSEGV recovery on this JVM
  ARENA_WALK_REPLACED_ALLOCATOR,    // malloc is not glibc's
  ARENA_WALK_HUGETLB_TUNABLE,       // heap size differs from HEAP_MAX_SIZE
  ARENA_WALK_NO_SEED,               // no non-main-arena chunk available
  ARENA_WALK_NO_LAYOUT,             // internal: no candidate layout tried
  ARENA_WALK_FAULT,                 // a read of arena memory faulted
  ARENA_WALK_IMPLAUSIBLE,           // system_mem / max_system_mem failed checks
  ARENA_WALK_BAD_NEXT,              // next pointer unreadable or null
  ARENA_WALK_SECOND_MAIN,           // more than one arena failed the heap check
  ARENA_WALK_NO_MAIN,               // the walk returned to the seed without main_arena
  ARENA_WALK_TOO_MANY,              // more arenas than the caller's cap
  ARENA_WALK_STATUS_COUNT
};

// Kebab-case name of a status ("ok", "no-seed", ...). Never returns null.
const char* arenaWalkStatusName(ArenaWalkStatus status);

// Byte offsets of the malloc_state fields the walk reads. glibc does not
// export them, and they differ between releases. off_attached == 0 means the
// layout has no attached_threads field.
struct ArenaLayout {
  size_t off_next;
  size_t off_attached;
  size_t off_sys;
  size_t off_max;
  const char* name;
};

static const int ARENA_LAYOUT_COUNT = 4;

// Candidate layout number idx, or nullptr when idx is out of range.
const ArenaLayout* arenaLayoutAt(int idx);

// Index of the candidate that matches the glibc release major.minor best.
// Vendors backport malloc changes, so this only orders the candidates.
int preferredArenaLayout(int major, int minor);

struct ArenaWalkResult {
  ArenaWalkStatus status;
  int arenaCount;
  u64 nonMainBytes;       // sum of system_mem over arenas other than main_arena
  u64 mainBytes;          // system_mem of main_arena
  u64 largestBytes;       // largest system_mem
  u64 largestMaxBytes;    // largest max_system_mem
  int threadPrivateArenas;  // arenas with attached_threads == 1, -1 if the layout has none
  int layoutIndex;          // index of the layout used, -1 when none
  size_t heapInfoSize;      // sizeof(heap_info) found at the seed, 0 when unknown
};

// Lock-free walk of glibc's circular malloc_state list (malloc_state->next).
//
// The seed is the arena of a chunk allocated by the calling thread. All reads
// of arena memory go through SafeAccess::safeCopy, so the walk needs the
// SIGSEGV/SIGBUS handler that routes to SafeAccess::handle_safefetch. It is
// not async-signal-safe: the seed allocation calls malloc.
class MallocArenaWalker {
 public:
  // Walks with the calibrated layout. Before calibration it tries the
  // preferred candidate first, then the others, and keeps the first layout
  // that passes every check. When none passes, out->status is the preferred
  // candidate's failure and out->layoutIndex is -1.
  // Allocates one small chunk until a seed is cached. cap bounds the arena
  // count; a longer list yields ARENA_WALK_TOO_MANY.
  static void walk(ArenaWalkResult* out, int cap);

  // Walks with one given layout, without changing the calibrated layout.
  // Public so tests can force a wrong layout.
  static void walkWithLayout(const ArenaLayout& layout, ArenaWalkResult* out, int cap);

  // Forgets the cached seed and the calibrated layout.
  static void resetForTest();
};

#endif  // _MALLOCARENAWALKER_H
