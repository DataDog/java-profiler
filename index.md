---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-15 13:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#144929894](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144929894) | ⚠️ | main | - |
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
| 2026-10-15 | Integration | [#144929894](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144929894) | main | - | ⚠️ |
| 2026-10-15 | Integration | [#144896033](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144896033) | main | - | ✅ |
| 2026-10-15 | Integration | [#144875696](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144875696) | main | - | ⚠️ |
| 2026-10-15 | Integration | [#144848020](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144848020) | main | - | ✅ |
| 2026-10-15 | Integration | [#144836443](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/144836443) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
