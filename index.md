---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-03 15:07 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94333923](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94333923) | ✅ | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) |
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
| 2026-02-03 | Integration | [#94333923](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94333923) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94331282](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94331282) | jb/scanbuild_cleanup | [#353](https://github.com/DataDog/java-profiler/pull/353) | ⚠️ |
| 2026-02-03 | Integration | [#94328097](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94328097) | main | - | ⚠️ |
| 2026-02-03 | Integration | [#94327679](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94327679) | jb/scanbuild_cleanup | [#353](https://github.com/DataDog/java-profiler/pull/353) | ✅ |
| 2026-02-03 | Integration | [#94326135](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94326135) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
