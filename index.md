---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-13 13:30 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152980469](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152980469) | ❓ | main | - |
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
| 2026-11-13 | Integration | [#152980469](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152980469) | main | - | ❓ |
| 2026-11-13 | Integration | [#152972140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152972140) | main | - | ✅ |
| 2026-11-13 | Integration | [#152964657](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152964657) | main | - | ✅ |
| 2026-11-13 | Integration | [#152963659](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152963659) | main | - | ✅ |
| 2026-11-13 | Integration | [#152962739](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152962739) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
