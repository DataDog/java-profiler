# Testing Guide

This document describes the complete test strategy for the java-profiler project:
what runs where, what each tier is designed to catch, and how to run each tier
locally.

## Overview

Tests are split across four tiers based on what they detect and what infrastructure
they require:

| Tier | System | When | Sanitizers | Purpose |
|------|--------|------|-----------|---------|
| **C++ unit tests** | GitLab | Every branch push | ASan + TSan (+ optimised release build) | Data races and memory errors in native internals |
| **Java functional tests** | GitHub Actions | Every PR/push (debug); nightly (ASan, slow tests) | ASan (nightly or `test:asan` label) | Correctness + memory errors in JVMTI paths |
| **dd-trace integration** | GitLab | Every branch push (not `release/*`) | None | Compatibility with the tracer agent |
| **Chaos / reliability** | GitLab | Scheduled pipelines; PRs with `test:reliability` label | None | Long-duration stability and probabilistic crash detection |

---

## Tier 1 — C++ Unit Tests (Every Branch Push)

**Pipeline:** `.gitlab/sanitizer-tests/.gitlab-ci.yml`, `sanitizer` stage

**Jobs:** `gtest-asan-amd64`, `gtest-tsan-amd64`, `gtest-asan-arm64`, `gtest-tsan-arm64`,
`gtest-release-amd64`, `gtest-release-arm64`

**Gradle tasks:** `:ddprof-lib:buildGtestAsan`, `:ddprof-lib:buildGtestTsan`,
`:ddprof-lib:buildGtestRelease` (compile + link only). The CI job then runs each
binary under `ddprof-lib/build/bin/gtest/<config>_<test>/` directly from the shell,
because the Gradle daemon swallows child-process output when fd 1/2 are not a terminal.

**Runs on:** amd64 and aarch64, using the standard `BUILD_IMAGE_X64` / `BUILD_IMAGE_ARM64`
images, on every branch push. Skipped for GitLab merge-request pipelines and for
JDK-integration triggers (`JDK_VERSION`/`DEBUG_LEVEL`/`HASH`/`DOWNSTREAM` set).

The `release` jobs are not sanitizers: they are the only jobs that compile the gtests
with optimisation, so they catch defects that only appear once the optimiser runs
(e.g. a fixture frame folded away by a tail call). Both sanitizer presets build
without `-O` and with `-fno-optimize-sibling-calls`.

The C++ gtest suite in `ddprof-lib/src/test/cpp/` exercises profiler internals
directly, without a JVM. This makes both ASan and TSan effective:

- **ASan** (`-fsanitize=address,undefined`) detects buffer overflows, use-after-free,
  and pointer arithmetic errors in the signal handler path and native data structures.
- **TSan** (`-fsanitize=thread`) detects data races between signal handlers, profiling
  threads, and class-unload callbacks — exactly the class of bug most likely to
  produce intermittent JVM crashes in the field.

TSan is only viable at this tier. The JVM binary contains intentional unsynchronized
patterns (lock-free GC internals, biased locking) that produce too many false
positives in the Java functional tier. `gradle/sanitizers/tsan.supp` captures
suppressions from earlier attempts. The CI jobs run the gtest binaries directly with no
`TSAN_OPTIONS`, so it is not applied there. Running `:ddprof-lib:gtestTsan` through Gradle
does pass the tsan config's `TSAN_OPTIONS` (including `suppressions=gradle/sanitizers/tsan.supp`)
to the binaries.

**Why GitLab and not GitHub Actions:** TSan requires `vm.mmap_rnd_bits ≤ 28` and its
re-exec fallback (`personality(ADDR_NO_RANDOMIZE)`) to handle ASLR conflicts. GitHub
Actions' ubuntu-latest runners have `vm.mmap_rnd_bits=32` and their seccomp profile
blocks the `personality` syscall. The Datadog GitLab runners have stable kernel
settings tuned for benchmark workloads.

**Key test files:**

| File | Covers |
|------|--------|
| `dictionary_ut.cpp` / `stringDictionary_ut.cpp` | `Dictionary` / `StringDictionary` lookup, bounded insert, collect and clear |
| `thread_teardown_safety_ut.cpp` | Signal delivery during `ProfiledThread` TLS clear and delete |
| `profiler_null_calltrace_buffer_ut.cpp` | Null calltrace buffer guard in the JVMTI sample path (PROF-14679) |
| `stress_callTraceStorage.cpp` | `CallTraceStorage` under concurrent write pressure |
| `test_callTraceStorage.cpp` | `CallTraceStorage` buffer swap correctness |
| `sigaction_interception_ut.cpp` | `sigaction` interception correctness and re-entrancy |
| `signalOrigin_ut.cpp` | Signal origin detection and classification |
| `spinLock_ut.cpp` | `SpinLock` / `OptionalSharedLockGuard` spin budget and contention |

