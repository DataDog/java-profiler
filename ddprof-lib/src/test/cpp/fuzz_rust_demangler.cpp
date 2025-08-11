#include <gtest/gtest.h>
#include "rustDemangler.h"
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept> // Include for std::length_error

// Fuzz test for RustDemangler::demangle
TEST(RustDemanglerFuzzTest, DemangleRandomStrings) {
    std::mt19937 gen(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> size_dist(0, 512); // Control max length
    std::uniform_int_distribution<> char_dist(0, 255);

    for (int i = 0; i < 10000; ++i) {
        int size = size_dist(gen);
        std::vector<char> random_data(size);
        for (int j = 0; j < size; ++j) {
            random_data[j] = static_cast<char>(char_dist(gen));
        }
        // Ensure null termination for c_str()
        random_data.push_back('\0');

        // Create a string_view or const char* depending on the demangle signature
        // Assuming it takes const char*
        std::string input_str(random_data.data(), size); 

        // Call demangle within ASSERT_NO_THROW
        // The function might return nullptr or an empty string for invalid input,
        // but it should not crash or throw std::length_error.
        ASSERT_NO_THROW({
            fprintf(stderr, "Size: %d\n", size);
            fprintf(stderr, "Input: ");
            for (unsigned char c : input_str) {
                std::cerr << std::hex << std::setw(2) << std::setfill('0')
                          << static_cast<int>(c) << ' ';
            }
            std::cerr << std::dec << std::endl;
            std::string demangled_name = RustDemangler::demangle(input_str);
        });
    }
}
