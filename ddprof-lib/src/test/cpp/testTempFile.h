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

using TempFileRead = ssize_t (*)(int, void*, size_t);
using TempFileWrite = ssize_t (*)(int, const void*, size_t);

static inline int copyToTempFileWithIO(const char* from, const char* dir, const char* prefix,
                                       char* path_out, size_t size, TempFileRead read_fn,
                                       TempFileWrite write_fn) {
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
  while (err == 0) {
    ssize_t n;
    do {
      n = read_fn(in.get(), buf, sizeof(buf));
    } while (n < 0 && errno == EINTR);
    if (n == 0) break;
    if (n < 0) {
      err = errno;
      break;
    }

    size_t offset = 0;
    while (offset < static_cast<size_t>(n)) {
      ssize_t written;
      do {
        written = write_fn(out.get(), buf + offset, static_cast<size_t>(n) - offset);
      } while (written < 0 && errno == EINTR);
      if (written < 0) {
        err = errno;
        break;
      }
      if (written == 0) {
        err = EIO;
        break;
      }
      offset += static_cast<size_t>(written);
    }
  }
  if (err != 0) unlink(path_out);
  return err;
}

// Copies `from` to a fresh "<dir>/<prefix>-XXXXXX.so" and writes its path to path_out;
// a null dir means TMPDIR, or /tmp when unset. Returns 0, or the errno of the failing
// step (EIO for a zero-progress write) after removing the partial copy.
static inline int copyToTempFile(const char* from, const char* dir, const char* prefix,
                                 char* path_out, size_t size) {
  return copyToTempFileWithIO(from, dir, prefix, path_out, size, &::read, &::write);
}

#endif // _TEST_TEMP_FILE_H
