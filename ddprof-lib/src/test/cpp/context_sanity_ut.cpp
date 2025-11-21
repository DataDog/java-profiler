/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "context.h"

/**
 * Sanity test for context write-read operations.
 * Verifies that values written to a Context can be immediately read back
 * correctly using the same volatile access and memory fence pattern
 * used in production code (flightRecorder.cpp).
 */
TEST(ContextSanityTest, BasicWriteRead) {
  // Allocate a Context on the stack
  Context ctx;

  // Initialize to zero
  ctx.spanId = 0;
  ctx.rootSpanId = 0;
  ctx.checksum = 0;

  // Write known values
  ctx.spanId = 100;
  ctx.rootSpanId = 200;
  ctx.checksum = 300;

  // Read back
  u64 readSpanId = ctx.spanId;
  u64 readRootSpanId = ctx.rootSpanId;
  u64 readChecksum = ctx.checksum;

  // Verify values match
  EXPECT_EQ(readSpanId, 100ULL);
  EXPECT_EQ(readRootSpanId, 200ULL);
  EXPECT_EQ(readChecksum, 300ULL);
}

/**
 * Test multiple sequential write-read cycles to ensure
 * values don't get cached or corrupted across updates.
 */
TEST(ContextSanityTest, SequentialWriteReadCycles) {
  Context ctx;
  ctx.spanId = 0;
  ctx.rootSpanId = 0;
  ctx.checksum = 0;

  // Cycle 1
  ctx.spanId = 1;
  ctx.rootSpanId = 2;
  ctx.checksum = 3;
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  EXPECT_EQ(ctx.spanId, 1ULL);
  EXPECT_EQ(ctx.rootSpanId, 2ULL);
  EXPECT_EQ(ctx.checksum, 3ULL);

  // Cycle 2
  ctx.spanId = 10;
  ctx.rootSpanId = 20;
  ctx.checksum = 30;
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  EXPECT_EQ(ctx.spanId, 10ULL);
  EXPECT_EQ(ctx.rootSpanId, 20ULL);
  EXPECT_EQ(ctx.checksum, 30ULL);

  // Cycle 3
  ctx.spanId = 100;
  ctx.rootSpanId = 200;
  ctx.checksum = 300;
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  EXPECT_EQ(ctx.spanId, 100ULL);
  EXPECT_EQ(ctx.rootSpanId, 200ULL);
  EXPECT_EQ(ctx.checksum, 300ULL);
}

/**
 * Test using Contexts TLS mechanism (actual production usage).
 * This simulates the real flow:
 * 1. Initialize context TLS via Contexts::initializeContextTls()
 * 2. Write values (simulating Java DirectByteBuffer writes)
 * 3. Read via Contexts::get() (simulating signal handler reads)
 */
TEST(ContextSanityTest, TlsBasedAccess) {
  // Initialize context TLS (matches JavaProfiler.initializeContextTls0)
  // This also marks ProfiledThread as having context TLS initialized
  Context& ctx = Contexts::initializeContextTls();

  // Initialize to zero
  ctx.spanId = 0;
  ctx.rootSpanId = 0;
  ctx.checksum = 0;

  // Write values (simulating Java DirectByteBuffer.putLong())
  ctx.spanId = 123;
  ctx.rootSpanId = 456;
  ctx.checksum = 789;

  // Read via TLS getter
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  Context& readCtx = Contexts::get();

  u64 readSpanId = readCtx.spanId;
  u64 readRootSpanId = readCtx.rootSpanId;
  u64 readChecksum = readCtx.checksum;

  // Verify values match
  EXPECT_EQ(readSpanId, 123ULL);
  EXPECT_EQ(readRootSpanId, 456ULL);
  EXPECT_EQ(readChecksum, 789ULL);
}

/**
 * Test multiple TLS write-read cycles (simulating repeated context updates).
 * This matches the actual usage pattern where context is updated multiple times
 * during a thread's lifetime and read by signal handlers.
 */
TEST(ContextSanityTest, TlsMultipleUpdates) {
  // Initialize context TLS
  Context& ctx = Contexts::initializeContextTls();
  ctx.spanId = 0;
  ctx.rootSpanId = 0;
  ctx.checksum = 0;

  // Update 1
  ctx.spanId = 1;
  ctx.rootSpanId = 2;
  ctx.checksum = 4;
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  Context& readCtx = Contexts::get();
  EXPECT_EQ(readCtx.spanId, 1ULL);
  EXPECT_EQ(readCtx.rootSpanId, 2ULL);
  EXPECT_EQ(readCtx.checksum, 4ULL);

  // Update 2
  ctx.spanId = 10;
  ctx.rootSpanId = 20;
  ctx.checksum = 40;
  Context& readCtx2 = Contexts::get();
  EXPECT_EQ(readCtx2.spanId, 10ULL);
  EXPECT_EQ(readCtx2.rootSpanId, 20ULL);
  EXPECT_EQ(readCtx2.checksum, 40ULL);

  // Update 3
  ctx.spanId = 100;
  ctx.rootSpanId = 200;
  ctx.checksum = 400;

  Context& readCtx3 = Contexts::get();
  EXPECT_EQ(readCtx3.spanId, 100ULL);
  EXPECT_EQ(readCtx3.rootSpanId, 200ULL);
  EXPECT_EQ(readCtx3.checksum, 400ULL);
}
