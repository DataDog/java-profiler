---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1776693513 29
1776693518 29
1776693523 29
1776693528 29
1776693533 29
1776693538 27
1776693543 27
1776693548 27
1776693553 27
1776693558 27
1776693563 27
1776693568 27
1776693573 27
1776693578 27
1776693583 27
1776693588 27
1776693593 27
1776693598 27
1776693603 27
1776693608 27
```
</details>

---

