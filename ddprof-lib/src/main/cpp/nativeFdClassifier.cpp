/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeFdClassifier.h"

#if defined(__linux__)

#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>

NativeFdClassifier::NativeFdClassifier() {
  for (int index = 0; index < FD_TYPE_CACHE_SIZE; index++) {
    _fd_type_cache[index].store(0, std::memory_order_relaxed);
  }
}

uint8_t NativeFdClassifier::fdType(int fd) {
  if (fd < 0) {
    return 0;
  }

  auto probe = [](int socket_fd) -> uint8_t {
    int so_type;
    socklen_t solen = sizeof(so_type);
    int rc = getsockopt(socket_fd, SOL_SOCKET, SO_TYPE, &so_type, &solen);
    if (rc == 0) {
      if (so_type == SOCK_STREAM) {
        return FD_TYPE_STREAM_SOCKET;
      }
      if (so_type == SOCK_DGRAM) {
        return FD_TYPE_DATAGRAM_SOCKET;
      }
      return FD_TYPE_OTHER_SOCKET;
    }
    return errno == ENOTSOCK ? FD_TYPE_NON_SOCKET : 0;
  };

  if (static_cast<size_t>(fd) >= static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    return probe(fd);
  }

  uint32_t gen = _fd_cache_gen.load(std::memory_order_acquire);
  uint32_t cached = _fd_type_cache[fd].load(std::memory_order_acquire);
  if ((cached >> FD_TYPE_GEN_SHIFT) == gen) {
    uint8_t type = static_cast<uint8_t>(cached & FD_TYPE_MASK);
    if (type != 0) {
      return type;
    }
  }

  uint8_t type = probe(fd);
  if (type != 0) {
    _fd_type_cache[fd].store((gen << FD_TYPE_GEN_SHIFT) | type,
                             std::memory_order_release);
  }
  return type;
}

bool NativeFdClassifier::isStreamSocket(int fd) {
  return fdType(fd) == FD_TYPE_STREAM_SOCKET;
}

bool NativeFdClassifier::isDatagramSocket(int fd) {
  return fdType(fd) == FD_TYPE_DATAGRAM_SOCKET;
}

void NativeFdClassifier::clearFdType(int fd) {
  if (fd >= 0 && static_cast<size_t>(fd) < static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    _fd_type_cache[fd].store(0, std::memory_order_release);
  }
}

void NativeFdClassifier::clearFdTypeCache() {
  _fd_cache_gen.fetch_add(1, std::memory_order_release);
}

#endif // __linux__
