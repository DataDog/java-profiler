# Native Build Plugin Architecture

This document describes the architecture of the Kotlin-based native build plugin (`com.datadoghq.native-build`) used for C++ compilation in the Datadog Java Profiler project.

## Overview

The native build plugin replaces Gradle's built-in `cpp-library` and `cpp-application` plugins with a custom, type-safe solution that directly invokes compilers without version string parsing. This design avoids known issues with Gradle's native plugins while providing a clean DSL for configuration.

## Why Custom Build Tasks?

Gradle's native plugins have several problems:

1. **Version Parsing Failures**: The plugins parse compiler version strings which breaks with newer gcc/clang versions
2. **JNI Header Detection Issues**: Problems with non-standard JAVA_HOME layouts
3. **Unresponsive Maintainers**: Plugin maintainers are unresponsive to fixes
4. **Undocumented Internals**: The plugins use internals that change between Gradle versions

**Solution**: Direct compiler invocation without version parsing. The tasks simply find `clang++` or `g++` on PATH and invoke them with configured flags.

## Component Architecture

```
build-logic/
└── conventions/
    └── src/main/kotlin/com/datadoghq/native/
        ├── NativeBuildPlugin.kt          # Main native build plugin
        ├── NativeBuildExtension.kt       # DSL extension for configuration
        ├── config/
        │   └── ConfigurationPresets.kt   # Standard build configurations
        ├── gtest/
        │   ├── GtestPlugin.kt            # Google Test integration plugin
        │   └── GtestExtension.kt         # DSL extension for gtest config
        ├── model/
        │   ├── Architecture.kt           # x64, arm64 enum
        │   ├── Platform.kt               # linux, macos enum
        │   ├── BuildConfiguration.kt     # Configuration model
        │   ├── LogLevel.kt               # QUIET, NORMAL, VERBOSE, DEBUG
        │   ├── ErrorHandlingMode.kt      # FAIL_FAST, COLLECT_ALL
        │   └── SourceSet.kt              # Per-directory compiler flags
        ├── tasks/
        │   ├── NativeCompileTask.kt      # C++ compilation task
        │   ├── NativeLinkTask.kt         # Library linking task
        │   └── NativeLinkExecutableTask.kt # Executable linking task
        └── util/
            └── PlatformUtils.kt          # Platform detection utilities
```

## Plugin Lifecycle

### 1. Plugin Application

When `com.datadoghq.native-build` is applied to a project:

```kotlin
plugins {
    id("com.datadoghq.native-build")
}
```

The plugin:
1. Creates the `nativeBuild` extension for DSL configuration
2. Registers an `afterEvaluate` hook for task generation

### 2. Configuration Phase

During project evaluation, users configure the build:

```kotlin
nativeBuild {
    version.set(project.version.toString())
    cppSourceDirs.set(listOf("src/main/cpp"))
    includeDirectories.set(listOf("src/main/cpp"))
}
```

### 3. Task Generation (afterEvaluate)

After project evaluation, the plugin:

1. **Detects Current Platform**: Uses `PlatformUtils.currentPlatform` and `PlatformUtils.currentArchitecture`

2. **Detects Compiler**: Runs the compiler detection algorithm (see below)

3. **Creates Standard Configurations**: If no configurations are explicitly defined, creates release, debug, asan, tsan, and fuzzer configurations

4. **Filters Active Configurations**: Only configurations matching the current platform/architecture are processed

5. **Generates Tasks**: For each active configuration, creates:
   - `compile{Config}` - Compiles C++ sources
   - `link{Config}` - Links shared library
   - `assemble{Config}` - Aggregates the above

6. **Creates Aggregation Tasks**: `assembleAll` depends on all individual assemble tasks

## Compiler Detection

The compiler detection algorithm prioritizes explicit overrides, then auto-detection:

```
┌─────────────────────────────────────────┐
│  Check -Pnative.forceCompiler property  │
└─────────────────┬───────────────────────┘
                  │
        ┌─────────▼─────────┐
        │ Property defined? │
        └─────────┬─────────┘
             Yes  │  No
        ┌─────────▼─────────┐    ┌─────────────────────┐
        │ Validate compiler │    │ Try clang++         │
        │ with --version    │    │ (preferred)         │
        └─────────┬─────────┘    └──────────┬──────────┘
                  │                         │
        ┌─────────▼─────────┐    ┌──────────▼──────────┐
        │ Available?        │    │ Available?          │
        └─────────┬─────────┘    └──────────┬──────────┘
             Yes  │  No              Yes    │  No
              ▼   │                   ▼     │
           Return │               Return    │
                  ▼                         ▼
           GradleException            Try g++ → c++
                                            │
                                      ┌─────▼─────┐
                                      │ None found│
                                      └─────┬─────┘
                                            ▼
                                      GradleException
```

