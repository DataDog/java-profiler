/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Regression test for the static-libgcc / forced-unwind incompatibility in
 * start_routine_wrapper (libraryPatcher_linux.cpp).
 *
 * Root cause: when libjavaProfiler.so is built with -static-libgcc, its
 * embedded __gxx_personality_v0 is called by the dynamic libgcc_s.so.1's
 * _Unwind_ForcedUnwind (triggered by pthread_exit / pthread_cancel).  The two
 * libgcc versions have incompatible _Unwind_Context layouts; calling
 * _Unwind_SetGR with a cross-version context triggers _Unwind_SetGR.cold,
 * which calls abort().  The same crash affects any gtest binary that is also
 * built with -static-libgcc.
 *
 * C++ RAII destructors (struct Cleanup { ~Cleanup() {...} }) add cleanup
 * entries to the LSDA, which cause __gxx_personality_v0 to call _Unwind_SetGR
 * → crash.  The pthread_cleanup_push C++ macro (__pthread_cleanup_class RAII)
 * has the same problem.
 *
 * Cleanup strategy (matches libraryPatcher_linux.cpp):
 *   - glibc:  Use __pthread_register_cancel / __pthread_unregister_cancel
 *             directly (the same mechanism the C form of pthread_cleanup_push
 *             uses).  This registers cleanup via a setjmp buffer in a runtime
 *             linked-list, NOT in the LSDA.  _Unwind_ForcedUnwind's stop
 *             function (__pthread_unwind_stop) handles the cleanup without
 *             ever calling __gxx_personality_v0 for the registered frame, so
 *             _Unwind_SetGR is never called and no crash occurs.
 *   - musl:   pthread_cleanup_push already uses the C/setjmp form (no RAII).
 *             pthread_exit on musl does not use _Unwind_ForcedUnwind at all,
 *             so there is no incompatibility issue.
 *
 * These tests verify the per-platform cleanup path:
 *   glibc  – __pthread_register_cancel callback fires on pthread_cancel,
 *             pthread_exit, and normal routine return.
 *   musl   – run_with_cleanup (pthread_cleanup_push/pop) callback fires on
 *             pthread_cancel, pthread_exit, and normal routine return.
 * A shared test verifies ProfiledThread::release() is safe to call from the
 * chosen cleanup path.
 */

#include <gtest/gtest.h>

#ifdef __linux__

#include "thread.h"

#include <atomic>
#include <pthread.h>
#include <setjmp.h>
#include <unistd.h>

// Production function under test — defined in libraryPatcher_linux.cpp.
// Declared here (outside any platform guard) because run_with_cleanup is built
// on both glibc and musl; each platform's tests call it directly.
extern "C++" void run_with_cleanup(void* (*)(void*), void*, void(*)(void*), void*);

// ===========================================================================
// glibc path: __pthread_register_cancel / __pthread_unregister_cancel tests
// ===========================================================================
#ifdef __GLIBC__

// ---------------------------------------------------------------------------

static std::atomic<bool> g_bare_cleanup_called{false};

static void bare_cleanup(void*) {
    g_bare_cleanup_called.store(true, std::memory_order_relaxed);
}

static void* bare_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* bare_cancel_thread(void*) {
    g_bare_cleanup_called.store(false, std::memory_order_relaxed);
    run_with_cleanup(bare_spin, nullptr, bare_cleanup, nullptr);
    return nullptr;
}

// Regression (glibc): __pthread_register_cancel callback fires on pthread_cancel.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadCancel) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, bare_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_bare_cleanup_called.load())
        << "__pthread_register_cancel callback must run during pthread_cancel";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_cleanup_called{false};
static std::atomic<bool> g_pt_release_called{false};

static void profiled_cleanup(void*) {
    g_pt_cleanup_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_pt_release_called.store(true, std::memory_order_relaxed);
}

static void* profiled_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* profiled_cancel_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);
    ProfiledThread::initCurrentThread();
    run_with_cleanup(profiled_spin, nullptr, profiled_cleanup, nullptr);
    return nullptr;
}

