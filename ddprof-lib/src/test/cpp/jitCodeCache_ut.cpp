/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>

#include "counters.h"
#include "hotspot/jitCodeCache.h"
#ifdef __aarch64__
#include "hotspot/stubUnwindInfo.h"
#endif

class JitCodeCacheTestAccessor {
public:
    static SpinLock& stubsLock() { return JitCodeCache::_stubs_lock; }
};

namespace {

// JitCodeCache state is process-wide and stubs are never removed, so every
// test registers into its own disjoint slice of this buffer. The buffer is
// static so registered addresses stay valid; on aarch64 the registration
// decodes it, so it is filled with NOPs. Stub names avoid "Interpreter" and
// "call_stub", which change other global state.
const int CODE_WORDS = 16384;
alignas(64) uint32_t g_code[CODE_WORDS];

const uint32_t* codeAt(int word) {
    static bool filled = [] {
        for (int i = 0; i < CODE_WORDS; i++) {
            g_code[i] = 0xd503201f;  // aarch64 NOP
        }
        return true;
    }();
    (void)filled;
    return &g_code[word];
}

void registerStub(const void* start, int length, const char* name) {
    JitCodeCache::DynamicCodeGenerated(nullptr, name, start, length);
}

// Runs body on a helper thread and reports whether it finished within the
// timeout. Joins in every case, so a body that waits on a lock held by the
// caller must be released by the caller before the join (see release).
template <typename Body, typename Release>
bool finishesWithin(std::chrono::milliseconds timeout, Body body, Release release) {
    std::atomic<bool> done{false};
    std::thread t([&] {
        body();
        done.store(true, std::memory_order_release);
    });
    auto deadline = std::chrono::steady_clock::now() + timeout;
    while (!done.load(std::memory_order_acquire) &&
           std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    bool finished = done.load(std::memory_order_acquire);
    release();
    t.join();
    return finished;
}

}  // namespace

// Regression for the stub-lock deadlock: a signal-handler lookup must not wait
// for a registration that holds _stubs_lock exclusively. Before the fix the
// lookup spun in lockShared() until the lock was released.
TEST(JitCodeCacheTest, FindRuntimeStubDoesNotWaitForExclusiveHolder) {
    const void* code = codeAt(0);
    registerStub(code, 64, "jcc_test_busy");

    const void* start = nullptr;
    const char* name = nullptr;
    ASSERT_TRUE(JitCodeCache::findRuntimeStub(code, &start, &name));
    EXPECT_EQ(code, start);
    EXPECT_STREQ("jcc_test_busy", name);

    SpinLock& lock = JitCodeCacheTestAccessor::stubsLock();
    long long before = Counters::getCounter(STUB_LOOKUP_LOCK_UNAVAILABLE);
    bool found = true;
    lock.lock();
    bool finished = finishesWithin(
        std::chrono::seconds(5),
        [&] { found = JitCodeCache::findRuntimeStub(code, &start, &name); },
        [&] { lock.unlock(); });
    ASSERT_TRUE(finished) << "findRuntimeStub waited for the exclusive holder";
    EXPECT_FALSE(found);
    EXPECT_EQ(1, Counters::getCounter(STUB_LOOKUP_LOCK_UNAVAILABLE) - before);

    EXPECT_TRUE(JitCodeCache::findRuntimeStub(code, &start, &name));
}

#ifdef __aarch64__
TEST(JitCodeCacheTest, FindRuntimeStubInfoDoesNotWaitForExclusiveHolder) {
    const void* code = codeAt(64);
    registerStub(code, 64, "jcc_test_busy_info");

    const void* start = nullptr;
    const char* name = nullptr;
    const StubUnwindInfo* info = nullptr;
    ASSERT_TRUE(JitCodeCache::findRuntimeStubInfo(code, &start, &name, &info));
    EXPECT_EQ(code, start);
    EXPECT_STREQ("jcc_test_busy_info", name);

    SpinLock& lock = JitCodeCacheTestAccessor::stubsLock();
    long long before = Counters::getCounter(STUB_LOOKUP_LOCK_UNAVAILABLE);
    bool found = true;
    lock.lock();
    bool finished = finishesWithin(
        std::chrono::seconds(5),
        [&] { found = JitCodeCache::findRuntimeStubInfo(code, &start, &name, &info); },
        [&] { lock.unlock(); });
    ASSERT_TRUE(finished) << "findRuntimeStubInfo waited for the exclusive holder";
    EXPECT_FALSE(found);
    EXPECT_EQ(nullptr, info);
    EXPECT_EQ(1, Counters::getCounter(STUB_LOOKUP_LOCK_UNAVAILABLE) - before);

    EXPECT_TRUE(JitCodeCache::findRuntimeStubInfo(code, &start, &name, &info));
}

// A second registration of the same start keeps the first unwind info.
TEST(JitCodeCacheTest, DuplicateRegistrationKeepsFirstInfo) {
    const void* code = codeAt(128);
    registerStub(code, 64, "jcc_test_dup");
    const void* start = nullptr;
    const char* name = nullptr;
    const StubUnwindInfo* first = nullptr;
    ASSERT_TRUE(JitCodeCache::findRuntimeStubInfo(code, &start, &name, &first));
    ASSERT_NE(nullptr, first);

    registerStub(code, 64, "jcc_test_dup_again");
    const StubUnwindInfo* second = nullptr;
    ASSERT_TRUE(JitCodeCache::findRuntimeStubInfo(code, &start, &name, &second));
    EXPECT_EQ(first, second);
}
#endif

// More registrations than the initial blob capacity (and, on aarch64, the
// initial unwind-registry capacity) force both arrays to be replaced; every
// stub must stay findable with its own start, name and unwind info.
TEST(JitCodeCacheTest, RegistrationsAcrossGrowthStayFindable) {
    const int STUBS = INITIAL_CODE_CACHE_CAPACITY + 100;
    const int WORDS_PER_STUB = 2;
    const int BASE = 256;
    ASSERT_LE(BASE + STUBS * WORDS_PER_STUB, CODE_WORDS);
    char name[32];
    for (int i = 0; i < STUBS; i++) {
        snprintf(name, sizeof(name), "jcc_grow_%d", i);
        registerStub(codeAt(BASE + i * WORDS_PER_STUB), WORDS_PER_STUB * 4, name);
    }
    for (int i = 0; i < STUBS; i++) {
        const void* code = codeAt(BASE + i * WORDS_PER_STUB);
        snprintf(name, sizeof(name), "jcc_grow_%d", i);
        const void* start = nullptr;
        const char* found_name = nullptr;
        ASSERT_TRUE(JitCodeCache::findRuntimeStub(code, &start, &found_name)) << i;
        EXPECT_EQ(code, start) << i;
        EXPECT_STREQ(name, found_name) << i;
#ifdef __aarch64__
        const StubUnwindInfo* info = nullptr;
        ASSERT_TRUE(JitCodeCache::findRuntimeStubInfo(code, &start, &found_name, &info)) << i;
        EXPECT_NE(nullptr, info) << i;
#endif
    }
}

// Lookups racing registrations that replace the blob array. Readers copy the
// stub fields out under the lock, so none can read a replaced array; under
// ASan a read of a freed array fails the test. Readers pause between lookups:
// SpinLock::lock() only succeeds when no reader holds the lock, so readers
// that only yield can delay the writers for seconds under ASan.
TEST(JitCodeCacheTest, ConcurrentRegistrationAndLookup) {
    const int WRITERS = 2;
    const int STUBS_PER_WRITER = 600;
    const int WORDS_PER_STUB = 2;
    const int BASE = 4096;
    ASSERT_LE(BASE + WRITERS * STUBS_PER_WRITER * WORDS_PER_STUB, CODE_WORDS);

    std::atomic<int> writers_left{WRITERS};
    std::vector<std::thread> threads;
    for (int w = 0; w < WRITERS; w++) {
        threads.emplace_back([&, w] {
            char name[32];
            for (int i = 0; i < STUBS_PER_WRITER; i++) {
                int slot = w * STUBS_PER_WRITER + i;
                snprintf(name, sizeof(name), "jcc_conc_%d", slot);
                registerStub(codeAt(BASE + slot * WORDS_PER_STUB), WORDS_PER_STUB * 4, name);
            }
            writers_left.fetch_sub(1);
        });
    }
    for (int r = 0; r < 4; r++) {
        threads.emplace_back([&, r] {
            int slot = r;
            while (writers_left.load() > 0) {
                const void* code = codeAt(BASE + slot * WORDS_PER_STUB);
                const void* start = nullptr;
                const char* name = nullptr;
                if (JitCodeCache::findRuntimeStub(code, &start, &name)) {
                    EXPECT_EQ(code, start);
                    EXPECT_EQ(0, strncmp(name, "jcc_conc_", 9));
                }
                slot = (slot + 7) % (WRITERS * STUBS_PER_WRITER);
                std::this_thread::sleep_for(std::chrono::microseconds(50));
            }
        });
    }
    for (auto& t : threads) {
        t.join();
    }
    for (int slot = 0; slot < WRITERS * STUBS_PER_WRITER; slot++) {
        const void* start = nullptr;
        const char* name = nullptr;
        EXPECT_TRUE(JitCodeCache::findRuntimeStub(codeAt(BASE + slot * WORDS_PER_STUB),
                                                  &start, &name)) << slot;
    }
}
