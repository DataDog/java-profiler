# Datadog Java Profiler Library
_Based on [async-profiler 2.8.3](https://github.com/jvm-profiling-tools/java-profiler/releases/tag/v2.8.3)_

## Disclaimer
This is not a fork of [async-profiler](https://github.com/jvm-profiling-tools/async-profiler). This is a work derived from __async-profiler__ but tailored very specifically for Datadog needs.
See [gritty details](#gritty-details) for more info.
If you need a full-fledged Java profiler head back to [async-profiler](https://github.com/jvm-profiling-tools/async-profiler)

## Build

### Prerequisites
1. JDK 8 or later (required for building)
2. Gradle (included in wrapper)
3. C++ compiler (gcc/g++ or clang)
4. Make (included in XCode on Macos)
5. Google Test (for unit testing)
   - On Ubuntu/Debian: `sudo apt install libgtest-dev`
   - On macOS: `brew install googletest`
   - On Alpine: `apk add gtest-dev`
6. clang-format 11 (for code formatting)
   - On Ubuntu/Debian: `sudo apt install clang-format-11`
   - On macOS: `brew install clang-format-11`
   - On Alpine: `apk add clang-format-11`

### Building the Project
1. Clone the repository:
```bash
git clone https://github.com/DataDog/java-profiler.git
cd java-profiler
```

2. Build a release version of the project:
```bash
./gradlew buildRelease
```

The resulting artifact will be in `ddprof-lib/build/libs/ddprof-<version>.jar`

#### Gritty details
To smoothen the absorption of the upstream changes, we are using parts of the upstream codebase in (mostly) vanilla form.

For this, we have several gradle tasks in [ddprof-lib/build.gradle](ddprof-lib/build.gradle):
- `cloneAsyncProfiler` - clones the [DataDog/async-profiler](https://github.com/DataDog/async-profiler) repository into `ddprof-lib/build/async-profiler` using the commit lock specified in [gradle/lock.properties](gradle/lock.properties)
  - in that repository, we are maintaining a branch called `dd/master` where we keep the upstream code in sync with the 'safe' changes from the upstream `master` branch
  - cherry-picks into that branch should be rare and only done for critical fixes that are needed in the project
  - otherwise, we should wait for the next upstream release to avoid conflicts
- `copyUpstreamFiles` - copies the selected upstream source files into the `ddprof-lib/src/main/cpp-external` directory
- `patchUpstreamFiles` - applies unified patches to upstream files for ASan compatibility, memory safety, and API extensions

Since the upstream code might not be 100% compatible with the current version of the project, we need to provide adapters.
The adapters are sharing the same file name as the upstream files but are suffixed with `_dd` (e.g. `arch_dd.h`).

In case we need to adapt a class from the upstream codebase, we put the adapter class into `ddprof` namespace to avoid
conflicts with the upstream code. This allows us to use the upstream code as-is while still providing the necessary modifications for our use case.

See [ddprof-lib/src/main/cpp/stackWalker_dd.h](ddprof-lib/src/main/cpp/stackWalker_dd.h) for an example of how we adapt the upstream code to fit our needs.

### Unified Patching System

The project uses a unified configuration-driven patching system to apply modifications to upstream source files:

- **Configuration File**: All patches are defined in `gradle/patching.gradle` using structured Gradle DSL
- **Direct Source Modification**: Patches are applied directly to upstream source files using regex-based find/replace
- **Idempotent Operations**: Each patch includes checks to prevent double-application
- **Validation System**: Pre-patch validation ensures upstream structure hasn't changed incompatibly
- **Single Unified Task**: One `patchUpstreamFiles` task replaces multiple fragmented patch tasks

## Patch Configuration Structure

Patches are defined in `gradle/patching.gradle` with this structure:

```groovy
ext.upstreamPatches = [
  "filename.cpp": [
    validations: [
      [contains: "expected_function"],
      [contains: "expected_class"]
    ],
    operations: [
      [
        type: "function_attribute",
        name: "Add ASan compatibility attribute", 
        find: "(bool\\s+StackFrame::unwindStub\\s*\\()",
        replace: "__attribute__((no_sanitize(\"address\"))) \$1",
        idempotent_check: "__attribute__((no_sanitize(\"address\"))) bool StackFrame::unwindStub("
      ]
    ]
  ]
]
```

### Patch Operation Types

1. **function_attribute**: Add attributes (like `__attribute__`) to function declarations
2. **expression_replace**: Replace unsafe code patterns with safe equivalents
3. **method_declaration**: Add new method declarations to class definitions  
4. **method_implementation**: Add complete method implementations to source files

### Adding New Patches

1. **Edit Configuration**: Add patch definition to `gradle/patching.gradle`
2. **Add Validations**: Ensure expected code structure exists
3. **Define Operations**: Specify find/replace patterns with appropriate type
4. **Include Idempotency**: Add `idempotent_check` to prevent double-application
5. **Test Thoroughly**: Verify patch works with clean upstream files

For detailed syntax documentation, see the comprehensive comments in `gradle/patching.gradle`.

## Claude Code Integration

This project includes Claude Code commands for streamlined development workflows when using [Claude Code](https://claude.ai/code):

### Available Commands

#### `/build-and-summarize <gradle-tasks...>`
Automated build execution with intelligent log analysis:
```bash
# Build with automated analysis
/build-and-summarize buildRelease

# Run tests with summary
/build-and-summarize testDebug

# Custom gradle tasks
/build-and-summarize clean buildDebug testDebug
```

**Features:**
- Executes Gradle builds with appropriate logging (`-i --console=plain`)
- Captures timestamped build logs in `build/logs/`
- Automatically analyzes build results using the gradle-logs-analyst agent
- Generates structured reports: `build/reports/claude/gradle-summary.md` and `build/reports/claude/gradle-summary.json`
- Extracts key information: build status, failed tasks, test results, warnings, and performance metrics

#### `/compare-and-patch <filename>`
Upstream/local file comparison and patch analysis:
```bash
# Analyze differences between upstream and local versions
/compare-and-patch stackFrame.h
/compare-and-patch symbols.cpp
/compare-and-patch buffers.h
```

**Features:**
- Automatically resolves upstream (`ddprof-lib/build/async-profiler/src/`) and local (`ddprof-lib/src/main/cpp/`) file paths
- Intelligently compares files while ignoring newline and copyright-only changes
- Uses the patch-analyst agent to generate comprehensive analysis
- Creates structured patch reports: `build/reports/claude/patches/<file>.patch.json` and `build/reports/claude/patches/<file>.patch.md`
- Identifies required patch operations compatible with the unified patching system
- Handles cases where files are Datadog-specific additions with no upstream equivalent

### Integration Benefits

These commands complement the existing patching workflow by providing:
- **Automated Analysis**: Intelligent parsing of build logs and patch requirements
- **Structured Output**: Machine-readable JSON and human-readable Markdown reports
- **Consistency**: Standardized analysis format across all patch operations
- **Efficiency**: Streamlined workflow for patch development and maintenance
- **Documentation**: Automatic generation of patch documentation

### Usage in Development Workflow

1. **Build Analysis**: Use `/build-and-summarize` to quickly identify build issues and performance bottlenecks
2. **Patch Development**: Use `/compare-and-patch` to analyze upstream changes and generate patch requirements
3. **Maintenance**: Regular patch analysis helps maintain compatibility with upstream updates

The generated reports integrate seamlessly with the existing `gradle/patching.gradle` configuration system, making it easier to maintain and update patches as the upstream codebase evolves.

## Testing

### Unit Tests
The project includes both Java and C++ unit tests. You can run them using:

```bash
# Run all tests
./gradlew test

# Run specific test configurations
./gradlew testRelease  # Run release build tests
./gradlew testDebug    # Run debug build tests
./gradlew testAsan     # Run tests with ASan
./gradlew testTsan     # Run tests with TSan

# Run C++ unit tests only
./gradlew gtestDebug   # Run C++ tests in debug mode
./gradlew gtestRelease # Run C++ tests in release mode
```

### Test Options
- Skip all tests: `./gradlew build -Pskip-tests`
- Keep JFR recordings: `./gradlew test -PkeepJFRs`
- Skip native build: `./gradlew build -Pskip-native`
- Skip C++ tests: `./gradlew build -Pskip-gtest`

### Cross-JDK Testing
`JAVA_TEST_HOME=<path to test JDK> ./gradlew testDebug`

## Unwinding Validation Tool

The project includes a comprehensive unwinding validation tool that tests JIT compilation unwinding scenarios to detect stack frame issues. This tool validates the profiler's ability to correctly unwind stack frames during complex JIT compilation scenarios.

### Running the Unwinding Validator

```bash
# Run all unwinding validation scenarios (release or debug build required)
./gradlew :ddprof-test:runUnwindingValidator

# Run specific scenario
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--scenario=C2CompilationTriggers"

# Generate markdown report for CI
./gradlew :ddprof-test:unwindingReport

# Show available options
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--help"
```

### Available Scenarios

The validator includes 13 specialized scenarios targeting different unwinding challenges:

- **C2CompilationTriggers** - Heavy computational workloads that trigger C2 compilation
- **OSRScenarios** - On-Stack Replacement compilation scenarios
- **ConcurrentC2Compilation** - Concurrent C2 compilation stress testing
- **C2DeoptScenarios** - C2 deoptimization and transition edge cases
- **ExtendedJNIScenarios** - Extended JNI operation patterns
- **MultipleStressRounds** - Multiple concurrent stress rounds
- **ExtendedPLTScenarios** - PLT (Procedure Linkage Table) resolution scenarios
- **ActivePLTResolution** - Intensive PLT resolution during profiling
- **ConcurrentCompilationStress** - Heavy JIT compilation + native activity
- **VeneerHeavyScenarios** - ARM64 veneer/trampoline intensive workloads
- **RapidTierTransitions** - Rapid compilation tier transitions
- **DynamicLibraryOps** - Dynamic library operations during profiling
- **StackBoundaryStress** - Stack boundary stress scenarios

### Output Formats

The validator supports multiple output formats:

```bash
# Text output (default)
./gradlew :ddprof-test:runUnwindingValidator

# JSON format for programmatic analysis
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--output-format=json --output-file=unwinding-report.json"

# Markdown format for documentation
./gradlew :ddprof-test:runUnwindingValidator -PvalidatorArgs="--output-format=markdown --output-file=unwinding-report.md"
```

### CI Integration

The unwinding validator is automatically integrated into GitHub Actions CI pipeline:

- Runs only on **debug builds** in CI (provides clean measurements without optimization interference)
- Generates rich markdown reports displayed directly in job summaries
- Creates downloadable report artifacts for historical analysis
- Fails builds when critical unwinding issues are detected

The validator provides immediate visibility into unwinding quality across all supported platforms and Java versions without requiring artifact downloads.

### Understanding Results

The tool analyzes JFR (Java Flight Recorder) data to measure:

- **Error Rate** - Percentage of samples with unwinding failures (`.unknown()`, `.break_interpreted()`)
- **Native Coverage** - Percentage of samples successfully unwound in native code
- **Sample Count** - Total profiling samples captured during validation
- **Error Types** - Breakdown of specific unwinding failure patterns

Results are categorized as:
- 🟢 **Excellent** - Error rate < 0.1%
- 🟢 **Good** - Error rate < 1.0%
- 🟡 **Moderate** - Error rate < 5.0%
- 🔴 **Needs Work** - Error rate ≥ 5.0%

## Release Builds and Debug Information

### Split Debug Information
Release builds automatically generate split debug information to optimize deployment size while preserving debugging capabilities:

- **Stripped libraries** (~1.2MB): Production-ready binaries with symbols removed for deployment
- **Debug symbol files** (~6.1MB): Separate `.debug` files containing full debugging information
- **Debug links**: Stripped libraries include `.gnu_debuglink` sections pointing to debug files

### Build Artifacts Structure
```
ddprof-lib/build/
├── lib/main/release/linux/x64/
│   ├── libjavaProfiler.so              # Original library with debug symbols
│   ├── stripped/
│   │   └── libjavaProfiler.so          # Stripped library (83% smaller)
│   └── debug/
│       └── libjavaProfiler.so.debug    # Debug symbols only
├── native/release/
│   └── META-INF/native-libs/linux-x64/
│       └── libjavaProfiler.so          # Final stripped library (deployed)
└── native/release-debug/
    └── META-INF/native-libs/linux-x64/
        └── libjavaProfiler.so.debug    # Debug symbols package
```

### Build Options
- **Skip debug extraction**: `./gradlew buildRelease -Pskip-debug-extraction=true`
- **Debug extraction requires**: `objcopy` (Linux) or `dsymutil` (macOS)
  - Ubuntu/Debian: `sudo apt-get install binutils`
  - Alpine: `apk add binutils`
  - macOS: Included with Xcode command line tools

## Development

### Code Quality
The project uses several tools for code quality:

1. clang-format for C++ code formatting
2. scan-build for static analysis
3. cppcheck for additional C++ checks

Run code quality checks:
```bash
# Run scan-build (this will use the scan-build binary)
./gradlew scanBuild

# Run cppcheck (if configured)
./gradlew cppcheck

# Run spotless (including code formatting)
./gradlew spotlessApply
```

### Debugging
**!TODO!**

### Stress Tests
The project includes JMH-based stress tests:

```bash
# Run all stress tests
./gradlew :ddprof-stresstest:runStressTests

### Common Issues
1. If you encounter strange crashes Asan:
   ```bash
   sudo sysctl vm.mmap_rnd_bits=28
   ```

2. For ASan/TSan issues, ensure you have the required libraries installed:
   - ASan: `libasan`
   - TSan: `libtsan`

## Contributing
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run tests: `./gradlew test`
5. Submit a pull request

## License
This project is licensed under the Apache License 2.0 - see the LICENSE file for details.

## Usage

### Example

Download the latest version of dd-trace-java and add `-Ddd.profiling.ddprof.debug.lib`. Example of a command line:
```bash
DD_SERVICE=your-service DD_TRACE_DEBUG=true java -javaagent:./temp/dd-java-agent.jar -Ddd.profiling.enabled=true -Ddd.profiling.ddprof.enabled=true -Ddd.profiling.ddprof.liveheap.enabled=true -Ddd.profiling.upload.period=10 -Ddd.profiling.start-force-first=true -Ddd.profiling.ddprof.debug.lib=~/dd/java-profiler/ddprof-lib/build/lib/main/debug/linux/x64/libjavaProfiler.so -XX:ErrorFile=${PWD}/hs_err_pid%p.log -XX:OnError='java -jar temp/dd-java-agent.jar uploadCrash hs_err_pid%p.log' -jar ./temp/renaissance-gpl-0.15.0.jar akka-uct -r 5
```

### Consuming the artifact

For dd-trace-java you just need to set the `ddprof.jar` project property.
Eg. you can run the gradle build like this - ./gradlew clean -Pddprof.jar=file://<path-to-artifact.jar> :dd-java-agent:shadowJar` - which will result in a custom `dd-java-agent.jar` build containing your test version of Java profiler.
