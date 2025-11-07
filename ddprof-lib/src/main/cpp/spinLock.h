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

#include <atomic>
#include <functional>

#include "arch_dd.h"

// Cannot use regular mutexes inside signal handler.
// This lock is based on CAS busy loop. GCC atomic builtins imply full barrier.
// Aligned to cache line size (64 bytes) to prevent false sharing between SpinLock instances
class alignas(DEFAULT_CACHE_LINE_SIZE) SpinLock {
private:
  //  0 - unlocked
  //  1 - exclusive lock
  // <0 - shared lock
  std::atomic_int _lock;
  char _padding[DEFAULT_CACHE_LINE_SIZE - sizeof(_lock)];
public:
  explicit constexpr SpinLock(int initial_state = 0) : _lock(initial_state), _padding() {
    static_assert(sizeof(SpinLock) == DEFAULT_CACHE_LINE_SIZE);
  }

  void reset() { _lock = 0; }

  bool tryLock() {
    int expected = 0;
    return _lock.compare_exchange_strong(expected, 1, std::memory_order_acquire, std::memory_order_relaxed);
  }

  void lock() {
    while (!tryLock()) {
      spinPause();
    }
  }

  void unlock() {
    _lock.fetch_sub(1, std::memory_order_release);
  }

  bool tryLockShared() {
    int value;
    // we use relaxed as the compare already offers the guarantees we need
    while ((value = _lock.load(std::memory_order_acquire)) <= 0) {
      if (_lock.compare_exchange_strong(value, value - 1, std::memory_order_acq_rel)) {
        return true;
      }
    }
    return false;
  }

  void lockShared() {
    int value;
    while ((value = _lock.load(std::memory_order_acquire)) > 0 ||
           !_lock.compare_exchange_strong(value, value - 1, std::memory_order_acq_rel)) {
      spinPause();
    }
  }

  void unlockShared() { _lock.fetch_add(1, std::memory_order_release); }
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
  OptionalSharedLockGuard(SpinLock* lock, const std::function<void()>& code) : _lock(lock) {
    if (_lock->tryLockShared()) {
      code();
    } else {
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
