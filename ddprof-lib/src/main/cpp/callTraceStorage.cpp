/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceStorage.h"
#include "counters.h"
#include "os_dd.h"
#include "common.h"
#include "thread.h"
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
    
    // Pre-allocate and pre-size collections with conservative load factor
    _traces_buffer.max_load_factor(0.75f);
    _traces_buffer.rehash(static_cast<size_t>(2048 / 0.75f));
    
    _traces_to_preserve_buffer.max_load_factor(0.75f);
    _traces_to_preserve_buffer.rehash(static_cast<size_t>(512 / 0.75f));
    
    _standby_traces_buffer.max_load_factor(0.75f);
    _standby_traces_buffer.rehash(static_cast<size_t>(512 / 0.75f));
    
    _active_traces_buffer.max_load_factor(0.75f);
    _active_traces_buffer.rehash(static_cast<size_t>(2048 / 0.75f));
    
    _preserve_set_buffer.max_load_factor(0.75f);
    _preserve_set_buffer.rehash(static_cast<size_t>(1024 / 0.75f));
    
    // Initialize triple-buffered storage
    auto active_table = std::make_unique<CallTraceHashTable>();
    u64 initial_instance_id = getNextInstanceId();
    active_table->setInstanceId(initial_instance_id);
    active_table->setParentStorage(this);
    _active_storage.store(active_table.release(), std::memory_order_release);

    auto standby_table = std::make_unique<CallTraceHashTable>();
    standby_table->setParentStorage(this);
    // Standby will get its instance ID during swap
    _standby_storage.store(standby_table.release(), std::memory_order_release);
    
    auto scratch_table = std::make_unique<CallTraceHashTable>();
    scratch_table->setParentStorage(this);
    // scratch table will get instance ID when it rotates to standby
    _scratch_storage.store(scratch_table.release(), std::memory_order_release);

    // Pre-allocate containers to avoid malloc() during hot path operations
    _liveness_checkers.reserve(4);      // Typical max: 1-2 checkers, avoid growth

    // Initialize counters
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);
}

CallTraceStorage::~CallTraceStorage() {
    // Atomically invalidate storage pointers to prevent new put() operations
    CallTraceHashTable* active = _active_storage.exchange(nullptr, std::memory_order_acq_rel);
    CallTraceHashTable* standby = _standby_storage.exchange(nullptr, std::memory_order_acq_rel);
    CallTraceHashTable* scratch = _scratch_storage.exchange(nullptr, std::memory_order_acq_rel);

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
    if (scratch && scratch != active && scratch != standby) {
        waitForHazardPointersToClear(scratch);
        delete scratch;
    }
    
}


CallTrace* CallTraceStorage::getDroppedTrace() {
    // Static dropped trace object - created once and reused
    // Use same pattern as storage_overflow trace for consistent platform handling
    static CallTrace dropped_trace(false, 1, DROPPED_TRACE_ID);
    // Initialize frame data only once
    static bool initialized = false;
    if (!initialized) {
        dropped_trace.frames[0] = {BCI_ERROR, LP64_ONLY(0 COMMA) (jmethodID)"<dropped>"};
        initialized = true;
    }

    return &dropped_trace;
}

// Per-instance hazard pointer system implementation
int CallTraceStorage::getThreadHazardSlot() {
    ProfiledThread* current = ProfiledThread::current();
    if (current != nullptr) {
        // Use ProfiledThread storage (signal-safe)
        if (current->getHazardInstance() != this || current->getHazardSlot() == -1) {
            // Allocate new slot for this storage instance
            int slot = _thread_counter.fetch_add(1, std::memory_order_relaxed) % MAX_THREADS;
            current->setHazardPointer(this, nullptr, slot);
        }
        return current->getHazardSlot();
    } else {
        // Fallback to TLS for stress tests and edge cases
        if (_thread_hazard_info.storage_instance != this || _thread_hazard_info.hazard_slot == -1) {
            // Allocate new slot for this storage instance
            _thread_hazard_info.hazard_slot = _thread_counter.fetch_add(1, std::memory_order_relaxed) % MAX_THREADS;
            _thread_hazard_info.storage_instance = this;
        }
        return _thread_hazard_info.hazard_slot;
    }
}

void CallTraceStorage::registerHazardPointer(CallTraceHashTable* table) {
    int slot = getThreadHazardSlot();
    
    ProfiledThread* current = ProfiledThread::current();
    if (current != nullptr) {
        // Use ProfiledThread storage (signal-safe)
        current->setHazardPointer(this, table, slot);
    } else {
        // Fallback to TLS for stress tests and edge cases
        _thread_hazard_info.hazard_pointer = table;
        _thread_hazard_info.storage_instance = this;
    }
    
    // Update this storage instance's hazard list
    _hazard_list[slot].store(table, std::memory_order_release);
    
    // Memory barrier to ensure hazard pointer is visible before any table access
    std::atomic_thread_fence(std::memory_order_seq_cst);
}

