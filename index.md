---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-28 22:13 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110300724](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110300724) | ✅ | main | - |
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
| 2026-04-28 | Integration | [#110300724](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110300724) | main | - | ✅ |
| 2026-04-28 | Integration | [#110292985](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110292985) | main | - | ✅ |
| 2026-04-28 | Integration | [#110258737](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110258737) | main | - | ✅ |
| 2026-04-28 | Integration | [#110207758](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110207758) | main | - | ✅ |
| 2026-04-28 | Integration | [#110204687](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110204687) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
