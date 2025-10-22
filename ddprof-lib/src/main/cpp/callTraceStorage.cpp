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

// HazardPointer static members
std::atomic<CallTraceHashTable*> HazardPointer::global_hazard_list[HazardPointer::MAX_THREADS];

// HazardPointer implementation
int HazardPointer::getThreadHazardSlot() {
    // Signal-safe: use thread ID hash to assign slots
    // This avoids thread_local allocation issues in signal handlers
    std::thread::id tid = std::this_thread::get_id();

    // Apply Knuth multiplicative hash directly to thread ID hash
    size_t hash = std::hash<std::thread::id>{}(tid) * KNUTH_MULTIPLICATIVE_CONSTANT;

    // Use high bits for better distribution (shift right to get top bits)
    return static_cast<int>((hash >> (sizeof(size_t) * 8 - 8)) % MAX_THREADS);
}

HazardPointer::HazardPointer(CallTraceHashTable* resource) : active_(true) {
    // Get thread hazard slot using signal-safe method
    my_slot_ = getThreadHazardSlot();

    // Update global hazard list
    global_hazard_list[my_slot_].store(resource, std::memory_order_seq_cst);
}

HazardPointer::~HazardPointer() {
    if (active_) {
        // Clear global hazard list using our assigned slot
        global_hazard_list[my_slot_].store(nullptr, std::memory_order_release);
    }
}

HazardPointer::HazardPointer(HazardPointer&& other) noexcept : active_(other.active_), my_slot_(other.my_slot_) {
    other.active_ = false;
}

HazardPointer& HazardPointer::operator=(HazardPointer&& other) noexcept {
    if (this != &other) {
        // Clean up current state
        if (active_) {
            global_hazard_list[my_slot_].store(nullptr, std::memory_order_release);
        }

        // Move from other
        active_ = other.active_;
        my_slot_ = other.my_slot_;

        // Clear other
        other.active_ = false;
    }
    return *this;
}

void HazardPointer::waitForHazardPointersToClear(CallTraceHashTable* table_to_delete) {
    const int MAX_WAIT_ITERATIONS = 5000;
    int wait_count = 0;

    while (wait_count < MAX_WAIT_ITERATIONS) {
        bool all_clear = true;

        // Check global hazard list for the table we want to delete
        //
        // TRIPLE-BUFFER PROTECTION MECHANISM:
        // 
        // The CallTraceStorage triple-buffer rotation provides architectural protection 
        // against race conditions. Here's why no race condition can occur:
        //
        // Timeline during CallTraceStorage::~CallTraceStorage():
        // 
        // T0: [ACTIVE=TableA] [STANDBY=TableB] [SCRATCH=TableC]
        //     │
        //     │ put() creates hazard pointers → TableA only
        //     │
        // T1: _active_storage.exchange(nullptr)  ← ATOMIC BARRIER
        //     [ACTIVE=nullptr] [STANDBY=nullptr] [SCRATCH=nullptr]
        //     │
        //     │ NEW put() calls after T1:
        //     │ ├─ active = nullptr
        //     │ ├─ return DROPPED_TRACE_ID  ← NO hazard pointer created!
        //     │
        // T2: waitForHazardPointersToClear(TableA)  ← We are here
        //     │ ← Only PRE-EXISTING hazard pointers can exist (from before T1)
        //     │ ← No NEW hazard pointers possible (active=nullptr) 
        //     │
        // T3: delete TableA  ← SAFE!
        //
        // Key insight: Hazard pointers are ONLY created for the ACTIVE table via put().
        // After nullification, put() returns early - no new hazard pointers possible.
        // We only need to wait for pre-existing hazard pointers to clear.
        for (int i = 0; i < MAX_THREADS; ++i) {
            CallTraceHashTable* hazard = global_hazard_list[i].load(std::memory_order_acquire);
            if (hazard == table_to_delete) {
                all_clear = false;
                break;
            }
        }

        if (all_clear) {
            return; // All hazard pointers have cleared
        }

        // Small delay before next check
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        wait_count++;
    }

    // If we reach here, some hazard pointers didn't clear in time
    // This shouldn't happen in normal operation but we log it for debugging
}

