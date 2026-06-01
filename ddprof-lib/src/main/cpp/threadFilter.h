/*
 * Copyright 2025, 2026 Datadog, Inc
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
#ifndef _THREADFILTER_H
#define _THREADFILTER_H

#include <atomic>
#include <array>
#include <vector>
#include <cstdint>
#include <memory>

#include "arch.h"
#include "threadState.h"

struct ThreadEntry;  // defined after ThreadFilter; carries a pointer to a ThreadFilter::Slot

class ThreadFilter {
public:
    using SlotID = int;

    // Optimized limits for reasonable memory usage
    static constexpr int kChunkSize = 256;
    static constexpr int kChunkShift = 8;   // log2(256)
    static constexpr int kChunkMask = kChunkSize - 1;
    static constexpr int kMaxThreads = 2048;
    static constexpr int kMaxChunks = (kMaxThreads + kChunkSize - 1) / kChunkSize;  // = 8 chunks
    // High-performance free list using Treiber stack, 64 shards
    static constexpr int kFreeListSize  = 1024;       // power-of-two for fast modulo
    static constexpr int kShardCount    = 64;          // power-of-two for fast modulo

    // One cache line per slot to avoid false sharing. Slot instances are never freed
    // (ChunkStorage is process-lifetime), so a captured Slot* is always dereferenceable.
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        std::atomic<int>           value{-1};                    // 4 bytes
        // Wall-clock once-per-run suppression state. Written by the signal handler on the
        // owning thread; read by the timer thread. Release/acquire on sampled_this_run
        // pairs with relaxed last_sampled_state, following the standard flag+payload pattern.
        std::atomic<OSThreadState> last_sampled_state{OSThreadState::UNKNOWN};  // 4 bytes
        // Set by explicit block enter/exit hooks. It lets the timer skip sending a signal
        // only while instrumentation still owns a suppressible blocking interval.
        std::atomic<OSThreadState> active_block_state{OSThreadState::UNKNOWN};   // 4 bytes
        std::atomic<bool>          sampled_this_run{false};                     // 1 byte
        char padding[DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<bool>)]; // sampled_this_run

        inline bool sampledThisRun() const {
            return sampled_this_run.load(std::memory_order_acquire);
        }
        inline OSThreadState lastSampledState() const {
            return last_sampled_state.load(std::memory_order_relaxed);
        }
        inline void markSampledThisRun(OSThreadState state) {
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(true, std::memory_order_release);
        }
        inline void resetSampledRun(OSThreadState state) {
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(false, std::memory_order_release);
        }
        inline OSThreadState activeBlockState() const {
            return active_block_state.load(std::memory_order_acquire);
        }
        inline void setActiveBlockState(OSThreadState state) {
            active_block_state.store(state, std::memory_order_release);
        }
    };
    static_assert(sizeof(Slot) == DEFAULT_CACHE_LINE_SIZE, "Slot must be exactly one cache line");
    static_assert(std::atomic<OSThreadState>::is_always_lock_free,
                  "Slot OSThreadState fields must be lock-free for signal-handler safety");
    static_assert(std::atomic<bool>::is_always_lock_free,
                  "Slot::sampled_this_run must be lock-free for signal-handler safety");

    ThreadFilter();
    ~ThreadFilter();

    void init(const char* filter);
    void initFreeList();
    bool enabled() const;
    // Hot path methods - slot_id MUST be from registerThread(), undefined behavior otherwise
    bool accept(SlotID slot_id) const;
    void add(int tid, SlotID slot_id);
    void remove(SlotID slot_id);
    void collect(std::vector<int>& tids) const;
    void collect(std::vector<ThreadEntry>& entries) const;
    void resetSlotRunState(SlotID slot_id);
    void enterBlockedRun(SlotID slot_id, OSThreadState state);
    void exitBlockedRun(SlotID slot_id);

    // Returns nullptr if slot_id is invalid or its chunk has not been allocated.
    inline Slot* slotForId(SlotID slot_id) const {
        if (slot_id < 0) return nullptr;
        int chunk_idx = slot_id >> kChunkShift;
        int slot_idx  = slot_id & kChunkMask;
        if (chunk_idx >= kMaxChunks) return nullptr;
        ChunkStorage* chunk = _chunks[chunk_idx].load(std::memory_order_acquire);
        return chunk != nullptr ? &chunk->slots[slot_idx] : nullptr;
    }

    SlotID registerThread();
    void unregisterThread(SlotID slot_id);

private:

    // Lock-free free list using a stack-like structure
    struct FreeListNode {
        std::atomic<int> value{-1};
        std::atomic<int> next{-1};
    };

    // Pre-allocated chunk storage to eliminate mutex contention
    struct ChunkStorage {
        std::array<Slot, kChunkSize> slots;
    };

    std::atomic<bool> _enabled{false};

    // Lazily allocated storage for chunks
    std::atomic<ChunkStorage*> _chunks[kMaxChunks];
    std::atomic<int> _num_chunks{1};

    // Lock-free slot allocation
    std::atomic<SlotID> _next_index{0};
    std::unique_ptr<FreeListNode[]> _free_list;

    // Cache line aligned to prevent false sharing between shards
    struct alignas(DEFAULT_CACHE_LINE_SIZE) ShardHead { std::atomic<int> head{-1}; };
    static ShardHead _free_heads[kShardCount];         // one cache-line each

    static inline int shardOf(int tid)  { return tid & (kShardCount - 1); }
    static inline int shardOfSlot(int s){ return s  & (kShardCount - 1); }
    // Helper methods for lock-free operations
    void initializeChunk(int chunk_idx);
    bool pushToFreeList(SlotID slot_id);
    SlotID popFromFreeList();
};

// Snapshot entry produced by ThreadFilter::collect for the wall-clock timer.
struct ThreadEntry {
    int tid;
    const ThreadFilter::Slot* slot;
};

#endif // _THREADFILTER_H
