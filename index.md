---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-06 19:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151082451](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151082451) | ❓ | main | - |
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
| 2026-11-06 | Integration | [#151082451](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151082451) | main | - | ❓ |
| 2026-11-06 | Integration | [#151069630](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151069630) | main | - | ✅ |
| 2026-11-06 | Integration | [#151031792](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151031792) | main | - | ✅ |
| 2026-11-06 | Integration | [#150972421](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150972421) | main | - | ✅ |
| 2026-11-06 | Integration | [#150947506](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150947506) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
