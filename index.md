---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-17 20:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138311778](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138311778) | ✅ | main | - |
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
| 2026-09-17 | Integration | [#138311778](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138311778) | main | - | ✅ |
| 2026-09-17 | Integration | [#138311719](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138311719) | main | - | ⚠️ |
| 2026-09-17 | Integration | [#138312057](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138312057) | main | - | ✅ |
| 2026-09-17 | Integration | [#138307129](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138307129) | main | - | ⚠️ |
| 2026-09-17 | Integration | [#138296866](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138296866) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
