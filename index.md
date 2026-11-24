---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-11-24 14:59 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#156159671](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156159671) | ✅ | main | - |
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
| 2026-11-24 | Integration | [#156159671](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156159671) | main | - | ✅ |
| 2026-11-24 | Integration | [#156149374](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156149374) | main | - | ✅ |
| 2026-11-24 | Integration | [#156137886](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156137886) | main | - | ✅ |
| 2026-11-24 | Integration | [#156138445](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156138445) | main | - | ❓ |
| 2026-11-24 | Integration | [#156130808](https://gitlab.ddbuild.io/DataDog/java-profiler/-/pipelines/156130808) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
