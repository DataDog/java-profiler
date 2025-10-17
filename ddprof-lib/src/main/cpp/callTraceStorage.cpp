/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceStorage.h"
#include "counters.h"
#include "os_dd.h"
#include "common.h"
#include "vmEntry.h" // For BCI_ERROR constant
#include "arch_dd.h" // For LP64_ONLY macro and COMMA macro
#include "criticalSection.h" // For table swap critical sections
#include <string.h>
#include <atomic>

static const u64 OVERFLOW_TRACE_ID = 0x7fffffffffffffffULL;  // Max 64-bit signed value

// Static atomic for instance ID generation - explicit initialization avoids function-local static issues
std::atomic<u64> CallTraceStorage::_next_instance_id{1};  // Start from 1, 0 is reserved

// Thread-local hazard pointer info - now tracks which storage instance owns the hazard pointer
thread_local CallTraceStorage::ThreadHazardInfo CallTraceStorage::_thread_hazard_info = {nullptr, -1, nullptr};

// Lazy initialization helper to avoid global constructor race conditions
u64 CallTraceStorage::getNextInstanceId() {
    u64 instance_id = _next_instance_id.fetch_add(1, std::memory_order_acq_rel);
    return instance_id;
}

CallTraceStorage::CallTraceStorage() : _generation_counter(1), _liveness_lock(0), _thread_counter(0) {
    // Initialize per-instance hazard pointer list
    for (int i = 0; i < MAX_THREADS; ++i) {
        _hazard_list[i].store(nullptr, std::memory_order_relaxed);
    }
    
    // Initialize triple-buffered storage
    auto active_table = std::make_unique<CallTraceHashTable>();
    u64 initial_instance_id = getNextInstanceId();
    active_table->setInstanceId(initial_instance_id);
    _active_storage.store(active_table.release(), std::memory_order_release);

    auto standby_table = std::make_unique<CallTraceHashTable>();
    // Standby will get its instance ID during swap
    _standby_storage.store(standby_table.release(), std::memory_order_release);
    
    auto cleanup_table = std::make_unique<CallTraceHashTable>();
    // Cleanup table will get instance ID when it rotates to standby
    _cleanup_storage.store(cleanup_table.release(), std::memory_order_release);

    // Pre-allocate containers to avoid malloc() during hot path operations
    _liveness_checkers.reserve(4);      // Typical max: 1-2 checkers, avoid growth
    _preserve_buffer.reserve(1024);     // Reserve for typical liveness workloads
    _preserve_set.reserve(1024);        // Pre-size hash buckets for lookups

    // Initialize counters
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);
}

CallTraceStorage::~CallTraceStorage() {
    // Atomically invalidate storage pointers to prevent new put() operations
    CallTraceHashTable* active = _active_storage.exchange(nullptr, std::memory_order_acq_rel);
    CallTraceHashTable* standby = _standby_storage.exchange(nullptr, std::memory_order_acq_rel);
    CallTraceHashTable* cleanup = _cleanup_storage.exchange(nullptr, std::memory_order_acq_rel);

    // Use the original per-table waiting approach but with duplicate detection
    // Wait for any ongoing hazard pointer usage to complete and delete each unique table
    // Note: In triple-buffering, all three pointers should be unique, but check anyway
    if (active) {
        waitForHazardPointersToClear(active);
        delete active;
    }
    if (standby && standby != active) {
        waitForHazardPointersToClear(standby);
        delete standby;
    }
    if (cleanup && cleanup != active && cleanup != standby) {
        waitForHazardPointersToClear(cleanup);
        delete cleanup;
    }
}

CallTrace* CallTraceStorage::getDroppedTrace() {
    // Static dropped trace object - created once and reused
    // Use same pattern as storage_overflow trace for consistent platform handling
    static CallTrace dropped_trace = {false, 1, DROPPED_TRACE_ID, {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"<dropped>"}};

    return &dropped_trace;
}