**Usage:**
```bash
# Auto-detect (default)
./gradlew build

# Force specific compiler
./gradlew build -Pnative.forceCompiler=clang++
./gradlew build -Pnative.forceCompiler=/usr/bin/g++-13
```

## Build Configurations

### Standard Configurations

| Config  | Active When                          | Optimization | Debug | Sanitizers |
|---------|--------------------------------------|--------------|-------|------------|
| release | Always                               | `-O3`        | `-g`  | None       |
| debug   | Always                               | `-O0`        | `-g`  | None       |
| asan    | `libasan` found + not musl           | None         | `-g`  | ASan, UBSan, LSan |
| tsan    | `libtsan` found + not musl           | None         | `-g`  | TSan       |
| fuzzer  | clang++ with libFuzzer + not musl    | None         | `-g`  | ASan, UBSan |

### Configuration Model

Each `BuildConfiguration` contains:

```kotlin
abstract class BuildConfiguration {
    val platform: Property<Platform>        // LINUX or MACOS
    val architecture: Property<Architecture> // X64 or ARM64
    val compilerArgs: ListProperty<String>  // Compiler flags
    val linkerArgs: ListProperty<String>    // Linker flags
    val testEnvironment: MapProperty<String, String>  // Test env vars
    val active: Property<Boolean>           // Whether to build
}
```

### Platform-Specific Flags

**Common Linux Flags:**
```
-fPIC -fno-omit-frame-pointer -momit-leaf-frame-pointer
-fvisibility=hidden -fdata-sections -ffunction-sections -std=c++17
```

**Common macOS Additions:**
```
-D_XOPEN_SOURCE -D_DARWIN_C_SOURCE
```

**Release Linker Flags (Linux):**
```
-Wl,-z,nodelete -static-libstdc++ -static-libgcc
-Wl,--exclude-libs,ALL -Wl,--gc-sections
```

## Task Architecture

### NativeCompileTask

Compiles C++ source files in parallel:

```
┌──────────────────────────────────────────────────────┐
│                 NativeCompileTask                    │
├──────────────────────────────────────────────────────┤
│ Inputs:                                              │
│   - compiler: String (e.g., "clang++")              │
│   - compilerArgs: List<String>                       │
│   - sources: FileCollection                          │
│   - includes: FileCollection                         │
│   - sourceSets: NamedDomainObjectContainer<SourceSet>│
│                                                      │
│ Outputs:                                             │
│   - objectFileDir: Directory                         │
│                                                      │
│ Features:                                            │
│   - Parallel compilation (configurable jobs)         │
│   - Per-source-set compiler flags                    │
│   - FAIL_FAST or COLLECT_ALL error modes            │
│   - Configurable logging verbosity                   │
│   - Convenience methods: define(), standard()        │
└──────────────────────────────────────────────────────┘
```

**Source Sets Support:**

Source sets allow different parts of the codebase to have different compilation flags:

```kotlin
tasks.register("compile", NativeCompileTask::class) {
    compilerArgs.set(listOf("-std=c++17", "-O3"))  // Base flags

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
}
```

### NativeLinkTask

Links object files into shared libraries:

```
┌──────────────────────────────────────────────────────┐
│                  NativeLinkTask                      │
├──────────────────────────────────────────────────────┤
│ Inputs:                                              │
│   - linker: String                                   │
│   - linkerArgs: List<String>                         │
│   - objectFiles: FileCollection                      │
│   - exportSymbols: List<String>                      │
│   - hideSymbols: List<String>                        │
│                                                      │
│ Outputs:                                             │
│   - outputFile: RegularFile                          │
│   - debugSymbolsDir: Directory (optional)            │
│                                                      │
│ Features:                                            │
│   - Symbol visibility control (version scripts)      │
│   - Debug symbol extraction (release builds)         │
│   - Platform-specific linking                        │
│   - macOS wildcard warning                           │
└──────────────────────────────────────────────────────┘
```

**Symbol Visibility:**

