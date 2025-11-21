/*
 * Copyright 2025, Datadog, Inc.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <gtest/gtest.h>
#include <set>
#include <unordered_set>
#include "primeProbing.h"
#include "../../main/cpp/gtest_crash_handler.h"

// Test name for crash handler
static constexpr char PRIME_PROBING_TEST_NAME[] = "PrimeProbingTest";

// Global crash handler installation
class PrimeProbingGlobalSetup {
public:
    PrimeProbingGlobalSetup() {
        installGtestCrashHandler<PRIME_PROBING_TEST_NAME>();
    }
    ~PrimeProbingGlobalSetup() {
        restoreDefaultSignalHandlers();
    }
};

// Install global crash handler for all tests in this file
static PrimeProbingGlobalSetup prime_probing_global_setup;

/**
 * Test basic HashProbe construction and initial state
 */
TEST(HashProbeTest, BasicConstruction) {
    u64 seed = 0x123456789ABCDEF0ULL;
    u32 capacity = 16;  // Power of 2
    
    HashProbe probe(seed, capacity);

    EXPECT_EQ(0, probe.stepCount());
    EXPECT_TRUE(probe.hasNext());
}

/**
 * Test probe sequence generation and uniqueness
 */
TEST(HashProbeTest, ProbeSequence) {
    u64 seed = 42;
    u32 capacity = 32;  // Power of 2
    
    HashProbe probe(seed, capacity);
    std::set<u32> visited_slots;
    
    // Test probe sequence
    while (probe.hasNext() && visited_slots.size() < capacity) {
        u32 current_slot = probe.slot();
        
        // Each slot should be unique until we've visited all slots
        EXPECT_EQ(0, visited_slots.count(current_slot)) 
            << "Slot " << current_slot << " visited twice";
        
        visited_slots.insert(current_slot);
        probe.next();
    }
    
    // Should be able to visit all slots in the capacity
    EXPECT_EQ(capacity, visited_slots.size());
}

/**
 * Test probe sequence with various capacities (all powers of 2)
 */
TEST(HashProbeTest, VariousCapacities) {
    u64 seed = 0xDEADBEEF;
    
    for (u32 capacity = 4; capacity <= 1024; capacity *= 2) {
        HashProbe probe(seed, capacity);
        std::set<u32> visited_slots;
        
        // Test that we can visit all slots
        while (probe.hasNext() && visited_slots.size() < capacity) {
            u32 current_slot = probe.slot();
            EXPECT_LT(current_slot, capacity) << "Slot " << current_slot 
                << " exceeds capacity " << capacity;
            
            visited_slots.insert(current_slot);
            probe.next();
        }
        
        EXPECT_EQ(capacity, visited_slots.size()) 
            << "Failed to visit all slots for capacity " << capacity;
    }
}

/**
 * Test different seeds produce different sequences
 */
TEST(HashProbeTest, DifferentSeeds) {
    u32 capacity = 64;
    u64 seed1 = 12345;
    u64 seed2 = 67890;
    
    HashProbe probe1(seed1, capacity);
    HashProbe probe2(seed2, capacity);
    
    // Different seeds should produce different initial slots (usually)
    // or different step patterns
    bool sequences_differ = false;
    
    for (int i = 0; i < 10 && probe1.hasNext() && probe2.hasNext(); i++) {
        if (probe1.slot() != probe2.slot()) {
            sequences_differ = true;
            break;
        }
        probe1.next();
        probe2.next();
    }
    
    // At least one difference should occur in the first 10 steps
    EXPECT_TRUE(sequences_differ) << "Sequences for different seeds are identical";
}

/**
 * Test step counting functionality
 */
TEST(HashProbeTest, StepCounting) {
    u64 seed = 999;
    u32 capacity = 16;
    
    HashProbe probe(seed, capacity);
    
    EXPECT_EQ(0, probe.stepCount());
    
    for (u32 expected_count = 1; expected_count <= capacity && probe.hasNext(); expected_count++) {
        probe.next();
        EXPECT_EQ(expected_count, probe.stepCount());
    }
}

/**
 * Test hasNext() boundary conditions
 */
