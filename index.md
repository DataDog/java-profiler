---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-05 13:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#150556029](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150556029) | ❓ | main | - |
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
| 2026-11-05 | Integration | [#150556029](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150556029) | main | - | ❓ |
| 2026-11-05 | Integration | [#150548162](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150548162) | main | - | ❓ |
| 2026-11-05 | Integration | [#150548242](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150548242) | main | - | ❓ |
| 2026-11-05 | Integration | [#150541390](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150541390) | main | - | ✅ |
| 2026-11-05 | Integration | [#150533756](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/150533756) | main | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
