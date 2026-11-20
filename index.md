---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-20 16:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#155250697](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155250697) | ✅ | main | - |
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
| 2026-11-20 | Integration | [#155250697](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155250697) | main | - | ✅ |
| 2026-11-20 | Integration | [#155247182](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155247182) | main | - | ⚠️ |
| 2026-11-20 | Integration | [#155231125](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155231125) | main | - | ❓ |
| 2026-11-20 | Integration | [#155224250](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155224250) | main | - | ✅ |
| 2026-11-20 | Integration | [#155225536](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/155225536) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
