---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-07 17:44 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112053680](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112053680) | ✅ | main | - |
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
| 2026-05-07 | Integration | [#112053680](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112053680) | main | - | ✅ |
| 2026-05-07 | Integration | [#112047457](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112047457) | main | - | ✅ |
| 2026-05-07 | Integration | [#112046741](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112046741) | main | - | ✅ |
| 2026-05-07 | Integration | [#112041657](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112041657) | main | - | ✅ |
| 2026-05-07 | Integration | [#112037394](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112037394) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
