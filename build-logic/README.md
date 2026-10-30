<!-- Copyright 2026, Datadog, Inc. -->

# Native Build Plugins

This directory contains a Gradle composite build that provides plugins for building C++ libraries and tests:

- **`com.datadoghq.native-build`** - Core C++ compilation and linking
- **`com.datadoghq.gtest`** - Google Test integration for C++ unit tests
- **`com.datadoghq.scanbuild`** - Clang static analyzer integration

Other plugins registered in `conventions/build.gradle.kts`: `com.datadoghq.native-root`
(root project configs), `com.datadoghq.profiler-test` (Java test tasks per config),
`com.datadoghq.fuzz-targets` (libFuzzer targets), `com.datadoghq.simple-native-lib`,
`com.datadoghq.spotless-convention`, `com.datadoghq.java-conventions`,
`com.datadoghq.versioned-sources`.

> **📚 New to these plugins?** Check out [QUICKSTART.md](QUICKSTART.md) for practical examples, common workflows, tips and tricks, and troubleshooting guidance.

## Architecture

The plugin uses Kotlin DSL for type-safe build configuration and follows modern Gradle conventions:

- **Composite Build**: Independent Gradle project for build logic versioning
- **Type-Safe DSL**: Kotlin-based configuration with compile-time checking
- **Property API**: Lazy evaluation using Gradle's Property types
- **Automatic Task Generation**: Creates compile, link, and assemble tasks per configuration

## Plugin Usage

```kotlin
plugins {
    id("com.datadoghq.native-build")
}

nativeBuild {
    version.set(project.version.toString())
    cppSourceDirs.set(listOf("src/main/cpp"))
    includeDirectories.set(listOf("src/main/cpp"))
}
```

The plugin automatically creates standard configurations (release, debug, asan, tsan, fuzzer) and generates tasks:
- `compile{Config}` - Compiles C++ sources
- `link{Config}` - Links shared library
- `assemble{Config}` - Assembles configuration
- `assembleAll` - Builds all active configurations

## Standard Configurations

### Release
- **Optimization**: `-O3 -DNDEBUG -g`
- **Debug symbols**: Extracted to separate files (done inside `linkRelease`)
- **Strip**: Yes (production binaries)
- **Output**: Stripped library + .dSYM bundle (macOS) or .debug file (Linux)

### Debug
- **Optimization**: `-O0 -g`
- **Debug symbols**: Embedded
- **Strip**: No
- **Output**: Full debug library

### ASan (AddressSanitizer)
- Active on Linux when the ASan runtime is found for the compiler and libc is not musl
  (`PlatformUtils.hasAsan()`); always inactive on macOS
- Memory error detection

### TSan (ThreadSanitizer)
- Active on Linux when the TSan runtime is found for the compiler and libc is not musl
  (`PlatformUtils.hasTsan()`); always inactive on macOS
- Thread safety validation

### Fuzzer
- Fuzzing instrumentation
- Requires libFuzzer (clang `-fsanitize=fuzzer`, not musl; `PlatformUtils.hasFuzzer()`)

## Compiler Detection

The plugin automatically detects and selects the best available C++ compiler:

### Auto-Detection (Default)
```bash
./gradlew build
# Logs: "Auto-detected compiler: clang++"
# or: "Auto-detected compiler: g++"
```

**Detection order:**
1. `clang++` (preferred - better optimization and diagnostics)
2. `g++` (fallback)
3. `c++` (last resort)

If no compiler is found, the build fails with a clear error message.

### Force Specific Compiler
Use the `-Pnative.forceCompiler` property to override auto-detection:

```bash
# Force clang++
./gradlew build -Pnative.forceCompiler=clang++

# Force g++
./gradlew build -Pnative.forceCompiler=g++

# Force specific version (full path)
./gradlew build -Pnative.forceCompiler=/usr/bin/g++-13
./gradlew build -Pnative.forceCompiler=/opt/homebrew/bin/clang++
```

**Validation:** The specified compiler is validated by running `<compiler> --version`. If validation fails, the build errors immediately with an actionable message.

### Sanitizer Library Detection
ASan and TSan library detection uses the detected/forced compiler instead of hardcoding `gcc`. This enables sanitizer builds on clang-only systems (e.g., macOS with Xcode but no gcc installed).

## Debug Symbol Extraction

Release builds automatically extract debug symbols for optimal production deployment:

### macOS
```
dsymutil library.dylib -o library.dylib.dSYM
strip -S library.dylib
```
- **Stripped library**: ~404KB (production; approximate, drifts with code size)
- **Debug bundle**: ~3.7MB (.dSYM)

