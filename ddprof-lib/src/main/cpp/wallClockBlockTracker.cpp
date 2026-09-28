/*
 * Copyright 2026, Datadog, Inc
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
#include "wallClockBlockTracker.h"

u64 WallClockBlockTracker::enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                                           OSThreadState state, BlockRunOwner owner) {
    ThreadFilter::Slot* identity_slot = registry->slotForId(slot_id);
    BlockState* block_slot = slotForId(slot_id);
    if (identity_slot == nullptr || block_slot == nullptr) {
        return 0;
    }
    u32 generation = 0;
    if (!block_slot->trySetActiveBlockRun(identity_slot, state, owner, &generation,
                                          registry->unfilteredWallTrackingActive())) {
        return 0;
    }
    return ThreadFilter::encodeBlockRunToken(slot_id, generation);
}

void WallClockBlockTracker::exitBlockedRun(ThreadFilter::SlotID slot_id) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetSlot(OSThreadState::RUNNABLE);
    }
}

bool WallClockBlockTracker::exitBlockedRun(ThreadFilter::SlotID slot_id, u32 generation) {
    BlockState* s = slotForId(slot_id);
    if (s == nullptr || generation == 0 || s->blockGeneration() != generation) {
        return false;
    }
    s->resetSlot(OSThreadState::RUNNABLE);
    return true;
}

void WallClockBlockTracker::resetSlot(ThreadFilter::SlotID slot_id, OSThreadState state) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetSlot(state);
    }
}

void WallClockBlockTracker::resetAll() {
    for (ThreadFilter::SlotID slot_id = 0; slot_id < ThreadFilter::kMaxThreads; ++slot_id) {
        _slots[slot_id].resetSlot(OSThreadState::UNKNOWN);
    }
}

bool WallClockBlockTracker::shouldSuppressOwnedBlock(ThreadFilter* registry,
                                                     const ThreadEntry& entry) const {
    ThreadFilter::Slot* identity_slot = entry.slot;
    if (identity_slot == nullptr || identity_slot->nativeTid() != entry.tid ||
        identity_slot->lifecycleGeneration() != entry.lifecycle_generation) {
        return false;
    }
    BlockState* slot = slotForId(entry.slot_id);
    if (slot == nullptr) {
        return false;
    }

    const bool unfiltered_tracking = registry->unfilteredWallTrackingActive();
    ThreadFilter::RecordingEpoch epoch = 0;
    if (unfiltered_tracking) {
        epoch = registry->recordingEpoch();
        if (epoch == 0 || entry.recording_epoch != epoch ||
            identity_slot->recordingEpoch() != epoch) {
            return false;
        }
    }

#ifdef UNIT_TEST
    if (_suppression_snapshot_hook != nullptr) {
        _suppression_snapshot_hook(_suppression_snapshot_hook_arg);
    }
#endif

    u32 block_generation = slot->blockGeneration();
    BlockRunOwner owner = slot->activeBlockOwner();
    OSThreadState state = slot->activeBlockState();
    bool context_eligible =
        !unfiltered_tracking || slot->activeBlockRemainedOutsideContextWindow(identity_slot);
    bool sampled = slot->sampledThisRun();
    OSThreadState last_sampled_state =
        sampled ? slot->lastSampledState() : OSThreadState::UNKNOWN;
    bool suppressible_state = isPrecheckSuppressionState(state);
    if (owner == BlockRunOwner::NONE || !context_eligible ||
        !suppressible_state || !sampled || state != last_sampled_state) {
        return false;
    }

    // The payload is spread across independent atomics. Accept it only if the
    // slot still represents the lifecycle and block run captured earlier in
    // this wall-clock timer-thread pass, when `entry` was populated — either
    // by ThreadFilter::collect() (inside timerLoop()'s collectThreads lambda)
    // or by the lazy registry lookup at the top of sampleThreadCommon() —
    // both in wallClock.cpp/.h (BaseWallClock::timerLoopCommon() itself is a
    // template defined in wallClock.h).
    if (slot->activeBlockOwner() != owner ||
        slot->blockGeneration() != block_generation ||
        identity_slot->nativeTid() != entry.tid ||
        identity_slot->lifecycleGeneration() != entry.lifecycle_generation) {
        return false;
    }
    if (unfiltered_tracking &&
        (registry->recordingEpoch() != epoch || identity_slot->recordingEpoch() != epoch ||
         !slot->activeBlockRemainedOutsideContextWindow(identity_slot))) {
        return false;
    }
    return true;
}
