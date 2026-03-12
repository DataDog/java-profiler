/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "gtest/gtest.h"
#include "event.h"
#include "codeCache.h"

// Tests for NativeSocketEvent data structures and SocketPatcher name matching.
// PLT patching integration requires Linux and is tested via Java integration tests.

TEST(NativeSocketEvent, StructLayout) {
  NativeSocketEvent event;
  event._start = 1000;
  event._end = 2000;
  event._fd = 42;
  event._bytes = 1024;
  event._operation = SOCKET_OP_RECV;

  EXPECT_EQ(event._start, 1000ULL);
  EXPECT_EQ(event._end, 2000ULL);
  EXPECT_EQ(event._fd, 42);
  EXPECT_EQ(event._bytes, 1024ULL);
  EXPECT_EQ(event._operation, (u32)SOCKET_OP_RECV);
}

TEST(NativeSocketEvent, OperationEnumValues) {
  EXPECT_EQ(SOCKET_OP_RECV, 0);
  EXPECT_EQ(SOCKET_OP_SEND, 1);
  EXPECT_EQ(SOCKET_OP_RECVFROM, 2);
  EXPECT_EQ(SOCKET_OP_SENDTO, 3);
  EXPECT_EQ(SOCKET_OP_READV, 4);
  EXPECT_EQ(SOCKET_OP_WRITEV, 5);
}

TEST(NativeSocketEvent, ImportIdBounds) {
  // Socket imports should be contiguous and within NUM_IMPORTS
  EXPECT_LT(im_recv, NUM_IMPORTS);
  EXPECT_LT(im_send, NUM_IMPORTS);
  EXPECT_LT(im_recvfrom, NUM_IMPORTS);
  EXPECT_LT(im_sendto, NUM_IMPORTS);
  EXPECT_LT(im_readv, NUM_IMPORTS);
  EXPECT_LT(im_writev, NUM_IMPORTS);
}

#ifdef __linux__
#include "socketPatcher.h"

TEST(SocketPatcher, NettyNameMatching) {
  EXPECT_TRUE(SocketPatcher::isNettyNativeLibrary(
      "/tmp/libnetty_transport_native_epoll_linux_x86_64.so"));
  EXPECT_TRUE(SocketPatcher::isNettyNativeLibrary(
      "/tmp/libnetty_transport_native_kqueue.jnilib"));
  EXPECT_TRUE(SocketPatcher::isNettyNativeLibrary(
      "libnetty_transport_native_io_uring.so"));
  EXPECT_FALSE(SocketPatcher::isNettyNativeLibrary(
      "/usr/lib/libc.so.6"));
  EXPECT_FALSE(SocketPatcher::isNettyNativeLibrary(
      "/path/to/libjavaProfiler.so"));
  EXPECT_FALSE(SocketPatcher::isNettyNativeLibrary(nullptr));
}
#endif
