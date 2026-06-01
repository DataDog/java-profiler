---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-01 13:37 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#116227200](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116227200) | ❌ | main | - |
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
| 2026-06-01 | Integration | [#116227200](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116227200) | main | - | ❌ |
| 2026-06-01 | Integration | [#116224294](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116224294) | main | - | ❌ |
| 2026-06-01 | Integration | [#116223109](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116223109) | main | - | ❌ |
| 2026-06-01 | Integration | [#116211328](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116211328) | main | - | ❓ |
| 2026-06-01 | Integration | [#116202000](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/116202000) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
