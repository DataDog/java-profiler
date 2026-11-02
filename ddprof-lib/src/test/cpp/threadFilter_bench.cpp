/*
 * Copyright 2026 Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 *
 * Microbenchmarks for ThreadFilter's hot-path operations: add()/accept()/
 * remove() (the full context-window-enter-and-TID-check sequence used by
 * context-filtered recordings) and the add()/remove() pair alone (used by
 * every context-window transition regardless of filtering).
 *
 * Reporting numbers without gating CI pass/fail is what these are actually
 * for, so they live here instead: this file is skipped unless
 * BENCH_THREAD_FILTER is set, matching signalOrigin_bench.cpp's pattern.
 */

#include <gtest/gtest.h>
#include "threadFilter.h"
#include "wallClockBlockTracker.h"
#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>

namespace {

bool benchEnabled() {
    const char* v = getenv("BENCH_THREAD_FILTER");
    return v != nullptr && v[0] != '\0' && strcmp(v, "0") != 0;
}

// Optimization barrier -- forces the compiler to materialize each loop
// iteration's memory effects instead of proving the loop has no observable
// result and eliminating or folding it. See this file's header comment.
inline void doNotOptimize() {
    asm volatile("" ::: "memory");
}

}  // namespace

class ThreadFilterBench : public ::testing::Test {
protected:
    void SetUp() override {
        if (!benchEnabled()) {
            GTEST_SKIP() << "Set BENCH_THREAD_FILTER=1 to run this benchmark";
        }
        filter = std::make_unique<ThreadFilter>();
        filter->init("enabled");
        tracker = std::make_unique<WallClockBlockTracker>();
        filter->setBlockTracker(tracker.get());
    }

    void TearDown() override {
        filter.reset();
        tracker.reset();
    }

    std::unique_ptr<ThreadFilter> filter;
    std::unique_ptr<WallClockBlockTracker> tracker;
};

TEST_F(ThreadFilterBench, AddAcceptRemove) {
    const int num_operations = 100000;

    std::vector<int> slot_ids;
    for (int i = 0; i < 100; i++) {
        int slot_id = filter->registerThread(i);
        ASSERT_GE(slot_id, 0);
        slot_ids.push_back(slot_id);
    }

    // Warm up.
    for (int i = 0; i < 1000; i++) {
        int slot_id = slot_ids[i % slot_ids.size()];
        filter->add(i % slot_ids.size(), slot_id);
        filter->accept(slot_id);
        filter->remove(slot_id);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        int slot_id = slot_ids[i % slot_ids.size()];
        filter->add(i % slot_ids.size(), slot_id);
        bool accepted = filter->accept(slot_id);
        EXPECT_TRUE(accepted);
        filter->remove(slot_id);
        doNotOptimize();
    }
    auto end = std::chrono::high_resolution_clock::now();

    double ns_per_op =
        (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() /
        num_operations;
    std::printf("\n  [add_accept_remove] %.2f ns/op  (iters=%d)\n", ns_per_op, num_operations);
}

TEST_F(ThreadFilterBench, ContextWindowEnterExit) {
    const int num_operations = 1000000;

    constexpr int tid = 4242;
    int slot_id = filter->registerThread(tid);
    ASSERT_GE(slot_id, 0);

    for (int i = 0; i < 1000; i++) {
        filter->add(tid, slot_id);
        filter->remove(slot_id);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_operations; i++) {
        filter->add(tid, slot_id);
        filter->remove(slot_id);
        doNotOptimize();
    }
    auto end = std::chrono::high_resolution_clock::now();

    double ns_per_op =
        (double)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() /
        (num_operations * 2);
    std::printf("\n  [context_window_enter_exit] %.2f ns/op  (pairs=%d)\n", ns_per_op,
                num_operations);
}
