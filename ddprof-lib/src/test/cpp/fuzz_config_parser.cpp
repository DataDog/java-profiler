#include <gtest/gtest.h>
#include "profiler.h"
#include "arguments.h" // Assuming Arguments class is defined here
#include <vector>
#include <string>
#include <random>
#include <chrono>

class ConfigFuzzTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize random generator
        gen.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    }
    
    // Generate a random configuration string
    std::string generateRandomConfig() {
        std::vector<std::string> validOptions = {
            "cpu", "alloc", "lock", "wall", "interval", "jstackdepth", "file",
            "threads", "cstack", "safemode", "dir", "event", "filter", "include",
            "exclude", "timeout", "format", "maxframes"
        };
        
        std::uniform_int_distribution<> optCountDist(1, 10);
        int optCount = optCountDist(gen);
        
        std::string config;
        for (int i = 0; i < optCount; i++) {
            // Select a random option
            std::uniform_int_distribution<> optDist(0, validOptions.size() - 1);
            std::string option = validOptions[optDist(gen)];
            
            // Generate a random value
            std::uniform_int_distribution<> valueTypeDist(0, 3);
            int valueType = valueTypeDist(gen);
            
            std::string value;
            switch (valueType) {
                case 0: { // Number
                    std::uniform_int_distribution<> numDist(0, 10000);
                    value = std::to_string(numDist(gen));
                    break;
                }
                case 1: { // String
                    static const char alphanum[] =
                        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
                    std::uniform_int_distribution<> lenDist(1, 20);
                    int len = lenDist(gen);
                    std::uniform_int_distribution<> charDist(0, sizeof(alphanum) - 2);
                    
                    value.reserve(len);
                    for (int j = 0; j < len; j++) {
                        value += alphanum[charDist(gen)];
                    }
                    break;
                }
                case 2: { // Boolean
                    std::uniform_int_distribution<> boolDist(0, 1);
                    value = boolDist(gen) ? "true" : "false";
                    break;
                }
                case 3: { // Number with unit
                    std::uniform_int_distribution<> numDist(0, 10000);
                    std::vector<std::string> units = {"ns", "us", "ms", "s", "m", "h", "k", "m", "g"};
                    std::uniform_int_distribution<> unitDist(0, units.size() - 1);
                    
                    value = std::to_string(numDist(gen)) + units[unitDist(gen)];
                    break;
                }
            }
            
            if (!config.empty()) {
                config += ",";
            }
            config += option + "=" + value;
        }
        
        return config;
    }
    
    // Generate malformed config with syntax errors
    std::string generateMalformedConfig() {
        std::string config = generateRandomConfig();
        
        // Apply random malformations
        std::uniform_int_distribution<> malformTypeDist(0, 5);
        int malformType = malformTypeDist(gen);
        
        switch (malformType) {
            case 0: // Remove random character
                if (!config.empty()) {
                    std::uniform_int_distribution<> posDist(0, config.size() - 1);
                    int pos = posDist(gen);
                    config.erase(pos, 1);
                }
                break;
            case 1: // Insert random character
                {
                    std::uniform_int_distribution<> posDist(0, config.size());
                    int pos = posDist(gen);
                    std::uniform_int_distribution<> charDist(0, 127);
                    char c = static_cast<char>(charDist(gen));
                    config.insert(pos, 1, c);
                }
                break;
            case 2: // Duplicate equals sign
                {
                    size_t pos = config.find('=');
                    if (pos != std::string::npos) {
                        config.insert(pos, 1, '=');
                    }
                }
                break;
            case 3: // Remove equals sign
                {
                    size_t pos = config.find('=');
                    if (pos != std::string::npos) {
                        config.erase(pos, 1);
                    }
                }
                break;
            case 4: // Add extra comma
                config += ",";
                break;
            case 5: // Add unclosed quote
                config += "\"";
                break;
        }
        
        return config;
    }
    
    std::mt19937 gen;
};

TEST_F(ConfigFuzzTest, RandomConfigFuzz) {
    Profiler profiler;
    
    // Test with 100 random but syntactically correct configs
    for (int i = 0; i < 100; i++) {
        std::string config = generateRandomConfig();
        
        ASSERT_NO_THROW({
            Arguments args; 
            args.parse(config.c_str()); 
            profiler.run(args); // Pass the Arguments object
        });
    }
}

TEST_F(ConfigFuzzTest, MalformedConfigFuzz) {
    Profiler profiler;
    
    // Test with 100 malformed configs
    for (int i = 0; i < 100; i++) {
        std::string config = generateMalformedConfig();
        
        ASSERT_NO_THROW({
            Arguments args;
            try {
                args.parse(config.c_str());
            } catch (...) {
                // Ignore parsing errors for fuzzing run()
            }
            profiler.run(args); // Pass the Arguments object
        });
    }
}

TEST_F(ConfigFuzzTest, ExtremeLongConfig) {
    Profiler profiler;
    
    // Create extremely long config string
    std::string longConfig;
    for (int i = 0; i < 1000; i++) {
        longConfig += generateRandomConfig() + ",";
    }
    
    ASSERT_NO_THROW({
        Arguments args;
        try {
            args.parse(longConfig.c_str());
        } catch (...) {
             // Ignore parsing errors for fuzzing run()
        }
        profiler.run(args); // Pass the Arguments object
    });
}
