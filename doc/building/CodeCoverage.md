<!-- Copyright 2026, Datadog, Inc. -->

# Code Coverage

`:ddprof-lib:coverageReport` produces two coverage reports from one run:

| Report | Tool | Sources | Output |
|--------|------|---------|--------|
| C++ | gcovr | gtest binaries + Java integration tests | `ddprof-lib/build/reports/coverage/cpp/index.html` |
| Java | JaCoCo | Java integration tests (incl. child JVMs) | `ddprof-lib/build/reports/coverage/java/html/index.html`, `.../java/jacoco.xml` |

Coverage is opt-in. Pass `-PenableCoverage`, or none of the coverage tasks exist.

```bash
./.claude/commands/build-and-summarize :ddprof-lib:coverageReport -PenableCoverage
```

A full run takes about 30 minutes. It builds an instrumented library and gtests,
then runs `gtestCoverage`, `:ddprof-test:testCoverage` and
`:ddprof-test:testSlowCoverage`.

## What the C++ Report Measures

The `coverage` build configuration (`configureCoverage` in `ConfigurationPresets.kt`)
is built on `configureDebug`: `-O0 -g -DDEBUG`, plus `--coverage
-fprofile-update=atomic`. The C++ report therefore covers **only the debug variant**
of the native code:

- Code under `#ifndef DEBUG` is never compiled into the coverage build. It never shows
  as covered, even if the release build runs it on every sample.
- Code under `#ifdef DEBUG` (test seams, `datadog.UnwindFailure` recording,
  `DEBUG_ASSERT_NOT_IN_SIGNAL()`) is compiled in and counts toward coverage, although it does not
  exist in the shipped library.
- Behavior that only differs with optimizations on (inlining, tail calls, frame
  layout seen by the stack walkers) is not exercised.

Read the C++ numbers as "lines the debug build executed", not as coverage of the
release library.

`-fprofile-update=atomic` is required. Plain counter updates race between profiler
threads and signal handlers, and produce negative branch counts (GCC bug 68080) that
gcovr refuses to parse.

## Prerequisites

`checkCoverageTools` runs before any coverage build or test. It reports every missing
tool at once, with an install hint, and fails before the long build starts.

| Tool | Needed for | Checked |
|------|-----------|---------|
| C++ compiler that links `--coverage -fprofile-update=atomic` | Instrumented library and gtests. Clang needs its profile runtime (`compiler-rt` / `libclang-rt-dev`), gcc needs libgcov | Always |
| gcov matching the compiler | gcovr reads `.gcda` files with it: `gcov-<N>` for `g++-<N>`, `llvm-cov-<N> gcov` for `clang++-<N>`, `xcrun llvm-cov gcov` for Apple clang. Clang vs. GCC is decided from the compiler's `--version` banner, not its name; a clang under another name (e.g. `c++` via update-alternatives) uses the `llvm-cov` next to the binary it resolves to, else `llvm-cov` on PATH | Always |
| Google Test | `gtestCoverage`. Without gtest the gtest tasks are skipped with only a warning, and the C++ report silently loses the gtest half | Always |
| make | `buildNativeLibs`, which builds the gtests' helper libraries | Linux only |
| gcovr **8.3+** | The C++ report. Older versions lack flags the report passes (`--gcov-ignore-parse-errors=negative_hits.warn_once_per_file`, `--gcov-suspicious-hits-threshold`). Distro packages are usually too old; install from PyPI | Only when `coverageReport` is in the task graph |

Pick a different compiler with `-Pnative.forceCompiler=<path>`. The gcov tool is
derived from that compiler's path.

## Tasks

All tasks exist only with `-PenableCoverage`.

```
:ddprof-lib:coverageReport          # Both reports; depends on all tasks below
:ddprof-lib:checkCoverageTools      # Preflight tool check; every coverage task depends on it
:ddprof-lib:gtestCoverage           # gtests against the coverage config (gtestCoverage_<test> per binary)
:ddprof-lib:assembleCoverageJar     # Instrumented library JAR (never published)
:ddprof-test:testCoverage           # Java tests against the instrumented library, with JaCoCo
:ddprof-test:testSlowCoverage       # Same, for tests tagged `slow`
:ddprof-test:jacocoTestReport       # Java half of coverageReport
```

`cleanGtestCoverageData` and `:ddprof-test:cleanLibCoverageData` delete old `.gcda`
files before the tests run, because gcov adds to existing counts. The coverage test
tasks therefore never report `UP-TO-DATE`.

JaCoCo instruments only `testCoverage` and `testSlowCoverage`. Other test tasks run
against unmodified bytecode, because JaCoCo's injected methods and probe arrays would
appear in the allocation and stack samples those tests assert on. Child JVMs started
by `AbstractProcessProfilerTest` get the agent through `JACOCO_AGENT_JAR` /
`JACOCO_CHILD_DIR` / `JACOCO_INCLUDES`. On musl, the test tasks are `Exec` tasks; the
agent is attached to them explicitly.

Within those tasks, every agent instruments only ddprof-lib's classes, the only classes
the report covers. The `includes` list names each class, derived from ddprof-lib's
source file names. A package wildcard would not narrow it: the tests share the
`com.datadoghq.profiler` package root, and JaCoCo's `*` also matches `.`.

## Test Failures

When `coverageReport` is in the task graph, failures in `testCoverage` and
`testSlowCoverage` are deferred: each failing task writes a marker file to
`ddprof-test/build/coverage-deferred-failures/`, and both reports are written first.
`:ddprof-test:checkCoverageTestFailures`, a finalizer of `coverageReport`, then fails
and names the failed tasks. As a finalizer it also runs when gcovr fails, so a gcovr
error does not hide test failures. Deferral is decided from the resolved task graph,
so it also applies to abbreviated task names (`covRep`).

Running `testCoverage` without the report fails on test failures as usual.
`gtestCoverage` failures are not deferred: the gtest plugin runs with `failFast`, so a
failing gtest stops the build before the report.

## Containers

`utils/run-containers-tests.sh` base images include gcovr from PyPI, and `llvm` on
glibc for the unversioned `llvm-cov`. The script reuses cached images, so a base image
cached before these packages were added lacks them, and so does every JDK test image
built on it. Pass `--rebuild-base` once: it rebuilds the base image and the JDK image
on top of it.

The script's `--config` does not accept `coverage`. Open a shell in the container and
run the task there:

```bash
./utils/run-containers-tests.sh --libc=glibc --jdk=21 --rebuild-base --shell
# inside the container:
./gradlew :ddprof-lib:coverageReport -PenableCoverage
```
