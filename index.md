---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-05 20:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94927555](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94927555) | ⚠️ | zgu/reduce-jmethodID | - |
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
| 2026-02-05 | Integration | [#94927555](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94927555) | zgu/reduce-jmethodID | - | ⚠️ |
| 2026-02-05 | Integration | [#94823236](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94823236) | main | - | ✅ |
| 2026-02-05 | Integration | [#94818116](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94818116) | jb/test_reports_ci | [#355](https://github.com/DataDog/java-profiler/pull/355) | ⚠️ |
| 2026-02-05 | Integration | [#94814412](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94814412) | jb/test_reports_ci | [#355](https://github.com/DataDog/java-profiler/pull/355) | ⚠️ |
| 2026-02-05 | Integration | [#94779864](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94779864) | zgu/reduce-jmethodID | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
