/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include "spinLock.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Unit tests for tryLockSharedBounded() and BoundedOptionalSharedLockGuard —
// the signal-safe locking API introduced to replace unbounded spinning in
// hotspotSupport.cpp (classMapTrySharedGuard()).

static constexpr char SPINLOCK_BOUNDED_TEST_NAME[] = "SpinLockBounded";

namespace {

class SpinLockBoundedSetup {
public:
    SpinLockBoundedSetup() {
        installGtestCrashHandler<SPINLOCK_BOUNDED_TEST_NAME>();
    }
    ~SpinLockBoundedSetup() {
        restoreDefaultSignalHandlers();
    }
};

static SpinLockBoundedSetup spinlock_bounded_global_setup;

} // namespace

TEST(SpinLockBounded, BoundedTryLockSucceedsOnFreeLock) {
    SpinLock lock;
    EXPECT_TRUE(lock.tryLockSharedBounded());
    lock.unlockShared();
}

TEST(SpinLockBounded, BoundedTryLockFailsWhenExclusiveLockHeld) {
    SpinLock lock;
    lock.lock();
    EXPECT_FALSE(lock.tryLockSharedBounded());
    lock.unlock();
}

// Multiple shared holders must coexist — bounded acquire must not treat a
// concurrent reader's negative _lock value as an exclusive lock.
TEST(SpinLockBounded, BoundedTryLockAllowsMultipleSharedHolders) {
    SpinLock lock;
    ASSERT_TRUE(lock.tryLockSharedBounded());
    EXPECT_TRUE(lock.tryLockSharedBounded());
    lock.unlockShared();
    lock.unlockShared();
}

TEST(SpinLockBounded, BoundedGuardOwnsLockWhenFree) {
    SpinLock lock;
    BoundedOptionalSharedLockGuard guard(&lock);
    EXPECT_TRUE(guard.ownsLock());
}

// When the exclusive lock is held the guard must not own the lock, and its
// destructor must not accidentally release the exclusive lock.
TEST(SpinLockBounded, BoundedGuardFailsWhenExclusiveLockHeld) {
    SpinLock lock;
    lock.lock();
    {
        BoundedOptionalSharedLockGuard guard(&lock);
        EXPECT_FALSE(guard.ownsLock());
    }
    // Exclusive lock must still be held — unlock() must succeed exactly once.
    lock.unlock();
}

// After the guard goes out of scope the lock must be fully released so that an
// exclusive acquire succeeds.
TEST(SpinLockBounded, BoundedGuardReleasesLockOnDestruction) {
    SpinLock lock;
    {
        BoundedOptionalSharedLockGuard guard(&lock);
        ASSERT_TRUE(guard.ownsLock());
    }
    EXPECT_TRUE(lock.tryLock());
    lock.unlock();
}

// Stress: concurrent BoundedOptionalSharedLockGuard readers vs an exclusive
// locker. Mirrors the classMapTrySharedGuard() signal-handler path vs the
// Profiler::dump path, using the RAII type that hotspotSupport.cpp now uses.
TEST(SpinLockBounded, BoundedGuardConcurrentWithExclusiveLock) {
    SpinLock lock;
    constexpr int kReaders = 4;
    const auto kDuration = std::chrono::milliseconds(300);

    std::atomic<bool> stop{false};
    std::atomic<long> total_acquired{0};
    std::atomic<long> total_skipped{0};
    std::atomic<long> total_exclusive{0};

    std::vector<std::thread> readers;
    readers.reserve(kReaders);
    for (int i = 0; i < kReaders; ++i) {
        readers.emplace_back([&]() {
            while (!stop.load(std::memory_order_relaxed)) {
                BoundedOptionalSharedLockGuard guard(&lock);
                if (guard.ownsLock()) {
                    total_acquired.fetch_add(1, std::memory_order_relaxed);
                } else {
                    total_skipped.fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    }

    std::thread exclusive_thread([&]() {
        while (!stop.load(std::memory_order_relaxed)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            lock.lock();
            lock.unlock();
            total_exclusive.fetch_add(1, std::memory_order_relaxed);
        }
    });

    std::this_thread::sleep_for(kDuration);
    stop.store(true, std::memory_order_relaxed);
    for (auto& t : readers) t.join();
    exclusive_thread.join();

    EXPECT_GT(total_acquired.load(), 0L);
    EXPECT_GT(total_exclusive.load(), 0L);
}