// Regression (glibc): ProfiledThread lifecycle survives pthread_cancel without
// abort() from _Unwind_SetGR.cold (the static-libgcc / libgcc_s.so.1 clash).
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, profiled_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_pt_cleanup_called.load())
        << "Cleanup callback must run when thread is cancelled";
    EXPECT_TRUE(g_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the cleanup callback";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_exit_cleanup_called{false};

static void exit_cleanup(void*) {
    g_exit_cleanup_called.store(true, std::memory_order_relaxed);
}

static void* exit_fn(void*) {
    pthread_exit(reinterpret_cast<void*>(42));
}

static void* exit_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    run_with_cleanup(exit_fn, nullptr, exit_cleanup, nullptr);
    return nullptr;
}

// Regression (glibc): __pthread_register_cancel callback fires on pthread_exit.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadExit) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_exit_cleanup_called.load())
        << "__pthread_register_cancel callback must also run during pthread_exit";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

// ---------------------------------------------------------------------------

static std::atomic<int> g_nr_cleanup_count{0};
static std::atomic<bool> g_nr_past_run{false};

static void* nr_routine(void*) { return nullptr; }

static void nr_cleanup(void*) {
    g_nr_cleanup_count.fetch_add(1, std::memory_order_relaxed);
}

static void* nr_thread(void*) {
    g_nr_cleanup_count.store(0, std::memory_order_relaxed);
    g_nr_past_run.store(false, std::memory_order_relaxed);
    run_with_cleanup(nr_routine, nullptr, nr_cleanup, nullptr);
    g_nr_past_run.store(true, std::memory_order_relaxed);
    // Spin with a cancellation point so the main thread can probe whether
    // __pthread_unregister_cancel took effect after run_with_cleanup returned.
    while (true) {
        pthread_testcancel();
        usleep(50);
    }
    __builtin_unreachable();
}

// Normal-return path (matches start_routine_wrapper on non-aarch64 glibc):
// cleanup_fn is called once AND __pthread_unregister_cancel removes the buf.
// Removing either call on this path is detected:
//   - no cleanup_fn             → g_nr_cleanup_count stays 0
//   - no __pthread_unregister_cancel → post-return cancel longjmps into the
//     freed cancel_buf (UB: crash or g_nr_cleanup_count becomes 2)
// Note: under ASAN/MSAN the UAF detection path (count==2) is not guaranteed — 
// a crash is also acceptable evidence.
TEST(ForcedUnwindTest, CleanupCalledExactlyOnceOnNormalReturn) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, nr_thread, nullptr));

    while (!g_nr_past_run.load(std::memory_order_relaxed)) {
        usleep(100);
    }
    EXPECT_EQ(1, g_nr_cleanup_count.load())
        << "cleanup_fn must be called once on the normal-return path of run_with_cleanup";

    // Cancel the spinning thread.  If __pthread_unregister_cancel was not
    // called, glibc still holds a pointer to run_with_cleanup's freed
    // cancel_buf; the cancel would longjmp into garbage and either crash or
    // fire nr_cleanup a second time (count == 2).
    pthread_cancel(t);
    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_EQ(1, g_nr_cleanup_count.load())
        << "__pthread_unregister_cancel must remove the buf so the "
           "post-return cancel does not re-fire cleanup_fn";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_pt_nr_called{false};
static std::atomic<bool> g_pt_nr_release_called{false};

static void* pt_nr_routine(void*) { return nullptr; }

static void pt_nr_cleanup(void*) {
    g_pt_nr_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_pt_nr_release_called.store(true, std::memory_order_relaxed);
}

static void* pt_nr_thread(void*) {
    g_pt_nr_called.store(false, std::memory_order_relaxed);
    g_pt_nr_release_called.store(false, std::memory_order_relaxed);
    ProfiledThread::initCurrentThread();
    run_with_cleanup(pt_nr_routine, nullptr, pt_nr_cleanup, nullptr);
    return reinterpret_cast<void*>(77);
}

