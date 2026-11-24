/*
 * Copyright 2026, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>

#include "monitorEntryStacks.h"
#include "nativeMem.h"
#include "profiler.h"

#include <type_traits>
#include <vector>

static_assert(!std::is_copy_constructible<MonitorEntryStackLease>::value,
              "a copied lease would release its slot twice");

namespace {
constexpr int kDepth = 4;

class MonitorEntryStacksTest : public ::testing::Test {
protected:
  MonitorEntryStacks stacks;

  void SetUp() override { ASSERT_TRUE(stacks.allocate(kDepth)); }
  void TearDown() override { stacks.release(); }

  void capture(u64 lease, jmethodID method) {
    CallTraceBuffer* buffer = stacks.buffer(lease);
    ASSERT_NE(nullptr, buffer);
    buffer->_asgct_frames[0].method_id = method;
    buffer->_asgct_frames[0].bci = 7;
    stacks.setCaptured(lease, 1, true);
  }
};
} // namespace

TEST_F(MonitorEntryStacksTest, UnallocatedOrMismatchedDepthNeverClaims) {
  MonitorEntryStacks idle;
  EXPECT_FALSE(idle.allocated());
  EXPECT_EQ(0u, idle.claim(kDepth));
  EXPECT_FALSE(idle.allocate(0));
  EXPECT_EQ(0u, stacks.claim(kDepth + 1)) << "slots hold kDepth + 1 frames only";
  EXPECT_FALSE(stacks.allocate(kDepth)) << "a second allocation would leak the first";
  EXPECT_EQ(0, stacks.claimedForTest());
}

TEST_F(MonitorEntryStacksTest, AllocationIsChargedToCallTraceAndReturnedOnRelease) {
  MonitorEntryStacks other;
  long long before = NativeMem::live(NM_CALLTRACE);
  ASSERT_TRUE(other.allocate(kDepth));
  EXPECT_EQ(before + static_cast<long long>(MonitorEntryStacks::SLOTS * (kDepth + 1) *
                                            sizeof(CallTraceBuffer)),
            NativeMem::live(NM_CALLTRACE));
  other.release();
  EXPECT_EQ(before, NativeMem::live(NM_CALLTRACE));
  EXPECT_FALSE(other.allocated());
}

TEST_F(MonitorEntryStacksTest, LeaseReleasesItsSlotExactlyOnce) {
  u64 first = stacks.claim(kDepth);
  ASSERT_NE(0u, first);
  {
    MonitorEntryStackLease lease(&stacks, first);
    EXPECT_EQ(1, stacks.claimedForTest());
  }
  EXPECT_EQ(0, stacks.claimedForTest());
  u64 second = stacks.claim(kDepth);
  ASSERT_NE(0u, second);
  // A repeated release of the first lease must not free the reclaimed slot.
  stacks.unclaim(first);
  EXPECT_EQ(1, stacks.claimedForTest());
  {
    MonitorEntryStackLease lease(&stacks, second);
    EXPECT_EQ(second, lease.detach());
  }
  EXPECT_EQ(1, stacks.claimedForTest()) << "a detached lease must stay claimed";
  stacks.unclaim(second);
  EXPECT_EQ(0, stacks.claimedForTest());
}

TEST_F(MonitorEntryStacksTest, FramesAreReturnedOnlyAfterCapture) {
  u64 lease = stacks.claim(kDepth);
  ASSERT_NE(0u, lease);
  int num_frames = -1;
  bool truncated = false;
  EXPECT_EQ(nullptr, stacks.frames(lease, num_frames, truncated));
  capture(lease, reinterpret_cast<jmethodID>(0x1234));
  ASSERT_NE(nullptr, stacks.frames(lease, num_frames, truncated));
  EXPECT_EQ(1, num_frames);
  EXPECT_TRUE(truncated);
  EXPECT_EQ(reinterpret_cast<jmethodID>(0x1234),
            stacks.frames(lease, num_frames, truncated)[0].method_id);
  stacks.unclaim(lease);
  EXPECT_EQ(nullptr, stacks.frames(lease, num_frames, truncated));
  EXPECT_EQ(nullptr, stacks.buffer(lease));
}

TEST_F(MonitorEntryStacksTest, ExhaustionRejectsOnlyPastCapacity) {
  std::vector<u64> leases;
  for (int i = 0; i < MonitorEntryStacks::SLOTS; i++) {
    u64 lease = stacks.claim(kDepth);
    ASSERT_NE(0u, lease) << "slot " << i;
    leases.push_back(lease);
  }
  EXPECT_EQ(0u, stacks.claim(kDepth));
  stacks.unclaim(leases.back());
  EXPECT_NE(0u, stacks.claim(kDepth)) << "a released slot must be claimable again";
}

TEST_F(MonitorEntryStacksTest, LeaseFromPreviousRecordingIsNeverUsed) {
  u64 old_lease = stacks.claim(kDepth);
  ASSERT_NE(0u, old_lease);
  capture(old_lease, reinterpret_cast<jmethodID>(0x1));
  stacks.release();
  int num_frames = 0;
  bool truncated = false;
  EXPECT_EQ(nullptr, stacks.frames(old_lease, num_frames, truncated));
  ASSERT_TRUE(stacks.allocate(kDepth));
  EXPECT_EQ(0, stacks.claimedForTest()) << "release() reclaims slots of exited holders";
  EXPECT_EQ(nullptr, stacks.frames(old_lease, num_frames, truncated));
  EXPECT_EQ(nullptr, stacks.buffer(old_lease));

  u64 new_lease = stacks.claim(kDepth);
  ASSERT_NE(0u, new_lease);
  ASSERT_NE(old_lease, new_lease) << "the same slot index carries a new serial";
  capture(new_lease, reinterpret_cast<jmethodID>(0x2));
  stacks.unclaim(old_lease);
  EXPECT_EQ(1, stacks.claimedForTest()) << "a stale release must not free a new lease";
  EXPECT_EQ(nullptr, stacks.frames(old_lease, num_frames, truncated));
  ASSERT_NE(nullptr, stacks.frames(new_lease, num_frames, truncated));
  stacks.unclaim(new_lease);
}
