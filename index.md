---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-06-26 14:54 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#121301381](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121301381) | ❌ | main | - |
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
| 2026-06-26 | Integration | [#121301381](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121301381) | main | - | ❌ |
| 2026-06-26 | Integration | [#121293067](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121293067) | main | - | ❌ |
| 2026-06-26 | Integration | [#121288809](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121288809) | main | - | ❌ |
| 2026-06-26 | Integration | [#121256816](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121256816) | main | - | ❌ |
| 2026-06-26 | Integration | [#121234479](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/121234479) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
