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
#include "threadLocal.h"
#include "gtest_crash_handler.h"
#include <atomic>
#include <cstdint>
#include <thread>
#include <vector>

static constexpr char THREADLOCAL_TEST_NAME[] = "ThreadLocalTest";

// NOTE on the instances below being namespace-scope `static`:
// ThreadLocal's destructor calls pthread_key_delete() but never resets
// _key_once, so destroying an instance and then constructing another of the
// same type would operate on a deleted key (UB). The production code only ever
// uses `static ThreadLocal<...>` locals (destroyed at process exit), so the
// tests mirror that: one long-lived instance per distinct type. Per-thread
// behaviour is exercised in freshly spawned threads, which start with empty
// thread-specific storage.

// ---- generic pointer specialization: plain set/get, no create/clean ----
static ThreadLocal<intptr_t> g_int_tl;

// ---- lazy-create + cleanup instrumentation ----
static std::atomic<int> g_created{0};
static std::atomic<int> g_freed{0};

static void *create_tracked() {
    g_created.fetch_add(1, std::memory_order_relaxed);
    return new int(1234);
}

static void free_tracked(void *p) {
    g_freed.fetch_add(1, std::memory_order_relaxed);
    delete static_cast<int *>(p);
}

static ThreadLocal<int *, create_tracked, free_tracked> g_tracked_tl;

// ---- double specialization ----
static ThreadLocal<double> g_double_tl;

class ThreadLocalTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<THREADLOCAL_TEST_NAME>();
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

// set() then get() round-trips a value on the same thread.
TEST_F(ThreadLocalTest, Generic_SetGetRoundTrip) {
    g_int_tl.set(42);
    EXPECT_EQ(42, g_int_tl.get());
    g_int_tl.set(-7);
    EXPECT_EQ(-7, g_int_tl.get());
}

// Each thread sees only its own value: storage is per-thread, not shared.
TEST_F(ThreadLocalTest, Generic_PerThreadIsolation) {
    constexpr int kThreads = 8;
    std::atomic<int> ready{0};
    std::atomic<bool> go{false};
    std::vector<std::thread> threads;
    std::atomic<int> mismatches{0};

    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([&, i] {
            // Fresh thread: storage must start empty.
            if (g_int_tl.get() != 0) {
                mismatches.fetch_add(1, std::memory_order_relaxed);
            }
            g_int_tl.set(i + 1);

            // Barrier: every thread writes before any thread reads back, so a
            // shared (buggy) slot would be observably clobbered.
            ready.fetch_add(1, std::memory_order_relaxed);
            while (!go.load(std::memory_order_acquire)) {
            }

            if (g_int_tl.get() != static_cast<intptr_t>(i + 1)) {
                mismatches.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }

    while (ready.load(std::memory_order_relaxed) != kThreads) {
    }
    go.store(true, std::memory_order_release);

    for (auto &t : threads) {
        t.join();
    }
    EXPECT_EQ(0, mismatches.load());
}

// A fresh thread that never called set() reads the zero-initialized default.
TEST_F(ThreadLocalTest, Generic_UnsetIsZero) {
    intptr_t observed = -1;
    std::thread t([&] { observed = g_int_tl.get(); });
    t.join();
    EXPECT_EQ(0, observed);
}

// The create function lazily initializes storage on first get() and is invoked
// exactly once per thread; subsequent get()s return the same pointer.
TEST_F(ThreadLocalTest, Lazy_CreateOncePerThread) {
    g_created.store(0, std::memory_order_relaxed);
    g_freed.store(0, std::memory_order_relaxed);

    int *first = nullptr;
    int *second = nullptr;
    int value = 0;
    std::thread t([&] {
        first = g_tracked_tl.get();
        second = g_tracked_tl.get();
        // Read the payload here: free_tracked() deletes it on thread exit, so
        // dereferencing first/second after join() would be use-after-free.
        value = *first;
    });
    t.join();

    ASSERT_NE(nullptr, first);
    EXPECT_EQ(first, second);          // same instance reused (pointer compare only)
    EXPECT_EQ(1234, value);            // created via create_tracked()
    EXPECT_EQ(1, g_created.load());    // created exactly once
}

// The clean function runs when the owning thread exits, freeing per-thread state.
TEST_F(ThreadLocalTest, Lazy_CleanupOnThreadExit) {
    g_created.store(0, std::memory_order_relaxed);
    g_freed.store(0, std::memory_order_relaxed);

    std::thread t([&] {
        // Touch storage so a value exists to be cleaned up on exit.
        ASSERT_NE(nullptr, g_tracked_tl.get());
    });
    t.join();
    // After join the thread has fully terminated, so its TSD destructor
    // (free_tracked) must have run.
    EXPECT_EQ(1, g_created.load());
    EXPECT_EQ(1, g_freed.load());
}

// Independent threads each create and free their own value.
TEST_F(ThreadLocalTest, Lazy_CleanupAcrossManyThreads) {
    g_created.store(0, std::memory_order_relaxed);
    g_freed.store(0, std::memory_order_relaxed);

    constexpr int kThreads = 16;
    std::vector<std::thread> threads;
    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([] { (void)g_tracked_tl.get(); });
    }
    for (auto &t : threads) {
        t.join();
    }
    EXPECT_EQ(kThreads, g_created.load());
    EXPECT_EQ(kThreads, g_freed.load());
}

// The double specialization preserves the exact bit pattern through the
// u64<->void* round-trip (on 64-bit targets, where a double fits in a pointer).
TEST_F(ThreadLocalTest, Double_RoundTripPreservesValue) {
    static_assert(sizeof(void *) >= sizeof(double),
                  "ThreadLocal<double> requires pointer >= double width");

    const double values[] = {
        0.0,
        1.0,
        -1.0,
        3.141592653589793,
        -2.718281828459045,
        1.7976931348623157e308,   // near DBL_MAX
        2.2250738585072014e-308,  // near DBL_MIN (smallest normal)
        4.9e-324,                 // smallest subnormal
    };

    std::atomic<int> mismatches{0};
    std::thread t([&] {
        for (double v : values) {
            g_double_tl.set(v);
            if (g_double_tl.get() != v) {
                mismatches.fetch_add(1, std::memory_order_relaxed);
            }
        }
    });
    t.join();
    EXPECT_EQ(0, mismatches.load());
}

// An unset double reads back as 0.0 (matches the original `thread_local double = 0`).
TEST_F(ThreadLocalTest, Double_UnsetIsZero) {
    double observed = -1.0;
    std::thread t([&] { observed = g_double_tl.get(); });
    t.join();
    EXPECT_EQ(0.0, observed);
}

// Per-thread accumulation mirrors LivenessTracker's `skipped` usage: each thread
// keeps its own running sum, isolated from the others.
TEST_F(ThreadLocalTest, Double_PerThreadAccumulation) {
    constexpr int kThreads = 8;
    constexpr int kIters = 1000;
    std::atomic<int> mismatches{0};
    std::vector<std::thread> threads;

    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([&, i] {
            const double step = static_cast<double>(i + 1);
            for (int k = 0; k < kIters; ++k) {
                g_double_tl.set(g_double_tl.get() + step);
            }
            if (g_double_tl.get() != step * kIters) {
                mismatches.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    for (auto &t : threads) {
        t.join();
    }
    EXPECT_EQ(0, mismatches.load());
}