// Regression (glibc): cleanup_fn fires and ProfiledThread is released when
// routine returns normally.  This is the start_routine_wrapper path for
// threads that finish naturally (no cancel, no pthread_exit).
// Removing cleanup_fn(cleanup_arg) after __pthread_unregister_cancel leaves
// g_pt_nr_called false and leaks the ProfiledThread entry.
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnNormalReturn) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, pt_nr_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_pt_nr_called.load())
        << "cleanup_fn must be called on the normal-return path";
    EXPECT_TRUE(g_pt_nr_release_called.load())
        << "ProfiledThread::release() must complete on the normal-return path";
    EXPECT_EQ(reinterpret_cast<void*>(77), retval);
}

#endif  // __GLIBC__

// ===========================================================================
// musl (non-glibc) path: run_with_cleanup (pthread_cleanup_push/pop) tests
// ===========================================================================
#ifndef __GLIBC__

// ---------------------------------------------------------------------------

static std::atomic<bool> g_m_cancel_called{false};

static void m_cancel_cleanup(void*) {
    g_m_cancel_called.store(true, std::memory_order_relaxed);
}

static void* m_cancel_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* m_cancel_thread(void*) {
    g_m_cancel_called.store(false, std::memory_order_relaxed);
    run_with_cleanup(m_cancel_spin, nullptr, m_cancel_cleanup, nullptr);
    return nullptr;
}

// musl: run_with_cleanup cleanup fires on pthread_cancel.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadCancel) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, m_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_m_cancel_called.load())
        << "run_with_cleanup cleanup must fire during pthread_cancel on musl";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_m_exit_called{false};

static void m_exit_cleanup(void*) {
    g_m_exit_called.store(true, std::memory_order_relaxed);
}

static void* m_exit_fn(void*) {
    pthread_exit(reinterpret_cast<void*>(42));
}

static void* m_exit_thread(void*) {
    g_m_exit_called.store(false, std::memory_order_relaxed);
    run_with_cleanup(m_exit_fn, nullptr, m_exit_cleanup, nullptr);
    return nullptr;
}

// musl: run_with_cleanup cleanup fires on pthread_exit.
TEST(ForcedUnwindTest, CleanupCallbackRunsOnPthreadExit) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, m_exit_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_m_exit_called.load())
        << "run_with_cleanup cleanup must fire during pthread_exit on musl";
    EXPECT_EQ(reinterpret_cast<void*>(42), retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_m_pt_called{false};
static std::atomic<bool> g_m_pt_release_called{false};

static void m_profiled_cleanup(void*) {
    g_m_pt_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_m_pt_release_called.store(true, std::memory_order_relaxed);
}

static void* m_profiled_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* m_profiled_cancel_thread(void*) {
    g_m_pt_called.store(false, std::memory_order_relaxed);
    g_m_pt_release_called.store(false, std::memory_order_relaxed);
    ProfiledThread::initCurrentThread();
    run_with_cleanup(m_profiled_spin, nullptr, m_profiled_cleanup, nullptr);
    return nullptr;
}

// musl: ProfiledThread lifecycle survives pthread_cancel via run_with_cleanup.
TEST(ForcedUnwindTest, ProfiledThreadReleasedOnForcedUnwind) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, m_profiled_cancel_thread, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_m_pt_called.load())
        << "Cleanup callback must run when thread is cancelled";
    EXPECT_TRUE(g_m_pt_release_called.load())
        << "ProfiledThread::release() must complete inside the cleanup callback";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<int> g_m_nr_count{0};

static void* m_nr_routine(void*) { return nullptr; }

static void m_nr_cleanup(void*) {
    g_m_nr_count.fetch_add(1, std::memory_order_relaxed);
}

static void* m_nr_thread(void*) {
    g_m_nr_count.store(0, std::memory_order_relaxed);
    run_with_cleanup(m_nr_routine, nullptr, m_nr_cleanup, nullptr);
    return reinterpret_cast<void*>(77);
}

