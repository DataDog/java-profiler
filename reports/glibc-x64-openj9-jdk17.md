---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 12:39:44 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1776962015 31
1776962020 31
1776962025 31
1776962030 31
1776962035 31
1776962040 31
1776962045 31
1776962050 31
1776962055 31
1776962060 31
1776962065 31
1776962070 31
1776962075 32
1776962080 32
1776962085 32
1776962090 32
1776962095 32
1776962100 32
1776962105 32
1776962110 32
```
</details>

---

