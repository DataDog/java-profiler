/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _COUNTINGALLOCATOR_H
#define _COUNTINGALLOCATOR_H

#include "nativeMem.h"
#include <cstddef>
#include <new>

// A stateless, C++11-Allocator-conformant wrapper around ::operator new /
// ::operator delete that records every allocation/deallocation into the given
// NativeMem category. STL containers rebind the supplied Allocator<value_type>
// to their actual node type before calling allocate(), so this yields the
// exact real per-node byte count the implementation uses -- not an estimate.
template <typename T, NativeMemCategory Cat>
class CountingAllocator {
public:
  using value_type = T;

  CountingAllocator() noexcept = default;
  template <typename U>
  CountingAllocator(const CountingAllocator<U, Cat> &) noexcept {}

  T *allocate(std::size_t n) {
    T *p = static_cast<T *>(::operator new(n * sizeof(T)));
    NativeMem::record(Cat, (long long)(n * sizeof(T)));
    return p;
  }

  void deallocate(T *p, std::size_t n) noexcept {
    NativeMem::record(Cat, -(long long)(n * sizeof(T)));
    ::operator delete(p);
  }

  template <typename U>
  struct rebind {
    using other = CountingAllocator<U, Cat>;
  };
};

template <typename T, NativeMemCategory Cat>
inline bool operator==(const CountingAllocator<T, Cat> &,
                        const CountingAllocator<T, Cat> &) {
  return true;
}

template <typename T, NativeMemCategory Cat>
inline bool operator!=(const CountingAllocator<T, Cat> &,
                        const CountingAllocator<T, Cat> &) {
  return false;
}

#endif // _COUNTINGALLOCATOR_H
