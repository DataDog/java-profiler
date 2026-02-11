<!-- CLAUDE BOOTSTRAP INSTRUCTIONS
If you are Claude and reading this file, check if CLAUDE.md exists in the same directory.
If CLAUDE.md does not exist or only contains a redirect to this file, that is correct.
If CLAUDE.md contains full instructions (not a redirect), you should update it to contain
only the following redirect content:

# CLAUDE.md

**This file redirects to AGENTS.md for tooling-agnostic project instructions.**

Read and follow all instructions in [AGENTS.md](AGENTS.md) in this directory.

All project guidance, build commands, architecture details, and development guidelines
are maintained in AGENTS.md to support multiple AI coding tools.
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

#### Google Test Plugin

The project uses a custom `GtestPlugin` (in `build-logic/`) for C++ unit testing with Google Test. The plugin automatically:
- Discovers `.cpp` test files in `src/test/cpp/`
- Creates compilation, linking, and execution tasks for each test
- Filters configurations by current platform/architecture
- Integrates with NativeCompileTask and NativeLinkExecutableTask

**Key features:**
- Platform-aware: Only creates tasks for matching OS/arch
- Assertion control: Removes `-DNDEBUG` to enable assertions in tests
- Symbol preservation: Keeps debug symbols in release test builds
- Task aggregation: Per-config (`gtestDebug`) and master (`gtest`) tasks
- Shared configurations: Uses BuildConfiguration from NativeBuildPlugin

**Configuration example (ddprof-lib/build.gradle.kts):**
```kotlin
plugins {
    id("com.datadoghq.native-build")
    id("com.datadoghq.gtest")
}

gtest {
    testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
    mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
    includes.from(
        "src/main/cpp",
        "${javaHome}/include",
        "${javaHome}/include/${platformInclude}"
    )
    // Optional
    enableAssertions.set(true)    // Remove -DNDEBUG (default: true)
    keepSymbols.set(true)         // Keep symbols in release (default: true)
    failFast.set(false)           // Stop on first failure (default: false)
}
```

**See:** `build-logic/README.md` for full documentation

#### Debug Symbol Extraction

Release builds automatically extract debug symbols via `NativeLinkTask`, reducing production binary size (~69% smaller) while maintaining separate debug files for offline debugging.

**Key features:**
- Platform-aware: Uses `objcopy`/`strip` on Linux, `dsymutil`/`strip` on macOS
- Automatic workflow: Extract symbols → Add GNU debuglink (Linux) → Strip library → Copy artifacts
- Size optimization: Stripped ~1.2MB production library from ~6.1MB with embedded debug info
- Debug preservation: Separate `.debug` files (Linux) or `.dSYM` bundles (macOS)

**Tool requirements:**
- Linux: `binutils` package (objcopy, strip)
- macOS: Xcode Command Line Tools (dsymutil, strip)

**Skip extraction:**
```bash
./gradlew buildRelease -Pskip-debug-extraction=true
```

**See:** `build-logic/README.md` for full documentation

### Docker-based Testing (Recommended for ASan/Non-Local Environments)

**When to use**: For ASan testing, cross-architecture testing (aarch64), different libc variants (musl), or reproducing CI environment issues.

```bash
# ASan tests on aarch64 Linux
./utils/run-docker-tests.sh --arch=aarch64 --config=asan --libc=glibc --jdk=21

# Run specific test pattern
./utils/run-docker-tests.sh --arch=aarch64 --tests="*SpecificTest*"

# Enable C++ gtests
./utils/run-docker-tests.sh --arch=aarch64 --gtest

# Drop to shell for debugging
./utils/run-docker-tests.sh --arch=aarch64 --shell

# Test with musl libc
./utils/run-docker-tests.sh --libc=musl --jdk=21

# Test with OpenJ9
./utils/run-docker-tests.sh --jdk=21-j9

# Use mounted repo (faster, but may have stale artifacts)
./utils/run-docker-tests.sh --mount

# Rebuild Docker images
./utils/run-docker-tests.sh --rebuild
```

**Note**: The Docker script supports `--config=debug|release|asan|tsan`. Use this for cross-architecture testing and reproducing CI environments. For local development, use `./gradlew testAsan` directly.

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
- **Platform Detection**: Automatic OS and architecture detection via `PlatformUtils` in build-logic
- **Configuration Matrix**: Multiple build configs (release/debug/asan/tsan) per platform
- **Symbol Processing**: Automatic debug symbol extraction for release builds
- **Library Packaging**: Final JAR contains all platform-specific native libraries
- **Compiler Detection**: Auto-detects clang++ (preferred) or g++ (fallback); override with `-Pnative.forceCompiler`

