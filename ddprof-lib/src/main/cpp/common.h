/*
 * Copyright 2026 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _COMMON_H
#define _COMMON_H

#include <cstddef>
#include <cstdio>

// Sanitizer detection: define ASAN_ENABLED / TSAN_ENABLED uniformly across
// toolchains.  clang exposes sanitizers only via __has_feature(...), while gcc
// defines __SANITIZE_ADDRESS__ / __SANITIZE_THREAD__.  Guarding code on the gcc
// macros alone silently drops every sanitizer annotation under clang (the CI
// sanitizer compiler), so always go through these macros instead.
#if defined(__has_feature)
#  if __has_feature(address_sanitizer)
#    ifndef ASAN_ENABLED
#      define ASAN_ENABLED 1
#    endif
#  endif
#  if __has_feature(thread_sanitizer)
#    ifndef TSAN_ENABLED
#      define TSAN_ENABLED 1
#    endif
#  endif
#endif
#ifdef __SANITIZE_ADDRESS__
#  ifndef ASAN_ENABLED
#    define ASAN_ENABLED 1
#  endif
#endif
#ifdef __SANITIZE_THREAD__
#  ifndef TSAN_ENABLED
#    define TSAN_ENABLED 1
#  endif
#endif

// Knuth's multiplicative constant (golden ratio * 2^64 for 64-bit)
// Used for hash distribution in various components
constexpr size_t KNUTH_MULTIPLICATIVE_CONSTANT = 0x9e3779b97f4a7c15ULL;

#ifdef DEBUG
    #include <cerrno>
    #include <cstdarg>
    #include <unistd.h>

    // Writes one "[TEST::INFO] ..." line to file descriptor 1. Callable from
    // signal handlers: it formats into a stack buffer and emits the line with
    // write(2), so unlike stdio it takes no stdout lock (a handler that
    // interrupts its own thread inside fprintf/fflush would wait on that lock
    // forever). glibc's vsnprintf() does not lock either. One write() of a line
    // of at most PIPE_BUF bytes is atomic on a pipe, which is what the tests
    // reading these lines from child processes rely on. Longer lines are cut.
    __attribute__((format(printf, 1, 2)))
    static inline void testLog(const char* fmt, ...) {
      int saved_errno = errno;
      char buf[1024];
      va_list args;
      va_start(args, fmt);
      int len = vsnprintf(buf, sizeof(buf) - 1, fmt, args);
      va_end(args);
      if (len >= 0) {
        if ((size_t)len > sizeof(buf) - 2) {
          len = (int)sizeof(buf) - 2;
        }
        buf[len++] = '\n';
        for (const char* p = buf; len > 0;) {
          ssize_t written = write(STDOUT_FILENO, p, (size_t)len);
          if (written < 0 && errno == EINTR) {
            continue;
          }
          if (written <= 0) {
            break;
          }
          p += written;
          len -= (int)written;
        }
      }
      errno = saved_errno;
    }

    #define DEBUG_ONLY(s) s
    #define TEST_LOG(fmt, ...) testLog("[TEST::INFO] " fmt, ##__VA_ARGS__)
#else
    #define DEBUG_ONLY(s)
    #define TEST_LOG(fmt, ...) // No-op in non-debug mode
#endif

// Same gate as assert(): use for state that only assert() reads. Keying it on
// DEBUG instead would break builds that keep asserts but do not define DEBUG
// (the gtest release build strips -DNDEBUG without adding -DDEBUG).
#ifndef NDEBUG
    #define ASSERT_ONLY(s) s
#else
    #define ASSERT_ONLY(s)
#endif

#ifdef __FAULT_INJECTION__
    #define FAULT_INJECTION_ONLY(s) s
#else
    #define FAULT_INJECTION_ONLY(s)
#endif

// Lightweight stderr warning that does not depend on the Log subsystem.
// Safe to call from low-level code where Log may not be initialized.
#define LOG_WARN(fmt, ...) do { \
  fprintf(stderr, "[ddprof] [WARN] " fmt "\n", ##__VA_ARGS__); \
} while (0)

#endif // _COMMON_H