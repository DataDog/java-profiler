# Native Build Plugins - Quick Start Guide

This guide provides practical examples, workflows, and tips for using the Datadog native build plugin suite. For architectural details and reference documentation, see [README.md](README.md).

## Table of Contents

- [Getting Started](#getting-started)
- [Common Workflows](#common-workflows)
- [How-To Guides](#how-to-guides)
- [Tips and Tricks](#tips-and-tricks)
- [Troubleshooting](#troubleshooting)

---

## Getting Started

### Minimal Setup

**build.gradle.kts:**
```kotlin
plugins {
    id("com.datadoghq.native-build")
}

nativeBuild {
    version.set(project.version.toString())
}
```

That's it! The plugin will:
- Auto-detect your compiler (clang++ or g++)
- Create standard configurations (release, debug, asan, tsan, fuzzer)
- Generate compile, link, and assemble tasks
- Use `src/main/cpp` as default source directory

### Quick Build

```bash
# Build release configuration
./gradlew assembleRelease

# Build all active configurations
./gradlew assembleAll

# Build specific configuration
./gradlew assembleDebug
```

### Adding Tests

**build.gradle.kts:**
```kotlin
plugins {
    id("com.datadoghq.native-build")
    id("com.datadoghq.gtest")
}

gtest {
    testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
    mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))

    val javaHome = com.datadoghq.native.util.PlatformUtils.javaHome()
    includes.from("src/main/cpp", "$javaHome/include")
}
```

```bash
# Run all tests
./gradlew gtest

# Run tests for specific configuration
./gradlew gtestDebug
./gradlew gtestRelease
```

---

## Common Workflows

### 1. Development: Fast Iteration with Debug Build

```bash
# One-time: ensure you have debug config
./gradlew tasks --group=build | grep Debug

# Edit code, then compile and link
./gradlew assembleDebug

# Run debug tests
./gradlew gtestDebug
```

**Why debug config?**
- No optimization (`-O0`) = faster compilation
- Full debug symbols embedded
- Assertions enabled (no `-DNDEBUG`)
- No symbol stripping

### 2. Testing: Memory Safety with ASan

```bash
# Check if ASan is available
./gradlew tasks | grep -i asan

# Build with AddressSanitizer
./gradlew assembleAsan

# Run tests with ASan instrumentation
./gradlew gtestAsan
```

**ASan detects:**
- Heap buffer overflow/underflow
- Stack buffer overflow
- Use-after-free
- Use-after-return
- Memory leaks
- Double-free

### 3. Testing: Thread Safety with TSan

```bash
# Build with ThreadSanitizer
./gradlew assembleTsan

# Run tests with TSan instrumentation
./gradlew gtestTsan
```

**TSan detects:**
- Data races
- Deadlocks
- Thread leaks
- Signal-unsafe functions in signal handlers

### 4. Release: Production Build with Debug Symbols

```bash
# Build release configuration
./gradlew assembleRelease

# Output structure:
# build/lib/main/release/{platform}/{arch}/
#   ├── libjavaProfiler.so          # Stripped library (~1.2MB)
#   └── debug/
#       └── libjavaProfiler.so.debug # Debug symbols (~6MB)
```

**Key features:**
- Fully optimized (`-O3 -DNDEBUG`)
- Debug symbols extracted to separate file
- 69% size reduction in production binary
- Symbols linked via `.gnu_debuglink`

### 5. Static Analysis: Clang scan-build

The `scanbuild` plugin integrates Clang's static analyzer to detect bugs without running code.

**build.gradle.kts:**
```kotlin
plugins {
    id("com.datadoghq.scanbuild")
}

scanBuild {
    makefileDir.set(layout.projectDirectory.dir("src/test/make"))
    outputDir.set(layout.buildDirectory.dir("reports/scan-build"))
    analyzer.set("/usr/bin/clang++")
    parallelJobs.set(4)
    makeTargets.set(listOf("all", "test"))  // Optional: specify make targets
}
```

```bash
# Run static analysis
./gradlew scanBuild

# View HTML report
open build/reports/scan-build/*/index.html

# Or on Linux
xdg-open build/reports/scan-build/*/index.html
```

**What scan-build detects:**
- Null pointer dereferences
- Memory leaks
- Use of uninitialized values
- Dead stores (unused assignments)
- Division by zero
- API misuse
- Logic errors
- Buffer overflows

**Note:** scan-build is only available on Linux by default. The plugin will skip on macOS unless you have scan-build installed via Homebrew.

---

## How-To Guides

### Override Compiler

```bash
# Use specific compiler
./gradlew build -Pnative.forceCompiler=clang++
./gradlew build -Pnative.forceCompiler=g++-13
./gradlew build -Pnative.forceCompiler=/usr/local/bin/clang++

# The plugin validates the compiler exists and works
```

### Customize Source Directories

```kotlin
nativeBuild {
    version.set("1.2.3")
    cppSourceDirs.set(listOf(
        "src/main/cpp",
        "src/vendor/library"
    ))
    includeDirectories.set(listOf(
        "src/main/cpp",
        "src/vendor/library/include",
        "/usr/local/include"
    ))
}
```

### Add Custom Configurations

```kotlin
nativeBuild {
    version.set(project.version.toString())

    // Override standard configs
    buildConfigurations {
        // Create custom configuration
        register("production") {
            platform.set(com.datadoghq.native.model.Platform.LINUX)
            architecture.set(com.datadoghq.native.model.Architecture.X64)
            active.set(true)

            compilerArgs.set(listOf(
                "-O3",
                "-DNDEBUG",
                "-march=native",  // Optimize for current CPU
                "-flto",          // Link-time optimization
                "-fPIC"
            ))

            linkerArgs.set(listOf(
                "-Wl,--gc-sections",
                "-flto"
            ))
        }
    }
}
```

**Generated tasks:**
- `compileProduction`
- `linkProduction`
- `assembleProduction`

### Add Common Flags to All Configurations

```kotlin
nativeBuild {
    version.set(project.version.toString())

    // Apply to all configurations
    commonCompilerArgs(
        "-Wall",
        "-Wextra",
        "-Werror"
    )

    commonLinkerArgs(
        "-Wl,--as-needed"
    )
}
```

### Control Google Test Behavior

```kotlin
gtest {
    testSourceDir.set(layout.projectDirectory.dir("src/test/cpp"))
    mainSourceDir.set(layout.projectDirectory.dir("src/main/cpp"))

    // Custom Google Test location (macOS)
    googleTestHome.set(file("/usr/local/opt/googletest"))

    // Always enable assertions (remove -DNDEBUG)
    enableAssertions.set(true)

    // Keep debug symbols in release test builds
    keepSymbols.set(true)

    // Stop on first test failure
    failFast.set(true)

    // Always re-run tests (ignore up-to-date checks)
    alwaysRun.set(true)

    // Skip building native test support libraries
    buildNativeLibs.set(false)

    includes.from(
        "src/main/cpp",
        "third-party/include"
    )
}
```

### Skip Builds Selectively

```bash
# Skip all tests
./gradlew build -Pskip-tests

# Skip only gtest (keep Java tests)
./gradlew build -Pskip-gtest

# Skip all native compilation
./gradlew build -Pskip-native
```

### Cross-Platform Configuration

```kotlin
nativeBuild {
    buildConfigurations {
        // Linux x64 release
        register("linuxRelease") {
            platform.set(Platform.LINUX)
            architecture.set(Architecture.X64)
            active.set(PlatformUtils.currentPlatform == Platform.LINUX)
            // ... compiler/linker args
        }

        // macOS ARM release
        register("macosRelease") {
            platform.set(Platform.MACOS)
            architecture.set(Architecture.ARM64)
            active.set(PlatformUtils.currentPlatform == Platform.MACOS)
            // ... compiler/linker args
        }
    }
}
```

### Integrate with Java Resource Packaging

```kotlin
// Copy native libraries to Java resources
val copyReleaseLibs by tasks.registering(Copy::class) {
    from("build/lib/main/release")
    into(layout.buildDirectory.dir("resources/main/native"))

    dependsOn(tasks.named("assembleRelease"))
}

tasks.named("processResources") {
    dependsOn(copyReleaseLibs)
}

// Include in JAR
tasks.named<Jar>("jar") {
    from(layout.buildDirectory.dir("resources/main/native")) {
        into("native")
    }
}
```

### Configure Static Analysis with scan-build

The scan-build plugin requires a Makefile-based build for analysis. This is typically separate from the Gradle native build.

**Basic configuration:**
```kotlin
plugins {
    id("com.datadoghq.scanbuild")
}

scanBuild {
    // Directory containing Makefile (required)
    makefileDir.set(layout.projectDirectory.dir("src/test/make"))

    // Where to output HTML reports
    outputDir.set(layout.buildDirectory.dir("reports/scan-build"))

    // Clang analyzer to use
    analyzer.set("/usr/bin/clang++")

    // Parallel make jobs
    parallelJobs.set(4)

    // Make targets to build (default: ["all"])
    makeTargets.set(listOf("all"))
}
```

**Advanced configuration:**
```kotlin
scanBuild {
    makefileDir.set(layout.projectDirectory.dir("src/test/make"))
    outputDir.set(layout.buildDirectory.dir("reports/scan-build"))

    // Use specific clang version
    analyzer.set("/usr/bin/clang++-15")

    // Increase parallelism for faster analysis
    parallelJobs.set(Runtime.getRuntime().availableProcessors())

    // Analyze multiple targets
    makeTargets.set(listOf("library", "tests"))
}
```

**Example Makefile structure:**

Create `src/test/make/Makefile`:
```makefile
# Compiler (will be intercepted by scan-build)
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../../main/cpp

# Source files
SOURCES = $(wildcard ../../main/cpp/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Targets
all: library

library: $(OBJECTS)
	$(CXX) -shared -o libjavaProfiler.so $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) libjavaProfiler.so

.PHONY: all clean
```

**Integration with CI:**
```kotlin
// Make scanBuild part of verification
tasks.named("check") {
    dependsOn("scanBuild")
}
```

**Platform-specific configuration:**
```kotlin
import com.datadoghq.native.util.PlatformUtils
import com.datadoghq.native.model.Platform

if (PlatformUtils.currentPlatform == Platform.LINUX) {
    scanBuild {
        makefileDir.set(layout.projectDirectory.dir("src/test/make"))
        outputDir.set(layout.buildDirectory.dir("reports/scan-build"))
    }
}
```

---

## Tips and Tricks

### Performance Tips

#### 1. Parallel Compilation
Gradle automatically parallelizes compilation at the file level. Each `.cpp` file compiles independently.

```bash
# Use more parallel workers
./gradlew build --parallel --max-workers=8
```

#### 2. Incremental Builds
The plugin tracks:
- Source file changes
- Header file changes (via `-MMD` dependency tracking)
- Compiler flag changes

Only modified files recompile:
```bash
# First build
./gradlew assembleDebug  # Compiles all files

# Edit one file
vim src/main/cpp/profiler.cpp

# Second build
./gradlew assembleDebug  # Only recompiles profiler.cpp
```

#### 3. Build Faster During Development

```bash
# Use debug config (no optimization)
./gradlew assembleDebug

# Skip tests
./gradlew assembleDebug -Pskip-tests

# Use clang++ (generally faster than g++)
./gradlew assembleDebug -Pnative.forceCompiler=clang++
```

### Debugging Tips

#### 1. Verbose Compiler Output

```kotlin
tasks.withType<com.datadoghq.native.tasks.NativeCompileTask> {
    doFirst {
        println("Compiler: ${compiler.get()}")
        println("Args: ${compilerArgs.get()}")
        println("Sources: ${sources.files}")
    }
}
```

#### 2. Inspect Generated Build Files

```bash
# Debug symbols location
ls -lh build/lib/main/release/*/*/debug/

# Object files
ls -lh build/obj/main/release/

# Task dependency tree
./gradlew assembleRelease --dry-run
```

#### 3. Check Active Configurations

```bash
# View all build tasks
./gradlew tasks --group=build

# The plugin logs active configurations:
./gradlew assembleAll | grep "Active configurations"
```

#### 4. Validate Debug Symbol Extraction

**Linux:**
```bash
# Check if symbols are stripped
nm build/lib/main/release/linux/x64/libjavaProfiler.so | wc -l

# Verify debug link
readelf -p .gnu_debuglink build/lib/main/release/linux/x64/libjavaProfiler.so

# Check debug file
file build/lib/main/release/linux/x64/debug/libjavaProfiler.so.debug
```

**macOS:**
```bash
# Check stripped library
nm -gU build/lib/main/release/macos/arm64/libjavaProfiler.dylib

# Verify dSYM bundle
dwarfdump --uuid build/lib/main/release/macos/arm64/libjavaProfiler.dylib.dSYM
```

### Testing Tips

#### 1. Run Specific Test

```bash
# Run one test from specific config
./gradlew gtestDebug_test_callTraceStorage
```

#### 2. Test with Multiple Configurations

```bash
# Run tests with sanitizers in parallel
./gradlew gtestDebug gtestAsan gtestTsan --parallel
```

#### 3. Investigate Test Failures

```bash
# Enable detailed test output
./gradlew gtestDebug --info

# Run specific test binary directly
./build/bin/gtest/debug_test_callTraceStorage/test_callTraceStorage
```

#### 4. Test Environment Variables

ASan and TSan tests automatically set environment variables:
```kotlin
// In BuildConfiguration:
testEnvironment.put("ASAN_OPTIONS", "...")
testEnvironment.put("TSAN_OPTIONS", "...")

// Add custom variables:
buildConfigurations {
    named("debug") {
        testEnvironment.put("LOG_LEVEL", "debug")
        testEnvironment.put("TEST_DATA_DIR", "$projectDir/testdata")
    }
}
```

### Static Analysis Tips

#### 1. Reading scan-build Reports

```bash
# Run analysis
./gradlew scanBuild

# Open report in browser
open build/reports/scan-build/*/index.html

# Reports are organized by bug type:
# - Dead store: Unused assignments
# - Memory leak: Leaked allocations
# - Null dereference: Potential null pointer access
# - Uninitialized value: Use of uninitialized variables
```

#### 2. Focus on High-Priority Issues

scan-build categorizes bugs by severity. Start with:
1. **Logic errors** - Wrong behavior
2. **Memory errors** - Leaks, use-after-free
3. **Null pointer issues** - Crashes
4. **Dead code** - Optimization opportunities

#### 3. Incremental Analysis

```bash
# Analyze after significant changes
./gradlew scanBuild

# Compare with previous run
diff -u old-report/index.html build/reports/scan-build/*/index.html
```

#### 4. Customize Analyzer Options

```kotlin
scanBuild {
    makefileDir.set(layout.projectDirectory.dir("src/test/make"))
    outputDir.set(layout.buildDirectory.dir("reports/scan-build"))

    // Use latest clang for better analysis
    analyzer.set("/usr/bin/clang++-15")

    // Faster analysis with more parallelism
    parallelJobs.set(8)
}
```

#### 5. Integration with Code Review

```bash
# Run in CI before merging
./gradlew scanBuild

# Fail build on new issues (requires custom script)
if grep -q "bugs found" build/reports/scan-build/*/index.html; then
    echo "Static analysis found issues"
    exit 1
fi
```

#### 6. Suppressing False Positives

If scan-build reports false positives, add assertions in code:
```cpp
void processData(Data* data) {
    // Tell analyzer this can't be null
    assert(data != nullptr);

    // Now scan-build knows data is valid
    data->process();
}
```

#### 7. Combine with Other Tools

```bash
# Static analysis + runtime sanitizers = comprehensive coverage
./gradlew scanBuild        # Find logic errors
./gradlew gtestAsan        # Find memory errors
./gradlew gtestTsan        # Find race conditions
```

### CI/CD Tips

#### 1. Minimal CI Build
```bash
# Quick validation build
./gradlew assembleRelease -Pskip-tests
```

#### 2. Full CI Build
```bash
# Build all configs and run all tests
./gradlew assembleAll gtest
```

#### 3. CI with Sanitizers
```bash
# Test memory safety in CI
./gradlew gtestAsan gtestTsan

# These are conditionally skipped if libasan/libtsan not available
```

#### 4. CI with Static Analysis
```bash
# Run static analysis in CI (Linux only)
./gradlew scanBuild

# Archive reports as CI artifacts
# GitHub Actions example:
# - name: Upload scan-build reports
#   uses: actions/upload-artifact@v3
#   with:
#     name: scan-build-reports
#     path: build/reports/scan-build/

# GitLab CI example:
# artifacts:
#   paths:
#     - build/reports/scan-build/
#   when: always
```

#### 5. Comprehensive CI Pipeline
```bash
# Full verification pipeline
./gradlew clean \
    assembleAll \
    gtest \
    gtestAsan \
    gtestTsan \
    scanBuild

# This covers:
# - Compilation for all configs
# - Unit tests
# - Memory safety (ASan)
# - Thread safety (TSan)
# - Static analysis (scan-build)
```

#### 6. Release Artifact Packaging
```bash
# Build release with extracted debug symbols
./gradlew assembleRelease

# Package production library (stripped)
tar czf library.tar.gz \
    build/lib/main/release/linux/x64/libjavaProfiler.so

# Package debug symbols separately
tar czf library-debug.tar.gz \
    build/lib/main/release/linux/x64/debug/
```

### Platform-Specific Tips

#### macOS: Homebrew Google Test
```bash
# Install Google Test
brew install googletest

# Plugin auto-detects at:
# /opt/homebrew/opt/googletest (Apple Silicon)
# /usr/local/opt/googletest (Intel)
```

#### Linux: System Google Test
```bash
# Ubuntu/Debian
sudo apt-get install libgtest-dev libgmock-dev

# Fedora/RHEL
sudo dnf install gtest-devel gmock-devel
```

#### musl libc Detection
The plugin automatically detects musl libc and adds `-D__musl__`:
```bash
# Check musl detection
./gradlew assembleRelease | grep __musl__

# Force musl detection (advanced)
./gradlew -Pnative.musl=true assembleRelease
```

#### Linux: scan-build Installation

scan-build is typically available on Linux but needs separate installation:

```bash
# Ubuntu/Debian - includes clang static analyzer
sudo apt-get install clang-tools

# Fedora/RHEL
sudo dnf install clang-tools-extra

# Arch Linux
sudo pacman -S clang

# Verify installation
which scan-build
scan-build --version
```

**Common scan-build locations:**
- `/usr/bin/scan-build` (most distros)
- `/usr/lib/llvm-*/bin/scan-build` (Ubuntu with specific LLVM versions)

If you have multiple clang versions:
```bash
# List available scan-build versions
ls /usr/lib/llvm-*/bin/scan-build

# Use specific version in plugin
scanBuild {
    analyzer.set("/usr/lib/llvm-15/bin/clang++")
}
```

---

## Troubleshooting

### Compiler Not Found

**Problem:**
```
Could not find any suitable C++ compiler
```

**Solutions:**
1. Install a compiler:
   - macOS: `xcode-select --install`
   - Linux: `sudo apt-get install build-essential` or `sudo dnf install gcc-c++`

2. Force specific compiler:
   ```bash
   ./gradlew build -Pnative.forceCompiler=/path/to/compiler
   ```

### Google Test Not Found

**Problem:**
```
WARNING: Google Test not found - skipping native tests
```

**Solutions:**
1. Install Google Test (see Platform-Specific Tips above)

2. Set custom location (macOS):
   ```kotlin
   gtest {
       googleTestHome.set(file("/custom/path/googletest"))
   }
   ```

3. Skip tests if not needed:
   ```bash
   ./gradlew build -Pskip-gtest
   ```

### Sanitizer Libraries Not Available

**Problem:**
ASan/TSan configurations are inactive.

**Check availability:**
```bash
# Check for libasan
find /usr/lib /usr/local/lib -name "libasan.so*" 2>/dev/null

# Check for libtsan
find /usr/lib /usr/local/lib -name "libtsan.so*" 2>/dev/null
```

**Solutions:**
1. Install sanitizer libraries:
   - Ubuntu/Debian: `sudo apt-get install libasan6 libtsan0`
   - Fedora/RHEL: `sudo dnf install libasan libtsan`

2. Use clang (includes sanitizers):
   ```bash
   ./gradlew build -Pnative.forceCompiler=clang++
   ```

### Compilation Errors

**Problem:**
```
error: 'std::optional' is not a member of 'std'
```

**Solution:**
Ensure C++17 standard:
```kotlin
nativeBuild {
    commonCompilerArgs("-std=c++17")
}
```

### Linking Errors

**Problem:**
```
undefined reference to `pthread_create'
```

**Solution:**
Add missing linker flags:
```kotlin
buildConfigurations {
    named("debug") {
        linkerArgs.add("-lpthread")
    }
}
```

### Test Failures with ASan/TSan

**Problem:**
Tests pass in debug but fail with ASan/TSan.

**Analysis:**
This indicates real bugs! ASan/TSan found:
- Memory leaks
- Race conditions
- Use-after-free
- Buffer overflows

**Solutions:**
1. Review the sanitizer output carefully
2. Fix the underlying bug (don't suppress unless false positive)
3. Add suppressions only for false positives:
   ```bash
   # ASan suppressions
   echo "leak:third_party_library" >> gradle/sanitizers/asan.supp

   # TSan suppressions
   echo "race:false_positive_function" >> gradle/sanitizers/tsan.supp
   ```

### Clean Build Issues

**Problem:**
Build fails after clean.

**Solution:**
```bash
# Full clean including native artifacts
./gradlew clean

# Rebuild
./gradlew assembleAll
```

### Task Not Found

**Problem:**
```
Task 'assembleAsan' not found
```

**Cause:**
Configuration is inactive (sanitizer not available).

**Check:**
```bash
./gradlew tasks --group=build | grep -i asan
```

If not listed, the configuration is skipped on your platform.

### scan-build Not Found

**Problem:**
```
scan-build not found in PATH - scanBuild task will fail if executed
```

**Solutions:**
1. Install scan-build on Linux:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install clang-tools

   # Fedora/RHEL
   sudo dnf install clang-tools-extra

   # Arch Linux
   sudo pacman -S clang
   ```

2. Install on macOS (optional, not typical):
   ```bash
   brew install llvm
   # Add to PATH:
   export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
   ```

3. Verify installation:
   ```bash
   which scan-build
   scan-build --help
   ```

### scan-build Fails on macOS

**Problem:**
Plugin skips scan-build task on macOS.

**Explanation:**
By design, the plugin only runs scan-build on Linux. This matches typical CI environments.

**Solution:**
If you need scan-build on macOS:
1. Install via Homebrew (see above)
2. Modify plugin check (advanced):
   ```kotlin
   // Override platform check
   tasks.register("scanBuildMac", Exec::class) {
       workingDir = file("src/test/make")
       commandLine(
           "scan-build",
           "-o", "build/reports/scan-build",
           "make", "all"
       )
   }
   ```

### scan-build Reports No Issues

**Problem:**
scan-build runs but reports 0 bugs, even when issues exist.

**Possible causes:**
1. **Makefile not using compiler correctly:**
   ```makefile
   # Wrong - hardcoded command
   build:
       /usr/bin/g++ -o output source.cpp

   # Correct - use $(CXX) variable
   build:
       $(CXX) -o output source.cpp
   ```

2. **Precompiled objects:**
   ```bash
   # Clean before analysis
   cd src/test/make
   make clean
   ./gradlew scanBuild
   ```

3. **Compiler wrappers not intercepted:**
   ```bash
   # Verify scan-build is wrapping compiler
   ./gradlew scanBuild --info | grep "scan-build"
   ```

### scan-build Makefile Errors

**Problem:**
```
make: *** No rule to make target 'all'. Stop.
```

**Solution:**
Verify Makefile exists and has required targets:
```bash
# Check Makefile location
ls -la src/test/make/Makefile

# Test make directly
cd src/test/make
make all

# If it works, then try scan-build
./gradlew scanBuild
```

### scan-build Reports Inaccessible

**Problem:**
Can't find or open HTML reports.

**Solution:**
```bash
# Find the latest report directory
find build/reports/scan-build -name "index.html"

# Open with browser
open $(find build/reports/scan-build -name "index.html" | head -1)

# Or view summary in terminal
grep -A 5 "bugs found" build/reports/scan-build/*/index.html
```

---

## Advanced Topics

### Custom Task Integration

Hook into native build lifecycle:

```kotlin
// Run custom validation after compilation
tasks.named("compileRelease") {
    doLast {
        println("Compiled ${outputs.files.files.size} object files")
    }
}

// Custom post-link processing
tasks.named("linkRelease") {
    doLast {
        val library = outputs.files.singleFile
        println("Built library: ${library.absolutePath}")
        println("Size: ${library.length() / 1024}KB")
    }
}
```

### Multi-Project Builds

Share native configurations across projects:

**root/buildSrc/src/main/kotlin/NativeConventions.kt:**
```kotlin
fun Project.configureNative() {
    apply(plugin = "com.datadoghq.native-build")

    configure<NativeBuildExtension> {
        version.set(rootProject.version.toString())
        commonCompilerArgs("-Wall", "-Wextra")
    }
}
```

**subproject/build.gradle.kts:**
```kotlin
configureNative()

nativeBuild {
    cppSourceDirs.set(listOf("src/cpp"))
}
```

### Conditional Platform Builds

```kotlin
import com.datadoghq.native.util.PlatformUtils
import com.datadoghq.native.model.Platform

if (PlatformUtils.currentPlatform == Platform.LINUX) {
    tasks.register("packageDeb") {
        dependsOn("assembleRelease")
        doLast {
            // Create .deb package
        }
    }
}
```

---

## Further Reading

- [README.md](README.md) - Full reference documentation
- [Plugin source code](conventions/src/main/kotlin/) - Implementation details
- [Gradle documentation](https://docs.gradle.org/) - Gradle build system
- [Google Test documentation](https://google.github.io/googletest/) - Unit testing framework
