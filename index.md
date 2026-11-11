---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-11 09:41 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152169290](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152169290) | ✅ | main | - |
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
| 2026-11-11 | Integration | [#152169290](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152169290) | main | - | ✅ |
| 2026-11-11 | Integration | [#152139253](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152139253) | main | - | ✅ |
| 2026-11-11 | Integration | [#152112857](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152112857) | main | - | ✅ |
| 2026-11-11 | Integration | [#152103639](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152103639) | main | - | ✅ |
| 2026-11-11 | Integration | [#152102360](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152102360) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
