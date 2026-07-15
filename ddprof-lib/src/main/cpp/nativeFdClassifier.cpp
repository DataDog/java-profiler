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
std::atomic<uint64_t> NativeFdClassifier::_probe_count{0};
#endif

NativeFdClassifier::NativeFdClassifier() {
  for (int index = 0; index < FD_TYPE_CACHE_SIZE; index++) {
    _fd_type_cache[index].store(0, std::memory_order_relaxed);
  }
  for (int index = 0; index < HIGH_FD_TYPE_CACHE_SIZE; index++) {
    _high_fd_type_cache[index].store(0, std::memory_order_relaxed);
  }
}

#ifdef UNIT_TEST
void NativeFdClassifier::setProbeOverrideForTest(ProbeOverride probe) {
  _probe_override.store(probe, std::memory_order_release);
}

uint64_t NativeFdClassifier::probeCountForTest() {
  return _probe_count.load(std::memory_order_acquire);
}

void NativeFdClassifier::resetProbeCountForTest() {
  _probe_count.store(0, std::memory_order_release);
}
#endif

uint8_t NativeFdClassifier::probeFdType(int fd) {
#ifdef UNIT_TEST
  _probe_count.fetch_add(1, std::memory_order_relaxed);
#endif
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

void NativeFdClassifier::cacheFdType(int fd, uint8_t type, uint32_t gen) {
  if (fd < 0 || type == 0) {
    return;
  }
  if (static_cast<size_t>(fd) < static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    _fd_type_cache[fd].store((gen << FD_TYPE_GEN_SHIFT) | type,
                             std::memory_order_release);
  } else {
    _high_fd_type_cache[highFdCacheIndex(fd)].store(highFdEntry(fd, gen, type),
                                                    std::memory_order_release);
  }
}

uint64_t NativeFdClassifier::highFdEntry(int fd, uint32_t gen, uint8_t type) {
  return (static_cast<uint64_t>(static_cast<uint32_t>(fd)) << 32)
      | (static_cast<uint64_t>(gen & FD_TYPE_GEN_MASK) << FD_TYPE_GEN_SHIFT)
      | static_cast<uint64_t>(type);
}

bool NativeFdClassifier::highFdEntryMatches(uint64_t entry, int fd, uint32_t gen) {
  return highFdEntryMatchesFd(entry, fd)
      && (((entry >> FD_TYPE_GEN_SHIFT) & FD_TYPE_GEN_MASK)
          == (gen & FD_TYPE_GEN_MASK));
}

bool NativeFdClassifier::highFdEntryMatchesFd(uint64_t entry, int fd) {
  return static_cast<uint32_t>(entry >> 32) == static_cast<uint32_t>(fd);
}

int NativeFdClassifier::highFdCacheIndex(int fd) {
  return static_cast<int>(static_cast<uint32_t>(fd) %
                          static_cast<uint32_t>(HIGH_FD_TYPE_CACHE_SIZE));
}

uint8_t NativeFdClassifier::highFdType(int fd, uint32_t gen) {
  int index = highFdCacheIndex(fd);
  uint64_t cached = _high_fd_type_cache[index].load(std::memory_order_acquire);
  if (highFdEntryMatches(cached, fd, gen)) {
    uint8_t type = static_cast<uint8_t>(cached & FD_TYPE_MASK);
    if (type != 0) {
      return type;
    }
  }

  uint8_t type = probeFdType(fd);
  // probeFdType() returns 0 for transient errors such as EBADF. Do not cache those:
  // the same fd number may later be reused for a socket.
  if (type != 0) {
    _high_fd_type_cache[index].store(highFdEntry(fd, gen, type),
                                     std::memory_order_release);
  }
  return type;
}

uint8_t NativeFdClassifier::fdType(int fd) {
  if (fd < 0) {
    return 0;
  }

  uint32_t gen = _fd_cache_gen.load(std::memory_order_acquire);
  if (static_cast<size_t>(fd) >= static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    return highFdType(fd, gen);
  }

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
    cacheFdType(fd, type, gen);
  }
  return type;
}

bool NativeFdClassifier::isStreamSocket(int fd) {
  return fdType(fd) == FD_TYPE_STREAM_SOCKET;
}

bool NativeFdClassifier::isDatagramSocket(int fd) {
  return fdType(fd) == FD_TYPE_DATAGRAM_SOCKET;
}

void NativeFdClassifier::cacheNonSocket(int fd) {
  if (fd < 0) {
    return;
  }
  uint32_t gen = _fd_cache_gen.load(std::memory_order_acquire);
  cacheFdType(fd, FD_TYPE_NON_SOCKET, gen);
}

void NativeFdClassifier::clearHighFdType(int fd) {
  int index = highFdCacheIndex(fd);
  uint64_t cached = _high_fd_type_cache[index].load(std::memory_order_acquire);
  while (highFdEntryMatchesFd(cached, fd)) {
    if (_high_fd_type_cache[index].compare_exchange_weak(
            cached, 0, std::memory_order_acq_rel, std::memory_order_acquire)) {
      return;
    }
  }
}

void NativeFdClassifier::clearFdType(int fd) {
  if (fd < 0) {
    return;
  }
  if (static_cast<size_t>(fd) < static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    _fd_type_cache[fd].store(0, std::memory_order_release);
  } else {
    clearHighFdType(fd);
  }
}

void NativeFdClassifier::clearFdTypeCache() {
  _fd_cache_gen.fetch_add(1, std::memory_order_release);
}

#endif // __linux__
