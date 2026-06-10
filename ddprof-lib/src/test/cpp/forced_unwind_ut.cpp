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
 *   glibc  – __pthread_register_cancel callback fires on pthread_cancel and
 *             pthread_exit.
 *   musl   – pthread_cleanup_push callback fires on pthread_cancel and
 *             pthread_exit.
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
// glibc path: __pthread_register_cancel / __pthread_unregister_cancel tests
// ===========================================================================
#ifdef __GLIBC__

// Redeclare glibc internals (hidden behind #ifndef __cplusplus in <pthread.h>).
extern "C" {
    extern void __pthread_register_cancel(__pthread_unwind_buf_t*);
    extern void __pthread_unregister_cancel(__pthread_unwind_buf_t*);
    [[noreturn]] extern void __pthread_unwind_next(__pthread_unwind_buf_t*);
}

// Helper: run `fn(arg)` with a glibc C-form cleanup handler that calls
// `cleanup(cleanup_arg)` if the thread is canceled or calls pthread_exit
// before fn returns.  Mirrors run_with_cleanup in libraryPatcher_linux.cpp.
static void run_with_cancel_handler(
        void (*fn)(void*), void* arg,
        void (*cleanup)(void*), void* cleanup_arg) {
    __pthread_unwind_buf_t cancel_buf;
    if (__builtin_expect(
            __sigsetjmp((struct __jmp_buf_tag*)(void*)cancel_buf.__cancel_jmp_buf, 0), 0)) {
        cleanup(cleanup_arg);
        __pthread_unwind_next(&cancel_buf);
    }
    __pthread_register_cancel(&cancel_buf);
    fn(arg);
    __pthread_unregister_cancel(&cancel_buf);
    cleanup(cleanup_arg);
}

// ---------------------------------------------------------------------------

static std::atomic<bool> g_bare_cleanup_called{false};

static void bare_cleanup(void*) {
    g_bare_cleanup_called.store(true, std::memory_order_relaxed);
}

static void bare_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* bare_cancel_thread(void*) {
    g_bare_cleanup_called.store(false, std::memory_order_relaxed);
    run_with_cancel_handler(bare_spin, nullptr, bare_cleanup, nullptr);
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

static void profiled_spin(void*) {
    while (true) {
        pthread_testcancel();
        usleep(100);
    }
}

static void* profiled_cancel_thread(void*) {
    g_pt_cleanup_called.store(false, std::memory_order_relaxed);
    g_pt_release_called.store(false, std::memory_order_relaxed);
    ProfiledThread::initCurrentThread();
    run_with_cancel_handler(profiled_spin, nullptr, profiled_cleanup, nullptr);
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

static void exit_fn(void*) {
    pthread_exit(reinterpret_cast<void*>(42));
}

static void* exit_thread(void*) {
    g_exit_cleanup_called.store(false, std::memory_order_relaxed);
    run_with_cancel_handler(exit_fn, nullptr, exit_cleanup, nullptr);
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
