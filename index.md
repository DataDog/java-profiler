---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 06:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151738430](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151738430) | ✅ | main | - |
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
| 2026-11-10 | Integration | [#151738430](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151738430) | main | - | ✅ |
| 2026-11-09 | Integration | [#151705167](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151705167) | main | - | ✅ |
| 2026-11-09 | Integration | [#151703123](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151703123) | main | - | ✅ |
| 2026-11-09 | Integration | [#151670530](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151670530) | main | - | ⚠️ |
| 2026-11-09 | Integration | [#151643383](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151643383) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