### Linux
```
objcopy --only-keep-debug library.so library.so.debug
objcopy --add-gnu-debuglink=library.so.debug library.so
strip --strip-debug library.so
```
- **Stripped library**: ~1.2MB (production)
- **Debug file**: ~6MB (.debug)

## Advanced Features

### Source Sets

Source sets allow different parts of the codebase to have different compilation flags. This is useful for:
- Legacy code requiring older C++ standards
- Third-party code with specific compiler warnings
- Platform-specific optimizations

**Example:**
```kotlin
tasks.register("compileLib", NativeCompileTask::class) {
    compiler.set("clang++")
    compilerArgs.set(listOf("-std=c++17", "-O3"))  // Base flags for all files
    includes.from("src/main/cpp")

    // Define source sets with per-set compiler flags
    sourceSets {
        create("main") {
            sources.from(fileTree("src/main/cpp"))
            compilerArgs.add("-fPIC")  // Additional flags for main code
        }
        create("legacy") {
            sources.from(fileTree("src/legacy"))
            compilerArgs.addAll("-Wno-deprecated", "-std=c++11")  // Different standard
            excludes.add("**/broken/*.cpp")  // Exclude specific files
        }
    }

    objectFileDir.set(file("build/obj"))
}
```

**Key features:**
- **Include/exclude patterns**: Ant-style patterns (e.g., `**/*.cpp`, `**/test_*.cpp`)
- **Merged compiler args**: Base args + source-set-specific args
- **Conveniences**: `from()`, `include()`, `exclude()`, `compileWith()` methods

### Symbol Visibility Control

Symbol visibility controls which symbols are exported from shared libraries. This is essential for:
- Hiding internal implementation details
- Reducing symbol table size
- Preventing symbol conflicts
- Creating clean JNI interfaces

**Example:**
```kotlin
tasks.register("linkLib", NativeLinkTask::class) {
    linker.set("clang++")
    objectFiles.from(fileTree("build/obj"))
    outputFile.set(file("build/lib/libjavaProfiler.dylib"))

    // Export only JNI symbols
    exportSymbols.set(listOf(
        "Java_*",           // All JNI methods
        "JNI_OnLoad",       // JNI initialization
        "JNI_OnUnload"      // JNI cleanup
    ))

    // Hide specific internal symbols (overrides exports)
    hideSymbols.set(listOf(
        "*_internal*",      // Internal functions
        "*_test*"           // Test utilities
    ))
}
```

**Platform-specific implementation:**
- **Linux**: Generates version script (`.ver` file) with wildcard pattern support (e.g., `Java_*` matches all JNI methods)
- **macOS**: Generates exported symbols list (`.exp` file) - **Note:** Wildcards are not supported on macOS. Patterns like `Java_*` are treated as literal symbol names. For JNI exports, you must either list individual symbols or use `-fvisibility` compiler flags instead.

**Generated files** (in `temporaryDir`):
- Linux: `library.ver` → `-Wl,--version-script=library.ver`
- macOS: `library.exp` → `-Wl,-exported_symbols_list,library.exp`

**Symbol visibility best practices:**
1. Start with `-fvisibility=hidden` compiler flag
2. Mark public API with `__attribute__((visibility("default")))` in source
3. OR use `exportSymbols` linker flag for pattern-based export
4. Verify with: `nm -gU library.dylib` (macOS) or `nm -D library.so` (Linux)

## Task Dependencies

```
compile{Config} → link{Config} → assemble{Config}
                       ↓
                 copy{Config}Libs → assemble{Config}Jar   (registered in ddprof-lib/build.gradle.kts)
```

For release, `link{Config}` itself extracts debug info and strips the library
(`NativeLinkTask` `extractDebugSymbols` / `stripSymbols`, enabled only for `release` in
`NativeBuildPlugin.kt`). These are task properties, not separate tasks.

## Design Benefits

The Kotlin-based build system provides:
- ✅ Compile-time type checking via Kotlin DSL
- ✅ Gradle idiomatic design (Property API, composite builds)
- ✅ Automatic debug symbol extraction for release builds
- ✅ Clean builds work from scratch
- ✅ Centralized configuration definitions

---

# Google Test Plugin

The `com.datadoghq.gtest` plugin provides Google Test integration for C++ unit testing.

## Plugin Usage

```kotlin
plugins {
    id("com.datadoghq.native-build")  // Required - provides configurations
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
}
```

## Generated Tasks

For each test file in `testSourceDir`, the plugin creates:

| Task Pattern | Description |
|--------------|-------------|
| `compileGtest{Config}_{TestName}` | Compile the test file only |
| `linkGtest{Config}_{TestName}` | Link test executable with gtest libraries |
| `gtest{Config}_{TestName}` | Execute the test |

