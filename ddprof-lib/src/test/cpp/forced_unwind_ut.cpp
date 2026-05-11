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
 * Fix: replace pthread_cleanup_push/pop (and the earlier glibc-only
 * catch(abi::__forced_unwind&) approach) with RAII cleanup structs whose
 * destructors run during any C++ stack unwinding — including forced unwind on
 * both glibc and musl.
 *
 * These tests verify:
 * 1. An RAII destructor runs when a thread is cancelled via pthread_cancel.
 * 2. The thread exits as PTHREAD_CANCELED.
 * 3. ProfiledThread::release() can be called safely from within an RAII destructor.
 * 4. pthread_exit() also triggers RAII destructor cleanup.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "thread.h"

#include <atomic>
#include <pthread.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// Test 1: bare RAII destructor runs on pthread_cancel
// ---------------------------------------------------------------------------

static std::atomic<bool> g_bare_cleanup_called{false};

static void* bare_raii_thread(void*) {
    g_bare_cleanup_called.store(false, std::memory_order_relaxed);
    struct Cleanup {
        ~Cleanup() {
            g_bare_cleanup_called.store(true, std::memory_order_relaxed);
        }
    } cleanup;
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
    return nullptr;
}

// Regression: RAII destructor must run during pthread_cancel's forced unwind
// on both glibc and musl, and the thread must exit as PTHREAD_CANCELED.
TEST(ForcedUnwindTest, BarePatternInterceptsAndRethrows) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, bare_raii_thread, nullptr));

    usleep(5000);  // let thread reach its testcancel loop
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_bare_cleanup_called.load())
        << "RAII destructor must fire on pthread_cancel";
    EXPECT_EQ(PTHREAD_CANCELED, retval)
        << "thread must exit as PTHREAD_CANCELED";
}

// ---------------------------------------------------------------------------
// Test 2: RAII pattern with ProfiledThread (mirrors start_routine_wrapper)
// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_cleanup_called{false};
static std::atomic<bool> g_pt_release_called{false};

static void* profiled_raii_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);

    // Mirrors what start_routine_wrapper does before calling routine(params).
    ProfiledThread::initCurrentThread();
    int tid = ProfiledThread::currentTid();
    (void)tid;

    struct Cleanup {
        ~Cleanup() {
            g_pt_cleanup_called.store(true, std::memory_order_relaxed);
            // Mirrors the RAII cleanup in the fixed start_routine_wrapper:
            // unregisterThread is omitted here (requires an initialised Profiler);
            // release() is the critical cleanup that must always run.
            ProfiledThread::release();
            g_pt_release_called.store(true, std::memory_order_relaxed);
        }
    } cleanup;

    while (true) {
        pthread_testcancel();
        usleep(100);
    }
    return nullptr;
}

// Regression: the start_routine_wrapper pattern with ProfiledThread lifecycle
// must survive pthread_cancel without terminate().
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, profiled_raii_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_pt_cleanup_called.load())
        << "RAII destructor must fire when thread is cancelled";
    EXPECT_TRUE(g_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the RAII destructor";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------
// Test 3: pthread_exit() also triggers RAII destructor cleanup
// ---------------------------------------------------------------------------

static std::atomic<bool> g_exit_cleanup_called{false};

static void* pthread_exit_raii_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    struct Cleanup {
        ~Cleanup() {
            g_exit_cleanup_called.store(true, std::memory_order_relaxed);
        }
    } cleanup;
    pthread_exit(reinterpret_cast<void*>(42));
    return nullptr;
}

// pthread_exit() unwinds the stack via _Unwind_ForcedUnwind — the same
// mechanism as pthread_cancel — so RAII destructors must also run, ensuring
// cleanup is not bypassed by a direct pthread_exit() call.
TEST(ForcedUnwindTest, PthreadExitAlsoCaughtByForcedUnwindCatch) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, pthread_exit_raii_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_exit_cleanup_called.load())
        << "RAII destructor must also run on pthread_exit()";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

#endif  // __linux__
