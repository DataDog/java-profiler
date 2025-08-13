# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is the Datadog Java Profiler Library, a specialized profiler derived from async-profiler but tailored for Datadog's needs. It's a multi-language project combining Java, C++, and Gradle build system with native library compilation.

**Key Technologies:**
- Java 8+ (main API and library loading)
- C++17 (native profiling engine)
- Gradle (build system with custom native compilation)
- JNI (Java Native Interface for C++ integration)
- CMake (for C++ unit tests via Google Test)

## Build Commands

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
# Run all tests
./gradlew test

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
./gradlew build -Pskip-native

# Skip all tests
./gradlew build -Pskip-tests

# Skip C++ tests
./gradlew build -Pskip-gtest

# Keep JFR recordings after tests
./gradlew test -PkeepJFRs

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

### Upstream Integration
The project maintains integration with async-profiler upstream:
- `cloneAsyncProfiler`: Clones DataDog's async-profiler fork
- `copyUpstreamFiles`: Copies selected upstream files to `ddprof-lib/src/main/cpp-external`
- `patchStackFrame`/`patchStackWalker`: Applies necessary patches for ASAN compatibility
- Lock file: `gradle/ap-lock.properties` specifies branch/commit

### Key Source Locations
- Java API: `ddprof-lib/src/main/java/com/datadoghq/profiler/JavaProfiler.java`
- C++ engine: `ddprof-lib/src/main/cpp/`
- Upstream C++ code: `ddprof-lib/src/main/cpp-external/` (generated)
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
1. Full rebuild: `./gradlew clean build`
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

## Legacy and Compatibility

- `legacy_tests/`: Shell-based tests (being migrated to Gradle)
- Java 8 compatibility maintained throughout
- JNI interface follows async-profiler conventions
- Supports both Oracle JDK and OpenJDK implementations
- Always test with ./gradlew testDebug
- Always consult openjdk source codes when analyzing profiler issues and looking for proposed solutions
- don't use assemble task. Use assembleDebug or assembleRelease instead
- gtest tests are located in ddprof-lib/src/test/cpp
- Module ddprof-lib/gtest is only containing the gtest build setup
- Java unit tests are in ddprof-test module