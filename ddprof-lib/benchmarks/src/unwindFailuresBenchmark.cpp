#include "benchmarkConfig.h"
#include "unwindStats.h"
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Test data - using JVM stub function names
const char *TEST_NAMES[] = {"Java_java_lang_String_toString", "Java_java_lang_Object_hashCode",
                            "Java_java_lang_System_arraycopy",
                            "Java_java_lang_Thread_currentThread", "Java_java_lang_Class_getName"};
const int NUM_NAMES = sizeof(TEST_NAMES) / sizeof(TEST_NAMES[0]);

// Global variables
std::vector<BenchmarkResult> results;
BenchmarkConfig config;

// Pre-generated random values for benchmarking
struct RandomValues {
    std::vector<std::string> names;
    std::vector<UnwindFailureKind> kinds;
    std::vector<int> name_indices;

    void generate(int count) {
        std::mt19937 rng(42); // Fixed seed for reproducibility
        names.resize(count);
        kinds.resize(count);
        name_indices.resize(count);

        for (int i = 0; i < count; i++) {
            name_indices[i] = rng() % NUM_NAMES;
            names[i] = TEST_NAMES[name_indices[i]];
            kinds[i] = static_cast<UnwindFailureKind>(rng() % 3);
        }
    }
};

RandomValues random_values;

void exportResultsToCSV(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Write header
    file << "Benchmark,Total Time (ns),Iterations,Average Time (ns)\n";

    // Write data
    for (const auto &result : results) {
        file << result.name << "," << result.total_time_ns << "," << result.iterations << ","
             << result.avg_time_ns << "\n";
    }

    file.close();
    std::cout << "Results exported to CSV: " << filename << std::endl;
}

void exportResultsToJSON(const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "{\n  \"benchmarks\": [\n";
    for (size_t i = 0; i < results.size(); ++i) {
        const auto &result = results[i];
        file << "    {\n"
             << "      \"name\": \"" << result.name << "\",\n"
             << "      \"total_time_ns\": " << result.total_time_ns << ",\n"
             << "      \"iterations\": " << result.iterations << ",\n"
             << "      \"avg_time_ns\": " << result.avg_time_ns << "\n"
             << "    }" << (i < results.size() - 1 ? "," : "") << "\n";
    }
    file << "  ]\n}\n";

    file.close();
    std::cout << "Results exported to JSON: " << filename << std::endl;
}

