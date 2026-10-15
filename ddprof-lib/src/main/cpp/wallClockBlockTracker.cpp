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
#include "nativeMem.h"

WallClockBlockTracker::WallClockBlockTracker() {
    NativeMem::record(NM_WALLCLOCK, static_cast<long long>(sizeof(_slots)));
}

WallClockBlockTracker::~WallClockBlockTracker() {
    NativeMem::record(NM_WALLCLOCK, -static_cast<long long>(sizeof(_slots)));
}

u64 WallClockBlockTracker::enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                                           OSThreadState state, BlockRunOwner owner) {
    if (state == OSThreadState::UNKNOWN) return 0;
    ThreadFilter::Slot* identity_slot = registry->slotForId(slot_id);
    BlockState* block_slot = slotForId(slot_id);
    if (identity_slot == nullptr || block_slot == nullptr) {
        return 0;
    }
    u64 generation = 0;
    if (!block_slot->tryPrepareActiveBlockRun(identity_slot, owner, &generation,
                                              registry->unfilteredWallTrackingActive())) {
        return 0;
    }
    block_slot->publishActiveBlockRun(state);
    return encodeBlockRunToken(slot_id, generation);
}

void WallClockBlockTracker::exitBlockedRun(ThreadFilter::SlotID slot_id) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetSlot();
    }
}

static inline bool isActiveRun(const WallClockBlockTracker::BlockState* s, u64 generation) {
    return s != nullptr && generation != 0 &&
           s->activeBlockState() != OSThreadState::UNKNOWN &&
           s->activeBlockOwner() != BlockRunOwner::NONE &&
           s->blockGeneration() == generation;
}

bool WallClockBlockTracker::exitBlockedRun(ThreadFilter::SlotID slot_id, u64 generation) {
    BlockState* s = slotForId(slot_id);
    if (!isActiveRun(s, generation)) {
        return false;
    }
    s->resetSlot();
    return true;
}

bool WallClockBlockTracker::snapshotAndExitBlockedRun(ThreadFilter* registry,
                                                      ThreadFilter::SlotID slot_id,
                                                      u64 generation,
                                                      BlockRunSnapshot* snapshot) {
    ThreadFilter::Slot* identity_slot = registry->slotForId(slot_id);
    BlockState* s = slotForId(slot_id);
    if (identity_slot == nullptr || !isActiveRun(s, generation)) {
        return false;
    }
    if (snapshot != nullptr) *snapshot = s->snapshotBlockRun(identity_slot);
    s->resetSlot();
    return true;
}

void WallClockBlockTracker::resetSlot(ThreadFilter::SlotID slot_id) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetSlot();
    }
}

void WallClockBlockTracker::resetSlotForReuse(ThreadFilter::SlotID slot_id) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetBlockGeneration();
        s->resetSlot();
    }
}

void WallClockBlockTracker::resetAll() {
    for (ThreadFilter::SlotID slot_id = 0; slot_id < ThreadFilter::kMaxThreads; ++slot_id) {
        _slots[slot_id].resetSlot();
    }
}

void WallClockBlockTracker::clearActiveBlockRun(ThreadFilter::SlotID slot_id) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->clearActiveBlockRun();
    }
}

bool WallClockBlockTracker::hasActiveBlockRun(ThreadFilter::SlotID slot_id) const {
    const BlockState* s = slotForId(slot_id);
    return s != nullptr && s->activeBlockOwner() != BlockRunOwner::NONE;
}

void WallClockBlockTracker::collectUnownedBlockedTraceIds(
    const std::function<void(u64)>& visit) const {
    for (const BlockState& slot : _slots) {
        u64 call_trace_id = slot.unowned_blocked_call_trace_id.load(std::memory_order_acquire);
        if (call_trace_id != 0) {
            visit(call_trace_id);
        }
    }
}

bool WallClockBlockTracker::activeOwnedBlockGeneration(ThreadFilter* registry,
                                                       const ThreadEntry& entry,
                                                       u64& generation) const {
    bool already_sampled = false;
    return ownedBlockGeneration(registry, entry, generation, already_sampled);
}

bool WallClockBlockTracker::isOwnedBlockSuppressionCandidate(ThreadFilter* registry,
                                                             const ThreadEntry& entry) const {
    u64 generation = 0;
    bool already_sampled = false;
    return ownedBlockGeneration(registry, entry, generation, already_sampled) &&
           already_sampled;
}

bool WallClockBlockTracker::ownedBlockGeneration(ThreadFilter* registry,
                                                 const ThreadEntry& entry,
                                                 u64& generation,
                                                 bool& already_sampled) const {
    ThreadFilter::Slot* identity_slot = entry.slot;
    if (!registry->unfilteredWallTrackingActive() || identity_slot == nullptr ||
        identity_slot->nativeTid() != entry.tid ||
        identity_slot->lifecycleGeneration() != entry.lifecycle_generation) {
        return false;
    }
    BlockState* slot = slotForId(entry.slot_id);
    if (slot == nullptr) {
        return false;
    }

    // active_block_state publishes the rest of the block-run payload. Acquire
    // it before reading the context epoch, owner, or generation so those reads
    // observe the stores that preceded publishActiveBlockRun().
    OSThreadState state = slot->activeBlockState();
    if (!isPrecheckSuppressionState(state)) return false;

    ThreadFilter::RecordingEpoch epoch = registry->recordingEpoch();
    if (epoch == 0 || entry.recording_epoch != epoch ||
        identity_slot->recordingEpoch() != epoch ||
        !slot->activeBlockRemainedOutsideContextWindow(identity_slot)) {
        return false;
    }

    u64 block_generation = slot->blockGeneration();
    BlockRunOwner owner = slot->activeBlockOwner();
    u64 sampled_generation = slot->sampledBlockGeneration();
    if (owner == BlockRunOwner::NONE) return false;

#ifdef UNIT_TEST
    if (_suppression_snapshot_hook != nullptr) {
        _suppression_snapshot_hook(_suppression_snapshot_hook_arg);
    }
#endif

    // The payload is spread across independent atomics. Accept it only if the
    // slot still represents the lifecycle and block run captured earlier in
    // this wall-clock timer-thread pass, when `entry` was populated — either
    // by ThreadFilter::collect() (inside timerLoop()'s collectThreads lambda)
    // or by the lazy registry lookup at the top of sampleThreadCommon() —
    // both in wallClock.cpp/.h (BaseWallClock::timerLoopCommon() itself is a
    // template defined in wallClock.h).
    if (slot->activeBlockOwner() != owner ||
        slot->blockGeneration() != block_generation ||
        slot->activeBlockState() != state ||
        identity_slot->nativeTid() != entry.tid ||
        identity_slot->lifecycleGeneration() != entry.lifecycle_generation ||
        slot->sampledBlockGeneration() != sampled_generation) {
        return false;
    }
    if (registry->recordingEpoch() != epoch || identity_slot->recordingEpoch() != epoch ||
        !slot->activeBlockRemainedOutsideContextWindow(identity_slot)) {
        return false;
    }
    generation = block_generation;
    already_sampled = sampled_generation == block_generation;
    return true;
}
