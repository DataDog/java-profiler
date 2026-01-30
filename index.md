---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-01-30 11:15 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#93793548](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93793548) | ⚠️ | main | - |
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
| 2026-01-30 | Integration | [#93793548](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93793548) | main | - | ⚠️ |
| 2026-01-30 | Integration | [#93786301](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93786301) | main | - | ⚠️ |
| 2026-01-30 | Integration | [#93611036](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93611036) | main | - | ✅ |
| 2026-01-29 | Integration | [#93603477](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93603477) | main | - | ⚠️ |
| 2026-01-29 | Integration | [#93594940](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/93594940) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
