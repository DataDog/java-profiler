// Copyright 2026, Datadog, Inc.

#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include "threadExitRegistry.h"

namespace {
constexpr int TABLE_SIZE = 4096;
constexpr int PROBE_LIMIT = 64;

// Mirrors the registry's hash so the test can build a full probe chain.
unsigned slotFor(uint64_t tid) {
    return (tid * 2654435761u) & (TABLE_SIZE - 1);
}

// Returns `count` distinct identities that all hash to the slot of `target`.
std::vector<uint64_t> collidersOf(uint64_t target, int count) {
    std::vector<uint64_t> out;
    for (uint64_t tid = target + 1; static_cast<int>(out.size()) < count; tid++) {
        if (slotFor(tid) == slotFor(target)) out.push_back(tid);
    }
    return out;
}

class ThreadExitRegistryTest : public ::testing::Test {
  protected:
    void SetUp() override { ThreadExitRegistry::resetForTest(); }
    void TearDown() override { ThreadExitRegistry::resetForTest(); }
};
}  // namespace

// The 64th probe position must be searched by contains().
TEST_F(ThreadExitRegistryTest, ContainsFindsMarkAtLastProbe) {
    const uint64_t target = 1000;
    for (uint64_t tid : collidersOf(target, PROBE_LIMIT - 1)) ThreadExitRegistry::markForTest(tid);
    ThreadExitRegistry::markForTest(target);
    EXPECT_TRUE(ThreadExitRegistry::contains(target));
}

// The 64th probe position must be searched by clear().
TEST_F(ThreadExitRegistryTest, ClearRemovesMarkAtLastProbe) {
    const uint64_t target = 2000;
    std::vector<uint64_t> colliders = collidersOf(target, PROBE_LIMIT - 1);
    for (uint64_t tid : colliders) ThreadExitRegistry::markForTest(tid);
    ThreadExitRegistry::markForTest(target);
    ASSERT_TRUE(ThreadExitRegistry::contains(target));
    ThreadExitRegistry::clear(target);
    EXPECT_FALSE(ThreadExitRegistry::contains(target));
    for (uint64_t tid : colliders) EXPECT_TRUE(ThreadExitRegistry::contains(tid)) << tid;
}
