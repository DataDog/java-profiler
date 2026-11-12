---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:32:59 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 61-75 cores)</summary>

```
1794497310 61
1794497315 61
1794497320 61
1794497325 61
1794497330 61
1794497335 61
1794497340 61
1794497345 61
1794497350 61
1794497355 69
1794497360 69
1794497365 69
1794497370 69
1794497375 71
1794497380 71
1794497385 71
1794497390 71
1794497395 71
1794497400 71
1794497405 73
```
</details>

---

