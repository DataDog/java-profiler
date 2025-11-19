/*
 * Copyright 2025, Datadog, Inc
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
 * Test using Contexts_1 TLS mechanism (actual production usage).
 * This simulates the real flow:
 * 1. Allocate Context
 * 2. Store in TLS via Contexts_1::setContextTls()
 * 3. Write values (simulating Java DirectByteBuffer writes)
 * 4. Read via Contexts_1::get() (simulating signal handler reads)
 */
TEST(ContextSanityTest, TlsBasedAccess) {
  // Allocate context (matches JavaProfiler.initializeContextTls0)
  Context* ctx = new Context();
  ctx->spanId = 0;
  ctx->rootSpanId = 0;
  ctx->checksum = 0;

  // Store in TLS (matches JavaProfiler.initializeContextTls0)
  Contexts_1::setContextTls(ctx);

  // Verify we can retrieve it
  Context* retrievedCtx = Contexts_1::get();
  ASSERT_NE(retrievedCtx, nullptr);
  EXPECT_EQ(retrievedCtx, ctx);

  // Write values via pointer (simulating Java DirectByteBuffer.putLong())
  ctx->spanId = 123;
  ctx->rootSpanId = 456;
  ctx->checksum = 789;

  // Read via TLS getter
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  Context* readCtx = Contexts_1::get();
  ASSERT_NE(readCtx, nullptr);

  u64 readSpanId = readCtx->spanId;
  u64 readRootSpanId = readCtx->rootSpanId;
  u64 readChecksum = readCtx->checksum;

  // Verify values match
  EXPECT_EQ(readSpanId, 123ULL);
  EXPECT_EQ(readRootSpanId, 456ULL);
  EXPECT_EQ(readChecksum, 789ULL);

  // Cleanup
  delete ctx;
}

/**
 * Test multiple TLS write-read cycles (simulating repeated context updates).
 * This matches the actual usage pattern where context is updated multiple times
 * during a thread's lifetime and read by signal handlers.
 */
TEST(ContextSanityTest, TlsMultipleUpdates) {
  Context* ctx = new Context();
  ctx->spanId = 0;
  ctx->rootSpanId = 0;
  ctx->checksum = 0;

  Contexts_1::setContextTls(ctx);

  // Update 1
  ctx->spanId = 1;
  ctx->rootSpanId = 2;
  ctx->checksum = 4;
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
  Context* readCtx = Contexts_1::get();
  ASSERT_NE(readCtx, nullptr);
  EXPECT_EQ(readCtx->spanId, 1ULL);
  EXPECT_EQ(readCtx->rootSpanId, 2ULL);
  EXPECT_EQ(readCtx->checksum, 4ULL);

  // Update 2
  ctx->spanId = 10;
  ctx->rootSpanId = 20;
  ctx->checksum = 40;
  readCtx = Contexts_1::get();
  ASSERT_NE(readCtx, nullptr);
  EXPECT_EQ(readCtx->spanId, 10ULL);
  EXPECT_EQ(readCtx->rootSpanId, 20ULL);
  EXPECT_EQ(readCtx->checksum, 40ULL);

  // Update 3
  ctx->spanId = 100;
  ctx->rootSpanId = 200;
  ctx->checksum = 400;

  readCtx = Contexts_1::get();
  ASSERT_NE(readCtx, nullptr);
  EXPECT_EQ(readCtx->spanId, 100ULL);
  EXPECT_EQ(readCtx->rootSpanId, 200ULL);
  EXPECT_EQ(readCtx->checksum, 400ULL);

  delete ctx;
}
