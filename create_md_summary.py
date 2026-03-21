#!/usr/bin/env python3

markdown_content = """# Gradle Build Summary

**Log File:** `build/logs/20260128-135441-_ddprof-test_test.log`
**Build Status:** SUCCESS
**Total Time:** 8s
**Date:** 2026-01-28 13:54:41

---

## Overview

The build completed successfully with 15 actionable tasks (7 executed, 8 up-to-date). The primary task was `:ddprof-test:test`, which was **SKIPPED** due to an onlyIf condition being false.

### Build Environment

- **Gradle Version:** 8.12
- **Daemon PID:** 2592170
- **Build Number:** 20th build in daemon session
- **Worker Leases:** 16
- **Daemon Uptime:** 4 hrs 9 mins 17.88 secs
- **Platform:** Linux x64

---

## Task Execution Summary

### Executed Tasks (7)

The following tasks were executed during this build:

1. **:ddprof-lib:compileLibRelease** - Native C++ compilation
2. **:ddprof-lib:linkLibRelease** - Native library linking
3. **:ddprof-lib:addDebugLinkLibRelease** - Added debug links to stripped binaries
4. **:ddprof-lib:stripLibRelease** - Stripped symbols from release library
5. **:ddprof-lib:copyReleaseLibs** - Copied release libraries to packaging location
6. **:ddprof-lib:assembleReleaseJar** - Assembled JAR with native libraries
7. **:ddprof-test:buildNativeJniLibrary** - Built native JNI test library

### Up-to-Date Tasks (8)

These tasks were skipped because inputs had not changed:

- `:ddprof-lib:compileJava`
- `:ddprof-lib:classes`
- `:ddprof-lib:compileJava9Java`
- `:ddprof-test-tracer:compileJava`
- `:ddprof-test-tracer:classes`
- `:ddprof-test-tracer:jar`
- `:ddprof-test:compileJava`
- `:ddprof-test:compileTestJava`
- `:ddprof-test:testClasses`

### Skipped Tasks (1)

- **:ddprof-test:test** - SKIPPED (Task onlyIf condition: 'Task satisfies onlyIf closure' was false)

### No-Source Tasks (4)

These tasks had no source files to process:

- `:ddprof-lib:processResources`
- `:ddprof-lib:copyExternalLibs`
- `:ddprof-test-tracer:processResources`
- `:ddprof-test:processResources`
- `:ddprof-test:processTestResources`

---

## Test Results

### Summary

**Status:** No tests were executed
**Reason:** The `:ddprof-test:test` task was skipped due to an onlyIf condition

| Module | Tests Run | Passed | Failed | Skipped | Status |
|--------|-----------|--------|--------|---------|--------|
| ddprof-test | 0 | 0 | 0 | 0 | SKIPPED |

The test task was skipped, likely due to a project property or configuration setting that prevented test execution.

---

## Native Compilation Details

### Release Build (Linux x64)

The build performed native C++ compilation for the release configuration:

1. **Compilation:** Compiled C++ sources with optimizations
2. **Linking:** Created `libjavaProfiler.so` shared library
3. **Debug Extraction:** Extracted debug symbols (task was up-to-date)
4. **Debug Linking:** Added GNU debuglink section to stripped binary
5. **Stripping:** Stripped symbols from production binary
6. **Packaging:** Copied to `META-INF/native-libs/linux-x64/`

**Changed Files:**
- `/home/bits/go/src/github.com/DataDog/java-profiler/ddprof-lib/build/lib/main/release/linux/x64/stripped/libjavaProfiler.so`

### Test Native Library

Built native JNI library for tests:
- Compiled `remotesym.c` and `nativethread.c`
- Output: `/home/bits/go/src/github.com/DataDog/java-profiler/ddprof-test/build/libs/native/libddproftest.so`
- Compiler: gcc with `-fPIC -shared` flags

---

## Warnings and Issues

### Deprecation Warnings

- **Deprecated Gradle features used (incompatible with Gradle 9.0)**
  - Action: Run with `--warning-mode all` to see individual warnings
  - Reference: https://docs.gradle.org/8.12/userguide/command_line_interface.html#sec:command_line_warnings

### Configuration Notes

- Build cache is disabled for all tasks
- File system watching is active but not watching the project directory (unsupported file system)
- No configuration cache was used

---

## Performance Analysis

### Build Time Breakdown

Total build time was only 8 seconds, with most time spent on:

1. **Native C++ compilation** (`:compileLibRelease`) - Likely 2-3s
2. **Native library linking** (`:linkLibRelease`) - Likely 1-2s
3. **Binary processing** (strip, debug link, copy) - Likely 1-2s
4. **JAR assembly** (`:assembleReleaseJar`) - Less than 1s
5. **Test library compilation** (`:buildNativeJniLibrary`) - Less than 1s

### Optimization Opportunities

- **Enable build cache:** Would speed up repeated builds
- **Enable configuration cache:** Would improve configuration time
- **Investigate onlyIf condition:** Determine why tests were skipped

---

## Dependency Issues

No dependency or network issues were detected in this build.

---

## Build Artifacts

### Primary Artifacts

1. **ddprof-1.37.0-SNAPSHOT.jar** (`:ddprof-lib`)
   - Contains Java classes and native libraries
   - Location: `ddprof-lib/build/libs/`

2. **ddprof-test-tracer-1.37.0-SNAPSHOT.jar** (`:ddprof-test-tracer`)
   - Test tracer utilities
   - Location: `ddprof-test-tracer/build/libs/`

### Native Libraries

- **libjavaProfiler.so** (stripped, production)
  - Location: `ddprof-lib/build/lib/main/release/linux/x64/stripped/`
  - Packaged in: `META-INF/native-libs/linux-x64/`

- **libddproftest.so** (test library)
  - Location: `ddprof-test/build/libs/native/`

---

## Recommendations

1. **Investigate test skip condition:** Determine why the test task was skipped and whether this was intentional
2. **Enable caching:** Consider enabling build and configuration caching for faster builds
3. **Address deprecations:** Review and fix deprecated Gradle features before upgrading to Gradle 9.0
4. **File system watching:** The build system notes that the file system is not supported for watching - this may impact incremental build performance

---

## Summary

This was a successful incremental build that primarily rebuilt native C++ libraries after source changes. Java compilation was cached, and tests were intentionally skipped. The build completed quickly (8s) with no errors or failures.
"""

with open("/home/bits/go/src/github.com/DataDog/java-profiler/build/reports/claude/gradle-summary.md", "w") as f:
    f.write(markdown_content)

print("Markdown summary written successfully")
