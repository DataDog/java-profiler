---
layout: default
title: Java Profiler Build - Test Dashboard
---

# Java Profiler Build - Test Dashboard

> **Last Updated:** 2026-02-03 13:38 UTC

## Quick Status

| Test Type | Latest | Status | Branch | PR |
|-----------|--------|--------|--------|-----|
| [Integration](integration/) | [#94311785](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94311785) | ✅ | main | - |
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
| 2026-02-03 | Integration | [#94311785](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94311785) | main | - | ✅ |
| 2026-02-03 | Integration | [#94309907](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94309907) | jb/flaky_tests | [#352](https://github.com/DataDog/java-profiler/pull/352) | ⚠️ |
| 2026-02-03 | Integration | [#94308035](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94308035) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94292253](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94292253) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |
| 2026-02-03 | Integration | [#94303091](https://gitlab.ddbuild.io/DataDog/apm-reliability/async-profiler-build/-/pipelines/94303091) | jb/fp_safeaccess | [#349](https://github.com/DataDog/java-profiler/pull/349) | ✅ |

---

[Repository](https://github.com/DataDog/java-profiler) | [java-profiler](https://github.com/DataDog/java-profiler) | [View history](https://github.com/DataDog/java-profiler/commits/gh-pages)
