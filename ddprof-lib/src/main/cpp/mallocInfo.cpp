/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mallocInfo.h"
#include <dlfcn.h>

// mallinfo2() replaced the int-based mallinfo() in glibc 2.33. The release
// libraries are built against older glibc headers (the el8 image has 2.28),
// where <malloc.h> declares neither mallinfo2() nor its struct -- so instead
// of gating the call on __GLIBC_MINOR__ at compile time, which compiled the
// arena counters out of every shipped build, the symbol is resolved at
// runtime with dlsym(). A dlsym string lookup adds no symbol-version
// reference, so the binary keeps loading on runtimes older than 2.33: there
// dlsym returns NULL and the counters stay unset, exactly as on musl and
// macOS where the symbol does not exist either.
//
// The mirror must match the real struct field for field: mallinfo2() is
// called through this type, and the return-by-value ABI (hidden sret pointer
// vs registers) is selected from it. Ten size_t fields, same order as the
// old struct mallinfo; verified against glibc 2.33+ <malloc.h>.
struct Mallinfo2 {
  size_t arena;
  size_t ordblks;
  size_t smblks;
  size_t hblks;
  size_t hblkhd;
  size_t usmblks;
  size_t fsmblks;
  size_t uordblks;
  size_t fordblks;
  size_t keepcost;
};

#if defined(__GLIBC__) && defined(__GLIBC_PREREQ)
  #if __GLIBC_PREREQ(2, 33)
    #include <malloc.h>
    #include <stddef.h>
    // On builds whose headers do declare struct mallinfo2, the mirror is
    // pinned to it field by field: every one of the ten offsets, not just the
    // five mallocArenaSnapshot() copies out (arena, hblkhd, uordblks,
    // fordblks, keepcost). On older headers -- including the el8 release
    // image (glibc 2.28), the builds this path exists for -- struct mallinfo2
    // is not declared, so this pin cannot run and the mirror is the only
    // definition. There the field mapping is cross-checked at runtime by
    // mallocArenaStats_ut.cpp wherever the test runtime provides mallinfo2:
    // glibc's accounting identity (arena == uordblks + fordblks, keepcost <=
    // fordblks), a large mmapped chunk moving only hblkhd, signed in-use
    // deltas across an allocation burst, and post-trim keepcost bounds. On
    // runtimes older than 2.33 those tests skip.
    static_assert(sizeof(Mallinfo2) == sizeof(struct mallinfo2),
                  "Mallinfo2 mirror does not match glibc's struct mallinfo2");
    #define DDPROF_PIN_MALLINFO2_FIELD(f)                                      \
      static_assert(offsetof(Mallinfo2, f) == offsetof(struct mallinfo2, f),   \
                    "Mallinfo2::" #f " offset diverges from glibc's struct mallinfo2")
    DDPROF_PIN_MALLINFO2_FIELD(arena);
    DDPROF_PIN_MALLINFO2_FIELD(ordblks);
    DDPROF_PIN_MALLINFO2_FIELD(smblks);
    DDPROF_PIN_MALLINFO2_FIELD(hblks);
    DDPROF_PIN_MALLINFO2_FIELD(hblkhd);
    DDPROF_PIN_MALLINFO2_FIELD(usmblks);
    DDPROF_PIN_MALLINFO2_FIELD(fsmblks);
    DDPROF_PIN_MALLINFO2_FIELD(uordblks);
    DDPROF_PIN_MALLINFO2_FIELD(fordblks);
    DDPROF_PIN_MALLINFO2_FIELD(keepcost);
    #undef DDPROF_PIN_MALLINFO2_FIELD
  #endif
#endif

bool mallocArenaSnapshot(MallocArenaInfo *out) {
  typedef Mallinfo2 (*mallinfo2_fn)();
  // Not cached: called once per JFR chunk flush, so the dlsym() lookup is
  // negligible (same trade-off as glibcMallocActive()).
  mallinfo2_fn fn = (mallinfo2_fn)dlsym(RTLD_DEFAULT, "mallinfo2");
  if (fn == NULL) {
    return false;
  }
  Mallinfo2 mi = fn();
  out->arena = mi.arena;
  out->hblkhd = mi.hblkhd;
  out->uordblks = mi.uordblks;
  out->fordblks = mi.fordblks;
  out->keepcost = mi.keepcost;
  return true;
}
