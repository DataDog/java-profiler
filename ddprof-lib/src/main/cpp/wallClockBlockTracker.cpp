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
#include "callTraceStorage.h"
#include "counters.h"
#include "signalSafety.h"
#include <memory>
#include <new>

WallClockBlockTracker::WallClockBlockTracker() {
    // Storage is allocated lazily by ensureAllocated(); nothing to record yet.
}

WallClockBlockTracker::~WallClockBlockTracker() {
    SlotStorage* storage = _storage.exchange(nullptr, std::memory_order_acq_rel);
    if (storage != nullptr) {
        delete storage;
        NativeMem::record(NM_WALLCLOCK, -static_cast<long long>(sizeof(SlotStorage)));
    }
    for (auto& pointer : _context_chunks) {
        UnownedContextChunk* chunk = pointer.exchange(nullptr, std::memory_order_acq_rel);
        if (chunk != nullptr) {
            delete chunk;
            NativeMem::record(NM_WALLCLOCK, -static_cast<long long>(sizeof(UnownedContextChunk)));
        }
    }
}

bool WallClockBlockTracker::ensureAllocated() {
    if (_storage.load(std::memory_order_acquire) != nullptr) {
        return true;
    }
    // A default-constructed BlockState is the resetSlot(UNKNOWN) state.
    SlotStorage* fresh = new (std::nothrow) SlotStorage();
    if (fresh == nullptr) {
        return false;
    }
    SlotStorage* expected = nullptr;
    if (_storage.compare_exchange_strong(expected, fresh, std::memory_order_acq_rel,
                                         std::memory_order_acquire)) {
        NativeMem::record(NM_WALLCLOCK, static_cast<long long>(sizeof(SlotStorage)));
    } else {
        delete fresh;
    }
    return true;
}

u64 WallClockBlockTracker::enterBlockedRun(ThreadFilter* registry, ThreadFilter::SlotID slot_id,
                                           OSThreadState state, BlockRunOwner owner) {
#ifdef UNIT_TEST
    if (_block_admission_hook != nullptr) {
        _block_admission_hook(_block_admission_hook_arg);
    }
#endif
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
    return WallClockBlockTracker::encodeBlockRunToken(slot_id, generation);
}

bool WallClockBlockTracker::exitBlockedRun(ThreadFilter::SlotID slot_id, u32 generation) {
    BlockState* s = slotForId(slot_id);
    if (s == nullptr || generation == 0 || s->blockGeneration() != generation) {
        return false;
    }
    // Owned-run fields only; the unowned-blocked tail survives the exit (R-B1).
    s->clearActiveBlockRun(OSThreadState::RUNNABLE);
    return true;
}

void WallClockBlockTracker::resetSlot(ThreadFilter::SlotID slot_id, OSThreadState state) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->resetSlot(state);
    }
}

void WallClockBlockTracker::resetAll() {
    SlotStorage* storage = _storage.load(std::memory_order_acquire);
    if (storage == nullptr) {
        return;
    }
    for (auto& s : storage->slots) {
        s.resetSlot(OSThreadState::UNKNOWN);
    }
}

