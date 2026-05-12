---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-12 19:31 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112804280](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112804280) | ❌ | main | - |
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
| 2026-05-12 | Integration | [#112804280](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112804280) | main | - | ❌ |
| 2026-05-12 | Integration | [#112801570](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112801570) | main | - | ❌ |
| 2026-05-12 | Integration | [#112800789](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112800789) | main | - | ❌ |
| 2026-05-12 | Integration | [#112771226](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112771226) | main | - | ❌ |
| 2026-05-12 | Integration | [#112765239](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112765239) | main | - | ❌ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
