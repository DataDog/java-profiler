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
#include "primeProbing.h"
#include "thread.h"
#include <string.h>
#include <atomic>

// HazardPointer static members
std::atomic<CallTraceHashTable*> HazardPointer::global_hazard_list[HazardPointer::MAX_THREADS];
std::atomic<int> HazardPointer::slot_owners[HazardPointer::MAX_THREADS];

// HazardPointer implementation
int HazardPointer::getThreadHazardSlot() {
    // Signal-safe collision resolution: use OS::threadId() with semi-random prime step probing
    // This avoids thread_local allocation issues
    ProfiledThread* thrd = ProfiledThread::current();
    int tid = thrd != nullptr ? thrd->tid() : OS::threadId();

    // Semi-random prime step probing to eliminate secondary clustering
    // Each thread gets a different prime step size for unique probe sequences
    HashProbe probe(static_cast<u64>(tid), MAX_THREADS);

    int slot = probe.slot();
    for (int i = 0; i < MAX_PROBE_DISTANCE; i++) {
        // Try to claim this slot atomically
        int expected = 0;  // Empty slot (no thread ID)
        if (slot_owners[slot].compare_exchange_strong(expected, tid, std::memory_order_acq_rel)) {
            // Successfully claimed the slot
            return slot;
        }
        
        // Check if we already own this slot (for reentrant calls)
        if (slot_owners[slot].load(std::memory_order_acquire) == tid) {
            return slot;
        }
        
        // Move to next slot using probe
        if (probe.hasNext()) {
            slot = probe.next();
        }
    }
    
    // All probing attempts failed - return -1 to indicate failure
    // Caller must handle graceful degradation
    return -1;
}

HazardPointer::HazardPointer(CallTraceHashTable* resource) : active_(true), my_slot_(-1) {
    // Get thread hazard slot using signal-safe collision resolution
    my_slot_ = getThreadHazardSlot();
    
    if (my_slot_ == -1) {
        // Slot allocation failed - hazard pointer is inactive
        active_ = false;
        return;
    }

    // Update global hazard list for the successfully claimed slot
    global_hazard_list[my_slot_].store(resource, std::memory_order_seq_cst);
}

HazardPointer::~HazardPointer() {
    if (active_ && my_slot_ >= 0) {
        // Clear global hazard list using our assigned slot
        global_hazard_list[my_slot_].store(nullptr, std::memory_order_release);
        
        // Release slot ownership
        slot_owners[my_slot_].store(0, std::memory_order_release);
    }
}

HazardPointer::HazardPointer(HazardPointer&& other) noexcept : active_(other.active_), my_slot_(other.my_slot_) {
    other.active_ = false;
}

HazardPointer& HazardPointer::operator=(HazardPointer&& other) noexcept {
    if (this != &other) {
        // Clean up current state
        if (active_ && my_slot_ >= 0) {
            global_hazard_list[my_slot_].store(nullptr, std::memory_order_release);
            slot_owners[my_slot_].store(0, std::memory_order_release);
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



    _preserve_set_buffer.max_load_factor(0.75f);
    _preserve_set_buffer.rehash(static_cast<size_t>(1024 / 0.75f));

    // Initialize triple-buffered storage
    auto active_table = std::make_unique<CallTraceHashTable>();
    active_table->setInstanceId(getNextInstanceId());
    active_table->setParentStorage(this);
    _active_storage.store(active_table.release(), std::memory_order_release);

    auto standby_table = std::make_unique<CallTraceHashTable>();
    standby_table->setParentStorage(this);
    standby_table->setInstanceId(getNextInstanceId());
    _standby_storage.store(standby_table.release(), std::memory_order_release);
    
    auto scratch_table = std::make_unique<CallTraceHashTable>();
    scratch_table->setParentStorage(this);
    scratch_table->setInstanceId(getNextInstanceId());
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
    
    // Check if hazard pointer allocation failed (slot exhaustion)
    if (!guard.isActive()) {
        // No hazard protection available - return dropped trace ID
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }
    
    // Check again after registering hazard pointer - storage might have been nullified
    CallTraceHashTable* original_active = _active_storage.load(std::memory_order_acquire);
    if (original_active != active || original_active == nullptr) {
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
    // PHASE 1: Collect liveness information with simple lock (rare operation)
    {
        SharedLockGuard lock(&_liveness_lock);

        // Use pre-allocated containers to avoid malloc()
        _preserve_set_buffer.clear();

        for (const auto& checker : _liveness_checkers) {
            checker(_preserve_set_buffer);
        }
    }

    // PHASE 2: 8-Step Triple-Buffer Rotation

    CallTraceHashTable* original_active = _active_storage.load(std::memory_order_relaxed);
    CallTraceHashTable* original_standby = _standby_storage.load(std::memory_order_relaxed);
    CallTraceHashTable* original_scratch = _scratch_storage.load(std::memory_order_acquire);

    // Clear process collection for reuse (no malloc/free)
    _traces_buffer.clear();

    // Step 1: Collect from current standby directly to _traces_buffer with hook for immediate preservation
    // Only 'original_active' can be used from multiple threads at this moment.
    // Both 'original_standby' and 'original_scratch' can be used only from the single thread executing 'processTraces'
    // so we can iterate the first one and at the same time add new elements to the second one safely
    original_standby->collect(_traces_buffer, [&](CallTrace* trace) {
        if (_preserve_set_buffer.find(trace->trace_id) != _preserve_set_buffer.end()) {
            original_scratch->putWithExistingId(trace, 1);
        }
    });

    // Step 3: Clear original_standby after collection -> it will become the new active
    original_standby->clear();

    {
        // Critical section for table swap operations - disallow signals to interrupt
        // Minimize the critical section by using the lexical scope around the critical code
        CriticalSection cs;
        
        // Step 4: standby (now empty) becomes new active
        // SYNCHRONIZATION POINT: After this store, new put() operations will target original_standby
        // but ongoing put() operations may still be accessing original_active via hazard pointers
        _active_storage.store(original_standby, std::memory_order_release);

        // Step 5: Complete the rotation: active→scratch, scratch→standby  
        _scratch_storage.exchange(original_active, std::memory_order_release);
        _standby_storage.store(original_scratch, std::memory_order_release);
    }

    // Just make sure all puts to the original_active are done before proceeding
    // Do this outside of the critical section not to block the new active area needlessly
    HazardPointer::waitForHazardPointersToClear(original_active);

    // Step 6: Collect from old active directly to _traces_buffer with hook for immediate preservation
    original_active->collect(_traces_buffer, [&](CallTrace* trace) {
        if (_preserve_set_buffer.find(trace->trace_id) != _preserve_set_buffer.end()) {
            original_scratch->putWithExistingId(trace, 1);
        }
    });

    // Step 7: Update the instance id for the recently retired active buffer
    original_active->setInstanceId(getNextInstanceId());
    
    // Step 8: Add dropped trace and call processor
    _traces_buffer.insert(getDroppedTrace());

    processor(_traces_buffer);

    // Step 9: Clear the original active area (now scratch)
    original_active->clear();
    
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
