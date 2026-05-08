---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-08 04:55 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112140557](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112140557) | ❌ | main | - |
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
| 2026-05-08 | Integration | [#112140557](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112140557) | main | - | ❌ |
| 2026-05-07 | Integration | [#112127577](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112127577) | main | - | ✅ |
| 2026-05-07 | Integration | [#112124718](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112124718) | main | - | ❓ |
| 2026-05-07 | Integration | [#112114691](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112114691) | main | - | ⚠️ |
| 2026-05-07 | Integration | [#112113526](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112113526) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
