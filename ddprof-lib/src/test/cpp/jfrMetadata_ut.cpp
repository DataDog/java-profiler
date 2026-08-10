/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

// Regression tests for PROF-15075 (SIGSEGV in Recording::writeElement).
//
// JfrMetadata::reset() used to clear _root._children (and the tracked
// NoField instances) without deleting the underlying heap-allocated Element
// objects that JfrMetadata::initialize() had allocated via element(),
// operator||(), and the conditional NoField path in field(). Once the
// allocator reused a freed address on the next initialize() call, any
// dangling pointer left over from before would point at unrelated memory.
//
// These tests exercise JfrMetadata::initialize()/reset() directly (no JVM
// attach required -- initialize() only touches VM::isHotspot()/
// VM::hotspot_version(), which default to false/-1 in this test binary,
// so the conditional NoField path in field() is deterministically taken).
// Running this test under an ASan/LeakSanitizer build (testAsan) is what
// actually proves the fix: a pre-fix build leaks every Element and NoField
// allocated by initialize() on every reset(), and LeakSanitizer reports it
// at process exit.

#include "jfrMetadata.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(JfrMetadataResetTest, ResetIsSafeBeforeAnyInitialize) {
  // reset() must be safe to call even if initialize() was never called
  // (e.g. Profiler::stop() racing a failed Profiler::start()).
  JfrMetadata::reset();
  EXPECT_TRUE(JfrMetadata::root()->_children.empty());
  // reset() re-registers "root" at string id 0 so _root._name stays valid,
  // so strings() always contains exactly that one entry, never empty.
  EXPECT_EQ(JfrMetadata::strings().size(), 1u);
  EXPECT_EQ(JfrMetadata::strings()[0], "root");
}

TEST(JfrMetadataResetTest, InitializeThenResetClearsTree) {
  JfrMetadata::reset();
  JfrMetadata::initialize({});

  EXPECT_FALSE(JfrMetadata::root()->_children.empty());
  EXPECT_FALSE(JfrMetadata::strings().empty());

  JfrMetadata::reset();

  EXPECT_TRUE(JfrMetadata::root()->_children.empty());
  // See ResetIsSafeBeforeAnyInitialize: "root" is always re-registered.
  EXPECT_EQ(JfrMetadata::strings().size(), 1u);
  EXPECT_EQ(JfrMetadata::strings()[0], "root");
}

TEST(JfrMetadataResetTest, MultipleInitializeResetCyclesDoNotCrash) {
  // Simulates repeated Profiler::start()/stop() restart cycles. Each
  // initialize() allocates a fresh Element/NoField tree; each reset() must
  // fully delete the previous cycle's tree before the next initialize()
  // reuses the freed heap addresses.
  for (int i = 0; i < 5; i++) {
    JfrMetadata::reset();
    JfrMetadata::initialize({});
    EXPECT_FALSE(JfrMetadata::root()->_children.empty())
        << "cycle " << i << " did not populate the metadata tree";
  }
  JfrMetadata::reset();
  EXPECT_TRUE(JfrMetadata::root()->_children.empty());
}

TEST(JfrMetadataResetTest, RestartCyclesWithContextAttributesDoNotCrash) {
  // Non-empty contextAttributes exercise Element::operator||(), which
  // allocates one "field" Element per attribute name; those instances must
  // also be reachable (and deleted) via reset()'s recursive tree cleanup.
  std::vector<std::string> contextAttributes = {"tag1", "tag2", "tag3"};
  for (int i = 0; i < 5; i++) {
    JfrMetadata::reset();
    JfrMetadata::initialize(contextAttributes);
    EXPECT_FALSE(JfrMetadata::root()->_children.empty())
        << "cycle " << i << " did not populate the metadata tree";
  }
  JfrMetadata::reset();
}

TEST(JfrMetadataResetTest, InitializeIsIdempotentWithoutReset) {
  // JfrMetadata::initialize() guards against double-initialization; calling
  // it twice without an intervening reset() must not double-allocate or
  // crash. This documents/protects the existing `if (_initialized) return;`
  // safeguard called out in the PROF-15075 spec.
  JfrMetadata::reset();
  JfrMetadata::initialize({});
  size_t childrenAfterFirst = JfrMetadata::root()->_children.size();

  JfrMetadata::initialize({}); // no-op: _initialized guard short-circuits
  EXPECT_EQ(childrenAfterFirst, JfrMetadata::root()->_children.size());

  JfrMetadata::reset();
}
