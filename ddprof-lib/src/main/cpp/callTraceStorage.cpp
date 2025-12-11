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
#include <time.h>

// HazardPointer static members
HazardSlot HazardPointer::global_hazard_list[HazardPointer::MAX_THREADS];
alignas(DEFAULT_CACHE_LINE_SIZE) int HazardPointer::slot_owners[HazardPointer::MAX_THREADS];
uint64_t HazardPointer::occupied_bitmap[HazardPointer::BITMAP_WORDS] = {};

// HazardPointer implementation
int HazardPointer::getThreadHazardSlot() {
    // Signal-safe collision resolution: use OS::threadId() with semi-random prime step probing
    // This avoids thread_local allocation issues
    ProfiledThread* thrd = ProfiledThread::currentSignalSafe();
    int tid = thrd != nullptr ? thrd->tid() : OS::threadId();

    // Semi-random prime step probing to eliminate secondary clustering
    // Each thread gets a different prime step size for unique probe sequences
    HashProbe probe(static_cast<u64>(tid), MAX_THREADS);

    int slot = probe.slot();
    for (int i = 0; i < MAX_PROBE_DISTANCE; i++) {
        // Try to claim this slot atomically
        int expected = 0;  // Empty slot (no thread ID)
        if (__atomic_compare_exchange_n(&slot_owners[slot], &expected, tid, false, __ATOMIC_ACQ_REL, __ATOMIC_RELAXED)) {
            // Successfully claimed the slot
            return slot;
        }
        
        // Check if we already own this slot (for reentrant calls)
        if (__atomic_load_n(&slot_owners[slot], __ATOMIC_ACQUIRE) == tid) {
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

HazardPointer::HazardPointer(CallTraceHashTable* resource) : _active(true), _my_slot(-1) {
    // Get thread hazard slot using signal-safe collision resolution
    _my_slot = getThreadHazardSlot();

    if (_my_slot == -1) {
        // Slot allocation failed - hazard pointer is inactive
        _active = false;
        return;
    }

    // CRITICAL ORDERING: Set bitmap bit BEFORE storing pointer
    // This ensures scanners (background threads checking hazard slots via waitForHazardPointersToClear)
    // using ACQUIRE on bitmap will see the pointer via RELEASE ordering
    // If we stored pointer first, scanner could:
    //   1. Load bitmap (doesn't see bit yet)
    //   2. Skip slot entirely
    //   3. Bitmap bit gets set (too late - already scanned past)
    //   4. Exit thinking all clear, but hazard pointer exists → USE-AFTER-FREE
    int word_index = _my_slot / 64;
    uint64_t bit_mask = 1ULL << (_my_slot % 64);
    __atomic_fetch_or(&occupied_bitmap[word_index], bit_mask, __ATOMIC_RELEASE);

    // Now store pointer - scanner's ACQUIRE on bitmap guarantees visibility of this pointer
    __atomic_store_n(&global_hazard_list[_my_slot].pointer, resource, __ATOMIC_RELEASE);
}

// Fast-path constructor using pre-allocated slot (thread-local caching optimization)
HazardPointer::HazardPointer(CallTraceHashTable* resource, int slot) : _active(true), _my_slot(slot) {
    // CRITICAL ORDERING: Set bitmap bit BEFORE storing pointer
    // Ensures scanners see pointer after observing the bitmap bit (same reasoning as above)
    int word_index = _my_slot / 64;
    uint64_t bit_mask = 1ULL << (_my_slot % 64);
    __atomic_fetch_or(&occupied_bitmap[word_index], bit_mask, __ATOMIC_RELEASE);

    // Store pointer - scanner's ACQUIRE on bitmap guarantees visibility of this pointer
    __atomic_store_n(&global_hazard_list[_my_slot].pointer, resource, __ATOMIC_RELEASE);
}

HazardPointer::~HazardPointer() {
    if (_active && _my_slot >= 0) {
        // CRITICAL ORDERING: Clear pointer BEFORE clearing bitmap bit
        // This ensures scanners (background threads in waitForHazardPointersToClear) that see
        // the bitmap bit will get nullptr for pointer
        // Even if scanner loads bitmap before we clear bit, it will see nullptr pointer (safe)
        __atomic_store_n(&global_hazard_list[_my_slot].pointer, nullptr, __ATOMIC_RELEASE);

        // Now clear bitmap bit - scanner's ACQUIRE on bitmap ensures it sees the nullptr
        int word_index = _my_slot / 64;
        uint64_t bit_mask = 1ULL << (_my_slot % 64);
        __atomic_fetch_and(&occupied_bitmap[word_index], ~bit_mask, __ATOMIC_RELEASE);

        // Release slot ownership
        __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
    }
}

HazardPointer::HazardPointer(HazardPointer&& other) noexcept : _active(other._active), _my_slot(other._my_slot) {
    other._active = false;
}

HazardPointer& HazardPointer::operator=(HazardPointer&& other) noexcept {
    if (this != &other) {
        // Clean up current state with same ordering as destructor
        if (_active && _my_slot >= 0) {
            // Clear pointer BEFORE bitmap bit (see destructor comments for rationale)
            __atomic_store_n(&global_hazard_list[_my_slot].pointer, nullptr, __ATOMIC_RELEASE);

            // Now clear bitmap bit
            int word_index = _my_slot / 64;
            uint64_t bit_mask = 1ULL << (_my_slot % 64);
            __atomic_fetch_and(&occupied_bitmap[word_index], ~bit_mask, __ATOMIC_RELEASE);

            __atomic_store_n(&slot_owners[_my_slot], 0, __ATOMIC_RELEASE);
        }

        // Move from other
        _active = other._active;
        _my_slot = other._my_slot;

        // Clear other
        other._active = false;
    }
    return *this;
}

void HazardPointer::waitForHazardPointersToClear(CallTraceHashTable* table_to_delete) {
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

    // PHASE 1: Fast path - spin with pause for short waits (common case)
    // Expected: hazard pointers clear within 1-20µs as put() operations complete
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        bool all_clear = true;

        // Scan only occupied slots using bitmap (avoids checking 8192 empty slots)
        for (int word_idx = 0; word_idx < BITMAP_WORDS; ++word_idx) {
            // Load bitmap word atomically (no malloc, async-signal-safe)
            uint64_t occupied_bits = __atomic_load_n(&occupied_bitmap[word_idx], __ATOMIC_ACQUIRE);

            // Process each set bit in this word
            while (occupied_bits) {
                // Find position of lowest set bit (0-63)
                int bit_pos = __builtin_ctzll(occupied_bits);
                int slot = word_idx * 64 + bit_pos;

                // Check if this occupied slot points to the table we're deleting
                CallTraceHashTable* hazard = const_cast<CallTraceHashTable*>(__atomic_load_n(&global_hazard_list[slot].pointer, __ATOMIC_ACQUIRE));
                if (hazard == table_to_delete) {
                    all_clear = false;
                    break;
                }

                // Clear the bit we just processed
                occupied_bits &= occupied_bits - 1;
            }

            if (!all_clear) {
                break;
            }
        }

        if (all_clear) {
            return; // Fast path success - hazard pointers cleared quickly
        }
        spinPause(); // CPU pause instruction, ~10-50 cycles
    }

    // PHASE 2: Slow path - async-signal-safe sleep for blocked thread case
    // Uses nanosleep() instead of std::this_thread::sleep_for() to avoid malloc deadlock on musl
    const int MAX_WAIT_ITERATIONS = 5000;
    struct timespec sleep_time = {0, 100000}; // 100 microseconds

    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        bool all_clear = true;

        // Scan only occupied slots using bitmap
        for (int word_idx = 0; word_idx < BITMAP_WORDS; ++word_idx) {
            uint64_t occupied_bits = __atomic_load_n(&occupied_bitmap[word_idx], __ATOMIC_ACQUIRE);

            while (occupied_bits) {
                int bit_pos = __builtin_ctzll(occupied_bits);
                int slot = word_idx * 64 + bit_pos;

                CallTraceHashTable* hazard = const_cast<CallTraceHashTable*>(__atomic_load_n(&global_hazard_list[slot].pointer, __ATOMIC_ACQUIRE));
                if (hazard == table_to_delete) {
                    all_clear = false;
                    break;
                }

                occupied_bits &= occupied_bits - 1;
            }

            if (!all_clear) {
                break;
            }
        }

        if (all_clear) {
            return; // Slow path success
        }

        // nanosleep is POSIX async-signal-safe and does not call malloc
        nanosleep(&sleep_time, nullptr);
    }

    // If we reach here, some hazard pointers didn't clear in time
    // This shouldn't happen in normal operation but we log it for debugging
}

void HazardPointer::waitForAllHazardPointersToClear() {
    // PHASE 1: Fast path - spin with pause for short waits (common case)
    const int SPIN_ITERATIONS = 100;
    for (int spin = 0; spin < SPIN_ITERATIONS; ++spin) {
        bool any_hazards = false;

        // Scan only occupied slots using bitmap
        for (int word_idx = 0; word_idx < BITMAP_WORDS; ++word_idx) {
            uint64_t occupied_bits = __atomic_load_n(&occupied_bitmap[word_idx], __ATOMIC_ACQUIRE);

            while (occupied_bits) {
                int bit_pos = __builtin_ctzll(occupied_bits);
                int slot = word_idx * 64 + bit_pos;

                // Uses GCC atomic builtin (no malloc, async-signal-safe)
                CallTraceHashTable* hazard = const_cast<CallTraceHashTable*>(__atomic_load_n(&global_hazard_list[slot].pointer, __ATOMIC_ACQUIRE));
                if (hazard != nullptr) {
                    any_hazards = true;
                    break;
                }

                occupied_bits &= occupied_bits - 1;
            }

            if (any_hazards) {
                break;
            }
        }

        if (!any_hazards) {
            return; // Fast path success - all hazard pointers cleared quickly
        }
        spinPause(); // CPU pause instruction, ~10-50 cycles
    }

    // PHASE 2: Slow path - async-signal-safe sleep for blocked thread case
    // Uses nanosleep() instead of std::this_thread::sleep_for() to avoid malloc deadlock on musl
    const int MAX_WAIT_ITERATIONS = 5000;
    struct timespec sleep_time = {0, 100000}; // 100 microseconds

    for (int wait_count = 0; wait_count < MAX_WAIT_ITERATIONS; ++wait_count) {
        bool any_hazards = false;

        // Scan only occupied slots using bitmap
        for (int word_idx = 0; word_idx < BITMAP_WORDS; ++word_idx) {
            uint64_t occupied_bits = __atomic_load_n(&occupied_bitmap[word_idx], __ATOMIC_ACQUIRE);

            while (occupied_bits) {
                int bit_pos = __builtin_ctzll(occupied_bits);
                int slot = word_idx * 64 + bit_pos;

                // Uses GCC atomic builtin (no malloc, async-signal-safe)
                CallTraceHashTable* hazard = const_cast<CallTraceHashTable*>(__atomic_load_n(&global_hazard_list[slot].pointer, __ATOMIC_ACQUIRE));
                if (hazard != nullptr) {
                    any_hazards = true;
                    break;
                }

                occupied_bits &= occupied_bits - 1;
            }

            if (any_hazards) {
                break;
            }
        }

        if (!any_hazards) {
            return; // Slow path success
        }

        // nanosleep is POSIX async-signal-safe and does not call malloc
        nanosleep(&sleep_time, nullptr);
    }

    // If we reach here, some hazard pointers didn't clear in time
    // This shouldn't happen in normal operation but we continue cleanup anyway
}


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
    // MEMORY_ORDER_ACQUIRE: Critical - synchronizes with release stores in processTraces()
    CallTraceHashTable* active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));

    // Safety check - if null, system is shutting down
    if (active == nullptr) {
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }

    // Thread-local slot caching optimization: Check if current thread has a cached hazard slot
    ProfiledThread* pThread = ProfiledThread::currentSignalSafe();
    int cached_slot = (pThread != nullptr) ? pThread->getHazardSlot() : -1;

    // Create hazard pointer guard using fast path (cached slot) or slow path (allocation)
    HazardPointer guard = (cached_slot >= 0)
        ? HazardPointer(active, cached_slot)  // Fast path: reuse cached slot (no probing)
        : HazardPointer(active);              // Slow path: allocate slot via probing

    // Check if hazard pointer allocation failed (slot exhaustion)
    if (!guard.isActive()) {
        // No hazard protection available - return dropped trace ID
        Counters::increment(CALLTRACE_STORAGE_DROPPED);
        return DROPPED_TRACE_ID;
    }

    // Cache the slot for next time if this was the first allocation
    if (pThread != nullptr && cached_slot == -1 && guard.slot() >= 0) {
        pThread->setHazardPointer(nullptr, nullptr, guard.slot());
    }

    // Check again after registering hazard pointer - storage might have been nullified
    // MEMORY_ORDER_ACQUIRE: Ensures we see any concurrent storage swaps
    CallTraceHashTable* original_active = const_cast<CallTraceHashTable*>(__atomic_load_n(&_active_storage, __ATOMIC_ACQUIRE));
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
        // but ongoing put() operations may still be accessing original_active via hazard pointers
        // MEMORY_ORDER_RELEASE: Critical - synchronizes with acquire loads in put() method
        __atomic_store_n(&_active_storage, original_standby, __ATOMIC_RELEASE);

        // Step 5: Complete the rotation: active→scratch, scratch→standby
        // MEMORY_ORDER_RELEASE: Ensures visibility of storage state changes to hazard pointer system
        __atomic_exchange_n(&_scratch_storage, original_active, __ATOMIC_RELEASE);
        __atomic_store_n(&_standby_storage, original_scratch, __ATOMIC_RELEASE);
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
