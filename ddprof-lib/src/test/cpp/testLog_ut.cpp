/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/common.h"

#include <algorithm>
#include <cerrno>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

#ifdef DEBUG

namespace {

// Points file descriptor 1 at a pipe for the lifetime of the object, so that
// what TEST_LOG writes can be read back.
class StdoutCapture {
public:
    StdoutCapture() {
        fflush(stdout);
        EXPECT_EQ(0, pipe(_fds));
        _saved = dup(STDOUT_FILENO);
        dup2(_fds[1], STDOUT_FILENO);
    }

    ~StdoutCapture() { restore(); }

    // Restores fd 1 and returns everything written to it meanwhile.
    std::string finish() {
        restore();
        std::string out;
        char buf[4096];
        ssize_t n;
        while ((n = read(_fds[0], buf, sizeof(buf))) > 0) {
            out.append(buf, (size_t)n);
        }
        close(_fds[0]);
        return out;
    }

private:
    int _fds[2] = {-1, -1};
    int _saved = -1;

    void restore() {
        if (_saved >= 0) {
            dup2(_saved, STDOUT_FILENO);
            close(_saved);
            close(_fds[1]);
            _saved = -1;
        }
    }
};

} // namespace

TEST(TestLogTest, WritesOneTaggedLine) {
    StdoutCapture capture;
    TEST_LOG("value=%d name=%s", 42, "spin");
    EXPECT_EQ("[TEST::INFO] value=42 name=spin\n", capture.finish());
}

// A signal handler that logs while its own thread is inside stdio would wait
// for the stdout lock forever. TEST_LOG must therefore not take that lock:
// here another thread holds it, and TEST_LOG still completes.
TEST(TestLogTest, DoesNotTakeTheStdoutLock) {
    // Set up before the lock is taken: StdoutCapture flushes stdout, and
    // nothing on this thread may touch stdio while the other thread holds it.
    StdoutCapture capture;
    std::mutex m;
    std::condition_variable cv;
    bool locked = false;
    bool release = false;
    std::thread holder([&] {
        flockfile(stdout);
        {
            std::lock_guard<std::mutex> lock(m);
            locked = true;
        }
        cv.notify_all();
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&] { return release; });
        funlockfile(stdout);
    });
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&] { return locked; });
    }

    std::future<void> logged = std::async(std::launch::async, [] { TEST_LOG("while stdout is locked"); });
    bool completed = logged.wait_for(std::chrono::seconds(2)) == std::future_status::ready;

    {
        std::lock_guard<std::mutex> lock(m);
        release = true;
    }
    cv.notify_all();
    holder.join();
    logged.wait();
    std::string out = capture.finish();

    EXPECT_TRUE(completed) << "TEST_LOG waited for the stdout lock";
    EXPECT_EQ("[TEST::INFO] while stdout is locked\n", out);
}

TEST(TestLogTest, CutsLongLinesAndKeepsTheNewline) {
    std::string long_value(5000, 'x');
    StdoutCapture capture;
    TEST_LOG("%s", long_value.c_str());
    std::string out = capture.finish();
    ASSERT_FALSE(out.empty());
    EXPECT_LT(out.size(), long_value.size());
    EXPECT_EQ(0u, out.rfind("[TEST::INFO] xxx", 0));
    EXPECT_EQ('\n', out.back());
    EXPECT_EQ(1, std::count(out.begin(), out.end(), '\n'));
}

// A signal handler must not change errno for the code it interrupted.
TEST(TestLogTest, PreservesErrno) {
    StdoutCapture capture;
    errno = ERANGE;
    TEST_LOG("errno check");
    EXPECT_EQ(ERANGE, errno);
    capture.finish();
}

#else

TEST(TestLogTest, OnlyInDebugBuilds) {
    GTEST_SKIP() << "TEST_LOG is a no-op without DEBUG";
}

#endif
