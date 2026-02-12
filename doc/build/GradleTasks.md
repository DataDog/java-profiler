# Gradle Tasks Reference

This document describes the custom Gradle tasks available in the java-profiler project.

## Quick Reference

| Task | Description |
|------|-------------|
| `./gradlew assembleRelease` | Build release native library and JAR |
| `./gradlew testRelease` | Run Java tests with release library |
| `./gradlew gtestDebug` | Run C++ unit tests (debug config) |
| `./gradlew spotlessApply` | Auto-format all source files |

## Build Tasks

### Native Library Compilation

Tasks are generated for each active build configuration (release, debug, asan, tsan, fuzzer).
Configuration availability depends on platform and compiler capabilities:
- **release/debug**: Always available
- **asan**: Available on Linux when libasan is found
- **tsan**: Available on Linux when libtsan is found
- **fuzzer**: Available when clang with libFuzzer support is detected

```
compile{Config}          # Compile C++ sources
link{Config}             # Link shared library
assemble{Config}         # Full build for configuration
assemble{Config}Jar      # Build JAR with native library
assembleAll              # Build all active configurations
```

**Examples:**
```bash
./gradlew assembleRelease     # Build release library
./gradlew assembleDebug       # Build debug library
./gradlew assembleAll         # Build all active configs
```

### JAR Tasks

```
jar                      # Standard JAR (requires external libs)
assembleReleaseJar       # JAR with release native library
assembleDebugJar         # JAR with debug native library
sourcesJar               # Sources JAR for publishing
javadocJar               # Javadoc JAR for publishing
```

## Test Tasks

### Java Tests (ddprof-test)

```
test{Config}             # Run Java tests with specified config
testRelease              # Java tests with release library
testDebug                # Java tests with debug library
testAsan                 # Java tests with ASAN library (Linux)
testTsan                 # Java tests with TSAN library (Linux)
```

**Examples:**
```bash
./gradlew :ddprof-test:testRelease
./gradlew :ddprof-test:testDebug -Ptests=ProfilerTest
```

**Note**: Use `-Ptests` (not `--tests`) with config-specific test tasks. The `--tests` flag only works with Gradle's Test task type, but config-specific tasks (testDebug, testRelease) use Exec task type to bypass toolchain issues on musl systems.

### C++ Unit Tests (Google Test)

```
gtest{Config}_{TestName}  # Run specific test (e.g., gtestDebug_SymbolAnalyzerTest)
gtest{Config}             # Run all tests for config
gtest                     # Run all tests for all configs
```

**Examples:**
```bash
./gradlew :ddprof-lib:gtestDebug              # All debug tests
./gradlew :ddprof-lib:gtest                   # All tests, all configs
```

### Stress Tests (JMH Benchmarks)

```
jmh                      # Run JMH benchmarks
jmhJar                   # Build executable JMH JAR
runStressTests           # Run stress tests with profiler
```

## Application Tasks

### Unwinding Validator

```
runUnwindingValidator{Config}   # Run validator with config
runUnwindingValidator           # Run validator (release or debug)
unwindingReport{Config}         # Generate markdown report
unwindingReport                 # Generate report (release or debug)
```

**Examples:**
```bash
./gradlew :ddprof-test:runUnwindingValidatorRelease
./gradlew :ddprof-test:runUnwindingValidatorRelease -PvalidatorArgs="--verbose"
```

## Code Quality Tasks

### Formatting (Spotless)

```
spotlessCheck            # Check formatting violations
spotlessApply            # Auto-fix formatting issues
```

### Static Analysis

```
scanbuild{Config}        # Run Clang Static Analyzer
```

## Fuzz Testing

```
fuzz_{TargetName}        # Run specific fuzz target
compileFuzz_{TargetName} # Compile fuzz target
linkFuzz_{TargetName}    # Link fuzz target
```

**Example:**
```bash
./gradlew :ddprof-lib:fuzz:fuzz_symbolAnalyzer
```

## Task Dependency Graph

```
                    ┌─────────────────┐
                    │  assembleAll    │
                    └────────┬────────┘
                             │
         ┌───────────────────┼───────────────────┐
         ▼                   ▼                   ▼
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│ assembleRelease │ │ assembleDebug   │ │ assembleAsan    │ ...
└────────┬────────┘ └────────┬────────┘ └────────┬────────┘
         │                   │                   │
         ▼                   ▼                   ▼
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│  linkRelease    │ │   linkDebug     │ │   linkAsan      │
└────────┬────────┘ └────────┬────────┘ └────────┬────────┘
         │                   │                   │
         ▼                   ▼                   ▼
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│ compileRelease  │ │  compileDebug   │ │  compileAsan    │
└─────────────────┘ └─────────────────┘ └─────────────────┘


                    ┌─────────────────┐
                    │     gtest       │
                    └────────┬────────┘
                             │
         ┌───────────────────┼───────────────────┐
         ▼                   ▼                   ▼
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│  gtestRelease   │ │  gtestDebug     │ │   gtestAsan     │
└────────┬────────┘ └────────┬────────┘ └────────┬────────┘
         │                   │                   │
    (per-test tasks)    (per-test tasks)    (per-test tasks)
```

## Common Workflows

### Full Build and Test
```bash
./gradlew assembleRelease :ddprof-test:testRelease :ddprof-lib:gtestRelease
```

### Quick Development Cycle
```bash
./gradlew assembleDebug :ddprof-test:testDebug -Ptests=MyTest
```

### Pre-commit Checks
```bash
./gradlew spotlessCheck :ddprof-lib:gtestDebug :ddprof-test:testDebug
```

### CI Pipeline
```bash
./gradlew -PCI assembleAll :ddprof-test:testRelease :ddprof-lib:gtest spotlessCheck
```

## Gradle Properties

See `gradle.properties.template` for all available properties:

| Property | Description |
|----------|-------------|
| `skip-tests` | Skip Java test execution |
| `skip-native` | Skip native C++ compilation |
| `skip-gtest` | Skip Google Test execution |
| `native.forceCompiler` | Force specific C++ compiler |
| `ddprof_version` | Override project version |
| `CI` | Enable CI-specific behavior |
