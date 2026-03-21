/*
 * Copyright 2025, 2026 Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "context.h"

/**
 * Tests the Context checksum computation algorithm.
 * The checksum is still used by the Context DTO for liveness tracker
 * serialization via writeContext(). snapshotContext() computes it.
 */
TEST(ContextSanityTest, ChecksumComputation) {
  u64 checksum1 = Contexts::checksum(123, 456);
  EXPECT_NE(checksum1, 0ULL) << "Checksum should never be 0";

  u64 checksum2 = Contexts::checksum(123, 456);
  EXPECT_EQ(checksum1, checksum2) << "Checksum should be deterministic";

  u64 checksum3 = Contexts::checksum(789, 012);
  EXPECT_NE(checksum1, checksum3) << "Different inputs should produce different checksums";

  u64 checksumZeros = Contexts::checksum(0, 0);
  EXPECT_NE(checksumZeros, 0ULL) << "Checksum of (0,0) should not be 0";

  u64 checksumMax = Contexts::checksum(UINT64_MAX, UINT64_MAX);
  EXPECT_NE(checksumMax, 0ULL) << "Checksum of max values should not be 0";
}

/**
 * Tests valid checksum validation — simulates signal handler reading
 * a properly written context with correct checksum.
 */
TEST(ContextSanityTest, ValidChecksumValidation) {
  Context ctx;

  u64 spanId = 0xDEADBEEFCAFEBABEULL;
  u64 rootSpanId = 0x123456789ABCDEF0ULL;
  u64 expectedChecksum = Contexts::checksum(spanId, rootSpanId);

  ctx.checksum = 0;
  ctx.spanId = spanId;
  ctx.rootSpanId = rootSpanId;
  ctx.checksum = expectedChecksum;

  u64 stored = ctx.checksum;
  ASSERT_NE(stored, 0ULL) << "Should not be in-progress state";

  u64 readSpanId = ctx.spanId;
  u64 readRootSpanId = ctx.rootSpanId;
  u64 computed = Contexts::checksum(readSpanId, readRootSpanId);

  EXPECT_EQ(stored, computed) << "Checksum validation should pass for valid context";
  EXPECT_EQ(readSpanId, spanId);
  EXPECT_EQ(readRootSpanId, rootSpanId);
}

/**
 * Tests checksum detection of torn/inconsistent reads.
 */
TEST(ContextSanityTest, InvalidChecksumDetection) {
  Context ctx;

  u64 spanId = 100;
  u64 rootSpanId = 200;
  u64 validChecksum = Contexts::checksum(spanId, rootSpanId);

  ctx.spanId = spanId;
  ctx.rootSpanId = rootSpanId;
  ctx.checksum = validChecksum;

  ctx.spanId = 999;

  u64 stored = ctx.checksum;
  u64 readSpanId = ctx.spanId;
  u64 readRootSpanId = ctx.rootSpanId;
  u64 computed = Contexts::checksum(readSpanId, readRootSpanId);

  EXPECT_NE(stored, computed) << "Checksum validation should fail for torn read";
}

/**
 * Tests in-progress detection (checksum=0).
 */
TEST(ContextSanityTest, InProgressDetection) {
  Context ctx;

  ctx.checksum = 0;
  ctx.spanId = 123;

  u64 stored = ctx.checksum;

  EXPECT_EQ(stored, 0ULL) << "Should detect in-progress write (checksum=0)";
}
