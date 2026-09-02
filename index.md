---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-02 05:58 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#134799105](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134799105) | ✅ | main | - |
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
| 2026-09-02 | Integration | [#134799105](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134799105) | main | - | ✅ |
| 2026-09-01 | Integration | [#134727916](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134727916) | main | - | ✅ |
| 2026-09-01 | Integration | [#134718965](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134718965) | main | - | ✅ |
| 2026-09-01 | Integration | [#134709197](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134709197) | main | - | ⚠️ |
| 2026-09-01 | Integration | [#134700654](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/134700654) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
