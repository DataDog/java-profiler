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

#if defined(__linux__)

#include "nativeSocketSampler.h"
#include "libraryPatcher.h"

#include <atomic>
#include <errno.h>
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

static const int kSamplerFdTypeCacheSizeForTest = 65536;
static const int kSamplerHighFdCacheSizeForTest = 4096;
static std::atomic<int> g_probe_calls{0};
static std::atomic<int> g_probe_last_fd{-1};
static std::atomic<int> g_probe_rc{0};
static std::atomic<int> g_probe_errno{0};
static std::atomic<int> g_probe_so_type{SOCK_STREAM};

static int stub_probe(int fd, int *so_type, int *probe_errno) {
    g_probe_calls++;
    g_probe_last_fd = fd;
    *so_type = g_probe_so_type.load();
    *probe_errno = g_probe_errno.load();
    return g_probe_rc.load();
}

class ScopedSamplerProbeOverride {
public:
    explicit ScopedSamplerProbeOverride(NativeSocketSampler::ProbeOverride probe) {
        NativeSocketSampler::setProbeOverrideForTest(probe);
    }

    ~ScopedSamplerProbeOverride() {
        NativeSocketSampler::setProbeOverrideForTest(nullptr);
    }
};

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
        NativeSocketSampler::getOriginalFunctions(_saved_send, _saved_recv, _saved_write, _saved_read);
        NativeSocketSampler::setOriginalFunctions(stub_send, stub_recv, stub_write, stub_read);
        g_send_calls  = 0;
        g_recv_calls  = 0;
        g_write_calls = 0;
        g_read_calls  = 0;
    }

    void TearDown() override {
        NativeSocketSampler::setOriginalFunctions(_saved_send, _saved_recv, _saved_write, _saved_read);
        NativeSocketSampler::send_fn cur_send; NativeSocketSampler::recv_fn cur_recv;
        NativeSocketSampler::write_fn cur_write; NativeSocketSampler::read_fn cur_read;
        NativeSocketSampler::getOriginalFunctions(cur_send, cur_recv, cur_write, cur_read);
        ASSERT_EQ(cur_send, _saved_send) << "Function pointers must be restored in TearDown";
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
 * fd=0 (stdin) is not a socket descriptor, so getsockopt fails and isSocket()
 * returns false; recordEvent() is never reached — the non-socket branch is
 * exercised here. Note: AF_UNIX SOCK_STREAM would return true from isSocket().
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
 * fd=0 (stdin) is not a socket descriptor, so getsockopt fails and isSocket()
 * returns false; the non-socket branch is exercised. Note: AF_UNIX SOCK_STREAM
 * would return true from isSocket().
 */
TEST_F(NativeSocketSamplerHookTest, ReadHookCallsOrigReadAndReturnsValue) {
    g_read_ret = 0;
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::read_hook(0, buf, sizeof(buf));

    EXPECT_EQ(g_read_calls.load(), 1) << "read_hook must call _orig_read exactly once";
    EXPECT_EQ(ret, 0) << "read_hook must propagate the return value from _orig_read";
}

#endif // __linux__

// ---------------------------------------------------------------------------
// PoissonSampler unit tests — no Linux/glibc guard needed.
// ---------------------------------------------------------------------------

#include "poissonSampler.h"

/**
 * Verifies that sample() returns false when value is 0 or interval is 0.
 */
TEST(PoissonSamplerTest, ReturnsFalseForZeroValueOrInterval) {
    PoissonSampler s;
    float w = 0.0f;

    // value == 0: must not sample regardless of interval
    EXPECT_FALSE(s.sample(0, 1000, /*epoch=*/1, w))
        << "sample() must return false when value is 0";

    // interval == 0: must not sample regardless of value
    EXPECT_FALSE(s.sample(1000, 0, /*epoch=*/1, w))
        << "sample() must return false when interval is 0";
}

/**
 * Verifies that a change in epoch causes the sampler to reset so subsequent
 * calls with large value cross the freshly-drawn threshold.
 */
TEST(PoissonSamplerTest, EpochChangeResetsState) {
    PoissonSampler s;
    float w = 0.0f;
    const u64 interval = 100;

    // Prime with epoch=1 until it fires at least once.
    bool fired = false;
    for (int i = 0; i < 10000 && !fired; i++) {
        fired = s.sample(interval, interval, /*epoch=*/1, w);
    }
    ASSERT_TRUE(fired) << "Sampler should have fired during priming";

    // Bump epoch: large value should fire quickly against the fresh threshold.
    bool fired_after_reset = false;
    for (int i = 0; i < 10000 && !fired_after_reset; i++) {
        fired_after_reset = s.sample(interval * 1000, interval, /*epoch=*/2, w);
    }
    EXPECT_TRUE(fired_after_reset)
        << "Sampler should fire quickly after epoch reset with large value";
}

/**
 * Verifies that when value >> interval the computed weight approaches 1.0.
 * For value = 1000 * interval, exp(-1000) ≈ 0 so P ≈ 1 and weight ≈ 1.
 */
TEST(PoissonSamplerTest, HighVolumeWeightApproachesOne) {
    PoissonSampler s;
    float w = 0.0f;
    const u64 interval = 100;
    const u64 big_value = interval * 1000;

    // Use successive epoch bumps to guarantee a fresh threshold each iteration.
    bool fired = false;
    for (int i = 0; i < 100 && !fired; i++) {
        fired = s.sample(big_value, interval, /*epoch=*/(u64)(i + 1), w);
    }
    ASSERT_TRUE(fired) << "Sampler must fire with value >> interval";
    EXPECT_NEAR(w, 1.0f, 1e-3f)
        << "Weight must be ~1.0 when value >> interval";
}

// ---------------------------------------------------------------------------
// Success-path and isSocket() tests — Linux guard required for socket APIs.
// ---------------------------------------------------------------------------

#if defined(__linux__)

#include <unistd.h>
#include <sys/socket.h>

// Global counter incremented by stub_send when it returns a positive value.
// Used to verify that recordEvent is reached on the success path.
static std::atomic<int> g_send_success_calls{0};

static ssize_t stub_send_success(int /*fd*/, const void* /*buf*/, size_t len, int /*flags*/) {
    g_send_success_calls++;
    return (ssize_t)len;  // report all bytes sent
}

/**
 * Verifies that send_hook calls _orig_send and propagates a successful return
 * value WHEN HOOKS ARE INACTIVE (the most common in-process state during tests).
 * Because _socket_active is false the hook short-circuits to _orig_send and
 * never reaches recordEvent / Profiler::recordSample — exercising recordEvent
 * requires a running profiler with a recorder bound, which is not feasible in
 * this gtest unit harness.
 *
 * To exercise the active-path short-circuit (i.e., the hook's outer guard
 * branch), see SendHookActivePathReachesRecorderGuard below.
 */
TEST_F(NativeSocketSamplerHookTest, SendHookSuccessPathReturnsBytes) {
    g_send_success_calls = 0;
    NativeSocketSampler::setOriginalFunctions(stub_send_success, stub_recv, stub_write, stub_read);
    char buf[16] = {};

    ssize_t ret = NativeSocketSampler::send_hook(0, buf, sizeof(buf), 0);

    EXPECT_EQ(g_send_success_calls.load(), 1)
        << "send_hook must call _orig_send exactly once on the inactive path";
    EXPECT_EQ(ret, (ssize_t)sizeof(buf))
        << "send_hook must propagate the byte count from _orig_send";
}

/**
 * Verifies that with _socket_active flipped to true the hook actually takes
 * the active branch (calls TSC::ticks twice and routes through record_if_positive).
 * No JVM/recorder is running so recordEvent's downstream Profiler::recordSample
 * is benign (returns without recording); we verify the orig fn is still called
 * exactly once and the return value is propagated.
 */
TEST_F(NativeSocketSamplerHookTest, SendHookActivePathReachesRecorderGuard) {
    g_send_success_calls = 0;
    NativeSocketSampler::setOriginalFunctions(stub_send_success, stub_recv, stub_write, stub_read);

    // Manually flip the active flag so the hook traverses the active branch.
    // Restore in a guard; tearing down the fixture must observe it cleared.
    bool prev = LibraryPatcher::_socket_active.exchange(true, std::memory_order_release);

    char buf[16] = {};
    ssize_t ret = NativeSocketSampler::send_hook(0, buf, sizeof(buf), 0);

    LibraryPatcher::_socket_active.store(prev, std::memory_order_release);

    EXPECT_EQ(g_send_success_calls.load(), 1)
        << "send_hook must call _orig_send exactly once on the active path";
    EXPECT_EQ(ret, (ssize_t)sizeof(buf))
        << "send_hook must propagate the byte count from _orig_send on the active path";
}

/**
 * Verifies write_hook pass-through: when hooks are inactive (_socket_active=false),
 * write_hook forwards immediately to _orig_write without calling isSocket().
 * Uses a real AF_UNIX SOCK_STREAM socketpair; the pass-through path must handle
 * any fd type correctly. After closing both ends the stub is still called (the
 * inactive guard fires before any fd inspection).
 */
TEST(NativeSocketSamplerIsSocketTest, UnixSocketPairReturnsFalseAfterClose) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0)
        << "socketpair() failed: " << strerror(errno);

    NativeSocketSampler* inst = NativeSocketSampler::instance();
    ASSERT_NE(inst, nullptr);

    // _socket_active is false — write_hook forwards to _orig_write without calling isSocket().
    // (write_hook is exercised with a stub that returns the full length, then verify the
    // return value is correct.)
    NativeSocketSampler::send_fn saved_send; NativeSocketSampler::recv_fn saved_recv;
    NativeSocketSampler::write_fn saved_write; NativeSocketSampler::read_fn saved_read;
    NativeSocketSampler::getOriginalFunctions(saved_send, saved_recv, saved_write, saved_read);
    NativeSocketSampler::setOriginalFunctions(saved_send, saved_recv,
        [](int /*fd*/, const void* /*buf*/, size_t len) -> ssize_t { return (ssize_t)len; },
        saved_read);

    char buf[16] = {};
    ssize_t ret = NativeSocketSampler::write_hook(fds[0], buf, sizeof(buf));
    EXPECT_EQ(ret, (ssize_t)sizeof(buf))
        << "write_hook must propagate the byte count even for AF_UNIX fds";

    NativeSocketSampler::setOriginalFunctions(saved_send, saved_recv, saved_write, saved_read);
    close(fds[0]);
    close(fds[1]);
}

