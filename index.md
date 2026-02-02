---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-02 17:03 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94138237](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94138237) | ⚠️ | jb/fp_safeaccess | - |
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
| 2026-02-02 | Integration | [#94138237](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94138237) | jb/fp_safeaccess | - | ⚠️ |
| 2026-02-02 | Integration | [#94141639](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94141639) | jb/fp_safeaccess | - | ❓ |
| 2026-02-02 | Integration | [#94100493](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94100493) | jb/fp_safeaccess | - | ⚠️ |
| 2026-02-02 | Integration | [#94088612](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94088612) | jb/fp_safeaccess | - | ✅ |
| 2026-02-02 | Integration | [#94074680](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94074680) | jb/fp_safeaccess | - | ❓ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
