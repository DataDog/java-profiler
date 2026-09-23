---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-09-23 14:08 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#139487460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139487460) | ✅ | main | - |
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
| 2026-09-23 | Integration | [#139487460](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139487460) | main | - | ✅ |
| 2026-09-23 | Integration | [#139480035](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139480035) | main | - | ✅ |
| 2026-09-23 | Integration | [#139465338](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139465338) | main | - | ✅ |
| 2026-09-23 | Integration | [#139464663](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139464663) | main | - | ✅ |
| 2026-09-23 | Integration | [#139452779](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/139452779) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