// musl: normal-return path calls cleanup exactly once via pthread_cleanup_pop(1).
// Removing the pop or changing pop(1) to pop(0) leaves count at 0.
TEST(ForcedUnwindTest, CleanupCalledExactlyOnceOnNormalReturn) {
    pthread_t t;
    ASSERT_EQ(0, pthread_create(&t, nullptr, m_nr_thread, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_EQ(1, g_m_nr_count.load())
        << "cleanup_fn must be called once via pthread_cleanup_pop(1) on the normal-return path";
    EXPECT_EQ(reinterpret_cast<void*>(77), retval);
}

#endif  // !__GLIBC__

// ===========================================================================
// Integration tests: start_routine_for_test → run_with_cleanup chain
//
// These tests exercise the full path that start_routine_wrapper takes in
// production (init TLS → run_with_cleanup → cleanup on cancel/exit), without
// the Profiler::registerThread/unregisterThread calls that require a live
// profiler instance.  Profiler registration is tested separately; these tests
// cover the wiring between the wrapper and run_with_cleanup.
//
// Removing run_with_cleanup from start_routine_wrapper, or wiring it to a
// no-op cleanup, would leave the unit tests passing but fail these tests.
// ===========================================================================

// Test entry point declared in libraryPatcher_linux.cpp under #ifdef UNIT_TEST.
extern "C++" int pthread_create_wrapped_for_test(
    pthread_t*, void* (*)(void*), void*, void (*)(void*), void*);

// ---------------------------------------------------------------------------

static std::atomic<bool> g_int_cancel_called{false};
static std::atomic<bool> g_int_cancel_released{false};

static void int_cancel_cleanup(void*) {
    g_int_cancel_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_int_cancel_released.store(true, std::memory_order_relaxed);
}

static void* int_cancel_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

// Integration: start_routine_for_test → run_with_cleanup → cleanup fires and
// ProfiledThread is released on pthread_cancel.
TEST(ForcedUnwindTest, WrapperReleasesProfiledThreadOnCancel) {
    g_int_cancel_called.store(false, std::memory_order_relaxed);
    g_int_cancel_released.store(false, std::memory_order_relaxed);

    pthread_t t;
    ASSERT_EQ(0, pthread_create_wrapped_for_test(
        &t, int_cancel_spin, nullptr, int_cancel_cleanup, nullptr));

    usleep(5000);
    pthread_cancel(t);

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_int_cancel_called.load())
        << "run_with_cleanup cleanup must fire when wrapped thread is cancelled";
    EXPECT_TRUE(g_int_cancel_released.load())
        << "ProfiledThread::release() must complete inside the wrapper cleanup";
    EXPECT_EQ(PTHREAD_CANCELED, retval);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_int_exit_called{false};
static std::atomic<bool> g_int_exit_released{false};

static void int_exit_cleanup(void*) {
    g_int_exit_called.store(true, std::memory_order_relaxed);
    ProfiledThread::release();
    g_int_exit_released.store(true, std::memory_order_relaxed);
}

static void* int_exit_fn(void*) {
    pthread_exit(reinterpret_cast<void*>(99));
}

// Integration: start_routine_for_test → run_with_cleanup → cleanup fires and
// ProfiledThread is released on pthread_exit.
TEST(ForcedUnwindTest, WrapperReleasesProfiledThreadOnPthreadExit) {
    g_int_exit_called.store(false, std::memory_order_relaxed);
    g_int_exit_released.store(false, std::memory_order_relaxed);

    pthread_t t;
    ASSERT_EQ(0, pthread_create_wrapped_for_test(
        &t, int_exit_fn, nullptr, int_exit_cleanup, nullptr));

    void* retval;
    ASSERT_EQ(0, pthread_join(t, &retval));

    EXPECT_TRUE(g_int_exit_called.load())
        << "run_with_cleanup cleanup must fire when wrapped thread calls pthread_exit";
    EXPECT_TRUE(g_int_exit_released.load())
        << "ProfiledThread::release() must complete inside the wrapper cleanup";
    EXPECT_EQ(reinterpret_cast<void*>(99), retval);
}

#endif  // __linux__
