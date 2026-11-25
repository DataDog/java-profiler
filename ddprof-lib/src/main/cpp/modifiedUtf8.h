/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef JAVA_PROFILER_MODIFIEDUTF8_H
#define JAVA_PROFILER_MODIFIEDUTF8_H

#include <cstddef>
#include <cstdint>
#include <cstring>

// Returns the length of the well-formed modified-UTF-8 sequence at p (1-3 bytes), or 0.
inline size_t modifiedUtf8SequenceLength(const unsigned char *p) {
  auto cont = [](unsigned char b) { return (b & 0xC0) == 0x80; };
  if (p[0] < 0x80) return 1;
  if ((p[0] == 0xC0 && p[1] == 0x80) || (p[0] >= 0xC2 && p[0] <= 0xDF && cont(p[1]))) return 2;
  if ((p[0] & 0xF0) == 0xE0 && cont(p[1]) && cont(p[2]) && (p[0] != 0xE0 || p[1] >= 0xA0)) {
    return 3;
  }
  return 0;
}

// Re-encodes JVMTI's modified UTF-8 as standard UTF-8 into out (3 * max_units bytes, unterminated),
// keeping at most max_units UTF-16 units without splitting a surrogate pair; returns the length.
// Only C0 80 and 6-byte surrogate pairs differ; a lone surrogate or malformed byte becomes U+FFFD.
inline size_t modifiedUtf8ToStandard(const char *name, size_t max_units, char *out) {
  const unsigned char *p = reinterpret_cast<const unsigned char *>(name);
  size_t units = 0;
  size_t length = 0;
  while (*p != '\0' && units < max_units) {
    size_t n = modifiedUtf8SequenceLength(p);
    bool surrogate = n == 3 && p[0] == 0xED && p[1] >= 0xA0;
    if (surrogate && p[1] <= 0xAF && p[3] == 0xED && p[4] >= 0xB0 && p[4] <= 0xBF &&
        (p[5] & 0xC0) == 0x80) {
      if (units + 2 > max_units) {
        break;
      }
      uint32_t c = 0x10000 + ((((p[1] & 0x0F) << 6) | (p[2] & 0x3F)) << 10) +
                   (((p[4] & 0x0F) << 6) | (p[5] & 0x3F));
      out[length++] = static_cast<char>(0xF0 | (c >> 18));
      out[length++] = static_cast<char>(0x80 | ((c >> 12) & 0x3F));
      out[length++] = static_cast<char>(0x80 | ((c >> 6) & 0x3F));
      out[length++] = static_cast<char>(0x80 | (c & 0x3F));
      p += 6;
      units += 2;
      continue;
    }
    if (n == 2 && p[0] == 0xC0) {
      out[length++] = '\0';
    } else if (n == 0 || surrogate) {
      out[length++] = static_cast<char>(0xEF);
      out[length++] = static_cast<char>(0xBF);
      out[length++] = static_cast<char>(0xBD);
      n = n == 0 ? 1 : n;
    } else {
      std::memcpy(out + length, p, n);
      length += n;
    }
    p += n;
    units++;
  }
  return length;
}

#endif