**Local run:**
```bash
# Individual sanitizer configs (Linux only; asan/tsan are inactive on macOS
# and on musl, so these tasks do not exist there)
./gradlew :ddprof-lib:gtestAsan
./gradlew :ddprof-lib:gtestTsan

# All active configs on this host
./gradlew :ddprof-lib:gtest

# Specific test: gtest<Config>_<file name without .cpp>
./gradlew :ddprof-lib:gtestAsan_dictionary_ut
```

Prerequisites on Ubuntu:
```bash
sudo apt-get install -y libgtest-dev libgmock-dev cmake g++ clang
```

The sanitizer runtimes are bundled with `g++` and `clang` on modern Ubuntu — no
separate `libasan` or `libtsan` package is needed.

On TSan failure the report is written to stderr and appears directly in the GitLab
job log.

---

## Tier 2 — Java Functional Tests (GitHub Actions)

**Workflows:** `.github/workflows/ci.yml` (PRs and pushes) and
`.github/workflows/nightly.yml`, both calling the reusable `test_workflow.yml`

**Gradle task:** `:ddprof-test:test<Config>` (or `:ddprof-test:testSlow<Config>` for
slow tests), with `-Pskip-gtest` in the nightly runs

**Runs on:** amd64 and aarch64 × glibc and musl ×
HotSpot / OpenJ9 / GraalVM / IBM / Liberica across JDK 8–25. The exact JDK matrix
per platform lives in `test_workflow.yml`; musl jobs drop `asan`/`tsan` configs.

**Triggers:**
- `ci.yml`: every PR and push runs the `debug` config; PR labels add more (below).
- `nightly.yml`: 03:00 UTC (and `workflow_dispatch`) runs `asan`, slow `debug`, slow
  `asan`, and a 120 s fuzz run (`:ddprof-lib:fuzz:fuzz -Pfuzz-duration=120`).

The Java functional tests run the profiler as a JVMTI agent attached to a real JVM
and assert correctness: allocation profiling reports the right classes, CPU samples
land on the right frames, class unloading is handled cleanly, wall-clock profiling
produces expected output.

ASan is applied here even though the JVM is not instrumented, because
`libjavaProfiler.so` is instrumented and ASan intercepts memory errors in JVMTI
callback paths — actual `GetStackTrace` calls, real `SampledObjectAlloc` events, real
class load/unload sequences — that cannot be fully replicated in C++ unit tests.

TSan is not run against the Java functional tests (see Tier 1 rationale above).

C++ gtests are skipped in the nightly (`-Pskip-gtest`) because they already run on
every branch push in Tier 1.

**Test configurations triggered by PR labels** (optional, in addition to the always-on
debug build):

| Label | Effect |
|-------|--------|
| `test:release` | Run Java functional tests with release library |
| `test:asan` | Run Java functional tests with ASan library on the PR |
| `test:tsan` | Run Java functional tests with TSan library on the PR (expect JVM false positives) |
| `test:fuzz` | Run the libFuzzer targets on the PR (GitHub Actions `fuzz` job) |
| `test:reliability` | Run the Tier 4 reliability + chaos matrix as a GitLab child pipeline |

**Local run:**
```bash
# Match the nightly configuration
./gradlew :ddprof-test:testAsan -Pskip-gtest

# Run against a specific JDK and libc in a container (close to CI)
./utils/run-containers-tests.sh --config=asan --jdk=21 --libc=glibc

# Run a single test
./gradlew :ddprof-test:testAsan -Ptests=AllocationProfilerTest -Pskip-gtest
```

On failure the workflow reports affected scenarios to Slack and uploads test reports
as artifacts.

---

## Tier 3 — dd-trace Integration Tests (GitLab, Every Push)

**Pipeline:** `.gitlab/dd-trace-integration/.gitlab-ci.yml`

**Runs on:** amd64 and aarch64 × glibc and musl × HotSpot + OpenJ9, JDK 8–25

