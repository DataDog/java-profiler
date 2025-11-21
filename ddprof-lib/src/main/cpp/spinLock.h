/*
 * Copyright 2017 Andrei Pangin
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

#ifndef _SPINLOCK_H
#define _SPINLOCK_H

#include "arch_dd.h"

// Cannot use regular mutexes inside signal handler.
// This lock is based on CAS busy loop. GCC atomic builtins imply full barrier.
// Aligned to cache line size (64 bytes) to prevent false sharing between SpinLock instances
class alignas(DEFAULT_CACHE_LINE_SIZE) SpinLock {
private:
  //  0 - unlocked
  //  1 - exclusive lock
  // <0 - shared lock
  volatile int _lock;
  char _padding[DEFAULT_CACHE_LINE_SIZE - sizeof(_lock)];
public:
  explicit constexpr SpinLock(int initial_state = 0) : _lock(initial_state), _padding() {
    static_assert(sizeof(SpinLock) == DEFAULT_CACHE_LINE_SIZE);
  }

  void reset() { _lock = 0; }

  bool tryLock() { return __sync_bool_compare_and_swap(&_lock, 0, 1); }

  void lock() {
    while (!tryLock()) {
      spinPause();
    }
  }

  void unlock() { __sync_fetch_and_sub(&_lock, 1); }

  bool tryLockShared() {
    int value;
    while ((value = __atomic_load_n(&_lock, __ATOMIC_ACQUIRE)) <= 0) {
      if (__sync_bool_compare_and_swap(&_lock, value, value - 1)) {
        return true;
      }
    }
    return false;
  }

  void lockShared() {
    int value;
    while ((value = __atomic_load_n(&_lock, __ATOMIC_ACQUIRE)) > 0 ||
           !__sync_bool_compare_and_swap(&_lock, value, value - 1)) {
      spinPause();
    }
  }

  void unlockShared() { __sync_fetch_and_add(&_lock, 1); }
};

// RAII guard classes for automatic lock management
class SharedLockGuard {
private:
  SpinLock* _lock;
public:
  explicit SharedLockGuard(SpinLock* lock) : _lock(lock) {
    _lock->lockShared();
  }
  ~SharedLockGuard() {
    _lock->unlockShared();
  }
  // Non-copyable and non-movable
  SharedLockGuard(const SharedLockGuard&) = delete;
  SharedLockGuard& operator=(const SharedLockGuard&) = delete;
  SharedLockGuard(SharedLockGuard&&) = delete;
  SharedLockGuard& operator=(SharedLockGuard&&) = delete;
};

class OptionalSharedLockGuard {
  SpinLock* _lock;
public:
  OptionalSharedLockGuard(SpinLock* lock) : _lock(lock) {
    if (!_lock->tryLockShared()) {
      // Locking failed, no need to unlock.
      _lock = nullptr;
    }
  }
  ~OptionalSharedLockGuard() {
    if (_lock != nullptr) {
      _lock->unlockShared();
    }
  }
  bool ownsLock() { return _lock != nullptr; }

  // Non-copyable and non-movable
  OptionalSharedLockGuard(const OptionalSharedLockGuard&) = delete;
  OptionalSharedLockGuard& operator=(const OptionalSharedLockGuard&) = delete;
  OptionalSharedLockGuard(OptionalSharedLockGuard&&) = delete;
  OptionalSharedLockGuard& operator=(OptionalSharedLockGuard&&) = delete;
};

class ExclusiveLockGuard {
private:
  SpinLock* _lock;
public:
  explicit ExclusiveLockGuard(SpinLock* lock) : _lock(lock) {
    _lock->lock();
  }
  ~ExclusiveLockGuard() {
    _lock->unlock();
  }
  // Non-copyable and non-movable
  ExclusiveLockGuard(const ExclusiveLockGuard&) = delete;
  ExclusiveLockGuard& operator=(const ExclusiveLockGuard&) = delete;
  ExclusiveLockGuard(ExclusiveLockGuard&&) = delete;
  ExclusiveLockGuard& operator=(ExclusiveLockGuard&&) = delete;
};

#endif // _SPINLOCK_H
