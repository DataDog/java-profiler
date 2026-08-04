/*
 * Copyright 2026 Datadog, Inc
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

#include <gtest/gtest.h>
#include "spinLock.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include <atomic>
#include <thread>

static constexpr char SPINLOCK_TEST_NAME[] = "SpinLockTest";

class SpinLockTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<SPINLOCK_TEST_NAME>();
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }

    SpinLock lock;
};

// OptionalSharedLockGuard acquires on a free lock and releases on destruction.
TEST_F(SpinLockTest, OptionalGuard_UncontendedAcquire) {
    {
        OptionalSharedLockGuard g(&lock);
        EXPECT_TRUE(g.ownsLock());
    }
    // After destruction the lock must be back to 0 (unlocked).
    // Verify by taking an exclusive lock — would spin forever if still shared.
    EXPECT_TRUE(lock.tryLock());
    lock.unlock();
}

// When an exclusive lock is held, tryLockShared returns false immediately
// (first load sees _lock == 1 > 0, exits without spinning).
TEST_F(SpinLockTest, OptionalGuard_ExclusiveHeld_ImmediateReturn) {
    lock.lock();
    OptionalSharedLockGuard g(&lock, 1000000);
    EXPECT_FALSE(g.ownsLock());
    lock.unlock();
}

// The spin budget must be honoured: even with a tiny budget the constructor
// returns (does not hang) when readers are continuously racing the CAS.
TEST_F(SpinLockTest, OptionalGuard_SpinBudgetBound) {
    // A background contender thread rapidly locks/unlocks shared to create
    // CAS contention on _lock; the guard must return without hanging.
    std::atomic<bool> stop{false};

    // Background thread hammers shared lock/unlock to create CAS contention.
    std::thread contender([&] {
        while (!stop.load(std::memory_order_relaxed)) {
            lock.lockShared();
            lock.unlockShared();
        }
    });

    // With a very small budget the guard must return promptly, not hang.
    for (int i = 0; i < 1000; ++i) {
        OptionalSharedLockGuard g(&lock, 8);
        // ownsLock() may be true or false depending on timing — we only assert
        // the constructor returned (i.e. we reach here without hanging).
        (void)g.ownsLock();
    }

    stop.store(true, std::memory_order_relaxed);
    contender.join();
}

// Verifies that the budget is enforced: with an exclusive lock held,
// tryLockShared(N) must return false regardless of N.
TEST_F(SpinLockTest, OptionalGuard_BudgetEnforced_ExclusivePath) {
    lock.lock();
    // With any budget, exclusive lock causes immediate false return.
    EXPECT_FALSE(lock.tryLockShared(1));
    EXPECT_FALSE(lock.tryLockShared(1000));
    EXPECT_FALSE(lock.tryLockShared(SpinLock::DEFAULT_SHARED_SPIN_BUDGET));
    lock.unlock();
}

// Multiple shared guards can be held simultaneously (readers don't starve each other).
TEST_F(SpinLockTest, OptionalGuard_SharedReentrancy) {
    OptionalSharedLockGuard g1(&lock);
    OptionalSharedLockGuard g2(&lock);
    EXPECT_TRUE(g1.ownsLock());
    EXPECT_TRUE(g2.ownsLock());
    // Exclusive try must fail while shared locks are held.
    EXPECT_FALSE(lock.tryLock());
}

// tryLockShared() (unbounded) still works correctly alongside the bounded overload.
TEST_F(SpinLockTest, TryLockShared_ExclusiveHeld_ReturnsFalse) {
    lock.lock();
    EXPECT_FALSE(lock.tryLockShared());
    lock.unlock();
}

TEST_F(SpinLockTest, TryLockShared_Free_ReturnsTrue) {
    EXPECT_TRUE(lock.tryLockShared());
    lock.unlockShared();
}