**Triggers:** every branch push; skipped on `release/*` branches, when
`CI_PIPELINE_SOURCE` is `merge_request_event` (GitLab merge-request pipeline), or when
JDK integration variables are set (`JDK_VERSION`, `DEBUG_LEVEL`, `HASH`, `DOWNSTREAM`)

This tier patches the latest `dd-java-agent.jar` snapshot with the locally built
`ddprof.jar` and runs integration tests against the combined agent. The patch
replaces the bundled (relocated) profiler classes inside the agent with the version
under test, keeping the classloader/relocation path identical to production.

It tests end-to-end agent startup, profiling data collection, and tracer/profiler
co-existence across the full JDK × libc matrix. Failures are posted as PR comments
and published to GitHub Pages as a compatibility matrix.

No sanitizers are applied here. The goal is compatibility verification, not crash
or race detection.

**Manual trigger:** The `DD_TRACE_VERSION` variable can be set to test against a
specific dd-java-agent snapshot version rather than auto-detecting the latest.

---

## Tier 4 — Chaos and Reliability (GitLab)

**Pipelines:** `.gitlab/reliability/.gitlab-ci.yml` (scheduled pipelines only) and
`.gitlab/reliability/pr-child.gitlab-ci.yml` (child pipeline generated for PRs carrying
the `test:reliability` label; same matrix, `RUNTIME=120`)

**Runs on:** amd64 and aarch64

This tier runs long-duration workloads designed to provoke probabilistic crashes and
stability regressions that bounded-time unit tests cannot reliably trigger.

### Reliability variants (`jit` and `memory`)

Runs `renaissance.jar akka-uct` under the profiler for `RUNTIME` seconds (default
3600 in the scheduled pipeline, overridable by a schedule variable; job timeout 6 h).
Tests `profiler` and `profiler+tracer` configurations against `gmalloc`, `jemalloc`,
and `tcmalloc` allocators. Detects crashes that require sustained JIT compilation
churn and GC pressure to manifest.

The `memory` variant additionally monitors RSS over time (via `memwatch.log`) and
runs `memory_trend_check.py` to detect upward memory trends.

### Chaos variant

`.gitlab/reliability/chaos_check.sh` is a thin CI wrapper around
`utils/run-chaos-harness.sh`, which patches a `dd-java-agent.jar` with the ddprof jar
under test and runs the `ddprof-stresstest` chaos harness (`src/chaos`) under
continuous antagonist load. Matrix: `profiler` / `profiler+tracer` × `gmalloc` /
`jemalloc` / `tcmalloc` × `CHAOS_JDK` (`21.0.3-tem`, `25.0.3-tem`).

Antagonists are implemented in `ddprof-stresstest/src/chaos/java/com/datadoghq/profiler/chaos/`
and selected by name in `Main.create()`. The default set is defined in
`utils/run-chaos-harness.sh` (`DEFAULT_ANTAGONISTS`); `trace-context` is only included
for `profiler+tracer` because `@Trace` is a no-op without the tracer. Examples:

| Antagonist | What it stresses |
|-----------|-----------------|
| `thread-churn` | Batches of short-lived threads (64 by default) racing signal delivery, stack walking and `RefCountGuard` slot allocation/release |
| `classloader-churn` | Rapid class definition and GC, `StringDictionary` insert/collect/clear races |
| `alloc-storm` | Continuous allocation pressure against the allocation profiler |
| `vthread-churn` | Virtual thread mount/unmount lifecycle against wall-clock profiling |
| `trace-context` | Trace context propagation under concurrent profiling (`profiler+tracer` only) |

See `Main.create()` for the complete list (`bounded-pool`, `context-hop`,
`consumer-group`, `hidden-class-churn`, `direct-memory`, `weakref-wave`, `dump-storm`,
`reapply-context-value`, `reference-chain-leak`, ...).

Failure criterion: a non-zero exit code (JVM crash), captured as an `hs_err.log`
artifact. Crashes are also reported to Slack.

No sanitizers are used. Tier 4 catches races that require hours at production-scale
concurrency to trigger with meaningful probability.

### JDK integration tests

`.gitlab/jdk-integration/.gitlab-ci.yml` handles upstream testing against custom JDK
builds. It is triggered externally (from the `async-profiler-build` pipeline) with
specific `JDK_VERSION`, `DEBUG_LEVEL`, and `HASH` parameters and runs `testDebug`
against that JDK build. This is used to validate compatibility with unreleased JDK
versions.

