#pragma once

#include <string>
#include <vector>

struct BenchmarkResult {
    std::string name;
    long long total_time_ns;
    int iterations;
    double avg_time_ns;
};

struct BenchmarkConfig {
    int warmup_iterations;
    int measurement_iterations;
    std::string csv_file;
    std::string json_file;
    bool debug;

    BenchmarkConfig() : warmup_iterations(100000), measurement_iterations(1000000), debug(false) {
    }
};
