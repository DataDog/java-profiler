---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-22 16:29 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146786808](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146786808) | ✅ | main | - |
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
| 2026-10-22 | Integration | [#146786808](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146786808) | main | - | ✅ |
| 2026-10-22 | Integration | [#146774998](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146774998) | main | - | ✅ |
| 2026-10-22 | Integration | [#146766340](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146766340) | main | - | ✅ |
| 2026-10-22 | Integration | [#146741247](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146741247) | main | - | ✅ |
| 2026-10-22 | Integration | [#146735182](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146735182) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
