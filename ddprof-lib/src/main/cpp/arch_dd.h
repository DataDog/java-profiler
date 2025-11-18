#ifndef _ARCH_DD_H
#define _ARCH_DD_H

#include "arch.h"

#define COMMA ,

#include <stddef.h>
#include <stdlib.h>
#include <cassert>

constexpr int DEFAULT_CACHE_LINE_SIZE = 64;

static inline long long atomicInc(volatile long long &var,
                                  long long increment = 1) {
  return __sync_fetch_and_add(&var, increment);
}

template <typename T>
static inline long long atomicIncRelaxed(volatile T &var,
                                         T increment = 1) {
  return __atomic_fetch_add(&var, increment, __ATOMIC_RELAXED);
}

// Atomic load/store (unordered)
template <typename T>
static inline T load(volatile T& var) {
    return __atomic_load_n(&var, __ATOMIC_RELAXED);
}

template <typename T>
static inline void store(volatile T& var, T value) {
  return __atomic_store_n(&var, value, __ATOMIC_RELAXED);
}


// Atomic load-acquire/release-store
template <typename T>
static inline T loadAcquire(volatile T& var) {
  return __atomic_load_n(&var, __ATOMIC_ACQUIRE);
}

template <typename T>
static inline void storeRelease(volatile T& var, T value) {
  return __atomic_store_n(&var, value, __ATOMIC_RELEASE);
}

inline bool is_power_of_2(size_t size) {
    return size > 0 && (size & (size - 1)) == 0;
}

template <typename T>
inline bool is_aligned(const T* ptr, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    // Convert the pointer to an integer type
    auto iptr = reinterpret_cast<uintptr_t>(ptr);

    // Check if the integer value is a multiple of the alignment
    return (iptr & ~(alignment - 1) == 0);
}

inline size_t align_down(size_t size, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    return size & ~(alignment - 1);
}

inline size_t align_up(size_t size, size_t alignment) noexcept {
    assert(is_power_of_2(alignment));
    return align_down(size + alignment - 1, alignment);
}

#endif // _ARCH_DD_H
