# Testing Guide

This document describes the complete test strategy for the java-profiler project:
what runs where, what each tier is designed to catch, and how to run each tier
locally.

## Overview

Tests are split across four tiers based on what they detect and what infrastructure
they require:

| Tier | System | When | Sanitizers | Purpose |
|------|--------|------|-----------|---------|
| **C++ unit tests** | GitLab | Every branch push | ASan + TSan | Data races and memory errors in native internals |
| **Java functional tests** | GitHub Actions | Nightly | ASan | Correctness + memory errors in JVMTI paths |
| **dd-trace integration** | GitLab | Every branch push | None | Compatibility with the tracer agent |
| **Chaos / reliability** | GitLab | Nightly scheduled | None | Long-duration stability and probabilistic crash detection |

---

## Tier 1 — C++ Unit Tests (Every Branch Push)

**Pipeline:** `.gitlab/sanitizer-tests/.gitlab-ci.yml`, `build` stage

**Jobs:** `gtest-asan-amd64`, `gtest-tsan-amd64`, `gtest-asan-arm64`, `gtest-tsan-arm64`

**Gradle tasks:** `:ddprof-lib:gtestAsan`, `:ddprof-lib:gtestTsan`

**Runs on:** amd64 and aarch64, using the standard `BUILD_IMAGE_X64` / `BUILD_IMAGE_ARM64`
images, on every branch push (same trigger as the dd-trace integration tests)

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
suppressions from earlier attempts; it exists for the benefit of any future JVM-level
TSan runs, but is not applied here since these tests never load a JVM.

**Why GitLab and not GitHub Actions:** TSan requires `vm.mmap_rnd_bits ≤ 28` and its
re-exec fallback (`personality(ADDR_NO_RANDOMIZE)`) to handle ASLR conflicts. GitHub
Actions' ubuntu-latest runners have `vm.mmap_rnd_bits=32` and their seccomp profile
blocks the `personality` syscall. The Datadog GitLab runners have stable kernel
settings tuned for benchmark workloads.

**Key test files:**

| File | Covers |
|------|--------|
| `dictionary_concurrent_ut.cpp` | Concurrent read/write/clear of `Dictionary` — the `std::_Rb_tree_increment` race path |
| `thread_teardown_safety_ut.cpp` | Signal delivery during `ProfiledThread` TLS clear and delete |
| `profiler_null_calltrace_buffer_ut.cpp` | Null calltrace buffer guard in the JVMTI sample path (PROF-14679) |
| `stress_callTraceStorage.cpp` | `CallTraceStorage` under concurrent write pressure |
| `test_callTraceStorage.cpp` | `CallTraceStorage` buffer swap correctness |
| `sigaction_interception_ut.cpp` | `sigaction` interception correctness and re-entrancy |
| `signalOrigin_ut.cpp` | Signal origin detection and classification |
| `spinlock_bounded_ut.cpp` | `SpinLock` / `BoundedOptionalSharedLockGuard` under contention |

**Local run:**
```bash
# Individual sanitizer configs
./gradlew :ddprof-lib:gtestAsan
./gradlew :ddprof-lib:gtestTsan

# All configs (debug, release, asan, tsan)
./gradlew :ddprof-lib:gtest

# Specific test
./gradlew :ddprof-lib:gtestAsan_dictionary_concurrent_ut
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

## Tier 2 — Java Functional Tests (Nightly)

**Workflow:** `.github/workflows/nightly.yml` → `test_workflow.yml`

**Gradle task:** `:ddprof-test:testAsan -Pskip-gtest`

**Runs on:** amd64 and aarch64 × glibc and musl ×
HotSpot / OpenJ9 / GraalVM / IBM / Liberica across JDK 8–25

**Triggers:** nightly at 03:00 UTC; also `workflow_dispatch` for manual runs

The Java functional tests run the profiler as a JVMTI agent attached to a real JVM
and assert correctness: allocation profiling reports the right classes, CPU samples
land on the right frames, class unloading is handled cleanly, wall-clock profiling
produces expected output.

ASan is applied here even though the JVM is not instrumented, because
`libjavaProfiler.so` is instrumented and ASan intercepts memory errors in JVMTI
callback paths — actual `GetStackTrace` calls, real `SampledObjectAlloc` events, real
class load/unload sequences — that cannot be fully replicated in C++ unit tests.

TSan is not run against the Java functional tests (see Tier 1 rationale above).

C++ gtests are skipped (`-Pskip-gtest`) because they already run on every PR in
Tier 1.

**Test configurations triggered by PR labels** (optional, in addition to the always-on
debug build):

| Label | Effect |
|-------|--------|
| `test:release` | Run Java functional tests with release library |
| `test:asan` | Run Java functional tests with ASan library on the PR |
| `test:tsan` | Run Java functional tests with TSan library on the PR (expect JVM false positives) |

**Local run:**
```bash
# Match the nightly configuration
./gradlew :ddprof-test:testAsan -Pskip-gtest

