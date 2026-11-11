---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-11 21:04 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152375794](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152375794) | ✅ | main | - |
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
| 2026-11-11 | Integration | [#152375794](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152375794) | main | - | ✅ |
| 2026-11-11 | Integration | [#152365142](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152365142) | main | - | ✅ |
| 2026-11-11 | Integration | [#152358103](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152358103) | main | - | ⚠️ |
| 2026-11-11 | Integration | [#152354884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152354884) | main | - | ⚠️ |
| 2026-11-11 | Integration | [#152353181](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152353181) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
