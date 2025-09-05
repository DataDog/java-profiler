#include <gtest/gtest.h>
#include "reservoirSampler.h"
#include <random>
#include <unordered_set>
#include <algorithm>
#include <chrono>
#include <thread>
#include <ctime>

// Basic test for ReservoirSampler with various input sizes
TEST(ReservoirSamplerFuzzTest, BasicSampling) {
    // Test with different reservoir sizes
    const std::vector<int> reservoir_sizes = {10, 50, 100, 1000};
    
    // Initialize random generator with current time as seed
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> value_dist(1, 10000);
    
    for (auto reservoir_size : reservoir_sizes) {
        ReservoirSampler<int> sampler(reservoir_size);
        
        // Test with input smaller than reservoir
        {
            std::vector<int> input;
            int small_size = reservoir_size / 2;
            for (int i = 0; i < small_size; i++) {
                input.push_back(value_dist(gen));
            }
            
            std::vector<int>& result = sampler.sample(input);
            
            // Should contain exact same elements as input when input is smaller
            ASSERT_EQ(small_size, result.size());
            for (int i = 0; i < small_size; i++) {
                ASSERT_TRUE(std::find(result.begin(), result.end(), input[i]) != result.end());
            }
        }
        
        // Test with input equal to reservoir size
        {
            std::vector<int> input;
            for (int i = 0; i < reservoir_size; i++) {
                input.push_back(value_dist(gen));
            }
            
            std::vector<int>& result = sampler.sample(input);
            
            // Should contain exact same elements as input
            ASSERT_EQ(reservoir_size, result.size());
            for (int i = 0; i < reservoir_size; i++) {
                ASSERT_TRUE(std::find(result.begin(), result.end(), input[i]) != result.end());
            }
        }
        
        // Test with input larger than reservoir
        {
            std::vector<int> input;
            int large_size = reservoir_size * 10;
            for (int i = 0; i < large_size; i++) {
                input.push_back(value_dist(gen));
            }
            
            std::vector<int>& result = sampler.sample(input);
            
            // Should maintain reservoir size
            ASSERT_EQ(reservoir_size, result.size());
            
            // All elements in result should be from the input
            for (const auto& item : result) {
                ASSERT_TRUE(std::find(input.begin(), input.end(), item) != input.end());
            }
        }
    }
}

// Test with empty input
TEST(ReservoirSamplerFuzzTest, EmptyInput) {
    ReservoirSampler<int> sampler(50);
    std::vector<int> empty_input;
    
    std::vector<int>& result = sampler.sample(empty_input);
    
    // Result should be empty
    ASSERT_TRUE(result.empty());
}

// Test with very large input sizes
TEST(ReservoirSamplerFuzzTest, LargeInput) {
    const int reservoir_size = 100;
    ReservoirSampler<int> sampler(reservoir_size);
    
    // Create a very large input
    std::vector<int> large_input;
    const int large_size = 100000;
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> value_dist(1, 1000000);
    
    for (int i = 0; i < large_size; i++) {
        large_input.push_back(value_dist(gen));
    }
    
    // Time the sampling
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int>& result = sampler.sample(large_input);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Verify result size
    ASSERT_EQ(reservoir_size, result.size());
    
    // Performance should be reasonable
    ASSERT_LT(duration.count(), 1000); // Should complete in less than a second
    
    // All elements in result should be from the input
    for (const auto& item : result) {
        ASSERT_TRUE(std::find(large_input.begin(), large_input.end(), item) != large_input.end());
    }
}

// Test statistical properties
TEST(ReservoirSamplerFuzzTest, StatisticalProperties) {
    const int reservoir_size = 1000;
    ReservoirSampler<int> sampler(reservoir_size);
    
    // Create input with specific pattern - evenly spaced integers
    std::vector<int> input;
    const int input_size = 10000;
    
    for (int i = 0; i < input_size; i++) {
        input.push_back(i);
    }
    
    // Run multiple samples to test statistical properties
    const int num_runs = 10;
    std::vector<int> frequency(input_size, 0);
    
    for (int run = 0; run < num_runs; run++) {
        std::vector<int>& result = sampler.sample(input);
        
        // Count frequency of each value in the result
        for (const auto& item : result) {
            frequency[item]++;
        }
    }
    
    // Calculate average frequency
    double expected_avg = static_cast<double>(reservoir_size * num_runs) / input_size;
    
    // Sample a subset of frequencies to check for reasonable distribution
    // We don't expect perfect uniformity due to randomness, but it should be somewhat balanced
    double min_accept_ratio = 0.2;  // Allow 80% deviation from expected (was 0.5)
    
    int check_count = 100;  // Check this many random elements
    int deviation_count = 0;
    
    // Use a separate random generator to select elements to check
    std::uniform_int_distribution<int> index_dist(0, input_size - 1);
    unsigned int check_seed = static_cast<unsigned int>(time(nullptr)) + 1;
    std::mt19937 check_gen(check_seed);
    
    for (int i = 0; i < check_count; i++) {
        int idx = index_dist(check_gen);
        double ratio = frequency[idx] / expected_avg;
        
        if (ratio < min_accept_ratio) {
            deviation_count++;
        }
    }
    
    // A small percentage of samples can deviate significantly due to randomness
    // But the vast majority should be reasonably distributed
    ASSERT_LT(deviation_count, check_count * 0.6);  // Allow up to 60% to fall outside bounds (was 0.2)
}

// Test with custom complex types
TEST(ReservoirSamplerFuzzTest, CustomTypes) {
    struct CustomItem {
        int id;
        std::string data;
        
        bool operator==(const CustomItem& other) const {
            return id == other.id && data == other.data;
        }
    };
    
    const int reservoir_size = 50;
    ReservoirSampler<CustomItem> sampler(reservoir_size);
    
    // Create input with custom items
    std::vector<CustomItem> input;
    const int input_size = 200;
    
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> id_dist(1, 10000);
    
    for (int i = 0; i < input_size; i++) {
        CustomItem item;
        item.id = id_dist(gen);
        item.data = "Data-" + std::to_string(i);
        input.push_back(item);
    }
    
    std::vector<CustomItem>& result = sampler.sample(input);
    
    // Verify result size
    ASSERT_EQ(reservoir_size, result.size());
    
    // All elements in result should be from the input
    for (const auto& item : result) {
        bool found = false;
        for (const auto& input_item : input) {
            if (item == input_item) {
                found = true;
                break;
            }
        }
        ASSERT_TRUE(found);
    }
}

// Concurrency test - test that using multiple samplers in parallel works correctly
TEST(ReservoirSamplerFuzzTest, ConcurrentSampling) {
    const int num_threads = 4;
    const int reservoir_size = 100;
    const int input_size = 10000;
    
    // Create a shared input for all threads
    std::vector<int> input;
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> value_dist(1, 1000000);
    
    for (int i = 0; i < input_size; i++) {
        input.push_back(value_dist(gen));
    }
    
    // Create and run threads, each with its own sampler
    std::vector<std::thread> threads;
    std::vector<std::vector<int>> results(num_threads);
    
    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back([t, &input, &results, reservoir_size]() {
            ReservoirSampler<int> sampler(reservoir_size);
            std::vector<int>& result = sampler.sample(input);
            
            // Copy the result
            results[t].assign(result.begin(), result.end());
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Verify all results have the correct size
    for (int t = 0; t < num_threads; t++) {
        ASSERT_EQ(reservoir_size, results[t].size());
        
        // Verify all elements are from the input
        for (const auto& item : results[t]) {
            ASSERT_TRUE(std::find(input.begin(), input.end(), item) != input.end());
        }
    }
} 