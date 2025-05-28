# Datadog Java Profiler Library
_Based on [async-profiler 2.8.3](https://github.com/jvm-profiling-tools/java-profiler/releases/tag/v2.8.3)_

## Disclaimer
This is not a fork of [async-profiler](https://github.com/jvm-profiling-tools/async-profiler). This is a work derived from __async-profiler__ but tailored very specifically for Datadog needs.
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
./gradle buildRelease
```

The resulting artifact will be in `ddprof-lib/build/libs/ddprof-<version>.jar`

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

## Working with upstream

Although this project still shares the git history with the upstream the code structure is different. This makes it dificult to reliably
cherry-pick the upstream changes. To make this easier we have a script that will prepare the upstream repository
and add it as 'cherry' remote to this repository.
This way you can cherry-pick the changes from the upstream repository with (relative) ease.

```bash
./utils/init_cherrypick_repo.sh # you need to run this only once

./utils/cherry.sh <commit>
# ... resolve conflicts, if any
./utils/cherry.sh --continue # to commit the resolved conflicts
```
