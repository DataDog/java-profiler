---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-05-12 09:49 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#112661173](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112661173) | ⚠️ | main | - |
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
| 2026-05-12 | Integration | [#112661173](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112661173) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112654515](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112654515) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112651347](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112651347) | main | - | ❌ |
| 2026-05-12 | Integration | [#112643645](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112643645) | main | - | ⚠️ |
| 2026-05-12 | Integration | [#112642973](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/112642973) | main | - | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
