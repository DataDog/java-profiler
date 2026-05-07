---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-07 14:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112004466](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112004466) | ✅ | main | - |
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
| 2026-05-07 | Integration | [#112004466](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112004466) | main | - | ✅ |
| 2026-05-07 | Integration | [#111992351](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111992351) | main | - | ❓ |
| 2026-05-07 | Integration | [#111975452](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111975452) | main | - | ✅ |
| 2026-05-07 | Integration | [#111967096](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111967096) | main | - | ❓ |
| 2026-05-07 | Integration | [#111956950](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/111956950) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
