---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-06 00:52 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#150806686](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150806686) | ✅ | main | - |
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
| 2026-11-06 | Integration | [#150806686](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150806686) | main | - | ✅ |
| 2026-11-06 | Integration | [#150800907](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150800907) | main | - | ✅ |
| 2026-11-05 | Integration | [#150638437](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150638437) | main | - | ✅ |
| 2026-11-05 | Integration | [#150623745](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150623745) | main | - | ❓ |
| 2026-11-05 | Integration | [#150616171](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150616171) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
