/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef JAVA_PROFILER_STANDARDUTF8_H
#define JAVA_PROFILER_STANDARDUTF8_H

#include <cstddef>
#include <cstdint>
#include <cstring>

// Writes in[0..len) as standard UTF-8 to out (null: measure only), at most cap bytes and never
// splitting a character; returns the byte count. Converts JVM modified UTF-8 (C0 80, 6-byte pairs),
// copies valid UTF-8, and writes U+FFFD or '?' for bad input, so output never exceeds input length.
inline size_t toStandardUtf8(const char *in, size_t len, char *out, size_t cap) {
  const unsigned char *p = reinterpret_cast<const unsigned char *>(in);
  auto cont = [](unsigned char b) { return (b & 0xC0) == 0x80; };
  size_t i = 0;
  size_t n = 0;
  while (i < len) {
    const unsigned char c = p[i];
    const size_t avail = len - i;
    size_t need = 0;  // length of the sequence c leads; 0 when c cannot lead one
    unsigned char lo = 0x80;  // range of the second byte
    unsigned char hi = 0xBF;
    if (c < 0x80) {
      need = 1;
    } else if (c == 0xC0) {
      need = 2;
      hi = 0x80;  // only C0 80, modified UTF-8's U+0000
    } else if (c >= 0xC2 && c <= 0xDF) {
      need = 2;
    } else if ((c & 0xF0) == 0xE0) {
      need = 3;
      lo = c == 0xE0 ? 0xA0 : 0x80;  // ED A0-BF are surrogate halves, handled below
    } else if (c >= 0xF0 && c <= 0xF4) {
      need = 4;
      lo = c == 0xF0 ? 0x90 : 0x80;
      hi = c == 0xF4 ? 0x8F : 0xBF;
    }
    size_t have = 1;
    while (have < need && have < avail &&
           (have == 1 ? p[i + 1] >= lo && p[i + 1] <= hi : cont(p[i + have]))) {
      have++;
    }
    if (have < need && have == avail) {
      break;  // cut off by the end of the input, e.g. a native thread name cut at 15 bytes
    }
    char buf[4];
    const char *src = in + i;
    size_t in_len = need;
    size_t out_len = need;
    if (have < need || need == 0) {
      buf[0] = '?';
      src = buf;
      in_len = out_len = 1;
    } else if (c == 0xC0) {
      buf[0] = '\0';
      src = buf;
      out_len = 1;
    } else if (c == 0xED && p[i + 1] >= 0xA0) {
      const unsigned char *q = p + i + 3;
      const size_t rest = avail - 3;
      if (p[i + 1] <= 0xAF && rest >= 3 && q[0] == 0xED && q[1] >= 0xB0 && q[1] <= 0xBF &&
          cont(q[2])) {
        uint32_t cp = 0x10000 + ((((p[i + 1] & 0x0F) << 6) | (p[i + 2] & 0x3F)) << 10) +
                      (((q[1] & 0x0F) << 6) | (q[2] & 0x3F));
        buf[0] = static_cast<char>(0xF0 | (cp >> 18));
        buf[1] = static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
        buf[2] = static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
        buf[3] = static_cast<char>(0x80 | (cp & 0x3F));
        in_len = 6;
        out_len = 4;
      } else if (p[i + 1] <= 0xAF &&
                 (rest == 0 ||
                  (q[0] == 0xED && (rest == 1 || (rest == 2 && q[1] >= 0xB0 && q[1] <= 0xBF))))) {
        break;  // a pair cut off by the end of the input
      } else {
        buf[0] = static_cast<char>(0xEF);
        buf[1] = static_cast<char>(0xBF);
        buf[2] = static_cast<char>(0xBD);
      }
      src = buf;
    }
    if (n + out_len > cap) {
      break;
    }
    if (out != nullptr) {
      std::memcpy(out + n, src, out_len);
    }
    n += out_len;
    i += in_len;
  }
  return n;
}

#endif
