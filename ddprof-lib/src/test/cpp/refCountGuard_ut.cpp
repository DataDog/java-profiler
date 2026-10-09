/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "refCountGuard.h"
#include <atomic>
#include <chrono>
#include <cstring>
#include <gtest/gtest.h>
#include <thread>

// ── Activation-window regression tests ────────────────────────────────────
//
// The non-reentrant RefCountGuard constructor stores active_ptr (RELEASE)
// BEFORE incrementing count (RELEASE).  Between those two stores the slot has
// count==0 but active_ptr!=null: the "activation window".
//
// The wait functions must also check active_ptr when count==0, otherwise they
// return early and the caller can free the resource while the holder is still in
// the window and will access it after the free (heap-use-after-free).
//
// These tests exercise exactly that scenario:
//   1. Holder stores active_ptr, sleeps to keep the window open.
//   2. Cleaner calls the wait function, then frees the resource.
//   3. Holder wakes, increments count (exits window), writes to the resource.
//
// Without the fix: cleaner's wait returns immediately (count==0 → skip slot),
//   freeing the resource before holder uses it.
//   ASAN reports: heap-use-after-free on holder's write.
//   TSAN reports: data race / use-after-free between the delete and the write.
//
// With the fix: cleaner's wait observes active_ptr!=null and blocks until
//   holder clears it (after finishing the write), so the free is safe.
//
// NOTE: These tests bypass getThreadRefCountSlot() and manipulate
//   refcount_slots[] directly.  They use the last slot (MAX_THREADS-1) which
//   is unlikely to be claimed by any real thread during the test, and always
//   restore it to the clean state on exit.

class RefCountGuardActivationWindowTest : public ::testing::Test {
protected:
    static constexpr int TEST_SLOT = RefCountGuard::MAX_THREADS - 1;

    void SetUp() override {
        auto& slot = RefCountGuard::refcount_slots[TEST_SLOT];
        __atomic_store_n(&slot.count, 0u, __ATOMIC_SEQ_CST);
        __atomic_store_n(&slot.active_ptr, nullptr, __ATOMIC_SEQ_CST);
        for (int i = 0; i < RefCountSlot::OUTER_STACK_DEPTH; ++i) {
            __atomic_store_n(&slot.outer_stack[i], nullptr, __ATOMIC_SEQ_CST);
        }
    }

    void TearDown() override {
        // Restore to clean state regardless of test outcome.
        auto& slot = RefCountGuard::refcount_slots[TEST_SLOT];
        __atomic_store_n(&slot.count, 0u, __ATOMIC_SEQ_CST);
        __atomic_store_n(&slot.active_ptr, nullptr, __ATOMIC_SEQ_CST);
    }
};

// waitForRefCountToClear(ptr) must not return while the target ptr is in the activation window.
TEST_F(RefCountGuardActivationWindowTest, WaitForSpecificBlocksDuringActivationWindow) {
    auto& slot = RefCountGuard::refcount_slots[TEST_SLOT];

    char* resource = new char[64];
    std::memset(resource, 0xAB, 64);

    volatile char* stable = resource;

    std::atomic<bool> window_entered{false};

    std::thread holder([&] {
        __atomic_store_n(&slot.active_ptr, resource, __ATOMIC_RELEASE);
        window_entered.store(true, std::memory_order_release);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        __atomic_fetch_add(&slot.count, 1u, __ATOMIC_RELEASE);

        *stable = 0xCD;

        __atomic_fetch_sub(&slot.count, 1u, __ATOMIC_RELEASE);
        __atomic_store_n(&slot.active_ptr, nullptr, __ATOMIC_RELEASE);
    });

    while (!window_entered.load(std::memory_order_acquire)) { /* spin */ }

    RefCountGuard::waitForRefCountToClear(resource);

    delete[] resource;
    resource = nullptr;

    holder.join();
}

// ── tryWaitForRefCountsToClear ────────────────────────────────────────────
//
// A guard held on a thread blocked until the test lets it go.

namespace {

class HeldGuard {
public:
    explicit HeldGuard(void* resource) : _thread([this, resource] {
        RefCountGuard guard(resource);
        _held.store(true, std::memory_order_release);
        while (!_release.load(std::memory_order_acquire)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }) {
        while (!_held.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
    }

    ~HeldGuard() {
        _release.store(true, std::memory_order_release);
        _thread.join();
    }

private:
    std::atomic<bool> _held{false};
    std::atomic<bool> _release{false};
    std::thread _thread;
};

} // namespace

TEST(RefCountGuardTryWaitTest, ReturnsTrueWhenNoGuardReferencesTargets) {
    int a, b;
    void* const targets[] = {&a, &b};
    EXPECT_TRUE(RefCountGuard::tryWaitForRefCountsToClear(targets, 2));
}

// Guards on unrelated resources must neither delay nor fail the drain - a
// global drain would time out here.
TEST(RefCountGuardTryWaitTest, IgnoresGuardsOnOtherResources) {
    int target, unrelated;
    HeldGuard held(&unrelated);
    void* const targets[] = {&target};
    auto start = std::chrono::steady_clock::now();
    EXPECT_TRUE(RefCountGuard::tryWaitForRefCountsToClear(targets, 1));
    EXPECT_LT(std::chrono::steady_clock::now() - start, std::chrono::milliseconds(100));
}

// A guard on any one of the targets keeps the drain from succeeding.
TEST(RefCountGuardTryWaitTest, ReturnsFalseWhileAnyTargetIsGuarded) {
    int a, b, c;
    HeldGuard held(&b);
    void* const targets[] = {&a, &b, &c};
    EXPECT_FALSE(RefCountGuard::tryWaitForRefCountsToClear(targets, 3));
}

// The drain succeeds once the last guard on a target is released mid-wait.
TEST(RefCountGuardTryWaitTest, ReturnsTrueOnceGuardIsReleased) {
    int target;
    void* const targets[] = {&target};
    std::thread releaser;
    {
        auto held = new HeldGuard(&target);
        releaser = std::thread([held] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            delete held;
        });
    }
    EXPECT_TRUE(RefCountGuard::tryWaitForRefCountsToClear(targets, 1));
    releaser.join();
}
