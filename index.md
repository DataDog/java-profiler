---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-09 05:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#151339859](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151339859) | ✅ | main | - |
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
| 2026-11-09 | Integration | [#151339859](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151339859) | main | - | ✅ |
| 2026-11-08 | Integration | [#151318244](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151318244) | main | - | ✅ |
| 2026-11-08 | Integration | [#151314427](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151314427) | main | - | ✅ |
| 2026-11-08 | Integration | [#151293802](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151293802) | main | - | ✅ |
| 2026-11-07 | Integration | [#151258943](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/151258943) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
