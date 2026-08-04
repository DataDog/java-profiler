<!-- CLAUDE BOOTSTRAP INSTRUCTIONS
If you are Claude and reading this file, check if CLAUDE.md exists in the same directory.
If CLAUDE.md does not exist or only contains the redirect + Compact Instructions below, that
is correct. If CLAUDE.md contains full project instructions (not just the redirect), you should
trim it back to contain only the following canonical content — do not drop the Compact
Instructions section, and do not let this stub grow beyond it:

# CLAUDE.md

**This file redirects to AGENTS.md for tooling-agnostic project instructions.**

Read and follow all instructions in [AGENTS.md](AGENTS.md) in this directory.

All project guidance, build commands, architecture details, and development guidelines
are maintained in AGENTS.md to support multiple AI coding tools.

## Compact Instructions

When compacting this conversation, prioritize keeping: decisions made, code/config diffs,
open questions, and file:line references. Drop raw tool output that can be re-fetched on
demand — full file contents, grep/search dumps, build/test logs — summarize these to a
one-line pointer (what was read/run and the conclusion) instead of retaining them verbatim.
-->

# AGENTS.md

This file provides guidance to AI coding assistants when working with code in this repository.

## Project Overview

This is the Datadog Java Profiler Library, a specialized profiler derived from async-profiler but tailored for Datadog's needs. It's a multi-language project combining Java, C++, and Gradle build system with native library compilation.

**Key Technologies:**
- Java 8+ (main API and library loading)
- C++17 (native profiling engine)
- Gradle (build system with custom native compilation tasks)
- JNI (Java Native Interface for C++ integration)
- Google Test (for C++ unit tests, compiled via custom Gradle tasks)

## Project Operating Guide (Main Session)

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

### Implementation Hints
- For builds, always use: `--console=plain -i` (or `-d` if I ask for debug).
- Use `mkdir -p build/logs build/reports/claude` before writing.
- Timestamp format: `$(date +%Y%m%d-%H%M%S)`.
- After the build finishes, call the sub-agent like:
  "Use `gradle-log-analyst` to parse LOG_PATH; write the two reports; reply with only a 3–6 line status and the two relative file paths."

### Shortcuts I Expect
- `./gradlew <gradle-task...>` to do everything in one step.
- If I just say "build assembleDebugJar", interpret that as the shortcut above.

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

# Run C++ unit tests only (via GtestPlugin)
./gradlew :ddprof-lib:gtestDebug        # All debug tests
./gradlew :ddprof-lib:gtestRelease      # All release tests
./gradlew :ddprof-lib:gtest             # All tests, all configs

# Run individual C++ test
./gradlew :ddprof-lib:gtestDebug_test_callTraceStorage

