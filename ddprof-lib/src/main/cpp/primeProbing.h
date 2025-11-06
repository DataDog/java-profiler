/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PRIME_PROBING_H
#define PRIME_PROBING_H

#include "arch_dd.h"

// Hash table probe iterator for efficient collision resolution
class HashProbe {
private:
    // Prime probing constants for better hash distribution and collision resolution
    static constexpr int PRIME_STEP_COUNT = 16;    // Number of prime steps for collision resolution

    // Prime numbers for semi-random probing, selected to provide good distribution
    // These primes are carefully chosen to avoid patterns and clustering
    static constexpr u32 PRIME_STEPS[PRIME_STEP_COUNT] = {
        1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
        1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097
    };

    u32 _slot;
    u32 _prime_step;
    u32 _capacity;
    u32 _step_count;

    inline static u32 getPrimeStep(u64 hash) {
        return PRIME_STEPS[(hash >> 4) % PRIME_STEP_COUNT];
    }

    inline static u32 advanceSlot(u32 slot, u32 prime_step, u32 capacity) {
        return (slot + prime_step) & (capacity - 1);
    }

public:
    HashProbe(u64 hash, u32 capacity) 
        : _slot(hash & (capacity - 1))
        , _prime_step(getPrimeStep(hash))
        , _capacity(capacity)
        , _step_count(0) {
    }

    u32 slot() const { return _slot; }
    u32 stepCount() const { return _step_count; }
    
    bool hasNext() const { return _step_count < _capacity; }
    
    void next() {
        _slot = advanceSlot(_slot, _prime_step, _capacity);
        _step_count++;
    }
};


#endif // PRIME_PROBING_H
