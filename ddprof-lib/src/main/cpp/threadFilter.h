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
#include "threadState.h"

class VMThread;
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

    // Optimized slot structure with padding to avoid false sharing.
    // The pointer is placed before the int field to avoid implicit alignment padding between them.
    //
    // Lifetime: Slot instances live inside ChunkStorage arrays that are allocated on first
    // use and never freed for the JVM-process lifetime. A captured `Slot*` is therefore
    // dereferenceable for the rest of the process, regardless of whether the thread that
    // currently owns the slot has exited. This is the lifetime guarantee the wall-clock
    // timer relies on for its once-per-run fast-path (sampledThisRun/lastSampledState are
    // read cross-thread).
    struct alignas(DEFAULT_CACHE_LINE_SIZE) Slot {
        std::atomic<VMThread*> vm_thread{nullptr};               // 8 bytes
        std::atomic<int>       value{-1};                        // 4 bytes
        // Wall-clock once-per-run filter state (wallprecheck=true). Written by the
        // SIGVTALRM handler on the slot's owning thread; read by both the handler and
        // the wall-clock timer thread. Reset on slot reuse via resetSampledRun() in
        // resetSlotRunState() when a new thread is associated with the slot.
        //
        // Memory ordering: the flag uses release/acquire so a reader that observes
        // sampledThisRun()==true is guaranteed to also observe the lastSampledState
        // value that was stored immediately before the flag was set. The state itself
        // can use relaxed loads because the && in the reader short-circuits on the
        // acquire-load of the flag, fencing any subsequent state read.
        std::atomic<OSThreadState> last_sampled_state{OSThreadState::UNKNOWN};  // 4 bytes
        std::atomic<bool>          sampled_this_run{false};                     // 1 byte
        char padding[DEFAULT_CACHE_LINE_SIZE
                     - sizeof(std::atomic<VMThread*>)
                     - sizeof(std::atomic<int>)
                     - sizeof(std::atomic<OSThreadState>)
                     - sizeof(std::atomic<bool>)];

        inline bool sampledThisRun() const {
            return sampled_this_run.load(std::memory_order_acquire);
        }
        inline OSThreadState lastSampledState() const {
            return last_sampled_state.load(std::memory_order_relaxed);
        }
        // Order matters: store the state under relaxed first, then publish the flag
        // with release. Readers do the inverse: acquire on the flag, then relaxed
        // read on the state. This pairing makes the "state-paired-with-flag"
        // invariant portable across weakly-ordered architectures (ARM64, POWER, etc.),
        // not just TSO. Stale reads on a flag observed as false fall through to
        // the unfenced authoritative check in the signal handler.
        inline void markSampledThisRun(OSThreadState state) {
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(true, std::memory_order_release);
        }
        inline void resetSampledRun(OSThreadState state) {
            last_sampled_state.store(state, std::memory_order_relaxed);
            sampled_this_run.store(false, std::memory_order_release);
        }
    };
    static_assert(sizeof(Slot) == DEFAULT_CACHE_LINE_SIZE, "Slot must be exactly one cache line");
    static_assert(std::atomic<OSThreadState>::is_always_lock_free,
                  "Slot::last_sampled_state must be lock-free for signal-handler safety");
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
    void setVMThread(SlotID slot_id, VMThread* vm_thread);
    // Resets the once-per-run wall-clock filter state for a slot on thread reuse.
    // Call when a new thread takes ownership of a slot so it does not inherit stale
    // suppression state from the previous occupant.
    void resetSlotRunState(SlotID slot_id);
    void collectWithState(std::vector<ThreadEntry>& entries) const;

    // Returns the (process-lifetime) Slot pointer for a registered slot_id, or nullptr
    // if slot_id is invalid or its chunk has not been allocated. Safe to call from the
    // signal handler and the wall-clock timer thread.
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

// Snapshot captured by ThreadFilter::collectWithState. The `slot` pointer is JVM-process
// stable (see Slot lifetime comment above) and is the safe channel for the wall-clock
// timer to read once-per-run filter state cross-thread.
// NOTE: ProfiledThread* is intentionally omitted — its lifetime ends at
// ProfiledThread::release() and is not safe to dereference from the timer thread.
// Re-add only when a concrete consumer with a defined lifetime contract is introduced.
struct ThreadEntry {
    int tid;
    VMThread* vm_thread;
    const ThreadFilter::Slot* slot;
};

#endif // _THREADFILTER_H
