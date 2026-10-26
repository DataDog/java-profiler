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

Tasks are generated for each active build configuration (release, debug, asan, tsan, fuzzer,
coverage; see `ConfigurationPresets.kt`). Configuration availability depends on platform and
compiler capabilities (the build logs `Active configurations: ...` during configuration):
- **release/debug**: Always available
- **asan**: Available when the ASan runtime is found for the selected compiler (not on musl)
- **tsan**: Available when the TSan runtime is found for the selected compiler (not on musl)
- **fuzzer**: Available when clang with libFuzzer support is detected (not on musl)
- **coverage**: Only with `-PenableCoverage` (see [Coverage Tasks](#coverage-tasks))

In practice the sanitizer configs are active on Linux glibc CI images and usually inactive on
macOS with Apple clang, so tasks such as `gtestAsan` / `testAsan` simply do not exist there.

```
compile{Config}          # Compile C++ sources
link{Config}             # Link shared library
assemble{Config}         # Full build for configuration
assemble{Config}Jar      # Build JAR with native library
assembleAll              # Build all active configurations
build{Config}            # Not a registered task: the Gradle base-plugin rule build<ConfigurationName>
                         # resolves it on demand to assemble{Config}Jar (e.g. buildRelease); it is
                         # not listed by `tasks --all`. Prefer assemble{Config}Jar in scripts.
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
testAsan                 # Java tests with ASAN library (when asan config is active)
testTsan                 # Java tests with TSAN library (when tsan config is active)
testSlow{Config}         # Only tests tagged `slow` (regular test{Config} excludes them)
```

**Examples:**
```bash
./gradlew :ddprof-test:testRelease
./gradlew :ddprof-test:testDebug -Ptests=ProfilerTest
```

**Note**: Use `-Ptests` (not `--tests`) with config-specific test tasks. The `-Ptests` property works uniformly across all platforms. On glibc/macOS, config-specific tasks use Gradle's Test task type. On musl systems, they use Exec task type to bypass toolchain probing issues.

### C++ Unit Tests (Google Test)

```
gtest{Config}_{TestFile}  # Run one test binary; TestFile is the .cpp name without
                          # extension (e.g., gtestDebug_dictionary_ut)
gtest{Config}             # Run all tests for config
buildGtest{Config}        # Compile + link all gtest binaries for config without running them
gtest                     # Run all tests for all active configs
```

**Examples:**
```bash
./gradlew :ddprof-lib:gtestDebug              # All debug tests
./gradlew :ddprof-lib:gtest                   # All tests, all configs
```

### Stress Tests (JMH Benchmarks)

```
jmh                      # Run JMH benchmarks (-PjmhInclude=<regex> to filter)
jmhJar                   # Build executable JMH JAR (build/libs/stresstests.jar)
runStressTests           # Run the JMH jar's scenarios.counters benchmarks with the WhiteboxProfiler
chaosJar                 # Build the chaos harness jar (see TestingGuide, Tier 4)
reproJar                 # Build the reference-chain leak demo app (refchains_repro.jar)
```

`./gradlew runBenchmarks` resolves to `:ddprof-lib:runBenchmarks`, which delegates to
`:ddprof-lib:benchmarks:runBenchmark`.

## Application Tasks

### Unwinding Validator

```
runUnwindingValidator{Config}   # Run validator with config
runUnwindingValidator           # Delegates to release if available, otherwise debug
unwindingReport{Config}         # Generate markdown report
unwindingReport                 # Delegates to release if available, otherwise debug
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
scanBuild                # Run the Clang Static Analyzer via scan-build (:ddprof-lib, Linux only)
```

## Fuzz Testing

Fuzz tasks live in the `:ddprof-lib:fuzz` project. Targets are discovered from
`ddprof-lib/src/test/fuzz/fuzz_*.cpp`; `{TargetName}` is the file name without the `fuzz_`
prefix and `.cpp` suffix.

```
fuzz                     # Run all fuzz targets
buildFuzz                # Compile + link all fuzz targets without running them
listFuzzTargets          # Print discovered targets
fuzz_{TargetName}        # Run specific fuzz target
compileFuzz_{TargetName} # Compile fuzz target
linkFuzz_{TargetName}    # Link fuzz target
```

**Example:**
```bash
./gradlew :ddprof-lib:fuzz:listFuzzTargets
./gradlew :ddprof-lib:fuzz:fuzz_stringDictionary -Pfuzz-duration=120
```

Requires clang with `-fsanitize=fuzzer` (on macOS, Homebrew LLVM). Without it the per-target
`compileFuzz_*` / `linkFuzz_*` / `fuzz_*` tasks are not created and `fuzz` / `buildFuzz` are skipped
with a warning; `listFuzzTargets` still works.
Crashes are written to `ddprof-lib/fuzz/build/fuzz-crashes/`.

## Coverage Tasks

Exist only with `-PenableCoverage`. Prerequisites (gcovr 8.3+, gtest, make on Linux),
the debug-only scope of the C++ report, and container setup are in
[CodeCoverage](CodeCoverage.md).

```
:ddprof-lib:coverageReport          # C++ (gcovr) + Java (JaCoCo) reports; runs everything below
:ddprof-lib:checkCoverageTools      # Preflight: compiler, gcov, gtest, make; gcovr if the report is requested
:ddprof-lib:gtestCoverage           # gtests against the coverage config
:ddprof-test:testCoverage           # Java tests against the instrumented library, with JaCoCo
:ddprof-test:testSlowCoverage       # Same, for tests tagged `slow`
:ddprof-test:jacocoTestReport       # Java half of coverageReport
```

**Example:**
```bash
./gradlew :ddprof-lib:coverageReport -PenableCoverage
```

Reports are written to `ddprof-lib/build/reports/coverage/{cpp,java}/`. Java test
failures are deferred until both reports are written; `coverageReport` then fails.

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
  gtestRelease_<t>     gtestDebug_<t>      gtestAsan_<t>    (per-test tasks)
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
GitHub Actions (`.github/workflows/test_workflow.yml`) runs one config per matrix cell:
```bash
./gradlew -PCI -PkeepJFRs :ddprof-test:test<config> --no-daemon --parallel --build-cache --no-watch-fs
```
GitLab runs the C++ gtests via `:ddprof-lib:buildGtest<Config>` and then executes the
binaries directly (see [TestingGuide](TestingGuide.md)).

## Gradle Properties

See `gradle.properties.template` for all available properties:

| Property | Description |
|----------|-------------|
| `skip-tests` | Skip Java test execution (also gates gtest and fuzz tasks) |
| `skip-native` | Skip native C++ compilation |
| `skip-gtest` | Skip Google Test execution |
| `skip-fuzz` | Skip fuzz targets |
| `fuzz-duration` | Seconds per fuzz target (default 60) |
| `tests` | Test filter for `test{Config}` tasks (`-Ptests=Class.method`, `-Ptests=Class`, `-Ptests="*.Class"`) |
| `keepJFRs` | Keep JFR recordings after test runs |
| `validatorArgs` | Extra arguments for the unwinding validator |
| `with-libs` | Use pre-built native libraries from a directory instead of compiling |
| `native.forceCompiler` | Force specific C++ compiler (`clang++`, `g++`, or a path) |
| `enableFaultInjection` | Compile release/debug with `-D__FAULT_INJECTION__` |
| `enableSamplerPerf` | Compile release/debug with `-D__SAMPLER_PERF__` (see `doc/reference/SamplerPerfCounters.md`) |
| `enableCoverage` | Activate the `coverage` configuration and the coverage tasks (see [CodeCoverage](CodeCoverage.md)) |
| `ddprof_version` | Override project version |
| `CI` | Enable CI-specific behavior |
