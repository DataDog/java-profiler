# Google Test Gradle Plugin

A reusable Gradle plugin for integrating Google Test C++ unit tests into Gradle builds. This plugin was extracted from the original `ddprof-lib/gtest` module to provide a clean, declarative API that can be reused across multiple C++ projects.

## Overview

The plugin automatically discovers C++ test files and creates compilation, linking, and execution tasks for each test across multiple build configurations (debug, release, asan, tsan, etc.). It handles:

- **Platform Detection**: Automatically filters configurations by OS and architecture
- **Compiler Detection**: Uses `CompilerUtils.findCxxCompiler()` to find the best available C++ compiler
- **Test Discovery**: Scans a directory for `.cpp` test files and creates tasks for each
- **Task Aggregation**: Creates per-config and master aggregation tasks for running multiple tests
- **Google Test Integration**: Automatically links with gtest, gmock, and platform-specific libraries
- **Assertion Control**: Can enable assertions by removing `-DNDEBUG` from compiler flags
- **Symbol Preservation**: Optionally keeps debug symbols in release builds for testing

## Usage

### Basic Configuration

```groovy
// Apply the plugin
apply plugin: GtestPlugin

// Configure Google Test
gtest {
    testSourceDir = file('src/test/cpp')
    mainSourceDir = file('src/main/cpp')

    includes = files(
        'src/main/cpp',
        "${javaHome()}/include",
        "${javaHome()}/include/${osIdentifier()}"
    )

    configurations = buildConfigurations

    // macOS: Specify Google Test location if not using Homebrew default
    if (os().isMacOsX()) {
        googleTestHome = file('/opt/homebrew/opt/googletest')
    }
}
```

### Advanced Configuration

```groovy
gtest {
    testSourceDir = file('src/test/cpp')
    mainSourceDir = file('src/main/cpp')

    includes = files('src/main/cpp', 'include')
    configurations = [debug, release, asan, tsan]

    // Enable assertions (remove -DNDEBUG) - defaults to true
    enableAssertions = true

    // Keep debug symbols in release builds for testing - defaults to true
    keepSymbols = true

    // Fail fast on first test failure - defaults to false
    failFast = false

    // Always re-run tests (disable up-to-date checking) - defaults to false
    alwaysRun = false

    // Custom Google Test locations (if not using defaults)
    gtestIncludePaths = ['macos': '/custom/path/include']
    gtestLibPaths = ['macos': '/custom/path/lib']

    // Linux: Build native test support libraries
    buildNativeLibs = true
    nativeLibsSourceDir = file('src/test/resources/native-libs')
    nativeLibsOutputDir = file('build/test/resources/native-libs')
}
```

## Configuration Properties

### Required Properties

- **`testSourceDir`** (DirectoryProperty): Directory containing C++ test files (*.cpp)
- **`mainSourceDir`** (DirectoryProperty): Directory containing main C++ source files
- **`includes`** (ConfigurableFileCollection): Include paths for compilation
- **`configurations`** (ListProperty<Object>): Build configurations to test (e.g., debug, release)

### Optional Properties

- **`googleTestHome`** (DirectoryProperty): Google Test installation directory (macOS)
- **`enableAssertions`** (Property<Boolean>): Remove `-DNDEBUG` to enable assertions (default: true)
- **`keepSymbols`** (Property<Boolean>): Skip minimizing flags for release gtest builds (default: true)
- **`failFast`** (Property<Boolean>): Stop on first test failure (default: false)
- **`alwaysRun`** (Property<Boolean>): Always re-run tests (default: false)
- **`gtestIncludePaths`** (MapProperty<String, String>): Custom Google Test include paths per platform
- **`gtestLibPaths`** (MapProperty<String, String>): Custom Google Test library paths per platform
- **`buildNativeLibs`** (Property<Boolean>): Build native test support libraries (Linux only, default: true)
- **`nativeLibsSourceDir`** (DirectoryProperty): Source directory for native test libraries
- **`nativeLibsOutputDir`** (DirectoryProperty): Output directory for built native test libraries

