---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-05 15:13 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#117362440](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117362440) | ❌ | main | - |
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
| 2026-06-05 | Integration | [#117362440](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117362440) | main | - | ❌ |
| 2026-06-05 | Integration | [#117327085](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117327085) | main | - | ❌ |
| 2026-06-05 | Integration | [#117325900](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117325900) | main | - | ❌ |
| 2026-06-05 | Integration | [#117238027](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117238027) | main | - | ❌ |
| 2026-06-05 | Integration | [#117217179](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/117217179) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
