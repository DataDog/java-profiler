/*
 * Copyright 2026, Datadog, Inc.
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

// Unit tests for the malloc-shim wiring contract (debugSupport.{h,cpp}):
// without libdebug.so preloaded the dlsym'd pointer stays NULL and
// setSighandlerTid must be a silent no-op. The preloaded detection matrix
// lives in malloc-shim/src/test/cpp/malloc_shim_validate.cpp and cannot be a
// gtest: the gtest binaries are sanitizer-instrumented and must not get
// malloc interposed.

#include <gtest/gtest.h>

#include <atomic>
#include <thread>
#include <vector>

#include "debugSupport.h"
#include "guards.h"
#include "gtest_crash_handler.h"

static constexpr char SHIMS_TEST_NAME[] = "ShimsTest";

class ShimsTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<SHIMS_TEST_NAME>();
    }
    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

// instance() must hand out the singleton itself: SighandlerTidScope calls it
// on every sampling window, and a by-value return would copy the object each
// time.
TEST_F(ShimsTest, InstanceReturnsStableReference) {
    ASSERT_EQ(&Shims::instance(), &Shims::instance());
}

// Without libdebug.so preloaded, the resolved pointer is NULL and every call
// is a silent no-op. Exercising the full tid range (-1, 0, plausible tids)
// asserts no path crashes or misbehaves when the shim is absent.
TEST_F(ShimsTest, SetSighandlerTidIsNoopWithoutShim) {
    const int tids[] = {-1, 0, 1, 4096, 1 << 30};
    for (int tid : tids) {
        Shims::instance().setSighandlerTid(tid);
    }
    SUCCEED();
}

// SighandlerTidScope's documented contract: sequential, non-nested scopes are
// legal on one thread — the guard is not nesting-safe, since the destructor
// restores a hardcoded -1 rather than the previous tid. Each real call site
// takes a per-ProfiledThread CriticalSection, which rules out a second live
// guard on the same thread only: the sampling handlers run on different
// threads concurrently, and concurrent windows there clobber each other's tid
// (pre-existing design inherited from the manual set/reset statements this
// guard replaced), which is acceptable because detection is diagnostic-only.
// The destructor resets without observable effects when the shim is absent.
TEST_F(ShimsTest, SighandlerTidScopeSequentialUse) {
    {
        SighandlerTidScope scope(1234);
    }
    {
        SighandlerTidScope scope(-1);
    }
    SUCCEED();
}

// Pins only the no-op path: without the shim preloaded, Shims::_tid_setter_ref
// is permanently nullptr (dlsym runs only under #ifdef DEBUG at static init),
// so every concurrent iteration here exercises the atomic acquire load of a
// NULL pointer plus the no-op branch — race-free under the
// sanitizer-instrumented gtest run. Visibility of a *resolved* setter across
// processes is not covered here; it is exercised by
// malloc-shim/src/test/cpp/malloc_shim_validate.cpp full mode, which cannot be
// a gtest (see the file-top comment above).
TEST_F(ShimsTest, ConcurrentSetSighandlerTidNoopPathIsRaceFree) {
    std::atomic<bool> stop{false};
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++) {
        threads.emplace_back([&stop, i]() {
            while (!stop.load(std::memory_order_relaxed)) {
                Shims::instance().setSighandlerTid(i);
                SighandlerTidScope scope(i);
            }
        });
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    stop.store(true, std::memory_order_relaxed);
    for (auto &t : threads) {
        t.join();
    }
    SUCCEED();
}
