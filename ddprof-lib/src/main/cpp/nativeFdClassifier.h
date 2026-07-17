/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _NATIVE_FD_CLASSIFIER_H
#define _NATIVE_FD_CLASSIFIER_H

#include <atomic>
#include <stdint.h>

#if defined(__linux__)

class NativeFdClassifier {
public:
  NativeFdClassifier();

  bool isStreamSocket(int fd);
  bool isDatagramSocket(int fd);
  void cacheNonSocket(int fd);
  void clearFdType(int fd);
  void clearFdTypeCache();

#ifdef UNIT_TEST
  using ProbeOverride = int (*)(int fd, int *so_type, int *probe_errno);
  static void setProbeOverrideForTest(ProbeOverride probe);
  static uint64_t probeCountForTest();
  static void resetProbeCountForTest();
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

  // A low-fd entry atomically couples its cached type to both the profiler
  // cache epoch and that fd's lifecycle incarnation. A probe may publish only
  // if close/dup has not changed the entry it observed before getsockopt().
  std::atomic<uint32_t> _fd_cache_gen{1};
  std::atomic<uint64_t> _fd_type_cache[FD_TYPE_CACHE_SIZE];
  std::atomic<uint64_t> _high_fd_type_cache[HIGH_FD_TYPE_CACHE_SIZE];

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
  uint8_t highFdType(int fd);
  void clearHighFdType(int fd);
  uint8_t fdType(int fd);

#ifdef UNIT_TEST
  static std::atomic<ProbeOverride> _probe_override;
  static std::atomic<uint64_t> _probe_count;
#endif
};

#endif // __linux__

#endif // _NATIVE_FD_CLASSIFIER_H
