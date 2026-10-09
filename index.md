---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-09 09:44 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#143642141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143642141) | ✅ | main | - |
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
| 2026-10-09 | Integration | [#143642141](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143642141) | main | - | ✅ |
| 2026-10-09 | Integration | [#143622413](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143622413) | main | - | ✅ |
| 2026-10-09 | Integration | [#143618433](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143618433) | main | - | ✅ |
| 2026-10-09 | Integration | [#143616743](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143616743) | main | - | ✅ |
| 2026-10-09 | Integration | [#143609172](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/143609172) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
