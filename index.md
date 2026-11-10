---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-10 22:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152060246](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152060246) | ✅ | main | - |
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
| 2026-11-10 | Integration | [#152060246](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152060246) | main | - | ✅ |
| 2026-11-10 | Integration | [#152050953](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152050953) | main | - | ✅ |
| 2026-11-10 | Integration | [#152045852](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152045852) | main | - | ✅ |
| 2026-11-10 | Integration | [#152045389](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152045389) | main | - | ⚠️ |
| 2026-11-10 | Integration | [#152040933](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152040933) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
