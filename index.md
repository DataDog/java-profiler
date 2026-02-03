---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-03 16:36 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94364564](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94364564) | ✅ | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) |
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
| 2026-02-03 | Integration | [#94364564](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94364564) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94359256](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94359256) | jb/flaky_tests_1 | [#354](https://github.com/DataDog/java-profiler/pull/354) | ✅ |
| 2026-02-03 | Integration | [#94357394](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94357394) | zgu/reduce-jmethodID | - | ⚠️ |
| 2026-02-03 | Integration | [#94357776](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94357776) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94345460](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94345460) | jb/fp_sanitation | [#351](https://github.com/DataDog/java-profiler/pull/351) | ⚠️ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
