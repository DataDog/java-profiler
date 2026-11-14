/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVE_FD_CLASSIFIER_H
#define _NATIVE_FD_CLASSIFIER_H

#include <atomic>
#include <mutex>
#include <stdint.h>

#if defined(__linux__)

class NativeFdClassifier {
public:
  NativeFdClassifier();
  ~NativeFdClassifier();

  bool isStreamSocket(int fd);
  bool isDatagramSocket(int fd);
  bool revalidateStreamSocket(int fd);
  bool revalidateDatagramSocket(int fd);
  void cacheNonSocket(int fd);
  void clearFdType(int fd);
  void clearFdTypeCache();

#ifdef UNIT_TEST
  using ProbeOverride = int (*)(int fd, int *so_type, int *probe_errno);
  static void setProbeOverrideForTest(ProbeOverride probe);
  static uint64_t probeCountForTest();
  static void resetProbeCountForTest();
  static uint64_t cacheAllocationCountForTest();
#endif

private:
  static const int FD_TYPE_CACHE_SIZE = 65536;
  static const int HIGH_FD_TYPE_CACHE_SIZE = 4096;
  static const uint64_t FD_TYPE_MASK = 0xf;
  static const int FD_TYPE_INCARNATION_SHIFT = 4;
  static const uint64_t FD_TYPE_INCARNATION_MASK = 0x0fffffff;
  static const int FD_TYPE_EPOCH_SHIFT = 32;
  static const uint64_t HIGH_FD_INCARNATION_MASK = 0x00ffffff;
  static const int HIGH_FD_EPOCH_SHIFT = 28;
  static const uint64_t HIGH_FD_EPOCH_MASK = 0x1ffff;
  static const int HIGH_FD_TAG_SHIFT = 45;
  static const uint8_t FD_TYPE_STREAM_SOCKET = 1;
  static const uint8_t FD_TYPE_DATAGRAM_SOCKET = 2;
  static const uint8_t FD_TYPE_OTHER_SOCKET = 3;
  static const uint8_t FD_TYPE_NON_SOCKET = 4;

  static const uint64_t CACHE_BANK_EPOCHS = HIGH_FD_EPOCH_MASK + 1;
  static const int CACHE_BANKS = 2;
  static const uint64_t CACHE_EPOCH_LIMIT = CACHE_BANKS * CACHE_BANK_EPOCHS;

  // Every publication and lifecycle invalidation advances the incarnation,
  // including same-type observations, so an older probe cannot overwrite them.
  // Never reuse a packed identity: epoch/incarnation exhaustion retires a bank.
  // After both banks retire, probes continue without caching. The full epoch
  // never wraps, and pending probes retain their original bank until returning.
  std::atomic<uint64_t> _fd_cache_gen{1};
  // Lazy, bounded 1088 KiB of entries. Lifecycle invalidation alone must not
  // allocate, and an allocation failure falls back to uncached classification.
  std::once_flag _cache_alloc_once;
  std::atomic<bool> _caches_allocated{false};
  std::atomic<uint64_t>* _fd_type_cache = nullptr;
  std::atomic<uint64_t>* _high_fd_type_cache = nullptr;
  void ensureCachesAllocated();
  void retireCacheBank(uint64_t epoch);

  static uint8_t probeFdType(int fd);
  static uint64_t fdEntry(uint32_t epoch, uint64_t incarnation, uint8_t type);
  static uint32_t fdEntryEpoch(uint64_t entry);
  static uint64_t fdEntryIncarnation(uint64_t entry);
  static uint64_t highFdEntry(int fd, uint32_t epoch, uint64_t incarnation,
                              uint8_t type);
  static uint32_t highFdEntryEpoch(uint64_t entry);
  static uint64_t highFdEntryIncarnation(uint64_t entry);
  static bool highFdEntryMatches(uint64_t entry, int fd, uint32_t gen);
  static bool highFdEntryMatchesFd(uint64_t entry, int fd);
  static int highFdCacheIndex(int fd);
  void cacheFdType(int fd, uint8_t type);
  uint8_t highFdType(int fd, bool revalidate);
  void clearHighFdType(int fd);
  uint8_t fdType(int fd, bool revalidate = false);

#ifdef UNIT_TEST
  static std::atomic<ProbeOverride> _probe_override;
  static std::atomic<uint64_t> _probe_count;
  static std::atomic<uint64_t> _cache_allocations;
#endif
};

#endif // __linux__

#endif // _NATIVE_FD_CLASSIFIER_H
