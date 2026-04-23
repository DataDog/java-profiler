---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 16:08:49 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776974317 64
1776974322 64
1776974327 64
1776974332 64
1776974337 64
1776974342 64
1776974347 64
1776974352 64
1776974357 64
1776974362 64
1776974367 64
1776974372 64
1776974377 64
1776974382 64
1776974387 64
1776974392 64
1776974397 64
1776974402 64
1776974407 64
1776974412 64
```
</details>

---

