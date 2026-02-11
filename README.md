# Datadog Java Profiler Library
_Based on [async-profiler 2.8.3](https://github.com/jvm-profiling-tools/java-profiler/releases/tag/v2.8.3)_

## Disclaimer
This is not a fork of [async-profiler](https://github.com/jvm-profiling-tools/async-profiler). This is a work derived from __async-profiler__ but tailored very specifically for Datadog needs.
See [gritty details](#gritty-details) for more info.
If you need a full-fledged Java profiler head back to [async-profiler](https://github.com/jvm-profiling-tools/async-profiler)

## Build

### Prerequisites
1. JDK 8 or later (required for building)
2. Gradle (included in wrapper)
3. C++ compiler (clang++ preferred, g++ supported)
   - Build system auto-detects clang++ or g++
   - Override with: `./gradlew build -Pnative.forceCompiler=g++`
4. Make (included in XCode on Macos)
5. Google Test (for unit testing)
   - On Ubuntu/Debian: `sudo apt install libgtest-dev`
   - On macOS: `brew install googletest`
   - On Alpine: `apk add gtest-dev`
6. clang-format 11 (for code formatting)
   - On Ubuntu/Debian: `sudo apt install clang-format-11`
   - On macOS: `brew install clang-format@11`
   - On Alpine: `apk add clang-format-11`

### Building the Project
1. Clone the repository:
```bash
git clone https://github.com/DataDog/java-profiler.git
cd java-profiler
```

2. Build a release version of the project:
```bash
./gradlew buildRelease
```

The resulting artifact will be in `ddprof-lib/build/libs/ddprof-<version>.jar`

#### Gritty details
Since the upstream code might not be 100% compatible with the current version of the project, we extend the base classes
with Datadog-specific functionality. These extensions are integrated directly into the base files (e.g., `stackWalker.h`)
with optional parameters and backward-compatible interfaces.

See [ddprof-lib/src/main/cpp/stackWalker.h](ddprof-lib/src/main/cpp/stackWalker.h) for an example of how we extend the upstream code with additional features like truncation detection.

## Claude Code Integration

This project includes Claude Code commands for streamlined development workflows when using [Claude Code](https://claude.ai/code):

### Available Commands

#### `/build-and-summarize <gradle-tasks...>`
Automated build execution with intelligent log analysis:
```bash
# Build with automated analysis
/build-and-summarize buildRelease

# Run tests with summary
/build-and-summarize testDebug

# Custom gradle tasks
/build-and-summarize clean buildDebug testDebug
```

**Features:**
- Executes Gradle builds with appropriate logging (`-i --console=plain`)
- Captures timestamped build logs in `build/logs/`
- Automatically analyzes build results using the gradle-logs-analyst agent
- Generates structured reports: `build/reports/claude/gradle-summary.md` and `build/reports/claude/gradle-summary.json`
- Extracts key information: build status, failed tasks, test results, warnings, and performance metrics

#### `/compare-and-patch <filename>`
Upstream/local file comparison and patch analysis:
```bash
# Analyze differences between upstream and local versions
/compare-and-patch stackFrame.h
/compare-and-patch symbols.cpp
/compare-and-patch buffers.h
```

**Features:**
- Automatically resolves upstream (`ddprof-lib/build/async-profiler/src/`) and local (`ddprof-lib/src/main/cpp/`) file paths
- Intelligently compares files while ignoring newline and copyright-only changes
- Uses the patch-analyst agent to generate comprehensive analysis
- Creates structured patch reports: `build/reports/claude/patches/<file>.patch.json` and `build/reports/claude/patches/<file>.patch.md`
- Identifies required patch operations compatible with the unified patching system
- Handles cases where files are Datadog-specific additions with no upstream equivalent

### Integration Benefits

These commands complement the existing patching workflow by providing:
- **Automated Analysis**: Intelligent parsing of build logs and patch requirements
- **Structured Output**: Machine-readable JSON and human-readable Markdown reports
- **Consistency**: Standardized analysis format across all patch operations
- **Efficiency**: Streamlined workflow for patch development and maintenance
- **Documentation**: Automatic generation of patch documentation

### Usage in Development Workflow

1. **Build Analysis**: Use `/build-and-summarize` to quickly identify build issues and performance bottlenecks
2. **Patch Development**: Use `/compare-and-patch` to analyze upstream changes and generate patch requirements
3. **Maintenance**: Regular patch analysis helps maintain compatibility with upstream updates

The generated reports integrate seamlessly with the existing `gradle/patching.gradle` configuration system, making it easier to maintain and update patches as the upstream codebase evolves.

## Testing

### Unit Tests
The project includes both Java and C++ unit tests. You can run them using:

```bash
# Run all tests
./gradlew test

# Run specific test configurations
./gradlew testRelease  # Run release build tests
./gradlew testDebug    # Run debug build tests
./gradlew testAsan     # Run tests with ASan
./gradlew testTsan     # Run tests with TSan

# Run C++ unit tests only
./gradlew gtestDebug   # Run C++ tests in debug mode
./gradlew gtestRelease # Run C++ tests in release mode
```

### Test Options
- Skip all tests: `./gradlew build -Pskip-tests`
- Keep JFR recordings: `./gradlew test -PkeepJFRs`
- Skip native build: `./gradlew build -Pskip-native`
- Skip C++ tests: `./gradlew build -Pskip-gtest`

### Cross-JDK Testing
`JAVA_TEST_HOME=<path to test JDK> ./gradlew testDebug`

### Docker-Based Testing (musl/glibc)
Run tests in Docker containers to test on different libc implementations. Uses two-level Docker image caching for fast subsequent runs:
1. **Base image** (`java-profiler-base:<libc>-<arch>`) - OS with all build tools + sanitizers
2. **JDK image** (`java-profiler-test:<libc>-jdk<version>-<arch>`) - Adds JDK + Gradle

By default, the script clones the repository at the current commit for clean builds. Use `--mount` to mount the local directory instead (faster but may have stale artifacts).

```bash
# Run specific test on musl (Alpine) with JDK 21 (clone mode - clean build)
./utils/run-docker-tests.sh --libc=musl --jdk=21 --tests="CTimerGCStressTest"

# Run all tests on glibc (Ubuntu) with JDK 17
./utils/run-docker-tests.sh --libc=glibc --jdk=17

# Run tests on aarch64 architecture (requires Docker with multi-arch support)
./utils/run-docker-tests.sh --libc=musl --jdk=21 --arch=aarch64

# Mount local repo for faster iteration (may have stale artifacts)
./utils/run-docker-tests.sh --libc=musl --jdk=21 --mount --tests="MyTest"

# Drop to interactive shell in musl container
./utils/run-docker-tests.sh --libc=musl --jdk=21 --shell

# Force rebuild of all cached Docker images
./utils/run-docker-tests.sh --libc=musl --jdk=21 --rebuild

# Force rebuild of base image only (useful after Alpine/Ubuntu updates)
./utils/run-docker-tests.sh --libc=musl --rebuild-base

# Show options
./utils/run-docker-tests.sh --help
```

Supported options:
- `--libc=glibc|musl` (default: glibc)
- `--jdk=8|11|17|21|25` (default: 21)
- `--arch=x64|aarch64` (default: auto-detect)
- `--config=debug|release` (default: debug)
- `--tests="TestPattern"`
- `--gtest` (enable C++ gtests, disabled by default for faster runs)
- `--shell` (interactive shell instead of running tests)
- `--mount` (mount local repo instead of cloning - faster but may have stale artifacts)
- `--rebuild` (force rebuild of all Docker images)
- `--rebuild-base` (force rebuild of base image only)

## Unwinding Validation Tool

The project includes a comprehensive unwinding validation tool that tests JIT compilation unwinding scenarios to detect stack frame issues. This tool validates the profiler's ability to correctly unwind stack frames during complex JIT compilation scenarios.

### Running the Unwinding Validator

```bash
# Run all unwinding validation scenarios (release or debug build required)
./gradlew :ddprof-test:runUnwindingValidator

# Run specific scenario
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--scenario=C2CompilationTriggers"

# Generate markdown report for CI
./gradlew :ddprof-test:unwindingReport

# Show available options
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--help"
```

### Available Scenarios

The validator includes 13 specialized scenarios targeting different unwinding challenges:

- **C2CompilationTriggers** - Heavy computational workloads that trigger C2 compilation
- **OSRScenarios** - On-Stack Replacement compilation scenarios
- **ConcurrentC2Compilation** - Concurrent C2 compilation stress testing
- **C2DeoptScenarios** - C2 deoptimization and transition edge cases
- **ExtendedJNIScenarios** - Extended JNI operation patterns
- **MultipleStressRounds** - Multiple concurrent stress rounds
- **ExtendedPLTScenarios** - PLT (Procedure Linkage Table) resolution scenarios
- **ActivePLTResolution** - Intensive PLT resolution during profiling
- **ConcurrentCompilationStress** - Heavy JIT compilation + native activity
- **VeneerHeavyScenarios** - ARM64 veneer/trampoline intensive workloads
- **RapidTierTransitions** - Rapid compilation tier transitions
- **DynamicLibraryOps** - Dynamic library operations during profiling
- **StackBoundaryStress** - Stack boundary stress scenarios

### Output Formats

The validator supports multiple output formats:

```bash
# Text output (default)
./gradlew :ddprof-test:runUnwindingValidator

# JSON format for programmatic analysis
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--output-format=json --output-file=unwinding-report.json"

# Markdown format for documentation
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--output-format=markdown --output-file=unwinding-report.md"
```

### CI Integration

The unwinding validator is automatically integrated into GitHub Actions CI pipeline:

- Runs only on **debug builds** in CI (provides clean measurements without optimization interference)
- Generates rich markdown reports displayed directly in job summaries
- Creates downloadable report artifacts for historical analysis
- Fails builds when critical unwinding issues are detected

The validator provides immediate visibility into unwinding quality across all supported platforms and Java versions without requiring artifact downloads.

### Understanding Results

The tool analyzes JFR (Java Flight Recorder) data to measure:

- **Error Rate** - Percentage of samples with unwinding failures (`.unknown()`, `.break_interpreted()`)
- **Native Coverage** - Percentage of samples successfully unwound in native code
- **Sample Count** - Total profiling samples captured during validation
- **Error Types** - Breakdown of specific unwinding failure patterns

Results are categorized as:
- 🟢 **Excellent** - Error rate < 0.1%
- 🟢 **Good** - Error rate < 1.0%
- 🟡 **Moderate** - Error rate < 5.0%
- 🔴 **Needs Work** - Error rate ≥ 5.0%

## Release Builds and Debug Information

### Split Debug Information
Release builds automatically generate split debug information to optimize deployment size while preserving debugging capabilities:

- **Stripped libraries** (~1.2MB): Production-ready binaries with symbols removed for deployment
- **Debug symbol files** (~6.1MB): Separate `.debug` files containing full debugging information
- **Debug links**: Stripped libraries include `.gnu_debuglink` sections pointing to debug files

### Build Artifacts Structure
```
ddprof-lib/build/
├── lib/main/release/linux/x64/
│   ├── libjavaProfiler.so              # Original library with debug symbols
│   ├── stripped/
│   │   └── libjavaProfiler.so          # Stripped library (83% smaller)
│   └── debug/
│       └── libjavaProfiler.so.debug    # Debug symbols only
├── native/release/
│   └── META-INF/native-libs/linux-x64/
│       └── libjavaProfiler.so          # Final stripped library (deployed)
└── native/release-debug/
    └── META-INF/native-libs/linux-x64/
        └── libjavaProfiler.so.debug    # Debug symbols package
```

### Build Options
- **Skip debug extraction**: `./gradlew buildRelease -Pskip-debug-extraction=true`
- **Debug extraction requires**: `objcopy` (Linux) or `dsymutil` (macOS)
  - Ubuntu/Debian: `sudo apt-get install binutils`
  - Alpine: `apk add binutils`
  - macOS: Included with Xcode command line tools

### Compiler Selection
The build system automatically detects the best available C++ compiler (prefers clang++, falls back to g++).

```bash
# Auto-detection (default)
./gradlew build

# Force specific compiler
./gradlew build -Pnative.forceCompiler=clang++
./gradlew build -Pnative.forceCompiler=g++
./gradlew build -Pnative.forceCompiler=/usr/bin/g++-13

# Test with specific compiler
./gradlew testDebug -Pnative.forceCompiler=g++
```

This is useful for:
- **Reproducibility**: Ensure builds use the same compiler across machines
- **clang-only systems**: macOS with Xcode but no gcc (sanitizer builds work)
- **Testing**: Verify code compiles with both gcc and clang

## Development

### Code Quality
The project uses several tools for code quality:

1. clang-format for C++ code formatting
2. scan-build for static analysis
3. cppcheck for additional C++ checks

Run code quality checks:
```bash
# Run scan-build (this will use the scan-build binary)
./gradlew scanBuild

# Run cppcheck (if configured)
./gradlew cppcheck

# Run spotless (including code formatting)
./gradlew spotlessApply
```

### Debugging
**!TODO!**

### Stress Tests
The project includes JMH-based stress tests:

```bash
# Run all stress tests
./gradlew :ddprof-stresstest:runStressTests

### Common Issues
1. If you encounter strange crashes Asan:
   ```bash
   sudo sysctl vm.mmap_rnd_bits=28
   ```

2. For ASan/TSan issues, ensure you have the required libraries installed:
   - ASan: `libasan`
   - TSan: `libtsan`

## Architectural Tidbits

This section documents important architectural decisions and enhancements made to the profiler core.

### Critical Section Management (2025)

Introduced race-free critical section management using atomic compare-and-swap operations instead of expensive signal blocking syscalls:

- **`CriticalSection` class**: Thread-local atomic flag-based protection against signal handler reentrancy
- **Lock-free design**: Uses `compare_exchange_strong` for atomic claiming of critical sections
- **Signal handler safety**: Eliminates race conditions between signal handlers and normal code execution
- **Performance improvement**: Avoids costly `sigprocmask`/`pthread_sigmask` syscalls in hot paths

**Key files**: `criticalSection.h`, `criticalSection.cpp`

### Triple-Buffered Call Trace Storage (2025)

Enhanced the call trace storage system from double-buffered to triple-buffered architecture with hazard pointer-based memory reclamation:

- **Triple buffering**: Active, standby, and cleanup storage rotation for smoother transitions
- **Hazard pointer system**: Per-instance thread-safe memory reclamation without global locks
- **ABA protection**: Generation counter prevents race conditions during table swaps
- **Instance-based trace IDs**: 64-bit IDs combining instance ID and slot for collision-free trace management
- **Lock-free hot paths**: Atomic operations minimize contention during profiling events

**Key changes**:
- Replaced `SpinLock` with atomic pointers and hazard pointer system
- Added generation counter for safe table swapping
- Enhanced liveness preservation across storage rotations
- Improved thread safety for high-frequency profiling scenarios

**Key files**: `callTraceStorage.h`, `callTraceStorage.cpp`, `callTraceHashTable.h`, `callTraceHashTable.cpp`

### Enhanced Testing Infrastructure (2025)

Comprehensive testing improvements for better debugging and stress testing:

- **GTest crash handler**: Detailed crash reporting with backtraces and register state for native code failures
- **Stress testing framework**: Multi-threaded stress tests for call trace storage under high contention
- **Platform-specific debugging**: macOS and Linux register state capture in crash handlers
- **Async-signal-safe reporting**: Crash handlers use only signal-safe functions for reliable diagnostics

**Key files**: `gtest_crash_handler.h`, `stress_callTraceStorage.cpp`

### TLS Priming Enhancements (2025)

Improved thread-local storage initialization to prevent race conditions:

- **Solid TLS priming**: Enhanced thread-local variable initialization timing
- **Signal handler compatibility**: Ensures TLS is fully initialized before signal handler access
- **Cross-platform consistency**: Unified TLS handling across Linux and macOS platforms

These architectural improvements focus on eliminating race conditions, improving performance in high-throughput scenarios, and providing better debugging capabilities for the native profiling engine.

### Remote Symbolication Support (2025)

Added support for remote symbolication to enable offloading symbol resolution from the agent to backend services:

- **Build-ID extraction**: Automatically extracts GNU build-id from ELF binaries on Linux
- **Raw addressing information**: Stores build-id and PC offset instead of resolved symbol names
- **Remote symbolication mode**: Enable with `remotesym=true` profiler argument
- **JFR integration**: Remote frames serialized with build-id and offset for backend resolution
- **Zero encoding overhead**: Uses dedicated frame type (FRAME_NATIVE_REMOTE) for efficient serialization

**Benefits**:
- Reduces agent overhead by eliminating local symbol resolution
- Enables centralized symbol resolution with better caching
- Supports scenarios where debug symbols are not available locally

**Key files**: `elfBuildId.h`, `elfBuildId.cpp`, `profiler.cpp`, `flightRecorder.cpp`

For detailed documentation, see [doc/RemoteSymbolication.md](doc/plans/RemoteSymbolication.md).

## Contributing
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run tests: `./gradlew test`
5. Submit a pull request

## License
This project is licensed under the Apache License 2.0 - see the LICENSE file for details.

## Usage

### Example

Download the latest version of dd-trace-java and add `-Ddd.profiling.ddprof.debug.lib`. Example of a command line:
```bash
DD_SERVICE=your-service DD_TRACE_DEBUG=true java -javaagent:./temp/dd-java-agent.jar -Ddd.profiling.enabled=true -Ddd.profiling.ddprof.enabled=true -Ddd.profiling.ddprof.liveheap.enabled=true -Ddd.profiling.upload.period=10 -Ddd.profiling.start-force-first=true -Ddd.profiling.ddprof.debug.lib=~/dd/java-profiler/ddprof-lib/build/lib/main/debug/linux/x64/libjavaProfiler.so -XX:ErrorFile=${PWD}/hs_err_pid%p.log -XX:OnError='java -jar temp/dd-java-agent.jar uploadCrash hs_err_pid%p.log' -jar ./temp/renaissance-gpl-0.15.0.jar akka-uct -r 5
```

### Consuming the artifact

For dd-trace-java you just need to set the `ddprof.jar` project property.
Eg. you can run the gradle build like this - ./gradlew clean -Pddprof.jar=file://<path-to-artifact.jar> :dd-java-agent:shadowJar` - which will result in a custom `dd-java-agent.jar` build containing your test version of Java profiler.