## Generated Tasks

### Per-Test Tasks

For each test file `foo_ut.cpp` in each matching configuration:

- **`compileGtest{Config}_{TestName}`**: Compile all main sources + test file
  - Example: `compileGtestDebug_foo_ut`
  - Uses SimpleCppCompile custom task
  - Combines main sources and test file into single compilation unit

- **`linkGtest{Config}_{TestName}`**: Link test executable with gtest libraries
  - Example: `linkGtestDebug_foo_ut`
  - Uses SimpleLinkExecutable custom task
  - Links with gtest, gtest_main, gmock, gmock_main, and platform libs

- **`gtest{Config}_{TestName}`**: Execute the test
  - Example: `gtestDebug_foo_ut`
  - Runs the compiled test executable
  - Respects `failFast` and `alwaysRun` settings

### Aggregation Tasks

- **`gtest{Config}`**: Run all tests for a specific configuration
  - Example: `gtestDebug`, `gtestRelease`
  - Depends on all test execution tasks for that config
  - Useful for running all debug or all release tests

- **`gtest`**: Run all tests across all configurations
  - Master aggregation task
  - Depends on all test execution tasks across all matching configs
  - Useful for comprehensive test runs

### Support Tasks (Linux Only)

- **`buildNativeLibs`**: Build native test support libraries
  - Only created if `buildNativeLibs = true`
  - Scans `nativeLibsSourceDir` for library source directories
  - Executes `make` in each directory to build test libraries
  - Test execution tasks depend on this if enabled

## Platform Support

The plugin automatically filters build configurations by platform:

- **macOS**: Uses Homebrew Google Test by default (`/opt/homebrew/opt/googletest`)
- **Linux**: Links with system Google Test libraries and includes `-lrt`
- **musl libc**: Automatically adds `-D__musl__` compiler flag when detected

Only configurations matching the current OS and architecture are processed.

## How It Works

### 1. Plugin Application

When applied to a project, the plugin creates a `GtestExtension` configuration object accessible via the `gtest {}` block.

### 2. Task Registration (afterEvaluate)

After project evaluation, the plugin:

1. Validates that `testSourceDir` and `configurations` are set
2. Checks if Google Test is available (via `hasGtest` project property)
3. Creates the master `gtest` aggregation task
4. Filters configurations by current platform/architecture
5. For each matching, active configuration:
   - Creates per-config aggregation task (`gtest{Config}`)
   - Discovers all `.cpp` files in `testSourceDir`
   - For each test file, creates compile, link, and execute tasks
   - Wires up task dependencies

### 3. Compiler and Linker Args

The plugin adjusts compiler and linker arguments:

**Compiler Args**:
- Removes `-DNDEBUG` if `enableAssertions = true`
- Ensures `-std=c++17` is used
- Adds `-D__musl__` on musl libc systems

**Linker Args**:
- For release configs with `keepSymbols = true`, skips minimizing flags
- Adds Google Test libraries: `-lgtest`, `-lgtest_main`, `-lgmock`, `-gmock_main`
- Adds platform libraries: `-ldl`, `-lpthread`, `-lm`
- On Linux, adds `-lrt`
- On macOS, adds `-L{googleTestHome}/lib` or default Homebrew path

### 4. Source Compilation

Each test is compiled by combining:
- All `.cpp` files from `mainSourceDir`
- The single test `.cpp` file

This creates a complete executable with both main library code and test code.

## Integration with Other Projects

### malloc-shim Example

```groovy
// malloc-shim/build.gradle
apply plugin: GtestPlugin

gtest {
    testSourceDir = file('src/test/cpp')
    mainSourceDir = file('src/main/cpp')

    includes = files(
        'src/main/cpp',
        'include'
    )

    configurations = [debug, release]
}
```

### Integration with Java Tests

