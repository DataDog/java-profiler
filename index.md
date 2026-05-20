---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-20 09:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#114172328](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114172328) | ✅ | main | - |
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
| 2026-05-20 | Integration | [#114172328](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114172328) | main | - | ✅ |
| 2026-05-20 | Integration | [#114162286](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114162286) | main | - | ❌ |
| 2026-05-20 | Integration | [#114158409](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114158409) | main | - | ❌ |
| 2026-05-20 | Integration | [#114145373](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114145373) | main | - | ❌ |
| 2026-05-19 | Integration | [#114049889](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/114049889) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
