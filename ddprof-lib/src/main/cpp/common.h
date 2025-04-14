#ifndef _COMMON_H
#define _COMMON_H

#include <cstddef>

static constexpr size_t MAX_THREAD_SLOTS = 128;

#ifdef DEBUG
#define TEST_LOG(fmt, ...) do { \
  fprintf(stdout, "[TEST::INFO] " fmt "\n", ##__VA_ARGS__); \
  fflush(stdout); \
} while (0)
#else
#define TEST_LOG(fmt, ...) // No-op in non-debug mode
#endif

#endif // _COMMON_H