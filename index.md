---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-16 15:50 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#119136397](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119136397) | ❌ | main | - |
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
| 2026-06-16 | Integration | [#119136397](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119136397) | main | - | ❌ |
| 2026-06-16 | Integration | [#119115523](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119115523) | main | - | ❌ |
| 2026-06-16 | Integration | [#119084938](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119084938) | main | - | ❌ |
| 2026-06-16 | Integration | [#119083046](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119083046) | main | - | ❌ |
| 2026-06-16 | Integration | [#119076236](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/119076236) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