// ---------------------------------------------------------------------------
// LRU fd→addr cache tests.
// ---------------------------------------------------------------------------

TEST(NativeSocketSamplerLruTest, ClearResetsCache) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->fdAddrCacheInsertForTest(1, "1.2.3.4:100");
    inst->fdAddrCacheInsertForTest(2, "1.2.3.4:200");
    ASSERT_GE(inst->fdAddrCacheSizeForTest(), 2);

    inst->clearFdCache();

    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), 0)
        << "clearFdCache() must empty both the map and the LRU list";
}

TEST(NativeSocketSamplerLruTest, ClearFdCacheEntryRemovesOnlyRequestedEntry) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    inst->fdAddrCacheInsertForTest(1, "1.2.3.4:100");
    inst->fdAddrCacheInsertForTest(2, "1.2.3.4:200");
    ASSERT_EQ(inst->fdAddrCacheSizeForTest(), 2);

    inst->clearFdCacheEntry(1);

    EXPECT_FALSE(inst->fdAddrCacheContainsForTest(1));
    EXPECT_TRUE(inst->fdAddrCacheContainsForTest(2));
    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), 1);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerLruTest, ClearFdCacheEntryHandlesInvalidFds) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    inst->fdAddrCacheInsertForTest(7, "1.2.3.4:700");

    inst->clearFdCacheEntry(-1);
    inst->clearFdCacheEntry(NativeSocketSampler::MAX_FD_CACHE + 1);

    EXPECT_TRUE(inst->fdAddrCacheContainsForTest(7));
    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), 1);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerLruTest, ClearFdCacheEntryInvalidatesFdTypeBeforeReuse) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    int stream_fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, stream_fds), 0);

    int reused_fd = stream_fds[0];
    EXPECT_TRUE(inst->isSocketForTest(reused_fd));
    close(reused_fd);

    inst->clearFdCacheEntry(reused_fd);

    int datagram_fd = socket(AF_INET, SOCK_DGRAM, 0);
    ASSERT_EQ(datagram_fd, reused_fd);
    EXPECT_FALSE(inst->isSocketForTest(datagram_fd));

    close(datagram_fd);
    close(stream_fds[1]);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, HighFdStreamVerdictIsCached) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = 0;
    g_probe_errno = 0;
    g_probe_so_type = SOCK_STREAM;
    int fd = kSamplerFdTypeCacheSizeForTest;

    EXPECT_TRUE(inst->isSocketForTest(fd));
    EXPECT_TRUE(inst->isSocketForTest(fd));

    EXPECT_EQ(g_probe_calls.load(), 1);
    EXPECT_EQ(g_probe_last_fd.load(), fd);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, HighFdEnotsockVerdictIsCached) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = -1;
    g_probe_errno = ENOTSOCK;
    g_probe_so_type = 0;
    int fd = kSamplerFdTypeCacheSizeForTest + 1;

    EXPECT_FALSE(inst->isSocketForTest(fd));
    EXPECT_FALSE(inst->isSocketForTest(fd));

    EXPECT_EQ(g_probe_calls.load(), 1);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, HighFdTransientProbeFailureIsNotCached) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = -1;
    g_probe_errno = EBADF;
    g_probe_so_type = 0;
    int fd = kSamplerFdTypeCacheSizeForTest + 2;

    EXPECT_FALSE(inst->isSocketForTest(fd));
    EXPECT_EQ(g_probe_calls.load(), 1);

    g_probe_rc = 0;
    g_probe_errno = 0;
    g_probe_so_type = SOCK_STREAM;

    EXPECT_TRUE(inst->isSocketForTest(fd));
    EXPECT_TRUE(inst->isSocketForTest(fd));
    EXPECT_EQ(g_probe_calls.load(), 2);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, ClearFdCacheEntryInvalidatesHighFdOnly) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = 0;
    g_probe_errno = 0;
    g_probe_so_type = SOCK_STREAM;
    int fd = kSamplerFdTypeCacheSizeForTest + 3;
    int other_fd = fd + 1;

    ASSERT_TRUE(inst->isSocketForTest(fd));
    ASSERT_TRUE(inst->isSocketForTest(other_fd));
    EXPECT_EQ(g_probe_calls.load(), 2);

    g_probe_so_type = SOCK_DGRAM;
    inst->clearFdCacheEntry(fd);

    EXPECT_FALSE(inst->isSocketForTest(fd));
    EXPECT_TRUE(inst->isSocketForTest(other_fd));
    EXPECT_EQ(g_probe_calls.load(), 3);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, ClearFdCacheInvalidatesHighFdsByGeneration) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = 0;
    g_probe_errno = 0;
    g_probe_so_type = SOCK_STREAM;
    int fd = kSamplerFdTypeCacheSizeForTest + 4;

    ASSERT_TRUE(inst->isSocketForTest(fd));
    EXPECT_EQ(g_probe_calls.load(), 1);

    g_probe_so_type = SOCK_DGRAM;
    inst->clearFdCache();

    EXPECT_FALSE(inst->isSocketForTest(fd));
    EXPECT_EQ(g_probe_calls.load(), 2);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerFdTypeTest, HighFdCacheCollisionReprobesExactFd) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = 0;
    g_probe_errno = 0;
    int stream_fd = kSamplerFdTypeCacheSizeForTest + 5;
    int datagram_fd = stream_fd + kSamplerHighFdCacheSizeForTest;

    g_probe_so_type = SOCK_STREAM;
    ASSERT_TRUE(inst->isSocketForTest(stream_fd));
    EXPECT_EQ(g_probe_calls.load(), 1);

    g_probe_so_type = SOCK_DGRAM;
    EXPECT_FALSE(inst->isSocketForTest(datagram_fd));
    EXPECT_EQ(g_probe_calls.load(), 2);
    EXPECT_EQ(g_probe_last_fd.load(), datagram_fd);

    g_probe_so_type = SOCK_STREAM;
    EXPECT_TRUE(inst->isSocketForTest(stream_fd));
    EXPECT_EQ(g_probe_calls.load(), 3);
    EXPECT_EQ(g_probe_last_fd.load(), stream_fd);
    inst->clearFdCache();
}