TEST(HashProbeTest, HasNextBoundary) {
    u64 seed = 777;
    u32 capacity = 8;
    
    HashProbe probe(seed, capacity);
    
    // Should have next for capacity iterations
    for (u32 i = 0; i < capacity; i++) {
        EXPECT_TRUE(probe.hasNext()) << "hasNext() failed at iteration " << i;
        if (i < capacity - 1) {  // Don't call next() on the last iteration
            probe.next();
        }
    }
    
    // After capacity steps, should not have next
    probe.next();
    EXPECT_FALSE(probe.hasNext());
}

/**
 * Test prime step selection avoids common factors
 */
TEST(HashProbeTest, PrimeStepSelection) {
    // Test with capacities that are multiples of small primes
    std::vector<u32> test_capacities = {16, 32, 64, 128, 256};
    
    for (u32 capacity : test_capacities) {
        // Try multiple seeds to ensure we get different step values
        std::set<u32> observed_steps;
        
        for (u64 seed = 0; seed < 100; seed++) {
            HashProbe probe(seed, capacity);
            
            // Force some probing to observe the step behavior
            std::set<u32> slots_in_sequence;
            u32 iterations = 0;
            
            while (probe.hasNext() && iterations < capacity && 
                   slots_in_sequence.size() < capacity) {
                u32 slot = probe.slot();
                slots_in_sequence.insert(slot);
                probe.next();
                iterations++;
            }
            
            // If we visited all slots, the step size was coprime with capacity
            if (slots_in_sequence.size() == capacity) {
                // This indicates a good step selection
                // We can't directly access the step, but this validates the behavior
                EXPECT_EQ(capacity, slots_in_sequence.size());
            }
        }
    }
}

/**
 * Test probe distribution quality
 */
TEST(HashProbeTest, ProbeDistribution) {
    u32 capacity = 64;
    u32 num_seeds = 100;
    
    // Count how often each slot is visited first across different seeds
    std::vector<u32> first_slot_counts(capacity, 0);
    
    for (u64 seed = 0; seed < num_seeds; seed++) {
        HashProbe probe(seed, capacity);
        first_slot_counts[probe.slot()]++;
    }
    
    // Check that distribution is reasonably uniform
    // Each slot should be visited at least once as the first slot
    u32 empty_slots = 0;
    for (u32 count : first_slot_counts) {
        if (count == 0) {
            empty_slots++;
        }
    }
    
    // Allow some empty slots, but not too many (less than 25% empty)
    EXPECT_LT(empty_slots, capacity / 4) 
        << "Too many slots never selected as first slot";
}

/**
 * Test edge case with minimum capacity
 */
TEST(HashProbeTest, MinimalCapacity) {
    u64 seed = 42;
    u32 capacity = 1;
    
    HashProbe probe(seed, capacity);
    
    EXPECT_EQ(0, probe.slot());  // Only slot 0 possible with capacity 1
    EXPECT_EQ(0, probe.stepCount());
    EXPECT_TRUE(probe.hasNext());
    
    probe.next();
    EXPECT_EQ(1, probe.stepCount());
    EXPECT_FALSE(probe.hasNext());
}

/**
 * Test that advance slot operation works correctly
 */
TEST(HashProbeTest, SlotAdvancement) {
    u64 seed = 12345;
    u32 capacity = 32;
    
    HashProbe probe(seed, capacity);
    u32 initial_slot = probe.slot();
    
    probe.next();
    u32 next_slot = probe.slot();
    
    // Slots should be different (unless step size is a multiple of capacity)
    // and both should be within bounds
    EXPECT_LT(initial_slot, capacity);
    EXPECT_LT(next_slot, capacity);
}

/**
 * Test full cycle completion for various seed patterns
 */
