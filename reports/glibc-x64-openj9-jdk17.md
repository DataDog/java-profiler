---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-01 10:24:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 8 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 21-30 cores)</summary>

```
1790864349 27
1790864354 27
1790864359 27
1790864364 27
1790864369 27
1790864374 27
1790864379 27
1790864384 27
1790864389 27
1790864394 27
1790864399 30
1790864404 30
1790864409 30
1790864414 30
1790864419 30
1790864424 28
1790864429 28
1790864434 28
1790864439 28
1790864444 23
```
</details>

---

