# Native Build Plugin

This directory contains a Gradle composite build that provides the `com.datadoghq.native-build` plugin for building C++ libraries.

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
- **Optimization**: `-O3 -DNDEBUG`
- **Debug symbols**: Extracted to separate files (69% size reduction)
- **Strip**: Yes (production binaries)
- **Output**: Stripped library + .dSYM bundle (macOS) or .debug file (Linux)

### Debug
- **Optimization**: `-O0 -g`
- **Debug symbols**: Embedded
- **Strip**: No
- **Output**: Full debug library

### ASan (AddressSanitizer)
- Conditionally active if libasan is available
- Memory error detection

### TSan (ThreadSanitizer)
- Conditionally active if libtsan is available
- Thread safety validation

### Fuzzer
- Fuzzing instrumentation
- Requires libFuzzer

## Debug Symbol Extraction

Release builds automatically extract debug symbols for optimal production deployment:

### macOS
```
dsymutil library.dylib -o library.dylib.dSYM
strip -S library.dylib
```
- **Stripped library**: ~404KB (production)
- **Debug bundle**: ~3.7MB (.dSYM)

### Linux
```
objcopy --only-keep-debug library.so library.so.debug
objcopy --strip-debug library.so
objcopy --add-gnu-debuglink=library.so.debug library.so
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
- **Linux**: Generates version script (`.ver` file) with wildcard pattern support
- **macOS**: Generates exported symbols list (`.exp` file) with explicit names (auto-adds `_` prefix)

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
compileConfig → linkConfig → assembleConfig
                    ↓
              extractDebugSymbols (release only)
                    ↓
              stripSymbols (release only)
                    ↓
              copyConfigLibs → assembleConfigJar
```

## Migration from Groovy

The new system replaces:
- `gradle/configurations.gradle` - Configuration definitions
- Groovy build scripts - Kotlin DSL (.gradle.kts)
- `buildSrc` tasks - Type-safe Kotlin plugin

**Benefits:**
- ✅ Eliminated configuration duplication
- ✅ Compile-time type checking
- ✅ Gradle idiomatic (Property API, composite builds)
- ✅ Debug symbol extraction (69% size reduction)
- ✅ Clean builds work from scratch

## Files

- `settings.gradle` - Composite build configuration
- `conventions/build.gradle.kts` - Plugin module
- `conventions/src/main/kotlin/` - Plugin implementation
  - `NativeBuildPlugin.kt` - Main plugin
  - `NativeBuildExtension.kt` - DSL extension
  - `model/` - Type-safe configuration models
  - `tasks/` - Compile and link tasks
  - `config/` - Configuration presets
  - `util/` - Platform utilities
