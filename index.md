---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-10 15:38 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#129974021](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129974021) | ✅ | main | - |
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
| 2026-08-10 | Integration | [#129974021](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129974021) | main | - | ✅ |
| 2026-08-10 | Integration | [#129957318](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129957318) | main | - | ❓ |
| 2026-08-10 | Integration | [#129935117](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129935117) | main | - | ✅ |
| 2026-08-10 | Integration | [#129929895](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129929895) | main | - | ✅ |
| 2026-08-10 | Integration | [#129923092](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/129923092) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
