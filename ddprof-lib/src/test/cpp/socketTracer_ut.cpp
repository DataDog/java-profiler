/*
 * Copyright 2026, Datadog, Inc
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "../../main/cpp/event.h"
#include "../../main/cpp/gtest_crash_handler.h"
#include "../../main/cpp/socketTracer.h"

static constexpr char SOCKET_TRACER_TEST_NAME[] = "SocketTracerTest";

class SocketTracerTest : public ::testing::Test {
protected:
    void SetUp() override {
        installGtestCrashHandler<SOCKET_TRACER_TEST_NAME>();
    }

    void TearDown() override {
        restoreDefaultSignalHandlers();
    }
};

// --------------------------------------------------------------------------
// isNettyLibrary tests
// --------------------------------------------------------------------------

TEST_F(SocketTracerTest, NettyEpollLibraryDetected) {
    // Typical names used by Netty native epoll transport on Linux x86_64
    EXPECT_TRUE(SocketTracer::isNettyLibrary("/tmp/netty-epoll1234/libnetty_transport_native_epoll_x86_64.so"))
        << "Should detect standard Netty epoll library";
    EXPECT_TRUE(SocketTracer::isNettyLibrary("libnetty_transport_native_epoll_aarch64.so"))
        << "Should detect Netty epoll library for aarch64";
}

TEST_F(SocketTracerTest, NettyInPathDetected) {
    EXPECT_TRUE(SocketTracer::isNettyLibrary("/var/folders/netty-custom-4.1.so"))
        << "Should detect library containing 'netty' anywhere in the path";
}

TEST_F(SocketTracerTest, NonNettyLibrariesNotDetected) {
    EXPECT_FALSE(SocketTracer::isNettyLibrary("/usr/lib/x86_64-linux-gnu/libc.so.6"))
        << "libc must not be flagged as Netty";
    EXPECT_FALSE(SocketTracer::isNettyLibrary("/usr/lib/jvm/java-21-openjdk/lib/server/libjvm.so"))
        << "libjvm must not be flagged as Netty";
    EXPECT_FALSE(SocketTracer::isNettyLibrary("libpthread.so.0"))
        << "libpthread must not be flagged as Netty";
    EXPECT_FALSE(SocketTracer::isNettyLibrary("/opt/app/libmyapp.so"))
        << "Unrelated app library must not be flagged as Netty";
}

TEST_F(SocketTracerTest, NullLibraryNameNotDetected) {
    EXPECT_FALSE(SocketTracer::isNettyLibrary(nullptr))
        << "nullptr should not be detected as Netty";
}

TEST_F(SocketTracerTest, EmptyLibraryNameNotDetected) {
    EXPECT_FALSE(SocketTracer::isNettyLibrary(""))
        << "Empty string should not be detected as Netty";
}

// --------------------------------------------------------------------------
// SocketIOEvent struct layout and field tests
// --------------------------------------------------------------------------

TEST_F(SocketTracerTest, SocketIOEventHoldsStartEndTimes) {
    SocketIOEvent event;
    event._start     = 1000ULL;
    event._end       = 2000ULL;
    event._operation = SOCKET_OP_READ;
    event._bytes     = 512L;

    EXPECT_EQ(event._start, 1000ULL);
    EXPECT_EQ(event._end,   2000ULL);
    EXPECT_STREQ(event._operation, "read");
    EXPECT_EQ(event._bytes, 512L);
}

TEST_F(SocketTracerTest, SocketIOEventNegativeBytesForNonTransferOps) {
    SocketIOEvent event;
    event._start     = 100ULL;
    event._end       = 200ULL;
    event._operation = SOCKET_OP_CONNECT;
    event._bytes     = -1L;

    EXPECT_EQ(event._bytes, -1L) << "connect does not transfer bytes; -1 is the sentinel";
    EXPECT_STREQ(event._operation, "connect");
}

TEST_F(SocketTracerTest, SocketIOEventAccept4Operation) {
    // accept4 is the preferred accept variant on Linux (used by Netty and glibc).
    // Verify it has its own distinct operation name and uses -1 for bytes.
    SocketIOEvent event;
    event._start     = 300ULL;
    event._end       = 400ULL;
    event._operation = SOCKET_OP_ACCEPT4;
    event._bytes     = -1L;

    EXPECT_STREQ(event._operation, "accept4");
    EXPECT_STRNE(event._operation, SOCKET_OP_ACCEPT) << "accept4 must be distinct from accept";
    EXPECT_EQ(event._bytes, -1L) << "accept4 does not transfer bytes";
}

// --------------------------------------------------------------------------
// Operation name constant tests
// --------------------------------------------------------------------------

TEST_F(SocketTracerTest, OperationNameConstantsAreCorrect) {
    EXPECT_STREQ(SOCKET_OP_READ,       "read");
    EXPECT_STREQ(SOCKET_OP_WRITE,      "write");
    EXPECT_STREQ(SOCKET_OP_READV,      "readv");
    EXPECT_STREQ(SOCKET_OP_WRITEV,     "writev");
    EXPECT_STREQ(SOCKET_OP_RECV,       "recv");
    EXPECT_STREQ(SOCKET_OP_SEND,       "send");
    EXPECT_STREQ(SOCKET_OP_RECVMSG,    "recvmsg");
    EXPECT_STREQ(SOCKET_OP_SENDMSG,    "sendmsg");
    EXPECT_STREQ(SOCKET_OP_CONNECT,    "connect");
    EXPECT_STREQ(SOCKET_OP_ACCEPT,     "accept");
    EXPECT_STREQ(SOCKET_OP_ACCEPT4,    "accept4");
    EXPECT_STREQ(SOCKET_OP_EPOLL_WAIT, "epoll_wait");
}

TEST_F(SocketTracerTest, OperationNameConstantsAreDistinct) {
    const char* ops[] = {
        SOCKET_OP_READ, SOCKET_OP_WRITE, SOCKET_OP_READV, SOCKET_OP_WRITEV,
        SOCKET_OP_RECV, SOCKET_OP_SEND, SOCKET_OP_RECVMSG, SOCKET_OP_SENDMSG,
        SOCKET_OP_CONNECT, SOCKET_OP_ACCEPT, SOCKET_OP_ACCEPT4, SOCKET_OP_EPOLL_WAIT
    };
    const int num_ops = sizeof(ops) / sizeof(ops[0]);
    for (int i = 0; i < num_ops; i++) {
        for (int j = i + 1; j < num_ops; j++) {
            EXPECT_STRNE(ops[i], ops[j])
                << "Duplicate operation name: ops[" << i << "] == ops[" << j << "]";
        }
    }
}

// --------------------------------------------------------------------------
// SocketTracer lifecycle tests
// --------------------------------------------------------------------------

TEST_F(SocketTracerTest, InitializeDoesNotCrash) {
    SocketTracer::initialize();
    EXPECT_TRUE(SocketTracer::isInitialized());
}

TEST_F(SocketTracerTest, PatchLibrariesWithoutNettyDoesNotCrash) {
    // When no Netty native library is loaded in this test process, patchLibraries()
    // should complete silently without patching anything.
    SocketTracer::initialize();
    SocketTracer::patchLibraries();
    // No assertion needed — the test passes if it does not crash or assert.
}

TEST_F(SocketTracerTest, UnpatchLibrariesWithoutPatchDoesNotCrash) {
    // Unpatching when nothing has been patched must be a safe no-op.
    SocketTracer::unpatchLibraries();
    // No assertion needed — the test passes if it does not crash.
}
