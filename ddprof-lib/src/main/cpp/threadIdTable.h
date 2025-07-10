/*
 * Copyright The async-profiler authors
 * SPDX-License-Identifier: Apache-2.0
 * Copyright 2021, 2025 Datadog, Inc
 */

#ifndef _THREADIDTABLE_H
#define _THREADIDTABLE_H

#include <atomic>
#include <unordered_set>

// Signal-safe thread ID table with fixed size
class ThreadIdTable {
private:
    static const int TABLE_SIZE = 256;  // Should handle most realistic thread counts
    std::atomic<int> table[TABLE_SIZE];
    
    int hash(int tid) const {
        // Simple hash function - could be improved if needed
        return tid % TABLE_SIZE;
    }
    
public:
    ThreadIdTable() {
        clear();
    }
    
    // Signal-safe insertion using atomic operations only
    void insert(int tid) {
        if (tid == 0) return; // Invalid thread ID, 0 is reserved for empty slots
        
        int start_slot = hash(tid);
        for (int probe = 0; probe < TABLE_SIZE; probe++) {
            int slot = (start_slot + (probe * 7)) % TABLE_SIZE;
            int expected = 0;
            
            // Try to claim empty slot
            if (table[slot].compare_exchange_strong(expected, tid, std::memory_order_relaxed)) {
                return; // Successfully inserted
            }
            
            // Check if already present
            if (table[slot].load(std::memory_order_relaxed) == tid) {
                return; // Already exists
            }
        }
        // Table full - thread ID will be lost, but this is rare and non-critical
        // Could increment a counter here for diagnostics if needed
    }
    
    // Clear the table (not signal-safe, called during buffer switch)
    void clear() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].store(0, std::memory_order_relaxed);
        }
    }
    
    // Collect all thread IDs into a set (not signal-safe, called during buffer switch)
    void collect(std::unordered_set<int>& result) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            int tid = table[i].load(std::memory_order_relaxed);
            if (tid != 0) {
                result.insert(tid);
            }
        }
    }
};

#endif // _THREADIDTABLE_H 