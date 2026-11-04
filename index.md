---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-04 13:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#150144555](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150144555) | ✅ | main | - |
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
| 2026-11-04 | Integration | [#150144555](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150144555) | main | - | ✅ |
| 2026-11-04 | Integration | [#150131179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150131179) | main | - | ❓ |
| 2026-11-04 | Integration | [#150093154](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150093154) | main | - | ✅ |
| 2026-11-04 | Integration | [#150090698](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150090698) | main | - | ✅ |
| 2026-11-04 | Integration | [#150061483](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150061483) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
