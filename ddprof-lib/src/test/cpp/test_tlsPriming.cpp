/*
 * Copyright 2025, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "os.h"
#include "common.h"
#include "thread.h"
#include <signal.h>
#include <unistd.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>

namespace {

static std::atomic<int> g_signal_received{0};
static std::atomic<int> g_threads_primed{0};

// Simple TLS test POD
thread_local uint64_t g_test_tls = 0;

void testTlsSignalHandler(int signo) {
    g_signal_received++;
    g_test_tls = 0x1234ABCD;  // Touch TLS to prime it
    g_threads_primed++;
}

class TlsPrimingTest : public ::testing::Test {
protected:
    void SetUp() override {
        g_signal_received.store(0);
        g_threads_primed.store(0);
        g_test_tls = 0;
    }
};

TEST_F(TlsPrimingTest, InstallSignalHandler) {
    int signal_num = OS::installTlsPrimeSignalHandler(testTlsSignalHandler, 5);
    
#ifdef __linux__
    if (signal_num > 0) {
        TEST_LOG("Successfully installed RT signal handler for signal %d", signal_num);
        EXPECT_GT(signal_num, SIGRTMIN);
        EXPECT_LE(signal_num, SIGRTMAX);
    } else {
        TEST_LOG("RT signal installation failed (may indicate signal exhaustion)");
        EXPECT_EQ(signal_num, -1);
    }
#elif defined(__APPLE__)
    TEST_LOG("TLS prime signal handler not supported on macOS");
    EXPECT_EQ(signal_num, -1);
#else
    TEST_LOG("TLS prime signal handler not supported on this platform");
    EXPECT_EQ(signal_num, -1);
#endif
}

TEST_F(TlsPrimingTest, EnumerateThreadIds) {
    std::atomic<int> thread_count{0};
    
    OS::enumerateThreadIds([&](int tid) {
        TEST_LOG("Found thread ID: %d", tid);
#ifdef __linux__
        EXPECT_GT(tid, 0);  // Linux uses actual thread IDs > 0
#endif
        thread_count++;
    });
    
    TEST_LOG("Found %d threads total", thread_count.load());
    
    // Should find at least the current thread on all platforms that implement enumeration
    EXPECT_GE(thread_count.load(), 1);
}

TEST_F(TlsPrimingTest, GetThreadCount) {
    int count = OS::getThreadCount();
    TEST_LOG("Thread count: %d", count);
    
    // Should be at least 1 on platforms that implement thread counting
    EXPECT_GE(count, 1);
}

TEST_F(TlsPrimingTest, SignalCurrentThread) {
    int signal_num = OS::installTlsPrimeSignalHandler(testTlsSignalHandler, 6);

#ifdef __linux__
    if (signal_num > 0) {
        TEST_LOG("Signaling current thread with signal %d", signal_num);

        // Get the first thread ID from enumeration
        std::atomic<int> first_tid{-1};
        OS::enumerateThreadIds([&](int tid) {
            if (first_tid.load() == -1) {
                first_tid.store(tid);
            }
        });

        int tid = first_tid.load();
        if (tid >= 0) {
            OS::signalThread(tid, signal_num);

            // Wait a bit for signal to be delivered
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            EXPECT_GT(g_signal_received.load(), 0);
            EXPECT_GT(g_threads_primed.load(), 0);
            EXPECT_EQ(g_test_tls, 0x1234ABCD);

            TEST_LOG("Signal delivered successfully, TLS primed");
        } else {
            TEST_LOG("No threads found for signaling");
            FAIL() << "Thread enumeration should find at least one thread";
        }
    } else {
        TEST_LOG("TLS prime signaling failed to install handler");
        FAIL() << "Signal handler installation should succeed on Linux";
    }
#else
    TEST_LOG("TLS prime signaling not supported on this platform");
    EXPECT_EQ(signal_num, -1);
#endif
}

// Test TLS cleanup for JVMTI-allocated threads (non-buffer)
TEST_F(TlsPrimingTest, JvmtiThreadCleanup) {
    TEST_LOG("Testing JVMTI-allocated thread cleanup");

    std::atomic<bool> thread_done{false};
    std::atomic<int> tid_observed{0};

    // Create a thread that simulates JVMTI initialization
    std::thread test_thread([&]() {
        // Simulate JVMTI callback: initCurrentThread()
        ProfiledThread::initCurrentThread();

        // Verify TLS is initialized
        ProfiledThread* tls = ProfiledThread::current();
        ASSERT_NE(tls, nullptr);

        tid_observed.store(tls->tid());
        TEST_LOG("JVMTI thread initialized with TID: %d", tls->tid());

        // Verify this is NOT a buffer-allocated thread
        // (buffer_pos should be -1 for JVMTI threads)
        // We can't directly access _buffer_pos, but we can verify behavior

        thread_done.store(true);
        // When thread exits, pthread should call freeKey() which should delete the instance
    });

    test_thread.join();

    EXPECT_TRUE(thread_done.load());
    EXPECT_GT(tid_observed.load(), 0);
    TEST_LOG("JVMTI thread cleanup completed (instance should be deleted)");
}

// Test TLS cleanup for buffer-allocated threads (signal priming)
TEST_F(TlsPrimingTest, BufferThreadCleanup) {
#ifdef __linux__
    TEST_LOG("Testing buffer-allocated thread cleanup");

    // Initialize the buffer system
    ProfiledThread::initExistingThreads();

    std::atomic<bool> thread_initialized{false};
    std::atomic<bool> thread_done{false};
    std::atomic<int> tid_observed{0};

    // Create a thread that simulates signal-based priming
    std::thread test_thread([&]() {
        // Directly call buffer initialization (simulating signal handler)
        // This is what simpleTlsSignalHandler() does for native threads
        ProfiledThread::initCurrentThreadWithBuffer();

        // Verify TLS is initialized from buffer
        ProfiledThread* tls = ProfiledThread::currentSignalSafe();
        if (tls != nullptr) {
            tid_observed.store(tls->tid());
            thread_initialized.store(true);
            TEST_LOG("Buffer thread initialized with TID: %d", tls->tid());
        }

        thread_done.store(true);
        // When thread exits, pthread should call freeKey() which should recycle the buffer slot
    });

    test_thread.join();

    EXPECT_TRUE(thread_done.load());
    EXPECT_TRUE(thread_initialized.load());
    EXPECT_GT(tid_observed.load(), 0);
    TEST_LOG("Buffer thread cleanup completed (slot should be recycled)");

    // Cleanup
    ProfiledThread::cleanupTlsPriming();
#else
    TEST_LOG("Buffer-allocated thread cleanup test only supported on Linux");
#endif
}

// Test that buffer slots are properly recycled
TEST_F(TlsPrimingTest, BufferSlotRecycling) {
#ifdef __linux__
    TEST_LOG("Testing buffer slot recycling");

    ProfiledThread::initExistingThreads();

    std::vector<int> tids_observed;
    const int num_threads = 10;

    for (int i = 0; i < num_threads; i++) {
        std::atomic<int> tid{0};

        std::thread test_thread([&]() {
            ProfiledThread::initCurrentThreadWithBuffer();
            ProfiledThread* tls = ProfiledThread::currentSignalSafe();
            if (tls != nullptr) {
                tid.store(tls->tid());
            }
        });

        test_thread.join();

        if (tid.load() > 0) {
            tids_observed.push_back(tid.load());
        }
    }

    EXPECT_EQ(tids_observed.size(), num_threads);
    TEST_LOG("Created and recycled %d buffer slots", num_threads);

    // Verify all threads got valid TIDs
    for (size_t i = 0; i < tids_observed.size(); i++) {
        EXPECT_GT(tids_observed[i], 0) << "Thread " << i << " got invalid TID";
    }

    ProfiledThread::cleanupTlsPriming();
#else
    TEST_LOG("Buffer slot recycling test only supported on Linux");
#endif
}

// Test mixed JVMTI and buffer-allocated thread cleanup
TEST_F(TlsPrimingTest, MixedThreadCleanup) {
#ifdef __linux__
    TEST_LOG("Testing mixed JVMTI and buffer-allocated thread cleanup");

    ProfiledThread::initExistingThreads();

    std::atomic<int> jvmti_count{0};
    std::atomic<int> buffer_count{0};

    std::vector<std::thread> threads;

    // Create mix of JVMTI-style and buffer-style threads
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            // JVMTI-style thread
            threads.emplace_back([&]() {
                ProfiledThread::initCurrentThread();
                ProfiledThread* tls = ProfiledThread::current();
                if (tls != nullptr) {
                    jvmti_count++;
                }
            });
        } else {
            // Buffer-style thread
            threads.emplace_back([&]() {
                ProfiledThread::initCurrentThreadWithBuffer();
                ProfiledThread* tls = ProfiledThread::currentSignalSafe();
                if (tls != nullptr) {
                    buffer_count++;
                }
            });
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    EXPECT_EQ(jvmti_count.load(), 5);
    EXPECT_EQ(buffer_count.load(), 5);
    TEST_LOG("Mixed cleanup: %d JVMTI threads (deleted), %d buffer threads (recycled)",
             jvmti_count.load(), buffer_count.load());

    ProfiledThread::cleanupTlsPriming();
#else
    TEST_LOG("Mixed thread cleanup test only supported on Linux");
#endif
}

} // namespace