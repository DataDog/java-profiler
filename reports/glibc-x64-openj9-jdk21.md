---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 16:36:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 10 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 71-79 cores)</summary>

```
1791232292 79
1791232297 79
1791232302 71
1791232307 71
1791232312 71
1791232317 71
1791232322 71
1791232327 71
1791232332 71
1791232337 71
1791232342 71
1791232347 71
1791232352 71
1791232357 71
1791232362 71
1791232367 71
1791232372 71
1791232377 71
1791232382 71
1791232387 71
```
</details>

---

