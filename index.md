---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-27 09:43 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121429800](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121429800) | ❌ | main | - |
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
| 2026-06-27 | Integration | [#121429800](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121429800) | main | - | ❌ |
| 2026-06-27 | Integration | [#121429053](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121429053) | main | - | ❌ |
| 2026-06-27 | Integration | [#121427762](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121427762) | main | - | ❓ |
| 2026-06-27 | Integration | [#121426740](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121426740) | main | - | ❓ |
| 2026-06-27 | Integration | [#121420645](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121420645) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
