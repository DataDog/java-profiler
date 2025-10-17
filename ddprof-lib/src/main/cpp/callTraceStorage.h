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
#include <atomic>
#include <thread>
#include <chrono>

// Forward declaration
class CallTraceStorage;

// Liveness checker function type
// Fills the provided vector with 64-bit call_trace_id values that should be preserved
// Using reference parameter avoids malloc() for vector creation and copying
typedef std::function<void(std::vector<u64>&)> LivenessChecker;

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
    std::vector<LivenessChecker> _liveness_checkers;
    volatile int _liveness_lock;  // Simple atomic lock for rare liveness operations
    
    // Static atomic for instance ID generation - avoids function-local static initialization issues
    static std::atomic<u64> _next_instance_id;
    
    // Lazy initialization helper to avoid global constructor
    static u64 getNextInstanceId();
    
    // Pre-allocated containers to avoid malloc() during hot path operations
    mutable std::vector<u64> _preserve_buffer;        // Reusable buffer for 64-bit trace IDs
    mutable std::unordered_set<u64> _preserve_set;    // Pre-sized hash set for 64-bit trace ID lookups
    
    // Per-instance hazard pointer system for safe memory reclamation
    static constexpr int MAX_THREADS = 256;  // Maximum supported threads
    std::atomic<CallTraceHashTable*> _hazard_list[MAX_THREADS];  // Per-instance hazard list
    std::atomic<int> _thread_counter;  // Per-instance thread counter for slot assignment
    
    // Thread-local storage for hazard pointer management - now uses instance pointer
    struct ThreadHazardInfo {
        CallTraceHashTable* hazard_pointer;
        int hazard_slot;
        CallTraceStorage* storage_instance;  // Which storage instance owns this hazard pointer
    };
    static thread_local ThreadHazardInfo _thread_hazard_info;
    
    // Hazard pointer management - now instance-specific
    void registerHazardPointer(CallTraceHashTable* table);
    void clearHazardPointer();
    void waitForHazardPointersToClear(CallTraceHashTable* table_to_delete);
    int getThreadHazardSlot();
    


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