---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-29 10:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115844186](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115844186) | ❌ | main | - |
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
| 2026-05-29 | Integration | [#115844186](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115844186) | main | - | ❌ |
| 2026-05-29 | Integration | [#115836704](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115836704) | main | - | ❌ |
| 2026-05-29 | Integration | [#115835022](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115835022) | main | - | ❌ |
| 2026-05-29 | Integration | [#115833878](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115833878) | main | - | ❌ |
| 2026-05-29 | Integration | [#115829186](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115829186) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
