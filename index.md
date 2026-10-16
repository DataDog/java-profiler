---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-16 13:11 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#145252332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145252332) | ⚠️ | main | - |
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
| 2026-10-16 | Integration | [#145252332](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145252332) | main | - | ⚠️ |
| 2026-10-16 | Integration | [#145233826](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145233826) | main | - | ❓ |
| 2026-10-16 | Integration | [#145224003](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145224003) | main | - | ✅ |
| 2026-10-16 | Integration | [#145211747](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145211747) | main | - | ✅ |
| 2026-10-16 | Integration | [#145205872](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/145205872) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
