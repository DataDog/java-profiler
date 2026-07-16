---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-16 12:57 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#124992958](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124992958) | ❌ | main | - |
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
| 2026-07-16 | Integration | [#124992958](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124992958) | main | - | ❌ |
| 2026-07-16 | Integration | [#124979884](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124979884) | main | - | ❌ |
| 2026-07-16 | Integration | [#124968735](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124968735) | main | - | ❌ |
| 2026-07-16 | Integration | [#124968653](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124968653) | main | - | ❌ |
| 2026-07-16 | Integration | [#124964281](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/124964281) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
