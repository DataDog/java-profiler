---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-16 11:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#153462553](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153462553) | ❓ | main | - |
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
| 2026-11-16 | Integration | [#153462553](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153462553) | main | - | ❓ |
| 2026-11-16 | Integration | [#153453977](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153453977) | main | - | ✅ |
| 2026-11-16 | Integration | [#153447413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153447413) | main | - | ✅ |
| 2026-11-16 | Integration | [#153446868](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153446868) | main | - | ✅ |
| 2026-11-16 | Integration | [#153442544](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/153442544) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
