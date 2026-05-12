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
 * Fix: replace pthread_cleanup_push/pop with an RAII guard struct.  Destructor-based
 * cleanup works across all C++ stdlibs and runtimes (glibc, musl, IBM J9) because
 * forced-unwind runs cleanup frames regardless of the exception type.
 *
 * These tests verify:
 * 1. The RAII destructor runs on pthread_cancel (forced unwind).
 * 2. The RAII destructor runs on pthread_exit.
 * 3. ProfiledThread::release() can be called safely from within the RAII destructor.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "thread.h"

#include <atomic>
#include <pthread.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
// Test 1: bare RAII destructor fires on pthread_cancel
// ---------------------------------------------------------------------------

static std::atomic<bool> g_bare_cleanup_called{false};

static void* bare_raii_cancel_thread(void*) {
    g_bare_cleanup_called.store(false, std::memory_order_relaxed);
    struct Cleanup {
        ~Cleanup() { g_bare_cleanup_called.store(true, std::memory_order_relaxed); }
    } cleanup;
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
    return nullptr;
}

// Regression: RAII destructor must fire when the thread is cancelled via
// pthread_cancel, letting cleanup run without std::terminate().
TEST(ForcedUnwindTest, RaiiDestructorRunsOnPthreadCancel) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, bare_raii_cancel_thread, nullptr));

    usleep(5000);  // let thread reach its testcancel loop
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_bare_cleanup_called.load())
        << "RAII destructor must run during pthread_cancel forced unwind";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------
// Test 2: RAII with ProfiledThread (mirrors start_routine_wrapper)
// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_cleanup_called{false};
static std::atomic<bool> g_pt_release_called{false};

static void* profiled_raii_cancel_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);

    ProfiledThread::initCurrentThread();
    int tid = ProfiledThread::currentTid();
    (void)tid;

    // Mirrors the RAII Cleanup struct in start_routine_wrapper.
    // unregisterThread is omitted here (requires an initialised Profiler);
    // release() is the critical cleanup that must always run.
    struct Cleanup {
        ~Cleanup() {
            g_pt_cleanup_called.store(true, std::memory_order_relaxed);
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

// Regression: the start_routine_wrapper RAII pattern with ProfiledThread lifecycle
// must survive pthread_cancel without terminate().
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, profiled_raii_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_pt_cleanup_called.load())
        << "RAII destructor must run when thread is cancelled";
    EXPECT_TRUE(g_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the RAII destructor";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------
// Test 3: RAII destructor also fires on pthread_exit
// ---------------------------------------------------------------------------

static std::atomic<bool> g_exit_cleanup_called{false};

static void* raii_pthread_exit_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    struct Cleanup {
        ~Cleanup() { g_exit_cleanup_called.store(true, std::memory_order_relaxed); }
    } cleanup;
    pthread_exit(reinterpret_cast<void*>(42));
    return nullptr;
}

// pthread_exit() also triggers forced unwind — the RAII destructor must run.
TEST(ForcedUnwindTest, RaiiDestructorRunsOnPthreadExit) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, raii_pthread_exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_exit_cleanup_called.load())
        << "RAII destructor must also run during pthread_exit";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

#endif  // __linux__
