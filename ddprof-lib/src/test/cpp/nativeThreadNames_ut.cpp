/*
 * Copyright 2026 Datadog, Inc
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

// Integration tests for Profiler::updateNativeThreadNames(bool), PROF-15139.
//
// The periodic refresher calls updateNativeThreadNames(true), which must skip
// a thread whose /proc comm still equals the process's own (inherited) name:
// such a thread is likely mid-initialization and recording it would latch a
// provisional name permanently (ThreadInfo is first-writer-wins). The dump-time
// pass calls updateNativeThreadNames(false), which records the name regardless.
//
// These tests spawn real parked threads and observe the recorded names via the
// UNIT_TEST-only Profiler::threadNameForTest hook, so they exercise the actual
// /proc resolution and defer predicate rather than re-stating the ThreadInfo
// contract (covered by threadInfo_ut.cpp). Linux-only: the deferral depends on
// /proc comm and pthread name inheritance.

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

// A thread that optionally sets its own pthread name, publishes its tid, then
// parks until released. Parking keeps it visible in OS::listThreads() across
// the updateNativeThreadNames() scans under test.
struct ParkedThread {
    std::string set_name;              // empty => leave the inherited comm
    std::atomic<int> tid{-1};
    std::atomic<bool> ready{false};
    std::atomic<bool> stop{false};
    pthread_t handle{};

    static void* run(void* arg) {
        ParkedThread* self = static_cast<ParkedThread*>(arg);
        if (!self->set_name.empty()) {
            // Linux caps the pthread name at 16 bytes incl. NUL; callers keep
            // set_name short enough to survive without truncation.
            pthread_setname_np(pthread_self(), self->set_name.c_str());
        }
        self->tid.store(OS::threadId(), std::memory_order_release);
        self->ready.store(true, std::memory_order_release);
        while (!self->stop.load(std::memory_order_acquire)) {
            struct timespec ts{0, 1000000};  // 1ms
            nanosleep(&ts, nullptr);
        }
        return nullptr;
    }

    void start() {
        ASSERT_EQ(0, pthread_create(&handle, nullptr, &ParkedThread::run, this));
        // Bounded spin: the thread publishes ready almost immediately.
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

std::string processComm() {
    char buf[64];
    EXPECT_TRUE(OS::threadName(OS::processId(), buf, sizeof(buf)));
    return std::string(buf);
}

}  // namespace

// A thread that has set its own (non-inherited) name is recorded by the
// deferring periodic scan: it is not mid-initialization.
TEST(NativeThreadNamesTest, deferringScanRecordsRealName) {
    const std::string real_name = "ut-real-name";  // 12 chars, fits the 16B cap
    ASSERT_NE(real_name, processComm());

    ParkedThread t;
    t.set_name = real_name;
    t.start();
    int tid = t.tid.load();

    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/true);

    EXPECT_EQ(real_name, Profiler::instance()->threadNameForTest(tid));

    t.join();
}

// A thread still showing the inherited process name is skipped by the deferring
// scan (so the provisional name is not latched), but recorded by the dump-time
// scan, which does not defer.
TEST(NativeThreadNamesTest, deferringScanSkipsInheritedNameDumpScanRecordsIt) {
    const std::string proc_comm = processComm();

    ParkedThread t;  // no set_name => inherits the parent's (process) comm
    t.start();
    int tid = t.tid.load();
    // Sanity: the child really is showing the inherited process name.
    char buf[64];
    ASSERT_TRUE(OS::threadName(tid, buf, sizeof(buf)));
    ASSERT_EQ(proc_comm, std::string(buf));

    // Deferring scan: must skip it, leaving the tid unrecorded.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/true);
    EXPECT_EQ("", Profiler::instance()->threadNameForTest(tid));

    // Dump-time scan: records the name even though it equals the process comm.
    Profiler::instance()->updateNativeThreadNames(/*defer_initializing=*/false);
    EXPECT_EQ(proc_comm, Profiler::instance()->threadNameForTest(tid));

    t.join();
}

#endif  // __linux__
