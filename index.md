---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-25 18:48 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156559444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156559444) | ⚠️ | main | - |
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
| 2026-11-25 | Integration | [#156559444](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156559444) | main | - | ⚠️ |
| 2026-11-25 | Integration | [#156559461](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156559461) | main | - | ✅ |
| 2026-11-25 | Integration | [#156559455](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156559455) | main | - | ✅ |
| 2026-11-25 | Integration | [#156557831](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156557831) | main | - | ✅ |
| 2026-11-25 | Integration | [#156557838](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156557838) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
