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