Per configuration, `compileGtestLibrary{Config}` compiles the main sources once and every
test executable links against those objects.

Aggregation tasks:
- `gtest` - Run all tests across all active configurations
- `gtest{Config}` - Run all tests for a specific configuration (e.g., `gtestDebug`)
- `buildGtest{Config}` - Compile + link all test executables for a configuration without running them

## Configuration Options

| Property | Type | Default | Description |
|----------|------|---------|-------------|
| `testSourceDir` | `DirectoryProperty` | Required | Directory containing test `.cpp` files |
| `mainSourceDir` | `DirectoryProperty` | Required | Directory containing main source files |
| `includes` | `ConfigurableFileCollection` | Empty | Include directories for compilation |
| `googleTestHome` | `DirectoryProperty` | Auto-detected | Google Test installation directory (macOS) |
| `enableAssertions` | `Property<Boolean>` | `true` | Remove `-DNDEBUG` to enable assertions |
| `keepSymbols` | `Property<Boolean>` | `true` | Keep debug symbols in release test builds |
| `failFast` | `Property<Boolean>` | `false` | Stop on first test failure |
| `alwaysRun` | `Property<Boolean>` | `true` | Ignore up-to-date checks for tests |
| `buildNativeLibs` | `Property<Boolean>` | `true` | Build native test support libraries (Linux) |
| `nativeLibsSourceDir` | `DirectoryProperty` | - | Source dir of the native test support libraries |
| `nativeLibsOutputDir` | `DirectoryProperty` | - | Output dir for the built support libraries |

## Platform Detection

The plugin automatically detects Google Test installation:

- **macOS**: `/opt/homebrew/opt/googletest` (Homebrew default), then `/usr/local/opt/googletest`
- **Linux**: System includes (`/usr/include/gtest`)

Override with `googleTestHome`:
```kotlin
gtest {
    googleTestHome.set(file("/custom/path/to/googletest"))
}
```

## Integration with NativeBuildPlugin

GtestPlugin consumes configurations from NativeBuildPlugin:

1. **Shared configurations**: Uses the same release/debug/asan/tsan/fuzzer configs
2. **Compiler detection**: Uses `PlatformUtils.findCompiler()` with `-Pnative.forceCompiler` support
3. **Consistent flags**: Inherits compiler/linker args from build configurations

Linux support helpers built by `buildNativeLibs` receive the resolved compiler as Make's
`CXX` variable. Changing the compiler invalidates the helper task. Their Makefiles own
the flags; configuration sanitizer flags are not forwarded, so allocator probes remain
unsanitized. Makefiles that hardcode a compiler instead of using `CXX` are unchanged.

## Example Output

```
$ ./gradlew gtestDebug

> Task :ddprof-lib:compileGtestLibraryDebug
Compiling <N> C++ source files with clang++...

> Task :ddprof-lib:compileGtestDebug_test_callTraceStorage
Compiling 1 C++ source file with clang++...

> Task :ddprof-lib:linkGtestDebug_test_callTraceStorage
Linking executable: test_callTraceStorage

> Task :ddprof-lib:gtestDebug_test_callTraceStorage
[==========] Running 5 tests from 1 test suite.
...
[  PASSED  ] 5 tests.

BUILD SUCCESSFUL
```

## Skip Options

```bash
# Skip all tests
./gradlew build -Pskip-tests

# Skip only gtest (keep Java tests)
./gradlew build -Pskip-gtest

# Skip native compilation entirely
./gradlew build -Pskip-native
```

---

## Files

- `settings.gradle` - Composite build configuration
- `conventions/build.gradle.kts` - Plugin module
- `conventions/src/main/kotlin/` - Plugin implementation
  - `NativeBuildPlugin.kt` - Native build plugin
  - `NativeBuildExtension.kt` - Native build DSL extension
  - `gtest/GtestPlugin.kt` - Google Test plugin
  - `gtest/GtestExtension.kt` - Google Test DSL extension
  - `gtest/GtestTaskBuilder.kt` - Per-test compile/link/run task builder
  - `fuzz/FuzzTargetsPlugin.kt` - libFuzzer target plugin
  - `scanbuild/ScanBuildPlugin.kt` - Static analysis plugin
  - `scanbuild/ScanBuildExtension.kt` - Static analysis DSL extension
  - `model/` - Type-safe configuration models
  - `tasks/` - Compile and link tasks
  - `config/` - Configuration presets
  - `util/` - Platform utilities

---

## Documentation

- **[QUICKSTART.md](QUICKSTART.md)** - Quick start guide with practical examples, workflows, tips and troubleshooting
- **[README.md](README.md)** (this file) - Architecture details, API reference, and design documentation
