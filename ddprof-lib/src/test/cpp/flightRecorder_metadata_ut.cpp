/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Regression tests for Recording::countSerializableChildren(), the helper
// writeElement() uses to decide which children of a JfrMetadata::Element
// tree get serialized when the tree is corrupted (null children) or
// unexpectedly deep (cycles / excessive recursion).
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
#include <memory>

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

// Owns the "field" Elements handed out by makeChild() below, so each test's
// children are freed when its owner goes out of scope instead of leaking
// (unlike JfrMetadata::root(), whose tree intentionally lives for the
// process lifetime, these are throwaway test fixtures).
class ElementOwner {
public:
  const Element *makeChild() {
    _owned.push_back(std::make_unique<Element>("field"));
    return _owned.back().get();
  }

private:
  std::vector<std::unique_ptr<Element>> _owned;
};

} // namespace

TEST(WriteElementMetadataGuardTest, AllValidChildrenAreCountedAtShallowDepth) {
  ElementOwner owner;
  std::vector<const Element *> children = {owner.makeChild(), owner.makeChild(),
                                           owner.makeChild()};

  size_t count = RecordingTestAccessor::countSerializableChildren(children, 0);

  EXPECT_EQ(3u, count);
}

TEST(WriteElementMetadataGuardTest, NullChildrenAreExcludedAndCounted) {
  ElementOwner owner;
  std::vector<const Element *> children = {owner.makeChild(), nullptr,
                                           owner.makeChild(), nullptr};

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
  ElementOwner owner;
  std::vector<const Element *> children = {owner.makeChild()};

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
  ElementOwner owner;
  std::vector<const Element *> children = {owner.makeChild(), owner.makeChild()};

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
