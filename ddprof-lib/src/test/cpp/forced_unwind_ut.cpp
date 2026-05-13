/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Regression test for SCP-1154: IBM J9 JVM crash in start_routine_wrapper.
 *
 * Root cause: pthread_cleanup_push in C++ mode on glibc creates
 * __pthread_cleanup_class with an implicitly-noexcept destructor.  When IBM
 * J9's thread teardown raises _Unwind_ForcedUnwind (via libgcc), the C++
 * runtime calls std::terminate() because the forced-unwind exception exits a
 * noexcept-bounded destructor.
 *
 * Cleanup strategy (matches libraryPatcher_linux.cpp):
 *   - glibc: RAII struct destructor.  Glibc's personality function handles
 *     forced-unwind correctly for user-defined destructors; IBM J9's forced-
 *     unwind also invokes personality functions.
 *   - musl:  pthread_cleanup_push/pop (C-style callback).  musl's signal-based
 *     thread cancellation invokes registered C callbacks but does NOT run C++
 *     destructors.
 *
 * These tests verify the per-platform cleanup path:
 *   glibc  – RAII destructor fires on pthread_cancel and pthread_exit.
 *   musl   – pthread_cleanup_push callback fires on pthread_cancel and
 *            pthread_exit.
 * A shared test verifies ProfiledThread::release() is safe to call from the
 * chosen cleanup path.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "thread.h"

#include <atomic>
#include <pthread.h>
#include <unistd.h>

// ===========================================================================
// glibc path: RAII destructor tests
// ===========================================================================
#ifdef __GLIBC__

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

// Regression (glibc): RAII destructor fires on pthread_cancel.
TEST(ForcedUnwindTest, RaiiDestructorRunsOnPthreadCancel) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, bare_raii_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_bare_cleanup_called.load())
        << "RAII destructor must run during pthread_cancel forced unwind";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_cleanup_called{false};
static std::atomic<bool> g_pt_release_called{false};

static void* profiled_raii_cancel_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);

    ProfiledThread::initCurrentThread();

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

// Regression (glibc): RAII pattern with ProfiledThread lifecycle survives
// pthread_cancel without terminate().
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

static std::atomic<bool> g_exit_cleanup_called{false};

static void* raii_pthread_exit_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    struct Cleanup {
        ~Cleanup() { g_exit_cleanup_called.store(true, std::memory_order_relaxed); }
    } cleanup;
    pthread_exit(reinterpret_cast<void*>(42));
    return nullptr;
}

// Regression (glibc): RAII destructor fires on pthread_exit.
TEST(ForcedUnwindTest, RaiiDestructorRunsOnPthreadExit) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, raii_pthread_exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_exit_cleanup_called.load())
        << "RAII destructor must also run during pthread_exit";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

#endif  // __GLIBC__

// ===========================================================================
// musl (non-glibc) path: pthread_cleanup_push/pop callback tests
// ===========================================================================
#ifndef __GLIBC__

static std::atomic<bool> g_c_cancel_called{false};

static void c_cleanup_cancel(void*) {
    g_c_cancel_called.store(true, std::memory_order_relaxed);
}

static void* c_cleanup_cancel_thread(void*) {
    g_c_cancel_called.store(false, std::memory_order_relaxed);
    pthread_cleanup_push(c_cleanup_cancel, nullptr);
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
    pthread_cleanup_pop(0);
    return nullptr;
}

// Regression (musl): C-style pthread_cleanup_push callback fires on pthread_cancel.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadCancel) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, c_cleanup_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_c_cancel_called.load())
        << "pthread_cleanup_push callback must run during pthread_cancel on musl";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_c_exit_called{false};

static void c_cleanup_exit(void*) {
    g_c_exit_called.store(true, std::memory_order_relaxed);
}

static void* c_cleanup_exit_thread(void*) {
    g_c_exit_called.store(false, std::memory_order_relaxed);
    pthread_cleanup_push(c_cleanup_exit, nullptr);
    pthread_exit(reinterpret_cast<void*>(42));
    pthread_cleanup_pop(0);
    return nullptr;
}

// Regression (musl): C-style pthread_cleanup_push callback fires on pthread_exit.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadExit) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, c_cleanup_exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_c_exit_called.load())
        << "pthread_cleanup_push callback must run during pthread_exit on musl";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_c_pt_called{false};
static std::atomic<bool> g_c_pt_release_called{false};

static void profiled_c_cleanup(void* arg) {
    int tid = *static_cast<int*>(arg);
    (void)tid;
    g_c_pt_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_c_pt_release_called.store(true, std::memory_order_relaxed);
}

static int g_c_pt_tid;

static void* profiled_c_cancel_thread(void*) {
    g_c_pt_called.store(false, std::memory_order_relaxed);
    g_c_pt_release_called.store(false, std::memory_order_relaxed);

    ProfiledThread::initCurrentThread();
    g_c_pt_tid = ProfiledThread::currentTid();

    pthread_cleanup_push(profiled_c_cleanup, &g_c_pt_tid);
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
    pthread_cleanup_pop(0);
    return nullptr;
}

// Regression (musl): pthread_cleanup_push pattern with ProfiledThread lifecycle
// survives pthread_cancel.
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, profiled_c_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_c_pt_called.load())
        << "C cleanup callback must run when thread is cancelled";
    EXPECT_TRUE(g_c_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the C cleanup callback";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

#endif  // !__GLIBC__

#endif  // __linux__
