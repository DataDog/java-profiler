---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:10:04 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 939 |
| Sample Rate | 15.65/sec |
| Health Score | 978% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (6 unique values: 64-79 cores)</summary>

```
1778187927 64
1778187932 70
1778187937 70
1778187942 70
1778187947 70
1778187952 76
1778187957 76
1778187962 76
1778187967 76
1778187972 76
1778187977 76
1778187982 76
1778187987 76
1778187992 76
1778187997 76
1778188002 76
1778188007 79
1778188012 79
1778188017 79
1778188022 75
```
</details>

---

