---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-12 17:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152679416](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152679416) | ✅ | main | - |
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
| 2026-11-12 | Integration | [#152679416](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152679416) | main | - | ✅ |
| 2026-11-12 | Integration | [#152673326](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152673326) | main | - | ✅ |
| 2026-11-12 | Integration | [#152675630](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152675630) | main | - | ❓ |
| 2026-11-12 | Integration | [#152663499](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152663499) | main | - | ✅ |
| 2026-11-12 | Integration | [#152662042](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152662042) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
