/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Test-only helpers for copying a file to a fresh temporary file.

#ifndef _TEST_TEMP_FILE_H
#define _TEST_TEMP_FILE_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Owns a file descriptor; closes it on scope exit.
class FdOwner {
 public:
  explicit FdOwner(int fd) : _fd(fd) {}
  ~FdOwner() { if (_fd >= 0) close(_fd); }
  FdOwner(const FdOwner&) = delete;
  FdOwner& operator=(const FdOwner&) = delete;
  int get() const { return _fd; }

 private:
  int _fd;
};

// Copies `from` to a fresh "<dir>/<prefix>-XXXXXX.so" and writes its path to path_out;
// a null dir means TMPDIR, or /tmp when unset. Returns 0, or the errno of the failing
// step (EIO for a short write) after removing the partial copy.
static inline int copyToTempFile(const char* from, const char* dir, const char* prefix,
                                 char* path_out, size_t size) {
  if (dir == nullptr) dir = getenv("TMPDIR");
  if (dir == nullptr || dir[0] == '\0') dir = "/tmp";
  int len = snprintf(path_out, size, "%s/%s-XXXXXX.so", dir, prefix);
  if (len < 0 || static_cast<size_t>(len) >= size) return ENAMETOOLONG;
  FdOwner out(mkstemps(path_out, 3));
  if (out.get() < 0) return errno;
  int err = 0;
  FdOwner in(open(from, O_RDONLY));
  if (in.get() < 0) err = errno;
  char buf[8192];
  ssize_t n;
  while (err == 0 && (n = read(in.get(), buf, sizeof(buf))) != 0) {
    if (n < 0) {
      err = errno;
    } else {
      ssize_t written = write(out.get(), buf, n);
      if (written != n) err = written < 0 ? errno : EIO;
    }
  }
  if (err != 0) unlink(path_out);
  return err;
}

#endif // _TEST_TEMP_FILE_H
