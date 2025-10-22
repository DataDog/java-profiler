/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACESTORAGE_H
#define _CALLTRACESTORAGE_H

#include "callTraceHashTable.h"
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
 * RAII guard for hazard pointer management.
 * 
 * This class encapsulates the hazard pointer mechanism used to protect CallTraceHashTable
 * instances from being deleted while they are being accessed by concurrent threads.
 *
 * Usage:
 *   HazardPointer guard(active_table);
 *   // active_table is now protected from deletion
 *   // Automatic cleanup when guard goes out of scope
 */
class HazardPointer {
public:
    static constexpr int MAX_THREADS = 256;
    static std::atomic<CallTraceHashTable*> global_hazard_list[MAX_THREADS];

private:
    bool active_;
    int my_slot_;  // This instance's assigned slot
    
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
    
    // Wait for specific hazard pointers to clear (used during shutdown)
    static void waitForAllHazardPointersToClear(CallTraceHashTable* table_to_delete);
    
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
    std::atomic<CallTraceHashTable*> _active_storage;
    std::atomic<CallTraceHashTable*> _standby_storage;
    std::atomic<CallTraceHashTable*> _scratch_storage;
    
    // Generation counter for ABA protection during table swaps
    std::atomic<u32> _generation_counter;
    
    // Liveness checkers - protected by simple spinlock during registration/clear
    // Using vector instead of unordered_set since std::function cannot be hashed
    std::vector<LivenessChecker> _liveness_checkers;
    volatile int _liveness_lock;  // Simple atomic lock for rare liveness operations
    
    // Static atomic for instance ID generation - avoids function-local static initialization issues
    static std::atomic<u64> _next_instance_id;
    
    // Lazy initialization helper to avoid global constructor
    static u64 getNextInstanceId();
    
    // Pre-allocated collections for processTraces (single-threaded operation)
    // These collections are reused to eliminate malloc/free cycles
    std::unordered_set<CallTrace*> _traces_buffer;           // Combined traces for JFR processing
    std::unordered_set<CallTrace*> _traces_to_preserve_buffer; // Traces selected for preservation
    std::unordered_set<CallTrace*> _standby_traces_buffer;   // Traces collected from standby
    std::unordered_set<CallTrace*> _active_traces_buffer;    // Traces collected from active/scratch
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
    
    
private:
    // Simple spinlock helpers for rare liveness operations
    void lockLivenessCheckers();
    void unlockLivenessCheckers();
};

#endif // _CALLTRACESTORAGE_H