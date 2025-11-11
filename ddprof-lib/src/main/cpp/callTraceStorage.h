/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACESTORAGE_H
#define _CALLTRACESTORAGE_H

#include "callTraceHashTable.h"
#include "spinLock.h"
#include "os_dd.h"
#include <functional>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <atomic>
#include <thread>
#include <chrono>

// Forward declarations
class CallTraceStorage;
class CallTraceHashTable;

// Liveness checker function type
// Fills the provided set with 64-bit call_trace_id values that should be preserved
// Using reference parameter avoids malloc() for vector creation and copying
typedef std::function<void(std::unordered_set<u64>&)> LivenessChecker;

/**
 * Cache-aligned hazard pointer slot to eliminate false sharing.
 * Each slot occupies a full cache line (64 bytes) to ensure that
 * updates by one thread do not invalidate cache lines for other threads.
 */
struct alignas(DEFAULT_CACHE_LINE_SIZE) HazardSlot {
    volatile CallTraceHashTable* pointer;
    char padding[DEFAULT_CACHE_LINE_SIZE - sizeof(pointer)];

    HazardSlot() : pointer(nullptr), padding{} {
        static_assert(sizeof(HazardSlot) == DEFAULT_CACHE_LINE_SIZE,
                      "HazardSlot must be exactly one cache line");
    }
};

/**
 * RAII guard for hazard pointer management.
 *
 * This class encapsulates the hazard pointer mechanism used to protect CallTraceHashTable
 * instances from being deleted while they are being accessed by concurrent threads.
 *
 * Usage:
 *   HazardPointer guard(_active_table);
 *   // _active_table is now protected from deletion
 *   // Automatic cleanup when guard goes out of scope
 */
class HazardPointer {
public:
    static constexpr int MAX_THREADS = 8192;
    static constexpr int MAX_PROBE_DISTANCE = 32;  // Maximum probing attempts
    static constexpr int BITMAP_WORDS = MAX_THREADS / 64;  // 8192 / 64 = 128 words

    static HazardSlot global_hazard_list[MAX_THREADS];
    static int slot_owners[MAX_THREADS];  // Thread ID ownership verification

    // Occupied slot bitmap for efficient scanning (avoids iterating 8192 empty slots)
    // Uses raw uint64_t with GCC atomic builtins to avoid any potential malloc on musl
    // Each bit represents whether the corresponding slot is occupied
    static uint64_t occupied_bitmap[BITMAP_WORDS];

private:
    bool _active;
    int _my_slot;  // This instance's assigned slot

    // Signal-safe slot assignment using thread ID hash
    static int getThreadHazardSlot();
    
public:
    HazardPointer(CallTraceHashTable* resource);
    ~HazardPointer();
    
    // Non-copyable, movable for efficiency
    HazardPointer(const HazardPointer&) = delete;
    HazardPointer& operator=(const HazardPointer&) = delete;
    
    HazardPointer(HazardPointer&& other) noexcept;
    HazardPointer& operator=(HazardPointer&& other) noexcept;
    
    // Check if hazard pointer is active (slot allocation succeeded)
    bool isActive() const { return _active; }
    
    // Wait for hazard pointers pointing to specific table to clear (used during shutdown)
    static void waitForHazardPointersToClear(CallTraceHashTable* table_to_delete);
    
    // Wait for ALL hazard pointers to clear (used by CallTraceHashTable::clear())
    static void waitForAllHazardPointersToClear();
};

class CallTraceStorage {
public:
    // Reserved trace ID for dropped samples due to contention
    // Real trace IDs are generated as (instance_id << 32) | slot, where instance_id starts from 1
    // Any ID with 0 in upper 32 bits is guaranteed to not clash with real trace IDs
    static const u64 DROPPED_TRACE_ID = 1ULL;
    
    // Static dropped trace object that appears in JFR constant pool
    static CallTrace* getDroppedTrace();

private:
    // Triple-buffered storage with atomic pointers  
    // Rotation: tmp=scratch, scratch=active, active=standby, standby=tmp
    // New active inherits preserved traces for continuity
    volatile CallTraceHashTable* _active_storage;
    volatile CallTraceHashTable* _standby_storage;
    volatile CallTraceHashTable* _scratch_storage;
    
    // Generation counter for ABA protection during table swaps
    u32 _generation_counter;
    
    // Liveness checkers - protected by simple spinlock during registration/clear
    // Using vector instead of unordered_set since std::function cannot be hashed
    std::vector<LivenessChecker> _liveness_checkers;
    SpinLock _liveness_lock;  // Simple atomic lock for rare liveness operations
    
    // Static atomic for instance ID generation - avoids function-local static initialization issues
    
    static u64 _next_instance_id;
    
    // Lazy initialization helper to avoid global constructor
    static u64 getNextInstanceId();
    
    // Pre-allocated collections for processTraces (single-threaded operation)
    // These collections are reused to eliminate malloc/free cycles
    std::unordered_set<CallTrace*> _traces_buffer;           // All traces for JFR processing
    std::unordered_set<u64> _preserve_set_buffer;           // Preserve set for current cycle
    
    
private:

    


public:
    CallTraceStorage();
    ~CallTraceStorage();

    // Register a liveness checker (rare operation - uses simple lock)
    void registerLivenessChecker(LivenessChecker checker);

    // Clear liveness checkers (rare operation - uses simple lock)
    void clearLivenessCheckers();

    // Lock-free put operation for signal handler safety
    // Uses hazard pointers and generation counter for ABA protection
    u64 put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight);
    
    // Lock-free trace processing with hazard pointer protection
    // The callback receives traces that are guaranteed to be valid during execution
    // Uses atomic table swapping with grace period for safe memory reclamation
    void processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor);

    // Enhanced clear with liveness preservation (rarely called - uses atomic operations)
    void clear();
};

#endif // _CALLTRACESTORAGE_H