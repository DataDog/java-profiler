#ifndef _ARCH_DD_H
#define _ARCH_DD_H

#include "arch.h"

#define COMMA ,

#include <stddef.h>

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

#endif // _ARCH_DD_H
