/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Regression test for SCP-1154: IBM J9 JVM crash in start_routine_wrapper.
 *
 * Root cause: pthread_cleanup_push in C++ mode creates __pthread_cleanup_class
 * with an implicitly-noexcept destructor.  When IBM J9's thread teardown raises
 * _Unwind_ForcedUnwind (via libgcc, sourced from libj9thr29.so), the C++ runtime
 * calls std::terminate() -> abort() because the forced-unwind exception tries to
 * exit a noexcept-bounded destructor.
 *
 * Fix: replace pthread_cleanup_push/pop with catch(abi::__forced_unwind&) + rethrow.
 *
 * These tests verify:
 * 1. abi::__forced_unwind (raised by pthread_cancel / pthread_exit) is caught by
 *    the new pattern.
 * 2. The cleanup block runs.
 * 3. The rethrow allows the thread to exit as PTHREAD_CANCELED.
 * 4. ProfiledThread::release() can be called safely from within the catch block.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "thread.h"

#include <atomic>
#include <cxxabi.h>
#include <pthread.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// Test 1: bare catch(abi::__forced_unwind&) + rethrow
// ---------------------------------------------------------------------------

static std::atomic<bool> g_bare_cleanup_called{false};

static void* bare_forced_unwind_thread(void*) {
    g_bare_cleanup_called.store(false, std::memory_order_relaxed);
    try {
        while (true) {
            pthread_testcancel();
            usleep(100);
        }
    } catch (abi::__forced_unwind&) {
        g_bare_cleanup_called.store(true, std::memory_order_relaxed);
        throw;  // must re-throw so thread exits as PTHREAD_CANCELED
    }
    return nullptr;
}

// Regression: catch(abi::__forced_unwind&) + rethrow must intercept the forced
// unwind raised by pthread_cancel, run the cleanup block, and let the thread
// exit cleanly as PTHREAD_CANCELED — not via std::terminate().
TEST(ForcedUnwindTest, BarePatternInterceptsAndRethrows) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, bare_forced_unwind_thread, nullptr));

    usleep(5000);  // let thread reach its testcancel loop
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_bare_cleanup_called.load())
        << "catch(abi::__forced_unwind&) must fire on pthread_cancel";
    EXPECT_EQ(PTHREAD_CANCELED, retval)
        << "rethrow must let thread exit as PTHREAD_CANCELED";
}

// ---------------------------------------------------------------------------
// Test 2: pattern with ProfiledThread (mirrors start_routine_wrapper)
// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_cleanup_called{false};
static std::atomic<bool> g_pt_release_called{false};

static void* profiled_forced_unwind_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);

    // Mirrors what start_routine_wrapper does before calling routine(params).
    ProfiledThread::initCurrentThread();
    int tid = ProfiledThread::currentTid();
    (void)tid;

    try {
        while (true) {
            pthread_testcancel();
            usleep(100);
        }
    } catch (abi::__forced_unwind&) {
        g_pt_cleanup_called.store(true, std::memory_order_relaxed);
        // Mirrors the catch block in the fixed start_routine_wrapper:
        // unregisterThread is omitted here (requires an initialised Profiler);
        // release() is the critical cleanup that must always run.
        ProfiledThread::release();
        g_pt_release_called.store(true, std::memory_order_relaxed);
        throw;
    }

    ProfiledThread::release();
    return nullptr;
}

// Regression: the start_routine_wrapper pattern with ProfiledThread lifecycle
// must survive pthread_cancel without terminate().
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, profiled_forced_unwind_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_pt_cleanup_called.load())
        << "catch(abi::__forced_unwind&) must fire when thread is cancelled";
    EXPECT_TRUE(g_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the catch block";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------
// Test 3: pthread_exit() also raises abi::__forced_unwind on glibc
// ---------------------------------------------------------------------------

static std::atomic<bool> g_exit_cleanup_called{false};

static void* pthread_exit_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    try {
        pthread_exit(reinterpret_cast<void*>(42));
    } catch (abi::__forced_unwind&) {
        g_exit_cleanup_called.store(true, std::memory_order_relaxed);
        throw;
    }
    return nullptr;
}

// pthread_exit() also uses abi::__forced_unwind on glibc — the same catch
// block must handle it so that threads calling pthread_exit() inside a
// wrapped routine don't bypass cleanup.
TEST(ForcedUnwindTest, PthreadExitAlsoCaughtByForcedUnwindCatch) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, pthread_exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_exit_cleanup_called.load())
        << "catch(abi::__forced_unwind&) must also catch pthread_exit()";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

#endif  // __linux__
