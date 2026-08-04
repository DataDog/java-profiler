/*
 * Copyright The async-profiler authors
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "callTraceStorage.h"
#include "counters.h"
#include "log.h"
#include "os.h"
#include "common.h"
#include "vmEntry.h" // For BCI_ERROR constant
#include "arch.h" // For LP64_ONLY macro and COMMA macro
#include "guards.h" // For table swap critical sections
#include "threadLocalData.h"
#include <string.h>
#include <atomic>

static const u64 OVERFLOW_TRACE_ID = 0x7fffffffffffffffULL;  // Max 64-bit signed value

// Static atomic for instance ID generation - explicit initialization avoids function-local static issues
u64 CallTraceStorage::_next_instance_id = 1;  // Start from 1, 0 is reserved


// Lazy initialization helper to avoid global constructor race conditions
u64 CallTraceStorage::getNextInstanceId() {
    // Uses GCC atomic builtin (no malloc, async-signal-safe)
    u64 instance_id = __atomic_fetch_add(&_next_instance_id, 1, __ATOMIC_ACQ_REL);
    return instance_id;
}

CallTraceStorage::CallTraceStorage() : _active_storage(nullptr), _standby_storage(nullptr), _scratch_storage(nullptr), _generation_counter(1), _liveness_lock(0) {
    
    // Pre-allocate and pre-size collections with conservative load factor
    _traces_buffer.max_load_factor(0.75f);
    _traces_buffer.rehash(static_cast<size_t>(2048 / 0.75f));



    _preserve_set_buffer.max_load_factor(0.75f);
    _preserve_set_buffer.rehash(static_cast<size_t>(1024 / 0.75f));

    // Initialize triple-buffered storage
    auto active_table = std::make_unique<CallTraceHashTable>();
    active_table->setInstanceId(getNextInstanceId());
    active_table->setParentStorage(this);
    __atomic_store_n(&_active_storage, active_table.release(), __ATOMIC_RELEASE);

    auto standby_table = std::make_unique<CallTraceHashTable>();
    standby_table->setParentStorage(this);
    standby_table->setInstanceId(getNextInstanceId());
    __atomic_store_n(&_standby_storage, standby_table.release(), __ATOMIC_RELEASE);
    
    auto scratch_table = std::make_unique<CallTraceHashTable>();
    scratch_table->setParentStorage(this);
    scratch_table->setInstanceId(getNextInstanceId());
    __atomic_store_n(&_scratch_storage, scratch_table.release(), __ATOMIC_RELEASE);

    // Pre-allocate containers to avoid malloc() during hot path operations
    _liveness_checkers.reserve(4);      // Typical max: 1-2 checkers, avoid growth

    // Initialize counters
    Counters::set(CALLTRACE_STORAGE_BYTES, 0);
    Counters::set(CALLTRACE_STORAGE_TRACES, 0);
}

CallTraceStorage::~CallTraceStorage() {
    // Atomically invalidate storage pointers to prevent new put() operations
    // ACQ_REL ordering: RELEASE ensures nullptr is visible to put()'s ACQUIRE load,
    // ACQUIRE ensures we see the latest pointer value for subsequent deletion
    CallTraceHashTable* active = const_cast<CallTraceHashTable*>(__atomic_exchange_n(&_active_storage, nullptr, __ATOMIC_ACQ_REL));
    CallTraceHashTable* standby = const_cast<CallTraceHashTable*>(__atomic_exchange_n(&_standby_storage, nullptr, __ATOMIC_ACQ_REL));
    CallTraceHashTable* scratch = const_cast<CallTraceHashTable*>(__atomic_exchange_n(&_scratch_storage, nullptr, __ATOMIC_ACQ_REL));

    // Wait for any ongoing refcount usage to complete and delete each unique table
    // Note: In triple-buffering, all three pointers should be unique, but check anyway
    RefCountGuard::waitForRefCountToClear(active);
    delete active;

    if (standby != active) {
        RefCountGuard::waitForRefCountToClear(standby);
        delete standby;
    }
    if (scratch != active && scratch != standby) {
        RefCountGuard::waitForRefCountToClear(scratch);
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
    // MEMORY_ORDER_ACQUIRE: Critical - synchronizes with release stores in processTraces()
    CallTraceHashTable* active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));

    // Safety check - if null, system is shutting down
    if (active == nullptr) {
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }

    // RAII refcount guard automatically manages reference count lifecycle
    // Uses pointer-first protocol for race-free operation
    RefCountGuard guard(active);

    // Check if refcount guard allocation failed (slot exhaustion)
    if (!guard.isActive()) {
        // No refcount protection available - return dropped trace ID
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }

    // CRITICAL REVALIDATION CHECK: Prevents use-after-free during guard construction race
    //
    // Race scenario: Scanner can see count=0 during guard construction window:
    //   1. We load active table pointer above
    //   2. RefCountGuard constructor stores pointer but count still 0 (preemption)
    //   3. Scanner sees count=0, treats slot as inactive, deletes table
    //   4. RefCountGuard constructor completes (count=1), but table already deleted
    //   5. This check detects the race: _active_storage was nullified by scanner
    //   6. We return DROPPED_TRACE_ID, never touching the deleted table
    //
    // Memory ordering: ACQUIRE load ensures we see scanner's ACQ_REL exchange to nullptr
    CallTraceHashTable* original_active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));
    if (original_active != active || original_active == nullptr) {
        // Storage was swapped or nullified during guard construction
        // SAFE: We detected the race, drop this trace, never use the table pointer
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }

    // Refcount guard prevents deletion
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

    // PHASE 2: 10-Step Triple-Buffer Rotation

    // Load storage pointers - ACQUIRE ordering synchronizes with RELEASE stores from
    // previous processTraces() calls and constructor initialization
    CallTraceHashTable* original_active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));
    CallTraceHashTable* original_standby = const_cast<CallTraceHashTable*>(__atomic_load_n(&_standby_storage, __ATOMIC_ACQUIRE));
    CallTraceHashTable* original_scratch = const_cast<CallTraceHashTable*>(__atomic_load_n(&_scratch_storage, __ATOMIC_ACQUIRE));

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

    // Step 3: Clear standby table structure but DEFER memory deallocation
    // The standby traces are now in _traces_buffer as raw pointers.
    // We must keep the underlying memory alive until processor() finishes.
    // clearTableOnly() resets the table for reuse but returns the chunks for later freeing.
    ChunkList standby_chunks = original_standby->clearTableOnly();

    {
        // Critical section for table swap operations - disallow signals to interrupt
        // Minimize the critical section by using the lexical scope around the critical code
        CriticalSection cs;
        
        // Step 4: standby (now empty) becomes new active
        // SYNCHRONIZATION POINT: After this store, new put() operations will target original_standby
        // but ongoing put() operations may still be accessing original_active via RefCountGuards
        // MEMORY_ORDER_RELEASE: Critical - synchronizes with acquire loads in put() method
        __atomic_store_n(&_active_storage, original_standby, __ATOMIC_RELEASE);

        // Step 5: Complete the rotation: active→scratch, scratch→standby
        // MEMORY_ORDER_RELEASE: Ensures visibility of storage state changes to RefCountGuard system
        __atomic_exchange_n(&_scratch_storage, original_active, __ATOMIC_RELEASE);
        __atomic_store_n(&_standby_storage, original_scratch, __ATOMIC_RELEASE);
    }

    // Just make sure all puts to the original_active are done before proceeding
    // Do this outside of the critical section not to block the new active area needlessly
    RefCountGuard::waitForRefCountToClear(original_active);

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

    // Step 9: NOW safe to free standby chunks - processor is done accessing those traces
    // This completes the deferred deallocation that prevents use-after-free
    LinearAllocator::freeChunks(standby_chunks);

    // Step 10: Clear the original active area (now scratch)
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

    // Load current table pointers - ACQUIRE ordering synchronizes with RELEASE stores
    // from processTraces() rotation and constructor initialization
    CallTraceHashTable* active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));
    CallTraceHashTable* standby = const_cast<CallTraceHashTable*>(__atomic_load_n(&_standby_storage, __ATOMIC_ACQUIRE));
    
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
