---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-24 22:40 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#126925971](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126925971) | ❌ | main | - |
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
| 2026-07-24 | Integration | [#126925971](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126925971) | main | - | ❌ |
| 2026-07-24 | Integration | [#126901028](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126901028) | main | - | ❌ |
| 2026-07-24 | Integration | [#126897385](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126897385) | main | - | ❓ |
| 2026-07-24 | Integration | [#126871458](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126871458) | main | - | ❌ |
| 2026-07-24 | Integration | [#126810764](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/126810764) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
