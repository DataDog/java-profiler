/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include "context.h"

/**
 * Tests the Context checksum computation algorithm.
 * Validates that Contexts::checksum() produces consistent results
 * and never returns 0 (reserved for "in-progress" marker).
 */
TEST(ContextSanityTest, ChecksumComputation) {
  // Test basic checksum computation
  u64 checksum1 = Contexts::checksum(123, 456);
  EXPECT_NE(checksum1, 0ULL) << "Checksum should never be 0";

  // Same inputs should produce same checksum
  u64 checksum2 = Contexts::checksum(123, 456);
  EXPECT_EQ(checksum1, checksum2) << "Checksum should be deterministic";

  // Different inputs should (very likely) produce different checksums
  u64 checksum3 = Contexts::checksum(789, 012);
  EXPECT_NE(checksum1, checksum3) << "Different inputs should produce different checksums";

  // Edge case: both inputs zero should not produce zero checksum
  u64 checksumZeros = Contexts::checksum(0, 0);
  EXPECT_NE(checksumZeros, 0ULL) << "Checksum of (0,0) should not be 0";

  // Edge case: max values
  u64 checksumMax = Contexts::checksum(UINT64_MAX, UINT64_MAX);
  EXPECT_NE(checksumMax, 0ULL) << "Checksum of max values should not be 0";
}

/**
 * Tests valid checksum validation - simulates signal handler reading
 * a properly written context with correct checksum.
 */
TEST(ContextSanityTest, ValidChecksumValidation) {
  Context ctx;

  // Simulate the write protocol from ThreadContext.putContextJava()
  u64 spanId = 0xDEADBEEFCAFEBABEULL;
  u64 rootSpanId = 0x123456789ABCDEF0ULL;
  u64 expectedChecksum = Contexts::checksum(spanId, rootSpanId);

  // Write in production order: checksum=0, data, checksum=valid
  ctx.checksum = 0;  // Mark in-progress
  ctx.spanId = spanId;
  ctx.rootSpanId = rootSpanId;
  ctx.checksum = expectedChecksum;  // Signal complete

  // Simulate signal handler read (flightRecorder.cpp:writeContext)
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
 * Simulates what happens if signal handler reads context mid-update.
 */
TEST(ContextSanityTest, InvalidChecksumDetection) {
  Context ctx;

  u64 spanId = 100;
  u64 rootSpanId = 200;
  u64 validChecksum = Contexts::checksum(spanId, rootSpanId);

  // Write valid context first
  ctx.spanId = spanId;
  ctx.rootSpanId = rootSpanId;
  ctx.checksum = validChecksum;

  // Simulate torn read: checksum is for old values, but spanId was updated
  ctx.spanId = 999;  // Changed by writer
  // Signal handler interrupts here - reads inconsistent state

  u64 stored = ctx.checksum;
  u64 readSpanId = ctx.spanId;
  u64 readRootSpanId = ctx.rootSpanId;
  u64 computed = Contexts::checksum(readSpanId, readRootSpanId);

  EXPECT_NE(stored, computed) << "Checksum validation should fail for torn read";
}

/**
 * Tests in-progress detection (checksum=0).
 * Simulates signal handler reading context while write is in progress.
 */
TEST(ContextSanityTest, InProgressDetection) {
  Context ctx;

  // Simulate interrupted write: checksum=0 written, data partially written
  ctx.checksum = 0;  // Mark in-progress
  ctx.spanId = 123;  // Partially written

  // Signal handler reads
  u64 stored = ctx.checksum;

  EXPECT_EQ(stored, 0ULL) << "Should detect in-progress write (checksum=0)";
  // Production code (flightRecorder.cpp) skips reading data when checksum=0
}

/**
 * Tests signal-safe TLS access mechanism.
 * Validates that Contexts::get() returns the same Context instance that was
 * initialized via Contexts::initializeContextTls(), proving the signal-safe
 * indirection through ProfiledThread works correctly.
 */
TEST(ContextSanityTest, TlsSignalSafeAccess) {
  // Initialize context TLS (matches JavaProfiler.initializeContextTls0)
  // This stores the Context pointer in ProfiledThread for signal-safe access
  Context& ctx = Contexts::initializeContextTls();

  // Write with valid checksum (simulate production write protocol)
  u64 spanId = 0xABCDEF0123456789ULL;
  u64 rootSpanId = 0x123456789ABCDEF0ULL;
  u64 expectedChecksum = Contexts::checksum(spanId, rootSpanId);

  ctx.checksum = 0;  // Mark in-progress
  ctx.spanId = spanId;
  ctx.rootSpanId = rootSpanId;
  ctx.checksum = expectedChecksum;  // Signal complete

  // Read via signal-safe TLS getter (simulates signal handler access)
  Context& readCtx = Contexts::get();

  // Verify same instance returned
  EXPECT_EQ(&ctx, &readCtx) << "Contexts::get() should return same instance as initializeContextTls()";

  // Verify checksum validates correctly
  u64 stored = readCtx.checksum;
  u64 readSpanId = readCtx.spanId;
  u64 readRootSpanId = readCtx.rootSpanId;
  u64 computed = Contexts::checksum(readSpanId, readRootSpanId);

  EXPECT_EQ(stored, computed) << "Checksum should validate after TLS round-trip";
  EXPECT_EQ(readSpanId, spanId);
  EXPECT_EQ(readRootSpanId, rootSpanId);
}

/**
 * Tests repeated context updates with checksum validation.
 * Simulates real usage: tracer updates context multiple times, signal handler
 * validates checksum each time to ensure no torn reads.
 */
TEST(ContextSanityTest, TlsMultipleValidatedUpdates) {
  Context& ctx = Contexts::initializeContextTls();

  // Update 1: Write with valid checksum
  u64 spanId1 = 100;
  u64 rootSpanId1 = 200;
  u64 checksum1 = Contexts::checksum(spanId1, rootSpanId1);

  ctx.checksum = 0;
  ctx.spanId = spanId1;
  ctx.rootSpanId = rootSpanId1;
  ctx.checksum = checksum1;

  // Signal handler read + validate
  Context& readCtx1 = Contexts::get();
  u64 computed1 = Contexts::checksum(readCtx1.spanId, readCtx1.rootSpanId);
  EXPECT_EQ(readCtx1.checksum, computed1) << "Update 1 checksum should validate";

  // Update 2: Write with valid checksum
  u64 spanId2 = 1000;
  u64 rootSpanId2 = 2000;
  u64 checksum2 = Contexts::checksum(spanId2, rootSpanId2);

  ctx.checksum = 0;
  ctx.spanId = spanId2;
  ctx.rootSpanId = rootSpanId2;
  ctx.checksum = checksum2;

  // Signal handler read + validate
  Context& readCtx2 = Contexts::get();
  u64 computed2 = Contexts::checksum(readCtx2.spanId, readCtx2.rootSpanId);
  EXPECT_EQ(readCtx2.checksum, computed2) << "Update 2 checksum should validate";

  // Update 3: Write with valid checksum
  u64 spanId3 = 999999;
  u64 rootSpanId3 = 888888;
  u64 checksum3 = Contexts::checksum(spanId3, rootSpanId3);

  ctx.checksum = 0;
  ctx.spanId = spanId3;
  ctx.rootSpanId = rootSpanId3;
  ctx.checksum = checksum3;

  // Signal handler read + validate
  Context& readCtx3 = Contexts::get();
  u64 computed3 = Contexts::checksum(readCtx3.spanId, readCtx3.rootSpanId);
  EXPECT_EQ(readCtx3.checksum, computed3) << "Update 3 checksum should validate";
}