### Native Build Plugin (build-logic)
The project includes a Kotlin-based native build plugin (`build-logic/`) for type-safe C++ compilation:
- **Composite Build**: Independent Gradle project for build logic versioning
- **Type-Safe DSL**: Kotlin-based configuration with compile-time checking
- **Auto Task Generation**: Creates compile, link, and assemble tasks per configuration
- **Debug Symbol Extraction**: Automatic split debug info for release builds (69% size reduction)
- **Source Sets**: Per-directory compiler flags for legacy/third-party code
- **Symbol Visibility**: Linux version scripts and macOS exported symbols lists

**See:** `build-logic/README.md` for full documentation

### Custom Native Build Plugin (build-logic)
The project uses a custom Kotlin-based native build plugin in `build-logic/` instead of Gradle's `cpp-library` and `cpp-application` plugins. This is intentional:

**Why not cpp-library/cpp-application plugins:**
- Gradle's native plugins parse compiler version strings which breaks with newer gcc/clang versions
- JNI header detection has issues with non-standard JAVA_HOME layouts
- Plugin maintainers are unresponsive to fixes
- The plugins use undocumented internals that change between Gradle versions

**Plugin components (`com.datadoghq.native-build`):**
- `NativeCompileTask` - Parallel C++ compilation with source sets support
- `NativeLinkTask` - Links shared libraries (.so/.dylib) with symbol visibility
- `PlatformUtils` - Platform detection and compiler location

**Plugin components (`com.datadoghq.gtest`):**
- `NativeLinkExecutableTask` - Links executables (for gtest)
- `GtestPlugin` - Google Test integration and task generation

**Key principle:** Direct compiler invocation without version parsing. The tasks simply find `clang++` or `g++` on PATH and invoke them with the configured flags.

#### Configuring Build Tasks

All build tasks support industry-standard configuration options. Configuration is done using Kotlin DSL:

**Basic compilation:**
```kotlin
tasks.register("compileLib", NativeCompileTask::class) {
    compiler.set("clang++")
    compilerArgs.set(listOf("-O3", "-std=c++17", "-fPIC"))
    sources.from(fileTree("src/main/cpp") { include("**/*.cpp") })
    includes.from("src/main/cpp", "${System.getenv("JAVA_HOME")}/include")
    objectFileDir.set(file("build/obj"))
}
```

**Advanced configuration with source sets:**
```kotlin
tasks.register("compileLib", NativeCompileTask::class) {
    compiler.set("clang++")
    compilerArgs.set(listOf("-Wall", "-O3"))  // Base flags for all files

    // Multiple source directories with per-directory flags
    sourceSets {
        create("main") {
            sources.from(fileTree("src/main/cpp"))
            compilerArgs.add("-fPIC")
        }
        create("legacy") {
            sources.from(fileTree("src/legacy"))
            compilerArgs.addAll("-Wno-deprecated", "-std=c++11")
            excludes.add("**/broken/*.cpp")
        }
    }

    // Logging
    logLevel.set(LogLevel.VERBOSE)

    objectFileDir.set(file("build/obj"))
}
```

**Linking shared libraries with symbol management:**
```kotlin
tasks.register("linkLib", NativeLinkTask::class) {
    linker.set("clang++")
    linkerArgs.set(listOf("-O3"))
    objectFiles.from(fileTree("build/obj") { include("*.o") })
    outputFile.set(file("build/lib/libjavaProfiler.so"))

    // Symbol visibility control
    exportSymbols.set(listOf("Java_*", "JNI_OnLoad", "JNI_OnUnload"))
    hideSymbols.set(listOf("*_internal*"))

    // Libraries
    lib("pthread", "dl", "m")
    libPath("/usr/local/lib")

    logLevel.set(LogLevel.VERBOSE)
}
```

**Executable linking (for gtest):**
```kotlin
tasks.register("linkTest", NativeLinkExecutableTask::class) {
    linker.set("clang++")
    objectFiles.from(fileTree("build/obj/gtest") { include("*.o") })
    outputFile.set(file("build/bin/callTrace_test"))

    // Library management
    lib("gtest", "gtest_main", "pthread")
    libPath("/usr/local/lib")
    runtimePath("/opt/lib", "/usr/local/lib")

    logLevel.set(LogLevel.VERBOSE)
}
```

**Task properties:**

*NativeCompileTask:*
- `compiler`, `compilerArgs` - Compiler and flags
- `sources`, `includes` - Source files and include paths
- `sourceSets` - Per-directory compiler flag overrides
- `objectFileDir` - Output directory for object files
- `logLevel` - QUIET, NORMAL, VERBOSE, DEBUG

*NativeLinkTask:*
- `linker`, `linkerArgs` - Linker and flags
- `objectFiles`, `outputFile` - Input objects and output library
- `exportSymbols`, `hideSymbols` - Symbol visibility control
- `lib()`, `libPath()` - Library convenience methods
- `logLevel`, `showCommandLine` - Logging options