# Run against a specific JDK and libc via Docker (matches CI exactly)
./utils/run-docker-tests.sh --config=asan --jdk=21 --libc=glibc

# Run a single test
./gradlew :ddprof-test:testAsan -Ptests=AllocationProfilerTest -Pskip-gtest
```

On failure the workflow reports affected scenarios to Slack and uploads test reports
as artifacts.

---

## Tier 3 — dd-trace Integration Tests (GitLab, Every Push)

**Pipeline:** `.gitlab/dd-trace-integration/.gitlab-ci.yml`

**Runs on:** amd64 and aarch64 × glibc and musl × HotSpot + OpenJ9, JDK 8–25

**Triggers:** every branch push; skipped when `CI_PIPELINE_SOURCE` is
`merge_request_event` (GitLab merge-request pipeline) or when JDK integration
variables are set (`JDK_VERSION`, `DEBUG_LEVEL`, `HASH`, `DOWNSTREAM`)

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

## Tier 4 — Chaos and Reliability (GitLab, Nightly Scheduled)

**Pipeline:** `.gitlab/reliability/.gitlab-ci.yml`

**Runs on:** amd64 and aarch64, nightly via GitLab pipeline schedule

This tier runs long-duration workloads designed to provoke probabilistic crashes and
stability regressions that bounded-time unit tests cannot reliably trigger.

### Reliability variants (`jit` and `memory`)

Runs `renaissance.jar akka-uct` repeatedly under the profiler for up to 6 hours.
Tests `profiler` and `profiler+tracer` configurations against `gmalloc`, `jemalloc`,
and `tcmalloc` allocators. Detects crashes that require sustained JIT compilation
churn and GC pressure to manifest.

The `memory` variant additionally monitors RSS over time (via `memwatch.log`) and
runs `memory_trend_check.py` to detect upward memory trends.

### Chaos variant

Patches the latest `dd-java-agent.jar` with the locally built `ddprof.jar` (same
patch mechanism as Tier 3) and runs the `ddprof-stresstest` chaos harness under
continuous antagonist load:

| Antagonist | What it stresses |
|-----------|-----------------|
| `thread-churn` | 64 short-lived threads racing signal delivery, `RefCountGuard` slot allocation |
| `classloader-churn` | Rapid class definition and GC, `StringDictionary` insert/collect/clear races |
| `alloc-storm` | Continuous allocation pressure against the allocation profiler |
| `vthread-churn` | Virtual thread mount/unmount lifecycle against wall-clock profiling |
| `trace-context` | Trace context propagation under concurrent profiling (requires `profiler+tracer`) |

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

**Tier 1** provides the fastest feedback (every PR, minutes). TSan without a JVM is
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

### Using Docker to match CI exactly

```bash
# Matches the nightly configuration
./utils/run-docker-tests.sh --config=asan --jdk=21 --libc=glibc

# Debug build against a specific JDK
./utils/run-docker-tests.sh --config=debug --jdk=17-j9 --libc=glibc

# Musl build
./utils/run-docker-tests.sh --config=debug --jdk=21-librca --libc=musl

# With C++ gtests enabled (disabled by default in run-docker-tests.sh)
./utils/run-docker-tests.sh --config=asan --jdk=21 --libc=glibc --gtest
```

### Running the chaos harness locally

```bash
# Build the chaos jar (auto-detected by chaos_check.sh when present)
./gradlew :ddprof-stresstest:chaosJar

# Run the chaos check (uses the local build artifact; downloads dd-java-agent.jar)
.gitlab/reliability/chaos_check.sh 300 profiler+tracer gmalloc
```

`chaos_check.sh` looks for `ddprof-lib/build/libs/ddprof-*.jar` first and only
falls back to downloading from Maven snapshots if not found (requiring
`CURRENT_VERSION` to be set in that case). Build the jar locally to skip the
Maven download.
