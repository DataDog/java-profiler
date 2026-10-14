---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-14 12:32 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144588432](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144588432) | ✅ | main | - |
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
| 2026-10-14 | Integration | [#144588432](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144588432) | main | - | ✅ |
| 2026-10-14 | Integration | [#144559037](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144559037) | main | - | ❓ |
| 2026-10-14 | Integration | [#144539259](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144539259) | main | - | ✅ |
| 2026-10-14 | Integration | [#144535648](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144535648) | main | - | ✅ |
| 2026-10-14 | Integration | [#144531625](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144531625) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