*NativeLinkExecutableTask:*
- `linker`, `linkerArgs` - Linker and flags
- `objectFiles`, `outputFile` - Input objects and output executable
- `lib()`, `libPath()`, `runtimePath()` - Library and rpath convenience methods
- `logLevel`, `showCommandLine` - Logging options

### Artifact Structure
Final artifacts maintain a specific structure for deployment:
```
META-INF/native-libs/{os}-{arch}/libjavaProfiler.{so|dylib}
```
With separate debug symbol packages for production debugging support.

## Build System Maintenance

> **Detailed guide**: [doc/build/BuildSystemGuide.md](doc/build/BuildSystemGuide.md)

### Quick Reference

**Convention plugins** (in `build-logic/conventions/`):
- `com.datadoghq.native-build` - Multi-config C++ compilation
- `com.datadoghq.gtest` - Google Test integration
- `com.datadoghq.profiler-test` - Multi-config Java test generation
- `com.datadoghq.simple-native-lib` - Simple single-library builds

**Key principle**: Build configurations (release/debug/asan/tsan/fuzzer) are **discovered dynamically**, not hardcoded. Add new configs in `ConfigurationPresets.kt` only.

**Key files**:
- `ConfigurationPresets.kt` - Defines all build configurations and their flags
- `PlatformUtils.kt` - Platform detection and compiler finding
- `NativeBuildPlugin.kt` - Creates compile/link tasks per configuration

### Common Tasks

| Task | Description |
|------|-------------|
| Add compiler flag to all configs | Edit `commonLinuxCompilerArgs()` in `ConfigurationPresets.kt` |
| Add new build configuration | Add `register("name")` block in `ConfigurationPresets.kt` |
| Create new convention plugin | Create class, register in `build.gradle.kts`, see [guide](doc/BUILD-SYSTEM-GUIDE.md#creating-a-new-convention-plugin) |

### Gradle Properties

See `gradle.properties.template` for all options. Key ones:
- `skip-tests`, `skip-native`, `skip-gtest` - Skip build phases
- `native.forceCompiler` - Override compiler detection
- `ddprof_version` - Override version

### Troubleshooting

- **Plugin changes not taking effect**: Run `./gradlew --stop`
- **"Task not found"**: Tasks are created dynamically; check `PlatformUtils` detection
- **"Configuration not found"**: Access configurations in `afterEvaluate`

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

- Run tests with 'testdebug' gradle task

## Build JDK Configuration

The project uses a **two-JDK pattern**:
- **Build JDK** (`JAVA_HOME`): Used to run Gradle itself. Must be JDK 17+ for Gradle 9.
- **Test JDK** (`JAVA_TEST_HOME`): Used to run tests against different Java versions.

**Current requirement:** JDK 21 (LTS) for building, targeting Java 8 bytecode via `--release 8`.

### Files to Modify When Changing Build JDK Version

When upgrading the build JDK (e.g., from JDK 21 to JDK 25), update these files:

| File | What to Change |
|------|----------------|
| `README.md` | Update "Prerequisites" section with new JDK version |
| `.github/actions/setup_cached_java/action.yml` | Change `build_jdk=jdk21` to new version (line ~25) |
| `.github/workflows/ci.yml` | Update `java-version` in `check-formatting` job's Setup Java step |
| `utils/run-docker-tests.sh` | Update `BUILD_JDK_VERSION="21"` constant |
| `build-logic/.../JavaConventionsPlugin.kt` | Update documentation comment if minimum changes |

### Files to Modify When Changing Target JDK Version

When changing the target bytecode version (e.g., from Java 8 to Java 11):

| File | What to Change |
|------|----------------|
| `build-logic/.../JavaConventionsPlugin.kt` | Change `--release 8` to new version |
| `ddprof-lib/build.gradle.kts` | Change `sourceCompatibility`/`targetCompatibility` |
| `README.md` | Update minimum Java runtime version |

### Gradle 9 API Changes Reference

When upgrading Gradle major versions, watch for these breaking changes:

| Old API | New API (Gradle 9+) | Affected Files |
|---------|---------------------|----------------|
| `project.exec { }` in task actions | `ProcessBuilder` directly | `GtestPlugin.kt` |
| `String.capitalize()` | `replaceFirstChar { it.uppercaseChar() }` | Kotlin plugins |
| `createTempFile()` | `kotlin.io.path.createTempFile()` | `PlatformUtils.kt` |
| Spotless `userData()` | `editorConfigOverride()` | `SpotlessConventionPlugin.kt` |
| Spotless `indentWithSpaces()` | `leadingTabsToSpaces()` | `SpotlessConventionPlugin.kt` |

### CI JDK Caching

The CI caches JDKs via `.github/workflows/cache_java.yml`. When adding a new JDK version:
1. Add version URLs to `cache_java.yml` environment variables
2. Add to the `java_variant` matrix in cache jobs
3. Run the `cache_java.yml` workflow manually to populate caches

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
