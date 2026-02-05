# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is the Datadog Java Profiler Library, a specialized profiler derived from async-profiler but tailored for Datadog's needs. It's a multi-language project combining Java, C++, and Gradle build system with native library compilation.

**Key Technologies:**
- Java 8+ (main API and library loading)
- C++17 (native profiling engine)
- Gradle (build system with custom native compilation tasks)
- JNI (Java Native Interface for C++ integration)
- Google Test (for C++ unit tests, compiled via custom Gradle tasks)

## Project Operating Guide for Claude (Main Session)

You are the **Main Orchestrator** for this repository.

### Goals
- When I ask you to build, you MUST:
    1) run the Gradle task with plain console and increased verbosity,
    2) capture stdout into `build/logs/<timestamp>-<task>.log`,
    3) **delegate** parsing to the sub-agent `gradle-log-analyst`,
    4) respond in chat with only a short status and the two output file paths:
        - `build/reports/claude/gradle-summary.md`
        - `build/reports/claude/gradle-summary.json`

### Rules
- **Never** paste large log chunks into the chat.
- Prefer shell over long in-chat output. If more than ~30 lines are needed, write to a file.
- If no log path is provided, use the newest `build/logs/*.log`.
- Assume macOS/Linux unless I explicitly say Windows; if Windows, use PowerShell equivalents.
- If a step fails, print the failing command and a one-line hint, then stop.

### Implementation Hints for You
- For builds, always use: `--console=plain -i` (or `-d` if I ask for debug).
- Use `mkdir -p build/logs build/reports/claude` before writing.
- Timestamp format: `$(date +%Y%m%d-%H%M%S)`.
- After the build finishes, call the sub-agent like:
  “Use `gradle-log-analyst` to parse LOG_PATH; write the two reports; reply with only a 3–6 line status and the two relative file paths.”

### Shortcuts I Expect
- `./gradlew <gradle-task...>` to do everything in one step.
- If I just say “build assembleDebugJar”, interpret that as the shortcut above.

## Build Commands
Never use 'gradle' or 'gradlew' directly. Instead, use the '/build-and-summarize' command.

### Main Build Tasks
```bash
# Build release version (primary artifact)
./gradlew buildRelease

# Build all configurations
./gradlew assembleAll

# Clean build
./gradlew clean
```

### Development Builds
```bash
# Debug build with symbols
./gradlew buildDebug

# ASan build (if available)
./gradlew buildAsan

# TSan build (if available)
./gradlew buildTsan
```

### Testing
```bash
# Run specific test configurations
./gradlew testRelease
./gradlew testDebug
./gradlew testAsan
./gradlew testTsan

# Run C++ unit tests only
./gradlew gtestDebug
./gradlew gtestRelease

# Cross-JDK testing
JAVA_TEST_HOME=/path/to/test/jdk ./gradlew testDebug
```

### Build Options
```bash
# Skip native compilation
./gradlew buildDebug -Pskip-native

# Skip all tests
./gradlew buildDebug -Pskip-tests

# Skip C++ tests
./gradlew buildDebug -Pskip-gtest

# Keep JFR recordings after tests
./gradlew testDebug -PkeepJFRs

# Skip debug symbol extraction
./gradlew buildRelease -Pskip-debug-extraction=true
```

### Code Quality
```bash
# Format code
./gradlew spotlessApply

# Static analysis
./gradlew scanBuild

# Run stress tests
./gradlew :ddprof-stresstest:runStressTests

# Run benchmarks
./gradlew runBenchmarks
```

## Architecture

### Module Structure
- **ddprof-lib**: Main profiler library (Java + C++)
- **ddprof-test**: Integration tests
- **ddprof-test-tracer**: Tracing context tests
- **ddprof-stresstest**: JMH-based performance tests
- **malloc-shim**: Memory allocation interceptor (Linux only)

### Build Configurations
The project supports multiple build configurations per platform:
- **release**: Optimized production build with stripped symbols
- **debug**: Debug build with full symbols
- **asan**: AddressSanitizer build for memory error detection
- **tsan**: ThreadSanitizer build for thread safety validation

### Key Source Locations
- Java API: `ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java`
- C++ engine: `ddprof-lib/src/main/cpp/`
- Native libraries: `ddprof-lib/build/lib/main/{config}/{os}/{arch}/`
- Test resources: `ddprof-test/src/test/java/`

### Platform Support
- **Linux**: x64, arm64 (primary platforms)
- **macOS**: arm64, x64
- **Architecture detection**: Automatic via `common.gradle`
- **musl libc detection**: Automatic detection and handling

### Debug Information Handling
Release builds automatically extract debug symbols:
- Stripped libraries (~1.2MB) for production
- Separate debug files (~6.1MB) with full symbols
- GNU debuglink sections connect stripped libraries to debug files

## Development Workflow

### Running Single Tests
Use standard Gradle syntax:
```bash
./gradlew :ddprof-test:test --tests "ClassName.methodName"
```