void WallClockBlockTracker::clearActiveBlockRun(ThreadFilter::SlotID slot_id, OSThreadState state) {
    BlockState* s = slotForId(slot_id);
    if (s != nullptr) {
        s->clearActiveBlockRun(state);
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

#ifdef UNIT_TEST
    if (_suppression_snapshot_hook != nullptr) {
        _suppression_snapshot_hook(_suppression_snapshot_hook_arg);
    }
#endif

    // Independent atomics can describe different runs during an exit/re-entry.
    // Reject a payload unless both the identity and block generation still match.
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

#ifdef UNIT_TEST
size_t WallClockBlockTracker::storageSize() {
    return sizeof(SlotStorage);
}

size_t WallClockBlockTracker::unownedContextChunkSizeForTest() {
    return sizeof(UnownedContextChunk);
}

bool WallClockBlockTracker::exchangeUnownedContextAllocationFailureForTest(bool fail) {
    return _context_allocation_failure.exchange(fail, std::memory_order_acq_rel);
}

void WallClockBlockTracker::setUnownedContextPublicationForTest(ThreadFilter::SlotID slot_id,
                                                               u64 publication) {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    auto* cell = unownedContextCell(slot_id);
    assert(cell != nullptr);
    if (cell != nullptr) cell->publication.store(publication, std::memory_order_release);
}
#endif

void WallClockBlockTracker::setUnownedContextSnapshotsNeeded(bool needed) {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    _context_snapshots_needed.store(needed, std::memory_order_release);
}

bool WallClockBlockTracker::ensureUnownedContextAllocated(ThreadFilter::SlotID slot_id) {
    DEBUG_ASSERT_NOT_IN_SIGNAL();
    if (slot_id < 0 || slot_id >= ThreadFilter::kMaxThreads) return false;
    if (!_context_snapshots_needed.load(std::memory_order_acquire)) return true;
    auto& pointer = _context_chunks[slot_id >> ThreadFilter::kChunkShift];
    if (pointer.load(std::memory_order_acquire) != nullptr) return true;
#ifdef UNIT_TEST
    if (_context_allocation_failure.load(std::memory_order_acquire)) return false;
#endif
    std::unique_ptr<UnownedContextChunk> fresh(new (std::nothrow) UnownedContextChunk());
    if (!fresh) return false;
    // All callers hold the same registry mutex (or are quiescent tests).
    // No competing allocator or fallible operation follows allocation, so no
    // rejected allocation needs freeing inside the registry critical section.
    pointer.store(fresh.release(), std::memory_order_release);
    NativeMem::record(NM_WALLCLOCK, static_cast<long long>(sizeof(UnownedContextChunk)));
    return true;
}

WallClockBlockTracker::UnownedContextCell* WallClockBlockTracker::unownedContextCell(
        ThreadFilter::SlotID slot_id) const {
    if (slot_id < 0 || slot_id >= ThreadFilter::kMaxThreads) return nullptr;
    auto* chunk = _context_chunks[slot_id >> ThreadFilter::kChunkShift].load(std::memory_order_acquire);
    return chunk != nullptr ? &chunk->cells[slot_id & ThreadFilter::kChunkMask] : nullptr;
}

bool WallClockBlockTracker::canPublishUnownedContext(ThreadFilter::SlotID slot_id) const {
    if (!_context_snapshots_needed.load(std::memory_order_acquire)) return false;
    auto* cell = unownedContextCell(slot_id);
    if (cell == nullptr) return false;
    u64 publication = cell->publication.load(std::memory_order_acquire);
    return (publication & 1) == 0 && publication != UINT64_MAX - 1;
}

bool WallClockBlockTracker::readUnownedContext(ThreadFilter::SlotID slot_id, Context& context,
                                              u64& publication) const {
    publication = 0;
    auto* cell = unownedContextCell(slot_id);
    auto* block = slotForId(slot_id);
    if (cell == nullptr || block == nullptr) return false;
    u64 before = cell->publication.load(std::memory_order_acquire);
    if (before == 0 || (before & 1) != 0) return false;
    context.spanId = cell->words[0].load(std::memory_order_acquire);
    context.rootSpanId = cell->words[1].load(std::memory_order_acquire);
    for (int i = 0; i < 5; ++i) {
        u64 pair = cell->words[i + 2].load(std::memory_order_acquire);
        context.setTag(i * 2, static_cast<u32>(pair));
        context.setTag(i * 2 + 1, static_cast<u32>(pair >> 32));
    }
#ifdef UNIT_TEST
    if (_context_read_hook != nullptr) _context_read_hook(_context_read_hook_arg);
#endif
    u64 root = block->unowned_blocked_call_trace_id.load(std::memory_order_acquire);
    u64 after = cell->publication.load(std::memory_order_acquire);
    if (before != after || root == 0) return false;
    publication = before;
    return true;
}

// One bounded ownership attempt. Every operation while owned is a trusted
// atomic access; no stack walk or fault-recovery jump may cross this scope.
class UnownedContextPublication {
    std::atomic<u64>& sequence;
    u64 next = 0;
public:
    explicit UnownedContextPublication(std::atomic<u64>& value) : sequence(value) {
        u64 even = sequence.load(std::memory_order_acquire);
        if ((even & 1) == 0 && even != UINT64_MAX - 1 &&
            sequence.compare_exchange_strong(even, even + 1, std::memory_order_acq_rel,
                                               std::memory_order_acquire)) {
            next = even + 2;
        }
    }
    ~UnownedContextPublication() {
        if (owned()) sequence.store(next, std::memory_order_release);
    }
    bool owned() const { return next != 0; }
    UnownedContextPublication(const UnownedContextPublication&) = delete;
    UnownedContextPublication& operator=(const UnownedContextPublication&) = delete;
};

bool WallClockBlockTracker::deferUnownedWeight(ThreadFilter::SlotID slot_id, u64 epoch_start) {
    auto* cell = unownedContextCell(slot_id);
    auto* block = slotForId(slot_id);
    if (cell == nullptr || block == nullptr || epoch_start == 0) return false;
    for (auto& segment : cell->segments) {
        u64 weight = segment.weight.load(std::memory_order_acquire);
        if (weight == 0 || segment.epoch_start.load(std::memory_order_acquire) == epoch_start) {
            segment.epoch_start.store(epoch_start, std::memory_order_release);
            segment.weight.store(weight + 1, std::memory_order_release);
            block->unowned_blocked_pending_weight.fetch_add(1, std::memory_order_release);
            return true;
        }
    }
    return false;
}

size_t WallClockBlockTracker::copyUnownedWeightSegments(ThreadFilter::SlotID slot_id,
                                                       WeightSegment* segments) const {
    auto* cell = unownedContextCell(slot_id);
    if (cell == nullptr) return 0;
    size_t count = 0;
    for (size_t i = 0; i < kMaxWeightSegments; ++i) {
        u64 weight = cell->segments[i].weight.load(std::memory_order_acquire);
        if (weight != 0) {
            segments[count++] = {cell->segments[i].epoch_start.load(std::memory_order_acquire), weight, i};
        }
    }
    return count;
}

bool WallClockBlockTracker::unownedWeightMatchesEpoch(ThreadFilter::SlotID slot_id,
                                                     u64 epoch_start) const {
    WeightSegment segments[kMaxWeightSegments];
    size_t count = copyUnownedWeightSegments(slot_id, segments);
    u64 weight = 0;
    for (size_t i = 0; i < count; ++i) {
        if (segments[i].epoch_start != epoch_start) return false;
        weight += segments[i].weight;
    }
    auto* block = slotForId(slot_id);
    return block != nullptr && weight == block->unowned_blocked_pending_weight.load(std::memory_order_acquire);
}

void WallClockBlockTracker::commitUnownedWeightSegment(ThreadFilter::SlotID slot_id,
                                                      const WeightSegment& segment) {
    auto* cell = unownedContextCell(slot_id);
    auto* block = slotForId(slot_id);
    if (cell == nullptr || block == nullptr) return;
    auto& retained = cell->segments[segment.index];
    if (retained.epoch_start.load(std::memory_order_acquire) == segment.epoch_start) {
        u64 expected = segment.weight;
        if (retained.weight.compare_exchange_strong(expected, 0, std::memory_order_acq_rel)) {
            block->unowned_blocked_pending_weight.fetch_sub(segment.weight, std::memory_order_release);
        }
    }
}

void WallClockBlockTracker::clearUnownedWeightSegments(ThreadFilter::SlotID slot_id) {
    auto* cell = unownedContextCell(slot_id);
    if (cell != nullptr) {
        for (auto& segment : cell->segments) segment.weight.store(0, std::memory_order_release);
    }
}

bool WallClockBlockTracker::publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id,
                                                OSThreadState state, const Context& context) {
    SlotStorage* storage = _storage.load(std::memory_order_acquire);
    auto* cell = unownedContextCell(slot_id);
    if (storage == nullptr || cell == nullptr || trace_id == 0 ||
        !_context_snapshots_needed.load(std::memory_order_acquire)) return false;
    UnownedContextPublication publication(cell->publication);
    if (!publication.owned()) return false;
    if (storage->slots[slot_id].unowned_blocked_pending_weight.load(std::memory_order_acquire) == 0) {
        clearUnownedWeightSegments(slot_id);
    }
#ifdef UNIT_TEST
    if (_context_publication_hook != nullptr) _context_publication_hook(0, _context_publication_hook_arg);
#endif
    for (int word = 0; word < 7; ++word) {
        u64 value = word == 0 ? context.spanId : context.rootSpanId;
        if (word >= 2) {
            int tag = (word - 2) * 2;
            value = static_cast<u64>(context.getTag(tag)) |
                    (static_cast<u64>(context.getTag(tag + 1)) << 32);
        }
        cell->words[word].store(value, std::memory_order_release);
#ifdef UNIT_TEST
        if (_context_publication_hook != nullptr) {
            _context_publication_hook(word + 1, _context_publication_hook_arg);
        }
#endif
    }
    storage->slots[slot_id].recordUnownedBlockedSample(trace_id, state);
    storage->roots[slot_id / 64].fetch_or(1ULL << (slot_id % 64), std::memory_order_release);
    return true;
}

#ifdef UNIT_TEST
void WallClockBlockTracker::publishUnownedTrace(ThreadFilter::SlotID slot_id, u64 trace_id,
                                                OSThreadState state) {
    SlotStorage* storage = _storage.load(std::memory_order_acquire);
    if (storage == nullptr || slot_id < 0 || slot_id >= ThreadFilter::kMaxThreads) return;
    storage->slots[slot_id].recordUnownedBlockedSample(trace_id, state);
    storage->roots[slot_id / 64].fetch_or(1ULL << (slot_id % 64), std::memory_order_release);
}
#endif

void WallClockBlockTracker::collectLiveTraceIds(CallTraceIdSet& live) {
    SlotStorage* storage = _storage.load(std::memory_order_acquire);
    if (storage == nullptr) return;
    for (size_t word = 0; word < storage->roots.size(); ++word) {
        u64 bits = storage->roots[word].load(std::memory_order_acquire);
        while (bits != 0) {
            const unsigned bit = __builtin_ctzll(bits);
            const u64 mask = 1ULL << bit;
            const u64 id = storage->slots[word * 64 + bit].unowned_blocked_call_trace_id.load(
                std::memory_order_acquire);
            if (id == 0) {
                // Only this collector prunes. Lifecycle resets never clear a bit,
                // and publication is excluded by the recording stripes.
                storage->roots[word].fetch_and(~mask, std::memory_order_release);
            } else if (id != CallTraceStorage::DROPPED_TRACE_ID) {
                live.insert(id);
            }
            bits &= bits - 1;
        }
    }
}

void WallClockBlockTracker::onUnpreservedTraceIds(const CallTraceIdSet& failed) {
    SlotStorage* storage = _storage.load(std::memory_order_acquire);
    if (storage == nullptr || failed.empty()) return;
    for (size_t word = 0; word < storage->roots.size(); ++word) {
        u64 bits = storage->roots[word].load(std::memory_order_acquire);
        while (bits != 0) {
            const unsigned bit = __builtin_ctzll(bits);
            auto& cached = storage->slots[word * 64 + bit].unowned_blocked_call_trace_id;
            u64 id = cached.load(std::memory_order_acquire);
            if (id != 0 && id != CallTraceStorage::DROPPED_TRACE_ID && failed.count(id) != 0 &&
                cached.compare_exchange_strong(id, CallTraceStorage::DROPPED_TRACE_ID,
                                               std::memory_order_acq_rel,
                                               std::memory_order_acquire)) {
                Counters::increment(WC_UNOWNED_BLOCKED_TRACE_PRESERVATION_FAILED);
            }
            bits &= bits - 1;
        }
    }
}
