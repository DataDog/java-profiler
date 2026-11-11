---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-11 18:18 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#152303776](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152303776) | ⚠️ | main | - |
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
| 2026-11-11 | Integration | [#152303776](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152303776) | main | - | ⚠️ |
| 2026-11-11 | Integration | [#152289832](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152289832) | main | - | ✅ |
| 2026-11-11 | Integration | [#152286515](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152286515) | main | - | ✅ |
| 2026-11-11 | Integration | [#152262609](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152262609) | main | - | ✅ |
| 2026-11-11 | Integration | [#152240814](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/152240814) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