// Per-instance hazard pointer system implementation
int CallTraceStorage::getThreadHazardSlot() {
    // Check if current thread already has a hazard slot for this storage instance
    if (_thread_hazard_info.storage_instance != this || _thread_hazard_info.hazard_slot == -1) {
        // Allocate new slot for this storage instance
        _thread_hazard_info.hazard_slot = _thread_counter.fetch_add(1, std::memory_order_relaxed) % MAX_THREADS;
        _thread_hazard_info.storage_instance = this;
    }
    return _thread_hazard_info.hazard_slot;
}

void CallTraceStorage::registerHazardPointer(CallTraceHashTable* table) {
    int slot = getThreadHazardSlot();
    
    // Update thread-local info for this storage instance
    _thread_hazard_info.hazard_pointer = table;
    _thread_hazard_info.storage_instance = this;
    
    // Update this storage instance's hazard list
    _hazard_list[slot].store(table, std::memory_order_release);
    
    // Memory barrier to ensure hazard pointer is visible before any table access
    std::atomic_thread_fence(std::memory_order_seq_cst);
}

void CallTraceStorage::clearHazardPointer() {
    // Only clear if this thread's hazard pointer belongs to this storage instance
    if (_thread_hazard_info.storage_instance == this) {
        int slot = _thread_hazard_info.hazard_slot;
        
        // Clear thread-local info for this storage instance
        _thread_hazard_info.hazard_pointer = nullptr;
        _hazard_list[slot].store(nullptr, std::memory_order_release);
    }
}

void CallTraceStorage::waitForHazardPointersToClear(CallTraceHashTable* table_to_delete) {
    // Check only this storage instance's hazard pointers
    const int MAX_WAIT_ITERATIONS = 5000;
    int wait_count = 0;
    
    while (wait_count < MAX_WAIT_ITERATIONS) {
        bool any_hazards = false;
        
        // Check this storage instance's hazard pointers
        for (int i = 0; i < MAX_THREADS; ++i) {
            CallTraceHashTable* current_hazard = _hazard_list[i].load(std::memory_order_acquire);
            if (current_hazard == table_to_delete) {
                any_hazards = true;
                break;
            }
        }
        
        if (!any_hazards) {
            break;
        }
        
        // Brief pause
        struct timespec ts = {0, 10000};  // 10 microseconds
        nanosleep(&ts, nullptr);
        wait_count++;
    }
}

// Simple spinlock helpers for rare liveness operations
void CallTraceStorage::lockLivenessCheckers() {
    while (__sync_bool_compare_and_swap(&_liveness_lock, 0, 1) == false) {
        // Busy wait - these operations are rare
    }
}

void CallTraceStorage::unlockLivenessCheckers() {
    __sync_bool_compare_and_swap(&_liveness_lock, 1, 0);
}

void CallTraceStorage::registerLivenessChecker(LivenessChecker checker) {
    lockLivenessCheckers();
    _liveness_checkers.push_back(checker);
    unlockLivenessCheckers();
}

void CallTraceStorage::clearLivenessCheckers() {
    lockLivenessCheckers();
    _liveness_checkers.clear();
    unlockLivenessCheckers();
}

