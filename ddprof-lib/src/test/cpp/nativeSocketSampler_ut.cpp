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

#include <gtest/gtest.h>

#if defined(__linux__) && defined(__GLIBC__)

#include "nativeSocketSampler.h"

#include <atomic>
#include <sys/socket.h>

// ---------------------------------------------------------------------------
// Stub tracking
// ---------------------------------------------------------------------------

static std::atomic<int>    g_send_calls{0};
static std::atomic<int>    g_recv_calls{0};
static std::atomic<ssize_t> g_send_ret{-1};
static std::atomic<ssize_t> g_recv_ret{-1};
static std::atomic<int>    g_write_calls{0};
static std::atomic<int>    g_read_calls{0};
static std::atomic<ssize_t> g_write_ret{-1};
static std::atomic<ssize_t> g_read_ret{-1};

static ssize_t stub_send(int /*fd*/, const void* /*buf*/, size_t /*len*/, int /*flags*/) {
    g_send_calls++;
    return g_send_ret.load();
}

static ssize_t stub_recv(int /*fd*/, void* /*buf*/, size_t /*len*/, int /*flags*/) {
    g_recv_calls++;
    return g_recv_ret.load();
}

static ssize_t stub_write(int /*fd*/, const void* /*buf*/, size_t /*len*/) {
    g_write_calls++;
    return g_write_ret.load();
}

static ssize_t stub_read(int /*fd*/, void* /*buf*/, size_t /*len*/) {
    g_read_calls++;
    return g_read_ret.load();
}

// ---------------------------------------------------------------------------
// Test fixture — installs stubs as the "original" function pointers so the
// hooks invoke them without needing GOT patching or a running JVM.
// ---------------------------------------------------------------------------

class NativeSocketSamplerHookTest : public ::testing::Test {
protected:
    NativeSocketSampler::send_fn  _saved_send;
    NativeSocketSampler::recv_fn  _saved_recv;
    NativeSocketSampler::write_fn _saved_write;
    NativeSocketSampler::read_fn  _saved_read;

    void SetUp() override {
        _saved_send  = NativeSocketSampler::_orig_send;
        _saved_recv  = NativeSocketSampler::_orig_recv;
        _saved_write = NativeSocketSampler::_orig_write;
        _saved_read  = NativeSocketSampler::_orig_read;
        NativeSocketSampler::_orig_send  = stub_send;
        NativeSocketSampler::_orig_recv  = stub_recv;
        NativeSocketSampler::_orig_write = stub_write;
        NativeSocketSampler::_orig_read  = stub_read;
        g_send_calls  = 0;
        g_recv_calls  = 0;
        g_write_calls = 0;
        g_read_calls  = 0;
    }

    void TearDown() override {
        NativeSocketSampler::_orig_send  = _saved_send;
        NativeSocketSampler::_orig_recv  = _saved_recv;
        NativeSocketSampler::_orig_write = _saved_write;
        NativeSocketSampler::_orig_read  = _saved_read;
    }
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

/**
 * Verifies that send_hook forwards the call to _orig_send and returns its
 * return value when the original function indicates failure (ret <= 0 so the
 * sampling path — which needs a JVM — is not entered).
 */
TEST_F(NativeSocketSamplerHookTest, SendHookCallsOrigSendAndReturnsValue) {
    g_send_ret = -1;  // error path avoids the JVM-dependent sampling code
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::send_hook(0, buf, sizeof(buf), 0);

    EXPECT_EQ(g_send_calls.load(), 1) << "send_hook must call _orig_send exactly once";
    EXPECT_EQ(ret, -1) << "send_hook must propagate the return value from _orig_send";
}

/**
 * Verifies that recv_hook forwards the call to _orig_recv and returns its
 * return value (same guard: ret <= 0 skips the JVM path).
 */
TEST_F(NativeSocketSamplerHookTest, RecvHookCallsOrigRecvAndReturnsValue) {
    g_recv_ret = 0;
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::recv_hook(0, buf, sizeof(buf), 0);

    EXPECT_EQ(g_recv_calls.load(), 1) << "recv_hook must call _orig_recv exactly once";
    EXPECT_EQ(ret, 0) << "recv_hook must propagate the return value from _orig_recv";
}

/**
 * Verifies that write_hook forwards the call to _orig_write and returns its
 * return value when the original function indicates failure (ret <= 0 skips
 * the sampling path that requires a running JVM).
 *
 * fd=0 (stdin) is not a TCP socket, so isSocket() returns false and
 * recordEvent() is never reached — the non-socket branch is exercised here.
 */
TEST_F(NativeSocketSamplerHookTest, WriteHookCallsOrigWriteAndReturnsValue) {
    g_write_ret = -1;  // error path avoids the JVM-dependent sampling code
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::write_hook(0, buf, sizeof(buf));

    EXPECT_EQ(g_write_calls.load(), 1) << "write_hook must call _orig_write exactly once";
    EXPECT_EQ(ret, -1) << "write_hook must propagate the return value from _orig_write";
}

/**
 * Verifies that read_hook forwards the call to _orig_read and returns its
 * return value (same guard: ret <= 0 skips the JVM path).
 *
 * fd=0 (stdin) is not a TCP socket, so the non-socket branch is exercised.
 */
TEST_F(NativeSocketSamplerHookTest, ReadHookCallsOrigReadAndReturnsValue) {
    g_read_ret = 0;
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::read_hook(0, buf, sizeof(buf));

    EXPECT_EQ(g_read_calls.load(), 1) << "read_hook must call _orig_read exactly once";
    EXPECT_EQ(ret, 0) << "read_hook must propagate the return value from _orig_read";
}

#endif // __linux__ && __GLIBC__

// ---------------------------------------------------------------------------
// Arguments parsing tests — no Linux/glibc guard needed.
// ---------------------------------------------------------------------------

#include "arguments.h"

/**
 * Verifies that a negative natsock interval is rejected by Arguments::parse.
 */
TEST(ArgumentsNatsock, NegativeIntervalRejected) {
    Arguments args;
    Error e = args.parse("natsock=-1us");
    ASSERT_TRUE(static_cast<bool>(e)) << "Expected error for negative natsock interval";
    ASSERT_NE(std::string(e.message()).find("must be >= 0"), std::string::npos)
        << "Error message should mention 'must be >= 0'";
}
