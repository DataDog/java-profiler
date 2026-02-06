---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-06 14:39 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#95000679](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95000679) | ⚠️ | zgu/validatedId | - |
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
| 2026-02-06 | Integration | [#95000679](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/95000679) | zgu/validatedId | - | ⚠️ |
| 2026-02-06 | Integration | [#94985044](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94985044) | jb/build_revamp | [#358](https://github.com/DataDog/java-profiler/pull/358) | ❓ |
| 2026-02-06 | Integration | [#94984980](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94984980) | jb/build_revamp | [#358](https://github.com/DataDog/java-profiler/pull/358) | ❓ |
| 2026-02-06 | Integration | [#94984937](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94984937) | jb/build_revamp | [#358](https://github.com/DataDog/java-profiler/pull/358) | ❓ |
| 2026-02-06 | Integration | [#94983737](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94983737) | main | - | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
