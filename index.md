---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-21 08:45 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#138770119](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138770119) | ✅ | main | - |
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
| 2026-09-21 | Integration | [#138770119](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138770119) | main | - | ✅ |
| 2026-09-21 | Integration | [#138770145](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138770145) | main | - | ✅ |
| 2026-09-21 | Integration | [#138770177](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138770177) | main | - | ✅ |
| 2026-09-21 | Integration | [#138770194](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138770194) | main | - | ✅ |
| 2026-09-21 | Integration | [#138757990](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/138757990) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
