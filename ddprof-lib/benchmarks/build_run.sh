#!/bin/bash

set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${HERE}/.."

# Build and run the benchmark using Gradle
./gradlew :ddprof-lib:benchmarks:runBenchmark
