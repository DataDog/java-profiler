---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-22 07:24 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114662140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114662140) | ❌ | main | - |
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
| 2026-05-22 | Integration | [#114662140](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114662140) | main | - | ❌ |
| 2026-05-22 | Integration | [#114660688](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114660688) | main | - | ❌ |
| 2026-05-22 | Integration | [#114660478](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114660478) | main | - | ❌ |
| 2026-05-22 | Integration | [#114659618](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114659618) | main | - | ❌ |
| 2026-05-21 | Integration | [#114531847](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114531847) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
