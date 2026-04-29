---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-29 18:43 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110534813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110534813) | ⚠️ | main | - |
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
| 2026-04-29 | Integration | [#110534813](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110534813) | main | - | ⚠️ |
| 2026-04-29 | Integration | [#110487437](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110487437) | main | - | ⚠️ |
| 2026-04-29 | Integration | [#110475387](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110475387) | main | - | ✅ |
| 2026-04-29 | Integration | [#110461194](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110461194) | main | - | ⚠️ |
| 2026-04-29 | Integration | [#110439601](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110439601) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