### Working with Native Code
Native compilation is automatic during build. C++ code changes require:
1. Full rebuild: `/build-and-summarize clean build`
2. The build system automatically handles JNI headers and platform detection

### Debugging Native Issues
- Use `buildDebug` for debug symbols
- Use `buildAsan` for memory error detection
- Check `gradle/sanitizers/*.supp` for suppressions
- Set `sudo sysctl vm.mmap_rnd_bits=28` if ASan crashes occur

### Cross-Platform Development
- Use `osIdentifier()` and `archIdentifier()` functions for platform detection
- Platform-specific code goes in `os_linux.cpp`, `os_macos.cpp`, etc.
- Build configurations automatically select appropriate compiler/linker flags

## Publishing and Artifacts

The main artifact is `ddprof-<version>.jar` containing:
- Java classes
- Native libraries for all supported platforms
- Metadata for library loading

Build artifacts structure:
```
ddprof-lib/build/
├── lib/main/{config}/{os}/{arch}/
│   ├── libjavaProfiler.{so|dylib}     # Full library
│   ├── stripped/ → production binary
│   └── debug/ → debug symbols
└── native/{config}/META-INF/native-libs/
    └── {os}-{arch}/ → final packaged libraries
```

## Core Architecture Components

### Double-Buffered Call Trace Storage
The profiler uses a sophisticated double-buffered storage system for call traces:
- **Active Storage**: Currently accepting new traces from profiling events
- **Standby Storage**: Background storage for JFR serialization and trace preservation
- **Instance-based Trace IDs**: 64-bit IDs combining instance ID (upper 32 bits) and slot (lower 32 bits)
- **Liveness Checkers**: Functions that determine which traces to preserve across storage swaps
- **Atomic Swapping**: Lock-free swap operations to minimize profiling overhead

### JFR Integration Architecture
- **FlightRecorder**: Central JFR event recording and buffer management
- **Metadata Generation**: Dynamic JFR metadata for stack traces, methods, and classes
- **Constant Pools**: Efficient deduplication of strings, methods, and stack traces
- **Buffer Management**: Thread-local recording buffers with configurable flush thresholds

### Native Integration Patterns
- **Signal Handler Safety**: Careful memory management in signal handler contexts

### Multi-Engine Profiling System
- **CPU Profiling**: SIGPROF-based sampling with configurable intervals
- **Wall Clock**: SIGALRM-based sampling for blocking I/O and sleep detection
- **Allocation Profiling**: TLAB-based allocation tracking and sampling
- **Live Heap**: Object liveness tracking with weak references and GC integration

## Critical Implementation Details

### Thread Safety and Performance
- **Lock-free Hot Paths**: Signal handlers avoid blocking operations
- **Thread-local Buffers**: Per-thread recording buffers minimize contention
- **Atomic Operations**: Instance ID management and counter updates use atomics
- **Memory Allocation**: Minimize malloc() in hot paths, use pre-allocated containers

### 64-bit Trace ID System
- **Collision Avoidance**: Instance-based IDs prevent collisions across storage swaps
- **JFR Compatibility**: 64-bit IDs work with JFR constant pool indices
- **Stability**: Trace IDs remain stable during liveness preservation
- **Performance**: Bit-packing approach avoids atomic operations in hot paths

### Platform-Specific Handling
- **musl libc Detection**: Automatic detection and symbol resolution adjustments
- **Architecture Support**: x64, arm64 with architecture-specific stack walking
- **Debug Symbol Handling**: Split debug information for production deployments

## Development Guidelines

### Code Organization Principles
- **Code Integration**: Datadog-specific extensions are integrated directly into base files (e.g., `stackWalker.h`)
- **External Dependencies**: Local code in `cpp/`

### Performance Constraints
- **Algorithmic Complexity**: Use O(N) or better, max 256 elements for linear scans
- **Memory Fragmentation**: Minimize allocations to avoid malloc arena issues
- **Signal Handler Safety**: No blocking operations, mutex locks, or malloc() in handlers

### Testing Strategy
- **Multi-configuration Testing**: Test across debug, release, ASan, and TSan builds
- **Cross-JDK Compatibility**: Test with Oracle JDK, OpenJDK, and OpenJ9
- **Native-Java Integration**: Both C++ unit tests (gtest) and Java integration tests
- **Stress Testing**: JMH-based performance and stability testing

### Debugging and Analysis
- **Debug Builds**: Use `buildDebug` for full symbols and debugging information
- **Sanitizer Builds**: ASan for memory errors, TSan for threading issues
- **Static Analysis**: `scanBuild` for additional code quality checks
- **Test Logging**: Use `TEST_LOG` macro for debug output in tests

## Build System Architecture

