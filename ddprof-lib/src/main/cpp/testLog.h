/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _TESTLOG_H
#define _TESTLOG_H

// TEST_LOG's line writer (see common.h). It runs in signal handlers, so it
// neither allocates nor locks: no stdio, and no libc formatting, whose
// conversions may allocate (glibc's floating-point and wide-character paths,
// BSD's gdtoa) or read locale state. It formats with its own printf subset
// into a stack buffer and emits the line with one write(2).

#include <cerrno>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <sys/types.h>
#include <unistd.h>

namespace test_log {

// Longest line written, newline included. One write() of at most PIPE_BUF
// bytes is atomic on a pipe, so concurrent lines never interleave for the
// tests that read them from a child process; 512 is the POSIX minimum of
// PIPE_BUF (and macOS's value). Longer lines are cut.
static const size_t MAX_LINE = 512;

struct Out {
  char* p;
  char* end;  // one past the last byte that may hold text

  void put(char c) {
    if (p < end) {
      *p++ = c;
    }
  }
  void put(const char* s, size_t n) {
    for (size_t i = 0; i < n; i++) {
      put(s[i]);
    }
  }
  void pad(char c, int n) {
    for (; n > 0; n--) {
      put(c);
    }
  }
};

struct Spec {
  bool left = false;  // '-'
  bool zero = false;  // '0'
  bool plus = false;  // '+'
  bool space = false; // ' '
  int width = 0;
  int precision = -1;
};

// `digits` (already converted, most significant first) with an optional
// sign or "0x" prefix, padded to the spec's width.
static inline void putPadded(Out& out, const Spec& spec, const char* prefix, size_t prefix_len,
                             const char* digits, size_t len) {
  int fill = spec.width - (int)(prefix_len + len);
  if (!spec.left && !spec.zero) {
    out.pad(' ', fill);
  }
  out.put(prefix, prefix_len);
  if (!spec.left && spec.zero) {
    out.pad('0', fill);
  }
  out.put(digits, len);
  if (spec.left) {
    out.pad(' ', fill);
  }
}

static inline size_t toDigits(unsigned long long v, unsigned base, bool upper, char* buf) {
  const char* set = upper ? "0123456789ABCDEF" : "0123456789abcdef";
  char tmp[24];
  size_t n = 0;
  do {
    tmp[n++] = set[v % base];
    v /= base;
  } while (v != 0);
  for (size_t i = 0; i < n; i++) {
    buf[i] = tmp[n - 1 - i];
  }
  return n;
}

static inline void putInteger(Out& out, const Spec& spec, unsigned long long magnitude, bool negative,
                              unsigned base, bool upper) {
  char digits[24];
  size_t len = toDigits(magnitude, base, upper, digits);
  char sign = negative ? '-' : spec.plus ? '+' : spec.space ? ' ' : '\0';
  putPadded(out, spec, &sign, sign != '\0' ? 1 : 0, digits, len);
}

// Fixed-point %f for the magnitudes TEST_LOG prints (durations, sizes);
// values of 1e18 or more come out as "big".
static inline void putFloat(Out& out, const Spec& spec, double v) {
  if (v != v) {
    putPadded(out, spec, "", 0, "nan", 3);
    return;
  }
  bool negative = v < 0;
  if (negative) {
    v = -v;
  }
  char sign = negative ? '-' : spec.plus ? '+' : spec.space ? ' ' : '\0';
  size_t sign_len = sign != '\0' ? 1 : 0;
  if (!(v < 1e18)) {
    const char* word = v > 1e308 ? "inf" : "big";
    putPadded(out, spec, &sign, sign_len, word, 3);
    return;
  }
  int precision = spec.precision < 0 ? 6 : spec.precision > 9 ? 9 : spec.precision;
  unsigned long long scale = 1;
  for (int i = 0; i < precision; i++) {
    scale *= 10;
  }
  unsigned long long whole = (unsigned long long)v;
  unsigned long long frac = (unsigned long long)((v - (double)whole) * (double)scale + 0.5);
  if (frac >= scale) {
    whole++;
    frac -= scale;
  }
  char digits[48];
  size_t len = toDigits(whole, 10, false, digits);
  if (precision > 0) {
    digits[len++] = '.';
    char fdigits[24];
    size_t flen = toDigits(frac, 10, false, fdigits);
    for (size_t i = flen; i < (size_t)precision; i++) {
      digits[len++] = '0';
    }
    for (size_t i = 0; i < flen; i++) {
      digits[len++] = fdigits[i];
    }
  }
  putPadded(out, spec, &sign, sign_len, digits, len);
}

enum Length { NONE, HH, H, L, LL, Z, J, T };

static inline long long signedArg(va_list& args, Length length) {
  switch (length) {
    case L: return va_arg(args, long);
    case LL: return va_arg(args, long long);
    case Z: return va_arg(args, ssize_t);
    case J: return va_arg(args, intmax_t);
    case T: return va_arg(args, ptrdiff_t);
    case HH: return (signed char)va_arg(args, int);
    case H: return (short)va_arg(args, int);
    default: return va_arg(args, int);
  }
}

static inline unsigned long long unsignedArg(va_list& args, Length length) {
  switch (length) {
    case L: return va_arg(args, unsigned long);
    case LL: return va_arg(args, unsigned long long);
    case Z: return va_arg(args, size_t);
    case J: return va_arg(args, uintmax_t);
    case T: return (unsigned long long)va_arg(args, ptrdiff_t);
    case HH: return (unsigned char)va_arg(args, unsigned int);
    case H: return (unsigned short)va_arg(args, unsigned int);
    default: return va_arg(args, unsigned int);
  }
}

// The printf subset TEST_LOG's callers use: flags "-0+ ", width and
// precision (numbers or '*'), lengths hh h l ll z j t, and conversions
// d i u x X o p s c f %. Anything else is copied through as written.
static inline void format(Out& out, const char* fmt, va_list& args) {
  while (*fmt != '\0') {
    if (*fmt != '%') {
      out.put(*fmt++);
      continue;
    }
    const char* start = fmt++;
    Spec spec;
    for (;; fmt++) {
      if (*fmt == '-') spec.left = true;
      else if (*fmt == '0') spec.zero = true;
      else if (*fmt == '+') spec.plus = true;
      else if (*fmt == ' ') spec.space = true;
      else if (*fmt != '#') break;
    }
    if (*fmt == '*') {
      spec.width = va_arg(args, int);
      if (spec.width < 0) {
        spec.left = true;
        spec.width = -spec.width;
      }
      fmt++;
    } else {
      for (; *fmt >= '0' && *fmt <= '9'; fmt++) {
        spec.width = spec.width * 10 + (*fmt - '0');
      }
    }
    if (*fmt == '.') {
      fmt++;
      spec.precision = 0;
      if (*fmt == '*') {
        spec.precision = va_arg(args, int);
        fmt++;
      } else {
        for (; *fmt >= '0' && *fmt <= '9'; fmt++) {
          spec.precision = spec.precision * 10 + (*fmt - '0');
        }
      }
    }
    Length length = NONE;
    if (*fmt == 'h') {
      length = fmt[1] == 'h' ? HH : H;
      fmt += length == HH ? 2 : 1;
    } else if (*fmt == 'l') {
      length = fmt[1] == 'l' ? LL : L;
      fmt += length == LL ? 2 : 1;
    } else if (*fmt == 'z') {
      length = Z;
      fmt++;
    } else if (*fmt == 'j') {
      length = J;
      fmt++;
    } else if (*fmt == 't') {
      length = T;
      fmt++;
    }
    if (spec.left) {
      spec.zero = false;
    }
    switch (*fmt) {
      case 'd':
      case 'i': {
        long long v = signedArg(args, length);
        unsigned long long magnitude = v < 0 ? 0ULL - (unsigned long long)v : (unsigned long long)v;
        putInteger(out, spec, magnitude, v < 0, 10, false);
        break;
      }
      case 'u':
        putInteger(out, spec, unsignedArg(args, length), false, 10, false);
        break;
      case 'x':
      case 'X':
        putInteger(out, spec, unsignedArg(args, length), false, 16, *fmt == 'X');
        break;
      case 'o':
        putInteger(out, spec, unsignedArg(args, length), false, 8, false);
        break;
      case 'p': {
        const void* p = va_arg(args, const void*);
        if (p == nullptr) {
          putPadded(out, spec, "", 0, "(nil)", 5);
        } else {
          char digits[24];
          size_t len = toDigits((unsigned long long)(uintptr_t)p, 16, false, digits);
          putPadded(out, spec, "0x", 2, digits, len);
        }
        break;
      }
      case 's': {
        const char* s = va_arg(args, const char*);
        if (s == nullptr) {
          s = "(null)";
        }
        size_t len = 0;
        while (s[len] != '\0' && (spec.precision < 0 || len < (size_t)spec.precision)) {
          len++;
        }
        Spec text = spec;
        text.zero = false;
        putPadded(out, text, "", 0, s, len);
        break;
      }
      case 'c': {
        char c = (char)va_arg(args, int);
        Spec text = spec;
        text.zero = false;
        putPadded(out, text, "", 0, &c, 1);
        break;
      }
      case 'f':
      case 'F':
        putFloat(out, spec, va_arg(args, double));
        break;
      case '%':
        out.put('%');
        break;
      default:
        // Unknown conversion: copy it through, so the line shows what went
        // unformatted. Its argument, if any, is not consumed.
        out.put(start, (size_t)(fmt - start) + (*fmt != '\0' ? 1 : 0));
        break;
    }
    if (*fmt != '\0') {
      fmt++;
    }
  }
}

}  // namespace test_log

// Writes the formatted text and a newline to file descriptor 1 as one
// write(2), preserving errno for the code a signal handler interrupted.
__attribute__((format(printf, 1, 2)))
static inline void testLog(const char* fmt, ...) {
  int saved_errno = errno;
  char buf[test_log::MAX_LINE];
  test_log::Out out = {buf, buf + sizeof(buf) - 1};  // keep room for '\n'
  va_list args;
  va_start(args, fmt);
  test_log::format(out, fmt, args);
  va_end(args);
  *out.p++ = '\n';
  size_t len = (size_t)(out.p - buf);
  for (const char* p = buf; len > 0;) {
    ssize_t written = write(STDOUT_FILENO, p, len);
    if (written < 0 && errno == EINTR) {
      continue;
    }
    if (written <= 0) {
      break;
    }
    p += written;
    len -= (size_t)written;
  }
  errno = saved_errno;
}

#endif // _TESTLOG_H
