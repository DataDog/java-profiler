---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-02 08:21 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#141862197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141862197) | ✅ | main | - |
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
| 2026-10-02 | Integration | [#141862197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141862197) | main | - | ✅ |
| 2026-10-02 | Integration | [#141845540](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141845540) | main | - | ✅ |
| 2026-10-01 | Integration | [#141767550](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141767550) | main | - | ⚠️ |
| 2026-10-01 | Integration | [#141651630](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141651630) | main | - | ⚠️ |
| 2026-10-01 | Integration | [#141648943](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/141648943) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
