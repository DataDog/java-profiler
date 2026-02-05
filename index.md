---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-05 09:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94814412](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94814412) | ⚠️ | jb/test_reports_ci | [#355](https://github.com/DataDog/java-profiler/pull/355) |
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
| 2026-02-05 | Integration | [#94814412](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94814412) | jb/test_reports_ci | [#355](https://github.com/DataDog/java-profiler/pull/355) | ⚠️ |
| 2026-02-05 | Integration | [#94779864](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94779864) | zgu/reduce-jmethodID | - | ✅ |
| 2026-02-04 | Integration | [#94693395](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94693395) | jb/test_reports_ci | [#355](https://github.com/DataDog/java-profiler/pull/355) | ✅ |
| 2026-02-04 | Integration | [#94687053](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94687053) | main | - | ✅ |
| 2026-02-04 | Integration | [#94677148](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94677148) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