void HazardPointer::waitForAllHazardPointersToClear() {
    const int MAX_WAIT_ITERATIONS = 5000;
    int wait_count = 0;

    while (wait_count < MAX_WAIT_ITERATIONS) {
        bool any_hazards = false;

        // Check ALL global hazard pointers
        for (int i = 0; i < MAX_THREADS; ++i) {
            CallTraceHashTable* hazard = global_hazard_list[i].load(std::memory_order_acquire);
            if (hazard != nullptr) {
                any_hazards = true;
                break;
            }
        }

        if (!any_hazards) {
            return; // All hazard pointers have cleared
        }

        // Small delay before next check
        std::this_thread::sleep_for(std::chrono::microseconds(100));
        wait_count++;
    }

    // If we reach here, some hazard pointers didn't clear in time
    // This shouldn't happen in normal operation but we continue cleanup anyway
}


static const u64 OVERFLOW_TRACE_ID = 0x7fffffffffffffffULL;  // Max 64-bit signed value

// Static atomic for instance ID generation - explicit initialization avoids function-local static issues
std::atomic<u64> CallTraceStorage::_next_instance_id{1};  // Start from 1, 0 is reserved


// Lazy initialization helper to avoid global constructor race conditions
u64 CallTraceStorage::getNextInstanceId() {
    u64 instance_id = _next_instance_id.fetch_add(1, std::memory_order_acq_rel);
    return instance_id;
}

CallTraceStorage::CallTraceStorage() : _generation_counter(1), _liveness_lock(0) {
    
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
    CallTraceHashTable* active = _active_storage.exchange(nullptr, std::memory_order_relaxed);
    CallTraceHashTable* standby = _standby_storage.exchange(nullptr, std::memory_order_relaxed);
    CallTraceHashTable* scratch = _scratch_storage.exchange(nullptr, std::memory_order_acq_rel);

    // Wait for any ongoing hazard pointer usage to complete and delete each unique table
    // Note: In triple-buffering, all three pointers should be unique, but check anyway
    HazardPointer::waitForHazardPointersToClear(active);
    delete active;

    if (standby != active) {
        HazardPointer::waitForHazardPointersToClear(standby);
        delete standby;
    }
    if (scratch != active && scratch != standby) {
        HazardPointer::waitForHazardPointersToClear(scratch);
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

void CallTraceStorage::registerLivenessChecker(LivenessChecker checker) {
    ExclusiveLockGuard lock(&_liveness_lock);
    _liveness_checkers.push_back(checker);
}

void CallTraceStorage::clearLivenessCheckers() {
    ExclusiveLockGuard lock(&_liveness_lock);
    _liveness_checkers.clear();
}


u64 CallTraceStorage::put(int num_frames, ASGCT_CallFrame* frames, bool truncated, u64 weight) {
    // Signal handlers can run concurrently with destructor
    CallTraceHashTable* active = _active_storage.load(std::memory_order_acquire);
    
    // Safety check - if null, system is shutting down
    if (active == nullptr) {
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // RAII hazard pointer guard automatically manages hazard pointer lifecycle
    HazardPointer guard(active);
    
    // Check again after registering hazard pointer - storage might have been nullified
    CallTraceHashTable* current_active = _active_storage.load(std::memory_order_acquire);
    if (current_active != active || current_active == nullptr) {
        // Storage was swapped or nullified, return dropped
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Hazard pointer prevents deletion
    u64 result = active->put(num_frames, frames, truncated, weight);

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
        SharedLockGuard lock(&_liveness_lock);
        
        // Use pre-allocated containers to avoid malloc()
        _preserve_set_buffer.clear();

        for (const auto& checker : _liveness_checkers) {
            checker(_preserve_set_buffer);
        }
    }

    // PHASE 2: Safe collection sequence - standby first, then rotate, then scratch
    
    CallTraceHashTable* current_active = _active_storage.load(std::memory_order_relaxed);
    CallTraceHashTable* current_standby = _standby_storage.load(std::memory_order_relaxed);
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
    CallTraceHashTable* standby = _standby_storage.load(std::memory_order_acquire);
    
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

