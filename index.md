---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-08-17 15:56 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#131361534](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131361534) | ✅ | main | - |
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
| 2026-08-17 | Integration | [#131361534](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131361534) | main | - | ✅ |
| 2026-08-17 | Integration | [#131352864](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131352864) | main | - | ✅ |
| 2026-08-17 | Integration | [#131346449](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131346449) | main | - | ✅ |
| 2026-08-17 | Integration | [#131321900](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131321900) | main | - | ✅ |
| 2026-08-17 | Integration | [#131319877](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/131319877) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