u64 CallTraceStorage::put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight) {
    // Signal handlers can run concurrently with destructor
    CallTraceHashTable* active = _active_storage.load(std::memory_order_acquire);
    
    // Safety check - if null, system is shutting down
    if (active == nullptr) {
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Register hazard pointer to prevent deletion during table access
    registerHazardPointer(active);
    
    // Check again after registering hazard pointer - storage might have been nullified
    CallTraceHashTable* current_active = _active_storage.load(std::memory_order_acquire);
    if (current_active != active || current_active == nullptr) {
        // Storage was swapped or nullified, clear hazard pointer and return dropped
        clearHazardPointer();
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Hazard pointer prevents deletion
    u64 result = active->put(num_frames, frames, truncated, weight);
    
    // Clear hazard pointer
    clearHazardPointer();
    
    return result;
}

/*
 * Trace processing with signal blocking for simplified concurrency.
 * This function is safe to call concurrently with put() operations, but should not be 
 * called concurrently with itself (FlightRecorder ensures this with recording lock).
 */
void CallTraceStorage::processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor) {
    // Keep critical section for table swap operations
    CriticalSection cs;
    std::unordered_set<u64> preserve_set;

    // PHASE 1: Collect liveness information with simple lock (rare operation)
    {
        lockLivenessCheckers();
        
        // Use pre-allocated containers to avoid malloc()
        _preserve_buffer.clear();
        _preserve_set.clear();

        for (const auto& checker : _liveness_checkers) {
            checker(_preserve_buffer);
        }

        _preserve_set.insert(_preserve_buffer.begin(), _preserve_buffer.end());
        preserve_set = _preserve_set;
        
        unlockLivenessCheckers();
    }

    // PHASE 2: Atomic swap - old active becomes read-only after swap
    
    CallTraceHashTable* current_active = _active_storage.load(std::memory_order_acquire);
    CallTraceHashTable* current_standby = _standby_storage.load(std::memory_order_acquire);
    CallTraceHashTable* current_cleanup = _cleanup_storage.load(std::memory_order_acquire);
    
    std::unordered_set<CallTrace*> traces;
    std::unordered_set<CallTrace*> traces_to_preserve;

    // Step 1: Triple-buffer rotation: tmp=cleanup, cleanup=active, active=standby, standby=tmp
    CallTraceHashTable* tmp = current_cleanup;
    
    // Step 2: Prepare standby (with preserved traces) to become new active
    u64 new_instance_id = getNextInstanceId();
    current_standby->setInstanceId(new_instance_id);
    
    // Step 3: ATOMIC SWAP - standby (with preserved traces) becomes new active
    CallTraceHashTable* old_active = _active_storage.exchange(current_standby, std::memory_order_acq_rel);
    
    // Step 4: Complete the rotation
    _cleanup_storage.store(old_active, std::memory_order_release);    // old active becomes cleanup
    _standby_storage.store(tmp, std::memory_order_release);           // old cleanup becomes new standby
    
    // Step 5: Collect traces from old active (now in cleanup)
    std::unordered_set<CallTrace*> active_traces;
    old_active->collectLockFree(active_traces);
    
    // Step 6: Collect from new standby (old cleanup)
    std::unordered_set<CallTrace*> cleanup_traces;
    tmp->collectLockFree(cleanup_traces);
    
    // Combine all traces for JFR processing
    traces.insert(active_traces.begin(), active_traces.end());
    traces.insert(cleanup_traces.begin(), cleanup_traces.end());

    // Always include dropped trace in JFR constant pool
    traces.insert(getDroppedTrace());

    // PHASE 3: Identify traces that need to be preserved from active traces only
    for (CallTrace* trace : active_traces) {
        if (preserve_set.find(trace->trace_id) != preserve_set.end()) {
            traces_to_preserve.insert(trace);
        }
    }

    // PHASE 4: Process traces
    processor(traces);

    // PHASE 5: Copy preserved traces to new standby
    CallTraceHashTable* preserve_standby = _standby_storage.load(std::memory_order_acquire);
    preserve_standby->clear();
    for (CallTrace* trace : traces_to_preserve) {
        preserve_standby->putWithExistingIdLockFree(trace, 1);  // New lock-free method
    }
    
    // PHASE 6: Clear cleanup storage
    old_active->clear();
    
    // Triple-buffer rotation maintains trace continuity:
    // - New active contains previously preserved traces
    // - Signal handlers write to new active with preserved traces  
    // - Old active (now cleanup) is safely collected and cleared
    // - New standby (old cleanup) receives newly preserved traces
}



void CallTraceStorage::clear() {
    // Mark critical section during clear operation for consistency
    CriticalSection cs;
    
    // Load current table pointers - simple operation with critical section protection
    CallTraceHashTable* active = _active_storage.load(std::memory_order_relaxed);
    CallTraceHashTable* standby = _standby_storage.load(std::memory_order_relaxed);
    
    // Direct clear operations with critical section protection
    if (active) {
        active->clear();
    }
    if (standby) {
        standby->clear();
    }

    // Reset counters when clearing all storage
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);
}

