---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-23 05:47:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 146 |
| Sample Rate | 2.43/sec |
| Health Score | 152% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 11 |
| Allocations | 168 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1787478204 24
1787478209 24
1787478214 24
1787478219 29
1787478224 29
1787478229 29
1787478234 29
1787478239 29
1787478244 29
1787478249 29
1787478254 29
1787478259 29
1787478264 29
1787478269 29
1787478274 29
1787478279 29
1787478284 29
1787478289 29
1787478294 29
1787478299 29
```
</details>

---

