/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PRIME_PROBING_H
#define PRIME_PROBING_H

#include "arch_dd.h"

// Prime probing constants for better hash distribution and collision resolution
static constexpr int PRIME_STEP_COUNT = 16;    // Number of prime steps for collision resolution

// Prime numbers for semi-random probing, selected to provide good distribution
// These primes are carefully chosen to avoid patterns and clustering
static constexpr u32 PRIME_STEPS[PRIME_STEP_COUNT] = {
    1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
    1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097
};

// Inline utility function to get prime step for hash-based probing
inline u32 getPrimeStep(u64 hash) {
    return PRIME_STEPS[(hash >> 4) % PRIME_STEP_COUNT];
}

// Inline utility function for prime-step slot advancement
inline u32 advanceSlotPrime(u32 slot, u64 hash, u32 capacity) {
    u32 prime_step = getPrimeStep(hash);
    return (slot + prime_step) & (capacity - 1);
}

#endif // PRIME_PROBING_H