The task generates platform-specific symbol export files:

- **Linux**: Version script (`.ver`) with wildcard support (`Java_*`)
- **macOS**: Exported symbols list (`.exp`) - **no wildcard support**

```kotlin
tasks.register("link", NativeLinkTask::class) {
    exportSymbols.set(listOf("Java_*", "JNI_OnLoad", "JNI_OnUnload"))
    hideSymbols.set(listOf("*_internal*"))
}
```

**Note:** On macOS, the task warns when wildcards are used since they're not supported.

## Task Dependencies

```
compile{Config}
       │
       ▼
  link{Config}
       │
       ├──────────────────┐
       │                  │
       ▼                  ▼
extractDebugLib    stripLib{Config}
  (release only)    (release only)
       │                  │
       └────────┬─────────┘
                │
                ▼
        assemble{Config}
                │
                ▼
           assembleAll
```

## Debug Symbol Extraction

Release builds automatically extract debug symbols for optimal deployment:

### Linux Workflow
```bash
objcopy --only-keep-debug library.so library.so.debug
objcopy --add-gnu-debuglink=library.so.debug library.so
strip --strip-debug library.so
```

### macOS Workflow
```bash
dsymutil library.dylib -o library.dylib.dSYM
strip -S library.dylib
```

### Size Reduction
- Original with debug: ~6.1 MB
- Stripped library: ~1.2 MB (80% reduction)
- Debug symbols: ~6.1 MB (separate file)

## Platform Utilities

`PlatformUtils` provides platform detection and tool location:

| Function | Description |
|----------|-------------|
| `currentPlatform` | Detects LINUX or MACOS |
| `currentArchitecture` | Detects X64 or ARM64 |
| `isMusl()` | Detects musl libc (Alpine Linux) |
| `javaHome()` | Finds JAVA_HOME |
| `jniIncludePaths()` | Returns JNI header paths |
| `isCompilerAvailable(compiler)` | Tests compiler with `--version` |
| `locateLibasan(compiler)` | Finds ASan library path |
| `locateLibtsan(compiler)` | Finds TSan library path |
| `hasFuzzer()` | Tests libFuzzer support |
| `sharedLibExtension()` | Returns "so" or "dylib" |

## Plugin Components

The `build-logic` directory contains all native build plugins:

| Component | Plugin ID | Purpose |
|-----------|-----------|---------|
| `NativeBuildPlugin` | `com.datadoghq.native-build` | C++ compilation and linking |
| `GtestPlugin` | `com.datadoghq.gtest` | Google Test integration |
| `NativeCompileTask` | - | Parallel C++ compilation task |
| `NativeLinkTask` | - | Shared library linking task |
| `NativeLinkExecutableTask` | - | Executable linking task (for gtest) |
| `PlatformUtils` | - | Platform detection and compiler location |

## GtestPlugin Integration

The `GtestPlugin` consumes configurations from `NativeBuildPlugin`:

```kotlin
plugins {
    id("com.datadoghq.native-build")
    id("com.datadoghq.gtest")
}

gtest {
    testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
    mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))
    includes.from("src/main/cpp", "$javaHome/include")
}
```

For each test file, GtestPlugin creates:
- `compileGtest{Config}_{TestName}` - Compile sources with test
- `linkGtest{Config}_{TestName}` - Link test executable
- `gtest{Config}_{TestName}` - Execute the test

See `build-logic/README.md` for full GtestPlugin documentation.

## Error Handling Modes

### FAIL_FAST (Default)
- Stops compilation on first error
- Uses sequential stream processing
- Provides immediate feedback

### COLLECT_ALL
- Compiles all files regardless of errors
- Uses parallel stream processing
- Reports all errors at end
- Configurable max errors to show

## Logging Levels

| Level | Description |
|-------|-------------|
| QUIET | Minimal output |
| NORMAL | Standard progress (default) |
| VERBOSE | Progress per N files |
| DEBUG | Full command lines |

## Future Considerations

1. **Windows Support**: Add MSVC/MinGW compiler support if needed
2. **Fuzzer Compiler Detection**: Currently hardcodes clang++
3. **Per-Configuration Compiler**: Allow different compilers per configuration
4. **Incremental Compilation**: Track source dependencies for partial rebuilds

## Related Documentation

- `build-logic/README.md` - Native build and GtestPlugin usage documentation
- `CLAUDE.md` - Build commands reference
