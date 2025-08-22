/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceStorage.h"
#include "counters.h"
#include "common.h"
#include "vmEntry.h" // For BCI_ERROR constant
#include "arch_dd.h" // For LP64_ONLY macro and COMMA macro
#include <string.h>
#include <atomic>

static const u64 OVERFLOW_TRACE_ID = 0x7fffffffffffffffULL;  // Max 64-bit signed value

// Static atomic for instance ID generation - explicit initialization avoids function-local static issues
std::atomic<u64> CallTraceStorage::_next_instance_id{1};  // Start from 1, 0 is reserved

// Lazy initialization helper to avoid global constructor race conditions
u64 CallTraceStorage::getNextInstanceId() {
    u64 instance_id = _next_instance_id.fetch_add(1, std::memory_order_relaxed);
    return instance_id;
}

CallTraceStorage::CallTraceStorage() : _lock(0) {
    // Initialize active storage with its instance ID
    _active_storage = std::make_unique<CallTraceHashTable>();
    u64 initial_instance_id = getNextInstanceId();
    _active_storage->setInstanceId(initial_instance_id);
    
    _standby_storage = std::make_unique<CallTraceHashTable>();
    // Standby will get its instance ID during swap

    // Pre-allocate containers to avoid malloc() during hot path operations
    _liveness_checkers.reserve(4);      // Typical max: 1-2 checkers, avoid growth
    _preserve_buffer.reserve(1024);     // Reserve for typical liveness workloads
    _preserve_set.reserve(1024);        // Pre-size hash buckets for lookups

    // Initialize counters
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);
}

CallTraceStorage::~CallTraceStorage() {
    TEST_LOG("CallTraceStorage::~CallTraceStorage() - shutting down, invalidating active storage to prevent use-after-destruction");
    
    // Take exclusive lock to ensure no ongoing put() operations
    _lock.lock();
    
    // Invalidate active storage first to prevent use-after-destruction
    // Any subsequent put() calls will see nullptr and return DROPPED_TRACE_ID safely
    _active_storage = nullptr;
    _standby_storage = nullptr;
    
    _lock.unlock();
    
    TEST_LOG("CallTraceStorage::~CallTraceStorage() - destruction complete");
    // Unique pointers will automatically clean up the actual objects
}

CallTrace* CallTraceStorage::getDroppedTrace() {
    // Static dropped trace object - created once and reused
    // Use same pattern as storage_overflow trace for consistent platform handling
    static CallTrace dropped_trace = {false, 1, DROPPED_TRACE_ID, {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"<dropped>"}};
    
    return &dropped_trace;
}

void CallTraceStorage::registerLivenessChecker(LivenessChecker checker) {
    _lock.lock();
    _liveness_checkers.push_back(checker);
    _lock.unlock();
}

void CallTraceStorage::clearLivenessCheckers() {
    _lock.lock();
    _liveness_checkers.clear();
    _lock.unlock();
}

u64 CallTraceStorage::put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight) {
    // Use shared lock - multiple put operations can run concurrently since each trace 
    // goes to a different slot based on its hash. Only blocked by exclusive operations like collectTraces() or clear().
    if (!_lock.tryLockShared()) {
        // Exclusive operation (collectTraces or clear) in progress - return special dropped trace ID
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Safety check: if active storage is invalid (e.g., during destruction), drop the sample
    if (_active_storage == nullptr) {
        TEST_LOG("CallTraceStorage::put() - _active_storage is NULL (shutdown/destruction?), returning DROPPED_TRACE_ID");
        _lock.unlockShared();
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Forward to active storage
    u64 result = _active_storage->put(num_frames, frames, truncated, weight);
    
    _lock.unlockShared();
    return result;
}

void CallTraceStorage::processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor) {
    // Split lock strategy: minimize time under exclusive lock by separating swap from processing
    std::unordered_set<u64> preserve_set;
    
    // PHASE 1: Brief exclusive lock for liveness collection and storage swap
    {
        _lock.lock();
        
        // Step 1: Collect all call_trace_id values that need to be preserved
        // Use pre-allocated containers to avoid malloc() in hot path
        _preserve_buffer.clear();      // No deallocation - keeps reserved capacity
        _preserve_set.clear();         // No bucket deallocation - keeps reserved buckets

        for (const auto& checker : _liveness_checkers) {
            checker(_preserve_buffer); // Fill buffer by reference - no malloc()
        }

        // Copy preserve set for use outside lock - bulk insert into set
        _preserve_set.insert(_preserve_buffer.begin(), _preserve_buffer.end());
        preserve_set = _preserve_set; // Copy the set for lock-free processing
        
        // Step 2: Assign new instance ID to standby storage to avoid trace ID clashes
        u64 new_instance_id = getNextInstanceId();
        _standby_storage->setInstanceId(new_instance_id);
        
        // Step 3: Swap storage atomically - standby (with new instance ID) becomes active
        // Old active becomes standby and will be processed lock-free
        _active_storage.swap(_standby_storage);
        
        _lock.unlock();
        // END PHASE 1 - Lock released, put() operations can now proceed concurrently
    }
    
    // PHASE 2: Lock-free processing - iterate owned storage and collect traces
    std::unordered_set<CallTrace*> traces;
    std::unordered_set<CallTrace*> traces_to_preserve;
    
    // Collect all traces and identify which ones to preserve (no lock held)
    _standby_storage->collect(traces);  // Get all traces from standby (old active) for JFR processing
    
    // Always ensure the dropped trace is included in JFR constant pool
    // This guarantees that events with DROPPED_TRACE_ID have a valid stack trace entry
    traces.insert(getDroppedTrace());
    
    // Identify traces that need to be preserved based on their IDs
    for (CallTrace* trace : traces) {
        if (preserve_set.find(trace->trace_id) != preserve_set.end()) {
            traces_to_preserve.insert(trace);
        }
    }
    
    // Process traces while they're still valid in standby storage (no lock held)
    // The callback is guaranteed that all traces remain valid during execution
    processor(traces);
    
    // PHASE 3: Brief exclusive lock to copy preserved traces back to active storage and clear standby
    {
        _lock.lock();
        
        // Copy preserved traces to current active storage, maintaining their original trace IDs
        for (CallTrace* trace : traces_to_preserve) {
            _active_storage->putWithExistingId(trace, 1);
        }
        
        // Clear standby storage (old active) now that we're done processing
        // This keeps the hash table structure but clears all data
        _standby_storage->clear();
        
        _lock.unlock();
        // END PHASE 3 - All preserved traces copied back to active storage, standby cleared for reuse
    }
}



void CallTraceStorage::clear() {
    // This is called from profiler start/dump - clear both storages
    _lock.lock();

    _active_storage->clear();
    _standby_storage->clear();

    // Reset counters when clearing all storage
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);

    _lock.unlock();
}

