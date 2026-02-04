---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-04 12:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94571316](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94571316) | ⚠️ | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) |
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
| 2026-02-04 | Integration | [#94571316](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94571316) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ⚠️ |
| 2026-02-03 | Integration | [#94391097](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94391097) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |
| 2026-02-03 | Integration | [#94389764](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94389764) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ⚠️ |
| 2026-02-03 | Integration | [#94383799](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94383799) | jb/fp_sanitation | [#351](https://github.com/DataDog/java-profiler/pull/351) | ✅ |
| 2026-02-03 | Integration | [#94382671](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94382671) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