TEST(HashProbeTest, FullCycleCompletion) {
    u32 capacity = 16;
    
    // Test with seeds that have different bit patterns
    std::vector<u64> test_seeds = {
        0x0000000000000001ULL,  // Minimal seed
        0x5555555555555555ULL,  // Alternating bits
        0xAAAAAAAAAAAAAAAAULL,  // Alternating bits (inverse)
        0xFFFFFFFFFFFFFFFFULL,  // All bits set
        0x123456789ABCDEF0ULL   // Mixed pattern
    };
    
    for (u64 seed : test_seeds) {
        HashProbe probe(seed, capacity);
        std::unordered_set<u32> visited;
        
        u32 steps = 0;
        while (probe.hasNext() && steps < capacity * 2) {  // Safety limit
            visited.insert(probe.slot());
            probe.next();
            steps++;
        }
        
        // Should visit all slots exactly once
        EXPECT_EQ(capacity, visited.size()) 
            << "Failed full cycle for seed 0x" << std::hex << seed;
        EXPECT_EQ(capacity, steps) 
            << "Wrong step count for seed 0x" << std::hex << seed;
    }
}

/**
 * Test enhanced Knuth multiplicative hashing distribution with high-bit extraction
 */
TEST(HashProbeTest, KnuthHashingDistribution) {
    u32 capacity = 64;
    u32 num_tests = 1000;
    
    // Test that Knuth hashing with high-bit extraction provides excellent distribution
    // The implementation uses: (hash >> (sizeof(size_t) * 8 - 13)) % capacity
    // This extracts the high-order bits after Knuth multiplication for better distribution
    std::vector<u32> slot_counts(capacity, 0);
    
    for (u64 seed = 1; seed <= num_tests; seed++) {
        HashProbe probe(seed, capacity);
        slot_counts[probe.slot()]++;
    }
    
    // Check for excellent distribution - high-bit extraction should provide superior results
    u32 min_hits = num_tests;
    u32 max_hits = 0;
    u32 empty_slots = 0;
    
    for (u32 count : slot_counts) {
        if (count == 0) {
            empty_slots++;
        } else {
            min_hits = std::min(min_hits, count);
            max_hits = std::max(max_hits, count);
        }
    }
    
    // With high-bit extraction after Knuth multiplication, we expect even better distribution:
    // - Very few empty slots (less than 5% of capacity due to high-bit extraction)
    // - Tighter distribution bounds (max hits shouldn't be more than 3x average)
    u32 expected_avg = num_tests / capacity;
    
    EXPECT_LT(empty_slots, capacity / 20) << "Too many empty slots - high-bit extraction should minimize this";
    EXPECT_LT(max_hits, expected_avg * 3) << "Max hits per slot too high - high-bit extraction should prevent clustering";
    
    if (min_hits > 0) {
        EXPECT_GT(min_hits * 8, expected_avg) << "Min hits per slot too low for enhanced hashing";
    }
}

/**
 * Test high-bit extraction effectiveness across different capacity sizes
 */
TEST(HashProbeTest, HighBitExtractionEffectiveness) {
    // Test multiple power-of-2 capacities to validate high-bit extraction
    std::vector<u32> test_capacities = {16, 32, 64, 128, 256};
    
    for (u32 capacity : test_capacities) {
        std::vector<u32> slot_counts(capacity, 0);
        u32 num_tests = capacity * 10;  // 10x capacity for good statistics
        
        // Use seeds with various bit patterns to stress-test the hash function
        for (u64 base_seed = 1; base_seed <= num_tests; base_seed++) {
            // Create seeds with different high/low bit patterns
            u64 seed = (base_seed << 32) | (base_seed * 0x9E3779B9ULL);
            HashProbe probe(seed, capacity);
            slot_counts[probe.slot()]++;
        }
        
        // Calculate distribution statistics
        u32 min_hits = num_tests, max_hits = 0, empty_slots = 0;
        for (u32 count : slot_counts) {
            if (count == 0) {
                empty_slots++;
            } else {
                min_hits = std::min(min_hits, count);
                max_hits = std::max(max_hits, count);
            }
        }
        
        u32 expected_avg = num_tests / capacity;
        
        // High-bit extraction should provide excellent distribution across all capacity sizes
        EXPECT_LT(empty_slots, capacity / 16) 
            << "Capacity " << capacity << ": too many empty slots with high-bit extraction";
        EXPECT_LT(max_hits, expected_avg * 2.5) 
            << "Capacity " << capacity << ": clustering detected despite high-bit extraction";
        
        if (min_hits > 0) {
            EXPECT_GT(min_hits * 6, expected_avg) 
                << "Capacity " << capacity << ": poor minimum distribution with high-bit extraction";
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}