---

## Why the Split

| Bug class | Caught by |
|-----------|-----------|
| Data race in native data structures (signal handler vs. mutator) | Tier 1 — TSan gtest |
| Memory corruption in signal handler path | Tier 1 — ASan gtest |
| Memory error in JVMTI callback path | Tier 2 — ASan Java functional |
| Correctness regression (wrong profiling output) | Tier 2 — Java functional |
| Tracer / profiler incompatibility | Tier 3 — dd-trace integration |
| Probabilistic crash under sustained load | Tier 4 — chaos / reliability |
| JDK-version-specific crash | Tier 4 — JDK integration |

**Tier 1** provides the fastest feedback (every branch push, minutes). TSan without a JVM is
definitive for the class of race that has caused the most production crashes: signal
handlers accessing shared data structures concurrently with writers on other threads.

**Tier 2** covers correctness and integration with real JVM behaviour. Some paths
(actual `GetStackTrace` interleaving with class unload, real `SampledObjectAlloc`
callback ordering) are impractical to replicate in C++ unit tests.

**Tier 3** catches regressions in the tracer/profiler integration boundary that would
otherwise only surface after a combined dd-trace-java release.

**Tier 4** provides long-duration soak coverage at realistic concurrency levels,
catching races with per-second probability too low for any bounded CI window.

---

## Local Development

### Quick feedback cycle

```bash
# C++ unit tests — debug build, fast
./gradlew :ddprof-lib:gtestDebug

# Java functional tests — debug build
./gradlew :ddprof-test:testDebug

# Single test
./gradlew :ddprof-test:testDebug -Ptests=WallclockDumpSmokeTest
```

### Sanitizer builds

```bash
# C++ ASan + TSan (no JVM needed)
./gradlew :ddprof-lib:gtestAsan
./gradlew :ddprof-lib:gtestTsan

# Java functional tests under ASan (JVM required)
./gradlew :ddprof-test:testAsan -Pskip-gtest
```

### Coverage

```bash
# C++ (gcovr) + Java (JaCoCo) reports; needs gcovr 8.3+, gtest, make (Linux)
./gradlew :ddprof-lib:coverageReport -PenableCoverage
```

The C++ report covers only the `-O0 -DDEBUG` build. Prerequisites and limits are in
[CodeCoverage](CodeCoverage.md).

### Using containers to approximate CI

`utils/run-containers-tests.sh` defaults to Podman. On macOS use Docker through colima
(`--container=docker`): podman's credential-helper lookup for the Datadog registries
(ddtool) fails outside the CI network and aborts container commands. Run `./utils/run-containers-tests.sh --help` for the full flag list
(`--tests`, `--gtest`, `--gtest-task`, `--mount`, `--rebuild`, `--matrix`, ...).
Cached base images are reused until `--rebuild-base` (or `--rebuild`) is passed. Use it
after the base image's package list changes, e.g. to pick up gcovr for coverage runs.

```bash
# Matches the nightly configuration
./utils/run-containers-tests.sh --config=asan --jdk=21 --libc=glibc

# Debug build against a specific JDK
./utils/run-containers-tests.sh --config=debug --jdk=17-j9 --libc=glibc

# Musl build
./utils/run-containers-tests.sh --config=debug --jdk=21 --libc=musl

# Cross-architecture
./utils/run-containers-tests.sh --arch=aarch64 --config=asan --libc=glibc --jdk=21

# With C++ gtests enabled (disabled by default)
./utils/run-containers-tests.sh --config=asan --jdk=21 --libc=glibc --gtest

# Drop into a shell inside the container (SYS_PTRACE enabled for gdb)
./utils/run-containers-tests.sh --shell
```

### Running the chaos harness locally

```bash
# Build the ddprof jar under test
./gradlew :ddprof-lib:jar

# Run the harness: <runtime-seconds> [config] [allocator] [antagonists]
# (builds :ddprof-stresstest:chaosJar if missing; downloads dd-java-agent.jar)
./utils/run-chaos-harness.sh 300 profiler+tracer gmalloc
```

`run-chaos-harness.sh` uses `ddprof-lib/build/libs/ddprof-*.jar` when present and only
falls back to downloading from Maven snapshots when it is absent (which requires
`CURRENT_VERSION`). `CHAOS_JDK` selects/downloads a specific JDK; otherwise the `java`
on `PATH` is used. See the script header for the remaining env vars.
