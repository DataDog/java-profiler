---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-03 11:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94286333](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94286333) | ✅ | main | - |
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
| 2026-02-03 | Integration | [#94286333](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94286333) | main | - | ✅ |
| 2026-02-03 | Integration | [#94278538](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94278538) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94274858](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94274858) | jb/fp_safeaccess | - | ✅ |
| 2026-02-03 | Integration | [#94270048](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94270048) | jb/fp_safeaccess | - | ✅ |
| 2026-02-03 | Integration | [#94267161](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94267161) | jb/fp_safeaccess | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
