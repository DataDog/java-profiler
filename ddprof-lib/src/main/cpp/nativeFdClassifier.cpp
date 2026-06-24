/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeFdClassifier.h"

#if defined(__linux__)

#include <errno.h>
#include <stddef.h>
#include <sys/socket.h>

#ifdef UNIT_TEST
std::atomic<NativeFdClassifier::ProbeOverride> NativeFdClassifier::_probe_override{nullptr};
#endif

NativeFdClassifier::NativeFdClassifier() {
  for (int index = 0; index < FD_TYPE_CACHE_SIZE; index++) {
    _fd_type_cache[index].store(0, std::memory_order_relaxed);
  }
}

#ifdef UNIT_TEST
void NativeFdClassifier::setProbeOverrideForTest(ProbeOverride probe) {
  _probe_override.store(probe, std::memory_order_release);
}
#endif

uint8_t NativeFdClassifier::probeFdType(int fd) {
  int so_type;
  socklen_t solen = sizeof(so_type);
  int rc;
#ifdef UNIT_TEST
  ProbeOverride probe = _probe_override.load(std::memory_order_acquire);
  int probe_errno = 0;
  if (probe != nullptr) {
    rc = probe(fd, &so_type, &probe_errno);
    if (rc != 0) {
      errno = probe_errno;
    }
  } else
#endif
  {
    rc = getsockopt(fd, SOL_SOCKET, SO_TYPE, &so_type, &solen);
  }
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
}

uint8_t NativeFdClassifier::fdType(int fd) {
  if (fd < 0) {
    return 0;
  }

  if (static_cast<size_t>(fd) >= static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    return probeFdType(fd);
  }

  uint32_t gen = _fd_cache_gen.load(std::memory_order_acquire);
  uint32_t cached = _fd_type_cache[fd].load(std::memory_order_acquire);
  if ((cached >> FD_TYPE_GEN_SHIFT) == gen) {
    uint8_t type = static_cast<uint8_t>(cached & FD_TYPE_MASK);
    if (type != 0) {
      return type;
    }
  }

  uint8_t type = probeFdType(fd);
  // probeFdType() returns 0 for transient errors such as EBADF. Do not cache those:
  // the same fd number may later be reused for a socket.
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
