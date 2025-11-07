/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PRIME_PROBING_H
#define PRIME_PROBING_H

#include "arch_dd.h"
#include "common.h"

// Hash table probe iterator for efficient collision resolution
// This class is not thread-safe - the caller must ensure that a single instance is used in a single thread only
class HashProbe {
private:
    // Prime probing constants for better hash distribution and collision resolution

    // Prime numbers for semi-random probing, selected to provide good distribution
    // These primes are carefully chosen to avoid patterns and clustering
    // We are using prime numbers that will allow an arbitrary capacity value, up to
    //   2224132796298468927597810244428305585566171739231 (LCM of all numbers in the list)
    static constexpr u32 PRIME_STEPS[] = {
        1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
        1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097
    };
    static constexpr int PRIME_STEP_COUNT = sizeof(PRIME_STEPS) / sizeof(u32);

    u32 _slot;
    u32 _step;
    u32 _capacity;
    u32 _step_count;

    inline static u32 baseSlot(u64 seed, u32 capacity) {
      // Apply Knuth multiplicative hash directly to the seed
      size_t hash = (static_cast<size_t>(seed) * KNUTH_MULTIPLICATIVE_CONSTANT);
      // Use high bits for better distribution (shift right to get top bits)
      return static_cast<u32>((hash >> (sizeof(size_t) * 8 - 13)) % capacity);
    }

    inline static u32 getStep(u64 seed, u32 capacity) {
      int idx = (seed >> 4) % PRIME_STEP_COUNT;
      int orig_idx = idx;
      while ((capacity % PRIME_STEPS[idx]) == 0) {
        // not a co-prime, try next one
        idx = (idx + 1) % PRIME_STEP_COUNT;
        if (idx == orig_idx) {
          // unlikely case as the smallest failing capacity is much bigger than u32
          // we will fall-back to step of '1' anyway
          return 1;
        }
      }
      return PRIME_STEPS[idx];
    }

    inline static u32 advanceSlot(u32 slot, u32 step, u32 capacity) {
      return (slot + step) & (capacity - 1);
    }

public:
    HashProbe(u64 seed, u32 capacity)
        : _slot(baseSlot(seed, capacity))
        , _step(getStep(seed, capacity))
        , _capacity(capacity)
        , _step_count(0) {
    }

    u32 slot() const { return _slot; }
    u32 stepCount() const { return _step_count; }
    
    bool hasNext() const { return _step_count < _capacity; }

    void updateCapacity(u32 capacity) {
        _capacity = capacity;
    }
    
    u32 next() {
        _slot = advanceSlot(_slot, _step, _capacity);
        _step_count++;
        return _slot;
    }
};


#endif // PRIME_PROBING_H
