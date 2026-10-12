---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-12 13:14 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144085279](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144085279) | ✅ | main | - |
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
| 2026-10-12 | Integration | [#144085279](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144085279) | main | - | ✅ |
| 2026-10-12 | Integration | [#144068494](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144068494) | main | - | ✅ |
| 2026-10-12 | Integration | [#144038301](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144038301) | main | - | ✅ |
| 2026-10-12 | Integration | [#144026577](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144026577) | main | - | ✅ |
| 2026-10-12 | Integration | [#144020810](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144020810) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
