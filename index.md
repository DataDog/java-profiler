---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-01 11:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122058877](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122058877) | ❓ | main | - |
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
| 2026-07-01 | Integration | [#122058877](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122058877) | main | - | ❓ |
| 2026-07-01 | Integration | [#122053059](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122053059) | main | - | ❌ |
| 2026-07-01 | Integration | [#122052996](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122052996) | main | - | ❌ |
| 2026-07-01 | Integration | [#122048738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122048738) | main | - | ❌ |
| 2026-07-01 | Integration | [#122041942](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122041942) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
