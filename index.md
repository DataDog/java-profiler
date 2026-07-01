---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-01 09:26 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122048738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122048738) | ❌ | main | - |
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
| 2026-07-01 | Integration | [#122048738](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122048738) | main | - | ❌ |
| 2026-07-01 | Integration | [#122041942](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122041942) | main | - | ❌ |
| 2026-07-01 | Integration | [#122041327](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122041327) | main | - | ❌ |
| 2026-07-01 | Integration | [#122035445](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122035445) | main | - | ❌ |
| 2026-07-01 | Integration | [#122033114](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122033114) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
