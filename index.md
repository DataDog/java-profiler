---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-10-21 15:27 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#146421032](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146421032) | ✅ | main | - |
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
| 2026-10-21 | Integration | [#146421032](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146421032) | main | - | ✅ |
| 2026-10-21 | Integration | [#146406950](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146406950) | main | - | ✅ |
| 2026-10-21 | Integration | [#146387489](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146387489) | main | - | ✅ |
| 2026-10-21 | Integration | [#146369710](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146369710) | main | - | ✅ |
| 2026-10-21 | Integration | [#146366596](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/146366596) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
