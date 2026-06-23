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
#define TEST_LOG(fmt, ...) do { \
  fprintf(stdout, "[TEST::INFO] " fmt "\n", ##__VA_ARGS__); \
  fflush(stdout); \
} while (0)
#else
#define TEST_LOG(fmt, ...) // No-op in non-debug mode
#endif

// Lightweight stderr warning that does not depend on the Log subsystem.
// Safe to call from low-level code where Log may not be initialized.
#define LOG_WARN(fmt, ...) do { \
  fprintf(stderr, "[ddprof] [WARN] " fmt "\n", ##__VA_ARGS__); \
} while (0)

#endif // _COMMON_H