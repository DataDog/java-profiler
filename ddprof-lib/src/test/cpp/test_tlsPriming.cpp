/*
 * Copyright 2025, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "os_dd.h"
#include "common.h"
#include <signal.h>
#include <unistd.h>
#include <atomic>
#include <thread>
#include <chrono>

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
    int signal_num = ddprof::OS::installTlsPrimeSignalHandler(testTlsSignalHandler, 5);
    
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
    
    ddprof::OS::enumerateThreadIds([&](int tid) {
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
    int count = ddprof::OS::getThreadCount();
    TEST_LOG("Thread count: %d", count);
    
    // Should be at least 1 on platforms that implement thread counting
    EXPECT_GE(count, 1);
}

TEST_F(TlsPrimingTest, SignalCurrentThread) {
    int signal_num = ddprof::OS::installTlsPrimeSignalHandler(testTlsSignalHandler, 6);
    
#ifdef __linux__
    if (signal_num > 0) {
        TEST_LOG("Signaling current thread with signal %d", signal_num);
        
        // Get the first thread ID from enumeration
        std::atomic<int> first_tid{-1};
        ddprof::OS::enumerateThreadIds([&](int tid) {
            if (first_tid.load() == -1) {
                first_tid.store(tid);
            }
        });
        
        int tid = first_tid.load();
        if (tid >= 0) {
            ddprof::OS::signalThread(tid, signal_num);
            
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

TEST_F(TlsPrimingTest, ThreadDirectoryWatcher) {
    std::atomic<int> new_threads{0};
    std::atomic<int> dead_threads{0};
    
    bool started = ddprof::OS::startThreadDirectoryWatcher(
        [&](int tid) {
            TEST_LOG("New thread detected: %d", tid);
            new_threads++;
        },
        [&](int tid) {
            TEST_LOG("Thread died: %d", tid);
            dead_threads++;
        }
    );
    
    if (started) {
        TEST_LOG("Thread directory watcher started successfully");
        
        // Create a short-lived thread to trigger the watcher
        std::thread test_thread([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        });
        
        test_thread.join();
        
        // Wait for watcher to detect changes
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        ddprof::OS::stopThreadDirectoryWatcher();
        TEST_LOG("Thread directory watcher stopped");
        
        // We might see events, but it's not guaranteed due to timing
        TEST_LOG("Detected %d new threads, %d dead threads", 
                new_threads.load(), dead_threads.load());
    } else {
        TEST_LOG("Thread directory watcher not supported on this platform");
    }
}

} // namespace