/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ERRNO_GUARD_H
#define _ERRNO_GUARD_H

#include <errno.h>

// Instrumentation must not change either the original's entry or result errno.
class ErrnoGuard {
public:
  ErrnoGuard() : _saved(errno) {}
  ~ErrnoGuard() { errno = _saved; }
  ErrnoGuard(const ErrnoGuard&) = delete;
  ErrnoGuard& operator=(const ErrnoGuard&) = delete;

private:
  int _saved;
};

#endif // _ERRNO_GUARD_H
