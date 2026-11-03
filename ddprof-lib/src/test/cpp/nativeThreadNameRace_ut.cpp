/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Reproducer for PROF-12574: missing thread names from method wall profiling
// samples for threads that die before any native-thread-name pass can see
// them.
//
// Wall-clock sampling enumerates every thread in /proc/self/task
// (WallClockASGCT::timerLoop, wallClock.cpp), so JVM-internal and other
// non-java.lang.Thread threads are sampled even though JVMTI never posts
// ThreadStart/ThreadEnd for them (see hotspot/vmStructs.cpp). Their only name
// sources are the /proc comm scans: the Libraries refresher pass
// (updateNativeThreadNames(true), every NATIVE_THREAD_NAME_INTERVAL_NS = 2s,
// libraries.cpp) and the dump-time pass (updateNativeThreadNames(false),
// Profiler::dump, profiler.cpp). A non-Java thread whose entire lifetime fits
// between two refresher passes and before the dump is therefore sampled and
// flushed by Recording::writeThreads with no ThreadInfo entry, rendering the
// fallback "[tid=N]" with java thread id 0 (flightRecorder.cpp).
//
// These tests pin down the naming side of that sequence deterministically:
// the name passes themselves are proven unable to recover the name of a
// thread that has already exited, while an identical thread that survives
// until the dump-time pass IS named. The sampled-side half (the wall engine
// really samples such threads) is established by the timerLoop enumeration
// cited above and is exercised end-to-end by the JVM integration tests.

#ifdef __linux__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <gtest/gtest.h>
#include <pthread.h>
#include <time.h>
#include <atomic>
#include <string>
#include "../../main/cpp/profiler.h"
#include "../../main/cpp/os.h"

namespace {

// A thread that publishes its tid, optionally sets its own pthread name, and
// exits once released. When stop is pre-set the thread's whole life is a few
// milliseconds -- short enough to fit between two refresher passes.
struct EphemeralThread {
    std::string set_name;              // empty => leave the inherited comm
    std::atomic<int> tid{-1};
    std::atomic<bool> ready{false};
    std::atomic<bool> stop{false};
    pthread_t handle{};

    static void* run(void* arg) {
        EphemeralThread* self = static_cast<EphemeralThread*>(arg);
        if (!self->set_name.empty()) {
            // Linux caps the pthread name at 16 bytes incl. NUL; callers keep
            // set_name short enough to survive without truncation.
            pthread_setname_np(pthread_self(), self->set_name.c_str());
        }
        self->tid.store(OS::threadId(), std::memory_order_release);
        self->ready.store(true, std::memory_order_release);
        // Stay briefly alive (visible in /proc/self/task) so the thread has a
        // window during which a wall-clock sample could be taken, then exit.
        while (!self->stop.load(std::memory_order_acquire)) {
            struct timespec ts{0, 1000000};  // 1ms
            nanosleep(&ts, nullptr);
        }
        return nullptr;
    }

    void start() {
        ASSERT_EQ(0, pthread_create(&handle, nullptr, &EphemeralThread::run, this));
        for (int i = 0; i < 5000 && !ready.load(std::memory_order_acquire); i++) {
            struct timespec ts{0, 1000000};  // 1ms
            nanosleep(&ts, nullptr);
        }
        ASSERT_TRUE(ready.load(std::memory_order_acquire));
        ASSERT_GT(tid.load(std::memory_order_acquire), 0);
    }

    void join() {
        stop.store(true, std::memory_order_release);
        pthread_join(handle, nullptr);
    }
};

}  // namespace

// The core of the PROF-12574 residual gap: a non-Java thread that dies before
// the first scan that could have observed it is never named, by any pass --
// not by the deferring refresher-style scan, and not by the dump-time scan,
// which only sees threads still present in /proc/self/task.
TEST(NativeThreadNameRaceTest, threadDyingBetweenScansIsNeverNamed) {
    // Refresher-style pass before the thread exists (the previous tick).
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/true);

    EphemeralThread t;  // unnamed => inherits the process comm
    t.start();
    int tid = t.tid.load();
    t.join();

    // Next refresher-style pass: the thread is already gone from
    // /proc/self/task, so the scan cannot record its name.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/true);
    // Dump-time pass (no deferral): same result -- nothing left to scan.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/false);

    // No naming path ever recorded the thread. Recording::writeThreads will
    // render its samples as "[tid=N]" with java thread id 0.
    EXPECT_EQ("", Profiler::instance()->threadNameForTest(tid));
}

// Control for the test above: the ONLY variable is death timing. An identical
// thread that survives until the dump-time pass is named by it.
TEST(NativeThreadNameRaceTest, identicalThreadAliveAtDumpScanIsNamed) {
    const std::string proc_comm = [] {
        char buf[64];
        EXPECT_TRUE(OS::threadName(OS::processId(), buf, sizeof(buf)));
        return std::string(buf);
    }();

    EphemeralThread t;  // unnamed => inherits the process comm
    t.start();
    int tid = t.tid.load();

    // Refresher-style pass: defers it (inherited process name), records
    // nothing -- same as in the dying-thread test.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/true);
    EXPECT_EQ("", Profiler::instance()->threadNameForTest(tid));

    // Dump-time pass while the thread is still alive: records the name.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/false);
    EXPECT_EQ(proc_comm, Profiler::instance()->threadNameForTest(tid));

    t.join();
}

#endif  // __linux__