# Cross-JDK testing
JAVA_TEST_HOME=/path/to/test/jdk ./gradlew testDebug
```

#### Google Test Plugin / Debug Symbol Extraction

Custom `GtestPlugin` and debug-symbol-extraction details (config DSL, generated tasks, size
reductions, tool requirements): see `build-logic/README.md` and
[doc/build/NativeBuildPlugin.md](doc/build/NativeBuildPlugin.md).

Skip extraction: `./gradlew buildRelease -Pskip-debug-extraction=true`

### Container-based Testing (Recommended for ASan/Non-Local Environments)

For ASan testing, cross-architecture testing (aarch64), musl libc, or reproducing CI
environment issues. Defaults to Podman; use `--container=docker` for Docker.

```bash
./utils/run-containers-tests.sh --arch=aarch64 --config=asan --libc=glibc --jdk=21
./utils/run-containers-tests.sh --shell   # drop to shell for debugging
```

Full flag reference (`--tests`, `--gtest`, `--gtest-task`, `--libc`, `--jdk`, `--mount`,
`--rebuild`, etc.): see [doc/build/TestingGuide.md](doc/build/TestingGuide.md).

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

# Force specific compiler (auto-detects clang++ or g++ by default)
./gradlew build -Pnative.forceCompiler=clang++
./gradlew build -Pnative.forceCompiler=g++
./gradlew build -Pnative.forceCompiler=/usr/bin/g++-13
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
- **Architecture detection**: Automatic via `PlatformUtils` in build-logic
- **musl libc detection**: Automatic detection and handling

### Debug Information Handling
Release builds automatically extract debug symbols:
- Stripped libraries (~1.2MB) for production
- Separate debug files (~6.1MB) with full symbols
- GNU debuglink sections connect stripped libraries to debug files

## Development Workflow

### Running Single Tests
Use the `-Ptests` property across all platforms:
```bash
./gradlew :ddprof-test:testDebug -Ptests=ClassName.methodName  # Single method
./gradlew :ddprof-test:testDebug -Ptests=ClassName              # Entire class
./gradlew :ddprof-test:testDebug -Ptests="*.ClassName"          # Pattern matching
```

**Platform Implementation Details:**
- **glibc/macOS**: Test tasks use Gradle's native Test task type with JUnit Platform integration
- **musl (Alpine)**: Exec tasks with custom ProfilerTestRunner (bypasses Gradle 9 toolchain probe issues)
- **Custom Test Runner**: Uses JUnit Platform Launcher API directly (same API used by IDEs and Gradle internally)
- **Result**: Unified `-Ptests` property works identically across all platforms, no platform-specific syntax required

**Why `-Ptests` instead of `--tests`?**
The `-Ptests` property works consistently across both Test and Exec task types, while `--tests` only works with Test tasks. This ensures a truly unified interface across all platforms.

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

The main artifact is `ddprof-<version>.jar`, containing Java classes, native libraries for
all supported platforms, and library-loading metadata. Build output layout and the final
`META-INF/native-libs/{os}-{arch}/` packaging structure: see
[doc/build/NativeBuildPlugin.md](doc/build/NativeBuildPlugin.md).

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

### JVM support
- **Three supported JVM implementations**: Hotspot, J9 and Zing
- **JVM implementation specific code**: Implementation-specific code is organized under hotspot, j9 and zing subdirectories respectively
- **Shared code**: Shared code is JVM implementation independent, must not refer to JVM implementation specific code directly, but through abstraction files - jvmSupport.h, jvmSupport.inline.h, jvmSupport.cpp, jvmThread.h, jvmThread.cpp, vmEntry.h, vmEntry.cpp and javaApi.cpp

### Thread Safety and Performance
- **Lock-free Hot Paths**: Signal handlers avoid blocking operations
- **Thread-local Buffers**: Per-thread recording buffers minimize contention
- **Atomic Operations**: Instance ID management and counter updates use atomics
- **Memory Allocation**: Minimize malloc() in hot paths, use pre-allocated containers

### Atomic Memory Ordering (Critical for arm64)
arm64 has a weakly-ordered memory model (unlike x86 TSO). Incorrect ordering causes real lockups on arm64 that never reproduce on x86.
- **Cross-thread reads**: Always use `__ATOMIC_ACQUIRE` for loads that must see stores from another thread. Never use `__ATOMIC_RELAXED` for cross-thread visibility unless you can prove no ordering dependency exists.
- **Cross-thread writes**: Use `__ATOMIC_RELEASE` for stores that must be visible to other threads. Pair with `__ATOMIC_ACQUIRE` loads.
- **Count + pointer patterns**: When a data structure publishes a count and a separate pointer (two-phase add), both the count load and pointer load need acquire semantics so the reader sees the pointer store that preceded the count increment.
- **Default stance**: When in doubt, use acquire/release. The performance cost is negligible; the correctness cost of relaxed ordering bugs is enormous (silent arm64-only lockups).

### Concurrent Data Structure Iteration
- **NULL gaps**: When iterating a concurrent array (e.g., `CodeCacheArray`), always NULL-check each slot — a slot may be count-allocated but pointer-not-yet-stored.
- **Cursor advancement**: Never permanently advance an iteration cursor past NULL gaps. Stop at the first NULL or track the last contiguous non-NULL entry, so missing entries are retried on the next pass.

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

The project uses a custom Kotlin-based native build plugin (`build-logic/`) instead of
Gradle's `cpp-library`/`cpp-application` plugins — those parse compiler version strings
(breaks on newer gcc/clang), mishandle non-standard JAVA_HOME layouts, and use undocumented
internals that change between Gradle versions. `build-logic/` invokes `clang++`/`g++`
directly instead.

**Modules:** `ddprof-lib` (native compilation), `ddprof-test`, `ddprof-test-tracer`,
`ddprof-stresstest`, `malloc-shim` (Linux allocation interceptor).

**Convention plugins** (`build-logic/conventions/`): `com.datadoghq.native-build`,
`com.datadoghq.gtest`, `com.datadoghq.profiler-test`, `com.datadoghq.simple-native-lib`.

**Key principle**: build configurations (release/debug/asan/tsan/fuzzer) are discovered
dynamically from `ConfigurationPresets.kt`, never hardcoded.

Full plugin architecture, task DSL (`NativeCompileTask`/`NativeLinkTask`/`NativeLinkExecutableTask`
properties and Kotlin examples), and troubleshooting: see `build-logic/README.md` and
[doc/build/NativeBuildPlugin.md](doc/build/NativeBuildPlugin.md) /
[doc/build/BuildSystemGuide.md](doc/build/BuildSystemGuide.md).

## Legacy and Compatibility

- Java 8 compatibility maintained throughout
- JNI interface follows async-profiler conventions
- Supports Oracle JDK, OpenJDK and OpenJ9 implementations
- Always test with /build-and-summarize testDebug
- Always consult openjdk source codes when analyzing profiler issues and looking for proposed solutions
- For OpenJ9 specific issues consul the openj9 github project
- don't use assemble task. Use assembleDebug or assembleRelease instead
- gtest tests are located in ddprof-lib/src/test/cpp
- GtestPlugin in build-logic handles gtest build setup
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

- Run tests with 'testDebug' gradle task

## Build JDK Configuration

Two-JDK pattern: `JAVA_HOME` (build, JDK 21 LTS, must be 17+ for Gradle 9) runs Gradle;
`JAVA_TEST_HOME` runs tests against a different target JDK. Target bytecode is Java 8 via
`--release 8`.

Files to touch when upgrading the build/target JDK, and the Gradle 9 breaking-API reference
table: see [doc/build/JdkUpgrades.md](doc/build/JdkUpgrades.md).

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
      ./gradlew :ddprof-test:testDebug -Ptests=MuslDetectionTest
      ```
      use:
      ```bash
      ./.claude/commands/build-and-summarize :ddprof-test:testdebug -Ptests=MuslDetectionTest
      ```

