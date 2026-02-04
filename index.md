---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-04 18:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94677148](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94677148) | ✅ | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) |
| [Benchmarks](benchmarks/) | - | - | - | - |
| [Reliability](reliability/) | - | - | - | - |

---

## Test Types

### Integration Tests
dd-trace-java compatibility tests verifying profiler works correctly with the Datadog tracer.
Tests run on every main branch build across multiple JDK versions and platforms.

### Benchmarks
Performance regression testing using Renaissance benchmark suite.
Compares profiler overhead against baseline (no profiling).

### Reliability Tests
Long-running stability tests checking for memory leaks and crashes.
Tests multiple allocator configurations (gmalloc, tcmalloc, jemalloc).

---

## Recent Runs (All Types)

| Date | Type | Pipeline | Branch | PR | Status |
|------|------|----------|--------|-----|--------|
| 2026-02-04 | Integration | [#94677148](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94677148) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |
| 2026-02-04 | Integration | [#94622638](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94622638) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |
| 2026-02-04 | Integration | [#94613481](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94613481) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |
| 2026-02-04 | Integration | [#94597295](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94597295) | main | - | ✅ |
| 2026-02-04 | Integration | [#94590373](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94590373) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
