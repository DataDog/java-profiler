/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _RECORDING_WRITE_FAILURE_FIXTURE_H
#define _RECORDING_WRITE_FAILURE_FIXTURE_H

#include <gtest/gtest.h>
#include <cerrno>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

// Fail the real output syscall by swapping in a read-only fd, then restore the
// original descriptor before closing every owned handle, including on assertions.
class RecordingWriteFailureFixture {
  int _fd = -1;
  int _writable_fd = -1;
  int _read_only_fd = -1;
  bool _swapped = false;

  static bool replaceDescriptor(int source, int target) {
    int result;
    do {
      result = dup2(source, target);
    } while (result < 0 && errno == EINTR);
    return result == target;
  }

public:
  RecordingWriteFailureFixture() {
    char path[] = "/tmp/ddprof-output-failure-XXXXXX";
    _fd = mkstemp(path);
    if (_fd < 0) return;
    _writable_fd = dup(_fd);
    _read_only_fd = open(path, O_RDONLY);
    EXPECT_EQ(0, unlink(path));
  }

  ~RecordingWriteFailureFixture() {
    if (_swapped) EXPECT_TRUE(replaceDescriptor(_writable_fd, _fd));
    if (_read_only_fd >= 0) close(_read_only_fd);
    if (_writable_fd >= 0) close(_writable_fd);
    if (_fd >= 0) close(_fd);
  }

  RecordingWriteFailureFixture(const RecordingWriteFailureFixture&) = delete;
  RecordingWriteFailureFixture& operator=(const RecordingWriteFailureFixture&) = delete;

  bool valid() const { return _fd >= 0 && _writable_fd >= 0 && _read_only_fd >= 0; }
  int fd() const { return _fd; }

  bool failWrites() {
    _swapped = replaceDescriptor(_read_only_fd, _fd);
    return _swapped;
  }
};

#endif // _RECORDING_WRITE_FAILURE_FIXTURE_H
