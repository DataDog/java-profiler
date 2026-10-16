---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-16 09:26 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#145200635](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145200635) | ❓ | main | - |
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
| 2026-10-16 | Integration | [#145200635](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145200635) | main | - | ❓ |
| 2026-10-16 | Integration | [#145194195](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145194195) | main | - | ✅ |
| 2026-10-16 | Integration | [#145194983](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145194983) | main | - | ⚠️ |
| 2026-10-16 | Integration | [#145186912](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145186912) | main | - | ✅ |
| 2026-10-16 | Integration | [#145182604](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145182604) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
