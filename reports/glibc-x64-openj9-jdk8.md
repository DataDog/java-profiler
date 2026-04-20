---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-20 10:05:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 16-23 cores)</summary>

```
1776693473 18
1776693478 16
1776693483 16
1776693488 23
1776693493 23
1776693498 23
1776693503 23
1776693508 23
1776693513 23
1776693518 23
1776693523 23
1776693528 23
1776693533 23
1776693538 21
1776693543 21
1776693548 21
1776693553 21
1776693558 22
1776693563 22
1776693568 22
```
</details>

---