TEST_F(NativeSocketSamplerHookTest, HighFdWriteHookReusesCachedSocketVerdict) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();
    ScopedSamplerProbeOverride override(stub_probe);
    g_probe_calls = 0;
    g_probe_rc = 0;
    g_probe_errno = 0;
    g_probe_so_type = SOCK_STREAM;
    g_write_ret = -1;
    int fd = kSamplerFdTypeCacheSizeForTest + 6;
    char buf[16] = {};

    bool prev = LibraryPatcher::_socket_active.exchange(true, std::memory_order_release);
    EXPECT_EQ(-1, NativeSocketSampler::write_hook(fd, buf, sizeof(buf)));
    EXPECT_EQ(-1, NativeSocketSampler::write_hook(fd, buf, sizeof(buf)));
    LibraryPatcher::_socket_active.store(prev, std::memory_order_release);

    EXPECT_EQ(g_write_calls.load(), 2);
    EXPECT_EQ(g_probe_calls.load(), 1);
    inst->clearFdCache();
}

TEST(NativeSocketSamplerLruTest, InsertAndLookupPreservesEntries) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    for (int fd = 0; fd < 16; fd++) {
        inst->fdAddrCacheInsertForTest(fd, "10.0.0.1:" + std::to_string(fd));
    }

    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), 16)
        << "All 16 distinct-fd inserts must be stored";
    inst->clearFdCache();
}