// Helper function to run a benchmark with warmup
template <typename F>
BenchmarkResult runBenchmark(const std::string &name, F &&func, double rng_overhead = 0.0) {
    std::cout << "\n--- Benchmark: " << name << " ---" << std::endl;

    // Warmup phase
    if (config.warmup_iterations > 0) {
        std::cout << "Warming up with " << config.warmup_iterations << " iterations..."
                  << std::endl;
        for (int i = 0; i < config.warmup_iterations; i++) {
            func(i);
        }
    }

    // Measurement phase
    std::cout << "Running " << config.measurement_iterations << " iterations..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < config.measurement_iterations; i++) {
        func(i);
        if (config.debug && i % 100000 == 0) {
            std::cout << "Progress: " << (i * 100 / config.measurement_iterations) << "%"
                      << std::endl;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    double avg_time = (double)duration.count() / config.measurement_iterations;
    if (rng_overhead > 0) {
        avg_time -= rng_overhead;
    }

    std::cout << "Total time: " << duration.count() << " ns" << std::endl;
    std::cout << "Average time per operation: " << avg_time << " ns" << std::endl;
    if (rng_overhead > 0) {
        std::cout << "  (RNG overhead of " << rng_overhead << " ns has been subtracted)"
                  << std::endl;
    }

    return {name, static_cast<long long>(avg_time * config.measurement_iterations),
            config.measurement_iterations, avg_time};
}

// Benchmark just the RNG overhead
BenchmarkResult measureRNGOverhead() {
    std::mt19937 rng(42);
    std::vector<const char *> names(config.measurement_iterations);
    std::vector<UnwindFailureKind> kinds(config.measurement_iterations);
    std::vector<int> indices(config.measurement_iterations);

    return runBenchmark("RNG Overhead", [&](int i) {
        indices[i] = rng() % NUM_NAMES;
        names[i] = TEST_NAMES[indices[i]];
        kinds[i] = static_cast<UnwindFailureKind>(rng() % 3);
    });
}

// Main benchmark function
void benchmarkUnwindFailures() {
    UnwindFailures failures;
    results.clear(); // Clear any previous results

    std::cout << "=== Benchmarking UnwindFailures ===" << std::endl;
    std::cout << "Configuration:" << std::endl;
    std::cout << "  Warmup iterations: " << config.warmup_iterations << std::endl;
    std::cout << "  Measurement iterations: " << config.measurement_iterations << std::endl;
    std::cout << "  Number of test names: " << NUM_NAMES << std::endl;
    std::cout << "  Debug mode: " << (config.debug ? "enabled" : "disabled") << std::endl;

    // First measure RNG overhead
    std::cout << "\nMeasuring RNG overhead..." << std::endl;
    auto rng_overhead = measureRNGOverhead();
    double overhead_per_op = rng_overhead.avg_time_ns;
    std::cout << "RNG overhead per operation: " << overhead_per_op << " ns" << std::endl;

    // Create RNG for actual benchmarks
    std::mt19937 rng(42);

    // Run actual benchmarks with RNG inline and overhead subtracted internally
    results.push_back(runBenchmark(
            "Record Single Failure Kind",
            [&](int) {
                int idx = rng() % NUM_NAMES;
                auto kind = static_cast<UnwindFailureKind>(rng() % 3);
                failures.record(UNWIND_FAILURE_STUB, TEST_NAMES[idx]);
            },
            overhead_per_op));

    results.push_back(runBenchmark(
        "Record Mixed Failures",
        [&](int) {
            int idx = rng() % NUM_NAMES;
            auto kind = static_cast<UnwindFailureKind>(rng() % 3);
            failures.record(kind, TEST_NAMES[idx]);
        },
        overhead_per_op));

    results.push_back(runBenchmark(
        "Find Name",
        [&](int) {
            int idx = rng() % NUM_NAMES;
            failures.findName(TEST_NAMES[idx]);
        },
        overhead_per_op));

    results.push_back(runBenchmark(
        "Count Failures with Mixed Kinds",
        [&](int) {
            int idx = rng() % NUM_NAMES;
            auto kind = static_cast<UnwindFailureKind>(rng() % 3);
            failures.count(TEST_NAMES[idx], kind);
        },
        overhead_per_op));

    // For merge benchmark, we'll pre-populate the collections since that's not part of what we're
    // measuring
    UnwindFailures failures1;
    UnwindFailures failures2;
    // Use a smaller number of items for pre-population to avoid overflow
    const int prePopulateCount = std::min(1000, config.measurement_iterations / 2);
    for (int i = 0; i < prePopulateCount; i++) {
        int idx = rng() % NUM_NAMES;
        auto kind = static_cast<UnwindFailureKind>(rng() % 3);
        failures1.record(kind, TEST_NAMES[idx]);
        failures2.record(kind, TEST_NAMES[idx]);
    }

    results.push_back(runBenchmark("Merge Failures", [&](int) {
        failures1.merge(failures2);
    }));

    std::cout << "\n=== Benchmark Complete ===" << std::endl;
}

void printUsage(const char *programName) {
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  --csv <filename>    Export results to CSV file\n"
              << "  --json <filename>   Export results to JSON file\n"
              << "  --warmup <n>        Number of warmup iterations (default: 100000)\n"
              << "  --iterations <n>    Number of measurement iterations (default: 1000000)\n"
              << "  --debug            Enable debug output\n"
              << "  -h, --help         Show this help message\n";
}

int main(int argc, char *argv[]) {
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--csv") == 0 && i + 1 < argc) {
            config.csv_file = argv[++i];
        } else if (strcmp(argv[i], "--json") == 0 && i + 1 < argc) {
            config.json_file = argv[++i];
        } else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
            config.warmup_iterations = std::atoi(argv[++i]);
        } else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
            config.measurement_iterations = std::atoi(argv[++i]);
        } else if (strcmp(argv[i], "--debug") == 0) {
            config.debug = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            printUsage(argv[0]);
            return 1;
        }
    }

    std::cout << "Running UnwindFailures benchmark..." << std::endl;
    benchmarkUnwindFailures();

    // Export results if requested
    if (!config.csv_file.empty()) {
        exportResultsToCSV(config.csv_file);
    }
    if (!config.json_file.empty()) {
        exportResultsToJSON(config.json_file);
    }

    return 0;
}
