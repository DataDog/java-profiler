---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-07-02 16:09 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#122403806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122403806) | ❌ | main | - |
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
| 2026-07-02 | Integration | [#122403806](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122403806) | main | - | ❌ |
| 2026-07-02 | Integration | [#122400168](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122400168) | main | - | ❌ |
| 2026-07-02 | Integration | [#122380761](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122380761) | main | - | ❌ |
| 2026-07-02 | Integration | [#122378757](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122378757) | main | - | ❌ |
| 2026-07-02 | Integration | [#122353172](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/122353172) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
