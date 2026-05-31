/*
 * Copyright 2026 Datadog, Inc.
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
#include "thread.h"
#include "threadFilter.h"

// ProfiledThread::parkEnter is responsible for two things:
//  (1) capturing the OTEP TLS context into _park_context via ContextApi::snapshot, and
//  (2) setting FLAG_PARKED atomically via fetch_or.
// These unit tests cover (2). The end-to-end context-capture behavior, including the
// stale-snapshot guarantee that tag encodings mutated after parkEnter do not leak into
// the recorded TaskBlock, is exercised by the Java integration test ParkTaskBlockTest
// where real OTEP TLS is set up.
//
// FLAG_PARKED gates parkExit → TaskBlock recording; its state is verified here through
// parkExit's return value and out-params.

TEST(ProfiledThreadParkStateTest, ParkFlagLifecycle) {
  ProfiledThread *thread = ProfiledThread::forTid(12345);

  // Thread starts not parked: parkExit must return false with no side-effects.
  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));

  thread->parkEnter(777);

  EXPECT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(777ULL, start_ticks);
  // No TLS context is initialized in this unit test, so the snapshot captured at
  // parkEnter is empty (validity-gated) — spanId=0 / tags=0.
  EXPECT_EQ(0ULL, park_context.spanId);
  EXPECT_EQ(0ULL, park_context.rootSpanId);

  // Second exit is a no-op once the parked bit is cleared.
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));
}

TEST(ProfiledThreadParkStateTest, ParkedSpanlessWhenNoActiveSpan) {
  ProfiledThread *thread = ProfiledThread::forTid(12346);
  thread->parkEnter(888);
  // ContextApi::snapshot() returns spanId=0 outside an initialized OTEP TLS, so the
  // context captured at park entry must have spanId=0 (no active span).
  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_TRUE(thread->parkExit(start_ticks, park_context));
  EXPECT_EQ(888ULL, start_ticks);
  EXPECT_EQ(0ULL, park_context.spanId);
}

TEST(ProfiledThreadParkStateTest, NewThreadStartsWithoutParkOrMonitorState) {
  ProfiledThread *thread = ProfiledThread::forTid(12347);

  // A freshly constructed thread must not be parked.
  u64 start_ticks = 0;
  Context park_context = {};
  EXPECT_FALSE(thread->parkExit(start_ticks, park_context));

  // objectWait state must also be clear.
  u64 blocker = 0;
  Context out_ctx = {};
  EXPECT_FALSE(thread->objectWaitExit(start_ticks, out_ctx, blocker));
}

// Once-per-run filter state lives on ThreadFilter::Slot (JVM-process-stable storage), not
// on ProfiledThread (per-thread heap, freed on exit). Both the SIGVTALRM handler (writer +
// reader on the owning thread) and the wall-clock timer thread (reader, fast-path skip)
// reach it through the slot. Behaviour invariants under wallprecheck=true:
// - First signal of a blocked-state run -> markSampledThisRun(state); handler emits MethodSample.
// - Subsequent signal in the SAME blocked state -> sampledThisRun() && state == lastSampledState();
//   handler suppresses emission.
// - Transition within the skip set (SLEEPING -> CONDVAR_WAIT) -> state != lastSampledState();
//   handler re-arms and emits.
// - Transition out of the skip set -> resetSampledRun(state); next blocked-state entry emits again.
TEST(WallClockOncePerRunFilterTest, SlotStateTransitions) {
  ThreadFilter::Slot slot;

  // Initial state: never sampled; state = UNKNOWN. Mirrors a freshly-allocated slot
  // (default-constructed via in-class initializers).
  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  slot.setActiveBlockState(OSThreadState::SLEEPING);
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());

  // First signal of a SLEEPING run: arm + emit.
  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());

  // Subsequent signal in the SAME SLEEPING run: suppression decision is
  // (sampledThisRun() && state == lastSampledState()). The release-acquire ordering on the
  // flag pairs with the relaxed state load so an observer that sees the flag also sees
  // a matching state without needing barriers between the two reads.
  EXPECT_TRUE(slot.sampledThisRun() &&
              OSThreadState::SLEEPING == slot.lastSampledState());
  EXPECT_TRUE(slot.sampledThisRun() &&
              slot.activeBlockState() == slot.lastSampledState());

  // Within-skip-set transition SLEEPING -> CONDVAR_WAIT: identity check fails,
  // so the handler re-arms and emits again. Re-arming overwrites lastSampledState.
  slot.setActiveBlockState(OSThreadState::CONDVAR_WAIT);
  EXPECT_FALSE(slot.sampledThisRun() &&
               OSThreadState::CONDVAR_WAIT == slot.lastSampledState());
  slot.markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot.lastSampledState());
  EXPECT_TRUE(slot.sampledThisRun() &&
              slot.activeBlockState() == slot.lastSampledState());

  // Explicit block exit clears the active block and sampled marker so the next
  // blocked-state entry will emit again.
  slot.setActiveBlockState(OSThreadState::UNKNOWN);
  slot.resetSampledRun(OSThreadState::RUNNABLE);
  EXPECT_FALSE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::RUNNABLE, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot.activeBlockState());

  // Next blocked-state entry after reset: arm + emit again.
  slot.setActiveBlockState(OSThreadState::SLEEPING);
  slot.markSampledThisRun(OSThreadState::SLEEPING);
  EXPECT_TRUE(slot.sampledThisRun());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.lastSampledState());
  EXPECT_EQ(OSThreadState::SLEEPING, slot.activeBlockState());
}

TEST(WallClockOncePerRunFilterTest, FilterHelpersManageActiveBlockState) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();

  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  slot->markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot->sampledThisRun());
  EXPECT_TRUE(slot->sampledThisRun() &&
              slot->activeBlockState() == slot->lastSampledState());

  filter.exitBlockedRun(slot_id);
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
  EXPECT_FALSE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::RUNNABLE, slot->lastSampledState());
}

// Regression for the slot-reuse stuck-suppression hazard: a slot whose previous owner
// exited mid-park ({sampledThisRun=true, lastSampledState=CONDVAR_WAIT,
// activeBlockState=CONDVAR_WAIT}) must be reset before a new thread takes ownership.
// ThreadFilter::resetSlotRunState(slot_id) does this.
TEST(WallClockOncePerRunFilterTest, ResetClearsArmedFlagOnSlotReuse) {
  ThreadFilter filter;
  filter.init("1");
  ThreadFilter::SlotID slot_id = filter.registerThread();
  filter.enterBlockedRun(slot_id, OSThreadState::CONDVAR_WAIT);
  ThreadFilter::Slot *slot = filter.slotForId(slot_id);
  ASSERT_NE(nullptr, slot);
  slot->markSampledThisRun(OSThreadState::CONDVAR_WAIT);
  EXPECT_TRUE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::CONDVAR_WAIT, slot->activeBlockState());

  filter.resetSlotRunState(slot_id);

  // Post-conditions a new occupant requires: flag clear AND state distinct from any blocked
  // skip-set value, so the very next signal in any state goes through the handler's
  // is-blocked-skip-state branch as "first of run" rather than a suppress decision.
  EXPECT_FALSE(slot->sampledThisRun());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->lastSampledState());
  EXPECT_EQ(OSThreadState::UNKNOWN, slot->activeBlockState());
}
