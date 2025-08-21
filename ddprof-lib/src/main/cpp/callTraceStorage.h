/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CALLTRACESTORAGE_H
#define _CALLTRACESTORAGE_H

#include "callTraceHashTable.h"
#include "spinLock.h"
#include <functional>
#include <vector>
#include <memory>
#include <unordered_set>
#include <atomic>

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
    std::unique_ptr<CallTraceHashTable> _active_storage;
    std::unique_ptr<CallTraceHashTable> _standby_storage;
    std::vector<LivenessChecker> _liveness_checkers;
    SpinLock _lock;
    
    // Static atomic for instance ID generation - avoids function-local static initialization issues
    static std::atomic<u64> _next_instance_id;
    
    // Lazy initialization helper to avoid global constructor
    static u64 getNextInstanceId();
    
    // Pre-allocated containers to avoid malloc() during hot path operations
    mutable std::vector<u64> _preserve_buffer;        // Reusable buffer for 64-bit trace IDs
    mutable std::unordered_set<u64> _preserve_set;    // Pre-sized hash set for 64-bit trace ID lookups
    


public:
    CallTraceStorage();
    ~CallTraceStorage();

    // Register a liveness checker
    void registerLivenessChecker(LivenessChecker checker);

    // Clear liveness checkers
    void clearLivenessCheckers();

    // Forward methods to active storage
    u64 put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight);
    
    // Safe trace processing with guaranteed lifetime during callback execution
    // The callback receives a const reference to traces that are guaranteed to be valid
    // during the entire callback execution. Cleanup happens automatically after callback returns.
    void processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor);

    // Enhanced clear with liveness preservation
    void clear();
};

#endif // _CALLTRACESTORAGE_H