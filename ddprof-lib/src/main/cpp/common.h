#ifndef _COMMON_H
#define _COMMON_H

#include <cstddef>

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

#endif // _COMMON_H