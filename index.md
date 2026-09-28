---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-28 01:22 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#140428993](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140428993) | ✅ | main | - |
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
| 2026-09-28 | Integration | [#140428993](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140428993) | main | - | ✅ |
| 2026-09-27 | Integration | [#140388467](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140388467) | main | - | ✅ |
| 2026-09-27 | Integration | [#140376772](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140376772) | main | - | ✅ |
| 2026-09-26 | Integration | [#140332295](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140332295) | main | - | ✅ |
| 2026-09-26 | Integration | [#140321259](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/140321259) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
