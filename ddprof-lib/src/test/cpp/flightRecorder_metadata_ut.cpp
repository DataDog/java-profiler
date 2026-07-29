/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Regression tests for Recording::countSerializableChildren(), the helper
// writeElement() uses (PROF-15075) to decide which children of a
// JfrMetadata::Element tree get serialized when the tree is corrupted
// (null children) or unexpectedly deep (cycles / excessive recursion).
//
// Recording itself can't be constructed in a plain gtest binary -- its
// constructor unconditionally calls VM::jvmti()->GetAvailableProcessors(),
// and writeSettings()/writeOsCpuInfo()/writeJvmInfo() reach into
// VM::libjvm() and Profiler::instance(), none of which are set up without a
// live JVM attached. countSerializableChildren() is extracted specifically
// so the counting/truncation logic writeElement() depends on can be tested
// directly, without needing any of that.
//
// The bug this guards against: originally, child_count was computed by
// counting every non-null child, while the recursive write skipped children
// once `depth > 10`. A non-null child at the depth boundary was included in
// child_count but never serialized, so the encoded count didn't match the
// number of children actually written -- a structurally invalid JFR
// metadata event. countSerializableChildren() now applies the exact same
// depth-truncation rule used to decide whether to recurse, so the count it
// returns can never diverge from what gets serialized.

#include <gtest/gtest.h>

#include "counters.h"
#include "flightRecorder.h"
#include "jfrMetadata.h"

// Friend of Recording (see flightRecorder.h), giving this test access to the
// private countSerializableChildren() helper. Same pattern as
// VMTestAccessor/ProfilerTestAccessor used elsewhere in this test suite.
class RecordingTestAccessor {
public:
  static size_t countSerializableChildren(
      const std::vector<const Element *> &children, int depth) {
    return Recording::countSerializableChildren(children, depth);
  }
};

namespace {

// Builds a chain of `depth` nested "field" elements: root -> child_1 -> ... .
// Only used to hold real Element children; JfrMetadata's own string interning
// keeps this allocation-free after warmup, and none of these elements are
// ever freed (mirrors JfrMetadata::root(), whose tree lives for the process
// lifetime).
const Element *makeChild() { return new Element("field"); }

} // namespace

TEST(WriteElementMetadataGuardTest, AllValidChildrenAreCountedAtShallowDepth) {
  std::vector<const Element *> children = {makeChild(), makeChild(),
                                           makeChild()};

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 0);

  EXPECT_EQ(3u, count);
}

TEST(WriteElementMetadataGuardTest, NullChildrenAreExcludedAndCounted) {
  std::vector<const Element *> children = {makeChild(), nullptr, makeChild(),
                                           nullptr};

  long long null_before = Counters::getCounter(METADATA_TREE_NULL_CHILD);

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 0);

  long long null_after = Counters::getCounter(METADATA_TREE_NULL_CHILD);

  // Only the two non-null children are counted -- a naive
  // children.size()-based count would report 4, which would make the
  // encoded metadata event advertise two children that are never written.
  EXPECT_EQ(2u, count);
  EXPECT_EQ(2, null_after - null_before);
}

// This is the exact structural-validity bug the depth guard must not
// reintroduce: a non-null child sitting exactly at the depth boundary
// (depth 10, so its would-be recursive call is at depth 11) must be
// excluded from child_count, not just skipped by the recursive writer --
// otherwise the encoded count and the actually-serialized children diverge.
TEST(WriteElementMetadataGuardTest, ChildAtDepthBoundaryIsExcludedFromCount) {
  std::vector<const Element *> children = {makeChild()};

  long long depth_before = Counters::getCounter(METADATA_TREE_DEPTH_EXCEEDED);

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 10);

  long long depth_after = Counters::getCounter(METADATA_TREE_DEPTH_EXCEEDED);

  EXPECT_EQ(0u, count);
  EXPECT_EQ(1, depth_after - depth_before);
}

// Sanity check: a child one level shallower than the boundary (depth 9, so
// its recursive call lands at depth 10, still within the depth > 10 limit)
// must still be counted normally -- the truncation must not kick in early.
TEST(WriteElementMetadataGuardTest, ChildJustBeforeDepthBoundaryIsStillCounted) {
  std::vector<const Element *> children = {makeChild(), makeChild()};

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 9);

  EXPECT_EQ(2u, count);
}

// A null child at the depth boundary must be reported as a null child, not
// double-counted against the depth-exceeded counter as well.
TEST(WriteElementMetadataGuardTest, NullChildAtDepthBoundaryIsReportedAsNull) {
  std::vector<const Element *> children = {nullptr};

  long long null_before = Counters::getCounter(METADATA_TREE_NULL_CHILD);
  long long depth_before = Counters::getCounter(METADATA_TREE_DEPTH_EXCEEDED);

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 10);

  long long null_after = Counters::getCounter(METADATA_TREE_NULL_CHILD);
  long long depth_after = Counters::getCounter(METADATA_TREE_DEPTH_EXCEEDED);

  EXPECT_EQ(0u, count);
  EXPECT_EQ(1, null_after - null_before);
  EXPECT_EQ(0, depth_after - depth_before);
}
