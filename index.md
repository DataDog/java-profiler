---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-04-30 13:25 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#110692453](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110692453) | ✅ | main | - |
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
| 2026-04-30 | Integration | [#110692453](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110692453) | main | - | ✅ |
| 2026-04-30 | Integration | [#110685657](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110685657) | main | - | ✅ |
| 2026-04-30 | Integration | [#110656821](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110656821) | main | - | ✅ |
| 2026-04-30 | Integration | [#110649363](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110649363) | main | - | ✅ |
| 2026-04-30 | Integration | [#110610033](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/110610033) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
