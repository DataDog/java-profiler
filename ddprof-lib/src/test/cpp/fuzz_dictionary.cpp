#include <gtest/gtest.h>
#include "dictionary.h"
#include <string>
#include <vector>
#include <random>
#include <chrono>

// Fuzz test for Dictionary::lookup
TEST(DictionaryFuzzTest, LookupRandomStrings) {
    Dictionary dict;
    std::mt19937 gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> size_dist(0, 1024); // Control max length
    std::uniform_int_distribution<> char_dist(0, 255);

    for (int i = 0; i < 10000; ++i) {
        int size = size_dist(gen);
        std::vector<char> random_data(size);
        for (int j = 0; j < size; ++j) {
            random_data[j] = static_cast<char>(char_dist(gen));
        }
        // Ensure null termination for c_str()
        random_data.push_back('\0');

        const char* input_str = random_data.data();

        // Call lookup within ASSERT_NO_THROW
        // The function should handle arbitrary byte sequences without crashing.
        ASSERT_NO_THROW({
            dict.lookup(input_str);
        });

        // Also test with length
         ASSERT_NO_THROW({
            dict.lookup(random_data.data(), size);
        });
    }
}
