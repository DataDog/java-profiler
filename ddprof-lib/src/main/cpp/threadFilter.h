/*
 * Copyright 2025 Datadog, Inc
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

    SlotID registerThread();
    void unregisterThread(SlotID slot_id);

private:
    // Optimized slot structure with padding to avoid false sharing
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        std::atomic<int> value{-1};
        char padding[DEFAULT_CACHE_LINE_SIZE - sizeof(value)];  // Pad to cache line size
    };
    static_assert(sizeof(Slot) == DEFAULT_CACHE_LINE_SIZE, "Slot must be exactly one cache line");

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

#endif // _THREADFILTER_H
