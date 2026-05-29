---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-29 14:11 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#115903128](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115903128) | ❌ | main | - |
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
| 2026-05-29 | Integration | [#115903128](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115903128) | main | - | ❌ |
| 2026-05-29 | Integration | [#115899991](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115899991) | main | - | ❌ |
| 2026-05-29 | Integration | [#115896387](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115896387) | main | - | ❌ |
| 2026-05-29 | Integration | [#115892126](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115892126) | main | - | ❌ |
| 2026-05-29 | Integration | [#115883953](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/115883953) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
