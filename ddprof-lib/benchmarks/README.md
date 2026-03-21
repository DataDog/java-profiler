# DDProf Benchmarks

This directory contains various benchmarks and performance tests for the Java profiler.

## Available Benchmarks

### branch-prediction/

Performance testing for branch prediction hints (likely/unlikely) using perf and Renaissance benchmarks.

See [branch-prediction/PERF_TESTING.md](branch-prediction/PERF_TESTING.md) for detailed usage instructions.

Quick start:
```bash
cd branch-prediction
./test_branch_prediction_perf.sh
```

## Requirements

- Linux with perf support (bare metal or appropriate VM instance type)
- Java 8 or later
- Built profiler library (run `./gradlew ddprof-lib:build` from repository root)

## Adding New Benchmarks

When adding new benchmarks to this directory:

1. Create a subdirectory with a descriptive name
2. Include a README or detailed documentation
3. Make scripts executable and self-contained
4. Auto-download dependencies when possible
5. Update this README with a brief description