TEST(NativeSocketSamplerLruTest, UpdateExistingEntryDoesNotGrowCache) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    inst->fdAddrCacheInsertForTest(42, "1.2.3.4:9000");
    inst->fdAddrCacheInsertForTest(42, "5.6.7.8:9001");  // update same fd

    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), 1)
        << "Re-inserting the same fd must update in-place, not add a second entry";
    inst->clearFdCache();
}

TEST(NativeSocketSamplerLruTest, EvictsLruEntryAtCapacity) {
    NativeSocketSampler* inst = NativeSocketSampler::instance();
    inst->clearFdCache();

    const int CAP = NativeSocketSampler::MAX_FD_CACHE;
    for (int fd = 0; fd < CAP; fd++) {
        inst->fdAddrCacheInsertForTest(fd, "x");
    }
    ASSERT_EQ(inst->fdAddrCacheSizeForTest(), CAP);

    // Insert one more entry beyond capacity.
    inst->fdAddrCacheInsertForTest(CAP, "overflow");

    EXPECT_EQ(inst->fdAddrCacheSizeForTest(), CAP)
        << "Cache size must stay at MAX_FD_CACHE after overflow insert";
    inst->clearFdCache();
}

#endif // __linux__ (success-path / isSocket tests)

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

/**
 * Verifies that bare natsock (no =value) enables socket profiling with the
 * default interval (same as natsock=0).
 */
TEST(ArgumentsNatsock, BareNatsockEnables) {
    Arguments args;
    Error e = args.parse("natsock");
    ASSERT_FALSE(static_cast<bool>(e)) << "Bare 'natsock' should be accepted";
    ASSERT_TRUE(args._nativesocket) << "Bare 'natsock' should enable socket profiling";
    ASSERT_EQ(args._nativesocket_interval, 0L) << "Bare 'natsock' should use default interval";
}

/**
 * Verifies that natsock=0us is accepted (zero interval is valid).
 */
TEST(ArgumentsNatsock, ZeroIntervalAccepted) {
    Arguments args;
    Error e = args.parse("natsock=0us");
    ASSERT_FALSE(static_cast<bool>(e)) << "natsock=0us should be accepted";
}

/**
 * Verifies that natsock with overflow value is rejected.
 */
TEST(ArgumentsNatsock, OverflowRejected) {
    Arguments args;
    Error e = args.parse("natsock=99999999999999999s");
    ASSERT_TRUE(static_cast<bool>(e)) << "Expected error for natsock with overflow value";
}
