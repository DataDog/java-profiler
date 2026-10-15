---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-15 16:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144992063](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144992063) | ⚠️ | main | - |
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
| 2026-10-15 | Integration | [#144992063](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144992063) | main | - | ⚠️ |
| 2026-10-15 | Integration | [#144989390](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144989390) | main | - | ✅ |
| 2026-10-15 | Integration | [#144969641](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144969641) | main | - | ✅ |
| 2026-10-15 | Integration | [#144966626](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144966626) | main | - | ✅ |
| 2026-10-15 | Integration | [#144942900](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144942900) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
