#include <gtest/gtest.h>
#include "threadFilter.h"
#include <string>
#include <vector>
#include <random>
#include <chrono>

// Fuzz test for ThreadFilter::accept
TEST(ThreadFilterFuzzTest, AcceptRandomTids) { // Renamed test
    ThreadFilter filter;
    // Test accept against a default (likely empty) filter

    std::mt19937 gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    // Generate random integers, including negative values and zero
    std::uniform_int_distribution<int> tid_dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (int i = 0; i < 10000; ++i) {
        int random_tid = tid_dist(gen);

        // Call accept with random integer TID within ASSERT_NO_THROW
        ASSERT_NO_THROW({
            filter.accept(random_tid); // Pass integer TID
        });
    }
}
