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
  void clearFdType(int fd);
  void clearFdTypeCache();

private:
  static const int FD_TYPE_CACHE_SIZE = 65536;
  static const uint32_t FD_TYPE_MASK = 0xf;
  static const uint32_t FD_TYPE_GEN_SHIFT = 4;
  static const uint8_t FD_TYPE_STREAM_SOCKET = 1;
  static const uint8_t FD_TYPE_DATAGRAM_SOCKET = 2;
  static const uint8_t FD_TYPE_OTHER_SOCKET = 3;
  static const uint8_t FD_TYPE_NON_SOCKET = 4;

  std::atomic<uint32_t> _fd_cache_gen{1};
  std::atomic<uint32_t> _fd_type_cache[FD_TYPE_CACHE_SIZE];

  uint8_t fdType(int fd);
};

#endif // __linux__

#endif // _NATIVE_FD_CLASSIFIER_H
