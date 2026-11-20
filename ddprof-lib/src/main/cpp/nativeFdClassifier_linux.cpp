/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nativeFdClassifier.h"

#if defined(__linux__)

#include <errno.h>
#include <stddef.h>
#include <memory>
#include <new>
#include <sys/socket.h>

#ifdef UNIT_TEST
std::atomic<NativeFdClassifier::ProbeOverride> NativeFdClassifier::_probe_override{nullptr};
std::atomic<uint64_t> NativeFdClassifier::_probe_count{0};
std::atomic<uint64_t> NativeFdClassifier::_cache_allocations{0};
#endif

NativeFdClassifier::NativeFdClassifier() {}

NativeFdClassifier::~NativeFdClassifier() {
  delete[] _fd_type_cache;
  delete[] _high_fd_type_cache;
}

void NativeFdClassifier::ensureCachesAllocated() {
  if (_fd_cache_gen.load(std::memory_order_acquire) >= CACHE_EPOCH_LIMIT) {
    return;
  }
  std::call_once(_cache_alloc_once, [this]() {
    std::unique_ptr<std::atomic<uint64_t>[]> fd_type_cache(
        new (std::nothrow) std::atomic<uint64_t>[CACHE_BANKS * FD_TYPE_CACHE_SIZE]);
    std::unique_ptr<std::atomic<uint64_t>[]> high_fd_type_cache(
        new (std::nothrow) std::atomic<uint64_t>[CACHE_BANKS * HIGH_FD_TYPE_CACHE_SIZE]);
    if (!fd_type_cache || !high_fd_type_cache) {
      return;
    }
    for (int index = 0; index < CACHE_BANKS * FD_TYPE_CACHE_SIZE; index++) {
      fd_type_cache[index].store(0, std::memory_order_relaxed);
    }
    for (int index = 0; index < CACHE_BANKS * HIGH_FD_TYPE_CACHE_SIZE; index++) {
      high_fd_type_cache[index].store(0, std::memory_order_relaxed);
    }
    _fd_type_cache = fd_type_cache.release();
    _high_fd_type_cache = high_fd_type_cache.release();
#ifdef UNIT_TEST
    _cache_allocations.fetch_add(1, std::memory_order_relaxed);
#endif
    _caches_allocated.store(true, std::memory_order_release);
  });
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

uint64_t NativeFdClassifier::cacheAllocationCountForTest() {
  return _cache_allocations.load(std::memory_order_acquire);
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

uint64_t NativeFdClassifier::fdEntry(uint32_t epoch, uint64_t incarnation,
                                     uint8_t type) {
  return (static_cast<uint64_t>(epoch) << FD_TYPE_EPOCH_SHIFT)
      | ((incarnation & FD_TYPE_INCARNATION_MASK)
         << FD_TYPE_INCARNATION_SHIFT)
      | static_cast<uint64_t>(type);
}

uint32_t NativeFdClassifier::fdEntryEpoch(uint64_t entry) {
  return static_cast<uint32_t>(entry >> FD_TYPE_EPOCH_SHIFT);
}

uint64_t NativeFdClassifier::fdEntryIncarnation(uint64_t entry) {
  return (entry >> FD_TYPE_INCARNATION_SHIFT) & FD_TYPE_INCARNATION_MASK;
}

void NativeFdClassifier::cacheFdType(int fd, uint8_t type) {
  if (fd < 0 || type == 0) {
    return;
  }
  uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
  if (!_caches_allocated.load(std::memory_order_acquire) || epoch >= CACHE_EPOCH_LIMIT) {
    return;
  }
  size_t bank = epoch / CACHE_BANK_EPOCHS;
  if (static_cast<size_t>(fd) < static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    auto& slot = _fd_type_cache[bank * FD_TYPE_CACHE_SIZE + fd];
    uint64_t cached = slot.load(std::memory_order_acquire);
    uint64_t incarnation = fdEntryIncarnation(cached);
    if (incarnation == FD_TYPE_INCARNATION_MASK) {
      retireCacheBank(epoch);
      return;
    }
    uint64_t desired = fdEntry(epoch, incarnation + 1, type);
    slot.compare_exchange_strong(
        cached, desired, std::memory_order_acq_rel, std::memory_order_acquire);
  } else {
    auto& slot = _high_fd_type_cache[bank * HIGH_FD_TYPE_CACHE_SIZE + highFdCacheIndex(fd)];
    uint64_t cached = slot.load(std::memory_order_acquire);
    uint64_t incarnation = highFdEntryIncarnation(cached);
    if (incarnation == HIGH_FD_INCARNATION_MASK) {
      retireCacheBank(epoch);
      return;
    }
    uint64_t desired = highFdEntry(fd, epoch, incarnation + 1, type);
    slot.compare_exchange_strong(
        cached, desired, std::memory_order_acq_rel, std::memory_order_acquire);
  }
}

uint64_t NativeFdClassifier::highFdEntry(int fd, uint32_t epoch,
                                         uint64_t incarnation, uint8_t type) {
  // The direct-mapped index carries the low 12 fd bits. The stored quotient
  // carries the remaining 19 bits of a non-negative int fd, leaving room for
  // a 17-bit cache epoch and a 24-bit slot incarnation in one atomic word.
  uint64_t fd_tag = static_cast<uint32_t>(fd) /
                    static_cast<uint32_t>(HIGH_FD_TYPE_CACHE_SIZE);
  return (fd_tag << HIGH_FD_TAG_SHIFT)
      | (static_cast<uint64_t>(epoch & HIGH_FD_EPOCH_MASK)
         << HIGH_FD_EPOCH_SHIFT)
      | ((incarnation & HIGH_FD_INCARNATION_MASK)
         << FD_TYPE_INCARNATION_SHIFT)
      | static_cast<uint64_t>(type);
}

uint32_t NativeFdClassifier::highFdEntryEpoch(uint64_t entry) {
  return static_cast<uint32_t>((entry >> HIGH_FD_EPOCH_SHIFT)
                               & HIGH_FD_EPOCH_MASK);
}

uint64_t NativeFdClassifier::highFdEntryIncarnation(uint64_t entry) {
  return (entry >> FD_TYPE_INCARNATION_SHIFT) & HIGH_FD_INCARNATION_MASK;
}

bool NativeFdClassifier::highFdEntryMatches(uint64_t entry, int fd,
                                             uint32_t epoch) {
  return highFdEntryMatchesFd(entry, fd)
      && highFdEntryEpoch(entry) == (epoch & HIGH_FD_EPOCH_MASK);
}

bool NativeFdClassifier::highFdEntryMatchesFd(uint64_t entry, int fd) {
  uint64_t fd_tag = static_cast<uint32_t>(fd) /
                    static_cast<uint32_t>(HIGH_FD_TYPE_CACHE_SIZE);
  return (entry >> HIGH_FD_TAG_SHIFT) == fd_tag;
}

int NativeFdClassifier::highFdCacheIndex(int fd) {
  return static_cast<int>(static_cast<uint32_t>(fd) %
                          static_cast<uint32_t>(HIGH_FD_TYPE_CACHE_SIZE));
}

uint8_t NativeFdClassifier::highFdType(int fd, bool revalidate) {
  uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
  if (epoch >= CACHE_EPOCH_LIMIT) {
    uint8_t type = probeFdType(fd);
    return _fd_cache_gen.load(std::memory_order_acquire) == epoch ? type : 0;
  }
  size_t bank = epoch / CACHE_BANK_EPOCHS;
  auto& slot = _high_fd_type_cache[bank * HIGH_FD_TYPE_CACHE_SIZE + highFdCacheIndex(fd)];
  uint64_t cached = slot.load(std::memory_order_acquire);
  if (!revalidate && highFdEntryMatches(cached, fd, epoch)) {
    uint8_t type = static_cast<uint8_t>(cached & FD_TYPE_MASK);
    if (type != 0) {
      return type;
    }
  }

  uint8_t type = probeFdType(fd);
  // probeFdType() returns 0 for transient errors such as EBADF. Do not cache those:
  // the same fd number may later be reused for a socket.
  if (type != 0) {
    uint64_t incarnation = highFdEntryIncarnation(cached);
    if (incarnation == HIGH_FD_INCARNATION_MASK) {
      retireCacheBank(epoch);
      return 0;
    }
    uint64_t desired = highFdEntry(fd, epoch, incarnation + 1, type);
    if (slot.compare_exchange_strong(
            cached, desired, std::memory_order_acq_rel,
            std::memory_order_acquire)) {
      return _fd_cache_gen.load(std::memory_order_acquire) == epoch ? type : 0;
    }
    uint64_t current_epoch = _fd_cache_gen.load(std::memory_order_acquire);
    if (current_epoch / CACHE_BANK_EPOCHS == bank &&
        highFdEntryMatches(cached, fd, current_epoch)) {
      return static_cast<uint8_t>(cached & FD_TYPE_MASK);
    }
    return 0;
  }
  return type;
}

uint8_t NativeFdClassifier::fdType(int fd, bool revalidate) {
  if (fd < 0) {
    return 0;
  }

  uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
  if (!_caches_allocated.load(std::memory_order_acquire) || epoch >= CACHE_EPOCH_LIMIT) {
    uint8_t type = probeFdType(fd);
    return _fd_cache_gen.load(std::memory_order_acquire) == epoch ? type : 0;
  }
  if (static_cast<size_t>(fd) >= static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    return highFdType(fd, revalidate);
  }

  size_t bank = epoch / CACHE_BANK_EPOCHS;
  auto& slot = _fd_type_cache[bank * FD_TYPE_CACHE_SIZE + fd];
  uint64_t cached = slot.load(std::memory_order_acquire);
  if (!revalidate && fdEntryEpoch(cached) == epoch) {
    uint8_t type = static_cast<uint8_t>(cached & FD_TYPE_MASK);
    if (type != 0) {
      return type;
    }
  }

  uint8_t type = probeFdType(fd);
  // probeFdType() returns 0 for transient errors such as EBADF. Do not cache those:
  // the same fd number may later be reused for a socket.
  if (type != 0) {
    uint64_t incarnation = fdEntryIncarnation(cached);
    if (incarnation == FD_TYPE_INCARNATION_MASK) {
      retireCacheBank(epoch);
      return 0;
    }
    uint64_t desired = fdEntry(epoch, incarnation + 1, type);
    if (slot.compare_exchange_strong(
            cached, desired, std::memory_order_acq_rel,
            std::memory_order_acquire)) {
      return _fd_cache_gen.load(std::memory_order_acquire) == epoch ? type : 0;
    }
    uint64_t current_epoch = _fd_cache_gen.load(std::memory_order_acquire);
    if (current_epoch / CACHE_BANK_EPOCHS == bank && fdEntryEpoch(cached) == current_epoch) {
      return static_cast<uint8_t>(cached & FD_TYPE_MASK);
    }
    return 0;
  }
  return type;
}

bool NativeFdClassifier::isStreamSocket(int fd) {
  if (fd < 0) return false;
  ensureCachesAllocated();
  return fdType(fd) == FD_TYPE_STREAM_SOCKET;
}

bool NativeFdClassifier::revalidateStreamSocket(int fd) {
  if (fd < 0) return false;
  ensureCachesAllocated();
  // Bypass a cached verdict, but retain the pre-probe epoch/incarnation CAS.
  // A close/dup during getsockopt must prevent publishing the old fd's type.
  return fdType(fd, true) == FD_TYPE_STREAM_SOCKET;
}

bool NativeFdClassifier::revalidateDatagramSocket(int fd) {
  if (fd < 0) return false;
  ensureCachesAllocated();
  return fdType(fd, true) == FD_TYPE_DATAGRAM_SOCKET;
}

bool NativeFdClassifier::isDatagramSocket(int fd) {
  if (fd < 0) return false;
  ensureCachesAllocated();
  return fdType(fd) == FD_TYPE_DATAGRAM_SOCKET;
}

void NativeFdClassifier::cacheNonSocket(int fd) {
  if (fd < 0) {
    return;
  }
  ensureCachesAllocated();
  cacheFdType(fd, FD_TYPE_NON_SOCKET);
}

void NativeFdClassifier::retireCacheBank(uint64_t epoch) {
  // A competing epoch change already invalidates probes captured before this
  // lifecycle operation. Never reset or reuse the retired bank's words.
  uint64_t next_bank = (epoch / CACHE_BANK_EPOCHS + 1) * CACHE_BANK_EPOCHS;
  _fd_cache_gen.compare_exchange_strong(
      epoch, next_bank, std::memory_order_acq_rel, std::memory_order_acquire);
}

void NativeFdClassifier::clearHighFdType(int fd) {
  int index = highFdCacheIndex(fd);
  uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
  for (;;) {
    if (epoch >= CACHE_EPOCH_LIMIT) {
      clearFdTypeCache();
      return;
    }
    size_t bank = epoch / CACHE_BANK_EPOCHS;
    auto& slot = _high_fd_type_cache[bank * HIGH_FD_TYPE_CACHE_SIZE + index];
    uint64_t cached = slot.load(std::memory_order_acquire);
    if (highFdEntryIncarnation(cached) == HIGH_FD_INCARNATION_MASK) {
      retireCacheBank(epoch);
      return;
    }
    // Colliding descriptors retain their verdict but not their publication word.
    uint64_t incarnation = highFdEntryIncarnation(cached) + 1;
    bool current_entry = highFdEntryEpoch(cached) == (epoch & HIGH_FD_EPOCH_MASK);
    int cached_fd = current_entry
        ? static_cast<int>((cached >> HIGH_FD_TAG_SHIFT) * HIGH_FD_TYPE_CACHE_SIZE + index)
        : fd;
    uint8_t type = current_entry && cached_fd != fd
        ? static_cast<uint8_t>(cached & FD_TYPE_MASK) : 0;
    uint64_t desired = highFdEntry(cached_fd, epoch, incarnation, type);
    if (slot.compare_exchange_weak(cached, desired, std::memory_order_acq_rel,
                                   std::memory_order_acquire)) {
      return;
    }
    epoch = _fd_cache_gen.load(std::memory_order_acquire);
  }
}

void NativeFdClassifier::clearFdType(int fd) {
  if (fd < 0) {
    return;
  }
  if (!_caches_allocated.load(std::memory_order_acquire)) {
    clearFdTypeCache();
    return;
  }
  if (static_cast<size_t>(fd) < static_cast<size_t>(FD_TYPE_CACHE_SIZE)) {
    uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
    for (;;) {
      if (epoch >= CACHE_EPOCH_LIMIT) {
        clearFdTypeCache();
        return;
      }
      size_t bank = epoch / CACHE_BANK_EPOCHS;
      auto& slot = _fd_type_cache[bank * FD_TYPE_CACHE_SIZE + fd];
      uint64_t cached = slot.load(std::memory_order_acquire);
      if (fdEntryIncarnation(cached) == FD_TYPE_INCARNATION_MASK) {
        retireCacheBank(epoch);
        return;
      }
      uint64_t desired = fdEntry(epoch, fdEntryIncarnation(cached) + 1, 0);
      if (slot.compare_exchange_weak(cached, desired, std::memory_order_acq_rel,
                                     std::memory_order_acquire)) {
        return;
      }
      epoch = _fd_cache_gen.load(std::memory_order_acquire);
    }
  } else {
    clearHighFdType(fd);
  }
}

void NativeFdClassifier::clearFdTypeCache() {
  uint64_t epoch = _fd_cache_gen.load(std::memory_order_acquire);
  while (epoch != UINT64_MAX && !_fd_cache_gen.compare_exchange_weak(
      epoch, epoch + 1, std::memory_order_acq_rel, std::memory_order_acquire)) {
  }
}

#endif // __linux__
