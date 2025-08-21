/*
 * Copyright 2025 Datadog, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _THREADIDTABLE_H
#define _THREADIDTABLE_H

#include <atomic>
#include <unordered_set>
#include "branch_hints.h"

// Simple fixed size thread ID table
class ThreadIdTable {
private:
    // We have 256 slots per concurrency level (currently 16)
    // This should cater for 4096 threads - if it turns out to be too small, we
    // can increase it or make it configurable
    static const int TABLE_SIZE = 256; // power of 2
    static const int TABLE_MASK = TABLE_SIZE - 1;  // For fast bit masking
    std::atomic<int> table[TABLE_SIZE];
    
    int hash(int tid) const {
        // Improved hash function with bit mixing to reduce clustering
        unsigned int utid = static_cast<unsigned int>(tid);
        utid ^= utid >> 16;  // Mix high and low bits
        return utid & TABLE_MASK;  // Fast bit masking instead of modulo
    }
    
public:
    ThreadIdTable() {
        clear();
    }
    
    // Signal-safe insertion using atomic operations only
    void insert(int tid) {
        if (unlikely(tid == 0)) return; // Invalid thread ID, 0 is reserved for empty slots
        
        int start_slot = hash(tid);
        for (int probe = 0; probe < TABLE_SIZE; probe++) {
            int slot = (start_slot + probe) & TABLE_MASK;  // Fast bit masking
            int expected = 0;
            
            // Try to claim empty slot
            if (table[slot].compare_exchange_strong(expected, tid, std::memory_order_relaxed)) {
                return; // Successfully inserted
            }
            
            // Check if already present (common case - threads insert multiple times)
            if (likely(table[slot].load(std::memory_order_relaxed) == tid)) {
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