void CallTraceStorage::clearHazardPointer() {
    ProfiledThread* current = ProfiledThread::current();
    if (current != nullptr) {
        // Use ProfiledThread storage (signal-safe)
        if (current->getHazardInstance() == this) {
            int slot = current->getHazardSlot();
            current->setHazardPointer(this, nullptr, slot);
            _hazard_list[slot].store(nullptr, std::memory_order_release);
        }
    } else {
        // Fallback to TLS for stress tests and edge cases
        if (_thread_hazard_info.storage_instance == this) {
            int slot = _thread_hazard_info.hazard_slot;
            
            // Clear thread-local info for this storage instance
            _thread_hazard_info.hazard_pointer = nullptr;
            _hazard_list[slot].store(nullptr, std::memory_order_release);
        }
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

void CallTraceStorage::waitForAllHazardPointersToClear() {
    // Wait for ALL hazard pointers to clear - needed before deallocating chain memory
    // This ensures no signal handler is traversing any hash table chains
    const int MAX_WAIT_ITERATIONS = 5000;
    int wait_count = 0;
    
    while (wait_count < MAX_WAIT_ITERATIONS) {
        bool any_hazards = false;
        
        // Check this storage instance's hazard pointers
        for (int i = 0; i < MAX_THREADS; ++i) {
            CallTraceHashTable* current_hazard = _hazard_list[i].load(std::memory_order_acquire);
            if (current_hazard != nullptr) {
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
 * This function is safe to call concurrently with put() operations.
 * It is not designed to be called concurrently with itself.
 */
void CallTraceStorage::processTraces(std::function<void(const std::unordered_set<CallTrace*>&)> processor) {
    // Critical section for table swap operations - disallow signals to interrupt
    CriticalSection cs;
    

    // PHASE 1: Collect liveness information with simple lock (rare operation)
    {
        lockLivenessCheckers();
        
        // Use pre-allocated containers to avoid malloc()
        _preserve_set_buffer.clear();

        for (const auto& checker : _liveness_checkers) {
            checker(_preserve_set_buffer);
        }
        
        unlockLivenessCheckers();
    }

    // PHASE 2: Safe collection sequence - standby first, then rotate, then scratch
    
    CallTraceHashTable* current_active = _active_storage.load(std::memory_order_acquire);
    CallTraceHashTable* current_standby = _standby_storage.load(std::memory_order_acquire);
    CallTraceHashTable* current_scratch = _scratch_storage.load(std::memory_order_acquire);
    
    // Clear process collections for reuse (no malloc/free)
    _traces_buffer.clear();
    _traces_to_preserve_buffer.clear();
    _standby_traces_buffer.clear();
    _active_traces_buffer.clear();

    // Step 1: Collect from current standby FIRST (preserved traces from previous cycle)
    current_standby->collect(_standby_traces_buffer);
    
    // Immediately preserve standby traces that need to be kept for next cycle
    for (CallTrace* trace : _standby_traces_buffer) {
        if (_preserve_set_buffer.find(trace->trace_id) != _preserve_set_buffer.end()) {
            _traces_to_preserve_buffer.insert(trace);
        }
    }
    
    // Step 2: Clear standby after collection, prepare for rotation
    current_standby->clear();
    u64 new_instance_id = getNextInstanceId();
    current_standby->setInstanceId(new_instance_id);
    
    // Step 3: ATOMIC SWAP - standby (now empty) becomes new active
    CallTraceHashTable* old_active = _active_storage.exchange(current_standby, std::memory_order_acq_rel);
    
    // Step 4: Complete the rotation: active→scratch, scratch→standby
    CallTraceHashTable* old_scratch = _scratch_storage.exchange(old_active, std::memory_order_acq_rel);
    _standby_storage.store(old_scratch, std::memory_order_release);
    
    // Step 5: NOW collect from scratch (old active, now read-only)
    old_active->collect(_active_traces_buffer);
    
    // Preserve traces from old active too
    for (CallTrace* trace : _active_traces_buffer) {
        if (_preserve_set_buffer.find(trace->trace_id) != _preserve_set_buffer.end()) {
            _traces_to_preserve_buffer.insert(trace);
        }
    }
    
    // Step 6: Combine all traces for JFR processing
    _traces_buffer.insert(_active_traces_buffer.begin(), _active_traces_buffer.end());
    _traces_buffer.insert(_standby_traces_buffer.begin(), _standby_traces_buffer.end());

    // Always include dropped trace in JFR constant pool
    _traces_buffer.insert(getDroppedTrace());

    // PHASE 3: Process traces
    processor(_traces_buffer);

    // PHASE 4: Copy all preserved traces to current standby (old scratch, now empty)
    old_scratch->clear();  // Should already be empty, but ensure it
    for (CallTrace* trace : _traces_to_preserve_buffer) {
        old_scratch->putWithExistingId(trace, 1);
    }
    
    // Triple-buffer rotation maintains trace continuity with thread-safe malloc-free operations:
    // - Pre-allocated collections prevent malloc/free during processTraces
    // - Standby traces collected first (safe - no signal handler writes to standby)
    // - New active (old standby, now empty) receives new traces from signal handlers
    // - Old active (now scratch) safely collected after rotation, then cleared
    // - New standby (old scratch) stores preserved traces for next cycle
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

