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
 * Cache-aligned reference counting slot for thread-local reference counting.
 * Each slot occupies a full cache line (64 bytes) to eliminate false sharing.
 *
 * CORRECTNESS: The pointer-first protocol ensures race-free operation:
 * - Constructor: Store pointer first, then increment count
 * - Destructor: Decrement count first, then clear pointer
 * - Scanner: Check count first (if 0, slot is inactive)
 *
 * This ordering ensures no window where scanner incorrectly believes a slot
 * is inactive when it should be protecting a table.
 */
struct alignas(DEFAULT_CACHE_LINE_SIZE) RefCountSlot {
    volatile uint32_t count;          // Reference count (0 = inactive)
    char _padding1[4];                // Alignment padding for pointer
    CallTraceHashTable* active_table; // Which table is being referenced (8 bytes on 64-bit)
    char padding[DEFAULT_CACHE_LINE_SIZE - 16];  // Remaining padding (64 - 16 = 48 bytes)

    RefCountSlot() : count(0), _padding1{}, active_table(nullptr), padding{} {
        static_assert(sizeof(RefCountSlot) == DEFAULT_CACHE_LINE_SIZE,
                      "RefCountSlot must be exactly one cache line");
    }
};

/**
 * RAII guard for thread-local reference counting.
 *
 * This class provides lock-free memory reclamation for CallTraceHashTable instances.
 * Uses the pointer-first protocol to avoid race conditions during slot activation/deactivation.
 *
 * Performance characteristics:
 * - Hot path: ~44-94 cycles
 * - Thread-local cache line access (zero contention)
 * - No bitmap operations required
 *
 * Correctness:
 * - Pointer stored BEFORE count increment (activation)
 * - Count decremented BEFORE pointer cleared (deactivation)
 * - Scanner checks count first, ensuring consistent view
 */
class RefCountGuard {
public:
    static constexpr int MAX_THREADS = 8192;
    static constexpr int MAX_PROBE_DISTANCE = 32;  // Maximum probing attempts

    static RefCountSlot refcount_slots[MAX_THREADS];
    static int slot_owners[MAX_THREADS];  // Thread ID ownership verification

private:
    bool _active;
    int _my_slot;  // This instance's assigned slot

    // Signal-safe slot assignment using thread ID hash with prime probing
    static int getThreadRefCountSlot();

public:
    RefCountGuard(CallTraceHashTable* resource);
    ~RefCountGuard();

    // Non-copyable, movable for efficiency
    RefCountGuard(const RefCountGuard&) = delete;
    RefCountGuard& operator=(const RefCountGuard&) = delete;

    RefCountGuard(RefCountGuard&& other) noexcept;
    RefCountGuard& operator=(RefCountGuard&& other) noexcept;

    // Check if refcount guard is active (slot allocation succeeded)
    bool isActive() const { return _active; }

    // Wait for reference counts pointing to specific table to clear
    static void waitForRefCountToClear(CallTraceHashTable* table_to_delete);

    // Wait for ALL reference counts to clear
    static void waitForAllRefCountsToClear();
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
    // Uses RefCountGuard and generation counter for ABA protection
    u64 put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight);
    
    // Lock-free trace processing with RefCountGuard protection
    // The callback receives traces that are guaranteed to be valid during execution
    // Uses atomic table swapping with grace period for safe memory reclamation
    void processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor);

    // Enhanced clear with liveness preservation (rarely called - uses atomic operations)
    void clear();
};

#endif // _CALLTRACESTORAGE_H