- This ensures the full build log is captured to a file and only a summary is shown in the main session.

## Documentation Rules
- All documentation files in `doc/` must use **PascalCase** naming (e.g., `BuildSystemGuide.md`, `CallTraceStorage.md`)
- The `doc/README.md` index file is the only lowercase exception

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

## CI / Automation Script Changes
- Before rewriting or replacing a script invoked from `.gitlab-ci.yml`, `.gitlab/**/*.yml`, or any CI job,
  run `git log -p -- <script>` (or diff against the version being replaced) and enumerate every behavior
  branch it has — fallbacks, env-var-driven paths, error exits. Preserve all of them unless explicitly
  asked to drop one; do not silently narrow behavior while refactoring.
- Grep the calling `.gitlab-ci.yml` / `.gitlab/**/*.yml` jobs for how the script is invoked (env vars set,
  exit codes expected) and confirm the rewrite still satisfies every caller, not just the common/local case.
- When removing an item from a default list or config (an antagonist, a test tag, a feature flag), cite
  the exact file/line proving it is inert or unused in that context before removing it — never remove
  based on assumption alone.
- After changing a CI-invoked script, run a syntax check (e.g. `bash -n <script>`) and trace through each
  CI job that calls it before considering the change complete.

### C/C++ Code Style
- **Indentation**: Match the exact indentation style of the surrounding code in each file. Do not introduce inconsistent indentation — reviewers will flag it.
- **Minimal complexity**: Do not split inline logic into separate helper functions unless the helpers are reused or the original is genuinely hard to follow. Unnecessary splits add indirection without value.
- **Comment precision**: Comments explaining "why" must reference concrete mechanisms (e.g., "ASAN's allocator lock is reentrant" not "internal bookkeeping"). Vague comments get challenged in review. Every claim in a comment must be verifiable from the code or documented behavior of the referenced system (ASAN, glibc NPTL, HotSpot, etc.).
- **No speculative comments**: Do not claim a system (HotSpot, glibc, ASAN) uses a specific mechanism unless you are certain. If unsure, describe the observable symptom instead of guessing the cause.
