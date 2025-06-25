#ifndef _ARCH_DD_H
#define _ARCH_DD_H

#include "arch.h"

#include <stddef.h>

static inline long long atomicInc(volatile long long &var,
                                  long long increment = 1) {
  return __sync_fetch_and_add(&var, increment);
}

static inline u64 loadAcquire(volatile u64 &var) {
  return __atomic_load_n(&var, __ATOMIC_ACQUIRE);
}

static inline size_t loadAcquire(volatile size_t &var) {
  return __atomic_load_n(&var, __ATOMIC_ACQUIRE);
}

static inline void storeRelease(volatile long long &var, long long value) {
  return __atomic_store_n(&var, value, __ATOMIC_RELEASE);
}

static inline void storeRelease(volatile size_t &var, size_t value) {
  return __atomic_store_n(&var, value, __ATOMIC_RELEASE);
}

#endif // _ARCH_DD_H
