/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MALLOCARENATESTENV_H
#define _MALLOCARENATESTENV_H

#include <cstdlib>
#include <cstring>

extern char** environ;

// True when GLIBC_TUNABLES or any MALLOC_* variable is set. They change the arena count,
// the mmap and trim thresholds, and which arena serves a thread, which the arena tests
// assume at their glibc defaults.
static inline bool mallocTuned() {
  if (getenv("GLIBC_TUNABLES") != NULL) {
    return true;
  }
  for (char** e = environ; *e != NULL; e++) {
    if (strncmp(*e, "MALLOC_", 7) == 0) {
      return true;
    }
  }
  return false;
}

#endif // _MALLOCARENATESTENV_H