The `ddprof-test` module shows how to integrate C++ gtest tasks with Java test tasks:

```groovy
buildConfigNames().each {
    def testTask = tasks.findByName("test${it}")
    def gtestTask = project(':ddprof-lib').tasks.findByName("gtest${it.capitalize()}")
    if (testTask && gtestTask) {
        testTask.dependsOn gtestTask
    }
}
```

This ensures C++ unit tests run before Java integration tests.

## Troubleshooting

### Google Test Not Found

If you see "WARNING: Google Test not found", check:

1. **macOS**: Install via Homebrew: `brew install googletest`
2. **Linux**: Install development packages: `sudo apt-get install libgtest-dev libgmock-dev`
3. Set `googleTestHome` to point to your installation
4. Verify `hasGtest` property is set correctly in your build

### No Tasks Created

If no tasks are created, check:

1. `testSourceDir` is set and contains `.cpp` files
2. `configurations` is set and not empty
3. At least one configuration matches your current platform/arch
4. At least one configuration has `active = true`

Enable debug logging by adding to your gradle.properties:
```properties
org.gradle.logging.level=debug
```

### Compilation Errors

If compilation fails:

1. Verify `includes` contains all necessary header paths
2. Check compiler args are appropriate for your platform
3. Ensure main source files compile independently
4. Review `compilerArgs` in your build configuration

### Linking Errors

If linking fails:

1. Verify Google Test libraries are installed
2. Check `googleTestHome` or `gtestLibPaths` are correct
3. Ensure platform-specific libraries are available
4. Review linker args in your build configuration

## Implementation Notes

### SimpleCppCompile Integration

The plugin uses the `SimpleCppCompile` task in simple mode:

```groovy
sources = fileTree(mainSourceDir) { include '**/*.cpp' } + files(testFile)
```

This combines main sources and test file without using source sets, avoiding complexity and potential issues with source set instantiation.

### Platform Detection

The plugin uses `osIdentifier()` and `archIdentifier()` functions from `common.gradle` to match configurations:

```groovy
def matches = (config.os == project.osIdentifier() &&
               config.arch == project.archIdentifier())
```

This ensures tasks are only created for the current platform.

### Task Dependencies

Task dependencies flow as follows:

```
gtestDebug_foo_ut (Exec)
  ↓ depends on
linkGtestDebug_foo_ut (SimpleLinkExecutable)
  ↓ depends on
compileGtestDebug_foo_ut (SimpleCppCompile)
```

Aggregation tasks depend on all test execution tasks:

```
gtestDebug
  ↓ depends on
  gtestDebug_foo_ut, gtestDebug_bar_ut, ...

gtest
  ↓ depends on
  gtestDebug_foo_ut, gtestRelease_foo_ut, ...
```

## Migration from ddprof-lib/gtest Module

If you're migrating from the old `ddprof-lib/gtest` module:

1. Remove `include ':ddprof-lib:gtest'` from `settings.gradle`
2. Remove `project(':ddprof-lib:gtest')` from dependencies
3. Apply `GtestPlugin` to your project
4. Configure the `gtest {}` block
5. Update task references from `project(':ddprof-lib:gtest')` to `project(':ddprof-lib')`
6. Delete the old `ddprof-lib/gtest` directory

## Future Enhancements

Potential future improvements:

- **XML Reports**: Generate JUnit XML format test reports
- **Test Filtering**: Run only tests matching a pattern
- **Parallel Execution**: Run tests in parallel with configurable concurrency
- **Test Timeouts**: Automatically timeout hung tests
- **Custom Arguments**: Pass arguments to test executables
- **Test Discovery Patterns**: Support for subdirectories and custom file patterns

## See Also

- `SimpleCppCompile.groovy` - Custom C++ compilation task
- `SimpleLinkExecutable.groovy` - Custom C++ linking task
- `CompilerUtils.groovy` - Compiler detection utilities
- `common.gradle` - Build configuration definitions
