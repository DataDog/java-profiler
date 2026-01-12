# Fuzz Testing for ddprof-lib

This directory contains libFuzzer-based fuzz targets for discovering bugs in the
Datadog Java Profiler's native C++ code.

## Prerequisites

- **clang** compiler with `-fsanitize=fuzzer` support (clang 6.0+)
- **libFuzzer** (bundled with clang)
- **AddressSanitizer** support (for memory error detection)

### Installation Instructions

#### Ubuntu/Debian (apt-based)
```bash
# Install clang and compiler-rt (includes libFuzzer)
sudo apt-get update
sudo apt-get install clang llvm

# For specific version (e.g., clang-15)
sudo apt-get install clang-15 llvm-15
```

#### RHEL/CentOS/Fedora (yum/dnf-based)
```bash
# Fedora
sudo dnf install clang compiler-rt llvm

# RHEL/CentOS (requires EPEL)
sudo yum install epel-release
sudo yum install clang compiler-rt llvm
```

#### Alpine Linux (apk-based)
```bash
# Install clang and compiler-rt
sudo apk add clang compiler-rt llvm

# Note: libFuzzer may not be available in older Alpine versions
# Check with: clang -fsanitize=fuzzer 2>&1 | grep -i fuzzer
```

#### macOS
```bash
# IMPORTANT: Xcode's clang does not include libFuzzer
# You MUST install LLVM via Homebrew:
brew install llvm

# The build system will automatically detect and use Homebrew LLVM
# No environment variables needed!
```

#### Verification

After installation, verify libFuzzer support:
```bash
# Test if libFuzzer is available
echo 'extern "C" int LLVMFuzzerTestOneInput(const char*, long) { return 0; }' | \
  clang++ -fsanitize=fuzzer -x c++ - -o /tmp/fuzz_test && \
  echo "✓ libFuzzer is available" || \
  echo "✗ libFuzzer not found"

# Clean up
rm -f /tmp/fuzz_test
```

### Troubleshooting

**"library 'libclang_rt.fuzzer_*.a' not found"**:
- On Ubuntu/Debian: Install `libclang-rt-*-dev` package
- On macOS: Use Homebrew LLVM instead of Xcode clang
- Check available sanitizer libraries:
  ```bash
  find /usr/lib /usr/local/lib $(brew --prefix 2>/dev/null)/lib -name "*clang_rt.fuzzer*" 2>/dev/null
  ```

**Build skips fuzz targets**:
- Run `./gradlew :ddprof-lib:fuzz:listFuzzTargets` to check if fuzzer is detected
- Check logs for "libFuzzer not available" warning

## Running Fuzz Tests

### Quick Start

Run all fuzz targets for 60 seconds each:
```bash
./gradlew :ddprof-lib:fuzz:fuzz
```

### Run Individual Targets

```bash
# DWARF parser fuzzer
./gradlew :ddprof-lib:fuzz:fuzz_dwarf

# Arguments parser fuzzer
./gradlew :ddprof-lib:fuzz:fuzz_arguments

# Buffer serialization fuzzer
./gradlew :ddprof-lib:fuzz:fuzz_buffer
```

### Configure Duration

```bash
# Run for 5 minutes per target
./gradlew :ddprof-lib:fuzz:fuzz -Pfuzz-duration=300
```

### List Available Targets

```bash
./gradlew :ddprof-lib:fuzz:listFuzzTargets
```

## Fuzz Targets

### fuzz_dwarf.cpp
**Target**: `DwarfParser::parse()` - DWARF exception frame parser

Parses `.eh_frame_hdr` sections from ELF files to build stack unwind tables.
This code runs in signal handler context, so crashes are JVM-fatal.

**Expected bugs**: Buffer over-reads, integer overflows in LEB128 decoding,
infinite loops from malformed structures.

### fuzz_arguments.cpp
**Target**: `Arguments::parse()` - Profiler argument parser

Processes configuration strings from JVM agent options and attach API.
User-controlled input with environment variable expansion.

**Expected bugs**: Buffer overflows in `expandFilePattern()`, hash collisions,
memory corruption from malformed strings.

### fuzz_buffer.cpp
**Target**: `Buffer::put*()` methods - JFR serialization primitives

**CRITICAL**: All bounds checks in Buffer are `assert()` only - disabled in
release builds! This fuzzer tests the assertions to catch overflow conditions
that would silently corrupt memory in production.

**Expected bugs**: Buffer overflows when assertions disabled, incorrect varint
encoding for edge-case values.

## Corpus

Seed corpus files are in `corpus/<target_name>/`. These provide starting points
for the fuzzer to understand the expected input format.

During fuzzing, libFuzzer will add new interesting inputs to the corpus
directory. These additions are machine-generated and should not be committed.

## Crash Artifacts

When the fuzzer finds a crash, it saves the triggering input to:
```
ddprof-lib/fuzz/build/fuzz-crashes/<target>-<hash>
```

To reproduce a crash:
```bash
# Build the fuzzer
./gradlew :ddprof-lib:fuzz:linkFuzz_dwarf

# Run with the crash file
ddprof-lib/fuzz/build/bin/fuzz/dwarf/dwarf <crash_file>
```

## Adding New Fuzz Targets

1. Create a new `.cpp` file in this directory (e.g., `fuzz_newfeature.cpp`)
2. Implement the `LLVMFuzzerTestOneInput` function:
   ```cpp
   extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
       // Parse or process the fuzzed data
       return 0;
   }
   ```
3. Optionally add seed corpus files in `corpus/fuzz_newfeature/`
4. The build system will automatically detect the new target

## CI Integration

Fuzz tests can be run in CI with a time limit:
```yaml
- name: Run fuzz tests
  run: ./gradlew :ddprof-lib:fuzz:fuzz -Pfuzz-duration=60
```

For continuous fuzzing, consider using OSS-Fuzz or ClusterFuzz.