### Gradle Multi-project Structure
- **ddprof-lib**: Core profiler with native compilation
- **ddprof-test**: Integration and Java unit tests
- **ddprof-test-tracer**: Tracing context integration tests
- **ddprof-stresstest**: JMH performance benchmarks
- **malloc-shim**: Linux memory allocation interceptor

### Native Compilation Pipeline
- **Platform Detection**: Automatic OS and architecture detection via `common.gradle`
- **Configuration Matrix**: Multiple build configs (release/debug/asan/tsan) per platform
- **Symbol Processing**: Automatic debug symbol extraction for release builds
- **Library Packaging**: Final JAR contains all platform-specific native libraries

### Custom Native Build Tasks (buildSrc)
The project uses custom Gradle task types in `buildSrc/` instead of Gradle's `cpp-library` and `cpp-application` plugins. This is intentional:

**Why not cpp-library/cpp-application plugins:**
- Gradle's native plugins parse compiler version strings which breaks with newer gcc/clang versions
- JNI header detection has issues with non-standard JAVA_HOME layouts
- Plugin maintainers are unresponsive to fixes
- The plugins use undocumented internals that change between Gradle versions

**Custom task types:**
- `SimpleCppCompile` - Parallel C++ compilation, directly invokes gcc/clang
- `SimpleLinkShared` - Links shared libraries (.so/.dylib)
- `SimpleLinkExecutable` - Links executables (for gtest, fuzz targets)
- `CompilerUtils` - Simple compiler detection (PATH lookup, no version parsing)

**Key principle:** Direct compiler invocation without version parsing. The tasks simply find `clang++` or `g++` on PATH and invoke them with the flags from `gradle/configurations.gradle`.

### Artifact Structure
Final artifacts maintain a specific structure for deployment:
```
META-INF/native-libs/{os}-{arch}/libjavaProfiler.{so|dylib}
```
With separate debug symbol packages for production debugging support.

## Legacy and Compatibility

- Java 8 compatibility maintained throughout
- JNI interface follows async-profiler conventions
- Supports Oracle JDK, OpenJDK and OpenJ9 implementations
- Always test with /build-and-summarize testDebug
- Always consult openjdk source codes when analyzing profiler issues and looking for proposed solutions
- For OpenJ9 specific issues consul the openj9 github project
- don't use assemble task. Use assembleDebug or assembleRelease instead
- gtest tests are located in ddprof-lib/src/test/cpp
- Module ddprof-lib/gtest is only containing the gtest build setup
- Java unit tests are in ddprof-test module
- Always run /build-and-summarize spotlessApply before commiting the changes

- When you are adding copyright - like 'Copyright 2021, 2023 Datadog, Inc' do the current year -> 'Copyright <current year>, Datadog, Inc'
  When you are modifying copyright already including 'Datadog' update the 'until year' ('Copyright from year, until year') to the current year
- If modifying a file that does not contain Datadog copyright, add one
- When proposing solutions try minimizing allocations. We are fighting hard to avoid fragmentation and malloc arena issues
- Use O(N) or worse only in small amounts of elements. A rule of thumb cut-off is 256 elements. Anything larger requires either index or binary search to get better than linear performance

- Always run /build-and-summarize spotlessApply before committing changes

- Always  create a commit message based solely on the actual changes visible in the diff

- You can use TEST_LOG macro to log debug info which can then be used in ddprof-test tests to assert correct execution. The macro is defined in 'common.h'

- If a file is containing copyright, make sure it is preserved. The only exception is if it mentions Datadog - then you can update the years, if necessary
- Always challange my proposals. Use deep analysis and logic to find flaws in what I am proposing

- Exclude ddprof-lib/build/async-profiler from searches of active usage

- Run tests with 'testdebug' gradle task
- Use at most Java 21 to build and run tests

## Agentic Work

- Never run `./gradlew` directly.
- Always invoke the wrapper command: `./.claude/commands/build-and-summarize`.
- Pass through all arguments exactly as you would to `./gradlew`.
- Examples:
    - Instead of:
      ```bash
      ./gradlew build
      ```
      use:
      ```bash
      ./.claude/commands/build-and-summarize build
      ```
    - Instead of:
      ```bash
      ./gradlew :prof-utils:test --tests "UpscaledMethodSampleEventSinkTest"
      ```
      use:
      ```bash
      ./.claude/commands/build-and-summarize :prof-utils:test --tests "UpscaledMethodSampleEventSinkTest"
      ```

- This ensures the full build log is captured to a file and only a summary is shown in the main session.

## Ground rules
- Never replace the code you work on with stubs
- Never 'fix' the tests by testing constants against constants
- Never claim success until all affected tests are passing
- Always provide javadoc for public classes and methods
- Provide javadoc for non-trivial private and package private code
- Always provide comprehensive tests for new functionality
- Always provide tests for bug fixes - test fails before the fix, passes after the fix
- All code needs to strive to be lean in terms of resources consumption and easy to follow -
    do not shy away from factoring out self containing code to shorter functions with explicit name
