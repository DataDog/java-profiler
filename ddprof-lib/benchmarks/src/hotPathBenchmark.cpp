/*
 * Microbenchmarks for hot-path optimizations:
 *   Fix 1 - getLockIndex: modulo vs bitmask for power-of-2 CONCURRENCY_LEVEL
 *   Fix 5 - findLibraryByAddress: O(N) linear scan vs thread-local last-hit cache
 *   Fix 6 - reservoir sample: vector copy vs reference
 */
#include "benchmarkConfig.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

// ---- shared helpers ---------------------------------------------------------

BenchmarkConfig config;
std::vector<BenchmarkResult> results;

template <typename F>
BenchmarkResult runBenchmark(const std::string &name, F &&func) {
    std::cout << "\n--- " << name << " ---" << std::endl;

    for (int i = 0; i < config.warmup_iterations; i++) {
        func(i);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < config.measurement_iterations; i++) {
        func(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double avg = (double)ns / config.measurement_iterations;

    std::cout << "  avg: " << avg << " ns/op  (total " << ns << " ns, "
              << config.measurement_iterations << " iters)\n";
    return {name, ns, config.measurement_iterations, avg};
}

// ---- Fix 1: getLockIndex modulo vs bitmask ----------------------------------

static const int CONCURRENCY_LEVEL = 16;

static volatile uint32_t sink; // prevent optimisation of result

void benchmarkGetLockIndex() {
    std::cout << "\n=== Fix 1: getLockIndex  (% vs &) ===" << std::endl;

    std::mt19937 rng(42);
    std::vector<int> tids(config.measurement_iterations);
    for (auto &t : tids) {
        t = static_cast<int>(rng());
    }

    results.push_back(runBenchmark("getLockIndex (modulo %)", [&](int i) {
        uint32_t lock_index = static_cast<uint32_t>(tids[i]);
        lock_index ^= lock_index >> 8;
        lock_index ^= lock_index >> 4;
        sink = lock_index % CONCURRENCY_LEVEL;
    }));

    results.push_back(runBenchmark("getLockIndex (bitmask &)", [&](int i) {
        uint32_t lock_index = static_cast<uint32_t>(tids[i]);
        lock_index ^= lock_index >> 8;
        lock_index ^= lock_index >> 4;
        sink = lock_index & (CONCURRENCY_LEVEL - 1);
    }));
}

// ---- Fix 5: findLibraryByAddress  linear scan vs last-hit-index cache -------

struct FakeLib {
    uintptr_t min_addr;
    uintptr_t max_addr;
    int       id;

    bool contains(uintptr_t addr) const {
        return addr >= min_addr && addr < max_addr;
    }
};

// 128 simulated loaded libraries, 64 KiB each, contiguous
static const int NUM_LIBS = 128;
static const uintptr_t LIB_SIZE = 64 * 1024;
static FakeLib fake_libs[NUM_LIBS];

static void initFakeLibs() {
    uintptr_t base = 0x7f0000000000ULL;
    for (int i = 0; i < NUM_LIBS; i++) {
        fake_libs[i] = {base, base + LIB_SIZE, i};
        base += LIB_SIZE;
    }
}

// Baseline: O(N) linear scan every call
static const FakeLib *findLibLinear(uintptr_t addr) {
    for (int i = 0; i < NUM_LIBS; i++) {
        if (fake_libs[i].contains(addr)) {
            return &fake_libs[i];
        }
    }
    return nullptr;
}

// Optimized: signal-safe static last-hit index (no DTLS allocation)
static volatile int last_hit_idx = 0;

static const FakeLib *findLibLastHit(uintptr_t addr) {
    int hint = last_hit_idx;
    if (hint < NUM_LIBS && fake_libs[hint].contains(addr)) {
        return &fake_libs[hint];
    }
    for (int i = 0; i < NUM_LIBS; i++) {
        if (fake_libs[i].contains(addr)) {
            last_hit_idx = i;
            return &fake_libs[i];
        }
    }
    return nullptr;
}

void benchmarkFindLibrary() {
    initFakeLibs();
    std::cout << "\n=== Fix 5: findLibraryByAddress  (linear vs last-hit index) ===" << std::endl;

    std::mt19937 rng(42);

    // Hot case: same lib repeatedly (models deep native stacks in one library)
    const uintptr_t hot_lib_base = fake_libs[NUM_LIBS / 2].min_addr;
    std::vector<uintptr_t> hot_addrs(config.measurement_iterations);
    for (auto &a : hot_addrs) {
        a = hot_lib_base + (rng() % LIB_SIZE);
    }

    // Cold case: uniform random across all libs
    std::vector<uintptr_t> cold_addrs(config.measurement_iterations);
    for (auto &a : cold_addrs) {
        int lib_idx = rng() % NUM_LIBS;
        a = fake_libs[lib_idx].min_addr + (rng() % LIB_SIZE);
    }

    static volatile int id_sink;

    // Hot addresses
    results.push_back(runBenchmark("findLib linear (hot)", [&](int i) {
        const FakeLib *lib = findLibLinear(hot_addrs[i]);
        if (lib) id_sink = lib->id;
    }));

    last_hit_idx = 0;
    results.push_back(runBenchmark("findLib last-hit idx (hot)", [&](int i) {
        const FakeLib *lib = findLibLastHit(hot_addrs[i]);
        if (lib) id_sink = lib->id;
    }));

    // Cold addresses
    results.push_back(runBenchmark("findLib linear (cold)", [&](int i) {
        const FakeLib *lib = findLibLinear(cold_addrs[i]);
        if (lib) id_sink = lib->id;
    }));

    last_hit_idx = 0;
    results.push_back(runBenchmark("findLib last-hit idx (cold)", [&](int i) {
        const FakeLib *lib = findLibLastHit(cold_addrs[i]);
        if (lib) id_sink = lib->id;
    }));
}

// ---- Fix 6: reservoir sample vector copy vs reference -----------------------

void benchmarkReservoirSample() {
    std::cout << "\n=== Fix 6: reservoir sample  (copy vs reference) ===" << std::endl;

    const int RESERVOIR_SIZE = 512;
    std::vector<int> threads(RESERVOIR_SIZE * 4);
    std::iota(threads.begin(), threads.end(), 1);

    // Simulate reservoir: pre-filled vector returned by value vs by reference
    std::vector<int> reservoir(RESERVOIR_SIZE);
    std::iota(reservoir.begin(), reservoir.end(), 1);

    // Baseline: copy (what the old code did — returns by value)
    auto sampleByCopy = [&]() -> std::vector<int> {
        return reservoir; // copy
    };

    // Optimized: reference (no allocation)
    auto sampleByRef = [&]() -> std::vector<int>& {
        return reservoir;
    };

    static volatile int elem_sink;

    results.push_back(runBenchmark("reservoir sample (copy)", [&](int) {
        std::vector<int> s = sampleByCopy();
        elem_sink = s[0];
    }));

    results.push_back(runBenchmark("reservoir sample (reference)", [&](int) {
        std::vector<int>& s = sampleByRef();
        elem_sink = s[0];
    }));
}

// ---- main -------------------------------------------------------------------

void printUsage(const char *prog) {
    std::cout << "Usage: " << prog << " [--warmup N] [--iterations N] [--csv FILE] [--json FILE]\n";
}

void exportCSV(const std::string &filename) {
    FILE *f = fopen(filename.c_str(), "w");
    if (!f) { std::cerr << "Cannot open " << filename << "\n"; return; }
    fprintf(f, "Benchmark,Total Time (ns),Iterations,Average Time (ns)\n");
    for (const auto &r : results) {
        fprintf(f, "%s,%lld,%d,%.3f\n", r.name.c_str(), r.total_time_ns, r.iterations, r.avg_time_ns);
    }
    fclose(f);
    std::cout << "Results written to " << filename << "\n";
}

void exportJSON(const std::string &filename) {
    FILE *f = fopen(filename.c_str(), "w");
    if (!f) { std::cerr << "Cannot open " << filename << "\n"; return; }
    fprintf(f, "{\n  \"benchmarks\": [\n");
    for (size_t i = 0; i < results.size(); i++) {
        const auto &r = results[i];
        fprintf(f, "    {\"name\":\"%s\",\"total_time_ns\":%lld,\"iterations\":%d,\"avg_time_ns\":%.3f}%s\n",
                r.name.c_str(), r.total_time_ns, r.iterations, r.avg_time_ns,
                i + 1 < results.size() ? "," : "");
    }
    fprintf(f, "  ]\n}\n");
    fclose(f);
    std::cout << "Results written to " << filename << "\n";
}

int main(int argc, char *argv[]) {
    std::string csv_file, json_file;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc) {
            config.warmup_iterations = std::atoi(argv[++i]);
        } else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
            config.measurement_iterations = std::atoi(argv[++i]);
        } else if (strcmp(argv[i], "--csv") == 0 && i + 1 < argc) {
            csv_file = argv[++i];
        } else if (strcmp(argv[i], "--json") == 0 && i + 1 < argc) {
            json_file = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    std::cout << "=== Hot-path optimization benchmarks ===\n";
    std::cout << "warmup=" << config.warmup_iterations
              << "  iterations=" << config.measurement_iterations << "\n";

    benchmarkGetLockIndex();
    benchmarkFindLibrary();
    benchmarkReservoirSample();

    std::cout << "\n=== Summary ===\n";
    for (const auto &r : results) {
        printf("  %-45s  %.3f ns/op\n", r.name.c_str(), r.avg_time_ns);
    }

    if (!csv_file.empty())  exportCSV(csv_file);
    if (!json_file.empty()) exportJSON(json_file);

    return 0;
}
